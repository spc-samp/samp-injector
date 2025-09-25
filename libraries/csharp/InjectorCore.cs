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

using System.IO;

namespace Samp_Injector_CSharp;

internal sealed class Injector_Core {
    public bool Try_Initialize_Game(Injection_Type inject_type, string folder, string nickname, string ip, string port, string password, out string error_message) {
        if (!Input_Validator.Try_Validate(folder, nickname, port, inject_type, out error_message))
            return false;

        string game_exe_path = Path.Combine(folder, Constants.GAME_EXE_NAME);
        using Process_Handler.Process_Info process_info = Process_Handler.Create_Game_Process(game_exe_path, folder, nickname, ip, port, password, out error_message);
        
        if (process_info.IsInvalid)
            return false;

        bool success = false;

        try {
            string samp_DLL_path = Path.Combine(folder, Constants.SAMP_DLL_NAME);

            if (!Process_Handler.Inject_DLL(process_info.ProcessHandle, samp_DLL_path, out error_message))
                return false;

            if (inject_type == Injection_Type.OMP) {
                string omp_DLL_path = Path.Combine(folder, Constants.OMP_DLL_NAME);

                if (!Process_Handler.Inject_DLL(process_info.ProcessHandle, omp_DLL_path, out error_message))
                    return false;
            }

            if (!Process_Handler.Resume_Game_Thread(process_info.ThreadHandle, out error_message))
                return false;

            success = true;
            error_message = string.Empty;

            return true;
        }
        finally {
            if (!success && !process_info.ProcessHandle.IsInvalid && !process_info.ProcessHandle.IsClosed) 
                process_info.ProcessHandle.Kill();
        }
    }
}