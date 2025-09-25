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

internal static class Input_Validator {
    public static bool Try_Validate(string folder_path, string nickname, string port_str, Injection_Type inject_type, out string error_message) {
        if (string.IsNullOrWhiteSpace(nickname))
            return (error_message = "Nickname cannot be empty. Please provide a valid nickname.") != null && false;

        if (nickname.Length > Constants.MAX_NICKNAME_LENGTH)
            return (error_message = $"Nickname length exceeds the maximum allowed of {Constants.MAX_NICKNAME_LENGTH} characters. Please use a shorter nickname.") != null && false;

        if (!int.TryParse(port_str, out int port_num))
            return (error_message = "Invalid port format. The port must be a numeric value. Please provide a valid integer for the port.") != null && false;

        if (port_num < Constants.MIN_PORT || port_num > Constants.MAX_PORT)
            return (error_message = $"The specified port number ({port_str}) is outside the valid range of {Constants.MIN_PORT} to {Constants.MAX_PORT}. Please provide a valid port.") != null && false;

        string game_exe_path = Path.Combine(folder_path, Constants.GAME_EXE_NAME);

        if (!File.Exists(game_exe_path))
            return (error_message = $"Game executable not found. Please ensure 'gta_sa.exe' exists at the specified path: {game_exe_path}") != null && false;

        string samp_dll_path = Path.Combine(folder_path, Constants.SAMP_DLL_NAME);

        if (!File.Exists(samp_dll_path))
            return (error_message = $"SA-MP library not found. Please ensure 'samp.dll' exists at the specified path: {samp_dll_path}") != null && false;

        if (inject_type == Injection_Type.OMP) {
            string omp_dll_path = Path.Combine(folder_path, Constants.OMP_DLL_NAME);
            
            if (!File.Exists(omp_dll_path))
                return (error_message = $"OMP library not found. Please ensure 'omp-client.dll' exists at the specified path for OMP injection: {omp_dll_path}") != null && false;
        }

        error_message = string.Empty;
        
        return true;
    }
}