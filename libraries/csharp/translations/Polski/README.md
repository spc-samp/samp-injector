# SA-MP Injector C#

<div align="center">

![C#](https://img.shields.io/badge/C%23-11.0%2B-512BD4?style=for-the-badge&logo=csharp&logoColor=white)
![.NET](https://img.shields.io/badge/.NET-7.0%2B-512BD4?style=for-the-badge&logo=dotnet&logoColor=white)
![Platform](https://img.shields.io/badge/Platform-Windows-blue?style=for-the-badge&logo=windows&logoColor=white)
![Architecture](https://img.shields.io/badge/Architecture-x86%20(32--bit)-lightgrey?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)

**Biblioteka C# do programowego wstrzykiwania DLL do procesów SA-MP i OMP, umożliwiająca automatyczne łączenie z serwerami.**

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

- [SA-MP Injector C#](#sa-mp-injector-c)
  - [Języki](#języki)
  - [Spis treści](#spis-treści)
  - [Wprowadzenie i Cel](#wprowadzenie-i-cel)
  - [Filozofia Projektu](#filozofia-projektu)
    - [Interoperacyjność (P/Invoke)](#interoperacyjność-pinvoke)
    - [Zarządzanie Zasobami (`SafeHandle`)](#zarządzanie-zasobami-safehandle)
    - [Bezpieczeństwo i Niezawodność](#bezpieczeństwo-i-niezawodność)
  - [Wymagania Systemowe](#wymagania-systemowe)
    - [Środowisko Programistyczne](#środowisko-programistyczne)
    - [Środowisko Uruchomieniowe](#środowisko-uruchomieniowe)
  - [Instalacja i Podstawowe Użycie](#instalacja-i-podstawowe-użycie)
    - [Dodawanie do Twojego Projektu](#dodawanie-do-twojego-projektu)
    - [Przykład Użycia](#przykład-użycia)
  - [Komponenty Biblioteki](#komponenty-biblioteki)
    - [1. `Constants.cs`](#1-constantscs)
    - [2. `InjectionType.cs`](#2-injectiontypecs)
    - [3. `Injector.cs`](#3-injectorcs)
    - [4. `InjectorCore.cs`](#4-injectorcorecs)
    - [5. `InputValidator.cs`](#5-inputvalidatorcs)
    - [6. `NativeImports.cs`](#6-nativeimportscs)
    - [7. `ProcessHandler.cs`](#7-processhandlercs)
    - [8. `SafeHandles.cs`](#8-safehandlescs)
  - [Szczegółowy Cykl Wstrzykiwania DLL](#szczegółowy-cykl-wstrzykiwania-dll)
    - [1. Walidacja Danych Wejściowych](#1-walidacja-danych-wejściowych)
    - [2. Tworzenie Procesu Gry (Wstrzymany)](#2-tworzenie-procesu-gry-wstrzymany)
    - [3. Wstrzykiwanie `samp.dll`](#3-wstrzykiwanie-sampdll)
    - [4. Wstrzykiwanie `omp-client.dll` (Opcjonalne, Zależne od SA-MP)](#4-wstrzykiwanie-omp-clientdll-opcjonalne-zależne-od-sa-mp)
    - [Wznowienie Głównego Wątku Gry](#wznowienie-głównego-wątku-gry)
  - [Obsługa Błędów i Przypadki Awarii](#obsługa-błędów-i-przypadki-awarii)
    - [Błędy Walidacji Danych Wejściowych](#błędy-walidacji-danych-wejściowych)
      - [Nieprawidłowy Nickname](#nieprawidłowy-nickname)
      - [Nieprawidłowy Port](#nieprawidłowy-port)
      - [Brakujące Pliki Gry/DLL](#brakujące-pliki-grydll)
    - [Błędy podczas Tworzenia Procesu](#błędy-podczas-tworzenia-procesu)
      - [Niepowodzenie Tworzenia Procesu](#niepowodzenie-tworzenia-procesu)
    - [Błędy podczas Wstrzykiwania DLL](#błędy-podczas-wstrzykiwania-dll)
      - [Uchwyt `kernel32.dll` Niedostępny](#uchwyt-kernel32dll-niedostępny)
      - [Funkcja `LoadLibraryA` Niedostępna](#funkcja-loadlibrarya-niedostępna)
      - [Niepowodzenie Alokacji Pamięci Zdalnej](#niepowodzenie-alokacji-pamięci-zdalnej)
      - [Niepowodzenie Zapisu do Pamięci Procesu](#niepowodzenie-zapisu-do-pamięci-procesu)
      - [Niepowodzenie Tworzenia Zdalnego Wątku](#niepowodzenie-tworzenia-zdalnego-wątku)
      - [Timeout lub Błąd podczas Oczekiwania na Wstrzyknięcie](#timeout-lub-błąd-podczas-oczekiwania-na-wstrzyknięcie)
      - [Wstrzyknięcie DLL Nie powiodło się lub Zwróciło Błąd](#wstrzyknięcie-dll-nie-powiodło-się-lub-zwróciło-błąd)
    - [Błąd podczas Wznawiania Wątku Gry](#błąd-podczas-wznawiania-wątku-gry)
  - [Licencja](#licencja)
    - [Warunki użytkowania](#warunki-użytkowania)
      - [1. Przyznane uprawnienia](#1-przyznane-uprawnienia)
      - [2. Obowiązkowe warunki](#2-obowiązkowe-warunki)
      - [3. Prawa autorskie](#3-prawa-autorskie)
      - [4. Wyłączenie gwarancji i ograniczenie odpowiedzialności](#4-wyłączenie-gwarancji-i-ograniczenie-odpowiedzialności)

## Wprowadzenie i Cel

Biblioteka **SA-MP Injector C#** to rozwiązanie w C# zaprojektowane w celu uproszczenia automatycznego uruchamiania i łączenia klientów San Andreas Multiplayer (SA-MP) i Open Multiplayer (OMP) z serwerami. Działa jako narzędzie do wstrzykiwania DLL (Dynamic Link Library), programowo ładując biblioteki `samp.dll` lub `omp-client.dll` do procesu gry Grand Theft Auto: San Andreas (`gta_sa.exe`).

Głównym celem tej biblioteki jest umożliwienie innym aplikacjom C# (takim jak niestandardowe launchery, narzędzia do zarządzania serwerem lub inne narzędzia) uruchamiania gry z określonymi parametrami (nickname, IP, port i hasło) w sposób przezroczysty dla użytkownika, automatyzując proces łączenia się z serwerem SA-MP/OMP.

## Filozofia Projektu

Projekt **SA-MP Injector C#** skupia się na niezawodności, bezpieczeństwie i uproszczonym interfejsie użytkownika, hermetyzując złożoność operacji systemowych niskiego poziomu.

### Interoperacyjność (P/Invoke)

Podstawowa funkcjonalność wstrzykiwania DLL i tworzenia wstrzymanych procesów jest z natury operacją systemową niskiego poziomu. W tym celu biblioteka szeroko wykorzystuje funkcję **P/Invoke (Platform Invoke)** platformy .NET, umożliwiając wywoływanie natywnych funkcji API systemu Windows (głównie z `kernel32.dll`) bezpośrednio z kodu C#. Jest to widoczne w deklaracji metod `partial` oraz w użyciu atrybutu `[LibraryImport(KERNEL32, SetLastError = true)]`.

### Zarządzanie Zasobami (`SafeHandle`)

Operacje na zasobach systemu operacyjnego, takie jak "uchwyty" do procesów i wątków, wymagają starannego zarządzania, aby uniknąć wycieków pamięci lub zasobów. Biblioteka wykorzystuje klasy pochodzące od `SafeHandle` (`SafeProcessHandle` i `SafeThreadHandle`), aby zapewnić, że te zasoby są zawsze prawidłowo zwalniane, nawet w przypadku wyjątków. Jest to zgodne z zasadą **RAII (Resource Acquisition Is Initialization)** z C++ i rozszerza ją na środowisko .NET.

### Bezpieczeństwo i Niezawodność

Biblioteka zawiera kilka warstw bezpieczeństwa:
- **Walidacja Danych Wejściowych:** Wszystkie dane wejściowe dostarczone przez użytkownika są rygorystycznie sprawdzane przed rozpoczęciem jakiejkolwiek krytycznej operacji, co minimalizuje ryzyko błędów wykonania lub nieoczekiwanych zachowań.
- **Obsługa Błędów:** Wywołania natywnych funkcji API są połączone ze sprawdzaniem błędów (`SetLastError = true` i `Marshal.GetLastWin32Error()`), aby dostarczyć szczegółowe i zrozumiałe komunikaty o błędach.
- **Zakończenie Procesu:** W przypadku awarii podczas procesu wstrzykiwania, nowo utworzony proces gry jest automatycznie zamykany, aby uniknąć pozostawienia "procesów-zombie" w stanie uruchomionym.

## Wymagania Systemowe

### Środowisko Programistyczne

- **.NET SDK 7.0 lub nowszy:** Biblioteka jest zbudowana dla `net7.0-windows`.
- **C# 11.0 lub nowszy:** Wymagany dla funkcji takich jak `ImplicitUsings`, `Nullable`, `AllowUnsafeBlocks` i `LibraryImport`.
- **Visual Studio 2022 lub kompatybilne środowisko programistyczne:** Do budowania i integrowania biblioteki.
- **Platforma Kompilacji:** `x86 (32-bit)` jest wymaganym celem ze względu na architekturę `gta_sa.exe` i bibliotek DLL SA-MP/OMP.

```xml
<!-- samp-injector-csharp.csproj -->
<Project Sdk="Microsoft.NET.Sdk">
    <PropertyGroup>
        <TargetFrameworks>net7.0-windows</TargetFrameworks>
        <PlatformTarget>x86</PlatformTarget> <!-- KRYTYCZNE: Musi być x86 -->
        <ImplicitUsings>enable</ImplicitUsings>
        <Nullable>enable</Nullable>
        <UseWindowsForms>true</UseWindowsForms>
        <AllowUnsafeBlocks>true</AllowUnsafeBlocks> <!-- Wymagane dla zaawansowanego P/Invoke -->
    </PropertyGroup>
</Project>
```

### Środowisko Uruchomieniowe

- **System Operacyjny:** Windows (dowolna nowoczesna wersja kompatybilna z .NET 7.0+).
- **Grand Theft Auto: San Andreas (GTA: SA):** Wymagana jest instalacja gry.
- **Biblioteki DLL klienta SA-MP lub OMP:** `samp.dll` lub `omp-client.dll` muszą znajdować się w głównym katalogu gry, w zależności od pożądanego typu wstrzyknięcia.

## Instalacja i Podstawowe Użycie

### Dodawanie do Twojego Projektu

Najprostszym sposobem użycia tej biblioteki jest dodanie projektu `Samp_Injector_CSharp` jako referencji do własnego projektu C#.

1. Sklonuj lub pobierz repozytorium biblioteki.
2. W Visual Studio kliknij prawym przyciskiem myszy na "Dependencies" (lub "References") w swoim projekcie.
3. Wybierz "Add Project Reference...".
4. Przejdź do katalogu biblioteki i dodaj projekt `samp-injector-csharp.csproj`.

### Przykład Użycia

Aby uruchomić grę i połączyć się z serwerem, wystarczy wywołać metodę statyczną `Injector.Initialize_Game`.

```csharp
using Samp_Injector_CSharp;
using System;
using System.Windows.Forms; // Dla MessageBox, jeśli to nie jest projekt WinForms

namespace Launcher {
    public partial class Main : Form {
        public Main() {
            InitializeComponent();
        }

        private void Connect(object sender, EventArgs e) {
            string inject_type = "SAMP"; // "SAMP" lub "OMP"
            string game_folder = @"C:\Games\GTA San Andreas"; // Ścieżka do folderu GTA: SA
            string nickname = "Nazwa";
            string ip = "127.0.0.1";
            string port = "7777";
            string password = ""; // Pozostaw puste, jeśli nie ma hasła

            // Przykład wstrzyknięcia SA-MP
            Injector.Initialize_Game(inject_type, game_folder, nickname, ip, port, password);

            // Jeśli to OMP, zmień inject_type:
            // inject_type = "OMP";
            // Injector.Initialize_Game(inject_type, game_folder, nickname, ip, port, password);
        }
    }
}
```

## Komponenty Biblioteki

Biblioteka jest zorganizowana w kilku plikach, z których każdy ma jasno określoną odpowiedzialność, co promuje organizację, łatwość konserwacji i separację odpowiedzialności. Poniżej znajduje się szczegółowy opis każdego komponentu.

### 1. `Constants.cs`

Ten plik jest scentralizowanym repozytorium wszystkich stałych i niezmiennych wartości używanych w całej bibliotece. Jego istnienie ułatwia konserwację kodu, czytelność i spójność, zapewniając, że krytyczne wartości są zdefiniowane w jednym miejscu.

Organizacja stałych według kategorii ułatwia zrozumienie ich celu:

- **Game Related Constants**
   - `MIN_PORT`: Definiuje minimalną dozwoloną wartość portu połączenia z serwerem (1).
   - `MAX_PORT`: Definiuje maksymalną dozwoloną wartość portu połączenia z serwerem (65535).
   - `MAX_NICKNAME_LENGTH`: Określa maksymalną dozwoloną długość pseudonimu gracza (23 znaki), limit narzucony przez samego klienta SA-MP/OMP.

- **File Names**
   - `SAMP_DLL_NAME`: Nazwa pliku głównej biblioteki klienta SA-MP (`"samp.dll"`).
   - `OMP_DLL_NAME`: Nazwa pliku biblioteki klienta Open Multiplayer (`"omp-client.dll"`), używana przy wstrzykiwaniu typu OMP.
   - `GAME_EXE_NAME`: Nazwa pliku wykonywalnego gry Grand Theft Auto: San Andreas (`"gta_sa.exe"`).

- **System Libraries and Functions**
   - `KERNEL32_DLL`: Nazwa biblioteki systemowej Windows, która zawiera kluczowe funkcje do manipulacji procesami i pamięcią (`"kernel32.dll"`).
   - `LOAD_LIBRARY_FUNC`: Nazwa funkcji w `kernel32.dll` odpowiedzialnej za dynamiczne ładowanie biblioteki (`"LoadLibraryA"`).

- **Command Line Arguments**
   - `CMD_ARGS_PART1`: Początkowa część argumentów wiersza poleceń dla gry (`"-c -n "`).
   - `CMD_ARGS_PART2`: Separator dla adresu IP (`" -h "`).
   - `CMD_ARGS_PART3`: Separator dla portu (`" -p "`).
   - `CMD_ARGS_PART4_PASSWORD`: Prefiks dla argumentu hasła (`" -z "`), używany tylko, jeśli hasło zostało podane.
   - `CMD_ARGS_BASE_LENGTH`: Domyślna długość stałych części wiersza poleceń, z wyłączeniem pliku wykonywalnego i wartości użytkownika (14 znaków).
   - `CMD_ARG_PASSWORD_LENGTH`: Długość prefiksu argumentu hasła (4 znaki).

- **Error Message Titles**
   - `ERROR_TITLE_SAMP`: Domyślny tytuł dla okien dialogowych błędów związanych z awariami SA-MP (`"SA-MP Injector Error - SPC"`).
   - `ERROR_TITLE_OMP`: Domyślny tytuł dla okien dialogowych błędów związanych z awariami OMP (`"OMP Injector Error - SPC"`).

- **Process Creation Flags**
   - `CREATE_SUSPENDED`: Flaga, która instruuje system operacyjny, aby utworzył proces i jego główny wątek w stanie wstrzymanym (`0x00000004`). Jest to kluczowe dla wstrzyknięcia DLL, zanim gra zacznie się wykonywać.
   - `PROCESS_CREATION_FLAGS`: Kombinacja flag tworzenia procesu, obecnie zdefiniowana tylko jako `CREATE_SUSPENDED`.

- **Timeouts**
   - `DLL_INJECTION_TIMEOUT_MS`: Maksymalny czas (w milisekundach), przez który biblioteka będzie czekać na zakończenie zdalnego wątku odpowiedzialnego za wstrzyknięcie DLL (10000ms = 10 sekund).

- **Memory Allocation Flags**
   - `MEM_COMMIT`: Flaga, która rezerwuje strony w pamięci wirtualnej i je "zatwierdza" (przydziela pamięć fizyczną) (`0x1000`).
   - `MEM_RESERVE`: Flaga, która tylko rezerwuje zakres przestrzeni adresowej wirtualnej do późniejszego wykorzystania (`0x2000`).
   - `MEM_RELEASE`: Flaga, która zwalnia i uwalnia region stron (`0x8000`).
   - `MEMORY_ALLOCATION_TYPE`: Kombinacja `MEM_COMMIT` i `MEM_RESERVE`, używana do alokacji pamięci na ścieżkę DLL w zdalnym procesie.
   - `MEMORY_PROTECTION`: Definiuje uprawnienia ochrony pamięci (obecnie `0x04`, co odpowiada `PAGE_READWRITE` w API Windows, pozwalając na odczyt i zapis w przydzielonej pamięci).

### 2. `InjectionType.cs`

Ten plik definiuje prosty enum, aby zapewnić bezpieczny i jasny sposób określania typu wstrzyknięcia do wykonania. Użycie `enum` zamiast ciągów znaków (`"samp"`, `"omp"`) zapobiega błędom literowym i czyni kod bardziej czytelnym i niezawodnym.

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

Ten plik jest publiczną fasadą (Facade) biblioteki, służącą jako jedyny punkt wejścia dla aplikacji klienckich. Abstrakcjonizuje całą wewnętrzną złożoność procesu wstrzykiwania w jednej metodzie statycznej.

- **Główna Odpowiedzialność:** Metoda `Initialize_Game` otrzymuje wszystkie niezbędne parametry jako ciągi znaków, określa typ wstrzyknięcia i deleguje pracę do `Injector_Core`. Jest również odpowiedzialna za przechwytywanie wyniku operacji i prezentowanie komunikatów o błędach użytkownikowi końcowemu za pomocą `MessageBox`, co zapewnia spójną interakcję z użytkownikiem.

```csharp
// Fragment z Injector.cs
public static class Injector {
    private static readonly Injector_Core s_core = new();

    public static void Initialize_Game(string inject_type_str, string folder, string nickname, string ip, string port, string password) {
        // ... Logika konwersji inject_type_str na Injection_Type ...

        if (!s_core.Try_Initialize_Game(type, folder, nickname, ip, port, password, out string error_message)) {
            string error_title = (type == Injection_Type.OMP) ? Constants.ERROR_TITLE_OMP : Constants.ERROR_TITLE_SAMP;
            MessageBox.Show(error_message, error_title, MessageBoxButtons.OK, MessageBoxIcon.Error);
        }
    }
}
```

### 4. `InjectorCore.cs`

To jest "mózg" biblioteki, gdzie orkiestrowana jest sekwencja operacji wstrzykiwania. Łączy walidatory danych wejściowych z obsługą procesów w celu wykonania pełnego przepływu pracy.

- **Główna Odpowiedzialność:** Metoda `Try_Initialize_Game` definiuje logikę krok po kroku: waliduje dane wejściowe, tworzy proces gry w stanie wstrzymanym, wstrzykuje niezbędne DLL (`samp.dll` i opcjonalnie `omp-client.dll`), a jeśli wszystko się powiedzie, wznawia wątek gry. Kluczowym aspektem jest blok `finally`, który zapewnia, że proces gry zostanie zakończony (`Kill()`) w przypadku jakiejkolwiek awarii podczas etapów wstrzykiwania, unikając "procesów-zombie".

```csharp
// Fragment z InjectorCore.cs
internal sealed class Injector_Core {
    public bool Try_Initialize_Game(...) {
        // ... Walidacja danych wejściowych ...

        using Process_Handler.Process_Info process_info = Process_Handler.Create_Game_Process(...);
        
        // ...
        bool success = false;
        try {
            // ... Wstrzyknięcie samp.dll ...
            // ... Opcjonalne wstrzyknięcie omp-client.dll ...
            // ... Wznowienie wątku gry ...
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

Działa jako pierwsza linia obrony biblioteki, zapewniając, że przetwarzane są tylko prawidłowe i bezpieczne dane. Wstępna walidacja zapobiega wyjątkom niskiego poziomu i pozwala bibliotece dostarczać jasne i użyteczne komunikaty o błędach.

- **Główna Odpowiedzialność:** Metoda statyczna `Try_Validate` wykonuje serię sprawdzeń, w tym format pseudonimu, zakres numeryczny portu i, co kluczowe, istnienie niezbędnych plików (`gta_sa.exe`, `samp.dll` itp.) w określonym katalogu. Jeśli którekolwiek sprawdzenie zawiedzie, zwraca `false` i wypełnia `out string` opisem błędu.

```csharp
// Fragment z InputValidator.cs
internal static class Input_Validator {
    public static bool Try_Validate(...) {
        if (nickname.Length > Constants.MAX_NICKNAME_LENGTH)
            return (error_message = $"Długość pseudonimu przekracza maksymalną...") != null && false;

        string game_exe_path = Path.Combine(folder_path, Constants.GAME_EXE_NAME);
        if (!File.Exists(game_exe_path))
            return (error_message = $"Plik wykonywalny gry nie został znaleziony...") != null && false;
        
        // ...
        return true;
    }
}
```

### 6. `NativeImports.cs`

Ten plik jest mostem między zarządzanym kodem C# a niezardządzanymi, natywnymi API systemu Windows. Wykorzystuje funkcję interoperacyjności P/Invoke do deklarowania sygnatur funkcji z `kernel32.dll`.

- **Główna Odpowiedzialność:** Deklarowanie metod `extern` z atrybutami `[LibraryImport]` lub `[DllImport]`, które odpowiadają funkcjom API systemu Windows, takim jak `CreateProcessA`, `VirtualAllocEx` i `CreateRemoteThread`. Definiuje również struktury danych (`Startup_Info`, `Process_Information`) z układem pamięci kompatybilnym z kodem natywnym. W celu optymalizacji, uchwyty do `kernel32.dll` i adres funkcji `LoadLibraryA` są ładowane statycznie podczas inicjalizacji.

```csharp
// Fragment z NativeImports.cs
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

Jest to warstwa niskiego poziomu, która wykonuje operacje manipulacji procesami. Wykorzystuje funkcje zaimportowane z `NativeImports.cs` do bezpośredniej interakcji z systemem operacyjnym.

- **Główne Odpowiedzialności:**
   1. **`Create_Game_Process`**: Buduje wiersz poleceń i uruchamia `gta_sa.exe` z flagą `CREATE_SUSPENDED`.
   2. **`Inject_DLL`**: Implementuje technikę wstrzykiwania DLL poprzez tworzenie zdalnego wątku. Jest to najbardziej krytyczna funkcja, która orkiestruje alokację pamięci, zapis i zdalne wykonanie `LoadLibraryA`.
   3. **`Resume_Game_Thread`**: Wykonuje ostatni krok "odmrażania" głównego wątku gry.

```csharp
// Fragment z ProcessHandler.cs
internal static bool Inject_DLL(SafeProcessHandle process_handle, string dll_path, out string error_message) {
    // ... Alokacja i zapis do pamięci zdalnej ...

    IntPtr remote_thread = Native_Imports.CreateRemoteThread(process_handle, IntPtr.Zero, 0, Native_Imports.load_library_address, remote_memory, 0, IntPtr.Zero);

    if (remote_thread == IntPtr.Zero)
        return (error_message = $"Nie udało się utworzyć zdalnego wątku...") != null && false;
    
    // ... Oczekiwanie na zakończenie i sprawdzanie wyniku ...
    return true;
}
```

### 8. `SafeHandles.cs`

Ten plik implementuje dobrą praktykę interoperacyjności: użycie `SafeHandle` do zarządzania niezarządzanymi zasobami. Zapewnia to, że uchwyty procesów i wątków systemu Windows są zwalniane w sposób deterministyczny i bezpieczny.

- **Główna Odpowiedzialność:** Klasy `SafeProcessHandle` i `SafeThreadHandle` dziedziczą po `SafeHandleZeroOrMinusOneIsInvalid`. Hermetyzują one `IntPtr`, który reprezentuje natywny uchwyt. Główną zaletą jest implementacja metody `ReleaseHandle`, która jest gwarantowana przez środowisko uruchomieniowe .NET do wywołania, gdy obiekt jest usuwany (np. na końcu bloku `using`), zapobiegając wyciekom zasobów.

```csharp
// Fragment z SafeHandles.cs
internal sealed class SafeProcessHandle : SafeHandleZeroOrMinusOneIsInvalid {
    // ... Konstruktory ...

    protected override bool ReleaseHandle() {
        // To wywołanie jest gwarantowane przez .NET w celu zwolnienia natywnego uchwytu.
        return Native_Imports.CloseHandle(handle);
    }
}
```

## Szczegółowy Cykl Wstrzykiwania DLL

Proces wstrzykiwania DLL to sekwencja krytycznych kroków, które muszą być wykonane z precyzją, aby zakończyły się sukcesem. Biblioteka **SA-MP Injector C#** orkiestruje to w następujący sposób:

### 1. Walidacja Danych Wejściowych

Przed jakąkolwiek interakcją z systemem, wszystkie parametry dostarczone przez użytkownika (ścieżka do folderu gry, pseudonim, IP, port i hasło) są sprawdzane przez `Input_Validator`. Obejmuje to:
- Sprawdzenie, czy pseudonim mieści się w limitach długości i nie jest pusty.
- Upewnienie się, że port jest prawidłową liczbą i mieści się w dopuszczalnym zakresie (1-65535).
- Potwierdzenie, że `gta_sa.exe`, `samp.dll` i `omp-client.dll` (jeśli `Injection_Type` to OMP) istnieją w oczekiwanych ścieżkach.

> [!NOTE]
> Ten krok prewencyjny jest kluczowy, aby uniknąć nieoczekiwanych awarii API i zapewnić użytkownikowi jasną informację zwrotną.

### 2. Tworzenie Procesu Gry (Wstrzymany)

Biblioteka używa `Native_Imports.CreateProcessA` do uruchomienia `gta_sa.exe`. Jednak kluczowym szczegółem jest użycie flagi `Constants.CREATE_SUSPENDED`.
- **Tworzenie Wstrzymane:** Ta flaga powoduje, że system Windows tworzy proces i jego główny wątek, ale umieszcza go w stanie wstrzymanym, uniemożliwiając rozpoczęcie wykonywania kodu gry.
- **Wiersz Poleceń:** Wiersz poleceń jest starannie konstruowany przez `Process_Handler.Build_Full_Command_Args_ANSI`, aby zawierał wszystkie parametry połączenia z serwerem (`-c -n <nickname> -h <ip> -p <port> -z <password>`).
- **Uchwyty Procesu/Wątku:** `CreateProcessA` zwraca uchwyty do procesu i głównego wątku, które są hermetyzowane w `SafeProcessHandle` i `SafeThreadHandle` w celu bezpiecznego zarządzania zasobami.

> [!IMPORTANT]
> Tworzenie wstrzymane jest kluczowe dla wstrzyknięcia. Gdyby gra zaczęła się wykonywać przed wstrzyknięciem, mogłaby zainicjować własne mechanizmy bezpieczeństwa, a `samp.dll`/`omp-client.dll` mogłyby zostać załadowane poza naszą kontrolą, co uczyniłoby wstrzyknięcie bardziej złożonym lub nieskutecznym.

### 3. Wstrzykiwanie `samp.dll`

Gdy proces gry jest wstrzymany, funkcja `Process_Handler.Inject_DLL` wykonuje następujące kroki:
1. **Pobranie `LoadLibraryA`:** Adres funkcji `LoadLibraryA` (z `kernel32.dll`) w procesie gry jest pobierany. Jest to funkcja, której system Windows używa do ładowania bibliotek DLL.
2. **Alokacja Pamięci Zdalnej:** `Native_Imports.VirtualAllocEx` jest używana do przydzielenia bloku pamięci w wirtualnej przestrzeni adresowej procesu `gta_sa.exe`. Rozmiar bloku jest wystarczający do przechowania pełnej ścieżki do `samp.dll`.
3. **Zapis Ścieżki DLL:** Pełna ścieżka do pliku `samp.dll` jest zapisywana w nowo przydzielonej pamięci w procesie gry za pomocą `Native_Imports.WriteProcessMemory`.
4. **Tworzenie Zdalnego Wątku:** `Native_Imports.CreateRemoteThread` jest wywoływana w celu utworzenia nowego wątku w procesie `gta_sa.exe`. Ten wątek jest instruowany, aby wykonać `LoadLibraryA` z adresem ciągu znaków ścieżki DLL jako jedynym argumentem.
5. **Oczekiwanie na Zakończenie:** Biblioteka czeka określony czas (`Constants.DLL_INJECTION_TIMEOUT_MS`) na zakończenie wykonywania zdalnego wątku, co wskazuje, że `LoadLibraryA` próbowała załadować DLL.
6. **Sprawdzenie Wyniku:** Kod wyjścia zdalnego wątku jest sprawdzany. Jeśli `LoadLibraryA` zakończyła się sukcesem, zwraca bazowy adres załadowanej DLL. Wartość zerowa lub niepowodzenie w uzyskaniu kodu wyjścia wskazuje, że wstrzyknięcie nie powiodło się.
7. **Czyszczenie:** Przydzielona pamięć zdalna jest zwalniana (`Native_Imports.VirtualFreeEx`), a uchwyt zdalnego wątku jest zamykany (`Native_Imports.CloseHandle`).

### 4. Wstrzykiwanie `omp-client.dll` (Opcjonalne, Zależne od SA-MP)

> [!TIP]
> Wstrzyknięcie `omp-client.dll` **zawsze następuje po udanym wstrzyknięciu `samp.dll`**. Klient OMP wykorzystuje infrastrukturę SA-MP, dlatego `samp.dll` jest wymagany.

Jeśli określony `Injection_Type` to `OMP`, krok 3 jest powtarzany w celu wstrzyknięcia `omp-client.dll`. Logika jest identyczna, co zapewnia, że obie biblioteki niezbędne dla OMP są załadowane przed pełnym uruchomieniem gry.

### Wznowienie Głównego Wątku Gry

Na koniec, po pomyślnym wstrzyknięciu wszystkich niezbędnych bibliotek DLL, wywoływana jest funkcja `Process_Handler.Resume_Game_Thread`. Ta funkcja używa `Native_Imports.ResumeThread`, aby umożliwić kontynuację wykonywania głównego wątku `gta_sa.exe`. Gra uruchamia się teraz z już załadowanymi bibliotekami SA-MP/OMP i zastosowanymi argumentami wiersza poleceń do połączenia z serwerem.

## Obsługa Błędów i Przypadki Awarii

Biblioteka została zaprojektowana tak, aby dostarczać jasnych informacji zwrotnych w przypadku awarii. Większość błędów jest przechwytywana, a opisowy `error_message` jest zwracany do wyświetlenia użytkownikowi, zazwyczaj za pomocą `MessageBox`.

### Błędy Walidacji Danych Wejściowych

Te błędy występują przed jakąkolwiek operacją systemową i są wykrywane przez `Input_Validator`.

#### Nieprawidłowy Nickname

- **Komunikat o Błędzie (Przykład 1):** `"Nickname cannot be empty. Please provide a valid nickname."`
- **Komunikat o Błędzie (Przykład 2):** `"Nickname length exceeds the maximum allowed of 23 characters. Please use a shorter nickname."`
- **Dlaczego:** Pole pseudonimu jest puste lub przekracza maksymalny limit 23 znaków.
- **Rozwiązanie:** Użytkownik musi podać prawidłowy pseudonim, który przestrzega limitu znaków.

#### Nieprawidłowy Port

- **Komunikat o Błędzie (Przykład 1):** `"Invalid port format. The port must be a numeric value. Please provide a valid integer for the port."`
- **Komunikat o Błędzie (Przykład 2):** `"The specified port number (70000) is outside the valid range of 1 to 65535. Please provide a valid port."`
- **Dlaczego:** Podany port nie jest liczbą całkowitą lub znajduje się poza prawidłowym zakresem od 1 do 65535.
- **Rozwiązanie:** Użytkownik musi wprowadzić prawidłowy numer portu, mieszczący się w określonym zakresie.

#### Brakujące Pliki Gry/DLL

- **Komunikat o Błędzie (Przykład 1):** `"Game executable not found. Please ensure 'gta_sa.exe' exists at the specified path: C:\Program Files (x86)\Rockstar Games\GTA San Andreas\gta_sa.exe"`
- **Komunikat o Błędzie (Przykład 2):** `"SA-MP library not found. Please ensure 'samp.dll' exists at the specified path: C:\Program Files (x86)\Rockstar Games\GTA San Andreas\samp.dll"`
- **Komunikat o Błędzie (Przykład 3, OMP):** `"OMP library not found. Please ensure 'omp-client.dll' exists at the specified path for OMP injection: C:\Program Files (x86)\Rockstar Games\GTA San Andreas\omp-client.dll"`
- **Dlaczego:** Plik wykonywalny gry (`gta_sa.exe`), biblioteka DLL SA-MP (`samp.dll`) lub biblioteka DLL OMP (`omp-client.dll`) nie zostały znalezione w podanym folderze gry.
- **Rozwiązanie:** Użytkownik powinien sprawdzić ścieżkę do folderu gry i upewnić się, że wszystkie wymagane pliki są obecne.

### Błędy podczas Tworzenia Procesu

Te błędy występują, gdy biblioteka próbuje uruchomić `gta_sa.exe`.

#### Niepowodzenie Tworzenia Procesu

- **Komunikat o Błędzie (Przykład):** `"Failed to create game process. Ensure 'gta_sa.exe' is not running and you have sufficient permissions to execute the file. System Error: Access is denied."`
- **Dlaczego:**
   - **Plik w Użyciu:** `gta_sa.exe` może już być uruchomiony, co uniemożliwia utworzenie nowej instancji, lub system operacyjny może mieć blokadę na pliku.
   - **Uprawnienia:** Użytkownik uruchamiający aplikację może nie mieć wystarczających uprawnień do uruchomienia nowego procesu lub dostępu do pliku wykonywalnego gry.
   - **Nieprawidłowa/Uszkodzona Ścieżka:** Chociaż podstawowa walidacja sprawdza istnienie, mogą wystąpić problemy z uprawnieniami do odczytu/wykonania lub plik wykonywalny może być uszkodzony.
- **Rozwiązanie:** Upewnij się, że żadna inna instancja `gta_sa.exe` nie jest uruchomiona. Uruchom aplikację jako administrator, jeśli to możliwe. Sprawdź integralność pliku `gta_sa.exe`.

### Błędy podczas Wstrzykiwania DLL

Są to najbardziej krytyczne błędy, które występują podczas próby wstrzyknięcia `samp.dll` lub `omp-client.dll` do procesu gry.

#### Uchwyt `kernel32.dll` Niedostępny

- **Komunikat o Błędzie:** `"Failed to obtain a handle to kernel32.dll. This is an essential system library and this error indicates a severe system issue."`
- **Dlaczego:** Biblioteka `kernel32.dll`, kluczowa dla operacji systemowych w systemie Windows, nie mogła zostać załadowana lub jej uchwyt nie mógł zostać uzyskany. Jest to niezwykle rzadkie i sugeruje poważny problem z systemem operacyjnym.
- **Rozwiązanie:** Ponowne uruchomienie systemu może rozwiązać problem. W przeciwnym razie wskazuje to na głębszy problem z instalacją systemu Windows.

#### Funkcja `LoadLibraryA` Niedostępna

- **Komunikat o Błędzie:** `"Failed to find the address of the LoadLibraryA function in kernel32.dll. This is critical for injecting the DLL."`
- **Dlaczego:** Funkcja `LoadLibraryA`, niezbędna do dynamicznego ładowania bibliotek DLL, nie mogła zostać znaleziona w `kernel32.dll`. Podobnie jak poprzedni błąd, jest to rzadki problem niskiego poziomu.
- **Rozwiązanie:** Podobne do niedostępności uchwytu `kernel32.dll`.

#### Niepowodzenie Alokacji Pamięci Zdalnej

- **Komunikat o Błędzie:** `"Failed to allocate memory in the target process. This might be due to insufficient permissions or process protection mechanisms."`
- **Dlaczego:** Biblioteka nie mogła przydzielić bloku pamięci w przestrzeni adresowej `gta_sa.exe`.
   - **Uprawnienia:** Aplikacja może nie mieć niezbędnych uprawnień do modyfikowania przestrzeni pamięci innego procesu.
   - **Ochrona Procesu:** Proces `gta_sa.exe` lub system operacyjny może stosować mechanizmy ochrony przed wstrzykiwaniem kodu.
   - **Przestrzeń Adresowa:** W skrajnych przypadkach przestrzeń adresowa procesu może być pofragmentowana lub pozbawiona wystarczającej ilości ciągłej pamięci, choć jest to mało prawdopodobne dla rozmiaru ciągu ścieżki DLL.
- **Rozwiązanie:** Uruchom aplikację jako administrator. Sprawdź, czy oprogramowanie zabezpieczające (antywirus, anti-cheat) może blokować alokację pamięci w innych procesach.

#### Niepowodzenie Zapisu do Pamięci Procesu

- **Komunikat o Błędzie:** `"Failed to write DLL path to the target process memory. Verify process permissions and ensure the DLL path is accessible."`
- **Dlaczego:** Biblioteka przydzieliła pamięć w procesie gry, ale nie udało się zapisać ścieżki DLL w tej lokalizacji.
   - **Uprawnienia:** Podobnie jak w przypadku niepowodzenia alokacji pamięci, może to być problem z uprawnieniami do zapisu.
   - **Ochrona:** Ochrona pamięci systemu operacyjnego lub anti-cheat może uniemożliwiać zapis.
- **Rozwiązanie:** Sprawdź uprawnienia i oprogramowanie zabezpieczające.

#### Niepowodzenie Tworzenia Zdalnego Wątku

- **Komunikat o Błędzie (Przykład):** `"Failed to create a remote thread in the target process to execute the DLL injection. This could be due to security restrictions or process state. System Error: Not enough memory resources are available to process this command."`
- **Dlaczego:** API `CreateRemoteThread` nie powiodło się przy tworzeniu nowego wątku w procesie `gta_sa.exe` w celu wywołania `LoadLibraryA`.
   - **Ochrona Procesu/Anti-Cheat:** Wiele systemów anti-cheat i mechanizmów ochrony systemu operacyjnego monitoruje i blokuje tworzenie zdalnych wątków, ponieważ jest to powszechna technika wstrzykiwania.
   - **Stan Procesu:** Proces gry może być w niespójnym stanie, który uniemożliwia tworzenie wątków.
- **Rozwiązanie:** Tymczasowo wyłącz oprogramowanie anti-cheat lub antywirusowe. Spróbuj uruchomić aplikację jako administrator.

#### Timeout lub Błąd podczas Oczekiwania na Wstrzyknięcie

- **Komunikat o Błędzie (Przykład):** `"Timeout or error waiting for DLL injection to complete. System Error: The wait operation timed out."`
- **Dlaczego:** Zdalny wątek (który wywołuje `LoadLibraryA`) nie zakończył swojego wykonania w określonym czasie (10 sekund).
   - **Zawieszenie:** `LoadLibraryA` mogła się zawiesić lub trwać zbyt długo.
   - **Blokada:** Jakiś mechanizm bezpieczeństwa mógł przechwycić i zablokować wykonanie `LoadLibraryA` na czas nieokreślony.
- **Rozwiązanie:** Może to wskazywać, że DLL ładuje się zbyt długo lub coś to uniemożliwia. Sprawdzenie logów systemowych lub samego SA-MP/OMP (jeśli istnieją) może pomóc.

#### Wstrzyknięcie DLL Nie powiodło się lub Zwróciło Błąd

- **Komunikat o Błędzie:** `"DLL injection failed or returned an error. The LoadLibrary call may have failed in the target process."`
- **Dlaczego:** Zdalny wątek zakończył się, ale kod wyjścia `LoadLibraryA` wskazywał na niepowodzenie (zazwyczaj `0` lub `NULL`).
   - **Nieistniejąca/Uszkodzona DLL:** Pomimo wstępnej walidacji, DLL mogła zostać przeniesiona lub uszkodzona między walidacją a wstrzyknięciem.
   - **Brakujące Zależności DLL:** `samp.dll` lub `omp-client.dll` mogą zależeć od innych bibliotek DLL, których nie ma w katalogu gry ani w ścieżce systemowej.
   - **Wewnętrzny Błąd DLL:** Sama biblioteka DLL może mieć wewnętrzny błąd, który uniemożliwia jej prawidłowe załadowanie.
- **Rozwiązanie:** Sprawdź integralność `samp.dll`/`omp-client.dll`. Upewnij się, że wszystkie zależności DLL są obecne.

### Błąd podczas Wznawiania Wątku Gry

Jest to ostatni możliwy błąd w cyklu wstrzykiwania.

- **Komunikat o Błędzie (Przykład):** `"Failed to resume the game process thread: Invalid handle."`
- **Dlaczego:** API `ResumeThread` nie powiodło się przy ponownym uruchomieniu głównego wątku `gta_sa.exe`.
   - **Nieprawidłowy Uchwyt:** Uchwyt wątku mógł zostać z jakiegoś powodu unieważniony.
   - **Problem z Uprawnieniami:** Aplikacja może nie mieć uprawnień do modyfikowania stanu wątku.
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