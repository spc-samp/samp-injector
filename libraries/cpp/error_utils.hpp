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
#include <windows.h>
//
#include "types.hpp"
#include "constants.hpp"

namespace Utils {
    inline std::wstring Get_System_Error_Message(DWORD error_code) {
        wchar_t buffer[512] = {0};
        DWORD result = FormatMessageW(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, nullptr, error_code, 0, buffer, 512, nullptr);
        
        return result ? std::wstring(buffer) : L"Unknown error (Code: " + std::to_wstring(error_code) + L")";
    }

    inline void Show_Error(std::wstring_view message, Types::Inject_Type injectType) {
        std::wstring title = (injectType == Types::Inject_Type::SAMP) ? Constants::ERROR_TITLE_SAMP : Constants::ERROR_TITLE_OMP;
        MessageBoxW(nullptr, message.data(), title.c_str(), MB_OK | MB_ICONERROR);
    }
}