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

#include <string>
#include <memory>
#include <functional>
#include <windows.h>
//
#include "constants.hpp"
#include "error_utils.hpp"
#include "resource_handle.hpp"
#include "types.hpp"
#include "version.hpp"
//
#if defined(SAMP_INJECTOR_CXX_MODERN)
    #include <optional>
#endif

class Process {
    public:
        Process() = default;
        Process(const Process&) = delete;
        Process& operator=(const Process&) = delete;
        Process(Process&&) = default;
        Process& operator=(Process&&) = default;
        ~Process() = default;

        struct Process_Info {
            Resource_Handle::Unique_Resource<HANDLE, std::function<void(HANDLE)>> process_handle;
            Resource_Handle::Unique_Resource<HANDLE, std::function<void(HANDLE)>> thread_handle;

            bool Resume() {
                return thread_handle && ResumeThread(thread_handle.get()) != static_cast<DWORD>(-1);
            }
        };
        
        enum class Injection_Status {
            SUCCESS,
            ALLOCATION_FAILED,
            WRITE_FAILED,
            KERNEL32_HANDLE_FAILED,
            LOADLIBRARY_ADDRESS_FAILED,
            THREAD_CREATION_FAILED,
            THREAD_WAIT_FAILED,
            GET_EXIT_CODE_FAILED,
            INJECTION_RETURNED_ERROR
        };

#if defined(SAMP_INJECTOR_CXX_MODERN)
        std::optional<Process_Info> Create_Game_Process(const std::wstring& game_path, std::wstring& command_args, const std::wstring& working_dir) {
#elif defined(SAMP_INJECTOR_CXX_14)
        std::unique_ptr<Process_Info> Create_Game_Process(const std::wstring& game_path, std::wstring& command_args, const std::wstring& working_dir) {
#endif
            STARTUPINFOW startup_info{};
            startup_info.cb = sizeof(STARTUPINFOW);
            PROCESS_INFORMATION process_info{};

            bool success = CreateProcessW(game_path.c_str(), command_args.empty() ? nullptr : &command_args[0], nullptr, nullptr, FALSE, Constants::PROCESS_CREATION_FLAGS, nullptr, working_dir.c_str(), &startup_info, &process_info);

            if (!success) {
                std::wstring error_msg = Error_Utils::Get_System_Error_Message(GetLastError());
                Error_Utils::Show_Error(L"Failed to create game process. Ensure 'gta_sa.exe' is not running and you have " L"sufficient permissions to execute the file. System Error: " + error_msg, Types::Inject_Type::SAMP);

#if defined(SAMP_INJECTOR_CXX_MODERN)
                return std::nullopt;
#elif defined(SAMP_INJECTOR_CXX_14)
                return nullptr;
#endif
            }

#if defined(SAMP_INJECTOR_CXX_MODERN)
            return Process_Info{
                Resource_Handle::Make_Unique_Handle(process_info.hProcess),
                Resource_Handle::Make_Unique_Handle(process_info.hThread)
            };
#elif defined(SAMP_INJECTOR_CXX_14)
            auto info = std::unique_ptr<Process_Info>(new Process_Info());
            info->process_handle = Resource_Handle::Make_Unique_Handle(process_info.hProcess);
            info->thread_handle = Resource_Handle::Make_Unique_Handle(process_info.hThread);
            
            return info;
#endif
        }
        
        SAMP_INJECTOR_NODISCARD
        Injection_Status Inject_DLL(HANDLE process, const std::wstring& DLL_path) {
            static const LPVOID load_library_addr = reinterpret_cast<LPVOID>(GetProcAddress(GetModuleHandleW(Constants::KERNEL32_DLL), Constants::LOAD_LIBRARY_FUNC));

            if (!load_library_addr)
                return Injection_Status::LOADLIBRARY_ADDRESS_FAILED;

            const size_t dll_path_size = (DLL_path.length() + 1) * sizeof(wchar_t);
            LPVOID remote_memory = VirtualAllocEx(process, nullptr, dll_path_size, Constants::MEMORY_ALLOCATION_TYPE, Constants::MEMORY_PROTECTION);

            if (!remote_memory)
                return Injection_Status::ALLOCATION_FAILED;

            auto memory_guard = Resource_Handle::Unique_Resource<LPVOID, std::function<void(LPVOID)>>(remote_memory, [process](LPVOID ptr) {
                if (ptr)
                    VirtualFreeEx(process, ptr, 0, MEM_RELEASE);
            });

            if (!WriteProcessMemory(process, remote_memory, DLL_path.c_str(), dll_path_size, nullptr)) 
                return Injection_Status::WRITE_FAILED;

            HANDLE remote_thread = CreateRemoteThread(process, nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(load_library_addr), remote_memory, 0, nullptr);

            if (!remote_thread)
                return Injection_Status::THREAD_CREATION_FAILED;

            auto thread_guard = Resource_Handle::Make_Unique_Handle(remote_thread);

            if (WaitForSingleObject(remote_thread, Constants::DLL_INJECTION_TIMEOUT_MS) != WAIT_OBJECT_0)
                return Injection_Status::THREAD_WAIT_FAILED;

            DWORD exit_code = 0;

            if (!GetExitCodeThread(remote_thread, &exit_code))
                return Injection_Status::GET_EXIT_CODE_FAILED;
            
            if (exit_code == 0)
                return Injection_Status::INJECTION_RETURNED_ERROR;

            return Injection_Status::SUCCESS;
        }
};