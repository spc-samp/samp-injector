/* ============================================================================= *
 * SA-MP Injector - C# injection ↓                                               *
 * library for SA-MP (San Andreas Multiplayer) and OMP (Open Multiplayer)        *
 * ============================================================================= *
 *                                                                               *
 * Copyright (c) 2025, SPC (SA-MP Programming Community)                         *
 * All rights reserved.                                                          *
 *                                                                               *
 * Developed by: Calasans                                                        *
 * Repository: https://github.com/spc-samp/samp-injector                         *
 *                                                                               *
 * ============================================================================= *
 *                                                                               *
 * Licensed under the MIT License (MIT);                                         *
 * you may not use this file except in compliance with the License.              *
 * You may obtain a copy of the License at:                                      *
 *                                                                               *
 *     https://opensource.org/licenses/MIT                                       *
 *                                                                               *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR    *
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,      *
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE   *
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER        *
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, *
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN     *
 * THE SOFTWARE.                                                                 *
 *                                                                               *
 * ============================================================================= */

using System;
using System.ComponentModel;
using System.IO;
using System.Runtime.InteropServices;
using System.Text;

namespace Samp_Injector_CSharp;

internal static unsafe partial class Process_Handler {
    internal readonly record struct Process_Info(SafeProcessHandle ProcessHandle, SafeThreadHandle ThreadHandle) : IDisposable {
        public bool IsInvalid => ProcessHandle.IsInvalid || ThreadHandle.IsInvalid;

        public void Dispose() {
            ProcessHandle?.Dispose();
            ThreadHandle?.Dispose();
        }
    }

    private static int Build_Full_Command_Args_ANSI(Span<byte> destination, string executable_path, string nickname, string ip, string port, string password) {
        int pos = 0;
        
        pos += Encoding.ASCII.GetBytes($"\"{executable_path}\" ", destination.Slice(pos));
        pos += Encoding.ASCII.GetBytes(Constants.CMD_ARGS_PART1, destination.Slice(pos));
        pos += Encoding.ASCII.GetBytes(nickname, destination.Slice(pos));
        pos += Encoding.ASCII.GetBytes(Constants.CMD_ARGS_PART2, destination.Slice(pos));
        pos += Encoding.ASCII.GetBytes(ip, destination.Slice(pos));
        pos += Encoding.ASCII.GetBytes(Constants.CMD_ARGS_PART3, destination.Slice(pos));
        pos += Encoding.ASCII.GetBytes(port, destination.Slice(pos));
        
        if (!string.IsNullOrEmpty(password)) {
            pos += Encoding.ASCII.GetBytes(Constants.CMD_ARGS_PART4_PASSWORD, destination.Slice(pos));
            pos += Encoding.ASCII.GetBytes(password, destination.Slice(pos));
        }

        destination[pos] = 0;

        return pos;
    }
    
    internal static Process_Info Create_Game_Process(string game_path, string working_dir, string nickname, string ip, string port, string password, out string error_message) {
        var startup_info = new Native_Imports.Startup_Info();
        startup_info.cb = Marshal.SizeOf(startup_info);
        
        bool has_password = !string.IsNullOrEmpty(password);
        int cmd_line_byte_length = $"\"{game_path}\" ".Length + Constants.CMD_ARGS_BASE_LENGTH + Encoding.ASCII.GetByteCount(nickname) + Encoding.ASCII.GetByteCount(ip) + Encoding.ASCII.GetByteCount(port)
            + (has_password ? Constants.CMD_ARG_PASSWORD_LENGTH + Encoding.ASCII.GetByteCount(password) : 0);

        Span<byte> cmd_line_ANSI_buffer = stackalloc byte[cmd_line_byte_length + 1];

        Build_Full_Command_Args_ANSI(cmd_line_ANSI_buffer, game_path, nickname, ip, port, password);

        fixed (byte* p_cmd_line = &MemoryMarshal.GetReference(cmd_line_ANSI_buffer)) {
            if (!Native_Imports.CreateProcessA(null, p_cmd_line, IntPtr.Zero, IntPtr.Zero, false, Constants.PROCESS_CREATION_FLAGS, IntPtr.Zero, working_dir, ref startup_info, out var process_info)) {
                error_message = $"Failed to create game process. Ensure 'gta_sa.exe' is not running and you have sufficient permissions to execute the file. System Error: {new Win32Exception(Marshal.GetLastWin32Error()).Message}";
                
                return new Process_Info(new SafeProcessHandle(), new SafeThreadHandle());
            }

            error_message = string.Empty;
            
            return new Process_Info(new SafeProcessHandle(process_info.hProcess), new SafeThreadHandle(process_info.hThread));
        }
    }
    
    internal static bool Inject_DLL(SafeProcessHandle process_handle, string dll_path, out string error_message) {
        int byte_count = Encoding.ASCII.GetByteCount(dll_path);
        Span<byte> dll_path_bytes = stackalloc byte[byte_count + 1];
        Encoding.ASCII.GetBytes(dll_path, dll_path_bytes);
        dll_path_bytes[byte_count] = 0;

        IntPtr remote_memory = IntPtr.Zero;
        IntPtr remote_thread = IntPtr.Zero;

        try {
            if (Native_Imports.s_kernel32_handle == IntPtr.Zero)
                return (error_message = "Failed to obtain a handle to kernel32.dll. This is an essential system library and this error indicates a severe system issue.") != null && false;

            IntPtr load_library_addr = Native_Imports.load_library_address;

            if (load_library_addr == IntPtr.Zero)
                return (error_message = "Failed to find the address of the LoadLibraryA function in kernel32.dll. This is critical for injecting the DLL.") != null && false;

            remote_memory = Native_Imports.VirtualAllocEx(process_handle, IntPtr.Zero, (uint)dll_path_bytes.Length, Constants.MEMORY_ALLOCATION_TYPE, Constants.MEMORY_PROTECTION);

            if (remote_memory == IntPtr.Zero)
                return (error_message = "Failed to allocate memory in the target process. This might be due to insufficient permissions or process protection mechanisms.") != null && false;

            if (!Native_Imports.WriteProcessMemory(process_handle, remote_memory, ref MemoryMarshal.GetReference(dll_path_bytes), (uint)dll_path_bytes.Length, out _))
                return (error_message = "Failed to write DLL path to the target process memory. Verify process permissions and ensure the DLL path is accessible.") != null && false;

            remote_thread = Native_Imports.CreateRemoteThread(process_handle, IntPtr.Zero, 0, load_library_addr, remote_memory, 0, IntPtr.Zero);

            if (remote_thread == IntPtr.Zero)
                return (error_message = $"Failed to create a remote thread in the target process to execute the DLL injection. This could be due to security restrictions or process state. System Error: {new Win32Exception(Marshal.GetLastWin32Error()).Message}") != null && false;

            uint wait_result = Native_Imports.WaitForSingleObject(remote_thread, Constants.DLL_INJECTION_TIMEOUT_MS);
            
            if (wait_result != 0)
                return (error_message = $"Timeout or error waiting for DLL injection to complete. System Error: {new Win32Exception(Marshal.GetLastWin32Error()).Message}") != null && false;

            if (!Native_Imports.GetExitCodeThread(remote_thread, out uint exit_code) || exit_code == 0)
                return (error_message = "DLL injection failed or returned an error. The LoadLibrary call may have failed in the target process.") != null && false;

            error_message = string.Empty;

            return true;
        }
        finally {
            if (remote_memory != IntPtr.Zero)
                Native_Imports.VirtualFreeEx(process_handle, remote_memory, 0, Constants.MEM_RELEASE);
            
            if (remote_thread != IntPtr.Zero)
                Native_Imports.CloseHandle(remote_thread);
        }
    }

    internal static bool Resume_Game_Thread(SafeThreadHandle thread_handle, out string error_message) {
        if (Native_Imports.ResumeThread(thread_handle) == -1)
            return (error_message = $"Failed to resume the game process thread: {new Win32Exception(Marshal.GetLastWin32Error()).Message}") != null && false;

        error_message = string.Empty;
        
        return true;
    }
}