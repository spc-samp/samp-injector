/* ============================================================================= *
 * SA-MP Injector - C++ injection ↓                                              *
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

#pragma once

#include <string_view>
#include <optional>
#include <functional>
#include <windows.h>
#include <memory>
#include <vector>
//
#include "resource_handle.hpp"
#include "error_utils.hpp"
#include "constants.hpp"
#include "types.hpp"

class Process {
    public:
        Process() = default;
        Process(const Process&) = delete;
        Process& operator=(const Process&) = delete;
        Process(Process&&) = default;
        Process& operator=(Process&&) = default;
        ~Process() = default;

        struct Process_Info {
            Resource_Handle::UniqueResource<HANDLE, std::function<void(HANDLE)>> process_handle;
            Resource_Handle::UniqueResource<HANDLE, std::function<void(HANDLE)>> thread_handle;
        };

        std::optional<Process_Info> Create_Game_Process(std::string_view game_path, std::string_view command_args, std::string_view working_dir) {
            STARTUPINFOA startup_info{};
            startup_info.cb = sizeof(STARTUPINFOA);

            PROCESS_INFORMATION process_info{};

            std::vector<char> args_buffer(command_args.size() + 1);

            if (!command_args.empty()) {
                std::memcpy(args_buffer.data(), command_args.data(), command_args.size());
                args_buffer[command_args.size()] = '\0';
            }

            bool success = CreateProcessA(game_path.data(), args_buffer.empty() ? nullptr : args_buffer.data(), nullptr, nullptr, FALSE, Constants::PROCESS_CREATION_FLAGS, nullptr, 
                working_dir.empty() ? nullptr : working_dir.data(), &startup_info, &process_info);

            if (!success) {
                std::wstring error_msg = Error_Utils::Get_System_Error_Message(GetLastError());
                Error_Utils::Show_Error(L"Failed to create game process. Ensure 'gta_sa.exe' is not running and you have " L"sufficient permissions to execute the file. System Error: " + error_msg,
                    Types::Inject_Type::SAMP);
                
                return std::nullopt;
            }

            Process_Info result;
            result.process_handle = Resource_Handle::Make_Unique_Handle(process_info.hProcess);
            result.thread_handle = Resource_Handle::Make_Unique_Handle(process_info.hThread);

            return result;
        }

        bool Inject_DLL(HANDLE process, std::string_view DLL_path, std::wstring& error_message) {
            LPVOID remote_memory = VirtualAllocEx(process, nullptr, DLL_path.size() + 1, Constants::MEMORY_ALLOCATION_TYPE, Constants::MEMORY_PROTECTION);

            if (!remote_memory)
                return (error_message = L"Failed to allocate memory in the target process. This might be due to " L"insufficient permissions or process protection mechanisms.", false);

            auto memory_guard = Resource_Handle::UniqueResource<LPVOID, std::function<void(LPVOID)>>(remote_memory, [process](LPVOID ptr) {
                if (ptr)
                    VirtualFreeEx(process, ptr, 0, MEM_RELEASE);
            });

            if (!WriteProcessMemory(process, remote_memory, DLL_path.data(), DLL_path.size() + 1, nullptr))
                return (error_message = L"Failed to write DLL path to the target process memory. Verify process " L"permissions and ensure the DLL path is accessible.", false);

            HMODULE kernel32 = GetModuleHandleA(Constants::KERNEL32_DLL);

            if (!kernel32)
                return (error_message = L"Failed to obtain a handle to kernel32.dll. This is an essential system " L"library and this error indicates a severe system issue.", false);

            LPVOID load_library_addr = reinterpret_cast<LPVOID>(GetProcAddress(kernel32, Constants::LOAD_LIBRARY_FUNC));

            if (!load_library_addr)
                return (error_message = L"Failed to find the address of the LoadLibraryA function in kernel32.dll. " L"This is critical for injecting the DLL.", false);

            HANDLE remote_thread = CreateRemoteThread(process, nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(load_library_addr), remote_memory, 0, nullptr);

            if (!remote_thread)
                return (error_message = L"Failed to create a remote thread in the target process to execute the " L"DLL injection. This could be due to security restrictions or process "
                    L"state. System Error: " + Error_Utils::Get_System_Error_Message(GetLastError()), false);

            auto thread_guard = Resource_Handle::Make_Unique_Handle(remote_thread);

            DWORD wait_result = WaitForSingleObject(remote_thread, Constants::DLL_INJECTION_TIMEOUT_MS);

            if (wait_result != WAIT_OBJECT_0)
                return (error_message = L"Timeout or error waiting for DLL injection to complete. " L"System Error: " + Error_Utils::Get_System_Error_Message(GetLastError()), false);

            DWORD exit_code = 0;

            if (!GetExitCodeThread(remote_thread, &exit_code) || exit_code == 0)
                return (error_message = L"DLL injection failed or returned an error. The LoadLibrary call " L"may have failed in the target process.", false);

            return true;
        }
};