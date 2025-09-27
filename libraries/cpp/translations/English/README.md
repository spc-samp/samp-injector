# SA-MP Injector C++

<div align="center">

![C++](https://img.shields.io/badge/C%2B%2B-14%2F17%2F20-00599C?style=for-the-badge&logo=cplusplus)
![Platform](https://img.shields.io/badge/Platform-Windows-blue?style=for-the-badge&logo=windows&logoColor=white)
![Architecture](https://img.shields.io/badge/Architecture-x86%20(32--bit)-lightgrey?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)

**A C++ library to launch and automate the connection of SA-MP and OMP clients to servers, via DLL injection.**

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

- [SA-MP Injector C++](#sa-mp-injector-c)
  - [Languages](#languages)
  - [Table of Contents](#table-of-contents)
  - [Overview and Purpose](#overview-and-purpose)
  - [Design Principles](#design-principles)
    - [Fully `Header-Only`](#fully-header-only)
    - [Safe Resource Management (RAII)](#safe-resource-management-raii)
    - [Robustness and Error Checking](#robustness-and-error-checking)
    - [C++ Standard Flexibility](#c-standard-flexibility)
  - [Required Environment](#required-environment)
    - [For Development](#for-development)
    - [For Execution](#for-execution)
  - [Quick Start](#quick-start)
    - [Project Integration](#project-integration)
    - [Simplified Usage Example](#simplified-usage-example)
  - [Library Structure](#library-structure)
    - [1. `constants.hpp`](#1-constantshpp)
    - [2. `types.hpp`](#2-typeshpp)
    - [3. `version.hpp`](#3-versionhpp)
    - [4. `error_utils.hpp`](#4-error_utilshpp)
    - [5. `validation.hpp`](#5-validationhpp)
    - [6. `resource_handle.hpp`](#6-resource_handlehpp)
    - [7. `privileges.hpp`](#7-privilegeshpp)
    - [8. `process.hpp`](#8-processhpp)
    - [9. `injector_core.hpp`](#9-injector_corehpp)
    - [10. `injector.hpp`](#10-injectorhpp)
  - [The Detailed Injection Process](#the-detailed-injection-process)
    - [1. Initialization Request](#1-initialization-request)
    - [2. Environment Preparation](#2-environment-preparation)
    - [3. Integrity and Parameter Checks](#3-integrity-and-parameter-checks)
    - [4. Preparing Arguments for the Game](#4-preparing-arguments-for-the-game)
    - [5. Initializing the Game Process (Suspended)](#5-initializing-the-game-process-suspended)
    - [6. Injecting the SA-MP Library (`samp.dll`)](#6-injecting-the-sa-mp-library-sampdll)
    - [7. Injecting the OMP Library (`omp-client.dll`) - Conditional](#7-injecting-the-omp-library-omp-clientdll---conditional)
    - [8. Activating the Game](#8-activating-the-game)
  - [Error and Failure Diagnostics](#error-and-failure-diagnostics)
    - [Input Validation Failures](#input-validation-failures)
      - [Invalid Username](#invalid-username)
      - [Invalid Connection Port](#invalid-connection-port)
      - [Missing Essential Resources](#missing-essential-resources)
    - [Process Management Failures](#process-management-failures)
      - [Difficulty Starting the Game Process](#difficulty-starting-the-game-process)
    - [DLL Injection Problems](#dll-injection-problems)
      - [Unable to Locate `LoadLibraryW`](#unable-to-locate-loadlibraryw)
      - [Failure in Remote Memory Reservation](#failure-in-remote-memory-reservation)
      - [Inability to Write Data to the Process](#inability-to-write-data-to-the-process)
      - [Failure to Create Injection Thread](#failure-to-create-injection-thread)
      - [Timeout Exceeded or Error While Waiting for Injection](#timeout-exceeded-or-error-while-waiting-for-injection)
      - [Internal DLL Injection Failure](#internal-dll-injection-failure)
    - [Difficulty Resuming Game Execution](#difficulty-resuming-game-execution)
  - [License](#license)
    - [Terms and Conditions of Use](#terms-and-conditions-of-use)
      - [1. Granted Permissions](#1-granted-permissions)
      - [2. Mandatory Conditions](#2-mandatory-conditions)
      - [3. Copyright](#3-copyright)
      - [4. Disclaimer of Warranty and Limitation of Liability](#4-disclaimer-of-warranty-and-limitation-of-liability)

## Overview and Purpose

**SA-MP Injector C++** is a compact and easy-to-integrate C++ library designed to automate the process of launching and connecting to San Andreas Multiplayer (SA-MP) and Open Multiplayer (OMP) servers. Unlike starting `gta_sa.exe` directly, this solution programmatically loads the `samp.dll` or `omp-client.dll` libraries into the Grand Theft Auto: San Andreas game process in a controlled manner.

Its main goal is to empower C++ developers to create custom `launchers`, community management tools, or utilities that need to start GTA:SA with predefined connection parameters (such as username, IP address, port, and password), offering a fluid and automated user experience.

## Design Principles

The architecture of **SA-MP Injector C++** is based on modern design principles, focusing on security, efficiency, and ease of use.

### Fully `Header-Only`

This library is distributed exclusively through header files (`.hpp`). This drastically simplifies integration into C++ projects, eliminating the need to compile separate libraries, configure `linkers`, or manage binary dependencies.
- **Instant Integration:** Simply include the relevant `headers`.
- **Deep Optimization:** The compiler can perform aggressive `inlining` and `link-time` optimizations that result in a more compact and faster final code.

### Safe Resource Management (RAII)

The library extensively employs the **RAII (Resource Acquisition Is Initialization)** pattern. Critical system resources, such as Windows process and thread `handles`, are encapsulated by `std::unique_ptr` with custom `deleters`. This ensures that, regardless of the execution flow or the occurrence of exceptions, resources are always released correctly, preventing leaks and improving application stability.

### Robustness and Error Checking

Every critical step of the injection is preceded by rigorous validations and followed by Windows API error checks. Detailed error messages are provided to the end-user through dialog boxes, with system descriptions (`GetLastError()`) whenever possible. This approach minimizes the chance of undefined behavior and offers a clear diagnosis in case of failure.

### C++ Standard Flexibility

The library was built to be compatible with different C++ standards, from C++14 to C++20. This is achieved through conditional macros that allow the use of modern features (like `std::string_view`, `std::filesystem`, and `std::optional` from C++17+) when available, while maintaining a `fallback` to equivalent constructions in C++14. This approach ensures broad compatibility without sacrificing modernity.

## Required Environment

### For Development

- **C++ Compiler:** Compatible with **C++14 or higher**.
   - Microsoft Visual C++ (Visual Studio 2015, 2017, 2019, 2022)
   - GCC (version 5 or newer)
   - Clang (version 3.6 or newer)
- **Operating System:** **Windows**.
- **Windows SDK:** Required for access to the operating system APIs.
- **Compilation Architecture:** **x86 (32-bit)**. This is a strict requirement, as `gta_sa.exe` and the SA-MP/OMP DLLs operate exclusively on this architecture.

### For Execution

- **Operating System:** Any modern version of **Windows** compatible with the compiled binary.
- **Grand Theft Auto: San Andreas (GTA:SA):** A valid installation of the game is mandatory.
- **SA-MP or OMP Client DLLs:** The `samp.dll` or `omp-client.dll` files must be present in the game's root directory, corresponding to the desired injection type.

## Quick Start

The `header-only` nature of the library makes it easy to incorporate into any C++ project.

### Project Integration

1.  **Download the Headers:** Obtain the `.hpp` files of the library (by cloning the repository or downloading them directly).
2.  **Organize the Files:** It is recommended to create a subfolder in your project for the library's `headers`, for example, `MyProject/libraries/samp-injector/`.
3.  **Set the Architecture:** Configure your project to compile for the **x86 (32-bit)** architecture.

```cpp
// Example directory structure
MyProject/
├── src/
│   └── main.cpp
├── libraries/
│   └── samp-injector/
│       ├── constants.hpp
│       ├── error_utils.hpp
│       ├── injector.hpp // The main header to include
│       └── ... (other headers)
└── built/ (your output directory)
```

### Simplified Usage Example

To automate the connection to a server, simply invoke the `Initialize_Game` function and provide the details.

```cpp
#include <iostream>
#include <string>
//
#include "samp-launcher/injector.hpp" // Include the main header

int main() {
    // Parameters for game initialization and connection
    std::wstring inject_type = L"samp"; // Or L"omp" for Open Multiplayer
    std::wstring game_folder = L"C:\\Games\\GTA San Andreas"; // Full path of the GTA:SA folder
    std::wstring nickname = L"Name";
    std::wstring ip = L"127.0.0.1";
    std::wstring port = L"7777";
    std::wstring password = L""; // Leave empty if there is no password

    // The main call to start the game and inject the DLL
    Initialize_Game(inject_type, game_folder, nickname, ip, port, password);

    // In case of failure, a Windows error message box is displayed automatically.

    return 0;
}
```

## Library Structure

The library is carefully modularized into several header files, each with well-defined responsibilities, facilitating organization, maintenance, and reusability.

### 1. `constants.hpp`

This file is the **central repository** of the library, serving as a centralized repository of all fixed and unchangeable values that dictate the behavior and interoperability of **SA-MP Injector C++**. Its organization by logical categories promotes not only code clarity and readability but also facilitates maintenance and ensures strict consistency throughout the library's ecosystem.

Each constant is defined with `CONSTEXPR_VAR`, which expands to `inline constexpr` (for C++17+) or `static constexpr` (for C++14), ensuring that these values are evaluated at compile time, optimizing performance and type safety.

The organization of constants by category makes their purpose easier to understand:

- **Game Related Constants**
   - `MIN_PORT`: An `int` that defines the lowest valid port number for connecting to a server (value: `1`).
   - `MAX_PORT`: An `int` that establishes the highest valid port number for connecting to a server (value: `65535`).
   - `MAX_NICKNAME_LENGTH`: An `int` that specifies the maximum allowed length for the player's nickname (value: `23` characters), a limit imposed by the SA-MP/OMP client specifications.

- **Essential File Names**
   - `SAMP_DLL_NAME`: A `const wchar_t*` containing the file name of the main SA-MP client library (value: `L"samp.dll"`). Essential for injecting the classic client.
   - `OMP_DLL_NAME`: A `const wchar_t*` containing the file name of the Open Multiplayer client library (value: `L"omp-client.dll"`). Used specifically when the injection is of the OMP type.
   - `GAME_EXE_NAME`: A `const wchar_t*` storing the name of the base Grand Theft Auto: San Andreas game executable file (value: `L"gta_sa.exe"`). The main target of the injection.

- **System Libraries and Functions**
   - `KERNEL32_DLL`: A `const wchar_t*` that defines the name of the Windows system library (`L"kernel32.dll"`). This DLL is vital as it hosts the process and memory manipulation functions that the injector uses. The use of `wchar_t` ensures compatibility with API functions that handle wide characters, such as `GetModuleHandleW`.
   - `LOAD_LIBRARY_FUNC`: A `const char*` with the name of the function to dynamically load a DLL (value: `"LoadLibraryW"`). Although the library primarily operates with wide characters, the `GetProcAddress` function of the Windows API requires a function name in ANSI format (`char*`).

- **Command Line Arguments**
   - These constants define the prefixes for the arguments that are passed to `gta_sa.exe` to configure the client's connection. They are provided in `Wide Character` (`const wchar_t*`) for compatibility with `CreateProcessW`.
      - `CMD_ARG_CONFIG`: Argument for general settings (value: `L"-c"`).
      - `CMD_ARG_NICKNAME`: Argument for the player's nickname (value: `L"-n"`).
      - `CMD_ARG_HOST`: Argument for the server's IP address (value: `L"-h"`).
      - `CMD_ARG_PORT`: Argument for the server's port (value: `L"-p"`).
      - `CMD_ARG_PASSWORD`: Argument for the server's password (value: `L"-z"`). Used only if a password is provided.

- **Injection types as strings**
   - `INJECT_TYPE_SAMP`: A `const wchar_t*` for the string representation of the SA-MP injection type (value: `L"samp"`).
   - `INJECT_TYPE_OMP`: A `const wchar_t*` for the string representation of the OMP injection type (value: `L"omp"`).

- **Error message titles**
   - `ERROR_TITLE_SAMP`: A `const wchar_t*` that defines the default title for error dialog boxes related to SA-MP failures (value: `L"SA-MP Injector Error - SPC"`).
   - `ERROR_TITLE_OMP`: A `const wchar_t*` that defines the default title for error dialog boxes related to OMP failures (value: `L"OMP Injector Error - SPC"`).

- **Process creation flags**
   - `PROCESS_CREATION_FLAGS`: A `DWORD` that encapsulates the flags passed to `CreateProcessW`. Crucially, it includes `CREATE_SUSPENDED` (`0x00000004`), which starts the game process in a paused state, and `DETACHED_PROCESS` (`0x00000008`), which detaches the new process from the parent process's console.

- **Timeouts**
   - `DLL_INJECTION_TIMEOUT_MS`: A `DWORD` that specifies the maximum time (in milliseconds) the library will wait for the completion of the remote thread responsible for DLL injection (value: `10000ms`, or 10 seconds).

- **Memory allocation flags**
   - These constants are used for memory manipulation API calls, such as `VirtualAllocEx` and `VirtualProtect`.
      - `MEM_COMMIT`: A `DWORD` that reserves pages in virtual memory and "commits" them (allocates physical memory) (value: `0x1000`).
      - `MEM_RESERVE`: A `DWORD` that only reserves a range of virtual address space for later use (value: `0x2000`).
      - `MEM_RELEASE`: A `DWORD` that decommits and releases a region of pages (value: `0x8000`).
      - `MEMORY_ALLOCATION_TYPE`: A combination of `MEM_COMMIT` and `MEM_RESERVE`, used to allocate initial memory for the DLL path in the remote process.
      - `MEMORY_PROTECTION`: A `DWORD` that defines memory protection permissions (value: `PAGE_READWRITE` or `0x04` in the Windows API), allowing reading and writing to the allocated memory.

### 2. `types.hpp`

This concise file introduces an `enum class` to type the different injection modalities. The use of an enumerated type, instead of string literals, enhances code safety, prevents typos, and improves readability.

- **`Inject_Type`:** An `enum class` with two members: `SAMP` and `OMP`, representing the client types to be injected.

```cpp
// Example of types.hpp
namespace Types {
    enum class Inject_Type {
        SAMP, // Indicates injection for the SA-MP client
        OMP   // Indicates injection for the Open Multiplayer client
    };
}
```

### 3. `version.hpp`

Acting as a compatibility adapter, this header dynamically detects the C++ standard in use by the compiler. It defines conditional macros (`SAMP_INJECTOR_CXX_14`, `SAMP_INJECTOR_CXX_MODERN`) that guide the library to use the most advanced C++ features (like `std::string_view` or `std::filesystem`) when available, while ensuring full functionality in C++14 environments.

- **`SAMP_INJECTOR_CXX_14`:** Defined if the C++ standard is C++14.
- **`SAMP_INJECTOR_CXX_MODERN`:** Defined for C++17 or higher, enabling more recent language features.
- **`SAMP_INJECTOR_NODISCARD`:** Adapts the `[[nodiscard]]` attribute for C++ versions that support it, encouraging the checking of return values.

```cpp
// Example of a relevant snippet from version.hpp
#if (defined(_MSC_VER) && _MSVC_LANG >= 201703L) || __cplusplus >= 201703L
    #define SAMP_INJECTOR_CXX_MODERN // Enables modern C++17+ features
#endif

#if defined(SAMP_INJECTOR_CXX_MODERN)
    #define SAMP_INJECTOR_NODISCARD [[nodiscard]] // Uses the nodiscard attribute from C++17
#elif defined(SAMP_INJECTOR_CXX_14)
    #define SAMP_INJECTOR_NODISCARD // For C++14, the attribute is disabled
#endif
```

### 4. `error_utils.hpp`

This utility is dedicated to managing and presenting error feedback. It abstracts the Windows mechanisms for retrieving system error messages and provides a unified interface for notifying the user about problems.

- **`Get_System_Error_Message`:** Translates a Windows error code (`GetLastError()`) into a readable `std::wstring`, crucial for accurate diagnosis.
- **`Show_Error`:** Displays a dialog box (`MessageBoxW`) containing the provided error message, with a specific title for SA-MP or OMP, ensuring clear communication with the user.

```cpp
// Example of a relevant snippet from error_utils.hpp
namespace Error_Utils {
    SAMP_INJECTOR_NODISCARD
    inline std::wstring Get_System_Error_Message(DWORD error_code) {
        if (error_code == 0)
            return L"No error occurred.";
        
        // ... Logic to format the system message ...
    }

    inline void Show_Error(std::wstring_view message, Types::Inject_Type inject_type) {
        const std::wstring title = (inject_type == Types::Inject_Type::SAMP) ? Constants::ERROR_TITLE_SAMP : Constants::ERROR_TITLE_OMP;
        MessageBoxW(nullptr, message.data(), title.c_str(), MB_OK | MB_ICONERROR);
    }
}
```

### 5. `validation.hpp`

Acting as the library's front line of robustness, this header provides rigorous routines to verify the validity of input data and the presence of necessary files. These checks are performed before any low-level interaction with the system, mitigating runtime risks and providing proactive feedback.

- **`Validate_Port`:** Validates if the port string represents an integer and if it falls within the configured range (`MIN_PORT` to `MAX_PORT`).
- **`Validate_Nickname`:** Checks if the nickname is not empty and if its length does not exceed `MAX_NICKNAME_LENGTH`.
- **`Validate_Files`:** Confirms the physical existence of `gta_sa.exe`, `samp.dll`, and, conditionally for OMP injection, `omp-client.dll`. The implementation adapts to `std::filesystem` (C++17+) or `GetFileAttributesW` (C++14).

```cpp
// Example of a relevant snippet from validation.hpp
namespace Validation {
    inline bool Validate_Nickname(std::wstring_view nickname_str, std::wstring& error_message) {
        if (nickname_str.empty())
            return (error_message = L"Nickname cannot be empty. Please provide a valid nickname.", false);
        
        if (nickname_str.length() > Constants::MAX_NICKNAME_LENGTH)
            return (error_message = L"Nickname length exceeds the maximum allowed of " + std::to_wstring(Constants::MAX_NICKNAME_LENGTH) + L" characters. Please use a shorter nickname.", false);
        
        return true;
    }

    inline bool Validate_Files(const std::filesystem::path& game_path, const std::filesystem::path& samp_DLL_path, const std::filesystem::path& omp_DLL_path, Types::Inject_Type inject_type) {
        if (!std::filesystem::exists(game_path))
            return (Error_Utils::Show_Error(L"Game executable not found. Please ensure 'gta_sa.exe' exists at the specified path: " + game_path.wstring(), inject_type), false);
        
        // ... Other file checks ...
        return true;
    }
}
```

### 6. `resource_handle.hpp`

Implements an elegant and safe strategy for managing operating system resources, such as Windows `HANDLE`s. Using the RAII principle, it ensures that all allocated resources are properly released, preventing leaks and strengthening the application's stability.

- **`Unique_Resource`:** A `template alias` that adapts `std::unique_ptr` to work with custom `deleters`, allowing the management of any type of resource that requires a specific release function.
- **`Make_Unique_Handle`:** A convenient `factory` function that constructs and returns a `Unique_Resource` pre-configured for Windows `HANDLE`s. The associated `deleter` automatically invokes `CloseHandle` when the `Unique_Resource` goes out of scope, ensuring the immediate deallocation of the resource.

```cpp
// Example of a relevant snippet from resource_handle.hpp
namespace Resource_Handle {
    // A custom std::unique_ptr for managing system resources.
    template<typename T, typename Deleter>
    using Unique_Resource = std::unique_ptr<std::remove_pointer_t<T>, Deleter>;

    // Creates a Unique_Resource for a HANDLE, with a deleter that calls CloseHandle.
    template<typename T>
    inline auto Make_Unique_Handle(T handle) {
        return Unique_Resource<T, std::function<void(T)>>(handle, [](T h) {
            if (h && h != INVALID_HANDLE_VALUE) // Ensures the handle is valid before closing
                CloseHandle(h);
        });
    }
}
```

### 7. `privileges.hpp`

This component is responsible for configuring the security environment of the application process. It contains the functionality to elevate privileges, specifically enabling the debug privilege (`SE_DEBUG_NAME`), which is a fundamental requirement for the library to perform DLL injection operations into external Windows processes.

- **`Enable_Debug_Privilege`:** This function attempts to acquire and enable the `SE_DEBUG_NAME` privilege for the running process. It is a crucial initial step to grant the application the necessary permissions to manipulate other processes, such as allocating memory and creating remote threads. Returns `true` on success.

```cpp
// Example of a relevant snippet from privileges.hpp
namespace Privileges {
    inline bool Enable_Debug_Privilege() {
        HANDLE token_handle;

        // Tries to open the current process token to adjust privileges
        if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &token_handle))
            return false;

        auto handle_guard = Resource_Handle::Make_Unique_Handle(token_handle); // Safe management of the handle

        TOKEN_PRIVILEGES tp;
        LUID luid;

        // Looks up the LUID value for the SE_DEBUG_NAME privilege
        if (!LookupPrivilegeValue(nullptr, SE_DEBUG_NAME, &luid))
            return false;
        
        tp.PrivilegeCount = 1;
        tp.Privileges[0].Luid = luid;
        tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED; // Enables the privilege

        // Adjusts the process privileges
        if (!AdjustTokenPrivileges(token_handle, FALSE, &tp, sizeof(TOKEN_PRIVILEGES), nullptr, nullptr))
            return false;

        return GetLastError() == ERROR_SUCCESS; // Returns true if the operation was successful (no pending error)
    }
}
```

### 8. `process.hpp`

This is one of the most critical components of the library, containing the low-level implementation for interacting with Windows processes. It encapsulates the complex operations of creating the game process, allocating memory, writing data, and the DLL injection technique through the creation of remote threads.

- **`Process_Info` struct:** An internal structure that stores the `Unique_Resource`s for the process `HANDLE` (`process_handle`) and the main thread `HANDLE` (`thread_handle`) of the game. It includes a `Resume()` method to reactivate the game's main thread when the injection is complete.
- **`Injection_Status` enum class:** Defines a detailed list of possible outcomes for the DLL injection operation, allowing for precise failure diagnosis.
- **`Create_Game_Process`:**
   - Uses the `CreateProcessW` function from the Windows API to start the `gta_sa.exe` executable.
   - It is crucial that the process is created with the `CREATE_SUSPENDED` flag (included in `Constants::PROCESS_CREATION_FLAGS`). This ensures that the game is paused immediately after its creation, before any code is executed, allowing the DLL injection to occur in a safe state.
   - Returns an `std::optional<Process_Info>` (for C++17+) or a `std::unique_ptr<Process_Info>` (for C++14), containing the encapsulated handles of the process and thread.
- **`Inject_DLL`:**
   - Implements the standard DLL injection technique via `CreateRemoteThread`:
      1.  **Address Acquisition:** Using the constants from `constants.hpp`, it locates the address of the `LoadLibraryW` function (from `kernel32.dll`), which Windows uses to dynamically load libraries.
      2.  **Memory Allocation:** `VirtualAllocEx` is used to reserve a block of virtual memory within the game process (`gta_sa.exe`). This block is sized to contain the full path of the DLL to be injected.
      3.  **Path Writing:** The DLL path (e.g., `L"C:\\path\\to\\samp.dll"`) is then copied to the remotely allocated memory in the game process via `WriteProcessMemory`.
      4.  **Remote Thread Creation:** `CreateRemoteThread` starts a new thread in the context of the game process. The entry point of this thread is the address of `LoadLibraryW`, and the argument passed is the address of the DLL path string we just wrote.
      5.  **Monitoring:** The execution of the remote thread is monitored by `WaitForSingleObject` until it completes or `DLL_INJECTION_TIMEOUT_MS` is reached.
      6.  **Success Verification:** `GetExitCodeThread` is used to check the return value of the remote thread. If `LoadLibraryW` was successful, it will return the base address of the loaded DLL (a non-zero value).
      7.  **Cleanup:** The memory allocated in the remote process is freed by `VirtualFreeEx`.
   - Returns an `Injection_Status` indicating the success or the specific type of injection failure.

```cpp
// Example of a relevant snippet from process.hpp
class Process {
public:
    struct Process_Info {
        Resource_Handle::Unique_Resource<HANDLE, std::function<void(HANDLE)>> process_handle; // Process handle with RAII management
        Resource_Handle::Unique_Resource<HANDLE, std::function<void(HANDLE)>> thread_handle;  // Thread handle with RAII management

        bool Resume() { // Resumes the execution of the game's main thread
            return thread_handle && ResumeThread(thread_handle.get()) != static_cast<DWORD>(-1);
        }
    };
    
    enum class Injection_Status { // Detailed status codes for DLL injection
        SUCCESS,
        ALLOCATION_FAILED,
        WRITE_FAILED,
        KERNEL32_HANDLE_FAILED,
        LOADLIBRARY_ADDRESS_FAILED,
        THREAD_CREATION_FAILED,
        THREAD_WAIT_FAILED,
        GET_EXIT_CODE_FAILED,
        INJECTION_RETURNED_ERROR
    };

    // Creates the game process in a suspended state
    std::optional<Process_Info> Create_Game_Process(const std::wstring& game_path, std::wstring& command_args, const std::wstring& working_dir) {
        // ... Logic of CreateProcessW with CREATE_SUSPENDED ...
    }
    
    SAMP_INJECTOR_NODISCARD // Ensures the return value is used
    Injection_Status Inject_DLL(HANDLE process, const std::wstring& DLL_path) {
        static const LPVOID load_library_addr = reinterpret_cast<LPVOID>(GetProcAddress(GetModuleHandleW(Constants::KERNEL32_DLL), Constants::LOAD_LIBRARY_FUNC));

        if (!load_library_addr)
            return Injection_Status::LOADLIBRARY_ADDRESS_FAILED;

        LPVOID remote_memory = VirtualAllocEx(process, nullptr, (DLL_path.length() + 1) * sizeof(wchar_t), Constants::MEMORY_ALLOCATION_TYPE, Constants::MEMORY_PROTECTION);

        if (!remote_memory)
            return Injection_Status::ALLOCATION_FAILED;

        auto memory_guard = Resource_Handle::Unique_Resource<LPVOID, std::function<void(LPVOID)>>(remote_memory, [process](LPVOID ptr) {
            if (ptr)
                VirtualFreeEx(process, ptr, 0, MEM_RELEASE); // Frees the memory in the remote process
        });

        if (!WriteProcessMemory(process, remote_memory, DLL_path.c_str(), (DLL_path.length() + 1) * sizeof(wchar_t), nullptr))
            return Injection_Status::WRITE_FAILED;

        HANDLE remote_thread = CreateRemoteThread(process, nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(load_library_addr), remote_memory, 0, nullptr);

        if (!remote_thread)
            return Injection_Status::THREAD_CREATION_FAILED;

        auto thread_guard = Resource_Handle::Make_Unique_Handle(remote_thread); // Safe management of the remote thread handle

        if (WaitForSingleObject(remote_thread, Constants::DLL_INJECTION_TIMEOUT_MS) != WAIT_OBJECT_0)
            return Injection_Status::THREAD_WAIT_FAILED;

        DWORD exit_code = 0;

        if (!GetExitCodeThread(remote_thread, &exit_code))
            return Injection_Status::GET_EXIT_CODE_FAILED;

        if (exit_code == 0)
            return Injection_Status::INJECTION_RETURNED_ERROR;

        return Injection_Status::SUCCESS;
    }
};
```

### 9. `injector_core.hpp`

This header defines the `Injector_Core` class, which serves as the library's command center. It orchestrates the logical sequence of injection operations, connecting the input validation, privilege management, and process manipulation modules. It is here that the complete injection workflow is defined.

- **`Injector_Core`:** The constructor of this class is where `Privileges::Enable_Debug_Privilege()` is called. This ensures that the application process has the necessary privileges to perform DLL injection operations before any other critical logic is executed.
- **`Initialize_Game`:**
   1.  **Comprehensive Validation:** Starts by calling the validation functions (`Validation::Validate_Port`, `Validation::Validate_Nickname`, `Validation::Validate_Files`) to ensure all parameters and essential resources are in order. If any validation fails, an error is immediately reported.
   2.  **Argument Preparation:** Constructs the complete command line (`std::wstring`) that will be passed to `gta_sa.exe`, incorporating the provided nickname, IP, port, and password.
   3.  **Suspended Process Creation:** Invokes `Process::Create_Game_Process` to start `gta_sa.exe` in a suspended state, obtaining the handles to the process and its main thread.
   4.  **`samp.dll` Injection:** Calls `Inject_DLL_With_Status_Check` to inject `samp.dll` into the game process. This wrapper function is also responsible for interpreting the returned `Injection_Status` and displaying informative error messages.
   5.  **Conditional `omp-client.dll` Injection:** If the `inject_type` is `Types::Inject_Type::OMP`, `omp-client.dll` is then injected in the same way as `samp.dll`.
   6.  **Game Resumption:** After all successful injections, `process_info.Resume()` is called to allow the game's main thread to continue its execution.
   7.  **Error Handling in the Cycle:** Any failure in any of these critical steps will result in a call to `Error_Utils::Show_Error`, providing clear feedback to the user and ensuring that the process is terminated correctly (the handles are automatically released by the `Unique_Resource`s).
- **`Build_Command_Args`:** A helper function that organizes and concatenates the command-line arguments, adding quotes where necessary for parameters containing spaces.
- **`Inject_DLL_With_Status_Check`:** A private function that acts as a wrapper for `Process::Inject_DLL`. It maps the different `Injection_Status` to understandable error messages, facilitating error handling and communication with the user.

```cpp
// Example of a relevant snippet from injector_core.hpp
namespace Injector {
    class Injector_Core {
    public:
        Injector_Core() { // The constructor enables the debug privilege
            Privileges::Enable_Debug_Privilege();
        }

        bool Initialize_Game(Types::Inject_Type inject_type, std::wstring_view folder, std::wstring_view nickname, std::wstring_view ip, std::wstring_view port, std::wstring_view password) {
            std::wstring error_message;

            // Sequence of input validations
            if (!Validation::Validate_Port(port, error_message))
                return (Error_Utils::Show_Error(error_message, inject_type), false);
            // ... other validations ...

            // Builds the command-line arguments
            std::wstring args = Build_Command_Args({
                Command_Arg{Constants::CMD_ARG_NICKNAME, std::wstring(nickname)},
                // ... other arguments ...
            });

            Process process_core;
            // Creates the game process in a suspended state
            auto process_info_opt = process_core.Create_Game_Process(game_path, args, std::wstring(folder));

            if (!process_info_opt)
                return false;

            auto& process_info = *process_info_opt;

            // Injects samp.dll and, conditionally, omp-client.dll
            if (!Inject_DLL_With_Status_Check(process_core, process_info.process_handle.get(), Constants::SAMP_DLL_NAME, samp_DLL_path.wstring(), inject_type))
                return false;
            
            if (inject_type == Types::Inject_Type::OMP) {
                if (!Inject_DLL_With_Status_Check(process_core, process_info.process_handle.get(), Constants::OMP_DLL_NAME, omp_DLL_path.wstring(), inject_type))
                    return false;
            }
            
            // Resumes the game's main thread
            if (!process_info.Resume())
                return (Error_Utils::Show_Error(L"Failed to resume the game process thread: " + Error_Utils::Get_System_Error_Message(GetLastError()), inject_type), false);

            return true;
        }
    };
}
```

### 10. `injector.hpp`

This header acts as the main `Facade` of the library, offering a simplified entry point for any application wishing to use the injection functionality. It abstracts the internal complexity of `Injector_Core` into a single, convenient function.

- **`Initialize_Game`:**
   - This static function is the library's public interface.
   - First, it validates the `inject_type_str` (if it is `L"samp"` or `L"omp"`) and converts it to the `enum class Types::Inject_Type`. In case of an invalid string, it displays an error and terminates.
   - Then, it creates an instance of `Injector::Injector_Core`.
   - Finally, it delegates the execution of the main logic to `Injector_Core::Initialize_Game`, which is where the entire process of validation, process creation, and DLL injection is orchestrated.

```cpp
// Example of a relevant snippet from injector.hpp
// The public interface to start the game
#if defined(SAMP_INJECTOR_CXX_MODERN)
inline bool Initialize_Game(std::wstring_view inject_type, std::wstring_view folder, std::wstring_view nickname, std::wstring_view ip, std::wstring_view port, std::wstring_view password) {
#elif defined(SAMP_INJECTOR_CXX_14)
inline bool Initialize_Game(const std::wstring& inject_type, const std::wstring& folder, const std::wstring& nickname, const std::wstring& ip, const std::wstring& port, const std::wstring& password) {
#endif
    Types::Inject_Type type;

    // Converts the injection type string to the corresponding enum
    if (inject_type == Constants::INJECT_TYPE_SAMP)
        type = Types::Inject_Type::SAMP;
    else if (inject_type == Constants::INJECT_TYPE_OMP)
        type = Types::Inject_Type::OMP;
    else
        // Displays an error if the injection type is invalid
        return (Error_Utils::Show_Error(L"Invalid injection mode. Use 'samp' or 'omp'.", Types::Inject_Type::SAMP), false);

    Injector::Injector_Core injector; // Creates the injector core instance

    // Delegates the main logic to the Injector_Core
    return injector.Initialize_Game(type, folder, nickname, ip, port, password);
}
```

## The Detailed Injection Process

The core functionality of this library is to orchestrate a precise sequence of operations to inject the SA-MP or OMP client DLLs into the GTA:SA process. This cycle is carefully planned to ensure stability and compatibility.

### 1. Initialization Request

The process begins with a call to the global function `Initialize_Game` (`injector.hpp`), which acts as the main point of contact for the application using the library. This function receives all crucial parameters, such as the desired injection type (SA-MP or OMP), the game directory, and the server connection data (nickname, IP, port, password).

### 2. Environment Preparation

When invoked, the `Initialize_Game` function creates an instance of `Injector::Injector_Core`. In the constructor of this class (`injector_core.hpp`), the first and essential step of environment setup is executed: privilege elevation.

> [!NOTE]
> `Privileges::Enable_Debug_Privilege()`: This call (`privileges.hpp`) grants the application process the `SE_DEBUG_NAME` privilege. This privilege is vital as it allows the application to perform low-level operations on other Windows processes, such as reading and writing to their memory and creating remote threads – fundamental actions for the DLL injection technique.

### 3. Integrity and Parameter Checks

With the privileges adjusted, the `Injector_Core::Initialize_Game` method proceeds with a series of rigorous validations. This is a preventive phase that minimizes the chance of failures in later stages and provides immediate feedback to the user.

- **Port Validation:** `Validation::Validate_Port` checks if the connection port number is correctly formatted and falls within the range of `1` to `65535` (`constants.hpp`).
- **Nickname Validation:** `Validation::Validate_Nickname` ensures that the player's nickname is not empty and does not exceed the limit of `23` characters.
- **Essential Files Check:** `Validation::Validate_Files` inspects the game directory to confirm the presence of `gta_sa.exe`, `samp.dll`, and, if the injection is of the OMP type, also `omp-client.dll`.

> [!WARNING]
> Any failure at this stage results in the immediate display of a `MessageBox` with a detailed error message (`error_utils.hpp`) and the interruption of the injection process. This avoids futile attempts to proceed with an invalid configuration.

### 4. Preparing Arguments for the Game

After successful validation, the `Injector_Core::Build_Command_Args` function is responsible for building the formatted command line that will be passed to `gta_sa.exe`. This command line includes all the necessary parameters for the SA-MP/OMP client to automatically connect to a server, such as `-n "nickname" -h "IP" -p "Port" -z "Password"`.

### 5. Initializing the Game Process (Suspended)

The `Process` component (`process.hpp`) is then tasked with starting the GTA:SA executable.

> [!IMPORTANT]
> The `Process::Create_Game_Process` function uses the `CREATE_SUSPENDED` flag (`constants.hpp`) when calling the Windows `CreateProcessW` API. This is a critical design measure: the game is loaded into memory and its main thread is created, but its execution is **paused**. This creates a controlled and stable environment, ideal for injecting DLLs, before the game can initialize its own defenses or internal logic. The process and thread `handles` are obtained and safely managed via `Resource_Handle::Unique_Resource`.

### 6. Injecting the SA-MP Library (`samp.dll`)

With the game process in a suspended state, the injection of `samp.dll` can be performed safely. The `Injector_Core::Inject_DLL_With_Status_Check` method delegates this task to `Process::Inject_DLL`, which executes the following steps of the `remote thread injection` technique:

1.  **Locating the `LoadLibraryW` Function:** The address of the `LoadLibraryW` function is identified. This operation uses the `Constants::KERNEL32_DLL` and `Constants::LOAD_LIBRARY_FUNC` constants to get a `handle` to `kernel32.dll` and then locate the address of the dynamic library loading function.
2.  **Remote Memory Allocation:** `VirtualAllocEx` is used to reserve a block of memory in the virtual address space of the `gta_sa.exe` process (which is suspended). The size of this block is sufficient to store the full path of `samp.dll`.
3.  **Writing the DLL Path:** The full path of the `samp.dll` file is written to this newly allocated remote memory by `WriteProcessMemory`.
4.  **Remote Thread Creation:** `CreateRemoteThread` is called to create a new thread within the `gta_sa.exe` process. The entry point of this new thread is the address of `LoadLibraryW`, and the argument it receives is the pointer to the DLL path we just wrote.
5.  **Monitoring the Injection:** The execution of the remote thread is monitored by `WaitForSingleObject` for a period defined by `Constants::DLL_INJECTION_TIMEOUT_MS`.
6.  **Verifying the Result:** The exit code of the remote thread is obtained via `GetExitCodeThread`. A return value other than zero indicates that `LoadLibraryW` was successful in loading `samp.dll`.

> [!WARNING]
> In case of any failure during the injection of `samp.dll`, a specific error message (`error_utils.hpp`) is displayed, the injection process is aborted, and the resources are released.

### 7. Injecting the OMP Library (`omp-client.dll`) - Conditional

If the specified injection type is `OMP`, the steps detailed in point 6 are repeated for `omp-client.dll`.

> [!TIP]
> The injection of `omp-client.dll` always occurs after the successful injection of `samp.dll`. This is because the Open Multiplayer client relies on the infrastructure provided by `samp.dll`.

### 8. Activating the Game

Finally, if all injections were completed successfully, the `process_info.Resume()` method is invoked. This call executes `ResumeThread` on the main thread of `gta_sa.exe`. At this moment, the game is activated and begins its normal execution, but with the SA-MP/OMP DLLs already loaded in its memory and with the connection parameters configured, allowing for an automated connection to the server.

> [!WARNING]
> If resuming the game's thread fails, a final error message is presented to the user.

## Error and Failure Diagnostics

The library is meticulously designed to clearly communicate any issues that may arise during the startup and injection process. At any point of failure, a `MessageBox` with a detailed description is presented to the user, often supplemented with operating system error messages.

### Input Validation Failures

These errors are detected in the initial phase (`validation.hpp`), before any low-level interaction with the system, and indicate problems with the data provided by the user or with the environment's configuration.

#### Invalid Username

- **Error Message (Example 1):** `"Nickname cannot be empty. Please provide a valid nickname."`
- **Error Message (Example 2):** `"Nickname length exceeds the maximum allowed of 23 characters. Please use a shorter nickname."`
- **Reason:** The provided username (`nickname`) is empty or exceeds the maximum limit of 23 characters allowed by the SA-MP/OMP clients.
- **Solution:** The user must enter a valid username that respects the length criteria.

#### Invalid Connection Port

- **Error Message (Example 1):** `"Invalid port format. The port must be a numeric value. Please provide a valid integer for the port."`
- **Error Message (Example 2):** `"The specified port number (70000) is outside the valid range of 1 to 65535. Please provide a valid port."`
- **Reason:** The value provided for the port is not an integer or is outside the valid range (1 to 65535).
- **Solution:** The user needs to provide a valid port number within the specified range.

#### Missing Essential Resources

- **Error Message (Example 1):** `"Game executable not found. Please ensure 'gta_sa.exe' exists at the specified path: C:\Games\GTA San Andreas\gta_sa.exe"`
- **Error Message (Example 2):** `"SA-MP library not found. Please ensure 'samp.dll' exists at the specified path: C:\Games\GTA San Andreas\samp.dll"`
- **Error Message (Example 3, for OMP):** `"OMP library not found. Please ensure 'omp-client.dll' exists at the specified path for OMP injection: C:\Games\GTA San Andreas\omp-client.dll"`
- **Reason:** One or more crucial files (`gta_sa.exe`, `samp.dll`, `omp-client.dll`) were not found in the specified game directory.
- **Solution:** Check the game folder path and ensure that all necessary files are present and accessible.

### Process Management Failures

These errors occur when the library attempts to start the game's executable (`gta_sa.exe`).

#### Difficulty Starting the Game Process

- **Error Message (Example):** `"Failed to create game process. Ensure 'gta_sa.exe' is not running and you have sufficient permissions to execute the file. System Error: Access is denied."`
- **Reason:**
   - **Executable in Use:** `gta_sa.exe` may already be running, or there is an operating system lock that prevents the creation of a new instance.
   - **Insufficient Permissions:** The application may not have the proper permissions to start `gta_sa.exe` or to access the file.
   - **Corrupted Executable:** Although the basic validation checks for the file's existence, it might be corrupted or inaccessible.
- **Solution:** Make sure no instance of `gta_sa.exe` is active. Try running your application as an administrator. Check the integrity of the `gta_sa.exe` file.

### DLL Injection Problems

These are the most critical and detailed errors, occurring during the attempt to inject `samp.dll` or `omp-client.dll` into the suspended game process. The error messages usually start with `"Failed to inject <DLL_NAME>:\n"` and are followed by a specific description and a system error code.

#### Unable to Locate `LoadLibraryW`

- **Error Message (Part):** `"Failed to find the address of LoadLibraryW in kernel32.dll."`
- **Reason:** The `LoadLibraryW` function, a fundamental Windows API for dynamic DLL loading, could not be found in `kernel32.dll`. This is an extremely rare low-level problem that points to possible operating system corruption or a highly unusual execution environment.
- **Solution:** A system reboot might resolve it. If it persists, it may indicate a more serious problem with the Windows installation.

#### Failure in Remote Memory Reservation

- **Error Message (Part):** `"Failed to allocate memory in the target process (VirtualAllocEx). System Error: Not enough storage is available to process this command."`
- **Reason:** The library could not allocate a block of memory in the virtual address space of the `gta_sa.exe` process.
   - **Permissions:** Your application may not have sufficient permissions to modify the memory space of another process.
   - **Process Protection:** Operating system security mechanisms or anti-cheat software may be blocking memory allocation in external processes.
- **Solution:** Run your application as an administrator. Check if security programs (antivirus, anti-cheat) are interfering and, if possible, temporarily disable them for testing.

#### Inability to Write Data to the Process

- **Error Message (Part):** `"Failed to write DLL path to process memory (WriteProcessMemory). System Error: Access is denied."`
- **Reason:** Memory was allocated in the game process, but the library could not write the DLL path to that location.
   - **Permissions/Protection:** Similar to the memory allocation failure, it could be a write permission issue or an active memory protection.
- **Solution:** The same solutions for memory allocation failure apply.

#### Failure to Create Injection Thread

- **Error Message (Part):** `"Failed to create remote thread (CreateRemoteThread). System Error: The parameter is incorrect."`
- **Reason:** The `CreateRemoteThread` API failed to start a new thread in the `gta_sa.exe` process to invoke `LoadLibraryW`.
   - **Security:** Many anti-cheat systems and OS protections monitor and block the creation of remote threads, as it is a common injection technique.
   - **Process State:** The game process may be in an unstable state that prevents thread creation.
- **Solution:** Temporarily disable any anti-cheat or antivirus software. Try running the application as an administrator.

#### Timeout Exceeded or Error While Waiting for Injection

- **Error Message (Part):** `"Timeout or error waiting for remote thread (WaitForSingleObject). System Error: The wait operation timed out."`
- **Reason:** The remote thread (which calls `LoadLibraryW`) did not complete its execution within the established timeout (10 seconds).
   - **Freezing:** `LoadLibraryW` may have frozen, taken too long, or been intercepted/blocked.
- **Solution:** This may indicate that the DLL is having trouble loading or that something is preventing it. Checking system or SA-MP/OMP logs (if available) may offer more clues.

#### Internal DLL Injection Failure

- **Error Message (Part):** `"LoadLibraryW call failed in the target process. The DLL might be corrupt, missing dependencies, or blocked by security software."`
- **Reason:** The remote thread completed, but the return value of `LoadLibraryW` was `0` (or `NULL`), indicating that the DLL was not loaded successfully.
   - **Corrupted/Non-existent DLL:** The DLL may have been moved, deleted, or corrupted after the initial validation.
   - **Missing Dependencies:** `samp.dll` or `omp-client.dll` may have dependencies (other DLLs) that are not present in the game directory or in the system `PATH`.
   - **Internal DLL Error:** The DLL itself may have an internal error that prevents it from loading.
- **Solution:** Check the integrity of the `samp.dll`/`omp-client.dll` files. Make sure all their dependencies are present.

### Difficulty Resuming Game Execution

This is the last possible point of failure in the injection cycle.

- **Error Message (Example):** `"Failed to resume the game process thread: Invalid handle."`
- **Reason:** The `ResumeThread` API failed to reactivate the main thread of `gta_sa.exe`.
   - **Invalid Handle:** The thread `handle` may have been invalidated by some unexpected event.
   - **Permission:** The application may not have permission to change the thread's state.
- **Solution:** Try running the application as an administrator. If the problem persists, it may indicate a deeper stability issue in the system or the game process.

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