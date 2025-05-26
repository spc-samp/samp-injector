# SA-MP Injector

[![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](https://opensource.org/licenses/MIT)
[![SA-MP | OMP](https://img.shields.io/badge/Support-SA--MP%20%7C%20OMP-yellow)](https://github.com/spc-samp/samp-injector)
[![x86 Only](https://img.shields.io/badge/Architecture-x86%20(32--bit)-orange)](https://github.com/spc-samp/samp-injector)

SA-MP Injector is a versatile tool designed for **SA-MP (San Andreas Multiplayer)** and **OMP (Open Multiplayer)**, functioning both as a **command-line executable** and as a **library for different languages**. Its main function is to inject `samp.dll` (for **SA-MP**) or both `samp.dll` and `omp-client.dll` (for **OMP**) into the **GTA:SA** process, allowing the game to be started with custom parameters for direct connection to a server.

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
    - For **OMP** mode, both `samp.dll` and `omp-client.dll` are injected.
    Injection is facilitated by remotely invoking the `LoadLibraryA` function, allowing GTA:SA to load the multiplayer modules and initialize the connection.
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

## Libraries

The libraries are the core components of the `SA-MP Injector`, containing the central logic for process manipulation, **DLL injection**, and parameter validation. The main advantage of using these libraries is the ease of initialization and injection, typically through a single function (or calls with specific parameters for scripting languages).

### Overview

The project is built on libraries that encapsulate the critical functionalities. This allows other projects to easily integrate the ability to launch **GTA:SA** with the necessary **multiplayer** modules.

### List of Libraries

| Language      | Name                       | Link to Library/Documentation |
| ------------- | -------------------------- | ----------------------------- |
| C++           | **SA-MP Injector C++**     | [View Library](libraries/cpp) |
| C             | **SA-MP Injector C**       | (Coming soon)                 |
| C#            | **SA-MP Injector C#**      | (Coming soon)                 |
| Java          | **SA-MP Injector Java**    | (Coming soon)                 |
| Python        | **SA-MP Injector Python**  | (Coming soon)                 |
| Go (Golang)   | **SA-MP Injector Go**      | (Coming soon)                 |
| Rust          | **SA-MP Injector Rust**    | (Coming soon)                 |
| Kotlin        | **SA-MP Injector Kotlin**  | (Coming soon)                 |
| Scala         | **SA-MP Injector Scala**   | (Coming soon)                 |
| Lua           | **SA-MP Injector Lua**     | (Coming soon)                 |
| Ruby          | **SA-MP Injector Ruby**    | (Coming soon)                 |
| Visual Basic  | **SA-MP Injector VB**      | (Coming soon)                 |
| F#            | **SA-MP Injector F#**      | (Coming soon)                 |
| Pascal/Delphi | **SA-MP Injector P/D**     | (Coming soon)                 |
| PowerShell    | **SA-MP Injector PS**      | (Coming soon)                 |
| D (Dlang)     | **SA-MP Injector D**       | (Coming soon)                 |
| Nim           | **SA-MP Injector Nim**     | (Coming soon)                 |
| Zig           | **SA-MP Injector Zig**     | (Coming soon)                 |
| V (VLang)     | **SA-MP Injector V**       | (Coming soon)                 |
| Crystal       | **SA-MP Injector Crystal** | (Coming soon)                 |
| Perl          | **SA-MP Injector Perl**    | (Coming soon)                 |
| Racket (Lisp) | **SA-MP Injector Racket**  | (Coming soon)                 |
| Haskell       | **SA-MP Injector Haskell** | (Coming soon)                 |
| OCaml         | **SA-MP Injector OCaml**   | (Coming soon)                 |

> [!TIP]
> Detailed documentation for each library will be available in its **respective directory**.

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