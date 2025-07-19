# SA-MP Injector PowerShell

![License](https://img.shields.io/badge/License-MIT-yellow.svg?style=flat)
![PowerShell](https://img.shields.io/badge/PowerShell-5.1%2B-blue.svg?style=flat&logo=powershell)
![Platform](https://img.shields.io/badge/Platform-Windows-0078D6.svg?style=flat&logo=windows)
[![SA-MP | OMP](https://img.shields.io/badge/Support-SA--MP%20%7C%20OMP-yellow)](https://github.com/spc-samp/samp-injector)
![Code Quality](https://img.shields.io/badge/Code%20Quality-High-brightgreen.svg?style=flat)

**SA-MP Injector PowerShell** är mer än bara ett **DLL-injektionsskript**. Det representerar ett **bibliotek av PowerShell-funktioner och klasser** som utvecklats för att erbjuda en robust och komplett lösning för programmatisk start av spelet **Grand Theft Auto: San Andreas** (**GTA:SA**) tillsammans med dess multiplayer-klienter, specifikt **SA-MP (San Andreas Multiplayer)** och **OMP (Open Multiplayer)**. Dess primära syfte är att förenkla processen att starta spelet, och eliminera den komplexitet som är förknippad med direkt hantering av operativsystemprocesser och överföring av kommandoradsargument.

Utvecklat för att erbjuda maximal flexibilitet och enkel integration, låter detta bibliotek utvecklare införliva det direkt i sina **PowerShell-projekt och skript**. Det orkestrerar inte bara den **grundläggande injektionen av multiplayer-klientens DLL-filer** (`samp.dll` eller `omp-client.dll`), utan hanterar också intelligent alla väsentliga anslutningsparametrar (**smeknamn**, **IP-adress**, **port** och **lösenord**), och simulerar en native start genom de inneboende funktionerna i **Windows API**, som nås direkt via **PowerShell**.

## Språk

- Português: [README](../../)
- Deutsch: [README](../Deutsch/README.md)
- English: [README](../English/README.md)
- Español: [README](../Espanol/README.md)
- Français: [README](../Francais/README.md)
- Italiano: [README](../Italiano/README.md)
- Polski: [README](../Polski/README.md)
- Русский: [README](../Русский/README.md)
- Türkçe: [README](../Turkce/README.md)

## Innehållsförteckning

- [SA-MP Injector PowerShell](#sa-mp-injector-powershell)
  - [Språk](#språk)
  - [Innehållsförteckning](#innehållsförteckning)
  - [Grundläggande Koncept och Motivation](#grundläggande-koncept-och-motivation)
    - [Varför Injicera DLL-filer?](#varför-injicera-dll-filer)
    - [SA-MP och OMP: Skillnader och Likheter](#sa-mp-och-omp-skillnader-och-likheter)
    - [DLL-injektion i PowerShell: En Direkt Metod med WinAPI](#dll-injektion-i-powershell-en-direkt-metod-med-winapi)
  - [Bibliotekets Interna Arkitektur: En Djupdykning](#bibliotekets-interna-arkitektur-en-djupdykning)
    - [`Constants.ps1`](#constantsps1)
    - [`CustomTypes.ps1`](#customtypesps1)
    - [`StringUtils.ps1`](#stringutilsps1)
    - [`ErrorUtils.ps1`](#errorutilsps1)
    - [`Process.ps1`](#processps1)
    - [`InjectorCore.ps1`](#injectorcoreps1)
    - [`Injector.ps1`](#injectorps1)
    - [`Cleanup.ps1`](#cleanupps1)
  - [Omfattande Användningsexempel](#omfattande-användningsexempel)
    - [1. Förberedelse av Utvecklingsmiljön](#1-förberedelse-av-utvecklingsmiljön)
    - [2. Grundläggande Scenario: Anslutning till en SA-MP Server](#2-grundläggande-scenario-anslutning-till-en-sa-mp-server)
    - [3. Avancerat Scenario: Anslutning till en OMP Server](#3-avancerat-scenario-anslutning-till-en-omp-server)
    - [4. Exekvering från ett Föräldraskript](#4-exekvering-från-ett-föräldraskript)
  - [Hantering av Vanliga Fel och Meddelanden](#hantering-av-vanliga-fel-och-meddelanden)
    - [1. Ogiltig Injektionstyp](#1-ogiltig-injektionstyp)
    - [2. Ogiltig Serverport (Format eller Intervall)](#2-ogiltig-serverport-format-eller-intervall)
      - [2.1. Icke-numeriskt Portformat](#21-icke-numeriskt-portformat)
      - [2.2. Port Utanför Giltigt Intervall](#22-port-utanför-giltigt-intervall)
    - [3. Ogiltigt Smeknamn (Tomt eller För Långt)](#3-ogiltigt-smeknamn-tomt-eller-för-långt)
      - [3.1. Tomt Smeknamn](#31-tomt-smeknamn)
      - [3.2. För Långt Smeknamn](#32-för-långt-smeknamn)
    - [4. Spelfiler eller DLL Hittades Inte](#4-spelfiler-eller-dll-hittades-inte)
      - [4.1. Spel-exekverbar (`gta_sa.exe`) Hittades Inte](#41-spel-exekverbar-gta_saexe-hittades-inte)
      - [4.2. SA-MP Bibliotek (`samp.dll`) Hittades Inte](#42-sa-mp-bibliotek-sampdll-hittades-inte)
      - [4.3. OMP Bibliotek (`omp-client.dll`) Hittades Inte (endast för OMP-injektion)](#43-omp-bibliotek-omp-clientdll-hittades-inte-endast-för-omp-injektion)
    - [5. Misslyckades med att Skapa Spelprocessen](#5-misslyckades-med-att-skapa-spelprocessen)
    - [6. Misslyckades med Minnesallokering i Målprocessen](#6-misslyckades-med-minnesallokering-i-målprocessen)
    - [7. Misslyckades med att Skriva DLL-sökväg till Processminnet](#7-misslyckades-med-att-skriva-dll-sökväg-till-processminnet)
    - [8. Misslyckades med att Hitta Viktiga Systemfunktioner](#8-misslyckades-med-att-hitta-viktiga-systemfunktioner)
      - [8.1. `kernel32.dll` Hittades Inte](#81-kernel32dll-hittades-inte)
      - [8.2. `LoadLibraryA` Hittades Inte](#82-loadlibrarya-hittades-inte)
    - [9. Misslyckades med att Skapa Fjärrtråd för Injektion](#9-misslyckades-med-att-skapa-fjärrtråd-för-injektion)
    - [10. Timeout eller Misslyckad Slutförande av Injektion](#10-timeout-eller-misslyckad-slutförande-av-injektion)
    - [11. Misslyckades med att Återuppta Spelprocessens Tråd](#11-misslyckades-med-att-återuppta-spelprocessens-tråd)
  - [Licens](#licens)
    - [Användarvillkor](#användarvillkor)
      - [1. Beviljade rättigheter](#1-beviljade-rättigheter)
      - [2. Obligatoriska villkor](#2-obligatoriska-villkor)
      - [3. Upphovsrätt](#3-upphovsrätt)
      - [4. Garantifriskrivning och ansvarsbegränsning](#4-garantifriskrivning-och-ansvarsbegränsning)

## Grundläggande Koncept och Motivation

### Varför Injicera DLL-filer?

> [!NOTE]
> **DLL (Dynamic Link Library) injektion** är en metod som används i **Microsoft Windows** operativsystem som tillåter exekvering av kod inom minnesutrymmet för en annan körande process. Det är en kraftfull teknik med flera legitima tillämpningar, från felsökning och övervakning av program till att modifiera applikationsbeteende för att utöka deras funktionalitet.

I sammanhanget av spel som **GTA San Andreas**, som ursprungligen inte utvecklades med inbyggd multiplayer-funktionalitet, är **DLL-injektion** grunden för existensen av multiplayer-klienter som **SA-MP** och **OMP**. Dessa klienter implementeras som **DLL-filer** som, när de injiceras i `gta_sa.exe`-processen, tar kontroll, avlyssnar spelfunktioner och etablerar kommunikation med multiplayer-servrar.

Istället för att förlita sig på en extern startprogram eller direkt modifiering av spelets exekverbara fil, möjliggör **DLL-injektion** en mer flexibel och programmerbar start, särskilt användbart i miljöer där man vill automatisera anslutningsprocessen till specifika servrar med fördefinierade konfigurationer.

### SA-MP och OMP: Skillnader och Likheter

**SA-MP** och **OMP** är de två huvudsakliga multiplayer-plattformarna för **GTA San Andreas**. Båda fungerar som modifieringar av grundspelet och omvandlar det till en massivt multiplayer-online-miljö.

- **SA-MP (San Andreas Multiplayer)**: Den ursprungliga och mest etablerade klienten, som har använts i stor utsträckning i många år. Dess arkitektur kräver `samp.dll` för att fungera.
- **OMP (Open Multiplayer)**: Ett open source-projekt, som ofta ses som en efterträdare eller ett modernare alternativ till **SA-MP**, och erbjuder förbättringar i prestanda, stabilitet och ytterligare funktioner. Det kräver `omp-client.dll`.

Även om de fungerar på liknande sätt (**genom att injicera en DLL** i **GTA:SA**-processen), har biblioteket **SA-MP Injector PowerShell** noggrant utvecklats för att stödja **båda DLL-filerna**, och erkänner deras skillnader i filnamn och låter utvecklaren välja önskad multiplayer-klient via en konfigurationsparameter. Detta säkerställer att biblioteket kan användas med det stora utbudet av servrar och projekt baserade på endera plattformen.

### DLL-injektion i PowerShell: En Direkt Metod med WinAPI

PowerShell är ett kraftfullt skriptspråk för automatisering i Windows, men hantering av processer och DLL-injektion på en så låg systemnivå är inte dess primära funktion. För att uppnå detta mål använder biblioteket **SA-MP Injector PowerShell** omfattande kommandot `Add-Type` för att direkt anropa funktioner från **Windows API (WinAPI)**.

`Add-Type` låter dig definiera och kompilera C#-kod (eller andra .NET-språk) vid körning i PowerShell-miljön. Denna C#-kod fungerar som en "bro" till de native WinAPI-funktionerna (`DllImport`), vilket möjliggör operationer som:

- **`CreateProcessA`**: För att starta GTA:SA-processen.
- **`VirtualAllocEx`**: För att allokera minne inom fjärrprocessen.
- **`WriteProcessMemory`**: För att kopiera DLL-sökvägen till det allokerade minnet.
- **`GetModuleHandleA` och `GetProcAddress`**: För att hämta adressen till `LoadLibraryA`-funktionen i `kernel32.dll`.
- **`CreateRemoteThread`**: För att skapa en tråd i fjärrprocessen som exekverar `LoadLibraryA`, vilket effektivt laddar DLL-filen.
- **`WaitForSingleObject` och `GetExitCodeThread`**: För att övervaka framgången av injektionen.
- **`ResumeThread`**: För att återaktivera spelprocessen efter injektionen.
- **`CloseHandle`**: För att stänga systemresurshandtag och undvika läckor.
- **`MessageBoxW`**: För att visa informativa felmeddelanden till användaren.

Denna direkta metod med WinAPI gör att PowerShell kan utföra samma lågnivåoperationer som en kompilerad applikation i **C++** skulle göra, med bekvämligheten av en skriptmiljö.

## Bibliotekets Interna Arkitektur: En Djupdykning

Biblioteket **SA-MP Injector PowerShell** använder ett modulärt tillvägagångssätt för att hantera komplexiteten i injektionsprocessen. Varje skript är en specialiserad modul, ansvarig för en specifik del av den övergripande funktionaliteten, vilket främjar kodens tydlighet, underhållbarhet och utbyggbarhet.

### `Constants.ps1`

Detta skript är grunden för alla fasta konfigurationer i biblioteket. Det definierar en global hash-tabell (`$global:CONSTANTS`) som lagrar alla literaler och numeriska värden som används, såsom portgränser, DLL-filnamn, referenser till system-API:er och flaggor för operationer som processkapande och minnesallokering.

```powershell
$global:CONSTANTS = @{
    # Valideringsgränser för port
    MIN_PORT = 1
    MAX_PORT = 65535
    
    # Begränsningar för smeknamn
    MAX_NICKNAME_LENGTH = 20
    
    # Nödvändiga filnamn
    SAMP_DLL_NAME = "samp.dll"
    OMP_DLL_NAME = "omp-client.dll"
    GAME_EXE_NAME = "gta_sa.exe"
    
    # System-API-referenser
    KERNEL32_DLL = "kernel32.dll"
    USER32_DLL = "user32.dll" # Används för MessageBoxW
    LOAD_LIBRARY_FUNC = "LoadLibraryA"
    
    # Prefix för kommandoradsargument
    CMD_ARG_CONFIG = "-c"
    CMD_ARG_NICKNAME = "-n"
    CMD_ARG_HOST = "-h"
    CMD_ARG_PORT = "-p"
    CMD_ARG_PASSWORD = "-z"
    
    # Identifierare för injektionstyp
    INJECT_TYPE_SAMP = "samp"
    INJECT_TYPE_OMP = "omp"
    
    # Titlar för felmeddelanden
    ERROR_TITLE_SAMP = "SA-MP Injector Error - SPC"
    ERROR_TITLE_OMP = "OMP Injector Error - SPC"
    
    # Flaggor för processkapande (CREATE_SUSPENDED | DETACHED_PROCESS)
    # 0x00000104 = CREATE_SUSPENDED (0x4) + DETACHED_PROCESS (0x100)
    PROCESS_CREATION_FLAGS = 0x00000104
    
    # Tidsgränser för operationer
    DLL_INJECTION_TIMEOUT_MS = 10000 # 10 sekunder
    
    # Konstanter för minnesallokering
    # 0x00003000 = MEM_COMMIT (0x1000) + MEM_RESERVE (0x2000)
    MEMORY_ALLOCATION_TYPE = 0x00003000
    # 0x00000004 = PAGE_READWRITE
    MEMORY_PROTECTION = 0x00000004
    # 0x00008000 = MEM_RELEASE
    MEMORY_FREE_TYPE = 0x00008000
    
    # Resultat för väntobjekt (Windows API)
    WAIT_OBJECT_0 = 0x00000000
    WAIT_TIMEOUT = 0x00000102
    WAIT_FAILED = 0xFFFFFFFF
    
    # Felindikator för återupptagande av tråd (Windows API)
    THREAD_RESUME_ERROR = 0xFFFFFFFF # ResumeThread returnerar -1 vid misslyckande
    
    # Konstanter för MessageBox (Windows API)
    MB_OK = 0x00000000
    MB_ICONERROR = 0x00000010
    MB_TOPMOST = 0x00040000
}
```

> [!TIP]
> Användningen av en global hash-tabell för konstanter är en vanlig praxis i PowerShell-skript. Det centraliserar konfigurationerna och undviker "magiska nummer" och upprepade strängar, vilket gör koden mer läsbar och lättare att underhålla. Värdena för flaggorna (`0x...`) motsvarar de decimala värdena för konstanterna definierade i Windows API.

### `CustomTypes.ps1`

Detta skript är grundläggande för interaktionen med Windows API. Det definierar C#-typer vid körning med `Add-Type`, inklusive:

- **`Inject_Type` enum**: För att kategorisera typen av injektion (SAMP eller OMP), vilket förbättrar typsäkerheten.
- **`WinAPI` class**: En statisk klass som importerar och exponerar de Windows API-funktioner som behövs för injektion. Varje metod i denna klass motsvarar en API-funktion (`DllImport`), med korrekt signatur och teckenuppsättning (`CharSet`).
- **`Startup_Info` struct och `Process_Information` struct**: C#-datastrukturer som replikerar `STARTUPINFO`- och `PROCESS_INFORMATION`-strukturerna som används av `CreateProcessA`-funktionen i Windows API.
- **`Process_Info` class**: En enkel C#-klass som fungerar som en container för process- och trådhandtagen som returneras efter ett framgångsrikt skapande av en process, vilket underlättar transport och hantering av dessa handtag inom PowerShell-miljön.

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
        using System.Text; // Krävs för Marshal.GetLastWin32Error
        
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
            
            // C#-struktur för STARTUPINFO
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
            
            // C#-struktur för PROCESS_INFORMATION
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
        
        // Hjälpklass för att transportera process- och trådhandtag
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
> Injektion av 32-bitars DLL-filer (som `samp.dll` och `omp-client.dll`) i en 32-bitars process (`gta_sa.exe`) **kräver att PowerShell-miljön också är 32-bitars**. **SA-MP Injector PowerShell** hanterar detta automatiskt genom att starta om sig själv i ett x86 PowerShell-skal om den upptäcker att den körs i en x64-miljö. Detta är avgörande för att säkerställa kompatibiliteten för pekarens storlek och korrekt funktion av injektionen.
>
> Direktivet `if (-not ([System.Management.Automation.PSTypeName]'TypeName').Type)` säkerställer att C#-typerna läggs till i PowerShell-miljön endast en gång, vilket undviker omdefinieringsfel om skriptet körs flera gånger i samma session.

### `StringUtils.ps1`

Denna modul tillhandahåller en väsentlig verktygsfunktion för strängmanipulation, specifikt för att hantera teckenkodningar som krävs vid interaktion med det äldre Windows API (funktioner "A" av char*).

```powershell
function Convert_Wide_To_Local_8Bit {
    param([Parameter(Mandatory = $false)] [AllowEmptyString()] [string]$wide_string)
    
    if ([string]::IsNullOrEmpty($wide_string)) {
        return [string]::Empty
    }

    try {
        # Hämtar systemets lokala ANSI-kod sida
        $ansi_code_page = [System.Globalization.CultureInfo]::CurrentCulture.TextInfo.ANSICodePage
        $encoding = [System.Text.Encoding]::GetEncoding($ansi_code_page)
        
        # Konverterar Unicode-strängen (wide) till bytes i den lokala ANSI-kodningen
        $bytes = $encoding.GetBytes($wide_string)

        # Konverterar byten tillbaka till en sträng med samma ANSI-kodning
        # Detta säkerställer att strängen är kompatibel med API:er som förväntar sig 8-bitars kodning (ANSI)
        return $encoding.GetString($bytes)
    }
    catch {
        # Vid fel i konverteringen (t.ex. tecken som inte kan mappas),
        # returnera den ursprungliga strängen som en fallback, även om det kan orsaka problem
        # om den innehåller tecken som inte stöds av ANSI-API:er.
        return $wide_string
    }
}
```

> [!IMPORTANT]
> Funktionen `Convert_Wide_To_Local_8Bit` är avgörande eftersom många Windows API-funktioner med suffixet "A" (`CreateProcessA`, `LoadLibraryA`, `GetModuleHandleA`, `GetProcAddress`) förväntar sig strängar kodade i ANSI (8-bit), som är beroende av systemets lokala kodsida. Som standard är strängar i PowerShell Unicode. Denna funktion utför den nödvändiga konverteringen. Om ett filnamn eller ett kommandoradsargument innehåller tecken utanför systemets ANSI-kod sida kan konverteringen resultera i felaktiga tecken eller dataförlust. För detta projekt, som syftar till att interagera med äldre program, är detta ANSI-tillvägagångssätt vanligtvis tillräckligt och nödvändigt.

### `ErrorUtils.ps1`

Denna modul ansvarar för att ge tydlig feedback till användaren vid fel. Den centraliserar logiken för att hämta systemfelmeddelanden och visa standarddialogrutor i Windows.

```powershell
function Get_System_Error_Message {
    param([Parameter(Mandatory = $true)][int]$error_code)
    
    try {
        # Använder Win32Exception för att få det systemformaterade felmeddelandet
        $exception = New-Object System.ComponentModel.Win32Exception($error_code)
        
        return $exception.Message
    }
    catch {
        # Fallback till okänt felmeddelande
        return "Okänt fel (Kod: $error_code)"
    }
}

function Show_Error {
    param([Parameter(Mandatory = $true)][string]$message, [Parameter(Mandatory = $true)][Inject_Type]$inject_type)
    
    # Bestämmer dialogrutans titel baserat på injektionstypen
    $title = if ($inject_type -eq [Inject_Type]::SAMP) {
        $global:CONSTANTS.ERROR_TITLE_SAMP
    }
    else {
        $global:CONSTANTS.ERROR_TITLE_OMP
    }
    
    try {
        # Kombinerar flaggor för MessageBoxW (OK, Felikon, Alltid Överst)
        $message_box_flags = $global:CONSTANTS.MB_OK -bor $global:CONSTANTS.MB_ICONERROR -bor $global:CONSTANTS.MB_TOPMOST
        
        # Anropar den importerade MessageBoxW-funktionen via Add-Type
        [void][WinAPI]::MessageBoxW([System.IntPtr]::Zero, $message, $title, $message_box_flags)
    }
    catch {
        # Om det inte går att visa MessageBox (t.ex. i miljöer utan UI), skriv till konsolen
        Write-Host "[$title] $message" -ForegroundColor Red
    }
}
```

> [!NOTE]
> `Get_System_Error_Message` använder `System.ComponentModel.Win32Exception` från .NET för att konvertera en numerisk felkod från Windows API (`GetLastError()`) till en textbeskrivning som är läsbar för användaren, och som kan vara lokaliserad till operativsystemets språk.
>
> `Show_Error` använder den importerade funktionen `MessageBoxW` från `user32.dll` via `Add-Type` (`CustomTypes.ps1`) för att visa en informativ dialogruta. Flaggor som `MB_OK` och `MB_ICONERROR` importeras från WinAPI-konstanterna.

### `Process.ps1`

Detta är huvudmodulen som ansvarar för den direkta interaktionen med Windows lågnivå-API:er för att manipulera processer. Den kapslar in de avgörande operationerna för processkapande och DLL-injektion, och hanterar handtag, minne och trådar.

```powershell
class Process {
    # Frigör process- och trådhandtagen, förhindrar resursläckor
    [void] Close_Process_Info([Process_Info]$process_info) {
        if ($null -ne $process_info) {
            # Stänger processhandtaget om det är giltigt
            if ($process_info.ProcessHandle -ne [System.IntPtr]::Zero -and $process_info.ProcessHandle -ne [System.IntPtr]::new(-1)) {
                [void][WinAPI]::CloseHandle($process_info.ProcessHandle)
                $process_info.ProcessHandle = [System.IntPtr]::Zero # Markerar som stängd
            }

            # Stänger trådhandtaget om det är giltigt
            if ($process_info.ThreadHandle -ne [System.IntPtr]::Zero -and $process_info.ThreadHandle -ne [System.IntPtr]::new(-1)) {
                [void][WinAPI]::CloseHandle($process_info.ThreadHandle)
                $process_info.ThreadHandle = [System.IntPtr]::Zero # Markerar som stängd
            }
        }
    }

    # Skapar spelprocessen för GTA:SA i suspenderat tillstånd
    [Process_Info] Create_Game_Process([string]$game_path, [string]$command_args, [string]$working_dir) {
        $startup_info = New-Object WinAPI+Startup_Info
        # Anger strukturens storlek, avgörande för Windows API:er
        $startup_info.cb = [System.Runtime.InteropServices.Marshal]::SizeOf($startup_info)
        
        $process_information = New-Object WinAPI+Process_Information
        
        $command_line_bytes = $null

        if (-not [string]::IsNullOrEmpty($command_args)) {
            # Konverterar kommandoradsargumenten till en byte-array i ANSI med null-terminering
            $command_line_bytes = [System.Text.Encoding]::Default.GetBytes($command_args + "`0")
        }
        
        # Anger arbetskatalogen, null om tom
        $current_directory = if ([string]::IsNullOrEmpty($working_dir)) {
            $null
        }
        else {
            $working_dir
        }
        
        # Anropar CreateProcessA-funktionen i Windows API
        $success = [WinAPI]::CreateProcessA($game_path, $command_line_bytes, [System.IntPtr]::Zero, [System.IntPtr]::Zero, $false, $global:CONSTANTS.PROCESS_CREATION_FLAGS, 
            [System.IntPtr]::Zero, $current_directory, [ref]$startup_info, [ref]$process_information)
        
        if (-not $success) {
            # Vid fel, hämta det sista systemfelet och visa det
            $error_code = [System.Runtime.InteropServices.Marshal]::GetLastWin32Error()
            $error_message = Get_System_Error_Message $error_code
            Show_Error "Misslyckades med att skapa spelprocessen. Se till att 'gta_sa.exe' inte körs och att du har tillräckliga behörigheter för att köra filen. Systemfel: $error_message" ([Inject_Type]::SAMP)

            return $null # Returnerar null vid fel
        }
        
        # Returnerar ett Process_Info-objekt som innehåller processens och trådens handtag
        $result = New-Object Process_Info
        $result.ProcessHandle = $process_information.hProcess
        $result.ThreadHandle = $process_information.hThread
        
        return $result
    }
    
    # Injicerar en DLL i fjärrprocessen
    [bool] Inject_DLL([IntPtr]$process_handle, [string]$dll_path, [ref]$error_message) {
        if ($process_handle -eq [System.IntPtr]::Zero) {
            $error_message.Value = "Ogiltigt processhandtag angivet för DLL-injektion."

            return $false
        }
        
        if ([string]::IsNullOrEmpty($dll_path)) {
            $error_message.Value = "DLL-sökväg kan inte vara tom."

            return $false
        }
        
        # Konverterar DLL-sökvägen till ASCII-bytes (ANSI 8-bit) med null-terminering
        $dll_path_bytes = [System.Text.Encoding]::ASCII.GetBytes($dll_path + "`0")
        $dll_path_size = $dll_path_bytes.Length
        
        # Allokerar minne i fjärrprocessen för DLL-sökvägen
        $remote_memory = [WinAPI]::VirtualAllocEx($process_handle, [System.IntPtr]::Zero, $dll_path_size, $global:CONSTANTS.MEMORY_ALLOCATION_TYPE, $global:CONSTANTS.MEMORY_PROTECTION)
        
        if ($remote_memory -eq [System.IntPtr]::Zero) {
            $error_code = [System.Runtime.InteropServices.Marshal]::GetLastWin32Error()
            $error_message.Value = "Misslyckades med att allokera minne i målprocessen. Detta kan bero på otillräckliga behörigheter eller processskyddsmekanismer. Systemfel: $(Get_System_Error_Message $error_code)"

            return $false
        }
        
        # Använder ett try/finally-block för att säkerställa att fjärrminnet frigörs
        try {
            $bytes_written = [System.IntPtr]::Zero
            # Skriver DLL-sökvägen till fjärrminnet
            $write_success = [WinAPI]::WriteProcessMemory($process_handle, $remote_memory, $dll_path_bytes, $dll_path_size, [ref]$bytes_written)
            
            if (-not $write_success) {
                $error_code = [System.Runtime.InteropServices.Marshal]::GetLastWin32Error()
                $error_message.Value = "Misslyckades med att skriva DLL-sökvägen till målprocessens minne. Verifiera processbehörigheter och se till att DLL-sökvägen är tillgänglig. Systemfel: $(Get_System_Error_Message $error_code)"
                
                return $false
            }
            
            # Hämtar handtaget till kernel32.dll (som är laddat i alla processer)
            $kernel32_handle = [WinAPI]::GetModuleHandleA($global:CONSTANTS.KERNEL32_DLL)

            if ($kernel32_handle -eq [System.IntPtr]::Zero) {
                $error_code = [System.Runtime.InteropServices.Marshal]::GetLastWin32Error()
                $error_message.Value = "Misslyckades med att hämta ett handtag till kernel32.dll. Detta är ett viktigt systembibliotek och detta fel indikerar ett allvarligt systemproblem. Systemfel: $(Get_System_Error_Message $error_code)"
                
                return $false
            }
            
            # Hämtar adressen till funktionen LoadLibraryA i kernel32.dll.
            # Denna adress är konsekvent mellan processer på samma operativsystem.
            $load_library_address = [WinAPI]::GetProcAddress($kernel32_handle, $global:CONSTANTS.LOAD_LIBRARY_FUNC)

            if ($load_library_address -eq [System.IntPtr]::Zero) {
                $error_code = [System.Runtime.InteropServices.Marshal]::GetLastWin32Error()
                $error_message.Value = "Misslyckades med att hitta adressen till LoadLibraryA-funktionen i kernel32.dll. Detta är kritiskt för att injicera DLL-filen. Systemfel: $(Get_System_Error_Message $error_code)"
                
                return $false
            }
            
            $thread_id = [System.IntPtr]::Zero
            # Skapar en fjärrtråd i målprocessen för att exekvera LoadLibraryA
            $remote_thread_handle = [WinAPI]::CreateRemoteThread($process_handle, [System.IntPtr]::Zero, 0, $load_library_address, $remote_memory, 0, [ref]$thread_id)
            
            if ($remote_thread_handle -eq [System.IntPtr]::Zero) {
                $error_code = [System.Runtime.InteropServices.Marshal]::GetLastWin32Error()
                $error_message.Value = "Misslyckades med att skapa en fjärrtråd i målprocessen för att utföra DLL-injektionen. Detta kan bero på säkerhetsrestriktioner eller processtillstånd. Systemfel: $(Get_System_Error_Message $error_code)"
                
                return $false
            }
            
            # Använder ett try/finally-block för att säkerställa att fjärrtrådens handtag stängs
            try {
                # Väntar på att fjärrtråden (DLL-injektionen) ska slutföras eller nå en timeout
                $wait_result = [WinAPI]::WaitForSingleObject($remote_thread_handle, $global:CONSTANTS.DLL_INJECTION_TIMEOUT_MS)
                
                if ($wait_result -ne $global:CONSTANTS.WAIT_OBJECT_0) {
                    $error_code = [System.Runtime.InteropServices.Marshal]::GetLastWin32Error()

                    $wait_result_message = switch ($wait_result) {
                        $global:CONSTANTS.WAIT_TIMEOUT { "timeout" }
                        $global:CONSTANTS.WAIT_FAILED { "väntan misslyckades" }
                        default { "okänt väntresultat ($wait_result)" }
                    }

                    $error_message.Value = "Timeout eller fel vid väntan på att DLL-injektionen ska slutföras ($wait_result_message). Systemfel: $(Get_System_Error_Message $error_code)"

                    return $false
                }
                
                $exit_code = 0
                # Hämtar utgångskoden från fjärrtråden. För LoadLibraryA betyder 0 misslyckande.
                $get_exit_code_success = [WinAPI]::GetExitCodeThread($remote_thread_handle, [ref]$exit_code)
                
                if (-not $get_exit_code_success -or $exit_code -eq 0) {
                    $error_code = [System.Runtime.InteropServices.Marshal]::GetLastWin32Error()
                    $error_message.Value = "DLL-injektion misslyckades eller returnerade ett fel. Anropet till LoadLibrary kan ha misslyckats i målprocessen. Utgångskod: $exit_code. Systemfel: $(Get_System_Error_Message $error_code)"

                    return $false
                }
                
                return $true # Injektion lyckades
            }
            finally {
                # Säkerställer att fjärrtrådens handtag stängs
                [void][WinAPI]::CloseHandle($remote_thread_handle)
            }
        }
        finally {
            # Säkerställer att det fjärrallokerade minnet frigörs
            # 0 för dwSize i MEM_RELEASE frigör hela regionen som allokerats av VirtualAllocEx
            [void][WinAPI]::VirtualFreeEx($process_handle, $remote_memory, 0, $global:CONSTANTS.MEMORY_FREE_TYPE)
        }
    }
}
```

> [!NOTE]
> Klassen `Process` använder `[System.IntPtr]` för att representera Windows-handtag. Det är viktigt att notera den omfattande användningen av `try/finally` för att säkerställa att handtagen (`ProcessHandle`, `ThreadHandle`, `remote_memory`, `remote_thread_handle`) stängs och minnet frigörs korrekt, även vid fel. Detta är PowerShell-sättet att implementera **RAII**-principen (Resource Acquisition Is Initialization), även om det är mindre integrerat i språkets syntax.

### `InjectorCore.ps1`

Detta är orkestreringsklassen som förenar alla funktioner från de tidigare modulerna. Den koordinerar validering, konstruktion av kommandoradsargument, skapande av process och anrop för DLL-injektion.

```powershell
class Injector_Core {
    # Huvudfunktion som orkestrerar spelets initialisering och injektion
    [bool] Initialize_Game([Inject_Type]$inject_type, [string]$folder, [string]$nickname, [string]$ip, [string]$port, [string]$password) {
        # Bygger de fullständiga sökvägarna till de nödvändiga filerna
        $game_path = Join-Path -Path $folder -ChildPath $global:CONSTANTS.GAME_EXE_NAME
        $samp_dll_path = Join-Path -Path $folder -ChildPath $global:CONSTANTS.SAMP_DLL_NAME
        $omp_dll_path = Join-Path -Path $folder -ChildPath $global:CONSTANTS.OMP_DLL_NAME
        
        $validation_error = [string]::Empty # Variabel för att fånga valideringsfelmeddelanden
        
        # 1. Filvalidering
        if (-not (Validate_Files $game_path $samp_dll_path $omp_dll_path $inject_type)) {
            # Fel har redan visats av valideringsfunktionen
            return $false
        }

        # 2. Portvalidering
        if (-not (Validate_Port $port ([ref]$validation_error))) {
            Show_Error $validation_error $inject_type
            return $false
        }
        
        # 3. Smeknamnsvalidering
        if (-not (Validate_Nickname $nickname ([ref]$validation_error))) {
            Show_Error $validation_error $inject_type
            return $false
        }
        
        # 4. Konvertering av strängar till ANSI/8-bitars kodning (krävs för äldre API:er)
        $converted_nickname = Convert_Wide_To_Local_8Bit $nickname
        $converted_ip = Convert_Wide_To_Local_8Bit $ip
        $converted_port = Convert_Wide_To_Local_8Bit $port
        $converted_password = Convert_Wide_To_Local_8Bit $password
        $converted_game_path = Convert_Wide_To_Local_8Bit $game_path
        $converted_folder = Convert_Wide_To_Local_8Bit $folder
        $converted_samp_dll_path = Convert_Wide_To_Local_8Bit $samp_dll_path
        $converted_omp_dll_path = Convert_Wide_To_Local_8Bit $omp_dll_path
        
        # 5. Konstruktion av kommandoradsargument
        $command_arguments = $this.Build_Command_Args($converted_nickname, $converted_ip, $converted_port, $converted_password)
        
        $process_manager = New-Object Process # Instansierar Process-klassen
        $process_info = $null # Variabel för att lagra information om den skapade processen
        
        # Använder ett try/finally-block för att säkerställa att processhandtagen stängs
        try {
            # 6. Skapande av Spelprocess (Suspenderad)
            $process_info = $process_manager.Create_Game_Process($converted_game_path, $command_arguments, $converted_folder)
            
            if ($null -eq $process_info) {
                # Fel har redan visats av processkapningsfunktionen
                return $false
            }

            $injection_error = [string]::Empty # Variabel för att fånga injektionsfelmeddelanden
            
            # 7. Injektion av samp.dll
            if (-not $process_manager.Inject_DLL($process_info.ProcessHandle, $converted_samp_dll_path, ([ref]$injection_error))) {
                Show_Error "Misslyckades med att injicera samp.dll: $injection_error" $inject_type
                return $false
            }
            
            # 8. Villkorlig injektion av omp-client.dll (endast om injektionstypen är OMP)
            if ($inject_type -eq [Inject_Type]::OMP) {
                if (-not $process_manager.Inject_DLL($process_info.ProcessHandle, $converted_omp_dll_path, ([ref]$injection_error))) {
                    Show_Error "Misslyckades med att injicera omp-client.dll: $injection_error" $inject_type
                    return $false
                }
            }
            
            # 9. Återuppta Spelprocessen
            # Processen skapades i ett suspenderat tillstånd för att tillåta injektion.
            # Nu när DLL-filerna har injicerats kan den återupptas.
            $resume_result = [WinAPI]::ResumeThread($process_info.ThreadHandle)

            if ($resume_result -eq $global:CONSTANTS.THREAD_RESUME_ERROR) {
                $error_code = [System.Runtime.InteropServices.Marshal]::GetLastWin32Error()
                $error_message = Get_System_Error_Message $error_code
                Show_Error "Misslyckades med att återuppta spelprocessens tråd: $error_message" $inject_type

                return $false
            }
            
            return $true # Framgång i alla steg!
        }
        finally {
            # Säkerställer att processhandtagen stängs i slutet,
            # oavsett om det lyckades eller misslyckades.
            if ($null -ne $process_info) {
                $process_manager.Close_Process_Info($process_info)
            }
        }
    }
    
    # Bygger kommandoradsargumentsträngen för spelets exekverbara fil
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
> För **OMP** involverar injektionen `omp-client.dll` *utöver* `samp.dll`. Detta är i linje med hur **OMP** vanligtvis fungerar, eftersom det kan använda `samp.dll` som bas och utöka funktionaliteten med `omp-client.dll`. Det är avgörande att **båda DLL-filerna** finns och fungerar i spelets katalog för att OMP-injektionen ska lyckas. Om en misslyckas kan spelet inte starta korrekt eller så kanske multiplayer-klienten inte laddas.
>
> Observera att eftersom PowerShell inte har en `std::optional` eller en native **RAII**-garanti på samma sätt som C++, använder koden ett explicit `try/finally`-block i `Initialize_Game`-funktionen för att säkerställa att `Close_Process_Info` anropas och handtagen frigörs, även om ett fel uppstår. Detta är en god praxis för resursstädning i PowerShell.

### `Injector.ps1`

Detta är bibliotekets huvudsakliga ingångsskript. Det hanterar laddningen av de andra modulerna, valideringen av PowerShell-miljön (kontrollerar om den är x86 för injektionskompatibilitet) och initialiseringen av `Injector_Core`-klassen. Det är skriptet som slutanvändaren kommer att köra.

```powershell
param([Parameter(Mandatory = $true, Position = 0)][ValidateNotNullOrEmpty()][string]$inject_type,
    [Parameter(Mandatory = $true, Position = 1)][ValidateNotNullOrEmpty()][string]$folder,
    [Parameter(Mandatory = $true, Position = 2)][ValidateNotNullOrEmpty()][string]$nickname,
    [Parameter(Mandatory = $true, Position = 3)][ValidateNotNullOrEmpty()][string]$ip,
    [Parameter(Mandatory = $true, Position = 4)][ValidateNotNullOrEmpty()][string]$port,
    [Parameter(Position = 5)][AllowEmptyString()][string]$password = "",
    [switch]$restarted_x86) # Intern flagga för att indikera att skriptet redan har startats om i x86

$ErrorActionPreference = 'Stop' # Säkerställer att icke-avslutande fel beter sig som avslutande fel
# Detta gör att catch-block fångar fler fel och förhindrar att skriptet fortsätter oväntat.

# Hämtar den fullständiga sökvägen till det aktuella skriptet, nödvändigt för att ladda hjälpmodulerna
$script_path = $MyInvocation.MyCommand.Path

if ([string]::IsNullOrEmpty($script_path)) {
    # I fall där skriptet anropas på ett speciellt sätt (t.ex. från en pipeline), kan $MyInvocation.MyCommand.Path vara tomt
    $script_path = Join-Path -Path (Get-Location) -ChildPath $MyInvocation.MyCommand.Name
}

$script_directory = Split-Path -Parent $script_path # Bibliotekets baskatalog
$exit_code = 1 # Standard utgångskod (fel)

try {
    # Laddar alla biblioteksmoduler (konstanter, anpassade typer, verktyg, etc.)
    . (Join-Path -Path $script_directory -ChildPath "Constants.ps1")
    . (Join-Path -Path $script_directory -ChildPath "CustomTypes.ps1")
    . (Join-Path -Path $script_directory -ChildPath "StringUtils.ps1")
    . (Join-Path -Path $script_directory -ChildPath "ErrorUtils.ps1")
    . (Join-Path -Path $script_directory -ChildPath "Validation.ps1")
    . (Join-Path -Path $script_directory -ChildPath "Process.ps1")
    . (Join-Path -Path $script_directory -ChildPath "InjectorCore.ps1")

    # Definierar huvudgränssnittsfunktionen för användaren.
    # Det är en wrapper för Injector_Core-klassen.
    function Initialize_Game {
        param([string]$inject_type, [string]$folder, [string]$nickname, [string]$ip, [string]$port, [string]$password = "")

        # Kontrollerar om PowerShell-miljön är x64 och om den ännu inte har startats om i x86
        if ([IntPtr]::Size -eq 8 -and -not $restarted_x86) {
            Write-Host "Upptäckte PowerShell x64-miljö. Startar om på PowerShell x86 för DLL-injektionskompatibilitet (32-bitars)..." -ForegroundColor Yellow

            # Lokaliserar den 32-bitars PowerShell-exekverbara filen
            $powershell_x86_path = Join-Path -Path $env:windir -ChildPath "SysWOW64\WindowsPowerShell\v1.0\powershell.exe"

            if (-not (Test-Path -Path $powershell_x86_path)) {
                Write-Host "Kunde inte hitta powershell.exe (x86) på '$powershell_x86_path'. 32-bitars DLL-injektion kan misslyckas." -ForegroundColor Red
                return $false
            }

            # Förbereder argumentlistan för den nya x86 PowerShell-processen
            $argument_list = @("-NoProfile", "-NonInteractive", "-ExecutionPolicy", "Bypass", "-File", $script_path, $inject_type, $folder, $nickname, $ip, $port)
            
            if (-not [string]::IsNullOrEmpty($password)) {
                $argument_list += $password
            }
            # Lägger till flaggan för att indikera att den redan har startats om
            $argument_list += "-restarted_x86"
            
            try {
                $process_start_info = New-Object System.Diagnostics.ProcessStartInfo
                $process_start_info.FileName = $powershell_x86_path
                # Förenar argumenten till en sträng för StartInfo.Arguments
                $process_start_info.Arguments = ($argument_list | ForEach-Object { "`"$_`"" }) -join " " # Omsluter argument med citattecken för att hantera mellanslag
                $process_start_info.RedirectStandardOutput = $true # Omdirigerar utdata från barnprocessen
                $process_start_info.RedirectStandardError = $true   # Omdirigerar fel från barnprocessen
                $process_start_info.UseShellExecute = $false     # Använder inte ShellExecute (kör PowerShell.exe direkt)
                $process_start_info.CreateNoWindow = $true       # Skapar inget nytt fönster för barnprocessen

                $child_process = New-Object System.Diagnostics.Process
                $child_process.StartInfo = $process_start_info
                
                # Startar barnprocessen och väntar på att den ska slutföras
                [void]$child_process.Start()
                $child_process.WaitForExit()
                
                # Fångar och visar utdata/fel från barnprocessen
                $standard_output = $child_process.StandardOutput.ReadToEnd()
                $standard_error = $child_process.StandardError.ReadToEnd()

                if (-not [string]::IsNullOrEmpty($standard_output)) { Write-Host $standard_output }
                if (-not [string]::IsNullOrEmpty($standard_error)) { Write-Host $standard_error -ForegroundColor Red }

                $child_exit_code = $child_process.ExitCode
                
                if ($child_exit_code -eq 0) {
                    Write-Host "PowerShell x86-process slutförd med kod 0 (Lyckades)." -ForegroundColor Green
                    return $true
                }
                else {
                    Write-Host "PowerShell x86-process slutförd med felkod: '$child_exit_code'." -ForegroundColor Red
                    return $false
                }
            }
            catch {
                Write-Host "Misslyckades med att starta PowerShell x86: '$($_.Exception.Message)'" -ForegroundColor Red
                return $false
            }
        }
        
        # Den faktiska initialiseringslogiken, nås endast om miljön är x86 eller redan har startats om
        $injection_type = $null

        switch ($inject_type.ToLower()) {
            $global:CONSTANTS.INJECT_TYPE_SAMP {
                $injection_type = [Inject_Type]::SAMP
            }
            $global:CONSTANTS.INJECT_TYPE_OMP {
                $injection_type = [Inject_Type]::OMP
            }
            default {
                Show_Error "Ogiltigt injektionsläge angett. Använd 'samp' eller 'omp'." ([Inject_Type]::SAMP)
                return $false
            }
        }

        $injector_core = New-Object Injector_Core # Instansierar huvudklassen för injektion

        # Delegerar anropet till Initialize_Game-funktionen i Injector_Core-klassen
        return $injector_core.Initialize_Game($injection_type, $folder, $nickname, $ip, $port, $password)
    }

    # Parametrar som skickas till huvudfunktionen
    $initialization_parameters = @{
        inject_type = $inject_type
        folder = $folder
        nickname = $nickname
        ip = $ip
        port = $port
        password = $password
    }

    # Anrop för att starta injektionsprocessen
    $game_initialization_result = Initialize_Game @initialization_parameters

    if ($game_initialization_result) {
        $exit_code = 0 # Lyckades
    }
    else {
        $exit_code = 1 # Misslyckades
    }
}
catch {
    Write-Host "Kritiskt fel under körning: '$($_.Exception.Message)'" -ForegroundColor Red
    $exit_code = 1
}
finally {
    # Säkerställer att städningsskriptet körs i slutet, oavsett om det lyckades eller misslyckades
    try {
        . (Join-Path -Path $script_directory -ChildPath "Cleanup.ps1")
    }
    catch {
        Write-Host "Varning: Körning av städningsskript misslyckades: '$($_.Exception.Message)'" -ForegroundColor Yellow
    }
    
    exit $exit_code # Avslutar med lämplig statuskod
}
```

> [!NOTE]
> Detta skript är den huvudsakliga ingångspunkten för injektionen. Det är ansvarigt för:
> - Definiera **kommandoradsparametrarna** som slutanvändaren kommer att använda.
> - Sätta `$ErrorActionPreference = 'Stop'` för en striktare felhantering.
> - **Ladda** alla hjälpskript med "dot-sourcing" (`. `), vilket säkerställer att deras funktioner och klasser är tillgängliga i den aktuella sessionen.
> - Implementera logiken för **omstart till x86-miljö**: Om PowerShell körs i 64-bitars, startar det om sig själv automatiskt i en 32-bitars instans (SysWOW64) och skickar samma argument, eftersom injektion av 32-bitars DLL-filer är mer tillförlitlig (och i många fall obligatorisk) från en 32-bitars process. Detta är en viktig skillnad för PowerShell jämfört med en C++-applikation som kompileras direkt för x86.
> - Anropa `Initialize_Game`-funktionen för att starta injektionsprocessen.
> - Hantera skriptets utgångskod (0 för framgång, 1 för misslyckande).
> - Anropa `Cleanup.ps1`-skriptet i `finally`-blocket.

### `Cleanup.ps1`

Detta skript ansvarar för att ta bort de funktioner och globala variabler som laddats av biblioteket från den aktuella PowerShell-sessionen. Detta är en god praxis för att undvika att förorena miljön och säkerställa att efterföljande körningar av skriptet med olika konfigurationer inte stöter på oväntade tillstånd från tidigare sessioner.

```powershell
$functions_to_remove = @(
    '*Initialize_Game*', # Använder jokertecken för att ta bort funktioner (kan ha alias)
    '*Get_System_Error_Message*',
    '*Show_Error*',
    '*Convert_Wide_To_Local_8Bit*',
    '*Validate_*', # Tar bort alla funktioner som börjar med 'Validate_'
    '*Build_Command_Args*'
)

# Itererar över mönstren och tar bort funktionerna
foreach ($pattern in $functions_to_remove) {
    Get-Command -CommandType Function -Name $pattern -ErrorAction SilentlyContinue | ForEach-Object {
        try {
            Remove-Item -Path "Function:$($_.Name)" -Force -ErrorAction SilentlyContinue
        }
        catch {} # Ignorerar fel om funktionen inte kan tas bort av någon anledning
    }
}

$global_variables_to_remove = @(
    'CONSTANTS',
    'CAN_SHOW_MESSAGE_BOX' # Lägg till här om fler globala variabler introduceras
)

# Itererar över de globala variablerna och tar bort dem
foreach ($variable_name in $global_variables_to_remove) {
    try {
        Remove-Variable -Name $variable_name -Scope Global -Force -ErrorAction SilentlyContinue
    }
    catch {} # Ignorerar fel
}

$variable_patterns_to_remove = @(
    '*_Core*', # Tar bort variabler som slutar med '_Core' (t.ex. $injector_core)
    '*Process*' # Tar bort variabler som slutar med 'Process' (t.ex. $process_manager)
)

# Tar bort variabler i olika scope med hjälp av mönster
foreach ($scope in @('Script', 'Local')) {
    foreach ($pattern in $variable_patterns_to_remove) {
        Get-Variable -Scope $scope -Name $pattern -ErrorAction SilentlyContinue | ForEach-Object {
            try {
                Remove-Variable -Name $_.Name -Scope $scope -Force -ErrorAction SilentlyContinue
            }
            catch {} # Ignorerar fel
        }
    }
}
```

> [!TIP]
> Städning är avgörande i PowerShell-skript som importerar många element till sessionen. `Remove-Item -Path "Function:..."` och `Remove-Variable` används för att frigöra dessa element. Användningen av `ErrorAction SilentlyContinue` och tomma `try/catch`-block i borttagningslooparna säkerställer att städningsskriptet inte misslyckas om något objekt redan har tagits bort eller inte existerar.

## Omfattande Användningsexempel

För att integrera **SA-MP Injector PowerShell** i ditt projekt eller använda det direkt, följ instruktionerna och analysera scenarierna nedan.

### 1. Förberedelse av Utvecklingsmiljön

- **PowerShell Version**: **PowerShell 5.1** eller senare rekommenderas (kompatibel med `Add-Type` för klasser).
- **Körningstillstånd**: PowerShell har exekveringspolicyer. Du måste tillåta körning av lokala skript. Öppna PowerShell som **Administratör** och kör:
   ```powershell
   Set-ExecutionPolicy -ExecutionPolicy RemoteSigned -Scope CurrentUser
   ```
   Detta tillåter signerade skript att köras, och skript som du har skapat (inte nedladdade från internet) att köras lokalt utan signatur.
- **Kopiera Filer**: Placera alla `.ps1`-filer från biblioteket (`Injector.ps1`, `Constants.ps1`, `CustomTypes.ps1`, `StringUtils.ps1`, `ErrorUtils.ps1`, `Validation.ps1`, `Process.ps1`, `InjectorCore.ps1`, `Cleanup.ps1`) i en enda katalog.
- **Processbehörigheter**: Ditt skript behöver **Administratörs**-privilegier för att skapa processer och injicera DLL-filer i en annan process. Kör alltid **PowerShell som Administratör** när du använder detta bibliotek.

### 2. Grundläggande Scenario: Anslutning till en SA-MP Server

Detta är det vanligaste användningsfallet, där GTA:SA startas och ansluts till en SA-MP-server med ett specifikt smeknamn och IP/port.

```powershell
# Skapa ett nytt skript, till exempel "StartSAMP.ps1"

# Importerar huvudfunktionen från SA-MP Injector PowerShell-biblioteket
# Se till att sökvägen nedan speglar var Injector.ps1 finns.
# Till exempel, om Injector.ps1 finns i samma mapp som detta skript:
$injector_path = Join-Path -Path $PSScriptRoot -ChildPath "Injector.ps1"

# Eller, om den finns i en underkatalog:
# $injector_path = Join-Path -Path $PSScriptRoot -ChildPath "SA-MP-Injector-PowerShell\Injector.ps1"

# Importerar Injector.ps1-funktionen med dot-sourcing så att dess funktioner
# blir tillgängliga i det aktuella scopet.
. $injector_path

# Definiera konfigurationsvariablerna
# Ändra dessa sökvägar och serverdetaljer för att matcha din lokala konfiguration.
$game_folder = "C:\Games\GTA San Andreas" # Där gta_sa.exe, samp.dll finns
$player_nickname = "Namn"
$server_ip = "127.0.0.1" # Exempel: din lokala server
$server_port = "7777"
$server_password = "" # Lämna tomt om det inte finns något lösenord

Write-Host "Startar SA-MP..." -ForegroundColor Cyan
Write-Host "Spelmapp: $game_folder" -ForegroundColor Gray
Write-Host "Smeknamn: $player_nickname" -ForegroundColor Gray
Write-Host "Server: $server_ip:$server_port" -ForegroundColor Gray

# Anrop till biblioteksfunktionen för att starta spelet
$result = Initialize_Game `
    -inject_type "samp" ` # Injektionstyp: "samp" eller "omp"
    -folder $game_folder ` # Sökväg till spelmappen
    -nickname $player_nickname ` # Önskat smeknamn
    -ip $server_ip ` # Serverns IP
    -port $server_port ` # Serverns port (sträng)
    -password $server_password # Serverns lösenord (sträng, kan vara tomt)

if ($result) {
    Write-Host "`n--- SA-MP startades framgångsrikt! ---" -ForegroundColor Green
    Write-Host "Spelet har startats i en separat process." -ForegroundColor Green
}
else {
    Write-Host "`n--- MISSLYCKADES med att starta SA-MP! ---" -ForegroundColor Red
    Write-Host "Kontrollera felmeddelandena som visas (pop-ups eller konsol)." -ForegroundColor Red
}

# Håller konsolen öppen för att se utdatameddelanden
Read-Host "`nTryck på Enter för att stänga programmet."
```

**För att köra skriptet:**
1.  **Spara** koden ovan som `StartSAMP.ps1` (eller något annat namn, så länge det slutar på `.ps1`).
2.  **Spara** alla biblioteksfiler från **SA-MP Injector PowerShell** i samma mapp eller i en undermappsstruktur som du hanterar med `$injector_path`.
3.  **Öppna PowerShell som Administratör**.
4.  Navigera till katalogen där du sparade `StartSAMP.ps1`.
5.  Kör skriptet:
    ```powershell
    .\StartSAMP.ps1
    ```
    (Kom ihåg att `.` före skriptnamnet är nödvändigt för skript i den aktuella katalogen, om du inte lägger till den i PATH).

### 3. Avancerat Scenario: Anslutning till en OMP Server

För OMP är logiken identisk med den för SA-MP, men du anger `"omp"` som `inject_type` och ser till att `omp-client.dll` finns i spelets katalog.

```powershell
# Skapa ett nytt skript, till exempel "StartOMP.ps1"

# Importerar huvudfunktionen från SA-MP Injector PowerShell-biblioteket
$injector_path = Join-Path -Path $PSScriptRoot -ChildPath "Injector.ps1"
. $injector_path

# Definiera konfigurationsvariablerna för OMP
$game_folder = "C:\Games\GTA San Andreas" # Där gta_sa.exe, samp.dll och omp-client.dll finns
$player_nickname = "Namn"
$server_ip = "127.0.0.1" # Exempel: din lokala server
$server_port = "7777"
$server_password = "" # Lämna tomt om det inte finns något lösenord

Write-Host "Startar OMP..." -ForegroundColor Cyan
Write-Host "Spelmapp: $game_folder" -ForegroundColor Gray
Write-Host "Smeknamn: $player_nickname" -ForegroundColor Gray
Write-Host "Server: $server_ip:$server_port" -ForegroundColor Gray

# Anrop till biblioteksfunktionen för att starta spelet
$result = Initialize_Game `
    -inject_type "omp" `   # Injektionstyp: "omp"
    -folder $game_folder `
    -nickname $player_nickname `
    -ip $server_ip `
    -port $server_port `
    -password $server_password

if ($result) {
    Write-Host "`n--- OMP startades framgångsrikt! ---" -ForegroundColor Green
    Write-Host "Spelet har startats i en separat process." -ForegroundColor Green
}
else {
    Write-Host "`n--- MISSLYCKADES med att starta OMP! ---" -ForegroundColor Red
    Write-Host "Kontrollera felmeddelandena som visas (pop-ups eller konsol)." -ForegroundColor Red
}

Read-Host "`nTryck på Enter för att stänga programmet."
```

**För att köra skriptet:**

Följ samma steg som i föregående avsnitt, och ersätt `StartSAMP.ps1` med `StartOMP.ps1`.

### 4. Exekvering från ett Föräldraskript

Det är möjligt att skapa ett mer komplext skript som anropar biblioteket och hanterar parametrar eller villkor på ett mer avancerat sätt. Det centrala konceptet förblir detsamma: `Injector.ps1` måste "dot-sourcas" i föräldraskriptet.

```powershell
# Launcher.ps1
param(
    [string]$type = "samp",
    [string]$game_dir = "C:\Games\GTA San Andreas",
    [string]$player_nickname = "Namn",
    [string]$server_ip = "127.0.0.1",
    [string]$server_port = "7777",
    [string]$server_password = ""
)

# Laddar Injector.ps1
$injector_script = Join-Path -Path $PSScriptRoot -ChildPath "Injector.ps1"

# Kontrollerar om huvudskriptet för injektorn finns innan det laddas
if (-not (Test-Path $injector_script -PathType Leaf)) {
    Write-Error "Injector.ps1 hittades inte på $injector_script. Vänligen kontrollera sökvägen."
    
    exit 1
}

. $injector_script # Använder dot-sourcing för att ladda funktionerna

Write-Host "Försöker starta spelet med de angivna parametrarna..." -ForegroundColor Yellow

$success = Initialize_Game -inject_type $type `
    -folder $game_dir `
    -nickname $player_nickname `
    -ip $server_ip `
    -port $server_port `
    -password $server_password

if ($success) {
    Write-Host "`nStartprogramrapport: Spelet startades framgångsrikt!" -ForegroundColor Green
}
else {
    Write-Host "`nStartprogramrapport: Misslyckades med att starta spelet!" -ForegroundColor Red
}

Read-Host "`nTryck på Enter för att avsluta."
```

**Körning av `Launcher.ps1`:**

```powershell
# Kör med standardvärden
.\Launcher.ps1

# Kör för OMP med specifik IP och port
.\Launcher.ps1 -type "omp" -server_ip "omp.server.com" -server_port "7777" -player_nickname "Namn" -server_password "secure123"
```

## Hantering av Vanliga Fel och Meddelanden

**SA-MP Injector PowerShell** prioriterar användbarhet, och en grundläggande del av detta är att ge tydlig feedback till användaren vid fel. Felmeddelandena presenteras via **Windows dialogrutor** (`MessageBoxW`) eller direkt i PowerShell-konsolen, och kategoriseras efter **injektionstyp (SA-MP eller OMP)** för ökad kontext. Detta säkerställer att du vet exakt vad som gick fel och hur du kan åtgärda det.

Här är några av de vanliga felen du kan stöta på och deras troliga orsaker/lösningar, tillsammans med visuella exempel på hur dessa dialogrutor ser ut för slutanvändaren:

### 1. Ogiltig Injektionstyp

Om den angivna `inject_type` inte är `"samp"` eller `"omp"`, kommer biblioteket inte att veta vilken multiplayer-klient du tänker starta.

![Error 1](screenshots/error_1.png)

- **Visat Felmeddelande**: `"Invalid injection mode specified. Please use 'samp' or 'omp'."`
- **Orsak**: Argumentet `inject_type` matchar inte de förväntade värdena `"samp"` eller `"omp"`. Det kan vara ett stavfel, en tom sträng eller ett okänt värde.
- **Lösning**: Kontrollera att `$inject_type` är korrekt inställt på `"samp"` eller `"omp"`. Det är viktigt att strängen matchar exakt (även om koden använder `ToLower()` för jämförelsen).
   ```powershell
   # Korrekt:
   Initialize_Game -inject_type "samp" ...
   Initialize_Game -inject_type "omp" ...

   # Felaktigt (kommer att orsaka fel):
   # Initialize_Game -inject_type "invalid" ...
   # Initialize_Game -inject_type "" ...
   ```

### 2. Ogiltig Serverport (Format eller Intervall)

Porten är en väsentlig numerisk parameter för anslutning till servern. Detta fel uppstår om värdet inte kan tolkas som ett giltigt tal eller ligger utanför det acceptabla intervallet (**1 till 65535**).

#### 2.1. Icke-numeriskt Portformat

![Error 2](screenshots/error_2.png)

- **Visat Felmeddelande**: `"Invalid port format. The port must be a numeric value. Please provide a valid integer for the port."`
- **Orsak**: Argumentet `port` innehåller tecken som inte är siffror eller kan inte konverteras till ett giltigt heltal (t.ex. `"abc"`, `"7777a"`).
- **Lösning**: Ange en sträng som endast innehåller siffror och representerar ett giltigt heltal.
   ```powershell
   # Korrekt:
   Initialize_Game ... -port "7777" ...
   
   # Felaktigt (ogiltigt format):
   # Initialize_Game ... -port "port7777" ...
   # Initialize_Game ... -port "invalid" ...
   ```

#### 2.2. Port Utanför Giltigt Intervall

![Error 3](screenshots/error_3.png)

- **Visat Felmeddelande**: `"The specified port number (XXXX) is outside the valid range of 1 to 65535. Please provide a valid port."` (**XXXX** kommer att vara det värde du försökte använda).
- **Orsak**: Den angivna porten är ett giltigt tal, men är lägre än `1` (reserverad eller oanvändbar) eller högre än `65535` (maxgräns för **TCP/UDP-portar**).
- **Lösning**: Ange en port som ligger inom intervallet `1` till `65535`. Vanliga portar för **SA-MP**/**OMP** är `7777`.
   ```powershell
   # Korrekt:
   Initialize_Game ... -port "7777" ...

   # Felaktigt (utanför intervallet):
   # Initialize_Game ... -port "0" ...      # För låg
   # Initialize_Game ... -port "65536" ...  # För hög
   # Initialize_Game ... -port "-1" ...     # Negativt värde
   ```

### 3. Ogiltigt Smeknamn (Tomt eller För Långt)

Spelarens **smeknamn** valideras för att säkerställa att spelklienten accepterar det.

#### 3.1. Tomt Smeknamn

![Error 4](screenshots/error_4.png)

- **Visat Felmeddelande**: `"Nickname cannot be empty. Please provide a valid nickname."`
- **Orsak**: Argumentet `nickname` angavs som en tom sträng.
- **Lösning**: Se till att smeknamnet inte är tomt.
   ```powershell
   # Korrekt:
   Initialize_Game ... -nickname "MittNamn" ...

   # Felaktigt (tomt):
   # Initialize_Game ... -nickname "" ...
   ```

#### 3.2. För Långt Smeknamn

![Error 5](screenshots/error_5.png)

- **Visat Felmeddelande**: `"Nickname length exceeds the maximum allowed of 20 characters. Please use a shorter nickname."`
- **Orsak**: Längden på det angivna **smeknamnet** överstiger `$global:CONSTANTS.MAX_NICKNAME_LENGTH`, vilket är `20` tecken.
- **Lösning**: Använd ett **smeknamn** som har högst `20` tecken.
   ```powershell
   # Korrekt:
   Initialize_Game ... -nickname "Kort" ...

   # Felaktigt (för långt):
   # Initialize_Game ... -nickname "DettaSpelarNamnÄrFörLångtFörAttAnvändasHär" ...
   ```

### 4. Spelfiler eller DLL Hittades Inte

Detta är en av de vanligaste orsakerna till fel. Biblioteket kräver att `gta_sa.exe`, `samp.dll` och, för **OMP**, `omp-client.dll` finns på de förväntade platserna.

#### 4.1. Spel-exekverbar (`gta_sa.exe`) Hittades Inte

![Error 6](screenshots/error_6.png)

- **Visat Felmeddelande**: `"Game executable not found. Please ensure 'gta_sa.exe' exists at the specified path: [fullständig sökväg]"`. `[fullständig sökväg]` kommer att inkludera mappen och filnamnet.
- **Orsak**: Filen `gta_sa.exe` hittades inte i mappen som angavs i `folder`-argumentet.
- **Lösning**:
   1. Kontrollera att `$folder` pekar på rätt installationskatalog för **GTA San Andreas**.
   2. Bekräfta att `gta_sa.exe` finns i den mappen och att dess namn inte har ändrats.

#### 4.2. SA-MP Bibliotek (`samp.dll`) Hittades Inte

![Error 7](screenshots/error_7.png)

- **Visat Felmeddelande**: `"SA-MP library not found. Please ensure 'samp.dll' exists at the specified path: [fullständig sökväg]"`.
- **Orsak**: Filen `samp.dll` hittades inte i mappen som angavs i `folder`-argumentet. **Denna DLL** är ett krav för **båda** injektionstyperna (`samp` och `omp`).
- **Lösning**: Se till att `samp.dll` finns i installationsmappen för **GTA San Andreas**.

#### 4.3. OMP Bibliotek (`omp-client.dll`) Hittades Inte (endast för OMP-injektion)

![Error 8](screenshots/error_8.png)

- **Visat Felmeddelande**: `"OMP library not found. Please ensure 'omp-client.dll' exists at the specified path for OMP injection: [fullständig sökväg]"`.
- **Orsak**: Om du angav `"omp"` som injektionstyp, men filen `omp-client.dll` inte hittades i den angivna mappen.
- **Lösning**: Ladda ner den senaste **OMP**-klienten och se till att `omp-client.dll` (och `samp.dll`) finns i installationsmappen för **GTA San Andreas**.

### 5. Misslyckades med att Skapa Spelprocessen

Detta är ett mer komplext fel, eftersom det involverar **operativsystembehörigheter** och det aktuella tillståndet för `gta_sa.exe`.

![Error 9](screenshots/error_9.png)

- **Visat Felmeddelande**: `"Failed to create game process. Ensure 'gta_sa.exe' is not running and you have sufficient permissions to execute the file. System Error: [Operativsystemets felmeddelande]"`. Systemmeddelandet kommer att läggas till av `Get_System_Error_Message` (t.ex. `Access is denied.` eller `The requested operation requires elevation.`).
- **Orsak**: Anropet `CreateProcessA` för att starta `gta_sa.exe` misslyckades. Vanliga orsaker inkluderar:
   - **Processen körs redan**: En instans av `gta_sa.exe` är redan aktiv och blockerar en ny körning.
   - **Otillräckliga behörigheter**: Ditt skript har inte nödvändiga privilegier (t.ex. administratör) för att skapa en process i vissa systemkonfigurationer (**UAC** aktiverat, skyddade mappar, etc.).
   - **Problem med den exekverbara filen**: `gta_sa.exe` kan vara skadad eller blockerad av ett annat program (t.ex. ett felkonfigurerat antivirusprogram).
- **Lösning**:
   1. Kontrollera Aktivitetshanteraren och se till att ingen instans av `gta_sa.exe` körs. Avsluta alla om det finns.
   2. Kör **PowerShell-skriptet som Administratör**. Högerklicka på PowerShell-ikonen och välj **"Kör som administratör"**, eller starta det från en genväg som är konfigurerad för detta.
   3. Om ett **antivirus** eller **säkerhetsprogram** stör, lägg till ditt skript och/eller **GTA:SA**-mappen i antivirusets undantag (gör detta med försiktighet och endast om du är säker på filernas integritet).

### 6. Misslyckades med Minnesallokering i Målprocessen

Biblioteket försöker allokera ett litet minnesutrymme i `gta_sa.exe` för att kopiera **DLL-sökvägen**.

![Error 10](screenshots/error_10.png)

- **Visat Felmeddelande**: `"Failed to allocate memory in the target process. This might be due to insufficient permissions or process protection mechanisms. System Error: [Operativsystemets felmeddelande]"`.
- **Orsak**: Funktionen `VirtualAllocEx` (som används för att allokera minne i en annan process) misslyckades. Detta är mest troligt om:
   - **GTA:SA**-processen (även i suspenderat tillstånd) har säkerhetsförsvar eller **anti-injektionspatchar** som förhindrar minnesallokering av externa processer.
   - Ditt skript saknar de nödvändiga förhöjda behörigheterna för att manipulera en annan process minne.
   - (Mindre vanligt) Det finns en extrem brist på virtuellt minne i systemet.
- **Lösning**:
   1. Kör ditt skript med **Administratörs**-privilegier.
   2. Se till att spelet inte har några modifieringar eller **säkerhetspatchar** som kan blockera försök till injektion eller minnesmanipulation (detta är vanligare i modifierade miljöer eller med vissa tredjeparts anti-cheat-verktyg).

### 7. Misslyckades med att Skriva DLL-sökväg till Processminnet

Efter att ha allokerat minnet försöker biblioteket kopiera **DLL-sökvägen** till det.

![Error 11](screenshots/error_11.png)

- **Visat Felmeddelande**: `"Failed to write DLL path to the target process memory. Verify process permissions and ensure the DLL path is accessible. System Error: [Operativsystemets felmeddelande]"`.
- **Orsak**: Funktionen `WriteProcessMemory` misslyckades med att kopiera **byten av DLL-sökvägen** till det fjärrallokerade minnet i `gta_sa.exe`. Detta pekar vanligtvis på:
   - **Skrivbehörigheter**: Ditt skript har inte tillåtelse att skriva till den minnesregionen eller i **GTA:SA**-processen.
   - **Ogiltigt handtag**: Processhandtaget har på något sätt blivit ogiltigt (mindre vanligt, men möjligt under extrema systemförhållanden).
   - **Problem med minnesskydd**: Något minnesskydd (antingen från **OS** eller spelmodifieringar) förhindrade skrivningen.
- **Lösning**: Kör som **Administratör**. Kontrollera att `gta_sa.exe` och dess miljö är "rena" från verktyg som kan blockera minnesoperationer.

### 8. Misslyckades med att Hitta Viktiga Systemfunktioner

Dessa är avgörande Windows-API:er; fel här indikerar ett grundläggande problem med operativsystemet eller körmiljön.

#### 8.1. `kernel32.dll` Hittades Inte

![Error 12](screenshots/error_12.png)

- **Visat Felmeddelande**: `"Failed to obtain a handle to kernel32.dll. This is an essential system library and this error indicates a severe system issue. System Error: [Operativsystemets felmeddelande]"`.
- **Orsak**: `kernel32.dll` är en av de mest grundläggande DLL-filerna i Windows och innehåller väsentliga funktioner. Om `GetModuleHandleA` inte kan få ett **handtag** till den, har operativsystemet mycket allvarliga problem.
- **Lösning**: Detta är ett **kritiskt** fel som sällan orsakas av biblioteket eller ditt skript. Det antyder korruption av systemfiler, allvarliga problem med **Windows**, eller en mycket ovanlig installation av **OS**. Det rekommenderas att köra systemintegritetskontroller (som `sfc /scannow` i **Kommandotolken** som **Administratör**) eller, i sista hand, ominstallera **Windows**.

#### 8.2. `LoadLibraryA` Hittades Inte

![Error 13](screenshots/error_13.png)

- **Visat Felmeddelande**: `"Failed to find the address of the LoadLibraryA function in kernel32.dll. This is critical for injecting the DLL. System Error: [Operativsystemets felmeddelande]"`.
- **Orsak**: Även om `kernel32.dll` hittades, kunde funktionen `LoadLibraryA` inte lösas via `GetProcAddress`. Även om det är extremt ovanligt, kan det vara resultatet av korruption av **DLL-filen** för `kernel32.dll` eller en mycket icke-standardiserad körmiljö.
- **Lösning**: Precis som felet med `kernel32.dll` ovan, indikerar detta ett allvarligt problem med operativsystemet.

### 9. Misslyckades med att Skapa Fjärrtråd för Injektion

Efter att ha förberett fjärrmiljön och kopierat **DLL-sökvägen**, skapas en ny **tråd** i spelprocessen för att "anropa" `LoadLibraryA`.

![Error 14](screenshots/error_14.png)

- **Visat Felmeddelande**: `"Failed to create a remote thread in the target process to execute the DLL injection. This could be due to security restrictions or process state. System Error: [Operativsystemets felmeddelande]"`.
- **Orsak**: Anropet `CreateRemoteThread` misslyckades. Detta fel är vanligt på system med robusta **anti-injektions**-försvar eller när ett program intensivt övervakar processens beteende:
   - **Säkerhetsmekanismer**: **Anti-cheat**-verktyg, **säkerhetsprogram** eller vissa **Windows**-policyer kan upptäcka och blockera försök att skapa **trådar** i tredjepartsprocesser.
   - **Inkonsekvent Målprocess**: Om **GTA:SA**-processen är i ett oväntat eller instabilt tillstånd (trots att den startats i `CREATE_SUSPENDED`), kan detta påverka förmågan att skapa **trådar** i den.
- **Lösning**:
   1. Kör ditt skript med **Administratörs**-privilegier.
   2. Kontrollera att det inte finns några **anti-cheat**-verktyg, **aggressiva antivirusprogram** eller **brandväggar** konfigurerade för att inspektera och blockera processmanipulation som kan vara i konflikt. Lägg till ditt skript och `gta_sa.exe` i undantagen, om tillämpligt (med försiktighet).
   3. Systemets felmeddelande kan ge ytterligare detaljer för att undersöka den specifika orsaken (t.ex. **"A process has been denied access to create threads for other processes."**).

### 10. Timeout eller Misslyckad Slutförande av Injektion

Efter att ha skapat den fjärrstyrda **tråden** väntar injektorn på att den ska slutföra **DLL-laddningen**.

![Error 15](screenshots/error_15.png)

- **Visat Felmeddelande**: `"Timeout or error waiting for DLL injection to complete (timeout). System Error: [Operativsystemets felmeddelande]"`.
- **Orsak**: Den fjärrstyrda **tråden** som kör `LoadLibraryA` tog längre tid än `$global:CONSTANTS.DLL_INJECTION_TIMEOUT_MS` (10 sekunder) att returnera, eller så misslyckades den och `GetExitCodeThread` returnerade 0. Potentiella orsaker inkluderar:
   - **Problem i den injicerade DLL:en**: `DllMain` för `samp.dll` eller `omp-client.dll` tar för lång tid att köra, innehåller en **oändlig loop**, en **krasch**, eller ett fel som **förhindrar DLL:en** från att laddas korrekt (t.ex. saknade **DLL-beroenden**).
   - **Tyst blockering**: En säkerhetsmekanism kan ha blockerat `LoadLibraryA` men inte meddelat med ett uppenbart fel vid skapandet av **tråden**.
- **Lösning**:
   1. Kontrollera integriteten hos filerna `samp.dll` och `omp-client.dll`. De kan vara korrupta eller av en inkompatibel version med din `gta_sa.exe`.
   2. Säkerställ att **den injicerade DLL:en** inte är beroende av **andra DLL:er** som kan saknas eller vara otillgängliga i systemet.

### 11. Misslyckades med att Återuppta Spelprocessens Tråd

Detta är det sista steget för att starta spelet efter att **DLL:erna** har injicerats.

![Error 16](screenshots/error_16.png)

- **Visat Felmeddelande**: `"Failed to resume the game process thread: [Operativsystemets felmeddelande]"`.
- **Orsak**: Anropet `ResumeThread` misslyckades, vilket innebär att huvud**tråden** i `gta_sa.exe` inte kunde aktiveras för att starta spelets exekvering. Detta är ett sällsynt fel, men kan inträffa om:
   - Processens **trådhandtag** har blivit ogiltigt.
   - Operativsystemet förhindrade återupptagandet av någon anledning, möjligen relaterat till en säkerhetsavbrott eller inkonsekvent processtillstånd.
   - Processen kan ha avslutats externt mellan **DLL-injektionen** och försöket att återuppta huvud**tråden**.
- **Lösning**: Om alla föregående steg lyckades och endast `ResumeThread` misslyckades, kan det vara ett problem med operativsystemet, med själva **GTA:SA**-installationen, eller med annan mycket strikt **säkerhetsprogramvara**. Granska tillståndet för `gta_sa.exe` via **Aktivitetshanteraren** precis före och efter felet. Att försöka starta om datorn kan lösa tillfälliga systemtillståndsproblem.

> [!TIP]
> I komplexa felsökningsscenarier kan verktyg som **Process Monitor (Sysinternals Suite)** eller en felsökare (som **WinDbg**) vara ovärderliga. De kan hjälpa till att observera **API**-anrop, kontrollera åtkomstfel, spåra **handtagens** tillstånd och till och med inspektera processens minne, vilket ger en djupgående inblick i vad som händer under huven.
>
> För att felsöka PowerShell-skript som använder `Add-Type` och interagerar med WinAPI på låg nivå, är verktyg som **PowerShell Integrated Scripting Environment (ISE)** eller **Visual Studio Code** med PowerShell-tillägget användbara, eftersom de tillåter att man sätter brytpunkter och inspekterar variabler. Kom alltid ihåg att köra dem **som Administratör**.

## Licens

Copyright © **SA-MP Programming Community**

Denna programvara är licensierad under villkoren i MIT-licensen ("Licensen"); du får använda denna programvara i enlighet med Licensens villkor. En kopia av Licensen kan erhållas på: [MIT License](https://opensource.org/licenses/MIT)

### Användarvillkor

#### 1. Beviljade rättigheter

Denna licens ger kostnadsfritt följande rättigheter till alla som erhåller en kopia av denna programvara och tillhörande dokumentationsfiler:
* Att använda, kopiera, modifiera, slå samman, publicera, distribuera, underlicensiera och/eller sälja kopior av programvaran utan begränsningar
* Att tillåta personer som programvaran tillhandahålls till att göra detsamma, under förutsättning att de följer nedanstående villkor

#### 2. Obligatoriska villkor

Alla kopior eller väsentliga delar av programvaran måste innehålla:
* Ovanstående upphovsrättsmeddelande
* Detta tillståndsmeddelande
* Nedanstående ansvarsfriskrivning

#### 3. Upphovsrätt

Programvaran och all tillhörande dokumentation skyddas av upphovsrättslagar. **SA-MP Programming Community** behåller den ursprungliga upphovsrätten till programvaran.

#### 4. Garantifriskrivning och ansvarsbegränsning

PROGRAMVARAN TILLHANDAHÅLLS "I BEFINTLIGT SKICK", UTAN NÅGON GARANTI AV NÅGOT SLAG, UTTRYCKLIG ELLER UNDERFÖRSTÅDD, INKLUSIVE MEN INTE BEGRÄNSAT TILL GARANTIER FÖR SÄLJBARHET, LÄMPLIGHET FÖR ETT SÄRSKILT SYFTE OCH ICKE-INTRÅNG.

UNDER INGA OMSTÄNDIGHETER SKA FÖRFATTARNA ELLER UPPHOVSRÄTTSINNEHAVARNA VARA ANSVARIGA FÖR NÅGRA ANSPRÅK, SKADOR ELLER ANNAT ANSVAR, VARE SIG I EN AVTALSHANDLING, SKADESTÅNDSANSPRÅK ELLER PÅ ANNAT SÄTT, SOM UPPSTÅR FRÅN, UT ELLER I SAMBAND MED PROGRAMVARAN ELLER ANVÄNDNINGEN ELLER ANNAT HANDHAVANDE AV PROGRAMVARAN.

---

För detaljerad information om MIT-licensen, besök: https://opensource.org/licenses/MIT