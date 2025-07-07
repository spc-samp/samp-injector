# SA-MP Injector

[![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](https://opensource.org/licenses/MIT)
[![SA-MP | OMP](https://img.shields.io/badge/Support-SA--MP%20%7C%20OMP-yellow)](https://github.com/spc-samp/samp-injector)
[![x86 Only](https://img.shields.io/badge/Architecture-x86%20(32--bit)-orange)](https://github.com/spc-samp/samp-injector)

**SA-MP Injector** to wszechstronne narzędzie zaprojektowane dla **SA-MP (San Andreas Multiplayer)** oraz **OMP (Open Multiplayer)**, działające jako **wykonywalny plik wiersza poleceń**, **dynamiczna biblioteka (DLL)** oraz **zbiór bibliotek dla różnych języków programowania**. Jego główną funkcją jest wstrzyknięcie pliku `samp.dll` (w przypadku **SA-MP**) lub obu `samp.dll` i `omp-client.dll` (w przypadku **OMP**) do procesu **GTA:SA**, umożliwiając uruchomienie gry z niestandardowymi parametrami, co pozwala na bezpośrednie połączenie z serwerem.

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

- [SA-MP Injector](#sa-mp-injector)
  - [Języki](#języki)
  - [Spis treści](#spis-treści)
  - [Plik wykonywalny](#plik-wykonywalny)
    - [Funkcjonalność](#funkcjonalność)
    - [Jak używać (Wiersz poleceń)](#jak-używać-wiersz-poleceń)
      - [Tryb SA-MP](#tryb-sa-mp)
      - [Tryb OMP](#tryb-omp)
      - [Parametry](#parametry)
    - [Jak używać (Wbudowany w aplikacje)](#jak-używać-wbudowany-w-aplikacje)
    - [Wykorzystanie biblioteki C++ w pliku wykonywalnym](#wykorzystanie-biblioteki-c-w-pliku-wykonywalnym)
    - [Jak skompilować](#jak-skompilować)
      - [Wymagania](#wymagania)
      - [Kroki kompilacji](#kroki-kompilacji)
  - [Biblioteka Dynamiczna (**DLL**)](#biblioteka-dynamiczna-dll)
    - [Funkcjonalność](#funkcjonalność-1)
    - [Jak Używać (Wywołanie API)](#jak-używać-wywołanie-api)
      - [Kontrakt Funkcji `Launch_Game`](#kontrakt-funkcji-launch_game)
      - [Parametry](#parametry-1)
    - [Jak Używać (Osadzone w Aplikacjach)](#jak-używać-osadzone-w-aplikacjach)
    - [Użycie Biblioteki C++ w **DLL**](#użycie-biblioteki-c-w-dll)
    - [Jak Skompilować](#jak-skompilować-1)
      - [Wymagania](#wymagania-1)
      - [Kroki Kompilacji](#kroki-kompilacji-1)
  - [Biblioteki](#biblioteki)
    - [Przegląd](#przegląd)
    - [Lista bibliotek](#lista-bibliotek)
  - [Licencja](#licencja)
    - [Warunki użytkowania](#warunki-użytkowania)
      - [1. Przyznane uprawnienia](#1-przyznane-uprawnienia)
      - [2. Obowiązkowe warunki](#2-obowiązkowe-warunki)
      - [3. Prawa autorskie](#3-prawa-autorskie)
      - [4. Wyłączenie gwarancji i ograniczenie odpowiedzialności](#4-wyłączenie-gwarancji-i-ograniczenie-odpowiedzialności)

## Plik wykonywalny

Plik wykonywalny `samp-injector.exe` oferuje interfejs wiersza poleceń do uruchamiania **GTA:SA** z **SA-MP** lub **OMP**, automatycznie konfigurując połączenie z serwerem. Upraszcza on logikę **wstrzykiwania bibliotek DLL** i przekazywania parametrów gry.

### Funkcjonalność

`samp-injector.exe` działa jako automatyczny launcher gry, eliminując złożoność konfiguracji i wstrzykiwania **DLL**:

1. **Weryfikacja środowiska:** Sprawdza istnienie niezbędnych plików (`gta_sa.exe`, `samp.dll`, `omp-client.dll`) w określonym katalogu oraz poprawność podanych parametrów połączenia.
2. **Tworzenie procesu w stanie zawieszenia:** Uruchamia `gta_sa.exe` w stanie zawieszonym, co jest warunkiem wstępnym do **bezpiecznego wstrzykiwania bibliotek DLL** przed rozpoczęciem głównego procesu gry.
3. **Dynamiczne wstrzykiwanie bibliotek DLL:**
   - W trybie **SA-MP** wstrzykiwana jest `samp.dll`.
   - W trybie **OMP** wstrzykiwane są `samp.dll` oraz `omp-client.dll`. Wstrzykiwanie jest realizowane poprzez zdalne wywołanie funkcji `LoadLibraryA`, umożliwiając grze GTA: SA załadowanie modułów multiplayer i zainicjowanie połączenia.
4. **Konfiguracja argumentów:** Argumenty wiersza poleceń, takie jak **pseudonim**, **adres IP serwera**, **port** oraz **hasło (jeśli podane)**, są przygotowywane i przekazywane do `gta_sa.exe`.
5. **Wznowienie procesu:** Po **pomyślnym wstrzyknięciu bibliotek DLL**, proces gry jest wznawiany, co pozwala grze **GTA:SA** na bezpośrednie połączenie z serwerem.

### Jak używać (Wiersz poleceń)

Aby użyć pliku wykonywalnego, wywołaj go z **Wiersza poleceń (CMD)**, **PowerShell** lub **terminala**, podając wymagane parametry.

Podstawowy format to:
```bash
samp-injector.exe <tryb> <katalog_gry> <pseudonim> <IP_serwera> <port_serwera> <hasło_serwera (opcjonalne)>
```

#### Tryb SA-MP

Dla wyłącznego wstrzykiwania `samp.dll`:
```bash
samp-injector.exe "samp" "C:\Games\GTA San Andreas" "Nazwa" "127.0.0.1" "7777" "hasło (opcjonalne)"
```

#### Tryb OMP

Dla wstrzykiwania `samp.dll` oraz `omp-client.dll`:
```bash
samp-injector.exe "omp" "C:\Games\GTA San Andreas" "Nazwa" "127.0.0.1" "7777" "hasło (opcjonalne)"
```

#### Parametry

- `<tryb>`: Określa typ wstrzykiwania.
   - `samp`: Dla **SA-MP** (`samp.dll`).
   - `omp`: Dla **OMP** (`samp.dll` oraz `omp-client.dll`).
- `<katalog_gry>`: Pełna ścieżka do katalogu **GTA:SA**. Katalog ten musi zawierać `gta_sa.exe` oraz odpowiednie pliki **DLL**.
- `<pseudonim>`: Twój pseudonim w grze (maksymalnie **20 znaków**).
- `<IP_serwera>`: Adres **IP** lub nazwa **domeny** serwera.
- `<port_serwera>`: Port połączenia serwera (wartość liczbowa od **1** do **65535**).
- `<hasło_serwera>`: Hasło wymagane do połączenia z serwerem **(jeśli serwer nie wymaga hasła, parametr ten można pominąć)**.

Jeśli argumenty są nieprawidłowe lub niewystarczające, wyświetli się komunikat o użyciu.

### Jak używać (Wbudowany w aplikacje)

`samp-injector.exe` jest idealny do integracji z aplikacjami innych firm, takimi jak własne launchery, które chcą zautomatyzować proces uruchamiania gry z predefiniowanymi ustawieniami.

Przykład wywołania `samp-injector.exe` z aplikacji w **C#**:
```csharp
using System;
using System.Diagnostics;
using System.Windows.Forms;

public class Launcher {
    public static void Main(string[] args) {
        string inject_mode = "omp"; 
        string folder = "C:\\Games\\GTA San Andreas";
        string nickname = "Nazwa";
        string ip = "127.0.0.1";
        string port = "7777";
        string password = "hasło (opcjonalne)";

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
                    MessageBox.Show($"SA-MP Injector zwrócił błąd (Kod: {process.ExitCode}). Gra mogła nie zostać uruchomiona poprawnie.", "Błąd uruchamiania", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }
        catch (Exception ex) {
            MessageBox.Show($"Wystąpił błąd podczas uruchamiania gry: {ex.Message}", "Błąd", MessageBoxButtons.OK, MessageBoxIcon.Error);
        }
    }
}
```

### Wykorzystanie biblioteki C++ w pliku wykonywalnym

Plik wykonywalny `samp-injector.exe` jest zbudowany na bazie biblioteki [SA-MP Injector C++](https://github.com/spc-samp/samp-injector/tree/main/libraries/cpp), która znajduje się w katalogu `libraries/cpp/`. Plik `main.cpp` wykonuje funkcjonalności tej biblioteki, aby przeprowadzić wstrzykiwanie i uruchomienie gry.

Główny plik nagłówkowy biblioteki **C++** to `libraries/samp-injector/cpp/injector.hpp`. Ponieważ biblioteka [SA-MP Injector C++](https://github.com/spc-samp/samp-injector/tree/main/libraries/cpp) jest typu **header-only**, jej użycie wymaga jedynie włączenia tego nagłówka do kodu źródłowego, bez potrzeby linkowania pliku `.lib`.

Istotny fragment `main.cpp`, który pokazuje integrację, jest następujący:
```cpp
// Pobiera argumenty wiersza poleceń
int argc;
std::unique_ptr<LPWSTR[], decltype(&LocalFree)> argv(CommandLineToArgvW(GetCommandLineW(), &argc), &LocalFree);

// ... (weryfikacja liczby argumentów i trybu wstrzykiwania) ...

// Pobiera parametry do zmiennych typu wide string
std::wstring folder = argv[2];
std::wstring nickname = argv[3];
std::wstring ip = argv[4];
std::wstring port = argv[5];
std::wstring password = (argc == 7) ? argv[6] : L"";

// Deleguje logikę wstrzykiwania do funkcji "Initialize_Game" z biblioteki
// Zauważ, że "injector.hpp" został wcześniej włączony w "main.cpp"
if (!Initialize_Game(inject_type, folder, nickname, ip, port, password))
    return 1;

Sleep(10000); // Czeka przed zakończeniem pliku wykonywalnego
```

Funkcja `Initialize_Game` działa jako interfejs wysokiego poziomu biblioteki, koordynując wszystkie operacje weryfikacji, tworzenia procesu i **wstrzykiwania bibliotek DLL**.

### Jak skompilować

Możesz skompilować `samp-injector.exe` z kodu źródłowego. Jeśli nie chcesz kompilować, możesz pobrać gotowe wersje w sekcji [Releases](https://github.com/spc-samp/samp-injector/releases).

#### Wymagania

- **Visual Studio:** Zaleca się **Visual Studio 2022** lub nowszy z zainstalowanym pakietem **"Rozwój aplikacji desktopowych w C++"**.
- **Git:** Do klonowania repozytorium (lub po prostu pobierz, klikając ten link: [Pobierz](https://github.com/spc-samp/samp-injector/archive/refs/heads/main.zip)).

#### Kroki kompilacji

1. **Sklonuj repozytorium:**
   ```bash
   git clone https://github.com/spc-samp/samp-injector.git
   cd samp-injector
   ```
2. **Otwórz rozwiązanie:**
   Przejdź do folderu `executable` i otwórz plik rozwiązania `.sln`:
   ```bash
   cd executable
   start samp-injector.sln
   ```
    Spowoduje to otwarcie projektu w **Visual Studio**.
3. **Skonfiguruj build:**
   - W **Visual Studio** sprawdź konfigurację rozwiązania. Zaleca się użycie trybów `Release` i `x86` **(32 bity)**. W kontekście **GTA:SA** oraz **SA-MP**/**OMP** architektura **x86 (32 bity)** jest obowiązkowa.
4. **Skompiluj:**
   - W menu `Kompilacja` kliknij `Skompiluj rozwiązanie` lub `Skompiluj samp-injector`.
   - Alternatywnie możesz użyć skrótów:
      - `Ctrl + Shift + B`, aby skompilować całe rozwiązanie.
      - `Ctrl + B` (jeśli skonfigurowane) do kompilacji bieżącego projektu.
   - Jeśli wszystko jest poprawnie skonfigurowane, plik wykonywalny `samp-injector.exe` zostanie wygenerowany w katalogu `executable\Release` (lub `executable\Debug`, w zależności od konfiguracji **build**).

## Biblioteka Dynamiczna (**DLL**)

Biblioteka `samp-injector.dll` oferuje **API (Application Programming Interface)** do programowego uruchamiania **GTA:SA** z **SA-MP** lub **OMP**. Jest to idealna alternatywa dla pliku wykonywalnego dla twórców launcherów, którzy chcą bardziej przejrzystej i bezpośredniej integracji, wywołując funkcję zamiast uruchamiać zewnętrzny proces.

### Funkcjonalność

Biblioteka `samp-injector.dll` aktywuje ten sam solidny przepływ pracy co biblioteka wewnętrzna, ukrywając złożoność wstrzykiwania i inicjalizacji gry:

1. **Tworzenie Zawieszonego Procesu:** Po wywołaniu uruchamia `gta_sa.exe` w stanie zawieszonym.
2. **Dynamiczne Wstrzykiwanie DLL:**
   - Dla trybu **SA-MP**, wstrzykiwana jest `samp.dll`.
   - Dla trybu **OMP**, wstrzykiwane są `samp.dll` i `omp-client.dll`.
3. **Konfiguracja Argumentów:** Parametry funkcji, takie jak **pseudonim**, **IP**, **port** i **hasło**, są przygotowywane dla `gta_sa.exe`.
4. **Wznowienie Procesu:** Po wstrzyknięciu proces gry jest wznawiany do wykonania, łącząc się bezpośrednio z serwerem.

### Jak Używać (Wywołanie API)

Aby użyć biblioteki, należy załadować `samp-injector.dll` do aplikacji i wywołać eksportowaną funkcję `Launch_Game`.

#### Kontrakt Funkcji `Launch_Game`

- **Plik DLL:** `samp-injector.dll`
- **Nazwa Eksportowanej Funkcji:** `Launch_Game`
- **Konwencja Wywoływania:** `__stdcall`
- **Typ Zwracany:** `int`
   - `0`: **Sukces.** Żądanie uruchomienia gry zostało wysłane do wątku w tle.
   - `1`: **Nieprawidłowe Argumenty.** Wymagany parametr był pusty lub tryb był nieprawidłowy. Zostanie wyświetlony komunikat o błędzie.
   - `2`: **Błąd Wątku.** Wystąpił krytyczny błąd podczas próby utworzenia wątku inicjalizującego. Zostanie wyświetlony komunikat o błędzie.

#### Parametry

Wszystkie parametry to ciągi znaków szerokich (Unicode).

- `mode` (`LPCWSTR`): Określa typ wstrzykiwania (`L"samp"` lub `L"omp"`).
- `folder` (`LPCWSTR`): Pełna ścieżka do katalogu **GTA:SA**.
- `nickname` (`LPCWSTR`): Twój pseudonim w grze.
- `ip` (`LPCWSTR`): Adres **IP** lub **nazwa domeny** serwera.
- `port` (`LPCWSTR`): Port połączenia serwera.
- `password` (`LPCWSTR`): Hasło do połączenia z serwerem. **(Ten parametr jest opcjonalny. Można przekazać `null` lub pusty ciąg `L""`, jeśli nie ma hasła)**.

### Jak Używać (Osadzone w Aplikacjach)

Przykład wywołania funkcji `Launch_Game` z **aplikacji C#**:
```csharp
using System;
using System.Runtime.InteropServices;
using System.Windows.Forms;

public class Launcher {
    // Importuje funkcję z DLL, określając kontrakt API.
    [DllImport("samp-injector.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.StdCall, EntryPoint = "Launch_Game")]
    private static extern int Launch_Game(string mode, string folder, string nickname, string ip, string port, string password);

    public static void Main(string[] args) {
        string inject_mode = "samp"; 
        string gta_folder = "C:\\Games\\GTA San Andreas"; // Uwaga: Użyj prawdziwej ścieżki!
        string nickname = "Nazwa";
        string ip = "127.0.0.1";
        string port = "7777";
        string password = "hasło (opcjonalne)"; // lub null, lub "" jeśli brak

        try {
            int result = Launch_Game(inject_mode, gta_folder, nickname, ip, port, password);
            
            if (result != 0) {
                // DLL już wyświetla szczegółowy komunikat o błędzie,
                // ale możesz tutaj zapisać lub wyświetlić inny komunikat.
                MessageBox.Show($"Wywołanie DLL zwróciło kod błędu: {result}", "Błąd w Launcherze", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }
        catch (DllNotFoundException) {
            MessageBox.Show("Błąd: samp-injector.dll nie znaleziono! Sprawdź, czy znajduje się w tym samym folderze co launcher.", "Błąd", MessageBoxButtons.OK, MessageBoxIcon.Error);
        }
        catch (Exception ex) {
            MessageBox.Show($"Wystąpił nieoczekiwany błąd: {ex.Message}", "Błąd", MessageBoxButtons.OK, MessageBoxIcon.Error);
        }
    }
}
```

### Użycie Biblioteki C++ w **DLL**

Podobnie jak w przypadku pliku wykonywalnego, `samp-injector.dll` również opiera się na bibliotece [SA-MP Injector C++](https://github.com/spc-samp/samp-injector/tree/main/libraries/cpp), która znajduje się w katalogu `libraries/cpp/`. Eksportowana funkcja `Launch_Game` działa jako wrapper, weryfikując parametry i delegując główną logikę wstrzykiwania do funkcji `Initialize_Game` biblioteki.

Główny plik nagłówkowy biblioteki **C++**, który należy włączyć, to `libraries/samp-injector/cpp/injector.hpp`. Ponieważ biblioteka [SA-MP Injector C++](https://github.com/spc-samp/samp-injector/tree/main/libraries/cpp) jest **header-only**, jej użycie wymaga jedynie włączenia tego nagłówka do kodu źródłowego, bez konieczności linkowania pliku `.lib`.

Poniższy fragment kodu z `main.cpp` w **DLL** pokazuje, jak zadanie jest delegowane do oddzielnego wątku:
```cpp
// Funkcja robocza działająca w wątku w tle
void Game_Thread_Worker(const std::wstring& mode, const std::wstring& folder, const std::wstring& nickname, const std::wstring& ip, const std::wstring& port, const std::wstring& password) {
    // Logika wstrzykiwania jest delegowana do funkcji "Initialize_Game" biblioteki.
    Initialize_Game(mode, folder, nickname, ip, port, password);
}

// Wewnątrz eksportowanej funkcji `Launch_Game`, tworzony jest wątek:
try {
    std::thread(Game_Thread_Worker, mode_str, folder_str, nickname_str, ip_str, port_str, password_str).detach();
}
// ...
```

To pokazuje, że **DLL** jest w istocie interfejsem API dla tej samej podstawowej funkcjonalności używanej przez plik wykonywalny.

### Jak Skompilować

Możesz skompilować `samp-injector.dll` z kodu źródłowego. Jeśli nie chcesz kompilować, możesz pobrać wstępnie skompilowane wersje w sekcji [Releases](https://github.com/spc-samp/samp-injector/releases).

#### Wymagania

- **Visual Studio:** Zaleca się **Visual Studio 2022** lub nowszy z zainstalowanym obciążeniem **"Rozwój aplikacji desktopowych w C++"**.
- **Git:** Do klonowania repozytorium (lub po prostu pobierz je, korzystając z tego linku: [Pobierz](https://github.com/spc-samp/samp-injector/archive/refs/heads/main.zip)).

#### Kroki Kompilacji

1. **Sklonuj Repozytorium:**
   ```bash
   git clone https://github.com/spc-samp/samp-injector.git
   cd samp-injector
   ```
2. **Otwórz Rozwiązanie:**
   Przejdź do folderu `dll` i otwórz plik rozwiązania `.sln`:
   ```bash
   cd dll
   start samp-injector.sln
   ```
   Spowoduje to otwarcie projektu w **Visual Studio**.
3. **Skonfiguruj Kompilację:**
   - W **Visual Studio** sprawdź konfigurację rozwiązania. Zaleca się użycie trybów `Release` i `x86` **(32-bitowy)**. W kontekście **GTA:SA** oraz **SA-MP**/**OMP**, architektura **x86 (32-bitowa)** jest obowiązkowa.
4. **Skompiluj:**
   - W menu `Compilation` kliknij `Compile Solution` lub `Build samp-injector`.
   - Alternatywnie możesz użyć skrótów:
      - `Ctrl + Shift + B`, aby skompilować całe rozwiązanie.
      - `Ctrl + B` (jeśli skonfigurowane) do skompilowania bieżącego projektu.
   - Jeśli wszystko jest poprawnie skonfigurowane, biblioteka `samp-injector.dll` zostanie wygenerowana w katalogu `dll\Release` (lub `dll\Debug`, w zależności od konfiguracji **build**).

## Biblioteki

Biblioteki są podstawowymi komponentami **SA-MP Injector**, zawierającymi główną logikę do manipulacji procesami, **wstrzykiwania bibliotek DLL** oraz weryfikacji parametrów. Główną zaletą korzystania z tych bibliotek jest łatwość inicjowania i wstrzykiwania, zwykle za pomocą pojedynczej funkcji (lub wywołań z określonymi parametrami dla języków skryptowych).

### Przegląd

Projekt opiera się na bibliotekach, które kapsułkują krytyczne funkcjonalności. Umożliwia to łatwą integrację możliwości uruchamiania **GTA:SA** z modułami **multiplayer** w innych projektach.

### Lista bibliotek

| Język         | Nazwa                      | Link do biblioteki/Dokumentacji     |
| ------------- | -------------------------- | ----------------------------------- |
| C++           | **SA-MP Injector C++**     | [Sprawdź bibliotekę](libraries/cpp) |
| C             | **SA-MP Injector C**       | (Wkrótce)                           |
| C#            | **SA-MP Injector C#**      | (Wkrótce)                           |
| Java          | **SA-MP Injector Java**    | (Wkrótce)                           |
| Python        | **SA-MP Injector Python**  | (Wkrótce)                           |
| Go (Golang)   | **SA-MP Injector Go**      | (Wkrótce)                           |
| Rust          | **SA-MP Injector Rust**    | (Wkrótce)                           |
| Kotlin        | **SA-MP Injector Kotlin**  | (Wkrótce)                           |
| Scala         | **SA-MP Injector Scala**   | (Wkrótce)                           |
| Lua           | **SA-MP Injector Lua**     | (Wkrótce)                           |
| Ruby          | **SA-MP Injector Ruby**    | (Wkrótce)                           |
| Visual Basic  | **SA-MP Injector VB**      | (Wkrótce)                           |
| F#            | **SA-MP Injector F#**      | (Wkrótce)                           |
| Pascal/Delphi | **SA-MP Injector P/D**     | (Wkrótce)                           |
| PowerShell    | **SA-MP Injector PS**      | (Wkrótce)                           |
| D (Dlang)     | **SA-MP Injector D**       | (Wkrótce)                           |
| Nim           | **SA-MP Injector Nim**     | (Wkrótce)                           |
| Zig           | **SA-MP Injector Zig**     | (Wkrótce)                           |
| V (VLang)     | **SA-MP Injector V**       | (Wkrótce)                           |
| Crystal       | **SA-MP Injector Crystal** | (Wkrótce)                           |
| Perl          | **SA-MP Injector Perl**    | (Wkrótce)                           |
| Racket (Lisp) | **SA-MP Injector Racket**  | (Wkrótce)                           |
| Haskell       | **SA-MP Injector Haskell** | (Wkrótce)                           |
| OCaml         | **SA-MP Injector OCaml**   | (Wkrótce)                           |

> [!TIP]
> Szczegółowa dokumentacja dla każdej biblioteki będzie dostępna w jej **odpowiednim katalogu**.

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