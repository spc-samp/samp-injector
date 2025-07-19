# SA-MP Injector PowerShell

![License](https://img.shields.io/badge/License-MIT-yellow.svg?style=flat)
![PowerShell](https://img.shields.io/badge/PowerShell-5.1%2B-blue.svg?style=flat&logo=powershell)
![Platform](https://img.shields.io/badge/Platform-Windows-0078D6.svg?style=flat&logo=windows)
[![SA-MP | OMP](https://img.shields.io/badge/Support-SA--MP%20%7C%20OMP-yellow)](https://github.com/spc-samp/samp-injector)
![Code Quality](https://img.shields.io/badge/Code%20Quality-High-brightgreen.svg?style=flat)

El **SA-MP Injector PowerShell** es más que un script de **inyección de DLL**. Representa una **biblioteca de funciones y clases de PowerShell** desarrollada para ofrecer una solución robusta y completa para la inicialización programática del juego **Grand Theft Auto: San Andreas** (**GTA:SA**) junto con sus clientes multijugador, específicamente **SA-MP (San Andreas Multiplayer)** y **OMP (Open Multiplayer)**. Su propósito primordial es simplificar el proceso de lanzamiento del juego, eliminando la complejidad inherente a la manipulación directa de procesos del sistema operativo y al paso de argumentos de línea de comandos.

Desarrollada para ofrecer la máxima flexibilidad y fácil integración, esta biblioteca permite que los desarrolladores la incorporen directamente en sus **proyectos y scripts de PowerShell**. No solo orquesta la **inyección fundamental de las DLLs** del cliente multijugador (`samp.dll` o `omp-client.dll`), sino que también gestiona de forma inteligente todos los parámetros esenciales de conexión (**nickname**, **dirección IP**, **puerto** y **contraseña**), simulando una inicialización nativa a través de los recursos intrínsecos de la **Windows API**, a los que se accede directamente vía **PowerShell**.

## Idiomas

- Português: [README](../../)
- Deutsch: [README](../Deutsch/README.md)
- English: [README](../English/README.md)
- Français: [README](../Francais/README.md)
- Italiano: [README](../Italiano/README.md)
- Polski: [README](../Polski/README.md)
- Русский: [README](../Русский/README.md)
- Svenska: [README](../Svenska/README.md)
- Türkçe: [README](../Turkce/README.md)

## Índice

- [SA-MP Injector PowerShell](#sa-mp-injector-powershell)
  - [Idiomas](#idiomas)
  - [Índice](#índice)
  - [Conceptos Fundamentales y Motivación](#conceptos-fundamentales-y-motivación)
    - [¿Por qué Inyectar DLLs?](#por-qué-inyectar-dlls)
    - [SA-MP y OMP: Distinciones y Similitudes](#sa-mp-y-omp-distinciones-y-similitudes)
    - [Inyección de DLLs en PowerShell: Un Enfoque Directo con WinAPI](#inyección-de-dlls-en-powershell-un-enfoque-directo-con-winapi)
  - [Arquitectura Interna de la Biblioteca: Una Inmersión Profunda](#arquitectura-interna-de-la-biblioteca-una-inmersión-profunda)
    - [`Constants.ps1`](#constantsps1)
    - [`CustomTypes.ps1`](#customtypesps1)
    - [`StringUtils.ps1`](#stringutilsps1)
    - [`ErrorUtils.ps1`](#errorutilsps1)
    - [`Process.ps1`](#processps1)
    - [`InjectorCore.ps1`](#injectorcoreps1)
    - [`Injector.ps1`](#injectorps1)
    - [`Cleanup.ps1`](#cleanupps1)
  - [Ejemplos Completos de Uso](#ejemplos-completos-de-uso)
    - [1. Preparación del Entorno de Desarrollo](#1-preparación-del-entorno-de-desarrollo)
    - [2. Escenario Básico: Conectando a un Servidor SA-MP](#2-escenario-básico-conectando-a-un-servidor-sa-mp)
    - [3. Escenario Avanzado: Conectando a un Servidor OMP](#3-escenario-avanzado-conectando-a-un-servidor-omp)
    - [4. Ejecución desde un Script Padre](#4-ejecución-desde-un-script-padre)
  - [Manejo de Errores Comunes y Mensajes](#manejo-de-errores-comunes-y-mensajes)
    - [1. Tipo de Inyección Inválido](#1-tipo-de-inyección-inválido)
    - [2. Puerto del Servidor Inválido (Formato o Rango)](#2-puerto-del-servidor-inválido-formato-o-rango)
      - [2.1. Formato de Puerto No Numérico](#21-formato-de-puerto-no-numérico)
      - [2.2. Puerto Fuera del Rango Válido](#22-puerto-fuera-del-rango-válido)
    - [3. Nickname Inválido (Vacío o Demasiado Largo)](#3-nickname-inválido-vacío-o-demasiado-largo)
      - [3.1. Nickname Vacío](#31-nickname-vacío)
      - [3.2. Nickname Demasiado Largo](#32-nickname-demasiado-largo)
    - [4. Archivos del Juego o DLL No Encontrados](#4-archivos-del-juego-o-dll-no-encontrados)
      - [4.1. Ejecutable del Juego (`gta_sa.exe`) No Encontrado](#41-ejecutable-del-juego-gta_saexe-no-encontrado)
      - [4.2. Biblioteca SA-MP (`samp.dll`) No Encontrada](#42-biblioteca-sa-mp-sampdll-no-encontrada)
      - [4.3. Biblioteca OMP (`omp-client.dll`) No Encontrada (solo para inyección OMP)](#43-biblioteca-omp-omp-clientdll-no-encontrada-solo-para-inyección-omp)
    - [5. Fallo en la Creación del Proceso del Juego](#5-fallo-en-la-creación-del-proceso-del-juego)
    - [6. Fallo en la Asignación de Memoria en el Proceso de Destino](#6-fallo-en-la-asignación-de-memoria-en-el-proceso-de-destino)
    - [7. Fallo al Escribir la Ruta de la DLL en la Memoria del Proceso](#7-fallo-al-escribir-la-ruta-de-la-dll-en-la-memoria-del-proceso)
    - [8. Fallo al Encontrar Funciones Esenciales del Sistema](#8-fallo-al-encontrar-funciones-esenciales-del-sistema)
      - [8.1. `kernel32.dll` No Encontrado](#81-kernel32dll-no-encontrado)
      - [8.2. `LoadLibraryA` No Encontrado](#82-loadlibrarya-no-encontrado)
    - [9. Fallo al Crear Hilo Remoto para Inyección](#9-fallo-al-crear-hilo-remoto-para-inyección)
    - [10. Timeout o Fallo en la Finalización de la Inyección](#10-timeout-o-fallo-en-la-finalización-de-la-inyección)
    - [11. Fallo al Reanudar el Hilo del Proceso del Juego](#11-fallo-al-reanudar-el-hilo-del-proceso-del-juego)
  - [Licencia](#licencia)
    - [Términos y Condiciones de Uso](#términos-y-condiciones-de-uso)
      - [1. Permisos Otorgados](#1-permisos-otorgados)
      - [2. Condiciones Obligatorias](#2-condiciones-obligatorias)
      - [3. Derechos de Autor](#3-derechos-de-autor)
      - [4. Exención de Garantías y Limitación de Responsabilidad](#4-exención-de-garantías-y-limitación-de-responsabilidad)

## Conceptos Fundamentales y Motivación

### ¿Por qué Inyectar DLLs?

> [!NOTE]
> La **inyección de DLL (Dynamic Link Library)** es un método utilizado en sistemas operativos **Microsoft Windows** que permite la ejecución de código dentro del espacio de memoria de otro proceso en ejecución. Es una técnica poderosa con diversas aplicaciones legítimas, desde la depuración y monitoreo de programas hasta la modificación del comportamiento de aplicaciones para extender sus funcionalidades.

En el contexto de juegos como **GTA San Andreas**, que no fueron originalmente desarrollados con funcionalidad multijugador integrada, la **inyección de DLLs** es la base para la existencia de clientes multijugador como **SA-MP** y **OMP**. Estos clientes se implementan como **DLLs** que, una vez inyectadas en el proceso de `gta_sa.exe`, asumen el control, interceptan funciones del juego y establecen comunicación con servidores multijugador.

En lugar de depender de un lanzador externo o de la modificación directa del ejecutable del juego, la **inyección de DLL** permite una inicialización más flexible y programable, especialmente útil en entornos donde se desea automatizar el proceso de conexión a servidores específicos con configuraciones predefinidas.

### SA-MP y OMP: Distinciones y Similitudes

**SA-MP** y **OMP** son las dos principales plataformas multijugador para **GTA San Andreas**. Ambas funcionan como modificaciones del juego base, transformándolo en un entorno online masivamente multijugador.

- **SA-MP (San Andreas Multiplayer)**: El cliente original y más consolidado, ampliamente utilizado durante muchos años. Su arquitectura requiere la `samp.dll` para operar.
- **OMP (Open Multiplayer)**: Un proyecto de código abierto, generalmente visto como un sucesor o alternativa más moderna a **SA-MP**, que ofrece mejoras de rendimiento, estabilidad y funcionalidades adicionales. Requiere la `omp-client.dll`.

Aunque operan de forma similar (**inyectando una DLL** en el proceso de **GTA:SA**), la biblioteca **SA-MP Injector PowerShell** ha sido cuidadosamente desarrollada para soportar **ambas DLLs**, reconociendo sus distinciones de nombres de archivo y permitiendo que el desarrollador elija el cliente multijugador deseado a través de un parámetro de configuración. Esto asegura que la biblioteca pueda ser utilizada con la vasta gama de servidores y proyectos basados en cualquiera de las plataformas.

### Inyección de DLLs en PowerShell: Un Enfoque Directo con WinAPI

PowerShell es un lenguaje de scripting potente para la automatización en Windows, pero la manipulación de procesos y la inyección de DLLs a un nivel tan bajo del sistema no es su función principal. Para lograr este objetivo, la biblioteca **SA-MP Injector PowerShell** hace un uso extensivo del comando `Add-Type` para invocar directamente las funciones de la **Windows API (WinAPI)**.

`Add-Type` permite definir y compilar código C# (u otros lenguajes .NET) en tiempo de ejecución en el entorno de PowerShell. Este código C# actúa como un "puente" hacia las funciones nativas de la WinAPI (`DllImport`), posibilitando operaciones como:

- **`CreateProcessA`**: Para iniciar el proceso de GTA:SA.
- **`VirtualAllocEx`**: Para asignar memoria dentro del proceso remoto.
- **`WriteProcessMemory`**: Para copiar la ruta de la DLL a la memoria asignada.
- **`GetModuleHandleA` y `GetProcAddress`**: Para obtener la dirección de la función `LoadLibraryA` en `kernel32.dll`.
- **`CreateRemoteThread`**: Para crear un hilo en el proceso remoto que ejecuta `LoadLibraryA`, cargando efectivamente la DLL.
- **`WaitForSingleObject` y `GetExitCodeThread`**: Para monitorear el éxito de la inyección.
- **`ResumeThread`**: Para reactivar el proceso del juego después de la inyección.
- **`CloseHandle`**: Para cerrar handles de recursos del sistema y evitar fugas.
- **`MessageBoxW`**: Para mostrar mensajes de error informativos al usuario.

Este enfoque directo con la WinAPI permite que PowerShell realice las mismas operaciones de bajo nivel que una aplicación compilada en **C++** haría, con la comodidad de un entorno de script.

## Arquitectura Interna de la Biblioteca: Una Inmersión Profunda

La biblioteca **SA-MP Injector PowerShell** adopta un enfoque modular para gestionar la complejidad del proceso de inyección. Cada script es un módulo especializado, responsable de una porción específica de la funcionalidad general, promoviendo la claridad del código, la mantenibilidad y la expansibilidad.

### `Constants.ps1`

Este script es la base de todas las configuraciones fijas de la biblioteca. Define una tabla hash global (`$global:CONSTANTS`) que almacena todos los literales y valores numéricos utilizados, como límites de puerto, nombres de archivos DLL, referencias a APIs del sistema y flags para operaciones como la creación de procesos y la asignación de memoria.

```powershell
$global:CONSTANTS = @{
    # Port validation limits
    MIN_PORT = 1
    MAX_PORT = 65535
    
    # Nickname constraints
    MAX_NICKNAME_LENGTH = 20
    
    # Required file names
    SAMP_DLL_NAME = "samp.dll"
    OMP_DLL_NAME = "omp-client.dll"
    GAME_EXE_NAME = "gta_sa.exe"
    
    # System API references
    KERNEL32_DLL = "kernel32.dll"
    USER32_DLL = "user32.dll" # Utilizado para MessageBoxW
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
    DLL_INJECTION_TIMEOUT_MS = 10000 # 10 segundos
    
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
> El uso de una tabla hash global para constantes es una práctica común en scripts de PowerShell. Centraliza las configuraciones y evita "números mágicos" y cadenas repetidas, haciendo el código más legible y fácil de mantener. Los valores de los flags (`0x...`) corresponden a los valores decimales de las constantes definidas en la Windows API.

### `CustomTypes.ps1`

Este script es fundamental para la interacción con la Windows API. Define tipos de C# en tiempo de ejecución usando `Add-Type`, incluyendo:

- **`Inject_Type` enum**: Para categorizar el tipo de inyección (SAMP u OMP), mejorando la seguridad de tipo.
- **`WinAPI` class**: Una clase estática que importa y expone las funciones de la Windows API necesarias para la inyección. Cada método en esta clase corresponde a una función de la API (`DllImport`), con la firma y el conjunto de caracteres (`CharSet`) correctos.
- **`Startup_Info` struct y `Process_Information` struct**: Estructuras de datos de C# que replican las estructuras `STARTUPINFO` y `PROCESS_INFORMATION` usadas por la función `CreateProcessA` de la Windows API.
- **`Process_Info` class**: Una clase simple en C# que actúa como un contenedor para los handles del proceso y del hilo devueltos tras la creación exitosa de un proceso, facilitando el transporte y manejo de estos handles dentro del entorno de PowerShell.

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
        using System.Text; // Necesario para Marshal.GetLastWin32Error
        
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
            
            // Estructura C# para STARTUPINFO
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
            
            // Estructura C# para PROCESS_INFORMATION
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
        
        // Clase auxiliar para transportar handles de proceso e hilo
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
> La inyección de DLLs de 32 bits (como `samp.dll` y `omp-client.dll`) en un proceso de 32 bits (`gta_sa.exe`) **requiere que el entorno de PowerShell también sea de 32 bits**. El **SA-MP Injector PowerShell** maneja esto automáticamente reiniciándose en un shell de PowerShell x86 si detecta que se está ejecutando en un entorno x64. Esto es crucial para garantizar la compatibilidad del tamaño de los punteros y el correcto funcionamiento de la inyección.
>
> La directiva `if (-not ([System.Management.Automation.PSTypeName]'TypeName').Type)` garantiza que los tipos de C# se agreguen al entorno de PowerShell solo una vez, evitando errores de redefinición si el script se ejecuta varias veces en la misma sesión.

### `StringUtils.ps1`

Este módulo proporciona una función de utilidad esencial para la manipulación de cadenas, específicamente para manejar las codificaciones de caracteres necesarias al interactuar con la Windows API legada (funciones "A" de char*).

```powershell
function Convert_Wide_To_Local_8Bit {
    param([Parameter(Mandatory = $false)] [AllowEmptyString()] [string]$wide_string)
    
    if ([string]::IsNullOrEmpty($wide_string)) {
        return [string]::Empty
    }

    try {
        # Obtiene la página de códigos ANSI local del sistema
        $ansi_code_page = [System.Globalization.CultureInfo]::CurrentCulture.TextInfo.ANSICodePage
        $encoding = [System.Text.Encoding]::GetEncoding($ansi_code_page)
        
        # Convierte la cadena Unicode (wide) a bytes en la codificación ANSI local
        $bytes = $encoding.GetBytes($wide_string)

        # Convierte los bytes de vuelta a una cadena usando la misma codificación ANSI
        # Esto garantiza que la cadena sea compatible con APIs que esperan codificación de 8 bits (ANSI)
        return $encoding.GetString($bytes)
    }
    catch {
        # En caso de error en la conversión (ej., caracteres que no se pueden mapear),
        # devuelve la cadena original como un fallback, aunque podría causar problemas
        # si contiene caracteres no soportados por las APIs ANSI.
        return $wide_string
    }
}
```

> [!IMPORTANT]
> La función `Convert_Wide_To_Local_8Bit` es crucial porque muchas funciones de la Windows API con sufijo "A" (`CreateProcessA`, `LoadLibraryA`, `GetModuleHandleA`, `GetProcAddress`) esperan cadenas codificadas en ANSI (8 bits), que dependen de la página de códigos del sistema local. Por defecto, las cadenas en PowerShell son Unicode. Esta función realiza la conversión necesaria. Si el nombre de archivo o un argumento de línea de comandos contiene caracteres fuera de la página de códigos ANSI del sistema, la conversión puede resultar en caracteres incorrectos o pérdida de datos. Para este proyecto, que busca interactuar con programas antiguos, este enfoque ANSI es típicamente suficiente y necesario.

### `ErrorUtils.ps1`

Este módulo es responsable de proporcionar retroalimentación clara al usuario en caso de fallo. Centraliza la lógica para obtener mensajes de error del sistema y mostrar cuadros de diálogo estándar de Windows.

```powershell
function Get_System_Error_Message {
    param([Parameter(Mandatory = $true)][int]$error_code)
    
    try {
        # Usa Win32Exception para obtener el mensaje de error formateado por el sistema
        $exception = New-Object System.ComponentModel.Win32Exception($error_code)
        
        return $exception.Message
    }
    catch {
        # Fallback para mensaje de error desconocido
        return "Unknown error (Code: $error_code)"
    }
}

function Show_Error {
    param([Parameter(Mandatory = $true)][string]$message, [Parameter(Mandatory = $true)][Inject_Type]$inject_type)
    
    # Determina el título del cuadro de diálogo según el tipo de inyección
    $title = if ($inject_type -eq [Inject_Type]::SAMP) {
        $global:CONSTANTS.ERROR_TITLE_SAMP
    }
    else {
        $global:CONSTANTS.ERROR_TITLE_OMP
    }
    
    try {
        # Combina flags para MessageBoxW (OK, Icono de Error, AlwaysOnTop)
        $message_box_flags = $global:CONSTANTS.MB_OK -bor $global:CONSTANTS.MB_ICONERROR -bor $global:CONSTANTS.MB_TOPMOST
        
        # Llama a la función MessageBoxW importada vía Add-Type
        [void][WinAPI]::MessageBoxW([System.IntPtr]::Zero, $message, $title, $message_box_flags)
    }
    catch {
        # En caso de fallo al mostrar el MessageBox (ej., en entornos sin UI), escribe en la consola
        Write-Host "[$title] $message" -ForegroundColor Red
    }
}
```

> [!NOTE]
> `Get_System_Error_Message` utiliza `System.ComponentModel.Win32Exception` de .NET para convertir un código de error numérico de la Windows API (`GetLastError()`) en una descripción de texto legible por el usuario, que puede estar localizada en el idioma del sistema operativo.
>
> `Show_Error` usa la función `MessageBoxW` importada de `user32.dll` a través de `Add-Type` (`CustomTypes.ps1`) para mostrar un cuadro de diálogo informativo. Los flags como `MB_OK` y `MB_ICONERROR` se importan de las constantes de la WinAPI.

### `Process.ps1`

Este es el módulo principal responsable de la interacción directa con las APIs de bajo nivel de Windows para manipular procesos. Encapsula las operaciones cruciales de creación de procesos e inyección de DLL, manejando handles, memoria e hilos.

```powershell
class Process {
    # Libera los handles de proceso e hilo, previniendo fugas de recursos
    [void] Close_Process_Info([Process_Info]$process_info) {
        if ($null -ne $process_info) {
            # Cierra el handle del proceso si es válido
            if ($process_info.ProcessHandle -ne [System.IntPtr]::Zero -and $process_info.ProcessHandle -ne [System.IntPtr]::new(-1)) {
                [void][WinAPI]::CloseHandle($process_info.ProcessHandle)
                $process_info.ProcessHandle = [System.IntPtr]::Zero # Marca como cerrado
            }

            # Cierra el handle del hilo si es válido
            if ($process_info.ThreadHandle -ne [System.IntPtr]::Zero -and $process_info.ThreadHandle -ne [System.IntPtr]::new(-1)) {
                [void][WinAPI]::CloseHandle($process_info.ThreadHandle)
                $process_info.ThreadHandle = [System.IntPtr]::Zero # Marca como cerrado
            }
        }
    }

    # Crea el proceso del juego GTA:SA en estado suspendido
    [Process_Info] Create_Game_Process([string]$game_path, [string]$command_args, [string]$working_dir) {
        $startup_info = New-Object WinAPI+Startup_Info
        # Define el tamaño de la estructura, crucial para las APIs de Windows
        $startup_info.cb = [System.Runtime.InteropServices.Marshal]::SizeOf($startup_info)
        
        $process_information = New-Object WinAPI+Process_Information
        
        $command_line_bytes = $null

        if (-not [string]::IsNullOrEmpty($command_args)) {
            # Convierte los argumentos de la línea de comandos a un array de bytes ANSI con terminador nulo
            $command_line_bytes = [System.Text.Encoding]::Default.GetBytes($command_args + "`0")
        }
        
        # Define el directorio de trabajo, null si está vacío
        $current_directory = if ([string]::IsNullOrEmpty($working_dir)) {
            $null
        }
        else {
            $working_dir
        }
        
        # Llama a la función CreateProcessA de la Windows API
        $success = [WinAPI]::CreateProcessA($game_path, $command_line_bytes, [System.IntPtr]::Zero, [System.IntPtr]::Zero, $false, $global:CONSTANTS.PROCESS_CREATION_FLAGS, 
            [System.IntPtr]::Zero, $current_directory, [ref]$startup_info, [ref]$process_information)
        
        if (-not $success) {
            # En caso de fallo, obtiene el último error del sistema y lo muestra
            $error_code = [System.Runtime.InteropServices.Marshal]::GetLastWin32Error()
            $error_message = Get_System_Error_Message $error_code
            Show_Error "Failed to create game process. Ensure 'gta_sa.exe' is not running and you have sufficient permissions to execute the file. System Error: $error_message" ([Inject_Type]::SAMP)

            return $null # Devuelve null en caso de fallo
        }
        
        # Devuelve un objeto Process_Info conteniendo los handles del proceso y del hilo
        $result = New-Object Process_Info
        $result.ProcessHandle = $process_information.hProcess
        $result.ThreadHandle = $process_information.hThread
        
        return $result
    }
    
    # Inyecta una DLL en el proceso remoto
    [bool] Inject_DLL([IntPtr]$process_handle, [string]$dll_path, [ref]$error_message) {
        if ($process_handle -eq [System.IntPtr]::Zero) {
            $error_message.Value = "Invalid process handle provided for DLL injection."

            return $false
        }
        
        if ([string]::IsNullOrEmpty($dll_path)) {
            $error_message.Value = "DLL path cannot be empty."

            return $false
        }
        
        # Convierte la ruta de la DLL a bytes ASCII (ANSI 8-bit) con terminador nulo
        $dll_path_bytes = [System.Text.Encoding]::ASCII.GetBytes($dll_path + "`0")
        $dll_path_size = $dll_path_bytes.Length
        
        # Asigna memoria en el proceso remoto para la ruta de la DLL
        $remote_memory = [WinAPI]::VirtualAllocEx($process_handle, [System.IntPtr]::Zero, $dll_path_size, $global:CONSTANTS.MEMORY_ALLOCATION_TYPE, $global:CONSTANTS.MEMORY_PROTECTION)
        
        if ($remote_memory -eq [System.IntPtr]::Zero) {
            $error_code = [System.Runtime.InteropServices.Marshal]::GetLastWin32Error()
            $error_message.Value = "Failed to allocate memory in the target process. This might be due to insufficient permissions or process protection mechanisms. System Error: $(Get_System_Error_Message $error_code)"

            return $false
        }
        
        # Usa un bloque try/finally para asegurar que la memoria remota sea liberada
        try {
            $bytes_written = [System.IntPtr]::Zero
            # Escribe la ruta de la DLL en la memoria remota
            $write_success = [WinAPI]::WriteProcessMemory($process_handle, $remote_memory, $dll_path_bytes, $dll_path_size, [ref]$bytes_written)
            
            if (-not $write_success) {
                $error_code = [System.Runtime.InteropServices.Marshal]::GetLastWin32Error()
                $error_message.Value = "Failed to write DLL path to the target process memory. Verify process permissions and ensure the DLL path is accessible. System Error: $(Get_System_Error_Message $error_code)"
                
                return $false
            }
            
            # Obtiene el handle para kernel32.dll (que está cargado en todos los procesos)
            $kernel32_handle = [WinAPI]::GetModuleHandleA($global:CONSTANTS.KERNEL32_DLL)

            if ($kernel32_handle -eq [System.IntPtr]::Zero) {
                $error_code = [System.Runtime.InteropServices.Marshal]::GetLastWin32Error()
                $error_message.Value = "Failed to obtain a handle to kernel32.dll. This is an essential system library and this error indicates a severe system issue. System Error: $(Get_System_Error_Message $error_code)"
                
                return $false
            }
            
            # Obtiene la dirección de la función LoadLibraryA en kernel32.dll.
            # Esta dirección es consistente entre procesos en el mismo SO.
            $load_library_address = [WinAPI]::GetProcAddress($kernel32_handle, $global:CONSTANTS.LOAD_LIBRARY_FUNC)

            if ($load_library_address -eq [System.IntPtr]::Zero) {
                $error_code = [System.Runtime.InteropServices.Marshal]::GetLastWin32Error()
                $error_message.Value = "Failed to find the address of the LoadLibraryA function in kernel32.dll. This is critical for injecting the DLL. System Error: $(Get_System_Error_Message $error_code)"
                
                return $false
            }
            
            $thread_id = [System.IntPtr]::Zero
            # Crea un hilo remoto en el proceso de destino para ejecutar LoadLibraryA
            $remote_thread_handle = [WinAPI]::CreateRemoteThread($process_handle, [System.IntPtr]::Zero, 0, $load_library_address, $remote_memory, 0, [ref]$thread_id)
            
            if ($remote_thread_handle -eq [System.IntPtr]::Zero) {
                $error_code = [System.Runtime.InteropServices.Marshal]::GetLastWin32Error()
                $error_message.Value = "Failed to create a remote thread in the target process to execute the DLL injection. This could be due to security restrictions or process state. System Error: $(Get_System_Error_Message $error_code)"
                
                return $false
            }
            
            # Usa un bloque try/finally para asegurar que el handle del hilo remoto sea cerrado
            try {
                # Espera a que el hilo remoto (inyección de DLL) se complete o alcance un timeout
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
                # Obtiene el código de salida del hilo remoto. Para LoadLibraryA, 0 significa fallo.
                $get_exit_code_success = [WinAPI]::GetExitCodeThread($remote_thread_handle, [ref]$exit_code)
                
                if (-not $get_exit_code_success -or $exit_code -eq 0) {
                    $error_code = [System.Runtime.InteropServices.Marshal]::GetLastWin32Error()
                    $error_message.Value = "DLL injection failed or returned an error. The LoadLibrary call may have failed in the target process. Exit Code: $exit_code. System Error: $(Get_System_Error_Message $error_code)"

                    return $false
                }
                
                return $true # Inyección exitosa
            }
            finally {
                # Asegura que el handle del hilo remoto sea cerrado
                [void][WinAPI]::CloseHandle($remote_thread_handle)
            }
        }
        finally {
            # Asegura que la memoria asignada remotamente sea liberada
            # 0 para dwSize en MEM_RELEASE libera toda la región asignada por VirtualAllocEx
            [void][WinAPI]::VirtualFreeEx($process_handle, $remote_memory, 0, $global:CONSTANTS.MEMORY_FREE_TYPE)
        }
    }
}
```

> [!NOTE]
> La clase `Process` usa `[System.IntPtr]` para representar handles de Windows. Es importante notar el uso extensivo de `try/finally` para asegurar que los handles (`ProcessHandle`, `ThreadHandle`, `remote_memory`, `remote_thread_handle`) se cierren y la memoria se libere correctamente, incluso en caso de errores. Esta es la forma en PowerShell de implementar el principio **RAII** (Resource Acquisition Is Initialization), aunque menos integrada en la sintaxis del lenguaje.

### `InjectorCore.ps1`

Esta es la clase orquestadora que une todas las funcionalidades de los módulos anteriores. Coordina la validación, la construcción de argumentos de línea de comandos, la creación del proceso y las llamadas de inyección de DLL.

```powershell
class Injector_Core {
    # Función principal que orquesta la inicialización e inyección del juego
    [bool] Initialize_Game([Inject_Type]$inject_type, [string]$folder, [string]$nickname, [string]$ip, [string]$port, [string]$password) {
        # Construye las rutas completas para los archivos esenciales
        $game_path = Join-Path -Path $folder -ChildPath $global:CONSTANTS.GAME_EXE_NAME
        $samp_dll_path = Join-Path -Path $folder -ChildPath $global:CONSTANTS.SAMP_DLL_NAME
        $omp_dll_path = Join-Path -Path $folder -ChildPath $global:CONSTANTS.OMP_DLL_NAME
        
        $validation_error = [string]::Empty # Variable para capturar mensajes de error de validación
        
        # 1. Validación de Archivos
        if (-not (Validate_Files $game_path $samp_dll_path $omp_dll_path $inject_type)) {
            # El error ya fue mostrado por la función de validación
            return $false
        }

        # 2. Validación de Puerto
        if (-not (Validate_Port $port ([ref]$validation_error))) {
            Show_Error $validation_error $inject_type
            return $false
        }
        
        # 3. Validación de Nickname
        if (-not (Validate_Nickname $nickname ([ref]$validation_error))) {
            Show_Error $validation_error $inject_type
            return $false
        }
        
        # 4. Conversión de Cadenas a Codificación ANSI/8-bit (necesario para APIs legadas)
        $converted_nickname = Convert_Wide_To_Local_8Bit $nickname
        $converted_ip = Convert_Wide_To_Local_8Bit $ip
        $converted_port = Convert_Wide_To_Local_8Bit $port
        $converted_password = Convert_Wide_To_Local_8Bit $password
        $converted_game_path = Convert_Wide_To_Local_8Bit $game_path
        $converted_folder = Convert_Wide_To_Local_8Bit $folder
        $converted_samp_dll_path = Convert_Wide_To_Local_8Bit $samp_dll_path
        $converted_omp_dll_path = Convert_Wide_To_Local_8Bit $omp_dll_path
        
        # 5. Construcción de los Argumentos de la Línea de Comandos
        $command_arguments = $this.Build_Command_Args($converted_nickname, $converted_ip, $converted_port, $converted_password)
        
        $process_manager = New-Object Process # Instancia la clase Process
        $process_info = $null # Variable para almacenar información del proceso creado
        
        # Usa un bloque try/finally para asegurar que los handles del proceso sean cerrados
        try {
            # 6. Creación del Proceso del Juego (Suspendido)
            $process_info = $process_manager.Create_Game_Process($converted_game_path, $command_arguments, $converted_folder)
            
            if ($null -eq $process_info) {
                # El error ya fue mostrado por la función de creación de proceso
                return $false
            }

            $injection_error = [string]::Empty # Variable para capturar mensajes de error de inyección
            
            # 7. Inyección de la samp.dll
            if (-not $process_manager.Inject_DLL($process_info.ProcessHandle, $converted_samp_dll_path, ([ref]$injection_error))) {
                Show_Error "Failed to inject samp.dll: $injection_error" $inject_type
                return $false
            }
            
            # 8. Inyección condicional de la omp-client.dll (solo si el tipo de inyección es OMP)
            if ($inject_type -eq [Inject_Type]::OMP) {
                if (-not $process_manager.Inject_DLL($process_info.ProcessHandle, $converted_omp_dll_path, ([ref]$injection_error))) {
                    Show_Error "Failed to inject omp-client.dll: $injection_error" $inject_type
                    return $false
                }
            }
            
            # 9. Reanudar el Proceso del Juego
            # El proceso fue creado en estado suspendido para permitir la inyección.
            # Ahora que las DLLs han sido inyectadas, puede ser reanudado.
            $resume_result = [WinAPI]::ResumeThread($process_info.ThreadHandle)

            if ($resume_result -eq $global:CONSTANTS.THREAD_RESUME_ERROR) {
                $error_code = [System.Runtime.InteropServices.Marshal]::GetLastWin32Error()
                $error_message = Get_System_Error_Message $error_code
                Show_Error "Failed to resume the game process thread: $error_message" $inject_type

                return $false
            }
            
            return $true # ¡Éxito en todos los pasos!
        }
        finally {
            # Asegura que los handles del proceso sean cerrados al final,
            # independientemente del éxito o fallo.
            if ($null -ne $process_info) {
                $process_manager.Close_Process_Info($process_info)
            }
        }
    }
    
    # Construye la cadena de argumentos de la línea de comandos para el ejecutable del juego
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
> Para **OMP**, la inyección involucra la `omp-client.dll` *además* de la `samp.dll`. Esto está de acuerdo con la forma en que **OMP** generalmente funciona, ya que puede usar `samp.dll` como base y extender funcionalidades con `omp-client.dll`. Es crucial que **ambas DLLs** estén presentes y funcionales en el directorio del juego para que la inyección OMP sea exitosa. Si una falla, el juego podría no inicializarse correctamente o el cliente multijugador podría no cargarse.
>
> Tenga en cuenta que, como PowerShell no tiene un `std::optional` o una garantía de **RAII** nativa de la misma manera que C++, el código usa un bloque `try/finally` explícito en la función `Initialize_Game` para asegurar que `Close_Process_Info` sea llamado y los handles se liberen, incluso si ocurre un error. Esta es una buena práctica para la limpieza de recursos en PowerShell.

### `Injector.ps1`

Este es el script de entrada principal de la biblioteca. Maneja la carga de los otros módulos, la validación del entorno de PowerShell (verificando si es x86 para compatibilidad de inyección) y la inicialización de la clase `Injector_Core`. Es el script que el usuario final ejecutará.

```powershell
param([Parameter(Mandatory = $true, Position = 0)][ValidateNotNullOrEmpty()][string]$inject_type,
    [Parameter(Mandatory = $true, Position = 1)][ValidateNotNullOrEmpty()][string]$folder,
    [Parameter(Mandatory = $true, Position = 2)][ValidateNotNullOrEmpty()][string]$nickname,
    [Parameter(Mandatory = $true, Position = 3)][ValidateNotNullOrEmpty()][string]$ip,
    [Parameter(Mandatory = $true, Position = 4)][ValidateNotNullOrEmpty()][string]$port,
    [Parameter(Position = 5)][AllowEmptyString()][string]$password = "",
    [switch]$restarted_x86) # Flag interna para indicar que el script ya ha sido reiniciado en x86

$ErrorActionPreference = 'Stop' # Asegura que los errores que no terminan se comporten como errores que terminan
# Esto hace que los bloques catch capturen más errores y previene que el script continúe inesperadamente.

# Obtiene la ruta completa del script actual, esencial para cargar los módulos auxiliares
$script_path = $MyInvocation.MyCommand.Path

if ([string]::IsNullOrEmpty($script_path)) {
    # En casos donde el script es invocado de forma especial (ej. desde pipeline), $MyInvocation.MyCommand.Path puede estar vacío
    $script_path = Join-Path -Path (Get-Location) -ChildPath $MyInvocation.MyCommand.Name
}

$script_directory = Split-Path -Parent $script_path # Directorio base de la biblioteca
$exit_code = 1 # Código de salida por defecto (fallo)

try {
    # Carga todos los módulos de la biblioteca (constantes, tipos personalizados, utilidades, etc.)
    . (Join-Path -Path $script_directory -ChildPath "Constants.ps1")
    . (Join-Path -Path $script_directory -ChildPath "CustomTypes.ps1")
    . (Join-Path -Path $script_directory -ChildPath "StringUtils.ps1")
    . (Join-Path -Path $script_directory -ChildPath "ErrorUtils.ps1")
    . (Join-Path -Path $script_directory -ChildPath "Validation.ps1")
    . (Join-Path -Path $script_directory -ChildPath "Process.ps1")
    . (Join-Path -Path $script_directory -ChildPath "InjectorCore.ps1")

    # Define la función de interfaz principal para el usuario.
    # Es un wrapper para la clase Injector_Core.
    function Initialize_Game {
        param([string]$inject_type, [string]$folder, [string]$nickname, [string]$ip, [string]$port, [string]$password = "")

        # Verifica si el entorno de PowerShell es x64 y si aún no ha sido reiniciado en x86
        if ([IntPtr]::Size -eq 8 -and -not $restarted_x86) {
            Write-Host "Detected PowerShell x64 environment. Restarting on PowerShell x86 for DLL injection compatibility (32-bit)..." -ForegroundColor Yellow

            # Localiza el ejecutable de PowerShell de 32 bits
            $powershell_x86_path = Join-Path -Path $env:windir -ChildPath "SysWOW64\WindowsPowerShell\v1.0\powershell.exe"

            if (-not (Test-Path -Path $powershell_x86_path)) {
                Write-Host "Could not find powershell.exe (x86) at '$powershell_x86_path'. 32-bit DLL injection may fail." -ForegroundColor Red
                return $false
            }

            # Prepara la lista de argumentos para el nuevo proceso de PowerShell x86
            $argument_list = @("-NoProfile", "-NonInteractive", "-ExecutionPolicy", "Bypass", "-File", $script_path, $inject_type, $folder, $nickname, $ip, $port)
            
            if (-not [string]::IsNullOrEmpty($password)) {
                $argument_list += $password
            }
            # Agrega el flag para indicar que ya fue reiniciado
            $argument_list += "-restarted_x86"
            
            try {
                $process_start_info = New-Object System.Diagnostics.ProcessStartInfo
                $process_start_info.FileName = $powershell_x86_path
                # Une los argumentos en una cadena para StartInfo.Arguments
                $process_start_info.Arguments = ($argument_list | ForEach-Object { "`"$_`"" }) -join " " # Envuelve los args en comillas para manejar espacios
                $process_start_info.RedirectStandardOutput = $true # Redirige la salida del proceso hijo
                $process_start_info.RedirectStandardError = $true   # Redirige los errores del proceso hijo
                $process_start_info.UseShellExecute = $false     # No usa ShellExecute (ejecuta directamente PowerShell.exe)
                $process_start_info.CreateNoWindow = $true       # No crea una nueva ventana para el proceso hijo

                $child_process = New-Object System.Diagnostics.Process
                $child_process.StartInfo = $process_start_info
                
                # Inicia el proceso hijo y espera a que termine
                [void]$child_process.Start()
                $child_process.WaitForExit()
                
                # Captura y muestra la salida/errores del proceso hijo
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
        
        # Lógica de inicialización real, solo se alcanza si el entorno es x86 o ya ha sido reiniciado
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

        $injector_core = New-Object Injector_Core # Instancia la clase principal de inyección

        # Delega la llamada a la función Initialize_Game de la clase Injector_Core
        return $injector_core.Initialize_Game($injection_type, $folder, $nickname, $ip, $port, $password)
    }

    # Parámetros pasados a la función principal
    $initialization_parameters = @{
        inject_type = $inject_type
        folder = $folder
        nickname = $nickname
        ip = $ip
        port = $port
        password = $password
    }

    # Llamada para iniciar el proceso de inyección
    $game_initialization_result = Initialize_Game @initialization_parameters

    if ($game_initialization_result) {
        $exit_code = 0 # Éxito
    }
    else {
        $exit_code = 1 # Fallo
    }
}
catch {
    Write-Host "Critical error during execution: '$($_.Exception.Message)'" -ForegroundColor Red
    $exit_code = 1
}
finally {
    # Asegura que el script de limpieza se ejecute al final, independientemente del éxito o fallo
    try {
        . (Join-Path -Path $script_directory -ChildPath "Cleanup.ps1")
    }
    catch {
        Write-Host "Warning: Cleanup script execution failed: '$($_.Exception.Message)'" -ForegroundColor Yellow
    }
    
    exit $exit_code # Sale con el código de estado apropiado
}
```

> [!NOTE]
> Este script es el punto de entrada principal para la inyección. Es responsable de:
> - Definir los **parámetros de línea de comandos** que el usuario final usará.
> - Definir `$ErrorActionPreference = 'Stop'` para un control de errores más estricto.
> - **Cargar** todos los scripts auxiliares usando "dot-sourcing" (`. `), asegurando que sus funciones y clases estén disponibles en la sesión actual.
> - Implementar la lógica de **reinicio para el entorno x86**: Si PowerShell se está ejecutando en 64 bits, se relanza automáticamente en una instancia de 32 bits (SysWOW64) y pasa los mismos argumentos, ya que la inyección de DLLs de 32 bits es más fiable (y, en muchos casos, obligatoria) desde un proceso de 32 bits. Esta es una distinción clave de PowerShell en comparación con una aplicación C++ compilada directamente para x86.
> - Llamar a la función `Initialize_Game` para iniciar el proceso de inyección.
> - Gestionar el código de salida del script (0 para éxito, 1 para fallo).
> - Llamar al script `Cleanup.ps1` en el bloque `finally`.

### `Cleanup.ps1`

Este script es responsable de eliminar las funciones y variables globales cargadas por la biblioteca de la sesión actual de PowerShell. Esta es una buena práctica para evitar la contaminación del entorno y asegurar que las ejecuciones posteriores del script con diferentes configuraciones no encuentren estados inesperados de sesiones anteriores.

```powershell
$functions_to_remove = @(
    '*Initialize_Game*', # Usa comodín para eliminar funciones (puede tener alias)
    '*Get_System_Error_Message*',
    '*Show_Error*',
    '*Convert_Wide_To_Local_8Bit*',
    '*Validate_*', # Elimina todas las funciones que comienzan con 'Validate_'
    '*Build_Command_Args*'
)

# Itera sobre los patrones y elimina las funciones
foreach ($pattern in $functions_to_remove) {
    Get-Command -CommandType Function -Name $pattern -ErrorAction SilentlyContinue | ForEach-Object {
        try {
            Remove-Item -Path "Function:$($_.Name)" -Force -ErrorAction SilentlyContinue
        }
        catch {} # Ignora errores si la función no puede ser eliminada por alguna razón
    }
}

$global_variables_to_remove = @(
    'CONSTANTS',
    'CAN_SHOW_MESSAGE_BOX' # Agregue aquí si se introducen más variables globales
)

# Itera sobre las variables globales y las elimina
foreach ($variable_name in $global_variables_to_remove) {
    try {
        Remove-Variable -Name $variable_name -Scope Global -Force -ErrorAction SilentlyContinue
    }
    catch {} # Ignora errores
}

$variable_patterns_to_remove = @(
    '*_Core*', # Elimina variables que terminan con '_Core' (ej., $injector_core)
    '*Process*' # Elimina variables que terminan con 'Process' (ej., $process_manager)
)

# Elimina variables en diferentes ámbitos usando patrones
foreach ($scope in @('Script', 'Local')) {
    foreach ($pattern in $variable_patterns_to_remove) {
        Get-Variable -Scope $scope -Name $pattern -ErrorAction SilentlyContinue | ForEach-Object {
            try {
                Remove-Variable -Name $_.Name -Scope $scope -Force -ErrorAction SilentlyContinue
            }
            catch {} # Ignora errores
        }
    }
}
```

> [!TIP]
> La limpieza es crucial en scripts de PowerShell que importan muchos elementos a la sesión. `Remove-Item -Path "Function:..."` y `Remove-Variable` se utilizan para desasignar estos elementos. El uso de `ErrorAction SilentlyContinue` y `try/catch` vacíos en los bucles de eliminación asegura que el script de limpieza no falle en caso de que algún elemento ya haya sido eliminado o no exista.

## Ejemplos Completos de Uso

Para integrar el **SA-MP Injector PowerShell** en su proyecto o usarlo directamente, siga las instrucciones y analice los escenarios a continuación.

### 1. Preparación del Entorno de Desarrollo

- **PowerShell Version**: Se recomienda **PowerShell 5.1** o superior (compatible con `Add-Type` para clases).
- **Permisos de Ejecución**: PowerShell tiene políticas de ejecución. Necesitará permitir la ejecución de scripts locales. Abra PowerShell como **Administrador** y ejecute:
   ```powershell
   Set-ExecutionPolicy -ExecutionPolicy RemoteSigned -Scope CurrentUser
   ```
   Esto permitirá que se ejecuten scripts firmados y que los scripts que usted creó (no descargados de Internet) se ejecuten localmente sin firma.
- **Copiar Archivos**: Coloque todos los archivos `.ps1` de la biblioteca (`Injector.ps1`, `Constants.ps1`, `CustomTypes.ps1`, `StringUtils.ps1`, `ErrorUtils.ps1`, `Validation.ps1`, `Process.ps1`, `InjectorCore.ps1`, `Cleanup.ps1`) en un único directorio.
- **Permisos de Proceso**: Su script necesitará privilegios de **Administrador** para crear procesos e inyectar DLLs en otro proceso. Siempre ejecute **PowerShell como Administrador** al usar esta biblioteca.

### 2. Escenario Básico: Conectando a un Servidor SA-MP

Este es el caso de uso más común, iniciando GTA:SA y conectando a un servidor SA-MP con un nickname e IP/puerto específicos.

```powershell
# Cree un nuevo script, por ejemplo, "StartSAMP.ps1"

# Importa la función principal de la biblioteca SA-MP Injector PowerShell
# Asegúrese de que la ruta de abajo refleje dónde se encuentra Injector.ps1.
# Por ejemplo, si Injector.ps1 está en la misma carpeta que este script:
$injector_path = Join-Path -Path $PSScriptRoot -ChildPath "Injector.ps1"

# O, si está en un subdirectorio:
# $injector_path = Join-Path -Path $PSScriptRoot -ChildPath "SA-MP-Injector-PowerShell\Injector.ps1"

# Importa la función Injector.ps1 usando dot-sourcing para que sus funciones
# estén disponibles en el ámbito actual.
. $injector_path

# Definir las variables de configuración
# Cambie estas rutas y detalles del servidor para que coincidan con su configuración local.
$game_folder = "C:\Games\GTA San Andreas" # Donde están gta_sa.exe, samp.dll
$player_nickname = "Nombre"
$server_ip = "127.0.0.1" # Ejemplo: su servidor local
$server_port = "7777"
$server_password = "" # Deje vacío si no hay contraseña

Write-Host "Iniciando SA-MP..." -ForegroundColor Cyan
Write-Host "Carpeta del juego: $game_folder" -ForegroundColor Gray
Write-Host "Nickname: $player_nickname" -ForegroundColor Gray
Write-Host "Servidor: $server_ip:$server_port" -ForegroundColor Gray

# Llamada a la función de la biblioteca para iniciar el juego
$result = Initialize_Game `
    -inject_type "samp" ` # Tipo de inyección: "samp" o "omp"
    -folder $game_folder ` # Ruta de la carpeta del juego
    -nickname $player_nickname ` # Nickname deseado
    -ip $server_ip ` # IP del servidor
    -port $server_port ` # Puerto del servidor (cadena)
    -password $server_password # Contraseña del servidor (cadena, puede estar vacía)

if ($result) {
    Write-Host "`n--- ¡SA-MP inicializado con éxito! ---" -ForegroundColor Green
    Write-Host "El juego se ha iniciado en un proceso separado." -ForegroundColor Green
}
else {
    Write-Host "`n--- ¡FALLO al iniciar SA-MP! ---" -ForegroundColor Red
    Write-Host "Verifique los mensajes de error mostrados (pop-ups o consola)." -ForegroundColor Red
}

# Mantiene la consola abierta para visualizar los mensajes de salida
Read-Host "`nPresione Enter para cerrar el programa."
```

**Para ejecutar el script:**
1.  **Guarde** el código anterior como `StartSAMP.ps1` (o cualquier nombre, siempre que termine con `.ps1`).
2.  **Guarde** todos los archivos de la biblioteca **SA-MP Injector PowerShell** en la misma carpeta o en una estructura de subcarpetas que gestione con `$injector_path`.
3.  **Abra PowerShell como Administrador**.
4.  Navegue hasta el directorio donde guardó `StartSAMP.ps1`.
5.  Ejecute el script:
    ```powershell
    .\StartSAMP.ps1
    ```
    (Recuerde que `.` antes del nombre del script es necesario para scripts en el directorio actual, a menos que lo agregue al PATH).

### 3. Escenario Avanzado: Conectando a un Servidor OMP

Para OMP, la lógica es idéntica a la de SA-MP, pero debe especificar `"omp"` como `inject_type` y asegurarse de que `omp-client.dll` esté presente en el directorio del juego.

```powershell
# Cree un nuevo script, por ejemplo, "StartOMP.ps1"

# Importa la función principal de la biblioteca SA-MP Injector PowerShell
$injector_path = Join-Path -Path $PSScriptRoot -ChildPath "Injector.ps1"
. $injector_path

# Definir las variables de configuración para OMP
$game_folder = "C:\Games\GTA San Andreas" # Donde están gta_sa.exe, samp.dll y omp-client.dll
$player_nickname = "Nombre"
$server_ip = "127.0.0.1" # Ejemplo: su servidor local
$server_port = "7777"
$server_password = "" # Deje vacío si no hay contraseña

Write-Host "Iniciando OMP..." -ForegroundColor Cyan
Write-Host "Carpeta del juego: $game_folder" -ForegroundColor Gray
Write-Host "Nickname: $player_nickname" -ForegroundColor Gray
Write-Host "Servidor: $server_ip:$server_port" -ForegroundColor Gray

# Llamada a la función de la biblioteca para iniciar el juego
$result = Initialize_Game `
    -inject_type "omp" `   # Tipo de inyección: "omp"
    -folder $game_folder `
    -nickname $player_nickname `
    -ip $server_ip `
    -port $server_port `
    -password $server_password

if ($result) {
    Write-Host "`n--- ¡OMP inicializado con éxito! ---" -ForegroundColor Green
    Write-Host "El juego se ha iniciado en un proceso separado." -ForegroundColor Green
}
else {
    Write-Host "`n--- ¡FALLO al iniciar OMP! ---" -ForegroundColor Red
    Write-Host "Verifique los mensajes de error mostrados (pop-ups o consola)." -ForegroundColor Red
}

Read-Host "`nPresione Enter para cerrar el programa."
```

**Para ejecutar el script:**

Siga los mismos pasos de la sección anterior, sustituyendo `StartSAMP.ps1` por `StartOMP.ps1`.

### 4. Ejecución desde un Script Padre

Es posible crear un script más complejo que invoque la biblioteca y maneje parámetros o condiciones de forma más avanzada. El concepto central sigue siendo el mismo: `Injector.ps1` debe ser "dot-sourced" en el script padre.

```powershell
# Launcher.ps1
param(
    [string]$type = "samp",
    [string]$game_dir = "C:\Games\GTA San Andreas",
    [string]$player_nickname = "Nombre",
    [string]$server_ip = "127.0.0.1",
    [string]$server_port = "7777",
    [string]$server_password = ""
)

# Carga Injector.ps1
$injector_script = Join-Path -Path $PSScriptRoot -ChildPath "Injector.ps1"

# Verifica si el script principal del inyector existe antes de cargarlo
if (-not (Test-Path $injector_script -PathType Leaf)) {
    Write-Error "Injector.ps1 no encontrado en $injector_script. Por favor, verifique la ruta."
    
    exit 1
}

. $injector_script # Usa dot-sourcing para cargar las funciones

Write-Host "Intentando iniciar el juego con los parámetros proporcionados..." -ForegroundColor Yellow

$success = Initialize_Game -inject_type $type `
    -folder $game_dir `
    -nickname $player_nickname `
    -ip $server_ip `
    -port $server_port `
    -password $server_password

if ($success) {
    Write-Host "`nReporte del lanzador: ¡Juego iniciado con éxito!" -ForegroundColor Green
}
else {
    Write-Host "`nReporte del lanzador: ¡Fallo al iniciar el juego!" -ForegroundColor Red
}

Read-Host "`nPresione Enter para salir."
```

**Ejecución de `Launcher.ps1`:**

```powershell
# Ejecuta con valores predeterminados
.\Launcher.ps1

# Ejecuta para OMP con IP y puerto específicos
.\Launcher.ps1 -type "omp" -server_ip "omp.server.com" -server_port "7777" -player_nickname "Nombre" -server_password "secure123"
```

## Manejo de Errores Comunes y Mensajes

El **SA-MP Injector PowerShell** prioriza la usabilidad, y una parte fundamental de esto es proporcionar retroalimentación clara al usuario en caso de fallo. Los mensajes de error se presentan a través de cuadros de **diálogo de Windows** (`MessageBoxW`) o directamente en la consola de PowerShell, y se categorizan por el tipo de **inyección (SA-MP u OMP)** para un mayor contexto. Esto asegura que sepa exactamente qué salió mal y cómo abordar la resolución.

Aquí están algunos de los errores comunes que puede encontrar y sus probables causas/soluciones, acompañados de ejemplos visuales de cómo aparecen estos cuadros de diálogo para el usuario final:

### 1. Tipo de Inyección Inválido

Si el `inject_type` proporcionado no es `"samp"` o `"omp"`, la biblioteca no sabrá qué cliente multijugador pretende inicializar.

![Error 1](screenshots/error_1.png)

- **Mensaje de Error Mostrado**: `"Invalid injection mode specified. Please use 'samp' or 'omp'."`
- **Causa**: El argumento `inject_type` no coincide con los valores esperados de `"samp"` o `"omp"`. Puede ser un error de escritura, una cadena vacía o un valor no reconocido.
- **Solución**: Verifique que el `$inject_type` esté definido correctamente como `"samp"` o `"omp"`. Es importante que la cadena coincida exactamente (aunque el código usa `ToLower()` para la comparación).
   ```powershell
   # Correcto:
   Initialize_Game -inject_type "samp" ...
   Initialize_Game -inject_type "omp" ...

   # Incorrecto (causará error):
   # Initialize_Game -inject_type "invalid" ...
   # Initialize_Game -inject_type "" ...
   ```

### 2. Puerto del Servidor Inválido (Formato o Rango)

El puerto es un parámetro numérico esencial para la conexión con el servidor. Este error ocurre si el valor no puede ser interpretado como un número válido o está fuera del rango aceptable (**1 a 65535**).

#### 2.1. Formato de Puerto No Numérico

![Error 2](screenshots/error_2.png)

- **Mensaje de Error Mostrado**: `"Invalid port format. The port must be a numeric value. Please provide a valid integer for the port."`
- **Causa**: El argumento `port` contiene caracteres que no son dígitos numéricos o no puede ser convertido a un número entero válido (ej., `"abc"`, `"7777a"`).
- **Solución**: Proporcione una cadena que contenga solo dígitos y represente un número entero válido.
   ```powershell
   # Correcto:
   Initialize_Game ... -port "7777" ...
   
   # Incorrecto (formato inválido):
   # Initialize_Game ... -port "port7777" ...
   # Initialize_Game ... -port "invalid" ...
   ```

#### 2.2. Puerto Fuera del Rango Válido

![Error 3](screenshots/error_3.png)

- **Mensaje de Error Mostrado**: `"The specified port number (XXXX) is outside the valid range of 1 to 65535. Please provide a valid port."` (El **XXXX** será el valor que intentó usar).
- **Causa**: El puerto proporcionado es un número válido, pero está por debajo de `1` (reservado o no utilizable) o por encima de `65535` (límite máximo para **puertos TCP/UDP**).
- **Solución**: Proporcione un puerto que esté dentro del rango de `1` a `65535`. Puertos comunes para **SA-MP**/**OMP** son `7777`.
   ```powershell
   # Correcto:
   Initialize_Game ... -port "7777" ...

   # Incorrecto (fuera de rango):
   # Initialize_Game ... -port "0" ...      # Muy bajo
   # Initialize_Game ... -port "65536" ...  # Muy alto
   # Initialize_Game ... -port "-1" ...     # Valor negativo
   ```

### 3. Nickname Inválido (Vacío o Demasiado Largo)

El **nickname** del jugador se valida para asegurar que el cliente del juego lo acepte.

#### 3.1. Nickname Vacío

![Error 4](screenshots/error_4.png)

- **Mensaje de Error Mostrado**: `"Nickname cannot be empty. Please provide a valid nickname."`
- **Causa**: El argumento `nickname` se proporcionó como una cadena vacía.
- **Solución**: Asegúrese de que el nickname no esté vacío.
   ```powershell
   # Correcto:
   Initialize_Game ... -nickname "MiNombre" ...

   # Incorrecto (vacío):
   # Initialize_Game ... -nickname "" ...
   ```

#### 3.2. Nickname Demasiado Largo

![Error 5](screenshots/error_5.png)

- **Mensaje de Error Mostrado**: `"Nickname length exceeds the maximum allowed of 20 characters. Please use a shorter nickname."`
- **Causa**: La longitud del **nickname** proporcionado excede `$global:CONSTANTS.MAX_NICKNAME_LENGTH`, que es de `20` caracteres.
- **Solución**: Use un **nickname** que tenga como máximo `20` caracteres.
   ```powershell
   # Correcto:
   Initialize_Game ... -nickname "Corto" ...

   # Incorrecto (demasiado largo):
   # Initialize_Game ... -nickname "EsteNombreDeJugadorEsDemasiadoLargoParaUsar" ...
   ```

### 4. Archivos del Juego o DLL No Encontrados

Esta es una de las causas más comunes de fallo. La biblioteca necesita que `gta_sa.exe`, `samp.dll` y, para **OMP**, `omp-client.dll` estén presentes en las ubicaciones esperadas.

#### 4.1. Ejecutable del Juego (`gta_sa.exe`) No Encontrado

![Error 6](screenshots/error_6.png)

- **Mensaje de Error Mostrado**: `"Game executable not found. Please ensure 'gta_sa.exe' exists at the specified path: [ruta completa]"`. La `[ruta completa]` incluirá la carpeta y el nombre del archivo.
- **Causa**: El archivo `gta_sa.exe` no se encontró en la carpeta proporcionada en el argumento `folder`.
- **Solución**:
   1. Verifique que `$folder` apunte al directorio de instalación correcto de **GTA San Andreas**.
   2. Confirme que `gta_sa.exe` existe dentro de esa carpeta y que su nombre no ha sido cambiado.

#### 4.2. Biblioteca SA-MP (`samp.dll`) No Encontrada

![Error 7](screenshots/error_7.png)

- **Mensaje de Error Mostrado**: `"SA-MP library not found. Please ensure 'samp.dll' exists at the specified path: [ruta completa]"`.
- **Causa**: El archivo `samp.dll` no se encontró en la carpeta proporcionada en el argumento `folder`. **Esta DLL** es un requisito para **ambos** tipos de inyección (`samp` y `omp`).
- **Solución**: Asegúrese de que `samp.dll` esté presente en la carpeta de instalación de **GTA San Andreas**.

#### 4.3. Biblioteca OMP (`omp-client.dll`) No Encontrada (solo para inyección OMP)

![Error 8](screenshots/error_8.png)

- **Mensaje de Error Mostrado**: `"OMP library not found. Please ensure 'omp-client.dll' exists at the specified path for OMP injection: [ruta completa]"`.
- **Causa**: Si especificó `"omp"` como tipo de inyección, pero el archivo `omp-client.dll` no se encontró en la carpeta proporcionada.
- **Solución**: Descargue el cliente **OMP** más reciente y asegúrese de que `omp-client.dll` (y `samp.dll`) estén presentes en la carpeta de instalación de **GTA San Andreas**.

### 5. Fallo en la Creación del Proceso del Juego

Este es un error más complejo, ya que involucra **permisos del sistema operativo** y el estado actual de `gta_sa.exe`.

![Error 9](screenshots/error_9.png)

- **Mensaje de Error Mostrado**: `"Failed to create game process. Ensure 'gta_sa.exe' is not running and you have sufficient permissions to execute the file. System Error: [Mensaje de error del sistema operativo]"`. El mensaje del sistema será añadido por `Get_System_Error_Message` (ej: `Access is denied.` o `The requested operation requires elevation.`).
- **Causa**: La llamada `CreateProcessA` para iniciar `gta_sa.exe` falló. Las causas comunes incluyen:
   - **Proceso ya en ejecución**: Una instancia de `gta_sa.exe` ya está activa y bloqueando una nueva ejecución.
   - **Permisos insuficientes**: Su script no tiene los privilegios necesarios (ej., administrador) para crear un proceso en determinadas configuraciones del sistema (**UAC** activado, carpetas protegidas, etc.).
   - **Problemas con el ejecutable**: El `gta_sa.exe` puede estar corrupto o bloqueado por otro programa (ej., un antivirus mal configurado).
- **Solución**:
   1. Verifique el Administrador de Tareas y asegúrese de que no haya ninguna instancia de `gta_sa.exe` en ejecución. Finalice cualquiera si la hay.
   2. Ejecute el script de **PowerShell como Administrador**. Haga clic derecho en el icono de PowerShell y seleccione **"Ejecutar como administrador"**, o inícielo desde un acceso directo configurado para ello.
   3. Si un **antivirus** o **software** de seguridad está interfiriendo, agregue su script y/o la carpeta de **GTA:SA** a las excepciones del antivirus (haga esto con cuidado y solo si está seguro de la integridad de sus archivos).

### 6. Fallo en la Asignación de Memoria en el Proceso de Destino

La biblioteca intenta asignar un pequeño espacio de memoria en `gta_sa.exe` para copiar la **ruta de la DLL**.

![Error 10](screenshots/error_10.png)

- **Mensaje de Error Mostrado**: `"Failed to allocate memory in the target process. This might be due to insufficient permissions or process protection mechanisms. System Error: [Mensaje de error del sistema operativo]"`.
- **Causa**: La función `VirtualAllocEx` (usada para asignar memoria dentro de otro proceso) falló. Esto es más probable si:
   - El proceso de **GTA:SA** (incluso estando en estado suspendido) posee defensas de seguridad o **parches anti-inyección** que impiden la asignación de memoria por procesos externos.
   - Su script no tiene los permisos elevados necesarios para manipular la memoria de otro proceso.
   - (Menos común) Hay una escasez extrema de memoria virtual en el sistema.
- **Solución**:
   1. Ejecute su script con privilegios de **Administrador**.
   2. Asegúrese de que el juego no tenga ninguna modificación o **parche de seguridad** que pueda estar bloqueando intentos de inyección o manipulación de memoria (esto es más común en entornos modificados o con ciertas herramientas anti-cheat de terceros).

### 7. Fallo al Escribir la Ruta de la DLL en la Memoria del Proceso

Después de asignar la memoria, la biblioteca intenta copiar la **ruta de la DLL** a ella.

![Error 11](screenshots/error_11.png)

- **Mensaje de Error Mostrado**: `"Failed to write DLL path to the target process memory. Verify process permissions and ensure the DLL path is accessible. System Error: [Mensaje de error del sistema operativo]"`.
- **Causa**: La función `WriteProcessMemory` falló al intentar copiar los **bytes de la ruta de la DLL** a la memoria remota asignada en `gta_sa.exe`. Esto generalmente apunta a:
   - **Permisos de escritura**: Su script no tiene permiso para escribir en esa región de memoria o en el proceso de **GTA:SA**.
   - **Handle inválido**: El **handle** del proceso de alguna manera se ha vuelto inválido (menos común, pero posible bajo condiciones extremas del sistema).
   - **Problemas de Protección de Memoria**: Alguna protección de memoria (ya sea del **SO** o de modificaciones del juego) impidió la escritura.
- **Solución**: Ejecute como **Administrador**. Verifique que `gta_sa.exe` y su entorno estén "limpios" de herramientas que podrían bloquear operaciones de memoria.

### 8. Fallo al Encontrar Funciones Esenciales del Sistema

Estas son APIs cruciales de Windows; errores aquí indican un problema fundamental con el sistema operativo o el entorno de ejecución.

#### 8.1. `kernel32.dll` No Encontrado

![Error 12](screenshots/error_12.png)

- **Mensaje de Error Mostrado**: `"Failed to obtain a handle to kernel32.dll. This is an essential system library and this error indicates a severe system issue. System Error: [Mensaje de error del sistema operativo]"`.
- **Causa**: `kernel32.dll` es una de las DLLs más básicas de Windows, conteniendo funciones esenciales. Si `GetModuleHandleA` no puede obtener un **handle** para ella, el sistema operativo tiene problemas muy serios.
- **Solución**: Este es un error **crítico** que raramente es causado por la biblioteca o su script. Sugiere corrupción de archivos del sistema, problemas graves con **Windows**, o una instalación muy inusual del **SO**. Se recomienda ejecutar verificaciones de integridad del sistema (como `sfc /scannow` en el **Símbolo del sistema** como **Administrador**) o, en último caso, reinstalar **Windows**.

#### 8.2. `LoadLibraryA` No Encontrado

![Error 13](screenshots/error_13.png)

- **Mensaje de Error Mostrado**: `"Failed to find the address of the LoadLibraryA function in kernel32.dll. This is critical for injecting the DLL. System Error: [Mensaje de error del sistema operativo]"`.
- **Causa**: Aunque se encontró `kernel32.dll`, la función `LoadLibraryA` no pudo ser resuelta a través de `GetProcAddress`. Aunque extremadamente inusual, puede ser el resultado de la corrupción del **archivo DLL** de `kernel32.dll` o un entorno de ejecución altamente no estándar.
- **Solución**: Al igual que el error de `kernel32.dll` anterior, esto indica un problema serio en el sistema operativo.

### 9. Fallo al Crear Hilo Remoto para Inyección

Después de preparar el entorno remoto y copiar la **ruta de la DLL**, se crea un nuevo **hilo** en el proceso del juego para "llamar" a `LoadLibraryA`.

![Error 14](screenshots/error_14.png)

- **Mensaje de Error Mostrado**: `"Failed to create a remote thread in the target process to execute the DLL injection. This could be due to security restrictions or process state. System Error: [Mensaje de error del sistema operativo]"`.
- **Causa**: La llamada `CreateRemoteThread` falló. Este error es común en sistemas con defensas **anti-inyección** robustas o cuando un programa está monitoreando intensamente el comportamiento del proceso:
   - **Mecanismos de Seguridad**: Herramientas **anti-cheat**, **software** de seguridad o ciertas políticas de **Windows** pueden detectar y bloquear intentos de crear **hilos** en procesos de terceros.
   - **Proceso de Destino Inconsistente**: Si el proceso de **GTA:SA** está en un estado inesperado o inestable (aunque se haya iniciado en `CREATE_SUSPENDED`), esto puede afectar la capacidad de crear **hilos** en él.
- **Solución**:
   1. Ejecute su script con privilegios de **Administrador**.
   2. Verifique que no haya herramientas **anti-cheat**, **antivirus agresivos** o **firewalls** configurados para inspeccionar y bloquear la manipulación de procesos que puedan estar en conflicto. Agregue su script y `gta_sa.exe` a las excepciones, si aplica (con precaución).
   3. El mensaje de error del sistema puede proporcionar detalles adicionales para investigar la causa específica (ej: **"A process has been denied access to create threads for other processes."**).

### 10. Timeout o Fallo en la Finalización de la Inyección

Después de crear el **hilo** remoto, el inyector espera a que complete la **carga de la DLL**.

![Error 15](screenshots/error_15.png)

- **Mensaje de Error Mostrado**: `"Timeout or error waiting for DLL injection to complete (timeout). System Error: [Mensaje de error del sistema operativo]"`.
- **Causa**: El **hilo** remoto que está ejecutando `LoadLibraryA` tardó más de `$global:CONSTANTS.DLL_INJECTION_TIMEOUT_MS` (10 segundos) en retornar, o falló y `GetExitCodeThread` devolvió 0. Las causas potenciales incluyen:
   - **Problemas en la DLL Inyectada**: La `DllMain` de `samp.dll` o `omp-client.dll` está tardando demasiado en ejecutarse, contiene un **bucle infinito**, un **crash**, o un error que **impide que la DLL** se cargue correctamente (ej: **dependencias de DLLs** ausentes).
   - **Bloqueo Silencioso**: Un mecanismo de seguridad puede haber bloqueado `LoadLibraryA` pero no lo notificó con un error obvio de creación de **hilo**.
- **Solución**:
   1. Verifique la integridad de los archivos `samp.dll` y `omp-client.dll`. Pueden estar corruptos o ser de una versión incompatible con su `gta_sa.exe`.
   2. Asegúrese de **que la DLL inyectada** no dependa de **otras DLLs** que puedan estar faltando o ser inaccesibles en el sistema.

### 11. Fallo al Reanudar el Hilo del Proceso del Juego

Este es el paso final para iniciar el juego después de **que las DLLs** son inyectadas.

![Error 16](screenshots/error_16.png)

- **Mensaje de Error Mostrado**: `"Failed to resume the game process thread: [Mensaje de error del sistema operativo]"`.
- **Causa**: La llamada `ResumeThread` falló, lo que significa que el **hilo** principal de `gta_sa.exe` no pudo ser activado para iniciar la ejecución del juego. Este es un error raro, pero puede suceder si:
   - El **handle** del **hilo** del proceso se ha vuelto inválido.
   - El sistema operativo impidió la reanudación por alguna razón, posiblemente relacionada con una interrupción de seguridad o un estado inconsistente del proceso.
   - El proceso puede haber sido terminado externamente entre la **inyección de la DLL** y el intento de reanudar el **hilo** principal.
- **Solución**: Si todos los pasos anteriores tuvieron éxito y solo `ResumeThread` falló, podría ser un problema con el sistema operativo, con la propia instalación de **GTA:SA**, o con otro **software** de seguridad muy estricto. Reexamine el estado de `gta_sa.exe` a través del **Administrador de Tareas** justo antes y después del error. Intentar reiniciar el ordenador puede resolver problemas de estado temporal del sistema.

> [!TIP]
> En escenarios de depuración complejos, herramientas como **Process Monitor (Sysinternals Suite)** o un depurador (como **WinDbg**) pueden ser invaluables. Pueden ayudar a observar las llamadas a la **API**, verificar errores de acceso, rastrear el estado de los **handles** e incluso inspeccionar la memoria del proceso, proporcionando una visión profunda de lo que está sucediendo tras bambalinas.
>
> Para depurar scripts de PowerShell que utilizan `Add-Type` e interactúan con la WinAPI a bajo nivel, herramientas como el **PowerShell Integrated Scripting Environment (ISE)** o **Visual Studio Code** con la extensión de PowerShell son útiles, permitiendo la colocación de puntos de interrupción y la inspección de variables. Recuerde siempre ejecutarlos **como Administrador**.

## Licencia

Copyright © **SA-MP Programming Community**

Este software está licenciado bajo los términos de la Licencia MIT ("Licencia"); puede utilizar este software de acuerdo con las condiciones de la Licencia. Puede obtener una copia de la Licencia en: [MIT License](https://opensource.org/licenses/MIT)

### Términos y Condiciones de Uso

#### 1. Permisos Otorgados

La presente licencia otorga, gratuitamente, a cualquier persona que obtenga una copia de este software y archivos de documentación asociados, los siguientes derechos:
* Usar, copiar, modificar, fusionar, publicar, distribuir, sublicenciar y/o vender copias del software sin restricciones
* Permitir que las personas a las que se les proporciona el software hagan lo mismo, sujeto a las siguientes condiciones

#### 2. Condiciones Obligatorias

Todas las copias o partes sustanciales del software deben incluir:
* El aviso de derechos de autor anterior
* Este aviso de permiso
* El aviso de exención de responsabilidad a continuación

#### 3. Derechos de Autor

El software y toda la documentación asociada están protegidos por leyes de derechos de autor. La **SA-MP Programming Community** mantiene la titularidad de los derechos de autor originales del software.

#### 4. Exención de Garantías y Limitación de Responsabilidad

EL SOFTWARE SE PROPORCIONA "TAL CUAL", SIN GARANTÍA DE NINGÚN TIPO, EXPRESA O IMPLÍCITA, INCLUYENDO PERO NO LIMITADO A LAS GARANTÍAS DE COMERCIABILIDAD, IDONEIDAD PARA UN PROPÓSITO PARTICULAR Y NO INFRACCIÓN.

EN NINGÚN CASO LOS AUTORES O TITULARES DE LOS DERECHOS DE AUTOR SERÁN RESPONSABLES DE CUALQUIER RECLAMACIÓN, DAÑOS U OTRA RESPONSABILIDAD, YA SEA EN UNA ACCIÓN DE CONTRATO, AGRAVIO O DE OTRO MODO, QUE SURJA DE, FUERA DE O EN CONEXIÓN CON EL SOFTWARE O EL USO U OTROS TRATOS EN EL SOFTWARE.

---

Para información detallada sobre la Licencia MIT, consulte: https://opensource.org/licenses/MIT