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
 
using Microsoft.Win32.SafeHandles;
using System;

namespace Samp_Injector_CSharp;

internal sealed class SafeProcessHandle : SafeHandleZeroOrMinusOneIsInvalid {
    public SafeProcessHandle() : base(true) {}
    public SafeProcessHandle(IntPtr handle) : base(true) => SetHandle(handle);

    public bool Kill() {
        if (IsInvalid || IsClosed)
            return false;

        return Native_Imports.TerminateProcess(this, 1);
    }

    protected override bool ReleaseHandle() {
        return Native_Imports.CloseHandle(handle);
    }
}

internal sealed class SafeThreadHandle : SafeHandleZeroOrMinusOneIsInvalid {
    public SafeThreadHandle() : base(true) {}
    public SafeThreadHandle(IntPtr handle) : base(true) => SetHandle(handle);

    protected override bool ReleaseHandle() {
        return Native_Imports.CloseHandle(handle);
    }
}