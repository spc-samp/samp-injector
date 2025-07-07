/* ============================================================================= *
 * SA-MP Injector - Injection ↓                                                  *
 * DLL for SA-MP (San Andreas Multiplayer) and OMP (Open Multiplayer)            *
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
#include <thread>
#include <exception>
//
#include "libraries/samp-injector/cpp/injector.hpp" 

#define SAMP_INJECTOR_DLL_API extern "C" __declspec(dllexport)

namespace {
    void Show_Usage() {
        MessageBoxW(nullptr, L"Invalid arguments for 'Launch_Game' function.\n\n" L"Expected format:\n" L"Launch_Game(<mode>, <folder>, <nickname>, <IP>, <port>, <password (optional)>)\n\n"
            L"Valid modes are 'samp' or 'omp'.", L"SA-MP Injector Error - SPC", MB_OK | MB_ICONERROR);
    }

    bool Parse_Inject_Type(const std::wstring& type) {
        if (type == L"samp" || type == L"omp")
            return true;

        MessageBoxW(nullptr, L"Invalid injection mode specified. Please use 'samp' or 'omp'.", L"SA-MP Injector Error - SPC", MB_OK | MB_ICONERROR);

        return false;
    }

    void Game_Thread_Worker(const std::wstring& mode, const std::wstring& folder, const std::wstring& nickname, const std::wstring& ip, const std::wstring& port, const std::wstring& password) {
        Initialize_Game(mode, folder, nickname, ip, port, password);
    }
}

SAMP_INJECTOR_DLL_API int __stdcall Launch_Game(const wchar_t* mode, const wchar_t* folder, const wchar_t* nickname, const wchar_t* ip, const wchar_t* port, const wchar_t* password) {
    if (!mode || !folder || !nickname || !ip || !port)
        return (Show_Usage(), 1);

    std::wstring mode_str = mode;

    if (!Parse_Inject_Type(mode_str))
        return 1;

    std::wstring folder_str = folder;
    std::wstring nickname_str = nickname;
    std::wstring ip_str = ip;
    std::wstring port_str = port;
    std::wstring password_str = (password) ? password : L"";

    try {
        std::thread(Game_Thread_Worker, mode_str, folder_str, nickname_str, ip_str, port_str, password_str).detach();
    }
    catch (const std::exception& e) {
        const char* what_ansi = e.what();
        int size_needed = MultiByteToWideChar(CP_UTF8, 0, what_ansi, -1, NULL, 0);
        std::wstring what_wide(size_needed, 0);
        MultiByteToWideChar(CP_UTF8, 0, what_ansi, -1, &what_wide[0], size_needed);

        std::wstring error_msg = L"Failed to create the game launch thread: ";
        error_msg += what_wide;

        MessageBoxW(nullptr, error_msg.c_str(), L"SA-MP Injector Critical Error - SPC", MB_OK | MB_ICONERROR);

        return 2;
    }

    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    switch (ul_reason_for_call) {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }

    return TRUE;
}