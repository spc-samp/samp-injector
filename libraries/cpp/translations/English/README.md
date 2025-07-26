# SA-MP Injector C++

![License](https://img.shields.io/badge/License-MIT-yellow.svg?style=flat)
![C++17](https://img.shields.io/badge/C%2B%2B-17-blue.svg?style=flat&logo=cplusplus)
![Platform](https://img.shields.io/badge/Platform-Windows-0078D6.svg?style=flat&logo=windows)
[![SA-MP | OMP](https://img.shields.io/badge/Support-SA--MP%20%7C%20OMP-yellow)](https://github.com/spc-samp/samp-injector)
![Code Quality](https://img.shields.io/badge/Code%20Quality-High-brightgreen.svg?style=flat)

The **SA-MP Injector C++** transcends the definition of a simple **DLL injection** tool. It is a carefully architected **C++ library**, designed to provide a robust and comprehensive solution for the programmatic initialization of the game **Grand Theft Auto: San Andreas** (**GTA:SA**) in conjunction with its multiplayer clients, specifically **SA-MP (San Andreas Multiplayer)** and **OMP (Open Multiplayer)**. Its primary goal is to simplify the game launch process, eliminating the complexity inherent in directly manipulating operating system processes and passing command-line arguments.

Developed with the purpose of offering maximum flexibility and easy integration, this `header-only` library eliminates the need for complex pre-compilations, allowing developers to incorporate it directly into their **C++ projects**. It not only orchestrates the **fundamental DLL injection** of the multiplayer client (`samp.dll` or `omp-client.dll`), but also intelligently manages all essential connection parameters (**nickname**, **IP address**, **port**, and **password**), simulating a native initialization through the intrinsic resources of the **Windows API**.

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
  - [Fundamental Concepts and Motivation](#fundamental-concepts-and-motivation)
    - [Why Inject DLLs?](#why-inject-dlls)
    - [SA-MP and OMP: Distinctions and Similarities](#sa-mp-and-omp-distinctions-and-similarities)
  - [Internal Library Architecture: A Deep Dive](#internal-library-architecture-a-deep-dive)
    - [`constants.hpp`](#constantshpp)
    - [`types.hpp`](#typeshpp)
    - [`string_utils.hpp`](#string_utilshpp)
    - [`error_utils.hpp`](#error_utilshpp)
    - [`resource_handle.hpp`](#resource_handlehpp)
    - [`validation.hpp`](#validationhpp)
    - [`process.hpp`](#processhpp)
    - [`injector_core.hpp`](#injector_corehpp)
    - [`injector.hpp`](#injectorhpp)
  - [Comprehensive Usage Examples](#comprehensive-usage-examples)
    - [1. Setting Up the Development Environment](#1-setting-up-the-development-environment)
    - [2. Basic Scenario: Connecting to an SA-MP Server](#2-basic-scenario-connecting-to-an-sa-mp-server)
    - [3. Advanced Scenario: Connecting to an OMP Server](#3-advanced-scenario-connecting-to-an-omp-server)
  - [Handling Common Errors and Messages](#handling-common-errors-and-messages)
    - [1. Invalid Injection Type](#1-invalid-injection-type)
    - [2. Invalid Server Port (Format or Range)](#2-invalid-server-port-format-or-range)
      - [2.1. Non-Numeric Port Format](#21-non-numeric-port-format)
      - [2.2. Port Out of Valid Range](#22-port-out-of-valid-range)
    - [3. Invalid Nickname (Empty or Too Long)](#3-invalid-nickname-empty-or-too-long)
      - [3.1. Empty Nickname](#31-empty-nickname)
      - [3.2. Nickname Too Long](#32-nickname-too-long)
    - [4. Game or DLL Files Not Found](#4-game-or-dll-files-not-found)
      - [4.1. Game Executable (`gta_sa.exe`) Not Found](#41-game-executable-gta_saexe-not-found)
      - [4.2. SA-MP Library (`samp.dll`) Not Found](#42-sa-mp-library-sampdll-not-found)
      - [4.3. OMP Library (`omp-client.dll`) Not Found (only for OMP injection)](#43-omp-library-omp-clientdll-not-found-only-for-omp-injection)
    - [5. Failure to Create Game Process](#5-failure-to-create-game-process)
    - [6. Failure to Allocate Memory in the Target Process](#6-failure-to-allocate-memory-in-the-target-process)
    - [7. Failure to Write DLL Path to Process Memory](#7-failure-to-write-dll-path-to-process-memory)
    - [8. Failure to Find Essential System Functions](#8-failure-to-find-essential-system-functions)
      - [8.1. `kernel32.dll` Not Found](#81-kernel32dll-not-found)
      - [8.2. `LoadLibraryA` Not Found](#82-loadlibrarya-not-found)
    - [9. Failure to Create Remote Thread for Injection](#9-failure-to-create-remote-thread-for-injection)
    - [10. Timeout or Failure in Injection Completion](#10-timeout-or-failure-in-injection-completion)
    - [11. Failure to Resume Game Process Thread](#11-failure-to-resume-game-process-thread)
  - [License](#license)
    - [Terms and Conditions of Use](#terms-and-conditions-of-use)
      - [1. Granted Permissions](#1-granted-permissions)
      - [2. Mandatory Conditions](#2-mandatory-conditions)
      - [3. Copyright](#3-copyright)
      - [4. Disclaimer of Warranty and Limitation of Liability](#4-disclaimer-of-warranty-and-limitation-of-liability)

## Fundamental Concepts and Motivation

### Why Inject DLLs?

> [!NOTE]
> **DLL (Dynamic Link Library) injection** is a method used in **Microsoft Windows** operating systems that allows the execution of code within the memory space of another running process. It is a powerful technique with various legitimate applications, from debugging and monitoring programs to modifying application behavior to extend their functionalities.

In the context of games like **GTA San Andreas**, which were not originally developed with integrated multiplayer functionality, **DLL injection** is the foundation for the existence of multiplayer clients like **SA-MP** and **OMP**. These clients are implemented as **DLLs** that, once injected into the `gta_sa.exe` process, take control, intercept game functions, and establish communication with multiplayer servers.

Instead of relying on an external launcher or direct modification of the game executable, **DLL injection** allows for a more flexible and programmable initialization, especially useful in environments where automating the connection to specific servers with predefined settings is desired.

### SA-MP and OMP: Distinctions and Similarities

**SA-MP** and **OMP** are the two main multiplayer platforms for **GTA San Andreas**. Both function as modifications to the base game, transforming it into a massively multiplayer online environment.

- **SA-MP (San Andreas Multiplayer)**: The original and most established client, widely used for many years. Its architecture requires the `samp.dll` to operate.
- **OMP (Open Multiplayer)**: An open-source project, often seen as a successor or more modern alternative to **SA-MP**, offering performance improvements, stability, and additional features. It requires the `omp-client.dll`.

Although they operate similarly (**injecting a DLL** into the **GTA:SA** process), the **SA-MP Injector C++** library was carefully developed to support **both DLLs**, recognizing their distinctions in file names and allowing the developer to choose the desired multiplayer client through a configuration parameter. This ensures that the library can be used with the wide range of servers and projects based on either platform.

## Internal Library Architecture: A Deep Dive

The **SA-MP Injector C++** adopts a modular and object-oriented approach (where applicable) to manage the complexity of the injection process. Each header file is a specialized module, responsible for a specific slice of the overall functionality, promoting code clarity, maintainability, and extensibility.

### `constants.hpp`

This file is the foundation of all fixed configurations in the library. It defines a `Constants` namespace to encapsulate all literals, ensuring no pollution of the global scope. The use of `inline constexpr` is crucial here: `constexpr` indicates that the values are evaluated at compile time, optimizing performance and ensuring immutability, while `inline` avoids redefinition issues when including the file in multiple compilation units.

```cpp
#pragma once

namespace Constants {
    // Game related constants
    inline constexpr int MIN_PORT = 1;
    inline constexpr int MAX_PORT = 65535;
    inline constexpr int MAX_NICKNAME_LENGTH = 23;
    
    // File names
    inline constexpr const wchar_t* SAMP_DLL_NAME = L"samp.dll";
    inline constexpr const wchar_t* OMP_DLL_NAME = L"omp-client.dll";
    inline constexpr const wchar_t* GAME_EXE_NAME = L"gta_sa.exe";
    
    // System libraries and functions
    inline constexpr const char* KERNEL32_DLL = "kernel32.dll";
    inline constexpr const char* LOAD_LIBRARY_FUNC = "LoadLibraryA"; // 'A' for ANSI/8-bit version
    
    // Command line arguments used by SA-MP/OMP clients
    inline constexpr const char* CMD_ARG_CONFIG = "-c";
    inline constexpr const char* CMD_ARG_NICKNAME = "-n";
    inline constexpr const char* CMD_ARG_HOST = "-h";
    inline constexpr const char* CMD_ARG_PORT = "-p";
    inline constexpr const char* CMD_ARG_PASSWORD = "-z";
    
    // Injection types as strings (wide-character)
    inline constexpr const wchar_t* INJECT_TYPE_SAMP = L"samp";
    inline constexpr const wchar_t* INJECT_TYPE_OMP = L"omp";
    
    // Error message titles for MessageBoxW
    inline constexpr const wchar_t* ERROR_TITLE_SAMP = L"SA-MP Injector Error - SPC";
    inline constexpr const wchar_t* ERROR_TITLE_OMP = L"OMP Injector Error - SPC";
    
    // Process creation flags for CreateProcessA
    inline constexpr DWORD PROCESS_CREATION_FLAGS = CREATE_SUSPENDED | DETACHED_PROCESS;
    
    // Timeouts for WaitForSingleObject (e.g., waiting for DLL injection)
    inline constexpr DWORD DLL_INJECTION_TIMEOUT_MS = 10000; // 10 seconds
    
    // Memory allocation flags for VirtualAllocEx
    inline constexpr DWORD MEMORY_ALLOCATION_TYPE = MEM_COMMIT | MEM_RESERVE;
    inline constexpr DWORD MEMORY_PROTECTION = PAGE_READWRITE; // Needed for writing DLL path
}
```

> [!TIP]
> The use of `wchar_t` for file names and error message titles is a recommended practice in **Windows development**. This ensures compatibility with all languages and character sets, especially useful for file paths that may contain **Unicode characters**. For **APIs** that expect `char` (such as `LoadLibraryA`), the conversion is explicitly performed in `string_utils.hpp`.

### `types.hpp`

A concise yet essential module for defining the enumeration that categorizes the supported injection types. This improves code readability and type safety, preventing errors from string or magic number usage.

```cpp
#pragma once

namespace Types {
    // Enumerations for supported injection types
    enum class Inject_Type {
        SAMP, // San Andreas Multiplayer
        OMP // Open Multiplayer
    };
}
```

### `string_utils.hpp`

Operating with the **Windows API** often requires conversion between different string encodings. This file provides a vital utility function for converting **wide-character** strings (`std::wstring_view`, used in the library's inputs) to **ANSI/8-bit** strings (`std::string`), which are required for **WinAPI** functions that operate with `char*` (such as `CreateProcessA` or `GetProcAddress`).

```cpp
#pragma once

#include <string>
#include <string_view>
#include <windows.h> // Necessary for WideCharToMultiByte

namespace Utils {
    inline std::string Wide_To_Local_8Bit(std::wstring_view wstr) {
        if (wstr.empty())
            return "";
        
        // Determines the required size for the resulting char string buffer
        int size = WideCharToMultiByte(CP_ACP, // ANSI Code Page (system locale dependent)
            0, // No additional flags
            wstr.data(), 
            static_cast<int>(wstr.size()), 
            nullptr, // Calculates size, does not fill buffer
            0, // Size 0, just for calculation
            nullptr, // Default character for unrepresentable characters
            nullptr); // Pointer to bool indicating if a default character was used

        if (size <= 0) // Returns an empty string in case of error or invalid size
            return "";

        std::string result(size, 0); // Allocates the string with the determined size
        // Performs the actual conversion, filling the 'result' buffer
        WideCharToMultiByte(CP_ACP, 
            0, 
            wstr.data(), 
            static_cast<int>(wstr.size()), 
            result.data(), // Destination buffer
            size, // Size of the destination buffer
            nullptr, 
            nullptr);

        return result;
    }
}
```

> [!IMPORTANT]
> The `CP_ACP` **(ANSI Code Page)** used in `WideCharToMultiByte` is the default code page of the **Windows** system. This means that the conversion may vary depending on the user's system language settings. For most use cases of file names and command-line arguments in **SA-MP**/**OMP** (which historically handle **ANSI** strings well), this approach is generally sufficient. However, in scenarios requiring full **Unicode** compatibility with external systems or global inputs, conversions to **UTF-8** (`CP_UTF8`) or other code pages would be necessary. For the scope of this project, `CP_ACP` is the functional standard.

### `error_utils.hpp`

A fundamental component for the library's usability, responsible for providing clear **feedback** to the user in case of failure. It centralizes the logic for retrieving system error messages and displaying dialog boxes.

```cpp
#pragma once

#include <string>
#include <string_view>
#include <windows.h> // For FormatMessageW and MessageBoxW
//
#include "types.hpp"
#include "constants.hpp"

namespace Utils {
    // Returns the Windows system error message for a specific error code
    inline std::wstring Get_System_Error_Message(DWORD error_code) {
        wchar_t buffer[512] = {0}; // Buffer for the message
        // FormatMessageW fills the buffer with the system error description
        DWORD result = FormatMessageW(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, 
            nullptr, // Message source (from the system)
            error_code, 
            0, // Language (use default)
            buffer, 
            512, // Buffer size
            nullptr);
        
        // If the function succeeded, return the buffer string; otherwise, a generic message
        return result ? std::wstring(buffer) : L"Unknown error (Code: " + std::to_wstring(error_code) + L")";
    }

    // Displays an error message box to the user
    inline void Show_Error(std::wstring_view message, Types::Inject_Type injectType) {
        // Chooses the dialog box title based on the injection type
        std::wstring title = (injectType == Types::Inject_Type::SAMP) ? Constants::ERROR_TITLE_SAMP : Constants::ERROR_TITLE_OMP;
        MessageBoxW(nullptr, // Parent window handle (nullptr for desktop)
            message.data(), 
            title.c_str(), 
            MB_OK | MB_ICONERROR); // OK button and error icon
    }
}
```

> [!NOTE]
> The `FormatMessageW` function is a powerful **Windows API** that retrieves the textual description of a system error code. It handles localization and provides clear messages that are essential for effective **diagnosis**, transforming a `DWORD` like `ERROR_FILE_NOT_FOUND` (2) into `L"The system cannot find the file specified."`.

### `resource_handle.hpp`

Safe resource management (such as **Windows** `HANDLE`s) is critical to avoid resource leaks and undefined behaviors. This file defines a `UniqueResource` using `std::unique_ptr` and a customized function for `CloseHandle`. This follows the **RAII (Resource Acquisition Is Initialization)** principle, ensuring that `HANDLE`s are automatically closed when their **wrappers** go out of scope, even in case of exceptions.

```cpp
#pragma once

#include <memory> // For std::unique_ptr
#include <functional> // For std::function
#include <windows.h> // For HANDLE and CloseHandle

namespace Utils {
    // Type alias for a std::unique_ptr that manages a HANDLE (or pointer) with a custom deleter
    // T: The type of resource to be managed (e.g., HANDLE, LPVOID)
    // Deleter: A class or lambda that knows how to release the resource
    template<typename T, typename Deleter>
    using UniqueResource = std::unique_ptr<std::remove_pointer_t<T>, Deleter>;

    // Helper function to create a UniqueResource instance for HANDLEs
    // It assumes T is a handle type and uses CloseHandle as the deleter.
    template<typename T>
    inline auto Make_Unique_Handle(T handle) {
        return UniqueResource<T, std::function<void(T)>>(handle, [](T h) {
            // Condition to ensure the handle is valid before attempting to close it
            // 0 and INVALID_HANDLE_VALUE are considered invalid for most handles
            if (h && h != INVALID_HANDLE_VALUE)
                CloseHandle(h); // Releases the HANDLE from the operating system
        });
    }
}
```

> [!IMPORTANT]
> The use of `UniqueResource` is a demonstration of good practices in **modern C++** and safe **Windows** development. It drastically simplifies the management of **handle** lifecycles, which, if not properly closed, can lead to memory or **kernel** resource leaks, impacting system stability over time.

### `validation.hpp`

The robustness of the injection begins with validating user inputs and checking file dependencies. This module contains functions that ensure all prerequisites and parameters are correct before attempting to start the injection process, preventing more complex errors later.

```cpp
#pragma once

#include <string>
#include <string_view>
#include <filesystem> // For std::filesystem::exists
//
#include "constants.hpp"
#include "types.hpp"
#include "string_utils.hpp" // For Wide_To_Local_8Bit
#include "error_utils.hpp" // For Show_Error

namespace Utils {
    // Validates if a port string is a valid number and within the allowed range
    inline bool Validate_Port(std::wstring_view port_str, std::wstring& error_message) {
        try {
            // Attempts to convert the wide-character string to std::string and then to int
            int port_num = std::stoi(Wide_To_Local_8Bit(port_str));

            // Checks if the port is within the valid range (1-65535)
            if (port_num < Constants::MIN_PORT || port_num > Constants::MAX_PORT)
                return (error_message = L"The specified port number (" + std::wstring(port_str) + 
                L") is outside the valid range of " +  std::to_wstring(Constants::MIN_PORT) + 
                L" to " + std::to_wstring(Constants::MAX_PORT) + 
                L". Please provide a valid port.", false);

            return true;
        }
        catch (...) { // Catches any exception (e.g., std::invalid_argument for non-numeric)
            return (error_message = L"Invalid port format. The port must be a numeric value. Please provide a valid integer for the port.", false);
        }
    }

    // Validates the nickname, checking if it is not empty and if the length is acceptable
    inline bool Validate_Nickname(std::wstring_view nickname_str, std::wstring& error_message) {
        if (nickname_str.empty())
            return (error_message = L"Nickname cannot be empty. Please provide a valid nickname.", false);
        
        if (nickname_str.size() > Constants::MAX_NICKNAME_LENGTH)
            return (error_message = L"Nickname length exceeds the maximum allowed of " + 
                std::to_wstring(Constants::MAX_NICKNAME_LENGTH) + 
                L" characters. Please use a shorter nickname.", false);

        return true;
    }

    // Validates the existence of critical files (gta_sa.exe, samp.dll, omp-client.dll)
    inline bool Validate_Files(const std::filesystem::path& game_path, 
        const std::filesystem::path& samp_DLL_path, 
        const std::filesystem::path& omp_DLL_path, 
        Types::Inject_Type inject_type) {
        std::wstring error_message_local; // Local variable used before passing to Show_Error
        
        // Checks the existence of the game executable
        if (!std::filesystem::exists(game_path)) {
            error_message_local = L"Game executable not found. Please ensure 'gta_sa.exe' exists at the specified path: " + game_path.wstring();
            Show_Error(error_message_local, inject_type);
            
            return false;
        }

        // Checks the existence of samp.dll (essential for both injection types)
        if (!std::filesystem::exists(samp_DLL_path)) {
            error_message_local = L"SA-MP library not found. Please ensure 'samp.dll' exists at the specified path: " + samp_DLL_path.wstring();
            Show_Error(error_message_local, inject_type);

            return false;
        }

        // If the injection type is OMP, checks the existence of omp-client.dll
        if (inject_type == Types::Inject_Type::OMP && !std::filesystem::exists(omp_DLL_path)) {
            error_message_local = L"OMP library not found. Please ensure 'omp-client.dll' exists at the specified path for OMP injection: " + omp_DLL_path.wstring();
            Show_Error(error_message_local, inject_type);

            return false;
        }

        return true; // All required files were found
    }
}
```

> [!NOTE]
> The use of `std::filesystem` is a modern addition to **C++17** that offers a powerful and platform-independent way to interact with the file system. For this project on **Windows**, it simplifies the handling of paths and file existence checks compared to older **WinAPI** functions.
>
> Ensure that your compiler supports **C++17** to use `std::filesystem`. You will need to configure your project to use the **C++17** standard (`/std:c++17` in **Visual Studio**).

### `process.hpp`

This is the main module responsible for direct interaction with low-level **Windows APIs** to manipulate processes. It encapsulates the critical operations of process creation and **DLL injection**, handling **handles**, **memory**, and **threads**.

```cpp
#pragma once

#include <string_view>
#include <optional> // For std::optional
#include <functional> // For std::function (used in UniqueResource)
#include <windows.h> // Windows APIs
#include <memory> // For std::unique_ptr
#include <vector> // For std::vector (args buffer)
//
#include "resource_handle.hpp" // Our wrapper for HANDLEs
#include "error_utils.hpp" // For Get_System_Error_Message and Show_Error
#include "constants.hpp" // Global constants
#include "types.hpp" // Injection types

class Process {
    public:
        // Constructors/Destructors and assignment operators
        // Explicitly default and delete to ensure value semantics and move-only.
        Process() = default;
        Process(const Process&) = delete; // No copy
        Process& operator=(const Process&) = delete; // No copy assignment
        Process(Process&&) = default; // Move semantics
        Process& operator=(Process&&) = default; // Move assignment
        ~Process() = default;

        // Structure to store process and thread handles, managed by UniqueResource
        struct Process_Info {
            Resource_Handle::UniqueResource<HANDLE, std::function<void(HANDLE)>> process_handle;
            Resource_Handle::UniqueResource<HANDLE, std::function<void(HANDLE)>> thread_handle;
        };

        // Creates the GTA:SA game process in a suspended state
        std::optional<Process_Info> Create_Game_Process(std::string_view game_path, std::string_view command_args, std::string_view working_dir) {
            STARTUPINFOA startup_info{}; // Structure for process startup information
            startup_info.cb = sizeof(STARTUPINFOA); // Sets the structure size

            PROCESS_INFORMATION process_info{}; // Structure to receive information about the new process

            // Creates a mutable buffer for command-line arguments.
            // CreateProcessA modifies the command-line buffer, so std::string_view directly won't work.
            std::vector<char> args_buffer(command_args.size() + 1); // +1 for null terminator

            if (!command_args.empty()) {
                std::memcpy(args_buffer.data(), command_args.data(), command_args.size());
                args_buffer[command_args.size()] = '\0'; // Ensures null terminator
            }

            // Creates the process
            bool success = CreateProcessA(game_path.data(), // Executable module name
                args_buffer.empty() ? nullptr : args_buffer.data(), // Command-line arguments
                nullptr, // Process security attributes
                nullptr, // Thread security attributes
                FALSE, // Do not inherit handles
                Constants::PROCESS_CREATION_FLAGS, // CREATE_SUSPENDED | DETACHED_PROCESS
                nullptr, // New process environment
                working_dir.empty() ? nullptr : working_dir.data(), // Working directory
                &startup_info, // Startup information
                &process_info); // Created process information

            if (!success) {
                // If failed, retrieves and displays the system error message
                std::wstring error_msg = Error_Utils::Get_System_Error_Message(GetLastError());
                Error_Utils::Show_Error(L"Failed to create game process. Ensure 'gta_sa.exe' is not running and you have " L"sufficient permissions to execute the file. System Error: " + error_msg, Types::Inject_Type::SAMP); // Uses SAMP as fallback for the title
                
                return std::nullopt; // Returns an empty optional
            }

            Process_Info result;
            // Stores the process and thread handles in UniqueResource for automatic management
            result.process_handle = Resource_Handle::Make_Unique_Handle(process_info.hProcess);
            result.thread_handle = Resource_Handle::Make_Unique_Handle(process_info.hThread);

            return result; // Returns the structure with managed handles
        }

        // Injects a DLL into the remote process
        bool Inject_DLL(HANDLE process, std::string_view DLL_path, std::wstring& error_message) {
            // Allocates memory in the remote process for the DLL path
            LPVOID remote_memory = VirtualAllocEx(process, // Target process handle
            nullptr, // Preferred address (nullptr to let the system choose)
            DLL_path.size() + 1, // Path size + null terminator
            Constants::MEMORY_ALLOCATION_TYPE, // MEM_COMMIT | MEM_RESERVE
            Constants::MEMORY_PROTECTION); // PAGE_READWRITE

            if (!remote_memory)
                return (error_message = L"Failed to allocate memory in the target process. This might be due to " L"insufficient permissions or process protection mechanisms.", false);

            // Resource management for the remotely allocated memory.
            // It will be automatically freed when out of scope.
            auto memory_guard = Resource_Handle::UniqueResource<LPVOID, std::function<void(LPVOID)>>(remote_memory, 
                [process](LPVOID ptr) { // Lambda as deleter
                    if (ptr)
                        VirtualFreeEx(process, ptr, 0, MEM_RELEASE); // Frees the allocated memory
                }
            );

            // Writes the DLL path to the remotely allocated memory
            if (!WriteProcessMemory(process, remote_memory, DLL_path.data(), DLL_path.size() + 1, nullptr))
                return (error_message = L"Failed to write DLL path to the target process memory. Verify process " L"permissions and ensure the DLL path is accessible.", false);

            // Obtains the handle for kernel32.dll (loaded in the injector's own process)
            HMODULE kernel32 = GetModuleHandleA(Constants::KERNEL32_DLL);
            
            if (!kernel32)
                return (error_message = L"Failed to obtain a handle to kernel32.dll. This is an essential system " L"library and this error indicates a severe system issue.", false);

            // Obtains the address of the LoadLibraryA function in kernel32.dll.
            // This address is consistent across processes in the same OS and is key to injection.
            LPVOID load_library_addr = reinterpret_cast<LPVOID>(GetProcAddress(kernel32, Constants::LOAD_LIBRARY_FUNC));

            if (!load_library_addr)
                return (error_message = L"Failed to find the address of the LoadLibraryA function in kernel32.dll. " L"This is critical for injecting the DLL.", false);

            // Creates a remote thread in the target process to execute LoadLibraryA
            // The argument for LoadLibraryA will be the remote address of the DLL path
            HANDLE remote_thread = CreateRemoteThread(process, // Target process handle
                nullptr, // Thread security attributes
                0, // Stack size (0 for default)
                reinterpret_cast<LPTHREAD_START_ROUTINE>(load_library_addr), // Address of LoadLibraryA
                remote_memory, // Argument for LoadLibraryA (DLL path)
                0, // Creation flags (0 to start immediately)
                nullptr); // Thread ID (nullptr to not return)

            if (!remote_thread)
                return (error_message = L"Failed to create a remote thread in the target process to execute the " L"DLL injection. This could be due to security restrictions or process "
                    L"state. System Error: " + Error_Utils::Get_System_Error_Message(GetLastError()), false);

            // Resource management for the remote thread handle
            auto thread_guard = Resource_Handle::Make_Unique_Handle(remote_thread);

            // Waits for the remote thread (DLL injection) to complete or reach a timeout
            DWORD wait_result = WaitForSingleObject(remote_thread, Constants::DLL_INJECTION_TIMEOUT_MS);

            if (wait_result != WAIT_OBJECT_0) {
                return (error_message = L"Timeout or error waiting for DLL injection to complete. " L"System Error: " + Error_Utils::Get_System_Error_Message(GetLastError()), false);

            // Obtains the exit code of the remote thread.
            // For LoadLibraryA, an exit code of 0 means failure (could not load the DLL).
            DWORD exit_code = 0;

            if (!GetExitCodeThread(remote_thread, &exit_code) || exit_code == 0)
                return (error_message = L"DLL injection failed or returned an error. The LoadLibrary call " L"may have failed in the target process.", false);

            return true; // Injection successful
        }
};
```

> [!NOTE]
> The `process.hpp` module demonstrates a robust and safe design. The `Create_Game_Process` function returns a `std::optional<Process_Info>`. This allows the function to explicitly and elegantly signal process creation failures (returning a `std::nullopt`) without resorting to exceptions or ambiguous error codes in its main return.
>
> More crucially, the `Process_Info` structure uses `Resource_Handle::UniqueResource<HANDLE, std::function<void(HANDLE)>>` to encapsulate the process and **thread** **handles**. This is an example of the **RAII (Resource Acquisition Is Initialization)** pattern, which ensures that the operating system's `HANDLE`s (such as `hProcess` and `hThread`) are automatically closed via `CloseHandle` when the `Process_Info` object goes out of scope. This eliminates **handle** leaks, which are a common source of instability and excessive resource consumption in long-running **Windows applications**.
>
> Similarly, within the `Inject_DLL` function, `UniqueResource` is used to manage remotely allocated memory (`VirtualAllocEx`), ensuring it is freed (`VirtualFreeEx`) as soon as it is no longer needed or in case of failure. This rigorous resource management significantly contributes to the reliability and stability of the **SA-MP Injector C++**.

### `injector_core.hpp`

This is the orchestrating class that ties together all the functionalities of the previous modules. It coordinates validation, command-line argument construction, process creation, and **DLL injection** calls.

```cpp
#pragma once

#include <string_view>
#include <sstream> // For building strings with stringstream
#include <filesystem> // For path manipulation
//
#include "process.hpp" // Process creation/injection functions
#include "validation.hpp" // Input validation functions
#include "string_utils.hpp" // String conversion functions
#include "error_utils.hpp" // Error handling functions
#include "constants.hpp" // Library constants
#include "types.hpp" // Injection types

namespace Injector {
    class Injector_Core {
        public:
            // Constructors/Destructors for move semantics
            Injector_Core() = default;
            Injector_Core(const Injector_Core&) = delete; // Disables copy
            Injector_Core& operator=(const Injector_Core&) = delete; // Disables copy assignment
            Injector_Core(Injector_Core&&) = default; // Enables move
            Injector_Core& operator=(Injector_Core&&) = default; // Enables move assignment
            ~Injector_Core() = default;

            // Main function that orchestrates game initialization and injection
            bool Initialize_Game(Types::Inject_Type inject_type, std::wstring_view folder, std::wstring_view nickname, std::wstring_view ip, std::wstring_view port, std::wstring_view password) {
                namespace fs = std::filesystem; // Alias for std::filesystem

                // Builds the full paths for essential files
                fs::path game_path = fs::path(folder) / Constants::GAME_EXE_NAME; // Ex: C:\GTA\gta_sa.exe
                fs::path samp_DLL_path = fs::path(folder) / Constants::SAMP_DLL_NAME; // Ex: C:\GTA\samp.dll
                fs::path omp_DLL_path = fs::path(folder) / Constants::OMP_DLL_NAME; // Ex: C:\GTA\omp-client.dll

                // 1. File Validation
                if (!Validation::Validate_Files(game_path, samp_DLL_path, omp_DLL_path, inject_type))
                    return false; // Error already displayed by the validation function
                
                std::wstring error_message_local; // To receive error messages from validations

                // 2. Port Validation
                if (!Validation::Validate_Port(port, error_message_local))
                    return (Error_Utils::Show_Error(error_message_local, inject_type), false);

                // 3. Nickname Validation
                if (!Validation::Validate_Nickname(nickname, error_message_local))
                    return (Error_Utils::Show_Error(error_message_local, inject_type), false);

                // 4. Wide-char to Local 8-bit Conversion (required for ANSI APIs)
                std::string nickname_str = String_Utils::Wide_To_Local_8Bit(nickname);
                std::string ip_str = String_Utils::Wide_To_Local_8Bit(ip);
                std::string port_str = String_Utils::Wide_To_Local_8Bit(port);
                std::string password_str = String_Utils::Wide_To_Local_8Bit(password);
                // Also converts paths to std::string (required by CreateProcessA as char*)
                std::string game_path_str = String_Utils::Wide_To_Local_8Bit(game_path.wstring());
                std::string folder_str = String_Utils::Wide_To_Local_8Bit(folder);
                std::string samp_DLL_path_str = String_Utils::Wide_To_Local_8Bit(samp_DLL_path.wstring());
                std::string omp_DLL_path_str = String_Utils::Wide_To_Local_8Bit(omp_DLL_path.wstring());

                // 5. Command-Line Argument Construction
                std::string args = Build_Command_Args(nickname_str, ip_str, port_str, password_str);

                // Instantiates the Process class to manage process operations
                Process process_core;
                
                // 6. Game Process Creation (Suspended)
                auto process_info_opt = process_core.Create_Game_Process(game_path_str, args, folder_str);

                if (!process_info_opt)
                    return false; // Error already displayed by the process creation function

                // Dereferences the optional to obtain the Process_Info structure
                auto& process_info = *process_info_opt; 
                std::wstring inject_error_message; // To receive error messages from injection

                // 7. Injection of samp.dll
                if (!process_core.Inject_DLL(process_info.process_handle.get(), samp_DLL_path_str, inject_error_message))
                    return (Error_Utils::Show_Error(L"Failed to inject samp.dll: " + inject_error_message, inject_type), false);

                // 8. Conditional injection of omp-client.dll (only if OMP)
                if (inject_type == Types::Inject_Type::OMP) {
                    if (!process_core.Inject_DLL(process_info.process_handle.get(), omp_DLL_path_str, inject_error_message))
                        return (Error_Utils::Show_Error(L"Failed to inject omp-client.dll: " + inject_error_message, inject_type), false);
                }

                // 9. Resume Game Process
                // The process was created in a suspended state to allow injection.
                // Now that the DLLs have been injected, it can be resumed.
                if (ResumeThread(process_info.thread_handle.get()) == static_cast<DWORD>(-1))
                    return (Error_Utils::Show_Error(L"Failed to resume the game process thread: " + Error_Utils::Get_System_Error_Message(GetLastError()), inject_type), false);

                return true; // Success in all steps!
            }
        private:
            // Builds the command-line argument string for the game executable
            std::string Build_Command_Args(const std::string& nickname, const std::string& ip, const std::string& port, const std::string& password) {
                std::stringstream command_args_stream; // Uses stringstream for efficient construction

                // SA-MP and OMP expect the arguments "-c -n [nickname] -h [ip] -p [port]"
                command_args_stream << Constants::CMD_ARG_CONFIG << " " 
                    << Constants::CMD_ARG_NICKNAME << " " << nickname << " " 
                    << Constants::CMD_ARG_HOST << " " << ip << " " 
                    << Constants::CMD_ARG_PORT << " " << port;

                // Adds the password only if it is not empty
                if (!password.empty())
                    command_args_stream << " " << Constants::CMD_ARG_PASSWORD << " " << password;

                return command_args_stream.str();
            }
    };
}
```

> [!CAUTION]
> Although the process for **OMP** involves injecting the `omp-client.dll` *in addition* to the `samp.dll`, this is in line with how **OMP** typically works. The **OMP** client often uses the `samp.dll` as a **base** or **proxy** for certain functionalities, while `omp-client.dll` extends or overrides behaviors.
>
> It is crucial that **both DLLs** are present and functional in the game directory for the **OMP injection** to succeed. If one fails, the game may not initialize correctly, or the multiplayer client may not load.

### `injector.hpp`

This is the library's interface file. It is the only file the end user will need to include to use the **SA-MP Injector C++**. It acts as a wrapper for the `Injector::Injector_Core` class, simplifying the interface to a single global function, `Initialize_Game`.

```cpp
#pragma once

#include <string_view>
//
#include "injector_core.hpp" // The main class with the logic
#include "error_utils.hpp" // For error display (in case of invalid injection type)
#include "types.hpp" // Injection type enumeration
#include "constants.hpp" // Constants (for injection type names)

// The high-level interface for the library.
// Simplifies usage by exposing only this global function.
inline bool Initialize_Game(std::wstring_view inject_type_str, std::wstring_view folder, std::wstring_view nickname, std::wstring_view ip, std::wstring_view port, std::wstring_view password) {
    Types::Inject_Type type; // Variable to store the injection type

    // Converts the injection type string to the Inject_Type enum
    if (inject_type_str == Constants::INJECT_TYPE_SAMP)
        type = Types::Inject_Type::SAMP;
    
    else if (inject_type_str == Constants::INJECT_TYPE_OMP)
        type = Types::Inject_Type::OMP;
    
    else
        // If the injection type string is invalid, displays an error and returns false
        return (Error_Utils::Show_Error(L"Invalid injection mode specified. Please use 'samp' or 'omp'.", Types::Inject_Type::SAMP), false); // Uses SAMP as fallback for the title

    Injector::Injector_Core injector; // Instantiates the object containing the core logic
    
    // Delegates the call to the Initialize_Game function of the Injector_Core class
    return injector.Initialize_Game(type, folder, nickname, ip, port, password);
}
```

> [!NOTE]
> The use of the `inline` keyword for all functions in this file and other utilities allows the library to be `header-only`. `inline` suggests to the compiler that the function body should be inserted directly at the call sites, but its main effect here is to relax the **One Definition Rule (ODR)** so that the function can be defined in multiple `.obj` files (which would happen if multiple `.cpp` files include `injector.hpp`). The **linkage** step will ensure that only one final version exists in the executable.

## Comprehensive Usage Examples

To integrate the **SA-MP Injector C++** into your project, follow the instructions and review the scenarios below.

### 1. Setting Up the Development Environment

- **C++ Compiler**: A compiler that **supports C++17** is recommended. **Visual Studio** with `vcpkg` (for `std::filesystem`) or **GCC/Clang (version 17+)** are options.
- **Project Configuration**:
  - Create a new **C++** project (e.g., a console project).
  - Copy **all** `.hpp` files from the **SA-MP Injector C++** to a folder accessible to your project (e.g., in the **headers** folder).
  - Ensure the **C++ standard** is set to **C++17**. It is essential to maintain this version for maximum compatibility with **SA-MP** and **OMP** libraries. In **Visual Studio**: `Project Properties > Configuration Properties > C/C++ > Language > C++ Language Standard -> "ISO C++17 Standard (/std:c++17)"`
- **Permissions**: Your executable will likely need to be run as **Administrator (not necessarily)** to create processes and **inject DLLs** in the system environment. In **Visual Studio**, this can be done in: `Project Properties > Configuration Properties > Linker > Manifest File > UAC Execution Level -> "requireAdministrator (/LEVEL='requireAdministrator')"`

### 2. Basic Scenario: Connecting to an SA-MP Server

This is the most common use case, starting **GTA:SA** and connecting to an **SA-MP** server with a specific **nickname** and **IP**/**port**.

```cpp
// main.cpp
#include <iostream>
#include <string>
#include <codecvt> // For std::wstring_convert (legacy, but functional for this case)
#include <locale> // For std::codecvt_utf8_to_utf16
//
#include "injector.hpp" // The only inclusion needed from the library!

int Main(int argc, char* argv[]) {
    // Define the configuration variables
    // Change these paths and server details to match your local setup
    std::wstring folder = L"C:\\Games\\GTA San Andreas"; // Where gta_sa.exe, samp.dll are located
    std::wstring nickname = L"Name";
    std::wstring ip = L"127.0.0.1"; // Example: your local server
    std::wstring port = L"7777";
    std::wstring password = L""; // Leave empty if no password

    // Optional: Allow the user to provide settings via command line (simplified)
    // For more robust argument parsing, use an argument parsing library.
    if (argc > 1) {
        // Example: if the first arg is a path
        if (argc > 1)
            folder = std::wstring_convert<std::codecvt_utf8_to_utf16>().from_bytes(argv[1]);
        
        if (argc > 2)
            nickname = std::wstring_convert<std::codecvt_utf8_to_utf16>().from_bytes(argv[2]);

        if (argc > 3)
            ip = std::wstring_convert<std::codecvt_utf8_to_utf16>().from_bytes(argv[3]);

        if (argc > 4)
            port = std::wstring_convert<std::codecvt_utf8_to_utf16>().from_bytes(argv[4]);
        
        if (argc > 5)
            password = std::wstring_convert<std::codecvt_utf8_to_utf16>().from_bytes(argv[5]);
    }

    std::wcout << L"Starting SA-MP..." << std::endl;
    std::wcout << L"Game folder: " << folder << std::endl;
    std::wcout << L"Nickname: " << nickname << std::endl;
    std::wcout << L"Server: " << ip << L":" << port << std::endl;

    // Call to the library function to start the game
    if (Initialize_Game(L"samp", // Injection type: SA-MP
        folder, // Game folder path
        nickname, // Desired nickname
        ip, // Server IP
        port, // Server port (string)
        password)) { // Server password (string, can be empty)
        std::wcout << L"\n--- SA-MP started successfully! ---" << std::endl;
        std::wcout << L"The game was started in a separate process." << std::endl;
    }
    else {
        std::wcout << L"\n--- FAILED to start SA-MP! ---" << std::endl;
        std::wcout << L"Check the displayed error messages." << std::endl;
    }

    // Keeps the console open to view output messages
    std::wcout << L"\nPress Enter to close the program." << std::endl;
    std::wcin.ignore();

    return 0;
}
```

**To compile and run:**

```bash
# Example with g++ (Linux/MinGW/MSYS2) - Requires libstdc++fs for filesystem
# It is important to ensure that the toolchain does not use a C++ version
# that introduces incompatibilities in the injection process.
# Check your compiler's specific documentation for binary compatibility (ABI) flags.
g++ main.cpp -o my_launcher -std=c++17 -Wall -lstdc++fs -municode -lkernel32

# Example with MSVC (Visual Studio Developer Command Prompt)
# The '/std:c++17' flag ensures compliance with C++17.
cl /EHsc /std:c++17 /permissive- /FS /utf-8 main.cpp /link /OUT:my_launcher.exe
```

> [!NOTE]
> **SA-MP** and **OMP**, as legacy projects, are compiled with specific tools that define their **Application Binary Interface (ABI)**. Although this library uses **C++17**, **it is crucial that the SA-MP and OMP DLLs it interacts with are also compatible with your compiler's ABI and the C++ runtime version (CRT) you use**.
>
> Using a compiler or **C++** version significantly different from what was used to **build the game DLLs** can lead to subtle issues (e.g., with memory allocation or parameter passing) that are not easily **diagnosable** and will not result in an explicit injector error. For this reason, **C++17 is the maximum recommended version**, as newer versions may introduce changes in the **ABI** or **CRT** that are not tolerated by older game modules.

### 3. Advanced Scenario: Connecting to an OMP Server

For **OMP**, the logic is identical to **SA-MP**, but you specify `L"omp"` as the `inject_type` and ensure that the `omp-client.dll` is present in the game directory.

```cpp
// main.cpp
#include <iostream>
#include <string>
#include <codecvt> // For std::wstring_convert (legacy, but functional for this case)
#include <locale> // For std::codecvt_utf8_to_utf16
//
#include "injector.hpp" // The only inclusion needed from the library!

int Main() {
    // Define the configuration variables
    // Change these paths and server details to match your local setup
    std::wstring folder = L"C:\\Games\\GTA San Andreas"; // Where gta_sa.exe, samp.dll, and omp-client.dll are located
    std::wstring nickname = L"Name";
    std::wstring ip = L"127.0.0.1"; // Example: your local server
    std::wstring port = L"7777";
    std::wstring password = L""; // Leave empty if no password

    // Optional: Allow the user to provide settings via command line (simplified)
    // For more robust argument parsing, use an argument parsing library.
    if (argc > 1) {
        // Example: if the first arg is a path
        if (argc > 1)
            folder = std::wstring_convert<std::codecvt_utf8_to_utf16>().from_bytes(argv[1]);
        
        if (argc > 2)
            nickname = std::wstring_convert<std::codecvt_utf8_to_utf16>().from_bytes(argv[2]);

        if (argc > 3)
            ip = std::wstring_convert<std::codecvt_utf8_to_utf16>().from_bytes(argv[3]);

        if (argc > 4)
            port = std::wstring_convert<std::codecvt_utf8_to_utf16>().from_bytes(argv[4]);
        
        if (argc > 5)
            password = std::wstring_convert<std::codecvt_utf8_to_utf16>().from_bytes(argv[5]);
    }

    std::wcout << L"Starting OMP..." << std::endl;
    std::wcout << L"Game folder: " << folder << std::endl;
    std::wcout << L"Nickname: " << nickname << std::endl;
    std::wcout << L"Server: " << ip << L":" << port << std::endl;

    // Call to the library function to start the game
    if (Initialize_Game(L"omp", // Injection type: OMP
        folder, // Game folder path
        nickname, // Desired nickname
        ip, // Server IP
        port, // Server port (string)
        password)) { // Server password (string, can be empty)
        std::wcout << L"\n--- OMP started successfully! ---" << std::endl;
        std::wcout << L"The game was started in a separate process." << std::endl;
    }
    else {
        std::wcout << L"\n--- FAILED to start OMP! ---" << std::endl;
        std::wcout << L"Check the displayed error messages." << std::endl;
    }

    // Keeps the console open to view output messages
    std::wcout << L"\nPress Enter to close the program." << std::endl;
    std::wcin.ignore();

    return 0;
}
```

## Handling Common Errors and Messages

The **SA-MP Injector C++** prioritizes usability, and a fundamental part of this is providing clear **feedback** to the user in case of failure. Error messages are presented through **Windows dialog boxes** (`MessageBoxW`) and are categorized by the **injection type (SA-MP or OMP)** for greater context. This ensures that you know exactly what went wrong and how to address the resolution.

Here are some of the common errors you may encounter and their likely causes/solutions, accompanied by visual examples of how these dialog boxes appear to the end user:

### 1. Invalid Injection Type

If the `inject_type` provided in the `Initialize_Game` function is not `L"samp"` or `L"omp"`, the library will not know which multiplayer client you intend to initialize.

![Error 1](screenshots/error_1.png)

- **Displayed Error Message**: `"Invalid injection mode specified. Please use 'samp' or 'omp'."`
- **Cause**: The first argument of the `Initialize_Game` function (`std::wstring_view inject_type`) does not match the expected values of `L"samp"` or `L"omp"`. It could be a typo, an empty string, or an unrecognized value.
- **Solution**: Ensure that the `std::wstring_view inject_type_str` is correctly set to `L"samp"` or `L"omp"`. It is essential to use the `L` prefix for **wide-character** literals to match the library's constants.
    ```cpp
    // Correct:
    Initialize_Game(L"samp", /* other parameters */);
    Initialize_Game(L"omp", /* other parameters */);

    // Incorrect (will cause error):
    // Initialize_Game(L"invalid", /* other parameters */);
    // Initialize_Game(L"", /* other parameters */);
    ```

### 2. Invalid Server Port (Format or Range)

The port is a critical numeric parameter for connecting to the server. This error occurs if the value cannot be interpreted as a valid number or is outside the acceptable range **(1 to 65535)**.

#### 2.1. Non-Numeric Port Format

![Error 2](screenshots/error_2.png)

- **Displayed Error Message**: `"Invalid port format. The port must be a numeric value. Please provide a valid integer for the port."`
- **Cause**: The `port` argument (`std::wstring_view`) contains characters that are not numeric digits or cannot be converted to an integer.
- **Solution**: Provide a string that contains only digits and represents a valid integer.
    ```cpp
    // Correct:
    Initialize_Game(/* other parameters */, L"7777", /* other parameters */);

    // Incorrect (invalid format):
    // Initialize_Game(/* other parameters */, L"port7777", /* other parameters */);

    // Incorrect (invalid):
    // Initialize_Game(/* other parameters */, L"invalid", /* other parameters */);
    ```

#### 2.2. Port Out of Valid Range

![Error 3](screenshots/error_3.png)

- **Displayed Error Message**: `"The specified port number (XXXX) is outside the valid range of 1 to 65535. Please provide a valid port."` (The **XXXX** will be the value you attempted to use).
- **Cause**: The provided port is a valid number but is below `1` (reserved or unusable) or above `65535` (the maximum limit for **TCP/UDP ports**).
- **Solution**: Provide a port within the range of `1` to `65535`. Common ports for **SA-MP**/**OMP** are `7777` or `7778`.
    ```cpp
    // Correct:
    Initialize_Game(/* other parameters */, L"7777", /* other parameters */);

    // Incorrect (out of range):
    // Initialize_Game(/* other parameters */, L"0", /* other parameters */); // Too low
    // Initialize_Game(/* other parameters */, L"65536", /* other parameters */); // Too high
    // Initialize_Game(/* other parameters */, L"-1", /* other parameters */); // Negative value
    ```

### 3. Invalid Nickname (Empty or Too Long)

The player's **nickname** is validated to ensure the game client accepts it.

#### 3.1. Empty Nickname

![Error 4](screenshots/error_4.png)

- **Displayed Error Message**: `"Nickname cannot be empty. Please provide a valid nickname."`
- **Cause**: The `nickname` argument (`std::wstring_view`) was provided as an empty string.
- **Solution**: Ensure the nickname is not empty.
    ```cpp
    // Correct:
    Initialize_Game(/* other parameters */, L"Name", /* other parameters */);

    // Incorrect (empty):
    // Initialize_Game(/* other parameters */, L"", /* other parameters */);
    ```

#### 3.2. Nickname Too Long

![Error 5](screenshots/error_5.png)

- **Displayed Error Message**: `"Nickname length exceeds the maximum allowed of 23 characters. Please use a shorter nickname."`
- **Cause**: The length of the provided **nickname** exceeds `Constants::MAX_NICKNAME_LENGTH`, which is `23` characters.
- **Solution**: Use a **nickname** that is at most `23` characters long.
    ```cpp
    // Correct:
    Initialize_Game(/* other parameters */, L"Name", /* other parameters */);

    // Incorrect (too long):
    // Initialize_Game(/* other parameters */, L"ThisNicknameIsTooLongAndExceedsTwentyCharacters", /* other parameters */);
    ```

### 4. Game or DLL Files Not Found

This is one of the most common causes of failure. The library requires `gta_sa.exe`, `samp.dll`, and, for **OMP**, `omp-client.dll` to be present in the expected locations.

#### 4.1. Game Executable (`gta_sa.exe`) Not Found

![Error 6](screenshots/error_6.png)

- **Displayed Error Message**: `"Game executable not found. Please ensure 'gta_sa.exe' exists at the specified path: [full path]"`. The `[full path]` will include the folder and file name.
- **Cause**: The `gta_sa.exe` file was not found in the folder provided in the `folder` argument.
- **Solution**:
  1. Verify that the `folder` (`std::wstring_view`) points to the correct **GTA San Andreas** installation directory.
  2. Confirm that `gta_sa.exe` exists in that folder and that its name has not been altered.

#### 4.2. SA-MP Library (`samp.dll`) Not Found

![Error 7](screenshots/error_7.png)

- **Displayed Error Message**: `"SA-MP library not found. Please ensure 'samp.dll' exists at the specified path: [full path]"`.
- **Cause**: The `samp.dll` file was not found in the folder provided in the `folder` argument. **This DLL** is a requirement for **both** injection types (`samp` and `omp`).
- **Solution**: Ensure that `samp.dll` is present in the **GTA San Andreas** installation folder.

#### 4.3. OMP Library (`omp-client.dll`) Not Found (only for OMP injection)

![Error 8](screenshots/error_8.png)

- **Displayed Error Message**: `"OMP library not found. Please ensure 'omp-client.dll' exists at the specified path for OMP injection: [full path]"`.
- **Cause**: If you specified `L"omp"` as the injection type, but the `omp-client.dll` file was not found in the provided folder.
- **Solution**: Download the latest **OMP** client and ensure that `omp-client.dll` (and `samp.dll`) are present in the **GTA San Andreas** installation folder.

### 5. Failure to Create Game Process

This is a more complex error, as it involves **operating system permissions** and the current state of `gta_sa.exe`.

![Error 9](screenshots/error_9.png)

- **Displayed Error Message**: `"Failed to create game process. Ensure 'gta_sa.exe' is not running and you have sufficient permissions to execute the file. System Error: [Operating system error message]"`. The system message will be appended by `GetLastError()` (e.g., `Access is denied.` or `The requested operation requires elevation.`).
- **Cause**: The `CreateProcessA` call to start `gta_sa.exe` failed. Common causes include:
  - **Process already running**: An instance of `gta_sa.exe` is already active and blocking a new execution.
  - **Insufficient permissions**: Your application does not have the necessary privileges (e.g., administrator) to create a process in certain system configurations (**UAC** enabled, protected folders, etc.).
  - **Issues with the executable**: The `gta_sa.exe` may be corrupted or blocked by another program (e.g., a misconfigured antivirus).
- **Solution**:
  1. Check the Task Manager and ensure no instance of `gta_sa.exe` is running. Terminate any if present.
  2. Run your application that uses the library with **Administrator** privileges. Right-click the executable and select **"Run as administrator"**.
  3. If an **antivirus** or security software is interfering, add your application and/or the **GTA:SA** folder to the antivirus exceptions (do this cautiously and only if you are sure of the integrity of your files).

### 6. Failure to Allocate Memory in the Target Process

The library attempts to allocate a small memory space in `gta_sa.exe` to copy the **DLL path**.

![Error 10](screenshots/error_10.png)

- **Displayed Error Message**: `"Failed to allocate memory in the target process. This might be due to insufficient permissions or process protection mechanisms."`
- **Cause**: The `VirtualAllocEx` function (used to allocate memory within another process) failed. This is more likely if:
  - The **GTA:SA** process (even in a suspended state) has security defenses or **anti-injection patches** that prevent memory allocation by external processes.
  - Your application does not have the necessary elevated permissions to manipulate another process's memory.
  - (Less common) There is an extreme shortage of virtual memory in the system.
- **Solution**:
  1. Run your application with **Administrator** privileges.
  2. Ensure the game does not have any modifications or **security patches** that might block injection or memory manipulation attempts (this is more common in modified environments or with certain third-party anti-cheat tools).

### 7. Failure to Write DLL Path to Process Memory

After allocating memory, the library attempts to copy the **DLL path** to it.

![Error 11](screenshots/error_11.png)

- **Displayed Error Message**: `"Failed to write DLL path to the target process memory. Verify process permissions and ensure the DLL path is accessible."`
- **Cause**: The `WriteProcessMemory` function failed to copy the **DLL path bytes** to the remotely allocated memory in `gta_sa.exe`. This usually points to:
  - **Write permissions**: Your application does not have permission to write to that memory region or the **GTA:SA** process.
  - **Invalid handle**: The process **handle** (`process_handle`) somehow became invalid between allocation and writing, which is very rare due to the use of `UniqueResource` but can occur under extreme system conditions.
  - **Memory Protection Issues**: Some memory protection (either from the **OS** or game modifications) prevented the write.
- **Solution**: Run as **Administrator**. Verify that `gta_sa.exe` and its environment are "clean" of tools that could block memory operations.

### 8. Failure to Find Essential System Functions

These are critical **Windows APIs**; errors here indicate a fundamental issue with the operating system or execution environment.

#### 8.1. `kernel32.dll` Not Found

![Error 12](screenshots/error_12.png)

- **Displayed Error Message**: `"Failed to obtain a handle to kernel32.dll. This is an essential system library and this error indicates a severe system issue."`
- **Cause**: The `kernel32.dll` is one of the most basic **DLLs** in **Windows**, containing essential functions like `CreateProcess`, `VirtualAllocEx`, etc. If `GetModuleHandleA` cannot obtain a **handle** for it, the operating system has very serious issues.
- **Solution**: This is a **critical** error that is rarely caused by the library or your application. It suggests system file corruption, severe **Windows** issues, or a highly unusual **OS** installation. It is recommended to run system integrity checks (such as `sfc /scannow` in the **Command Prompt** as **Administrator**) or, as a last resort, reinstall **Windows**.

#### 8.2. `LoadLibraryA` Not Found

![Error 13](screenshots/error_13.png)

- **Displayed Error Message**: `"Failed to find the address of the LoadLibraryA function in kernel32.dll. This is critical for injecting the DLL."`
- **Cause**: Although `kernel32.dll` was found, the `LoadLibraryA` function could not be resolved via `GetProcAddress`. While extremely uncommon, this could result from corruption of the `kernel32.dll` **file** or a highly non-standard execution environment.
- **Solution**: As with the `kernel32.dll` error above, this indicates a serious operating system issue.

### 9. Failure to Create Remote Thread for Injection

After preparing the remote environment and copying the **DLL path**, a new **thread** is created in the game process to "call" `LoadLibraryA`.

![Error 14](screenshots/error_14.png)

- **Displayed Error Message**: `"Failed to create a remote thread in the target process to execute the DLL injection. This could be due to security restrictions or process state. System Error: [Operating system error message]"`.
- **Cause**: The `CreateRemoteThread` call failed. This error is common in systems with robust **anti-injection** defenses or when a program is heavily monitoring the process's behavior:
  - **Security Mechanisms**: **Anti-cheat** tools, security **software**, or certain **Windows** policies may detect and block attempts to create **threads** in third-party processes.
  - **Inconsistent Target Process**: If the **GTA:SA** process is in an unexpected or unstable state (although started in `CREATE_SUSPENDED`), this may affect the ability to create **threads** in it.
- **Solution**:
  1. Run your application with **Administrator** privileges.
  2. Check for **anti-cheat** tools, aggressive **antivirus**, or **firewalls** configured to inspect and block process manipulation that may be conflicting. Add your application and the `gta_sa.exe` to exceptions, if applicable (with caution).
  3. The system error message (`GetLastError()`) may provide additional details to investigate the specific cause (e.g., **"A process has been denied access to create threads for other processes."**).

### 10. Timeout or Failure in Injection Completion

After creating the remote **thread**, the injector waits for it to complete the **DLL load**.

![Error 15](screenshots/error_15.png)

- **Displayed Error Message**: `"Timeout or error waiting for DLL injection to complete. System Error: [Operating system error message]"`.
- **Cause**: The remote **thread** executing `LoadLibraryA` took longer than `Constants::DLL_INJECTION_TIMEOUT_MS` (10 seconds) to return, or it failed, and `GetExitCodeThread` returned 0. Potential causes include:
  - **Issues in the Injected DLL**: The `DllMain` of `samp.dll` or `omp-client.dll` is taking too long to execute, contains an **infinite loop**, a **crash**, or an error that **prevents the DLL** from loading correctly (e.g., missing **DLL dependencies**).
  - **Silent Blocking**: A security mechanism may have blocked `LoadLibraryA` but did not notify with an obvious thread creation error.
- **Solution**:
  1. Verify the integrity of the `samp.dll` and `omp-client.dll` files. They may be corrupted or from a version incompatible with your `gta_sa.exe`.
  2. Ensure **that the injected DLL** does not depend on **other DLLs** that may be missing or inaccessible in the system.

### 11. Failure to Resume Game Process Thread

This is the final step to start the game after **the DLLs** are injected.

![Error 16](screenshots/error_16.png)

- **Displayed Error Message**: `"Failed to resume the game process thread: [Operating system error message]"`.
- **Cause**: The `ResumeThread` call failed, meaning the main **thread** of `gta_sa.exe` could not be activated to start the game's execution. This is a rare error but can occur if:
  - The **thread handle** of the process became invalid.
  - The operating system prevented resumption for some reason, possibly related to a security interruption or inconsistent process state.
  - The process may have been terminated externally between **DLL injection** and the attempt to resume the main **thread**.
- **Solution**: If all previous steps were successful and only `ResumeThread` failed, it may be an issue with the operating system, the **GTA:SA** installation itself, or overly strict security **software**. Re-examine the state of `gta_sa.exe` via **Task Manager** just before and after the error. Restarting the computer may resolve temporary system state issues.

> [!TIP]
> In complex debugging scenarios, tools like **Process Monitor (Sysinternals Suite)** or a debugger (such as **Visual Studio Debugger**, **WinDbg**, **OllyDbg**) can be invaluable. They can help observe **API** calls, check access errors, track **handle** states, and even inspect process memory, providing deep insight into what is happening under the hood.

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