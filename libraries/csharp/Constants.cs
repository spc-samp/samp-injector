/* ============================================================================= *
 * SA-MP Injector - C# injection ↓                                               *
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

namespace Samp_Injector_CSharp;

internal static class Constants {
    // Game related constants
    public const int MIN_PORT = 1;
    public const int MAX_PORT = 65535;
    public const int MAX_NICKNAME_LENGTH = 23;

    // File names
    public const string SAMP_DLL_NAME = "samp.dll";
    public const string OMP_DLL_NAME = "omp-client.dll";
    public const string GAME_EXE_NAME = "gta_sa.exe";

    // System libraries and functions
    public const string KERNEL32_DLL = "kernel32.dll";
    public const string LOAD_LIBRARY_FUNC = "LoadLibraryA";

    // Command line arguments
    public const string CMD_ARGS_PART1 = "-c -n ";
    public const string CMD_ARGS_PART2 = " -h ";
    public const string CMD_ARGS_PART3 = " -p ";
    public const string CMD_ARGS_PART4_PASSWORD = " -z ";

    // Pre-calculated lengths of the constant parts of the command line.
    public const int CMD_ARGS_BASE_LENGTH = 14;
    public const int CMD_ARG_PASSWORD_LENGTH = 4;

    // Error message titles
    public const string ERROR_TITLE_SAMP = "SA-MP Injector Error - SPC";
    public const string ERROR_TITLE_OMP = "OMP Injector Error - SPC";

    // Process creation flags
    public const uint CREATE_SUSPENDED = 0x00000004;
    public const uint PROCESS_CREATION_FLAGS = CREATE_SUSPENDED;

    // Timeouts
    public const uint DLL_INJECTION_TIMEOUT_MS = 10000;

    // Memory allocation
    public const uint MEM_COMMIT = 0x1000;
    public const uint MEM_RESERVE = 0x2000;
    public const uint MEM_RELEASE = 0x8000;
    public const uint MEMORY_ALLOCATION_TYPE = MEM_COMMIT | MEM_RESERVE;
    public const uint MEMORY_PROTECTION = 0x04;
}