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
using System.Runtime.InteropServices;

namespace Samp_Injector_CSharp;

internal static unsafe partial class Native_Imports {
    private const string KERNEL32 = Constants.KERNEL32_DLL;
    
    internal static readonly IntPtr s_kernel32_handle = NativeLibrary.Load(KERNEL32);
    internal static readonly IntPtr load_library_address = NativeLibrary.GetExport(s_kernel32_handle, Constants.LOAD_LIBRARY_FUNC);
    
    [LibraryImport(KERNEL32, SetLastError = true)]
    internal static partial int ResumeThread(SafeThreadHandle hThread);

    [LibraryImport(KERNEL32, SetLastError = true)]
    internal static partial IntPtr VirtualAllocEx(SafeProcessHandle hProcess, IntPtr lpAddress, uint dwSize, uint flAllocationType, uint flProtect);

    [LibraryImport(KERNEL32, SetLastError = true)]
    [return: MarshalAs(UnmanagedType.Bool)]
    internal static partial bool VirtualFreeEx(SafeProcessHandle hProcess, IntPtr lpAddress, int dwSize, uint dwFreeType);
    
    [LibraryImport(KERNEL32, SetLastError = true)]
    [return: MarshalAs(UnmanagedType.Bool)]
    internal static partial bool WriteProcessMemory(SafeProcessHandle hProcess, IntPtr lpBaseAddress, ref byte lpBuffer, uint nSize, out IntPtr lpNumberOfBytesWritten);

    [LibraryImport(KERNEL32, SetLastError = true)]
    internal static partial IntPtr CreateRemoteThread(SafeProcessHandle hProcess, IntPtr lpThreadAttributes, uint dwStackSize, IntPtr lpStartAddress, IntPtr lpParameter, uint dwCreationFlags, IntPtr lpThreadId);
    
    [LibraryImport(KERNEL32, SetLastError = true)]
    internal static partial uint WaitForSingleObject(IntPtr hHandle, uint dwMilliseconds);

    [LibraryImport(KERNEL32, SetLastError = true)]
    [return: MarshalAs(UnmanagedType.Bool)]
    internal static partial bool GetExitCodeThread(IntPtr hThread, out uint lpExitCode);

    [LibraryImport(KERNEL32, SetLastError = true)]
    [return: MarshalAs(UnmanagedType.Bool)]
    internal static partial bool CloseHandle(IntPtr hObject);

    [LibraryImport(KERNEL32, SetLastError = true)]
    [return: MarshalAs(UnmanagedType.Bool)]
    internal static partial bool TerminateProcess(SafeProcessHandle hProcess, uint uExitCode);

    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi)]
    internal struct Startup_Info {
        public int cb;
        public string lpReserved;
        public string lpDesktop;
        public string lpTitle;
        public int dwX;
        public int dwY;
        public int dwXSize;
        public int dwYSize;
        public int dwXCountChars;
        public int dwYCountChars;
        public int dwFillAttribute;
        public int dwFlags;
        public short wShowWindow;
        public short cbReserved2;
        public IntPtr lpReserved2;
        public IntPtr hStdInput;
        public IntPtr hStdOutput;
        public IntPtr hStdError;
    }

    [StructLayout(LayoutKind.Sequential)]
    internal struct Process_Information {
        public IntPtr hProcess;
        public IntPtr hThread;
        public int dwProcessId;
        public int dwThreadId;
    }

    [DllImport(KERNEL32, SetLastError = true, CharSet = CharSet.Ansi)]
    [return: MarshalAs(UnmanagedType.Bool)]
    internal static extern bool CreateProcessA(
        string? lpApplicationName,
        byte* lpCommandLine,
        IntPtr lpProcessAttributes,
        IntPtr lpThreadAttributes,
        [MarshalAs(UnmanagedType.Bool)] bool bInheritHandles,
        uint dwCreationFlags,
        IntPtr lpEnvironment,
        string? lpCurrentDirectory,
        ref Startup_Info lpStartupInfo,
        out Process_Information lpProcessInformation
    );
}