# SA-MP Injector C++

<div align="center">

![C++](https://img.shields.io/badge/C%2B%2B-14%2F17%2F20-00599C?style=for-the-badge&logo=cplusplus)
![Platform](https://img.shields.io/badge/Platform-Windows-blue?style=for-the-badge&logo=windows&logoColor=white)
![Architecture](https://img.shields.io/badge/Architecture-x86%20(32--bit)-lightgrey?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)

**Una biblioteca C++ para iniciar y automatizar la conexión de clientes SA-MP y OMP a servidores, mediante inyección de DLLs.**

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

- [SA-MP Injector C++](#sa-mp-injector-c)
  - [Idiomas](#idiomas)
  - [Índice](#índice)
  - [Visión General y Propósito](#visión-general-y-propósito)
  - [Principios de Diseño](#principios-de-diseño)
    - [Totalmente `Header-Only`](#totalmente-header-only)
    - [Gestión Segura de Recursos (RAII)](#gestión-segura-de-recursos-raii)
    - [Robustez y Verificación de Errores](#robustez-y-verificación-de-errores)
    - [Flexibilidad de Estándares C++](#flexibilidad-de-estándares-c)
  - [Entorno Requerido](#entorno-requerido)
    - [Para Desarrollo](#para-desarrollo)
    - [Para Ejecución](#para-ejecución)
  - [Inicio Rápido](#inicio-rápido)
    - [Integración al Proyecto](#integración-al-proyecto)
    - [Ejemplo de Uso Simplificado](#ejemplo-de-uso-simplificado)
  - [Estructura de la Biblioteca](#estructura-de-la-biblioteca)
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
  - [El Proceso Detallado de Inyección](#el-proceso-detallado-de-inyección)
    - [1. Solicitud de Inicialización](#1-solicitud-de-inicialización)
    - [2. Preparación del Entorno](#2-preparación-del-entorno)
    - [3. Verificación de Integridad y Parámetros](#3-verificación-de-integridad-y-parámetros)
    - [4. Preparación de los Argumentos para el Juego](#4-preparación-de-los-argumentos-para-el-juego)
    - [5. Inicialización del Proceso del Juego (Suspendido)](#5-inicialización-del-proceso-del-juego-suspendido)
    - [6. Inyección de la Biblioteca SA-MP (`samp.dll`)](#6-inyección-de-la-biblioteca-sa-mp-sampdll)
    - [7. Inyección de la Biblioteca OMP (`omp-client.dll`) - Condicional](#7-inyección-de-la-biblioteca-omp-omp-clientdll---condicional)
    - [8. Activación del Juego](#8-activación-del-juego)
  - [Diagnóstico de Errores y Fallos](#diagnóstico-de-errores-y-fallos)
    - [Fallos de Validación de Entrada](#fallos-de-validación-de-entrada)
      - [Nombre de Usuario Inválido](#nombre-de-usuario-inválido)
      - [Puerto de Conexión Inválido](#puerto-de-conexión-inválido)
      - [Recursos Esenciales Ausentes](#recursos-esenciales-ausentes)
    - [Fallos en la Gestión del Proceso](#fallos-en-la-gestión-del-proceso)
      - [Dificultad al Iniciar el Proceso del Juego](#dificultad-al-iniciar-el-proceso-del-juego)
    - [Problemas en la Inyección de la DLL](#problemas-en-la-inyección-de-la-dll)
      - [Imposible Localizar `LoadLibraryW`](#imposible-localizar-loadlibraryw)
      - [Fallo en la Reserva de Memoria Remota](#fallo-en-la-reserva-de-memoria-remota)
      - [Incapacidad de Escribir Datos en el Proceso](#incapacidad-de-escribir-datos-en-el-proceso)
      - [Fallo al Crear Hilo de Inyección](#fallo-al-crear-hilo-de-inyección)
      - [Tiempo Límite Excedido o Error en la Espera por la Inyección](#tiempo-límite-excedido-o-error-en-la-espera-por-la-inyección)
      - [Fallo Interno en la Inyección de la DLL](#fallo-interno-en-la-inyección-de-la-dll)
    - [Dificultad al Reanudar la Ejecución del Juego](#dificultad-al-reanudar-la-ejecución-del-juego)
  - [Licencia](#licencia)
    - [Términos y Condiciones de Uso](#términos-y-condiciones-de-uso)
      - [1. Permisos Otorgados](#1-permisos-otorgados)
      - [2. Condiciones Obligatorias](#2-condiciones-obligatorias)
      - [3. Derechos de Autor](#3-derechos-de-autor)
      - [4. Exención de Garantías y Limitación de Responsabilidad](#4-exención-de-garantías-y-limitación-de-responsabilidad)

## Visión General y Propósito

**SA-MP Injector C++** es una biblioteca C++ compacta y de fácil integración, diseñada para automatizar el proceso de inicialización y conexión a servidores de San Andreas Multiplayer (SA-MP) y Open Multiplayer (OMP). A diferencia de iniciar `gta_sa.exe` directamente, esta solución carga programáticamente las bibliotecas `samp.dll` u `omp-client.dll` en el proceso del juego Grand Theft Auto: San Andreas de forma controlada.

Su objetivo principal es capacitar a los desarrolladores de C++ para crear `launchers` personalizados, herramientas de gestión de comunidad o utilidades que necesiten iniciar GTA:SA con parámetros de conexión predefinidos (como nombre de usuario, dirección IP, puerto y contraseña), ofreciendo una experiencia de usuario fluida y automatizada.

## Principios de Diseño

La arquitectura de **SA-MP Injector C++** se fundamenta en principios de diseño modernos, centrándose en la seguridad, la eficiencia y la facilidad de uso.

### Totalmente `Header-Only`

Esta biblioteca se distribuye exclusivamente a través de archivos de cabecera (`.hpp`). Esto simplifica drásticamente la integración en proyectos C++, eliminando la necesidad de compilar bibliotecas separadas, configurar `linkers` o gestionar dependencias de binarios.
- **Integración Instantánea:** Simplemente incluye los `headers` relevantes.
- **Optimización Profunda:** El compilador puede realizar `inlining` agresivo y optimizaciones de `link-time` que resultan en un código final más compacto y rápido.

### Gestión Segura de Recursos (RAII)

La biblioteca emplea el patrón **RAII (Resource Acquisition Is Initialization)** de forma extensiva. Recursos críticos del sistema, como `handles` de procesos y `threads` de Windows, son encapsulados por `std::unique_ptr` con `deleters` personalizados. Esto asegura que, independientemente del flujo de ejecución o de la ocurrencia de excepciones, los recursos siempre se liberen correctamente, previniendo fugas y mejorando la estabilidad de la aplicación.

### Robustez y Verificación de Errores

Cada etapa crítica de la inyección está precedida por validaciones rigurosas y seguida por verificaciones de errores de la API de Windows. Se proporcionan mensajes de error detallados al usuario final a través de cuadros de diálogo, con descripciones del sistema (`GetLastError()`) siempre que sea posible. Este enfoque minimiza la posibilidad de comportamientos indefinidos y ofrece un diagnóstico claro en caso de fallo.

### Flexibilidad de Estándares C++

La biblioteca fue construida para ser compatible con diferentes estándares de C++, desde C++14 hasta C++20. Esto se logra mediante macros condicionales que permiten la utilización de características modernas (como `std::string_view`, `std::filesystem` y `std::optional` de C++17+) cuando están disponibles, mientras se mantiene un `fallback` para construcciones equivalentes en C++14. Este enfoque garantiza una amplia compatibilidad sin sacrificar la modernidad.

## Entorno Requerido

### Para Desarrollo

- **Compilador C++:** Compatible con **C++14 o superior**.
   - Microsoft Visual C++ (Visual Studio 2015, 2017, 2019, 2022)
   - GCC (versión 5 o más reciente)
   - Clang (versión 3.6 o más reciente)
- **Sistema Operativo:** **Windows**.
- **Windows SDK:** Necesario para acceder a las APIs del sistema operativo.
- **Arquitectura de Compilación:** **x86 (32-bit)**. Este es un requisito estricto, ya que `gta_sa.exe` y las DLLs SA-MP/OMP operan exclusivamente en esta arquitectura.

### Para Ejecución

- **Sistema Operativo:** Cualquier versión moderna de **Windows** compatible con el binario compilado.
- **Grand Theft Auto: San Andreas (GTA:SA):** Una instalación válida del juego es obligatoria.
- **DLLs del Cliente SA-MP u OMP:** Los archivos `samp.dll` u `omp-client.dll` deben estar presentes en el directorio raíz del juego, correspondiendo al tipo de inyección deseado.

## Inicio Rápido

La naturaleza `header-only` de la biblioteca facilita su incorporación en cualquier proyecto C++.

### Integración al Proyecto

1. **Descarga los Headers:** Obtén los archivos `.hpp` de la biblioteca (clonando el repositorio o descargándolos directamente).
2. **Organiza los Archivos:** Se recomienda crear una subcarpeta en tu proyecto para los `headers` de la biblioteca, por ejemplo, `MiProyecto/libraries/samp-injector/`.
3. **Define la Arquitectura:** Configura tu proyecto para compilar para la arquitectura **x86 (32-bit)**.

```cpp
// Ejemplo de estructura de directorios
MiProyecto/
├── src/
│   └── main.cpp
├── libraries/
│   └── samp-injector/
│       ├── constants.hpp
│       ├── error_utils.hpp
│       ├── injector.hpp // El encabezado principal a incluir
│       └── ... (otros encabezados)
└── built/ (tu directorio de salida)
```

### Ejemplo de Uso Simplificado

Para automatizar la conexión a un servidor, basta con invocar la función `Initialize_Game` y proporcionar los detalles.

```cpp
#include <iostream>
#include <string>
//
#include "samp-launcher/injector.hpp" // Incluye el encabezado principal

int main() {
    // Parámetros para la inicialización del juego y conexión
    std::wstring inject_type = L"samp"; // O L"omp" para Open Multiplayer
    std::wstring game_folder = L"C:\\Games\\GTA San Andreas"; // Ruta completa de la carpeta de GTA:SA
    std::wstring nickname = L"Nombre";
    std::wstring ip = L"127.0.0.1";
    std::wstring port = L"7777";
    std::wstring password = L""; // Dejar vacío si no hay contraseña

    // La llamada principal para iniciar el juego e inyectar la DLL
    Initialize_Game(inject_type, game_folder, nickname, ip, port, password);

    // En caso de fallo, se muestra automáticamente un cuadro de mensaje de error de Windows.

    return 0;
}
```

## Estructura de la Biblioteca

La biblioteca está cuidadosamente modularizada en varios archivos de cabecera, cada uno con responsabilidades bien definidas, facilitando la organización, el mantenimiento y la reutilización.

### 1. `constants.hpp`

Este archivo es el **repositorio central** de la biblioteca, sirviendo como un repositorio centralizado de todos los valores fijos e inalterables que dictan el comportamiento y la interoperabilidad de **SA-MP Injector C++**. Su organización por categorías lógicas promueve no solo la claridad y la legibilidad del código, sino que también facilita el mantenimiento y garantiza una consistencia rigurosa en todo el ecosistema de la biblioteca.

Cada constante se define con `CONSTEXPR_VAR`, que se expande a `inline constexpr` (para C++17+) o `static constexpr` (para C++14), asegurando que estos valores se evalúen en tiempo de compilación, optimizando el rendimiento y la seguridad de tipos.

La organización de las constantes por categoría facilita la comprensión de su propósito:

- **Constantes Relacionadas con el Juego (`Game Related Constants`)**
   - `MIN_PORT`: Un `int` que define el número de puerto válido más bajo para la conexión a un servidor (valor: `1`).
   - `MAX_PORT`: Un `int` que establece el número de puerto válido más alto para la conexión a un servidor (valor: `65535`).
   - `MAX_NICKNAME_LENGTH`: Un `int` que especifica la longitud máxima permitida para el nickname del jugador (valor: `23` caracteres), un límite impuesto por las especificaciones del cliente SA-MP/OMP.

- **Nombres de Archivos Esenciales (`File Names`)**
   - `SAMP_DLL_NAME`: Un `const wchar_t*` que contiene el nombre del archivo de la biblioteca principal del cliente SA-MP (valor: `L"samp.dll"`). Esencial para la inyección del cliente clásico.
   - `OMP_DLL_NAME`: Un `const wchar_t*` que contiene el nombre del archivo de la biblioteca del cliente Open Multiplayer (valor: `L"omp-client.dll"`). Utilizado específicamente cuando la inyección es del tipo OMP.
   - `GAME_EXE_NAME`: Un `const wchar_t*` que almacena el nombre del archivo ejecutable del juego base Grand Theft Auto: San Andreas (valor: `L"gta_sa.exe"`). El objetivo principal de la inyección.

- **APIs y Funciones del Sistema (`System Libraries and Functions`)**
   - `KERNEL32_DLL`: Un `const wchar_t*` que define el nombre de la biblioteca de sistema de Windows (`L"kernel32.dll"`). Esta DLL es vital, ya que alberga las funciones de manipulación de procesos y memoria que utiliza el inyector. El uso de `wchar_t` garantiza la compatibilidad con las funciones de la API que manejan caracteres anchos, como `GetModuleHandleW`.
   - `LOAD_LIBRARY_FUNC`: Un `const char*` con el nombre de la función para cargar una DLL dinámicamente (valor: `"LoadLibraryW"`). Aunque la biblioteca opera principalmente con caracteres anchos, la función `GetProcAddress` de la API de Windows requiere un nombre de función en formato ANSI (`char*`).

- **Argumentos de Línea de Comandos (`Command Line Arguments`)**
   - Estas constantes definen los prefijos para los argumentos que se pasan a `gta_sa.exe` para configurar la conexión del cliente. Se proporcionan en `Wide Character` (`const wchar_t*`) para compatibilidad con `CreateProcessW`.
      - `CMD_ARG_CONFIG`: Argumento para configuraciones generales (valor: `L"-c"`).
      - `CMD_ARG_NICKNAME`: Argumento para el nickname del jugador (valor: `L"-n"`).
      - `CMD_ARG_HOST`: Argumento para la dirección IP del servidor (valor: `L"-h"`).
      - `CMD_ARG_PORT`: Argumento para el puerto del servidor (valor: `L"-p"`).
      - `CMD_ARG_PASSWORD`: Argumento para la contraseña del servidor (valor: `L"-z"`). Se utiliza solo si se proporciona una contraseña.

- **Identificadores de Tipo de Inyección (`Injection types as strings`)**
   - `INJECT_TYPE_SAMP`: Un `const wchar_t*` para la representación en cadena del tipo de inyección SA-MP (valor: `L"samp"`).
   - `INJECT_TYPE_OMP`: Un `const wchar_t*` para la representación en cadena del tipo de inyección OMP (valor: `L"omp"`).

- **Títulos para Mensajes de Error (`Error message titles`)**
   - `ERROR_TITLE_SAMP`: Un `const wchar_t*` que define el título predeterminado para los cuadros de diálogo de error relacionados con fallos de SA-MP (valor: `L"SA-MP Injector Error - SPC"`).
   - `ERROR_TITLE_OMP`: Un `const wchar_t*` que define el título predeterminado para los cuadros de diálogo de error relacionados con fallos de OMP (valor: `L"OMP Injector Error - SPC"`).

- **Flags de Creación de Proceso (`Process creation`)**
   - `PROCESS_CREATION_FLAGS`: Un `DWORD` que encapsula las banderas pasadas a `CreateProcessW`. Crucialmente, incluye `CREATE_SUSPENDED` (`0x00000004`), que inicia el proceso del juego en un estado pausado, y `DETACHED_PROCESS` (`0x00000008`), que desvincula el nuevo proceso de la consola del proceso padre.

- **Tiempos de Espera (`Timeouts`)**
   - `DLL_INJECTION_TIMEOUT_MS`: Un `DWORD` que especifica el tiempo máximo (en milisegundos) que la biblioteca esperará a que se complete el `thread` remoto responsable de la inyección de la DLL (valor: `10000ms`, o 10 segundos).

- **Flags de Asignación de Memoria (`Memory allocation`)**
   - Estas constantes se utilizan para las llamadas a la API de manipulación de memoria, como `VirtualAllocEx` y `VirtualProtect`.
      - `MEM_COMMIT`: Un `DWORD` que reserva páginas en la memoria virtual y las "confirma" (asigna memoria física) (valor: `0x1000`).
      - `MEM_RESERVE`: Un `DWORD` que solo reserva un rango de espacio de direcciones virtuales para uso posterior (valor: `0x2000`).
      - `MEM_RELEASE`: Un `DWORD` que desconfirma y libera una región de páginas (valor: `0x8000`).
      - `MEMORY_ALLOCATION_TYPE`: Una combinación de `MEM_COMMIT` y `MEM_RESERVE`, utilizada para asignar la memoria inicial para la ruta de la DLL en el proceso remoto.
      - `MEMORY_PROTECTION`: Un `DWORD` que define los permisos de protección de memoria (valor: `PAGE_READWRITE` o `0x04` en la API de Windows), permitiendo la lectura y escritura en la memoria asignada.

### 2. `types.hpp`

Este conciso archivo introduce un `enum class` para tipificar las diferentes modalidades de inyección. El uso de un tipo enumerado, en lugar de cadenas literales, eleva la seguridad del código, previene errores de tipeo y mejora la legibilidad.

- **`Inject_Type`:** Un `enum class` con dos miembros: `SAMP` y `OMP`, que representan los tipos de cliente a inyectar.

```cpp
// Ejemplo de types.hpp
namespace Types {
    enum class Inject_Type {
        SAMP, // Indica inyección para el cliente SA-MP
        OMP // Indica inyección para el cliente Open Multiplayer
    };
}
```

### 3. `version.hpp`

Actuando como un adaptador de compatibilidad, este encabezado detecta dinámicamente el estándar C++ en uso por el compilador. Define macros condicionales (`SAMP_INJECTOR_CXX_14`, `SAMP_INJECTOR_CXX_MODERN`) que guían a la biblioteca a emplear las funcionalidades más avanzadas de C++ (como `std::string_view` o `std::filesystem`) cuando están disponibles, mientras asegura una funcionalidad completa en entornos C++14.

- **`SAMP_INJECTOR_CXX_14`:** Definida si el estándar C++ es C++14.
- **`SAMP_INJECTOR_CXX_MODERN`:** Definida para C++17 o superior, habilitando características del lenguaje más recientes.
- **`SAMP_INJECTOR_NODISCARD`:** Adapta el atributo `[[nodiscard]]` para las versiones de C++ que lo soportan, incentivando la verificación de valores de retorno.

```cpp
// Ejemplo de fragmento relevante de version.hpp
#if (defined(_MSC_VER) && _MSVC_LANG >= 201703L) || __cplusplus >= 201703L
    #define SAMP_INJECTOR_CXX_MODERN // Habilita características modernas de C++17+
#endif

#if defined(SAMP_INJECTOR_CXX_MODERN)
    #define SAMP_INJECTOR_NODISCARD [[nodiscard]] // Usa el atributo nodiscard de C++17
#elif defined(SAMP_INJECTOR_CXX_14)
    #define SAMP_INJECTOR_NODISCARD // Para C++14, el atributo se desactiva
#endif
```

### 4. `error_utils.hpp`

Esta utilidad está dedicada a la gestión y presentación de retroalimentación de errores. Abstrae los mecanismos de Windows para recuperar mensajes de error del sistema y ofrece una interfaz unificada para notificar al usuario sobre problemas.

- **`Get_System_Error_Message`:** Traduce un código de error de Windows (`GetLastError()`) a una `std::wstring` legible, crucial para un diagnóstico preciso.
- **`Show_Error`:** Presenta un cuadro de diálogo (`MessageBoxW`) que contiene el mensaje de error proporcionado, con un título específico para SA-MP u OMP, garantizando una comunicación clara con el usuario.

```cpp
// Ejemplo de fragmento relevante de error_utils.hpp
namespace Error_Utils {
    SAMP_INJECTOR_NODISCARD
    inline std::wstring Get_System_Error_Message(DWORD error_code) {
        if (error_code == 0)
            return L"No error occurred.";
        
        // ... Lógica para formatear el mensaje del sistema ...
    }

    inline void Show_Error(std::wstring_view message, Types::Inject_Type inject_type) {
        const std::wstring title = (inject_type == Types::Inject_Type::SAMP) ? Constants::ERROR_TITLE_SAMP : Constants::ERROR_TITLE_OMP;
        MessageBoxW(nullptr, message.data(), title.c_str(), MB_OK | MB_ICONERROR);
    }
}
```

### 5. `validation.hpp`

Actuando como la primera línea de robustez de la biblioteca, este encabezado proporciona rutinas rigurosas para verificar la validez de los datos de entrada y la presencia de los archivos necesarios. Estas verificaciones se realizan antes de cualquier interacción de bajo nivel con el sistema, mitigando riesgos de `runtime` y proporcionando retroalimentación proactiva.

- **`Validate_Port`:** Valida si la cadena del puerto representa un número entero y si este se encuentra dentro del rango configurado (`MIN_PORT` a `MAX_PORT`).
- **`Validate_Nickname`:** Verifica que el nickname no esté vacío y que su longitud no exceda el `MAX_NICKNAME_LENGTH`.
- **`Validate_Files`:** Confirma la existencia física de `gta_sa.exe`, `samp.dll` y, condicionalmente para la inyección OMP, `omp-client.dll`. La implementación se adapta a `std::filesystem` (C++17+) o `GetFileAttributesW` (C++14).

```cpp
// Ejemplo de fragmento relevante de validation.hpp
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
        
        // ... Otras verificaciones de archivos ...
        return true;
    }
}
```

### 6. `resource_handle.hpp`

Implementa una estrategia elegante y segura para la gestión de recursos del sistema operativo, como los `HANDLE`s de Windows. Utilizando el principio RAII, garantiza que todos los recursos asignados se liberen debidamente, previniendo fugas y fortaleciendo la estabilidad de la aplicación.

- **`Unique_Resource`:** Un `alias template` que adapta `std::unique_ptr` para trabajar con `deleters` personalizados, permitiendo la gestión de cualquier tipo de recurso que necesite una función de liberación específica.
- **`Make_Unique_Handle`:** Una función `factory` conveniente que construye y devuelve un `Unique_Resource` preconfigurado para `HANDLE`s de Windows. El `deleter` asociado invoca `CloseHandle` automáticamente cuando el `Unique_Resource` sale del ámbito, garantizando la desocupación inmediata del recurso.

```cpp
// Ejemplo de fragmento relevante de resource_handle.hpp
namespace Resource_Handle {
    // Un std::unique_ptr personalizado para gestionar recursos del sistema.
    template<typename T, typename Deleter>
    using Unique_Resource = std::unique_ptr<std::remove_pointer_t<T>, Deleter>;

    // Crea un Unique_Resource para un HANDLE, con un deleter que llama a CloseHandle.
    template<typename T>
    inline auto Make_Unique_Handle(T handle) {
        return Unique_Resource<T, std::function<void(T)>>(handle, [](T h) {
            if (h && h != INVALID_HANDLE_VALUE) // Garantiza que el handle sea válido antes de cerrar
                CloseHandle(h);
        });
    }
}
```

### 7. `privileges.hpp`

Este componente es responsable de configurar el entorno de seguridad del proceso de la aplicación. Contiene la funcionalidad para elevar los privilegios, específicamente habilitando el privilegio de depuración (`SE_DEBUG_NAME`), que es un requisito fundamental para que la biblioteca pueda realizar operaciones de inyección de DLL en procesos externos de Windows.

- **`Enable_Debug_Privilege`:** Esta función intenta adquirir y activar el privilegio `SE_DEBUG_NAME` para el proceso en ejecución. Es un paso inicial crucial para conceder a la aplicación los permisos necesarios para manipular otros procesos, como asignar memoria y crear `threads` remotos. Devuelve `true` en caso de éxito.

```cpp
// Ejemplo de fragmento relevante de privileges.hpp
namespace Privileges {
    inline bool Enable_Debug_Privilege() {
        HANDLE token_handle;

        // Intenta abrir el token del proceso actual para ajustar privilegios
        if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &token_handle))
            return false;

        auto handle_guard = Resource_Handle::Make_Unique_Handle(token_handle); // Gestión segura del handle

        TOKEN_PRIVILEGES tp;
        LUID luid;

        // Busca el valor LUID para el privilegio SE_DEBUG_NAME
        if (!LookupPrivilegeValue(nullptr, SE_DEBUG_NAME, &luid))
            return false;
        
        tp.PrivilegeCount = 1;
        tp.Privileges[0].Luid = luid;
        tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED; // Habilita el privilegio

        // Ajusta los privilegios del proceso
        if (!AdjustTokenPrivileges(token_handle, FALSE, &tp, sizeof(TOKEN_PRIVILEGES), nullptr, nullptr))
            return false;

        return GetLastError() == ERROR_SUCCESS; // Devuelve true si la operación fue exitosa (ningún error pendiente)
    }
}
```

### 8. `process.hpp`

Este es uno de los componentes más críticos de la biblioteca, que contiene la implementación de bajo nivel para interactuar con procesos de Windows. Encapsula las complejas operaciones de creación del proceso del juego, asignación de memoria, escritura de datos y la técnica de inyección de DLL a través de la creación de `threads` remotos.

- **struct `Process_Info`:** Una estructura interna que almacena los `Unique_Resource`s para el `HANDLE` del proceso (`process_handle`) y el `HANDLE` del `thread` principal (`thread_handle`) del juego. Incluye un método `Resume()` para reactivar el `thread` principal del juego cuando la inyección esté completa.
- **enum class `Injection_Status`:** Define una lista detallada de posibles resultados para la operación de inyección de DLL, permitiendo un diagnóstico preciso de fallos.
- **`Create_Game_Process`:**
   - Utiliza la función `CreateProcessW` de la API de Windows para iniciar el ejecutable `gta_sa.exe`.
   - Es fundamental que el proceso se cree con la bandera `CREATE_SUSPENDED` (incluida en `Constants::PROCESS_CREATION_FLAGS`). Esto garantiza que el juego se pause inmediatamente después de su creación, antes de que se ejecute cualquier código, permitiendo que la inyección de la DLL ocurra en un estado seguro.
   - Devuelve un `std::optional<Process_Info>` (para C++17+) o un `std::unique_ptr<Process_Info>` (para C++14), que contiene los `handles` encapsulados del proceso y del `thread`.
- **`Inject_DLL`:**
   - Implementa la técnica estándar de inyección de DLL vía `CreateRemoteThread`:
      1. **Obtención de la Dirección:** Utilizando las constantes de `constants.hpp`, localiza la dirección de la función `LoadLibraryW` (de `kernel32.dll`), que Windows utiliza para cargar bibliotecas dinámicamente.
      2. **Asignación de Memoria:** Se utiliza `VirtualAllocEx` para reservar un bloque de memoria virtual dentro del proceso del juego (`gta_sa.exe`). Este bloque se dimensiona para contener la ruta completa de la DLL a inyectar.
      3. **Escritura de la Ruta:** La ruta de la DLL (p. ej., `L"C:\\ruta\\a\\samp.dll"`) se copia luego en la memoria asignada remotamente en el proceso del juego a través de `WriteProcessMemory`.
      4. **Creación del Hilo Remoto:** `CreateRemoteThread` inicia un nuevo `thread` en el contexto del proceso del juego. El punto de entrada de este `thread` es la dirección de `LoadLibraryW`, y el argumento pasado es la dirección de la cadena de la ruta de la DLL que acabamos de escribir.
      5. **Monitoreo:** La ejecución del `thread` remoto se monitorea con `WaitForSingleObject` hasta que se complete o se alcance el `DLL_INJECTION_TIMEOUT_MS`.
      6. **Verificación de Éxito:** Se utiliza `GetExitCodeThread` para verificar el valor de retorno del `thread` remoto. Si `LoadLibraryW` tuvo éxito, devolverá la dirección base de la DLL cargada (un valor distinto de cero).
      7. **Limpieza:** La memoria asignada en el proceso remoto se libera con `VirtualFreeEx`.
   - Devuelve un `Injection_Status` que indica el éxito o el tipo específico de fallo de la inyección.

```cpp
// Ejemplo de fragmento relevante de process.hpp
class Process {
public:
    struct Process_Info {
        Resource_Handle::Unique_Resource<HANDLE, std::function<void(HANDLE)>> process_handle; // Handle del proceso con gestión RAII
        Resource_Handle::Unique_Resource<HANDLE, std::function<void(HANDLE)>> thread_handle; // Handle del hilo con gestión RAII

        bool Resume() { // Reanuda la ejecución del hilo principal del juego
            return thread_handle && ResumeThread(thread_handle.get()) != static_cast<DWORD>(-1);
        }
    };
    
    enum class Injection_Status { // Códigos de estado detallados para la inyección de DLL
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

    // Crea el proceso del juego en estado suspendido
    std::optional<Process_Info> Create_Game_Process(const std::wstring& game_path, std::wstring& command_args, const std::wstring& working_dir) {
        // ... Lógica de CreateProcessW con CREATE_SUSPENDED ...
    }
    
    SAMP_INJECTOR_NODISCARD // Garantiza que el valor de retorno sea utilizado
    Injection_Status Inject_DLL(HANDLE process, const std::wstring& DLL_path) {
        static const LPVOID load_library_addr = reinterpret_cast<LPVOID>(GetProcAddress(GetModuleHandleW(Constants::KERNEL32_DLL), Constants::LOAD_LIBRARY_FUNC));

        if (!load_library_addr)
            return Injection_Status::LOADLIBRARY_ADDRESS_FAILED;

        LPVOID remote_memory = VirtualAllocEx(process, nullptr, (DLL_path.length() + 1) * sizeof(wchar_t), Constants::MEMORY_ALLOCATION_TYPE, Constants::MEMORY_PROTECTION);

        if (!remote_memory)
            return Injection_Status::ALLOCATION_FAILED;

        auto memory_guard = Resource_Handle::Unique_Resource<LPVOID, std::function<void(LPVOID)>>(remote_memory, [process](LPVOID ptr) {
            if (ptr)
                VirtualFreeEx(process, ptr, 0, MEM_RELEASE); // Libera la memoria en el proceso remoto
        });

        if (!WriteProcessMemory(process, remote_memory, DLL_path.c_str(), (DLL_path.length() + 1) * sizeof(wchar_t), nullptr))
            return Injection_Status::WRITE_FAILED;

        HANDLE remote_thread = CreateRemoteThread(process, nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(load_library_addr), remote_memory, 0, nullptr);

        if (!remote_thread)
            return Injection_Status::THREAD_CREATION_FAILED;

        auto thread_guard = Resource_Handle::Make_Unique_Handle(remote_thread); // Gestión segura del handle del hilo remoto

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

Este encabezado define la clase `Injector_Core`, que sirve como el centro de comando de la biblioteca. Orquesta la secuencia lógica de las operaciones de inyección, conectando los módulos de validación de entrada, gestión de privilegios y manipulación de procesos. Es aquí donde se define el flujo de trabajo completo de la inyección.

- **`Injector_Core`:** El constructor de esta clase es el punto donde se llama a `Privileges::Enable_Debug_Privilege()`. Esto garantiza que el proceso de la aplicación posea los privilegios necesarios para realizar operaciones de inyección de DLL antes de que se ejecute cualquier otra lógica crítica.
- **`Initialize_Game`:**
   1. **Validación Exhaustiva:** Comienza llamando a las funciones de validación (`Validation::Validate_Port`, `Validation::Validate_Nickname`, `Validation::Validate_Files`) para asegurar que todos los parámetros y recursos esenciales estén en orden. Si alguna validación falla, se informa un error inmediatamente.
   2. **Preparación de Argumentos:** Construye la línea de comandos completa (`std::wstring`) que se pasará a `gta_sa.exe`, incorporando el nickname, IP, puerto y contraseña proporcionados.
   3. **Creación del Proceso Suspendido:** Invoca `Process::Create_Game_Process` para iniciar `gta_sa.exe` en un estado suspendido, obteniendo los `handles` del proceso y del `thread` principal.
   4. **Inyección de `samp.dll`:** Llama a `Inject_DLL_With_Status_Check` para inyectar `samp.dll` en el proceso del juego. Esta función wrapper también es responsable de interpretar el `Injection_Status` devuelto y mostrar mensajes de error informativos.
   5. **Inyección Condicional de `omp-client.dll`:** Si el `inject_type` es `Types::Inject_Type::OMP`, se inyecta `omp-client.dll` de la misma manera que `samp.dll`.
   6. **Reanudación del Juego:** Después de todas las inyecciones exitosas, se llama a `process_info.Resume()` para permitir que el `thread` principal del juego continúe su ejecución.
   7. **Manejo de Errores en el Ciclo:** Cualquier fallo en cualquiera de estos pasos críticos resultará en una llamada a `Error_Utils::Show_Error`, proporcionando retroalimentación clara al usuario y asegurando que el proceso se cierre correctamente (los `handles` se liberan automáticamente por los `Unique_Resource`s).
- **`Build_Command_Args`:** Una función auxiliar que organiza y concatena los argumentos de la línea de comandos, añadiendo comillas donde sea necesario para parámetros que contengan espacios.
- **`Inject_DLL_With_Status_Check`:** Una función privada que actúa como un envoltorio para `Process::Inject_DLL`. Mapea los diferentes `Injection_Status` a mensajes de error comprensibles, facilitando el manejo de errores y la comunicación con el usuario.

```cpp
// Ejemplo de fragmento relevante de injector_core.hpp
namespace Injector {
    class Injector_Core {
    public:
        Injector_Core() { // El constructor habilita el privilegio de depuración
            Privileges::Enable_Debug_Privilege();
        }

        bool Initialize_Game(Types::Inject_Type inject_type, std::wstring_view folder, std::wstring_view nickname, std::wstring_view ip, std::wstring_view port, std::wstring_view password) {
            std::wstring error_message;

            // Secuencia de validaciones de entrada
            if (!Validation::Validate_Port(port, error_message))
                return (Error_Utils::Show_Error(error_message, inject_type), false);
            // ... otras validaciones ...

            // Construye los argumentos de la línea de comandos
            std::wstring args = Build_Command_Args({
                Command_Arg{Constants::CMD_ARG_NICKNAME, std::wstring(nickname)},
                // ... otros argumentos ...
            });

            Process process_core;
            // Crea el proceso del juego en estado suspendido
            auto process_info_opt = process_core.Create_Game_Process(game_path, args, std::wstring(folder));

            if (!process_info_opt)
                return false;

            auto& process_info = *process_info_opt;

            // Inyecta samp.dll y, condicionalmente, omp-client.dll
            if (!Inject_DLL_With_Status_Check(process_core, process_info.process_handle.get(), Constants::SAMP_DLL_NAME, samp_DLL_path.wstring(), inject_type))
                return false;
            
            if (inject_type == Types::Inject_Type::OMP) {
                if (!Inject_DLL_With_Status_Check(process_core, process_info.process_handle.get(), Constants::OMP_DLL_NAME, omp_DLL_path.wstring(), inject_type))
                    return false;
            }
            
            // Reanuda el hilo principal del juego
            if (!process_info.Resume())
                return (Error_Utils::Show_Error(L"Failed to resume the game process thread: " + Error_Utils::Get_System_Error_Message(GetLastError()), inject_type), false);

            return true;
        }
    };
}
```

### 10. `injector.hpp`

Este encabezado actúa como la fachada (`Facade`) principal de la biblioteca, ofreciendo un punto de entrada simplificado para cualquier aplicación que desee utilizar la funcionalidad de inyección. Abstrae la complejidad interna de `Injector_Core` en una única y conveniente función.

- **`Initialize_Game`:**
   - Esta función estática es la interfaz pública de la biblioteca.
   - Primero, valida la `inject_type_str` (si es `L"samp"` o `L"omp"`) y la convierte al `enum class Types::Inject_Type`. En caso de una cadena inválida, muestra un error y termina.
   - Luego, crea una instancia de `Injector::Injector_Core`.
   - Finalmente, delega la ejecución de la lógica principal a `Injector_Core::Initialize_Game`, que es donde se orquesta todo el proceso de validación, creación de proceso e inyección de DLL.

```cpp
// Ejemplo de fragmento relevante de injector.hpp
// La interfaz pública para iniciar el juego
#if defined(SAMP_INJECTOR_CXX_MODERN)
inline bool Initialize_Game(std::wstring_view inject_type, std::wstring_view folder, std::wstring_view nickname, std::wstring_view ip, std::wstring_view port, std::wstring_view password) {
#elif defined(SAMP_INJECTOR_CXX_14)
inline bool Initialize_Game(const std::wstring& inject_type, const std::wstring& folder, const std::wstring& nickname, const std::wstring& ip, const std::wstring& port, const std::wstring& password) {
#endif
    Types::Inject_Type type;

    // Convierte la cadena de tipo de inyección al enum correspondiente
    if (inject_type == Constants::INJECT_TYPE_SAMP)
        type = Types::Inject_Type::SAMP;
    else if (inject_type == Constants::INJECT_TYPE_OMP)
        type = Types::Inject_Type::OMP;
    else
        // Muestra un error si el tipo de inyección es inválido
        return (Error_Utils::Show_Error(L"Modo de inyección inválido. Use 'samp' u 'omp'.", Types::Inject_Type::SAMP), false);

    Injector::Injector_Core injector; // Crea la instancia del núcleo del inyector

    // Delega la lógica principal al Injector_Core
    return injector.Initialize_Game(type, folder, nickname, ip, port, password);
}
```

## El Proceso Detallado de Inyección

La funcionalidad central de esta biblioteca es orquestar una secuencia precisa de operaciones para inyectar las DLLs del cliente SA-MP u OMP en el proceso de GTA:SA. Este ciclo está cuidadosamente planificado para garantizar la estabilidad y la compatibilidad.

### 1. Solicitud de Inicialización

El proceso se inicia con la llamada a la función global `Initialize_Game` (`injector.hpp`), que actúa como el principal punto de contacto para la aplicación que utiliza la biblioteca. Esta función recibe todos los parámetros cruciales, como el tipo de inyección deseado (SA-MP u OMP), el directorio del juego y los datos de conexión al servidor (nickname, IP, puerto, contraseña).

### 2. Preparación del Entorno

Al ser invocada, la función `Initialize_Game` crea una instancia de `Injector::Injector_Core`. En el constructor de esta clase (`injector_core.hpp`), se ejecuta el primer y esencial paso de configuración del entorno: la elevación de privilegios.

> [!NOTE]
> `Privileges::Enable_Debug_Privilege()`: Esta llamada (`privileges.hpp`) concede al proceso de la aplicación el privilegio `SE_DEBUG_NAME`. Este privilegio es vital, ya que permite que la aplicación ejecute operaciones de bajo nivel en otros procesos de Windows, como leer y escribir en su memoria y crear `threads` remotos, acciones fundamentales para la técnica de inyección de DLL.

### 3. Verificación de Integridad y Parámetros

Con los privilegios ajustados, el método `Injector_Core::Initialize_Game` procede con una serie de validaciones rigurosas. Esta es una fase preventiva que minimiza la posibilidad de fallos en etapas posteriores y proporciona retroalimentación inmediata al usuario.

- **Validación del Puerto:** `Validation::Validate_Port` verifica que el número del puerto de conexión esté formateado correctamente y se encuentre dentro del rango de `1` a `65535` (`constants.hpp`).
- **Validación del nickname:** `Validation::Validate_Nickname` garantiza que el nickname del jugador no esté vacío y no exceda el límite de `23` caracteres.
- **Verificación de Archivos Esenciales:** `Validation::Validate_Files` inspecciona el directorio del juego para confirmar la presencia de `gta_sa.exe`, `samp.dll` y, si la inyección es del tipo OMP, también `omp-client.dll`.

> [!WARNING]
> Cualquier fallo en esta etapa resulta en la exhibición inmediata de un `MessageBox` con un mensaje de error detallado (`error_utils.hpp`) y la interrupción del proceso de inyección. Esto evita intentos inútiles de proceder con una configuración inválida.

### 4. Preparación de los Argumentos para el Juego

Tras una validación exitosa, la función `Injector_Core::Build_Command_Args` es responsable de construir la línea de comandos formateada que se pasará a `gta_sa.exe`. Esta línea de comandos incluye todos los parámetros necesarios para que el cliente SA-MP/OMP se conecte automáticamente a un servidor, como `-n "nickname" -h "IP" -p "Puerto" -z "Contraseña"`.

### 5. Inicialización del Proceso del Juego (Suspendido)

El componente `Process` (`process.hpp`) se encarga entonces de iniciar el ejecutable de GTA:SA.

> [!IMPORTANT]
> La función `Process::Create_Game_Process` utiliza la bandera `CREATE_SUSPENDED` (`constants.hpp`) al llamar a la API `CreateProcessW` de Windows. Esta es una medida de diseño crítica: el juego se carga en la memoria y se crea su `thread` principal, pero su ejecución es **pausada**. Esto crea un entorno controlado y estable, ideal para la inyección de DLLs, antes de que el juego pueda inicializar sus propias defensas o lógicas internas. Los `handles` del proceso y del `thread` se obtienen y gestionan de forma segura a través de `Resource_Handle::Unique_Resource`.

### 6. Inyección de la Biblioteca SA-MP (`samp.dll`)

Con el proceso del juego en estado de suspensión, la inyección de `samp.dll` puede realizarse de forma segura. El método `Injector_Core::Inject_DLL_With_Status_Check` delega esta tarea a `Process::Inject_DLL`, que ejecuta los siguientes pasos de la técnica de `remote thread injection`:

1. **Localización de la Función `LoadLibraryW`:** Se identifica la dirección de la función `LoadLibraryW`. Esta operación utiliza las constantes `Constants::KERNEL32_DLL` y `Constants::LOAD_LIBRARY_FUNC` para obtener un `handle` para `kernel32.dll` y, a continuación, localizar la dirección de la función de carga de bibliotecas dinámicas.
2. **Asignación de Memoria Remota:** Se utiliza `VirtualAllocEx` para reservar un bloque de memoria en el espacio de direcciones virtuales del proceso `gta_sa.exe` (que está suspendido). El tamaño de este bloque es suficiente para almacenar la ruta completa de `samp.dll`.
3. **Escritura de la Ruta de la DLL:** La ruta completa del archivo `samp.dll` se escribe en esta memoria remota recién asignada mediante `WriteProcessMemory`.
4. **Creación de Hilo Remoto:** Se llama a `CreateRemoteThread` para crear un nuevo `thread` dentro del proceso `gta_sa.exe`. El punto de entrada de este nuevo `thread` es la dirección de `LoadLibraryW`, y el argumento que recibe es el puntero a la ruta de la DLL que acabamos de escribir.
5. **Monitoreo de la Inyección:** La ejecución del `thread` remoto se monitorea con `WaitForSingleObject` por un período definido por `Constants::DLL_INJECTION_TIMEOUT_MS`.
6. **Verificación del Resultado:** El código de salida del `thread` remoto se obtiene a través de `GetExitCodeThread`. Un valor de retorno diferente de cero indica que `LoadLibraryW` tuvo éxito al cargar `samp.dll`.

> [!WARNING]
> En caso de cualquier fallo durante la inyección de `samp.dll`, se muestra un mensaje de error específico (`error_utils.hpp`), se aborta el proceso de inyección y se liberan los recursos.

### 7. Inyección de la Biblioteca OMP (`omp-client.dll`) - Condicional

Si el tipo de inyección especificado es `OMP`, los pasos detallados en el punto 6 se repiten para `omp-client.dll`.

> [!TIP]
> La inyección de `omp-client.dll` siempre ocurre después de la inyección exitosa de `samp.dll`. Esto se debe a que el cliente Open Multiplayer se basa en la infraestructura proporcionada por `samp.dll`.

### 8. Activación del Juego

Finalmente, si todas las inyecciones se completaron con éxito, se invoca el método `process_info.Resume()`. Esta llamada ejecuta `ResumeThread` en el `thread` principal de `gta_sa.exe`. En este momento, el juego se activa e inicia su ejecución normal, pero ya con las DLLs de SA-MP/OMP cargadas en su memoria y con los parámetros de conexión configurados, permitiendo una conexión automatizada al servidor.

> [!WARNING]
> Si la reanudación del `thread` del juego falla, se presenta un último mensaje de error al usuario.

## Diagnóstico de Errores y Fallos

La biblioteca está meticulosamente diseñada para comunicar claramente cualquier problema que pueda surgir durante el proceso de inicialización e inyección. En cualquier punto de fallo, se presenta al usuario un `MessageBox` con una descripción detallada, a menudo complementada con mensajes de error del sistema operativo.

### Fallos de Validación de Entrada

Estos errores se detectan en la fase inicial (`validation.hpp`), antes de cualquier interacción de bajo nivel con el sistema, e indican problemas con los datos proporcionados por el usuario o con la configuración del entorno.

#### Nombre de Usuario Inválido

- **Mensaje de Error (Ejemplo 1):** `"Nickname cannot be empty. Please provide a valid nickname."`
- **Mensaje de Error (Ejemplo 2):** `"Nickname length exceeds the maximum allowed of 23 characters. Please use a shorter nickname."`
- **Razón:** El nombre de usuario (`nickname`) proporcionado está vacío o supera el límite máximo de 23 caracteres permitido por los clientes SA-MP/OMP.
- **Solución:** El usuario debe introducir un nombre de usuario válido que respete los criterios de longitud.

#### Puerto de Conexión Inválido

- **Mensaje de Error (Ejemplo 1):** `"Invalid port format. The port must be a numeric value. Please provide a valid integer for the port."`
- **Mensaje de Error (Ejemplo 2):** `"The specified port number (70000) is outside the valid range of 1 to 65535. Please provide a valid port."`
- **Razón:** El valor proporcionado para el puerto no es un número entero o está fuera del rango válido (1 a 65535).
- **Solución:** El usuario necesita proporcionar un número de puerto válido y dentro del rango especificado.

#### Recursos Esenciales Ausentes

- **Mensaje de Error (Ejemplo 1):** `"Game executable not found. Please ensure 'gta_sa.exe' exists at the specified path: C:\Games\GTA San Andreas\gta_sa.exe"`
- **Mensaje de Error (Ejemplo 2):** `"SA-MP library not found. Please ensure 'samp.dll' exists at the specified path: C:\Games\GTA San Andreas\samp.dll"`
- **Mensaje de Error (Ejemplo 3, para OMP):** `"OMP library not found. Please ensure 'omp-client.dll' exists at the specified path for OMP injection: C:\Games\GTA San Andreas\omp-client.dll"`
- **Razón:** Uno o más archivos cruciales (`gta_sa.exe`, `samp.dll`, `omp-client.dll`) no se encontraron en el directorio del juego especificado.
- **Solución:** Verifica la ruta de la carpeta del juego y asegúrate de que todos los archivos necesarios estén presentes y accesibles.

### Fallos en la Gestión del Proceso

Estos errores ocurren cuando la biblioteca intenta iniciar el ejecutable del juego (`gta_sa.exe`).

#### Dificultad al Iniciar el Proceso del Juego

- **Mensaje de Error (Ejemplo):** `"Failed to create game process. Ensure 'gta_sa.exe' is not running and you have sufficient permissions to execute the file. System Error: Access is denied."`
- **Razón:**
   - **Ejecutable en Uso:** `gta_sa.exe` ya puede estar en ejecución, o hay algún bloqueo del sistema operativo que impide la creación de una nueva instancia.
   - **Permisos Insuficientes:** La aplicación puede no tener los permisos adecuados para iniciar `gta_sa.exe` o para acceder al archivo.
   - **Ejecutable Corrupto:** Aunque la validación básica verifica la existencia del archivo, este puede estar corrupto o inaccesible.
- **Solución:** Asegúrate de que ninguna instancia de `gta_sa.exe` esté activa. Intenta ejecutar tu aplicación como administrador. Verifica la integridad del archivo `gta_sa.exe`.

### Problemas en la Inyección de la DLL

Estos son los errores más críticos y detallados, que ocurren durante el intento de inyectar `samp.dll` u `omp-client.dll` en el proceso suspendido del juego. Los mensajes de error generalmente comienzan con `"Failed to inject <DLL_NAME>:\n"` y van seguidos de una descripción específica y un código de error del sistema.

#### Imposible Localizar `LoadLibraryW`

- **Mensaje de Error (Parte):** `"Failed to find the address of LoadLibraryW in kernel32.dll."`
- **Razón:** La función `LoadLibraryW`, una API fundamental de Windows para la carga dinámica de DLLs, no pudo ser encontrada en `kernel32.dll`. Este es un problema de bajo nivel extremadamente raro, que apunta a una posible corrupción del sistema operativo o un entorno de ejecución muy inusual.
- **Solución:** Un reinicio del sistema puede resolverlo. Si persiste, podría indicar un problema más grave en la instalación de Windows.

#### Fallo en la Reserva de Memoria Remota

- **Mensaje de Error (Parte):** `"Failed to allocate memory in the target process (VirtualAllocEx). System Error: Not enough storage is available to process this command."`
- **Razón:** La biblioteca no pudo asignar un bloque de memoria en el espacio de direcciones virtuales del proceso `gta_sa.exe`.
   - **Permisos:** Tu aplicación puede no tener permisos suficientes para modificar el espacio de memoria de otro proceso.
   - **Protección de Proceso:** Mecanismos de seguridad del sistema operativo o software anti-cheat podrían estar bloqueando la asignación de memoria en procesos externos.
- **Solución:** Ejecuta tu aplicación como administrador. Verifica si programas de seguridad (antivirus, anti-cheat) están interfiriendo y, si es posible, desactívalos temporalmente para probar.

#### Incapacidad de Escribir Datos en el Proceso

- **Mensaje de Error (Parte):** `"Failed to write DLL path to process memory (WriteProcessMemory). System Error: Access is denied."`
- **Razón:** Se asignó memoria en el proceso del juego, pero la biblioteca no pudo escribir la ruta de la DLL en esa ubicación.
   - **Permisos/Protección:** Similar al fallo de asignación de memoria, puede ser un problema de permiso de escritura o una protección de memoria activa.
- **Solución:** Se aplican las mismas soluciones que para el fallo de asignación de memoria.

#### Fallo al Crear Hilo de Inyección

- **Mensaje de Error (Parte):** `"Failed to create remote thread (CreateRemoteThread). System Error: The parameter is incorrect."`
- **Razón:** La API `CreateRemoteThread` falló al iniciar un nuevo `thread` en el proceso `gta_sa.exe` para invocar `LoadLibraryW`.
   - **Seguridad:** Muchos sistemas anti-cheat y protecciones del SO monitorean y bloquean la creación de `threads` remotos, ya que es una técnica común de inyección.
   - **Estado del Proceso:** El proceso del juego puede estar en un estado inestable que impide la creación de `threads`.
- **Solución:** Desactiva temporalmente cualquier software anti-cheat o antivirus. Intenta ejecutar la aplicación como administrador.

#### Tiempo Límite Excedido o Error en la Espera por la Inyección

- **Mensaje de Error (Parte):** `"Timeout or error waiting for remote thread (WaitForSingleObject). System Error: The wait operation timed out."`
- **Razón:** El `thread` remoto (que llama a `LoadLibraryW`) no completó su ejecución dentro del tiempo límite establecido (10 segundos).
   - **Congelamiento:** `LoadLibraryW` puede haberse bloqueado, tardado excesivamente, o haber sido interceptado/bloqueado.
- **Solución:** Esto puede indicar que la DLL está teniendo dificultades para cargarse o que algo lo está impidiendo. Verificar los registros del sistema o del propio SA-MP/OMP (si están disponibles) puede ofrecer más pistas.

#### Fallo Interno en la Inyección de la DLL

- **Mensaje de Error (Parte):** `"LoadLibraryW call failed in the target process. The DLL might be corrupt, missing dependencies, or blocked by security software."`
- **Razón:** El `thread` remoto se completó, pero el valor de retorno de `LoadLibraryW` fue `0` (o `NULL`), lo que indica que la DLL no se cargó con éxito.
   - **DLL Corrupta/Inexistente:** La DLL puede haber sido movida, eliminada o corrompida después de la validación inicial.
   - **Dependencias Ausentes:** `samp.dll` u `omp-client.dll` pueden tener dependencias (otras DLLs) que no están presentes en el directorio del juego o en el `PATH` del sistema.
   - **Error Interno de la DLL:** La propia DLL puede tener un error interno que impide su carga.
- **Solución:** Verifica la integridad de los archivos `samp.dll`/`omp-client.dll`. Asegúrate de que todas sus dependencias estén presentes.

### Dificultad al Reanudar la Ejecución del Juego

Este es el último punto de fallo posible en el ciclo de inyección.

- **Mensaje de Error (Ejemplo):** `"Failed to resume the game process thread: Invalid handle."`
- **Razón:** La API `ResumeThread` falló al reactivar el `thread` principal de `gta_sa.exe`.
   - **Handle Inválido:** El `handle` del `thread` puede haber sido invalidado por algún evento inesperado.
   - **Permiso:** La aplicación puede no tener permiso para alterar el estado del `thread`.
- **Solución:** Intenta ejecutar la aplicación como administrador. Si el problema persiste, puede indicar un problema de estabilidad más profundo en el sistema o en el proceso del juego.

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