# SA-MP Injector C++

<div align="center">

![C++](https://img.shields.io/badge/C%2B%2B-14%2F17%2F20-00599C?style=for-the-badge&logo=cplusplus)
![Platform](https://img.shields.io/badge/Platform-Windows-blue?style=for-the-badge&logo=windows&logoColor=white)
![Architecture](https://img.shields.io/badge/Architecture-x86%20(32--bit)-lightgrey?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)

**Библиотека C++ для запуска и автоматизации подключения клиентов SA-MP и OMP к серверам через инъекцию DLL.**

</div>

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

- [SA-MP Injector C++](#sa-mp-injector-c)
  - [Языки](#языки)
  - [Содержание](#содержание)
  - [Обзор и Назначение](#обзор-и-назначение)
  - [Принципы Проектирования](#принципы-проектирования)
    - [Полностью `Header-Only`](#полностью-header-only)
    - [Безопасное Управление Ресурсами (RAII)](#безопасное-управление-ресурсами-raii)
    - [Надежность и Проверка Ошибок](#надежность-и-проверка-ошибок)
    - [Гибкость Стандартов C++](#гибкость-стандартов-c)
  - [Требуемое Окружение](#требуемое-окружение)
    - [Для Разработки](#для-разработки)
    - [Для Выполнения](#для-выполнения)
  - [Быстрый Старт](#быстрый-старт)
    - [Интеграция в Проект](#интеграция-в-проект)
    - [Пример Упрощенного Использования](#пример-упрощенного-использования)
  - [Структура Библиотеки](#структура-библиотеки)
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
  - [Подробный Процесс Инъекции](#подробный-процесс-инъекции)
    - [1. Запрос на Инициализацию](#1-запрос-на-инициализацию)
    - [2. Подготовка Окружения](#2-подготовка-окружения)
    - [3. Проверка Целостности и Параметров](#3-проверка-целостности-и-параметров)
    - [4. Подготовка Аргументов для Игры](#4-подготовка-аргументов-для-игры)
    - [5. Инициализация Процесса Игры (Приостановлено)](#5-инициализация-процесса-игры-приостановлено)
    - [6. Инъекция Библиотеки SA-MP (`samp.dll`)](#6-инъекция-библиотеки-sa-mp-sampdll)
    - [7. Инъекция Библиотеки OMP (`omp-client.dll`) - Условно](#7-инъекция-библиотеки-omp-omp-clientdll---условно)
    - [8. Активация Игры](#8-активация-игры)
  - [Диагностика Ошибок и Сбоев](#диагностика-ошибок-и-сбоев)
    - [Сбои Валидации Входных Данных](#сбои-валидации-входных-данных)
      - [Недопустимое Имя Пользователя](#недопустимое-имя-пользователя)
      - [Недопустимый Порт Подключения](#недопустимый-порт-подключения)
      - [Отсутствие Основных Ресурсов](#отсутствие-основных-ресурсов)
    - [Сбои в Управлении Процессом](#сбои-в-управлении-процессом)
      - [Сложности при Запуске Процесса Игры](#сложности-при-запуске-процесса-игры)
    - [Проблемы при Инъекции DLL](#проблемы-при-инъекции-dll)
      - [Невозможно Найти `LoadLibraryW`](#невозможно-найти-loadlibraryw)
      - [Сбой Резервирования Удаленной Памяти](#сбой-резервирования-удаленной-памяти)
      - [Невозможность Записи Данных в Процесс](#невозможность-записи-данных-в-процесс)
      - [Сбой при Создании Потока Инъекции](#сбой-при-создании-потока-инъекции)
      - [Превышено Время Ожидания или Ошибка при Ожидании Инъекции](#превышено-время-ожидания-или-ошибка-при-ожидании-инъекции)
      - [Внутренний Сбой при Инъекции DLL](#внутренний-сбой-при-инъекции-dll)
    - [Сложности при Возобновлении Выполнения Игры](#сложности-при-возобновлении-выполнения-игры)
  - [Лицензия](#лицензия)
    - [Условия использования](#условия-использования)
      - [1. Предоставленные разрешения](#1-предоставленные-разрешения)
      - [2. Обязательные условия](#2-обязательные-условия)
      - [3. Авторские права](#3-авторские-права)
      - [4. Отказ от гарантий и ограничение ответственности](#4-отказ-от-гарантий-и-ограничение-ответственности)

## Обзор и Назначение

**SA-MP Injector C++** — это компактная и легко интегрируемая библиотека C++, предназначенная для автоматизации процесса запуска и подключения к серверам San Andreas Multiplayer (SA-MP) и Open Multiplayer (OMP). В отличие от прямого запуска `gta_sa.exe`, это решение программно загружает библиотеки `samp.dll` или `omp-client.dll` в процесс игры Grand Theft Auto: San Andreas контролируемым образом.

Ее основная цель — дать возможность разработчикам C++ создавать кастомные `лаунчеры`, инструменты для управления сообществом или утилиты, которым необходимо запускать GTA:SA с предопределенными параметрами подключения (такими как имя пользователя, IP-адрес, порт и пароль), обеспечивая плавный и автоматизированный пользовательский опыт.

## Принципы Проектирования

Архитектура **SA-MP Injector C++** основана на современных принципах проектирования, с акцентом на безопасность, эффективность и простоту использования.

### Полностью `Header-Only`

Эта библиотека распространяется исключительно через заголовочные файлы (`.hpp`). Это значительно упрощает интеграцию в проекты C++, устраняя необходимость компилировать отдельные библиотеки, настраивать `компоновщики` или управлять зависимостями бинарных файлов.
- **Мгновенная Интеграция:** Просто подключите соответствующие `заголовки`.
- **Глубокая Оптимизация:** Компилятор может выполнять агрессивное `встраивание` и оптимизации на этапе `компоновки`, что приводит к более компактному и быстрому конечному коду.

### Безопасное Управление Ресурсами (RAII)

Библиотека широко использует паттерн **RAII (Resource Acquisition Is Initialization)**. Критически важные системные ресурсы, такие как `дескрипторы` процессов и `потоков` Windows, инкапсулируются `std::unique_ptr` с кастомными `deleters`. Это гарантирует, что независимо от потока выполнения или возникновения исключений, ресурсы всегда будут освобождены корректно, предотвращая утечки и повышая стабильность приложения.

### Надежность и Проверка Ошибок

Каждый критический этап инъекции предваряется строгими проверками и сопровождается проверками ошибок Windows API. Подробные сообщения об ошибках предоставляются конечному пользователю через диалоговые окна с системными описаниями (`GetLastError()`), когда это возможно. Такой подход минимизирует вероятность неопределенного поведения и предлагает четкую диагностику в случае сбоя.

### Гибкость Стандартов C++

Библиотека была создана для совместимости с различными стандартами C++, от C++14 до C++20. Это достигается за счет условных макросов, которые позволяют использовать современные возможности (такие как `std::string_view`, `std::filesystem` и `std::optional` из C++17+), когда они доступны, при этом сохраняя `fallback` на эквивалентные конструкции в C++14. Этот подход обеспечивает широкую совместимость без ущерба для современности.

## Требуемое Окружение

### Для Разработки

- **Компилятор C++:** Совместимый с **C++14 или выше**.
   - Microsoft Visual C++ (Visual Studio 2015, 2017, 2019, 2022)
   - GCC (версия 5 или новее)
   - Clang (версия 3.6 или новее)
- **Операционная Система:** **Windows**.
- **Windows SDK:** Необходим для доступа к API операционной системы.
- **Архитектура Компиляции:** **x86 (32-bit)**. Это строгое требование, так как `gta_sa.exe` и DLL-библиотеки SA-MP/OMP работают исключительно на этой архитектуре.

### Для Выполнения

- **Операционная Система:** Любая современная версия **Windows**, совместимая со скомпилированным бинарным файлом.
- **Grand Theft Auto: San Andreas (GTA:SA):** Обязательна действующая установка игры.
- **DLL-библиотеки клиента SA-MP или OMP:** Файлы `samp.dll` или `omp-client.dll` должны находиться в корневом каталоге игры, в соответствии с желаемым типом инъекции.

## Быстрый Старт

Природа библиотеки `header-only` облегчает ее включение в любой проект C++.

### Интеграция в Проект

1. **Скачайте Заголовки:** Получите файлы `.hpp` библиотеки (клонировав репозиторий или скачав их напрямую).
2. **Организуйте Файлы:** Рекомендуется создать подпапку в вашем проекте для `заголовков` библиотеки, например, `МойПроект/libraries/samp-injector/`.
3. **Установите Архитектуру:** Настройте ваш проект для компиляции под архитектуру **x86 (32-bit)**.

```cpp
// Пример структуры каталогов
МойПроект/
├── src/
│   └── main.cpp
├── libraries/
│   └── samp-injector/
│       ├── constants.hpp
│       ├── error_utils.hpp
│       ├── injector.hpp // Основной заголовок для подключения
│       └── ... (другие заголовки)
└── built/ (ваш выходной каталог)
```

### Пример Упрощенного Использования

Для автоматизации подключения к серверу достаточно вызвать функцию `Initialize_Game` и предоставить детали.

```cpp
#include <iostream>
#include <string>
//
#include "samp-launcher/injector.hpp" // Подключите основной заголовок

int main() {
    // Параметры для инициализации игры и подключения
    std::wstring inject_type = L"samp"; // Или L"omp" для Open Multiplayer
    std::wstring game_folder = L"C:\\Games\\GTA San Andreas"; // Полный путь к папке GTA:SA
    std::wstring nickname = L"Имя";
    std::wstring ip = L"127.0.0.1";
    std::wstring port = L"7777";
    std::wstring password = L""; // Оставьте пустым, если пароля нет

    // Основной вызов для запуска игры и инъекции DLL
    Initialize_Game(inject_type, game_folder, nickname, ip, port, password);

    // В случае сбоя автоматически отображается окно сообщения об ошибке Windows.

    return 0;
}
```

## Структура Библиотеки

Библиотека тщательно разделена на несколько заголовочных файлов, каждый из которых имеет четко определенные обязанности, что облегчает организацию, поддержку и повторное использование.

### 1. `constants.hpp`

Этот файл является **центральным хранилищем** библиотеки, служа централизованным репозиторием всех фиксированных и неизменяемых значений, которые определяют поведение и совместимость **SA-MP Injector C++**. Его организация по логическим категориям способствует не только ясности и читаемости кода, но и облегчает поддержку и обеспечивает строгую согласованность во всей экосистеме библиотеки.

Каждая константа определяется с помощью `CONSTEXPR_VAR`, который раскрывается в `inline constexpr` (для C++17+) или `static constexpr` (для C++14), обеспечивая вычисление этих значений во время компиляции, что оптимизирует производительность и безопасность типов.

Организация констант по категориям облегчает понимание их назначения:

- **Константы, связанные с игрой (`Game Related Constants`)**
   - `MIN_PORT`: `int`, определяющий наименьший допустимый номер порта для подключения к серверу (значение: `1`).
   - `MAX_PORT`: `int`, устанавливающий наибольший допустимый номер порта для подключения к серверу (значение: `65535`).
   - `MAX_NICKNAME_LENGTH`: `int`, указывающий максимальную допустимую длину никнейма игрока (значение: `23` символа), ограничение, наложенное спецификациями клиента SA-MP/OMP.

- **Имена основных файлов (`File Names`)**
   - `SAMP_DLL_NAME`: `const wchar_t*`, содержащий имя файла основной библиотеки клиента SA-MP (значение: `L"samp.dll"`). Необходимо для инъекции классического клиента.
   - `OMP_DLL_NAME`: `const wchar_t*`, содержащий имя файла библиотеки клиента Open Multiplayer (значение: `L"omp-client.dll"`). Используется специально, когда инъекция типа OMP.
   - `GAME_EXE_NAME`: `const wchar_t*`, хранящий имя исполняемого файла базовой игры Grand Theft Auto: San Andreas (значение: `L"gta_sa.exe"`). Основная цель инъекции.

- **API и функции системы (`System Libraries and Functions`)**
   - `KERNEL32_DLL`: `const wchar_t*`, определяющий имя системной библиотеки Windows (`L"kernel32.dll"`). Эта DLL жизненно важна, так как она содержит функции для манипулирования процессами и памятью, которые использует инжектор. Использование `wchar_t` обеспечивает совместимость с функциями API, работающими с широкими символами, такими как `GetModuleHandleW`.
   - `LOAD_LIBRARY_FUNC`: `const char*` с именем функции для динамической загрузки DLL (значение: `"LoadLibraryW"`). Хотя библиотека в основном работает с широкими символами, функция `GetProcAddress` из Windows API требует имя функции в формате ANSI (`char*`).

- **Аргументы командной строки (`Command Line Arguments`)**
   - Эти константы определяют префиксы для аргументов, которые передаются `gta_sa.exe` для настройки подключения клиента. Они предоставляются в `Wide Character` (`const wchar_t*`) для совместимости с `CreateProcessW`.
      - `CMD_ARG_CONFIG`: Аргумент для общих настроек (значение: `L"-c"`).
      - `CMD_ARG_NICKNAME`: Аргумент для никнейма игрока (значение: `L"-n"`).
      - `CMD_ARG_HOST`: Аргумент для IP-адреса сервера (значение: `L"-h"`).
      - `CMD_ARG_PORT`: Аргумент для порта сервера (значение: `L"-p"`).
      - `CMD_ARG_PASSWORD`: Аргумент для пароля сервера (значение: `L"-z"`). Используется только если предоставлен пароль.

- **Идентификаторы типа инъекции (`Injection types as strings`)**
   - `INJECT_TYPE_SAMP`: `const wchar_t*` для строкового представления типа инъекции SA-MP (значение: `L"samp"`).
   - `INJECT_TYPE_OMP`: `const wchar_t*` для строкового представления типа инъекции OMP (значение: `L"omp"`).

- **Заголовки для сообщений об ошибках (`Error message titles`)**
   - `ERROR_TITLE_SAMP`: `const wchar_t*`, определяющий заголовок по умолчанию для диалоговых окон ошибок, связанных со сбоями SA-MP (значение: `L"SA-MP Injector Error - SPC"`).
   - `ERROR_TITLE_OMP`: `const wchar_t*`, определяющий заголовок по умолчанию для диалоговых окон ошибок, связанных со сбоями OMP (значение: `L"OMP Injector Error - SPC"`).

- **Флаги создания процесса (`Process creation`)**
   - `PROCESS_CREATION_FLAGS`: `DWORD`, инкапсулирующий флаги, передаваемые в `CreateProcessW`. Важно, что он включает `CREATE_SUSPENDED` (`0x00000004`), который запускает процесс игры в приостановленном состоянии, и `DETACHED_PROCESS` (`0x00000008`), который отсоединяет новый процесс от консоли родительского процесса.

- **Тайм-ауты (`Timeouts`)**
   - `DLL_INJECTION_TIMEOUT_MS`: `DWORD`, указывающий максимальное время (в миллисекундах), которое библиотека будет ждать завершения удаленного `потока`, ответственного за инъекцию DLL (значение: `10000ms`, или 10 секунд).

- **Флаги выделения памяти (`Memory allocation`)**
   - Эти константы используются для вызовов API манипулирования памятью, таких как `VirtualAllocEx` и `VirtualProtect`.
      - `MEM_COMMIT`: `DWORD`, который резервирует страницы в виртуальной памяти и "коммитит" их (выделяет физическую память) (значение: `0x1000`).
      - `MEM_RESERVE`: `DWORD`, который только резервирует диапазон виртуального адресного пространства для последующего использования (значение: `0x2000`).
      - `MEM_RELEASE`: `DWORD`, который декоммитит и освобождает регион страниц (значение: `0x8000`).
      - `MEMORY_ALLOCATION_TYPE`: Комбинация `MEM_COMMIT` и `MEM_RESERVE`, используемая для выделения начальной памяти для пути DLL в удаленном процессе.
      - `MEMORY_PROTECTION`: `DWORD`, который определяет права доступа к памяти (значение: `PAGE_READWRITE` или `0x04` в Windows API), разрешая чтение и запись в выделенную память.

### 2. `types.hpp`

Этот краткий файл вводит `enum class` для типизации различных режимов инъекции. Использование перечисляемого типа вместо строковых литералов повышает безопасность кода, предотвращает опечатки и улучшает читаемость.

- **`Inject_Type`:** `enum class` с двумя членами: `SAMP` и `OMP`, представляющими типы клиентов для инъекции.

```cpp
// Пример types.hpp
namespace Types {
    enum class Inject_Type {
        SAMP, // Указывает на инъекцию для клиента SA-MP
        OMP // Указывает на инъекцию для клиента Open Multiplayer
    };
}
```

### 3. `version.hpp`

Действуя как адаптер совместимости, этот заголовок динамически определяет используемый компилятором стандарт C++. Он определяет условные макросы (`SAMP_INJECTOR_CXX_14`, `SAMP_INJECTOR_CXX_MODERN`), которые направляют библиотеку на использование более продвинутых возможностей C++ (таких как `std::string_view` или `std::filesystem`), когда они доступны, при этом обеспечивая полную функциональность в средах C++14.

- **`SAMP_INJECTOR_CXX_14`:** Определяется, если стандарт C++ - C++14.
- **`SAMP_INJECTOR_CXX_MODERN`:** Определяется для C++17 или выше, включая более новые языковые возможности.
- **`SAMP_INJECTOR_NODISCARD`:** Адаптирует атрибут `[[nodiscard]]` для версий C++, которые его поддерживают, поощряя проверку возвращаемых значений.

```cpp
// Пример соответствующего фрагмента из version.hpp
#if (defined(_MSC_VER) && _MSVC_LANG >= 201703L) || __cplusplus >= 201703L
    #define SAMP_INJECTOR_CXX_MODERN // Включает современные возможности C++17+
#endif

#if defined(SAMP_INJECTOR_CXX_MODERN)
    #define SAMP_INJECTOR_NODISCARD [[nodiscard]] // Использует атрибут nodiscard из C++17
#elif defined(SAMP_INJECTOR_CXX_14)
    #define SAMP_INJECTOR_NODISCARD // Для C++14 атрибут отключается
#endif
```

### 4. `error_utils.hpp`

Эта утилита предназначена для управления и представления обратной связи об ошибках. Она абстрагирует механизмы Windows для получения системных сообщений об ошибках и предлагает унифицированный интерфейс для уведомления пользователя о проблемах.

- **`Get_System_Error_Message`:** Переводит код ошибки Windows (`GetLastError()`) в читаемую `std::wstring`, что крайне важно для точной диагностики.
- **`Show_Error`:** Отображает диалоговое окно (`MessageBoxW`), содержащее предоставленное сообщение об ошибке, с заголовком, специфичным для SA-MP или OMP, обеспечивая ясную коммуникацию с пользователем.

```cpp
// Пример соответствующего фрагмента из error_utils.hpp
namespace Error_Utils {
    SAMP_INJECTOR_NODISCARD
    inline std::wstring Get_System_Error_Message(DWORD error_code) {
        if (error_code == 0)
            return L"No error occurred.";
        
        // ... Логика для форматирования системного сообщения ...
    }

    inline void Show_Error(std::wstring_view message, Types::Inject_Type inject_type) {
        const std::wstring title = (inject_type == Types::Inject_Type::SAMP) ? Constants::ERROR_TITLE_SAMP : Constants::ERROR_TITLE_OMP;
        MessageBoxW(nullptr, message.data(), title.c_str(), MB_OK | MB_ICONERROR);
    }
}
```

### 5. `validation.hpp`

Действуя как первая линия обороны надежности библиотеки, этот заголовок предоставляет строгие процедуры для проверки валидности входных данных и наличия необходимых файлов. Эти проверки выполняются до любого низкоуровневого взаимодействия с системой, снижая риски времени выполнения и предоставляя проактивную обратную связь.

- **`Validate_Port`:** Проверяет, представляет ли строка порта целое число и находится ли оно в пределах настроенного диапазона (`MIN_PORT` до `MAX_PORT`).
- **`Validate_Nickname`:** Проверяет, что никнейм не пуст и его длина не превышает `MAX_NICKNAME_LENGTH`.
- **`Validate_Files`:** Подтверждает физическое существование `gta_sa.exe`, `samp.dll` и, условно для инъекции OMP, `omp-client.dll`. Реализация адаптируется к `std::filesystem` (C++17+) или `GetFileAttributesW` (C++14).

```cpp
// Пример соответствующего фрагмента из validation.hpp
namespace Validation {
    inline bool Validate_Nickname(std::wstring_view nickname_str, std::wstring& error_message) {
        if (nickname_str.empty())
            return (error_message = L"Никнейм не может быть пустым. Пожалуйста, укажите допустимый никнейм.", false);
        
        if (nickname_str.length() > Constants::MAX_NICKNAME_LENGTH)
            return (error_message = L"Длина никнейма превышает максимально допустимую в " + std::to_wstring(Constants::MAX_NICKNAME_LENGTH) + L" символов. Пожалуйста, используйте более короткий никнейм.", false);
        
        return true;
    }

    inline bool Validate_Files(const std::filesystem::path& game_path, const std::filesystem::path& samp_DLL_path, const std::filesystem::path& omp_DLL_path, Types::Inject_Type inject_type) {
        if (!std::filesystem::exists(game_path))
            return (Error_Utils::Show_Error(L"Исполняемый файл игры не найден. Убедитесь, что 'gta_sa.exe' существует по указанному пути: " + game_path.wstring(), inject_type), false);
        
        // ... Другие проверки файлов ...
        return true;
    }
}
```

### 6. `resource_handle.hpp`

Реализует элегантную и безопасную стратегию управления ресурсами операционной системы, такими как `HANDLE`'ы Windows. Используя принцип RAII, он гарантирует, что все выделенные ресурсы будут должным образом освобождены, предотвращая утечки и укрепляя стабильность приложения.

- **`Unique_Resource`:** `alias template`, который адаптирует `std::unique_ptr` для работы с кастомными `deleters`, позволяя управлять любым типом ресурсов, требующим специальной функции освобождения.
- **`Make_Unique_Handle`:** Удобная `фабричная` функция, которая создает и возвращает `Unique_Resource`, предварительно настроенный для `HANDLE`'ов Windows. Связанный `deleter` автоматически вызывает `CloseHandle`, когда `Unique_Resource` выходит из области видимости, гарантируя немедленное освобождение ресурса.

```cpp
// Пример соответствующего фрагмента из resource_handle.hpp
namespace Resource_Handle {
    // Кастомный std::unique_ptr для управления системными ресурсами.
    template<typename T, typename Deleter>
    using Unique_Resource = std::unique_ptr<std::remove_pointer_t<T>, Deleter>;

    // Создает Unique_Resource для HANDLE, с deleter'ом, который вызывает CloseHandle.
    template<typename T>
    inline auto Make_Unique_Handle(T handle) {
        return Unique_Resource<T, std::function<void(T)>>(handle, [](T h) {
            if (h && h != INVALID_HANDLE_VALUE) // Гарантирует, что хэндл действителен перед закрытием
                CloseHandle(h);
        });
    }
}
```

### 7. `privileges.hpp`

Этот компонент отвечает за настройку среды безопасности процесса приложения. Он содержит функциональность для повышения привилегий, в частности, включение привилегии отладки (`SE_DEBUG_NAME`), которая является фундаментальным требованием для того, чтобы библиотека могла выполнять операции инъекции DLL во внешние процессы Windows.

- **`Enable_Debug_Privilege`:** Эта функция пытается получить и активировать привилегию `SE_DEBUG_NAME` для текущего процесса. Это критически важный начальный шаг для предоставления приложению необходимых разрешений для манипулирования другими процессами, такими как выделение памяти и создание удаленных `потоков`. Возвращает `true` в случае успеха.

```cpp
// Пример соответствующего фрагмента из privileges.hpp
namespace Privileges {
    inline bool Enable_Debug_Privilege() {
        HANDLE token_handle;

        // Попытка открыть токен текущего процесса для настройки привилегий
        if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &token_handle))
            return false;

        auto handle_guard = Resource_Handle::Make_Unique_Handle(token_handle); // Безопасное управление хэндлом

        TOKEN_PRIVILEGES tp;
        LUID luid;

        // Поиск значения LUID для привилегии SE_DEBUG_NAME
        if (!LookupPrivilegeValue(nullptr, SE_DEBUG_NAME, &luid))
            return false;
        
        tp.PrivilegeCount = 1;
        tp.Privileges[0].Luid = luid;
        tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED; // Включает привилегию

        // Настройка привилегий процесса
        if (!AdjustTokenPrivileges(token_handle, FALSE, &tp, sizeof(TOKEN_PRIVILEGES), nullptr, nullptr))
            return false;

        return GetLastError() == ERROR_SUCCESS; // Возвращает true, если операция прошла успешно (нет ожидающих ошибок)
    }
}
```

### 8. `process.hpp`

Это один из самых критически важных компонентов библиотеки, содержащий низкоуровневую реализацию для взаимодействия с процессами Windows. Он инкапсулирует сложные операции создания игрового процесса, выделения памяти, записи данных и технику инъекции DLL через создание удаленных `потоков`.

- **`Process_Info` struct:** Внутренняя структура, которая хранит `Unique_Resource`'ы для `HANDLE` процесса (`process_handle`) и `HANDLE` основного `потока` (`thread_handle`) игры. Включает метод `Resume()` для возобновления основного `потока` игры после завершения инъекции.
- **`Injection_Status` enum class:** Определяет подробный список возможных результатов операции инъекции DLL, позволяя точно диагностировать сбои.
- **`Create_Game_Process`:**
   - Использует функцию `CreateProcessW` из Windows API для запуска исполняемого файла `gta_sa.exe`.
   - Важно, чтобы процесс создавался с флагом `CREATE_SUSPENDED` (включенным в `Constants::PROCESS_CREATION_FLAGS`). Это гарантирует, что игра будет приостановлена сразу после ее создания, до выполнения какого-либо кода, что позволяет провести инъекцию DLL в безопасном состоянии.
   - Возвращает `std::optional<Process_Info>` (для C++17+) или `std::unique_ptr<Process_Info>` (для C++14), содержащий инкапсулированные `хэндлы` процесса и `потока`.
- **`Inject_DLL`:**
   - Реализует стандартную технику инъекции DLL через `CreateRemoteThread`:
      1. **Получение Адреса:** Используя константы из `constants.hpp`, находит адрес функции `LoadLibraryW` (из `kernel32.dll`), которую Windows использует для динамической загрузки библиотек.
      2. **Выделение Памяти:** `VirtualAllocEx` используется для резервирования блока виртуальной памяти внутри процесса игры (`gta_sa.exe`). Этот блок имеет размер, достаточный для хранения полного пути к инъектируемой DLL.
      3. **Запись Пути:** Путь к DLL (например, `L"C:\\путь\\к\\samp.dll"`) затем копируется в удаленно выделенную память в игровом процессе через `WriteProcessMemory`.
      4. **Создание Удаленного Потока:** `CreateRemoteThread` запускает новый `поток` в контексте игрового процесса. Точкой входа этого `потока` является адрес `LoadLibraryW`, а передаваемым аргументом — адрес строки пути к DLL, который мы только что записали.
      5. **Мониторинг:** Выполнение удаленного `потока` отслеживается с помощью `WaitForSingleObject` до его завершения или до истечения `DLL_INJECTION_TIMEOUT_MS`.
      6. **Проверка Успеха:** `GetExitCodeThread` используется для проверки возвращаемого значения удаленного `потока`. Если `LoadLibraryW` выполнилась успешно, она вернет базовый адрес загруженной DLL (ненулевое значение).
      7. **Очистка:** Выделенная в удаленном процессе память освобождается с помощью `VirtualFreeEx`.
   - Возвращает `Injection_Status`, указывающий на успех или конкретный тип сбоя инъекции.

```cpp
// Пример соответствующего фрагмента из process.hpp
class Process {
public:
    struct Process_Info {
        Resource_Handle::Unique_Resource<HANDLE, std::function<void(HANDLE)>> process_handle; // Хэндл процесса с управлением RAII
        Resource_Handle::Unique_Resource<HANDLE, std::function<void(HANDLE)>> thread_handle; // Хэндл потока с управлением RAII

        bool Resume() { // Возобновляет выполнение основного потока игры
            return thread_handle && ResumeThread(thread_handle.get()) != static_cast<DWORD>(-1);
        }
    };
    
    enum class Injection_Status { // Подробные коды статуса для инъекции DLL
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

    // Создает процесс игры в приостановленном состоянии
    std::optional<Process_Info> Create_Game_Process(const std::wstring& game_path, std::wstring& command_args, const std::wstring& working_dir) {
        // ... Логика CreateProcessW с CREATE_SUSPENDED ...
    }
    
    SAMP_INJECTOR_NODISCARD // Гарантирует, что возвращаемое значение будет использовано
    Injection_Status Inject_DLL(HANDLE process, const std::wstring& DLL_path) {
        static const LPVOID load_library_addr = reinterpret_cast<LPVOID>(GetProcAddress(GetModuleHandleW(Constants::KERNEL32_DLL), Constants::LOAD_LIBRARY_FUNC));

        if (!load_library_addr)
            return Injection_Status::LOADLIBRARY_ADDRESS_FAILED;

        LPVOID remote_memory = VirtualAllocEx(process, nullptr, (DLL_path.length() + 1) * sizeof(wchar_t), Constants::MEMORY_ALLOCATION_TYPE, Constants::MEMORY_PROTECTION);

        if (!remote_memory)
            return Injection_Status::ALLOCATION_FAILED;

        auto memory_guard = Resource_Handle::Unique_Resource<LPVOID, std::function<void(LPVOID)>>(remote_memory, [process](LPVOID ptr) {
            if (ptr)
                VirtualFreeEx(process, ptr, 0, MEM_RELEASE); // Освобождает память в удаленном процессе
        });

        if (!WriteProcessMemory(process, remote_memory, DLL_path.c_str(), (DLL_path.length() + 1) * sizeof(wchar_t), nullptr))
            return Injection_Status::WRITE_FAILED;

        HANDLE remote_thread = CreateRemoteThread(process, nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(load_library_addr), remote_memory, 0, nullptr);

        if (!remote_thread)
            return Injection_Status::THREAD_CREATION_FAILED;

        auto thread_guard = Resource_Handle::Make_Unique_Handle(remote_thread); // Безопасное управление хэндлом удаленного потока

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

Этот заголовок определяет класс `Injector_Core`, который служит командным центром библиотеки. Он организует логическую последовательность операций инъекции, связывая модули валидации ввода, управления привилегиями и манипуляции процессами. Именно здесь определяется полный рабочий процесс инъекции.

- **`Injector_Core`:** Конструктор этого класса является точкой, где вызывается `Privileges::Enable_Debug_Privilege()`. Это гарантирует, что процесс приложения обладает необходимыми привилегиями для выполнения операций инъекции DLL до того, как будет выполнена любая другая критическая логика.
- **`Initialize_Game`:**
   1. **Всесторонняя Валидация:** Начинает с вызова функций валидации (`Validation::Validate_Port`, `Validation::Validate_Nickname`, `Validation::Validate_Files`), чтобы убедиться, что все параметры и основные ресурсы в порядке. Если какая-либо проверка не проходит, немедленно сообщается об ошибке.
   2. **Подготовка Аргументов:** Собирает полную командную строку (`std::wstring`), которая будет передана `gta_sa.exe`, включая предоставленные никнейм, IP, порт и пароль.
   3. **Создание Приостановленного Процесса:** Вызывает `Process::Create_Game_Process` для запуска `gta_sa.exe` в приостановленном состоянии, получая `хэндлы` процесса и основного `потока`.
   4. **Инъекция `samp.dll`:** Вызывает `Inject_DLL_With_Status_Check` для инъекции `samp.dll` в игровой процесс. Эта оберточная функция также отвечает за интерпретацию возвращаемого `Injection_Status` и отображение информативных сообщений об ошибках.
   5. **Условная Инъекция `omp-client.dll`:** Если `inject_type` равен `Types::Inject_Type::OMP`, то `omp-client.dll` инъектируется так же, как и `samp.dll`.
   6. **Возобновление Игры:** После всех успешных инъекций вызывается `process_info.Resume()`, чтобы позволить основному `потоку` игры продолжить свое выполнение.
   7. **Обработка Ошибок в Цикле:** Любой сбой на любом из этих критических этапов приведет к вызову `Error_Utils::Show_Error`, предоставляя четкую обратную связь пользователю и гарантируя, что процесс будет завершен корректно (`хэндлы` автоматически освобождаются `Unique_Resource`'ами).
- **`Build_Command_Args`:** Вспомогательная функция, которая организует и конкатенирует аргументы командной строки, добавляя кавычки там, где это необходимо для параметров, содержащих пробелы.
- **`Inject_DLL_With_Status_Check`:** Приватная функция, которая действует как обертка для `Process::Inject_DLL`. Она сопоставляет различные `Injection_Status` с понятными сообщениями об ошибках, облегчая обработку ошибок и коммуникацию с пользователем.

```cpp
// Пример соответствующего фрагмента из injector_core.hpp
namespace Injector {
    class Injector_Core {
    public:
        Injector_Core() { // Конструктор включает привилегию отладки
            Privileges::Enable_Debug_Privilege();
        }

        bool Initialize_Game(Types::Inject_Type inject_type, std::wstring_view folder, std::wstring_view nickname, std::wstring_view ip, std::wstring_view port, std::wstring_view password) {
            std::wstring error_message;

            // Последовательность проверок входных данных
            if (!Validation::Validate_Port(port, error_message))
                return (Error_Utils::Show_Error(error_message, inject_type), false);
            // ... другие проверки ...

            // Собирает аргументы командной строки
            std::wstring args = Build_Command_Args({
                Command_Arg{Constants::CMD_ARG_NICKNAME, std::wstring(nickname)},
                // ... другие аргументы ...
            });

            Process process_core;
            // Создает процесс игры в приостановленном состоянии
            auto process_info_opt = process_core.Create_Game_Process(game_path, args, std::wstring(folder));

            if (!process_info_opt)
                return false;

            auto& process_info = *process_info_opt;

            // Инъектирует samp.dll и, условно, omp-client.dll
            if (!Inject_DLL_With_Status_Check(process_core, process_info.process_handle.get(), Constants::SAMP_DLL_NAME, samp_DLL_path.wstring(), inject_type))
                return false;
            
            if (inject_type == Types::Inject_Type::OMP) {
                if (!Inject_DLL_With_Status_Check(process_core, process_info.process_handle.get(), Constants::OMP_DLL_NAME, omp_DLL_path.wstring(), inject_type))
                    return false;
            }
            
            // Возобновляет основной поток игры
            if (!process_info.Resume())
                return (Error_Utils::Show_Error(L"Не удалось возобновить поток игрового процесса: " + Error_Utils::Get_System_Error_Message(GetLastError()), inject_type), false);

            return true;
        }
    };
}
```

### 10. `injector.hpp`

Этот заголовок действует как основной фасад (`Facade`) библиотеки, предлагая упрощенную точку входа для любого приложения, желающего использовать функциональность инъекции. Он абстрагирует внутреннюю сложность `Injector_Core` в одну удобную функцию.

- **`Initialize_Game`:**
   - Эта статическая функция является публичным интерфейсом библиотеки.
   - Сначала она проверяет `inject_type_str` (является ли она `L"samp"` или `L"omp"`) и преобразует ее в `enum class Types::Inject_Type`. В случае недопустимой строки отображается ошибка и выполнение завершается.
   - Затем она создает экземпляр `Injector::Injector_Core`.
   - Наконец, она делегирует выполнение основной логики `Injector_Core::Initialize_Game`, где и организуется весь процесс валидации, создания процесса и инъекции DLL.

```cpp
// Пример соответствующего фрагмента из injector.hpp
// Публичный интерфейс для запуска игры
#if defined(SAMP_INJECTOR_CXX_MODERN)
inline bool Initialize_Game(std::wstring_view inject_type, std::wstring_view folder, std::wstring_view nickname, std::wstring_view ip, std::wstring_view port, std::wstring_view password) {
#elif defined(SAMP_INJECTOR_CXX_14)
inline bool Initialize_Game(const std::wstring& inject_type, const std::wstring& folder, const std::wstring& nickname, const std::wstring& ip, const std::wstring& port, const std::wstring& password) {
#endif
    Types::Inject_Type type;

    // Преобразует строку типа инъекции в соответствующий enum
    if (inject_type == Constants::INJECT_TYPE_SAMP)
        type = Types::Inject_Type::SAMP;
    else if (inject_type == Constants::INJECT_TYPE_OMP)
        type = Types::Inject_Type::OMP;
    else
        // Отображает ошибку, если тип инъекции недействителен
        return (Error_Utils::Show_Error(L"Недопустимый режим инъекции. Используйте 'samp' или 'omp'.", Types::Inject_Type::SAMP), false);

    Injector::Injector_Core injector; // Создает экземпляр ядра инжектора

    // Делегирует основную логику Injector_Core
    return injector.Initialize_Game(type, folder, nickname, ip, port, password);
}
```

## Подробный Процесс Инъекции

Основная функциональность этой библиотеки заключается в организации точной последовательности операций для инъекции DLL-библиотек клиента SA-MP или OMP в процесс GTA:SA. Этот цикл тщательно спланирован для обеспечения стабильности и совместимости.

### 1. Запрос на Инициализацию

Процесс начинается с вызова глобальной функции `Initialize_Game` (`injector.hpp`), которая действует как основная точка контакта для приложения, использующего библиотеку. Эта функция получает все ключевые параметры, такие как желаемый тип инъекции (SA-MP или OMP), каталог игры и данные для подключения к серверу (никнейм, IP, порт, пароль).

### 2. Подготовка Окружения

При вызове функция `Initialize_Game` создает экземпляр `Injector::Injector_Core`. В конструкторе этого класса (`injector_core.hpp`) выполняется первый и важнейший этап настройки окружения: повышение привилегий.

> [!NOTE]
> `Privileges::Enable_Debug_Privilege()`: Этот вызов (`privileges.hpp`) предоставляет процессу приложения привилегию `SE_DEBUG_NAME`. Эта привилегия жизненно важна, поскольку она позволяет приложению выполнять низкоуровневые операции над другими процессами Windows, такие как чтение и запись в их память и создание удаленных `потоков` — фундаментальные действия для техники инъекции DLL.

### 3. Проверка Целостности и Параметров

С настроенными привилегиями метод `Injector_Core::Initialize_Game` приступает к серии строгих проверок. Это превентивный этап, который минимизирует вероятность сбоев на последующих этапах и предоставляет немедленную обратную связь пользователю.

- **Валидация Порта:** `Validation::Validate_Port` проверяет, правильно ли отформатирован номер порта подключения и находится ли он в диапазоне от `1` до `65535` (`constants.hpp`).
- **Валидация никнейма:** `Validation::Validate_Nickname` гарантирует, что никнейм игрока не пуст и не превышает лимит в `23` символа.
- **Проверка Основных Файлов:** `Validation::Validate_Files` проверяет каталог игры на наличие `gta_sa.exe`, `samp.dll` и, если инъекция типа OMP, также `omp-client.dll`.

> [!WARNING]
> Любой сбой на этом этапе приводит к немедленному отображению `MessageBox` с подробным сообщением об ошибке (`error_utils.hpp`) и прекращению процесса инъекции. Это предотвращает бесполезные попытки продолжить с неверной конфигурацией.

### 4. Подготовка Аргументов для Игры

После успешной валидации функция `Injector_Core::Build_Command_Args` отвечает за построение отформатированной командной строки, которая будет передана `gta_sa.exe`. Эта командная строка включает все необходимые параметры для автоматического подключения клиента SA-MP/OMP к серверу, такие как `-n "никнейм" -h "IP" -p "Порт" -z "Пароль"`.

### 5. Инициализация Процесса Игры (Приостановлено)

Компонент `Process` (`process.hpp`) затем отвечает за запуск исполняемого файла GTA:SA.

> [!IMPORTANT]
> Функция `Process::Create_Game_Process` использует флаг `CREATE_SUSPENDED` (`constants.hpp`) при вызове API `CreateProcessW` Windows. Это критически важное проектное решение: игра загружается в память и создается ее основной `поток`, но его выполнение **приостанавливается**. Это создает контролируемую и стабильную среду, идеальную для инъекции DLL, прежде чем игра сможет инициализировать свои собственные защитные механизмы или внутреннюю логику. `Хэндлы` процесса и `потока` получаются и безопасно управляются через `Resource_Handle::Unique_Resource`.

### 6. Инъекция Библиотеки SA-MP (`samp.dll`)

Когда процесс игры находится в приостановленном состоянии, инъекция `samp.dll` может быть выполнена безопасно. Метод `Injector_Core::Inject_DLL_With_Status_Check` делегирует эту задачу `Process::Inject_DLL`, который выполняет следующие шаги техники `remote thread injection`:

1. **Поиск Функции `LoadLibraryW`:** Определяется адрес функции `LoadLibraryW`. Эта операция использует константы `Constants::KERNEL32_DLL` и `Constants::LOAD_LIBRARY_FUNC` для получения `хэндла` к `kernel32.dll` и затем нахождения адреса функции динамической загрузки библиотек.
2. **Выделение Удаленной Памяти:** `VirtualAllocEx` используется для резервирования блока памяти в виртуальном адресном пространстве процесса `gta_sa.exe` (который приостановлен). Размер этого блока достаточен для хранения полного пути к `samp.dll`.
3. **Запись Пути к DLL:** Полный путь к файлу `samp.dll` записывается в эту только что выделенную удаленную память с помощью `WriteProcessMemory`.
4. **Создание Удаленного Потока:** `CreateRemoteThread` вызывается для создания нового `потока` внутри процесса `gta_sa.exe`. Точкой входа этого нового `потока` является адрес `LoadLibraryW`, а аргументом, который он получает, является указатель на путь к DLL, который мы только что записали.
5. **Мониторинг Инъекции:** Выполнение удаленного `потока` отслеживается с помощью `WaitForSingleObject` в течение периода, определенного `Constants::DLL_INJECTION_TIMEOUT_MS`.
6. **Проверка Результата:** Код завершения удаленного `потока` получается через `GetExitCodeThread`. Ненулевое возвращаемое значение указывает, что `LoadLibraryW` успешно загрузила `samp.dll`.

> [!WARNING]
> В случае любого сбоя во время инъекции `samp.dll`, отображается специфическое сообщение об ошибке (`error_utils.hpp`), процесс инъекции прерывается, и ресурсы освобождаются.

### 7. Инъекция Библиотеки OMP (`omp-client.dll`) - Условно

Если указан тип инъекции `OMP`, шаги, описанные в пункте 6, повторяются для `omp-client.dll`.

> [!TIP]
> Инъекция `omp-client.dll` всегда происходит после успешной инъекции `samp.dll`. Это связано с тем, что клиент Open Multiplayer основан на инфраструктуре, предоставляемой `samp.dll`.

### 8. Активация Игры

Наконец, если все инъекции были успешно завершены, вызывается метод `process_info.Resume()`. Этот вызов выполняет `ResumeThread` на основном `потоке` `gta_sa.exe`. В этот момент игра активируется и начинает свое нормальное выполнение, но уже с загруженными в ее память DLL-библиотеками SA-MP/OMP и с настроенными параметрами подключения, что позволяет автоматически подключиться к серверу.

> [!WARNING]
> Если возобновление `потока` игры не удается, пользователю представляется последнее сообщение об ошибке.

## Диагностика Ошибок и Сбоев

Библиотека тщательно спроектирована для четкого сообщения о любых проблемах, которые могут возникнуть в процессе инициализации и инъекции. В любой точке сбоя пользователю представляется `MessageBox` с подробным описанием, часто дополненным системными сообщениями об ошибках операционной системы.

### Сбои Валидации Входных Данных

Эти ошибки обнаруживаются на начальном этапе (`validation.hpp`), до любого низкоуровневого взаимодействия с системой, и указывают на проблемы с предоставленными пользователем данными или с настройкой окружения.

#### Недопустимое Имя Пользователя

- **Сообщение об Ошибке (Пример 1):** `"Никнейм не может быть пустым. Пожалуйста, укажите допустимый никнейм."`
- **Сообщение об Ошибке (Пример 2):** `"Длина никнейма превышает максимально допустимые 23 символа. Пожалуйста, используйте более короткий никнейм."`
- **Причина:** Предоставленное имя пользователя (`никнейм`) пусто или превышает максимальный лимит в 23 символа, разрешенный клиентами SA-MP/OMP.
- **Решение:** Пользователь должен ввести допустимое имя пользователя, которое соответствует критериям длины.

#### Недопустимый Порт Подключения

- **Сообщение об Ошибке (Пример 1):** `"Неверный формат порта. Порт должен быть числовым значением. Пожалуйста, укажите допустимое целое число для порта."`
- **Сообщение об Ошибке (Пример 2):** `"Указанный номер порта (70000) находится вне допустимого диапазона от 1 до 65535. Пожалуйста, укажите допустимый порт."`
- **Причина:** Предоставленное значение для порта не является целым числом или находится вне допустимого диапазона (от 1 до 65535).
- **Решение:** Пользователь должен предоставить допустимый номер порта в указанном диапазоне.

#### Отсутствие Основных Ресурсов

- **Сообщение об Ошибке (Пример 1):** `"Исполняемый файл игры не найден. Убедитесь, что 'gta_sa.exe' существует по указанному пути: C:\Games\GTA San Andreas\gta_sa.exe"`
- **Сообщение об Ошибке (Пример 2):** `"Библиотека SA-MP не найдена. Убедитесь, что 'samp.dll' существует по указанному пути: C:\Games\GTA San Andreas\samp.dll"`
- **Сообщение об Ошибке (Пример 3, для OMP):** `"Библиотека OMP не найдена. Убедитесь, что 'omp-client.dll' существует по указанному пути для инъекции OMP: C:\Games\GTA San Andreas\omp-client.dll"`
- **Причина:** Один или несколько ключевых файлов (`gta_sa.exe`, `samp.dll`, `omp-client.dll`) не были найдены в указанном каталоге игры.
- **Решение:** Проверьте путь к папке с игрой и убедитесь, что все необходимые файлы присутствуют и доступны.

### Сбои в Управлении Процессом

Эти ошибки возникают, когда библиотека пытается запустить исполняемый файл игры (`gta_sa.exe`).

#### Сложности при Запуске Процесса Игры

- **Сообщение об Ошибке (Пример):** `"Не удалось создать процесс игры. Убедитесь, что 'gta_sa.exe' не запущен и у вас достаточно прав для выполнения файла. Системная ошибка: Отказано в доступе."`
- **Причина:**
   - **Исполняемый Файл Используется:** `gta_sa.exe` может уже быть запущен, или есть какая-то блокировка операционной системы, которая препятствует созданию нового экземпляра.
   - **Недостаточно Прав:** У приложения может не быть соответствующих разрешений для запуска `gta_sa.exe` или доступа к файлу.
   - **Поврежденный Исполняемый Файл:** Хотя базовая проверка проверяет существование файла, он может быть поврежден или недоступен.
- **Решение:** Убедитесь, что ни один экземпляр `gta_sa.exe` не активен. Попробуйте запустить ваше приложение от имени администратора. Проверьте целостность файла `gta_sa.exe`.

### Проблемы при Инъекции DLL

Это самые критические и подробные ошибки, возникающие при попытке инъекции `samp.dll` или `omp-client.dll` в приостановленный процесс игры. Сообщения об ошибках обычно начинаются с `"Не удалось инъектировать <DLL_NAME>:\n"` и сопровождаются конкретным описанием и кодом системной ошибки.

#### Невозможно Найти `LoadLibraryW`

- **Часть Сообщения об Ошибке:** `"Не удалось найти адрес LoadLibraryW в kernel32.dll."`
- **Причина:** Функция `LoadLibraryW`, фундаментальный API Windows для динамической загрузки DLL, не может быть найдена в `kernel32.dll`. Это крайне редкая низкоуровневая проблема, которая может указывать на возможное повреждение операционной системы или очень необычную среду выполнения.
- **Решение:** Перезагрузка системы может решить проблему. Если она сохраняется, это может указывать на более серьезную проблему с установкой Windows.

#### Сбой Резервирования Удаленной Памяти

- **Часть Сообщения об Ошибке:** `"Не удалось выделить память в целевом процессе (VirtualAllocEx). Системная ошибка: Недостаточно памяти для обработки этой команды."`
- **Причина:** Библиотека не смогла выделить блок памяти в виртуальном адресном пространстве процесса `gta_sa.exe`.
   - **Разрешения:** Ваше приложение может не иметь достаточных разрешений для изменения адресного пространства другого процесса.
   - **Защита Процесса:** Механизмы безопасности операционной системы или анти-читерское программное обеспечение могут блокировать выделение памяти во внешних процессах.
- **Решение:** Запустите ваше приложение от имени администратора. Проверьте, не мешают ли программы безопасности (антивирусы, анти-читы) и, если возможно, временно отключите их для тестирования.

#### Невозможность Записи Данных в Процесс

- **Часть Сообщения об Ошибке:** `"Не удалось записать путь DLL в память процесса (WriteProcessMemory). Системная ошибка: Отказано в доступе."`
- **Причина:** Память была выделена в игровом процессе, но библиотека не смогла записать путь к DLL в это место.
   - **Разрешения/Защита:** Аналогично сбою выделения памяти, это может быть проблема с разрешением на запись или активной защитой памяти.
- **Решение:** Применяются те же решения, что и для сбоя выделения памяти.

#### Сбой при Создании Потока Инъекции

- **Часть Сообщения об Ошибке:** `"Не удалось создать удаленный поток (CreateRemoteThread). Системная ошибка: Неверный параметр."`
- **Причина:** API `CreateRemoteThread` не удалось запустить новый `поток` в процессе `gta_sa.exe` для вызова `LoadLibraryW`.
   - **Безопасность:** Многие анти-читерские системы и защиты ОС отслеживают и блокируют создание удаленных `потоков`, так как это распространенная техника инъекции.
   - **Состояние Процесса:** Игровой процесс может находиться в нестабильном состоянии, которое препятствует созданию `потоков`.
- **Решение:** Временно отключите любое анти-читерское или антивирусное программное обеспечение. Попробуйте запустить приложение от имени администратора.

#### Превышено Время Ожидания или Ошибка при Ожидании Инъекции

- **Часть Сообщения об Ошибке:** `"Тайм-аут или ошибка при ожидании удаленного потока (WaitForSingleObject). Системная ошибка: Операция ожидания истекла."`
- **Причина:** Удаленный `поток` (который вызывает `LoadLibraryW`) не завершил свое выполнение в установленный лимит времени (10 секунд).
   - **Зависание:** `LoadLibraryW` мог зависнуть, выполняться слишком долго или быть перехвачен/заблокирован.
- **Решение:** Это может указывать на то, что DLL испытывает трудности с загрузкой или что-то ей мешает. Проверка системных логов или логов самого SA-MP/OMP (если они доступны) может дать больше подсказок.

#### Внутренний Сбой при Инъекции DLL

- **Часть Сообщения об Ошибке:** `"Вызов LoadLibraryW завершился сбоем в целевом процессе. DLL может быть повреждена, отсутствуют зависимости или заблокирована программным обеспечением безопасности."`
- **Причина:** Удаленный `поток` завершился, но возвращаемое значение `LoadLibraryW` было `0` (или `NULL`), что указывает на то, что DLL не была успешно загружена.
   - **Поврежденная/Отсутствующая DLL:** DLL могла быть перемещена, удалена или повреждена после начальной проверки.
   - **Отсутствующие Зависимости:** `samp.dll` или `omp-client.dll` могут иметь зависимости (другие DLL), которые отсутствуют в каталоге игры или в системном `PATH`.
   - **Внутренняя Ошибка DLL:** Сама DLL может иметь внутреннюю ошибку, которая препятствует ее загрузке.
- **Решение:** Проверьте целостность файлов `samp.dll`/`omp-client.dll`. Убедитесь, что все их зависимости присутствуют.

### Сложности при Возобновлении Выполнения Игры

Это последняя возможная точка сбоя в цикле инъекции.

- **Сообщение об Ошибке (Пример):** `"Не удалось возобновить поток игрового процесса: Неверный хэндл."`
- **Причина:** API `ResumeThread` не удалось возобновить основной `поток` `gta_sa.exe`.
   - **Неверный Хэндл:** `Хэндл` `потока` мог стать недействительным из-за какого-то неожиданного события.
   - **Разрешение:** У приложения может не быть разрешения на изменение состояния `потока`.
- **Решение:** Попробуйте запустить приложение от имени администратора. Если проблема сохраняется, это может указывать на более глубокую проблему стабильности в системе или в игровом процессе.

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