# SA-MP Injector C++

<div align="center">

![C++](https://img.shields.io/badge/C%2B%2B-14%2F17%2F20-00599C?style=for-the-badge&logo=cplusplus)
![Platform](https://img.shields.io/badge/Platform-Windows-blue?style=for-the-badge&logo=windows&logoColor=white)
![Architecture](https://img.shields.io/badge/Architecture-x86%20(32--bit)-lightgrey?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)

**Biblioteka C++ do uruchamiania i automatyzacji połączeń klientów SA-MP i OMP z serwerami poprzez wstrzykiwanie DLL.**

</div>

## Języki

- Português: [README](../../)
- Deutsch: [README](../Deutsch/README.md)
- English: [README](../English/README.md)
- Español: [README](../Espanol/README.md)
- Français: [README](../Francais/README.md)
- Italiano: [README](../Italiano/README.md)
- Русский: [README](../Русский/README.md)
- Svenska: [README](../Svenska/README.md)
- Türkçe: [README](../Turkce/README.md)

## Spis treści

- [SA-MP Injector C++](#sa-mp-injector-c)
  - [Języki](#języki)
  - [Spis treści](#spis-treści)
  - [Przegląd i cel](#przegląd-i-cel)
  - [Zasady projektowania](#zasady-projektowania)
    - [W pełni `Header-Only`](#w-pełni-header-only)
    - [Bezpieczne zarządzanie zasobami (RAII)](#bezpieczne-zarządzanie-zasobami-raii)
    - [Solidność i obsługa błędów](#solidność-i-obsługa-błędów)
    - [Elastyczność standardów C++](#elastyczność-standardów-c)
  - [Wymagane środowisko](#wymagane-środowisko)
    - [Dla deweloperów](#dla-deweloperów)
    - [Do uruchomienia](#do-uruchomienia)
  - [Szybki start](#szybki-start)
    - [Integracja z projektem](#integracja-z-projektem)
    - [Prosty przykład użycia](#prosty-przykład-użycia)
  - [Struktura biblioteki](#struktura-biblioteki)
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
  - [Szczegółowy proces wstrzykiwania](#szczegółowy-proces-wstrzykiwania)
    - [1. Żądanie inicjalizacji](#1-żądanie-inicjalizacji)
    - [2. Przygotowanie środowiska](#2-przygotowanie-środowiska)
    - [3. Weryfikacja integralności i parametrów](#3-weryfikacja-integralności-i-parametrów)
    - [4. Przygotowanie argumentów dla gry](#4-przygotowanie-argumentów-dla-gry)
    - [5. Uruchomienie procesu gry (w stanie wstrzymanym)](#5-uruchomienie-procesu-gry-w-stanie-wstrzymanym)
    - [6. Wstrzyknięcie biblioteki SA-MP (`samp.dll`)](#6-wstrzyknięcie-biblioteki-sa-mp-sampdll)
    - [7. Wstrzyknięcie biblioteki OMP (`omp-client.dll`) - Warunkowe](#7-wstrzyknięcie-biblioteki-omp-omp-clientdll---warunkowe)
    - [8. Aktywacja gry](#8-aktywacja-gry)
  - [Diagnostyka błędów i awarii](#diagnostyka-błędów-i-awarii)
    - [Błędy walidacji danych wejściowych](#błędy-walidacji-danych-wejściowych)
      - [Nieprawidłowa nazwa użytkownika](#nieprawidłowa-nazwa-użytkownika)
      - [Nieprawidłowy port połączenia](#nieprawidłowy-port-połączenia)
      - [Brak niezbędnych zasobów](#brak-niezbędnych-zasobów)
    - [Błędy w zarządzaniu procesem](#błędy-w-zarządzaniu-procesem)
      - [Problem z uruchomieniem procesu gry](#problem-z-uruchomieniem-procesu-gry)
    - [Problemy z wstrzykiwaniem DLL](#problemy-z-wstrzykiwaniem-dll)
      - [Nie można zlokalizować `LoadLibraryW`](#nie-można-zlokalizować-loadlibraryw)
      - [Błąd rezerwacji pamięci zdalnej](#błąd-rezerwacji-pamięci-zdalnej)
      - [Nie można zapisać danych w procesie](#nie-można-zapisać-danych-w-procesie)
      - [Błąd tworzenia wątku wstrzykiwania](#błąd-tworzenia-wątku-wstrzykiwania)
      - [Przekroczono limit czasu lub błąd podczas oczekiwania na wstrzyknięcie](#przekroczono-limit-czasu-lub-błąd-podczas-oczekiwania-na-wstrzyknięcie)
      - [Wewnętrzny błąd wstrzykiwania DLL](#wewnętrzny-błąd-wstrzykiwania-dll)
    - [Problem z wznowieniem działania gry](#problem-z-wznowieniem-działania-gry)
  - [Licencja](#licencja)
    - [Warunki użytkowania](#warunki-użytkowania)
      - [1. Przyznane uprawnienia](#1-przyznane-uprawnienia)
      - [2. Obowiązkowe warunki](#2-obowiązkowe-warunki)
      - [3. Prawa autorskie](#3-prawa-autorskie)
      - [4. Wyłączenie gwarancji i ograniczenie odpowiedzialności](#4-wyłączenie-gwarancji-i-ograniczenie-odpowiedzialności)

## Przegląd i cel

**SA-MP Injector C++** to kompaktowa i łatwa w integracji biblioteka C++, zaprojektowana do automatyzacji procesu uruchamiania i łączenia się z serwerami San Andreas Multiplayer (SA-MP) i Open Multiplayer (OMP). W odróżnieniu od bezpośredniego uruchamiania `gta_sa.exe`, to rozwiązanie programowo ładuje biblioteki `samp.dll` lub `omp-client.dll` do procesu gry Grand Theft Auto: San Andreas w kontrolowany sposób.

Jej głównym celem jest umożliwienie programistom C++ tworzenia niestandardowych `launcherów`, narzędzi do zarządzania społecznością lub programów narzędziowych, które wymagają uruchomienia GTA:SA z predefiniowanymi parametrami połączenia (takimi jak nazwa użytkownika, adres IP, port i hasło), oferując płynne i zautomatyzowane doświadczenie użytkownika.

## Zasady projektowania

Architektura **SA-MP Injector C++** opiera się na nowoczesnych zasadach projektowania, skupiając się na bezpieczeństwie, wydajności i łatwości użycia.

### W pełni `Header-Only`

Ta biblioteka jest dystrybuowana wyłącznie za pośrednictwem plików nagłówkowych (`.hpp`). To drastycznie upraszcza integrację z projektami C++, eliminując potrzebę kompilowania osobnych bibliotek, konfigurowania `linkerów` czy zarządzania zależnościami binarnymi.
- **Natychmiastowa integracja:** Wystarczy dołączyć odpowiednie `headers`.
- **Głęboka optymalizacja:** Kompilator może przeprowadzać agresywne `inlining` i optymalizacje `link-time`, co skutkuje bardziej kompaktowym i szybszym kodem końcowym.

### Bezpieczne zarządzanie zasobami (RAII)

Biblioteka szeroko stosuje wzorzec **RAII (Resource Acquisition Is Initialization)**. Krytyczne zasoby systemowe, takie jak `handles` procesów i `wątków` systemu Windows, są opakowane w `std::unique_ptr` z niestandardowymi `deleters`. Zapewnia to, że niezależnie od przepływu wykonania lub wystąpienia wyjątków, zasoby są zawsze prawidłowo zwalniane, zapobiegając wyciekom i poprawiając stabilność aplikacji.

### Solidność i obsługa błędów

Każdy krytyczny etap wstrzykiwania jest poprzedzony rygorystycznymi walidacjami i następuje po nim weryfikacja błędów API systemu Windows. Szczegółowe komunikaty o błędach są dostarczane użytkownikowi końcowemu za pośrednictwem okien dialogowych, z opisami systemowymi (`GetLastError()`) zawsze, gdy jest to możliwe. Takie podejście minimalizuje ryzyko nieokreślonego zachowania i oferuje jasną diagnostykę w przypadku awarii.

### Elastyczność standardów C++

Biblioteka została zbudowana tak, aby była kompatybilna z różnymi standardami C++, od C++14 do C++20. Osiągnięto to dzięki makrom warunkowym, które pozwalają na użycie nowoczesnych funkcji (takich jak `std::string_view`, `std::filesystem` i `std::optional` z C++17+), gdy są dostępne, jednocześnie zachowując `fallback` do równoważnych konstrukcji w C++14. Takie podejście zapewnia szeroką kompatybilność bez poświęcania nowoczesności.

## Wymagane środowisko

### Dla deweloperów

- **Kompilator C++:** Kompatybilny z **C++14 lub nowszym**.
   - Microsoft Visual C++ (Visual Studio 2015, 2017, 2019, 2022)
   - GCC (wersja 5 lub nowsza)
   - Clang (wersja 3.6 lub nowsza)
- **System operacyjny:** **Windows**.
- **Windows SDK:** Wymagane do dostępu do API systemu operacyjnego.
- **Architektura kompilacji:** **x86 (32-bit)**. Jest to ścisłe wymaganie, ponieważ `gta_sa.exe` oraz biblioteki DLL SA-MP/OMP działają wyłącznie na tej architekturze.

### Do uruchomienia

- **System operacyjny:** Każda nowoczesna wersja **Windows** kompatybilna ze skompilowanym plikiem binarnym.
- **Grand Theft Auto: San Andreas (GTA:SA):** Wymagana jest prawidłowa instalacja gry.
- **DLL klienta SA-MP lub OMP:** Pliki `samp.dll` lub `omp-client.dll` muszą być obecne w głównym katalogu gry, odpowiadając pożądanemu typowi wstrzyknięcia.

## Szybki start

Charakter `header-only` biblioteki ułatwia jej włączenie do dowolnego projektu C++.

### Integracja z projektem

1. **Pobierz nagłówki:** Pobierz pliki `.hpp` biblioteki (klonując repozytorium lub pobierając je bezpośrednio).
2. **Zorganizuj pliki:** Zaleca się utworzenie podfolderu w projekcie na `headers` biblioteki, na przykład, `MojProjekt/libraries/samp-injector/`.
3. **Zdefiniuj architekturę:** Skonfiguruj swój projekt do kompilacji dla architektury **x86 (32-bit)**.

```cpp
// Przykładowa struktura katalogów
MojProjekt/
├── src/
│   └── main.cpp
├── libraries/
│   └── samp-injector/
│       ├── constants.hpp
│       ├── error_utils.hpp
│       ├── injector.hpp // Główny nagłówek do dołączenia
│       └── ... (inne nagłówki)
└── built/ (twój katalog wyjściowy)
```

### Prosty przykład użycia

Aby zautomatyzować połączenie z serwerem, wystarczy wywołać funkcję `Initialize_Game` i podać szczegóły.

```cpp
#include <iostream>
#include <string>
//
#include "samp-launcher/injector.hpp" // Dołącz główny nagłówek

int main() {
    // Parametry do uruchomienia gry i połączenia
    std::wstring inject_type = L"samp"; // Lub L"omp" dla Open Multiplayer
    std::wstring game_folder = L"C:\\Games\\GTA San Andreas"; // Pełna ścieżka do folderu GTA:SA
    std::wstring nickname = L"Nazwa";
    std::wstring ip = L"127.0.0.1";
    std::wstring port = L"7777";
    std::wstring password = L""; // Zostaw puste, jeśli nie ma hasła

    // Główne wywołanie do uruchomienia gry i wstrzyknięcia DLL
    Initialize_Game(inject_type, game_folder, nickname, ip, port, password);

    // W przypadku błędu, automatycznie wyświetlane jest okno komunikatu o błędzie systemu Windows.

    return 0;
}
```

## Struktura biblioteki

Biblioteka jest starannie zmodularyzowana na kilka plików nagłówkowych, z których każdy ma dobrze zdefiniowane obowiązki, co ułatwia organizację, konserwację i ponowne wykorzystanie.

### 1. `constants.hpp`

Ten plik jest **centralnym repozytorium** biblioteki, służącym jako scentralizowane repozytorium wszystkich stałych i niezmiennych wartości, które dyktują zachowanie i interoperacyjność **SA-MP Injector C++**. Jego organizacja według kategorii logicznych promuje nie tylko przejrzystość i czytelność kodu, ale także ułatwia konserwację i zapewnia ścisłą spójność w całym ekosystemie biblioteki.

Każda stała jest zdefiniowana za pomocą `CONSTEXPR_VAR`, które rozwija się do `inline constexpr` (dla C++17+) lub `static constexpr` (dla C++14), zapewniając, że te wartości są oceniane w czasie kompilacji, optymalizując wydajność i bezpieczeństwo typów.

Organizacja stałych według kategorii ułatwia zrozumienie ich przeznaczenia:

- **Stałe związane z grą (`Game Related Constants`)**
   - `MIN_PORT`: `int`, który definiuje najmniejszy prawidłowy numer portu do połączenia z serwerem (wartość: `1`).
   - `MAX_PORT`: `int`, który ustala największy prawidłowy numer portu do połączenia z serwerem (wartość: `65535`).
   - `MAX_NICKNAME_LENGTH`: `int`, który określa maksymalną dozwoloną długość pseudonimu gracza (wartość: `23` znaków), limit narzucony przez specyfikacje klienta SA-MP/OMP.

- **Nazwy niezbędnych plików (`File Names`)**
   - `SAMP_DLL_NAME`: `const wchar_t*`, który zawiera nazwę pliku głównej biblioteki klienta SA-MP (wartość: `L"samp.dll"`). Niezbędny do wstrzyknięcia klasycznego klienta.
   - `OMP_DLL_NAME`: `const wchar_t*`, który zawiera nazwę pliku biblioteki klienta Open Multiplayer (wartość: `L"omp-client.dll"`). Używany specjalnie, gdy wstrzyknięcie jest typu OMP.
   - `GAME_EXE_NAME`: `const wchar_t*`, który przechowuje nazwę pliku wykonywalnego podstawowej gry Grand Theft Auto: San Andreas (wartość: `L"gta_sa.exe"`). Główny cel wstrzyknięcia.

- **API i funkcje systemowe (`System Libraries and Functions`)**
   - `KERNEL32_DLL`: `const wchar_t*`, który definiuje nazwę biblioteki systemowej Windows (`L"kernel32.dll"`). Ta biblioteka DLL jest kluczowa, ponieważ zawiera funkcje do manipulacji procesami i pamięcią, których używa injector. Użycie `wchar_t` zapewnia kompatybilność z funkcjami API, które obsługują szerokie znaki, takie jak `GetModuleHandleW`.
   - `LOAD_LIBRARY_FUNC`: `const char*` z nazwą funkcji do dynamicznego ładowania biblioteki DLL (wartość: `"LoadLibraryW"`). Chociaż biblioteka działa głównie z szerokimi znakami, funkcja `GetProcAddress` z API systemu Windows wymaga nazwy funkcji w formacie ANSI (`char*`).

- **Argumenty wiersza poleceń (`Command Line Arguments`)**
   - Te stałe definiują prefiksy dla argumentów, które są przekazywane do `gta_sa.exe` w celu skonfigurowania połączenia klienta. Są one dostarczane w formacie `Wide Character` (`const wchar_t*`) dla kompatybilności z `CreateProcessW`.
      - `CMD_ARG_CONFIG`: Argument dla ogólnych ustawień (wartość: `L"-c"`).
      - `CMD_ARG_NICKNAME`: Argument dla pseudonimu gracza (wartość: `L"-n"`).
      - `CMD_ARG_HOST`: Argument dla adresu IP serwera (wartość: `L"-h"`).
      - `CMD_ARG_PORT`: Argument dla portu serwera (wartość: `L"-p"`).
      - `CMD_ARG_PASSWORD`: Argument dla hasła serwera (wartość: `L"-z"`). Używany tylko, jeśli podano hasło.

- **Identyfikatory typów wstrzyknięć (`Injection types as strings`)**
   - `INJECT_TYPE_SAMP`: `const wchar_t*` dla reprezentacji w postaci ciągu znaków typu wstrzyknięcia SA-MP (wartość: `L"samp"`).
   - `INJECT_TYPE_OMP`: `const wchar_t*` dla reprezentacji w postaci ciągu znaków typu wstrzyknięcia OMP (wartość: `L"omp"`).

- **Tytuły komunikatów o błędach (`Error message titles`)**
   - `ERROR_TITLE_SAMP`: `const wchar_t*`, który definiuje domyślny tytuł dla okien dialogowych błędów związanych z awariami SA-MP (wartość: `L"SA-MP Injector Error - SPC"`).
   - `ERROR_TITLE_OMP`: `const wchar_t*`, który definiuje domyślny tytuł dla okien dialogowych błędów związanych z awariami OMP (wartość: `L"OMP Injector Error - SPC"`).

- **Flagi tworzenia procesu (`Process creation`)**
   - `PROCESS_CREATION_FLAGS`: `DWORD`, który hermetyzuje flagi przekazywane do `CreateProcessW`. Co najważniejsze, zawiera `CREATE_SUSPENDED` (`0x00000004`), który uruchamia proces gry w stanie wstrzymanym, oraz `DETACHED_PROCESS` (`0x00000008`), który odłącza nowy proces od konsoli procesu nadrzędnego.

- **Limity czasowe (`Timeouts`)**
   - `DLL_INJECTION_TIMEOUT_MS`: `DWORD`, który określa maksymalny czas (w milisekundach), przez który biblioteka będzie czekać na zakończenie zdalnego `wątku` odpowiedzialnego za wstrzyknięcie biblioteki DLL (wartość: `10000ms`, czyli 10 sekund).

- **Flagi alokacji pamięci (`Memory allocation`)**
   - Te stałe są używane do wywołań API manipulacji pamięcią, takich jak `VirtualAllocEx` i `VirtualProtect`.
      - `MEM_COMMIT`: `DWORD`, który rezerwuje strony w pamięci wirtualnej i je "zatwierdza" (przydziela pamięć fizyczną) (wartość: `0x1000`).
      - `MEM_RESERVE`: `DWORD`, który tylko rezerwuje zakres przestrzeni adresowej wirtualnej do późniejszego użycia (wartość: `0x2000`).
      - `MEM_RELEASE`: `DWORD`, który odzatwierdza i zwalnia region stron (wartość: `0x8000`).
      - `MEMORY_ALLOCATION_TYPE`: Kombinacja `MEM_COMMIT` i `MEM_RESERVE`, używana do alokacji początkowej pamięci na ścieżkę DLL w procesie zdalnym.
      - `MEMORY_PROTECTION`: `DWORD`, który definiuje uprawnienia ochrony pamięci (wartość: `PAGE_READWRITE` lub `0x04` w Windows API), zezwalając na odczyt i zapis w przydzielonej pamięci.

### 2. `types.hpp`

Ten zwięzły plik wprowadza `enum class` do typowania różnych trybów wstrzykiwania. Użycie typu wyliczeniowego, zamiast literałów ciągów znaków, podnosi bezpieczeństwo kodu, zapobiega literówkom i poprawia czytelność.

- **`Inject_Type`:** `enum class` z dwoma członkami: `SAMP` i `OMP`, reprezentującymi typy klienta do wstrzyknięcia.

```cpp
// Przykładowy types.hpp
namespace Types {
    enum class Inject_Type {
        SAMP, // Wskazuje wstrzyknięcie dla klienta SA-MP
        OMP // Wskazuje wstrzyknięcie dla klienta Open Multiplayer
    };
}
```

### 3. `version.hpp`

Działając jako adapter kompatybilności, ten nagłówek dynamicznie wykrywa standard C++ używany przez kompilator. Definiuje on makra warunkowe (`SAMP_INJECTOR_CXX_14`, `SAMP_INJECTOR_CXX_MODERN`), które kierują bibliotekę do używania bardziej zaawansowanych funkcji C++ (takich jak `std::string_view` czy `std::filesystem`), gdy są dostępne, jednocześnie zapewniając pełną funkcjonalność w środowiskach C++14.

- **`SAMP_INJECTOR_CXX_14`:** Definiowane, jeśli standardem C++ jest C++14.
- **`SAMP_INJECTOR_CXX_MODERN`:** Definiowane dla C++17 lub nowszych, włączając nowsze funkcje języka.
- **`SAMP_INJECTOR_NODISCARD`:** Dostosowuje atrybut `[[nodiscard]]` do wersji C++, które go obsługują, zachęcając do sprawdzania wartości zwracanych.

```cpp
// Przykładowy istotny fragment z version.hpp
#if (defined(_MSC_VER) && _MSVC_LANG >= 201703L) || __cplusplus >= 201703L
    #define SAMP_INJECTOR_CXX_MODERN // Włącza nowoczesne funkcje C++17+
#endif

#if defined(SAMP_INJECTOR_CXX_MODERN)
    #define SAMP_INJECTOR_NODISCARD [[nodiscard]] // Używa atrybutu nodiscard z C++17
#elif defined(SAMP_INJECTOR_CXX_14)
    #define SAMP_INJECTOR_NODISCARD // Dla C++14 atrybut jest wyłączony
#endif
```

### 4. `error_utils.hpp`

To narzędzie jest dedykowane do zarządzania i prezentacji informacji zwrotnej o błędach. Abstrahuje mechanizmy systemu Windows do pobierania komunikatów o błędach systemowych i oferuje ujednolicony interfejs do powiadamiania użytkownika o problemach.

- **`Get_System_Error_Message`:** Tłumaczy kod błędu systemu Windows (`GetLastError()`) na czytelny `std::wstring`, kluczowy dla dokładnej diagnostyki.
- **`Show_Error`:** Wyświetla okno dialogowe (`MessageBoxW`) zawierające dostarczony komunikat o błędzie, z tytułem specyficznym dla SA-MP lub OMP, zapewniając jasną komunikację z użytkownikiem.

```cpp
// Przykładowy istotny fragment z error_utils.hpp
namespace Error_Utils {
    SAMP_INJECTOR_NODISCARD
    inline std::wstring Get_System_Error_Message(DWORD error_code) {
        if (error_code == 0)
            return L"Nie wystąpił żaden błąd.";
        
        // ... Logika do formatowania komunikatu systemowego ...
    }

    inline void Show_Error(std::wstring_view message, Types::Inject_Type inject_type) {
        const std::wstring title = (inject_type == Types::Inject_Type::SAMP) ? Constants::ERROR_TITLE_SAMP : Constants::ERROR_TITLE_OMP;
        MessageBoxW(nullptr, message.data(), title.c_str(), MB_OK | MB_ICONERROR);
    }
}
```

### 5. `validation.hpp`

Działając jako pierwsza linia obrony solidności biblioteki, ten nagłówek dostarcza rygorystycznych procedur do weryfikacji poprawności danych wejściowych i obecności niezbędnych plików. Te kontrole są przeprowadzane przed jakąkolwiek interakcją niskiego poziomu z systemem, co minimalizuje ryzyko błędów `runtime` i zapewnia proaktywną informację zwrotną.

- **`Validate_Port`:** Sprawdza, czy ciąg znaków portu reprezentuje liczbę całkowitą i czy mieści się ona w skonfigurowanym zakresie (od `MIN_PORT` do `MAX_PORT`).
- **`Validate_Nickname`:** Weryfikuje, czy pseudonim nie jest pusty i czy jego długość nie przekracza `MAX_NICKNAME_LENGTH`.
- **`Validate_Files`:** Potwierdza fizyczne istnienie `gta_sa.exe`, `samp.dll` oraz, warunkowo dla wstrzyknięcia OMP, `omp-client.dll`. Implementacja dostosowuje się do `std::filesystem` (C++17+) lub `GetFileAttributesW` (C++14).

```cpp
// Przykładowy istotny fragment z validation.hpp
namespace Validation {
    inline bool Validate_Nickname(std::wstring_view nickname_str, std::wstring& error_message) {
        if (nickname_str.empty())
            return (error_message = L"Pseudonim nie może być pusty. Proszę podać prawidłowy pseudonim.", false);
        
        if (nickname_str.length() > Constants::MAX_NICKNAME_LENGTH)
            return (error_message = L"Długość pseudonimu przekracza maksymalną dozwoloną długość " + std::to_wstring(Constants::MAX_NICKNAME_LENGTH) + L" znaków. Proszę użyć krótszego pseudonimu.", false);
        
        return true;
    }

    inline bool Validate_Files(const std::filesystem::path& game_path, const std::filesystem::path& samp_DLL_path, const std::filesystem::path& omp_DLL_path, Types::Inject_Type inject_type) {
        if (!std::filesystem::exists(game_path))
            return (Error_Utils::Show_Error(L"Nie znaleziono pliku wykonywalnego gry. Upewnij się, że 'gta_sa.exe' istnieje w podanej ścieżce: " + game_path.wstring(), inject_type), false);
        
        // ... Inne weryfikacje plików ...
        return true;
    }
}
```

### 6. `resource_handle.hpp`

Implementuje elegancką i bezpieczną strategię zarządzania zasobami systemu operacyjnego, takimi jak `HANDLE` systemu Windows. Wykorzystując zasadę RAII, gwarantuje, że wszystkie przydzielone zasoby są prawidłowo zwalniane, zapobiegając wyciekom i wzmacniając stabilność aplikacji.

- **`Unique_Resource`:** `alias template`, który dostosowuje `std::unique_ptr` do pracy z niestandardowymi `deleters`, umożliwiając zarządzanie dowolnym typem zasobu, który wymaga określonej funkcji zwalniającej.
- **`Make_Unique_Handle`:** Wygodna funkcja `factory`, która konstruuje i zwraca `Unique_Resource` wstępnie skonfigurowany dla `HANDLE` systemu Windows. Powiązany `deleter` automatycznie wywołuje `CloseHandle`, gdy `Unique_Resource` wychodzi z zakresu, zapewniając natychmiastowe zwolnienie zasobu.

```cpp
// Przykładowy istotny fragment z resource_handle.hpp
namespace Resource_Handle {
    // Niestandardowy std::unique_ptr do zarządzania zasobami systemowymi.
    template<typename T, typename Deleter>
    using Unique_Resource = std::unique_ptr<std::remove_pointer_t<T>, Deleter>;

    // Tworzy Unique_Resource dla HANDLE, z deleterem, który wywołuje CloseHandle.
    template<typename T>
    inline auto Make_Unique_Handle(T handle) {
        return Unique_Resource<T, std::function<void(T)>>(handle, [](T h) {
            if (h && h != INVALID_HANDLE_VALUE) // Zapewnia, że uchwyt jest prawidłowy przed zamknięciem
                CloseHandle(h);
        });
    }
}
```

### 7. `privileges.hpp`

Ten komponent jest odpowiedzialny za konfigurowanie środowiska bezpieczeństwa procesu aplikacji. Zawiera funkcjonalność do podnoszenia uprawnień, w szczególności włączając uprawnienie do debugowania (`SE_DEBUG_NAME`), które jest fundamentalnym wymogiem, aby biblioteka mogła wykonywać operacje wstrzykiwania DLL do zewnętrznych procesów systemu Windows.

- **`Enable_Debug_Privilege`:** Ta funkcja próbuje uzyskać i aktywować uprawnienie `SE_DEBUG_NAME` dla bieżącego procesu. Jest to kluczowy początkowy krok, aby przyznać aplikacji niezbędne uprawnienia do manipulowania innymi procesami, takimi jak alokacja pamięci i tworzenie zdalnych `wątków`. Zwraca `true` w przypadku sukcesu.

```cpp
// Przykładowy istotny fragment z privileges.hpp
namespace Privileges {
    inline bool Enable_Debug_Privilege() {
        HANDLE token_handle;

        // Próbuje otworzyć token bieżącego procesu, aby dostosować uprawnienia
        if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &token_handle))
            return false;

        auto handle_guard = Resource_Handle::Make_Unique_Handle(token_handle); // Bezpieczne zarządzanie uchwytem

        TOKEN_PRIVILEGES tp;
        LUID luid;

        // Wyszukuje wartość LUID dla uprawnienia SE_DEBUG_NAME
        if (!LookupPrivilegeValue(nullptr, SE_DEBUG_NAME, &luid))
            return false;
        
        tp.PrivilegeCount = 1;
        tp.Privileges[0].Luid = luid;
        tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED; // Włącza uprawnienie

        // Dostosowuje uprawnienia procesu
        if (!AdjustTokenPrivileges(token_handle, FALSE, &tp, sizeof(TOKEN_PRIVILEGES), nullptr, nullptr))
            return false;

        return GetLastError() == ERROR_SUCCESS; // Zwraca true, jeśli operacja zakończyła się sukcesem (brak oczekujących błędów)
    }
}
```

### 8. `process.hpp`

Jest to jeden z najbardziej krytycznych komponentów biblioteki, zawierający niskopoziomową implementację interakcji z procesami systemu Windows. Hermetyzuje złożone operacje tworzenia procesu gry, alokacji pamięci, zapisu danych oraz technikę wstrzykiwania DLL poprzez tworzenie zdalnych `wątków`.

- **`Process_Info` struct:** Wewnętrzna struktura przechowująca `Unique_Resource` dla `HANDLE` procesu (`process_handle`) i `HANDLE` głównego `wątku` (`thread_handle`) gry. Zawiera metodę `Resume()` do ponownej aktywacji głównego `wątku` gry po zakończeniu wstrzykiwania.
- **`Injection_Status` enum class:** Definiuje szczegółową listę możliwych wyników operacji wstrzykiwania DLL, umożliwiając precyzyjną diagnostykę awarii.
- **`Create_Game_Process`:**
   - Używa funkcji `CreateProcessW` z API systemu Windows do uruchomienia pliku wykonywalnego `gta_sa.exe`.
   - Kluczowe jest, aby proces został utworzony z flagą `CREATE_SUSPENDED` (zawartą w `Constants::PROCESS_CREATION_FLAGS`). Zapewnia to, że gra jest wstrzymywana natychmiast po jej utworzeniu, zanim jakikolwiek kod zostanie wykonany, co pozwala na bezpieczne wstrzyknięcie DLL.
   - Zwraca `std::optional<Process_Info>` (dla C++17+) lub `std::unique_ptr<Process_Info>` (dla C++14), zawierające hermetyzowane `handles` procesu i `wątku`.
- **`Inject_DLL`:**
   - Implementuje standardową technikę wstrzykiwania DLL za pomocą `CreateRemoteThread`:
      1. **Pobranie adresu:** Wykorzystując stałe z `constants.hpp`, lokalizuje adres funkcji `LoadLibraryW` (z `kernel32.dll`), której system Windows używa do dynamicznego ładowania bibliotek.
      2. **Alokacja pamięci:** `VirtualAllocEx` jest używane do zarezerwowania bloku pamięci wirtualnej w procesie gry (`gta_sa.exe`). Ten blok jest wymiarowany tak, aby pomieścić pełną ścieżkę do wstrzykiwanej biblioteki DLL.
      3. **Zapis ścieżki:** Ścieżka do biblioteki DLL (np. `L"C:\\ścieżka\\do\\samp.dll"`) jest następnie kopiowana do zdalnie przydzielonej pamięci w procesie gry za pomocą `WriteProcessMemory`.
      4. **Tworzenie zdalnego wątku:** `CreateRemoteThread` uruchamia nowy `wątek` w kontekście procesu gry. Punktem wejścia tego `wątku` jest adres `LoadLibraryW`, a przekazanym argumentem jest adres ciągu znaków ze ścieżką do DLL, który właśnie zapisaliśmy.
      5. **Monitorowanie:** Wykonanie zdalnego `wątku` jest monitorowane przez `WaitForSingleObject` do momentu jego zakończenia lub osiągnięcia `DLL_INJECTION_TIMEOUT_MS`.
      6. **Weryfikacja sukcesu:** `GetExitCodeThread` jest używane do sprawdzenia wartości zwracanej przez zdalny `wątek`. Jeśli `LoadLibraryW` zakończyło się sukcesem, zwróci ono bazowy adres załadowanej biblioteki DLL (wartość różna od zera).
      7. **Sprzątanie:** Pamięć przydzielona w procesie zdalnym jest zwalniana przez `VirtualFreeEx`.
   - Zwraca `Injection_Status` wskazujący sukces lub konkretny typ awarii wstrzyknięcia.

```cpp
// Przykładowy istotny fragment z process.hpp
class Process {
public:
    struct Process_Info {
        Resource_Handle::Unique_Resource<HANDLE, std::function<void(HANDLE)>> process_handle; // Uchwyt procesu z zarządzaniem RAII
        Resource_Handle::Unique_Resource<HANDLE, std::function<void(HANDLE)>> thread_handle; // Uchwyt wątku z zarządzaniem RAII

        bool Resume() { // Wznawia wykonanie głównego wątku gry
            return thread_handle && ResumeThread(thread_handle.get()) != static_cast<DWORD>(-1);
        }
    };
    
    enum class Injection_Status { // Szczegółowe kody statusu dla wstrzyknięcia DLL
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

    // Tworzy proces gry w stanie wstrzymanym
    std::optional<Process_Info> Create_Game_Process(const std::wstring& game_path, std::wstring& command_args, const std::wstring& working_dir) {
        // ... Logika CreateProcessW z CREATE_SUSPENDED ...
    }
    
    SAMP_INJECTOR_NODISCARD // Zapewnia, że wartość zwracana jest używana
    Injection_Status Inject_DLL(HANDLE process, const std::wstring& DLL_path) {
        static const LPVOID load_library_addr = reinterpret_cast<LPVOID>(GetProcAddress(GetModuleHandleW(Constants::KERNEL32_DLL), Constants::LOAD_LIBRARY_FUNC));

        if (!load_library_addr)
            return Injection_Status::LOADLIBRARY_ADDRESS_FAILED;

        LPVOID remote_memory = VirtualAllocEx(process, nullptr, (DLL_path.length() + 1) * sizeof(wchar_t), Constants::MEMORY_ALLOCATION_TYPE, Constants::MEMORY_PROTECTION);

        if (!remote_memory)
            return Injection_Status::ALLOCATION_FAILED;

        auto memory_guard = Resource_Handle::Unique_Resource<LPVOID, std::function<void(LPVOID)>>(remote_memory, [process](LPVOID ptr) {
            if (ptr)
                VirtualFreeEx(process, ptr, 0, MEM_RELEASE); // Zwalnia pamięć w procesie zdalnym
        });

        if (!WriteProcessMemory(process, remote_memory, DLL_path.c_str(), (DLL_path.length() + 1) * sizeof(wchar_t), nullptr))
            return Injection_Status::WRITE_FAILED;

        HANDLE remote_thread = CreateRemoteThread(process, nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(load_library_addr), remote_memory, 0, nullptr);

        if (!remote_thread)
            return Injection_Status::THREAD_CREATION_FAILED;

        auto thread_guard = Resource_Handle::Make_Unique_Handle(remote_thread); // Bezpieczne zarządzanie uchwytem zdalnego wątku

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

Ten nagłówek definiuje klasę `Injector_Core`, która służy jako centrum dowodzenia biblioteki. Orkiestruje ona logiczną sekwencję operacji wstrzykiwania, łącząc moduły walidacji danych wejściowych, zarządzania uprawnieniami i manipulacji procesami. To tutaj zdefiniowany jest pełny przepływ pracy wstrzykiwania.

- **`Injector_Core`:** Konstruktor tej klasy jest miejscem, w którym wywoływane jest `Privileges::Enable_Debug_Privilege()`. Zapewnia to, że proces aplikacji posiada niezbędne uprawnienia do wykonywania operacji wstrzykiwania DLL, zanim zostanie wykonana jakakolwiek inna krytyczna logika.
- **`Initialize_Game`:**
   1. **Wszechstronna walidacja:** Rozpoczyna od wywołania funkcji walidacyjnych (`Validation::Validate_Port`, `Validation::Validate_Nickname`, `Validation::Validate_Files`), aby upewnić się, że wszystkie parametry i niezbędne zasoby są w porządku. Jeśli którakolwiek walidacja się nie powiedzie, natychmiast zgłaszany jest błąd.
   2. **Przygotowanie argumentów:** Buduje kompletną linię poleceń (`std::wstring`), która zostanie przekazana do `gta_sa.exe`, zawierającą podany pseudonim, IP, port i hasło.
   3. **Tworzenie wstrzymanego procesu:** Wywołuje `Process::Create_Game_Process`, aby uruchomić `gta_sa.exe` w stanie wstrzymanym, uzyskując `handles` procesu i głównego `wątku`.
   4. **Wstrzyknięcie `samp.dll`:** Wywołuje `Inject_DLL_With_Status_Check`, aby wstrzyknąć `samp.dll` do procesu gry. Ta funkcja opakowująca jest również odpowiedzialna za interpretację zwróconego `Injection_Status` i wyświetlanie informacyjnych komunikatów o błędach.
   5. **Warunkowe wstrzyknięcie `omp-client.dll`:** Jeśli `inject_type` to `Types::Inject_Type::OMP`, `omp-client.dll` jest następnie wstrzykiwany w ten sam sposób co `samp.dll`.
   6. **Wznowienie gry:** Po pomyślnym zakończeniu wszystkich wstrzyknięć, wywoływane jest `process_info.Resume()`, aby pozwolić głównemu `wątkowi` gry kontynuować swoje wykonanie.
   7. **Obsługa błędów w cyklu:** Jakakolwiek awaria na którymkolwiek z tych krytycznych etapów spowoduje wywołanie `Error_Utils::Show_Error`, dostarczając jasnej informacji zwrotnej użytkownikowi i zapewniając, że proces zostanie prawidłowo zakończony (`handles` są automatycznie zwalniane przez `Unique_Resource`).
- **`Build_Command_Args`:** Funkcja pomocnicza, która organizuje i konkatenujje argumenty wiersza poleceń, dodając cudzysłowy tam, gdzie jest to konieczne dla parametrów zawierających spacje.
- **`Inject_DLL_With_Status_Check`:** Prywatna funkcja działająca jako opakowanie dla `Process::Inject_DLL`. Mapuje ona różne `Injection_Status` na zrozumiałe komunikaty o błędach, ułatwiając obsługę błędów i komunikację z użytkownikiem.

```cpp
// Przykładowy istotny fragment z injector_core.hpp
namespace Injector {
    class Injector_Core {
    public:
        Injector_Core() { // Konstruktor włącza uprawnienie do debugowania
            Privileges::Enable_Debug_Privilege();
        }

        bool Initialize_Game(Types::Inject_Type inject_type, std::wstring_view folder, std::wstring_view nickname, std::wstring_view ip, std::wstring_view port, std::wstring_view password) {
            std::wstring error_message;

            // Sekwencja walidacji danych wejściowych
            if (!Validation::Validate_Port(port, error_message))
                return (Error_Utils::Show_Error(error_message, inject_type), false);
            // ... inne walidacje ...

            // Buduje argumenty wiersza poleceń
            std::wstring args = Build_Command_Args({
                Command_Arg{Constants::CMD_ARG_NICKNAME, std::wstring(nickname)},
                // ... inne argumenty ...
            });

            Process process_core;
            // Tworzy proces gry w stanie wstrzymanym
            auto process_info_opt = process_core.Create_Game_Process(game_path, args, std::wstring(folder));

            if (!process_info_opt)
                return false;

            auto& process_info = *process_info_opt;

            // Wstrzykuje samp.dll i, warunkowo, omp-client.dll
            if (!Inject_DLL_With_Status_Check(process_core, process_info.process_handle.get(), Constants::SAMP_DLL_NAME, samp_DLL_path.wstring(), inject_type))
                return false;
            
            if (inject_type == Types::Inject_Type::OMP) {
                if (!Inject_DLL_With_Status_Check(process_core, process_info.process_handle.get(), Constants::OMP_DLL_NAME, omp_DLL_path.wstring(), inject_type))
                    return false;
            }
            
            // Wznawia główny wątek gry
            if (!process_info.Resume())
                return (Error_Utils::Show_Error(L"Nie udało się wznowić wątku procesu gry: " + Error_Utils::Get_System_Error_Message(GetLastError()), inject_type), false);

            return true;
        }
    };
}
```

### 10. `injector.hpp`

Ten nagłówek działa jako główna fasada (`Facade`) biblioteki, oferując uproszczony punkt wejścia dla każdej aplikacji, która chce korzystać z funkcjonalności wstrzykiwania. Abstrahuje on wewnętrzną złożoność `Injector_Core` w jedną, wygodną funkcję.

- **`Initialize_Game`:**
   - Ta funkcja statyczna jest publicznym interfejsem biblioteki.
   - Najpierw waliduje `inject_type_str` (czy to `L"samp"` czy `L"omp"`) i konwertuje go na `enum class Types::Inject_Type`. W przypadku nieprawidłowego ciągu znaków, wyświetla błąd i kończy działanie.
   - Następnie tworzy instancję `Injector::Injector_Core`.
   - Na koniec deleguje wykonanie głównej logiki do `Injector_Core::Initialize_Game`, gdzie cały proces walidacji, tworzenia procesu i wstrzykiwania DLL jest orkiestrowany.

```cpp
// Przykładowy istotny fragment z injector.hpp
// Publiczny interfejs do uruchamiania gry
#if defined(SAMP_INJECTOR_CXX_MODERN)
inline bool Initialize_Game(std::wstring_view inject_type, std::wstring_view folder, std::wstring_view nickname, std::wstring_view ip, std::wstring_view port, std::wstring_view password) {
#elif defined(SAMP_INJECTOR_CXX_14)
inline bool Initialize_Game(const std::wstring& inject_type, const std::wstring& folder, const std::wstring& nickname, const std::wstring& ip, const std::wstring& port, const std::wstring& password) {
#endif
    Types::Inject_Type type;

    // Konwertuje ciąg znaków typu wstrzyknięcia na odpowiedni enum
    if (inject_type == Constants::INJECT_TYPE_SAMP)
        type = Types::Inject_Type::SAMP;
    else if (inject_type == Constants::INJECT_TYPE_OMP)
        type = Types::Inject_Type::OMP;
    else
        // Wyświetla błąd, jeśli typ wstrzyknięcia jest nieprawidłowy
        return (Error_Utils::Show_Error(L"Nieprawidłowy tryb wstrzykiwania. Użyj 'samp' lub 'omp'.", Types::Inject_Type::SAMP), false);

    Injector::Injector_Core injector; // Tworzy instancję rdzenia injectora

    // Deleguje główną logikę do Injector_Core
    return injector.Initialize_Game(type, folder, nickname, ip, port, password);
}
```

## Szczegółowy proces wstrzykiwania

Główną funkcjonalnością tej biblioteki jest orkiestracja precyzyjnej sekwencji operacji w celu wstrzyknięcia bibliotek DLL klienta SA-MP lub OMP do procesu GTA:SA. Ten cykl jest starannie zaplanowany, aby zapewnić stabilność i kompatybilność.

### 1. Żądanie inicjalizacji

Proces rozpoczyna się od wywołania globalnej funkcji `Initialize_Game` (`injector.hpp`), która działa jako główny punkt kontaktowy dla aplikacji korzystającej z biblioteki. Funkcja ta otrzymuje wszystkie kluczowe parametry, takie jak pożądany typ wstrzyknięcia (SA-MP lub OMP), katalog gry oraz dane do połączenia z serwerem (pseudonim, IP, port, hasło).

### 2. Przygotowanie środowiska

Po wywołaniu, funkcja `Initialize_Game` tworzy instancję `Injector::Injector_Core`. W konstruktorze tej klasy (`injector_core.hpp`) wykonywany jest pierwszy i niezbędny etap konfiguracji środowiska: podniesienie uprawnień.

> [!NOTE]
> `Privileges::Enable_Debug_Privilege()`: To wywołanie (`privileges.hpp`) nadaje procesowi aplikacji uprawnienie `SE_DEBUG_NAME`. To uprawnienie jest kluczowe, ponieważ pozwala aplikacji na wykonywanie niskopoziomowych operacji na innych procesach systemu Windows, takich jak odczyt i zapis w ich pamięci oraz tworzenie zdalnych `wątków` – fundamentalne działania dla techniki wstrzykiwania DLL.

### 3. Weryfikacja integralności i parametrów

Po dostosowaniu uprawnień, metoda `Injector_Core::Initialize_Game` przechodzi do serii rygorystycznych walidacji. Jest to faza prewencyjna, która minimalizuje ryzyko awarii na późniejszych etapach i dostarcza natychmiastowej informacji zwrotnej użytkownikowi.

- **Walidacja portu:** `Validation::Validate_Port` sprawdza, czy numer portu połączenia jest poprawnie sformatowany i mieści się w zakresie od `1` do `65535` (`constants.hpp`).
- **Walidacja pseudonimu:** `Validation::Validate_Nickname` zapewnia, że pseudonim gracza nie jest pusty i nie przekracza limitu `23` znaków.
- **Weryfikacja niezbędnych plików:** `Validation::Validate_Files` sprawdza katalog gry w celu potwierdzenia obecności `gta_sa.exe`, `samp.dll` oraz, jeśli wstrzyknięcie jest typu OMP, także `omp-client.dll`.

> [!WARNING]
> Jakakolwiek awaria na tym etapie skutkuje natychmiastowym wyświetleniem `MessageBox` ze szczegółowym komunikatem o błędzie (`error_utils.hpp`) i przerwaniem procesu wstrzykiwania. Zapobiega to bezcelowym próbom kontynuowania z nieprawidłową konfiguracją.

### 4. Przygotowanie argumentów dla gry

Po pomyślnej walidacji, funkcja `Injector_Core::Build_Command_Args` jest odpowiedzialna za zbudowanie sformatowanej linii poleceń, która zostanie przekazana do `gta_sa.exe`. Ta linia poleceń zawiera wszystkie niezbędne parametry, aby klient SA-MP/OMP automatycznie połączył się z serwerem, takie jak `-n "pseudonim" -h "IP" -p "Port" -z "Hasło"`.

### 5. Uruchomienie procesu gry (w stanie wstrzymanym)

Komponent `Process` (`process.hpp`) jest następnie odpowiedzialny za uruchomienie pliku wykonywalnego GTA:SA.

> [!IMPORTANT]
> Funkcja `Process::Create_Game_Process` używa flagi `CREATE_SUSPENDED` (`constants.hpp`) podczas wywoływania API `CreateProcessW` systemu Windows. Jest to krytyczne rozwiązanie projektowe: gra jest ładowana do pamięci, a jej główny `wątek` jest tworzony, ale jego wykonanie jest **wstrzymane**. Tworzy to kontrolowane i stabilne środowisko, idealne do wstrzykiwania bibliotek DLL, zanim gra zdąży zainicjować własne mechanizmy obronne lub wewnętrzną logikę. `Handles` procesu i `wątku` są uzyskiwane i bezpiecznie zarządzane za pomocą `Resource_Handle::Unique_Resource`.

### 6. Wstrzyknięcie biblioteki SA-MP (`samp.dll`)

Gdy proces gry jest w stanie wstrzymania, wstrzyknięcie `samp.dll` może być przeprowadzone bezpiecznie. Metoda `Injector_Core::Inject_DLL_With_Status_Check` deleguje to zadanie do `Process::Inject_DLL`, które wykonuje następujące kroki techniki `remote thread injection`:

1. **Lokalizacja funkcji `LoadLibraryW`:** Identyfikowany jest adres funkcji `LoadLibraryW`. Operacja ta wykorzystuje stałe `Constants::KERNEL32_DLL` i `Constants::LOAD_LIBRARY_FUNC` do uzyskania `handle` do `kernel32.dll`, a następnie zlokalizowania adresu funkcji do dynamicznego ładowania bibliotek.
2. **Alokacja pamięci zdalnej:** `VirtualAllocEx` jest używane do zarezerwowania bloku pamięci w przestrzeni adresowej wirtualnej procesu `gta_sa.exe` (który jest wstrzymany). Rozmiar tego bloku jest wystarczający do przechowania pełnej ścieżki do `samp.dll`.
3. **Zapis ścieżki DLL:** Pełna ścieżka do pliku `samp.dll` jest zapisywana w tej nowo przydzielonej pamięci zdalnej za pomocą `WriteProcessMemory`.
4. **Tworzenie zdalnego wątku:** `CreateRemoteThread` jest wywoływane w celu utworzenia nowego `wątku` w procesie `gta_sa.exe`. Punktem wejścia tego nowego `wątku` jest adres `LoadLibraryW`, a argumentem, który otrzymuje, jest wskaźnik do ścieżki DLL, którą właśnie zapisaliśmy.
5. **Monitorowanie wstrzyknięcia:** Wykonanie zdalnego `wątku` jest monitorowane przez `WaitForSingleObject` przez okres zdefiniowany przez `Constants::DLL_INJECTION_TIMEOUT_MS`.
6. **Weryfikacja wyniku:** Kod wyjścia zdalnego `wątku` jest uzyskiwany za pomocą `GetExitCodeThread`. Wartość zwracana różna od zera wskazuje, że `LoadLibraryW` pomyślnie załadowało `samp.dll`.

> [!WARNING]
> W przypadku jakiejkolwiek awarii podczas wstrzykiwania `samp.dll`, wyświetlany jest specyficzny komunikat o błędzie (`error_utils.hpp`), proces wstrzykiwania jest przerywany, a zasoby są zwalniane.

### 7. Wstrzyknięcie biblioteki OMP (`omp-client.dll`) - Warunkowe

Jeśli określony typ wstrzyknięcia to `OMP`, kroki szczegółowo opisane w punkcie 6 są powtarzane dla `omp-client.dll`.

> [!TIP]
> Wstrzyknięcie `omp-client.dll` zawsze następuje po pomyślnym wstrzyknięciu `samp.dll`. Dzieje się tak, ponieważ klient Open Multiplayer opiera się na infrastrukturze dostarczanej przez `samp.dll`.

### 8. Aktywacja gry

Na koniec, jeśli wszystkie wstrzyknięcia zakończyły się pomyślnie, wywoływana jest metoda `process_info.Resume()`. To wywołanie wykonuje `ResumeThread` na głównym `wątku` `gta_sa.exe`. W tym momencie gra jest aktywowana i rozpoczyna normalne działanie, ale już z załadowanymi w pamięci bibliotekami DLL SA-MP/OMP i skonfigurowanymi parametrami połączenia, co pozwala na automatyczne połączenie z serwerem.

> [!WARNING]
> Jeśli wznowienie `wątku` gry się nie powiedzie, użytkownikowi prezentowany jest ostatni komunikat o błędzie.

## Diagnostyka błędów i awarii

Biblioteka jest skrupulatnie zaprojektowana, aby jasno komunikować wszelkie problemy, które mogą pojawić się podczas procesu inicjalizacji i wstrzykiwania. W każdym punkcie awarii, użytkownikowi prezentowany jest `MessageBox` ze szczegółowym opisem, często uzupełniony o komunikaty błędów systemu operacyjnego.

### Błędy walidacji danych wejściowych

Błędy te są wykrywane na początkowym etapie (`validation.hpp`), przed jakąkolwiek niskopoziomową interakcją z systemem, i wskazują na problemy z danymi dostarczonymi przez użytkownika lub z konfiguracją środowiska.

#### Nieprawidłowa nazwa użytkownika

- **Komunikat o błędzie (Przykład 1):** `"Pseudonim nie może być pusty. Proszę podać prawidłowy pseudonim."`
- **Komunikat o błędzie (Przykład 2):** `"Długość pseudonimu przekracza maksymalną dozwoloną długość 23 znaków. Proszę użyć krótszego pseudonimu."`
- **Przyczyna:** Podana nazwa użytkownika (`nickname`) jest pusta lub przekracza maksymalny limit 23 znaków dozwolony przez klientów SA-MP/OMP.
- **Rozwiązanie:** Użytkownik musi wprowadzić prawidłową nazwę użytkownika, która spełnia kryteria długości.

#### Nieprawidłowy port połączenia

- **Komunikat o błędzie (Przykład 1):** `"Nieprawidłowy format portu. Port musi być wartością numeryczną. Proszę podać prawidłową liczbę całkowitą dla portu."`
- **Komunikat o błędzie (Przykład 2):** `"Podany numer portu (70000) jest poza prawidłowym zakresem od 1 do 65535. Proszę podać prawidłowy port."`
- **Przyczyna:** Podana wartość dla portu nie jest liczbą całkowitą lub jest poza prawidłowym zakresem (1 do 65535).
- **Rozwiązanie:** Użytkownik musi podać prawidłowy numer portu mieszczący się w określonym zakresie.

#### Brak niezbędnych zasobów

- **Komunikat o błędzie (Przykład 1):** `"Nie znaleziono pliku wykonywalnego gry. Upewnij się, że 'gta_sa.exe' istnieje w podanej ścieżce: C:\Games\GTA San Andreas\gta_sa.exe"`
- **Komunikat o błędzie (Przykład 2):** `"Nie znaleziono biblioteki SA-MP. Upewnij się, że 'samp.dll' istnieje w podanej ścieżce: C:\Games\GTA San Andreas\samp.dll"`
- **Komunikat o błędzie (Przykład 3, dla OMP):** `"Nie znaleziono biblioteki OMP. Upewnij się, że 'omp-client.dll' istnieje w podanej ścieżce dla wstrzyknięcia OMP: C:\Games\GTA San Andreas\omp-client.dll"`
- **Przyczyna:** Jeden lub więcej kluczowych plików (`gta_sa.exe`, `samp.dll`, `omp-client.dll`) nie zostało znalezionych w podanym katalogu gry.
- **Rozwiązanie:** Sprawdź ścieżkę do folderu gry i upewnij się, że wszystkie niezbędne pliki są obecne i dostępne.

### Błędy w zarządzaniu procesem

Błędy te występują, gdy biblioteka próbuje uruchomić plik wykonywalny gry (`gta_sa.exe`).

#### Problem z uruchomieniem procesu gry

- **Komunikat o błędzie (Przykład):** `"Nie udało się utworzyć procesu gry. Upewnij się, że 'gta_sa.exe' nie jest uruchomiony i masz wystarczające uprawnienia do wykonania pliku. Błąd systemowy: Odmowa dostępu."`
- **Przyczyna:**
   - **Plik wykonywalny w użyciu:** `gta_sa.exe` może już być uruchomiony, lub istnieje jakaś blokada systemu operacyjnego, która uniemożliwia utworzenie nowej instancji.
   - **Niewystarczające uprawnienia:** Aplikacja może nie mieć odpowiednich uprawnień do uruchomienia `gta_sa.exe` lub do dostępu do pliku.
   - **Uszkodzony plik wykonywalny:** Chociaż podstawowa walidacja sprawdza istnienie pliku, może on być uszkodzony lub niedostępny.
- **Rozwiązanie:** Upewnij się, że żadna instancja `gta_sa.exe` nie jest aktywna. Spróbuj uruchomić swoją aplikację jako administrator. Sprawdź integralność pliku `gta_sa.exe`.

### Problemy z wstrzykiwaniem DLL

Są to najbardziej krytyczne i szczegółowe błędy, występujące podczas próby wstrzyknięcia `samp.dll` lub `omp-client.dll` do wstrzymanego procesu gry. Komunikaty o błędach zazwyczaj zaczynają się od `"Nie udało się wstrzyknąć <NAZWA_DLL>:\n"` i są po nich szczegółowy opis oraz kod błędu systemowego.

#### Nie można zlokalizować `LoadLibraryW`

- **Komunikat o błędzie (Część):** `"Nie udało się znaleźć adresu LoadLibraryW w kernel32.dll."`
- **Przyczyna:** Funkcja `LoadLibraryW`, fundamentalne API systemu Windows do dynamicznego ładowania bibliotek DLL, nie mogła zostać znaleziona w `kernel32.dll`. Jest to niezwykle rzadki problem niskiego poziomu, który wskazuje na możliwe uszkodzenie systemu operacyjnego lub bardzo nietypowe środowisko wykonawcze.
- **Rozwiązanie:** Ponowne uruchomienie systemu może rozwiązać problem. Jeśli problem będzie się powtarzał, może to wskazywać na poważniejszy problem z instalacją systemu Windows.

#### Błąd rezerwacji pamięci zdalnej

- **Komunikat o błędzie (Część):** `"Nie udało się przydzielić pamięci w procesie docelowym (VirtualAllocEx). Błąd systemowy: Za mało dostępnej pamięci masowej do przetworzenia tego polecenia."`
- **Przyczyna:** Biblioteka nie mogła przydzielić bloku pamięci w przestrzeni adresowej wirtualnej procesu `gta_sa.exe`.
   - **Uprawnienia:** Twoja aplikacja może nie mieć wystarczających uprawnień do modyfikowania przestrzeni pamięci innego procesu.
   - **Ochrona procesu:** Mechanizmy bezpieczeństwa systemu operacyjnego lub oprogramowanie anty-cheat mogą blokować alokację pamięci w zewnętrznych procesach.
- **Rozwiązanie:** Uruchom swoją aplikację jako administrator. Sprawdź, czy programy zabezpieczające (antywirus, anty-cheat) nie ingerują i, jeśli to możliwe, tymczasowo je wyłącz, aby przetestować.

#### Nie można zapisać danych w procesie

- **Komunikat o błędzie (Część):** `"Nie udało się zapisać ścieżki DLL do pamięci procesu (WriteProcessMemory). Błąd systemowy: Odmowa dostępu."`
- **Przyczyna:** Pamięć została przydzielona w procesie gry, ale biblioteka nie mogła zapisać ścieżki DLL w tym miejscu.
   - **Uprawnienia/Ochrona:** Podobnie jak w przypadku błędu alokacji pamięci, może to być problem z uprawnieniami do zapisu lub aktywną ochroną pamięci.
- **Rozwiązanie:** Zastosowanie mają te same rozwiązania, co w przypadku błędu alokacji pamięci.

#### Błąd tworzenia wątku wstrzykiwania

- **Komunikat o błędzie (Część):** `"Nie udało się utworzyć zdalnego wątku (CreateRemoteThread). Błąd systemowy: Parametr jest nieprawidłowy."`
- **Przyczyna:** API `CreateRemoteThread` nie powiodło się przy uruchamianiu nowego `wątku` w procesie `gta_sa.exe` w celu wywołania `LoadLibraryW`.
   - **Bezpieczeństwo:** Wiele systemów anty-cheat i zabezpieczeń systemu operacyjnego monitoruje i blokuje tworzenie zdalnych `wątków`, ponieważ jest to powszechna technika wstrzykiwania.
   - **Stan procesu:** Proces gry może być w niestabilnym stanie, który uniemożliwia tworzenie `wątków`.
- **Rozwiązanie:** Tymczasowo wyłącz oprogramowanie anty-cheat lub antywirus. Spróbuj uruchomić aplikację jako administrator.

#### Przekroczono limit czasu lub błąd podczas oczekiwania na wstrzyknięcie

- **Komunikat o błędzie (Część):** `"Przekroczono limit czasu lub błąd podczas oczekiwania na zdalny wątek (WaitForSingleObject). Błąd systemowy: Operacja oczekiwania przekroczyła limit czasu."`
- **Przyczyna:** Zdalny `wątek` (który wywołuje `LoadLibraryW`) nie zakończył swojego wykonania w ustalonym limicie czasu (10 sekund).
   - **Zawieszenie:** `LoadLibraryW` mogło się zawiesić, trwać zbyt długo lub zostać przechwycone/zablokowane.
- **Rozwiązanie:** Może to wskazywać, że biblioteka DLL ma problemy z załadowaniem lub coś ją blokuje. Sprawdzenie logów systemowych lub samego SA-MP/OMP (jeśli są dostępne) może dostarczyć więcej wskazówek.

#### Wewnętrzny błąd wstrzykiwania DLL

- **Komunikat o błędzie (Część):** `"Wywołanie LoadLibraryW w procesie docelowym nie powiodło się. Biblioteka DLL może być uszkodzona, brakować zależności lub być zablokowana przez oprogramowanie zabezpieczające."`
- **Przyczyna:** Zdalny `wątek` zakończył się, ale wartość zwracana przez `LoadLibraryW` wyniosła `0` (lub `NULL`), co wskazuje, że biblioteka DLL nie została pomyślnie załadowana.
   - **Uszkodzona/Nieistniejąca DLL:** Biblioteka DLL mogła zostać przeniesiona, usunięta lub uszkodzona po początkowej walidacji.
   - **Brakujące zależności:** `samp.dll` lub `omp-client.dll` mogą mieć zależności (inne biblioteki DLL), które nie są obecne w katalogu gry lub w `PATH` systemowym.
   - **Wewnętrzny błąd DLL:** Sama biblioteka DLL może mieć wewnętrzny błąd, który uniemożliwia jej załadowanie.
- **Rozwiązanie:** Sprawdź integralność plików `samp.dll`/`omp-client.dll`. Upewnij się, że wszystkie ich zależności są obecne.

### Problem z wznowieniem działania gry

Jest to ostatni możliwy punkt awarii w cyklu wstrzykiwania.

- **Komunikat o błędzie (Przykład):** `"Nie udało się wznowić wątku procesu gry: Nieprawidłowy uchwyt."`
- **Przyczyna:** API `ResumeThread` nie powiodło się przy ponownej aktywacji głównego `wątku` `gta_sa.exe`.
   - **Nieprawidłowy uchwyt:** `Handle` `wątku` mógł zostać unieważniony przez jakieś nieoczekiwane zdarzenie.
   - **Uprawnienia:** Aplikacja może nie mieć uprawnień do zmiany stanu `wątku`.
- **Rozwiązanie:** Spróbuj uruchomić aplikację jako administrator. Jeśli problem będzie się powtarzał, może to wskazywać na głębszy problem ze stabilnością systemu lub procesu gry.

## Licencja

Copyright © **SA-MP Programming Community**

To oprogramowanie jest licencjonowane na warunkach licencji MIT ("Licencja"); możesz korzystać z tego oprogramowania zgodnie z warunkami Licencji. Kopię Licencji można uzyskać pod adresem: [MIT License](https://opensource.org/licenses/MIT)

### Warunki użytkowania

#### 1. Przyznane uprawnienia

Niniejsza licencja bezpłatnie przyznaje każdej osobie otrzymującej kopię tego oprogramowania i powiązanych plików dokumentacji następujące prawa:
* Używanie, kopiowanie, modyfikowanie, łączenie, publikowanie, rozpowszechnianie, sublicencjonowanie i/lub sprzedaż kopii oprogramowania bez ograniczeń
* Zezwalanie osobom, którym oprogramowanie jest dostarczane, na to samo, pod warunkiem przestrzegania poniższych warunków

#### 2. Obowiązkowe warunki

Wszystkie kopie lub istotne części oprogramowania muszą zawierać:
* Powyższą informację o prawach autorskich
* Niniejsze zezwolenie
* Poniższe wyłączenie odpowiedzialności

#### 3. Prawa autorskie

Oprogramowanie i cała powiązana dokumentacja są chronione prawami autorskimi. **SA-MP Programming Community** zachowuje oryginalne prawa autorskie do oprogramowania.

#### 4. Wyłączenie gwarancji i ograniczenie odpowiedzialności

OPROGRAMOWANIE JEST DOSTARCZANE "TAK JAK JEST", BEZ JAKIEJKOLWIEK GWARANCJI, WYRAŹNEJ LUB DOROZUMIANEJ, W TYM MIĘDZY INNYMI GWARANCJI PRZYDATNOŚCI HANDLOWEJ, PRZYDATNOŚCI DO OKREŚLONEGO CELU I NIENARUSZANIA PRAW.

W ŻADNYM WYPADKU AUTORZY LUB POSIADACZE PRAW AUTORSKICH NIE PONOSZĄ ODPOWIEDZIALNOŚCI ZA JAKIEKOLWIEK ROSZCZENIA, SZKODY LUB INNE ZOBOWIĄZANIA, CZY TO W RAMACH DZIAŁAŃ UMOWNYCH, DELIKTOWYCH CZY INNYCH, WYNIKAJĄCYCH Z OPROGRAMOWANIA LUB ZWIĄZANYCH Z NIM LUB Z JEGO UŻYTKOWANIEM LUB INNYMI CZYNNOŚCIAMI W OPROGRAMOWANIU.

---

Szczegółowe informacje o licencji MIT można znaleźć pod adresem: https://opensource.org/licenses/MIT