# SA-MP Injector C#

<div align="center">

![C#](https://img.shields.io/badge/C%23-11.0%2B-512BD4?style=for-the-badge&logo=csharp&logoColor=white)
![.NET](https://img.shields.io/badge/.NET-7.0%2B-512BD4?style=for-the-badge&logo=dotnet&logoColor=white)
![Platform](https://img.shields.io/badge/Platform-Windows-blue?style=for-the-badge&logo=windows&logoColor=white)
![Architecture](https://img.shields.io/badge/Architecture-x86%20(32--bit)-lightgrey?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)

**Ett C#-bibliotek för programmatisk injektion av DLL:er i SA-MP- och OMP-processer, vilket möjliggör automatiserad anslutning till servrar.**

</div>

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

- [SA-MP Injector C#](#sa-mp-injector-c)
  - [Språk](#språk)
  - [Innehållsförteckning](#innehållsförteckning)
  - [Introduktion och Syfte](#introduktion-och-syfte)
  - [Designfilosofi](#designfilosofi)
    - [Interoperabilitet (P/Invoke)](#interoperabilitet-pinvoke)
    - [Resurshantering (`SafeHandle`)](#resurshantering-safehandle)
    - [Säkerhet och Robusthet](#säkerhet-och-robusthet)
  - [Systemkrav](#systemkrav)
    - [Utvecklingsmiljö](#utvecklingsmiljö)
    - [Körmiljö](#körmiljö)
  - [Installation och Grundläggande Användning](#installation-och-grundläggande-användning)
    - [Lägga till i Ditt Projekt](#lägga-till-i-ditt-projekt)
    - [Användningsexempel](#användningsexempel)
  - [Bibliotekets Komponenter](#bibliotekets-komponenter)
    - [1. `Constants.cs`](#1-constantscs)
    - [2. `InjectionType.cs`](#2-injectiontypecs)
    - [3. `Injector.cs`](#3-injectorcs)
    - [4. `InjectorCore.cs`](#4-injectorcorecs)
    - [5. `InputValidator.cs`](#5-inputvalidatorcs)
    - [6. `NativeImports.cs`](#6-nativeimportscs)
    - [7. `ProcessHandler.cs`](#7-processhandlercs)
    - [8. `SafeHandles.cs`](#8-safehandlescs)
  - [Detaljerad Cykel för DLL-injektion](#detaljerad-cykel-för-dll-injektion)
    - [1. Validering av Indata](#1-validering-av-indata)
    - [2. Skapande av Spelprocessen (Suspenderad)](#2-skapande-av-spelprocessen-suspenderad)
    - [3. Injektion av `samp.dll`](#3-injektion-av-sampdll)
    - [4. Injektion av `omp-client.dll` (Valfritt, Beroende av SA-MP)](#4-injektion-av-omp-clientdll-valfritt-beroende-av-sa-mp)
    - [Återuppta Spelets Huvudtråd](#återuppta-spelets-huvudtråd)
  - [Felhantering och Felfall](#felhantering-och-felfall)
    - [Valideringsfel för Indata](#valideringsfel-för-indata)
      - [Ogiltigt Smeknamn](#ogiltigt-smeknamn)
      - [Ogiltig Port](#ogiltig-port)
      - [Saknade Spel-/DLL-filer](#saknade-spel-dll-filer)
    - [Fel vid Skapande av Process](#fel-vid-skapande-av-process)
      - [Misslyckades med att Skapa Processen](#misslyckades-med-att-skapa-processen)
    - [Fel vid DLL-injektion](#fel-vid-dll-injektion)
      - [Handtag till `kernel32.dll` Otillgängligt](#handtag-till-kernel32dll-otillgängligt)
      - [Funktionen `LoadLibraryA` Otillgänglig](#funktionen-loadlibrarya-otillgänglig)
      - [Misslyckad Allokering av Fjärrminne](#misslyckad-allokering-av-fjärrminne)
      - [Misslyckades med att Skriva till Processens Minne](#misslyckades-med-att-skriva-till-processens-minne)
      - [Misslyckades med att Skapa Fjärrtråd](#misslyckades-med-att-skapa-fjärrtråd)
      - [Timeout eller Fel vid Väntan på Injektion](#timeout-eller-fel-vid-väntan-på-injektion)
      - [DLL-injektion Misslyckades eller Returnerade Fel](#dll-injektion-misslyckades-eller-returnerade-fel)
    - [Fel vid Återupptagande av Speltråden](#fel-vid-återupptagande-av-speltråden)
  - [Licens](#licens)
    - [Användarvillkor](#användarvillkor)
      - [1. Beviljade rättigheter](#1-beviljade-rättigheter)
      - [2. Obligatoriska villkor](#2-obligatoriska-villkor)
      - [3. Upphovsrätt](#3-upphovsrätt)
      - [4. Garantifriskrivning och ansvarsbegränsning](#4-garantifriskrivning-och-ansvarsbegränsning)

## Introduktion och Syfte

Biblioteket **SA-MP Injector C#** är en C#-lösning designad för att förenkla den automatiserade starten och anslutningen av San Andreas Multiplayer (SA-MP) och Open Multiplayer (OMP) klienter till servrar. Det fungerar som ett verktyg för DLL-injektion (Dynamic Link Library), och laddar programmatiskt `samp.dll`- eller `omp-client.dll`-biblioteken i spelprocessen Grand Theft Auto: San Andreas (`gta_sa.exe`).

Huvudsyftet med detta bibliotek är att möjliggöra för andra C#-applikationer (som anpassade launchers, serverhanteringsverktyg eller andra verktyg) att starta spelet med specifika parametrar (smeknamn, IP, port och lösenord) på ett transparent sätt för användaren, vilket automatiserar anslutningsprocessen till en SA-MP/OMP-server.

## Designfilosofi

Designen av **SA-MP Injector C#** fokuserar på robusthet, säkerhet och ett förenklat användargränssnitt, vilket kapslar in komplexiteten i lågnivåsystemoperationer.

### Interoperabilitet (P/Invoke)

Den centrala funktionaliteten för DLL-injektion och skapande av suspenderade processer är i grunden en lågnivåoperation i operativsystemet. För detta ändamål använder biblioteket i stor utsträckning **P/Invoke (Platform Invoke)**-funktionen i .NET, vilket möjliggör anrop av inbyggda funktioner från Windows API (främst från `kernel32.dll`) direkt från C#-kod. Detta är tydligt i deklarationen av `partial`-metoder och användningen av `[LibraryImport(KERNEL32, SetLastError = true)]`-attributet.

### Resurshantering (`SafeHandle`)

Operationer med operativsystemresurser, som "handles" för processer och trådar, kräver noggrann hantering för att undvika minnes- eller resursläckor. Biblioteket använder klasser som ärver från `SafeHandle` (`SafeProcessHandle` och `SafeThreadHandle`) för att säkerställa att dessa resurser alltid frigörs korrekt, även vid undantag. Detta följer principen **RAII (Resource Acquisition Is Initialization)** från C++ och utökar den till .NET-miljön.

### Säkerhet och Robusthet

Biblioteket innehåller flera säkerhetslager:
- **Validering av Indata:** All indata från användaren valideras strikt innan några kritiska operationer påbörjas, vilket minimerar risken för körtidsfel eller oväntat beteende.
- **Felhantering:** Anrop till inbyggda API:er åtföljs av felkontroller (`SetLastError = true` och `Marshal.GetLastWin32Error()`) för att ge detaljerade och förståeliga felmeddelanden.
- **Processavslutning:** Om ett fel uppstår under injektionsprocessen avslutas den nyskapade spelprocessen automatiskt för att förhindra att "zombie"-processer fortsätter att köras.

## Systemkrav

### Utvecklingsmiljö

- **.NET SDK 7.0 eller högre:** Biblioteket är byggt för `net7.0-windows`.
- **C# 11.0 eller högre:** Krävs för funktioner som `ImplicitUsings`, `Nullable`, `AllowUnsafeBlocks` och `LibraryImport`.
- **Visual Studio 2022 eller en kompatibel utvecklingsmiljö:** För att bygga och integrera biblioteket.
- **Kompileringsplattform:** `x86 (32-bit)` är det obligatoriska målet på grund av arkitekturen för `gta_sa.exe` och SA-MP/OMP DLL:erna.

```xml
<!-- samp-injector-csharp.csproj -->
<Project Sdk="Microsoft.NET.Sdk">
    <PropertyGroup>
        <TargetFrameworks>net7.0-windows</TargetFrameworks>
        <PlatformTarget>x86</PlatformTarget> <!-- KRITISKT: Måste vara x86 -->
        <ImplicitUsings>enable</ImplicitUsings>
        <Nullable>enable</Nullable>
        <UseWindowsForms>true</UseWindowsForms>
        <AllowUnsafeBlocks>true</AllowUnsafeBlocks> <!-- Krävs för avancerad P/Invoke -->
    </PropertyGroup>
</Project>
```

### Körmiljö

- **Operativsystem:** Windows (alla moderna versioner som är kompatibla med .NET 7.0+).
- **Grand Theft Auto: San Andreas (GTA: SA):** En installation av spelet krävs.
- **SA-MP eller OMP Client DLL:er:** `samp.dll` eller `omp-client.dll` måste finnas i spelets rotkatalog, beroende på vilken typ av injektion som önskas.

## Installation och Grundläggande Användning

### Lägga till i Ditt Projekt

Det enklaste sättet att använda detta bibliotek är att lägga till `Samp_Injector_CSharp`-projektet som en referens i ditt eget C#-projekt.

1. Klona eller ladda ner bibliotekets arkiv.
2. I Visual Studio, högerklicka på "Dependencies" (eller "References") i ditt projekt.
3. Välj "Add Project Reference...".
4. Navigera till bibliotekets katalog och lägg till `samp-injector-csharp.csproj`-projektet.

### Användningsexempel

För att starta spelet och ansluta till en server, anropa helt enkelt den statiska metoden `Injector.Initialize_Game`.

```csharp
using Samp_Injector_CSharp;
using System;
using System.Windows.Forms; // För MessageBox, om det inte är ett WinForms-projekt

namespace Launcher {
    public partial class Main : Form {
        public Main() {
            InitializeComponent();
        }

        private void Connect(object sender, EventArgs e) {
            string inject_type = "SAMP"; // "SAMP" eller "OMP"
            string game_folder = @"C:\Games\GTA San Andreas"; // Sökväg till GTA: SA-mappen
            string nickname = "Namn";
            string ip = "127.0.0.1";
            string port = "7777";
            string password = ""; // Lämna tomt om det inte finns något lösenord

            // Exempel på SA-MP-injektion
            Injector.Initialize_Game(inject_type, game_folder, nickname, ip, port, password);

            // Om det är OMP, ändra inject_type:
            // inject_type = "OMP";
            // Injector.Initialize_Game(inject_type, game_folder, nickname, ip, port, password);
        }
    }
}
```

## Bibliotekets Komponenter

Biblioteket är strukturerat i flera filer, var och en med ett tydligt och väldefinierat ansvar, vilket främjar organisation, underhållbarhet och separation av ansvarsområden. Nedan följer en detaljerad beskrivning av varje komponent.

### 1. `Constants.cs`

Denna fil är en centraliserad förvaringsplats för alla konstanter och oföränderliga värden som används i hela biblioteket. Dess existens främjar kodunderhåll, läsbarhet och konsistens, och säkerställer att kritiska värden definieras på en enda plats.

Organisationen av konstanter per kategori underlättar förståelsen av deras syfte:

- **Game Related Constants**
   - `MIN_PORT`: Definierar det minsta tillåtna värdet för en serveranslutningsport (1).
   - `MAX_PORT`: Definierar det maximala tillåtna värdet för en serveranslutningsport (65535).
   - `MAX_NICKNAME_LENGTH`: Anger den maximala tillåtna längden för spelarens smeknamn (23 tecken), en gräns som införts av SA-MP/OMP-klienten själv.

- **File Names**
   - `SAMP_DLL_NAME`: Filnamnet på huvudbiblioteket för SA-MP-klienten (`"samp.dll"`).
   - `OMP_DLL_NAME`: Filnamnet på biblioteket för Open Multiplayer-klienten (`"omp-client.dll"`), som används vid OMP-injektioner.
   - `GAME_EXE_NAME`: Namnet på den körbara filen för spelet Grand Theft Auto: San Andreas (`"gta_sa.exe"`).

- **System Libraries and Functions**
   - `KERNEL32_DLL`: Namnet på Windows-systembiblioteket som innehåller väsentliga funktioner för hantering av processer och minne (`"kernel32.dll"`).
   - `LOAD_LIBRARY_FUNC`: Namnet på funktionen inom `kernel32.dll` som ansvarar för att dynamiskt ladda ett bibliotek (`"LoadLibraryA"`).

- **Command Line Arguments**
   - `CMD_ARGS_PART1`: Inledande del av kommandoradsargumenten för spelet (`"-c -n "`).
   - `CMD_ARGS_PART2`: Separator för IP-adressen (`" -h "`).
   - `CMD_ARGS_PART3`: Separator för porten (`" -p "`).
   - `CMD_ARGS_PART4_PASSWORD`: Prefix för lösenordsargumentet (`" -z "`), används endast om ett lösenord anges.
   - `CMD_ARGS_BASE_LENGTH`: Den fördefinierade längden på de konstanta delarna av kommandoraden, exklusive den körbara filen och användarens värden (14 tecken).
   - `CMD_ARG_PASSWORD_LENGTH`: Längden på prefixet för lösenordsargumentet (4 tecken).

- **Error Message Titles**
   - `ERROR_TITLE_SAMP`: Standardtitel för felmeddelanderutor relaterade till SA-MP-fel (`"SA-MP Injector Error - SPC"`).
   - `ERROR_TITLE_OMP`: Standardtitel för felmeddelanderutor relaterade till OMP-fel (`"OMP Injector Error - SPC"`).

- **Process Creation Flags**
   - `CREATE_SUSPENDED`: Flagga som instruerar operativsystemet att skapa en process och dess huvudtråd i ett suspenderat tillstånd (`0x00000004`). Detta är grundläggande för DLL-injektionen innan spelet börjar köras.
   - `PROCESS_CREATION_FLAGS`: En kombination av processkapningsflaggor, för närvarande endast definierad som `CREATE_SUSPENDED`.

- **Timeouts**
   - `DLL_INJECTION_TIMEOUT_MS`: Den maximala tiden (i millisekunder) som biblioteket väntar på att den fjärrtråd som ansvarar för DLL-injektionen ska slutföras (10000ms = 10 sekunder).

- **Memory Allocation Flags**
   - `MEM_COMMIT`: Flagga som reserverar sidor i det virtuella minnet och "committar" dem (allokerar fysiskt minne) (`0x1000`).
   - `MEM_RESERVE`: Flagga som endast reserverar ett intervall av virtuellt adressutrymme för senare användning (`0x2000`).
   - `MEM_RELEASE`: Flagga som av-committar och frigör en region av sidor (`0x8000`).
   - `MEMORY_ALLOCATION_TYPE`: En kombination av `MEM_COMMIT` och `MEM_RESERVE`, som används för att allokera minne för DLL-sökvägen i fjärrprocessen.
   - `MEMORY_PROTECTION`: Definierar minnesskyddsbehörigheter (för närvarande `0x04`, vilket motsvarar `PAGE_READWRITE` i Windows API, vilket tillåter läsning och skrivning i det allokerade minnet).

### 2. `InjectionType.cs`

Denna fil definierar en enkel enumerator för att ge ett säkert och tydligt sätt att specificera vilken typ av injektion som ska utföras. Användningen av en `enum` istället för strängar (`"samp"`, `"omp"`) förhindrar stavfel och gör koden mer läsbar och robust.

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

Denna fil är bibliotekets publika fasad (Facade) och fungerar som den enda ingångspunkten för konsumerande applikationer. Den abstraherar bort all intern komplexitet i injektionsprocessen till en enda statisk metod.

- **Huvudansvar:** Metoden `Initialize_Game` tar emot alla nödvändiga parametrar som strängar, bestämmer typen av injektion och delegerar arbetet till `Injector_Core`. Den är också ansvarig för att fånga resultatet av operationen och presentera felmeddelanden för slutanvändaren via `MessageBox`, vilket gör interaktionen med slutanvändaren konsekvent.

```csharp
// Utdrag från Injector.cs
public static class Injector {
    private static readonly Injector_Core s_core = new();

    public static void Initialize_Game(string inject_type_str, string folder, string nickname, string ip, string port, string password) {
        // ... Logik för att konvertera inject_type_str till Injection_Type ...

        if (!s_core.Try_Initialize_Game(type, folder, nickname, ip, port, password, out string error_message)) {
            string error_title = (type == Injection_Type.OMP) ? Constants.ERROR_TITLE_OMP : Constants.ERROR_TITLE_SAMP;
            MessageBox.Show(error_message, error_title, MessageBoxButtons.OK, MessageBoxIcon.Error);
        }
    }
}
```

### 4. `InjectorCore.cs`

Detta är bibliotekets "hjärna", där sekvensen av injektionsoperationer orkestreras. Den kopplar samman indatavalidatorer med processhanterare för att utföra hela arbetsflödet.

- **Huvudansvar:** Metoden `Try_Initialize_Game` definierar den stegvisa logiken: den validerar indata, skapar spelprocessen i ett suspenderat tillstånd, injicerar de nödvändiga DLL:erna (`samp.dll` och, valfritt, `omp-client.dll`) och, om allt lyckas, återupptar den spelets tråd. En avgörande aspekt är `finally`-blocket, som säkerställer att spelprocessen avslutas (`Kill()`) i händelse av något fel under injektionsstegen, vilket förhindrar "zombie"-processer.

```csharp
// Utdrag från InjectorCore.cs
internal sealed class Injector_Core {
    public bool Try_Initialize_Game(...) {
        // ... Validering av indata ...

        using Process_Handler.Process_Info process_info = Process_Handler.Create_Game_Process(...);
        
        // ...
        bool success = false;
        try {
            // ... Injektion av samp.dll ...
            // ... Valfri injektion av omp-client.dll ...
            // ... Återupptagande av speltråden ...
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

Fungerar som bibliotekets första försvarslinje och säkerställer att endast giltiga och säkra data bearbetas. Den förberedande valideringen förhindrar lågnivåundantag och gör det möjligt för biblioteket att ge tydliga och åtgärdbara felmeddelanden.

- **Huvudansvar:** Den statiska metoden `Try_Validate` utför en serie kontroller, inklusive smeknamnets format, det numeriska intervallet för porten och, avgörande, existensen av väsentliga filer (`gta_sa.exe`, `samp.dll`, etc.) i den angivna katalogen. Om någon kontroll misslyckas returnerar den `false` och fyller i en `out string` med en beskrivning av felet.

```csharp
// Utdrag från InputValidator.cs
internal static class Input_Validator {
    public static bool Try_Validate(...) {
        if (nickname.Length > Constants.MAX_NICKNAME_LENGTH)
            return (error_message = $"Nickname length exceeds the maximum...") != null && false;

        string game_exe_path = Path.Combine(folder_path, Constants.GAME_EXE_NAME);
        if (!File.Exists(game_exe_path))
            return (error_message = $"Game executable not found...") != null && false;
        
        // ...
        return true;
    }
}
```

### 6. `NativeImports.cs`

Denna fil är bron mellan den hanterade C#-koden och de ohanterade inbyggda Windows-API:erna. Den använder P/Invoke-interoperabilitetsfunktionen för att deklarera funktionssignaturer från `kernel32.dll`.

- **Huvudansvar:** Deklarera `extern`-metoder med `[LibraryImport]`- eller `[DllImport]`-attributen som motsvarar funktioner i Windows API, såsom `CreateProcessA`, `VirtualAllocEx` och `CreateRemoteThread`. Den definierar också datastrukturerna (`Startup_Info`, `Process_Information`) med en minneslayout som är kompatibel med den inbyggda koden. För optimering laddas handtagen till `kernel32.dll` och adressen till `LoadLibraryA`-funktionen statiskt vid initiering.

```csharp
// Utdrag från NativeImports.cs
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

Det är det lågnivåskikt som utför operationer för processhantering. Det använder funktionerna som importerats från `NativeImports.cs` för att interagera direkt med operativsystemet.

- **Huvudansvar:**
   1. **`Create_Game_Process`**: Bygger kommandoraden och startar `gta_sa.exe` med `CREATE_SUSPENDED`-flaggan.
   2. **`Inject_DLL`**: Implementerar DLL-injektionstekniken genom att skapa en fjärrtråd. Detta är den mest kritiska funktionen, som orkestrerar minnesallokering, skrivning och fjärrkörning av `LoadLibraryA`.
   3. **`Resume_Game_Thread`**: Utför det sista steget att "tina upp" spelets huvudtråd.

```csharp
// Utdrag från ProcessHandler.cs
internal static bool Inject_DLL(SafeProcessHandle process_handle, string dll_path, out string error_message) {
    // ... Allokering och skrivning till fjärrminne ...

    IntPtr remote_thread = Native_Imports.CreateRemoteThread(process_handle, IntPtr.Zero, 0, Native_Imports.load_library_address, remote_memory, 0, IntPtr.Zero);

    if (remote_thread == IntPtr.Zero)
        return (error_message = $"Failed to create a remote thread...") != null && false;
    
    // ... Väntar på slutförande och kontrollerar resultatet ...
    return true;
}
```

### 8. `SafeHandles.cs`

Denna fil implementerar en rekommenderad praxis för interoperabilitet: användningen av `SafeHandle` för att hantera ohanterade resurser. Detta säkerställer att Windows process- och tråd-"handles" frigörs på ett deterministiskt och säkert sätt.

- **Huvudansvar:** Klasserna `SafeProcessHandle` och `SafeThreadHandle` ärver från `SafeHandleZeroOrMinusOneIsInvalid`. De kapslar in en `IntPtr` som representerar det inbyggda handtaget. Den största fördelen är implementeringen av `ReleaseHandle`-metoden, som garanteras av .NET runtime att anropas när objektet kasseras (till exempel i slutet av ett `using`-block), vilket förhindrar resursläckor.

```csharp
// Utdrag från SafeHandles.cs
internal sealed class SafeProcessHandle : SafeHandleZeroOrMinusOneIsInvalid {
    // ... Konstruktorer ...

    protected override bool ReleaseHandle() {
        // Detta anrop garanteras av .NET för att frigöra det inbyggda handtaget.
        return Native_Imports.CloseHandle(handle);
    }
}
```

## Detaljerad Cykel för DLL-injektion

Processen för DLL-injektion är en sekvens av kritiska steg som måste utföras med precision för att lyckas. Biblioteket **SA-MP Injector C#** orkestrerar detta på följande sätt:

### 1. Validering av Indata

Innan någon interaktion med systemet kontrolleras alla parametrar som tillhandahålls av användaren (sökväg till spelmappen, smeknamn, IP, port och lösenord) av `Input_Validator`. Detta inkluderar:
- Kontrollera att smeknamnet ligger inom längdgränserna och inte är tomt.
- Säkerställa att porten är ett giltigt nummer och ligger inom det acceptabla intervallet (1-65535).
- Bekräfta att `gta_sa.exe`, `samp.dll` och `omp-client.dll` (om `Injection_Type` är OMP) finns på de förväntade sökvägarna.

> [!NOTE]
> Detta förebyggande steg är grundläggande för att undvika oväntade API-fel och ge tydlig feedback till användaren.

### 2. Skapande av Spelprocessen (Suspenderad)

Biblioteket använder `Native_Imports.CreateProcessA` för att starta `gta_sa.exe`. En avgörande detalj är dock användningen av `Constants.CREATE_SUSPENDED`-flaggan.
- **Suspenderad Skapelse:** Denna flagga gör att Windows skapar processen och dess huvudtråd, men placerar den i ett suspenderat tillstånd, vilket förhindrar att spelkoden börjar köras.
- **Kommandorad:** Kommandoraden är noggrant konstruerad av `Process_Handler.Build_Full_Command_Args_ANSI` för att inkludera alla serveranslutningsparametrar (`-c -n <nickname> -h <ip> -p <port> -z <password>`).
- **Process/Tråd-handtag:** `CreateProcessA` returnerar handtagen till processen och huvudtråden, som är inkapslade i `SafeProcessHandle` och `SafeThreadHandle` för säker resurshantering.

> [!IMPORTANT]
> Suspenderad skapelse är avgörande för injektionen. Om spelet skulle börja köras före injektionen, skulle det kunna initiera sina egna säkerhetsmekanismer eller så skulle `samp.dll`/`omp-client.dll` kunna laddas före vår kontroll, vilket gör injektionen mer komplex eller ineffektiv.

### 3. Injektion av `samp.dll`

Med spelprocessen suspenderad, utför funktionen `Process_Handler.Inject_DLL` följande steg:
1. **Hämta `LoadLibraryA`:** Adressen till funktionen `LoadLibraryA` (från `kernel32.dll`) i spelprocessen hämtas. Detta är den funktion som Windows använder för att ladda DLL:er.
2. **Allokering av Fjärrminne:** `Native_Imports.VirtualAllocEx` används för att allokera ett minnesblock inom adressutrymmet för `gta_sa.exe`-processen. Storleken på blocket är tillräcklig för att lagra den fullständiga sökvägen till `samp.dll`.
3. **Skrivning av DLL-sökväg:** Den fullständiga sökvägen till `samp.dll`-filen skrivs till det nyligen allokerade minnet i spelprocessen med hjälp av `Native_Imports.WriteProcessMemory`.
4. **Skapande av Fjärrtråd:** `Native_Imports.CreateRemoteThread` anropas för att skapa en ny tråd i `gta_sa.exe`-processen. Denna tråd instrueras att köra `LoadLibraryA` med adressen till DLL-sökvägssträngen som sitt enda argument.
5. **Vänta på Slutförande:** Biblioteket väntar en timeout (`Constants.DLL_INJECTION_TIMEOUT_MS`) på att fjärrtråden ska slutföra sin körning, vilket indikerar att `LoadLibraryA` har försökt ladda DLL:en.
6. **Kontrollera Resultat:** Returkoden från fjärrtråden kontrolleras. Om `LoadLibraryA` lyckades, returnerar den basadressen för den laddade DLL:en. Ett nollvärde eller ett misslyckande att hämta returkoden indikerar att injektionen misslyckades.
7. **Rensning:** Det allokerade fjärrminnet frigörs (`Native_Imports.VirtualFreeEx`) och handtaget till fjärrtråden stängs (`Native_Imports.CloseHandle`).

### 4. Injektion av `omp-client.dll` (Valfritt, Beroende av SA-MP)

> [!TIP]
> Injektionen av `omp-client.dll` **sker alltid efter en lyckad injektion av `samp.dll`**. OMP-klienten använder SA-MP:s infrastruktur, därför är `samp.dll` ett krav.

Om den specificerade `Injection_Type` är `OMP`, upprepas steg 3 för att injicera `omp-client.dll`. Logiken är identisk, vilket säkerställer att båda biblioteken som krävs för OMP laddas innan spelet startar helt.

### Återuppta Spelets Huvudtråd

Slutligen, efter att alla nödvändiga DLL:er har injicerats framgångsrikt, anropas funktionen `Process_Handler.Resume_Game_Thread`. Denna funktion använder `Native_Imports.ResumeThread` för att tillåta huvudtråden i `gta_sa.exe` att fortsätta sin körning. Spelet startar nu med SA-MP/OMP DLL:erna redan laddade och kommandoradsargumenten för serveranslutning tillämpade.

## Felhantering och Felfall

Biblioteket är utformat för att ge tydlig feedback vid fel. De flesta fel fångas upp och ett beskrivande `error_message` returneras för att presenteras för användaren, vanligtvis via en `MessageBox`.

### Valideringsfel för Indata

Dessa fel uppstår innan någon systemoperation och upptäcks av `Input_Validator`.

#### Ogiltigt Smeknamn

- **Felmeddelande (Exempel 1):** `"Nickname cannot be empty. Please provide a valid nickname."`
- **Felmeddelande (Exempel 2):** `"Nickname length exceeds the maximum allowed of 23 characters. Please use a shorter nickname."`
- **Varför:** Smeknamnsfältet är tomt eller överskrider den maximala gränsen på 23 tecken.
- **Lösning:** Användaren måste ange ett giltigt smeknamn som respekterar teckengränsen.

#### Ogiltig Port

- **Felmeddelande (Exempel 1):** `"Invalid port format. The port must be a numeric value. Please provide a valid integer for the port."`
- **Felmeddelande (Exempel 2):** `"The specified port number (70000) is outside the valid range of 1 to 65535. Please provide a valid port."`
- **Varför:** Den angivna porten är inte ett heltal, eller ligger utanför det giltiga intervallet 1 till 65535.
- **Lösning:** Användaren måste ange ett giltigt portnummer inom det specificerade intervallet.

#### Saknade Spel-/DLL-filer

- **Felmeddelande (Exempel 1):** `"Game executable not found. Please ensure 'gta_sa.exe' exists at the specified path: C:\Program Files (x86)\Rockstar Games\GTA San Andreas\gta_sa.exe"`
- **Felmeddelande (Exempel 2):** `"SA-MP library not found. Please ensure 'samp.dll' exists at the specified path: C:\Program Files (x86)\Rockstar Games\GTA San Andreas\samp.dll"`
- **Felmeddelande (Exempel 3, OMP):** `"OMP library not found. Please ensure 'omp-client.dll' exists at the specified path for OMP injection: C:\Program Files (x86)\Rockstar Games\GTA San Andreas\omp-client.dll"`
- **Varför:** Spelets körbara fil (`gta_sa.exe`), SA-MP DLL (`samp.dll`) eller OMP DLL (`omp-client.dll`) hittades inte i den angivna spelmappen.
- **Lösning:** Användaren bör verifiera sökvägen till spelmappen och se till att alla nödvändiga filer finns där.

### Fel vid Skapande av Process

Dessa fel uppstår när biblioteket försöker starta `gta_sa.exe`.

#### Misslyckades med att Skapa Processen

- **Felmeddelande (Exempel):** `"Failed to create game process. Ensure 'gta_sa.exe' is not running and you have sufficient permissions to execute the file. System Error: Access is denied."`
- **Varför:**
   - **Fil i Användning:** `gta_sa.exe` kan redan vara igång, vilket förhindrar att en ny instans skapas, eller så kan operativsystemet ha en låsning på filen.
   - **Behörigheter:** Användaren som kör applikationen kanske inte har tillräckliga behörigheter för att starta en ny process eller för att komma åt spelets körbara fil.
   - **Ogiltig/Skadad Sökväg:** Även om den grundläggande valideringen kontrollerar existens, kan det finnas problem med läs-/körbehörigheter eller så kan den körbara filen vara skadad.
- **Lösning:** Se till att inga andra instanser av `gta_sa.exe` körs. Kör applikationen som administratör, om möjligt. Kontrollera integriteten hos `gta_sa.exe`-filen.

### Fel vid DLL-injektion

Dessa är de mest kritiska felen och inträffar under försöket att injicera `samp.dll` eller `omp-client.dll` i spelprocessen.

#### Handtag till `kernel32.dll` Otillgängligt

- **Felmeddelande:** `"Failed to obtain a handle to kernel32.dll. This is an essential system library and this error indicates a severe system issue."`
- **Varför:** Biblioteket `kernel32.dll`, som är grundläggande för systemoperationer i Windows, kunde inte laddas eller dess handtag kunde inte erhållas. Detta är extremt sällsynt och tyder på ett allvarligt problem med operativsystemet.
- **Lösning:** En omstart av systemet kan lösa problemet. Annars indikerar det ett djupare problem med Windows-installationen.

#### Funktionen `LoadLibraryA` Otillgänglig

- **Felmeddelande:** `"Failed to find the address of the LoadLibraryA function in kernel32.dll. This is critical for injecting the DLL."`
- **Varför:** Funktionen `LoadLibraryA`, som är väsentlig för att dynamiskt ladda DLL:er, kunde inte hittas i `kernel32.dll`. Precis som det föregående felet är detta ett sällsynt lågnivåproblem.
- **Lösning:** Liknar otillgängligheten för handtaget till `kernel32.dll`.

#### Misslyckad Allokering av Fjärrminne

- **Felmeddelande:** `"Failed to allocate memory in the target process. This might be due to insufficient permissions or process protection mechanisms."`
- **Varför:** Biblioteket kunde inte allokera ett minnesblock i adressutrymmet för `gta_sa.exe`.
   - **Behörigheter:** Applikationen kanske inte har nödvändiga behörigheter för att ändra minnesutrymmet för en annan process.
   - **Processkydd:** `gta_sa.exe`-processen eller operativsystemet kan tillämpa skydd mot kodinjektion.
   - **Adressutrymme:** I extrema fall kan processens adressutrymme vara fragmenterat eller sakna tillräckligt med sammanhängande minne, även om det är osannolikt för storleken på en DLL-sökvägssträng.
- **Lösning:** Kör applikationen som administratör. Kontrollera om det finns säkerhetsprogramvara (antivirus, anti-cheat) som kan blockera minnesallokering i andra processer.

#### Misslyckades med att Skriva till Processens Minne

- **Felmeddelande:** `"Failed to write DLL path to the target process memory. Verify process permissions and ensure the DLL path is accessible."`
- **Varför:** Biblioteket allokerade minne i spelprocessen, men kunde inte skriva DLL-sökvägen till den platsen.
   - **Behörigheter:** Liknande misslyckad minnesallokering, kan det vara ett problem med skrivbehörigheter.
   - **Skydd:** Operativsystemets minnesskydd eller anti-cheat kan förhindra skrivning.
- **Lösning:** Kontrollera behörigheter och säkerhetsprogramvara.

#### Misslyckades med att Skapa Fjärrtråd

- **Felmeddelande (Exempel):** `"Failed to create a remote thread in the target process to execute the DLL injection. This could be due to security restrictions or process state. System Error: Not enough memory resources are available to process this command."`
- **Varför:** API:et `CreateRemoteThread` misslyckades med att skapa en ny tråd i `gta_sa.exe`-processen för att anropa `LoadLibraryA`.
   - **Processkydd/Anti-Cheat:** Många anti-cheat-system och operativsystemskydd övervakar och blockerar skapandet av fjärrtrådar, eftersom det är en vanlig injektionsteknik.
   - **Processtillstånd:** Spelprocessen kan vara i ett inkonsekvent tillstånd som förhindrar skapandet av trådar.
- **Lösning:** Inaktivera tillfälligt all anti-cheat- eller antivirusprogramvara. Försök att köra applikationen som administratör.

#### Timeout eller Fel vid Väntan på Injektion

- **Felmeddelande (Exempel):** `"Timeout or error waiting for DLL injection to complete. System Error: The wait operation timed out."`
- **Varför:** Fjärrtråden (som anropar `LoadLibraryA`) avslutade inte sin körning inom den angivna tidsgränsen (10 sekunder).
   - **Frysning:** `LoadLibraryA` kan ha hängt sig eller tagit överdrivet lång tid.
   - **Blockering:** Någon säkerhetsmekanism kan ha avlyssnat och blockerat körningen av `LoadLibraryA` på obestämd tid.
- **Lösning:** Kan indikera att DLL:en tar för lång tid att ladda eller att något hindrar den. Att kontrollera systemloggar eller SA-MP/OMP-loggar (om de finns) kan hjälpa.

#### DLL-injektion Misslyckades eller Returnerade Fel

- **Felmeddelande:** `"DLL injection failed or returned an error. The LoadLibrary call may have failed in the target process."`
- **Varför:** Fjärrtråden slutfördes, men returkoden från `LoadLibraryA` indikerade ett fel (vanligtvis `0` eller `NULL`).
   - **Icke-existerande/Skadad DLL:** Trots den inledande valideringen kan DLL:en ha flyttats eller skadats mellan valideringen och injektionen.
   - **Saknade DLL-beroenden:** `samp.dll` eller `omp-client.dll` kan vara beroende av andra DLL:er som inte finns i spelkatalogen eller i systemets PATH.
   - **Internt DLL-fel:** DLL:en själv kan ha ett internt fel som förhindrar att den laddas korrekt.
- **Lösning:** Kontrollera integriteten hos `samp.dll`/`omp-client.dll`. Se till att alla DLL-beroenden finns.

### Fel vid Återupptagande av Speltråden

Detta är det sista möjliga felet i injektionscykeln.

- **Felmeddelande (Exempel):** `"Failed to resume the game process thread: Invalid handle."`
- **Varför:** API:et `ResumeThread` misslyckades med att återstarta huvudtråden i `gta_sa.exe`.
   - **Ogiltigt Handtag:** Trådens handtag kan ha blivit ogiltigförklarat av någon anledning.
   - **Behörighetsproblem:** Applikationen kanske inte har behörighet att ändra trådens tillstånd.
- **Lösning:** Försök att köra applikationen som administratör. Om det kvarstår kan det indikera ett djupare problem med systemets eller spelprocessens stabilitet.

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