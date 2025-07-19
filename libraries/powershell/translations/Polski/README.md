# SA-MP Injector PowerShell

![License](https://img.shields.io/badge/License-MIT-yellow.svg?style=flat)
![PowerShell](https://img.shields.io/badge/PowerShell-5.1%2B-blue.svg?style=flat&logo=powershell)
![Platform](https://img.shields.io/badge/Platform-Windows-0078D6.svg?style=flat&logo=windows)
[![SA-MP | OMP](https://img.shields.io/badge/Support-SA--MP%20%7C%20OMP-yellow)](https://github.com/spc-samp/samp-injector)
![Code Quality](https://img.shields.io/badge/Code%20Quality-High-brightgreen.svg?style=flat)

**SA-MP Injector PowerShell** to więcej niż skrypt do **wstrzykiwania DLL**. Reprezentuje on **bibliotekę funkcji i klas PowerShell**, opracowaną w celu zapewnienia solidnego i kompletnego rozwiązania do programowego uruchamiania gry **Grand Theft Auto: San Andreas** (**GTA:SA**) wraz z jej klientami wieloosobowymi, w szczególności **SA-MP (San Andreas Multiplayer)** i **OMP (Open Multiplayer)**. Jego głównym celem jest uproszczenie procesu uruchamiania gry, eliminując złożoność związaną z bezpośrednią manipulacją procesami systemu operacyjnego i przekazywaniem argumentów wiersza poleceń.

Opracowana w celu zapewnienia maksymalnej elastyczności i łatwej integracji, biblioteka ta pozwala programistom na jej bezpośrednie włączenie do swoich **projektów i skryptów PowerShell**. Nie tylko zarządza **podstawowym wstrzykiwaniem DLL** klienta wieloosobowego (`samp.dll` lub `omp-client.dll`), ale także inteligentnie zarządza wszystkimi niezbędnymi parametrami połączenia (**nazwa użytkownika**, **adres IP**, **port** i **hasło**), symulując natywne uruchomienie za pomocą wbudowanych funkcji **Windows API**, do których dostęp uzyskuje się bezpośrednio przez **PowerShell**.

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

- [SA-MP Injector PowerShell](#sa-mp-injector-powershell)
  - [Języki](#języki)
  - [Spis treści](#spis-treści)
  - [Podstawowe koncepcje i motywacja](#podstawowe-koncepcje-i-motywacja)
    - [Dlaczego wstrzykiwać DLL?](#dlaczego-wstrzykiwać-dll)
    - [SA-MP i OMP: Różnice i podobieństwa](#sa-mp-i-omp-różnice-i-podobieństwa)
    - [Wstrzykiwanie DLL w PowerShell: Bezpośrednie podejście z WinAPI](#wstrzykiwanie-dll-w-powershell-bezpośrednie-podejście-z-winapi)
  - [Wewnętrzna architektura biblioteki: Dogłębna analiza](#wewnętrzna-architektura-biblioteki-dogłębna-analiza)
    - [`Constants.ps1`](#constantsps1)
    - [`CustomTypes.ps1`](#customtypesps1)
    - [`StringUtils.ps1`](#stringutilsps1)
    - [`ErrorUtils.ps1`](#errorutilsps1)
    - [`Process.ps1`](#processps1)
    - [`InjectorCore.ps1`](#injectorcoreps1)
    - [`Injector.ps1`](#injectorps1)
    - [`Cleanup.ps1`](#cleanupps1)
  - [Wszechstronne przykłady użycia](#wszechstronne-przykłady-użycia)
    - [1. Przygotowanie środowiska deweloperskiego](#1-przygotowanie-środowiska-deweloperskiego)
    - [2. Scenariusz podstawowy: Łączenie z serwerem SA-MP](#2-scenariusz-podstawowy-łączenie-z-serwerem-sa-mp)
    - [3. Scenariusz zaawansowany: Łączenie z serwerem OMP](#3-scenariusz-zaawansowany-łączenie-z-serwerem-omp)
    - [4. Wykonanie z skryptu nadrzędnego](#4-wykonanie-z-skryptu-nadrzędnego)
  - [Obsługa typowych błędów i komunikatów](#obsługa-typowych-błędów-i-komunikatów)
    - [1. Nieprawidłowy typ wstrzykiwania](#1-nieprawidłowy-typ-wstrzykiwania)
    - [2. Nieprawidłowy port serwera (format lub zakres)](#2-nieprawidłowy-port-serwera-format-lub-zakres)
      - [2.1. Nienumeryczny format portu](#21-nienumeryczny-format-portu)
      - [2.2. Port poza prawidłowym zakresem](#22-port-poza-prawidłowym-zakresem)
    - [3. Nieprawidłowa nazwa użytkownika (pusta lub zbyt długa)](#3-nieprawidłowa-nazwa-użytkownika-pusta-lub-zbyt-długa)
      - [3.1. Pusta nazwa użytkownika](#31-pusta-nazwa-użytkownika)
      - [3.2. Zbyt długa nazwa użytkownika](#32-zbyt-długa-nazwa-użytkownika)
    - [4. Nie znaleziono plików gry lub DLL](#4-nie-znaleziono-plików-gry-lub-dll)
      - [4.1. Nie znaleziono pliku wykonywalnego gry (`gta_sa.exe`)](#41-nie-znaleziono-pliku-wykonywalnego-gry-gta_saexe)
      - [4.2. Nie znaleziono biblioteki SA-MP (`samp.dll`)](#42-nie-znaleziono-biblioteki-sa-mp-sampdll)
      - [4.3. Nie znaleziono biblioteki OMP (`omp-client.dll`) (tylko dla wstrzykiwania OMP)](#43-nie-znaleziono-biblioteki-omp-omp-clientdll-tylko-dla-wstrzykiwania-omp)
    - [5. Niepowodzenie tworzenia procesu gry](#5-niepowodzenie-tworzenia-procesu-gry)
    - [6. Błąd alokacji pamięci w procesie docelowym](#6-błąd-alokacji-pamięci-w-procesie-docelowym)
    - [7. Błąd zapisu ścieżki DLL w pamięci procesu](#7-błąd-zapisu-ścieżki-dll-w-pamięci-procesu)
    - [8. Błąd podczas znajdowania podstawowych funkcji systemowych](#8-błąd-podczas-znajdowania-podstawowych-funkcji-systemowych)
      - [8.1. Nie znaleziono `kernel32.dll`](#81-nie-znaleziono-kernel32dll)
      - [8.2. Nie znaleziono `LoadLibraryA`](#82-nie-znaleziono-loadlibrarya)
    - [9. Błąd tworzenia zdalnego wątku do wstrzykiwania](#9-błąd-tworzenia-zdalnego-wątku-do-wstrzykiwania)
    - [10. Przekroczenie limitu czasu lub niepowodzenie ukończenia wstrzykiwania](#10-przekroczenie-limitu-czasu-lub-niepowodzenie-ukończenia-wstrzykiwania)
    - [11. Niepowodzenie wznowienia wątku procesu gry](#11-niepowodzenie-wznowienia-wątku-procesu-gry)
  - [Licencja](#licencja)
    - [Warunki użytkowania](#warunki-użytkowania)
      - [1. Przyznane uprawnienia](#1-przyznane-uprawnienia)
      - [2. Obowiązkowe warunki](#2-obowiązkowe-warunki)
      - [3. Prawa autorskie](#3-prawa-autorskie)
      - [4. Wyłączenie gwarancji i ograniczenie odpowiedzialności](#4-wyłączenie-gwarancji-i-ograniczenie-odpowiedzialności)

## Podstawowe koncepcje i motywacja

### Dlaczego wstrzykiwać DLL?

> [!NOTE]
> **Wstrzykiwanie DLL (Dynamic Link Library)** to metoda stosowana w systemach operacyjnych **Microsoft Windows**, która pozwala na wykonanie kodu w przestrzeni pamięci innego działającego procesu. Jest to potężna technika z wieloma legalnymi zastosowaniami, od debugowania i monitorowania programów po modyfikację zachowania aplikacji w celu rozszerzenia ich funkcjonalności.

W kontekście gier takich jak **GTA San Andreas**, które nie zostały pierwotnie opracowane z wbudowaną funkcjonalnością wieloosobową, **wstrzykiwanie DLL** jest podstawą istnienia klientów wieloosobowych, takich jak **SA-MP** i **OMP**. Klienci ci są zaimplementowani jako **DLL**, które po wstrzyknięciu do procesu `gta_sa.exe` przejmują kontrolę, przechwytują funkcje gry i nawiązują komunikację z serwerami wieloosobowymi.

Zamiast polegać na zewnętrznym launcherze lub bezpośredniej modyfikacji pliku wykonywalnego gry, **wstrzykiwanie DLL** pozwala na bardziej elastyczne i programowalne uruchamianie, szczególnie przydatne w środowiskach, w których chce się zautomatyzować proces łączenia z określonymi serwerami z predefiniowanymi konfiguracjami.

### SA-MP i OMP: Różnice i podobieństwa

**SA-MP** i **OMP** to dwie główne platformy wieloosobowe dla **GTA San Andreas**. Obie działają jako modyfikacje podstawowej gry, przekształcając ją w masowe środowisko online dla wielu graczy.

- **SA-MP (San Andreas Multiplayer)**: Oryginalny i najbardziej ugruntowany klient, szeroko stosowany od wielu lat. Jego architektura wymaga do działania pliku `samp.dll`.
- **OMP (Open Multiplayer)**: Projekt open source, często postrzegany jako następca lub bardziej nowoczesna alternatywa dla **SA-MP**, oferujący ulepszenia wydajności, stabilności i dodatkowe funkcje. Wymaga on pliku `omp-client.dll`.

Chociaż działają w podobny sposób (**wstrzykując DLL** do procesu **GTA:SA**), biblioteka **SA-MP Injector PowerShell** została starannie opracowana, aby obsługiwać **obie biblioteki DLL**, rozpoznając różnice w nazwach plików i pozwalając deweloperowi na wybór pożądanego klienta wieloosobowego za pomocą parametru konfiguracyjnego. Zapewnia to, że biblioteka może być używana z szeroką gamą serwerów i projektów opartych na którejkolwiek z platform.

### Wstrzykiwanie DLL w PowerShell: Bezpośrednie podejście z WinAPI

PowerShell to potężny język skryptowy do automatyzacji w systemie Windows, ale manipulacja procesami i wstrzykiwanie DLL na tak niskim poziomie systemowym nie jest jego główną funkcją. Aby osiągnąć ten cel, biblioteka **SA-MP Injector PowerShell** intensywnie korzysta z polecenia `Add-Type` do bezpośredniego wywoływania funkcji **Windows API (WinAPI)**.

`Add-Type` pozwala na definiowanie i kompilowanie kodu C# (lub innych języków .NET) w czasie rzeczywistym w środowisku PowerShell. Ten kod C# działa jako „most” do natywnych funkcji WinAPI (`DllImport`), umożliwiając operacje takie jak:

- **`CreateProcessA`**: Do uruchomienia procesu GTA:SA.
- **`VirtualAllocEx`**: Do alokacji pamięci wewnątrz zdalnego procesu.
- **`WriteProcessMemory`**: Do skopiowania ścieżki DLL do alokowanej pamięci.
- **`GetModuleHandleA` i `GetProcAddress`**: Do uzyskania adresu funkcji `LoadLibraryA` w `kernel32.dll`.
- **`CreateRemoteThread`**: Do utworzenia wątku w zdalnym procesie, który wykonuje `LoadLibraryA`, skutecznie ładując DLL.
- **`WaitForSingleObject` i `GetExitCodeThread`**: Do monitorowania powodzenia wstrzykiwania.
- **`ResumeThread`**: Do ponownej aktywacji procesu gry po wstrzyknięciu.
- **`CloseHandle`**: Do zamykania uchwytów zasobów systemowych i unikania wycieków.
- **`MessageBoxW`**: Do wyświetlania informacyjnych komunikatów o błędach dla użytkownika.

To bezpośrednie podejście z WinAPI pozwala PowerShellowi na wykonywanie tych samych operacji niskiego poziomu, co skompilowana aplikacja w **C++**, z wygodą środowiska skryptowego.

## Wewnętrzna architektura biblioteki: Dogłębna analiza

Biblioteka **SA-MP Injector PowerShell** przyjmuje modularne podejście do zarządzania złożonością procesu wstrzykiwania. Każdy skrypt jest wyspecjalizowanym modułem, odpowiedzialnym za określoną część ogólnej funkcjonalności, co promuje przejrzystość kodu, łatwość konserwacji i rozszerzalność.

### `Constants.ps1`

Ten skrypt jest podstawą wszystkich stałych konfiguracji biblioteki. Definiuje on globalną tablicę mieszającą (`$global:CONSTANTS`), która przechowuje wszystkie używane literały i wartości numeryczne, takie jak limity portów, nazwy plików DLL, odwołania do API systemowych i flagi dla operacji takich jak tworzenie procesu i alokacja pamięci.

```powershell
$global:CONSTANTS = @{
    # Limity walidacji portu
    MIN_PORT = 1
    MAX_PORT = 65535
    
    # Ograniczenia nazwy użytkownika
    MAX_NICKNAME_LENGTH = 20
    
    # Wymagane nazwy plików
    SAMP_DLL_NAME = "samp.dll"
    OMP_DLL_NAME = "omp-client.dll"
    GAME_EXE_NAME = "gta_sa.exe"
    
    # Odwołania do API systemowego
    KERNEL32_DLL = "kernel32.dll"
    USER32_DLL = "user32.dll" # Używane dla MessageBoxW
    LOAD_LIBRARY_FUNC = "LoadLibraryA"
    
    # Prefiksy argumentów wiersza poleceń
    CMD_ARG_CONFIG = "-c"
    CMD_ARG_NICKNAME = "-n"
    CMD_ARG_HOST = "-h"
    CMD_ARG_PORT = "-p"
    CMD_ARG_PASSWORD = "-z"
    
    # Identyfikatory typu wstrzykiwania
    INJECT_TYPE_SAMP = "samp"
    INJECT_TYPE_OMP = "omp"
    
    # Tytuły okien dialogowych błędów
    ERROR_TITLE_SAMP = "Błąd Injectora SA-MP - SPC"
    ERROR_TITLE_OMP = "Błąd Injectora OMP - SPC"
    
    # Flagi tworzenia procesu (CREATE_SUSPENDED | DETACHED_PROCESS)
    # 0x00000104 = CREATE_SUSPENDED (0x4) + DETACHED_PROCESS (0x100)
    PROCESS_CREATION_FLAGS = 0x00000104
    
    # Limity czasu operacji
    DLL_INJECTION_TIMEOUT_MS = 10000 # 10 sekund
    
    # Stałe alokacji pamięci
    # 0x00003000 = MEM_COMMIT (0x1000) + MEM_RESERVE (0x2000)
    MEMORY_ALLOCATION_TYPE = 0x00003000
    # 0x00000004 = PAGE_READWRITE
    MEMORY_PROTECTION = 0x00000004
    # 0x00008000 = MEM_RELEASE
    MEMORY_FREE_TYPE = 0x00008000
    
    # Wyniki obiektu oczekiwania (Windows API)
    WAIT_OBJECT_0 = 0x00000000
    WAIT_TIMEOUT = 0x00000102
    WAIT_FAILED = 0xFFFFFFFF
    
    # Wskaźnik błędu wznowienia wątku (Windows API)
    THREAD_RESUME_ERROR = 0xFFFFFFFF # ResumeThread zwraca -1 w przypadku niepowodzenia
    
    # Stałe MessageBox (Windows API)
    MB_OK = 0x00000000
    MB_ICONERROR = 0x00000010
    MB_TOPMOST = 0x00040000
}
```

> [!TIP]
> Użycie globalnej tablicy mieszającej dla stałych jest powszechną praktyką w skryptach PowerShell. Centralizuje to ustawienia i unika "magicznych liczb" oraz powtarzających się ciągów znaków, co sprawia, że kod jest bardziej czytelny i łatwiejszy w utrzymaniu. Wartości flag (`0x...`) odpowiadają dziesiętnym wartościom stałych zdefiniowanych w Windows API.

### `CustomTypes.ps1`

Ten skrypt jest kluczowy dla interakcji z Windows API. Definiuje on typy C# w czasie rzeczywistym za pomocą `Add-Type`, w tym:

- **`Inject_Type` enum**: Do kategoryzacji typu wstrzykiwania (SAMP lub OMP), poprawiając bezpieczeństwo typów.
- **`WinAPI` class**: Statyczna klasa, która importuje i udostępnia funkcje Windows API niezbędne do wstrzykiwania. Każda metoda w tej klasie odpowiada funkcji API (`DllImport`), z poprawną sygnaturą i zestawem znaków (`CharSet`).
- **`Startup_Info` struct i `Process_Information` struct**: Struktury danych C#, które replikują struktury `STARTUPINFO` i `PROCESS_INFORMATION` używane przez funkcję `CreateProcessA` z Windows API.
- **`Process_Info` class**: Prosta klasa w C#, która działa jako kontener na uchwyty procesu i wątku zwracane po pomyślnym utworzeniu procesu, ułatwiając transport i zarządzanie tymi uchwytami w środowisku PowerShell.

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
        using System.Text; // Wymagane dla Marshal.GetLastWin32Error
        
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
            
            // Struktura C# dla STARTUPINFO
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
            
            // Struktura C# dla PROCESS_INFORMATION
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
        
        // Klasa pomocnicza do transportu uchwytów procesu i wątku
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
> Wstrzykiwanie 32-bitowych DLL (takich jak `samp.dll` i `omp-client.dll`) do 32-bitowego procesu (`gta_sa.exe`) **wymaga, aby środowisko PowerShell również było 32-bitowe**. **SA-MP Injector PowerShell** radzi sobie z tym automatycznie, restartując się w powłoce PowerShell x86, jeśli wykryje, że jest uruchomiony w środowisku x64. Jest to kluczowe dla zapewnienia zgodności rozmiaru wskaźników i prawidłowego działania wstrzykiwania.
>
> Dyrektywa `if (-not ([System.Management.Automation.PSTypeName]'TypeName').Type)` zapewnia, że typy C# są dodawane do środowiska PowerShell tylko raz, unikając błędów redefinicji, jeśli skrypt jest uruchamiany wielokrotnie w tej samej sesji.

### `StringUtils.ps1`

Ten moduł dostarcza niezbędną funkcję narzędziową do manipulacji ciągami znaków, w szczególności do obsługi kodowania znaków wymaganego podczas interakcji ze starszymi funkcjami Windows API (funkcje "A" z char*).

```powershell
function Convert_Wide_To_Local_8Bit {
    param([Parameter(Mandatory = $false)] [AllowEmptyString()] [string]$wide_string)
    
    if ([string]::IsNullOrEmpty($wide_string)) {
        return [string]::Empty
    }

    try {
        # Pobiera lokalną stronę kodową ANSI systemu
        $ansi_code_page = [System.Globalization.CultureInfo]::CurrentCulture.TextInfo.ANSICodePage
        $encoding = [System.Text.Encoding]::GetEncoding($ansi_code_page)
        
        # Konwertuje ciąg znaków Unicode (wide) na bajty w lokalnym kodowaniu ANSI
        $bytes = $encoding.GetBytes($wide_string)

        # Konwertuje bajty z powrotem na ciąg znaków przy użyciu tego samego kodowania ANSI
        # To zapewnia, że ciąg jest kompatybilny z API oczekującymi kodowania 8-bitowego (ANSI)
        return $encoding.GetString($bytes)
    }
    catch {
        # W przypadku błędu konwersji (np. znaków, których nie można zmapować),
        # zwraca oryginalny ciąg jako fallback, chociaż może to powodować problemy,
        # jeśli zawiera znaki nieobsługiwane przez API ANSI.
        return $wide_string
    }
}
```

> [!IMPORTANT]
> Funkcja `Convert_Wide_To_Local_8Bit` jest kluczowa, ponieważ wiele funkcji Windows API z sufiksem "A" (`CreateProcessA`, `LoadLibraryA`, `GetModuleHandleA`, `GetProcAddress`) oczekuje ciągów znaków zakodowanych w ANSI (8-bit), które zależą od lokalnej strony kodowej systemu. Domyślnie ciągi znaków w PowerShell są w formacie Unicode. Ta funkcja wykonuje niezbędną konwersję. Jeśli nazwa pliku lub argument wiersza poleceń zawiera znaki spoza strony kodowej ANSI systemu, konwersja może skutkować nieprawidłowymi znakami lub utratą danych. Dla tego projektu, który ma na celu interakcję ze starymi programami, to podejście ANSI jest zazwyczaj wystarczające i konieczne.

### `ErrorUtils.ps1`

Ten moduł jest odpowiedzialny za dostarczanie jasnych informacji zwrotnych dla użytkownika w przypadku awarii. Centralizuje logikę pobierania komunikatów o błędach systemowych i wyświetlania standardowych okien dialogowych systemu Windows.

```powershell
function Get_System_Error_Message {
    param([Parameter(Mandatory = $true)][int]$error_code)
    
    try {
        # Używa Win32Exception, aby uzyskać sformatowany komunikat o błędzie systemowym
        $exception = New-Object System.ComponentModel.Win32Exception($error_code)
        
        return $exception.Message
    }
    catch {
        # Fallback na nieznany komunikat o błędzie
        return "Nieznany błąd (Kod: $error_code)"
    }
}

function Show_Error {
    param([Parameter(Mandatory = $true)][string]$message, [Parameter(Mandatory = $true)][Inject_Type]$inject_type)
    
    # Określa tytuł okna dialogowego na podstawie typu wstrzykiwania
    $title = if ($inject_type -eq [Inject_Type]::SAMP) {
        $global:CONSTANTS.ERROR_TITLE_SAMP
    }
    else {
        $global:CONSTANTS.ERROR_TITLE_OMP
    }
    
    try {
        # Łączy flagi dla MessageBoxW (OK, Ikona Błędu, AlwaysOnTop)
        $message_box_flags = $global:CONSTANTS.MB_OK -bor $global:CONSTANTS.MB_ICONERROR -bor $global:CONSTANTS.MB_TOPMOST
        
        # Wywołuje funkcję MessageBoxW zaimportowaną przez Add-Type
        [void][WinAPI]::MessageBoxW([System.IntPtr]::Zero, $message, $title, $message_box_flags)
    }
    catch {
        # W przypadku błędu wyświetlania MessageBox (np. w środowiskach bez UI), pisze do konsoli
        Write-Host "[$title] $message" -ForegroundColor Red
    }
}
```

> [!NOTE]
> `Get_System_Error_Message` używa `System.ComponentModel.Win32Exception` z .NET do konwersji numerycznego kodu błędu z Windows API (`GetLastError()`) na czytelny dla użytkownika opis tekstowy, który może być zlokalizowany w języku systemu operacyjnego.
>
> `Show_Error` używa funkcji `MessageBoxW` zaimportowanej z `user32.dll` za pomocą `Add-Type` (`CustomTypes.ps1`) do wyświetlania informacyjnego okna dialogowego. Flagi takie jak `MB_OK` i `MB_ICONERROR` są importowane ze stałych WinAPI.

### `Process.ps1`

Jest to główny moduł odpowiedzialny za bezpośrednią interakcję z niskopoziomowymi API systemu Windows w celu manipulowania procesami. Hermetyzuje kluczowe operacje tworzenia procesu i wstrzykiwania DLL, zarządzając uchwytami, pamięcią i wątkami.

```powershell
class Process {
    # Zwalnia uchwyty procesu i wątku, zapobiegając wyciekom zasobów
    [void] Close_Process_Info([Process_Info]$process_info) {
        if ($null -ne $process_info) {
            # Zamyka uchwyt procesu, jeśli jest prawidłowy
            if ($process_info.ProcessHandle -ne [System.IntPtr]::Zero -and $process_info.ProcessHandle -ne [System.IntPtr]::new(-1)) {
                [void][WinAPI]::CloseHandle($process_info.ProcessHandle)
                $process_info.ProcessHandle = [System.IntPtr]::Zero # Oznacza jako zamknięty
            }

            # Zamyka uchwyt wątku, jeśli jest prawidłowy
            if ($process_info.ThreadHandle -ne [System.IntPtr]::Zero -and $process_info.ThreadHandle -ne [System.IntPtr]::new(-1)) {
                [void][WinAPI]::CloseHandle($process_info.ThreadHandle)
                $process_info.ThreadHandle = [System.IntPtr]::Zero # Oznacza jako zamknięty
            }
        }
    }

    # Tworzy proces gry GTA:SA w stanie wstrzymanym
    [Process_Info] Create_Game_Process([string]$game_path, [string]$command_args, [string]$working_dir) {
        $startup_info = New-Object WinAPI+Startup_Info
        # Ustawia rozmiar struktury, kluczowy dla API Windows
        $startup_info.cb = [System.Runtime.InteropServices.Marshal]::SizeOf($startup_info)
        
        $process_information = New-Object WinAPI+Process_Information
        
        $command_line_bytes = $null

        if (-not [string]::IsNullOrEmpty($command_args)) {
            # Konwertuje argumenty wiersza poleceń na tablicę bajtów ANSI z terminatorem null
            $command_line_bytes = [System.Text.Encoding]::Default.GetBytes($command_args + "`0")
        }
        
        # Ustawia katalog roboczy, null jeśli jest pusty
        $current_directory = if ([string]::IsNullOrEmpty($working_dir)) {
            $null
        }
        else {
            $working_dir
        }
        
        # Wywołuje funkcję CreateProcessA z Windows API
        $success = [WinAPI]::CreateProcessA($game_path, $command_line_bytes, [System.IntPtr]::Zero, [System.IntPtr]::Zero, $false, $global:CONSTANTS.PROCESS_CREATION_FLAGS, 
            [System.IntPtr]::Zero, $current_directory, [ref]$startup_info, [ref]$process_information)
        
        if (-not $success) {
            # W przypadku niepowodzenia pobiera ostatni błąd systemowy i wyświetla go
            $error_code = [System.Runtime.InteropServices.Marshal]::GetLastWin32Error()
            $error_message = Get_System_Error_Message $error_code
            Show_Error "Nie udało się utworzyć procesu gry. Upewnij się, że 'gta_sa.exe' nie jest uruchomiony i masz wystarczające uprawnienia do wykonania pliku. Błąd systemowy: $error_message" ([Inject_Type]::SAMP)

            return $null # Zwraca null w przypadku niepowodzenia
        }
        
        # Zwraca obiekt Process_Info zawierający uchwyty procesu i wątku
        $result = New-Object Process_Info
        $result.ProcessHandle = $process_information.hProcess
        $result.ThreadHandle = $process_information.hThread
        
        return $result
    }
    
    # Wstrzykuje DLL do zdalnego procesu
    [bool] Inject_DLL([IntPtr]$process_handle, [string]$dll_path, [ref]$error_message) {
        if ($process_handle -eq [System.IntPtr]::Zero) {
            $error_message.Value = "Podano nieprawidłowy uchwyt procesu do wstrzyknięcia DLL."

            return $false
        }
        
        if ([string]::IsNullOrEmpty($dll_path)) {
            $error_message.Value = "Ścieżka DLL nie może być pusta."

            return $false
        }
        
        # Konwertuje ścieżkę DLL na bajty ASCII (ANSI 8-bit) z terminatorem null
        $dll_path_bytes = [System.Text.Encoding]::ASCII.GetBytes($dll_path + "`0")
        $dll_path_size = $dll_path_bytes.Length
        
        # Alokuje pamięć w zdalnym procesie na ścieżkę DLL
        $remote_memory = [WinAPI]::VirtualAllocEx($process_handle, [System.IntPtr]::Zero, $dll_path_size, $global:CONSTANTS.MEMORY_ALLOCATION_TYPE, $global:CONSTANTS.MEMORY_PROTECTION)
        
        if ($remote_memory -eq [System.IntPtr]::Zero) {
            $error_code = [System.Runtime.InteropServices.Marshal]::GetLastWin32Error()
            $error_message.Value = "Nie udało się zaalokować pamięci w procesie docelowym. Może to być spowodowane niewystarczającymi uprawnieniami lub mechanizmami ochrony procesu. Błąd systemowy: $(Get_System_Error_Message $error_code)"

            return $false
        }
        
        # Używa bloku try/finally, aby upewnić się, że zdalna pamięć zostanie zwolniona
        try {
            $bytes_written = [System.IntPtr]::Zero
            # Zapisuje ścieżkę DLL do zdalnej pamięci
            $write_success = [WinAPI]::WriteProcessMemory($process_handle, $remote_memory, $dll_path_bytes, $dll_path_size, [ref]$bytes_written)
            
            if (-not $write_success) {
                $error_code = [System.Runtime.InteropServices.Marshal]::GetLastWin32Error()
                $error_message.Value = "Nie udało się zapisać ścieżki DLL do pamięci procesu docelowego. Sprawdź uprawnienia procesu i upewnij się, że ścieżka DLL jest dostępna. Błąd systemowy: $(Get_System_Error_Message $error_code)"
                
                return $false
            }
            
            # Pobiera uchwyt do kernel32.dll (który jest załadowany we wszystkich procesach)
            $kernel32_handle = [WinAPI]::GetModuleHandleA($global:CONSTANTS.KERNEL32_DLL)

            if ($kernel32_handle -eq [System.IntPtr]::Zero) {
                $error_code = [System.Runtime.InteropServices.Marshal]::GetLastWin32Error()
                $error_message.Value = "Nie udało się uzyskać uchwytu do kernel32.dll. Jest to niezbędna biblioteka systemowa i ten błąd wskazuje na poważny problem systemowy. Błąd systemowy: $(Get_System_Error_Message $error_code)"
                
                return $false
            }
            
            # Pobiera adres funkcji LoadLibraryA w kernel32.dll.
            # Ten adres jest spójny między procesami w tym samym systemie operacyjnym.
            $load_library_address = [WinAPI]::GetProcAddress($kernel32_handle, $global:CONSTANTS.LOAD_LIBRARY_FUNC)

            if ($load_library_address -eq [System.IntPtr]::Zero) {
                $error_code = [System.Runtime.InteropServices.Marshal]::GetLastWin32Error()
                $error_message.Value = "Nie udało się znaleźć adresu funkcji LoadLibraryA w kernel32.dll. Jest to kluczowe dla wstrzyknięcia DLL. Błąd systemowy: $(Get_System_Error_Message $error_code)"
                
                return $false
            }
            
            $thread_id = [System.IntPtr]::Zero
            # Tworzy zdalny wątek w procesie docelowym, aby wykonać LoadLibraryA
            $remote_thread_handle = [WinAPI]::CreateRemoteThread($process_handle, [System.IntPtr]::Zero, 0, $load_library_address, $remote_memory, 0, [ref]$thread_id)
            
            if ($remote_thread_handle -eq [System.IntPtr]::Zero) {
                $error_code = [System.Runtime.InteropServices.Marshal]::GetLastWin32Error()
                $error_message.Value = "Nie udało się utworzyć zdalnego wątku w procesie docelowym w celu wykonania wstrzyknięcia DLL. Może to być spowodowane ograniczeniami bezpieczeństwa lub stanem procesu. Błąd systemowy: $(Get_System_Error_Message $error_code)"
                
                return $false
            }
            
            # Używa bloku try/finally, aby upewnić się, że uchwyt zdalnego wątku zostanie zamknięty
            try {
                # Czeka na zakończenie zdalnego wątku (wstrzyknięcia DLL) lub przekroczenie limitu czasu
                $wait_result = [WinAPI]::WaitForSingleObject($remote_thread_handle, $global:CONSTANTS.DLL_INJECTION_TIMEOUT_MS)
                
                if ($wait_result -ne $global:CONSTANTS.WAIT_OBJECT_0) {
                    $error_code = [System.Runtime.InteropServices.Marshal]::GetLastWin32Error()

                    $wait_result_message = switch ($wait_result) {
                        $global:CONSTANTS.WAIT_TIMEOUT { "przekroczenie limitu czasu" }
                        $global:CONSTANTS.WAIT_FAILED { "oczekiwanie nie powiodło się" }
                        default { "nieznany wynik oczekiwania ($wait_result)" }
                    }

                    $error_message.Value = "Przekroczono limit czasu lub wystąpił błąd podczas oczekiwania na zakończenie wstrzykiwania DLL ($wait_result_message). Błąd systemowy: $(Get_System_Error_Message $error_code)"

                    return $false
                }
                
                $exit_code = 0
                # Pobiera kod wyjścia zdalnego wątku. Dla LoadLibraryA, 0 oznacza niepowodzenie.
                $get_exit_code_success = [WinAPI]::GetExitCodeThread($remote_thread_handle, [ref]$exit_code)
                
                if (-not $get_exit_code_success -or $exit_code -eq 0) {
                    $error_code = [System.Runtime.InteropServices.Marshal]::GetLastWin32Error()
                    $error_message.Value = "Wstrzykiwanie DLL nie powiodło się lub zwróciło błąd. Wywołanie LoadLibrary mogło się nie udać w procesie docelowym. Kod wyjścia: $exit_code. Błąd systemowy: $(Get_System_Error_Message $error_code)"

                    return $false
                }
                
                return $true # Wstrzykiwanie zakończone sukcesem
            }
            finally {
                # Upewnia się, że uchwyt zdalnego wątku zostanie zamknięty
                [void][WinAPI]::CloseHandle($remote_thread_handle)
            }
        }
        finally {
            # Upewnia się, że zdalnie zaalokowana pamięć zostanie zwolniona
            # 0 dla dwSize w MEM_RELEASE zwalnia cały region zaalokowany przez VirtualAllocEx
            [void][WinAPI]::VirtualFreeEx($process_handle, $remote_memory, 0, $global:CONSTANTS.MEMORY_FREE_TYPE)
        }
    }
}
```

> [!NOTE]
> Klasa `Process` używa `[System.IntPtr]` do reprezentowania uchwytów Windows. Warto zauważyć szerokie zastosowanie `try/finally` w celu zapewnienia, że uchwyty (`ProcessHandle`, `ThreadHandle`, `remote_memory`, `remote_thread_handle`) są poprawnie zamykane, a pamięć zwalniana, nawet w przypadku błędów. Jest to sposób na zaimplementowanie w PowerShell zasady **RAII** (Resource Acquisition Is Initialization), chociaż mniej zintegrowany z składnią języka.

### `InjectorCore.ps1`

Jest to klasa orkiestrująca, która łączy wszystkie funkcjonalności z poprzednich modułów. Koordynuje ona walidację, budowanie argumentów wiersza poleceń, tworzenie procesu i wywołania wstrzykiwania DLL.

```powershell
class Injector_Core {
    # Główna funkcja, która koordynuje inicjalizację i wstrzykiwanie gry
    [bool] Initialize_Game([Inject_Type]$inject_type, [string]$folder, [string]$nickname, [string]$ip, [string]$port, [string]$password) {
        # Buduje pełne ścieżki do niezbędnych plików
        $game_path = Join-Path -Path $folder -ChildPath $global:CONSTANTS.GAME_EXE_NAME
        $samp_dll_path = Join-Path -Path $folder -ChildPath $global:CONSTANTS.SAMP_DLL_NAME
        $omp_dll_path = Join-Path -Path $folder -ChildPath $global:CONSTANTS.OMP_DLL_NAME
        
        $validation_error = [string]::Empty # Zmienna do przechwytywania komunikatów o błędach walidacji
        
        # 1. Walidacja plików
        if (-not (Validate_Files $game_path $samp_dll_path $omp_dll_path $inject_type)) {
            # Błąd został już wyświetlony przez funkcję walidacji
            return $false
        }

        # 2. Walidacja portu
        if (-not (Validate_Port $port ([ref]$validation_error))) {
            Show_Error $validation_error $inject_type
            return $false
        }
        
        # 3. Walidacja nazwy użytkownika
        if (-not (Validate_Nickname $nickname ([ref]$validation_error))) {
            Show_Error $validation_error $inject_type
            return $false
        }
        
        # 4. Konwersja ciągów znaków na kodowanie ANSI/8-bit (wymagane dla starszych API)
        $converted_nickname = Convert_Wide_To_Local_8Bit $nickname
        $converted_ip = Convert_Wide_To_Local_8Bit $ip
        $converted_port = Convert_Wide_To_Local_8Bit $port
        $converted_password = Convert_Wide_To_Local_8Bit $password
        $converted_game_path = Convert_Wide_To_Local_8Bit $game_path
        $converted_folder = Convert_Wide_To_Local_8Bit $folder
        $converted_samp_dll_path = Convert_Wide_To_Local_8Bit $samp_dll_path
        $converted_omp_dll_path = Convert_Wide_To_Local_8Bit $omp_dll_path
        
        # 5. Budowanie argumentów wiersza poleceń
        $command_arguments = $this.Build_Command_Args($converted_nickname, $converted_ip, $converted_port, $converted_password)
        
        $process_manager = New-Object Process # Tworzy instancję klasy Process
        $process_info = $null # Zmienna do przechowywania informacji o utworzonym procesie
        
        # Używa bloku try/finally, aby upewnić się, że uchwyty procesu zostaną zamknięte
        try {
            # 6. Tworzenie procesu gry (wstrzymany)
            $process_info = $process_manager.Create_Game_Process($converted_game_path, $command_arguments, $converted_folder)
            
            if ($null -eq $process_info) {
                # Błąd został już wyświetlony przez funkcję tworzenia procesu
                return $false
            }

            $injection_error = [string]::Empty # Zmienna do przechwytywania komunikatów o błędach wstrzykiwania
            
            # 7. Wstrzykiwanie samp.dll
            if (-not $process_manager.Inject_DLL($process_info.ProcessHandle, $converted_samp_dll_path, ([ref]$injection_error))) {
                Show_Error "Nie udało się wstrzyknąć samp.dll: $injection_error" $inject_type
                return $false
            }
            
            # 8. Warunkowe wstrzykiwanie omp-client.dll (tylko jeśli typ wstrzykiwania to OMP)
            if ($inject_type -eq [Inject_Type]::OMP) {
                if (-not $process_manager.Inject_DLL($process_info.ProcessHandle, $converted_omp_dll_path, ([ref]$injection_error))) {
                    Show_Error "Nie udało się wstrzyknąć omp-client.dll: $injection_error" $inject_type
                    return $false
                }
            }
            
            # 9. Wznowienie procesu gry
            # Proces został utworzony w stanie wstrzymanym, aby umożliwić wstrzyknięcie.
            # Teraz, gdy biblioteki DLL zostały wstrzyknięte, można go wznowić.
            $resume_result = [WinAPI]::ResumeThread($process_info.ThreadHandle)

            if ($resume_result -eq $global:CONSTANTS.THREAD_RESUME_ERROR) {
                $error_code = [System.Runtime.InteropServices.Marshal]::GetLastWin32Error()
                $error_message = Get_System_Error_Message $error_code
                Show_Error "Nie udało się wznowić wątku procesu gry: $error_message" $inject_type

                return $false
            }
            
            return $true # Sukces we wszystkich krokach!
        }
        finally {
            # Zapewnia, że uchwyty procesu zostaną zamknięte na końcu,
            # niezależnie od sukcesu czy porażki.
            if ($null -ne $process_info) {
                $process_manager.Close_Process_Info($process_info)
            }
        }
    }
    
    # Buduje ciąg argumentów wiersza poleceń dla pliku wykonywalnego gry
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
> Dla **OMP**, wstrzykiwanie obejmuje `omp-client.dll` *oprócz* `samp.dll`. Jest to zgodne ze sposobem działania **OMP**, ponieważ może on używać `samp.dll` jako podstawy i rozszerzać funkcjonalność za pomocą `omp-client.dll`. Jest kluczowe, aby **obie biblioteki DLL** były obecne i funkcjonalne w katalogu gry, aby wstrzykiwanie OMP zakończyło się pomyślnie. Jeśli jedna z nich zawiedzie, gra może nie uruchomić się poprawnie lub klient wieloosobowy może się nie załadować.
>
> Zauważ, że ponieważ PowerShell nie ma `std::optional` ani natywnej gwarancji **RAII** w taki sam sposób jak C++, kod używa jawnego bloku `try/finally` w funkcji `Initialize_Game`, aby upewnić się, że `Close_Process_Info` zostanie wywołane, a uchwyty zwolnione, nawet jeśli wystąpi błąd. Jest to dobra praktyka czyszczenia zasobów w PowerShell.

### `Injector.ps1`

Jest to główny skrypt wejściowy biblioteki. Obsługuje on ładowanie innych modułów, walidację środowiska PowerShell (sprawdzanie, czy jest to x86 dla kompatybilności wstrzykiwania) oraz inicjalizację klasy `Injector_Core`. Jest to skrypt, który użytkownik końcowy będzie uruchamiał.

```powershell
param([Parameter(Mandatory = $true, Position = 0)][ValidateNotNullOrEmpty()][string]$inject_type,
    [Parameter(Mandatory = $true, Position = 1)][ValidateNotNullOrEmpty()][string]$folder,
    [Parameter(Mandatory = $true, Position = 2)][ValidateNotNullOrEmpty()][string]$nickname,
    [Parameter(Mandatory = $true, Position = 3)][ValidateNotNullOrEmpty()][string]$ip,
    [Parameter(Mandatory = $true, Position = 4)][ValidateNotNullOrEmpty()][string]$port,
    [Parameter(Position = 5)][AllowEmptyString()][string]$password = "",
    [switch]$restarted_x86) # Wewnętrzna flaga wskazująca, że skrypt został już zrestartowany w x86

$ErrorActionPreference = 'Stop' # Zapewnia, że błędy niekończące zachowują się jak błędy kończące
# To sprawia, że bloki catch przechwytują więcej błędów i zapobiega nieoczekiwanemu kontynuowaniu skryptu.

# Pobiera pełną ścieżkę bieżącego skryptu, niezbędną do załadowania modułów pomocniczych
$script_path = $MyInvocation.MyCommand.Path

if ([string]::IsNullOrEmpty($script_path)) {
    # W przypadkach, gdy skrypt jest wywoływany w specjalny sposób (np. z potoku), $MyInvocation.MyCommand.Path może być pusty
    $script_path = Join-Path -Path (Get-Location) -ChildPath $MyInvocation.MyCommand.Name
}

$script_directory = Split-Path -Parent $script_path # Katalog bazowy biblioteki
$exit_code = 1 # Domyślny kod wyjścia (niepowodzenie)

try {
    # Ładuje wszystkie moduły biblioteki (stałe, typy niestandardowe, narzędzia, itp.)
    . (Join-Path -Path $script_directory -ChildPath "Constants.ps1")
    . (Join-Path -Path $script_directory -ChildPath "CustomTypes.ps1")
    . (Join-Path -Path $script_directory -ChildPath "StringUtils.ps1")
    . (Join-Path -Path $script_directory -ChildPath "ErrorUtils.ps1")
    . (Join-Path -Path $script_directory -ChildPath "Validation.ps1")
    . (Join-Path -Path $script_directory -ChildPath "Process.ps1")
    . (Join-Path -Path $script_directory -ChildPath "InjectorCore.ps1")

    # Definiuje główną funkcję interfejsu dla użytkownika.
    # Jest to opakowanie dla klasy Injector_Core.
    function Initialize_Game {
        param([string]$inject_type, [string]$folder, [string]$nickname, [string]$ip, [string]$port, [string]$password = "")

        # Sprawdza, czy środowisko PowerShell jest x64 i czy nie zostało jeszcze zrestartowane w x86
        if ([IntPtr]::Size -eq 8 -and -not $restarted_x86) {
            Write-Host "Wykryto środowisko PowerShell x64. Restartowanie w PowerShell x86 w celu zapewnienia kompatybilności wstrzykiwania DLL (32-bit)..." -ForegroundColor Yellow

            # Lokalizuje plik wykonywalny PowerShell 32-bitowego
            $powershell_x86_path = Join-Path -Path $env:windir -ChildPath "SysWOW64\WindowsPowerShell\v1.0\powershell.exe"

            if (-not (Test-Path -Path $powershell_x86_path)) {
                Write-Host "Nie można znaleźć powershell.exe (x86) w '$powershell_x86_path'. Wstrzykiwanie DLL 32-bit może się nie pow
ść." -ForegroundColor Red
                return $false
            }

            # Przygotowuje listę argumentów dla nowego procesu PowerShell x86
            $argument_list = @("-NoProfile", "-NonInteractive", "-ExecutionPolicy", "Bypass", "-File", $script_path, $inject_type, $folder, $nickname, $ip, $port)
            
            if (-not [string]::IsNullOrEmpty($password)) {
                $argument_list += $password
            }
            # Dodaje flagę wskazującą, że już został zrestartowany
            $argument_list += "-restarted_x86"
            
            try {
                $process_start_info = New-Object System.Diagnostics.ProcessStartInfo
                $process_start_info.FileName = $powershell_x86_path
                # Łączy argumenty w ciąg znaków dla StartInfo.Arguments
                $process_start_info.Arguments = ($argument_list | ForEach-Object { "`"$_`"" }) -join " " # Obejmuje argumenty cudzysłowami, aby obsłużyć spacje
                $process_start_info.RedirectStandardOutput = $true # Przekierowuje standardowe wyjście procesu potomnego
                $process_start_info.RedirectStandardError = $true   # Przekierowuje błędy procesu potomnego
                $process_start_info.UseShellExecute = $false     # Nie używa ShellExecute (bezpośrednio uruchamia PowerShell.exe)
                $process_start_info.CreateNoWindow = $true       # Nie tworzy nowego okna dla procesu potomnego

                $child_process = New-Object System.Diagnostics.Process
                $child_process.StartInfo = $process_start_info
                
                # Uruchamia proces potomny i czeka na jego zakończenie
                [void]$child_process.Start()
                $child_process.WaitForExit()
                
                # Przechwytuje i wyświetla wyjście/błędy procesu potomnego
                $standard_output = $child_process.StandardOutput.ReadToEnd()
                $standard_error = $child_process.StandardError.ReadToEnd()

                if (-not [string]::IsNullOrEmpty($standard_output)) { Write-Host $standard_output }
                if (-not [string]::IsNullOrEmpty($standard_error)) { Write-Host $standard_error -ForegroundColor Red }

                $child_exit_code = $child_process.ExitCode
                
                if ($child_exit_code -eq 0) {
                    Write-Host "Proces PowerShell x86 zakończony z kodem 0 (Sukces)." -ForegroundColor Green
                    return $true
                }
                else {
                    Write-Host "Proces PowerShell x86 zakończony z kodem błędu: '$child_exit_code'." -ForegroundColor Red
                    return $false
                }
            }
            catch {
                Write-Host "Nie udało się uruchomić PowerShell x86: '$($_.Exception.Message)'" -ForegroundColor Red
                return $false
            }
        }
        
        # Rzeczywista logika inicjalizacji, osiągana tylko, gdy środowisko jest x86 lub zostało już zrestartowane
        $injection_type = $null

        switch ($inject_type.ToLower()) {
            $global:CONSTANTS.INJECT_TYPE_SAMP {
                $injection_type = [Inject_Type]::SAMP
            }
            $global:CONSTANTS.INJECT_TYPE_OMP {
                $injection_type = [Inject_Type]::OMP
            }
            default {
                Show_Error "Określono nieprawidłowy tryb wstrzykiwania. Proszę użyć 'samp' lub 'omp'." ([Inject_Type]::SAMP)
                return $false
            }
        }

        $injector_core = New-Object Injector_Core # Tworzy instancję głównej klasy wstrzykiwania

        # Deleguje wywołanie do funkcji Initialize_Game klasy Injector_Core
        return $injector_core.Initialize_Game($injection_type, $folder, $nickname, $ip, $port, $password)
    }

    # Parametry przekazane do głównej funkcji
    $initialization_parameters = @{
        inject_type = $inject_type
        folder = $folder
        nickname = $nickname
        ip = $ip
        port = $port
        password = $password
    }

    # Wywołanie w celu rozpoczęcia procesu wstrzykiwania
    $game_initialization_result = Initialize_Game @initialization_parameters

    if ($game_initialization_result) {
        $exit_code = 0 # Sukces
    }
    else {
        $exit_code = 1 # Niepowodzenie
    }
}
catch {
    Write-Host "Krytyczny błąd podczas wykonania: '$($_.Exception.Message)'" -ForegroundColor Red
    $exit_code = 1
}
finally {
    # Zapewnia, że skrypt czyszczący zostanie wykonany na końcu, niezależnie od sukcesu czy porażki
    try {
        . (Join-Path -Path $script_directory -ChildPath "Cleanup.ps1")
    }
    catch {
        Write-Host "Ostrzeżenie: Wykonanie skryptu czyszczącego nie powiodło się: '$($_.Exception.Message)'" -ForegroundColor Yellow
    }
    
    exit $exit_code # Kończy z odpowiednim kodem statusu
}
```

> [!NOTE]
> Ten skrypt jest głównym punktem wejścia do wstrzykiwania. Jest odpowiedzialny za:
> - Definiowanie **parametrów wiersza poleceń**, których będzie używał użytkownik końcowy.
> - Ustawienie `$ErrorActionPreference = 'Stop'` dla bardziej rygorystycznej kontroli błędów.
> - **Ładowanie** wszystkich skryptów pomocniczych za pomocą "dot-sourcing" (`. `), zapewniając, że ich funkcje i klasy są dostępne w bieżącej sesji.
> - Implementację logiki **restartu dla środowiska x86**: Jeśli PowerShell działa w trybie 64-bitowym, automatycznie uruchamia się ponownie w instancji 32-bitowej (SysWOW64) i przekazuje te same argumenty, ponieważ wstrzykiwanie 32-bitowych bibliotek DLL jest bardziej niezawodne (i w wielu przypadkach obowiązkowe) z procesu 32-bitowego. Jest to kluczowa różnica w PowerShell w porównaniu z aplikacją C++ skompilowaną bezpośrednio dla x86.
> - Wywołanie funkcji `Initialize_Game` w celu rozpoczęcia procesu wstrzykiwania.
> - Zarządzanie kodem wyjścia skryptu (0 dla sukcesu, 1 dla niepowodzenia).
> - Wywołanie skryptu `Cleanup.ps1` w bloku `finally`.

### `Cleanup.ps1`

Ten skrypt jest odpowiedzialny za usuwanie funkcji i zmiennych globalnych załadowanych przez bibliotekę z bieżącej sesji PowerShell. Jest to dobra praktyka, aby uniknąć zanieczyszczenia środowiska i zapewnić, że kolejne uruchomienia skryptu z różnymi konfiguracjami nie napotkają nieoczekiwanych stanów z poprzednich sesji.

```powershell
$functions_to_remove = @(
    '*Initialize_Game*', # Używa symbolu wieloznacznego do usuwania funkcji (mogą mieć aliasy)
    '*Get_System_Error_Message*',
    '*Show_Error*',
    '*Convert_Wide_To_Local_8Bit*',
    '*Validate_*', # Usuwa wszystkie funkcje zaczynające się od 'Validate_'
    '*Build_Command_Args*'
)

# Iteruje po wzorcach i usuwa funkcje
foreach ($pattern in $functions_to_remove) {
    Get-Command -CommandType Function -Name $pattern -ErrorAction SilentlyContinue | ForEach-Object {
        try {
            Remove-Item -Path "Function:$($_.Name)" -Force -ErrorAction SilentlyContinue
        }
        catch {} # Ignoruje błędy, jeśli funkcja nie może być usunięta z jakiegoś powodu
    }
}

$global_variables_to_remove = @(
    'CONSTANTS',
    'CAN_SHOW_MESSAGE_BOX' # Dodaj tutaj, jeśli zostaną wprowadzone kolejne zmienne globalne
)

# Iteruje po zmiennych globalnych i usuwa je
foreach ($variable_name in $global_variables_to_remove) {
    try {
        Remove-Variable -Name $variable_name -Scope Global -Force -ErrorAction SilentlyContinue
    }
    catch {} # Ignoruje błędy
}

$variable_patterns_to_remove = @(
    '*_Core*', # Usuwa zmienne kończące się na '_Core' (np. $injector_core)
    '*Process*' # Usuwa zmienne kończące się na 'Process' (np. $process_manager)
)

# Usuwa zmienne w różnych zakresach za pomocą wzorców
foreach ($scope in @('Script', 'Local')) {
    foreach ($pattern in $variable_patterns_to_remove) {
        Get-Variable -Scope $scope -Name $pattern -ErrorAction SilentlyContinue | ForEach-Object {
            try {
                Remove-Variable -Name $_.Name -Scope $scope -Force -ErrorAction SilentlyContinue
            }
            catch {} # Ignoruje błędy
        }
    }
}
```

> [!TIP]
> Czyszczenie jest kluczowe w skryptach PowerShell, które importują wiele elementów do sesji. `Remove-Item -Path "Function:..."` i `Remove-Variable` są używane do zwalniania tych elementów. Użycie `ErrorAction SilentlyContinue` i pustych bloków `try/catch` w pętlach usuwania zapewnia, że skrypt czyszczący nie zawiedzie, jeśli jakiś element został już usunięty lub nie istnieje.

## Wszechstronne przykłady użycia

Aby zintegrować **SA-MP Injector PowerShell** w swoim projekcie lub używać go bezpośrednio, postępuj zgodnie z poniższymi instrukcjami i przeanalizuj scenariusze.

### 1. Przygotowanie środowiska deweloperskiego

- **PowerShell Version**: Zalecany jest **PowerShell 5.1** lub nowszy (kompatybilny z `Add-Type` dla klas).
- **Uprawnienia do wykonywania**: PowerShell ma zasady wykonywania. Będziesz musiał zezwolić na uruchamianie lokalnych skryptów. Otwórz PowerShell jako **Administrator** i wykonaj:
   ```powershell
   Set-ExecutionPolicy -ExecutionPolicy RemoteSigned -Scope CurrentUser
   ```
   Pozwoli to na uruchamianie podpisanych skryptów oraz skryptów, które utworzyłeś (nie pobranych z internetu) lokalnie bez podpisu.
- **Kopiowanie plików**: Umieść wszystkie pliki `.ps1` biblioteki (`Injector.ps1`, `Constants.ps1`, `CustomTypes.ps1`, `StringUtils.ps1`, `ErrorUtils.ps1`, `Validation.ps1`, `Process.ps1`, `InjectorCore.ps1`, `Cleanup.ps1`) w jednym katalogu.
- **Uprawnienia procesu**: Twój skrypt będzie potrzebował uprawnień **Administratora** do tworzenia procesów i wstrzykiwania DLL do innego procesu. Zawsze uruchamiaj **PowerShell jako Administrator** podczas korzystania z tej biblioteki.

### 2. Scenariusz podstawowy: Łączenie z serwerem SA-MP

Jest to najczęstszy przypadek użycia, uruchamianie GTA:SA i łączenie się z serwerem SA-MP z określoną nazwą użytkownika i adresem IP/portem.

```powershell
# Utwórz nowy skrypt, na przykład "StartSAMP.ps1"

# Importuje główną funkcję z biblioteki SA-MP Injector PowerShell
# Upewnij się, że poniższa ścieżka odzwierciedla lokalizację pliku Injector.ps1.
# Na przykład, jeśli Injector.ps1 znajduje się w tym samym folderze co ten skrypt:
$injector_path = Join-Path -Path $PSScriptRoot -ChildPath "Injector.ps1"

# Lub, jeśli znajduje się w podkatalogu:
# $injector_path = Join-Path -Path $PSScriptRoot -ChildPath "SA-MP-Injector-PowerShell\Injector.ps1"

# Importuje funkcję Injector.ps1 za pomocą dot-sourcing, aby jej funkcje
# były dostępne w bieżącym zakresie.
. $injector_path

# Zdefiniuj zmienne konfiguracyjne
# Zmień te ścieżki i szczegóły serwera, aby pasowały do Twojej lokalnej konfiguracji.
$game_folder = "C:\Games\GTA San Andreas" # Gdzie znajdują się gta_sa.exe, samp.dll
$player_nickname = "Nazwa"
$server_ip = "127.0.0.1" # Przykład: Twój lokalny serwer
$server_port = "7777"
$server_password = "" # Pozostaw puste, jeśli nie ma hasła

Write-Host "Uruchamianie SA-MP..." -ForegroundColor Cyan
Write-Host "Folder gry: $game_folder" -ForegroundColor Gray
Write-Host "Nazwa gracza: $player_nickname" -ForegroundColor Gray
Write-Host "Serwer: $server_ip:$server_port" -ForegroundColor Gray

# Wywołanie funkcji z biblioteki w celu uruchomienia gry
$result = Initialize_Game `
    -inject_type "samp" ` # Typ wstrzykiwania: "samp" lub "omp"
    -folder $game_folder ` # Ścieżka do folderu gry
    -nickname $player_nickname ` # Pożądana nazwa użytkownika
    -ip $server_ip ` # IP serwera
    -port $server_port ` # Port serwera (ciąg znaków)
    -password $server_password # Hasło serwera (ciąg znaków, może być pusty)

if ($result) {
    Write-Host "`n--- SA-MP pomyślnie zainicjowany! ---" -ForegroundColor Green
    Write-Host "Gra została uruchomiona w osobnym procesie." -ForegroundColor Green
}
else {
    Write-Host "`n--- NIEPOWODZENIE podczas uruchamiania SA-MP! ---" -ForegroundColor Red
    Write-Host "Sprawdź wyświetlone komunikaty o błędach (wyskakujące okienka lub konsola)." -ForegroundColor Red
}

# Utrzymuje konsolę otwartą, aby wyświetlić komunikaty wyjściowe
Read-Host "`nNaciśnij Enter, aby zamknąć program."```

**Aby uruchomić skrypt:**
1. **Zapisz** powyższy kod jako `StartSAMP.ps1` (lub dowolna inna nazwa, o ile kończy się na `.ps1`).
2. **Zapisz** wszystkie pliki biblioteki **SA-MP Injector PowerShell** w tym samym folderze lub w strukturze podfolderów, którą zarządzasz za pomocą `$injector_path`.
3. **Otwórz PowerShell jako Administrator**.
4. Przejdź do katalogu, w którym zapisałeś `StartSAMP.ps1`.
5. Uruchom skrypt:
   ```powershell
   .\StartSAMP.ps1
   ```
   (Pamiętaj, że `.` przed nazwą skryptu jest wymagane dla skryptów w bieżącym katalogu, chyba że dodasz go do zmiennej PATH).

### 3. Scenariusz zaawansowany: Łączenie z serwerem OMP

Dla OMP logika jest identyczna jak dla SA-MP, ale należy podać `"omp"` jako `inject_type` i upewnić się, że `omp-client.dll` jest obecny w katalogu gry.

```powershell
# Utwórz nowy skrypt, na przykład "StartOMP.ps1"

# Importuje główną funkcję z biblioteki SA-MP Injector PowerShell
$injector_path = Join-Path -Path $PSScriptRoot -ChildPath "Injector.ps1"
. $injector_path

# Zdefiniuj zmienne konfiguracyjne dla OMP
$game_folder = "C:\Games\GTA San Andreas" # Gdzie znajdują się gta_sa.exe, samp.dll i omp-client.dll
$player_nickname = "Nazwa"
$server_ip = "127.0.0.1" # Przykład: Twój lokalny serwer
$server_port = "7777"
$server_password = "" # Pozostaw puste, jeśli nie ma hasła

Write-Host "Uruchamianie OMP..." -ForegroundColor Cyan
Write-Host "Folder gry: $game_folder" -ForegroundColor Gray
Write-Host "Nazwa gracza: $player_nickname" -ForegroundColor Gray
Write-Host "Serwer: $server_ip:$server_port" -ForegroundColor Gray

# Wywołanie funkcji z biblioteki w celu uruchomienia gry
$result = Initialize_Game `
    -inject_type "omp" `   # Typ wstrzykiwania: "omp"
    -folder $game_folder `
    -nickname $player_nickname `
    -ip $server_ip `
    -port $server_port `
    -password $server_password

if ($result) {
    Write-Host "`n--- OMP pomyślnie zainicjowany! ---" -ForegroundColor Green
    Write-Host "Gra została uruchomiona w osobnym procesie." -ForegroundColor Green
}
else {
    Write-Host "`n--- NIEPOWODZENIE podczas uruchamiania OMP! ---" -ForegroundColor Red
    Write-Host "Sprawdź wyświetlone komunikaty o błędach (wyskakujące okienka lub konsola)." -ForegroundColor Red
}

Read-Host "`nNaciśnij Enter, aby zamknąć program."
```

**Aby uruchomić skrypt:**

Postępuj zgodnie z tymi samymi krokami co w poprzedniej sekcji, zastępując `StartSAMP.ps1` na `StartOMP.ps1`.

### 4. Wykonanie z skryptu nadrzędnego

Możliwe jest utworzenie bardziej złożonego skryptu, który wywołuje bibliotekę i obsługuje parametry lub warunki w bardziej zaawansowany sposób. Podstawowa koncepcja pozostaje ta sama: `Injector.ps1` musi być "dot-sourced" w skrypcie nadrzędnym.

```powershell
# Launcher.ps1
param(
    [string]$type = "samp",
    [string]$game_dir = "C:\Games\GTA San Andreas",
    [string]$player_nickname = "Nazwa",
    [string]$server_ip = "127.0.0.1",
    [string]$server_port = "7777",
    [string]$server_password = ""
)

# Ładuje Injector.ps1
$injector_script = Join-Path -Path $PSScriptRoot -ChildPath "Injector.ps1"

# Sprawdza, czy główny skrypt wstrzykiwacza istnieje przed załadowaniem
if (-not (Test-Path $injector_script -PathType Leaf)) {
    Write-Error "Nie znaleziono Injector.ps1 w $injector_script. Proszę sprawdzić ścieżkę."
    
    exit 1
}

. $injector_script # Używa dot-sourcing do załadowania funkcji

Write-Host "Próba uruchomienia gry z podanymi parametrami..." -ForegroundColor Yellow

$success = Initialize_Game -inject_type $type `
    -folder $game_dir `
    -nickname $player_nickname `
    -ip $server_ip `
    -port $server_port `
    -password $server_password

if ($success) {
    Write-Host "`nRaport launchera: Gra uruchomiona pomyślnie!" -ForegroundColor Green
}
else {
    Write-Host "`nRaport launchera: Nie udało się uruchomić gry!" -ForegroundColor Red
}

Read-Host "`nNaciśnij Enter, aby wyjść."
```

**Uruchomienie `Launcher.ps1`:**

```powershell
# Uruchamia z wartościami domyślnymi
.\Launcher.ps1

# Uruchamia dla OMP z określonym IP i portem
.\Launcher.ps1 -type "omp" -server_ip "omp.server.com" -server_port "7777" -player_nickname "Nazwa" -server_password "secure123"
```

## Obsługa typowych błędów i komunikatów

**SA-MP Injector PowerShell** priorytetowo traktuje użyteczność, a kluczową częścią tego jest dostarczanie jasnych informacji zwrotnych dla użytkownika w przypadku niepowodzenia. Komunikaty o błędach są prezentowane za pomocą **okien dialogowych systemu Windows** (`MessageBoxW`) lub bezpośrednio w konsoli PowerShell i są kategoryzowane według typu **wstrzykiwania (SA-MP lub OMP)** dla większego kontekstu. Zapewnia to, że dokładnie wiesz, co poszło nie tak i jak podejść do rozwiązania problemu.

Oto niektóre z typowych błędów, które możesz napotkać, oraz ich prawdopodobne przyczyny/rozwiązania, wraz z wizualnymi przykładami, jak te okna dialogowe pojawiają się dla użytkownika końcowego:

### 1. Nieprawidłowy typ wstrzykiwania

Jeśli podany `inject_type` nie jest `"samp"` ani `"omp"`, biblioteka nie będzie wiedziała, którego klienta wieloosobowego zamierzasz zainicjować.

![Error 1](screenshots/error_1.png)

- **Wyświetlany komunikat o błędzie**: `"Określono nieprawidłowy tryb wstrzykiwania. Proszę użyć 'samp' lub 'omp'."`
- **Przyczyna**: Argument `inject_type` nie odpowiada oczekiwanym wartościom `"samp"` lub `"omp"`. Może to być literówka, pusty ciąg znaków lub nierozpoznana wartość.
- **Rozwiązanie**: Sprawdź, czy `$inject_type` jest poprawnie ustawiony na `"samp"` lub `"omp"`. Ważne jest, aby ciąg znaków pasował dokładnie (chociaż kod używa `ToLower()` do porównania).
   ```powershell
   # Poprawnie:
   Initialize_Game -inject_type "samp" ...
   Initialize_Game -inject_type "omp" ...

   # Niepoprawnie (spowoduje błąd):
   # Initialize_Game -inject_type "invalid" ...
   # Initialize_Game -inject_type "" ...
   ```

### 2. Nieprawidłowy port serwera (format lub zakres)

Port jest niezbędnym parametrem numerycznym do połączenia z serwerem. Ten błąd występuje, jeśli wartość nie może być zinterpretowana jako prawidłowa liczba lub jest poza dopuszczalnym zakresem (**1 do 65535**).

#### 2.1. Nienumeryczny format portu

![Error 2](screenshots/error_2.png)

- **Wyświetlany komunikat o błędzie**: `"Nieprawidłowy format portu. Port musi być wartością numeryczną. Proszę podać prawidłową liczbę całkowitą dla portu."`
- **Przyczyna**: Argument `port` zawiera znaki, które nie są cyframi numerycznymi lub nie może być przekonwertowany na prawidłową liczbę całkowitą (np. `"abc"`, `"7777a"`).
- **Rozwiązanie**: Podaj ciąg znaków, który zawiera tylko cyfry i reprezentuje prawidłową liczbę całkowitą.
   ```powershell
   # Poprawnie:
   Initialize_Game ... -port "7777" ...
   
   # Niepoprawnie (nieprawidłowy format):
   # Initialize_Game ... -port "port7777" ...
   # Initialize_Game ... -port "invalid" ...
   ```

#### 2.2. Port poza prawidłowym zakresem

![Error 3](screenshots/error_3.png)

- **Wyświetlany komunikat o błędzie**: `"Podany numer portu (XXXX) jest poza prawidłowym zakresem od 1 do 65535. Proszę podać prawidłowy port."` (**XXXX** będzie wartością, którą próbowałeś użyć).
- **Przyczyna**: Podany port jest prawidłową liczbą, ale jest poniżej `1` (zarezerwowany lub nieużyteczny) lub powyżej `65535` (maksymalny limit dla **portów TCP/UDP**).
- **Rozwiązanie**: Podaj port, który mieści się w zakresie od `1` do `65535`. Typowe porty dla **SA-MP**/**OMP** to `7777`.
   ```powershell
   # Poprawnie:
   Initialize_Game ... -port "7777" ...

   # Niepoprawnie (poza zakresem):
   # Initialize_Game ... -port "0" ...      # Za niski
   # Initialize_Game ... -port "65536" ...  # Za wysoki
   # Initialize_Game ... -port "-1" ...     # Wartość ujemna
   ```

### 3. Nieprawidłowa nazwa użytkownika (pusta lub zbyt długa)

**Nazwa użytkownika** gracza jest walidowana, aby upewnić się, że klient gry ją zaakceptuje.

#### 3.1. Pusta nazwa użytkownika

![Error 4](screenshots/error_4.png)

- **Wyświetlany komunikat o błędzie**: `"Nazwa użytkownika nie może być pusta. Proszę podać prawidłową nazwę użytkownika."`
- **Przyczyna**: Argument `nickname` został podany jako pusty ciąg znaków.
- **Rozwiązanie**: Upewnij się, że nazwa użytkownika nie jest pusta.
   ```powershell
   # Poprawnie:
   Initialize_Game ... -nickname "MojaNazwa" ...

   # Niepoprawnie (pusty):
   # Initialize_Game ... -nickname "" ...
   ```

#### 3.2. Zbyt długa nazwa użytkownika

![Error 5](screenshots/error_5.png)

- **Wyświetlany komunikat o błędzie**: `"Długość nazwy użytkownika przekracza maksymalną dozwoloną liczbę 20 znaków. Proszę użyć krótszej nazwy użytkownika."`
- **Przyczyna**: Długość podanej **nazwy użytkownika** przekracza `$global:CONSTANTS.MAX_NICKNAME_LENGTH`, czyli `20` znaków.
- **Rozwiązanie**: Użyj **nazwy użytkownika**, która ma maksymalnie `20` znaków.
   ```powershell
   # Poprawnie:
   Initialize_Game ... -nickname "Krotka" ...

   # Niepoprawnie (za długa):
   # Initialize_Game ... -nickname "TaNazwaGraczaJestZbytDlugaDoUzyciaTutaj" ...
   ```

### 4. Nie znaleziono plików gry lub DLL

Jest to jedna z najczęstszych przyczyn niepowodzenia. Biblioteka wymaga, aby `gta_sa.exe`, `samp.dll` oraz, w przypadku **OMP**, `omp-client.dll` były obecne w oczekiwanych lokalizacjach.

#### 4.1. Nie znaleziono pliku wykonywalnego gry (`gta_sa.exe`)

![Error 6](screenshots/error_6.png)

- **Wyświetlany komunikat o błędzie**: `"Nie znaleziono pliku wykonywalnego gry. Proszę upewnić się, że 'gta_sa.exe' istnieje w podanej ścieżce: [pełna ścieżka]"`. `[pełna ścieżka]` będzie zawierać folder i nazwę pliku.
- **Przyczyna**: Plik `gta_sa.exe` nie został znaleziony w folderze podanym w argumencie `folder`.
- **Rozwiązanie**:
   1. Sprawdź, czy `$folder` wskazuje na poprawny katalog instalacyjny **GTA San Andreas**.
   2. Potwierdź, że `gta_sa.exe` istnieje w tym folderze i że jego nazwa nie została zmieniona.

#### 4.2. Nie znaleziono biblioteki SA-MP (`samp.dll`)

![Error 7](screenshots/error_7.png)

- **Wyświetlany komunikat o błędzie**: `"Nie znaleziono biblioteki SA-MP. Proszę upewnić się, że 'samp.dll' istnieje w podanej ścieżce: [pełna ścieżka]"`.
- **Przyczyna**: Plik `samp.dll` nie został znaleziony w folderze podanym w argumencie `folder`. **Ta DLL** jest wymagana dla **obu** typów wstrzykiwania (`samp` i `omp`).
- **Rozwiązanie**: Upewnij się, że `samp.dll` jest obecny w folderze instalacyjnym **GTA San Andreas**.

#### 4.3. Nie znaleziono biblioteki OMP (`omp-client.dll`) (tylko dla wstrzykiwania OMP)

![Error 8](screenshots/error_8.png)

- **Wyświetlany komunikat o błędzie**: `"Nie znaleziono biblioteki OMP. Proszę upewnić się, że 'omp-client.dll' istnieje w podanej ścieżce dla wstrzykiwania OMP: [pełna ścieżka]"`.
- **Przyczyna**: Jeśli określiłeś `"omp"` jako typ wstrzykiwania, ale plik `omp-client.dll` nie został znaleziony w podanym folderze.
- **Rozwiązanie**: Pobierz najnowszego klienta **OMP** i upewnij się, że `omp-client.dll` (oraz `samp.dll`) są obecne w folderze instalacyjnym **GTA San Andreas**.

### 5. Niepowodzenie tworzenia procesu gry

Jest to bardziej złożony błąd, ponieważ dotyczy **uprawnień systemu operacyjnego** i aktualnego stanu `gta_sa.exe`.

![Error 9](screenshots/error_9.png)

- **Wyświetlany komunikat o błędzie**: `"Nie udało się utworzyć procesu gry. Upewnij się, że 'gta_sa.exe' nie jest uruchomiony i masz wystarczające uprawnienia do wykonania pliku. Błąd systemowy: [Komunikat o błędzie systemu operacyjnego]"`. Komunikat systemowy zostanie dodany przez `Get_System_Error_Message` (np. `Odmowa dostępu.` lub `Żądana operacja wymaga podniesienia uprawnień.`).
- **Przyczyna**: Wywołanie `CreateProcessA` w celu uruchomienia `gta_sa.exe` nie powiodło się. Typowe przyczyny to:
   - **Proces już działa**: Instancja `gta_sa.exe` jest już aktywna i blokuje nowe uruchomienie.
   - **Niewystarczające uprawnienia**: Twój skrypt nie ma niezbędnych uprawnień (np. administratora) do tworzenia procesu w określonych konfiguracjach systemu (**UAC** włączone, chronione foldery itp.).
   - **Problemy z plikiem wykonywalnym**: `gta_sa.exe` może być uszkodzony lub zablokowany przez inny program (np. źle skonfigurowany antywirus).
- **Rozwiązanie**:
   1. Sprawdź Menedżera zadań i upewnij się, że nie ma uruchomionej żadnej instancji `gta_sa.exe`. Zamknij wszystkie, jeśli istnieją.
   2. Uruchom skrypt **PowerShell jako Administrator**. Kliknij prawym przyciskiem myszy na ikonę PowerShell i wybierz **"Uruchom jako administrator"** lub uruchom go ze skrótu skonfigurowanego do tego celu.
   3. Jeśli **antywirus** lub **oprogramowanie** zabezpieczające przeszkadza, dodaj swój skrypt i/lub folder **GTA:SA** do wyjątków antywirusa (rób to ostrożnie i tylko jeśli jesteś pewien integralności swoich plików).

### 6. Błąd alokacji pamięci w procesie docelowym

Biblioteka próbuje zaalokować niewielką przestrzeń pamięci w `gta_sa.exe`, aby skopiować **ścieżkę DLL**.

![Error 10](screenshots/error_10.png)

- **Wyświetlany komunikat o błędzie**: `"Nie udało się zaalokować pamięci w procesie docelowym. Może to być spowodowane niewystarczającymi uprawnieniami lub mechanizmami ochrony procesu. Błąd systemowy: [Komunikat o błędzie systemu operacyjnego]"`.
- **Przyczyna**: Funkcja `VirtualAllocEx` (używana do alokowania pamięci w innym procesie) nie powiodła się. Jest to najbardziej prawdopodobne, jeśli:
   - Proces **GTA:SA** (nawet w stanie zawieszonym) ma zabezpieczenia lub **łatki anty-wstrzykiwania**, które uniemożliwiają alokację pamięci przez zewnętrzne procesy.
   - Twój skrypt nie ma niezbędnych podniesionych uprawnień do manipulowania pamięcią innego procesu.
   - (Mniej powszechne) W systemie występuje skrajny niedobór pamięci wirtualnej.
- **Rozwiązanie**:
   1. Uruchom swój skrypt z uprawnieniami **Administratora**.
   2. Upewnij się, że gra nie ma żadnych modyfikacji ani **łatek bezpieczeństwa**, które mogłyby blokować próby wstrzykiwania lub manipulacji pamięcią (jest to częstsze w zmodyfikowanych środowiskach lub z niektórymi narzędziami anty-cheat firm trzecich).

### 7. Błąd zapisu ścieżki DLL w pamięci procesu

Po zaalokowaniu pamięci biblioteka próbuje skopiować do niej **ścieżkę DLL**.

![Error 11](screenshots/error_11.png)

- **Wyświetlany komunikat o błędzie**: `"Nie udało się zapisać ścieżki DLL do pamięci procesu docelowego. Sprawdź uprawnienia procesu i upewnij się, że ścieżka DLL jest dostępna. Błąd systemowy: [Komunikat o błędzie systemu operacyjnego]"`.
- **Przyczyna**: Funkcja `WriteProcessMemory` nie powiodła się podczas próby skopiowania **bajtów ścieżki DLL** do zdalnej pamięci zaalokowanej w `gta_sa.exe`. Zazwyczaj wskazuje to na:
   - **Uprawnienia do zapisu**: Twój skrypt nie ma uprawnień do zapisu w tym regionie pamięci lub w procesie **GTA:SA**.
   - **Nieprawidłowy uchwyt**: **Uchwyt** procesu w jakiś sposób stał się nieprawidłowy (mniej powszechne, ale możliwe w ekstremalnych warunkach systemowych).
   - **Problemy z ochroną pamięci**: Jakaś ochrona pamięci (czy to z **SO**, czy z modyfikacji gry) uniemożliwiła zapis.
- **Rozwiązanie**: Uruchom jako **Administrator**. Sprawdź, czy `gta_sa.exe` i jego środowisko są "czyste" od narzędzi, które mogłyby blokować operacje na pamięci.

### 8. Błąd podczas znajdowania podstawowych funkcji systemowych

Są to kluczowe API systemu Windows; błędy w tym miejscu wskazują na fundamentalny problem z systemem operacyjnym lub środowiskiem wykonawczym.

#### 8.1. Nie znaleziono `kernel32.dll`

![Error 12](screenshots/error_12.png)

- **Wyświetlany komunikat o błędzie**: `"Nie udało się uzyskać uchwytu do kernel32.dll. Jest to niezbędna biblioteka systemowa i ten błąd wskazuje na poważny problem systemowy. Błąd systemowy: [Komunikat o błędzie systemu operacyjnego]"`.
- **Przyczyna**: `kernel32.dll` jest jedną z najbardziej podstawowych bibliotek DLL systemu Windows, zawierającą niezbędne funkcje. Jeśli `GetModuleHandleA` nie może uzyskać do niej **uchwytu**, system operacyjny ma bardzo poważne problemy.
- **Rozwiązanie**: Jest to błąd **krytyczny**, który rzadko jest spowodowany przez bibliotekę lub twój skrypt. Sugeruje uszkodzenie plików systemowych, poważne problemy z **Windows** lub wysoce nietypową instalację **SO**. Zaleca się uruchomienie sprawdzania integralności systemu (takiego jak `sfc /scannow` w **Wierszu polecenia** jako **Administrator**) lub, w ostateczności, ponowną instalację **Windows**.

#### 8.2. Nie znaleziono `LoadLibraryA`

![Error 13](screenshots/error_13.png)

- **Wyświetlany komunikat o błędzie**: `"Nie udało się znaleźć adresu funkcji LoadLibraryA w kernel32.dll. Jest to kluczowe dla wstrzyknięcia DLL. Błąd systemowy: [Komunikat o błędzie systemu operacyjnego]"`.
- **Przyczyna**: Chociaż `kernel32.dll` został znaleziony, funkcja `LoadLibraryA` nie mogła zostać rozwiązana przez `GetProcAddress`. Chociaż jest to niezwykle rzadkie, może być wynikiem uszkodzenia **pliku DLL** `kernel32.dll` lub wysoce niestandardowego środowiska wykonawczego.
- **Rozwiązanie**: Podobnie jak błąd z `kernel32.dll` powyżej, wskazuje to na poważny problem z systemem operacyjnym.

### 9. Błąd tworzenia zdalnego wątku do wstrzykiwania

Po przygotowaniu środowiska zdalnego i skopiowaniu **ścieżki DLL**, tworzony jest nowy **wątek** w procesie gry, aby "wywołać" `LoadLibraryA`.

![Error 14](screenshots/error_14.png)

- **Wyświetlany komunikat o błędzie**: `"Nie udało się utworzyć zdalnego wątku w procesie docelowym w celu wykonania wstrzyknięcia DLL. Może to być spowodowane ograniczeniami bezpieczeństwa lub stanem procesu. Błąd systemowy: [Komunikat o błędzie systemu operacyjnego]"`.
- **Przyczyna**: Wywołanie `CreateRemoteThread` nie powiodło się. Ten błąd jest powszechny w systemach z solidnymi zabezpieczeniami **anty-wstrzykiwania** lub gdy program intensywnie monitoruje zachowanie procesu:
   - **Mechanizmy bezpieczeństwa**: Narzędzia **anty-cheat**, **oprogramowanie** zabezpieczające lub pewne zasady **Windows** mogą wykrywać i blokować próby tworzenia **wątków** w procesach firm trzecich.
   - **Niespójny proces docelowy**: Jeśli proces **GTA:SA** jest w nieoczekiwanym lub niestabilnym stanie (mimo że uruchomiony w `CREATE_SUSPENDED`), może to wpłynąć na zdolność do tworzenia w nim **wątków**.
- **Rozwiązanie**:
   1. Uruchom swój skrypt z uprawnieniami **Administratora**.
   2. Sprawdź, czy nie ma narzędzi **anty-cheat**, **agresywnych antywirusów** lub **zapór sieciowych** skonfigurowanych do inspekcji i blokowania manipulacji procesami, które mogą być w konflikcie. Dodaj swój skrypt i `gta_sa.exe` do wyjątków, jeśli to konieczne (z ostrożnością).
   3. Komunikat o błędzie systemowym może dostarczyć dodatkowych szczegółów do zbadania konkretnej przyczyny (np. **"Procesowi odmówiono dostępu do tworzenia wątków dla innych procesów."**).

### 10. Przekroczenie limitu czasu lub niepowodzenie ukończenia wstrzykiwania

Po utworzeniu **zdalnego wątku**, wstrzykiwacz czeka, aż zakończy on **ładowanie DLL**.

![Error 15](screenshots/error_15.png)

- **Wyświetlany komunikat o błędzie**: `"Przekroczono limit czasu lub wystąpił błąd podczas oczekiwania na zakończenie wstrzykiwania DLL (przekroczenie limitu czasu). Błąd systemowy: [Komunikat o błędzie systemu operacyjnego]"`.
- **Przyczyna**: **Zdalny wątek** wykonujący `LoadLibraryA` zajął więcej niż `$global:CONSTANTS.DLL_INJECTION_TIMEOUT_MS` (10 sekund), aby zakończyć, lub nie powiódł się i `GetExitCodeThread` zwrócił 0. Potencjalne przyczyny to:
   - **Problemy we wstrzykniętej DLL**: `DllMain` w `samp.dll` lub `omp-client.dll` wykonuje się zbyt długo, zawiera **nieskończoną pętlę**, **awarię** lub błąd, który **uniemożliwia poprawne załadowanie DLL** (np. brakujące **zależności DLL**).
   - **Ciche blokowanie**: Mechanizm bezpieczeństwa mógł zablokować `LoadLibraryA`, ale nie powiadomił o tym oczywistym błędem tworzenia **wątku**.
- **Rozwiązanie**:
   1. Sprawdź integralność plików `samp.dll` i `omp-client.dll`. Mogą być uszkodzone lub pochodzić z niekompatybilnej wersji z twoim `gta_sa.exe`.
   2. Upewnij się, że **wstrzyknięta DLL** nie zależy od **innych DLL**, które mogą brakować lub być niedostępne w systemie.

### 11. Niepowodzenie wznowienia wątku procesu gry

Jest to ostatni krok do uruchomienia gry po wstrzyknięciu **DLL**.

![Error 16](screenshots/error_16.png)

- **Wyświetlany komunikat o błędzie**: `"Nie udało się wznowić wątku procesu gry: [Komunikat o błędzie systemu operacyjnego]"`.
- **Przyczyna**: Wywołanie `ResumeThread` nie powiodło się, co oznacza, że **główny wątek** `gta_sa.exe` nie mógł zostać aktywowany, aby rozpocząć wykonywanie gry. Jest to rzadki błąd, ale może się zdarzyć, jeśli:
   - **Uchwyt** do **wątku** procesu stał się nieprawidłowy.
   - System operacyjny z jakiegoś powodu uniemożliwił wznowienie, być może związane z przerwaniem bezpieczeństwa lub niespójnym stanem procesu.
   - Proces mógł zostać zakończony zewnętrznie między **wstrzyknięciem DLL** a próbą wznowienia **głównego wątku**.
- **Rozwiązanie**: Jeśli wszystkie poprzednie kroki zakończyły się powodzeniem, a tylko `ResumeThread` nie powiodło się, może to być problem z systemem operacyjnym, samą instalacją **GTA:SA** lub innym bardzo rygorystycznym **oprogramowaniem** zabezpieczającym. Sprawdź ponownie stan `gta_sa.exe` za pomocą **Menedżera zadań** tuż przed i po błędzie. Próba ponownego uruchomienia komputera może rozwiązać tymczasowe problemy ze stanem systemu.

> [!TIP]
> W złożonych scenariuszach debugowania narzędzia takie jak **Process Monitor (Sysinternals Suite)** lub debuger (taki jak **WinDbg**) mogą być nieocenione. Mogą pomóc w obserwowaniu wywołań **API**, sprawdzaniu błędów dostępu, śledzeniu stanu **uchwytów**, a nawet inspekcji pamięci procesu, zapewniając dogłębny wgląd w to, co dzieje się pod maską.
>
> Do debugowania skryptów PowerShell, które używają `Add-Type` i wchodzą w interakcje z WinAPI na niskim poziomie, przydatne są narzędzia takie jak **PowerShell Integrated Scripting Environment (ISE)** lub **Visual Studio Code** z rozszerzeniem PowerShell, pozwalające na ustawianie punktów przerwania i inspekcję zmiennych. Pamiętaj, aby zawsze uruchamiać je **jako Administrator**.

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