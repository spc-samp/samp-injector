# SA-MP Injector C++

<div align="center">

![C++](https://img.shields.io/badge/C%2B%2B-14%2F17%2F20-00599C?style=for-the-badge&logo=cplusplus)
![Platform](https://img.shields.io/badge/Platform-Windows-blue?style=for-the-badge&logo=windows&logoColor=white)
![Architecture](https://img.shields.io/badge/Architecture-x86%20(32--bit)-lightgrey?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)

**Ett C++-bibliotek för att starta och automatisera anslutningen av SA-MP- och OMP-klienter till servrar, via DLL-injektion.**

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

- [SA-MP Injector C++](#sa-mp-injector-c)
  - [Språk](#språk)
  - [Innehållsförteckning](#innehållsförteckning)
  - [Översikt och Syfte](#översikt-och-syfte)
  - [Designprinciper](#designprinciper)
    - [Helt `Header-Only`](#helt-header-only)
    - [Säker Resurshantering (RAII)](#säker-resurshantering-raii)
    - [Robusthet och Felkontroll](#robusthet-och-felkontroll)
    - [Flexibilitet med C++-standarder](#flexibilitet-med-c-standarder)
  - [Nödvändig Miljö](#nödvändig-miljö)
    - [För Utveckling](#för-utveckling)
    - [För Körning](#för-körning)
  - [Snabbstart](#snabbstart)
    - [Integration i Projektet](#integration-i-projektet)
    - [Förenklat Användningsexempel](#förenklat-användningsexempel)
  - [Bibliotekets Struktur](#bibliotekets-struktur)
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
  - [Den Detaljerade Injektionsprocessen](#den-detaljerade-injektionsprocessen)
    - [1. Initieringsbegäran](#1-initieringsbegäran)
    - [2. Förberedelse av Miljön](#2-förberedelse-av-miljön)
    - [3. Integritets- och Parameterkontroll](#3-integritets--och-parameterkontroll)
    - [4. Förberedelse av Argument för Spelet](#4-förberedelse-av-argument-för-spelet)
    - [5. Initiering av Spelprocessen (Suspenderad)](#5-initiering-av-spelprocessen-suspenderad)
    - [6. Injektion av SA-MP-biblioteket (`samp.dll`)](#6-injektion-av-sa-mp-biblioteket-sampdll)
    - [7. Injektion av OMP-biblioteket (`omp-client.dll`) - Villkorlig](#7-injektion-av-omp-biblioteket-omp-clientdll---villkorlig)
    - [8. Aktivering av Spelet](#8-aktivering-av-spelet)
  - [Diagnostik av Fel och Problem](#diagnostik-av-fel-och-problem)
    - [Valideringsfel vid Inmatning](#valideringsfel-vid-inmatning)
      - [Ogiltigt Användarnamn](#ogiltigt-användarnamn)
      - [Ogiltig Anslutningsport](#ogiltig-anslutningsport)
      - [Nödvändiga Resurser Saknas](#nödvändiga-resurser-saknas)
    - [Problem med Processhantering](#problem-med-processhantering)
      - [Svårigheter att Starta Spelprocessen](#svårigheter-att-starta-spelprocessen)
    - [Problem med DLL-injektion](#problem-med-dll-injektion)
      - [Kan inte hitta `LoadLibraryW`](#kan-inte-hitta-loadlibraryw)
      - [Misslyckad Allokering av Fjärrminne](#misslyckad-allokering-av-fjärrminne)
      - [Oförmåga att Skriva Data till Processen](#oförmåga-att-skriva-data-till-processen)
      - [Misslyckande vid Skapande av Injektionstråd](#misslyckande-vid-skapande-av-injektionstråd)
      - [Tidsgräns Överskriden eller Fel vid Väntan på Injektion](#tidsgräns-överskriden-eller-fel-vid-väntan-på-injektion)
      - [Internt Fel i DLL-injektionen](#internt-fel-i-dll-injektionen)
    - [Svårigheter att Återuppta Spelets Körning](#svårigheter-att-återuppta-spelets-körning)
  - [Licens](#licens)
    - [Användarvillkor](#användarvillkor)
      - [1. Beviljade rättigheter](#1-beviljade-rättigheter)
      - [2. Obligatoriska villkor](#2-obligatoriska-villkor)
      - [3. Upphovsrätt](#3-upphovsrätt)
      - [4. Garantifriskrivning och ansvarsbegränsning](#4-garantifriskrivning-och-ansvarsbegränsning)

## Översikt och Syfte

**SA-MP Injector C++** är ett kompakt och lättintegrerat C++-bibliotek, utformat för att automatisera processen för att starta och ansluta till San Andreas Multiplayer (SA-MP) och Open Multiplayer (OMP) servrar. Till skillnad från att starta `gta_sa.exe` direkt, laddar denna lösning programmatiskt biblioteken `samp.dll` eller `omp-client.dll` i Grand Theft Auto: San Andreas-spelprocessen på ett kontrollerat sätt.

Huvudsyftet är att ge C++-utvecklare möjlighet att skapa anpassade `launchers`, verktyg för communityhantering eller andra verktyg som behöver starta GTA:SA med fördefinierade anslutningsparametrar (som användarnamn, IP-adress, port och lösenord), vilket ger en smidig och automatiserad användarupplevelse.

## Designprinciper

Arkitekturen för **SA-MP Injector C++** bygger på moderna designprinciper med fokus på säkerhet, effektivitet och användarvänlighet.

### Helt `Header-Only`

Detta bibliotek distribueras uteslutande via header-filer (`.hpp`). Detta förenklar drastiskt integrationen i C++-projekt, vilket eliminerar behovet av att kompilera separata bibliotek, konfigurera `linkers` eller hantera binära beroenden.
- **Omedelbar Integration:** Det räcker med att inkludera relevanta `headers`.
- **Djup Optimering:** Kompilatorn kan utföra aggressiv `inlining` och `link-time`-optimeringar som resulterar i en mer kompakt och snabbare slutkod.

### Säker Resurshantering (RAII)

Biblioteket använder **RAII (Resource Acquisition Is Initialization)**-mönstret i stor utsträckning. Kritiska systemresurser, som Windows-process- och tråd-`handles`, är inkapslade av `std::unique_ptr` med anpassade `deleters`. Detta säkerställer att resurser alltid frigörs korrekt, oavsett exekveringsflöde eller förekomsten av undantag, vilket förhindrar läckor och förbättrar applikationens stabilitet.

### Robusthet och Felkontroll

Varje kritiskt steg i injektionen föregås av rigorösa valideringar och följs av felkontroller från Windows API. Detaljerade felmeddelanden ges till slutanvändaren via dialogrutor, med systembeskrivningar (`GetLastError()`) när det är möjligt. Detta tillvägagångssätt minimerar risken för odefinierat beteende och ger en tydlig diagnos vid fel.

### Flexibilitet med C++-standarder

Biblioteket är byggt för att vara kompatibelt med olika C++-standarder, från C++14 till C++20. Detta uppnås genom villkorliga makron som möjliggör användning av moderna funktioner (som `std::string_view`, `std::filesystem` och `std::optional` från C++17+) när de är tillgängliga, samtidigt som en `fallback` för motsvarande konstruktioner i C++14 bibehålls. Detta tillvägagångssätt säkerställer bred kompatibilitet utan att offra modernitet.

## Nödvändig Miljö

### För Utveckling

- **C++-kompilator:** Kompatibel med **C++14 eller högre**.
   - Microsoft Visual C++ (Visual Studio 2015, 2017, 2019, 2022)
   - GCC (version 5 eller senare)
   - Clang (version 3.6 eller senare)
- **Operativsystem:** **Windows**.
- **Windows SDK:** Nödvändigt för åtkomst till operativsystemets API:er.
- **Kompileringsarkitektur:** **x86 (32-bit)**. Detta är ett strikt krav, eftersom `gta_sa.exe` och SA-MP/OMP DLL:er endast fungerar på denna arkitektur.

### För Körning

- **Operativsystem:** Vilken modern version av **Windows** som helst som är kompatibel med den kompilerade binärfilen.
- **Grand Theft Auto: San Andreas (GTA:SA):** En giltig installation av spelet är obligatorisk.
- **DLL:er för SA-MP- eller OMP-klienten:** Filerna `samp.dll` eller `omp-client.dll` måste finnas i spelets rotkatalog, motsvarande den önskade injektionstypen.

## Snabbstart

Bibliotekets `header-only`-natur gör det enkelt att införliva i vilket C++-projekt som helst.

### Integration i Projektet

1. **Ladda ner Headers:** Hämta bibliotekets `.hpp`-filer (genom att klona arkivet eller ladda ner dem direkt).
2. **Organisera Filerna:** Det rekommenderas att skapa en undermapp i ditt projekt för bibliotekets `headers`, till exempel `MittProjekt/libraries/samp-injector/`.
3. **Ställ in Arkitekturen:** Konfigurera ditt projekt för att kompilera för **x86 (32-bit)**-arkitekturen.

```cpp
// Exempel på katalogstruktur
MittProjekt/
├── src/
│   └── main.cpp
├── libraries/
│   └── samp-injector/
│       ├── constants.hpp
│       ├── error_utils.hpp
│       ├── injector.hpp // Den huvudsakliga header-filen som ska inkluderas
│       └── ... (andra header-filer)
└── built/ (din utdatakatalog)
```

### Förenklat Användningsexempel

För att automatisera anslutningen till en server, anropa helt enkelt funktionen `Initialize_Game` och ange detaljerna.

```cpp
#include <iostream>
#include <string>
//
#include "samp-launcher/injector.hpp" // Inkludera den huvudsakliga header-filen

int main() {
    // Parametrar för att starta spelet och ansluta
    std::wstring inject_type = L"samp"; // Eller L"omp" för Open Multiplayer
    std::wstring game_folder = L"C:\\Games\\GTA San Andreas"; // Fullständig sökväg till GTA:SA-mappen
    std::wstring nickname = L"Namn";
    std::wstring ip = L"127.0.0.1";
    std::wstring port = L"7777";
    std::wstring password = L""; // Lämna tomt om inget lösenord

    // Huvudanropet för att starta spelet och injicera DLL:en
    Initialize_Game(inject_type, game_folder, nickname, ip, port, password);

    // Vid fel visas automatiskt en Windows-felmeddelanderuta.

    return 0;
}
```

## Bibliotekets Struktur

Biblioteket är noggrant modulariserat i flera header-filer, var och en med väldefinierade ansvarsområden, vilket underlättar organisation, underhåll och återanvändbarhet.

### 1. `constants.hpp`

Denna fil är bibliotekets **centrala förvaringsplats**, och fungerar som ett centraliserat arkiv för alla fasta och oföränderliga värden som styr beteendet och interoperabiliteten hos **SA-MP Injector C++**. Dess organisation efter logiska kategorier främjar inte bara kodens tydlighet och läsbarhet, utan underlättar också underhåll och säkerställer en strikt konsistens i hela bibliotekets ekosystem.

Varje konstant definieras med `CONSTEXPR_VAR`, som expanderar till `inline constexpr` (för C++17+) eller `static constexpr` (för C++14), vilket säkerställer att dessa värden utvärderas vid kompileringstid, vilket optimerar prestanda och typsäkerhet.

Organisationen av konstanterna efter kategori gör det lättare att förstå deras syfte:

- **Spelrelaterade Konstanter (`Game Related Constants`)**
   - `MIN_PORT`: En `int` som definierar det lägsta giltiga portnumret för anslutning till en server (värde: `1`).
   - `MAX_PORT`: En `int` som fastställer det högsta giltiga portnumret för anslutning till en server (värde: `65535`).
   - `MAX_NICKNAME_LENGTH`: En `int` som specificerar den maximala tillåtna längden för spelarens smeknamn (värde: `23` tecken), en gräns som införts av specifikationerna för SA-MP/OMP-klienten.

- **Nödvändiga Filnamn (`File Names`)**
   - `SAMP_DLL_NAME`: En `const wchar_t*` som innehåller filnamnet för SA-MP-klientens huvudbibliotek (värde: `L"samp.dll"`). Nödvändig för injektion av den klassiska klienten.
   - `OMP_DLL_NAME`: En `const wchar_t*` som innehåller filnamnet för Open Multiplayer-klientens bibliotek (värde: `L"omp-client.dll"`). Används specifikt när injektionstypen är OMP.
   - `GAME_EXE_NAME`: En `const wchar_t*` som lagrar namnet på den körbara filen för basspelet Grand Theft Auto: San Andreas (värde: `L"gta_sa.exe"`). Huvudmålet för injektionen.

- **System-API:er och Funktioner (`System Libraries and Functions`)**
   - `KERNEL32_DLL`: En `const wchar_t*` som definierar namnet på Windows systembibliotek (`L"kernel32.dll"`). Denna DLL är avgörande, eftersom den innehåller funktionerna för process- och minneshantering som injektorn använder. Användningen av `wchar_t` säkerställer kompatibilitet med API-funktioner som hanterar breda tecken, som `GetModuleHandleW`.
   - `LOAD_LIBRARY_FUNC`: En `const char*` med namnet på funktionen för att ladda en DLL dynamiskt (värde: `"LoadLibraryW"`). Även om biblioteket primärt arbetar med breda tecken, kräver Windows API-funktionen `GetProcAddress` ett funktionsnamn i ANSI-format (`char*`).

- **Kommandoradsargument (`Command Line Arguments`)**
   - Dessa konstanter definierar prefixen för argumenten som skickas till `gta_sa.exe` för att konfigurera klientens anslutning. De tillhandahålls i `Wide Character` (`const wchar_t*`) för kompatibilitet med `CreateProcessW`.
      - `CMD_ARG_CONFIG`: Argument för allmänna inställningar (värde: `L"-c"`).
      - `CMD_ARG_NICKNAME`: Argument för spelarens smeknamn (värde: `L"-n"`).
      - `CMD_ARG_HOST`: Argument för serverns IP-adress (värde: `L"-h"`).
      - `CMD_ARG_PORT`: Argument för serverns port (värde: `L"-p"`).
      - `CMD_ARG_PASSWORD`: Argument för serverns lösenord (värde: `L"-z"`). Används endast om ett lösenord anges.

- **Identifierare för Injektionstyp (`Injection types as strings`)**
   - `INJECT_TYPE_SAMP`: En `const wchar_t*` för strängrepresentationen av SA-MP-injektionstypen (värde: `L"samp"`).
   - `INJECT_TYPE_OMP`: En `const wchar_t*` för strängrepresentationen av OMP-injektionstypen (värde: `L"omp"`).

- **Titlar för Felmeddelanden (`Error message titles`)**
   - `ERROR_TITLE_SAMP`: En `const wchar_t*` som definierar standardtiteln för felmeddelanderutor relaterade till SA-MP-fel (värde: `L"SA-MP Injector Error - SPC"`).
   - `ERROR_TITLE_OMP`: En `const wchar_t*` som definierar standardtiteln för felmeddelanderutor relaterade till OMP-fel (värde: `L"OMP Injector Error - SPC"`).

- **Flaggor för Processkapande (`Process creation`)**
   - `PROCESS_CREATION_FLAGS`: En `DWORD` som inkapslar flaggorna som skickas till `CreateProcessW`. Avgörande är att den inkluderar `CREATE_SUSPENDED` (`0x00000004`), som startar spelprocessen i ett pausat tillstånd, och `DETACHED_PROCESS` (`0x00000008`), som kopplar bort den nya processen från föräldraprocessens konsol.

- **Tidsgränser (`Timeouts`)**
   - `DLL_INJECTION_TIMEOUT_MS`: En `DWORD` som specificerar den maximala tiden (i millisekunder) som biblioteket väntar på att den fjärrstyrda tråden som ansvarar för DLL-injektionen ska slutföras (värde: `10000ms`, eller 10 sekunder).

- **Flaggor för Minnesallokering (`Memory allocation`)**
   - Dessa konstanter används för API-anrop för minneshantering, som `VirtualAllocEx` och `VirtualProtect`.
      - `MEM_COMMIT`: En `DWORD` som reserverar sidor i virtuellt minne och "committar" dem (allokerar fysiskt minne) (värde: `0x1000`).
      - `MEM_RESERVE`: En `DWORD` som endast reserverar ett intervall av virtuellt adressutrymme för senare användning (värde: `0x2000`).
      - `MEM_RELEASE`: En `DWORD` som av-committar och frigör en region av sidor (värde: `0x8000`).
      - `MEMORY_ALLOCATION_TYPE`: En kombination av `MEM_COMMIT` och `MEM_RESERVE`, som används för att allokera det initiala minnet för DLL-sökvägen i den fjärrstyrda processen.
      - `MEMORY_PROTECTION`: En `DWORD` som definierar minnesskyddsbehörigheter (värde: `PAGE_READWRITE` eller `0x04` i Windows API), vilket tillåter läs- och skrivåtkomst till det allokerade minnet.

### 2. `types.hpp`

Denna koncisa fil introducerar en `enum class` för att typa de olika injektionsmodaliteterna. Användningen av en uppräkningstyp, istället för strängliteraler, höjer kodens säkerhet, förhindrar stavfel och förbättrar läsbarheten.

- **`Inject_Type`:** En `enum class` med två medlemmar: `SAMP` och `OMP`, som representerar de klienttyper som ska injiceras.

```cpp
// Exempel på types.hpp
namespace Types {
    enum class Inject_Type {
        SAMP, // Indikerar injektion för SA-MP-klienten
        OMP // Indikerar injektion för Open Multiplayer-klienten
    };
}
```

### 3. `version.hpp`

Denna header fungerar som en kompatibilitetsadapter och detekterar dynamiskt den C++-standard som används av kompilatorn. Den definierar villkorliga makron (`SAMP_INJECTOR_CXX_14`, `SAMP_INJECTOR_CXX_MODERN`) som vägleder biblioteket att använda de mest avancerade C++-funktionerna (som `std::string_view` eller `std::filesystem`) när de är tillgängliga, samtidigt som full funktionalitet säkerställs i C++14-miljöer.

- **`SAMP_INJECTOR_CXX_14`:** Definieras om C++-standarden är C++14.
- **`SAMP_INJECTOR_CXX_MODERN`:** Definieras för C++17 eller högre, vilket aktiverar nyare språkfunktioner.
- **`SAMP_INJECTOR_NODISCARD`:** Anpassar `[[nodiscard]]`-attributet för de C++-versioner som stöder det, vilket uppmuntrar kontroll av returvärden.

```cpp
// Exempel på relevant avsnitt från version.hpp
#if (defined(_MSC_VER) && _MSVC_LANG >= 201703L) || __cplusplus >= 201703L
    #define SAMP_INJECTOR_CXX_MODERN // Aktiverar moderna funktioner från C++17+
#endif

#if defined(SAMP_INJECTOR_CXX_MODERN)
    #define SAMP_INJECTOR_NODISCARD [[nodiscard]] // Använder nodiscard-attributet från C++17
#elif defined(SAMP_INJECTOR_CXX_14)
    #define SAMP_INJECTOR_NODISCARD // För C++14 är attributet inaktiverat
#endif
```

### 4. `error_utils.hpp`

Detta verktyg är dedikerat till hantering och presentation av felåterkoppling. Det abstraherar Windows-mekanismerna för att hämta systemfelmeddelanden och erbjuder ett enhetligt gränssnitt för att meddela användaren om problem.

- **`Get_System_Error_Message`:** Översätter en Windows-felkod (`GetLastError()`) till en läsbar `std::wstring`, vilket är avgörande för korrekt diagnos.
- **`Show_Error`:** Visar en dialogruta (`MessageBoxW`) som innehåller det angivna felmeddelandet, med en specifik titel för SA-MP eller OMP, vilket säkerställer tydlig kommunikation med användaren.

```cpp
// Exempel på relevant avsnitt från error_utils.hpp
namespace Error_Utils {
    SAMP_INJECTOR_NODISCARD
    inline std::wstring Get_System_Error_Message(DWORD error_code) {
        if (error_code == 0)
            return L"No error occurred.";
        
        // ... Logik för att formatera systemmeddelandet ...
    }

    inline void Show_Error(std::wstring_view message, Types::Inject_Type inject_type) {
        const std::wstring title = (inject_type == Types::Inject_Type::SAMP) ? Constants::ERROR_TITLE_SAMP : Constants::ERROR_TITLE_OMP;
        MessageBoxW(nullptr, message.data(), title.c_str(), MB_OK | MB_ICONERROR);
    }
}
```

### 5. `validation.hpp`

Denna header fungerar som bibliotekets första försvarslinje för robusthet och tillhandahåller rigorösa rutiner för att verifiera giltigheten av inmatningsdata och närvaron av nödvändiga filer. Dessa kontroller utförs innan någon lågnivåinteraktion med systemet, vilket minskar risker vid körtid och ger proaktiv återkoppling.

- **`Validate_Port`:** Validerar om portsträngen representerar ett heltal och om det ligger inom det konfigurerade intervallet (`MIN_PORT` till `MAX_PORT`).
- **`Validate_Nickname`:** Kontrollerar att smeknamnet inte är tomt och att dess längd inte överstiger `MAX_NICKNAME_LENGTH`.
- **`Validate_Files`:** Bekräftar den fysiska existensen av `gta_sa.exe`, `samp.dll` och, villkorligt för OMP-injektion, `omp-client.dll`. Implementeringen anpassar sig till `std::filesystem` (C++17+) eller `GetFileAttributesW` (C++14).

```cpp
// Exempel på relevant avsnitt från validation.hpp
namespace Validation {
    inline bool Validate_Nickname(std::wstring_view nickname_str, std::wstring& error_message) {
        if (nickname_str.empty())
            return (error_message = L"Nickname cannot be empty. Please provide a valid nickname.", false);
        
        if (nickname_str.length() > Constants::MAX_NICKNAME_LENGTH)
            return (error_message = L"Nickname length exceeds the maximum allowed of " + std::to_wstring(Constants::MAX_NICKNAME_LENGTH) + L" characters. Please use a shorter nickname.", false);
        
        return true;
    }

    inline bool Validate_Files(const std::filesystem::path& game_path, const std::filesystem::path& samp_DLL_path, const std::filesystem::path& omp_DLL_path, Types::Inject_Type inject_type) {
        if (!std::filesystem::exists(game_path))
            return (Error_Utils::Show_Error(L"Game executable not found. Please ensure 'gta_sa.exe' exists at the specified path: " + game_path.wstring(), inject_type), false);
        
        // ... Andra filkontroller ...
        return true;
    }
}
```

### 6. `resource_handle.hpp`

Implementerar en elegant och säker strategi för hantering av operativsystemets resurser, såsom Windows `HANDLE`s. Genom att använda RAII-principen garanteras att alla allokerade resurser frigörs korrekt, vilket förhindrar läckor och stärker applikationens stabilitet.

- **`Unique_Resource`:** Ett `alias template` som anpassar `std::unique_ptr` för att fungera med anpassade `deleters`, vilket möjliggör hantering av alla typer av resurser som kräver en specifik frigöringsfunktion.
- **`Make_Unique_Handle`:** En bekväm `factory`-funktion som konstruerar och returnerar en `Unique_Resource` förkonfigurerad för Windows `HANDLE`s. Den associerade `deleter` anropar `CloseHandle` automatiskt när `Unique_Resource` går ur scope, vilket säkerställer omedelbar frigörelse av resursen.

```cpp
// Exempel på relevant avsnitt från resource_handle.hpp
namespace Resource_Handle {
    // En anpassad std::unique_ptr för att hantera systemresurser.
    template<typename T, typename Deleter>
    using Unique_Resource = std::unique_ptr<std::remove_pointer_t<T>, Deleter>;

    // Skapar en Unique_Resource for en HANDLE, med en deleter som anropar CloseHandle.
    template<typename T>
    inline auto Make_Unique_Handle(T handle) {
        return Unique_Resource<T, std::function<void(T)>>(handle, [](T h) {
            if (h && h != INVALID_HANDLE_VALUE) // Säkerställer att handtaget är giltigt innan det stängs
                CloseHandle(h);
        });
    }
}
```

### 7. `privileges.hpp`

Denna komponent ansvarar för att konfigurera applikationens processsäkerhetsmiljö. Den innehåller funktionaliteten för att höja privilegier, specifikt genom att aktivera felsökningsprivilegiet (`SE_DEBUG_NAME`), vilket är ett grundläggande krav för att biblioteket ska kunna utföra DLL-injektionsoperationer i externa Windows-processer.

- **`Enable_Debug_Privilege`:** Denna funktion försöker förvärva och aktivera `SE_DEBUG_NAME`-privilegiet för den körande processen. Det är ett avgörande första steg för att ge applikationen de nödvändiga behörigheterna för att manipulera andra processer, som att allokera minne och skapa fjärrtrådar. Returnerar `true` vid framgång.

```cpp
// Exempel på relevant avsnitt från privileges.hpp
namespace Privileges {
    inline bool Enable_Debug_Privilege() {
        HANDLE token_handle;

        // Försöker öppna den aktuella processens token för att justera privilegier
        if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &token_handle))
            return false;

        auto handle_guard = Resource_Handle::Make_Unique_Handle(token_handle); // Säker hantering av handtaget

        TOKEN_PRIVILEGES tp;
        LUID luid;

        // Söker efter LUID-värdet för SE_DEBUG_NAME-privilegiet
        if (!LookupPrivilegeValue(nullptr, SE_DEBUG_NAME, &luid))
            return false;
        
        tp.PrivilegeCount = 1;
        tp.Privileges[0].Luid = luid;
        tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED; // Aktiverar privilegiet

        // Justerar processens privilegier
        if (!AdjustTokenPrivileges(token_handle, FALSE, &tp, sizeof(TOKEN_PRIVILEGES), nullptr, nullptr))
            return false;

        return GetLastError() == ERROR_SUCCESS; // Returnerar true om operationen lyckades (inget väntande fel)
    }
}
```

### 8. `process.hpp`

Detta är en av de mest kritiska komponenterna i biblioteket och innehåller lågnivåimplementeringen för att interagera med Windows-processer. Den kapslar in de komplexa operationerna för att skapa spelprocessen, allokera minne, skriva data och tekniken för DLL-injektion genom att skapa fjärrtrådar.

- **`Process_Info` struct:** En intern struktur som lagrar `Unique_Resource`s för processens `HANDLE` (`process_handle`) och huvudtrådens `HANDLE` (`thread_handle`) i spelet. Inkluderar en `Resume()`-metod för att återaktivera spelets huvudtråd när injektionen är klar.
- **`Injection_Status` enum class:** Definierar en detaljerad lista över möjliga resultat för DLL-injektionsoperationen, vilket möjliggör en exakt diagnos av fel.
- **`Create_Game_Process`:**
   - Använder `CreateProcessW`-funktionen från Windows API för att starta den körbara filen `gta_sa.exe`.
   - Det är grundläggande att processen skapas med `CREATE_SUSPENDED`-flaggan (inkluderad i `Constants::PROCESS_CREATION_FLAGS`). Detta säkerställer att spelet pausas omedelbart efter att det har skapats, innan någon kod exekveras, vilket gör att DLL-injektionen kan ske i ett säkert tillstånd.
   - Returnerar en `std::optional<Process_Info>` (för C++17+) eller en `std::unique_ptr<Process_Info>` (för C++14), som innehåller de inkapslade handtagen för processen och tråden.
- **`Inject_DLL`:**
   - Implementerar standardtekniken för DLL-injektion via `CreateRemoteThread`:
      1. **Hämtning av Adress:** Med hjälp av konstanterna från `constants.hpp`, lokaliseras adressen till funktionen `LoadLibraryW` (från `kernel32.dll`), som Windows använder för att ladda dynamiska bibliotek.
      2. **Minnesallokering:** `VirtualAllocEx` används för att reservera ett block av virtuellt minne inom spelprocessen (`gta_sa.exe`). Detta block är dimensionerat för att innehålla den fullständiga sökvägen till DLL:en som ska injiceras.
      3. **Skrivning av Sökväg:** Sökvägen till DLL:en (t.ex. `L"C:\\sökväg\\till\\samp.dll"`) kopieras sedan till det fjärrallokerade minnet i spelprocessen via `WriteProcessMemory`.
      4. **Skapande av Fjärrtråd:** `CreateRemoteThread` startar en ny tråd i spelprocessens kontext. Ingångspunkten för denna tråd är adressen till `LoadLibraryW`, och argumentet som skickas är adressen till DLL-sökvägssträngen som vi just skrev.
      5. **Övervakning:** Exekveringen av fjärrtråden övervakas av `WaitForSingleObject` tills den är klar eller `DLL_INJECTION_TIMEOUT_MS` uppnås.
      6. **Framgångskontroll:** `GetExitCodeThread` används för att kontrollera returvärdet från fjärrtråden. Om `LoadLibraryW` lyckades, returnerar den basadressen för den laddade DLL:en (ett värde som inte är noll).
      7. **Rensning:** Minnet som allokerats i den fjärrstyrda processen frigörs med `VirtualFreeEx`.
   - Returnerar en `Injection_Status` som indikerar framgång eller den specifika typen av fel vid injektionen.

```cpp
// Exempel på relevant avsnitt från process.hpp
class Process {
public:
    struct Process_Info {
        Resource_Handle::Unique_Resource<HANDLE, std::function<void(HANDLE)>> process_handle; // Processhandtag med RAII-hantering
        Resource_Handle::Unique_Resource<HANDLE, std::function<void(HANDLE)>> thread_handle; // Trådhandtag med RAII-hantering

        bool Resume() { // Återupptar exekveringen av spelets huvudtråd
            return thread_handle && ResumeThread(thread_handle.get()) != static_cast<DWORD>(-1);
        }
    };
    
    enum class Injection_Status { // Detaljerade statuskoder för DLL-injektion
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

    // Skapar spelprocessen i suspenderat tillstånd
    std::optional<Process_Info> Create_Game_Process(const std::wstring& game_path, std::wstring& command_args, const std::wstring& working_dir) {
        // ... Logik för CreateProcessW med CREATE_SUSPENDED ...
    }
    
    SAMP_INJECTOR_NODISCARD // Säkerställer att returvärdet används
    Injection_Status Inject_DLL(HANDLE process, const std::wstring& DLL_path) {
        static const LPVOID load_library_addr = reinterpret_cast<LPVOID>(GetProcAddress(GetModuleHandleW(Constants::KERNEL32_DLL), Constants::LOAD_LIBRARY_FUNC));

        if (!load_library_addr)
            return Injection_Status::LOADLIBRARY_ADDRESS_FAILED;

        LPVOID remote_memory = VirtualAllocEx(process, nullptr, (DLL_path.length() + 1) * sizeof(wchar_t), Constants::MEMORY_ALLOCATION_TYPE, Constants::MEMORY_PROTECTION);

        if (!remote_memory)
            return Injection_Status::ALLOCATION_FAILED;

        auto memory_guard = Resource_Handle::Unique_Resource<LPVOID, std::function<void(LPVOID)>>(remote_memory, [process](LPVOID ptr) {
            if (ptr)
                VirtualFreeEx(process, ptr, 0, MEM_RELEASE); // Frigör minnet i den fjärrstyrda processen
        });

        if (!WriteProcessMemory(process, remote_memory, DLL_path.c_str(), (DLL_path.length() + 1) * sizeof(wchar_t), nullptr))
            return Injection_Status::WRITE_FAILED;

        HANDLE remote_thread = CreateRemoteThread(process, nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(load_library_addr), remote_memory, 0, nullptr);

        if (!remote_thread)
            return Injection_Status::THREAD_CREATION_FAILED;

        auto thread_guard = Resource_Handle::Make_Unique_Handle(remote_thread); // Säker hantering av den fjärrstyrda trådens handtag

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

Denna header definierar klassen `Injector_Core`, som fungerar som bibliotekets kommandocentral. Den orkestrerar den logiska sekvensen av injektionsoperationer och kopplar samman modulerna för inmatningsvalidering, privilegiehantering och processmanipulation. Det är här det fullständiga arbetsflödet för injektionen definieras.

- **`Injector_Core`:** Konstruktorn för denna klass är den punkt där `Privileges::Enable_Debug_Privilege()` anropas. Detta säkerställer att applikationsprocessen har de nödvändiga privilegierna för att utföra DLL-injektionsoperationer innan någon annan kritisk logik exekveras.
- **`Initialize_Game`:**
   1. **Omfattande Validering:** Börjar med att anropa valideringsfunktionerna (`Validation::Validate_Port`, `Validation::Validate_Nickname`, `Validation::Validate_Files`) för att säkerställa att alla parametrar och nödvändiga resurser är i ordning. Om någon validering misslyckas rapporteras ett fel omedelbart.
   2. **Förberedelse av Argument:** Bygger den fullständiga kommandoraden (`std::wstring`) som kommer att skickas till `gta_sa.exe`, med smeknamn, IP, port och lösenord.
   3. **Skapande av Suspenderad Process:** Anropar `Process::Create_Game_Process` för att starta `gta_sa.exe` i ett suspenderat tillstånd, och erhåller handtagen för processen och huvudtråden.
   4. **Injektion av `samp.dll`:** Anropar `Inject_DLL_With_Status_Check` för att injicera `samp.dll` i spelprocessen. Denna wrapper-funktion ansvarar också för att tolka den returnerade `Injection_Status` och visa informativa felmeddelanden.
   5. **Villkorlig Injektion av `omp-client.dll`:** Om `inject_type` är `Types::Inject_Type::OMP`, injiceras `omp-client.dll` på samma sätt som `samp.dll`.
   6. **Återupptagande av Spelet:** Efter att alla injektioner har lyckats anropas `process_info.Resume()` för att låta spelets huvudtråd fortsätta sin exekvering.
   7. **Felhantering i Cykeln:** Eventuella fel i något av dessa kritiska steg kommer att resultera i ett anrop till `Error_Utils::Show_Error`, vilket ger tydlig feedback till användaren och säkerställer att processen avslutas korrekt (handtagen frigörs automatiskt av `Unique_Resource`s).
- **`Build_Command_Args`:** En hjälpfunktion som organiserar och sammanfogar kommandoradsargumenten och lägger till citattecken där det behövs för parametrar som innehåller mellanslag.
- **`Inject_DLL_With_Status_Check`:** En privat funktion som fungerar som en omslutning för `Process::Inject_DLL`. Den mappar de olika `Injection_Status`-värdena till förståeliga felmeddelanden, vilket underlättar felhantering och kommunikation med användaren.

```cpp
// Exempel på relevant avsnitt från injector_core.hpp
namespace Injector {
    class Injector_Core {
    public:
        Injector_Core() { // Konstruktorn aktiverar felsökningsprivilegiet
            Privileges::Enable_Debug_Privilege();
        }

        bool Initialize_Game(Types::Inject_Type inject_type, std::wstring_view folder, std::wstring_view nickname, std::wstring_view ip, std::wstring_view port, std::wstring_view password) {
            std::wstring error_message;

            // Sekvens av inmatningsvalideringar
            if (!Validation::Validate_Port(port, error_message))
                return (Error_Utils::Show_Error(error_message, inject_type), false);
            // ... andra valideringar ...

            // Bygger kommandoradsargumenten
            std::wstring args = Build_Command_Args({
                Command_Arg{Constants::CMD_ARG_NICKNAME, std::wstring(nickname)},
                // ... andra argument ...
            });

            Process process_core;
            // Skapar spelprocessen i suspenderat tillstånd
            auto process_info_opt = process_core.Create_Game_Process(game_path, args, std::wstring(folder));

            if (!process_info_opt)
                return false;

            auto& process_info = *process_info_opt;

            // Injicerar samp.dll och, villkorligt, omp-client.dll
            if (!Inject_DLL_With_Status_Check(process_core, process_info.process_handle.get(), Constants::SAMP_DLL_NAME, samp_DLL_path.wstring(), inject_type))
                return false;
            
            if (inject_type == Types::Inject_Type::OMP) {
                if (!Inject_DLL_With_Status_Check(process_core, process_info.process_handle.get(), Constants::OMP_DLL_NAME, omp_DLL_path.wstring(), inject_type))
                    return false;
            }
            
            // Återupptar spelets huvudtråd
            if (!process_info.Resume())
                return (Error_Utils::Show_Error(L"Failed to resume the game process thread: " + Error_Utils::Get_System_Error_Message(GetLastError()), inject_type), false);

            return true;
        }
    };
}
```

### 10. `injector.hpp`

Denna header fungerar som bibliotekets huvudfasad (`Facade`) och erbjuder en förenklad ingångspunkt för alla applikationer som vill använda injektionsfunktionaliteten. Den abstraherar den interna komplexiteten i `Injector_Core` till en enda och bekväm funktion.

- **`Initialize_Game`:**
   - Denna statiska funktion är bibliotekets publika gränssnitt.
   - Först validerar den `inject_type_str` (om det är `L"samp"` eller `L"omp"`) och konverterar den till `enum class Types::Inject_Type`. Vid en ogiltig sträng visas ett fel och funktionen avslutas.
   - Därefter skapar den en instans av `Injector::Injector_Core`.
   - Slutligen delegerar den exekveringen av huvudlogiken till `Injector_Core::Initialize_Game`, där hela processen för validering, processkapande och DLL-injektion orkestreras.

```cpp
// Exempel på relevant avsnitt från injector.hpp
// Det publika gränssnittet för att starta spelet
#if defined(SAMP_INJECTOR_CXX_MODERN)
inline bool Initialize_Game(std::wstring_view inject_type, std::wstring_view folder, std::wstring_view nickname, std::wstring_view ip, std::wstring_view port, std::wstring_view password) {
#elif defined(SAMP_INJECTOR_CXX_14)
inline bool Initialize_Game(const std::wstring& inject_type, const std::wstring& folder, const std::wstring& nickname, const std::wstring& ip, const std::wstring& port, const std::wstring& password) {
#endif
    Types::Inject_Type type;

    // Konverterar injektionstypsträngen till motsvarande enum
    if (inject_type == Constants::INJECT_TYPE_SAMP)
        type = Types::Inject_Type::SAMP;
    else if (inject_type == Constants::INJECT_TYPE_OMP)
        type = Types::Inject_Type::OMP;
    else
        // Visar fel om injektionstypen är ogiltig
        return (Error_Utils::Show_Error(L"Ogiltigt injektionsläge. Använd 'samp' eller 'omp'.", Types::Inject_Type::SAMP), false);

    Injector::Injector_Core injector; // Skapar en instans av injektionskärnan

    // Delegerar huvudlogiken till Injector_Core
    return injector.Initialize_Game(type, folder, nickname, ip, port, password);
}
```

## Den Detaljerade Injektionsprocessen

Den centrala funktionaliteten i detta bibliotek är att orkestrera en exakt sekvens av operationer för att injicera SA-MP- eller OMP-klientens DLL:er i GTA:SA-processen. Denna cykel är noggrant planerad för att säkerställa stabilitet och kompatibilitet.

### 1. Initieringsbegäran

Processen börjar med anropet till den globala funktionen `Initialize_Game` (`injector.hpp`), som fungerar som den primära kontaktpunkten för applikationen som använder biblioteket. Denna funktion tar emot alla avgörande parametrar, såsom önskad injektionstyp (SA-MP eller OMP), spelkatalogen och serveranslutningsdata (smeknamn, IP, port, lösenord).

### 2. Förberedelse av Miljön

När `Initialize_Game`-funktionen anropas skapas en instans av `Injector::Injector_Core`. I konstruktorn för denna klass (`injector_core.hpp`) utförs det första och väsentliga steget för att konfigurera miljön: höjning av privilegier.

> [!NOTE]
> `Privileges::Enable_Debug_Privilege()`: Detta anrop (`privileges.hpp`) ger applikationsprocessen `SE_DEBUG_NAME`-privilegiet. Detta privilegium är avgörande, eftersom det tillåter applikationen att utföra lågnivåoperationer på andra Windows-processer, som att läsa och skriva till deras minne och skapa fjärrtrådar – grundläggande åtgärder för DLL-injektionstekniken.

### 3. Integritets- och Parameterkontroll

Med justerade privilegier fortsätter `Injector_Core::Initialize_Game`-metoden med en serie rigorösa valideringar. Detta är en förebyggande fas som minimerar risken för fel i senare steg och ger omedelbar feedback till användaren.

- **Portvalidering:** `Validation::Validate_Port` kontrollerar att anslutningsportnumret är korrekt formaterat och ligger inom intervallet `1` till `65535` (`constants.hpp`).
- **Smeknamnsvalidering:** `Validation::Validate_Nickname` säkerställer att spelarens smeknamn inte är tomt och inte överskrider gränsen på `23` tecken.
- **Kontroll av nödvändiga filer:** `Validation::Validate_Files` inspekterar spelkatalogen för att bekräfta närvaron av `gta_sa.exe`, `samp.dll` och, om injektionen är av typen OMP, även `omp-client.dll`.

> [!WARNING]
> Eventuella fel i detta steg resulterar i att en `MessageBox` med ett detaljerat felmeddelande (`error_utils.hpp`) omedelbart visas och injektionsprocessen avbryts. Detta förhindrar meningslösa försök att fortsätta med en ogiltig konfiguration.

### 4. Förberedelse av Argument för Spelet

Efter en lyckad validering ansvarar `Injector_Core::Build_Command_Args`-funktionen för att bygga den formaterade kommandoraden som kommer att skickas till `gta_sa.exe`. Denna kommandorad inkluderar alla nödvändiga parametrar för att SA-MP/OMP-klienten automatiskt ska ansluta till en server, såsom `-n "smeknamn" -h "IP" -p "Port" -z "Lösenord"`.

### 5. Initiering av Spelprocessen (Suspenderad)

`Process`-komponenten (`process.hpp`) får sedan i uppdrag att starta GTA:SA:s körbara fil.

> [!IMPORTANT]
> `Process::Create_Game_Process`-funktionen använder `CREATE_SUSPENDED`-flaggan (`constants.hpp`) när den anropar Windows API `CreateProcessW`. Detta är ett kritiskt designmått: spelet laddas i minnet och dess huvudtråd skapas, men dess exekvering **pausas**. Detta skapar en kontrollerad och stabil miljö, idealisk för injektion av DLL:er, innan spelet kan initiera sina egna försvar eller interna logiker. Processens och trådens `handles` erhålls och hanteras säkert via `Resource_Handle::Unique_Resource`.

### 6. Injektion av SA-MP-biblioteket (`samp.dll`)

Med spelprocessen i ett suspenderat tillstånd kan injektionen av `samp.dll` utföras säkert. `Injector_Core::Inject_DLL_With_Status_Check`-metoden delegerar denna uppgift till `Process::Inject_DLL`, som utför följande steg i `remote thread injection`-tekniken:

1. **Lokalisering av `LoadLibraryW`-funktionen:** Adressen till `LoadLibraryW`-funktionen identifieras. Denna operation använder konstanterna `Constants::KERNEL32_DLL` och `Constants::LOAD_LIBRARY_FUNC` för att få ett `handle` till `kernel32.dll` och sedan lokalisera adressen till funktionen för dynamisk biblioteksladdning.
2. **Allokering av Fjärrminne:** `VirtualAllocEx` används för att reservera ett minnesblock i det virtuella adressutrymmet för `gta_sa.exe`-processen (som är suspenderad). Storleken på detta block är tillräcklig för att lagra den fullständiga sökvägen till `samp.dll`.
3. **Skrivning av DLL-sökvägen:** Den fullständiga sökvägen till `samp.dll`-filen skrivs till detta nyligen allokerade fjärrminne med `WriteProcessMemory`.
4. **Skapande av Fjärrtråd:** `CreateRemoteThread` anropas för att skapa en ny tråd inom `gta_sa.exe`-processen. Ingångspunkten för denna nya tråd är adressen till `LoadLibraryW`, och argumentet den tar emot är pekaren till sökvägen till DLL:en som vi just skrev.
5. **Övervakning av Injektionen:** Exekveringen av fjärrtråden övervakas av `WaitForSingleObject` under en period som definieras av `Constants::DLL_INJECTION_TIMEOUT_MS`.
6. **Verifiering av Resultat:** Fjärrtrådens slutkod hämtas via `GetExitCodeThread`. Ett returvärde som inte är noll indikerar att `LoadLibraryW` lyckades ladda `samp.dll`.

> [!WARNING]
> Vid eventuella fel under injektionen av `samp.dll` visas ett specifikt felmeddelande (`error_utils.hpp`), injektionsprocessen avbryts och resurserna frigörs.

### 7. Injektion av OMP-biblioteket (`omp-client.dll`) - Villkorlig

Om den specificerade injektionstypen är `OMP`, upprepas de detaljerade stegen i punkt 6 för `omp-client.dll`.

> [!TIP]
> Injektionen av `omp-client.dll` sker alltid efter en lyckad injektion av `samp.dll`. Detta beror på att Open Multiplayer-klienten bygger på den infrastruktur som tillhandahålls av `samp.dll`.

### 8. Aktivering av Spelet

Slutligen, om alla injektioner har slutförts framgångsrikt, anropas `process_info.Resume()`-metoden. Detta anrop exekverar `ResumeThread` på `gta_sa.exe`:s huvudtråd. I detta ögonblick aktiveras spelet och startar sin normala exekvering, men redan med SA-MP/OMP-DLL:erna laddade i sitt minne och med anslutningsparametrarna konfigurerade, vilket möjliggör en automatiserad anslutning till servern.

> [!WARNING]
> Om återupptagandet av speltråden misslyckas, presenteras ett sista felmeddelande för användaren.

## Diagnostik av Fel och Problem

Biblioteket är noggrant utformat för att tydligt kommunicera eventuella problem som kan uppstå under start- och injektionsprocessen. Vid varje felpunkt presenteras en `MessageBox` med en detaljerad beskrivning för användaren, ofta kompletterad med felmeddelanden från operativsystemet.

### Valideringsfel vid Inmatning

Dessa fel upptäcks i den inledande fasen (`validation.hpp`), innan någon lågnivåinteraktion med systemet, och indikerar problem med de data som tillhandahållits av användaren eller med miljökonfigurationen.

#### Ogiltigt Användarnamn

- **Felmeddelande (Exempel 1):** `"Nickname cannot be empty. Please provide a valid nickname."`
- **Felmeddelande (Exempel 2):** `"Nickname length exceeds the maximum allowed of 23 characters. Please use a shorter nickname."`
- **Orsak:** Det angivna användarnamnet (`nickname`) är tomt eller överskrider den maximala gränsen på 23 tecken som tillåts av SA-MP/OMP-klienterna.
- **Lösning:** Användaren måste ange ett giltigt användarnamn som respekterar längdkraven.

#### Ogiltig Anslutningsport

- **Felmeddelande (Exempel 1):** `"Invalid port format. The port must be a numeric value. Please provide a valid integer for the port."`
- **Felmeddelande (Exempel 2):** `"The specified port number (70000) is outside the valid range of 1 to 65535. Please provide a valid port."`
- **Orsak:** Värdet som angetts för porten är inte ett heltal eller ligger utanför det giltiga intervallet (1 till 65535).
- **Lösning:** Användaren måste ange ett giltigt portnummer inom det specificerade intervallet.

#### Nödvändiga Resurser Saknas

- **Felmeddelande (Exempel 1):** `"Game executable not found. Please ensure 'gta_sa.exe' exists at the specified path: C:\Games\GTA San Andreas\gta_sa.exe"`
- **Felmeddelande (Exempel 2):** `"SA-MP library not found. Please ensure 'samp.dll' exists at the specified path: C:\Games\GTA San Andreas\samp.dll"`
- **Felmeddelande (Exempel 3, för OMP):** `"OMP library not found. Please ensure 'omp-client.dll' exists at the specified path for OMP injection: C:\Games\GTA San Andreas\omp-client.dll"`
- **Orsak:** En eller flera avgörande filer (`gta_sa.exe`, `samp.dll`, `omp-client.dll`) hittades inte i den specificerade spelkatalogen.
- **Lösning:** Kontrollera sökvägen till spelmappen och se till att alla nödvändiga filer finns och är tillgängliga.

### Problem med Processhantering

Dessa fel uppstår när biblioteket försöker starta spelets körbara fil (`gta_sa.exe`).

#### Svårigheter att Starta Spelprocessen

- **Felmeddelande (Exempel):** `"Failed to create game process. Ensure 'gta_sa.exe' is not running and you have sufficient permissions to execute the file. System Error: Access is denied."`
- **Orsak:**
   - **Körbar fil i användning:** `gta_sa.exe` kan redan vara igång, eller så finns det en blockering från operativsystemet som förhindrar skapandet av en ny instans.
   - **Otillräckliga behörigheter:** Applikationen kanske inte har tillräckliga behörigheter för att starta `gta_sa.exe` eller för att komma åt filen.
   - **Körbar fil korrupt:** Även om den grundläggande valideringen kontrollerar filens existens, kan den vara korrupt eller oåtkomlig.
- **Lösning:** Se till att ingen instans av `gta_sa.exe` är aktiv. Försök att köra din applikation som administratör. Kontrollera integriteten hos `gta_sa.exe`-filen.

### Problem med DLL-injektion

Dessa är de mest kritiska och detaljerade felen, som inträffar under försöket att injicera `samp.dll` eller `omp-client.dll` i den suspenderade spelprocessen. Felmeddelandena börjar vanligtvis med `"Failed to inject <DLL_NAME>:\n"` och följs av en specifik beskrivning och en systemfelkod.

#### Kan inte hitta `LoadLibraryW`

- **Felmeddelande (Del):** `"Failed to find the address of LoadLibraryW in kernel32.dll."`
- **Orsak:** `LoadLibraryW`-funktionen, ett grundläggande Windows API för dynamisk laddning av DLL:er, kunde inte hittas i `kernel32.dll`. Detta är ett extremt sällsynt lågnivåproblem som tyder på en möjlig korruption av operativsystemet eller en mycket ovanlig körtidsmiljö.
- **Lösning:** En omstart av systemet kan lösa problemet. Om det kvarstår kan det indikera ett allvarligare problem med Windows-installationen.

#### Misslyckad Allokering av Fjärrminne

- **Felmeddelande (Del):** `"Failed to allocate memory in the target process (VirtualAllocEx). System Error: Not enough storage is available to process this command."`
- **Orsak:** Biblioteket kunde inte allokera ett minnesblock i `gta_sa.exe`-processens virtuella adressutrymme.
   - **Behörigheter:** Din applikation kanske inte har tillräckliga behörigheter för att ändra minnesutrymmet för en annan process.
   - **Processkydd:** Säkerhetsmekanismer i operativsystemet eller anti-cheat-programvara kan blockera minnesallokering i externa processer.
- **Lösning:** Kör din applikation som administratör. Kontrollera om säkerhetsprogram (antivirus, anti-cheat) stör och, om möjligt, inaktivera dem tillfälligt för att testa.

#### Oförmåga att Skriva Data till Processen

- **Felmeddelande (Del):** `"Failed to write DLL path to process memory (WriteProcessMemory). System Error: Access is denied."`
- **Orsak:** Minne allokerades i spelprocessen, men biblioteket kunde inte skriva DLL-sökvägen till den platsen.
   - **Behörigheter/Skydd:** Liksom vid misslyckad minnesallokering kan det vara ett problem med skrivbehörighet eller ett aktivt minnesskydd.
- **Lösning:** Samma lösningar som för misslyckad minnesallokering gäller.

#### Misslyckande vid Skapande av Injektionstråd

- **Felmeddelande (Del):** `"Failed to create remote thread (CreateRemoteThread). System Error: The parameter is incorrect."`
- **Orsak:** `CreateRemoteThread` API misslyckades med att starta en ny tråd i `gta_sa.exe`-processen för att anropa `LoadLibraryW`.
   - **Säkerhet:** Många anti-cheat-system och OS-skydd övervakar och blockerar skapandet av fjärrtrådar, eftersom det är en vanlig injektionsteknik.
   - **Processens Tillstånd:** Spelprocessen kan vara i ett instabilt tillstånd som förhindrar skapandet av trådar.
- **Lösning:** Inaktivera tillfälligt all anti-cheat- eller antivirusprogramvara. Försök att köra applikationen som administratör.

#### Tidsgräns Överskriden eller Fel vid Väntan på Injektion

- **Felmeddelande (Del):** `"Timeout or error waiting for remote thread (WaitForSingleObject). System Error: The wait operation timed out."`
- **Orsak:** Fjärrtråden (som anropar `LoadLibraryW`) slutförde inte sin exekvering inom den fastställda tidsgränsen (10 sekunder).
   - **Frysning:** `LoadLibraryW` kan ha hängt sig, tagit för lång tid eller ha blivit avlyssnad/blockerad.
- **Lösning:** Detta kan indikera att DLL:en har svårt att ladda eller att något hindrar den. Att kontrollera systemloggar eller SA-MP/OMP:s egna loggar (om tillgängliga) kan ge fler ledtrådar.

#### Internt Fel i DLL-injektionen

- **Felmeddelande (Del):** `"LoadLibraryW call failed in the target process. The DLL might be corrupt, missing dependencies, or blocked by security software."`
- **Orsak:** Fjärrtråden slutfördes, men returvärdet från `LoadLibraryW` var `0` (eller `NULL`), vilket indikerar att DLL:en inte laddades framgångsrikt.
   - **Korrupt/Saknad DLL:** DLL:en kan ha flyttats, tagits bort eller skadats efter den initiala valideringen.
   - **Saknade Beroenden:** `samp.dll` eller `omp-client.dll` kan ha beroenden (andra DLL:er) som inte finns i spelkatalogen eller i systemets `PATH`.
   - **Internt DLL-fel:** Själva DLL:en kan ha ett internt fel som förhindrar att den laddas.
- **Lösning:** Kontrollera integriteten hos `samp.dll`/`omp-client.dll`-filerna. Se till att alla deras beroenden finns.

### Svårigheter att Återuppta Spelets Körning

Detta är den sista möjliga felpunkten i injektionscykeln.

- **Felmeddelande (Exempel):** `"Failed to resume the game process thread: Invalid handle."`
- **Orsak:** `ResumeThread` API misslyckades med att återaktivera `gta_sa.exe`:s huvudtråd.
   - **Ogiltigt Handtag:** Trådens `handle` kan ha blivit ogiltigt på grund av någon oväntad händelse.
   - **Behörighet:** Applikationen kanske inte har behörighet att ändra trådens tillstånd.
- **Lösning:** Försök att köra applikationen som administratör. Om problemet kvarstår kan det tyda på ett djupare stabilitetsproblem i systemet eller spelprocessen.

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