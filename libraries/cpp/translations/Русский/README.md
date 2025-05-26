# SA-MP Injector C++

![License](https://img.shields.io/badge/License-MIT-yellow.svg?style=flat)
![C++17](https://img.shields.io/badge/C%2B%2B-17-blue.svg?style=flat&logo=cplusplus)
![Platform](https://img.shields.io/badge/Platform-Windows-0078D6.svg?style=flat&logo=windows)
[![SA-MP | OMP](https://img.shields.io/badge/Support-SA--MP%20%7C%20OMP-yellow)](https://github.com/spc-samp/samp-injector)
![Code Quality](https://img.shields.io/badge/Code%20Quality-High-brightgreen.svg?style=flat)

**SA-MP Injector C++** превосходит определение простого инструмента для **инъекции DLL**. Это тщательно разработанная **библиотека C++**, предназначенная для предоставления надежного и всестороннего решения для программного запуска игры **Grand Theft Auto: San Andreas** (**GTA:SA**) вместе с ее многопользовательскими клиентами, в частности **SA-MP (San Andreas Multiplayer)** и **OMP (Open Multiplayer)**. Основная цель — упростить процесс запуска игры, устраняя сложности, связанные с прямым управлением процессами операционной системы и передачей аргументов командной строки.

Разработанная с учетом максимальной гибкости и упрощения интеграции, эта библиотека, реализованная только в заголовочных файлах (`header-only`), устраняет необходимость в сложных предварительных компиляциях, позволяя разработчикам напрямую включать ее в свои **проекты C++**. Она не только выполняет **основную инъекцию DLL** клиента многопользовательской игры (`samp.dll` или `omp-client.dll`), но и интеллектуально управляет всеми необходимыми параметрами подключения (**никнейм**, **IP-адрес**, **порт** и **пароль**), имитируя нативный запуск с использованием встроенных возможностей **Windows API**.

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

## Оглавление

- [SA-MP Injector C++](#sa-mp-injector-c)
  - [Языки](#языки)
  - [Оглавление](#оглавление)
  - [Основные концепции и мотивация](#основные-концепции-и-мотивация)
    - [Почему инъекция DLL?](#почему-инъекция-dll)
    - [SA-MP и OMP: различия и сходства](#sa-mp-и-omp-различия-и-сходства)
  - [Внутренняя архитектура библиотеки: глубокое погружение](#внутренняя-архитектура-библиотеки-глубокое-погружение)
    - [`constants.hpp`](#constantshpp)
    - [`types.hpp`](#typeshpp)
    - [`string_utils.hpp`](#string_utilshpp)
    - [`error_utils.hpp`](#error_utilshpp)
    - [`resource_handle.hpp`](#resource_handlehpp)
    - [`validation.hpp`](#validationhpp)
    - [`process.hpp`](#processhpp)
    - [`injector_core.hpp`](#injector_corehpp)
    - [`injector.hpp`](#injectorhpp)
  - [Подробные примеры использования](#подробные-примеры-использования)
    - [1. Подготовка среды разработки](#1-подготовка-среды-разработки)
    - [2. Базовый сценарий: подключение к серверу SA-MP](#2-базовый-сценарий-подключение-к-серверу-sa-mp)
    - [3. Продвинутый сценарий: подключение к серверу OMP](#3-продвинутый-сценарий-подключение-к-серверу-omp)
  - [Обработка распространенных ошибок и сообщений](#обработка-распространенных-ошибок-и-сообщений)
    - [1. Неверный тип инъекции](#1-неверный-тип-инъекции)
    - [2. Неверный порт сервера (формат или диапазон)](#2-неверный-порт-сервера-формат-или-диапазон)
      - [2.1. Ненumeric формат порта](#21-ненumeric-формат-порта)
      - [2.2. Порт вне допустимого диапазона](#22-порт-вне-допустимого-диапазона)
    - [3. Неверный никнейм (пустой или слишком длинный)](#3-неверный-никнейм-пустой-или-слишком-длинный)
      - [3.1. Пустой никнейм](#31-пустой-никнейм)
      - [3.2. Слишком длинный никнейм](#32-слишком-длинный-никнейм)
    - [4. Файлы игры или DLL не найдены](#4-файлы-игры-или-dll-не-найдены)
      - [4.1. Исполняемый файл игры (`gta_sa.exe`) не найден](#41-исполняемый-файл-игры-gta_saexe-не-найден)
      - [4.2. Библиотека SA-MP (`samp.dll`) не найдена](#42-библиотека-sa-mp-sampdll-не-найдена)
      - [4.3. Библиотека OMP (`omp-client.dll`) не найдена (только для инъекции OMP)](#43-библиотека-omp-omp-clientdll-не-найдена-только-для-инъекции-omp)
    - [5. Ошибка создания процесса игры](#5-ошибка-создания-процесса-игры)
    - [6. Ошибка выделения памяти в целевом процессе](#6-ошибка-выделения-памяти-в-целевом-процессе)
    - [7. Ошибка записи пути DLL в память процесса](#7-ошибка-записи-пути-dll-в-память-процесса)
    - [8. Не удалось найти основные системные функции](#8-не-удалось-найти-основные-системные-функции)
      - [8.1. `kernel32.dll` не найдена](#81-kernel32dll-не-найдена)
      - [8.2. `LoadLibraryA` не найдена](#82-loadlibrarya-не-найдена)
    - [9. Не удалось создать удалённую нить для инъекции](#9-не-удалось-создать-удалённую-нить-для-инъекции)
    - [10. Тайм-аут или сбой при завершении инъекции](#10-тайм-аут-или-сбой-при-завершении-инъекции)
    - [11. Не удалось возобновить нить процесса игры](#11-не-удалось-возобновить-нить-процесса-игры)
  - [Лицензия](#лицензия)
    - [Условия использования](#условия-использования)
      - [1. Предоставленные разрешения](#1-предоставленные-разрешения)
      - [2. Обязательные условия](#2-обязательные-условия)
      - [3. Авторские права](#3-авторские-права)
      - [4. Отказ от гарантий и ограничение ответственности](#4-отказ-от-гарантий-и-ограничение-ответственности)

## Основные концепции и мотивация

### Почему инъекция DLL?

> [!NOTE] Инъекция DLL: суть динамической загрузки.
> **Инъекция DLL (Dynamic Link Library)** — это метод, используемый в операционных системах **Microsoft Windows**, который позволяет выполнять код в адресном пространстве другого запущенного процесса. Это мощная техника с множеством законных применений, от отладки и мониторинга программ до модификации поведения приложений для расширения их функциональности.

В контексте игр, таких как **GTA San Andreas**, которые изначально не разрабатывались с интегрированной многопользовательской функциональностью, **инъекция DLL** является основой для существования многопользовательских клиентов, таких как **SA-MP** и **OMP**. Эти клиенты реализованы как **DLL**, которые после инъекции в процесс `gta_sa.exe` берут управление, перехватывают функции игры и устанавливают связь с многопользовательскими серверами.

Вместо зависимости от внешнего лаунчера или прямой модификации исполняемого файла игры, **инъекция DLL** позволяет более гибкий и программируемый запуск, что особенно полезно в средах, где требуется автоматизация подключения к конкретным серверам с предопределенными настройками.

### SA-MP и OMP: различия и сходства

**SA-MP** и **OMP** — это две основные многопользовательские платформы для **GTA San Andreas**. Обе функционируют как модификации базовой игры, превращая ее в массовую многопользовательскую онлайн-среду.

- **SA-MP (San Andreas Multiplayer)**: Оригинальный и наиболее устоявшийся клиент, широко используемый на протяжении многих лет. Его архитектура требует `samp.dll` для работы.
- **OMP (Open Multiplayer)**: Проект с открытым исходным кодом, часто рассматриваемый как преемник или более современная альтернатива **SA-MP**, предлагающая улучшения в производительности, стабильности и дополнительные функции. Требует `omp-client.dll`.

Хотя они работают схожим образом (**инъекция DLL** в процесс **GTA:SA**), библиотека **SA-MP Injector C++** была тщательно разработана для поддержки **обеих DLL**, учитывая различия в именах файлов и позволяя разработчику выбирать желаемый многопользовательский клиент через параметр конфигурации. Это обеспечивает возможность использования библиотеки с широким спектром серверов и проектов, основанных на любой из платформ.

## Внутренняя архитектура библиотеки: глубокое погружение

**SA-MP Injector C++** использует модульный и объектно-ориентированный подход (где это применимо) для управления сложностью процесса инъекции. Каждый заголовочный файл представляет собой специализированный модуль, отвечающий за определенную часть общей функциональности, что способствует ясности кода, его поддерживаемости и расширяемости.

### `constants.hpp`

Этот файл является основой всех фиксированных конфигураций библиотеки. Он определяет пространство имен `Constants` для инкапсуляции всех литералов, предотвращая загрязнение глобального пространства имен. Использование `inline constexpr` здесь критично: `constexpr` указывает, что значения вычисляются во время компиляции, оптимизируя производительность и гарантируя неизменяемость, в то время как `inline` предотвращает проблемы с повторным определением при включении файла в несколько единиц компиляции.

```cpp
#pragma once

namespace Constants {
    // Game related constants
    inline constexpr int MIN_PORT = 1;
    inline constexpr int MAX_PORT = 65535;
    inline constexpr int MAX_NICKNAME_LENGTH = 20;
    
    // File names
    inline constexpr const wchar_t* SAMP_DLL_NAME = L"samp.dll";
    inline constexpr const wchar_t* OMP_DLL_NAME = L"omp-client.dll";
    inline constexpr const wchar_t* GAME_EXE_NAME = L"gta_sa.exe";
    
    // System libraries and functions
    inline constexpr const char* KERNEL32_DLL = "kernel32.dll";
    inline constexpr const char* LOAD_LIBRARY_FUNC = "LoadLibraryA"; // 'A' для версии ANSI/8-bit
    
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
> Использование `wchar_t` для имен файлов и заголовков сообщений об ошибках — это рекомендуемая практика в **разработке для Windows**. Это обеспечивает совместимость со всеми языками и наборами символов, особенно полезно для путей к файлам, которые могут содержать **символы Unicode**. Для **API**, ожидающих `char` (например, `LoadLibraryA`), преобразование выполняется явно в `string_utils.hpp`.

### `types.hpp`

Краткий, но важный модуль для определения перечисления, которое классифицирует поддерживаемые типы инъекции. Это улучшает читаемость и безопасность типов кода, предотвращая ошибки с использованием строк или магических чисел.

```cpp
#pragma once

namespace Types {
    // Enumerações para типов инъекции suportados
    enum class Inject_Type {
        SAMP, // San Andreas Multiplayer
        OMP // Open Multiplayer
    };
}
```

### `string_utils.hpp`

Работа с **Windows API** часто требует преобразования между различными кодировками строк. Этот файл предоставляет важную утилитарную функцию для преобразования строк из **широких символов** (`std::wstring_view`, используемых во входных данных библиотеки) в строки **ANSI/8-bit** (`std::string`), которые необходимы для функций **WinAPI**, работающих с `char*` (таких как `CreateProcessA` или `GetProcAddress`).

```cpp
#pragma once

#include <string>
#include <string_view>
#include <windows.h> // Necessário para WideCharToMultiByte

namespace Utils {
    inline std::string Wide_To_Local_8Bit(std::wstring_view wstr) {
        if (wstr.empty())
            return "";
        
        // Определяет необходимый размер буфера для результирующей строки в char
        int size = WideCharToMultiByte(CP_ACP, // Code Page ANSI (зависит от локальной системы)
            0, // Без дополнительных флагов
            wstr.data(), 
            static_cast<int>(wstr.size()), 
            nullptr, // Вычисляет размер, не заполняет буфер
            0, // Размер 0, только для вычисления
            nullptr, // Символ по умолчанию для непредставимых символов
            nullptr); // Указатель на bool, указывающий, использовался ли символ по умолчанию

        if (size <= 0) // Возвращает пустую строку в случае ошибки или недопустимого размера
            return "";

        std::string result(size, 0); // Выделяет строку с определенным размером
        // Выполняет фактическое преобразование, заполняя буфер 'result'
        WideCharToMultiByte(CP_ACP, 
            0, 
            wstr.data(), 
            static_cast<int>(wstr.size()), 
            result.data(), // Буфер назначения
            size, // Размер буфера назначения
            nullptr, 
            nullptr);

        return result;
    }
}
```

> [!IMPORTANT] Важность кодировки!
> `CP_ACP` **(ANSI Code Page)**, используемая в `WideCharToMultiByte`, — это стандартная кодовая страница системы **Windows**. Это означает, что преобразование может варьироваться в зависимости от языковых настроек системы пользователя. Для большинства случаев использования имен файлов и аргументов командной строки в **SA-MP**/**OMP** (которые исторически хорошо справляются со строками **ANSI**), этот подход обычно достаточен. Однако в сценариях, требующих полной совместимости с **Unicode** для внешних систем или глобальных входных данных, потребовалось бы преобразование в **UTF-8** (`CP_UTF8`) или другие кодовые страницы. В рамках этого проекта `CP_ACP` является функциональным стандартом.

### `error_utils.hpp`

Фундаментальный компонент для удобства использования библиотеки, отвечающий за предоставление **обратной связи** пользователю в случае сбоя. Он централизует логику получения системных сообщений об ошибках и отображения диалоговых окон.

```cpp
#pragma once

#include <string>
#include <string_view>
#include <windows.h> // Для FormatMessageW и MessageBoxW
//
#include "types.hpp"
#include "constants.hpp"

namespace Utils {
    // Возвращает сообщение об ошибке системы Windows для конкретного кода ошибки
    inline std::wstring Get_System_Error_Message(DWORD error_code) {
        wchar_t buffer[512] = {0}; // Буфер для сообщения
        // FormatMessageW заполняет буфер описанием ошибки системы
        DWORD result = FormatMessageW(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, 
            nullptr, // Источник сообщения (из системы)
            error_code, 
            0, // Язык (использовать стандартный)
            buffer, 
            512, // Размер буфера
            nullptr);
        
        // Если функция выполнена успешно, возвращает строку из буфера; в противном случае — обобщенное сообщение
        return result ? std::wstring(buffer) : L"Unknown error (Code: " + std::to_wstring(error_code) + L")";
    }

    // Отображает диалоговое окно с сообщением об ошибке для пользователя
    inline void Show_Error(std::wstring_view message, Types::Inject_Type injectType) {
        // Выбирает заголовок диалогового окна на основе типа инъекции
        std::wstring title = (injectType == Types::Inject_Type::SAMP) ? Constants::ERROR_TITLE_SAMP : Constants::ERROR_TITLE_OMP;
        MessageBoxW(nullptr, // Дескриптор родительского окна (nullptr для рабочего стола)
            message.data(), 
            title.c_str(), 
            MB_OK | MB_ICONERROR); // Кнопка OK и иконка ошибки
    }
}
```

> [!NOTE] Форматирование сообщений об ошибках
> Функция `FormatMessageW` — это мощный **Windows API**, который извлекает текстовое описание кода ошибки системы. Она обрабатывает локализацию и предоставляет четкие сообщения, которые необходимы для эффективной **диагностики**, превращая `DWORD`, например `ERROR_FILE_NOT_FOUND` (2), в `L"Система не может найти указанный файл."`.

### `resource_handle.hpp`

Безопасное управление ресурсами (такими как `HANDLE` в **Windows**) критически важно для предотвращения утечек ресурсов и неопределенного поведения. Этот файл определяет `UniqueResource`, использующий `std::unique_ptr` и пользовательскую функцию для `CloseHandle`. Это соответствует принципу **RAII (Resource Acquisition Is Initialization)**, гарантируя, что `HANDLE` автоматически закрываются, когда их **обертки** выходят из области видимости, даже в случае исключений.

```cpp
#pragma once

#include <memory> // Для std::unique_ptr
#include <functional> // Для std::function
#include <windows.h> // Для HANDLE и CloseHandle

namespace Utils {
    // Псевдоним типа для std::unique_ptr, который управляет HANDLE (или указателем) с пользовательским удалителем
    // T: Тип ресурса для управления (например, HANDLE, LPVOID)
    // Deleter: Класс или лямбда, знающая, как освободить ресурс
    template<typename T, typename Deleter>
    using UniqueResource = std::unique_ptr<std::remove_pointer_t<T>, Deleter>;

    // Вспомогательная функция для создания экземпляра UniqueResource для HANDLE
    // Предполагается, что T — это тип дескриптора, и используется CloseHandle как удалитель.
    template<typename T>
    inline auto Make_Unique_Handle(T handle) {
        return UniqueResource<T, std::function<void(T)>>(handle, [](T h) {
            // Условие для проверки валидности дескриптора перед попыткой его закрытия
            // 0 и INVALID_HANDLE_VALUE считаются недействительными для большинства дескрипторов
            if (h && h != INVALID_HANDLE_VALUE)
                CloseHandle(h); // Освобождает дескриптор операционной системы
        });
    }
}
```

> [!IMPORTANT]
> Использование `UniqueResource` — это пример лучших практик **современного C++** и безопасной разработки для **Windows**. Оно значительно упрощает управление жизненным циклом **дескрипторов**, которые, если не закрыты должным образом, могут привести к утечкам памяти или ресурсов ядра, влияя на стабильность системы со временем.

### `validation.hpp`

Надежность инъекции начинается с проверки пользовательских входных данных и зависимостей файлов. Этот модуль содержит функции, которые гарантируют корректность всех предварительных условий и параметров перед попыткой начать процесс инъекции, предотвращая более сложные ошибки в дальнейшем.

```cpp
#pragma once

#include <string>
#include <string_view>
#include <filesystem> // Для std::filesystem::exists
//
#include "constants.hpp"
#include "types.hpp"
#include "string_utils.hpp" // Для Wide_To_Local_8Bit
#include "error_utils.hpp" // Для Show_Error

namespace Utils {
    // Проверяет, является ли строка порта действительным числом и находится ли в допустимом диапазоне
    inline bool Validate_Port(std::wstring_view port_str, std::wstring& error_message) {
        try {
            // Пытается преобразовать строку широких символов в std::string, а затем в int
            int port_num = std::stoi(Wide_To_Local_8Bit(port_str));

            // Проверяет, находится ли порт в допустимом диапазоне (1-65535)
            if (port_num < Constants::MIN_PORT || port_num > Constants::MAX_PORT)
                return (error_message = L"The specified port number (" + std::wstring(port_str) + 
                L") is outside the valid range of " +  std::to_wstring(Constants::MIN_PORT) + 
                L" to " + std::to_wstring(Constants::MAX_PORT) + 
                L". Please provide a valid port.", false);

            return true;
        }
        catch (...) { // Ловит любое исключение (например, std::invalid_argument для нечислового значения)
            return (error_message = L"Invalid port format. The port must be a numeric value. Please provide a valid integer for the port.", false);
        }
    }

    // Проверяет никнейм, убеждаясь, что он не пустой и его длина допустима
    inline bool Validate_Nickname(std::wstring_view nickname_str, std::wstring& error_message) {
        if (nickname_str.empty())
            return (error_message = L"Nickname cannot be empty. Please provide a valid nickname.", false);
        
        if (nickname_str.size() > Constants::MAX_NICKNAME_LENGTH)
            return (error_message = L"Nickname length exceeds the maximum allowed of " + 
                std::to_wstring(Constants::MAX_NICKNAME_LENGTH) + 
                L" characters. Please use a shorter nickname.", false);

        return true;
    }

    // Проверяет наличие критически важных файлов (gta_sa.exe, samp.dll, omp-client.dll)
    inline bool Validate_Files(const std::filesystem::path& game_path, 
        const std::filesystem::path& samp_DLL_path, 
        const std::filesystem::path& omp_DLL_path, 
        Types::Inject_Type inject_type) {
        std::wstring error_message_local; // Локальная переменная для сообщений об ошибках перед передачей в Show_Error
        
        // Проверяет наличие исполняемого файла игры
        if (!std::filesystem::exists(game_path)) {
            error_message_local = L"Game executable not found. Please ensure 'gta_sa.exe' exists at the specified path: " + game_path.wstring();
            Show_Error(error_message_local, inject_type);
            return false;
        }

        // Проверяет наличие samp.dll (необходим для обоих типов инъекции)
        if (!std::filesystem::exists(samp_DLL_path)) {
            error_message_local = L"SA-MP library not found. Please ensure 'samp.dll' exists at the specified path: " + samp_DLL_path.wstring();
            Show_Error(error_message_local, inject_type);

            return false;
        }

        // Если тип инъекции — OMP, проверяет наличие omp-client.dll
        if (inject_type == Types::Inject_Type::OMP && !std::filesystem::exists(omp_DLL_path)) {
            error_message_local = L"OMP library not found. Please ensure 'omp-client.dll' exists at the specified path for OMP injection: " + omp_DLL_path.wstring();
            Show_Error(error_message_local, inject_type);

            return false;
        }

        return true; // Все необходимые файлы найдены
    }
}
```

> [!NOTE] C++17 `std::filesystem`
> Использование `std::filesystem` — это современное дополнение к **C++17**, которое предоставляет мощный и кроссплатформенный способ взаимодействия с файловой системой. Для этого проекта в **Windows** оно упрощает обработку путей и проверку существования файлов по сравнению с более старыми **API** **WinAPI**.
>
> Убедитесь, что ваш компилятор поддерживает **C++17** для использования `std::filesystem`. Вам нужно будет настроить ваш проект для использования стандарта **C++17** (`/std:c++17` в **Visual Studio**).

### `process.hpp`

Это основной модуль, отвечающий за прямое взаимодействие с низкоуровневыми **API** **Windows** для управления процессами. Он инкапсулирует критически важные операции по созданию процесса и **инъекции DLL**, обрабатывая **дескрипторы**, **память** и **нити**.

```cpp
#pragma once

#include <string_view>
#include <optional> // Для std::optional
#include <functional> // Для std::function (используется в UniqueResource)
#include <windows.h> // API Windows
#include <memory> // Для std::unique_ptr
#include <vector> // Для std::vector (буфер аргументов)
//
#include "resource_handle.hpp" // Наша обертка для дескрипторов
#include "error_utils.hpp" // Для Get_System_Error_Message и Show_Error
#include "constants.hpp" // Глобальные константы
#include "types.hpp" // Типы инъекции

class Process {
    public:
        // Конструкторы/Деструкторы и операторы присваивания
        // Явно default и delete для обеспечения семантики значения и только перемещения.
        Process() = default;
        Process(const Process&) = delete; // Без копирования
        Process& operator=(const Process&) = delete; // Без присваивания копированием
        Process(Process&&) = default; // Семантика перемещения
        Process& operator=(Process&&) = default; // Присваивание перемещением
        ~Process() = default;

        // Структура для хранения дескрипторов процесса и нити, управляемых UniqueResource
        struct Process_Info {
            Utils::UniqueResource<HANDLE, std::function<void(HANDLE)>> process_handle;
            Utils::UniqueResource<HANDLE, std::function<void(HANDLE)>> thread_handle;
        };

        // Создает процесс игры GTA:SA в приостановленном состоянии
        std::optional<Process_Info> Create_Game_Process(std::string_view game_path, std::string_view command_args, std::string_view working_dir) {
            STARTUPINFOA startup_info{}; // Структура для информации о запуске процесса
            startup_info.cb = sizeof(STARTUPINFOA); // Определяет размер структуры

            PROCESS_INFORMATION process_info{}; // Структура, которая получит информацию о новом процессе

            // Создает изменяемый буфер для аргументов командной строки.
            // CreateProcessA изменяет буфер командной строки, поэтому std::string_view напрямую не работает.
            std::vector<char> args_buffer(command_args.size() + 1); // +1 для нулевого терминатора

            if (!command_args.empty()) {
                std::memcpy(args_buffer.data(), command_args.data(), command_args.size());
                args_buffer[command_args.size()] = '\0'; // Гарантирует нулевой терминатор
            }

            // Создает процесс
            bool success = CreateProcessA(game_path.data(), // Имя исполняемого модуля
                args_buffer.empty() ? nullptr : args_buffer.data(), // Аргументы командной строки
                nullptr, // Атрибуты безопасности процесса
                nullptr, // Атрибуты безопасности нити
                FALSE, // Не наследовать дескрипторы
                Constants::PROCESS_CREATION_FLAGS, // CREATE_SUSPENDED | DETACHED_PROCESS
                nullptr, // Среда нового процесса
                working_dir.empty() ? nullptr : working_dir.data(), // Рабочая директория
                &startup_info, // Информация о запуске
                &process_info); // Информация о созданном процессе

            if (!success) {
                // Если не удалось, получает и отображает сообщение об ошибке системы
                std::wstring error_msg = Utils::Get_System_Error_Message(GetLastError());
                Utils::Show_Error(L"Failed to create game process. Ensure 'gta_sa.exe' is not running and you have " L"sufficient permissions to execute the file. System Error: " + error_msg, Types::Inject_Type::SAMP); // Использует SAMP как заголовок по умолчанию
                
                return std::nullopt; // Возвращает пустой optional
            }

            Process_Info result;
            // Сохраняет дескрипторы процесса и нити в UniqueResource для автоматического управления
            result.process_handle = Utils::Make_Unique_Handle(process_info.hProcess);
            result.thread_handle = Utils::Make_Unique_Handle(process_info.hThread);

            return result; // Возвращает структуру с управляемыми дескрипторами
        }

        // Инъекция DLL в удаленный процесс
        bool Inject_DLL(HANDLE process, std::string_view DLL_path, std::wstring& error_message) {
            // Выделяет память в удаленном процессе для пути DLL
            LPVOID remote_memory = VirtualAllocEx(process, // Дескриптор целевого процесса
            nullptr, // Предпочтительный адрес (nullptr, чтобы система выбрала)
            DLL_path.size() + 1, // Размер пути + нулевой терминатор
            Constants::MEMORY_ALLOCATION_TYPE, // MEM_COMMIT | MEM_RESERVE
            Constants::MEMORY_PROTECTION); // PAGE_READWRITE

            if (!remote_memory)
                return (error_message = L"Failed to allocate memory in the target process. This might be due to " L"insufficient permissions or process protection mechanisms.", false);

            // Управление ресурсом для удаленно выделенной памяти.
            // Будет автоматически освобождено при выходе из области видимости.
            auto memory_guard = Utils::UniqueResource<LPVOID, std::function<void(LPVOID)>>(remote_memory, 
                [process](LPVOID ptr) { // Лямбда как удалитель
                    if (ptr)
                        VirtualFreeEx(process, ptr, 0, MEM_RELEASE); // Освобождает выделенную память
                }
            );

            // Записывает путь DLL в удаленно выделенную память
            if (!WriteProcessMemory(process, remote_memory, DLL_path.data(), DLL_path.size() + 1, nullptr))
                return (error_message = L"Failed to write DLL path to the target process memory. Verify process " L"permissions and ensure the DLL path is accessible.", false);

            // Получает дескриптор для kernel32.dll (которая загружена в собственный процесс инъектора)
            HMODULE kernel32 = GetModuleHandleA(Constants::KERNEL32_DLL);
            
            if (!kernel32)
                return (error_message = L"Failed to obtain a handle to kernel32.dll. This is an essential system " L"library and this error indicates a severe system issue.", false);

            // Получает адрес функции LoadLibraryA в kernel32.dll.
            // Этот адрес одинаков для всех процессов в одной ОС и является ключом к инъекции.
            LPVOID load_library_addr = reinterpret_cast<LPVOID>(GetProcAddress(kernel32, Constants::LOAD_LIBRARY_FUNC));

            if (!load_library_addr)
                return (error_message = L"Failed to find the address of the LoadLibraryA function in kernel32.dll. " L"This is critical for injecting the DLL.", false);

            // Создает удаленную нить в целевом процессе для выполнения LoadLibraryA
            // Аргументом для LoadLibraryA будет удаленный адрес пути DLL
            HANDLE remote_thread = CreateRemoteThread(process, // Дескриптор целевого процесса
                nullptr, // Атрибуты безопасности нити
                0, // Размер стека (0 для значения по умолчанию)
                reinterpret_cast<LPTHREAD_START_ROUTINE>(load_library_addr), // Адрес LoadLibraryA
                remote_memory, // Аргумент для LoadLibraryA (путь DLL)
                0, // Флаги создания (0 для немедленного запуска)
                nullptr); // ID нити (nullptr, чтобы не возвращать)

            if (!remote_thread)
                return (error_message = L"Failed to create a remote thread in the target process to execute the " L"DLL injection. This could be due to security restrictions or process "
                    L"state. System Error: " + Utils::Get_System_Error_Message(GetLastError()), false);

            // Управление ресурсом для дескриптора удаленной нити
            auto thread_guard = Utils::Make_Unique_Handle(remote_thread);

            // Ожидает завершения удаленной нити (инъекции DLL) или достижения тайм-аута
            DWORD wait_result = WaitForSingleObject(remote_thread, Constants::DLL_INJECTION_TIMEOUT_MS);

            if (wait_result != WAIT_OBJECT_0) {
                return (error_message = L"Timeout or error waiting for DLL injection to complete. " L"System Error: " + Utils::Get_System_Error_Message(GetLastError()), false);

            // Получает код выхода удаленной нити.
            // Для LoadLibraryA код выхода 0 означает сбой (не удалось загрузить DLL).
            DWORD exit_code = 0;

            if (!GetExitCodeThread(remote_thread, &exit_code) || exit_code == 0)
                return (error_message = L"DLL injection failed or returned an error. The LoadLibrary call " L"may have failed in the target process.", false);

            return true; // Инъекция успешна
        }
};
```

> [!NOTE] Надежный дизайн с `std::optional` и RAII
> Модуль `process.hpp` демонстрирует надежный и безопасный дизайн. Функция `Create_Game_Process` возвращает `std::optional<Process_Info>`. Это позволяет функции явно и элегантно сигнализировать о сбоях в создании процесса (возвращая `std::nullopt`) без использования исключений или неоднозначных кодов ошибок в основном возвращаемом значении.
>
> Более того, структура `Process_Info` использует `Utils::UniqueResource<HANDLE, std::function<void(HANDLE)>>` для инкапсуляции **дескрипторов** процесса и **нити**. Это пример шаблона **RAII (Resource Acquisition Is Initialization)**, который гарантирует, что дескрипторы операционной системы (такие как `hProcess` и `hThread`) автоматически закрываются через `CloseHandle`, когда объект `Process_Info` выходит из области видимости. Это устраняет утечки дескрипторов, которые являются распространенной причиной нестабильности и чрезмерного потребления ресурсов в **приложениях Windows** длительного действия.
>
> Аналогично, внутри функции `Inject_DLL` используется `UniqueResource` для управления удаленно выделенной памятью (`VirtualAllocEx`), гарантируя, что она освобождается (`VirtualFreeEx`) сразу после того, как перестает быть нужной, или в случае сбоя. Это строгое управление ресурсами значительно способствует надежности и стабильности **SA-MP Injector C++**.

### `injector_core.hpp`

Это оркестрирующий класс, объединяющий все функциональности предыдущих модулей. Он координирует проверку, построение аргументов командной строки, создание процесса и вызовы **инъекции DLL**.

```cpp
#pragma once

#include <string_view>
#include <sstream> // Для построения строк с stringstream
#include <filesystem> // Для обработки путей
//
#include "process.hpp" // Функции создания/инъекции процесса
#include "validation.hpp" // Функции проверки входных данных
#include "string_utils.hpp" // Функции преобразования строк
#include "error_utils.hpp" // Функции обработки ошибок
#include "constants.hpp" // Константы библиотеки
#include "types.hpp" // Типы инъекции

namespace Injector {
    class Injector_Core {
        public:
            // Конструкторы/Деструкторы для семантики перемещения
            Injector_Core() = default;
            Injector_Core(const Injector_Core&) = delete; // Запрещает копирование
            Injector_Core& operator=(const Injector_Core&) = delete; // Запрещает присваивание копированием
            Injector_Core(Injector_Core&&) = default; // Разрешает перемещение
            Injector_Core& operator=(Injector_Core&&) = default; // Разрешает присваивание перемещением
            ~Injector_Core() = default;

            // Основная функция, оркестрирующая запуск и инъекцию игры
            bool Initialize_Game(Types::Inject_Type inject_type, std::wstring_view folder, 
                std::wstring_view nickname, 
                std::wstring_view ip, 
                std::wstring_view port, 
                std::wstring_view password) {
                namespace fs = std::filesystem; // Псевдоним для std::filesystem

                // Строит полные пути к необходимым файлам
                fs::path game_path = fs::path(folder) / Constants::GAME_EXE_NAME; // Например: C:\GTA\gta_sa.exe
                fs::path samp_DLL_path = fs::path(folder) / Constants::SAMP_DLL_NAME; // Например: C:\GTA\samp.dll
                fs::path omp_DLL_path = fs::path(folder) / Constants::OMP_DLL_NAME; // Например: C:\GTA\omp-client.dll

                // 1. Проверка файлов
                if (!Utils::Validate_Files(game_path, samp_DLL_path, omp_DLL_path, inject_type))
                    return false; // Ошибка уже отображена функцией проверки
                
                std::wstring error_message_local; // Для получения сообщений об ошибках от проверок

                // 2. Проверка порта
                if (!Utils::Validate_Port(port, error_message_local))
                    return (Utils::Show_Error(error_message_local, inject_type), false);

                // 3. Проверка никнейма
                if (!Utils::Validate_Nickname(nickname, error_message_local))
                    return (Utils::Show_Error(error_message_local, inject_type), false);

                // 4. Преобразование Wide-char в Local 8-bit (необходимо для API ANSI)
                std::string nickname_str = Utils::Wide_To_Local_8Bit(nickname);
                std::string ip_str = Utils::Wide_To_Local_8Bit(ip);
                std::string port_str = Utils::Wide_To_Local_8Bit(port);
                std::string password_str = Utils::Wide_To_Local_8Bit(password);
                // Преобразует также пути в std::string (требуются для CreateProcessA как char*)
                std::string game_path_str = Utils::Wide_To_Local_8Bit(game_path.wstring());
                std::string folder_str = Utils::Wide_To_Local_8Bit(folder);
                std::string samp_DLL_path_str = Utils::Wide_To_Local_8Bit(samp_DLL_path.wstring());
                std::string omp_DLL_path_str = Utils::Wide_To_Local_8Bit(omp_DLL_path.wstring());

                // 5. Построение аргументов командной строки
                std::string args = Build_Command_Args(nickname_str, ip_str, port_str, password_str);

                // Создает экземпляр класса Process для управления операциями с процессом
                Process process_core;
                
                // 6. Создание процесса игры (приостановленного)
                auto process_info_opt = process_core.Create_Game_Process(game_path_str, args, folder_str);

                if (!process_info_opt)
                    return false; // Ошибка уже отображена функцией создания процесса

                // Разыменовывает optional для получения структуры Process_Info
                auto& process_info = *process_info_opt; 
                std::wstring inject_error_message; // Для получения сообщений об ошибках инъекции

                // 7. Инъекция samp.dll
                if (!process_core.Inject_DLL(process_info.process_handle.get(), samp_DLL_path_str, inject_error_message))
                    return (Utils::Show_Error(L"Failed to inject samp.dll: " + inject_error_message, inject_type), false);

                // 8. Условная инъекция omp-client.dll (только если это OMP)
                if (inject_type == Types::Inject_Type::OMP) {
                    if (!process_core.Inject_DLL(process_info.process_handle.get(), omp_DLL_path_str, inject_error_message))
                        return (Utils::Show_Error(L"Failed to inject omp-client.dll: " + inject_error_message, inject_type), false);
                }

                // 9. Возобновление процесса игры
                // Процесс был создан в приостановленном состоянии, чтобы позволить инъекцию.
                // Теперь, когда DLL инъектированы, его можно возобновить.
                if (ResumeThread(process_info.thread_handle.get()) == static_cast<DWORD>(-1))
                    return (Utils::Show_Error(L"Failed to resume the game process thread: " + Utils::Get_System_Error_Message(GetLastError()), inject_type), false);

                return true; // Успех на всех этапах!
            }
        private:
            // Строит строку аргументов командной строки для исполняемого файла игры
            std::string Build_Command_Args(const std::string& nickname, const std::string& ip, const std::string& port, const std::string& password) {
                std::stringstream command_args_stream; // Использует stringstream для эффективного построения

                // SA-MP и OMP ожидают аргументы "-c -n [nickname] -h [ip] -p [port]"
                command_args_stream << Constants::CMD_ARG_CONFIG << " " 
                    << Constants::CMD_ARG_NICKNAME << " " << nickname << " " 
                    << Constants::CMD_ARG_HOST << " " << ip << " " 
                    << Constants::CMD_ARG_PORT << " " << port;

                // Добавляет пароль только если он не пустой
                if (!password.empty())
                    command_args_stream << " " << Constants::CMD_ARG_PASSWORD << " " << password;

                return command_args_stream.str();
            }
    };
}
```

> [!CAUTION] Двойная инъекция (SA-MP и OMP)
> Хотя процесс для **OMP** включает инъекцию `omp-client.dll` *в дополнение* к `samp.dll`, это соответствует тому, как обычно работает **OMP**. Клиент **OMP** часто использует `samp.dll` как **основу** или **прокси** для определенных функций, в то время как `omp-client.dll` расширяет или переопределяет поведение.
>
> Крайне важно, чтобы **обе DLL** присутствовали и были функциональны в директории игры для успешной **инъекции OMP**. Если одна из них не работает, игра может не запуститься должным образом, или многопользовательский клиент может не загрузиться.

### `injector.hpp`

Это файл интерфейса библиотеки. Это единственный файл, который конечному пользователю нужно будет включить для использования **SA-MP Injector C++**. Он выступает как обертка для класса `Injector::Injector_Core`, упрощая интерфейс до единственной глобальной функции `Initialize_Game`.

```cpp
#pragma once

#include <string_view>
//
#include "injector_core.hpp" // Основной класс с логикой
#include "error_utils.hpp" // Для отображения ошибок (в случае неверного типа инъекции)
#include "types.hpp" // Перечисление типов
#include "constants.hpp" // Константы (для имен типов инъекции)

// Высокоуровневый интерфейс библиотеки.
// Упрощает использование, предоставляя только эту глобальную функцию.
inline bool Initialize_Game(std::wstring_view inject_type_str, std::wstring_view folder, 
    std::wstring_view nickname, 
    std::wstring_view ip, 
    std::wstring_view port, 
    std::wstring_view password) {
    Types::Inject_Type type; // Переменная для хранения типа инъекции

    // Преобразует строку типа инъекции в enum Inject_Type
    if (inject_type_str == Constants::INJECT_TYPE_SAMP)
        type = Types::Inject_Type::SAMP;
    
    else if (inject_type_str == Constants::INJECT_TYPE_OMP)
        type = Types::Inject_Type::OMP;
    
    else
        // Если строка типа инъекции неверна, отображает ошибку и возвращает false
        return (Utils::Show_Error(L"Invalid injection mode specified. Please use 'samp' or 'omp'.", Types::Inject_Type::SAMP), false); // Использует SAMP как заголовок по умолчанию

    Injector::Injector_Core injector; // Создает экземпляр объекта, содержащего основную логику
    
    // Делегирует вызов функции Initialize_Game класса Injector_Core
    return injector.Initialize_Game(type, folder, nickname, ip, port, password);
}
```

> [!NOTE] Дизайн `inline` для `header-only`
> Использование ключевого слова `inline` для всех функций в этом файле и других утилитах позволяет библиотеке быть `header-only`. `inline` предлагает компилятору вставлять тело функции непосредственно в точки вызова, но его основным эффектом здесь является ослабление **правила одного определения (ODR)**, чтобы функция могла быть определена в нескольких файлах `.obj` (что произошло бы, если несколько `.cpp` включали `injector.hpp`). Этап **линковки** гарантирует, что в исполняемом файле будет только одна финальная версия.

## Подробные примеры использования

Чтобы интегрировать **SA-MP Injector C++** в ваш проект, следуйте инструкциям и рассмотрите сценарии ниже.

### 1. Подготовка среды разработки

- **Компилятор C++**: Рекомендуется компилятор, **поддерживающий C++17**. **Visual Studio** с `vcpkg` (для `std::filesystem`) или **GCC/Clang (версия 17+)** — подходящие варианты.
- **Настройка проекта**:
  - Создайте новый проект **C++** (например, консольный проект).
  - Скопируйте **все** файлы `.hpp` из **SA-MP Injector C++** в папку, доступную вашему проекту (например, в папку **headers**).
  - Убедитесь, что стандарт **C++** установлен на **C++17**. Это важно для максимальной совместимости с библиотеками **SA-MP** и **OMP**. В **Visual Studio**: `Project Properties > Configuration Properties > C/C++ > Language > C++ Language Standard -> "ISO C++17 Standard (/std:c++17)"`
- **Разрешения**: Вашему исполняемому файлу, вероятно, потребуется запуск от имени **Администратора (не обязательно)** для создания процессов и **инъекции DLL** в среде системы. В **Visual Studio** это можно сделать в: `Project Properties > Configuration Properties > Linker > Manifest File > UAC Execution Level -> "requireAdministrator (/LEVEL='requireAdministrator')"`

### 2. Базовый сценарий: подключение к серверу SA-MP

Это наиболее распространенный случай использования, запускающий **GTA:SA** и подключающий к серверу **SA-MP** с конкретным **никнеймом** и **IP**/**портом**.

```cpp
// main.cpp
#include <iostream>
#include <string>
#include <codecvt> // Для std::wstring_convert (устаревший, но функциональный для этого случая)
#include <locale> // Для std::codecvt_utf8_to_utf16
//
#include "injector.hpp" // Единственное необходимое включение библиотеки!

int Main(int argc, char* argv[]) {
    // Определение переменных конфигурации
    // Измените эти пути и детали сервера в соответствии с вашей локальной конфигурацией
    std::wstring folder = L"C:\\Jogos\\GTA San Andreas"; // Где находятся gta_sa.exe, samp.dll
    std::wstring nickname = L"Имя";
    std::wstring ip = L"127.0.0.1"; // Пример: ваш локальный сервер
    std::wstring port = L"7777";
    std::wstring password = L""; // Оставьте пустым, если пароля нет

    // Опционально: Разрешить пользователю предоставлять настройки через командную строку (упрощенно)
    // Для более надежной обработки аргументов используйте библиотеку разбора аргументов.
    if (argc > 1) {
        // Пример: если первый аргумент — путь
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

    std::wcout << L"Запуск SA-MP..." << std::endl;
    std::wcout << L"Папка игры: " << folder << std::endl;
    std::wcout << L"Никнейм: " << nickname << std::endl;
    std::wcout << L"Сервер: " << ip << L":" << port << std::endl;

    // Вызов функции библиотеки для запуска игры
    if (Initialize_Game(L"samp", // Тип инъекции: SA-MP
        folder, // Путь к папке игры
        nickname, // Желаемый никнейм
        ip, // IP сервера
        port, // Порт сервера (строка)
        password)) { // Пароль сервера (строка, может быть пустой)
        std::wcout << L"\n--- SA-MP успешно запущен! ---" << std::endl;
        std::wcout << L"Игра запущена в отдельном процессе." << std::endl;
    }
    else {
        std::wcout << L"\n--- Ошибка запуска SA-MP! ---" << std::endl;
        std::wcout << L"Проверьте отображаемые сообщения об ошибках." << std::endl;
    }

    // Оставляет консоль открытой для просмотра сообщений
    std::wcout << L"\nНажмите Enter для закрытия программы." << std::endl;
    std::wcin.ignore();

    return 0;
}
```

**Для компиляции и запуска:**

```bash
# Пример с g++ (Linux/MinGW/MSYS2) - Требуется libstdc++fs для filesystem
# Важно убедиться, что toolchain не использует версию C++,
# которая приводит к несовместимости в процессе инъекции.
# Проверьте документацию вашего компилятора для флагов совместимости ABI.
g++ main.cpp -o my_launcher -std=c++17 -Wall -lstdc++fs -municode -lkernel32

# Пример с MSVC (Visual Studio Developer Command Prompt)
# Флаг '/std:c++17' обеспечивает соответствие стандарту C++17.
cl /EHsc /std:c++17 /permissive- /FS /utf-8 main.cpp /link /OUT:my_launcher.exe
```

> [!NOTE] Совместимость компилятора и C++
> **SA-MP** и **OMP**, как устаревшие проекты, компилируются с использованием специфических инструментов, определяющих их **Application Binary Interface (ABI)**. Хотя эта библиотека использует **C++17**, **крайне важно, чтобы DLL SA-MP и OMP, с которыми она взаимодействует, также были совместимы с ABI вашего компилятора и используемой версией среды выполнения C++ (CRT)**.
>
> Использование компилятора или версии **C++**, значительно отличающихся от тех, что использовались для **сборки DLL** игры, может привести к тонким проблемам (например, с выделением памяти или передачей параметров), которые не легко **диагностируются** и не приведут к явной ошибке инъектора. По этой причине **C++17 является максимально рекомендуемой версией**, так как более поздние версии могут вводить изменения в **ABI** или **CRT**, которые не поддерживаются более старыми модулями игры.

### 3. Продвинутый сценарий: подключение к серверу OMP

Для **OMP** логика идентична **SA-MP**, но вы указываете `L"omp"` как `inject_type` и убедитесь, что `omp-client.dll` присутствует в директории игры.

```cpp
// main.cpp
#include <iostream>
#include <string>
#include <codecvt> // Для std::wstring_convert (устаревший, но функциональный для этого случая)
#include <locale> // Для std::codecvt_utf8_to_utf16
//
#include "injector.hpp" // Единственное необходимое включение библиотеки!

int Main() {
    // Определение переменных конфигурации
    // Измените эти пути и детали сервера в соответствии с вашей локальной конфигурацией
    std::wstring folder = L"C:\\Jogos\\GTA San Andreas"; // Где находятся gta_sa.exe, samp.dll и omp-client.dll
    std::wstring nickname = L"Имя";
    std::wstring ip = L"127.0.0.1"; // Пример: ваш локальный сервер
    std::wstring port = L"7777";
    std::wstring password = L""; // Оставьте пустым, если пароля нет

    // Опционально: Разрешить пользователю предоставлять настройки через командную строку (упрощенно)
    // Для более надежной обработки аргументов используйте библиотеку разбора аргументов.
    if (argc > 1) {
        // Пример: если первый аргумент — путь
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

    std::wcout << L"Запуск OMP..." << std::endl;
    std::wcout << L"Папка игры: " << folder << std::endl;
    std::wcout << L"Никнейм: " << nickname << std::endl;
    std::wcout << L"Сервер: " << ip << L":" << port << std::endl;

    // Вызов функции библиотеки для запуска игры
    if (Initialize_Game(L"omp", // Тип инъекции: OMP
        folder, // Путь к папке игры
        nickname, // Желаемый никнейм
        ip, // IP сервера
        port, // Порт сервера (строка)
        password)) { // Пароль сервера (строка, может быть пустой)
        std::wcout << L"\n--- OMP успешно запущен! ---" << std::endl;
        std::wcout << L"Игра запущена в отдельном процессе." << std::endl;
    }
    else {
        std::wcout << L"\n--- Ошибка запуска OMP! ---" << std::endl;
        std::wcout << L"Проверьте отображаемые сообщения об ошибках." << std::endl;
    }

    // Оставляет консоль открытой для просмотра сообщений
    std::wcout << L"\nНажмите Enter для закрытия программы." << std::endl;
    std::wcin.ignore();

    return 0;
}
```

## Обработка распространенных ошибок и сообщений

**SA-MP Injector C++** приоритизирует удобство использования, и важной частью этого является предоставление **четкой обратной связи** пользователю в случае сбоя. Сообщения об ошибках отображаются через диалоговые окна **Windows** (`MessageBoxW`) и классифицируются по типу **инъекции (SA-MP или OMP)** для большего контекста. Это гарантирует, что вы точно знаете, что пошло не так, и как решить проблему.

Вот некоторые из распространенных ошибок, с которыми вы можете столкнуться, их вероятные причины и решения, сопровождаемые визуальными примерами того, как эти диалоговые окна отображаются для конечного пользователя:

### 1. Неверный тип инъекции

Если указанный `inject_type` в функции `Initialize_Game` не является `L"samp"` или `L"omp"`, библиотека не сможет определить, какой многопользовательский клиент вы намерены запустить.

![Error 1](screenshots/error_1.png)

- **Отображаемое сообщение об ошибке**: `"Invalid injection mode specified. Please use 'samp' or 'omp'."`
- **Причина**: Первый аргумент функции `Initialize_Game` (`std::wstring_view inject_type`) не соответствует ожидаемым значениям `L"samp"` или `L"omp"`. Это может быть опечатка, пустая строка или нераспознанное значение.
- **Решение**: Убедитесь, что `std::wstring_view inject_type_str` правильно установлен как `L"samp"` или `L"omp"`. Обязательно используйте префикс `L` для литералов **широких символов** при определении строк для совместимости с константами библиотеки.
    ```cpp
    // Правильно:
    Initialize_Game(L"samp", /* другие параметры */);
    Initialize_Game(L"omp", /* другие параметры */);

    // Неправильно (вызовет ошибку):
    // Initialize_Game(L"invalid", /* другие параметры */);
    // Initialize_Game(L"", /* другие параметры */);
    ```

### 2. Неверный порт сервера (формат или диапазон)

Порт — это важный числовой параметр для подключения к серверу. Эта ошибка возникает, если значение не может быть интерпретировано как действительное число или находится вне допустимого диапазона **(1–65535)**.

#### 2.1. Ненumeric формат порта

![Error 2](screenshots/error_2.png)

- **Отображаемое сообщение об ошибке**: `"Invalid port format. The port must be a numeric value. Please provide a valid integer for the port."`
- **Причина**: Аргумент `port` (`std::wstring_view`) содержит символы, которые не являются числовыми цифрами, или не может быть преобразован в целое число.
- **Решение**: Укажите строку, содержащую только цифры и представляющую действительное целое число.
    ```cpp
    // Правильно:
    Initialize_Game(/* другие параметры */, L"7777", /* другие параметры */);

    // Неправильно (неверный формат):
    // Initialize_Game(/* другие параметры */, L"port7777", /* другие параметры */);

    // Неправильно (недействительно):
    // Initialize_Game(/* другие параметры */, L"invalid", /* другие параметры */);
    ```

#### 2.2. Порт вне допустимого диапазона

![Error 3](screenshots/error_3.png)

- **Отображаемое сообщение об ошибке**: `"The specified port number (XXXX) is outside the valid range of 1 to 65535. Please provide a valid port."` (**XXXX** будет значением, которое вы пытались использовать).
- **Причина**: Указанный порт является действительным числом, но находится ниже `1` (зарезервировано или не используется) или выше `65535` (максимальный предел для **портов TCP/UDP**).
- **Решение**: Укажите порт в диапазоне от `1` до `65535`. Обычные порты для **SA-MP**/**OMP** — это `7777` или `7778`.
    ```cpp
    // Правильно:
    Initialize_Game(/* другие параметры */, L"7777", /* другие параметры */);

    // Неправильно (вне диапазона):
    // Initialize_Game(/* другие параметры */, L"0", /* другие параметры */); // Слишком низкий
    // Initialize_Game(/* другие параметры */, L"65536", /* другие параметры */); // Слишком высокий
    // Initialize_Game(/* другие параметры */, L"-1", /* другие параметры */); // Отрицательное значение
    ```

### 3. Неверный никнейм (пустой или слишком длинный)

**Никнейм** игрока проверяется, чтобы гарантировать его принятие клиентом игры.

#### 3.1. Пустой никнейм

![Error 4](screenshots/error_4.png)

- **Отображаемое сообщение об ошибке**: `"Nickname cannot be empty. Please provide a valid nickname."`
- **Причина**: Аргумент `nickname` (`std::wstring_view`) был передан как пустая строка.
- **Решение**: Убедитесь, что никнейм не пустой.
    ```cpp
    // Правильно:
    Initialize_Game(/* другие параметры */, L"Имя", /* другие параметры */);

    // Неправильно (пустой):
    // Initialize_Game(/* другие параметры */, L"", /* другие параметры */);
    ```

#### 3.2. Слишком длинный никнейм

![Error 5](screenshots/error_5.png)

- **Отображаемое сообщение об ошибке**: `"Nickname length exceeds the maximum allowed of 20 characters. Please use a shorter nickname."`
- **Причина**: Длина предоставленного **никнейма** превышает `Constants::MAX_NICKNAME_LENGTH`, который составляет `20` символов.
- **Решение**: Используйте **никнейм** длиной не более `20` символов.
    ```cpp
    // Правильно:
    Initialize_Game(/* другие параметры */, L"Имя", /* другие параметры */);

    // Неправильно (слишком длинный):
    // Initialize_Game(/* другие параметры */, L"ЭтотНикСлишкомДлинныйИПревышаетДвадцатьСимволов", /* другие параметры */);
    ```

### 4. Файлы игры или DLL не найдены

Это одна из самых распространенных причин сбоев. Библиотека требует, чтобы `gta_sa.exe`, `samp.dll` и, для **OMP**, `omp-client.dll` присутствовали в ожидаемых местах.

#### 4.1. Исполняемый файл игры (`gta_sa.exe`) не найден

![Error 6](screenshots/error_6.png)

- **Отображаемое сообщение об ошибке**: `"Game executable not found. Please ensure 'gta_sa.exe' exists at the specified path: [полный путь]"`. `[полный путь]` будет включать папку и имя файла.
- **Причина**: Файл `gta_sa.exe` не найден в папке, указанной в аргументе `folder`.
- **Решение**:
  1. Проверьте, указывает ли `folder` (`std::wstring_view`) на правильную папку установки **GTA San Andreas**.
  2. Убедитесь, что `gta_sa.exe` существует в этой папке и его имя не было изменено.

#### 4.2. Библиотека SA-MP (`samp.dll`) не найдена

![Error 7](screenshots/error_7.png)

- **Отображаемое сообщение об ошибке**: `"SA-MP library not found. Please ensure 'samp.dll' exists at the specified path: [полный путь]"`.
- **Причина**: Файл `samp.dll` не найден в папке, указанной в аргументе `folder`. **Эта DLL** требуется для **обоих** типов инъекции (`samp` и `omp`).
- **Решение**: Убедитесь, что `samp.dll` присутствует в папке установки **GTA San Andreas**.

#### 4.3. Библиотека OMP (`omp-client.dll`) не найдена (только для инъекции OMP)

![Error 8](screenshots/error_8.png)

- **Отображаемое сообщение об ошибке**: `"OMP library not found. Please ensure 'omp-client.dll' exists at the specified path for OMP injection: [полный путь]"`.
- **Причина**: Если вы указали `L"omp"` как тип инъекции, но файл `omp-client.dll` не найден в указанной папке.
- **Решение**: Загрузите последнюю версию клиента **OMP** и убедитесь, что `omp-client.dll` (и `samp.dll`) присутствуют в папке установки **GTA San Andreas**.

### 5. Ошибка создания процесса игры

Это более сложная ошибка, так как она связана с **разрешениями операционной системы** и текущим состоянием `gta_sa.exe`.

![Error 9](screenshots/error_9.png)

- **Отображаемое сообщение об ошибке**: `"Failed to create game process. Ensure 'gta_sa.exe' is not running and you have sufficient permissions to execute the file. System Error: [Сообщение об ошибке операционной системы]"`. Сообщение системы будет добавлено через `GetLastError()` (например, `Access is denied.` или `The requested operation requires elevation.`).
- **Причина**: Вызов `CreateProcessA` для запуска `gta_sa.exe` не удался. Распространенные причины включают:
  - **Процесс уже запущен**: Экземпляр `gta_sa.exe` уже активен и блокирует новую попытку запуска.
  - **Недостаточно разрешений**: Ваше приложение не имеет необходимых привилегий (например, администратор) для создания процесса в определенных конфигурациях системы (**UAC** включен, защищенные папки и т.д.).
  - **Проблемы с исполняемым файлом**: `gta_sa.exe` может быть поврежден или заблокирован другим программным обеспечением (например, неправильно настроенным антивирусом).
- **Решение**:
  1. Проверьте Диспетчер задач и убедитесь, что нет запущенных экземпляров `gta_sa.exe`. Завершите их, если они есть.
  2. Запустите ваше приложение, использующее библиотеку, с правами **Администратора**. Щелкните правой кнопкой мыши на исполняемом файле и выберите **"Запуск от имени администратора"**.
  3. Если **антивирус** или **программное обеспечение** безопасности мешает, добавьте ваше приложение и/или папку **GTA:SA** в исключения антивируса (делайте это осторожно и только если уверены в целостности ваших файлов).

### 6. Ошибка выделения памяти в целевом процессе

Библиотека пытается выделить небольшой участок памяти в `gta_sa.exe` для копирования **пути DLL**.

![Error 10](screenshots/error_10.png)

- **Отображаемое сообщение об ошибке**: `"Failed to allocate memory in the target process. This might be due to insufficient permissions or process protection mechanisms."`
- **Причина**: Функция `VirtualAllocEx` (используемая для выделения памяти внутри другого процесса) не удалась. Это наиболее вероятно, если:
  - Процесс **GTA:SA** (даже будучи в приостановленном состоянии) имеет защитные механизмы или **патчи против инъекций**, которые предотвращают выделение памяти внешними процессами.
  - Ваше приложение не имеет повышенных разрешений, необходимых для управления памятью другого процесса.
  - (Менее распространено) В системе наблюдается крайний дефицит виртуальной памяти.
- **Решение**:
  1. Запустите ваше приложение с правами **Администратора**.
  2. Убедитесь, что игра не имеет модификаций или **патчей безопасности**, которые могут блокировать попытки инъекции или управления памятью (это чаще встречается в модифицированных средах или с определенными сторонними инструментами защиты от читов).

### 7. Ошибка записи пути DLL в память процесса

После выделения памяти библиотека пытается скопировать **путь DLL** в нее.

![Error 11](screenshots/error_11.png)

- **Отображаемое сообщение об ошибке**: `"Failed to write DLL path to the target process memory. Verify process permissions and ensure the DLL path is accessible."`
- **Причина**: Функция `WriteProcessMemory` не смогла скопировать **байты пути DLL** в удаленно выделенную память в `gta_sa.exe`. Это обычно указывает на:
  - **Разрешения на запись**: Ваше приложение не имеет прав на запись в эту область памяти или в процесс **GTA:SA**.
  - **Недействительный дескриптор**: Дескриптор процесса (`process_handle`) каким-то образом стал недействительным между выделением и записью, что очень редко из-за использования `UniqueResource`, но может происходить в экстремальных системных условиях.
  - **Проблемы защиты памяти**: Защита памяти (от ОС или модификаций игры) предотвратила запись.
- **Решение**: Запустите как **Администратор**. Проверьте, что `gta_sa.exe` и его окружение не содержат инструментов, которые могут блокировать операции с памятью.

### 8. Не удалось найти основные системные функции

Эти **API** являются критически важными для **Windows**; ошибки здесь указывают на фундаментальную проблему с операционной системой или средой выполнения.

#### 8.1. `kernel32.dll` не найдена

![Error 12](screenshots/error_12.png)

- **Отображаемое сообщение об ошибке**: `"Failed to obtain a handle to kernel32.dll. This is an essential system library and this error indicates a severe system issue."`
- **Причина**: `kernel32.dll` — одна из самых базовых **DLL** в **Windows**, содержащая основные функции, такие как `CreateProcess`, `VirtualAllocEx` и т.д. Если `GetModuleHandleA` не может получить **дескриптор** для неё, это означает, что с операционной системой существуют очень серьёзные проблемы.
- **Решение**: Это **критическая** ошибка, которая редко вызывается библиотекой или вашим приложением. Она указывает на повреждение системных файлов, серьёзные проблемы с **Windows** или крайне необычную установку **ОС**. Рекомендуется выполнить проверку целостности системы (например, `sfc /scannow` в **командной строке** от имени **администратора**) или, в крайнем случае, переустановить **Windows**.

#### 8.2. `LoadLibraryA` не найдена

![Error 13](screenshots/error_13.png)

- **Отображаемое сообщение об ошибке**: `"Failed to find the address of the LoadLibraryA function in kernel32.dll. This is critical for injecting the DLL."`
- **Причина**: Хотя `kernel32.dll` была найдена, функция `LoadLibraryA` не могла быть разрешена через `GetProcAddress`. Хотя это крайне необычно, это может быть результатом повреждения **файла DLL** `kernel32.dll` или крайне нестандартной среды выполнения.
- **Решение**: Как и в случае с ошибкой `kernel32.dll` выше, это указывает на серьёзную проблему в операционной системе.

### 9. Не удалось создать удалённую нить для инъекции

После подготовки удалённой среды и копирования **пути к DLL** создаётся новая **нить** в процессе игры для "вызова" `LoadLibraryA`.

![Error 14](screenshots/error_14.png)

- **Отображаемое сообщение об ошибке**: `"Failed to create a remote thread in the target process to execute the DLL injection. This could be due to security restrictions or process state. System Error: [Сообщение об ошибке операционной системы]"`.
- **Причина**: Вызов `CreateRemoteThread` не удался. Эта ошибка часто встречается в системах с мощными механизмами **анти-инъекции** или когда программа интенсивно отслеживает поведение процесса:
  - **Механизмы безопасности**: Инструменты **анти-чит**, **программное обеспечение** безопасности или определённые политики **Windows** могут обнаруживать и блокировать попытки создания **нитей** в процессах третьих сторон.
  - **Нестабильное состояние целевого процесса**: Если процесс **GTA:SA** находится в неожиданном или нестабильном состоянии (хотя и запущен в режиме `CREATE_SUSPENDED`), это может повлиять на возможность создания **нитей** в нём.
- **Решение**:
  1. Запустите ваше приложение с правами **администратора**.
  2. Проверьте, нет ли инструментов **анти-чит**, **агрессивных антивирусов** или **фаерволов**, настроенных на проверку и блокировку манипуляций с процессами, которые могут конфликтовать. Добавьте ваше приложение и `gta_sa.exe` в исключения, если это применимо (с осторожностью).
  3. Сообщение об ошибке системы (`GetLastError()`) может предоставить дополнительные детали для выяснения конкретной причины (например: **"A process has been denied access to create threads for other processes."**).

### 10. Тайм-аут или сбой при завершении инъекции

После создания **удалённой нити** инжектор ожидает, пока она завершит **загрузку DLL**.

![Error 15](screenshots/error_15.png)

- **Отображаемое сообщение об ошибке**: `"Timeout or error waiting for DLL injection to complete. System Error: [Сообщение об ошибке операционной системы]"`.
- **Причина**: **Удалённая нить**, выполняющая `LoadLibraryA`, заняла больше времени, чем `Constants::DLL_INJECTION_TIMEOUT_MS` (10 секунд), чтобы вернуть результат, или она завершилась с ошибкой, и `GetExitCodeThread` вернул 0. Возможные причины включают:
  - **Проблемы с инжектируемой DLL**: `DllMain` в `samp.dll` или `omp-client.dll` выполняется слишком долго, содержит **бесконечный цикл**, **сбой** или ошибку, которая **препятствует загрузке DLL** (например, отсутствуют **зависимости DLL**).
  - **Тихая блокировка**: Механизм безопасности мог заблокировать `LoadLibraryA`, но не сообщил об этом с явной ошибкой создания **нити**.
- **Решение**:
  1. Проверьте целостность файлов `samp.dll` и `omp-client.dll`. Они могут быть повреждены или несовместимы с вашим `gta_sa.exe`.
  2. Убедитесь, **что инжектируемая DLL** не зависит от **других DLL**, которые могут отсутствовать или быть недоступными в системе.

### 11. Не удалось возобновить нить процесса игры

Это последний шаг для запуска игры после того, как **DLL** были инжектированы.

![Error 16](screenshots/error_16.png)

- **Отображаемое сообщение об ошибке**: `"Failed to resume the game process thread: [Сообщение об ошибке операционной системы]"`.
- **Причина**: Вызов `ResumeThread` не удался, что означает, что **основная нить** `gta_sa.exe` не могла быть активирована для начала выполнения игры. Это редкая ошибка, но она может возникнуть, если:
  - **Дескриптор** **нити** процесса стал недействительным.
  - Операционная система по какой-то причине помешала возобновлению, возможно, из-за прерывания безопасности или нестабильного состояния процесса.
  - Процесс мог быть завершён извне между **инъекцией DLL** и попыткой возобновления **основной нити**.
- **Решение**: Если все предыдущие шаги были успешными, а `ResumeThread` завершился с ошибкой, это может быть проблема с операционной системой, с самой установкой **GTA:SA** или с другим **программным обеспечением** безопасности, которое слишком строгое. Перепроверьте состояние `gta_sa.exe` через **Диспетчер задач** непосредственно перед и после ошибки. Перезапуск компьютера может решить временные проблемы состояния системы.

> [!TIP] Инструменты диагностики
> В сложных сценариях отладки такие инструменты, как **Process Monitor (Sysinternals Suite)** или отладчик (например, **Visual Studio Debugger**, **WinDbg**, **OllyDbg**), могут быть неоценимыми. Они могут помочь отслеживать вызовы **API**, проверять ошибки доступа, отслеживать состояние **дескрипторов** и даже инспектировать память процесса, предоставляя глубокое понимание того, что происходит за кулисами.

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