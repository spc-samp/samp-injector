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
#include <sstream>
#include <filesystem>
//
#include "process.hpp"
#include "validation.hpp"
#include "string_utils.hpp"
#include "error_utils.hpp"
#include "constants.hpp"
#include "types.hpp"

namespace Injector {
    class Injector_Core {
        public:
            Injector_Core() = default;
            Injector_Core(const Injector_Core&) = delete;
            Injector_Core& operator=(const Injector_Core&) = delete;
            Injector_Core(Injector_Core&&) = default;
            Injector_Core& operator=(Injector_Core&&) = default;
            ~Injector_Core() = default;

            bool Initialize_Game(Types::Inject_Type inject_type, std::wstring_view folder, std::wstring_view nickname, std::wstring_view ip, std::wstring_view port, std::wstring_view password) {
                namespace fs = std::filesystem;

                fs::path game_path = fs::path(folder) / Constants::GAME_EXE_NAME;
                fs::path samp_DLL_path = fs::path(folder) / Constants::SAMP_DLL_NAME;
                fs::path omp_DLL_path = fs::path(folder) / Constants::OMP_DLL_NAME;

                if (!Validation::Validate_Files(game_path, samp_DLL_path, omp_DLL_path, inject_type))
                    return false;
                
                std::wstring error_message;

                if (!Validation::Validate_Port(port, error_message))
                    return (Error_Utils::Show_Error(error_message, inject_type), false);

                if (!Validation::Validate_Nickname(nickname, error_message))
                    return (Error_Utils::Show_Error(error_message, inject_type), false);

                std::string nickname_str = String_Utils::Wide_To_Local_8Bit(nickname);
                std::string ip_str = String_Utils::Wide_To_Local_8Bit(ip);
                std::string port_str = String_Utils::Wide_To_Local_8Bit(port);
                std::string password_str = String_Utils::Wide_To_Local_8Bit(password);
                std::string game_path_str = String_Utils::Wide_To_Local_8Bit(game_path.wstring());
                std::string folder_str = String_Utils::Wide_To_Local_8Bit(folder);
                std::string samp_DLL_path_str = String_Utils::Wide_To_Local_8Bit(samp_DLL_path.wstring());
                std::string omp_DLL_path_str = String_Utils::Wide_To_Local_8Bit(omp_DLL_path.wstring());

                std::string args = Build_Command_Args(nickname_str, ip_str, port_str, password_str);

                Process process_core;
                auto process_info_opt = process_core.Create_Game_Process(game_path_str, args, folder_str);

                if (!process_info_opt)
                    return false;

                auto& process_info = *process_info_opt;

                std::wstring inject_error;

                if (!process_core.Inject_DLL(process_info.process_handle.get(), samp_DLL_path_str, inject_error))
                    return (Error_Utils::Show_Error(L"Failed to inject samp.dll: " + inject_error, inject_type), false);

                if (inject_type == Types::Inject_Type::OMP) {
                    if (!process_core.Inject_DLL(process_info.process_handle.get(), omp_DLL_path_str, inject_error))
                        return (Error_Utils::Show_Error(L"Failed to inject omp-client.dll: " + inject_error, inject_type), false);
                }

                if (ResumeThread(process_info.thread_handle.get()) == static_cast<DWORD>(-1))
                    return (Error_Utils::Show_Error(L"Failed to resume the game process thread: " + Error_Utils::Get_System_Error_Message(GetLastError()), inject_type), false);

                return true;
            }
        private:
            std::string Build_Command_Args(const std::string& nickname, const std::string& ip, const std::string& port, const std::string& password) {
                std::stringstream command_args;

                command_args << Constants::CMD_ARG_CONFIG << " " << Constants::CMD_ARG_NICKNAME << " " << nickname << " " << Constants::CMD_ARG_HOST << " " << ip << " " 
                    << Constants::CMD_ARG_PORT << " " << port;

                if (!password.empty())
                    command_args << " " << Constants::CMD_ARG_PASSWORD << " " << password;

                return command_args.str();
            }
    };
}