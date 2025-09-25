# SA-MP Injector

[![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](https://opensource.org/licenses/MIT)
[![SA-MP | OMP](https://img.shields.io/badge/Support-SA--MP%20%7C%20OMP-yellow)](https://github.com/spc-samp/samp-injector)
[![x86 Only](https://img.shields.io/badge/Architecture-x86%20(32--bit)-orange)](https://github.com/spc-samp/samp-injector)

**SA-MP Injector** is a versatile tool designed for **SA-MP (San Andreas Multiplayer)** and **OMP (Open Multiplayer)**, functioning as a **command-line executable**, a **dynamic library (DLL)**, and a **set of libraries for different programming languages**. Its main function is to inject the `samp.dll` (in the case of **SA-MP**) or both `samp.dll` and `omp-client.dll` (in the case of **OMP**) into the **GTA:SA** process, allowing the game to be launched with customized parameters, enabling direct connection to a server.

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

- [SA-MP Injector](#sa-mp-injector)
  - [Languages](#languages)
  - [Table of Contents](#table-of-contents)
  - [Executable](#executable)
    - [Functionality](#functionality)
    - [How to Use (Command Line)](#how-to-use-command-line)
      - [SA-MP Mode](#sa-mp-mode)
      - [OMP Mode](#omp-mode)
      - [Parameters](#parameters)
    - [How to Use (Embedded in Applications)](#how-to-use-embedded-in-applications)
    - [Using the C++ Library in the Executable](#using-the-c-library-in-the-executable)
    - [How to Compile](#how-to-compile)
      - [Requirements](#requirements)
      - [Compilation Steps](#compilation-steps)
  - [Dynamic Library (**DLL**)](#dynamic-library-dll)
    - [Functionality](#functionality-1)
    - [How to Use (API Call)](#how-to-use-api-call)
      - [`Launch_Game` Function Contract](#launch_game-function-contract)
      - [Parameters](#parameters-1)
    - [How to Use (Embedded in Applications)](#how-to-use-embedded-in-applications-1)
    - [Using the C++ Library in the **DLL**](#using-the-c-library-in-the-dll)
    - [How to Compile](#how-to-compile-1)
      - [Requirements](#requirements-1)
      - [Compilation Steps](#compilation-steps-1)
  - [Libraries](#libraries)
    - [Overview](#overview)
    - [List of Libraries](#list-of-libraries)
  - [License](#license)
    - [Terms and Conditions of Use](#terms-and-conditions-of-use)
      - [1. Granted Permissions](#1-granted-permissions)
      - [2. Mandatory Conditions](#2-mandatory-conditions)
      - [3. Copyright](#3-copyright)
      - [4. Disclaimer of Warranty and Limitation of Liability](#4-disclaimer-of-warranty-and-limitation-of-liability)

## Executable

The `samp-injector.exe` executable provides a command-line interface to launch **GTA:SA** with **SA-MP** or **OMP**, automatically configuring the connection to a server. It encapsulates the logic of **DLL injection** and the passing of game parameters.

### Functionality

The `samp-injector.exe` operates as an automated game launcher, abstracting the complexities of configuration and **DLL injection**:

1. **Environment Validation:** Checks for the existence of essential files (`gta_sa.exe`, `samp.dll`, `omp-client.dll`) in the specified directory, as well as validating the provided connection parameters.
2. **Creation of a Suspended Process:** Launches `gta_sa.exe` in a suspended state, a prerequisite for safely **injecting DLLs** before the game's main process is executed.
3. **Dynamic DLL Injection:**
   - For **SA-MP** mode, `samp.dll` is injected.
   - For **OMP** mode, both `samp.dll` and `omp-client.dll` are injected. Injection is facilitated by remotely invoking the `LoadLibraryA` function, allowing GTA:SA to load the multiplayer modules and initialize the connection.
4. **Argument Configuration:** Command-line arguments such as **nickname**, **server IP**, **port**, and **password (if provided)** are prepared and passed to `gta_sa.exe`.
5. **Process Resumption:** After successful **DLL injection**, the game process is resumed for normal execution, leading **GTA:SA** to connect directly to the server.

### How to Use (Command Line)

To use the executable, invoke it from the **Command Prompt (CMD)**, **PowerShell**, or **terminal**, providing the necessary parameters.

The basic format is:
```bash
samp-injector.exe <mode> <game_directory> <nickname> <server_ip> <server_port> <server_password (optional)>
```

#### SA-MP Mode

For exclusive injection of `samp.dll`:
```bash
samp-injector.exe "samp" "C:\Games\GTA San Andreas" "Name" "127.0.0.1" "7777" "password (optional)"
```

#### OMP Mode

For injection of `samp.dll` and `omp-client.dll`:
```bash
samp-injector.exe "omp" "C:\Games\GTA San Andreas" "Name" "127.0.0.1" "7777" "password (optional)"
```

#### Parameters

- `<mode>`: Defines the type of injection.
   - `samp`: For **SA-MP** (`samp.dll`).
   - `omp`: For **OMP** (`samp.dll` and `omp-client.dll`).
- `<game_directory>`: The full path to the **GTA:SA** directory. This directory must contain `gta_sa.exe` and the respective **DLL** files.
- `<nickname>`: Your in-game nickname (maximum of **20 characters**).
- `<server_ip>`: The **IP address** or **domain name** of the server.
- `<server_port>`: The server's connection port (a **numeric value** between **1** and **65535**).
- `<server_password>`: The password required to connect to the server **(if the server does not require a password, this parameter is not needed)**.

If the arguments are incorrect or insufficient, a usage message will be displayed.

### How to Use (Embedded in Applications)

The `samp-injector.exe` is ideal for integration into third-party applications, such as custom launchers, that aim to automate the process of launching the game with predefined settings.

Example of invoking `samp-injector.exe` from a **C# application**:
```csharp
using System;
using System.Diagnostics;
using System.Windows.Forms;

public class Launcher {
    public static void Main(string[] args) {
        string inject_mode = "omp"; 
        string folder = "C:\\Games\\GTA San Andreas";
        string nickname = "Name";
        string ip = "127.0.0.1";
        string port = "7777";
        string password = "password (optional)";

        try {
            string arguments = $"{inject_mode} \"{folder}\" \"{nickname}\" \"{ip}\" {port}";

            if (!string.IsNullOrEmpty(password))
                arguments += $" \"{password}\"";

            ProcessStartInfo start_info = new ProcessStartInfo {
                FileName = "samp-injector.exe", 
                Arguments = arguments,
                UseShellExecute = false,
                CreateNoWindow = true 
            };

            using (Process process = Process.Start(start_info)) {
                process.WaitForExit(); 

                if (process.ExitCode != 0)
                    MessageBox.Show($"The SA-MP Injector returned an error (Code: {process.ExitCode}). The game may not have started correctly.", "Launch Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }
        catch (Exception ex) {
            MessageBox.Show($"An error occurred while launching the game: {ex.Message}", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
        }
    }
}
```

### Using the C++ Library in the Executable

The `samp-injector.exe` executable is built on top of the [SA-MP Injector C++](https://github.com/spc-samp/samp-injector/tree/main/libraries/cpp) library, located in the `libraries/cpp/` directory. The `main.cpp` file of the executable invokes the functionalities of this library to perform the injection and game launch.

The main header file of the **C++** library to be included is `libraries/samp-injector/cpp/injector.hpp`. As the [SA-MP Injector C++](https://github.com/spc-samp/samp-injector/tree/main/libraries/cpp) library is **header-only**, its usage requires only including this header in the source code, without the need to link a `.lib` file.

The relevant section of `main.cpp` demonstrating the integration is as follows:
```cpp
// Extracts command-line arguments
int argc;
std::unique_ptr<LPWSTR[], decltype(&LocalFree)> argv(CommandLineToArgvW(GetCommandLineW(), &argc), &LocalFree);

// ... (validation of the number of arguments and injection mode) ...

// Extracts parameters into wide string variables
std::wstring folder = argv[2];
std::wstring nickname = argv[3];
std::wstring ip = argv[4];
std::wstring port = argv[5];
std::wstring password = (argc == 7) ? argv[6] : L"";

// Delegates the injection logic to the "Initialize_Game" function of the library
// Note that "injector.hpp" was previously included in "main.cpp"
if (!Initialize_Game(inject_type, folder, nickname, ip, port, password))
    return 1;

Sleep(10000); // Waits before terminating the executable
```

The `Initialize_Game` function acts as the high-level interface of the library, orchestrating all operations for validation, process creation, and **DLL injection**.

### How to Compile

You can compile the `samp-injector.exe` from the source code. If you do not wish to compile, you can download precompiled versions from the [Releases](https://github.com/spc-samp/samp-injector/releases) section.

#### Requirements

- **Visual Studio:** **Visual Studio 2022** or higher with the **"Desktop development with C++" workload** installed is recommended.
- **Git:** To clone the repository (or simply download it using this link: [Download](https://github.com/spc-samp/samp-injector/archive/refs/heads/main.zip)).

#### Compilation Steps

1. **Clone the Repository:**
   ```bash
   git clone https://github.com/spc-samp/samp-injector.git
   cd samp-injector
   ```
2. **Open the Solution:**
   Navigate to the `executable` folder and open the `.sln` solution file:
   ```bash
   cd executable
   start samp-injector.sln
   ```
   This will open the project in **Visual Studio**.
3. **Configure Build:**
   - In **Visual Studio**, verify the solution configuration. It is recommended to use the `Release` and `x86` **(32-bit)** modes. In the context of **GTA:SA** and **SA-MP**/**OMP**, the **x86 (32-bit)** architecture is mandatory.
4. **Compile:**
   - In the `Build` menu, click `Build Solution` or `Build samp-injector`.
   - Alternatively, you can use the shortcuts:
      - `Ctrl + Shift + B` to compile the entire solution.
      - `Ctrl + B` (if configured) to compile the current project.
   - If everything is configured correctly, the `samp-injector.exe` executable will be generated in the `executable\Release` directory (or `executable\Debug`, depending on your **build** configuration).

## Dynamic Library (**DLL**)

The `samp-injector.dll` library provides an **API (Application Programming Interface)** to programmatically launch **GTA:SA** with **SA-MP** or **OMP**. It is the ideal alternative to the executable for developers of launchers who want a cleaner and more direct integration by calling a function instead of launching an external process.

### Functionality

The `samp-injector.dll` triggers the same robust workflow as the internal library, encapsulating the complexities of injection and game initialization:

1. **Creation of a Suspended Process:** When called, it launches `gta_sa.exe` in a suspended state.
2. **Dynamic DLL Injection:**
   - For **SA-MP** mode, `samp.dll` is injected.
   - For **OMP** mode, `samp.dll` and `omp-client.dll` are injected.
3. **Argument Configuration:** The function parameters, such as **nickname**, **IP**, **port**, and **password**, are prepared for `gta_sa.exe`.
4. **Process Resumption:** After injection, the game process is resumed for execution, connecting directly to the server.

### How to Use (API Call)

To use the library, you need to load the `samp-injector.dll` into your application and call the exported `Launch_Game` function.

#### `Launch_Game` Function Contract

- **DLL File:** `samp-injector.dll`
- **Exported Function Name:** `Launch_Game`
- **Calling Convention:** `__stdcall`
- **Return Type:** `int`
   - `0`: **Success.** The game launch request was sent to a background thread.
   - `1`: **Invalid Arguments.** A required parameter was null, or the mode was invalid. An error message will be displayed.
   - `2`: **Thread Failure.** A critical error occurred while attempting to create the initialization thread. An error message will be displayed.

#### Parameters

All parameters are wide-character (Unicode) strings.

- `mode` (`LPCWSTR`): Defines the injection type (`L"samp"` or `L"omp"`).
- `folder` (`LPCWSTR`): The full path to the **GTA:SA** directory.
- `nickname` (`LPCWSTR`): Your in-game nickname.
- `ip` (`LPCWSTR`): The **IP** address or **domain name** of the server.
- `port` (`LPCWSTR`): The server's connection port.
- `password` (`LPCWSTR`): The password to connect to the server. **(This parameter is optional. You can pass `null` or an empty string `L""` if there is no password)**.

### How to Use (Embedded in Applications)

Example of calling the `Launch_Game` function from a **C# application**:
```csharp
using System;
using System.Runtime.InteropServices;
using System.Windows.Forms;

public class Launcher {
    // Imports the function from the DLL, specifying the API contract.
    [DllImport("samp-injector.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.StdCall, EntryPoint = "Launch_Game")]
    private static extern int Launch_Game(string mode, string folder, string nickname, string ip, string port, string password);

    public static void Main(string[] args) {
        string inject_mode = "samp"; 
        string gta_folder = "C:\\Games\\GTA San Andreas"; // Note: Use the actual path!
        string nickname = "Name";
        string ip = "127.0.0.1";
        string port = "7777";
        string password = "password (optional)"; // or null, or "" if none

        try {
            int result = Launch_Game(inject_mode, gta_folder, nickname, ip, port, password);
            
            if (result != 0) {
                // The DLL already displays a detailed error message,
                // but you can log or display another message here.
                MessageBox.Show($"The DLL call returned an error code: {result}", "Launcher Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }
        catch (DllNotFoundException) {
            MessageBox.Show("Error: samp-injector.dll not found! Check if it is in the same folder as the launcher.", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
        }
        catch (Exception ex) {
            MessageBox.Show($"An unexpected error occurred: {ex.Message}", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
        }
    }
}
```

### Using the C++ Library in the **DLL**

Like the executable, the `samp-injector.dll` is also built on the [SA-MP Injector C++](https://github.com/spc-samp/samp-injector/tree/main/libraries/cpp) library, located in the `libraries/cpp/` directory. The exported `Launch_Game` function acts as a wrapper, validating parameters and delegating the main injection logic to the `Initialize_Game` function of the library.

The main header file of the **C++** library to include is `libraries/samp-injector/cpp/injector.hpp`. Since the [SA-MP Injector C++](https://github.com/spc-samp/samp-injector/tree/main/libraries/cpp) library is **header-only**, its use requires only including this header in the source code, without needing to link a `.lib` file.

The following code snippet from the `main.cpp` of the **DLL** demonstrates how the task is delegated to a separate thread:
```cpp
// Worker function that runs in a background thread
void Game_Thread_Worker(const std::wstring& mode, const std::wstring& folder, const std::wstring& nickname, const std::wstring& ip, const std::wstring& port, const std::wstring& password) {
    // The injection logic is delegated to the "Initialize_Game" function of the library.
    Initialize_Game(mode, folder, nickname, ip, port, password);
}

// Within the exported `Launch_Game` function, the thread is created:
try {
    std::thread(Game_Thread_Worker, mode_str, folder_str, nickname_str, ip_str, port_str, password_str).detach();
}
// ...
```

This shows that the **DLL** is essentially an API interface for the same core functionality used by the executable.

### How to Compile

You can compile the `samp-injector.dll` from the source code. If you do not wish to compile, you can download pre-compiled versions from the [Releases](https://github.com/spc-samp/samp-injector/releases) section.

#### Requirements

- **Visual Studio:** **Visual Studio 2022** or higher with the **"Desktop development with C++"** workload installed is recommended.
- **Git:** To clone the repository (or simply download it via this link: [Download](https://github.com/spc-samp/samp-injector/archive/refs/heads/main.zip)).

#### Compilation Steps

1. **Clone the Repository:**
   ```bash
   git clone https://github.com/spc-samp/samp-injector.git
   cd samp-injector
   ```
2. **Open the Solution:**
   Navigate to the `dll` folder and open the `.sln` solution file:
   ```bash
   cd dll
   start samp-injector.sln
   ```
   This will open the project in **Visual Studio**.
3. **Configure Build:**
   - In **Visual Studio**, check the solution configuration. It is recommended to use the `Release` and `x86` **(32-bit)** modes. In the context of **GTA:SA** and **SA-MP**/**OMP**, the **x86 (32-bit)** architecture is mandatory.
4. **Compile:**
   - In the `Compilation` menu, click on `Compile Solution` or `Build samp-injector`.
   - Alternatively, you can use the shortcuts:
      - `Ctrl + Shift + B` to compile the entire solution.
      - `Ctrl + B` (if configured) to compile the current project.
   - If everything is set up correctly, the `samp-injector.dll` library will be generated in the `dll\Release` directory (or `dll\Debug`, depending on your **build** configuration).

## Libraries

The libraries are the core components of the **SA-MP Injector**, containing the central logic for process manipulation, **DLL injection**, and parameter validation. The main advantage of using these libraries is the ease of initialization and injection, typically through a single function (or calls with specific parameters for scripting languages).

### Overview

The project is built on libraries that encapsulate the critical functionalities. This allows other projects to easily integrate the ability to launch **GTA:SA** with the necessary **multiplayer** modules.

### List of Libraries

| Language   | Name                   | Link to Library/Documentation              |
| ---------- | ---------------------- | ------------------------------------------ |
| C++        | **SA-MP Injector C++** | [View Library](../../libraries/cpp)        |
| C#         | **SA-MP Injector C#**  | [View Library](../../libraries/csharp)     |
| PowerShell | **SA-MP Injector PS**  | [View Library](../../libraries/powershell) |

> [!WARNING]
> The **PowerShell** library has been discontinued and will no longer receive updates or maintenance. This happened because **GitHub’s filters** consider the library to contain potentially **malicious** behavior, as it performs **low-level** operations. When this occurs, both the **author’s** account and the **SPC** profile may be **suspended** and **flagged**. However, **don’t worry**: the **PowerShell** library will remain available for use, it just **won’t receive new updates**.

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