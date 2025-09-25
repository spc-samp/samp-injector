# SA-MP Injector C#

<div align="center">

![C#](https://img.shields.io/badge/C%23-11.0%2B-512BD4?style=for-the-badge&logo=csharp&logoColor=white)
![.NET](https://img.shields.io/badge/.NET-7.0%2B-512BD4?style=for-the-badge&logo=dotnet&logoColor=white)
![Platform](https://img.shields.io/badge/Platform-Windows-blue?style=for-the-badge&logo=windows&logoColor=white)
![Architecture](https://img.shields.io/badge/Architecture-x86%20(32--bit)-lightgrey?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)

**A C# library for programmatic injection of DLLs into SA-MP and OMP processes, allowing automated connection to servers.**

</div>

## Languages

- Português: [README](../../)
- Deutsch: [README](../Deutsch/README.md)
- Español: [README](../Espanol/README.md)
- Français: [README](../Francais/README.md)
- Italiano: [README](../Italiano/README.md)
- Polski: [README](../Polski/README.md)
- Русский: [README](../Русский/README.md)
- Svenska: [README](../Svenska/README.md)
- Türkçe: [README](../Turkce/README.md)

## Table of Contents

- [SA-MP Injector C#](#sa-mp-injector-c)
  - [Languages](#languages)
  - [Table of Contents](#table-of-contents)
  - [Introduction and Purpose](#introduction-and-purpose)
  - [Design Philosophy](#design-philosophy)
    - [Interoperability (P/Invoke)](#interoperability-pinvoke)
    - [Resource Management (`SafeHandle`)](#resource-management-safehandle)
    - [Security and Robustness](#security-and-robustness)
  - [System Requirements](#system-requirements)
    - [Development Environment](#development-environment)
    - [Execution Environment](#execution-environment)
  - [Installation and Basic Usage](#installation-and-basic-usage)
    - [Adding to Your Project](#adding-to-your-project)
    - [Usage Example](#usage-example)
  - [Library Components](#library-components)
    - [1. `Constants.cs`](#1-constantscs)
    - [2. `InjectionType.cs`](#2-injectiontypecs)
    - [3. `Injector.cs`](#3-injectorcs)
    - [4. `InjectorCore.cs`](#4-injectorcorecs)
    - [5. `InputValidator.cs`](#5-inputvalidatorcs)
    - [6. `NativeImports.cs`](#6-nativeimportscs)
    - [7. `ProcessHandler.cs`](#7-processhandlercs)
    - [8. `SafeHandles.cs`](#8-safehandlescs)
  - [Detailed DLL Injection Cycle](#detailed-dll-injection-cycle)
    - [1. Input Validation](#1-input-validation)
    - [2. Game Process Creation (Suspended)](#2-game-process-creation-suspended)
    - [3. `samp.dll` Injection](#3-sampdll-injection)
    - [4. `omp-client.dll` Injection (Optional, SA-MP Dependent)](#4-omp-clientdll-injection-optional-sa-mp-dependent)
    - [Resume the Main Game Thread](#resume-the-main-game-thread)
  - [Error Handling and Failure Cases](#error-handling-and-failure-cases)
    - [Input Validation Errors](#input-validation-errors)
      - [Invalid Nickname](#invalid-nickname)
      - [Invalid Port](#invalid-port)
      - [Missing Game/DLL Files](#missing-gamedll-files)
    - [Process Creation Errors](#process-creation-errors)
      - [Failed to Create Process](#failed-to-create-process)
    - [DLL Injection Errors](#dll-injection-errors)
      - [`kernel32.dll` Handle Unavailable](#kernel32dll-handle-unavailable)
      - [`LoadLibraryA` Function Unavailable](#loadlibrarya-function-unavailable)
      - [Remote Memory Allocation Failure](#remote-memory-allocation-failure)
      - [Failure to Write to Process Memory](#failure-to-write-to-process-memory)
      - [Remote Thread Creation Failure](#remote-thread-creation-failure)
      - [Timeout or Error While Waiting for Injection](#timeout-or-error-while-waiting-for-injection)
      - [DLL Injection Failed or Returned an Error](#dll-injection-failed-or-returned-an-error)
    - [Error Resuming the Game Thread](#error-resuming-the-game-thread)
  - [License](#license)
    - [Terms and Conditions of Use](#terms-and-conditions-of-use)
      - [1. Granted Permissions](#1-granted-permissions)
      - [2. Mandatory Conditions](#2-mandatory-conditions)
      - [3. Copyright](#3-copyright)
      - [4. Disclaimer of Warranty and Limitation of Liability](#4-disclaimer-of-warranty-and-limitation-of-liability)

## Introduction and Purpose

The **SA-MP Injector C#** library is a C# solution designed to simplify the automated startup and connection of San Andreas Multiplayer (SA-MP) and Open Multiplayer (OMP) clients to servers. It acts as a DLL (Dynamic Link Library) injection tool, programmatically loading the `samp.dll` or `omp-client.dll` libraries into the Grand Theft Auto: San Andreas game process (`gta_sa.exe`).

The main purpose of this library is to allow other C# applications (such as custom launchers, server management tools, or utilities) to start the game with specific parameters (nickname, IP, port, and password) transparently to the user, automating the process of connecting to a SA-MP/OMP server.

## Design Philosophy

The design of **SA-MP Injector C#** focuses on robustness, security, and a simplified user interface, encapsulating the complexities of low-level system operations.

### Interoperability (P/Invoke)

The core functionality of DLL injection and creating suspended processes is intrinsically a low-level operating system operation. For this, the library makes extensive use of the **P/Invoke (Platform Invoke)** feature of .NET, allowing native Windows API functions (mainly from `kernel32.dll`) to be called directly from C# code. This is evident in the declaration of `partial` methods and the use of the `[LibraryImport(KERNEL32, SetLastError = true)]` attribute.

### Resource Management (`SafeHandle`)

Operations with operating system resources, such as process and thread handles, require careful management to avoid memory or resource leaks. The library employs classes derived from `SafeHandle` (`SafeProcessHandle` and `SafeThreadHandle`) to ensure that these resources are always released correctly, even in the event of exceptions. This adheres to the **RAII (Resource Acquisition Is Initialization)** principle of C++ and extends it to the .NET environment.

### Security and Robustness

The library incorporates several layers of security:
- **Input Validation:** All user-provided inputs are rigorously validated before any critical operations are initiated, minimizing the risk of runtime errors or unexpected behavior.
- **Error Handling:** Native API calls are accompanied by error checks (`SetLastError = true` and `Marshal.GetLastWin32Error()`) to provide detailed and understandable error messages.
- **Process Termination:** In case of failure during the injection process, the newly created game process is automatically terminated to prevent "zombie" processes from running.

## System Requirements

### Development Environment

- **.NET SDK 7.0 or higher:** The library is built for `net7.0-windows`.
- **C# 11.0 or higher:** Required for features like `ImplicitUsings`, `Nullable`, `AllowUnsafeBlocks`, and `LibraryImport`.
- **Visual Studio 2022 or a compatible development environment:** To build and integrate the library.
- **Compilation Platform:** `x86 (32-bit)` is the mandatory target due to the architecture of `gta_sa.exe` and the SA-MP/OMP DLLs.

```xml
<!-- samp-injector-csharp.csproj -->
<Project Sdk="Microsoft.NET.Sdk">
    <PropertyGroup>
        <TargetFrameworks>net7.0-windows</TargetFrameworks>
        <PlatformTarget>x86</PlatformTarget> <!-- CRITICAL: Must be x86 -->
        <ImplicitUsings>enable</ImplicitUsings>
        <Nullable>enable</Nullable>
        <UseWindowsForms>true</UseWindowsForms>
        <AllowUnsafeBlocks>true</AllowUnsafeBlocks> <!-- Required for advanced P/Invoke -->
    </PropertyGroup>
</Project>
```

### Execution Environment

- **Operating System:** Windows (any modern version compatible with .NET 7.0+).
- **Grand Theft Auto: San Andreas (GTA: SA):** The game installation is required.
- **SA-MP or OMP Client DLLs:** `samp.dll` or `omp-client.dll` must be present in the game's root directory, depending on the desired injection type.

## Installation and Basic Usage

### Adding to Your Project

The simplest way to use this library is to add the `Samp_Injector_CSharp` project as a reference in your own C# project.

1. Clone or download the library's repository.
2. In Visual Studio, right-click on "Dependencies" (or "References") in your project.
3. Select "Add Project Reference...".
4. Navigate to the library's directory and add the `samp-injector-csharp.csproj` project.

### Usage Example

To start the game and connect to a server, simply call the static `Injector.Initialize_Game` method.

```csharp
using Samp_Injector_CSharp;
using System;
using System.Windows.Forms; // For MessageBox, if it's not a WinForms project

namespace Launcher {
    public partial class Main : Form {
        public Main() {
            InitializeComponent();
        }

        private void Connect(object sender, EventArgs e) {
            string inject_type = "SAMP"; // "SAMP" or "OMP"
            string game_folder = @"C:\Games\GTA San Andreas"; // Path to the GTA: SA folder
            string nickname = "Name";
            string ip = "127.0.0.1";
            string port = "7777";
            string password = ""; // Leave empty if there is no password

            // Example of SA-MP injection
            Injector.Initialize_Game(inject_type, game_folder, nickname, ip, port, password);

            // If it is OMP, change inject_type:
            // inject_type = "OMP";
            // Injector.Initialize_Game(inject_type, game_folder, nickname, ip, port, password);
        }
    }
}
```

## Library Components

The library is structured into several files, each with a clear and well-defined responsibility, which promotes organization, maintainability, and separation of concerns. Below is a detailed description of each component.

### 1. `Constants.cs`

This file is a centralized repository of all constants and immutable values that are used throughout the library. Its existence promotes code maintenance, readability, and consistency by ensuring that critical values are defined in a single location.

The organization of constants by category makes it easier to understand their purpose:

- **Game Related Constants**
   - `MIN_PORT`: Defines the minimum allowed value for a server's connection port (1).
   - `MAX_PORT`: Defines the maximum allowed value for a server's connection port (65535).
   - `MAX_NICKNAME_LENGTH`: Specifies the maximum allowed length for the player's nickname (23 characters), a limit imposed by the SA-MP/OMP client itself.

- **File Names**
   - `SAMP_DLL_NAME`: The name of the main library file for the SA-MP client (`"samp.dll"`).
   - `OMP_DLL_NAME`: The name of the Open Multiplayer client library file (`"omp-client.dll"`), used in OMP type injections.
   - `GAME_EXE_NAME`: The name of the Grand Theft Auto: San Andreas game executable (`"gta_sa.exe"`).

- **System Libraries and Functions**
   - `KERNEL32_DLL`: The name of the Windows system library that contains essential functions for process and memory manipulation (`"kernel32.dll"`).
   - `LOAD_LIBRARY_FUNC`: The name of the function within `kernel32.dll` responsible for dynamically loading a library (`"LoadLibraryA"`).

- **Command Line Arguments**
   - `CMD_ARGS_PART1`: The initial part of the command-line arguments for the game (`"-c -n "`).
   - `CMD_ARGS_PART2`: Separator for the IP address (`" -h "`).
   - `CMD_ARGS_PART3`: Separator for the port (`" -p "`).
   - `CMD_ARGS_PART4_PASSWORD`: Prefix for the password argument (`" -z "`), used only if a password is provided.
   - `CMD_ARGS_BASE_LENGTH`: The predefined length of the constant parts of the command line, excluding the executable and user values (14 characters).
   - `CMD_ARG_PASSWORD_LENGTH`: The length of the password argument prefix (4 characters).

- **Error Message Titles**
   - `ERROR_TITLE_SAMP`: Default title for error dialog boxes related to SA-MP failures (`"SA-MP Injector Error - SPC"`).
   - `ERROR_TITLE_OMP`: Default title for error dialog boxes related to OMP failures (`"OMP Injector Error - SPC"`).

- **Process Creation Flags**
   - `CREATE_SUSPENDED`: Flag that instructs the operating system to create a process and its main thread in a suspended state (`0x00000004`). This is crucial for injecting the DLL before the game starts running.
   - `PROCESS_CREATION_FLAGS`: A combination of process creation flags, currently defined only as `CREATE_SUSPENDED`.

- **Timeouts**
   - `DLL_INJECTION_TIMEOUT_MS`: The maximum time (in milliseconds) the library will wait for the completion of the remote thread responsible for DLL injection (10000ms = 10 seconds).

- **Memory Allocation Flags**
   - `MEM_COMMIT`: Flag that reserves pages in virtual memory and "commits" them (allocates physical memory) (`0x1000`).
   - `MEM_RESERVE`: Flag that only reserves a range of virtual address space for later use (`0x2000`).
   - `MEM_RELEASE`: Flag that decommits and releases a region of pages (`0x8000`).
   - `MEMORY_ALLOCATION_TYPE`: A combination of `MEM_COMMIT` and `MEM_RESERVE`, used to allocate memory for the DLL path in the remote process.
   - `MEMORY_PROTECTION`: Defines the memory protection permissions (currently `0x04`, which corresponds to `PAGE_READWRITE` in the Windows API, allowing reading and writing to the allocated memory).

### 2. `InjectionType.cs`

This file defines a simple enumerator to provide a type-safe and clear way to specify the type of injection to be performed. Using an `enum` instead of strings (`"samp"`, `"omp"`) prevents typos and makes the code more readable and robust.

```csharp
// InjectionType.cs
namespace Samp_Injector_CSharp {
    public enum Injection_Type {
        SAMP,
        OMP
    }
}
```

### 3. `Injector.cs`

This file is the public facade of the library, serving as the single entry point for consuming applications. It abstracts all the internal complexity of the injection process into a single static method.

- **Main Responsibility:** The `Initialize_Game` method receives all necessary parameters as strings, determines the injection type, and delegates the work to `Injector_Core`. It is also responsible for capturing the operation's result and presenting error messages to the end-user via `MessageBox`, making user interaction consistent.

```csharp
// Snippet from Injector.cs
public static class Injector {
    private static readonly Injector_Core s_core = new();

    public static void Initialize_Game(string inject_type_str, string folder, string nickname, string ip, string port, string password) {
        // ... Logic to convert inject_type_str to Injection_Type ...

        if (!s_core.Try_Initialize_Game(type, folder, nickname, ip, port, password, out string error_message)) {
            string error_title = (type == Injection_Type.OMP) ? Constants.ERROR_TITLE_OMP : Constants.ERROR_TITLE_SAMP;
            MessageBox.Show(error_message, error_title, MessageBoxButtons.OK, MessageBoxIcon.Error);
        }
    }
}
```

### 4. `InjectorCore.cs`

This is the "brain" of the library, where the sequence of injection operations is orchestrated. It connects the input validators with the process handlers to execute the complete workflow.

- **Main Responsibility:** The `Try_Initialize_Game` method defines the step-by-step logic: it validates the inputs, creates the game process in a suspended state, injects the necessary DLLs (`samp.dll` and, optionally, `omp-client.dll`), and, if everything is successful, resumes the game's thread. A crucial aspect is the `finally` block, which ensures that the game process is terminated (`Kill()`) in case of any failure during the injection steps, preventing "zombie" processes.

```csharp
// Snippet from InjectorCore.cs
internal sealed class Injector_Core {
    public bool Try_Initialize_Game(...) {
        // ... Input validation ...

        using Process_Handler.Process_Info process_info = Process_Handler.Create_Game_Process(...);
        
        // ...
        bool success = false;
        try {
            // ... samp.dll injection ...
            // ... Optional omp-client.dll injection ...
            // ... Resume game thread ...
            success = true;
            return true;
        }
        finally {
            if (!success && !process_info.ProcessHandle.IsInvalid) 
                process_info.ProcessHandle.Kill();
        }
    }
}
```

### 5. `InputValidator.cs`

Acts as the library's first line of defense, ensuring that only valid and safe data is processed. Pre-validation prevents low-level exceptions and allows the library to provide clear and actionable error messages.

- **Main Responsibility:** The static `Try_Validate` method performs a series of checks, including the nickname format, the numerical range of the port, and, crucially, the existence of essential files (`gta_sa.exe`, `samp.dll`, etc.) in the specified directory. If any check fails, it returns `false` and populates an `out string` with the error description.

```csharp
// Snippet from InputValidator.cs
internal static class Input_Validator {
    public static bool Try_Validate(...) {
        if (nickname.Length > Constants.MAX_NICKNAME_LENGTH)
            return (error_message = $"Nickname length exceeds the maximum...") != null && false;

        string game_exe_path = Path.Combine(folder_path, Constants.GAME_EXE_NAME);
        if (!File.Exists(game_exe_path))
            return (error_message = $"Game executable not found...") != null && false;
        
        // ...
        return true;
    }
}
```

### 6. `NativeImports.cs`

This file is the bridge between the managed C# code and the unmanaged native Windows APIs. It uses the P/Invoke interoperability feature to declare function signatures from `kernel32.dll`.

- **Main Responsibility:** Declare `extern` methods with `[LibraryImport]` or `[DllImport]` attributes that correspond to Windows API functions, such as `CreateProcessA`, `VirtualAllocEx`, and `CreateRemoteThread`. It also defines data structures (`Startup_Info`, `Process_Information`) with a memory layout compatible with native code. For optimization, the handles to `kernel32.dll` and the address of the `LoadLibraryA` function are loaded statically upon initialization.

```csharp
// Snippet from NativeImports.cs
internal static unsafe partial class Native_Imports {
    private const string KERNEL32 = Constants.KERNEL32_DLL;
    
    internal static readonly IntPtr load_library_address = NativeLibrary.GetExport(s_kernel32_handle, Constants.LOAD_LIBRARY_FUNC);
    
    [LibraryImport(KERNEL32, SetLastError = true)]
    internal static partial int ResumeThread(SafeThreadHandle hThread);

    [LibraryImport(KERNEL32, SetLastError = true)]
    internal static partial IntPtr CreateRemoteThread(SafeProcessHandle hProcess, ...);
}
```

### 7. `ProcessHandler.cs`

This is the low-level layer that performs process manipulation operations. It uses the functions imported from `NativeImports.cs` to interact directly with the operating system.

- **Main Responsibilities:**
   1. **`Create_Game_Process`**: Builds the command line and starts `gta_sa.exe` with the `CREATE_SUSPENDED` flag.
   2. **`Inject_DLL`**: Implements the DLL injection technique by creating a remote thread. This is the most critical function, orchestrating memory allocation, writing, and remote execution of `LoadLibraryA`.
   3. **`Resume_Game_Thread`**: Performs the final step of "unfreezing" the game's main thread.

```csharp
// Snippet from ProcessHandler.cs
internal static bool Inject_DLL(SafeProcessHandle process_handle, string dll_path, out string error_message) {
    // ... Allocation and writing to remote memory ...

    IntPtr remote_thread = Native_Imports.CreateRemoteThread(process_handle, IntPtr.Zero, 0, Native_Imports.load_library_address, remote_memory, 0, IntPtr.Zero);

    if (remote_thread == IntPtr.Zero)
        return (error_message = $"Failed to create a remote thread...") != null && false;
    
    // ... Wait for completion and check the result ...
    return true;
}
```

### 8. `SafeHandles.cs`

This file implements a recommended interoperability practice: the use of `SafeHandle` to manage unmanaged resources. This ensures that Windows process and thread handles are released deterministically and safely.

- **Main Responsibility:** The `SafeProcessHandle` and `SafeThreadHandle` classes inherit from `SafeHandleZeroOrMinusOneIsInvalid`. They encapsulate an `IntPtr` that represents the native handle. The main advantage is the implementation of the `ReleaseHandle` method, which is guaranteed by the .NET runtime to be called when the object is disposed (e.g., at the end of a `using` block), preventing resource leaks.

```csharp
// Snippet from SafeHandles.cs
internal sealed class SafeProcessHandle : SafeHandleZeroOrMinusOneIsInvalid {
    // ... Constructors ...

    protected override bool ReleaseHandle() {
        // This call is guaranteed by .NET to release the native handle.
        return Native_Imports.CloseHandle(handle);
    }
}
```

## Detailed DLL Injection Cycle

The DLL injection process is a sequence of critical steps that need to be executed precisely to be successful. The **SA-MP Injector C#** library orchestrates this as follows:

### 1. Input Validation

Before any interaction with the system, all user-provided parameters (game folder path, nickname, IP, port, and password) are checked by `Input_Validator`. This includes:
- Checking if the nickname is within the length limits and not empty.
- Ensuring the port is a valid number and within the acceptable range (1-65535).
- Confirming that `gta_sa.exe`, `samp.dll`, and `omp-client.dll` (if `Injection_Type` is OMP) exist at the expected paths.

> [!NOTE]
> This preventive step is crucial to avoid unexpected API failures and provide clear feedback to the user.

### 2. Game Process Creation (Suspended)

The library uses `Native_Imports.CreateProcessA` to start `gta_sa.exe`. However, a crucial detail is the use of the `Constants.CREATE_SUSPENDED` flag.
- **Suspended Creation:** This flag causes Windows to create the process and its main thread, but places it in a suspended state, preventing the game's code from starting to execute.
- **Command Line:** The command line is carefully constructed by `Process_Handler.Build_Full_Command_Args_ANSI` to include all server connection parameters (`-c -n <nickname> -h <ip> -p <port> -z <password>`).
- **Process/Thread Handles:** `CreateProcessA` returns handles to the process and the main thread, which are encapsulated in `SafeProcessHandle` and `SafeThreadHandle` for safe resource management.

> [!IMPORTANT]
> Suspended creation is vital for injection. If the game started running before the injection, it could initialize its own security mechanisms, or `samp.dll`/`omp-client.dll` could be loaded before our control, making the injection more complex or ineffective.

### 3. `samp.dll` Injection

With the game process suspended, the `Process_Handler.Inject_DLL` function performs the following steps:
1. **Get `LoadLibraryA`:** The address of the `LoadLibraryA` function (from `kernel32.dll`) in the game process is obtained. This is the function Windows uses to load DLLs.
2. **Remote Memory Allocation:** `Native_Imports.VirtualAllocEx` is used to allocate a block of memory within the virtual address space of the `gta_sa.exe` process. The block size is sufficient to store the full path of `samp.dll`.
3. **Write DLL Path:** The full file path of `samp.dll` is written to the newly allocated memory in the game process using `Native_Imports.WriteProcessMemory`.
4. **Remote Thread Creation:** `Native_Imports.CreateRemoteThread` is called to create a new thread in the `gta_sa.exe` process. This thread is instructed to execute `LoadLibraryA` with the address of the DLL path string as its only argument.
5. **Wait for Completion:** The library waits for a timeout (`Constants.DLL_INJECTION_TIMEOUT_MS`) for the remote thread to complete its execution, indicating that `LoadLibraryA` has attempted to load the DLL.
6. **Check Result:** The exit code of the remote thread is checked. If `LoadLibraryA` was successful, it returns the base address of the loaded DLL. A zero value or failure to get the exit code indicates that the injection failed.
7. **Cleanup:** The allocated remote memory is freed (`Native_Imports.VirtualFreeEx`), and the remote thread's handle is closed (`Native_Imports.CloseHandle`).

### 4. `omp-client.dll` Injection (Optional, SA-MP Dependent)

> [!TIP]
> The injection of `omp-client.dll` **always occurs after the successful injection of `samp.dll`**. The OMP client uses the SA-MP infrastructure, so `samp.dll` is a requirement.

If the specified `Injection_Type` is `OMP`, step 3 is repeated to inject `omp-client.dll`. The logic is identical, ensuring that both libraries necessary for OMP are loaded before the game fully starts.

### Resume the Main Game Thread

Finally, after all necessary DLLs have been successfully injected, the `Process_Handler.Resume_Game_Thread` function is called. This function uses `Native_Imports.ResumeThread` to allow the main thread of `gta_sa.exe` to continue its execution. The game now starts with the SA-MP/OMP DLLs already loaded and the command-line arguments for server connection applied.

## Error Handling and Failure Cases

The library is designed to provide clear feedback in case of failure. Most errors are caught, and a descriptive `error_message` is returned to be presented to the user, usually via a `MessageBox`.

### Input Validation Errors

These errors occur before any system operations and are detected by `Input_Validator`.

#### Invalid Nickname

- **Error Message (Example 1):** `"Nickname cannot be empty. Please provide a valid nickname."`
- **Error Message (Example 2):** `"Nickname length exceeds the maximum allowed of 23 characters. Please use a shorter nickname."`
- **Why:** The nickname field is empty or exceeds the maximum limit of 23 characters.
- **Solution:** The user must provide a valid nickname that respects the character limit.

#### Invalid Port

- **Error Message (Example 1):** `"Invalid port format. The port must be a numeric value. Please provide a valid integer for the port."`
- **Error Message (Example 2):** `"The specified port number (70000) is outside the valid range of 1 to 65535. Please provide a valid port."`
- **Why:** The provided port is not an integer, or it is outside the valid range of 1 to 65535.
- **Solution:** The user must enter a valid port number within the specified range.

#### Missing Game/DLL Files

- **Error Message (Example 1):** `"Game executable not found. Please ensure 'gta_sa.exe' exists at the specified path: C:\Program Files (x86)\Rockstar Games\GTA San Andreas\gta_sa.exe"`
- **Error Message (Example 2):** `"SA-MP library not found. Please ensure 'samp.dll' exists at the specified path: C:\Program Files (x86)\Rockstar Games\GTA San Andreas\samp.dll"`
- **Error Message (Example 3, OMP):** `"OMP library not found. Please ensure 'omp-client.dll' exists at the specified path for OMP injection: C:\Program Files (x86)\Rockstar Games\GTA San Andreas\omp-client.dll"`
- **Why:** The game's executable (`gta_sa.exe`), the SA-MP DLL (`samp.dll`), or the OMP DLL (`omp-client.dll`) were not found in the specified game folder.
- **Solution:** The user should check the game folder path and ensure all necessary files are present.

### Process Creation Errors

These errors occur when the library attempts to start `gta_sa.exe`.

#### Failed to Create Process

- **Error Message (Example):** `"Failed to create game process. Ensure 'gta_sa.exe' is not running and you have sufficient permissions to execute the file. System Error: Access is denied."`
- **Why:**
   - **File in Use:** `gta_sa.exe` may already be running, preventing a new instance from being created, or the operating system may have a lock on the file.
   - **Permissions:** The user running the application may not have sufficient permissions to start a new process or to access the game executable.
   - **Invalid/Corrupted Path:** Although basic validation checks for existence, there may be read/execute permission issues or the executable may be corrupted.
- **Solution:** Make sure no other instances of `gta_sa.exe` are running. Run the application as an administrator, if possible. Check the integrity of the `gta_sa.exe` file.

### DLL Injection Errors

These are the most critical errors and occur during the attempt to inject `samp.dll` or `omp-client.dll` into the game process.

#### `kernel32.dll` Handle Unavailable

- **Error Message:** `"Failed to obtain a handle to kernel32.dll. This is an essential system library and this error indicates a severe system issue."`
- **Why:** The `kernel32.dll` library, fundamental for system operations in Windows, could not be loaded or its handle could not be obtained. This is extremely rare and suggests a serious problem with the operating system.
- **Solution:** Restarting the system might resolve it. Otherwise, it indicates a deeper issue with the Windows installation.

#### `LoadLibraryA` Function Unavailable

- **Error Message:** `"Failed to find the address of the LoadLibraryA function in kernel32.dll. This is critical for injecting the DLL."`
- **Why:** The `LoadLibraryA` function, essential for dynamically loading DLLs, could not be found in `kernel32.dll`. Like the previous error, this is a rare low-level problem.
- **Solution:** Similar to the unavailability of the `kernel32.dll` handle.

#### Remote Memory Allocation Failure

- **Error Message:** `"Failed to allocate memory in the target process. This might be due to insufficient permissions or process protection mechanisms."`
- **Why:** The library could not allocate a block of memory in the address space of `gta_sa.exe`.
   - **Permissions:** The application may not have the necessary permissions to modify the memory space of another process.
   - **Process Protection:** The `gta_sa.exe` process or the operating system may be applying protections against code injection.
   - **Address Space:** In extreme cases, the process's address space may be fragmented or lack sufficient contiguous memory, although unlikely for the size of a DLL path string.
- **Solution:** Run the application as an administrator. Check for security software (antivirus, anti-cheat) that might be blocking memory allocation in other processes.

#### Failure to Write to Process Memory

- **Error Message:** `"Failed to write DLL path to the target process memory. Verify process permissions and ensure the DLL path is accessible."`
- **Why:** The library allocated memory in the game process but could not write the DLL path to that location.
   - **Permissions:** Similar to memory allocation failure, this could be a write permission issue.
   - **Protection:** Operating system memory protection or anti-cheat could be preventing the write.
- **Solution:** Check permissions and security software.

#### Remote Thread Creation Failure

- **Error Message (Example):** `"Failed to create a remote thread in the target process to execute the DLL injection. This could be due to security restrictions or process state. System Error: Not enough memory resources are available to process this command."`
- **Why:** The `CreateRemoteThread` API failed to create a new thread in the `gta_sa.exe` process to call `LoadLibraryA`.
   - **Process Protection/Anti-Cheat:** Many anti-cheat systems and operating system protections monitor and block the creation of remote threads, as it is a common injection technique.
   - **Process State:** The game process might be in an inconsistent state that prevents thread creation.
- **Solution:** Temporarily disable any anti-cheat or antivirus software. Try running the application as an administrator.

#### Timeout or Error While Waiting for Injection

- **Error Message (Example):** `"Timeout or error waiting for DLL injection to complete. System Error: The wait operation timed out."`
- **Why:** The remote thread (which calls `LoadLibraryA`) did not finish its execution within the specified timeout (10 seconds).
   - **Freezing:** `LoadLibraryA` may have crashed or taken too long.
   - **Blocking:** Some security mechanism may have intercepted and blocked the execution of `LoadLibraryA` indefinitely.
- **Solution:** This may indicate that the DLL is taking too long to load or that something is preventing it. Checking system or SA-MP/OMP logs (if they exist) might help.

#### DLL Injection Failed or Returned an Error

- **Error Message:** `"DLL injection failed or returned an error. The LoadLibrary call may have failed in the target process."`
- **Why:** The remote thread completed, but the exit code of `LoadLibraryA` indicated failure (usually `0` or `NULL`).
   - **Missing/Corrupted DLL:** Despite the initial validation, the DLL might have been moved or corrupted between validation and injection.
   - **Missing DLL Dependencies:** `samp.dll` or `omp-client.dll` may depend on other DLLs that are not present in the game directory or the system PATH.
   - **Internal DLL Error:** The DLL itself may have an internal error that prevents it from loading correctly.
- **Solution:** Check the integrity of `samp.dll`/`omp-client.dll`. Ensure that all DLL dependencies are present.

### Error Resuming the Game Thread

This is the last possible error in the injection cycle.

- **Error Message (Example):** `"Failed to resume the game process thread: Invalid handle."`
- **Why:** The `ResumeThread` API failed to restart the main thread of `gta_sa.exe`.
   - **Invalid Handle:** The thread handle may have been invalidated for some reason.
   - **Permission Issue:** The application may not have permission to modify the thread's state.
- **Solution:** Try running the application as an administrator. If it persists, it may indicate a deeper system or game process stability issue.

## License

Copyright © **SA-MP Programming Community**

This software is licensed under the terms of the MIT License ("License"); you may use this software according to the License terms. A copy of the License can be obtained at: [MIT License](https://opensource.org/licenses/MIT)

### Terms and Conditions of Use

#### 1. Granted Permissions

This license grants, free of charge, to any person obtaining a copy of this software and associated documentation files, the following rights:
* To use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the software without restriction
* To permit persons to whom the software is furnished to do so, subject to the following conditions

#### 2. Mandatory Conditions

All copies or substantial portions of the software must include:
* The above copyright notice
* This permission notice
* The disclaimer notice below

#### 3. Copyright

The software and all associated documentation are protected by copyright laws. The **SA-MP Programming Community** retains the original copyright of the software.

#### 4. Disclaimer of Warranty and Limitation of Liability

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.

IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

---

For detailed information about the MIT License, visit: https://opensource.org/licenses/MIT