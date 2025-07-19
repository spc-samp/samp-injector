<# ============================================================================= *
 * SA-MP Injector - PowerShell injection ↓                                       *
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
 * ============================================================================= #>

function Validate_Port {
    param([Parameter(Mandatory = $true)][string]$port_string, [Parameter(Mandatory = $true)][ref]$error_message)
    
    try {
        $port_number = [int]$port_string
        
        if ($port_number -lt $global:CONSTANTS.MIN_PORT -or $port_number -gt $global:CONSTANTS.MAX_PORT) {
            $error_message.Value = "The specified port number ($port_string) is outside the valid range of $($global:CONSTANTS.MIN_PORT) to $($global:CONSTANTS.MAX_PORT). Please provide a valid port."

            return $false
        }
        
        return $true
    }
    catch {
        $error_message.Value = "Invalid port format. The port must be a numeric value. Please provide a valid integer for the port."

        return $false
    }
}

function Validate_Nickname {
    param([Parameter(Mandatory = $true)][AllowEmptyString()][string]$nickname_string, [Parameter(Mandatory = $true)][ref]$error_message)
    
    if ([string]::IsNullOrEmpty($nickname_string)) {
        $error_message.Value = "Nickname cannot be empty. Please provide a valid nickname."

        return $false
    }
    
    if ($nickname_string.Length -gt $global:CONSTANTS.MAX_NICKNAME_LENGTH) {
        $error_message.Value = "Nickname length exceeds the maximum allowed of $($global:CONSTANTS.MAX_NICKNAME_LENGTH) characters. Please use a shorter nickname."

        return $false
    }
    
    return $true
}

function Validate_Files {
    param([Parameter(Mandatory = $true)][string]$game_path, [Parameter(Mandatory = $true)][string]$samp_dll_path, [Parameter(Mandatory = $true)][string]$omp_dll_path, 
    [Parameter(Mandatory = $true)][Inject_Type]$inject_type)
    
    if (-not (Test-Path -Path $game_path -PathType Leaf)) {
        Show_Error "Game executable not found. Please ensure 'gta_sa.exe' exists at the specified path: $game_path" $inject_type

        return $false
    }
    
    if (-not (Test-Path -Path $samp_dll_path -PathType Leaf)) {
        Show_Error "SA-MP library not found. Please ensure 'samp.dll' exists at the specified path: $samp_dll_path" $inject_type

        return $false
    }
    
    if ($inject_type -eq [Inject_Type]::OMP -and -not (Test-Path -Path $omp_dll_path -PathType Leaf)) {
        Show_Error "OMP library not found. Please ensure 'omp-client.dll' exists at the specified path for OMP injection: $omp_dll_path" $inject_type
        
        return $false
    }
    
    return $true
}