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
#include <vector>
//
#include "constants.hpp"
#include "error_utils.hpp"
#include "privileges.hpp"
#include "process.hpp"
#include "types.hpp"
#include "validation.hpp"
#include "version.hpp"
//
#if defined(SAMP_INJECTOR_CXX_MODERN)
    #include <string_view>
    #include <filesystem>
#endif

namespace Injector {
    class Injector_Core {
        public:
            Injector_Core() {
                Privileges::Enable_Debug_Privilege();
            }

            Injector_Core(const Injector_Core&) = delete;
            Injector_Core& operator=(const Injector_Core&) = delete;
            Injector_Core(Injector_Core&&) = default;
            Injector_Core& operator=(Injector_Core&&) = default;
            ~Injector_Core() = default;

#if defined(SAMP_INJECTOR_CXX_MODERN)
            bool Initialize_Game(Types::Inject_Type inject_type, std::wstring_view folder, std::wstring_view nickname, std::wstring_view ip, std::wstring_view port, std::wstring_view password) {
#elif defined(SAMP_INJECTOR_CXX_14)
            bool Initialize_Game(Types::Inject_Type inject_type, const std::wstring& folder, const std::wstring& nickname, const std::wstring& ip, const std::wstring& port, const std::wstring& password) {
#endif
                std::wstring error_message;

                if (!Validation::Validate_Port(port, error_message))
                    return (Error_Utils::Show_Error(error_message, inject_type), false);
                
                if (!Validation::Validate_Nickname(nickname, error_message))
                    return (Error_Utils::Show_Error(error_message, inject_type), false);
                
#if defined(SAMP_INJECTOR_CXX_MODERN)
                namespace fs = std::filesystem;

                const fs::path game_folder(folder);
                const fs::path game_path = game_folder / Constants::GAME_EXE_NAME;
                const fs::path samp_DLL_path = game_folder / Constants::SAMP_DLL_NAME;
                const fs::path omp_DLL_path = game_folder / Constants::OMP_DLL_NAME;

                if (!Validation::Validate_Files(game_path, samp_DLL_path, omp_DLL_path, inject_type))
                    return false;
#elif defined(SAMP_INJECTOR_CXX_14)
                const std::wstring separator = L"\\";
                const std::wstring game_folder(folder);
                const std::wstring game_path = game_folder + separator + Constants::GAME_EXE_NAME;
                const std::wstring samp_DLL_path = game_folder + separator + Constants::SAMP_DLL_NAME;
                const std::wstring omp_DLL_path = folder + separator + Constants::OMP_DLL_NAME;

                if (!Validation::Validate_Files(game_path, samp_DLL_path, omp_DLL_path, inject_type))
                    return false;
#endif

                std::wstring args = Build_Command_Args({
                    Command_Arg{Constants::CMD_ARG_NICKNAME, std::wstring(nickname)},
                    Command_Arg{Constants::CMD_ARG_HOST, std::wstring(ip)},
                    Command_Arg{Constants::CMD_ARG_PORT, std::wstring(port)},
                    Command_Arg{Constants::CMD_ARG_PASSWORD, std::wstring(password)}
                });

                Process process_core;
                auto process_info_opt = process_core.Create_Game_Process(game_path, args, std::wstring(folder));

                if (!process_info_opt)
                    return false;

                auto& process_info = *process_info_opt;

#if defined(SAMP_INJECTOR_CXX_MODERN)
                if (!Inject_DLL_With_Status_Check(process_core, process_info.process_handle.get(), Constants::SAMP_DLL_NAME, samp_DLL_path.wstring(), inject_type))
                    return false;
                
                if (inject_type == Types::Inject_Type::OMP) {
                    if (!Inject_DLL_With_Status_Check(process_core, process_info.process_handle.get(), Constants::OMP_DLL_NAME, omp_DLL_path.wstring(), inject_type))
                        return false;
                }
#elif defined(SAMP_INJECTOR_CXX_14)
                if (!Inject_DLL_With_Status_Check(process_core, process_info.process_handle.get(), Constants::SAMP_DLL_NAME, samp_DLL_path, inject_type))
                    return false;
                
                if (inject_type == Types::Inject_Type::OMP) {
                    if (!Inject_DLL_With_Status_Check(process_core, process_info.process_handle.get(), Constants::OMP_DLL_NAME, omp_DLL_path, inject_type))
                        return false;
                }
#endif
                
                if (!process_info.Resume())
                    return (Error_Utils::Show_Error(L"Failed to resume the game process thread: " + Error_Utils::Get_System_Error_Message(GetLastError()), inject_type), false);

                return true;
            }
        private:
            struct Command_Arg {
                const wchar_t* key;
                std::wstring value;
            };
            
            std::wstring Build_Command_Args(const std::vector<Command_Arg>& args) {
                std::wstring command_line = Constants::CMD_ARG_CONFIG;
                
                for (const auto& arg : args) {
                    if (!arg.value.empty()) {
                        command_line += L' ';
                        command_line += arg.key;
                        command_line += L' ';

                        if (arg.value.find(L' ') != std::wstring::npos) {
                            command_line += L'"';
                            command_line += arg.value;
                            command_line += L'"';
                        }
                        else
                            command_line += arg.value;
                    }
                }

                return command_line;
            }
            
            bool Inject_DLL_With_Status_Check(Process& pc, HANDLE ph, const wchar_t* dll_name, const std::wstring& dll_path, Types::Inject_Type it) {
                const auto status = pc.Inject_DLL(ph, dll_path);

                if (status == Process::Injection_Status::SUCCESS)
                    return true;
                
                std::wstring error_details;
                DWORD last_error = GetLastError();

                switch (status) {
                    case Process::Injection_Status::ALLOCATION_FAILED:
                        error_details = L"Failed to allocate memory in the target process (VirtualAllocEx). System Error: " + Error_Utils::Get_System_Error_Message(last_error);
                        break;
                    case Process::Injection_Status::WRITE_FAILED:
                        error_details = L"Failed to write DLL path to process memory (WriteProcessMemory). System Error: " + Error_Utils::Get_System_Error_Message(last_error);
                        break;
                    case Process::Injection_Status::KERNEL32_HANDLE_FAILED:
                        error_details = L"Failed to get a handle to kernel32.dll, a critical system library.";
                        break;
                    case Process::Injection_Status::LOADLIBRARY_ADDRESS_FAILED:
                        error_details = L"Failed to find the address of LoadLibraryW in kernel32.dll.";
                        break;
                    case Process::Injection_Status::THREAD_CREATION_FAILED:
                        error_details = L"Failed to create remote thread (CreateRemoteThread). System Error: " + Error_Utils::Get_System_Error_Message(last_error);
                        break;
                    case Process::Injection_Status::THREAD_WAIT_FAILED:
                        error_details = L"Timeout or error waiting for remote thread (WaitForSingleObject). System Error: " + Error_Utils::Get_System_Error_Message(last_error);
                        break;
                    case Process::Injection_Status::GET_EXIT_CODE_FAILED:
                    case Process::Injection_Status::INJECTION_RETURNED_ERROR:
                        error_details = L"LoadLibraryW call failed in the target process. The DLL might be corrupt, missing dependencies, or blocked by security software.";
                        break;
                }

                Error_Utils::Show_Error(L"Failed to inject " + std::wstring(dll_name) + L":\n" + error_details, it);
                
                return false;
            }
        };
}