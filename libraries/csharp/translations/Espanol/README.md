# SA-MP Injector C#

<div align="center">

![C#](https://img.shields.io/badge/C%23-11.0%2B-512BD4?style=for-the-badge&logo=csharp&logoColor=white)
![.NET](https://img.shields.io/badge/.NET-7.0%2B-512BD4?style=for-the-badge&logo=dotnet&logoColor=white)
![Platform](https://img.shields.io/badge/Platform-Windows-blue?style=for-the-badge&logo=windows&logoColor=white)
![Architecture](https://img.shields.io/badge/Architecture-x86%20(32--bit)-lightgrey?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)

**Una biblioteca C# para la inyección programática de DLLs en procesos SA-MP y OMP, permitiendo la conexión automatizada a servidores.**

</div>

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

- [SA-MP Injector C#](#sa-mp-injector-c)
  - [Idiomas](#idiomas)
  - [Índice](#índice)
  - [Introducción y Propósito](#introducción-y-propósito)
  - [Filosofía de Diseño](#filosofía-de-diseño)
    - [Interoperabilidad (P/Invoke)](#interoperabilidad-pinvoke)
    - [Gestión de Recursos (`SafeHandle`)](#gestión-de-recursos-safehandle)
    - [Seguridad y Robustez](#seguridad-y-robustez)
  - [Requisitos del Sistema](#requisitos-del-sistema)
    - [Entorno de Desarrollo](#entorno-de-desarrollo)
    - [Entorno de Ejecución](#entorno-de-ejecución)
  - [Instalación y Uso Básico](#instalación-y-uso-básico)
    - [Añadiendo a Su Proyecto](#añadiendo-a-su-proyecto)
    - [Ejemplo de Uso](#ejemplo-de-uso)
  - [Componentes de la Biblioteca](#componentes-de-la-biblioteca)
    - [1. `Constants.cs`](#1-constantscs)
    - [2. `InjectionType.cs`](#2-injectiontypecs)
    - [3. `Injector.cs`](#3-injectorcs)
    - [4. `InjectorCore.cs`](#4-injectorcorecs)
    - [5. `InputValidator.cs`](#5-inputvalidatorcs)
    - [6. `NativeImports.cs`](#6-nativeimportscs)
    - [7. `ProcessHandler.cs`](#7-processhandlercs)
    - [8. `SafeHandles.cs`](#8-safehandlescs)
  - [Ciclo de Inyección de DLL Detallado](#ciclo-de-inyección-de-dll-detallado)
    - [1. Validación de Entrada](#1-validación-de-entrada)
    - [2. Creación del Proceso del Juego (Suspendido)](#2-creación-del-proceso-del-juego-suspendido)
    - [3. Inyección de `samp.dll`](#3-inyección-de-sampdll)
    - [4. Inyección de `omp-client.dll` (Opcional, Dependiente de SA-MP)](#4-inyección-de-omp-clientdll-opcional-dependiente-de-sa-mp)
    - [Reanudar el Hilo Principal del Juego](#reanudar-el-hilo-principal-del-juego)
  - [Manejo de Errores y Casos de Falla](#manejo-de-errores-y-casos-de-falla)
    - [Errores de Validación de Entrada](#errores-de-validación-de-entrada)
      - [Nickname Inválido](#nickname-inválido)
      - [Puerto Inválido](#puerto-inválido)
      - [Archivos de Juego/DLLs Faltantes](#archivos-de-juegodlls-faltantes)
    - [Errores en la Creación del Proceso](#errores-en-la-creación-del-proceso)
      - [Falla al Crear el Proceso](#falla-al-crear-el-proceso)
    - [Errores en la Inyección de la DLL](#errores-en-la-inyección-de-la-dll)
      - [Handle `kernel32.dll` No Disponible](#handle-kernel32dll-no-disponible)
      - [Función `LoadLibraryA` No Disponible](#función-loadlibrarya-no-disponible)
      - [Falla en la Asignación de Memoria Remota](#falla-en-la-asignación-de-memoria-remota)
      - [Falla en la Escritura en la Memoria del Proceso](#falla-en-la-escritura-en-la-memoria-del-proceso)
      - [Falla en la Creación del Hilo Remoto](#falla-en-la-creación-del-hilo-remoto)
      - [Timeout o Error en la Espera por la Inyección](#timeout-o-error-en-la-espera-por-la-inyección)
      - [Inyección de la DLL Falló o Retornó Error](#inyección-de-la-dll-falló-o-retornó-error)
    - [Error al Reanudar el Hilo del Juego](#error-al-reanudar-el-hilo-del-juego)
  - [Licencia](#licencia)
    - [Términos y Condiciones de Uso](#términos-y-condiciones-de-uso)
      - [1. Permisos Otorgados](#1-permisos-otorgados)
      - [2. Condiciones Obligatorias](#2-condiciones-obligatorias)
      - [3. Derechos de Autor](#3-derechos-de-autor)
      - [4. Exención de Garantías y Limitación de Responsabilidad](#4-exención-de-garantías-y-limitación-de-responsabilidad)

## Introducción y Propósito

La biblioteca **SA-MP Injector C#** es una solución en C# diseñada para simplificar el inicio y la conexión automatizada de clientes San Andreas Multiplayer (SA-MP) y Open Multiplayer (OMP) a servidores. Actúa como una herramienta de inyección de DLL (Dynamic Link Library), cargando programáticamente las bibliotecas `samp.dll` u `omp-client.dll` en el proceso del juego Grand Theft Auto: San Andreas (`gta_sa.exe`).

El principal objetivo de esta biblioteca es permitir que otras aplicaciones C# (como launchers personalizados, herramientas de gestión de servidores o utilidades) puedan iniciar el juego con parámetros específicos (apodo, IP, puerto y contraseña) de forma transparente para el usuario, automatizando el proceso de conexión a un servidor de SA-MP/OMP.

## Filosofía de Diseño

El diseño del **SA-MP Injector C#** se enfoca en la robustez, seguridad y una interfaz de uso simplificada, encapsulando las complejidades de las operaciones de bajo nivel del sistema.

### Interoperabilidad (P/Invoke)

La funcionalidad central de la inyección de DLL y la creación de procesos suspendidos es intrínsecamente una operación de sistema operativo de bajo nivel. Para ello, la biblioteca hace un uso extensivo de la característica **P/Invoke (Platform Invoke)** de .NET, permitiendo la llamada de funciones nativas de la API de Windows (principalmente de `kernel32.dll`) directamente desde el código C#. Esto es evidente en la declaración de métodos `partial` y en la utilización del atributo `[LibraryImport(KERNEL32, SetLastError = true)]`.

### Gestión de Recursos (`SafeHandle`)

Las operaciones con recursos del sistema operativo, como los "handles" de procesos e hilos, exigen una gestión cuidadosa para evitar fugas de memoria o recursos. La biblioteca emplea clases derivadas de `SafeHandle` (`SafeProcessHandle` y `SafeThreadHandle`) para garantizar que estos recursos siempre se liberen correctamente, incluso en caso de excepciones. Esto se adhiere al principio de **RAII (Resource Acquisition Is Initialization)** de C++ y lo extiende al entorno .NET.

### Seguridad y Robustez

La biblioteca incorpora varias capas de seguridad:
- **Validación de Entrada:** Todas las entradas proporcionadas por el usuario se validan rigurosamente antes de que se inicie cualquier operación crítica, minimizando el riesgo de errores de runtime o comportamientos inesperados.
- **Manejo de Errores:** Las llamadas a la API nativa van acompañadas de verificaciones de error (`SetLastError = true` y `Marshal.GetLastWin32Error()`) para proporcionar mensajes de error detallados y comprensibles.
- **Finalización de Proceso:** En caso de falla durante el proceso de inyección, el proceso del juego recién creado se cierra automáticamente para evitar que procesos "zombis" queden en ejecución.

## Requisitos del Sistema

### Entorno de Desarrollo

- **.NET SDK 7.0 o superior:** La biblioteca está construida para `net7.0-windows`.
- **C# 11.0 o superior:** Necesario para características como `ImplicitUsings`, `Nullable`, `AllowUnsafeBlocks` y `LibraryImport`.
- **Visual Studio 2022 o entorno de desarrollo compatible:** Para construir e integrar la biblioteca.
- **Plataforma de Compilación:** `x86 (32-bit)` es el objetivo obligatorio debido a la arquitectura de `gta_sa.exe` y de las DLLs SA-MP/OMP.

```xml
<!-- samp-injector-csharp.csproj -->
<Project Sdk="Microsoft.NET.Sdk">
    <PropertyGroup>
        <TargetFrameworks>net7.0-windows</TargetFrameworks>
        <PlatformTarget>x86</PlatformTarget> <!-- CRÍTICO: Debe ser x86 -->
        <ImplicitUsings>enable</ImplicitUsings>
        <Nullable>enable</Nullable>
        <UseWindowsForms>true</UseWindowsForms>
        <AllowUnsafeBlocks>true</AllowUnsafeBlocks> <!-- Necesario para P/Invoke avanzado -->
    </PropertyGroup>
</Project>
```

### Entorno de Ejecución

- **Sistema Operativo:** Windows (cualquier versión moderna compatible con .NET 7.0+).
- **Grand Theft Auto: San Andreas (GTA: SA):** Se requiere la instalación del juego.
- **SA-MP o OMP Client DLLs:** `samp.dll` u `omp-client.dll` deben estar presentes en el directorio raíz del juego, dependiendo del tipo de inyección deseado.

## Instalación y Uso Básico

### Añadiendo a Su Proyecto

La forma más simple de usar esta biblioteca es agregar el proyecto `Samp_Injector_CSharp` como una referencia en su propio proyecto C#.

1. Clone o descargue el repositorio de la biblioteca.
2. En Visual Studio, haga clic con el botón derecho en "Dependencies" (o "Referencias") en su proyecto.
3. Seleccione "Add Project Reference...".
4. Navegue hasta el directorio de la biblioteca y agregue el proyecto `samp-injector-csharp.csproj`.

### Ejemplo de Uso

Para iniciar el juego y conectarse a un servidor, simplemente llame al método estático `Injector.Initialize_Game`.

```csharp
using Samp_Injector_CSharp;
using System;
using System.Windows.Forms; // Para MessageBox, si no es un proyecto WinForms

namespace Launcher {
    public partial class Main : Form {
        public Main() {
            InitializeComponent();
        }

        private void Connect(object sender, EventArgs e) {
            string inject_type = "SAMP"; // "SAMP" u "OMP"
            string game_folder = @"C:\Games\GTA San Andreas"; // Ruta a la carpeta de GTA: SA
            string nickname = "Nombre";
            string ip = "127.0.0.1";
            string port = "7777";
            string password = ""; // Deje vacío si no hay contraseña

            // Ejemplo de inyección SA-MP
            Injector.Initialize_Game(inject_type, game_folder, nickname, ip, port, password);

            // Si es OMP, cambie inject_type:
            // inject_type = "OMP";
            // Injector.Initialize_Game(inject_type, game_folder, nickname, ip, port, password);
        }
    }
}
```

## Componentes de la Biblioteca

La biblioteca está estructurada en varios archivos, cada uno con una responsabilidad clara y bien definida, lo que promueve la organización, la mantenibilidad y la separación de responsabilidades. A continuación, una descripción detallada de cada componente.

### 1. `Constants.cs`

Este archivo es un repositorio centralizado de todas las constantes y valores inmutables que se utilizan en toda la biblioteca. Su existencia promueve el mantenimiento del código, la legibilidad y la consistencia, garantizando que los valores críticos se definan en un único lugar.

La organización de las constantes por categoría facilita la comprensión de su propósito:

- **Game Related Constants**
   - `MIN_PORT`: Define el valor mínimo permitido para el puerto de conexión de un servidor (1).
   - `MAX_PORT`: Define el valor máximo permitido para el puerto de conexión de un servidor (65535).
   - `MAX_NICKNAME_LENGTH`: Especifica la longitud máxima permitida para el apodo del jugador (23 caracteres), un límite impuesto por el propio cliente SA-MP/OMP.

- **File Names**
   - `SAMP_DLL_NAME`: El nombre del archivo de la biblioteca principal del cliente SA-MP (`"samp.dll"`).
   - `OMP_DLL_NAME`: El nombre del archivo de la biblioteca del cliente Open Multiplayer (`"omp-client.dll"`), utilizada en inyecciones de tipo OMP.
   - `GAME_EXE_NAME`: El nombre del archivo ejecutable del juego Grand Theft Auto: San Andreas (`"gta_sa.exe"`).

- **System Libraries and Functions**
   - `KERNEL32_DLL`: El nombre de la biblioteca del sistema Windows que contiene funciones esenciales para la manipulación de procesos y memoria (`"kernel32.dll"`).
   - `LOAD_LIBRARY_FUNC`: El nombre de la función dentro de `kernel32.dll` responsable de cargar dinámicamente una biblioteca (`"LoadLibraryA"`).

- **Command Line Arguments**
   - `CMD_ARGS_PART1`: Parte inicial de los argumentos de línea de comandos para el juego (`"-c -n "`).
   - `CMD_ARGS_PART2`: Separador para la dirección IP (`" -h "`).
   - `CMD_ARGS_PART3`: Separador para el puerto (`" -p "`).
   - `CMD_ARGS_PART4_PASSWORD`: Prefijo para el argumento de contraseña (`" -z "`), usado solo si se proporciona una contraseña.
   - `CMD_ARGS_BASE_LENGTH`: La longitud predefinida de las partes constantes de la línea de comandos, excluyendo el ejecutable y los valores del usuario (14 caracteres).
   - `CMD_ARG_PASSWORD_LENGTH`: La longitud del prefijo del argumento de contraseña (4 caracteres).

- **Error Message Titles**
   - `ERROR_TITLE_SAMP`: Título predeterminado para cuadros de diálogo de error relacionados con fallas de SA-MP (`"SA-MP Injector Error - SPC"`).
   - `ERROR_TITLE_OMP`: Título predeterminado para cuadros de diálogo de error relacionados con fallas de OMP (`"OMP Injector Error - SPC"`).

- **Process Creation Flags**
   - `CREATE_SUSPENDED`: Flag que instruye al sistema operativo a crear un proceso y su hilo principal en un estado suspendido (`0x00000004`). Esto es fundamental para la inyección de la DLL antes de que el juego comience a ejecutarse.
   - `PROCESS_CREATION_FLAGS`: Una combinación de flags de creación de proceso, actualmente definida solo como `CREATE_SUSPENDED`.

- **Timeouts**
   - `DLL_INJECTION_TIMEOUT_MS`: El tiempo máximo (en milisegundos) que la biblioteca esperará para la finalización del hilo remoto responsable de la inyección de la DLL (10000ms = 10 segundos).

- **Memory Allocation Flags**
   - `MEM_COMMIT`: Flag que reserva páginas en la memoria virtual y las "confirma" (asigna memoria física) (`0x1000`).
   - `MEM_RESERVE`: Flag que solo reserva un rango de espacio de dirección virtual para uso posterior (`0x2000`).
   - `MEM_RELEASE`: Flag que desconfirma y libera una región de páginas (`0x8000`).
   - `MEMORY_ALLOCATION_TYPE`: Una combinación de `MEM_COMMIT` y `MEM_RESERVE`, usada para asignar memoria para la ruta de la DLL en el proceso remoto.
   - `MEMORY_PROTECTION`: Define los permisos de protección de memoria (actualmente `0x04`, que corresponde a `PAGE_READWRITE` en la API de Windows, permitiendo lectura y escritura en la memoria asignada).

### 2. `InjectionType.cs`

Este archivo define un enumerador simple para proporcionar una forma segura y clara de especificar el tipo de inyección a realizar. El uso de un `enum` en lugar de strings (`"samp"`, `"omp"`) previene errores de tipeo y hace que el código sea más legible y robusto.

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

Este archivo es la fachada (Facade) pública de la biblioteca, sirviendo como el único punto de entrada para las aplicaciones consumidoras. Abstrae toda la complejidad interna del proceso de inyección en un único método estático.

- **Responsabilidad Principal:** El método `Initialize_Game` recibe todos los parámetros necesarios como strings, determina el tipo de inyección y delega el trabajo al `Injector_Core`. También es responsable de capturar el resultado de la operación y presentar mensajes de error al usuario final a través de `MessageBox`, haciendo que la interacción con el usuario final sea consistente.

```csharp
// Fragmento de Injector.cs
public static class Injector {
    private static readonly Injector_Core s_core = new();

    public static void Initialize_Game(string inject_type_str, string folder, string nickname, string ip, string port, string password) {
        // ... Lógica para convertir inject_type_str a Injection_Type ...

        if (!s_core.Try_Initialize_Game(type, folder, nickname, ip, port, password, out string error_message)) {
            string error_title = (type == Injection_Type.OMP) ? Constants.ERROR_TITLE_OMP : Constants.ERROR_TITLE_SAMP;
            MessageBox.Show(error_message, error_title, MessageBoxButtons.OK, MessageBoxIcon.Error);
        }
    }
}
```

### 4. `InjectorCore.cs`

Este es el "cerebro" de la biblioteca, donde se orquesta la secuencia de operaciones de inyección. Conecta los validadores de entrada con los manejadores de proceso para ejecutar el flujo de trabajo completo.

- **Responsabilidad Principal:** El método `Try_Initialize_Game` define la lógica paso a paso: valida las entradas, crea el proceso del juego en estado suspendido, inyecta las DLLs necesarias (`samp.dll` y, opcionalmente, `omp-client.dll`) y, si todo tiene éxito, reanuda el hilo del juego. Un aspecto crucial es el bloque `finally`, que garantiza que el proceso del juego se termine (`Kill()`) en caso de cualquier falla durante las etapas de inyección, evitando procesos "zombis".

```csharp
// Fragmento de InjectorCore.cs
internal sealed class Injector_Core {
    public bool Try_Initialize_Game(...) {
        // ... Validación de entrada ...

        using Process_Handler.Process_Info process_info = Process_Handler.Create_Game_Process(...);
        
        // ...
        bool success = false;
        try {
            // ... Inyección de samp.dll ...
            // ... Inyección opcional de omp-client.dll ...
            // ... Reanudación del hilo del juego ...
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

Actúa como la primera línea de defensa de la biblioteca, garantizando que solo se procesen datos válidos y seguros. La validación previa previene excepciones de bajo nivel y permite que la biblioteca proporcione mensajes de error claros y accionables.

- **Responsabilidad Principal:** El método estático `Try_Validate` ejecuta una serie de verificaciones, incluyendo el formato del apodo, el rango numérico del puerto y, crucialmente, la existencia de los archivos esenciales (`gta_sa.exe`, `samp.dll`, etc.) en el directorio especificado. Si alguna verificación falla, retorna `false` y llena un `out string` con la descripción del error.

```csharp
// Fragmento de InputValidator.cs
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

Este archivo es el puente entre el código administrado de C# y las APIs nativas no administradas de Windows. Utiliza la característica de interoperabilidad P/Invoke para declarar firmas de funciones de `kernel32.dll`.

- **Responsabilidad Principal:** Declarar métodos `extern` con los atributos `[LibraryImport]` o `[DllImport]` que corresponden a funciones de la API de Windows, como `CreateProcessA`, `VirtualAllocEx` y `CreateRemoteThread`. También define las estructuras de datos (`Startup_Info`, `Process_Information`) con un layout de memoria compatible con el código nativo. Para optimización, los handles para `kernel32.dll` y la dirección de la función `LoadLibraryA` se cargan estáticamente en la inicialización.

```csharp
// Fragmento de NativeImports.cs
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

Es la capa de bajo nivel que ejecuta las operaciones de manipulación de procesos. Utiliza las funciones importadas de `NativeImports.cs` para interactuar directamente con el sistema operativo.

- **Responsabilidades Principales:**
   1. **`Create_Game_Process`**: Construye la línea de comandos e inicia `gta_sa.exe` con el flag `CREATE_SUSPENDED`.
   2. **`Inject_DLL`**: Implementa la técnica de inyección de DLL a través de la creación de un hilo remoto. Esta es la función más crítica, orquestando la asignación de memoria, escritura y ejecución remota de `LoadLibraryA`.
   3. **`Resume_Game_Thread`**: Realiza el paso final de "descongelar" el hilo principal del juego.

```csharp
// Fragmento de ProcessHandler.cs
internal static bool Inject_DLL(SafeProcessHandle process_handle, string dll_path, out string error_message) {
    // ... Asignación y escritura en la memoria remota ...

    IntPtr remote_thread = Native_Imports.CreateRemoteThread(process_handle, IntPtr.Zero, 0, Native_Imports.load_library_address, remote_memory, 0, IntPtr.Zero);

    if (remote_thread == IntPtr.Zero)
        return (error_message = $"Failed to create a remote thread...") != null && false;
    
    // ... Espera la finalización y verifica el resultado ...
    return true;
}
```

### 8. `SafeHandles.cs`

Este archivo implementa una práctica recomendada de interoperabilidad: el uso de `SafeHandle` para gestionar recursos no administrados. Esto garantiza que los "handles" de proceso e hilo de Windows se liberen de forma determinista y segura.

- **Responsabilidad Principal:** Las clases `SafeProcessHandle` y `SafeThreadHandle` heredan de `SafeHandleZeroOrMinusOneIsInvalid`. Encapsulan un `IntPtr` que representa el handle nativo. La principal ventaja es la implementación del método `ReleaseHandle`, que está garantizado por el runtime de .NET para ser llamado cuando el objeto se descarta (por ejemplo, al final de un bloque `using`), previniendo fugas de recursos.

```csharp
// Fragmento de SafeHandles.cs
internal sealed class SafeProcessHandle : SafeHandleZeroOrminusOneIsInvalid {
    // ... Constructores ...

    protected override bool ReleaseHandle() {
        // Esta llamada está garantizada por .NET para liberar el handle nativo.
        return Native_Imports.CloseHandle(handle);
    }
}
```

## Ciclo de Inyección de DLL Detallado

El proceso de inyección de DLL es una secuencia de pasos críticos que deben ejecutarse con precisión para tener éxito. La biblioteca **SA-MP Injector C#** lo orquesta de la siguiente manera:

### 1. Validación de Entrada

Antes de cualquier interacción con el sistema, todos los parámetros proporcionados por el usuario (ruta de la carpeta del juego, apodo, IP, puerto y contraseña) son verificados por `Input_Validator`. Esto incluye:
- Verificar que el apodo esté dentro de los límites de longitud y no esté vacío.
- Asegurar que el puerto sea un número válido y esté en el rango aceptable (1-65535).
- Confirmar que `gta_sa.exe`, `samp.dll` y `omp-client.dll` (si `Injection_Type` es OMP) existan en las rutas esperadas.

> [!NOTE]
> Este paso preventivo es fundamental para evitar fallas inesperadas de la API y proporcionar retroalimentación clara al usuario.

### 2. Creación del Proceso del Juego (Suspendido)

La biblioteca utiliza `Native_Imports.CreateProcessA` para iniciar `gta_sa.exe`. Sin embargo, un detalle crucial es el uso del flag `Constants.CREATE_SUSPENDED`.
- **Creación Suspendida:** Este flag hace que Windows cree el proceso y su hilo principal, pero lo coloca en un estado suspendido, impidiendo que el código del juego comience a ejecutarse.
- **Línea de Comandos:** La línea de comandos se construye cuidadosamente por `Process_Handler.Build_Full_Command_Args_ANSI` para incluir todos los parámetros de conexión del servidor (`-c -n <nickname> -h <ip> -p <port> -z <password>`).
- **Handles de Proceso/Hilo:** `CreateProcessA` devuelve los handles para el proceso y el hilo principal, que se encapsulan en `SafeProcessHandle` y `SafeThreadHandle` para una gestión segura de recursos.

> [!IMPORTANT]
> La creación suspendida es vital para la inyección. Si el juego comenzara a ejecutarse antes de la inyección, podría inicializar sus propios mecanismos de seguridad o la `samp.dll`/`omp-client.dll` podría cargarse antes de nuestro control, haciendo la inyección más compleja o ineficaz.

### 3. Inyección de `samp.dll`

Con el proceso del juego suspendido, la función `Process_Handler.Inject_DLL` ejecuta los siguientes pasos:
1. **Obtener `LoadLibraryA`:** Se obtiene la dirección de la función `LoadLibraryA` (de `kernel32.dll`) en el proceso del juego. Esta es la función que Windows usa para cargar DLLs.
2. **Asignación de Memoria Remota:** Se utiliza `Native_Imports.VirtualAllocEx` para asignar un bloque de memoria dentro del espacio de direcciones virtual del proceso `gta_sa.exe`. El tamaño del bloque es suficiente para almacenar la ruta completa de `samp.dll`.
3. **Escritura de la Ruta de la DLL:** La ruta completa del archivo `samp.dll` se escribe en la memoria recién asignada en el proceso del juego usando `Native_Imports.WriteProcessMemory`.
4. **Creación de Hilo Remoto:** Se llama a `Native_Imports.CreateRemoteThread` para crear un nuevo hilo en el proceso `gta_sa.exe`. A este hilo se le instruye que ejecute `LoadLibraryA` con la dirección de la cadena de la ruta de la DLL como su único argumento.
5. **Esperar Finalización:** La biblioteca espera un tiempo límite (`Constants.DLL_INJECTION_TIMEOUT_MS`) para que el hilo remoto complete su ejecución, indicando que `LoadLibraryA` intentó cargar la DLL.
6. **Verificar Resultado:** Se verifica el código de salida del hilo remoto. Si `LoadLibraryA` tuvo éxito, devuelve la dirección base de la DLL cargada. Un valor cero o una falla en la obtención del código de salida indica que la inyección falló.
7. **Limpieza:** La memoria remota asignada se libera (`Native_Imports.VirtualFreeEx`) y el handle del hilo remoto se cierra (`Native_Imports.CloseHandle`).

### 4. Inyección de `omp-client.dll` (Opcional, Dependiente de SA-MP)

> [!TIP]
> La inyección de `omp-client.dll` **siempre ocurre después de la inyección exitosa de `samp.dll`**. El cliente OMP utiliza la infraestructura de SA-MP, por lo tanto, `samp.dll` es un requisito.

Si el `Injection_Type` especificado es `OMP`, el paso 3 se repite para inyectar `omp-client.dll`. La lógica es idéntica, garantizando que ambas bibliotecas necesarias para OMP se carguen antes de que el juego se inicie por completo.

### Reanudar el Hilo Principal del Juego

Finalmente, después de que todas las DLLs necesarias hayan sido inyectadas con éxito, se llama a la función `Process_Handler.Resume_Game_Thread`. Esta función utiliza `Native_Imports.ResumeThread` para permitir que el hilo principal de `gta_sa.exe` continúe su ejecución. El juego ahora se inicia con las DLLs de SA-MP/OMP ya cargadas y los argumentos de línea de comandos para la conexión al servidor aplicados.

## Manejo de Errores y Casos de Falla

La biblioteca fue diseñada para proporcionar retroalimentación clara en caso de falla. La mayoría de los errores son capturados y se devuelve un `error_message` descriptivo para ser presentado al usuario, generalmente mediante un `MessageBox`.

### Errores de Validación de Entrada

Estos errores ocurren antes de cualquier operación del sistema y son detectados por `Input_Validator`.

#### Nickname Inválido

- **Mensaje de Error (Ejemplo 1):** `"Nickname cannot be empty. Please provide a valid nickname."`
- **Mensaje de Error (Ejemplo 2):** `"Nickname length exceeds the maximum allowed of 23 characters. Please use a shorter nickname."`
- **Por Qué:** El campo de apodo está vacío o excede el límite máximo de 23 caracteres.
- **Solución:** El usuario debe proporcionar un apodo válido que respete el límite de caracteres.

#### Puerto Inválido

- **Mensaje de Error (Ejemplo 1):** `"Invalid port format. The port must be a numeric value. Please provide a valid integer for the port."`
- **Mensaje de Error (Ejemplo 2):** `"The specified port number (70000) is outside the valid range of 1 to 65535. Please provide a valid port."`
- **Por Qué:** El puerto proporcionado no es un número entero, o está fuera del rango válido de 1 a 65535.
- **Solución:** El usuario debe introducir un número de puerto válido y dentro del rango especificado.

#### Archivos de Juego/DLLs Faltantes

- **Mensaje de Error (Ejemplo 1):** `"Game executable not found. Please ensure 'gta_sa.exe' exists at the specified path: C:\Program Files (x86)\Rockstar Games\GTA San Andreas\gta_sa.exe"`
- **Mensaje de Error (Ejemplo 2):** `"SA-MP library not found. Please ensure 'samp.dll' exists at the specified path: C:\Program Files (x86)\Rockstar Games\GTA San Andreas\samp.dll"`
- **Mensaje de Error (Ejemplo 3, OMP):** `"OMP library not found. Please ensure 'omp-client.dll' exists at the specified path for OMP injection: C:\Program Files (x86)\Rockstar Games\GTA San Andreas\omp-client.dll"`
- **Por Qué:** El archivo ejecutable del juego (`gta_sa.exe`), la DLL de SA-MP (`samp.dll`) o la DLL de OMP (`omp-client.dll`) no se encontraron en la carpeta del juego especificada.
- **Solución:** El usuario debe verificar la ruta de la carpeta del juego y asegurarse de que todos los archivos necesarios estén presentes.

### Errores en la Creación del Proceso

Estos errores ocurren cuando la biblioteca intenta iniciar `gta_sa.exe`.

#### Falla al Crear el Proceso

- **Mensaje de Error (Ejemplo):** `"Failed to create game process. Ensure 'gta_sa.exe' is not running and you have sufficient permissions to execute the file. System Error: Access is denied."`
- **Por Qué:**
   - **Archivo en Uso:** `gta_sa.exe` ya puede estar en ejecución, impidiendo que se cree una nueva instancia, o que el sistema operativo tenga un bloqueo sobre el archivo.
   - **Permisos:** El usuario que ejecuta la aplicación puede no tener permisos suficientes para iniciar un nuevo proceso o para acceder al ejecutable del juego.
   - **Ruta Inválida/Corrupta:** Aunque la validación básica verifica la existencia, puede haber problemas de permiso de lectura/ejecución o el ejecutable puede estar dañado.
- **Solución:** Asegúrese de que no haya ninguna otra instancia de `gta_sa.exe` en ejecución. Ejecute la aplicación como administrador, si es posible. Verifique la integridad del archivo `gta_sa.exe`.

### Errores en la Inyección de la DLL

Estos son los errores más críticos y ocurren durante el intento de inyectar `samp.dll` u `omp-client.dll` en el proceso del juego.

#### Handle `kernel32.dll` No Disponible

- **Mensaje de Error:** `"Failed to obtain a handle to kernel32.dll. This is an essential system library and this error indicates a severe system issue."`
- **Por Qué:** La biblioteca `kernel32.dll`, fundamental para las operaciones del sistema en Windows, no pudo ser cargada o su handle no pudo ser obtenido. Esto es extremadamente raro y sugiere un problema grave en el sistema operativo.
- **Solución:** Reiniciar el sistema puede resolverlo. De lo contrario, indica un problema más profundo con la instalación de Windows.

#### Función `LoadLibraryA` No Disponible

- **Mensaje de Error:** `"Failed to find the address of the LoadLibraryA function in kernel32.dll. This is critical for injecting the DLL."`
- **Por Qué:** La función `LoadLibraryA`, esencial para cargar DLLs dinámicamente, no pudo ser encontrada en `kernel32.dll`. Al igual que el error anterior, es un problema de bajo nivel raro.
- **Solución:** Similar a la indisponibilidad del handle de `kernel32.dll`.

#### Falla en la Asignación de Memoria Remota

- **Mensaje de Error:** `"Failed to allocate memory in the target process. This might be due to insufficient permissions or process protection mechanisms."`
- **Por Qué:** La biblioteca no pudo asignar un bloque de memoria en el espacio de direcciones de `gta_sa.exe`.
   - **Permisos:** La aplicación puede no tener los permisos necesarios para modificar el espacio de memoria de otro proceso.
   - **Protección del Proceso:** El proceso `gta_sa.exe` o el sistema operativo pueden estar aplicando protecciones contra la inyección de código.
   - **Espacio de Direcciones:** En casos extremos, el espacio de direcciones del proceso puede estar fragmentado o sin suficiente memoria contigua, aunque es poco probable para el tamaño de una cadena de ruta de DLL.
- **Solución:** Ejecute la aplicación como administrador. Verifique si hay software de seguridad (antivirus, anti-cheat) que pueda estar bloqueando la asignación de memoria en otros procesos.

#### Falla en la Escritura en la Memoria del Proceso

- **Mensaje de Error:** `"Failed to write DLL path to the target process memory. Verify process permissions and ensure the DLL path is accessible."`
- **Por Qué:** La biblioteca asignó memoria en el proceso del juego, pero no pudo escribir la ruta de la DLL en esa ubicación.
   - **Permisos:** Similar a la falla de asignación de memoria, puede ser un problema de permiso de escritura.
   - **Protección:** La protección de memoria del sistema operativo o un anti-cheat pueden estar impidiendo la escritura.
- **Solución:** Verifique los permisos y el software de seguridad.

#### Falla en la Creación del Hilo Remoto

- **Mensaje de Error (Ejemplo):** `"Failed to create a remote thread in the target process to execute the DLL injection. This could be due to security restrictions or process state. System Error: Not enough memory resources are available to process this command."`
- **Por Qué:** La API `CreateRemoteThread` falló al crear un nuevo hilo en el proceso `gta_sa.exe` para llamar a `LoadLibraryA`.
   - **Protección de Proceso/Anti-Cheat:** Muchos sistemas anti-cheat y protecciones del sistema operativo monitorean y bloquean la creación de hilos remotos, ya que es una técnica común de inyección.
   - **Estado del Proceso:** El proceso del juego puede estar en un estado inconsistente que impide la creación de hilos.
- **Solución:** Desactive temporalmente cualquier software anti-cheat o antivirus. Intente ejecutar la aplicación como administrador.

#### Timeout o Error en la Espera por la Inyección

- **Mensaje de Error (Ejemplo):** `"Timeout or error waiting for DLL injection to complete. System Error: The wait operation timed out."`
- **Por Qué:** El hilo remoto (que llama a `LoadLibraryA`) no terminó su ejecución dentro del tiempo límite especificado (10 segundos).
   - **Congelamiento:** `LoadLibraryA` puede haberse bloqueado o tardado excesivamente.
   - **Bloqueo:** Algún mecanismo de seguridad puede haber interceptado y bloqueado la ejecución de `LoadLibraryA` indefinidamente.
- **Solución:** Puede indicar que la DLL está tardando mucho en cargarse o que algo la está impidiendo. Verificar los registros del sistema o del propio SA-MP/OMP (si existen) puede ayudar.

#### Inyección de la DLL Falló o Retornó Error

- **Mensaje de Error:** `"DLL injection failed or returned an error. The LoadLibrary call may have failed in the target process."`
- **Por Qué:** El hilo remoto se completó, pero el código de salida de `LoadLibraryA` indicó una falla (generalmente `0` o `NULL`).
   - **DLL Inexistente/Corrupta:** A pesar de la validación inicial, la DLL puede haber sido movida o dañada entre la validación y la inyección.
   - **Dependencias de la DLL Faltantes:** `samp.dll` u `omp-client.dll` pueden depender de otras DLLs que no están presentes en el directorio del juego o en el PATH del sistema.
   - **Error Interno de la DLL:** La propia DLL puede tener un error interno que le impide cargarse correctamente.
- **Solución:** Verifique la integridad de `samp.dll`/`omp-client.dll`. Asegúrese de que todas las dependencias de la DLL estén presentes.

### Error al Reanudar el Hilo del Juego

Este es el último error posible en el ciclo de inyección.

- **Mensaje de Error (Ejemplo):** `"Failed to resume the game process thread: Invalid handle."`
- **Por Qué:** La API `ResumeThread` falló al reiniciar el hilo principal de `gta_sa.exe`.
   - **Handle Inválido:** El handle del hilo puede haber sido invalidado por alguna razón.
   - **Problema de Permiso:** La aplicación puede no tener permiso para modificar el estado del hilo.
- **Solución:** Intente ejecutar la aplicación como administrador. Si persiste, puede indicar un problema más profundo de estabilidad del sistema o del proceso del juego.

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