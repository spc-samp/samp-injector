# SA-MP Injector C++

![License](https://img.shields.io/badge/License-MIT-yellow.svg?style=flat)
![C++17](https://img.shields.io/badge/C%2B%2B-17-blue.svg?style=flat&logo=cplusplus)
![Platform](https://img.shields.io/badge/Platform-Windows-0078D6.svg?style=flat&logo=windows)
[![SA-MP | OMP](https://img.shields.io/badge/Support-SA--MP%20%7C%20OMP-yellow)](https://github.com/spc-samp/samp-injector)
![Code Quality](https://img.shields.io/badge/Code%20Quality-High-brightgreen.svg?style=flat)

**SA-MP Injector C++** wykracza poza definicję prostego narzędzia do **wstrzykiwania DLL**. Jest to starannie zaprojektowana **biblioteka C++**, stworzona, aby dostarczyć solidne i kompleksowe rozwiązanie do programistycznego uruchamiania gry **Grand Theft Auto: San Andreas** (**GTA:SA**) w połączeniu z jej klientami wieloosobowymi, w szczególności **SA-MP (San Andreas Multiplayer)** oraz **OMP (Open Multiplayer)**. Jej głównym celem jest uproszczenie procesu uruchamiania gry, eliminując złożoność związaną z bezpośrednią manipulacją procesami systemu operacyjnego i przekazywaniem argumentów wiersza poleceń.

Zaprojektowana z myślą o zapewnieniu maksymalnej elastyczności i łatwej integracji, ta biblioteka `header-only` eliminuje potrzebę skomplikowanych wstępnych kompilacji, umożliwiając programistom bezpośrednie włączenie jej do swoich **projektów C++**. Nie tylko zarządza **podstawowym wstrzykiwaniem DLL** klienta wieloosobowego (`samp.dll` lub `omp-client.dll`), ale także inteligentnie obsługuje wszystkie kluczowe parametry połączenia (**pseudonim**, **adres IP**, **port** i **hasło**), symulując natywne uruchamianie za pomocą wewnętrznych zasobów **Windows API**.

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
  - [Podstawowe koncepcje i motywacja](#podstawowe-koncepcje-i-motywacja)
    - [Dlaczego wstrzykiwać DLL?](#dlaczego-wstrzykiwać-dll)
    - [SA-MP i OMP: Różnice i podobieństwa](#sa-mp-i-omp-różnice-i-podobieństwa)
  - [Architektura wewnętrzna biblioteki: Głębokie zanurzenie](#architektura-wewnętrzna-biblioteki-głębokie-zanurzenie)
    - [`constants.hpp`](#constantshpp)
    - [`types.hpp`](#typeshpp)
    - [`string_utils.hpp`](#string_utilshpp)
    - [`error_utils.hpp`](#error_utilshpp)
    - [`resource_handle.hpp`](#resource_handlehpp)
    - [`validation.hpp`](#validationhpp)
    - [`process.hpp`](#processhpp)
    - [`injector_core.hpp`](#injector_corehpp)
    - [`injector.hpp`](#injectorhpp)
  - [Wszechstronne przykłady użycia](#wszechstronne-przykłady-użycia)
    - [1. Przygotowanie środowiska programistycznego](#1-przygotowanie-środowiska-programistycznego)
    - [2. Podstawowy scenariusz: Łączenie z serwerem SA-MP](#2-podstawowy-scenariusz-łączenie-z-serwerem-sa-mp)
    - [3. Zaawansowany scenariusz: Łączenie z serwerem OMP](#3-zaawansowany-scenariusz-łączenie-z-serwerem-omp)
  - [Obsługa typowych błędów i komunikatów](#obsługa-typowych-błędów-i-komunikatów)
    - [1. Nieprawidłowy typ wstrzykiwania](#1-nieprawidłowy-typ-wstrzykiwania)
    - [2. Nieprawidłowy port serwera (format lub zakres)](#2-nieprawidłowy-port-serwera-format-lub-zakres)
      - [2.1. Nienumeryczny format portu](#21-nienumeryczny-format-portu)
      - [2.2. Port poza prawidłowym zakresem](#22-port-poza-prawidłowym-zakresem)
    - [3. Nieprawidłowy pseudonim (pusty lub za długi)](#3-nieprawidłowy-pseudonim-pusty-lub-za-długi)
      - [3.1. Pusty pseudonim](#31-pusty-pseudonim)
      - [3.2. Za długi pseudonim](#32-za-długi-pseudonim)
    - [4. Nie znaleziono plików gry lub DLL](#4-nie-znaleziono-plików-gry-lub-dll)
      - [4.1. Nie znaleziono pliku wykonywalnego gry (`gta_sa.exe`)](#41-nie-znaleziono-pliku-wykonywalnego-gry-gta_saexe)
      - [4.2. Nie znaleziono biblioteki SA-MP (`samp.dll`)](#42-nie-znaleziono-biblioteki-sa-mp-sampdll)
      - [4.3. Nie znaleziono biblioteki OMP (`omp-client.dll`) (tylko dla wstrzykiwania OMP)](#43-nie-znaleziono-biblioteki-omp-omp-clientdll-tylko-dla-wstrzykiwania-omp)
    - [5. Niepowodzenie w tworzeniu procesu gry](#5-niepowodzenie-w-tworzeniu-procesu-gry)
    - [6. Niepowodzenie w alokacji pamięci w procesie docelowym](#6-niepowodzenie-w-alokacji-pamięci-w-procesie-docelowym)
    - [7. Niepowodzenie w zapisie ścieżki DLL do pamięci procesu](#7-niepowodzenie-w-zapisie-ścieżki-dll-do-pamięci-procesu)
    - [8. Niepowodzenie w znalezieniu kluczowych funkcji systemowych](#8-niepowodzenie-w-znalezieniu-kluczowych-funkcji-systemowych)
      - [8.1. Nie znaleziono `kernel32.dll`](#81-nie-znaleziono-kernel32dll)
      - [8.2. Nie znaleziono `LoadLibraryA`](#82-nie-znaleziono-loadlibrarya)
    - [9. Niepowodzenie w utworzeniu zdalnego wątku do iniekcji](#9-niepowodzenie-w-utworzeniu-zdalnego-wątku-do-iniekcji)
    - [10. Przekroczenie limitu czasu lub niepowodzenie w zakończeniu iniekcji](#10-przekroczenie-limitu-czasu-lub-niepowodzenie-w-zakończeniu-iniekcji)
    - [11. Niepowodzenie w wznowieniu wątku procesu gry](#11-niepowodzenie-w-wznowieniu-wątku-procesu-gry)
  - [Licencja](#licencja)
    - [Warunki użytkowania](#warunki-użytkowania)
      - [1. Przyznane uprawnienia](#1-przyznane-uprawnienia)
      - [2. Obowiązkowe warunki](#2-obowiązkowe-warunki)
      - [3. Prawa autorskie](#3-prawa-autorskie)
      - [4. Wyłączenie gwarancji i ograniczenie odpowiedzialności](#4-wyłączenie-gwarancji-i-ograniczenie-odpowiedzialności)

## Podstawowe koncepcje i motywacja

### Dlaczego wstrzykiwać DLL?

> [!NOTE]
> **Wstrzykiwanie DLL (Dynamic Link Library)** to metoda stosowana w systemach operacyjnych **Microsoft Windows**, która umożliwia wykonywanie kodu w przestrzeni pamięci innego działającego procesu. Jest to potężna technika z wieloma legalnymi zastosowaniami, od debugowania i monitorowania programów po modyfikację zachowania aplikacji w celu rozszerzenia ich funkcjonalności.

W kontekście gier takich jak **GTA San Andreas**, które nie zostały pierwotnie zaprojektowane z wbudowaną funkcjonalnością wieloosobową, **wstrzykiwanie DLL** stanowi podstawę dla istnienia klientów wieloosobowych, takich jak **SA-MP** i **OMP**. Ci klienci są implementowani jako **DLL**, które po wstrzyknięciu do procesu `gta_sa.exe` przejmują kontrolę, przechwytują funkcje gry i nawiązują komunikację z serwerami wieloosobowymi.

Zamiast polegać na zewnętrznym launcherze lub bezpośredniej modyfikacji pliku wykonywalnego gry, **wstrzykiwanie DLL** umożliwia bardziej elastyczne i programowalne uruchamianie, szczególnie przydatne w środowiskach, gdzie chce się zautomatyzować proces łączenia z określonymi serwerami z wcześniej zdefiniowanymi ustawieniami.

### SA-MP i OMP: Różnice i podobieństwa

**SA-MP** i **OMP** to dwie główne platformy wieloosobowe dla **GTA San Andreas**. Obie działają jako modyfikacje podstawowej gry, przekształcając ją w środowisko online masowo wieloosobowe.

- **SA-MP (San Andreas Multiplayer)**: Oryginalny i najbardziej ugruntowany klient, szeroko stosowany przez wiele lat. Jego architektura wymaga `samp.dll` do działania.
- **OMP (Open Multiplayer)**: Projekt open-source, często postrzegany jako następca lub bardziej nowoczesna alternatywa dla **SA-MP**, oferujący poprawę wydajności, stabilności i dodatkowe funkcje. Wymaga `omp-client.dll`.

Chociaż działają w podobny sposób (**wstrzykując DLL** do procesu **GTA:SA**), biblioteka **SA-MP Injector C++** została starannie zaprojektowana, aby obsługiwać **obie DLL**, uwzględniając różnice w nazwach plików i umożliwiając programistom wybór żądanego klienta wieloosobowego za pomocą parametru konfiguracyjnego. Zapewnia to, że biblioteka może być używana z szeroką gamą serwerów i projektów opartych na każdej z platform.

## Architektura wewnętrzna biblioteki: Głębokie zanurzenie

**SA-MP Injector C++** przyjmuje modułowe i zorientowane obiektowo podejście (tam, gdzie jest to stosowne) do zarządzania złożonością procesu wstrzykiwania. Każdy plik nagłówkowy jest wyspecjalizowanym modułem, odpowiedzialnym za określony fragment ogólnej funkcjonalności, promując przejrzystość kodu, łatwość utrzymania i rozszerzalność.

### `constants.hpp`

Ten plik stanowi podstawę wszystkich stałych konfiguracji biblioteki. Definiuje przestrzeń nazw `Constants`, aby kapsułkować wszystkie literały, zapewniając brak zanieczyszczenia globalnego zakresu. Użycie `inline constexpr` jest tutaj kluczowe: `constexpr` wskazuje, że wartości są obliczane w czasie kompilacji, optymalizując wydajność i zapewniając niezmienność, natomiast `inline` zapobiega problemom z wielokrotną definicją przy włączaniu pliku w wielu jednostkach kompilacji.

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
    inline constexpr const char* LOAD_LIBRARY_FUNC = "LoadLibraryA"; // 'A' dla wersji ANSI/8-bit
    
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
    inline constexpr DWORD DLL_INJECTION_TIMEOUT_MS = 10000; // 10 sekund
    
    // Memory allocation flags for VirtualAllocEx
    inline constexpr DWORD MEMORY_ALLOCATION_TYPE = MEM_COMMIT | MEM_RESERVE;
    inline constexpr DWORD MEMORY_PROTECTION = PAGE_READWRITE; // Potrzebne do zapisu ścieżki DLL
}
```

> [!TIP]
> Użycie `wchar_t` dla nazw plików i tytułów komunikatów o błędach jest zalecaną praktyką w **rozwoju dla Windows**. Zapewnia to kompatybilność ze wszystkimi językami i zestawami znaków, szczególnie przydatne dla ścieżek plików, które mogą zawierać **znaki Unicode**. Dla **API**, które oczekują `char` (jak `LoadLibraryA`), konwersja jest przeprowadzana jawnie w `string_utils.hpp`.

### `types.hpp`

Zwięzły, ale kluczowy moduł do definiowania wyliczenia, które kategoryzuje obsługiwane typy wstrzykiwania. Poprawia to czytelność i bezpieczeństwo typów kodu, zapobiegając błędom związanym z ciągami znaków lub magicznymi liczbami.

```cpp
#pragma once

namespace Types {
    // Wyliczenia dla obsługiwanych typów wstrzykiwania
    enum class Inject_Type {
        SAMP, // San Andreas Multiplayer
        OMP // Open Multiplayer
    };
}
```

### `string_utils.hpp`

Operowanie z **API Windows** często wymaga konwersji między różnymi kodowaniami ciągów znaków. Ten plik dostarcza kluczową funkcję narzędziową do konwersji ciągów znaków z **szerokich znaków** (`std::wstring_view`, używanych w danych wejściowych biblioteki) na ciągi **ANSI/8-bit** (`std::string`), które są wymagane dla funkcji **WinAPI**, które operują na `char*` (takich jak `CreateProcessA` lub `GetProcAddress`).

```cpp
#pragma once

#include <string>
#include <string_view>
#include <windows.h> // Potrzebne dla WideCharToMultiByte

namespace Utils {
    inline std::string Wide_To_Local_8Bit(std::wstring_view wstr) {
        if (wstr.empty())
            return "";
        
        // Określa rozmiar potrzebny dla bufora wynikowego ciągu w char
        int size = WideCharToMultiByte(CP_ACP, // Strona kodowa ANSI (zależna od lokalnego systemu)
            0, // Brak dodatkowych flag
            wstr.data(), 
            static_cast<int>(wstr.size()), 
            nullptr, // Oblicza rozmiar, nie wypełnia bufora
            0, // Rozmiar 0, tylko do obliczeń
            nullptr, // Domyślny znak dla znaków nieprzetwarzalnych
            nullptr); // Wskaźnik na bool wskazujący, czy użyto domyślnego znaku

        if (size <= 0) // Zwraca pusty ciąg w przypadku błędu lub nieprawidłowego rozmiaru
            return "";

        std::string result(size, 0); // Alokuje ciąg o określonym rozmiarze
        // Wykonuje rzeczywistą konwersję, wypełniając bufor 'result'
        WideCharToMultiByte(CP_ACP, 
            0, 
            wstr.data(), 
            static_cast<int>(wstr.size()), 
            result.data(), // Bufor docelowy
            size, // Rozmiar bufora docelowego
            nullptr, 
            nullptr);

        return result;
    }
}
```

> [!IMPORTANT]
> `CP_ACP` **(strona kodowa ANSI)** używana w `WideCharToMultiByte` to domyślna strona kodowa systemu **Windows**. Oznacza to, że konwersja może się różnić w zależności od ustawień językowych systemu użytkownika. Dla większości przypadków użycia nazw plików i argumentów wiersza poleceń w **SA-MP**/**OMP** (które historycznie dobrze radzą sobie z ciągami **ANSI**), to podejście jest wystarczające. Jednak w scenariuszach wymagających pełnej kompatybilności z **Unicode** z systemami zewnętrznymi lub globalnymi danymi wejściowymi, potrzebne byłyby konwersje na **UTF-8** (`CP_UTF8`) lub inne strony kodowe. Dla zakresu tego projektu `CP_ACP` jest standardem funkcjonalnym.

### `error_utils.hpp`

Podstawowy komponent dla użyteczności biblioteki, odpowiedzialny za dostarczanie wyraźnego **feedbacku** użytkownikowi w przypadku niepowodzenia. Centralizuje logikę uzyskiwania komunikatów o błędach systemu i wyświetlania okien dialogowych.

```cpp
#pragma once

#include <string>
#include <string_view>
#include <windows.h> // Dla FormatMessageW i MessageBoxW
//
#include "types.hpp"
#include "constants.hpp"

namespace Utils {
    // Zwraca komunikat o błędzie systemu Windows dla określonego kodu błędu
    inline std::wstring Get_System_Error_Message(DWORD error_code) {
        wchar_t buffer[512] = {0}; // Bufor na komunikat
        // FormatMessageW wypełnia bufor opisem błędu systemowego
        DWORD result = FormatMessageW(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, 
            nullptr, // Źródło komunikatu (z systemu)
            error_code, 
            0, // Język (użyj domyślnego)
            buffer, 
            512, // Rozmiar bufora
            nullptr);
        
        // Jeśli funkcja zakończyła się powodzeniem, zwraca ciąg z bufora; w przeciwnym razie ogólny komunikat
        return result ? std::wstring(buffer) : L"Unknown error (Code: " + std::to_wstring(error_code) + L")";
    }

    // Wyświetla okno dialogowe błędu użytkownikowi
    inline void Show_Error(std::wstring_view message, Types::Inject_Type injectType) {
        // Wybiera tytuł okna dialogowego na podstawie typu wstrzykiwania
        std::wstring title = (injectType == Types::Inject_Type::SAMP) ? Constants::ERROR_TITLE_SAMP : Constants::ERROR_TITLE_OMP;
        MessageBoxW(nullptr, // Uchwyt okna nadrzędnego (nullptr dla pulpitu)
            message.data(), 
            title.c_str(), 
            MB_OK | MB_ICONERROR); // Przycisk OK i ikona błędu
    }
}
```

> [!NOTE]
> Funkcja `FormatMessageW` to potężne **API Windows**, które pobiera tekstowy opis kodu błędu systemowego. Obsługuje lokalizację i dostarcza jasne komunikaty, które są kluczowe dla skutecznej **diagnostyki**, przekształcając `DWORD`, taki jak `ERROR_FILE_NOT_FOUND` (2), w `L"System nie może znaleźć określonego pliku."`.

### `resource_handle.hpp`

Bezpieczne zarządzanie zasobami (takimi jak `HANDLE` w **Windows**) jest kluczowe dla uniknięcia wycieków zasobów i niezdefiniowanego zachowania. Ten plik definiuje `UniqueResource` z użyciem `std::unique_ptr` i niestandardowej funkcji dla `CloseHandle`. To stosuje zasadę **RAII (Resource Acquisition Is Initialization)**, zapewniając, że `HANDLE` są automatycznie zamykane, gdy ich **opakowania** opuszczają zakres, nawet w przypadku wyjątków.

```cpp
#pragma once

#include <memory> // Dla std::unique_ptr
#include <functional> // Dla std::function
#include <windows.h> // Dla HANDLE i CloseHandle

namespace Utils {
    // Alias typu dla std::unique_ptr, który zarządza HANDLE (lub wskaźnikiem) z niestandardowym zwalniaczem
    // T: Typ zasobu do zarządzania (np. HANDLE, LPVOID)
    // Deleter: Klasa lub lambda, która wie, jak zwolnić zasób
    template<typename T, typename Deleter>
    using UniqueResource = std::unique_ptr<std::remove_pointer_t<T>, Deleter>;

    // Funkcja pomocnicza do tworzenia instancji UniqueResource dla HANDLE
    // Zakłada, że T to typ uchwytu i używa CloseHandle jako zwalniacza.
    template<typename T>
    inline auto Make_Unique_Handle(T handle) {
        return UniqueResource<T, std::function<void(T)>>(handle, [](T h) {
            // Warunek, aby zapewnić, że uchwyt jest ważny przed próbą jego zamknięcia
            // 0 i INVALID_HANDLE_VALUE są uważane za nieważne dla większości uchwytów
            if (h && h != INVALID_HANDLE_VALUE)
                CloseHandle(h); // Zwalnia HANDLE systemu operacyjnego
        });
    }
}
```

> [!IMPORTANT]
> Użycie `UniqueResource` jest demonstracją dobrych praktyk **nowoczesnego C++** i bezpiecznego programowania w **Windows**. Znacząco upraszcza zarządzanie cyklem życia **uchwytów**, które, jeśli nie zostaną poprawnie zamknięte, mogą prowadzić do wycieków pamięci lub zasobów **kernela**, wpływając na stabilność systemu w dłuższej perspektywie.

### `validation.hpp`

Solidność wstrzykiwania zaczyna się od walidacji danych wejściowych użytkownika i weryfikacji zależności plików. Ten moduł zawiera funkcje, które zapewniają, że wszystkie warunki wstępne i parametry są poprawne przed próbą rozpoczęcia procesu wstrzykiwania, zapobiegając bardziej skomplikowanym błędom w dalszej części.

```cpp
#pragma once

#include <string>
#include <string_view>
#include <filesystem> // Dla std::filesystem::exists
//
#include "constants.hpp"
#include "types.hpp"
#include "string_utils.hpp" // Dla Wide_To_Local_8Bit
#include "error_utils.hpp" // Dla Show_Error

namespace Utils {
    // Sprawdza, czy ciąg portu jest prawidłową liczbą i mieści się w dozwolonym zakresie
    inline bool Validate_Port(std::wstring_view port_str, std::wstring& error_message) {
        try {
            // Próbuje skonwertować ciąg szerokich znaków na std::string, a następnie na int
            int port_num = std::stoi(Wide_To_Local_8Bit(port_str));

            // Sprawdza, czy port mieści się w prawidłowym zakresie (1-65535)
            if (port_num < Constants::MIN_PORT || port_num > Constants::MAX_PORT)
                return (error_message = L"Określony numer portu (" + std::wstring(port_str) + 
                L") znajduje się poza prawidłowym zakresem od " + std::to_wstring(Constants::MIN_PORT) + 
                L" do " + std::to_wstring(Constants::MAX_PORT) + 
                L". Proszę podać prawidłowy port.", false);

            return true;
        }
        catch (...) { // Przechwytuje dowolny wyjątek (np. std::invalid_argument dla nienumerycznych)
            return (error_message = L"Nieprawidłowy format portu. Port musi być wartością liczbową. Proszę podać prawidłową liczbę całkowitą dla portu.", false);
        }
    }

    // Sprawdza pseudonim, weryfikując, czy nie jest pusty i czy jego długość jest akceptowalna
    inline bool Validate_Nickname(std::wstring_view nickname_str, std::wstring& error_message) {
        if (nickname_str.empty())
            return (error_message = L"Pseudonim nie może być pusty. Proszę podać prawidłowy pseudonim.", false);
        
        if (nickname_str.size() > Constants::MAX_NICKNAME_LENGTH)
            return (error_message = L"Długość pseudonimu przekracza maksymalną dozwoloną liczbę " + 
                std::to_wstring(Constants::MAX_NICKNAME_LENGTH) + 
                L" znaków. Proszę użyć krótszego pseudonimu.", false);

        return true;
    }

    // Sprawdza istnienie kluczowych plików (gta_sa.exe, samp.dll, omp-client.dll)
    inline bool Validate_Files(const std::filesystem::path& game_path, 
        const std::filesystem::path& samp_DLL_path, 
        const std::filesystem::path& omp_DLL_path, 
        Types::Inject_Type inject_type) {
        std::wstring error_message_local; // Używamy zmiennej lokalnej przed przekazaniem do Show_Error
        
        // Sprawdza istnienie pliku wykonywalnego gry
        if (!std::filesystem::exists(game_path)) {
            error_message_local = L"Nie znaleziono pliku wykonywalnego gry. Upewnij się, że 'gta_sa.exe' istnieje w określonej ścieżce: " + game_path.wstring();
            Show_Error(error_message_local, inject_type);
            return false;
        }

        // Sprawdza istnienie samp.dll (niezbędne dla obu typów wstrzykiwania)
        if (!std::filesystem::exists(samp_DLL_path)) {
            error_message_local = L"Nie znaleziono biblioteki SA-MP. Upewnij się, że 'samp.dll' istnieje w określonej ścieżce: " + samp_DLL_path.wstring();
            Show_Error(error_message_local, inject_type);

            return false;
        }

        // Jeśli typem wstrzykiwania jest OMP, sprawdza istnienie omp-client.dll
        if (inject_type == Types::Inject_Type::OMP && !std::filesystem::exists(omp_DLL_path)) {
            error_message_local = L"Nie znaleziono biblioteki OMP. Upewnij się, że 'omp-client.dll' istnieje w określonej ścieżce dla wstrzykiwania OMP: " + omp_DLL_path.wstring();
            Show_Error(error_message_local, inject_type);

            return false;
        }

        return true; // Wszystkie wymagane pliki zostały znalezione
    }
}
```

> [!NOTE]
> Wykorzystanie `std::filesystem` to nowoczesny dodatek do **C++17**, który oferuje potężny i niezależny od platformy sposób interakcji z systemem plików. Dla tego projektu w **Windows**, upraszcza obsługę ścieżek i sprawdzanie istnienia plików w porównaniu do starszych **API** **WinAPI**.
>
> Upewnij się, że twój kompilator obsługuje **C++17** dla użycia `std::filesystem`. Musisz skonfigurować swój projekt, aby używał standardu **C++17** (`/std:c++17` w **Visual Studio**).

### `process.hpp`

Jest to główny moduł odpowiedzialny za bezpośrednią interakcję z niskopoziomowymi **API** **Windows** do manipulacji procesami. Kapsułkuje kluczowe operacje tworzenia procesu i **wstrzykiwania DLL**, obsługując **uchwyty**, **pamięć** i **wątki**.

```cpp
#pragma once

#include <string_view>
#include <optional> // Dla std::optional
#include <functional> // Dla std::function (używane w UniqueResource)
#include <windows.h> // API Windows
#include <memory> // Dla std::unique_ptr
#include <vector> // Dla std::vector (bufor argumentów)
//
#include "resource_handle.hpp" // Nasz wrapper dla HANDLE
#include "error_utils.hpp" // Dla Get_System_Error_Message i Show_Error
#include "constants.hpp" // Globalne stałe
#include "types.hpp" // Typy wstrzykiwania

class Process {
    public:
        // Konstruktory/Destruktory i operatory przypisania
        // Jawnie domyślne i usunięte, aby zapewnić semantykę wartości i tylko przenoszenie.
        Process() = default;
        Process(const Process&) = delete; // Bez kopiowania
        Process& operator=(const Process&) = delete; // Bez przypisania kopiowania
        Process(Process&&) = default; // Semantyka przenoszenia
        Process& operator=(Process&&) = default; // Przypisanie przenoszenia
        ~Process() = default;

        // Struktura do przechowywania uchwytów procesu i wątku, zarządzanych przez UniqueResource
        struct Process_Info {
            Utils::UniqueResource<HANDLE, std::function<void(HANDLE)>> process_handle;
            Utils::UniqueResource<HANDLE, std::function<void(HANDLE)>> thread_handle;
        };

        // Tworzy proces gry GTA:SA w stanie zawieszonym
        std::optional<Process_Info> Create_Game_Process(std::string_view game_path, std::string_view command_args, std::string_view working_dir) {
            STARTUPINFOA startup_info{}; // Struktura dla informacji o uruchamianiu procesu
            startup_info.cb = sizeof(STARTUPINFOA); // Określa rozmiar struktury

            PROCESS_INFORMATION process_info{}; // Struktura, która otrzyma informacje o nowym procesie

            // Tworzy zmienny bufor dla argumentów wiersza poleceń.
            // CreateProcessA modyfikuje bufor wiersza poleceń, więc bezpośrednie std::string_view nie działa.
            std::vector<char> args_buffer(command_args.size() + 1); // +1 dla terminatora null

            if (!command_args.empty()) {
                std::memcpy(args_buffer.data(), command_args.data(), command_args.size());
                args_buffer[command_args.size()] = '\0'; // Zapewnia terminator null
            }

            // Tworzy proces
            bool success = CreateProcessA(game_path.data(), // Nazwa modułu wykonywalnego
                args_buffer.empty() ? nullptr : args_buffer.data(), // Argumenty wiersza poleceń
                nullptr, // Atrybuty bezpieczeństwa procesu
                nullptr, // Atrybuty bezpieczeństwa wątku
                FALSE, // Nie dziedzicz uchwytów
                Constants::PROCESS_CREATION_FLAGS, // CREATE_SUSPENDED | DETACHED_PROCESS
                nullptr, // Środowisko nowego procesu
                working_dir.empty() ? nullptr : working_dir.data(), // Katalog roboczy
                &startup_info, // Informacje o uruchamianiu
                &process_info); // Informacje o utworzonym procesie

            if (!success) {
                // Jeśli nie powiodło się, pobiera i wyświetla komunikat o błędzie systemowym
                std::wstring error_msg = Utils::Get_System_Error_Message(GetLastError());
                Utils::Show_Error(L"Nie udało się utworzyć procesu gry. Upewnij się, że 'gta_sa.exe' nie jest uruchomiony i masz wystarczające uprawnienia do wykonania pliku. Błąd systemowy: " + error_msg, Types::Inject_Type::SAMP); // Używa SAMP jako domyślnego dla tytułu
                
                return std::nullopt; // Zwraca pusty optional
            }

            Process_Info result;
            // Przechowuje uchwyty procesu i wątku w UniqueResource dla automatycznego zarządzania
            result.process_handle = Utils::Make_Unique_Handle(process_info.hProcess);
            result.thread_handle = Utils::Make_Unique_Handle(process_info.hThread);

            return result; // Zwraca strukturę z zarządzanymi uchwytami
        }

        // Wstrzykuje DLL do zdalnego procesu
        bool Inject_DLL(HANDLE process, std::string_view DLL_path, std::wstring& error_message) {
            // Alokuje pamięć w zdalnym procesie dla ścieżki DLL
            LPVOID remote_memory = VirtualAllocEx(process, // Uchwyt procesu docelowego
            nullptr, // Preferowany adres (nullptr, aby system wybrał)
            DLL_path.size() + 1, // Rozmiar ścieżki + terminator null
            Constants::MEMORY_ALLOCATION_TYPE, // MEM_COMMIT | MEM_RESERVE
            Constants::MEMORY_PROTECTION); // PAGE_READWRITE

            if (!remote_memory)
                return (error_message = L"Nie udało się zaalokować pamięci w procesie docelowym. Może to być spowodowane niewystarczającymi uprawnieniami lub mechanizmami ochrony procesu.", false);

            // Zarządzanie zasobem dla pamięci zaalokowanej zdalnie.
            // Zostanie automatycznie zwolnione po opuszczeniu zakresu.
            auto memory_guard = Utils::UniqueResource<LPVOID, std::function<void(LPVOID)>>(remote_memory, 
                [process](LPVOID ptr) { // Lambda jako zwalniacz
                    if (ptr)
                        VirtualFreeEx(process, ptr, 0, MEM_RELEASE); // Zwalnia zaalokowaną pamięć
                }
            );

            // Zapisuje ścieżkę DLL do zaalokowanej zdalnie pamięci
            if (!WriteProcessMemory(process, remote_memory, DLL_path.data(), DLL_path.size() + 1, nullptr))
                return (error_message = L"Nie udało się zapisać ścieżki DLL do pamięci procesu docelowego. Sprawdź uprawnienia procesu i upewnij się, że ścieżka DLL jest dostępna.", false);

            // Pobiera uchwyt dla kernel32.dll (który jest załadowany w procesie wstrzykującym)
            HMODULE kernel32 = GetModuleHandleA(Constants::KERNEL32_DLL);
            
            if (!kernel32)
                return (error_message = L"Nie udało się uzyskać uchwytu do kernel32.dll. Jest to kluczowa biblioteka systemowa, a ten błąd wskazuje na poważny problem systemowy.", false);

            // Pobiera adres funkcji LoadLibraryA w kernel32.dll.
            // Ten adres jest spójny między procesami w tym samym systemie operacyjnym i jest kluczem do wstrzykiwania.
            LPVOID load_library_addr = reinterpret_cast<LPVOID>(GetProcAddress(kernel32, Constants::LOAD_LIBRARY_FUNC));

            if (!load_library_addr)
                return (error_message = L"Nie udało się znaleźć adresu funkcji LoadLibraryA w kernel32.dll. Jest to kluczowe dla wstrzykiwania DLL.", false);

            // Tworzy zdalny wątek w procesie docelowym do wykonania LoadLibraryA
            // Argumentem dla LoadLibraryA będzie zdalny adres ścieżki DLL
            HANDLE remote_thread = CreateRemoteThread(process, // Uchwyt procesu docelowego
                nullptr, // Atrybuty bezpieczeństwa wątku
                0, // Rozmiar stosu (0 dla domyślnego)
                reinterpret_cast<LPTHREAD_START_ROUTINE>(load_library_addr), // Adres LoadLibraryA
                remote_memory, // Argument dla LoadLibraryA (ścieżka DLL)
                0, // Flag tworzenia (0 dla natychmiastowego startu)
                nullptr); // ID wątku (nullptr, aby nie zwracać)

            if (!remote_thread)
                return (error_message = L"Nie udało się utworzyć zdalnego wątku w procesie docelowym do wykonania wstrzykiwania DLL. Może to być spowodowane ograniczeniami bezpieczeństwa lub stanem procesu. Błąd systemowy: " + Utils::Get_System_Error_Message(GetLastError()), false);

            // Zarządzanie zasobem dla uchwytu zdalnego wątku
            auto thread_guard = Utils::Make_Unique_Handle(remote_thread);

            // Czeka na zakończenie zdalnego wątku (wstrzykiwanie DLL) lub przekroczenie limitu czasu
            DWORD wait_result = WaitForSingleObject(remote_thread, Constants::DLL_INJECTION_TIMEOUT_MS);

            if (wait_result != WAIT_OBJECT_0) {
                return (error_message = L"Przekroczenie limitu czasu lub błąd podczas oczekiwania na zakończenie wstrzykiwania DLL. Błąd systemowy: " + Utils::Get_System_Error_Message(GetLastError()), false);

            // Pobiera kod wyjścia zdalnego wątku.
            // Dla LoadLibraryA kod wyjścia 0 oznacza niepowodzenie (nie udało się załadować DLL).
            DWORD exit_code = 0;

            if (!GetExitCodeThread(remote_thread, &exit_code) || exit_code == 0)
                return (error_message = L"Wstrzykiwanie DLL nie powiodło się lub zwróciło błąd. Wywołanie LoadLibrary mogło się nie powieść w procesie docelowym.", false);

            return true; // Wstrzykiwanie zakończone sukcesem
        }
};
```

> [!NOTE]
> Moduł `process.hpp` demonstruje solidny i bezpieczny projekt. Funkcja `Create_Game_Process` zwraca `std::optional<Process_Info>`. Pozwala to funkcji sygnalizować niepowodzenia w tworzeniu procesu w sposób wyraźny i elegancki (zwracając `std::nullopt`) bez uciekania się do wyjątków lub niejednoznacznych kodów błędów w jej głównym zwrocie.
>
> Co ważniejsze, struktura `Process_Info` używa `Utils::UniqueResource<HANDLE, std::function<void(HANDLE)>>` do kapsułkowania **uchwytów** procesu i **wątku**. Jest to przykład wzorca **RAII (Resource Acquisition Is Initialization)**, który gwarantuje, że uchwyty systemu operacyjnego (takie jak `hProcess` i `hThread`) są automatycznie zamykane przez `CloseHandle`, gdy obiekt `Process_Info` opuszcza zakres. Eliminuje to wycieki **uchwytów**, które są powszechnym źródłem niestabilności i nadmiernego zużycia zasobów w **aplikacjach Windows** działających przez dłuższy czas.
>
> Podobnie, w funkcji `Inject_DLL`, `UniqueResource` jest używany do zarządzania pamięcią zaalokowaną zdalnie (`VirtualAllocEx`), zapewniając, że zostanie ona zwolniona (`VirtualFreeEx`) zaraz po tym, jak przestanie być potrzebna lub w przypadku niepowodzenia. To rygorystyczne zarządzanie zasobami znacząco przyczynia się do niezawodności i stabilności **SA-MP Injector C++**.

### `injector_core.hpp`

To klasa orkiestrująca, która łączy wszystkie funkcjonalności poprzednich modułów. Koordynuje walidację, budowanie argumentów wiersza poleceń, tworzenie procesu i wywołania **wstrzykiwania DLL**.

```cpp
#pragma once

#include <string_view>
#include <sstream> // Do budowania ciągów z stringstream
#include <filesystem> // Do manipulacji ścieżkami
//
#include "process.hpp" // Funkcje tworzenia/wstrzykiwania procesu
#include "validation.hpp" // Funkcje walidacji danych wejściowych
#include "string_utils.hpp" // Funkcje konwersji ciągów
#include "error_utils.hpp" // Funkcje obsługi błędów
#include "constants.hpp" // Stałe biblioteki
#include "types.hpp" // Typy wstrzykiwania

namespace Injector {
    class Injector_Core {
        public:
            // Konstruktory/Destruktory dla semantyki przenoszenia
            Injector_Core() = default;
            Injector_Core(const Injector_Core&) = delete; // Wyłącza kopiowanie
            Injector_Core& operator=(const Injector_Core&) = delete; // Wyłącza przypisanie kopiowania
            Injector_Core(Injector_Core&&) = default; // Włącza przenoszenie
            Injector_Core& operator=(Injector_Core&&) = default; // Włącza przypisanie przenoszenia
            ~Injector_Core() = default;

            // Główna funkcja orkiestrująca uruchamianie i wstrzykiwanie gry
            bool Initialize_Game(Types::Inject_Type inject_type, std::wstring_view folder, 
                std::wstring_view nickname, 
                std::wstring_view ip, 
                std::wstring_view port, 
                std::wstring_view password) {
                namespace fs = std::filesystem; // Alias dla std::filesystem

                // Buduje pełne ścieżki dla kluczowych plików
                fs::path game_path = fs::path(folder) / Constants::GAME_EXE_NAME; // Np. C:\GTA\gta_sa.exe
                fs::path samp_DLL_path = fs::path(folder) / Constants::SAMP_DLL_NAME; // Np. C:\GTA\samp.dll
                fs::path omp_DLL_path = fs::path(folder) / Constants::OMP_DLL_NAME; // Np. C:\GTA\omp-client.dll

                // 1. Walidacja plików
                if (!Utils::Validate_Files(game_path, samp_DLL_path, omp_DLL_path, inject_type))
                    return false; // Błąd został już wyświetlony przez funkcję walidacji
                
                std::wstring error_message_local; // Do odbierania komunikatów o błędach z walidacji

                // 2. Walidacja portu
                if (!Utils::Validate_Port(port, error_message_local))
                    return (Utils::Show_Error(error_message_local, inject_type), false);

                // 3. Walidacja pseudonimu
                if (!Utils::Validate_Nickname(nickname, error_message_local))
                    return (Utils::Show_Error(error_message_local, inject_type), false);

                // 4. Konwersja szerokich znaków na lokalne 8-bit (potrzebne dla API ANSI)
                std::string nickname_str = Utils::Wide_To_Local_8Bit(nickname);
                std::string ip_str = Utils::Wide_To_Local_8Bit(ip);
                std::string port_str = Utils::Wide_To_Local_8Bit(port);
                std::string password_str = Utils::Wide_To_Local_8Bit(password);
                // Konwertuje również ścieżki na std::string (wymagane przez CreateProcessA jako char*)
                std::string game_path_str = Utils::Wide_To_Local_8Bit(game_path.wstring());
                std::string folder_str = Utils::Wide_To_Local_8Bit(folder);
                std::string samp_DLL_path_str = Utils::Wide_To_Local_8Bit(samp_DLL_path.wstring());
                std::string omp_DLL_path_str = Utils::Wide_To_Local_8Bit(omp_DLL_path.wstring());

                // 5. Budowanie argumentów wiersza poleceń
                std::string args = Build_Command_Args(nickname_str, ip_str, port_str, password_str);

                // Tworzy instancję klasy Process do zarządzania operacjami procesu
                Process process_core;
                
                // 6. Tworzenie procesu gry (zawieszonego)
                auto process_info_opt = process_core.Create_Game_Process(game_path_str, args, folder_str);

                if (!process_info_opt)
                    return false; // Błąd został już wyświetlony przez funkcję tworzenia procesu

                // Dereferencjonuje optional, aby uzyskać strukturę Process_Info
                auto& process_info = *process_info_opt; 
                std::wstring inject_error_message; // Do odbierania komunikatów o błędach wstrzykiwania

                // 7. Wstrzykiwanie samp.dll
                if (!process_core.Inject_DLL(process_info.process_handle.get(), samp_DLL_path_str, inject_error_message))
                    return (Utils::Show_Error(L"Nie udało się wstrzyknąć samp.dll: " + inject_error_message, inject_type), false);

                // 8. Warunkowe wstrzykiwanie omp-client.dll (tylko jeśli to OMP)
                if (inject_type == Types::Inject_Type::OMP) {
                    if (!process_core.Inject_DLL(process_info.process_handle.get(), omp_DLL_path_str, inject_error_message))
                        return (Utils::Show_Error(L"Nie udało się wstrzyknąć omp-client.dll: " + inject_error_message, inject_type), false);
                }

                // 9. Wznowienie procesu gry
                // Proces został utworzony w stanie zawieszonym, aby umożliwić wstrzykiwanie.
                // Teraz, gdy DLL zostały wstrzyknięte, można go wznowić.
                if (ResumeThread(process_info.thread_handle.get()) == static_cast<DWORD>(-1))
                    return (Utils::Show_Error(L"Nie udało się wznowić wątku procesu gry: " + Utils::Get_System_Error_Message(GetLastError()), inject_type), false);

                return true; // Sukces we wszystkich etapach!
            }
        private:
            // Buduje ciąg argumentów wiersza poleceń dla pliku wykonywalnego gry
            std::string Build_Command_Args(const std::string& nickname, const std::string& ip, const std::string& port, const std::string& password) {
                std::stringstream command_args_stream; // Używa stringstream dla efektywnego budowania

                // SA-MP i OMP oczekują argumentów "-c -n [pseudonim] -h [ip] -p [port]"
                command_args_stream << Constants::CMD_ARG_CONFIG << " " 
                    << Constants::CMD_ARG_NICKNAME << " " << nickname << " " 
                    << Constants::CMD_ARG_HOST << " " << ip << " " 
                    << Constants::CMD_ARG_PORT << " " << port;

                // Dodaje hasło tylko, jeśli nie jest puste
                if (!password.empty())
                    command_args_stream << " " << Constants::CMD_ARG_PASSWORD << " " << password;

                return command_args_stream.str();
            }
    };
}
```

> [!CAUTION]
> Chociaż proces dla **OMP** obejmuje wstrzyknięcie `omp-client.dll` *oprócz* `samp.dll`, jest to zgodne z tym, jak **OMP** zazwyczaj działa. Klient **OMP** często używa `samp.dll` jako **bazy** lub **proxy** dla pewnych funkcjonalności, podczas gdy `omp-client.dll` rozszerza lub nadpisuje zachowania.
>
> Kluczowe jest, aby **obie DLL** były obecne i funkcjonalne w katalogu gry, aby **wstrzykiwanie OMP** zakończyło się sukcesem. Jeśli jedna z nich zawiedzie, gra może się nie uruchomić poprawnie lub klient wieloosobowy może się nie załadować.

### `injector.hpp`

To plik interfejsu biblioteki. Jest to jedyny plik, który użytkownik końcowy będzie musiał dołączyć, aby używać **SA-MP Injector C++**. Działa jako opakowanie dla klasy `Injector::Injector_Core`, upraszczając interfejs do pojedynczej funkcji globalnej, `Initialize_Game`.

```cpp
#pragma once

#include <string_view>
//
#include "injector_core.hpp" // Główna klasa z logiką
#include "error_utils.hpp" // Dla wyświetlania błędów (w przypadku nieprawidłowego typu wstrzykiwania)
#include "types.hpp" // Wyliczenie typów
#include "constants.hpp" // Stałe (dla nazw typów wstrzykiwania)

// Interfejs wysokiego poziomu dla biblioteki.
// Upraszcza użycie, eksponując tylko tę funkcję globalną.
inline bool Initialize_Game(std::wstring_view inject_type_str, std::wstring_view folder, 
    std::wstring_view nickname, 
    std::wstring_view ip, 
    std::wstring_view port, 
    std::wstring_view password) {
    Types::Inject_Type type; // Zmienna do przechowywania typu wstrzykiwania

    // Konwertuje ciąg typu wstrzykiwania na enum Inject_Type
    if (inject_type_str == Constants::INJECT_TYPE_SAMP)
        type = Types::Inject_Type::SAMP;
    
    else if (inject_type_str == Constants::INJECT_TYPE_OMP)
        type = Types::Inject_Type::OMP;
    
    else
        // Jeśli ciąg typu wstrzykiwania jest nieprawidłowy, wyświetla błąd i zwraca false
        return (Utils::Show_Error(L"Określono nieprawidłowy tryb wstrzykiwania. Proszę użyć 'samp' lub 'omp'.", Types::Inject_Type::SAMP), false); // Używa SAMP jako domyślnego dla tytułu

    Injector::Injector_Core injector; // Tworzy instancję obiektu zawierającego główną logikę
    
    // Deleguje wywołanie do funkcji Initialize_Game klasy Injector_Core
    return injector.Initialize_Game(type, folder, nickname, ip, port, password);
}
```

> [!NOTE]
> Użycie słowa kluczowego `inline` dla wszystkich funkcji w tym pliku i innych narzędziach pozwala bibliotece być `header-only`. `inline` sugeruje kompilatorowi, że ciało funkcji powinno być wstawione bezpośrednio w miejscach wywołania, ale głównym efektem tutaj jest złagodzenie **Zasady Jednej Definicji (ODR)**, aby funkcja mogła być zdefiniowana w wielu plikach `.obj` (co miałoby miejsce, gdyby wiele `.cpp` dołączało `injector.hpp`). Etap **linkowania** zapewni, że w pliku wykonywalnym znajdzie się tylko jedna ostateczna wersja.

## Wszechstronne przykłady użycia

Aby zintegrować **SA-MP Injector C++** z twoim projektem, postępuj zgodnie z poniższymi instrukcjami i przeanalizuj poniższe scenariusze.

### 1. Przygotowanie środowiska programistycznego

- **Kompilator C++**: Zaleca się kompilator, który **obsługuje C++17**. **Visual Studio** z `vcpkg` (dla `std::filesystem`) lub **GCC/Clang (wersja 17+)** to opcje.
- **Konfiguracja projektu**:
  - Utwórz nowy projekt **C++** (np. projekt konsolowy).
  - Skopiuj **wszystkie** pliki `.hpp` z **SA-MP Injector C++** do folderu dostępnego dla twojego projektu (np. do folderu **headers**).
  - Upewnij się, że standard **C++** jest ustawiony na **C++17**. Jest to kluczowe dla maksymalnej kompatybilności z bibliotekami **SA-MP** i **OMP**. W **Visual Studio**: `Project Properties > Configuration Properties > C/C++ > Language > C++ Language Standard -> "ISO C++17 Standard (/std:c++17)"`
- **Uprawnienia**: Twój plik wykonywalny prawdopodobnie będzie musiał być uruchomiony jako **Administrator (niekoniecznie)**, aby tworzyć procesy i **wstrzykiwać DLL** w środowisku systemowym. W **Visual Studio** można to zrobić w: `Project Properties > Configuration Properties > Linker > Manifest File > UAC Execution Level -> "requireAdministrator (/LEVEL='requireAdministrator')"`

### 2. Podstawowy scenariusz: Łączenie z serwerem SA-MP

To najczęstszy przypadek użycia, uruchamiający **GTA:SA** i łączący z serwerem **SA-MP** z określonym **pseudonimem** i **IP**/**portem**.

```cpp
// main.cpp
#include <iostream>
#include <string>
#include <codecvt> // Dla std::wstring_convert (przestarzałe, ale funkcjonalne dla tego przypadku)
#include <locale> // Dla std::codecvt_utf8_to_utf16
//
#include "injector.hpp" // Jedyna potrzebna inkluzja z biblioteki!

int Main(int argc, char* argv[]) {
    // Definiowanie zmiennych konfiguracyjnych
    // Zmień te ścieżki i szczegóły serwera, aby pasowały do twojej lokalnej konfiguracji
    std::wstring folder = L"C:\\Gry\\GTA San Andreas"; // Gdzie znajdują się gta_sa.exe, samp.dll
    std::wstring nickname = L"Nazwa";
    std::wstring ip = L"127.0.0.1"; // Przykład: twój lokalny serwer
    std::wstring port = L"7777";
    std::wstring password = L""; // Pozostaw puste, jeśli nie ma hasła

    // Opcjonalne: Zezwól użytkownikowi na podanie ustawień przez wiersz poleceń (uproszczone)
    // Dla bardziej solidnej obsługi argumentów użyj biblioteki do parsowania argumentów.
    if (argc > 1) {
        // Przykład: jeśli pierwszym argumentem jest ścieżka
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

    std::wcout << L"Uruchamianie SA-MP..." << std::endl;
    std::wcout << L"Folder gry: " << folder << std::endl;
    std::wcout << L"Pseudonim: " << nickname << std::endl;
    std::wcout << L"Serwer: " << ip << L":" << port << std::endl;

    // Wywołanie funkcji biblioteki do uruchomienia gry
    if (Initialize_Game(L"samp", // Typ wstrzykiwania: SA-MP
        folder, // Ścieżka do folderu gry
        nickname, // Żądany pseudonim
        ip, // IP serwera
        port, // Port serwera (ciąg)
        password)) { // Hasło serwera (ciąg, może być pusty)
        std::wcout << L"\n--- SA-MP uruchomiony pomyślnie! ---" << std::endl;
        std::wcout << L"Gra została uruchomiona w oddzielnym procesie." << std::endl;
    }
    else {
        std::wcout << L"\n--- NIEPOWODZENIE uruchomienia SA-MP! ---" << std::endl;
        std::wcout << L"Sprawdź wyświetlone komunikaty o błędach." << std::endl;
    }

    // Utrzymuje konsolę otwartą, aby zobaczyć komunikaty wyjściowe
    std::wcout << L"\nNaciśnij Enter, aby zamknąć program." << std::endl;
    std::wcin.ignore();

    return 0;
}
```

**Aby skompilować i uruchomić:**

```bash
# Przykład z g++ (Linux/MinGW/MSYS2) - Wymaga libstdc++fs dla filesystem
# Ważne jest, aby upewnić się, że toolchain nie używa wersji C++,
# która wprowadza niezgodności w procesie wstrzykiwania.
# Sprawdź dokumentację swojego kompilatora dla flag zgodności binarnej (ABI).
g++ main.cpp -o my_launcher -std=c++17 -Wall -lstdc++fs -municode -lkernel32

# Przykład z MSVC (Visual Studio Developer Command Prompt)
# Flaga '/std:c++17' zapewnia zgodność z C++17.
cl /EHsc /std:c++17 /permissive- /FS /utf-8 main.cpp /link /OUT:my_launcher.exe
```

> [!NOTE]
> **SA-MP** i **OMP**, jako projekty starsze, są kompilowane z określonymi narzędziami, które definiują ich **Application Binary Interface (ABI)**. Chociaż ta biblioteka używa **C++17**, **kluczowe jest, aby DLL SA-MP i OMP, z którymi interaguje, były również kompatybilne z ABI twojego kompilatora i wersją środowiska uruchomieniowego C++ (CRT), której używasz**.
>
> Użycie kompilatora lub wersji **C++** znacznie różniącej się od tej użytej do **budowania DLL** gry może prowadzić do subtelnych problemów (np. z alokacją pamięci lub przekazywaniem parametrów), które nie są łatwe do **zdiagnozowania** i nie spowodują wyraźnego błędu wstrzykującego. Z tego powodu **C++17 jest maksymalną zalecaną wersją**, ponieważ nowsze wersje mogą wprowadzać zmiany w **ABI** lub **CRT**, które nie są tolerowane przez starsze moduły gry.

### 3. Zaawansowany scenariusz: Łączenie z serwerem OMP

Dla **OMP** logika jest identyczna jak dla **SA-MP**, ale określisz `L"omp"` jako `inject_type` i upewnisz się, że `omp-client.dll` jest obecny w katalogu gry.

```cpp
// main.cpp
#include <iostream>
#include <string>
#include <codecvt> // Dla std::wstring_convert (przestarzałe, ale funkcjonalne dla tego przypadku)
#include <locale> // Dla std::codecvt_utf8_to_utf16
//
#include "injector.hpp" // Jedyna potrzebna inkluzja z biblioteki!

int Main() {
    // Definiowanie zmiennych konfiguracyjnych
    // Zmień te ścieżki i szczegóły serwera, aby pasowały do twojej lokalnej konfiguracji
    std::wstring folder = L"C:\\Gry\\GTA San Andreas"; // Gdzie znajdują się gta_sa.exe, samp.dll i omp-client.dll
    std::wstring nickname = L"Nazwa";
    std::wstring ip = L"127.0.0.1"; // Przykład: twój lokalny serwer
    std::wstring port = L"7777";
    std::wstring password = L""; // Pozostaw puste, jeśli nie ma hasła

    // Opcjonalne: Zezwól użytkownikowi na podanie ustawień przez wiersz poleceń (uproszczone)
    // Dla bardziej solidnej obsługi argumentów użyj biblioteki do parsowania argumentów.
    if (argc > 1) {
        // Przykład: jeśli pierwszym argumentem jest ścieżka
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

    std::wcout << L"Uruchamianie OMP..." << std::endl;
    std::wcout << L"Folder gry: " << folder << std::endl;
    std::wcout << L"Pseudonim: " << nickname << std::endl;
    std::wcout << L"Serwer: " << ip << L":" << port << std::endl;

    // Wywołanie funkcji biblioteki do uruchomienia gry
    if (Initialize_Game(L"omp", // Typ wstrzykiwania: OMP
        folder, // Ścieżka do folderu gry
        nickname, // Żądany pseudonim
        ip, // IP serwera
        port, // Port serwera (ciąg)
        password)) { // Hasło serwera (ciąg, może być pusty)
        std::wcout << L"\n--- OMP uruchomiony pomyślnie! ---" << std::endl;
        std::wcout << L"Gra została uruchomiona w oddzielnym procesie." << std::endl;
    }
    else {
        std::wcout << L"\n--- NIEPOWODZENIE uruchomienia OMP! ---" << std::endl;
        std::wcout << L"Sprawdź wyświetlone komunikaty o błędach." << std::endl;
    }

    // Utrzymuje konsolę otwartą, aby zobaczyć komunikaty wyjściowe
    std::wcout << L"\nNaciśnij Enter, aby zamknąć program." << std::endl;
    std::wcin.ignore();

    return 0;
}
```

## Obsługa typowych błędów i komunikatów

**SA-MP Injector C++** priorytetowo traktuje użyteczność, a kluczową częścią tego jest dostarczanie wyraźnego **feedbacku** użytkownikowi w przypadku niepowodzenia. Komunikaty o błędach są prezentowane za pomocą okien **dialogowych Windows** (`MessageBoxW`) i są kategoryzowane według typu **wstrzykiwania (SA-MP lub OMP)** dla większego kontekstu. Zapewnia to, że dokładnie wiesz, co poszło nie tak i jak podejść do rozwiązania.

Oto niektóre z typowych błędów, które możesz napotkać, oraz ich prawdopodobne przyczyny/rozwiązania, wraz z przykładami wizualnymi, jak te okna dialogowe wyglądają dla użytkownika końcowego:

### 1. Nieprawidłowy typ wstrzykiwania

Jeśli podany `inject_type` w funkcji `Initialize_Game` nie jest `L"samp"` ani `L"omp"`, biblioteka nie będzie wiedzieć, który klient wieloosobowy zamierzasz uruchomić.

![Error 1](screenshots/error_1.png)

- **Wyświetlany komunikat o błędzie**: `"Invalid injection mode specified. Please use 'samp' or 'omp'."`
- **Przyczyna**: Pierwszy argument funkcji `Initialize_Game` (`std::wstring_view inject_type`) nie odpowiada oczekiwanym wartościom `L"samp"` lub `L"omp"`. Może to być literówka, pusty ciąg lub nierozpoznana wartość.
- **Rozwiązanie**: Upewnij się, że `std::wstring_view inject_type_str` jest poprawnie ustawiony na `L"samp"` lub `L"omp"`. Kluczowe jest użycie prefiksu `L` dla literałów **szerokich znaków** podczas definiowania ciągów dla kompatybilności z stałymi biblioteki.
    ```cpp
    // Poprawnie:
    Initialize_Game(L"samp", /* inne parametry */);
    Initialize_Game(L"omp", /* inne parametry */);

    // Niepoprawnie (spowoduje błąd):
    // Initialize_Game(L"invalid", /* inne parametry */);
    // Initialize_Game(L"", /* inne parametry */);
    ```

### 2. Nieprawidłowy port serwera (format lub zakres)

Port jest kluczowym parametrem numerycznym dla połączenia z serwerem. Ten błąd występuje, jeśli wartość nie może być zinterpretowana jako prawidłowa liczba lub znajduje się poza akceptowalnym zakresem **(1 do 65535)**.

#### 2.1. Nienumeryczny format portu

![Error 2](screenshots/error_2.png)

- **Wyświetlany komunikat o błędzie**: `"Invalid port format. The port must be a numeric value. Please provide a valid integer for the port."`
- **Przyczyna**: Argument `port` (`std::wstring_view`) zawiera znaki, które nie są cyframi numerycznymi lub nie można go skonwertować na liczbę całkowitą.
- **Rozwiązanie**: Podaj ciąg, który zawiera tylko cyfry i reprezentuje prawidłową liczbę całkowitą.
    ```cpp
    // Poprawnie:
    Initialize_Game(/* inne parametry */, L"7777", /* inne parametry */);

    // Niepoprawnie (nieprawidłowy format):
    // Initialize_Game(/* inne parametry */, L"port7777", /* inne parametry */);

    // Niepoprawnie (nieprawidłowy):
    // Initialize_Game(/* inne parametry */, L"invalid", /* inne parametry */);
    ```

#### 2.2. Port poza prawidłowym zakresem

![Error 3](screenshots/error_3.png)

- **Wyświetlany komunikat o błędzie**: `"The specified port number (XXXX) is outside the valid range of 1 to 65535. Please provide a valid port."` (**XXXX** będzie wartością, którą próbowałeś użyć).
- **Przyczyna**: Podany port jest prawidłową liczbą, ale znajduje się poniżej `1` (zarezerwowany lub nieużywalny) lub powyżej `65535` (maksymalny limit dla **portów TCP/UDP**).
- **Rozwiązanie**: Podaj port, który mieści się w zakresie od `1` do `65535`. Typowe porty dla **SA-MP**/**OMP** to `7777` lub `7778`.
    ```cpp
    // Poprawnie:
    Initialize_Game(/* inne parametry */, L"7777", /* inne parametry */);

    // Niepoprawnie (poza zakresem):
    // Initialize_Game(/* inne parametry */, L"0", /* inne parametry */); // Za niski
    // Initialize_Game(/* inne parametry */, L"65536", /* inne parametry */); // Za wysoki
    // Initialize_Game(/* inne parametry */, L"-1", /* inne parametry */); // Wartość ujemna
    ```

### 3. Nieprawidłowy pseudonim (pusty lub za długi)

**Pseudonim** gracza jest walidowany, aby zapewnić, że klient gry go zaakceptuje.

#### 3.1. Pusty pseudonim

![Error 4](screenshots/error_4.png)

- **Wyświetlany komunikat o błędzie**: `"Nickname cannot be empty. Please provide a valid nickname."`
- **Przyczyna**: Argument `nickname` (`std::wstring_view`) został podany jako pusty ciąg.
- **Rozwiązanie**: Upewnij się, że pseudonim nie jest pusty.
    ```cpp
    // Poprawnie:
    Initialize_Game(/* inne parametry */, L"Nazwa", /* inne parametry */);

    // Niepoprawnie (pusty):
    // Initialize_Game(/* inne parametry */, L"", /* inne parametry */);
    ```

#### 3.2. Za długi pseudonim

![Error 5](screenshots/error_5.png)

- **Wyświetlany komunikat o błędzie**: `"Nickname length exceeds the maximum allowed of 20 characters. Please use a shorter nickname."`
- **Przyczyna**: Długość podanego **pseudonimu** przekracza `Constants::MAX_NICKNAME_LENGTH`, czyli `20` znaków.
- **Rozwiązanie**: Użyj **pseudonimu**, który ma maksymalnie `20` znaków.
    ```cpp
    // Poprawnie:
    Initialize_Game(/* inne parametry */, L"Nazwa", /* inne parametry */);

    // Niepoprawnie (za długi):
    // Initialize_Game(/* inne parametry */, L"TenPseudonimJestZaDlugiIP超過DwudziestuZnakow", /* inne parametry */);
    ```

### 4. Nie znaleziono plików gry lub DLL

Jest to jedna z najczęstszych przyczyn niepowodzenia. Biblioteka wymaga, aby `gta_sa.exe`, `samp.dll` oraz, dla **OMP**, `omp-client.dll` były obecne w oczekiwanych lokalizacjach.

#### 4.1. Nie znaleziono pliku wykonywalnego gry (`gta_sa.exe`)

![Error 6](screenshots/error_6.png)

- **Wyświetlany komunikat o błędzie**: `"Game executable not found. Please ensure 'gta_sa.exe' exists at the specified path: [pełna ścieżka]"`. `[pełna ścieżka]` będzie zawierać folder i nazwę pliku.
- **Przyczyna**: Plik `gta_sa.exe` nie został znaleziony w folderze podanym w argumencie `folder`.
- **Rozwiązanie**:
  1. Sprawdź, czy `folder` (`std::wstring_view`) wskazuje na prawidłowy katalog instalacji **GTA San Andreas**.
  2. Potwierdź, że `gta_sa.exe` istnieje w tym folderze i że jego nazwa nie została zmieniona.

#### 4.2. Nie znaleziono biblioteki SA-MP (`samp.dll`)

![Error 7](screenshots/error_7.png)

- **Wyświetlany komunikat o błędzie**: `"SA-MP library not found. Please ensure 'samp.dll' exists at the specified path: [pełna ścieżka]"`.
- **Przyczyna**: Plik `samp.dll` nie został znaleziony w folderze podanym w argumencie `folder`. **Ta DLL** jest wymagana dla **obu** typów wstrzykiwania (`samp` i `omp`).
- **Rozwiązanie**: Upewnij się, że `samp.dll` jest obecny w folderze instalacji **GTA San Andreas**.

#### 4.3. Nie znaleziono biblioteki OMP (`omp-client.dll`) (tylko dla wstrzykiwania OMP)

![Error 8](screenshots/error_8.png)

- **Wyświetlany komunikat o błędzie**: `"OMP library not found. Please ensure 'omp-client.dll' exists at the specified path for OMP injection: [pełna ścieżka]"`.
- **Przyczyna**: Jeśli określiłeś `L"omp"` jako typ wstrzykiwania, ale plik `omp-client.dll` nie został znaleziony w podanym folderze.
- **Rozwiązanie**: Pobierz najnowszego klienta **OMP** i upewnij się, że `omp-client.dll` (oraz `samp.dll`) są obecne w folderze instalacji **GTA San Andreas**.

### 5. Niepowodzenie w tworzeniu procesu gry

Jest to bardziej złożony błąd, ponieważ dotyczy **uprawnień systemu operacyjnego** i aktualnego stanu `gta_sa.exe`.

![Error 9](screenshots/error_9.png)

- **Wyświetlany komunikat o błędzie**: `"Failed to create game process. Ensure 'gta_sa.exe' is not running and you have sufficient permissions to execute the file. System Error: [Komunikat o błędzie systemowym]"`. Komunikat systemowy zostanie dodany przez `GetLastError()` (np. `Access is denied.` lub `The requested operation requires elevation.`).
- **Przyczyna**: Wywołanie `CreateProcessA` do uruchomienia `gta_sa.exe` nie powiodło się. Typowe przyczyny obejmują:
  - **Proces już uruchomiony**: Instancja `gta_sa.exe` jest już aktywna i blokuje nowe wykonanie.
  - **Niewystarczające uprawnienia**: Twoja aplikacja nie ma wymaganych uprawnień (np. administratora) do tworzenia procesu w określonych konfiguracjach systemu (**UAC** włączony, chronione foldery itp.).
  - **Problemy z plikiem wykonywalnym**: `gta_sa.exe` może być uszkodzony lub zablokowany przez inny program (np. źle skonfigurowany antywirus).
- **Rozwiązanie**:
  1. Sprawdź Menedżer Zadań i upewnij się, że nie ma żadnych instancji `gta_sa.exe` w działaniu. Zakończ je, jeśli są.
  2. Uruchom swoją aplikację wykorzystującą bibliotekę z uprawnieniami **Administratora**. Kliknij prawym przyciskiem myszy na plik wykonywalny i wybierz **"Uruchom jako administrator"**.
  3. Jeśli **antywirus** lub **oprogramowanie** zabezpieczające zakłóca, dodaj swoją aplikację i/lub folder **GTA:SA** do wyjątków antywirusa (rób to ostrożnie i tylko jeśli masz pewność co do integralności swoich plików).

### 6. Niepowodzenie w alokacji pamięci w procesie docelowym

Biblioteka próbuje zaalokować mały fragment pamięci w `gta_sa.exe` dla skopiowania **ścieżki DLL**.

![Error 10](screenshots/error_10.png)

- **Wyświetlany komunikat o błędzie**: `"Failed to allocate memory in the target process. This might be due to insufficient permissions or process protection mechanisms."`
- **Przyczyna**: Funkcja `VirtualAllocEx` (używana do alokacji pamięci w innym procesie) nie powiodła się. Jest to bardziej prawdopodobne, jeśli:
  - Proces **GTA:SA** (nawet będąc w stanie zawieszonym) ma mechanizmy obronne lub **łaty anty-wstrzykiwania**, które uniemożliwiają alokację pamięci przez procesy zewnętrzne.
  - Twoja aplikacja nie ma wystarczających uprawnień do manipulacji pamięcią innego procesu.
  - (Mniej powszechne) Występuje ekstremalny niedobór pamięci wirtualnej w systemie.
- **Rozwiązanie**:
  1. Uruchom swoją aplikację z uprawnieniami **Administratora**.
  2. Upewnij się, że gra nie ma żadnych modyfikacji lub **łat bezpieczeństwa**, które mogłyby blokować próby wstrzykiwania lub manipulacji pamięcią (to bardziej powszechne w zmodyfikowanych środowiskach lub z pewnymi narzędziami anty-cheat).

### 7. Niepowodzenie w zapisie ścieżki DLL do pamięci procesu

Po zaalokowaniu pamięci biblioteka próbuje skopiować **ścieżkę DLL** do niej.

![Error 11](screenshots/error_11.png)

- **Wyświetlany komunikat o błędzie**: `"Failed to write DLL path to the target process memory. Verify process permissions and ensure the DLL path is accessible."`
- **Przyczyna**: Funkcja `WriteProcessMemory` nie powiodła się podczas próby skopiowania **bajtów ścieżki DLL** do zaalokowanej pamięci zdalnej w `gta_sa.exe`. Zazwyczaj wskazuje to na:
  - **Uprawnienia do zapisu**: Twoja aplikacja nie ma uprawnień do zapisu w tym obszarze pamięci lub w procesie **GTA:SA**.
  - **Nieprawidłowy uchwyt**: **Uchwyt** procesu (`process_handle`) z jakiegoś powodu stał się nieprawidłowy między alokacją a zapisem, co jest bardzo rzadkie z powodu użycia `UniqueResource`, ale może wystąpić w ekstremalnych warunkach systemowych.
  - **Problemy z ochroną pamięci**: Jakaś ochrona pamięci (czy to ze strony **systemu operacyjnego**, czy modyfikacji gry) uniemożliwiła zapis.
- **Rozwiązanie**: Uruchom jako **Administrator**. Sprawdź, czy `gta_sa.exe` i jego środowisko są "czyste" od narzędzi, które mogłyby blokować operacje na pamięci.

### 8. Niepowodzenie w znalezieniu kluczowych funkcji systemowych

Są to **API** kluczowe dla **Windows**; błędy tutaj wskazują na fundamentalny problem z systemem operacyjnym lub środowiskiem wykonawczym.

#### 8.1. Nie znaleziono `kernel32.dll`

![Error 12](screenshots/error_12.png)

- **Wyświetlany komunikat o błędzie**: `"Failed to obtain a handle to kernel32.dll. This is an essential system library and this error indicates a severe system issue."`
- **Przyczyna**: `kernel32.dll` to jedna z najbardziej podstawowych **DLL** w **Windows**, zawierająca kluczowe funkcje, takie jak `CreateProcess`, `VirtualAllocEx` itp. Jeśli `GetModuleHandleA` nie może uzyskać **uchwytu** do niej, system operacyjny ma bardzo poważne problemy.
- **Rozwiązanie**: Jest to **krytyczny** błąd, który rzadko jest spowodowany przez bibliotekę lub twoją aplikację. Sugeruje uszkodzenie plików systemowych, poważne problemy z **Windows** lub wysoce nietypową instalację **systemu operacyjnego**. Zaleca się przeprowadzenie weryfikacji integralności systemu (np. `sfc /scannow` w **Wierszu polecenia** jako **Administrator**) lub, w ostateczności, ponowną instalację **Windows**.

#### 8.2. Nie znaleziono `LoadLibraryA`

![Error 13](screenshots/error_13.png)

- **Wyświetlany komunikat o błędzie**: `"Failed to find the address of the LoadLibraryA function in kernel32.dll. This is critical for injecting the DLL."`
- **Przyczyna**: Chociaż `kernel32.dll` został znaleziony, funkcja `LoadLibraryA` nie mogła zostać odnaleziona za pomocą `GetProcAddress`. Choć jest to niezwykle rzadkie, może wynikać z uszkodzenia **pliku DLL** `kernel32.dll` lub wysoce niestandardowego środowiska wykonawczego.
- **Rozwiązanie**: Podobnie jak w przypadku błędu `kernel32.dll` powyżej, wskazuje to na poważny problem z systemem operacyjnym.

### 9. Niepowodzenie w utworzeniu zdalnego wątku do iniekcji

Po przygotowaniu zdalnego środowiska i skopiowaniu **ścieżki DLL**, tworzony jest nowy **wątek** w procesie gry, aby "wywołać" `LoadLibraryA`.

![Error 14](screenshots/error_14.png)

- **Wyświetlany komunikat o błędzie**: `"Failed to create a remote thread in the target process to execute the DLL injection. This could be due to security restrictions or process state. System Error: [Komunikat błędu systemowego]"`.
- **Przyczyna**: Wywołanie `CreateRemoteThread` nie powiodło się. Ten błąd jest powszechny w systemach z silnymi mechanizmami **antyiniekcyjnymi** lub gdy program intensywnie monitoruje zachowanie procesu:
  - **Mechanizmy bezpieczeństwa**: Narzędzia **anty-cheat**, **oprogramowanie** zabezpieczające lub określone polityki **Windows** mogą wykrywać i blokować próby tworzenia **wątków** w procesach stron trzecich.
  - **Niespójny proces docelowy**: Jeśli proces **GTA:SA** znajduje się w nieoczekiwanym lub niestabilnym stanie (mimo uruchomienia w trybie `CREATE_SUSPENDED`), może to wpłynąć na możliwość tworzenia **wątków**.
- **Rozwiązanie**:
  1. Uruchom aplikację z uprawnieniami **Administratora**.
  2. Sprawdź, czy nie ma narzędzi **anty-cheat**, **agresywnych antywirusów** lub **zapór ogniowych** skonfigurowanych do inspekcji i blokowania manipulacji procesami, które mogą powodować konflikt. Dodaj swoją aplikację i `gta_sa.exe` do wyjątków, jeśli dotyczy (z ostrożnością).
  3. Komunikat błędu systemowego (`GetLastError()`) może dostarczyć dodatkowych szczegółów do zbadania konkretnej przyczyny (np. **"Procesowi odmówiono dostępu do tworzenia wątków dla innych procesów."**).

### 10. Przekroczenie limitu czasu lub niepowodzenie w zakończeniu iniekcji

Po utworzeniu **zdalnego wątku**, iniektor oczekuje na zakończenie **ładowania DLL**.

![Error 15](screenshots/error_15.png)

- **Wyświetlany komunikat o błędzie**: `"Timeout or error waiting for DLL injection to complete. System Error: [Komunikat błędu systemowego]"`.
- **Przyczyna**: **Zdalny wątek** wykonujący `LoadLibraryA` trwał dłużej niż `Constants::DLL_INJECTION_TIMEOUT_MS` (10 sekund), aby zwrócić wynik, lub zakończył się niepowodzeniem i `GetExitCodeThread` zwrócił 0. Potencjalne przyczyny obejmują:
  - **Problemy z wstrzykniętą DLL**: `DllMain` w `samp.dll` lub `omp-client.dll` trwa zbyt długo, zawiera **nieskończoną pętlę**, **awarię** lub błąd, który **uniemożliwia ładowanie DLL** (np. brakujące **zależności DLL**).
  - **Ciche blokowanie**: Mechanizm bezpieczeństwa mógł zablokować `LoadLibraryA`, ale nie zgłosił wyraźnego błędu podczas tworzenia **wątku**.
- **Rozwiązanie**:
  1. Sprawdź integralność plików `samp.dll` i `omp-client.dll`. Mogą być uszkodzone lub pochodzić z wersji niekompatybilnej z `gta_sa.exe`.
  2. Upewnij się, że **wstrzyknięta DLL** nie zależy od **innych DLL**, które mogą być niedostępne lub brakujące w systemie.

### 11. Niepowodzenie w wznowieniu wątku procesu gry

To ostatni krok do uruchomienia gry po **wstrzyknięciu DLL**.

![Error 16](screenshots/error_16.png)

- **Wyświetlany komunikat o błędzie**: `"Failed to resume the game process thread: [Komunikat błędu systemowego]"`.
- **Przyczyna**: Wywołanie `ResumeThread` nie powiodło się, co oznacza, że główny **wątek** `gta_sa.exe` nie mógł zostać aktywowany, aby rozpocząć wykonywanie gry. Jest to rzadki błąd, ale może wystąpić, jeśli:
  - **Uchwyt** **wątku** procesu stał się nieprawidłowy.
  - System operacyjny uniemożliwił wznowienie z jakiegoś powodu, prawdopodobnie związanego z przerwą bezpieczeństwa lub niespójnym stanem procesu.
  - Proces mógł zostać zakończony zewnętrznie między **wstrzyknięciem DLL** a próbą wznowienia głównego **wątku**.
- **Rozwiązanie**: Jeśli wszystkie poprzednie kroki zakończyły się powodzeniem, a tylko `ResumeThread` nie powiódł się, może to być problem z systemem operacyjnym, samą instalacją **GTA:SA** lub zbyt rygorystycznym **oprogramowaniem** zabezpieczającym. Ponownie sprawdź stan `gta_sa.exe` w **Menedżerze zadań** tuż przed i po błędzie. Ponowne uruchomienie komputera może rozwiązać tymczasowe problemy stanu systemu.

> [!TIP]
> W złożonych scenariuszach debugowania narzędzia takie jak **Process Monitor (Sysinternals Suite)** lub debuger (np. **Visual Studio Debugger**, **WinDbg**, **OllyDbg**) mogą być nieocenione. Mogą pomóc w obserwacji wywołań **API**, sprawdzaniu błędów dostępu, śledzeniu stanu **uchwytów** i nawet inspekcji pamięci procesu, zapewniając dogłębny wgląd w to, co dzieje się pod spodem.

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