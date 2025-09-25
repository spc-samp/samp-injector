/* ============================================================================= *
 * SA-MP Injector - Injection ↓                                                  *
 * executable for SA-MP (San Andreas Multiplayer) and OMP (Open Multiplayer)     *
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

#include <windows.h>
#include <string>
#include <memory>
//
#include "libraries/samp-injector/cpp/injector.hpp"

namespace {
    void Show_Usage() {
        MessageBoxW(nullptr, L"Invalid command line arguments. Please use the following format:\n\n" L"samp-injector.exe <mode> <directory> <nickname> <IP> <port> <password (optional)>\n\n"
            L"Valid modes are 'samp' or 'omp'.", L"SA-MP Injector Error - SPC", MB_OK | MB_ICONERROR);
    }

    bool Parse_Inject_Type(const std::wstring& type) {
        if (type == L"samp" || type == L"omp")
            return true;

        MessageBoxW(nullptr, L"Invalid injection mode specified. Please use 'samp' or 'omp'.", L"SA-MP Injector Error - SPC", MB_OK | MB_ICONERROR);

        return false;
    }
}

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow) {
    int argc;
    std::unique_ptr<LPWSTR[], decltype(&LocalFree)> argv(CommandLineToArgvW(GetCommandLineW(), &argc), &LocalFree);

    if (!argv)
        return (MessageBoxW(nullptr, L"Failed to parse command line arguments. Unable to retrieve necessary information.", L"SA-MP Injector Error - SPC", MB_OK | MB_ICONERROR), 1);

    if (argc < 6 || argc > 7)
        return (Show_Usage(), 1);

    std::wstring inject_type = argv[1];

    if (!Parse_Inject_Type(inject_type))
        return 1;

    std::wstring folder = argv[2];
    std::wstring nickname = argv[3];
    std::wstring ip = argv[4];
    std::wstring port = argv[5];
    std::wstring password = (argc == 7) ? argv[6] : L"";

    if (!Initialize_Game(inject_type, folder, nickname, ip, port, password))
        return 1;

    return 0;
}