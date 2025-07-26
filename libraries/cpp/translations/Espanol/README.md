# SA-MP Injector C++

![License](https://img.shields.io/badge/License-MIT-yellow.svg?style=flat)
![C++17](https://img.shields.io/badge/C%2B%2B-17-blue.svg?style=flat&logo=cplusplus)
![Platform](https://img.shields.io/badge/Platform-Windows-0078D6.svg?style=flat&logo=windows)
[![SA-MP | OMP](https://img.shields.io/badge/Support-SA--MP%20%7C%20OMP-yellow)](https://github.com/spc-samp/samp-injector)
![Code Quality](https://img.shields.io/badge/Code%20Quality-High-brightgreen.svg?style=flat)

El **SA-MP Injector C++** trasciende la definición de una simple herramienta de **inyección de DLL**. Es una **biblioteca C++** cuidadosamente diseñada, proyectada para proporcionar una solución robusta y completa para la inicialización programática del juego **Grand Theft Auto: San Andreas** (**GTA:SA**) en conjunto con sus clientes multijugador, específicamente **SA-MP (San Andreas Multiplayer)** y **OMP (Open Multiplayer)**. Su objetivo principal es simplificar el proceso de lanzamiento del juego, eliminando la complejidad inherente a la manipulación directa de procesos del sistema operativo y al paso de argumentos de línea de comandos.

Desarrollada con el propósito de ofrecer máxima flexibilidad e integración facilitada, esta biblioteca `header-only` elimina la necesidad de compilaciones previas complejas, permitiendo que los desarrolladores la incorporen directamente en sus **proyectos C++**. No solo orquesta la **inyección fundamental de las DLLs** del cliente multijugador (`samp.dll` o `omp-client.dll`), sino que también gestiona inteligentemente todos los parámetros esenciales de conexión (**nickname**, **dirección IP**, **puerto** y **contraseña**), simulando una inicialización nativa a través de los recursos intrínsecos de la **Windows API**.

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
  - [Conceptos Fundamentales y Motivación](#conceptos-fundamentales-y-motivación)
    - [¿Por qué Inyectar DLLs?](#por-qué-inyectar-dlls)
    - [SA-MP y OMP: Distinciones y Similitudes](#sa-mp-y-omp-distinciones-y-similitudes)
  - [Arquitectura Interna de la Biblioteca: Una Inmersión Profunda](#arquitectura-interna-de-la-biblioteca-una-inmersión-profunda)
    - [`constants.hpp`](#constantshpp)
    - [`types.hpp`](#typeshpp)
    - [`string_utils.hpp`](#string_utilshpp)
    - [`error_utils.hpp`](#error_utilshpp)
    - [`resource_handle.hpp`](#resource_handlehpp)
    - [`validation.hpp`](#validationhpp)
    - [`process.hpp`](#processhpp)
    - [`injector_core.hpp`](#injector_corehpp)
    - [`injector.hpp`](#injectorhpp)
  - [Ejemplos Completos de Utilización](#ejemplos-completos-de-utilización)
    - [1. Preparación del Ambiente de Desarrollo](#1-preparación-del-ambiente-de-desarrollo)
    - [2. Escenario Básico: Conectando a un Servidor SA-MP](#2-escenario-básico-conectando-a-un-servidor-sa-mp)
    - [3. Escenario Avanzado: Conectando a un Servidor OMP](#3-escenario-avanzado-conectando-a-un-servidor-omp)
  - [Tratamiento de Errores Comunes y Mensajes](#tratamiento-de-errores-comunes-y-mensajes)
    - [1. Tipo de Inyección Inválido](#1-tipo-de-inyección-inválido)
    - [2. Puerto del Servidor Inválido (Formato o Rango)](#2-puerto-del-servidor-inválido-formato-o-rango)
      - [2.1. Formato de Puerto No Numérico](#21-formato-de-puerto-no-numérico)
      - [2.2. Puerto Fuera del Rango Válido](#22-puerto-fuera-del-rango-válido)
    - [3. Nickname Inválido (Vacío o Muy Largo)](#3-nickname-inválido-vacío-o-muy-largo)
      - [3.1. Nickname Vacío](#31-nickname-vacío)
      - [3.2. Nickname Muy Largo](#32-nickname-muy-largo)
    - [4. Archivos del Juego o DLL No Encontrados](#4-archivos-del-juego-o-dll-no-encontrados)
      - [4.1. Ejecutable del Juego (`gta_sa.exe`) No Encontrado](#41-ejecutable-del-juego-gta_saexe-no-encontrado)
      - [4.2. Biblioteca SA-MP (`samp.dll`) No Encontrada](#42-biblioteca-sa-mp-sampdll-no-encontrada)
      - [4.3. Biblioteca OMP (`omp-client.dll`) No Encontrada (solo para inyección OMP)](#43-biblioteca-omp-omp-clientdll-no-encontrada-solo-para-inyección-omp)
    - [5. Falla en la Creación del Proceso del Juego](#5-falla-en-la-creación-del-proceso-del-juego)
    - [6. Falla en la Asignación de Memoria en el Proceso Objetivo](#6-falla-en-la-asignación-de-memoria-en-el-proceso-objetivo)
    - [7. Falla en la Escritura del Camino de la DLL en la Memoria del Proceso](#7-falla-en-la-escritura-del-camino-de-la-dll-en-la-memoria-del-proceso)
    - [8. Falla al Encontrar Funciones Esenciales del Sistema](#8-falla-al-encontrar-funciones-esenciales-del-sistema)
      - [8.1. `kernel32.dll` No Encontrado](#81-kernel32dll-no-encontrado)
      - [8.2. `LoadLibraryA` No Encontrado](#82-loadlibrarya-no-encontrado)
    - [9. Fallo al Crear un Hilo Remoto para la Inyección](#9-fallo-al-crear-un-hilo-remoto-para-la-inyección)
    - [10. Tiempo de Espera Agotado o Fallo en la Finalización de la Inyección](#10-tiempo-de-espera-agotado-o-fallo-en-la-finalización-de-la-inyección)
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

En el contexto de juegos como el **GTA San Andreas**, que no fueron originalmente desarrollados con funcionalidad multijugador integrada, la **inyección de DLLs** es la base para la existencia de clientes multijugador como **SA-MP** y **OMP**. Estos clientes se implementan como **DLLs** que, una vez inyectadas en el proceso del `gta_sa.exe`, asumen el control, interceptan funciones del juego y establecen comunicación con servidores multijugador.

En lugar de depender de un lanzador externo o de la modificación directa del ejecutable del juego, la **inyección de DLL** permite una inicialización más flexible y programable, especialmente útil en entornos donde se desea automatizar el proceso de conexión a servidores específicos con configuraciones predefinidas.

### SA-MP y OMP: Distinciones y Similitudes

El **SA-MP** y el **OMP** son las dos principales plataformas de multijugador para **GTA San Andreas**. Ambos funcionan como modificaciones del juego base, transformándolo en un entorno en línea masivamente multijugador.

- **SA-MP (San Andreas Multiplayer)**: El cliente original y más consolidado, ampliamente utilizado durante muchos años. Su arquitectura requiere la `samp.dll` para operar.
- **OMP (Open Multiplayer)**: Un proyecto de código abierto, generalmente visto como un sucesor o alternativa más moderna al **SA-MP**, ofreciendo mejoras de rendimiento, estabilidad y funcionalidades adicionales. Requiere la `omp-client.dll`.

Aunque operan de manera similar (**inyectando una DLL** en el proceso del **GTA:SA**), la biblioteca **SA-MP Injector C++** fue cuidadosamente desarrollada para soportar **ambas DLLs**, reconociendo sus distinciones de nombres de archivo y permitiendo que el desarrollador elija el cliente multijugador deseado a través de un parámetro de configuración. Esto asegura que la biblioteca pueda ser utilizada con la amplia gama de servidores y proyectos basados en cualquiera de las plataformas.

## Arquitectura Interna de la Biblioteca: Una Inmersión Profunda

El **SA-MP Injector C++** adopta un enfoque modular y orientado a objetos (donde aplica) para gestionar la complejidad del proceso de inyección. Cada archivo de cabecera es un módulo especializado, responsable de una porción específica de la funcionalidad general, promoviendo la claridad del código, la mantenibilidad y la expansibilidad.

### `constants.hpp`

Este archivo es la base de todas las configuraciones fijas de la biblioteca. Define un namespace `Constants` para encapsular todas las literales, garantizando que no haya contaminación del ámbito global. El uso de `inline constexpr` es crucial aquí: `constexpr` indica que los valores se evalúan en tiempo de compilación, optimizando el rendimiento y garantizando la inmutabilidad, mientras que `inline` evita problemas de redefinición al incluir el archivo en múltiples unidades de compilación.

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
    inline constexpr const char* LOAD_LIBRARY_FUNC = "LoadLibraryA"; // 'A' para versión ANSI/8-bit
    
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
> El uso de `wchar_t` para nombres de archivos y títulos de mensajes de error es una práctica recomendada en **desarrollo Windows**. Esto garantiza la compatibilidad con todos los idiomas y conjuntos de caracteres, especialmente útil para rutas de archivo que pueden contener **caracteres Unicode**. Para **APIs** que esperan `char` (como `LoadLibraryA`), la conversión se realiza explícitamente en `string_utils.hpp`.

### `types.hpp`

Un módulo conciso, pero esencial, para definir la enumeración que categoriza los tipos de inyección soportados. Esto mejora la legibilidad y la seguridad de tipo del código, previniendo errores de string o enteros mágicos.

```cpp
#pragma once

namespace Types {
    // Enumeraciones para tipos de inyección soportados
    enum class Inject_Type {
        SAMP, // San Andreas Multiplayer
        OMP // Open Multiplayer
    };
}
```

### `string_utils.hpp`

Operar con la **API de Windows** frecuentemente requiere la conversión entre diferentes codificaciones de strings. Este archivo proporciona una función utilitaria vital para convertir strings de **wide-character** (`std::wstring_view`, usadas en las entradas de la biblioteca) a strings **ANSI/8-bit** (`std::string`), que son necesarias para funciones **WinAPI** que operan con `char*` (como `CreateProcessA` o `GetProcAddress`).

```cpp
#pragma once

#include <string>
#include <string_view>
#include <windows.h> // Necesario para WideCharToMultiByte

namespace Utils {
    inline std::string Wide_To_Local_8Bit(std::wstring_view wstr) {
        if (wstr.empty())
            return "";
        
        // Determina el tamaño necesario para el buffer de la string resultante en char
        int size = WideCharToMultiByte(CP_ACP, // Code Page ANSI (dependiente del sistema local)
            0, // Sin flags adicionales
            wstr.data(), 
            static_cast<int>(wstr.size()), 
            nullptr, // Calcula el tamaño, no llena el buffer
            0, // Tamaño 0, solo para cálculo
            nullptr, // Carácter por defecto para caracteres no representables
            nullptr); // Puntero a bool que indica si hubo un carácter estándar

        if (size <= 0) // Retorna una string vacía en caso de error o tamaño inválido
            return "";

        std::string result(size, 0); // Aloca la string con el tamaño determinado
        // Realiza la conversión real, llenando el buffer 'result'
        WideCharToMultiByte(CP_ACP, 
            0, 
            wstr.data(), 
            static_cast<int>(wstr.size()), 
            result.data(), // Buffer de destino
            size, // Tamaño del buffer de destino
            nullptr, 
            nullptr);

        return result;
    }
}
```

> [!IMPORTANT]
> El `CP_ACP` **(ANSI Code Page)** usado en `WideCharToMultiByte` es la página de código estándar del sistema **Windows**. Esto significa que la conversión puede variar dependiendo de la configuración de idioma del sistema del usuario. Para la mayoría de los casos de uso de nombres de archivos y argumentos de línea de comandos en **SA-MP**/**OMP** (que históricamente manejan bien strings **ANSI**), este enfoque es generalmente suficiente. Sin embargo, en escenarios que requieren compatibilidad **Unicode** total con sistemas externos o entradas globales, serían necesarias conversiones para **UTF-8** (`CP_UTF8`) u otras páginas de código. Para el ámbito de este proyecto, el `CP_ACP` es el estándar funcional.

### `error_utils.hpp`

Un componente fundamental para la usabilidad de la biblioteca, responsable de proporcionar **feedback** claro al usuario en caso de falla. Centraliza la lógica de obtención de mensajes de error del sistema y la exhibición de cuadros de diálogo.

```cpp
#pragma once

#include <string>
#include <string_view>
#include <windows.h> // Para FormatMessageW y MessageBoxW
//
#include "types.hpp"
#include "constants.hpp"

namespace Utils {
    // Retorna el mensaje de error del sistema Windows para un código de error específico
    inline std::wstring Get_System_Error_Message(DWORD error_code) {
        wchar_t buffer[512] = {0}; // Buffer para el mensaje
        // FormatMessageW llena el buffer con la descripción del error del sistema
        DWORD result = FormatMessageW(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, 
            nullptr, // Fuente del mensaje (del sistema)
            error_code, 
            0, // Idioma (usar estándar)
            buffer, 
            512, // Tamaño del buffer
            nullptr);
        
        // Si la función fue exitosa, retorna la string del buffer; caso contrario, un mensaje genérico
        return result ? std::wstring(buffer) : L"Unknown error (Code: " + std::to_wstring(error_code) + L")";
    }

    // Muestra un cuadro de mensaje de error al usuario
    inline void Show_Error(std::wstring_view message, Types::Inject_Type injectType) {
        // Escoge el título del cuadro de diálogo basado en el tipo de inyección
        std::wstring title = (injectType == Types::Inject_Type::SAMP) ? Constants::ERROR_TITLE_SAMP : Constants::ERROR_TITLE_OMP;
        MessageBoxW(nullptr, // Handle de la ventana padre (nullptr para escritorio)
            message.data(), 
            title.c_str(), 
            MB_OK | MB_ICONERROR); // Botón OK e ícono de error
    }
}
```

> [!NOTE]
> La función `FormatMessageW` es una **API Windows** poderosa que recupera la descripción textual de un código de error del sistema. Maneja la localización y proporciona mensajes claros que son esenciales para un **diagnóstico** eficaz, transformando un `DWORD` como `ERROR_FILE_NOT_FOUND` (2) en `L"El sistema no puede encontrar el archivo especificado."`.

### `resource_handle.hpp`

La gestión segura de recursos (como `HANDLE`s de **Windows**) es crítica para evitar fugas de recursos y comportamientos indefinidos. Este archivo define un `UniqueResource` utilizando `std::unique_ptr` y una función personalizada para `CloseHandle`. Esto sigue el principio **RAII (Resource Acquisition Is Initialization)**, garantizando que los `HANDLE`s se cierren automáticamente cuando sus **wrappers** salen del ámbito, incluso en caso de excepciones.

```cpp
#pragma once

#include <memory> // Para std::unique_ptr
#include <functional> // Para std::function
#include <windows.h> // Para HANDLE y CloseHandle

namespace Utils {
    // Alias de tipo para un std::unique_ptr que gestiona un HANDLE (o puntero) con un deleter personalizado
    // T: El tipo de recurso a ser gestionado (ej: HANDLE, LPVOID)
    // Deleter: Una clase o lambda que sabe cómo liberar el recurso
    template<typename T, typename Deleter>
    using UniqueResource = std::unique_ptr<std::remove_pointer_t<T>, Deleter>;

    // Función auxiliar para crear una instancia de UniqueResource para HANDLEs
    // Asume que T es un tipo de handle y usa CloseHandle como deleter.
    template<typename T>
    inline auto Make_Unique_Handle(T handle) {
        return UniqueResource<T, std::function<void(T)>>(handle, [](T h) {
            // Condición para garantizar que el handle es válido antes de intentar cerrarlo
            // 0 e INVALID_HANDLE_VALUE son considerados inválidos para la mayoría de los handles
            if (h && h != INVALID_HANDLE_VALUE)
                CloseHandle(h); // Libera el HANDLE del sistema operativo
        });
    }
}
```

> [!IMPORTANT]
> El uso de `UniqueResource` es una demostración de buenas prácticas de **C++ moderno** y desarrollo seguro en **Windows**. Simplifica drásticamente la gestión de ciclos de vida de **handles**, que, si no se cierran correctamente, pueden llevar a fugas de memoria o recursos del **kernel**, impactando la estabilidad del sistema a lo largo del tiempo.

### `validation.hpp`

La robustez de la inyección comienza con la validación de las entradas del usuario y la verificación de las dependencias de archivos. Este módulo contiene funciones que garantizan que todos los prerrequisitos y parámetros estén correctos antes de intentar iniciar el proceso de inyección, previniendo errores más complejos más adelante.

```cpp
#pragma once

#include <string>
#include <string_view>
#include <filesystem> // Para std::filesystem::exists
//
#include "constants.hpp"
#include "types.hpp"
#include "string_utils.hpp" // Para Wide_To_Local_8Bit
#include "error_utils.hpp" // Para Show_Error

namespace Utils {
    // Valida si una string de puerto es un número válido y está dentro del rango permitido
    inline bool Validate_Port(std::wstring_view port_str, std::wstring& error_message) {
        try {
            // Intenta convertir la string de wide-character a std::string y luego a int
            int port_num = std::stoi(Wide_To_Local_8Bit(port_str));

            // Verifica si el puerto está dentro del rango válido (1-65535)
            if (port_num < Constants::MIN_PORT || port_num > Constants::MAX_PORT)
                return (error_message = L"El número de puerto especificado (" + std::wstring(port_str) + 
                L") está fuera del rango válido de " +  std::to_wstring(Constants::MIN_PORT) + 
                L" a " + std::to_wstring(Constants::MAX_PORT) + 
                L". Por favor, proporcione un puerto válido.", false);

            return true;
        }
        catch (...) { // Captura cualquier excepción (como std::invalid_argument para no numérico)
            return (error_message = L"Formato de puerto inválido. El puerto debe ser un valor numérico. Por favor, proporcione un entero válido para el puerto.", false);
        }
    }

    // Valida el nickname, verificando si no está vacío y si el tamaño es aceptable
    inline bool Validate_Nickname(std::wstring_view nickname_str, std::wstring& error_message) {
        if (nickname_str.empty())
            return (error_message = L"El nickname no puede estar vacío. Por favor, proporcione un nickname válido.", false);
        
        if (nickname_str.size() > Constants::MAX_NICKNAME_LENGTH)
            return (error_message = L"El tamaño del nickname excede el máximo permitido de " + 
                std::to_wstring(Constants::MAX_NICKNAME_LENGTH) + 
                L" caracteres. Por favor, use un nickname más corto.", false);

        return true;
    }

    // Valida la existencia de los archivos críticos (gta_sa.exe, samp.dll, omp-client.dll)
    inline bool Validate_Files(const std::filesystem::path& game_path, 
        const std::filesystem::path& samp_DLL_path, 
        const std::filesystem::path& omp_DLL_path, 
        Types::Inject_Type inject_type) {
        std::wstring error_message_local; // Usamos una variable local aquí antes de pasar a Show_Error
        
        // Verifica la existencia del ejecutable del juego
        if (!std::filesystem::exists(game_path)) {
            error_message_local = L"Ejecutable del juego no encontrado. Asegúrese de que 'gta_sa.exe' exista en la ruta especificada: " + game_path.wstring();
            Show_Error(error_message_local, inject_type);
            
            return false;
        }

        // Verifica la existencia de samp.dll (esencial para ambos tipos de inyección)
        if (!std::filesystem::exists(samp_DLL_path)) {
            error_message_local = L"Biblioteca SA-MP no encontrada. Asegúrese de que 'samp.dll' exista en la ruta especificada: " + samp_DLL_path.wstring();
            Show_Error(error_message_local, inject_type);

            return false;
        }

        // Si el tipo de inyección es OMP, verifica la existencia de omp-client.dll
        if (inject_type == Types::Inject_Type::OMP && !std::filesystem::exists(omp_DLL_path)) {
            error_message_local = L"Biblioteca OMP no encontrada. Asegúrese de que 'omp-client.dll' exista en la ruta especificada para la inyección OMP: " + omp_DLL_path.wstring();
            Show_Error(error_message_local, inject_type);

            return false;
        }

        return true; // Todos los archivos necesarios fueron encontrados
    }
}
```

> [!NOTE]
> La utilización de `std::filesystem` es una adición moderna al **C++17** que ofrece una manera poderosa y multiplataforma de interactuar con el sistema de archivos. Para este proyecto en **Windows**, simplifica el tratamiento de rutas y la verificación de la existencia de archivos en comparación con **APIs** más antiguas de **WinAPI**.
>
> Asegúrese de que su compilador soporte **C++17** para usar `std::filesystem`. Necesitará configurar su proyecto para usar un estándar **C++17** (`/std:c++17` en **Visual Studio**).

### `process.hpp`

Este es el módulo principal responsable de la interacción directa con las **APIs** de bajo nivel de **Windows** para manipular procesos. Encapsula las operaciones cruciales de creación de procesos e **inyección de DLL**, manejando **handles**, **memoria** e **hilos**.

```cpp
#pragma once

#include <string_view>
#include <optional> // Para std::optional
#include <functional> // Para std::function (usado en UniqueResource)
#include <windows.h> // APIs de Windows
#include <memory> // Para std::unique_ptr
#include <vector> // Para std::vector (buffer de args)
//
#include "resource_handle.hpp" // Nuestro wrapper para HANDLEs
#include "error_utils.hpp" // Para Get_System_Error_Message y Show_Error
#include "constants.hpp" // Constantes globales
#include "types.hpp" // Tipos de inyección

class Process {
    public:
        // Constructores/Destructores y operadores de asignación
        // Explícitamente default y delete para garantizar semántica de valor y mover-only.
        Process() = default;
        Process(const Process&) = delete; // Sin copia
        Process& operator=(const Process&) = delete; // Sin asignación de copia
        Process(Process&&) = default; // Semántica de movimiento
        Process& operator=(Process&&) = default; // Asignación de movimiento
        ~Process() = default;

        // Estructura para almacenar los handles del proceso y del hilo, gestionados por UniqueResource
        struct Process_Info {
            Resource_Handle::UniqueResource<HANDLE, std::function<void(HANDLE)>> process_handle;
            Resource_Handle::UniqueResource<HANDLE, std::function<void(HANDLE)>> thread_handle;
        };

        // Crea el proceso del juego GTA:SA en estado suspendido
        std::optional<Process_Info> Create_Game_Process(std::string_view game_path, std::string_view command_args, std::string_view working_dir) {
            STARTUPINFOA startup_info{}; // Estructura para información de inicialización del proceso
            startup_info.cb = sizeof(STARTUPINFOA); // Define el tamaño de la estructura

            PROCESS_INFORMATION process_info{}; // Estructura que recibirá información sobre el nuevo proceso

            // Crea un buffer mutable para los argumentos de la línea de comandos.
            // CreateProcessA modifica el buffer de la línea de comandos, entonces std::string_view directo no funciona.
            std::vector<char> args_buffer(command_args.size() + 1); // +1 para el terminador nulo

            if (!command_args.empty()) {
                std::memcpy(args_buffer.data(), command_args.data(), command_args.size());
                args_buffer[command_args.size()] = '\0'; // Garantiza terminador nulo
            }

            // Crea el proceso
            bool success = CreateProcessA(game_path.data(), // Nombre del módulo ejecutable
                args_buffer.empty() ? nullptr : args_buffer.data(), // Argumentos de la línea de comandos
                nullptr, // Atributos de seguridad del proceso
                nullptr, // Atributos de seguridad del hilo
                FALSE, // No heredar handles
                Constants::PROCESS_CREATION_FLAGS, // CREATE_SUSPENDED | DETACHED_PROCESS
                nullptr, // Ambiente del nuevo proceso
                working_dir.empty() ? nullptr : working_dir.data(), // Directorio de trabajo
                &startup_info, // Información de inicialización
                &process_info); // Información del proceso creado

            if (!success) {
                // Si falló, obtiene y muestra el mensaje de error del sistema
                std::wstring error_msg = Error_Utils::Get_System_Error_Message(GetLastError());
                Error_Utils::Show_Error(L"Falló la creación del proceso del juego. Asegúrese de que 'gta_sa.exe' no esté en ejecución y de que tenga permisos suficientes para ejecutar el archivo. Error del sistema: " + error_msg, Types::Inject_Type::SAMP); // Usa SAMP como fallback para el título
                
                return std::nullopt; // Retorna un optional vacío
            }

            Process_Info result;
            // Almacena los handles del proceso y del hilo en UniqueResource para gestión automática
            result.process_handle = Resource_Handle::Make_Unique_Handle(process_info.hProcess);
            result.thread_handle = Resource_Handle::Make_Unique_Handle(process_info.hThread);

            return result; // Retorna la estructura con los handles gestionados
        }

        // Inyecta una DLL en el proceso remoto
        bool Inject_DLL(HANDLE process, std::string_view DLL_path, std::wstring& error_message) {
            // Aloca memoria en el proceso remoto para la ruta de la DLL
            LPVOID remote_memory = VirtualAllocEx(process, // Handle del proceso objetivo
            nullptr, // Dirección preferencial (nullptr para dejar que el sistema elija)
            DLL_path.size() + 1, // Tamaño de la ruta + terminador nulo
            Constants::MEMORY_ALLOCATION_TYPE, // MEM_COMMIT | MEM_RESERVE
            Constants::MEMORY_PROTECTION); // PAGE_READWRITE

            if (!remote_memory)
                return (error_message = L"Falló la asignación de memoria en el proceso objetivo. Esto puede deberse a permisos insuficientes o mecanismos de protección del proceso.", false);

            // Gestión de recursos para la memoria asignada remotamente.
            // Será liberada automáticamente al salir del ámbito.
            auto memory_guard = Resource_Handle::UniqueResource<LPVOID, std::function<void(LPVOID)>>(remote_memory, 
                [process](LPVOID ptr) { // Lambda como deleter
                    if (ptr)
                        VirtualFreeEx(process, ptr, 0, MEM_RELEASE); // Libera la memoria asignada
                }
            );

            // Escribe la ruta de la DLL en la memoria asignada remotamente
            if (!WriteProcessMemory(process, remote_memory, DLL_path.data(), DLL_path.size() + 1, nullptr))
                return (error_message = L"Falló la escritura de la ruta de la DLL en la memoria del proceso objetivo. Verifique los permisos del proceso y asegúrese de que la ruta de la DLL sea accesible.", false);

            // Obtiene el handle para kernel32.dll (que está cargado en el propio proceso del inyector)
            HMODULE kernel32 = GetModuleHandleA(Constants::KERNEL32_DLL);
            
            if (!kernel32)
                return (error_message = L"Falló la obtención de un handle para kernel32.dll. Esta es una biblioteca esencial del sistema y este error indica un problema grave del sistema.", false);

            // Obtiene la dirección de la función LoadLibraryA en kernel32.dll.
            // Esta dirección es consistente entre procesos en el mismo SO y es la clave de la inyección.
            LPVOID load_library_addr = reinterpret_cast<LPVOID>(GetProcAddress(kernel32, Constants::LOAD_LIBRARY_FUNC));

            if (!load_library_addr)
                return (error_message = L"Falló la búsqueda de la dirección de la función LoadLibraryA en kernel32.dll. Esto es crítico para inyectar la DLL.", false);

            // Crea un hilo remoto en el proceso objetivo para ejecutar LoadLibraryA
            // El argumento para LoadLibraryA será la dirección remota de la ruta de la DLL
            HANDLE remote_thread = CreateRemoteThread(process, // Handle del proceso objetivo
                nullptr, // Atributos de seguridad del hilo
                0, // Tamaño de la pila (0 para default)
                reinterpret_cast<LPTHREAD_START_ROUTINE>(load_library_addr), // Dirección de LoadLibraryA
                remote_memory, // Argumento para LoadLibraryA (ruta de la DLL)
                0, // Flags de creación (0 para iniciar inmediatamente)
                nullptr); // ID del hilo (nullptr para no retornar)

            if (!remote_thread)
                return (error_message = L"Falló la creación de un hilo remoto en el proceso objetivo para ejecutar la inyección de la DLL. Esto podría deberse a restricciones de seguridad o estado del proceso. Error del sistema: " + Error_Utils::Get_System_Error_Message(GetLastError()), false);

            // Gestión de recursos para el handle del hilo remoto
            auto thread_guard = Resource_Handle::Make_Unique_Handle(remote_thread);

            // Espera que el hilo remoto (inyección de DLL) se complete o alcance un timeout
            DWORD wait_result = WaitForSingleObject(remote_thread, Constants::DLL_INJECTION_TIMEOUT_MS);

            if (wait_result != WAIT_OBJECT_0) {
                return (error_message = L"Timeout o error esperando que la inyección de la DLL se complete. Error del sistema: " + Error_Utils::Get_System_Error_Message(GetLastError()), false);

            // Obtiene el código de salida del hilo remoto.
            // Para LoadLibraryA, un código de salida 0 significa falla (no pudo cargar la DLL).
            DWORD exit_code = 0;

            if (!GetExitCodeThread(remote_thread, &exit_code) || exit_code == 0)
                return (error_message = L"La inyección de la DLL falló o retornó un error. La llamada a LoadLibrary puede haber fallado en el proceso objetivo.", false);

            return true; // Inyección exitosa
        }
};
```

> [!NOTE]
> El módulo `process.hpp` demuestra un diseño robusto y seguro. La función `Create_Game_Process` retorna un `std::optional<Process_Info>`. Esto permite que la función indique fallas en la creación del proceso de forma explícita y elegante (retornando un `std::nullopt`) sin recurrir a excepciones o códigos de error ambiguos en su retorno principal.
>
> Más crucialmente, la estructura `Process_Info` utiliza `Resource_Handle::UniqueResource<HANDLE, std::function<void(HANDLE)>>` para encapsular los **handles** del proceso y del **hilo**. Este es un ejemplo del patrón **RAII (Resource Acquisition Is Initialization)**, que garantiza que los `HANDLE`s del sistema operativo (como `hProcess` y `hThread`) se cierren automáticamente vía `CloseHandle` cuando el objeto `Process_Info` sale del ámbito. Esto elimina fugas de **handles**, que son una fuente común de inestabilidad y consumo excesivo de recursos en **aplicaciones Windows** de larga duración.
>
> De manera similar, dentro de la función `Inject_DLL`, `UniqueResource` se usa para gestionar la memoria asignada remotamente (`VirtualAllocEx`), garantizando que se libere (`VirtualFreeEx`) tan pronto como no sea necesaria o en caso de falla. Esta rigurosa gestión de recursos contribuye significativamente a la confiabilidad y estabilidad del **SA-MP Injector C++**.

### `injector_core.hpp`

Esta es la clase orquestadora que une todas las funcionalidades de los módulos anteriores. Coordina la validación, la construcción de argumentos de línea de comandos, la creación del proceso y las llamadas de **inyección de DLL**.

```cpp
#pragma once

#include <string_view>
#include <sstream> // Para construir strings con stringstream
#include <filesystem> // Para manipulación de rutas
//
#include "process.hpp" // Funciones de creación/inyección de proceso
#include "validation.hpp" // Funciones de validación de entradas
#include "string_utils.hpp" // Funciones de conversión de string
#include "error_utils.hpp" // Funciones de tratamiento de errores
#include "constants.hpp" // Constantes de la biblioteca
#include "types.hpp" // Tipos de inyección

namespace Injector {
    class Injector_Core {
        public:
            // Constructores/Destructores para semántica de movimiento
            Injector_Core() = default;
            Injector_Core(const Injector_Core&) = delete; // Deshabilita copia
            Injector_Core& operator=(const Injector_Core&) = delete; // Deshabilita asignación de copia
            Injector_Core(Injector_Core&&) = default; // Habilita movimiento
            Injector_Core& operator=(Injector_Core&&) = default; // Habilita asignación de movimiento
            ~Injector_Core() = default;

            // Función principal que orquesta la inicialización e inyección del juego
            bool Initialize_Game(Types::Inject_Type inject_type, std::wstring_view folder, std::wstring_view nickname, std::wstring_view ip, std::wstring_view port, std::wstring_view password) {
                namespace fs = std::filesystem; // Alias para std::filesystem

                // Construye las rutas completas para los archivos esenciales
                fs::path game_path = fs::path(folder) / Constants::GAME_EXE_NAME; // Ej: C:\GTA\gta_sa.exe
                fs::path samp_DLL_path = fs::path(folder) / Constants::SAMP_DLL_NAME; // Ej: C:\GTA\samp.dll
                fs::path omp_DLL_path = fs::path(folder) / Constants::OMP_DLL_NAME; // Ej: C:\GTA\omp-client.dll

                // 1. Validación de Archivos
                if (!Validation::Validate_Files(game_path, samp_DLL_path, omp_DLL_path, inject_type))
                    return false; // Error ya fue mostrado por la función de validación
                
                std::wstring error_message_local; // Para recibir mensajes de error de las validaciones

                // 2. Validación de Puerto
                if (!Validation::Validate_Port(port, error_message_local))
                    return (Error_Utils::Show_Error(error_message_local, inject_type), false);

                // 3. Validación de Nickname
                if (!Validation::Validate_Nickname(nickname, error_message_local))
                    return (Error_Utils::Show_Error(error_message_local, inject_type), false);

                // 4. Conversión de Wide-char a Local 8-bit (necesario para APIs ANSI)
                std::string nickname_str = String_Utils::Wide_To_Local_8Bit(nickname);
                std::string ip_str = String_Utils::Wide_To_Local_8Bit(ip);
                std::string port_str = String_Utils::Wide_To_Local_8Bit(port);
                std::string password_str = String_Utils::Wide_To_Local_8Bit(password);
                // Convierte también las rutas a std::string (requeridas por CreateProcessA como char*)
                std::string game_path_str = String_Utils::Wide_To_Local_8Bit(game_path.wstring());
                std::string folder_str = String_Utils::Wide_To_Local_8Bit(folder);
                std::string samp_DLL_path_str = String_Utils::Wide_To_Local_8Bit(samp_DLL_path.wstring());
                std::string omp_DLL_path_str = String_Utils::Wide_To_Local_8Bit(omp_DLL_path.wstring());

                // 5. Construcción de los Argumentos de la Línea de Comandos
                std::string args = Build_Command_Args(nickname_str, ip_str, port_str, password_str);

                // Instancia la clase Process para gestionar las operaciones de proceso
                Process process_core;
                
                // 6. Creación del Proceso del Juego (Suspendido)
                auto process_info_opt = process_core.Create_Game_Process(game_path_str, args, folder_str);

                if (!process_info_opt)
                    return false; // Error ya fue mostrado por la función de creación de proceso

                // Desreferencia el optional para obtener la estructura Process_Info
                auto& process_info = *process_info_opt; 
                std::wstring inject_error_message; // Para recibir mensajes de error de la inyección

                // 7. Inyección de samp.dll
                if (!process_core.Inject_DLL(process_info.process_handle.get(), samp_DLL_path_str, inject_error_message))
                    return (Error_Utils::Show_Error(L"Falló la inyección de samp.dll: " + inject_error_message, inject_type), false);

                // 8. Inyección condicional de omp-client.dll (solo si es OMP)
                if (inject_type == Types::Inject_Type::OMP) {
                    if (!process_core.Inject_DLL(process_info.process_handle.get(), omp_DLL_path_str, inject_error_message))
                        return (Error_Utils::Show_Error(L"Falló la inyección de omp-client.dll: " + inject_error_message, inject_type), false);
                }

                // 9. Reanudar el Proceso del Juego
                // El proceso fue creado en estado suspendido para permitir la inyección.
                // Ahora que las DLLs fueron inyectadas, puede ser reanudado.
                if (ResumeThread(process_info.thread_handle.get()) == static_cast<DWORD>(-1))
                    return (Error_Utils::Show_Error(L"Falló la reanudación del hilo del proceso del juego: " + Error_Utils::Get_System_Error_Message(GetLastError()), inject_type), false);

                return true; // ¡Éxito en todas las etapas!
            }
        private:
            // Construye la string de argumentos de la línea de comandos para el ejecutable del juego
            std::string Build_Command_Args(const std::string& nickname, const std::string& ip, const std::string& port, const std::string& password) {
                std::stringstream command_args_stream; // Usa stringstream para construcción eficiente

                // SA-MP y OMP esperan los argumentos "-c -n [nickname] -h [ip] -p [port]"
                command_args_stream << Constants::CMD_ARG_CONFIG << " " 
                    << Constants::CMD_ARG_NICKNAME << " " << nickname << " " 
                    << Constants::CMD_ARG_HOST << " " << ip << " " 
                    << Constants::CMD_ARG_PORT << " " << port;

                // Agrega la contraseña solo si no está vacía
                if (!password.empty())
                    command_args_stream << " " << Constants::CMD_ARG_PASSWORD << " " << password;

                return command_args_stream.str();
            }
    };
}
```

> [!CAUTION]
> Aunque el proceso para **OMP** implica inyectar la `omp-client.dll` *además* de la `samp.dll`, esto está de acuerdo con la manera en que el **OMP** generalmente funciona. El cliente **OMP** a menudo usa la `samp.dll` como **base** o **proxy** para ciertas funcionalidades, mientras que `omp-client.dll` extiende o sobrescribe comportamientos.
>
> Es crucial que **ambas DLLs** estén presentes y funcionales en el directorio del juego para que la **inyección OMP** sea exitosa. Si una falla, el juego puede no inicializarse correctamente o el cliente multijugador puede no cargarse.

### `injector.hpp`

Este es el archivo de interfaz de la biblioteca. Es el único archivo que el usuario final necesitará incluir para usar el **SA-MP Injector C++**. Actúa como un envoltorio para la clase `Injector::Injector_Core`, simplificando la interfaz a una única función global, `Initialize_Game`.

```cpp
#pragma once

#include <string_view>
//
#include "injector_core.hpp" // La clase principal con la lógica
#include "error_utils.hpp" // Para exhibición de errores (en caso de tipo de inyección inválido)
#include "types.hpp" // Enumeración de tipos
#include "constants.hpp" // Constantes (para nombres de tipo de inyección)

// La interfaz de alto nivel para la biblioteca.
// Simplifica el uso exponiendo solo esta función global.
inline bool Initialize_Game(std::wstring_view inject_type_str, std::wstring_view folder, std::wstring_view nickname, std::wstring_view ip, std::wstring_view port, std::wstring_view password) {
    Types::Inject_Type type; // Variable para almacenar el tipo de inyección

    // Convierte la string de tipo de inyección al enum Inject_Type
    if (inject_type_str == Constants::INJECT_TYPE_SAMP)
        type = Types::Inject_Type::SAMP;
    
    else if (inject_type_str == Constants::INJECT_TYPE_OMP)
        type = Types::Inject_Type::OMP;
    
    else
        // Si la string de tipo de inyección es inválida, muestra un error y retorna falso
        return (Error_Utils::Show_Error(L"Modo de inyección especificado inválido. Por favor, use 'samp' o 'omp'.", Types::Inject_Type::SAMP), false); // Usa SAMP como fallback para el título

    Injector::Injector_Core injector; // Instancia el objeto que contiene la lógica central
    
    // Delega la llamada a la función Initialize_Game de la clase Injector_Core
    return injector.Initialize_Game(type, folder, nickname, ip, port, password);
}
```

> [!NOTE]
> El uso de la palabra clave `inline` para todas las funciones en este archivo y en otros utilitarios permite que la biblioteca sea `header-only`. `inline` sugiere al compilador que el cuerpo de la función debe insertarse directamente en los puntos de llamada, pero su principal efecto aquí es relajar la **One Definition Rule (ODR)** para que la función pueda definirse en múltiples archivos `.obj` (lo que sucedería si varios `.cpp` incluyen `injector.hpp`). La etapa de **linkage** garantizará que solo exista una versión final en el ejecutable.

## Ejemplos Completos de Utilización

Para integrar el **SA-MP Injector C++** en su proyecto, siga las instrucciones y analice los escenarios a continuación.

### 1. Preparación del Ambiente de Desarrollo

- **Compilador C++**: Se recomienda un compilador que **soporte C++17**. **Visual Studio** con `vcpkg` (para `std::filesystem`) o **GCC/Clang (versión 17+)** son opciones.
- **Configuración del Proyecto**:
  - Cree un nuevo proyecto **C++** (por ejemplo, un proyecto de consola).
  - Copie **todos** los archivos `.hpp` del **SA-MP Injector C++** a una carpeta accesible para su proyecto (ej: en la carpeta de **headers**).
  - Asegúrese de que el **estándar C++** esté configurado para **C++17**. Es fundamental mantener esta versión para compatibilidad máxima con las bibliotecas de **SA-MP** y **OMP**. En **Visual Studio**: `Project Properties > Configuration Properties > C/C++ > Language > C++ Language Standard -> "ISO C++17 Standard (/std:c++17)"`
- **Permisos**: Su ejecutable probablemente necesitará ejecutarse como **Administrador (no necesariamente)** para crear procesos e **inyectar DLLs** en el entorno del sistema. En **Visual Studio**, esto puede hacerse en: `Project Properties > Configuration Properties > Linker > Manifest File > UAC Execution Level -> "requireAdministrator (/LEVEL='requireAdministrator')"`

### 2. Escenario Básico: Conectando a un Servidor SA-MP

Este es el caso de uso más común, iniciando el **GTA:SA** y conectando a un servidor **SA-MP** con un **nickname** y **IP**/**puerto** específicos.

```cpp
// main.cpp
#include <iostream>
#include <string>
#include <codecvt> // Para std::wstring_convert (legado, pero funcional para este caso)
#include <locale> // Para std::codecvt_utf8_to_utf16
//
#include "injector.hpp" // ¡La única inclusión necesaria de la biblioteca!

int Main(int argc, char* argv[]) {
    // Definir las variables de configuración
    // Cambie estas rutas y detalles del servidor para que coincidan con su configuración local
    std::wstring folder = L"C:\\Juegos\\GTA San Andreas"; // Donde están gta_sa.exe, samp.dll
    std::wstring nickname = L"Nombre";
    std::wstring ip = L"127.0.0.1"; // Ejemplo: su servidor local
    std::wstring port = L"7777";
    std::wstring password = L""; // Deje vacío si no hay contraseña

    // Opcional: Permitir que el usuario proporcione configuraciones vía línea de comandos (simplificado)
    // Para un tratamiento de args más robusto, use una biblioteca de análisis de argumentos.
    if (argc > 1) {
        // Ejemplo: si el primer arg es una ruta
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

    std::wcout << L"Iniciando SA-MP..." << std::endl;
    std::wcout << L"Carpeta del juego: " << folder << std::endl;
    std::wcout << L"Nickname: " << nickname << std::endl;
    std::wcout << L"Servidor: " << ip << L":" << port << std::endl;

    // Llamada a la función de la biblioteca para iniciar el juego
    if (Initialize_Game(L"samp", // Tipo de inyección: SA-MP
        folder, // Ruta de la carpeta del juego
        nickname, // Nickname deseado
        ip, // IP del servidor
        port, // Puerto del servidor (string)
        password)) { // Contraseña del servidor (string, puede estar vacía)
        std::wcout << L"\n--- ¡SA-MP inicializado con éxito! ---" << std::endl;
        std::wcout << L"El juego fue iniciado en un proceso separado." << std::endl;
    }
    else {
        std::wcout << L"\n--- ¡FALLA al iniciar SA-MP! ---" << std::endl;
        std::wcout << L"Verifique los mensajes de error mostrados." << std::endl;
    }

    // Mantiene la consola abierta para visualizar los mensajes de salida
    std::wcout << L"\nPresione Enter para cerrar el programa." << std::endl;
    std::wcin.ignore();

    return 0;
}
```

**Para compilar y ejecutar:**

```bash
# Ejemplo con g++ (Linux/MinGW/MSYS2) - Requiere la libstdc++fs para filesystem
# Es importante garantizar que el toolchain no esté usando una versión de C++
# que introduzca incompatibilidades en el proceso de inyección.
# Verifique la documentación específica de su compilador para banderas de compatibilidad binaria (ABI).
g++ main.cpp -o my_launcher -std=c++17 -Wall -lstdc++fs -municode -lkernel32

# Ejemplo con MSVC (Visual Studio Developer Command Prompt)
# La bandera '/std:c++17' garantiza la conformidad con C++17.
cl /EHsc /std:c++17 /permissive- /FS /utf-8 main.cpp /link /OUT:my_launcher.exe
```

> [!NOTE]
> El **SA-MP** y **OMP**, como proyectos legados, son compilados con herramientas específicas que definen su **Application Binary Interface (ABI)**. Aunque esta biblioteca usa **C++17**, **es crucial que las DLLs de SA-MP y OMP con las que interactúa también sean compatibles con la ABI de su compilador y de la versión de tiempo de ejecución de C++ (CRT) que usa**.
>
> Usar un compilador o versión de **C++** muy diferente de la que se usó para **construir las DLLs** del juego puede llevar a problemas sutiles (por ejemplo, con la asignación de memoria o paso de parámetros) que no son fácilmente **diagnosticables** y no resultarán en un error explícito del inyector. Por esta razón, **el C++17 es la versión máxima recomendada**, ya que versiones más recientes pueden introducir cambios en la **ABI** o en la **CRT** que no son tolerados por los módulos de juego más antiguos.

### 3. Escenario Avanzado: Conectando a un Servidor OMP

Para el **OMP**, la lógica es idéntica a la del **SA-MP**, pero especifica `L"omp"` como el `inject_type` y asegura que la `omp-client.dll` esté presente en el directorio del juego.

```cpp
// main.cpp
#include <iostream>
#include <string>
#include <codecvt> // Para std::wstring_convert (legado, pero funcional para este caso)
#include <locale> // Para std::codecvt_utf8_to_utf16
//
#include "injector.hpp" // ¡La única inclusión necesaria de la biblioteca!

int Main() {
    // Definir las variables de configuración
    // Cambie estas rutas y detalles del servidor para que coincidan con su configuración local
    std::wstring folder = L"C:\\Juegos\\GTA San Andreas"; // Donde están gta_sa.exe, samp.dll y omp-client.dll
    std::wstring nickname = L"Nombre";
    std::wstring ip = L"127.0.0.1"; // Ejemplo: su servidor local
    std::wstring port = L"7777";
    std::wstring password = L""; // Deje vacío si no hay contraseña

    // Opcional: Permitir que el usuario proporcione configuraciones vía línea de comandos (simplificado)
    // Para un tratamiento de args más robusto, use una biblioteca de análisis de argumentos.
    if (argc > 1) {
        // Ejemplo: si el primer arg es una ruta
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

    std::wcout << L"Iniciando OMP..." << std::endl;
    std::wcout << L"Carpeta del juego: " << folder << std::endl;
    std::wcout << L"Nickname: " << nickname << std::endl;
    std::wcout << L"Servidor: " << ip << L":" << port << std::endl;

    // Llamada a la función de la biblioteca para iniciar el juego
    if (Initialize_Game(L"omp", // Tipo de inyección: OMP
        folder, // Ruta de la carpeta del juego
        nickname, // Nickname deseado
        ip, // IP del servidor
        port, // Puerto del servidor (string)
        password)) { // Contraseña del servidor (string, puede estar vacía)
        std::wcout << L"\n--- ¡OMP inicializado con éxito! ---" << std::endl;
        std::wcout << L"El juego fue iniciado en un proceso separado." << std::endl;
    }
    else {
        std::wcout << L"\n--- ¡FALLA al iniciar OMP! ---" << std::endl;
        std::wcout << L"Verifique los mensajes de error mostrados." << std::endl;
    }

    // Mantiene la consola abierta para visualizar los mensajes de salida
    std::wcout << L"\nPresione Enter para cerrar el programa." << std::endl;
    std::wcin.ignore();

    return 0;
}
```

## Tratamiento de Errores Comunes y Mensajes

El **SA-MP Injector C++** prioriza la usabilidad, y una parte fundamental de esto es proporcionar **feedback** claro al usuario en caso de falla. Los mensajes de error se presentan a través de cuadros de **diálogo de Windows** (`MessageBoxW`) y se categorizan por el tipo de **inyección (SA-MP o OMP)** para mayor contexto. Esto garantiza que sepa exactamente qué salió mal y cómo abordar la resolución.

Aquí están algunos de los errores comunes que puede encontrar y sus probables causas/soluciones, acompañados de ejemplos visuales de cómo aparecen estos cuadros de diálogo para el usuario final:

### 1. Tipo de Inyección Inválido

Si el `inject_type` proporcionado en la función `Initialize_Game` no es `L"samp"` o `L"omp"`, la biblioteca no sabrá qué cliente multijugador intenta inicializar.

![Error 1](screenshots/error_1.png)

- **Mensaje de Error Mostrado**: `"Invalid injection mode specified. Please use 'samp' or 'omp'."`
- **Causa**: El primer argumento de la función `Initialize_Game` (`std::wstring_view inject_type`) no coincide con los valores esperados de `L"samp"` o `L"omp"`. Puede ser un error de tipeo, una string vacía o un valor no reconocido.
- **Solución**: Verifique que el `std::wstring_view inject_type_str` esté definido correctamente como `L"samp"` o `L"omp"`. Es fundamental usar el prefijo `L` para literales de **wide-character (caracteres anchos)** al definir strings para compatibilidad con las constantes de la biblioteca.
    ```cpp
    // Correcto:
    Initialize_Game(L"samp", /* otros parámetros */);
    Initialize_Game(L"omp", /* otros parámetros */);

    // Incorrecto (causará error):
    // Initialize_Game(L"invalid", /* otros parámetros */);
    // Initialize_Game(L"", /* otros parámetros */);
    ```

### 2. Puerto del Servidor Inválido (Formato o Rango)

El puerto es un parámetro numérico esencial para la conexión con el servidor. Este error ocurre si el valor no puede interpretarse como un número válido o está fuera del rango aceptable **(1 a 65535)**.

#### 2.1. Formato de Puerto No Numérico

![Error 2](screenshots/error_2.png)

- **Mensaje de Error Mostrado**: `"Invalid port format. The port must be a numeric value. Please provide a valid integer for the port."`
- **Causa**: El argumento `port` (`std::wstring_view`) contiene caracteres que no son dígitos numéricos o no puede convertirse a un número entero.
- **Solución**: Proporcione una string que contenga solo dígitos y represente un número entero válido.
    ```cpp
    // Correcto:
    Initialize_Game(/* otros parámetros */, L"7777", /* otros parámetros */);

    // Incorrecto (formato inválido):
    // Initialize_Game(/* otros parámetros */, L"port7777", /* otros parámetros */);

    // Incorrecto (inválido):
    // Initialize_Game(/* otros parámetros */, L"invalid", /* otros parámetros */);
    ```

#### 2.2. Puerto Fuera del Rango Válido

![Error 3](screenshots/error_3.png)

- **Mensaje de Error Mostrado**: `"The specified port number (XXXX) is outside the valid range of 1 to 65535. Please provide a valid port."` (El **XXXX** será el valor que intentó usar).
- **Causa**: El puerto proporcionado es un número válido, pero está por debajo de `1` (reservado o no utilizable) o por encima de `65535` (límite máximo para **puertos TCP/UDP**).
- **Solución**: Proporcione un puerto que esté dentro del rango de `1` a `65535`. Puertos comunes para **SA-MP**/**OMP** son `7777` o `7778`.
    ```cpp
    // Correcto:
    Initialize_Game(/* otros parámetros */, L"7777", /* otros parámetros */);

    // Incorrecto (fuera del rango):
    // Initialize_Game(/* otros parámetros */, L"0", /* otros parámetros */); // Muy bajo
    // Initialize_Game(/* otros parámetros */, L"65536", /* otros parámetros */); // Muy alto
    // Initialize_Game(/* otros parámetros */, L"-1", /* otros parámetros */); // Valor negativo
    ```

### 3. Nickname Inválido (Vacío o Muy Largo)

El **nickname** del jugador se valida para garantizar que el cliente del juego lo acepte.

#### 3.1. Nickname Vacío

![Error 4](screenshots/error_4.png)

- **Mensaje de Error Mostrado**: `"Nickname cannot be empty. Please provide a valid nickname."`
- **Causa**: El argumento `nickname` (`std::wstring_view`) fue proporcionado como una string vacía.
- **Solución**: Asegúrese de que el nickname no esté vacío.
    ```cpp
    // Correcto:
    Initialize_Game(/* otros parámetros */, L"Nombre", /* otros parámetros */);

    // Incorrecto (vacío):
    // Initialize_Game(/* otros parámetros */, L"", /* otros parámetros */);
    ```

#### 3.2. Nickname Muy Largo

![Error 5](screenshots/error_5.png)

- **Mensaje de Error Mostrado**: `"Nickname length exceeds the maximum allowed of 23 characters. Please use a shorter nickname."`
- **Causa**: El tamaño del **nickname** proporcionado excede `Constants::MAX_NICKNAME_LENGTH`, que es `23` caracteres.
- **Solución**: Use un **nickname** que tenga como máximo `23` caracteres.
    ```cpp
    // Correcto:
    Initialize_Game(/* otros parámetros */, L"Nombre", /* otros parámetros */);

    // Incorrecto (muy largo):
    // Initialize_Game(/* otros parámetros */, L"EsteApodoEsMuyLargoYSuperaVeinteCaracteres", /* otros parámetros */);
    ```

### 4. Archivos del Juego o DLL No Encontrados

Esta es una de las causas más comunes de falla. La biblioteca necesita que `gta_sa.exe`, `samp.dll` y, para **OMP**, `omp-client.dll` estén presentes en los lugares esperados.

#### 4.1. Ejecutable del Juego (`gta_sa.exe`) No Encontrado

![Error 6](screenshots/error_6.png)

- **Mensaje de Error Mostrado**: `"Game executable not found. Please ensure 'gta_sa.exe' exists at the specified path: [ruta completa]"`. La `[ruta completa]` incluirá la carpeta y el nombre del archivo.
- **Causa**: El archivo `gta_sa.exe` no fue encontrado en la carpeta proporcionada en el argumento `folder`.
- **Solución**:
  1. Verifique que el `folder` (`std::wstring_view`) apunte al directorio correcto de instalación del **GTA San Andreas**.
  2. Confirme que `gta_sa.exe` existe dentro de esa carpeta y que su nombre no ha sido cambiado.

#### 4.2. Biblioteca SA-MP (`samp.dll`) No Encontrada

![Error 7](screenshots/error_7.png)

- **Mensaje de Error Mostrado**: `"SA-MP library not found. Please ensure 'samp.dll' exists at the specified path: [ruta completa]"`.
- **Causa**: El archivo `samp.dll` no fue encontrado en la carpeta proporcionada en el argumento `folder`. **Esta DLL** es un requisito para **ambos** tipos de inyección (`samp` y `omp`).
- **Solución**: Asegúrese de que el `samp.dll` esté presente en la carpeta de instalación del **GTA San Andreas**.

#### 4.3. Biblioteca OMP (`omp-client.dll`) No Encontrada (solo para inyección OMP)

![Error 8](screenshots/error_8.png)

- **Mensaje de Error Mostrado**: `"OMP library not found. Please ensure 'omp-client.dll' exists at the specified path for OMP injection: [ruta completa]"`.
- **Causa**: Si especificó `L"omp"` como tipo de inyección, pero el archivo `omp-client.dll` no fue encontrado en la carpeta proporcionada.
- **Solución**: Descargue el cliente **OMP** más reciente y asegúrese de que `omp-client.dll` (y `samp.dll`) estén presentes en la carpeta de instalación del **GTA San Andreas**.

### 5. Falla en la Creación del Proceso del Juego

Este es un error más complejo, ya que involucra **permisos del sistema operativo** y el estado actual del `gta_sa.exe`.

![Error 9](screenshots/error_9.png)

- **Mensaje de Error Mostrado**: `"Failed to create game process. Ensure 'gta_sa.exe' is not running and you have sufficient permissions to execute the file. System Error: [Mensaje de error del sistema operativo]"`. El mensaje del sistema será añadido por `GetLastError()` (ej: `Access is denied.` o `The requested operation requires elevation.`).
- **Causa**: La llamada `CreateProcessA` para iniciar el `gta_sa.exe` falló. Las causas comunes incluyen:
  - **Proceso ya en ejecución**: Una instancia de `gta_sa.exe` ya está activa y bloqueando una nueva ejecución.
  - **Permisos insuficientes**: Su aplicación no tiene los privilegios necesarios (ej: administrador) para crear un proceso en ciertas configuraciones de sistema (**UAC** activado, carpetas protegidas, etc.).
  - **Problemas con el ejecutable**: El `gta_sa.exe` puede estar corrupto o bloqueado por otro programa (ej: un antivirus mal configurado).
- **Solución**:
  1. Verifique el Administrador de Tareas y asegúrese de que no haya ninguna instancia de `gta_sa.exe` en ejecución. Finalice cualquiera si la hay.
  2. Ejecute su aplicación que utiliza la biblioteca con privilegios de **Administrador**. Haga clic derecho en el ejecutable y seleccione **"Ejecutar como administrador"**.
  3. Si un **antivirus** o **software** de seguridad está interfiriendo, añada su aplicación y/o la carpeta del **GTA:SA** a las excepciones del antivirus (haga esto con cuidado y solo si está seguro de la integridad de sus archivos).

### 6. Falla en la Asignación de Memoria en el Proceso Objetivo

La biblioteca intenta asignar un pequeño espacio de memoria en el `gta_sa.exe` para copiar la **ruta de la DLL**.

![Error 10](screenshots/error_10.png)

- **Mensaje de Error Mostrado**: `"Failed to allocate memory in the target process. This might be due to insufficient permissions or process protection mechanisms."`
- **Causa**: La función `VirtualAllocEx` (usada para asignar memoria dentro de otro proceso) falló. Esto es más probable si:
  - El proceso del **GTA:SA** (aunque esté en estado suspendido) tiene defensas de seguridad o **parches anti-inyección** que impiden la asignación de memoria por procesos externos.
  - Su aplicación no tiene los permisos elevados necesarios para manipular la memoria de otro proceso.
  - (Menos común) Hay una escasez extrema de memoria virtual en el sistema.
- **Solución**:
  1. Ejecute su aplicación con privilegios de **Administrador**.
  2. Asegúrese de que el juego no tenga ninguna modificación o **parche de seguridad** que pueda estar bloqueando intentos de inyección o manipulación de memoria (esto es más común en entornos modificados o con ciertas herramientas anti-trampas de terceros).

### 7. Falla en la Escritura del Camino de la DLL en la Memoria del Proceso

Tras asignar la memoria, la biblioteca intenta copiar la **ruta de la DLL** a ella.

![Error 11](screenshots/error_11.png)

- **Mensaje de Error Mostrado**: `"Failed to write DLL path to the target process memory. Verify process permissions and ensure the DLL path is accessible."`
- **Causa**: La función `WriteProcessMemory` falló al intentar copiar los **bytes de la ruta de la DLL** a la memoria remota asignada en el `gta_sa.exe`. Esto generalmente apunta a:
  - **Permisos de escritura**: Su aplicación no tiene permiso para escribir en esa región de memoria o en el proceso del **GTA:SA**.
  - **Handle inválido**: El **handle** del proceso (`process_handle`) de alguna manera se volvió inválido entre la asignación y la escritura, lo que es muy raro debido al uso de `UniqueResource` pero puede ocurrir bajo condiciones extremas del sistema.
  - **Problemas de Protección de Memoria**: Alguna protección de memoria (ya sea del **SO** o de modificaciones del juego) impidió la escritura.
- **Solución**: Ejecute como **Administrador**. Verifique que el `gta_sa.exe` y su entorno estén "limpios" de herramientas que podrían bloquear operaciones de memoria.

### 8. Falla al Encontrar Funciones Esenciales del Sistema

Estas son **APIs** cruciales de **Windows**; errores aquí indican un problema fundamental con el sistema operativo o el entorno de ejecución.

#### 8.1. `kernel32.dll` No Encontrado

![Error 12](screenshots/error_12.png)

- **Mensaje de Error Mostrado**: `"Failed to obtain a handle to kernel32.dll. This is an essential system library and this error indicates a severe system issue."`
- **Causa**: El `kernel32.dll` es una de las **DLLs** más básicas de **Windows**, que contiene funciones esenciales como `CreateProcess`, `VirtualAllocEx`, etc. Si `GetModuleHandleA` no logra obtener un **handle** para ella, el sistema operativo tiene problemas muy serios.
- **Solución**: Este es un error **crítico** que raramente es causado por la biblioteca o su aplicación. Sugiere corrupción de archivos del sistema, problemas graves con **Windows**, o una instalación altamente inusual del **SO**. Se recomienda ejecutar verificaciones de integridad del sistema (como `sfc /scannow` en el **Símbolo del sistema** como **Administrador**) o, en última instancia, reinstalar **Windows**.

#### 8.2. `LoadLibraryA` No Encontrado

![Error 13](screenshots/error_13.png)

- **Mensaje de Error Mostrado**: `"Failed to find the address of the LoadLibraryA function in kernel32.dll. This is critical for injecting the DLL."`
- **Causa**: Aunque `kernel32.dll` fue encontrado, la función `LoadLibraryA` no pudo resolverse vía `GetProcAddress`. Aunque extremadamente raro, puede ser resultado de corrupción del **archivo DLL** del `kernel32.dll` o un entorno de ejecución altamente no estándar.
- **Solución**: Al igual que el error de `kernel32.dll` anterior, esto indica un problema serio en el sistema operativo.

### 9. Fallo al Crear un Hilo Remoto para la Inyección

Tras preparar el entorno remoto y copiar la **ruta de la DLL**, se crea un nuevo **hilo** en el proceso del juego para "llamar" a `LoadLibraryA`.

![Error 14](screenshots/error_14.png)

- **Mensaje de Error Mostrado**: `"Failed to create a remote thread in the target process to execute the DLL injection. This could be due to security restrictions or process state. System Error: [Mensaje de error del sistema operativo]"`.
- **Causa**: La llamada `CreateRemoteThread` falló. Este error es común en sistemas con defensas **anti-inyección** robustas o cuando un programa está monitoreando intensamente el comportamiento del proceso:
  - **Mecanismos de Seguridad**: Herramientas **anti-cheat**, **softwares** de seguridad o ciertas políticas de **Windows** pueden detectar y bloquear intentos de crear **hilos** en procesos de terceros.
  - **Proceso Objetivo Inconsistente**: Si el proceso de **GTA:SA** está en un estado inesperado o inestable (aunque iniciado en `CREATE_SUSPENDED`), esto puede afectar la capacidad de crear **hilos** en él.
- **Solución**:
  1. Ejecuta tu aplicación con privilegios de **Administrador**.
  2. Verifica que no haya herramientas **anti-cheat**, **antivirus agresivos** o **firewalls** configurados para inspeccionar y bloquear la manipulación de procesos que puedan estar en conflicto. Agrega tu aplicación y `gta_sa.exe` a las excepciones, si aplica (con precaución).
  3. El mensaje de error del sistema (`GetLastError()`) puede proporcionar detalles adicionales para investigar la causa específica (ej: **"A process has been denied access to create threads for other processes."**).

### 10. Tiempo de Espera Agotado o Fallo en la Finalización de la Inyección

Tras crear el **hilo** remoto, el inyector espera que complete la **carga de la DLL**.

![Error 15](screenshots/error_15.png)

- **Mensaje de Error Mostrado**: `"Timeout or error waiting for DLL injection to complete. System Error: [Mensaje de error del sistema operativo]"`.
- **Causa**: El **hilo** remoto que está ejecutando `LoadLibraryA` tomó más de `Constants::DLL_INJECTION_TIMEOUT_MS` (10 segundos) en regresar, o falló y `GetExitCodeThread` retornó 0. Las causas potenciales incluyen:
  - **Problemas en la DLL Inyectada**: La `DllMain` de `samp.dll` o `omp-client.dll` está tomando mucho tiempo en ejecutarse, contiene un **bucle infinito**, un **fallo**, o un error que **impide que la DLL** se cargue correctamente (ej: **dependencias de DLLs** ausentes).
  - **Bloqueo Silencioso**: Un mecanismo de seguridad puede haber bloqueado `LoadLibraryA` pero no notificó con un error evidente de creación de **hilo**.
- **Solución**:
  1. Verifica la integridad de los archivos `samp.dll` y `omp-client.dll`. Pueden estar corruptos o ser de una versión incompatible con tu `gta_sa.exe`.
  2. Asegúrate de que **la DLL inyectada** no dependa de **otras DLLs** que puedan estar ausentes o inaccesibles en el sistema.

### 11. Fallo al Reanudar el Hilo del Proceso del Juego

Este es el paso final para iniciar el juego después de que **las DLLs** son inyectadas.

![Error 16](screenshots/error_16.png)

- **Mensaje de Error Mostrado**: `"Failed to resume the game process thread: [Mensaje de error del sistema operativo]"`.
- **Causa**: La llamada `ResumeThread` falló, lo que significa que el **hilo** principal de `gta_sa.exe` no pudo ser activado para iniciar la ejecución del juego. Este es un error raro, pero puede ocurrir si:
  - El **handle** del **hilo** del proceso se volvió inválido.
  - El sistema operativo impidió la reanudación por alguna razón, posiblemente relacionada con una interrupción de seguridad o un estado inconsistente del proceso.
  - El proceso puede haber sido terminado externamente entre la **inyección de la DLL** y el intento de reanudar el **hilo** principal.
- **Solución**: Si todas las etapas anteriores fueron exitosas y solo `ResumeThread` falló, puede ser un problema con el sistema operativo, con la propia instalación de **GTA:SA**, o con otro **software** de seguridad muy estricto. Revisa el estado de `gta_sa.exe` a través del **Administrador de Tareas** justo antes y después del error. Intentar reiniciar la computadora puede resolver problemas de estado temporal del sistema.

> [!TIP]
> En escenarios de depuración complejos, herramientas como **Process Monitor (Sysinternals Suite)** o un depurador (como **Visual Studio Debugger**, **WinDbg**, **OllyDbg**) pueden ser invaluables. Pueden ayudar a observar las llamadas de **API**, verificar errores de acceso, rastrear el estado de los **handles** e incluso inspeccionar la memoria del proceso, proporcionando una visión profunda de lo que está ocurriendo detrás de escena.

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