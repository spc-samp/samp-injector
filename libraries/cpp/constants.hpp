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

namespace Constants {
    // Game related constants
    inline constexpr int MIN_PORT = 1;
    inline constexpr int MAX_PORT = 65535;
    inline constexpr int MAX_NICKNAME_LENGTH = 20;
    
    // File names
    inline constexpr const wchar_t* SAMP_DLL_NAME = L"samp.dll";
    inline constexpr const wchar_t* OMP_DLL_NAME = L"omp-client.dll";
    inline constexpr const wchar_t* GAME_EXE_NAME = L"gta_sa.exe";
    
    // System libraries and functions
    inline constexpr const char* KERNEL32_DLL = "kernel32.dll";
    inline constexpr const char* LOAD_LIBRARY_FUNC = "LoadLibraryA";
    
    // Command line arguments
    inline constexpr const char* CMD_ARG_CONFIG = "-c";
    inline constexpr const char* CMD_ARG_NICKNAME = "-n";
    inline constexpr const char* CMD_ARG_HOST = "-h";
    inline constexpr const char* CMD_ARG_PORT = "-p";
    inline constexpr const char* CMD_ARG_PASSWORD = "-z";
    
    // Injection types as strings
    inline constexpr const wchar_t* INJECT_TYPE_SAMP = L"samp";
    inline constexpr const wchar_t* INJECT_TYPE_OMP = L"omp";
    
    // Error message titles
    inline constexpr const wchar_t* ERROR_TITLE_SAMP = L"SA-MP Injector Error - SPC";
    inline constexpr const wchar_t* ERROR_TITLE_OMP = L"OMP Injector Error - SPC";
    
    // Process creation
    inline constexpr DWORD PROCESS_CREATION_FLAGS = CREATE_SUSPENDED | DETACHED_PROCESS;
    
    // Timeouts
    inline constexpr DWORD DLL_INJECTION_TIMEOUT_MS = 10000;
    
    // Memory allocation
    inline constexpr DWORD MEMORY_ALLOCATION_TYPE = MEM_COMMIT | MEM_RESERVE;
    inline constexpr DWORD MEMORY_PROTECTION = PAGE_READWRITE;
}