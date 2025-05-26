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

namespace Utils {
    inline std::string Wide_To_Local_8Bit(std::wstring_view wstr) {
        if (wstr.empty())
            return "";
        
        int size = WideCharToMultiByte(CP_ACP, 0, wstr.data(), static_cast<int>(wstr.size()), nullptr, 0, nullptr, nullptr);

        if (size <= 0)
            return "";

        std::string result(size, 0);
        WideCharToMultiByte(CP_ACP, 0, wstr.data(), static_cast<int>(wstr.size()), result.data(), size, nullptr, nullptr);

        return result;
    }
}