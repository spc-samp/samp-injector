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
 * - This file is part of the SA-MP Injector project.                            *
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
#include <string_view>
#include <filesystem>
//
#include "constants.hpp"
#include "types.hpp"
#include "string_utils.hpp"
#include "error_utils.hpp"

namespace Utils {
    inline bool Validate_Port(std::wstring_view port_str, std::wstring& error_message) {
        try {
            int port_num = std::stoi(Wide_To_Local_8Bit(port_str));

            if (port_num < Constants::MIN_PORT || port_num > Constants::MAX_PORT)
                return (error_message = L"The specified port number (" + std::wstring(port_str) + L") is outside the valid range of " +  std::to_wstring(Constants::MIN_PORT) + L" to " + 
                    std::to_wstring(Constants::MAX_PORT) + L". Please provide a valid port.", false);

            return true;
        }
        catch (...) {
            return (error_message = L"Invalid port format. The port must be a numeric value. Please provide a valid integer for the port.", false);
        }
    }

    inline bool Validate_Nickname(std::wstring_view nickname_str, std::wstring& error_message) {
        if (nickname_str.empty())
            return (error_message = L"Nickname cannot be empty. Please provide a valid nickname.", false);
        
        if (nickname_str.size() > Constants::MAX_NICKNAME_LENGTH)
            return (error_message = L"Nickname length exceeds the maximum allowed of " + std::to_wstring(Constants::MAX_NICKNAME_LENGTH) + L" characters. Please use a shorter nickname.", false);
        
        return true;
    }

    inline bool Validate_Files(const std::filesystem::path& game_path, const std::filesystem::path& samp_DLL_path, const std::filesystem::path& omp_DLL_path, Types::Inject_Type inject_type) {
        std::wstring error_message;
        
        if (!std::filesystem::exists(game_path)) {
            error_message = L"Game executable not found. Please ensure 'gta_sa.exe' exists at the specified path: " + game_path.wstring();
            Show_Error(error_message, inject_type);

            return false;
        }

        if (!std::filesystem::exists(samp_DLL_path)) {
            error_message = L"SA-MP library not found. Please ensure 'samp.dll' exists at the specified path: " + samp_DLL_path.wstring();
            Show_Error(error_message, inject_type);

            return false;
        }

        if (inject_type == Types::Inject_Type::OMP && !std::filesystem::exists(omp_DLL_path)) {
            error_message = L"OMP library not found. Please ensure 'omp-client.dll' exists at the specified path for OMP injection: " + omp_DLL_path.wstring();
            Show_Error(error_message, inject_type);
            
            return false;
        }

        return true;
    }
}