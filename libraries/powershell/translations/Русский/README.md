# SA-MP Injector PowerShell

![License](https://img.shields.io/badge/License-MIT-yellow.svg?style=flat)
![PowerShell](https://img.shields.io/badge/PowerShell-5.1%2B-blue.svg?style=flat&logo=powershell)
![Platform](https://img.shields.io/badge/Platform-Windows-0078D6.svg?style=flat&logo=windows)
[![SA-MP | OMP](https://img.shields.io/badge/Support-SA--MP%20%7C%20OMP-yellow)](https://github.com/spc-samp/samp-injector)
![Code Quality](https://img.shields.io/badge/Code%20Quality-High-brightgreen.svg?style=flat)

**SA-MP Injector PowerShell** — это больше, чем просто скрипт для **внедрения DLL**. Он представляет собой **библиотеку функций и классов PowerShell**, разработанную для предоставления надежного и полного решения для программного запуска игры **Grand Theft Auto: San Andreas** (**GTA:SA**) вместе с ее многопользовательскими клиентами, в частности **SA-MP (San Andreas Multiplayer)** и **OMP (Open Multiplayer)**. Его основная цель — упростить процесс запуска игры, устраняя сложность, присущую прямому манипулированию процессами операционной системы и передаче аргументов командной строки.

Разработанная для обеспечения максимальной гибкости и легкой интеграции, эта библиотека позволяет разработчикам встраивать ее непосредственно в свои **проекты и скрипты PowerShell**. Она не только организует **фундаментальное внедрение DLL** многопользовательского клиента (`samp.dll` или `omp-client.dll`), но и интеллектуально управляет всеми основными параметрами подключения (**никнейм**, **IP-адрес**, **порт** и **пароль**), симулируя нативный запуск через внутренние ресурсы **Windows API**, доступ к которым осуществляется напрямую через **PowerShell**.

## Языки

- Português: [README](../../)
- Deutsch: [README](../Deutsch/README.md)
- English: [README](../English/README.md)
- Español: [README](../Espanol/README.md)
- Français: [README](../Francais/README.md)
- Italiano: [README](../Italiano/README.md)
- Polski: [README](../Polski/README.md)
- Svenska: [README](../Svenska/README.md)
- Türkçe: [README](../Turkce/README.md)

## Содержание

- [SA-MP Injector PowerShell](#sa-mp-injector-powershell)
  - [Языки](#языки)
  - [Содержание](#содержание)
  - [Основные концепции и мотивация](#основные-концепции-и-мотивация)
    - [Зачем внедрять DLLs?](#зачем-внедрять-dlls)
    - [SA-MP и OMP: различия и сходства](#sa-mp-и-omp-различия-и-сходства)
    - [Внедрение DLLs в PowerShell: прямой подход с WinAPI](#внедрение-dlls-в-powershell-прямой-подход-с-winapi)
  - [Внутренняя архитектура библиотеки: глубокое погружение](#внутренняя-архитектура-библиотеки-глубокое-погружение)
    - [`Constants.ps1`](#constantsps1)
    - [`CustomTypes.ps1`](#customtypesps1)
    - [`StringUtils.ps1`](#stringutilsps1)
    - [`ErrorUtils.ps1`](#errorutilsps1)
    - [`Process.ps1`](#processps1)
    - [`InjectorCore.ps1`](#injectorcoreps1)
    - [`Injector.ps1`](#injectorps1)
    - [`Cleanup.ps1`](#cleanupps1)
  - [Комплексные примеры использования](#комплексные-примеры-использования)
    - [1. Подготовка среды разработки](#1-подготовка-среды-разработки)
    - [2. Базовый сценарий: подключение к серверу SA-MP](#2-базовый-сценарий-подключение-к-серверу-sa-mp)
    - [3. Продвинутый сценарий: подключение к серверу OMP](#3-продвинутый-сценарий-подключение-к-серверу-omp)
    - [4. Выполнение из родительского скрипта](#4-выполнение-из-родительского-скрипта)
  - [Обработка распространенных ошибок и сообщений](#обработка-распространенных-ошибок-и-сообщений)
    - [1. Недопустимый тип внедрения](#1-недопустимый-тип-внедрения)
    - [2. Неверный порт сервера (формат или диапазон)](#2-неверный-порт-сервера-формат-или-диапазон)
      - [2.1. Нечисловой формат порта](#21-нечисловой-формат-порта)
      - [2.2. Порт вне допустимого диапазона](#22-порт-вне-допустимого-диапазона)
    - [3. Неверный никнейм (пустой или слишком длинный)](#3-неверный-никнейм-пустой-или-слишком-длинный)
      - [3.1. Пустой никнейм](#31-пустой-никнейм)
      - [3.2. Слишком длинный никнейм](#32-слишком-длинный-никнейм)
    - [4. Файлы игры или DLL не найдены](#4-файлы-игры-или-dll-не-найдены)
      - [4.1. Исполняемый файл игры (`gta_sa.exe`) не найден](#41-исполняемый-файл-игры-gta_saexe-не-найден)
      - [4.2. Библиотека SA-MP (`samp.dll`) не найдена](#42-библиотека-sa-mp-sampdll-не-найдена)
      - [4.3. Библиотека OMP (`omp-client.dll`) не найдена (только для внедрения OMP)](#43-библиотека-omp-omp-clientdll-не-найдена-только-для-внедрения-omp)
    - [5. Сбой при создании процесса игры](#5-сбой-при-создании-процесса-игры)
    - [6. Сбой при выделении памяти в целевом процессе](#6-сбой-при-выделении-памяти-в-целевом-процессе)
    - [7. Сбой при записи пути DLL в память процесса](#7-сбой-при-записи-пути-dll-в-память-процесса)
    - [8. Сбой при поиске основных системных функций](#8-сбой-при-поиске-основных-системных-функций)
      - [8.1. `kernel32.dll` не найден](#81-kernel32dll-не-найден)
      - [8.2. `LoadLibraryA` не найден](#82-loadlibrarya-не-найден)
    - [9. Сбой при создании удаленного потока для внедрения](#9-сбой-при-создании-удаленного-потока-для-внедрения)
    - [10. Тайм-аут или сбой при завершении внедрения](#10-тайм-аут-или-сбой-при-завершении-внедрения)
    - [11. Сбой при возобновлении потока процесса игры](#11-сбой-при-возобновлении-потока-процесса-игры)
  - [Лицензия](#лицензия)
    - [Условия использования](#условия-использования)
      - [1. Предоставленные разрешения](#1-предоставленные-разрешения)
      - [2. Обязательные условия](#2-обязательные-условия)
      - [3. Авторские права](#3-авторские-права)
      - [4. Отказ от гарантий и ограничение ответственности](#4-отказ-от-гарантий-и-ограничение-ответственности)

## Основные концепции и мотивация

### Зачем внедрять DLLs?

> [!NOTE]
> **Внедрение DLL (Dynamic Link Library)** — это метод, используемый в операционных системах **Microsoft Windows**, который позволяет выполнять код в адресном пространстве другого запущенного процесса. Это мощная техника с множеством законных применений, от отладки и мониторинга программ до изменения поведения приложений для расширения их функциональности.

В контексте игр, таких как **GTA San Andreas**, которые изначально не были разработаны со встроенной многопользовательской функциональностью, **внедрение DLL** является основой для существования многопользовательских клиентов, таких как **SA-MP** и **OMP**. Эти клиенты реализованы в виде **DLL**, которые, будучи внедренными в процесс `gta_sa.exe`, берут на себя управление, перехватывают функции игры и устанавливают связь с многопользовательскими серверами.

Вместо того чтобы полагаться на внешний лаунчер или прямое изменение исполняемого файла игры, **внедрение DLL** позволяет более гибкий и программируемый запуск, что особенно полезно в средах, где требуется автоматизировать процесс подключения к конкретным серверам с предопределенными настройками.

### SA-MP и OMP: различия и сходства

**SA-MP** и **OMP** — это две основные многопользовательские платформы для **GTA San Andreas**. Обе работают как модификации базовой игры, превращая ее в массовую многопользовательскую онлайн-среду.

- **SA-MP (San Andreas Multiplayer)**: Оригинальный и наиболее устоявшийся клиент, широко использовавшийся на протяжении многих лет. Для его работы требуется `samp.dll`.
- **OMP (Open Multiplayer)**: Проект с открытым исходным кодом, который часто рассматривается как преемник или более современная альтернатива **SA-MP**, предлагающая улучшения производительности, стабильности и дополнительные функции. Для него требуется `omp-client.dll`.

Хотя они работают схожим образом (**внедряя DLL** в процесс **GTA:SA**), библиотека **SA-MP Injector PowerShell** была тщательно разработана для поддержки **обеих DLL**, распознавая их различия в именах файлов и позволяя разработчику выбирать желаемый многопользовательский клиент через параметр конфигурации. Это гарантирует, что библиотеку можно использовать с широким спектром серверов и проектов, основанных на любой из этих платформ.

### Внедрение DLLs в PowerShell: прямой подход с WinAPI

PowerShell — это мощный скриптовый язык для автоматизации в Windows, но манипулирование процессами и внедрение DLL на таком низком системном уровне не является его основной функцией. Для достижения этой цели библиотека **SA-MP Injector PowerShell** широко использует команду `Add-Type` для прямого вызова функций **Windows API (WinAPI)**.

`Add-Type` позволяет определять и компилировать код C# (или другие языки .NET) во время выполнения в среде PowerShell. Этот код C# действует как "мост" к нативным функциям WinAPI (`DllImport`), позволяя выполнять такие операции, как:

- **`CreateProcessA`**: Для запуска процесса GTA:SA.
- **`VirtualAllocEx`**: Для выделения памяти в удаленном процессе.
- **`WriteProcessMemory`**: Для копирования пути DLL в выделенную память.
- **`GetModuleHandleA` и `GetProcAddress`**: Для получения адреса функции `LoadLibraryA` в `kernel32.dll`.
- **`CreateRemoteThread`**: Для создания потока в удаленном процессе, который выполняет `LoadLibraryA`, эффективно загружая DLL.
- **`WaitForSingleObject` и `GetExitCodeThread`**: Для мониторинга успешности внедрения.
- **`ResumeThread`**: Для возобновления работы процесса игры после внедрения.
- **`CloseHandle`**: Для закрытия дескрипторов системных ресурсов и предотвращения утечек.
- **`MessageBoxW`**: Для отображения информативных сообщений об ошибках пользователю.

Этот прямой подход с использованием WinAPI позволяет PowerShell выполнять те же низкоуровневые операции, что и скомпилированное приложение на **C++**, с удобством скриптовой среды.

## Внутренняя архитектура библиотеки: глубокое погружение

Библиотека **SA-MP Injector PowerShell** использует модульный подход для управления сложностью процесса внедрения. Каждый скрипт является специализированным модулем, отвечающим за определенную часть общей функциональности, что способствует ясности кода, удобству обслуживания и расширяемости.

### `Constants.ps1`

Этот скрипт является основой для всех фиксированных конфигураций библиотеки. Он определяет глобальную хеш-таблицу (`$global:CONSTANTS`), которая хранит все литералы и числовые значения, используемые, такие как ограничения портов, имена файлов DLL, ссылки на системные API и флаги для операций, таких как создание процесса и выделение памяти.

```powershell
$global:CONSTANTS = @{
    # Port validation limits
    MIN_PORT = 1
    MAX_PORT = 65535
    
    # Nickname constraints
    MAX_NICKNAME_LENGTH = 23
    
    # Required file names
    SAMP_DLL_NAME = "samp.dll"
    OMP_DLL_NAME = "omp-client.dll"
    GAME_EXE_NAME = "gta_sa.exe"
    
    # System API references
    KERNEL32_DLL = "kernel32.dll"
    USER32_DLL = "user32.dll" # Используется для MessageBoxW
    LOAD_LIBRARY_FUNC = "LoadLibraryA"
    
    # Command line argument prefixes
    CMD_ARG_CONFIG = "-c"
    CMD_ARG_NICKNAME = "-n"
    CMD_ARG_HOST = "-h"
    CMD_ARG_PORT = "-p"
    CMD_ARG_PASSWORD = "-z"
    
    # Injection type identifiers
    INJECT_TYPE_SAMP = "samp"
    INJECT_TYPE_OMP = "omp"
    
    # Error dialog titles
    ERROR_TITLE_SAMP = "SA-MP Injector Error - SPC"
    ERROR_TITLE_OMP = "OMP Injector Error - SPC"
    
    # Process creation flags (CREATE_SUSPENDED | DETACHED_PROCESS)
    # 0x00000104 = CREATE_SUSPENDED (0x4) + DETACHED_PROCESS (0x100)
    PROCESS_CREATION_FLAGS = 0x00000104
    
    # Operation timeouts
    DLL_INJECTION_TIMEOUT_MS = 10000 # 10 секунд
    
    # Memory allocation constants
    # 0x00003000 = MEM_COMMIT (0x1000) + MEM_RESERVE (0x2000)
    MEMORY_ALLOCATION_TYPE = 0x00003000
    # 0x00000004 = PAGE_READWRITE
    MEMORY_PROTECTION = 0x00000004
    # 0x00008000 = MEM_RELEASE
    MEMORY_FREE_TYPE = 0x00008000
    
    # Wait object results (Windows API)
    WAIT_OBJECT_0 = 0x00000000
    WAIT_TIMEOUT = 0x00000102
    WAIT_FAILED = 0xFFFFFFFF
    
    # Thread resume error indicator (Windows API)
    THREAD_RESUME_ERROR = 0xFFFFFFFF # ResumeThread returns -1 on failure
    
    # MessageBox constants (Windows API)
    MB_OK = 0x00000000
    MB_ICONERROR = 0x00000010
    MB_TOPMOST = 0x00040000
}
```

> [!TIP]
> Использование глобальной хеш-таблицы для констант — это распространенная практика в скриптах PowerShell. Она централизует настройки и позволяет избежать "магических чисел" и повторяющихся строк, делая код более читаемым и легким в обслуживании. Значения флагов (`0x...`) соответствуют десятичным значениям констант, определенных в Windows API.

### `CustomTypes.ps1`

Этот скрипт является основополагающим для взаимодействия с Windows API. Он определяет типы C# во время выполнения с помощью `Add-Type`, включая:

- **`Inject_Type` enum**: Для категоризации типа внедрения (SAMP или OMP), улучшая безопасность типов.
- **`WinAPI` class**: Статический класс, который импортирует и предоставляет функции Windows API, необходимые для внедрения. Каждый метод в этом классе соответствует функции API (`DllImport`) с правильной сигнатурой и набором символов (`CharSet`).
- **`Startup_Info` struct и `Process_Information` struct**: Структуры данных C#, которые дублируют структуры `STARTUPINFO` и `PROCESS_INFORMATION`, используемые функцией `CreateProcessA` из Windows API.
- **`Process_Info` class**: Простой класс C#, который действует как контейнер для дескрипторов процесса и потока, возвращаемых после успешного создания процесса, облегчая передачу и управление этими дескрипторами в среде PowerShell.

```powershell
if (-not ([System.Management.Automation.PSTypeName]'Inject_Type').Type) {
    Add-Type -TypeDefinition @'
        public enum Inject_Type {
            SAMP = 0,
            OMP = 1
        }
'@
}

if (-not ([System.Management.Automation.PSTypeName]'WinAPI').Type) {
    Add-Type -TypeDefinition @'
        using System;
        using System.Runtime.InteropServices;
        using System.Text; // Необходимо для Marshal.GetLastWin32Error
        
        public class WinAPI {
            [DllImport("kernel32.dll", SetLastError = true, CharSet = CharSet.Ansi)]
            public static extern bool CreateProcessA(string lpApplicationName, [In, Out] byte[] lpCommandLine, IntPtr lpProcessAttributes, IntPtr lpThreadAttributes, bool bInheritHandles, 
                uint dwCreationFlags, IntPtr lpEnvironment, string lpCurrentDirectory, [In, Out] ref Startup_Info lpStartupInfo, out Process_Information lpProcessInformation);
            
            [DllImport("kernel32.dll", SetLastError = true)]
            public static extern IntPtr VirtualAllocEx(IntPtr hProcess, IntPtr lpAddress, uint dwSize, uint flAllocationType, uint flProtect);
            
            [DllImport("kernel32.dll", SetLastError = true)]
            public static extern bool VirtualFreeEx(IntPtr hProcess, IntPtr lpAddress, uint dwSize, uint dwFreeType);
            
            [DllImport("kernel32.dll", SetLastError = true)]
            public static extern bool WriteProcessMemory(IntPtr hProcess, IntPtr lpBaseAddress, byte[] lpBuffer, uint nSize, out IntPtr lpNumberOfBytesWritten);
            
            [DllImport("kernel32.dll", SetLastError = true, CharSet = CharSet.Ansi)]
            public static extern IntPtr GetModuleHandleA(string lpModuleName);
            
            [DllImport("kernel32.dll", SetLastError = true, CharSet = CharSet.Ansi)]
            public static extern IntPtr GetProcAddress(IntPtr hModule, string lpProcName);
            
            [DllImport("kernel32.dll", SetLastError = true)]
            public static extern IntPtr CreateRemoteThread(IntPtr hProcess, IntPtr lpThreadAttributes, uint dwStackSize, IntPtr lpStartAddress, IntPtr lpParameter, uint dwCreationFlags, 
                out IntPtr lpThreadId);
            
            [DllImport("kernel32.dll", SetLastError = true)]
            public static extern uint WaitForSingleObject(IntPtr hHandle, uint dwMilliseconds);
            
            [DllImport("kernel32.dll", SetLastError = true)]
            public static extern bool GetExitCodeThread(IntPtr hThread, out uint lpExitCode);
            
            [DllImport("kernel32.dll", SetLastError = true)]
            public static extern uint ResumeThread(IntPtr hThread);
            
            [DllImport("kernel32.dll", SetLastError = true)]
            public static extern bool CloseHandle(IntPtr hObject);
            
            [DllImport("user32.dll", SetLastError = true, CharSet = CharSet.Unicode)]
            public static extern int MessageBoxW(IntPtr hWnd, string lpText, string lpCaption, uint uType);
            
            // Структура C# для STARTUPINFO
            [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi)]
            public struct Startup_Info {
                public uint cb;
                public string lpReserved;
                public string lpDesktop;
                public string lpTitle;
                public uint dwX;
                public uint dwY;
                public uint dwXSize;
                public uint dwYSize;
                public uint dwXCountChars;
                public uint dwYCountChars;
                public uint dwFillAttribute;
                public uint dwFlags;
                public short wShowWindow;
                public short cbReserved2;
                public IntPtr lpReserved2;
                public IntPtr hStdInput;
                public IntPtr hStdOutput;
                public IntPtr hStdError;
            }
            
            // Структура C# для PROCESS_INFORMATION
            [StructLayout(LayoutKind.Sequential)]
            public struct Process_Information {
                public IntPtr hProcess;
                public IntPtr hThread;
                public uint dwProcessId;
                public uint dwThreadId;
            }
        }
'@
}

if (-not ([System.Management.Automation.PSTypeName]'Process_Info').Type) {
    Add-Type -TypeDefinition @'
        using System;
        
        // Вспомогательный класс для передачи дескрипторов процесса и потока
        public class Process_Info {
            public IntPtr ProcessHandle { get; set; }
            public IntPtr ThreadHandle { get; set; }
            
            public Process_Info() {
                ProcessHandle = IntPtr.Zero;
                ThreadHandle = IntPtr.Zero;
            }
        }
'@
}
```

> [!IMPORTANT]
> Внедрение 32-битных DLL (таких как `samp.dll` и `omp-client.dll`) в 32-битный процесс (`gta_sa.exe`) **требует, чтобы среда PowerShell также была 32-битной**. **SA-MP Injector PowerShell** автоматически справляется с этим, перезапускаясь в оболочке PowerShell x86, если обнаруживает, что выполняется в среде x64. Это критически важно для обеспечения совместимости размеров указателей и правильной работы внедрения.
>
> Директива `if (-not ([System.Management.Automation.PSTypeName]'TypeName').Type)` гарантирует, что типы C# добавляются в среду PowerShell только один раз, избегая ошибок переопределения, если скрипт выполняется несколько раз в одной и той же сессии.

### `StringUtils.ps1`

Этот модуль предоставляет важную утилитарную функцию для манипулирования строками, в частности для обработки кодировок символов, необходимых при взаимодействии с устаревшим Windows API (функции "A" с char*).

```powershell
function Convert_Wide_To_Local_8Bit {
    param([Parameter(Mandatory = $false)] [AllowEmptyString()] [string]$wide_string)
    
    if ([string]::IsNullOrEmpty($wide_string)) {
        return [string]::Empty
    }

    try {
        # Получает локальную кодовую страницу ANSI системы
        $ansi_code_page = [System.Globalization.CultureInfo]::CurrentCulture.TextInfo.ANSICodePage
        $encoding = [System.Text.Encoding]::GetEncoding($ansi_code_page)
        
        # Преобразует строку Unicode (wide) в байты в локальной кодировке ANSI
        $bytes = $encoding.GetBytes($wide_string)

        # Преобразует байты обратно в строку, используя ту же кодировку ANSI
        # Это гарантирует, что строка будет совместима с API, которые ожидают 8-битную кодировку (ANSI)
        return $encoding.GetString($bytes)
    }
    catch {
        # В случае ошибки преобразования (например, символы, которые не могут быть отображены),
        # возвращает исходную строку в качестве запасного варианта, хотя это может вызвать проблемы,
        # если она содержит символы, не поддерживаемые API ANSI.
        return $wide_string
    }
}
```

> [!IMPORTANT]
> Функция `Convert_Wide_To_Local_8Bit` является критически важной, поскольку многие функции Windows API с суффиксом "A" (`CreateProcessA`, `LoadLibraryA`, `GetModuleHandleA`, `GetProcAddress`) ожидают строки в кодировке ANSI (8-бит), которые зависят от локальной кодовой страницы системы. По умолчанию строки в PowerShell являются Unicode. Эта функция выполняет необходимое преобразование. Если имя файла или аргумент командной строки содержат символы вне системной кодовой страницы ANSI, преобразование может привести к некорректным символам или потере данных. Для этого проекта, который нацелен на взаимодействие со старыми программами, этот подход с ANSI обычно достаточен и необходим.

### `ErrorUtils.ps1`

Этот модуль отвечает за предоставление четкой обратной связи пользователю в случае сбоя. Он централизует логику получения сообщений об ошибках из системы и отображения стандартных диалоговых окон Windows.

```powershell
function Get_System_Error_Message {
    param([Parameter(Mandatory = $true)][int]$error_code)
    
    try {
        # Использует Win32Exception для получения отформатированного системой сообщения об ошибке
        $exception = New-Object System.ComponentModel.Win32Exception($error_code)
        
        return $exception.Message
    }
    catch {
        # Запасной вариант для неизвестной ошибки
        return "Unknown error (Code: $error_code)"
    }
}

function Show_Error {
    param([Parameter(Mandatory = $true)][string]$message, [Parameter(Mandatory = $true)][Inject_Type]$inject_type)
    
    # Определяет заголовок диалогового окна в зависимости от типа внедрения
    $title = if ($inject_type -eq [Inject_Type]::SAMP) {
        $global:CONSTANTS.ERROR_TITLE_SAMP
    }
    else {
        $global:CONSTANTS.ERROR_TITLE_OMP
    }
    
    try {
        # Комбинирует флаги для MessageBoxW (OK, Иконка Ошибки, Поверх всех окон)
        $message_box_flags = $global:CONSTANTS.MB_OK -bor $global:CONSTANTS.MB_ICONERROR -bor $global:CONSTANTS.MB_TOPMOST
        
        # Вызывает функцию MessageBoxW, импортированную через Add-Type
        [void][WinAPI]::MessageBoxW([System.IntPtr]::Zero, $message, $title, $message_box_flags)
    }
    catch {
        # В случае сбоя отображения MessageBox (например, в средах без UI), выводит в консоль
        Write-Host "[$title] $message" -ForegroundColor Red
    }
}
```

> [!NOTE]
> `Get_System_Error_Message` использует `System.ComponentModel.Win32Exception` из .NET для преобразования числового кода ошибки Windows API (`GetLastError()`) в читаемое для пользователя текстовое описание, которое может быть локализовано на язык операционной системы.
>
> `Show_Error` использует функцию `MessageBoxW`, импортированную из `user32.dll` через `Add-Type` (`CustomTypes.ps1`), для отображения информативного диалогового окна. Флаги, такие как `MB_OK` и `MB_ICONERROR`, импортируются из констант WinAPI.

### `Process.ps1`

Это основной модуль, отвечающий за прямое взаимодействие с низкоуровневыми API Windows для манипулирования процессами. Он инкапсулирует ключевые операции создания процесса и внедрения DLL, работая с дескрипторами, памятью и потоками.

```powershell
class Process {
    # Освобождает дескрипторы процесса и потока, предотвращая утечки ресурсов
    [void] Close_Process_Info([Process_Info]$process_info) {
        if ($null -ne $process_info) {
            # Закрывает дескриптор процесса, если он действителен
            if ($process_info.ProcessHandle -ne [System.IntPtr]::Zero -and $process_info.ProcessHandle -ne [System.IntPtr]::new(-1)) {
                [void][WinAPI]::CloseHandle($process_info.ProcessHandle)
                $process_info.ProcessHandle = [System.IntPtr]::Zero # Помечает как закрытый
            }

            # Закрывает дескриптор потока, если он действителен
            if ($process_info.ThreadHandle -ne [System.IntPtr]::Zero -and $process_info.ThreadHandle -ne [System.IntPtr]::new(-1)) {
                [void][WinAPI]::CloseHandle($process_info.ThreadHandle)
                $process_info.ThreadHandle = [System.IntPtr]::Zero # Помечает как закрытый
            }
        }
    }

    # Создает процесс игры GTA:SA в приостановленном состоянии
    [Process_Info] Create_Game_Process([string]$game_path, [string]$command_args, [string]$working_dir) {
        $startup_info = New-Object WinAPI+Startup_Info
        # Устанавливает размер структуры, что критически важно для API Windows
        $startup_info.cb = [System.Runtime.InteropServices.Marshal]::SizeOf($startup_info)
        
        $process_information = New-Object WinAPI+Process_Information
        
        $command_line_bytes = $null

        if (-not [string]::IsNullOrEmpty($command_args)) {
            # Преобразует аргументы командной строки в массив байтов ANSI с нулевым терминатором
            $command_line_bytes = [System.Text.Encoding]::Default.GetBytes($command_args + "`0")
        }
        
        # Устанавливает рабочий каталог, null если пустой
        $current_directory = if ([string]::IsNullOrEmpty($working_dir)) {
            $null
        }
        else {
            $working_dir
        }
        
        # Вызывает функцию CreateProcessA из Windows API
        $success = [WinAPI]::CreateProcessA($game_path, $command_line_bytes, [System.IntPtr]::Zero, [System.IntPtr]::Zero, $false, $global:CONSTANTS.PROCESS_CREATION_FLAGS, 
            [System.IntPtr]::Zero, $current_directory, [ref]$startup_info, [ref]$process_information)
        
        if (-not $success) {
            # В случае сбоя получает последнюю системную ошибку и отображает ее
            $error_code = [System.Runtime.InteropServices.Marshal]::GetLastWin32Error()
            $error_message = Get_System_Error_Message $error_code
            Show_Error "Failed to create game process. Ensure 'gta_sa.exe' is not running and you have sufficient permissions to execute the file. System Error: $error_message" ([Inject_Type]::SAMP)

            return $null # Возвращает null в случае сбоя
        }
        
        # Возвращает объект Process_Info, содержащий дескрипторы процесса и потока
        $result = New-Object Process_Info
        $result.ProcessHandle = $process_information.hProcess
        $result.ThreadHandle = $process_information.hThread
        
        return $result
    }
    
    # Внедряет DLL в удаленный процесс
    [bool] Inject_DLL([IntPtr]$process_handle, [string]$dll_path, [ref]$error_message) {
        if ($process_handle -eq [System.IntPtr]::Zero) {
            $error_message.Value = "Invalid process handle provided for DLL injection."

            return $false
        }
        
        if ([string]::IsNullOrEmpty($dll_path)) {
            $error_message.Value = "DLL path cannot be empty."

            return $false
        }
        
        # Преобразует путь к DLL в байты ASCII (ANSI 8-бит) с нулевым терминатором
        $dll_path_bytes = [System.Text.Encoding]::ASCII.GetBytes($dll_path + "`0")
        $dll_path_size = $dll_path_bytes.Length
        
        # Выделяет память в удаленном процессе для пути к DLL
        $remote_memory = [WinAPI]::VirtualAllocEx($process_handle, [System.IntPtr]::Zero, $dll_path_size, $global:CONSTANTS.MEMORY_ALLOCATION_TYPE, $global:CONSTANTS.MEMORY_PROTECTION)
        
        if ($remote_memory -eq [System.IntPtr]::Zero) {
            $error_code = [System.Runtime.InteropServices.Marshal]::GetLastWin32Error()
            $error_message.Value = "Failed to allocate memory in the target process. This might be due to insufficient permissions or process protection mechanisms. System Error: $(Get_System_Error_Message $error_code)"

            return $false
        }
        
        # Использует блок try/finally для гарантии освобождения удаленной памяти
        try {
            $bytes_written = [System.IntPtr]::Zero
            # Записывает путь к DLL в удаленную память
            $write_success = [WinAPI]::WriteProcessMemory($process_handle, $remote_memory, $dll_path_bytes, $dll_path_size, [ref]$bytes_written)
            
            if (-not $write_success) {
                $error_code = [System.Runtime.InteropServices.Marshal]::GetLastWin32Error()
                $error_message.Value = "Failed to write DLL path to the target process memory. Verify process permissions and ensure the DLL path is accessible. System Error: $(Get_System_Error_Message $error_code)"
                
                return $false
            }
            
            # Получает дескриптор для kernel32.dll (который загружен во всех процессах)
            $kernel32_handle = [WinAPI]::GetModuleHandleA($global:CONSTANTS.KERNEL32_DLL)

            if ($kernel32_handle -eq [System.IntPtr]::Zero) {
                $error_code = [System.Runtime.InteropServices.Marshal]::GetLastWin32Error()
                $error_message.Value = "Failed to obtain a handle to kernel32.dll. This is an essential system library and this error indicates a severe system issue. System Error: $(Get_System_Error_Message $error_code)"
                
                return $false
            }
            
            # Получает адрес функции LoadLibraryA в kernel32.dll.
            # Этот адрес является постоянным между процессами в одной и той же ОС.
            $load_library_address = [WinAPI]::GetProcAddress($kernel32_handle, $global:CONSTANTS.LOAD_LIBRARY_FUNC)

            if ($load_library_address -eq [System.IntPtr]::Zero) {
                $error_code = [System.Runtime.InteropServices.Marshal]::GetLastWin32Error()
                $error_message.Value = "Failed to find the address of the LoadLibraryA function in kernel32.dll. This is critical for injecting the DLL. System Error: $(Get_System_Error_Message $error_code)"
                
                return $false
            }
            
            $thread_id = [System.IntPtr]::Zero
            # Создает удаленный поток в целевом процессе для выполнения LoadLibraryA
            $remote_thread_handle = [WinAPI]::CreateRemoteThread($process_handle, [System.IntPtr]::Zero, 0, $load_library_address, $remote_memory, 0, [ref]$thread_id)
            
            if ($remote_thread_handle -eq [System.IntPtr]::Zero) {
                $error_code = [System.Runtime.InteropServices.Marshal]::GetLastWin32Error()
                $error_message.Value = "Failed to create a remote thread in the target process to execute the DLL injection. This could be due to security restrictions or process state. System Error: $(Get_System_Error_Message $error_code)"
                
                return $false
            }
            
            # Использует блок try/finally для гарантии закрытия дескриптора удаленного потока
            try {
                # Ожидает завершения удаленного потока (внедрения DLL) или тайм-аута
                $wait_result = [WinAPI]::WaitForSingleObject($remote_thread_handle, $global:CONSTANTS.DLL_INJECTION_TIMEOUT_MS)
                
                if ($wait_result -ne $global:CONSTANTS.WAIT_OBJECT_0) {
                    $error_code = [System.Runtime.InteropServices.Marshal]::GetLastWin32Error()

                    $wait_result_message = switch ($wait_result) {
                        $global:CONSTANTS.WAIT_TIMEOUT { "timeout" }
                        $global:CONSTANTS.WAIT_FAILED { "wait failed" }
                        default { "unknown wait result ($wait_result)" }
                    }

                    $error_message.Value = "Timeout or error waiting for DLL injection to complete ($wait_result_message). System Error: $(Get_System_Error_Message $error_code)"

                    return $false
                }
                
                $exit_code = 0
                # Получает код завершения удаленного потока. Для LoadLibraryA 0 означает сбой.
                $get_exit_code_success = [WinAPI]::GetExitCodeThread($remote_thread_handle, [ref]$exit_code)
                
                if (-not $get_exit_code_success -or $exit_code -eq 0) {
                    $error_code = [System.Runtime.InteropServices.Marshal]::GetLastWin32Error()
                    $error_message.Value = "DLL injection failed or returned an error. The LoadLibrary call may have failed in the target process. Exit Code: $exit_code. System Error: $(Get_System_Error_Message $error_code)"

                    return $false
                }
                
                return $true # Внедрение прошло успешно
            }
            finally {
                # Гарантирует закрытие дескриптора удаленного потока
                [void][WinAPI]::CloseHandle($remote_thread_handle)
            }
        }
        finally {
            # Гарантирует освобождение удаленно выделенной памяти
            # 0 для dwSize в MEM_RELEASE освобождает всю область, выделенную VirtualAllocEx
            [void][WinAPI]::VirtualFreeEx($process_handle, $remote_memory, 0, $global:CONSTANTS.MEMORY_FREE_TYPE)
        }
    }
}
```

> [!NOTE]
> Класс `Process` использует `[System.IntPtr]` для представления дескрипторов Windows. Важно отметить широкое использование `try/finally` для гарантии правильного закрытия дескрипторов (`ProcessHandle`, `ThreadHandle`, `remote_memory`, `remote_thread_handle`) и освобождения памяти, даже в случае ошибок. Это способ реализации принципа **RAII** (Resource Acquisition Is Initialization) в PowerShell, хотя и менее интегрированный в синтаксис языка.

### `InjectorCore.ps1`

Это класс-оркестратор, который объединяет все функциональные возможности предыдущих модулей. Он координирует проверку, построение аргументов командной строки, создание процесса и вызовы для внедрения DLL.

```powershell
class Injector_Core {
    # Основная функция, которая организует инициализацию и внедрение в игру
    [bool] Initialize_Game([Inject_Type]$inject_type, [string]$folder, [string]$nickname, [string]$ip, [string]$port, [string]$password) {
        # Строит полные пути к основным файлам
        $game_path = Join-Path -Path $folder -ChildPath $global:CONSTANTS.GAME_EXE_NAME
        $samp_dll_path = Join-Path -Path $folder -ChildPath $global:CONSTANTS.SAMP_DLL_NAME
        $omp_dll_path = Join-Path -Path $folder -ChildPath $global:CONSTANTS.OMP_DLL_NAME
        
        $validation_error = [string]::Empty # Переменная для захвата сообщений об ошибках валидации
        
        # 1. Валидация файлов
        if (-not (Validate_Files $game_path $samp_dll_path $omp_dll_path $inject_type)) {
            # Ошибка уже была отображена функцией валидации
            return $false
        }

        # 2. Валидация порта
        if (-not (Validate_Port $port ([ref]$validation_error))) {
            Show_Error $validation_error $inject_type
            return $false
        }
        
        # 3. Валидация никнейма
        if (-not (Validate_Nickname $nickname ([ref]$validation_error))) {
            Show_Error $validation_error $inject_type
            return $false
        }
        
        # 4. Преобразование строк в кодировку ANSI/8-бит (необходимо для устаревших API)
        $converted_nickname = Convert_Wide_To_Local_8Bit $nickname
        $converted_ip = Convert_Wide_To_Local_8Bit $ip
        $converted_port = Convert_Wide_To_Local_8Bit $port
        $converted_password = Convert_Wide_To_Local_8Bit $password
        $converted_game_path = Convert_Wide_To_Local_8Bit $game_path
        $converted_folder = Convert_Wide_To_Local_8Bit $folder
        $converted_samp_dll_path = Convert_Wide_To_Local_8Bit $samp_dll_path
        $converted_omp_dll_path = Convert_Wide_To_Local_8Bit $omp_dll_path
        
        # 5. Построение аргументов командной строки
        $command_arguments = $this.Build_Command_Args($converted_nickname, $converted_ip, $converted_port, $converted_password)
        
        $process_manager = New-Object Process # Создает экземпляр класса Process
        $process_info = $null # Переменная для хранения информации о созданном процессе
        
        # Использует блок try/finally для гарантии закрытия дескрипторов процесса
        try {
            # 6. Создание процесса игры (приостановленного)
            $process_info = $process_manager.Create_Game_Process($converted_game_path, $command_arguments, $converted_folder)
            
            if ($null -eq $process_info) {
                # Ошибка уже была отображена функцией создания процесса
                return $false
            }

            $injection_error = [string]::Empty # Переменная для захвата сообщений об ошибках внедрения
            
            # 7. Внедрение samp.dll
            if (-not $process_manager.Inject_DLL($process_info.ProcessHandle, $converted_samp_dll_path, ([ref]$injection_error))) {
                Show_Error "Failed to inject samp.dll: $injection_error" $inject_type
                return $false
            }
            
            # 8. Условное внедрение omp-client.dll (только если тип внедрения - OMP)
            if ($inject_type -eq [Inject_Type]::OMP) {
                if (-not $process_manager.Inject_DLL($process_info.ProcessHandle, $converted_omp_dll_path, ([ref]$injection_error))) {
                    Show_Error "Failed to inject omp-client.dll: $injection_error" $inject_type
                    return $false
                }
            }
            
            # 9. Возобновление процесса игры
            # Процесс был создан в приостановленном состоянии, чтобы разрешить внедрение.
            # Теперь, когда DLL были внедрены, его можно возобновить.
            $resume_result = [WinAPI]::ResumeThread($process_info.ThreadHandle)

            if ($resume_result -eq $global:CONSTANTS.THREAD_RESUME_ERROR) {
                $error_code = [System.Runtime.InteropServices.Marshal]::GetLastWin32Error()
                $error_message = Get_System_Error_Message $error_code
                Show_Error "Failed to resume the game process thread: $error_message" $inject_type

                return $false
            }
            
            return $true # Успех на всех этапах!
        }
        finally {
            # Гарантирует закрытие дескрипторов процесса в конце,
            # независимо от успеха или сбоя.
            if ($null -ne $process_info) {
                $process_manager.Close_Process_Info($process_info)
            }
        }
    }
    
    # Строит строку аргументов командной строки для исполняемого файла игры
    [string] Build_Command_Args([string]$nickname, [string]$ip, [string]$port, [string]$password) {
        $arguments = @(
            $global:CONSTANTS.CMD_ARG_CONFIG,
            $global:CONSTANTS.CMD_ARG_NICKNAME, $nickname,
            $global:CONSTANTS.CMD_ARG_HOST, $ip, 
            $global:CONSTANTS.CMD_ARG_PORT, $port
        )
        
        if (-not [string]::IsNullOrEmpty($password)) {
            $arguments += @($global:CONSTANTS.CMD_ARG_PASSWORD, $password)
        }

        return $arguments -join ' '
    }
}
```

> [!CAUTION]
> Для **OMP** внедрение включает `omp-client.dll` *помимо* `samp.dll`. Это соответствует тому, как обычно работает **OMP**, поскольку он может использовать `samp.dll` в качестве основы и расширять функциональность с помощью `omp-client.dll`. Критически важно, чтобы **обе DLL** присутствовали и были работоспособны в каталоге игры для успешного внедрения OMP. Если одна из них не сработает, игра может не запуститься правильно или многопользовательский клиент может не загрузиться.
>
> Обратите внимание, что, поскольку в PowerShell нет `std::optional` или нативной гарантии **RAII**, как в C++, код использует явный блок `try/finally` в функции `Initialize_Game`, чтобы гарантировать вызов `Close_Process_Info` и освобождение дескрипторов, даже если произойдет ошибка. Это хорошая практика очистки ресурсов в PowerShell.

### `Injector.ps1`

Это основной входной скрипт библиотеки. Он занимается загрузкой других модулей, проверкой среды PowerShell (проверяя, является ли она x86 для совместимости внедрения) и инициализацией класса `Injector_Core`. Это скрипт, который будет выполнять конечный пользователь.

```powershell
param([Parameter(Mandatory = $true, Position = 0)][ValidateNotNullOrEmpty()][string]$inject_type,
    [Parameter(Mandatory = $true, Position = 1)][ValidateNotNullOrEmpty()][string]$folder,
    [Parameter(Mandatory = $true, Position = 2)][ValidateNotNullOrEmpty()][string]$nickname,
    [Parameter(Mandatory = $true, Position = 3)][ValidateNotNullOrEmpty()][string]$ip,
    [Parameter(Mandatory = $true, Position = 4)][ValidateNotNullOrEmpty()][string]$port,
    [Parameter(Position = 5)][AllowEmptyString()][string]$password = "",
    [switch]$restarted_x86) # Внутренний флаг для указания, что скрипт уже был перезапущен в x86

$ErrorActionPreference = 'Stop' # Гарантирует, что не-завершающие ошибки ведут себя как завершающие
# Это заставляет блоки catch перехватывать больше ошибок и предотвращает неожиданное продолжение работы скрипта.

# Получает полный путь к текущему скрипту, необходимый для загрузки вспомогательных модулей
$script_path = $MyInvocation.MyCommand.Path

if ([string]::IsNullOrEmpty($script_path)) {
    # В случаях, когда скрипт вызывается особым образом (например, из конвейера), $MyInvocation.MyCommand.Path может быть пустым
    $script_path = Join-Path -Path (Get-Location) -ChildPath $MyInvocation.MyCommand.Name
}

$script_directory = Split-Path -Parent $script_path # Базовый каталог библиотеки
$exit_code = 1 # Код выхода по умолчанию (сбой)

try {
    # Загружает все модули библиотеки (константы, пользовательские типы, утилиты и т.д.)
    . (Join-Path -Path $script_directory -ChildPath "Constants.ps1")
    . (Join-Path -Path $script_directory -ChildPath "CustomTypes.ps1")
    . (Join-Path -Path $script_directory -ChildPath "StringUtils.ps1")
    . (Join-Path -Path $script_directory -ChildPath "ErrorUtils.ps1")
    . (Join-Path -Path $script_directory -ChildPath "Validation.ps1")
    . (Join-Path -Path $script_directory -ChildPath "Process.ps1")
    . (Join-Path -Path $script_directory -ChildPath "InjectorCore.ps1")

    # Определяет основную интерфейсную функцию для пользователя.
    # Это обертка для класса Injector_Core.
    function Initialize_Game {
        param([string]$inject_type, [string]$folder, [string]$nickname, [string]$ip, [string]$port, [string]$password = "")

        # Проверяет, является ли среда PowerShell x64 и еще не была ли перезапущена в x86
        if ([IntPtr]::Size -eq 8 -and -not $restarted_x86) {
            Write-Host "Detected PowerShell x64 environment. Restarting on PowerShell x86 for DLL injection compatibility (32-bit)..." -ForegroundColor Yellow

            # Находит исполняемый файл PowerShell 32-бит
            $powershell_x86_path = Join-Path -Path $env:windir -ChildPath "SysWOW64\WindowsPowerShell\v1.0\powershell.exe"

            if (-not (Test-Path -Path $powershell_x86_path)) {
                Write-Host "Could not find powershell.exe (x86) at '$powershell_x86_path'. 32-bit DLL injection may fail." -ForegroundColor Red
                return $false
            }

            # Готовит список аргументов для нового процесса PowerShell x86
            $argument_list = @("-NoProfile", "-NonInteractive", "-ExecutionPolicy", "Bypass", "-File", $script_path, $inject_type, $folder, $nickname, $ip, $port)
            
            if (-not [string]::IsNullOrEmpty($password)) {
                $argument_list += $password
            }
            # Добавляет флаг для указания, что уже был перезапущен
            $argument_list += "-restarted_x86"
            
            try {
                $process_start_info = New-Object System.Diagnostics.ProcessStartInfo
                $process_start_info.FileName = $powershell_x86_path
                # Объединяет аргументы в строку для StartInfo.Arguments
                $process_start_info.Arguments = ($argument_list | ForEach-Object { "`"$_`"" }) -join " " # Оборачивает аргументы в кавычки для обработки пробелов
                $process_start_info.RedirectStandardOutput = $true # Перенаправляет стандартный вывод дочернего процесса
                $process_start_info.RedirectStandardError = $true   # Перенаправляет ошибки дочернего процесса
                $process_start_info.UseShellExecute = $false     # Не использует ShellExecute (запускает напрямую PowerShell.exe)
                $process_start_info.CreateNoWindow = $true       # Не создает нового окна для дочернего процесса

                $child_process = New-Object System.Diagnostics.Process
                $child_process.StartInfo = $process_start_info
                
                # Запускает дочерний процесс и ожидает его завершения
                [void]$child_process.Start()
                $child_process.WaitForExit()
                
                # Захватывает и отображает вывод/ошибки дочернего процесса
                $standard_output = $child_process.StandardOutput.ReadToEnd()
                $standard_error = $child_process.StandardError.ReadToEnd()

                if (-not [string]::IsNullOrEmpty($standard_output)) { Write-Host $standard_output }
                if (-not [string]::IsNullOrEmpty($standard_error)) { Write-Host $standard_error -ForegroundColor Red }

                $child_exit_code = $child_process.ExitCode
                
                if ($child_exit_code -eq 0) {
                    Write-Host "PowerShell x86 process completed with code 0 (Success)." -ForegroundColor Green
                    return $true
                }
                else {
                    Write-Host "PowerShell x86 process completed with error code: '$child_exit_code'." -ForegroundColor Red
                    return $false
                }
            }
            catch {
                Write-Host "Failed to start PowerShell x86: '$($_.Exception.Message)'" -ForegroundColor Red
                return $false
            }
        }
        
        # Реальная логика инициализации, достигается только если среда x86 или уже была перезапущена
        $injection_type = $null

        switch ($inject_type.ToLower()) {
            $global:CONSTANTS.INJECT_TYPE_SAMP {
                $injection_type = [Inject_Type]::SAMP
            }
            $global:CONSTANTS.INJECT_TYPE_OMP {
                $injection_type = [Inject_Type]::OMP
            }
            default {
                Show_Error "Invalid injection mode specified. Please use 'samp' or 'omp'." ([Inject_Type]::SAMP)
                return $false
            }
        }

        $injector_core = New-Object Injector_Core # Создает экземпляр основного класса для внедрения

        # Делегирует вызов функции Initialize_Game класса Injector_Core
        return $injector_core.Initialize_Game($injection_type, $folder, $nickname, $ip, $port, $password)
    }

    # Параметры, переданные основной функции
    $initialization_parameters = @{
        inject_type = $inject_type
        folder = $folder
        nickname = $nickname
        ip = $ip
        port = $port
        password = $password
    }

    # Вызов для начала процесса внедрения
    $game_initialization_result = Initialize_Game @initialization_parameters

    if ($game_initialization_result) {
        $exit_code = 0 # Успех
    }
    else {
        $exit_code = 1 # Сбой
    }
}
catch {
    Write-Host "Critical error during execution: '$($_.Exception.Message)'" -ForegroundColor Red
    $exit_code = 1
}
finally {
    # Гарантирует, что скрипт очистки будет выполнен в конце, независимо от успеха или сбоя
    try {
        . (Join-Path -Path $script_directory -ChildPath "Cleanup.ps1")
    }
    catch {
        Write-Host "Warning: Cleanup script execution failed: '$($_.Exception.Message)'" -ForegroundColor Yellow
    }
    
    exit $exit_code # Выходит с соответствующим кодом состояния
}
```

> [!NOTE]
> Этот скрипт является основной точкой входа для внедрения. Он отвечает за:
> - Определение **параметров командной строки**, которые будет использовать конечный пользователь.
> - Установку `$ErrorActionPreference = 'Stop'` для более строгого контроля ошибок.
> - **Загрузку** всех вспомогательных скриптов с помощью "dot-sourcing" (`. `), гарантируя, что их функции и классы будут доступны в текущей сессии.
> - Реализацию логики **перезапуска для среды x86**: Если PowerShell работает в 64-битном режиме, он автоматически перезапускается в 32-битном экземпляре (SysWOW64) и передает те же аргументы, поскольку внедрение 32-битных DLL более надежно (и, во многих случаях, обязательно) из 32-битного процесса. Это ключевое отличие PowerShell по сравнению с приложением C++, скомпилированным напрямую для x86.
> - Вызов функции `Initialize_Game` для начала процесса внедрения.
> - Управление кодом выхода скрипта (0 для успеха, 1 для сбоя).
> - Вызов скрипта `Cleanup.ps1` в блоке `finally`.

### `Cleanup.ps1`

Этот скрипт отвечает за удаление функций и глобальных переменных, загруженных библиотекой, из текущей сессии PowerShell. Это хорошая практика, чтобы избежать загрязнения среды и гарантировать, что последующие запуски скрипта с другими настройками не столкнутся с неожиданными состояниями из предыдущих сессий.

```powershell
$functions_to_remove = @(
    '*Initialize_Game*', # Использует маску для удаления функций (могут быть псевдонимы)
    '*Get_System_Error_Message*',
    '*Show_Error*',
    '*Convert_Wide_To_Local_8Bit*',
    '*Validate_*', # Удаляет все функции, начинающиеся с 'Validate_'
    '*Build_Command_Args*'
)

# Итерирует по шаблонам и удаляет функции
foreach ($pattern in $functions_to_remove) {
    Get-Command -CommandType Function -Name $pattern -ErrorAction SilentlyContinue | ForEach-Object {
        try {
            Remove-Item -Path "Function:$($_.Name)" -Force -ErrorAction SilentlyContinue
        }
        catch {} # Игнорирует ошибки, если функция не может быть удалена по какой-либо причине
    }
}

$global_variables_to_remove = @(
    'CONSTANTS',
    'CAN_SHOW_MESSAGE_BOX' # Добавьте сюда, если будут введены другие глобальные переменные
)

# Итерирует по глобальным переменным и удаляет их
foreach ($variable_name in $global_variables_to_remove) {
    try {
        Remove-Variable -Name $variable_name -Scope Global -Force -ErrorAction SilentlyContinue
    }
    catch {} # Игнорирует ошибки
}

$variable_patterns_to_remove = @(
    '*_Core*', # Удаляет переменные, заканчивающиеся на '_Core' (например, $injector_core)
    '*Process*' # Удаляет переменные, заканчивающиеся на 'Process' (например, $process_manager)
)

# Удаляет переменные в разных областях видимости с использованием шаблонов
foreach ($scope in @('Script', 'Local')) {
    foreach ($pattern in $variable_patterns_to_remove) {
        Get-Variable -Scope $scope -Name $pattern -ErrorAction SilentlyContinue | ForEach-Object {
            try {
                Remove-Variable -Name $_.Name -Scope $scope -Force -ErrorAction SilentlyContinue
            }
            catch {} # Игнорирует ошибки
        }
    }
}
```

> [!TIP]
> Очистка является критически важной в скриптах PowerShell, которые импортируют много элементов в сессию. `Remove-Item -Path "Function:..."` и `Remove-Variable` используются для освобождения этих элементов. Использование `ErrorAction SilentlyContinue` и пустых `try/catch` в циклах удаления гарантирует, что скрипт очистки не завершится сбоем, если какой-либо элемент уже был удален или не существует.

## Комплексные примеры использования

Чтобы интегрировать **SA-MP Injector PowerShell** в свой проект или использовать его напрямую, следуйте инструкциям и изучите сценарии ниже.

### 1. Подготовка среды разработки

- **PowerShell Version**: Рекомендуется **PowerShell 5.1** или выше (совместим с `Add-Type` для классов).
- **Разрешения на выполнение**: PowerShell имеет политики выполнения. Вам потребуется разрешить выполнение локальных скриптов. Откройте PowerShell от имени **Администратора** и выполните:
   ```powershell
   Set-ExecutionPolicy -ExecutionPolicy RemoteSigned -Scope CurrentUser
   ```
   Это позволит запускать подписанные скрипты, а также скрипты, которые вы создали (не скачанные из интернета), локально без подписи.
- **Копирование файлов**: Поместите все файлы `.ps1` библиотеки (`Injector.ps1`, `Constants.ps1`, `CustomTypes.ps1`, `StringUtils.ps1`, `ErrorUtils.ps1`, `Validation.ps1`, `Process.ps1`, `InjectorCore.ps1`, `Cleanup.ps1`) в один каталог.
- **Разрешения процесса**: Вашему скрипту потребуются привилегии **Администратора** для создания процессов и внедрения DLL в другой процесс. Всегда запускайте **PowerShell от имени Администратора** при использовании этой библиотеки.

### 2. Базовый сценарий: подключение к серверу SA-MP

Это наиболее распространенный случай использования, запуск GTA:SA и подключение к серверу SA-MP с определенным никнеймом и IP/портом.

```powershell
# Создайте новый скрипт, например, "StartSAMP.ps1"

# Импортирует основную функцию из библиотеки SA-MP Injector PowerShell
# Убедитесь, что указанный ниже путь соответствует расположению Injector.ps1.
# Например, если Injector.ps1 находится в той же папке, что и этот скрипт:
$injector_path = Join-Path -Path $PSScriptRoot -ChildPath "Injector.ps1"

# Или, если он находится в подкаталоге:
# $injector_path = Join-Path -Path $PSScriptRoot -ChildPath "SA-MP-Injector-PowerShell\Injector.ps1"

# Импортирует Injector.ps1 с помощью dot-sourcing, чтобы его функции
# стали доступны в текущей области видимости.
. $injector_path

# Определение переменных конфигурации
# Измените эти пути и данные сервера в соответствии с вашей локальной конфигурацией.
$game_folder = "C:\Games\GTA San Andreas" # Где находятся gta_sa.exe, samp.dll
$player_nickname = "Имя"
$server_ip = "127.0.0.1" # Пример: ваш локальный сервер
$server_port = "7777"
$server_password = "" # Оставьте пустым, если пароля нет

Write-Host "Запуск SA-MP..." -ForegroundColor Cyan
Write-Host "Папка с игрой: $game_folder" -ForegroundColor Gray
Write-Host "Никнейм: $player_nickname" -ForegroundColor Gray
Write-Host "Сервер: $server_ip:$server_port" -ForegroundColor Gray

# Вызов функции библиотеки для запуска игры
$result = Initialize_Game `
    -inject_type "samp" ` # Тип внедрения: "samp" или "omp"
    -folder $game_folder ` # Путь к папке с игрой
    -nickname $player_nickname ` # Желаемый никнейм
    -ip $server_ip ` # IP сервера
    -port $server_port ` # Порт сервера (строка)
    -password $server_password # Пароль сервера (строка, может быть пустой)

if ($result) {
    Write-Host "`n--- SA-MP успешно запущен! ---" -ForegroundColor Green
    Write-Host "Игра была запущена в отдельном процессе." -ForegroundColor Green
}
else {
    Write-Host "`n--- НЕ УДАЛОСЬ запустить SA-MP! ---" -ForegroundColor Red
    Write-Host "Проверьте отображаемые сообщения об ошибках (всплывающие окна или консоль)." -ForegroundColor Red
}

# Оставляет консоль открытой для просмотра сообщений вывода
Read-Host "`nНажмите Enter, чтобы закрыть программу."
```

**Чтобы запустить скрипт:**
1. **Сохраните** приведенный выше код как `StartSAMP.ps1` (или любое другое имя, главное, чтобы оно заканчивалось на `.ps1`).
2. **Сохраните** все файлы библиотеки **SA-MP Injector PowerShell** в ту же папку или в структуру подпапок, которую вы управляете с помощью `$injector_path`.
3. **Откройте PowerShell от имени Администратора**.
4. Перейдите в каталог, где вы сохранили `StartSAMP.ps1`.
5. Запустите скрипт:
   ```powershell
   .\StartSAMP.ps1
   ```
   (Помните, что `.` перед именем скрипта необходима для скриптов в текущем каталоге, если вы не добавили его в PATH).

### 3. Продвинутый сценарий: подключение к серверу OMP

Для OMP логика идентична логике SA-MP, но вы указываете `"omp"` в качестве `inject_type` и убеждаетесь, что `omp-client.dll` присутствует в каталоге игры.

```powershell
# Создайте новый скрипт, например, "StartOMP.ps1"

# Импортирует основную функцию из библиотеки SA-MP Injector PowerShell
$injector_path = Join-Path -Path $PSScriptRoot -ChildPath "Injector.ps1"
. $injector_path

# Определение переменных конфигурации для OMP
$game_folder = "C:\Games\GTA San Andreas" # Где находятся gta_sa.exe, samp.dll и omp-client.dll
$player_nickname = "Имя"
$server_ip = "127.0.0.1" # Пример: ваш локальный сервер
$server_port = "7777"
$server_password = "" # Оставьте пустым, если пароля нет

Write-Host "Запуск OMP..." -ForegroundColor Cyan
Write-Host "Папка с игрой: $game_folder" -ForegroundColor Gray
Write-Host "Никнейм: $player_nickname" -ForegroundColor Gray
Write-Host "Сервер: $server_ip:$server_port" -ForegroundColor Gray

# Вызов функции библиотеки для запуска игры
$result = Initialize_Game `
    -inject_type "omp" `   # Тип внедрения: "omp"
    -folder $game_folder `
    -nickname $player_nickname `
    -ip $server_ip `
    -port $server_port `
    -password $server_password

if ($result) {
    Write-Host "`n--- OMP успешно запущен! ---" -ForegroundColor Green
    Write-Host "Игра была запущена в отдельном процессе." -ForegroundColor Green
}
else {
    Write-Host "`n--- НЕ УДАЛОСЬ запустить OMP! ---" -ForegroundColor Red
    Write-Host "Проверьте отображаемые сообщения об ошибках (всплывающие окна или консоль)." -ForegroundColor Red
}

Read-Host "`nНажмите Enter, чтобы закрыть программу."
```

**Чтобы запустить скрипт:**

Следуйте тем же шагам, что и в предыдущем разделе, заменив `StartSAMP.ps1` на `StartOMP.ps1`.

### 4. Выполнение из родительского скрипта

Можно создать более сложный скрипт, который вызывает библиотеку и обрабатывает параметры или условия более продвинутым способом. Основная концепция остается прежней: `Injector.ps1` должен быть "dot-sourced" в родительском скрипте.

```powershell
# Launcher.ps1
param(
    [string]$type = "samp",
    [string]$game_dir = "C:\Games\GTA San Andreas",
    [string]$player_nickname = "Имя",
    [string]$server_ip = "127.0.0.1",
    [string]$server_port = "7777",
    [string]$server_password = ""
)

# Загружает Injector.ps1
$injector_script = Join-Path -Path $PSScriptRoot -ChildPath "Injector.ps1"

# Проверяет, существует ли основной скрипт инжектора, прежде чем загружать
if (-not (Test-Path $injector_script -PathType Leaf)) {
    Write-Error "Injector.ps1 не найден в $injector_script. Пожалуйста, проверьте путь."
    
    exit 1
}

. $injector_script # Использует dot-sourcing для загрузки функций

Write-Host "Попытка запустить игру с предоставленными параметрами..." -ForegroundColor Yellow

$success = Initialize_Game -inject_type $type `
    -folder $game_dir `
    -nickname $player_nickname `
    -ip $server_ip `
    -port $server_port `
    -password $server_password

if ($success) {
    Write-Host "`nОтчет лаунчера: Игра успешно запущена!" -ForegroundColor Green
}
else {
    Write-Host "`nОтчет лаунчера: Не удалось запустить игру!" -ForegroundColor Red
}

Read-Host "`nНажмите Enter для выхода."
```

**Выполнение `Launcher.ps1`:**

```powershell
# Запуск со значениями по умолчанию
.\Launcher.ps1

# Запуск для OMP с конкретным IP и портом
.\Launcher.ps1 -type "omp" -server_ip "omp.server.com" -server_port "7777" -player_nickname "Имя" -server_password "secure123"
```

## Обработка распространенных ошибок и сообщений

**SA-MP Injector PowerShell** ставит в приоритет удобство использования, и ключевой частью этого является предоставление четкой обратной связи пользователю в случае сбоя. Сообщения об ошибках отображаются через **диалоговые окна Windows** (`MessageBoxW`) или непосредственно в консоли PowerShell и классифицируются по типу **внедрения (SA-MP или OMP)** для большего контекста. Это гарантирует, что вы точно знаете, что пошло не так и как подойти к решению проблемы.

Вот некоторые из распространенных ошибок, с которыми вы можете столкнуться, и их вероятные причины/решения, сопровождаемые визуальными примерами того, как эти диалоговые окна выглядят для конечного пользователя:

### 1. Недопустимый тип внедрения

Если предоставленный `inject_type` не является `"samp"` или `"omp"`, библиотека не будет знать, какой многопользовательский клиент вы собираетесь запустить.

![Error 1](screenshots/error_1.png)

- **Отображаемое сообщение об ошибке**: `"Invalid injection mode specified. Please use 'samp' or 'omp'."`
- **Причина**: Аргумент `inject_type` не соответствует ожидаемым значениям `"samp"` или `"omp"`. Это может быть опечатка, пустая строка или нераспознанное значение.
- **Решение**: Убедитесь, что `$inject_type` правильно установлен как `"samp"` или `"omp"`. Важно, чтобы строка точно совпадала (хотя код использует `ToLower()` для сравнения).
   ```powershell
   # Правильно:
   Initialize_Game -inject_type "samp" ...
   Initialize_Game -inject_type "omp" ...

   # Неправильно (вызовет ошибку):
   # Initialize_Game -inject_type "invalid" ...
   # Initialize_Game -inject_type "" ...
   ```

### 2. Неверный порт сервера (формат или диапазон)

Порт является важным числовым параметром для подключения к серверу. Эта ошибка возникает, если значение не может быть интерпретировано как действительное число или находится вне допустимого диапазона (**от 1 до 65535**).

#### 2.1. Нечисловой формат порта

![Error 2](screenshots/error_2.png)

- **Отображаемое сообщение об ошибке**: `"Invalid port format. The port must be a numeric value. Please provide a valid integer for the port."`
- **Причина**: Аргумент `port` содержит символы, которые не являются цифрами, или не может быть преобразован в допустимое целое число (например, `"abc"`, `"7777a"`).
- **Решение**: Предоставьте строку, которая содержит только цифры и представляет собой допустимое целое число.
   ```powershell
   # Правильно:
   Initialize_Game ... -port "7777" ...
   
   # Неправильно (неверный формат):
   # Initialize_Game ... -port "port7777" ...
   # Initialize_Game ... -port "invalid" ...
   ```

#### 2.2. Порт вне допустимого диапазона

![Error 3](screenshots/error_3.png)

- **Отображаемое сообщение об ошибке**: `"The specified port number (XXXX) is outside the valid range of 1 to 65535. Please provide a valid port."` (**XXXX** будет значением, которое вы пытались использовать).
- **Причина**: Предоставленный порт является действительным числом, но он меньше `1` (зарезервирован или не используется) или больше `65535` (максимальный предел для **портов TCP/UDP**).
- **Решение**: Предоставьте порт, который находится в диапазоне от `1` до `65535`. Обычные порты для **SA-MP**/**OMP** — `7777`.
   ```powershell
   # Правильно:
   Initialize_Game ... -port "7777" ...

   # Неправильно (вне диапазона):
   # Initialize_Game ... -port "0" ...      # Слишком низкий
   # Initialize_Game ... -port "65536" ...  # Слишком высокий
   # Initialize_Game ... -port "-1" ...     # Отрицательное значение
   ```

### 3. Неверный никнейм (пустой или слишком длинный)

**Никнейм** игрока проверяется, чтобы убедиться, что клиент игры его примет.

#### 3.1. Пустой никнейм

![Error 4](screenshots/error_4.png)

- **Отображаемое сообщение об ошибке**: `"Nickname cannot be empty. Please provide a valid nickname."`
- **Причина**: Аргумент `nickname` был предоставлен как пустая строка.
- **Решение**: Убедитесь, что никнейм не пуст.
   ```powershell
   # Правильно:
   Initialize_Game ... -nickname "МоеИмя" ...

   # Неправильно (пустой):
   # Initialize_Game ... -nickname "" ...
   ```

#### 3.2. Слишком длинный никнейм

![Error 5](screenshots/error_5.png)

- **Отображаемое сообщение об ошибке**: `"Nickname length exceeds the maximum allowed of 23 characters. Please use a shorter nickname."`
- **Причина**: Длина предоставленного **никнейма** превышает `$global:CONSTANTS.MAX_NICKNAME_LENGTH`, что составляет `23` символов.
- **Решение**: Используйте **никнейм**, который имеет не более `23` символов.
   ```powershell
   # Правильно:
   Initialize_Game ... -nickname "Короткий" ...

   # Неправильно (слишком длинный):
   # Initialize_Game ... -nickname "ЭтоИмяИгрокаСлишкомДлинноеДляИспользованияЗдесь" ...
   ```

### 4. Файлы игры или DLL не найдены

Это одна из самых распространенных причин сбоя. Библиотеке необходимо, чтобы `gta_sa.exe`, `samp.dll` и, для **OMP**, `omp-client.dll` присутствовали в ожидаемых местах.

#### 4.1. Исполняемый файл игры (`gta_sa.exe`) не найден

![Error 6](screenshots/error_6.png)

- **Отображаемое сообщение об ошибке**: `"Game executable not found. Please ensure 'gta_sa.exe' exists at the specified path: [полный путь]"`. `[полный путь]` будет включать папку и имя файла.
- **Причина**: Файл `gta_sa.exe` не был найден в папке, указанной в аргументе `folder`.
- **Решение**:
   1. Проверьте, что `$folder` указывает на правильный каталог установки **GTA San Andreas**.
   2. Убедитесь, что `gta_sa.exe` существует в этой папке и его имя не было изменено.

#### 4.2. Библиотека SA-MP (`samp.dll`) не найдена

![Error 7](screenshots/error_7.png)

- **Отображаемое сообщение об ошибке**: `"SA-MP library not found. Please ensure 'samp.dll' exists at the specified path: [полный путь]"`.
- **Причина**: Файл `samp.dll` не был найден в папке, указанной в аргументе `folder`. **Эта DLL** является требованием для **обоих** типов внедрения (`samp` и `omp`).
- **Решение**: Убедитесь, что `samp.dll` присутствует в папке установки **GTA San Andreas**.

#### 4.3. Библиотека OMP (`omp-client.dll`) не найдена (только для внедрения OMP)

![Error 8](screenshots/error_8.png)

- **Отображаемое сообщение об ошибке**: `"OMP library not found. Please ensure 'omp-client.dll' exists at the specified path for OMP injection: [полный путь]"`.
- **Причина**: Если вы указали `"omp"` как тип внедрения, но файл `omp-client.dll` не был найден в указанной папке.
- **Решение**: Загрузите последнюю версию клиента **OMP** и убедитесь, что `omp-client.dll` (и `samp.dll`) присутствуют в папке установки **GTA San Andreas**.

### 5. Сбой при создании процесса игры

Это более сложная ошибка, так как она связана с **разрешениями операционной системы** и текущим состоянием `gta_sa.exe`.

![Error 9](screenshots/error_9.png)

- **Отображаемое сообщение об ошибке**: `"Failed to create game process. Ensure 'gta_sa.exe' is not running and you have sufficient permissions to execute the file. System Error: [Сообщение об ошибке операционной системы]"`. Сообщение системы будет добавлено `Get_System_Error_Message` (например, `Access is denied.` или `The requested operation requires elevation.`).
- **Причина**: Вызов `CreateProcessA` для запуска `gta_sa.exe` завершился неудачей. Распространенные причины включают:
   - **Процесс уже запущен**: Экземпляр `gta_sa.exe` уже активен и блокирует новый запуск.
   - **Недостаточно разрешений**: У вашего скрипта нет необходимых привилегий (например, администратора) для создания процесса при определенных настройках системы (**UAC** включен, защищенные папки и т.д.).
   - **Проблемы с исполняемым файлом**: `gta_sa.exe` может быть поврежден или заблокирован другой программой (например, неправильно настроенным антивирусом).
- **Решение**:
   1. Проверьте Диспетчер задач и убедитесь, что нет запущенных экземпляров `gta_sa.exe`. Завершите все, если они есть.
   2. Запустите скрипт **PowerShell от имени Администратора**. Щелкните правой кнопкой мыши по иконке PowerShell и выберите **"Запуск от имени администратора"** или запустите его из ярлыка, настроенного для этого.
   3. Если **антивирус** или **программное обеспечение** безопасности вмешивается, добавьте ваш скрипт и/или папку **GTA:SA** в исключения антивируса (делайте это с осторожностью и только если вы уверены в целостности ваших файлов).

### 6. Сбой при выделении памяти в целевом процессе

Библиотека пытается выделить небольшое пространство памяти в `gta_sa.exe` для копирования **пути DLL**.

![Error 10](screenshots/error_10.png)

- **Отображаемое сообщение об ошибке**: `"Failed to allocate memory in the target process. This might be due to insufficient permissions or process protection mechanisms. System Error: [Сообщение об ошибке операционной системы]"`.
- **Причина**: Функция `VirtualAllocEx` (используемая для выделения памяти в другом процессе) завершилась неудачей. Это наиболее вероятно, если:
   - Процесс **GTA:SA** (даже находясь в приостановленном состоянии) имеет защитные механизмы или **патчи против внедрения**, которые предотвращают выделение памяти внешними процессами.
   - У вашего скрипта нет необходимых повышенных разрешений для манипулирования памятью другого процесса.
   - (Менее распространено) В системе наблюдается крайняя нехватка виртуальной памяти.
- **Решение**:
   1. Запустите ваш скрипт с привилегиями **Администратора**.
   2. Убедитесь, что игра не имеет никаких модификаций или **патчей безопасности**, которые могут блокировать попытки внедрения или манипулирования памятью (это чаще встречается в модифицированных средах или с некоторыми сторонними античитерскими инструментами).

### 7. Сбой при записи пути DLL в память процесса

После выделения памяти библиотека пытается скопировать в нее **путь DLL**.

![Error 11](screenshots/error_11.png)

- **Отображаемое сообщение об ошибке**: `"Failed to write DLL path to the target process memory. Verify process permissions and ensure the DLL path is accessible. System Error: [Сообщение об ошибке операционной системы]"`.
- **Причина**: Функция `WriteProcessMemory` не смогла скопировать **байты пути DLL** в удаленную память, выделенную в `gta_sa.exe`. Это обычно указывает на:
   - **Разрешения на запись**: У вашего скрипта нет разрешения на запись в этот регион памяти или в процесс **GTA:SA**.
   - **Неверный дескриптор**: **Дескриптор** процесса каким-то образом стал недействительным (менее распространено, но возможно в экстремальных системных условиях).
   - **Проблемы с защитой памяти**: Какая-либо защита памяти (будь то от **ОС** или от модификаций игры) предотвратила запись.
- **Решение**: Запустите от имени **Администратора**. Убедитесь, что `gta_sa.exe` и его среда "чисты" от инструментов, которые могли бы блокировать операции с памятью.

### 8. Сбой при поиске основных системных функций

Это критически важные API Windows; ошибки здесь указывают на фундаментальную проблему с операционной системой или средой выполнения.

#### 8.1. `kernel32.dll` не найден

![Error 12](screenshots/error_12.png)

- **Отображаемое сообщение об ошибке**: `"Failed to obtain a handle to kernel32.dll. This is an essential system library and this error indicates a severe system issue. System Error: [Сообщение об ошибке операционной системы]"`.
- **Причина**: `kernel32.dll` — одна из самых базовых DLL Windows, содержащая основные функции. Если `GetModuleHandleA` не может получить для нее **дескриптор**, значит, у операционной системы очень серьезные проблемы.
- **Решение**: Это **критическая** ошибка, которая редко вызвана библиотекой или вашим скриптом. Она предполагает повреждение системных файлов, серьезные проблемы с **Windows** или очень необычную установку **ОС**. Рекомендуется выполнить проверку целостности системных файлов (например, `sfc /scannow` в **Командной строке** от имени **Администратора**) или, в крайнем случае, переустановить **Windows**.

#### 8.2. `LoadLibraryA` не найден

![Error 13](screenshots/error_13.png)

- **Отображаемое сообщение об ошибке**: `"Failed to find the address of the LoadLibraryA function in kernel32.dll. This is critical for injecting the DLL. System Error: [Сообщение об ошибке операционной системы]"`.
- **Причина**: Хотя `kernel32.dll` была найдена, функция `LoadLibraryA` не могла быть разрешена через `GetProcAddress`. Хотя это крайне необычно, это может быть результатом повреждения **файла DLL** `kernel32.dll` или очень нестандартной среды выполнения.
- **Решение**: Как и в случае с ошибкой `kernel32.dll` выше, это указывает на серьезную проблему в операционной системе.

### 9. Сбой при создании удаленного потока для внедрения

После подготовки удаленной среды и копирования **пути DLL**, в процессе игры создается новый **поток** для "вызова" `LoadLibraryA`.

![Error 14](screenshots/error_14.png)

- **Отображаемое сообщение об ошибке**: `"Failed to create a remote thread in the target process to execute the DLL injection. This could be due to security restrictions or process state. System Error: [Сообщение об ошибке операционной системы]"`.
- **Причина**: Вызов `CreateRemoteThread` завершился неудачей. Эта ошибка распространена в системах с надежной **защитой от внедрения** или когда программа интенсивно отслеживает поведение процесса:
   - **Механизмы безопасности**: Инструменты **анти-чита**, **программное обеспечение** безопасности или определенные политики **Windows** могут обнаруживать и блокировать попытки создания **потоков** в сторонних процессах.
   - **Нестабильное состояние целевого процесса**: Если процесс **GTA:SA** находится в неожиданном или нестабильном состоянии (хотя и запущен в `CREATE_SUSPENDED`), это может повлиять на возможность создания **потоков** в нем.
- **Решение**:
   1. Запустите ваш скрипт с привилегиями **Администратора**.
   2. Убедитесь, что нет инструментов **анти-чита**, **агрессивных антивирусов** или **файрволов**, настроенных на проверку и блокировку манипуляций с процессами, которые могут конфликтовать. Добавьте ваш скрипт и `gta_sa.exe` в исключения, если применимо (с осторожностью).
   3. Сообщение об ошибке системы может предоставить дополнительные детали для расследования конкретной причины (например, **"A process has been denied access to create threads for other processes."**).

### 10. Тайм-аут или сбой при завершении внедрения

После создания удаленного **потока**, инжектор ожидает, пока он завершит **загрузку DLL**.

![Error 15](screenshots/error_15.png)

- **Отображаемое сообщение об ошибке**: `"Timeout or error waiting for DLL injection to complete (timeout). System Error: [Сообщение об ошибке операционной системы]"`.
- **Причина**: Удаленный **поток**, выполняющий `LoadLibraryA`, занял больше `$global:CONSTANTS.DLL_INJECTION_TIMEOUT_MS` (10 секунд) для возврата, или он завершился сбоем и `GetExitCodeThread` вернул 0. Возможные причины включают:
   - **Проблемы во внедренной DLL**: `DllMain` из `samp.dll` или `omp-client.dll` выполняется слишком долго, содержит **бесконечный цикл**, **сбой** или ошибку, которая **мешает DLL** правильно загрузиться (например, отсутствующие **зависимости DLL**).
   - **Тихая блокировка**: Механизм безопасности мог заблокировать `LoadLibraryA`, но не уведомил об этом с явной ошибкой создания **потока**.
- **Решение**:
   1. Проверьте целостность файлов `samp.dll` и `omp-client.dll`. Они могут быть повреждены или быть несовместимой версии с вашим `gta_sa.exe`.
   2. Убедитесь, что **внедряемая DLL** не зависит от **других DLL**, которые могут отсутствовать или быть недоступны в системе.

### 11. Сбой при возобновлении потока процесса игры

Это заключительный шаг для запуска игры после **внедрения DLL**.

![Error 16](screenshots/error_16.png)

- **Отображаемое сообщение об ошибке**: `"Failed to resume the game process thread: [Сообщение об ошибке операционной системы]"`.
- **Причина**: Вызов `ResumeThread` завершился неудачей, что означает, что основной **поток** `gta_sa.exe` не мог быть активирован для начала выполнения игры. Это редкая ошибка, но она может произойти, если:
   - **Дескриптор** **потока** процесса стал недействительным.
   - Операционная система по какой-то причине предотвратила возобновление, возможно, связанное с прерыванием безопасности или нестабильным состоянием процесса.
   - Процесс мог быть завершен извне между **внедрением DLL** и попыткой возобновления основного **потока**.
- **Решение**: Если все предыдущие шаги прошли успешно и только `ResumeThread` завершился сбоем, это может быть проблемой с операционной системой, самой установкой **GTA:SA** или очень строгим **программным обеспечением** безопасности. Перепроверьте состояние `gta_sa.exe` через **Диспетчер задач** непосредственно до и после ошибки. Перезагрузка компьютера может решить временные проблемы с состоянием системы.

> [!TIP]
> В сложных сценариях отладки инструменты, такие как **Process Monitor (Sysinternals Suite)** или отладчик (например, **WinDbg**), могут быть бесценны. Они могут помочь отслеживать вызовы **API**, проверять ошибки доступа, отслеживать состояние **дескрипторов** и даже проверять память процесса, предоставляя глубокое понимание того, что происходит "под капотом".
>
> Для отладки скриптов PowerShell, использующих `Add-Type` и взаимодействующих с WinAPI на низком уровне, полезны такие инструменты, как **PowerShell Integrated Scripting Environment (ISE)** или **Visual Studio Code** с расширением PowerShell, позволяющие устанавливать точки останова и проверять переменные. Всегда помните запускать их **от имени Администратора**.

## Лицензия

Copyright © **SA-MP Programming Community**

Данное программное обеспечение лицензируется в соответствии с условиями лицензии MIT ("Лицензия"); вы можете использовать это программное обеспечение в соответствии с условиями Лицензии. Копию Лицензии можно получить по адресу: [MIT License](https://opensource.org/licenses/MIT)

### Условия использования

#### 1. Предоставленные разрешения

Настоящая лицензия бесплатно предоставляет любому лицу, получающему копию данного программного обеспечения и связанных с ним файлов документации, следующие права:
* Использовать, копировать, изменять, объединять, публиковать, распространять, сублицензировать и/или продавать копии программного обеспечения без ограничений
* Разрешать лицам, которым предоставляется программное обеспечение, делать то же самое при соблюдении указанных ниже условий

#### 2. Обязательные условия

Все копии или существенные части программного обеспечения должны включать:
* Вышеуказанное уведомление об авторских правах
* Данное уведомление о разрешении
* Приведенное ниже заявление об отказе от ответственности

#### 3. Авторские права

Программное обеспечение и вся связанная с ним документация защищены законами об авторских правах. **SA-MP Programming Community** сохраняет за собой оригинальные авторские права на программное обеспечение.

#### 4. Отказ от гарантий и ограничение ответственности

ПРОГРАММНОЕ ОБЕСПЕЧЕНИЕ ПРЕДОСТАВЛЯЕТСЯ "КАК ЕСТЬ", БЕЗ КАКИХ-ЛИБО ГАРАНТИЙ, ЯВНЫХ ИЛИ ПОДРАЗУМЕВАЕМЫХ, ВКЛЮЧАЯ, НО НЕ ОГРАНИЧИВАЯСЬ ГАРАНТИЯМИ ТОВАРНОЙ ПРИГОДНОСТИ, ПРИГОДНОСТИ ДЛЯ КОНКРЕТНОЙ ЦЕЛИ И НЕНАРУШЕНИЯ ПРАВ.

НИ ПРИ КАКИХ ОБСТОЯТЕЛЬСТВАХ АВТОРЫ ИЛИ ПРАВООБЛАДАТЕЛИ НЕ НЕСУТ ОТВЕТСТВЕННОСТИ ЗА ЛЮБЫЕ ПРЕТЕНЗИИ, УБЫТКИ ИЛИ ИНУЮ ОТВЕТСТВЕННОСТЬ, БУДЬ ТО В СИЛУ ДОГОВОРА, ДЕЛИКТА ИЛИ ИНЫМ ОБРАЗОМ, ВОЗНИКАЮЩИЕ ИЗ, ИЗ-ЗА ИЛИ В СВЯЗИ С ПРОГРАММНЫМ ОБЕСПЕЧЕНИЕМ ИЛИ ИСПОЛЬЗОВАНИЕМ ИЛИ ИНЫМИ ДЕЙСТВИЯМИ С ПРОГРАММНЫМ ОБЕСПЕЧЕНИЕМ.

---

Для подробной информации о лицензии MIT посетите: https://opensource.org/licenses/MIT