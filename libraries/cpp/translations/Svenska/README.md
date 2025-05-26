# SA-MP Injector C++

![License](https://img.shields.io/badge/License-MIT-yellow.svg?style=flat)
![C++17](https://img.shields.io/badge/C%2B%2B-17-blue.svg?style=flat&logo=cplusplus)
![Platform](https://img.shields.io/badge/Platform-Windows-0078D6.svg?style=flat&logo=windows)
[![SA-MP | OMP](https://img.shields.io/badge/Support-SA--MP%20%7C%20OMP-yellow)](https://github.com/spc-samp/samp-injector)
![Code Quality](https://img.shields.io/badge/Code%20Quality-High-brightgreen.svg?style=flat)

**SA-MP Injector C++** överskrider definitionen av ett enkelt **DLL-injektionsverktyg**. Det är ett **C++-bibliotek** noggrant utformat för att tillhandahålla en robust och omfattande lösning för programmatisk start av spelet **Grand Theft Auto: San Andreas** (**GTA:SA**) tillsammans med dess multiplayer-klienter, specifikt **SA-MP (San Andreas Multiplayer)** och **OMP (Open Multiplayer)**. Dess primära mål är att förenkla processen för att starta spelet, eliminera komplexiteten i direkt manipulation av operativsystemets processer och överföring av kommandoradsargument.

Utvecklat med syftet att erbjuda maximal flexibilitet och enkel integration, eliminerar detta `header-only`-bibliotek behovet av komplexa förkompileringar, vilket gör det möjligt för utvecklare att direkt inkludera det i sina **C++-projekt**. Det orkestrerar inte bara den **grundläggande injektionen av DLL:er** för multiplayer-klienten (`samp.dll` eller `omp-client.dll`), utan hanterar också intelligent alla väsentliga anslutningsparametrar (**smeknamn**, **IP-adress**, **port** och **lösenord**), och simulerar en naturlig uppstart genom att använda de inbyggda funktionerna i **Windows API**.

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
  - [Grundläggande Koncept och Motivation](#grundläggande-koncept-och-motivation)
    - [Varför Injicera DLL:er?](#varför-injicera-dller)
    - [SA-MP och OMP: Skillnader och Likheter](#sa-mp-och-omp-skillnader-och-likheter)
  - [Bibliotekets Interna Arkitektur: En Djupdykning](#bibliotekets-interna-arkitektur-en-djupdykning)
    - [`constants.hpp`](#constantshpp)
    - [`types.hpp`](#typeshpp)
    - [`string_utils.hpp`](#string_utilshpp)
    - [`error_utils.hpp`](#error_utilshpp)
    - [`resource_handle.hpp`](#resource_handlehpp)
    - [`validation.hpp`](#validationhpp)
    - [`process.hpp`](#processhpp)
    - [`injector_core.hpp`](#injector_corehpp)
    - [`injector.hpp`](#injectorhpp)
  - [Omfattande Användningsexempel](#omfattande-användningsexempel)
    - [1. Förberedelse av Utvecklingsmiljön](#1-förberedelse-av-utvecklingsmiljön)
    - [2. Grundläggande Scenario: Ansluta till en SA-MP Server](#2-grundläggande-scenario-ansluta-till-en-sa-mp-server)
    - [3. Avancerat Scenario: Ansluta till en OMP Server](#3-avancerat-scenario-ansluta-till-en-omp-server)
  - [Hantering av Vanliga Fel och Meddelanden](#hantering-av-vanliga-fel-och-meddelanden)
    - [1. Ogiltig Injektionstyp](#1-ogiltig-injektionstyp)
    - [2. Ogiltig Serverport (Format eller Intervall)](#2-ogiltig-serverport-format-eller-intervall)
      - [2.1. Icke-Numeriskt Portformat](#21-icke-numeriskt-portformat)
      - [2.2. Port Utanför Giltigt Intervall](#22-port-utanför-giltigt-intervall)
    - [3. Ogiltigt Smeknamn (Tomt eller För Långt)](#3-ogiltigt-smeknamn-tomt-eller-för-långt)
      - [3.1. Tomt Smeknamn](#31-tomt-smeknamn)
      - [3.2. För Långt Smeknamn](#32-för-långt-smeknamn)
    - [4. Spelfiler eller DLL:er Hittades Inte](#4-spelfiler-eller-dller-hittades-inte)
      - [4.1. Spel-Exekverbar (`gta_sa.exe`) Hittades Inte](#41-spel-exekverbar-gta_saexe-hittades-inte)
      - [4.2. SA-MP Bibliotek (`samp.dll`) Hittades Inte](#42-sa-mp-bibliotek-sampdll-hittades-inte)
      - [4.3. OMP Bibliotek (`omp-client.dll`) Hittades Inte (endast för OMP-injektion)](#43-omp-bibliotek-omp-clientdll-hittades-inte-endast-för-omp-injektion)
    - [5. Misslyckande vid Skapande av Spelprocess](#5-misslyckande-vid-skapande-av-spelprocess)
    - [6. Misslyckande med minnesallokering i målprocessen](#6-misslyckande-med-minnesallokering-i-målprocessen)
    - [7. Misslyckande med att skriva DLL-sökvägen till processens minne](#7-misslyckande-med-att-skriva-dll-sökvägen-till-processens-minne)
    - [8. Misslyckande med att hitta viktiga systemfunktioner](#8-misslyckande-med-att-hitta-viktiga-systemfunktioner)
      - [8.1. `kernel32.dll` Hittades Inte](#81-kernel32dll-hittades-inte)
      - [8.2. `LoadLibraryA` Hittades Inte](#82-loadlibrarya-hittades-inte)
    - [9. Misslyckande med att skapa fjärrtråd för injektion](#9-misslyckande-med-att-skapa-fjärrtråd-för-injektion)
    - [10. Timeout eller misslyckande med att slutföra injektionen](#10-timeout-eller-misslyckande-med-att-slutföra-injektionen)
    - [11. Misslyckande med att återuppta spelets processtråd](#11-misslyckande-med-att-återuppta-spelets-processtråd)
  - [Licens](#licens)
    - [Användarvillkor](#användarvillkor)
      - [1. Beviljade rättigheter](#1-beviljade-rättigheter)
      - [2. Obligatoriska villkor](#2-obligatoriska-villkor)
      - [3. Upphovsrätt](#3-upphovsrätt)
      - [4. Garantifriskrivning och ansvarsbegränsning](#4-garantifriskrivning-och-ansvarsbegränsning)

## Grundläggande Koncept och Motivation

### Varför Injicera DLL:er?

> [!NOTE] DLL-injektion: Kärnan i dynamisk laddning.
> **DLL-injektion (Dynamic Link Library)** är en metod som används i **Microsoft Windows** operativsystem som möjliggör körning av kod inom minnesutrymmet för en annan pågående process. Det är en kraftfull teknik med många legitima tillämpningar, från felsökning och övervakning av program till modifiering av applikationers beteende för att utöka deras funktionalitet.

I sammanhanget av spel som **GTA San Andreas**, som ursprungligen inte utvecklades med integrerad multiplayer-funktionalitet, är **DLL-injektion** grunden för existensen av multiplayer-klienter som **SA-MP** och **OMP**. Dessa klienter implementeras som **DLL:er** som, när de injiceras i processen för `gta_sa.exe`, tar kontroll, avlyssnar spelfunktioner och etablerar kommunikation med multiplayer-servrar.

Istället för att förlita sig på en extern launcher eller direkt modifiering av spelets exekverbara fil, möjliggör **DLL-injektion** en mer flexibel och programmerbar uppstart, särskilt användbart i miljöer där man vill automatisera processen för att ansluta till specifika servrar med fördefinierade konfigurationer.

### SA-MP och OMP: Skillnader och Likheter

**SA-MP** och **OMP** är de två huvudsakliga multiplayer-plattformarna för **GTA San Andreas**. Båda fungerar som modifieringar av basspelet, och omvandlar det till en massiv online multiplayer-miljö.

- **SA-MP (San Andreas Multiplayer)**: Den ursprungliga och mest etablerade klienten, som används i många år. Dess arkitektur kräver `samp.dll` för att fungera.
- **OMP (Open Multiplayer)**: Ett open-source-projekt, ofta sett som en efterföljare eller ett mer modernt alternativ till **SA-MP**, som erbjuder förbättringar i prestanda, stabilitet och ytterligare funktioner. Det kräver `omp-client.dll`.

Även om de fungerar på liknande sätt (**injicerar en DLL** i processen för **GTA:SA**), är biblioteket **SA-MP Injector C++** noggrant utvecklat för att stödja **båda DLL:erna**, och erkänner deras skillnader i filnamn och gör det möjligt för utvecklaren att välja önskad multiplayer-klient genom en konfigurationsparameter. Detta säkerställer att biblioteket kan användas med det breda utbudet av servrar och projekt baserade på någon av plattformarna.

## Bibliotekets Interna Arkitektur: En Djupdykning

**SA-MP Injector C++** antar en modulär och objektorienterad (där det är tillämpbart) strategi för att hantera komplexiteten i injektionsprocessen. Varje header-fil är en specialiserad modul, ansvarig för en specifik del av den övergripande funktionaliteten, vilket främjar kodens tydlighet, underhållbarhet och utbyggbarhet.

### `constants.hpp`

Denna fil är grunden för alla fasta konfigurationer i biblioteket. Den definierar ett namespace `Constants` för att kapsla in alla litteraler, vilket säkerställer att det inte finns någon förorening av det globala scopet. Användningen av `inline constexpr` är avgörande här: `constexpr` indikerar att värdena utvärderas vid kompilering, vilket optimerar prestanda och säkerställer oföränderlighet, medan `inline` undviker problem med omdefinition när filen inkluderas i flera kompilationsenheter.

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
    inline constexpr const char* LOAD_LIBRARY_FUNC = "LoadLibraryA"; // 'A' för ANSI/8-bit versionen
    
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
    inline constexpr DWORD DLL_INJECTION_TIMEOUT_MS = 10000; // 10 sekunder
    
    // Memory allocation flags for VirtualAllocEx
    inline constexpr DWORD MEMORY_ALLOCATION_TYPE = MEM_COMMIT | MEM_RESERVE;
    inline constexpr DWORD MEMORY_PROTECTION = PAGE_READWRITE; // Behövs för att skriva DLL-sökväg
}
```

> [!TIP]
> Användningen av `wchar_t` för filnamn och titlar på felmeddelanden är en rekommenderad praxis i **Windows-utveckling**. Detta säkerställer kompatibilitet med alla språk och teckenuppsättningar, särskilt användbart för filsökvägar som kan innehålla **Unicode-tecken**. För **API:er** som förväntar sig `char` (som `LoadLibraryA`), utförs konverteringen explicit i `string_utils.hpp`.

### `types.hpp`

En kortfattad men väsentlig modul för att definiera uppräkningen som kategoriserar de stödda injektionstyperna. Detta förbättrar kodens läsbarhet och typsäkerhet, och förhindrar fel med strängar eller magiska heltal.

```cpp
#pragma once

namespace Types {
    // Uppräkningar för stödda injektionstyper
    enum class Inject_Type {
        SAMP, // San Andreas Multiplayer
        OMP // Open Multiplayer
    };
}
```

### `string_utils.hpp`

Att arbeta med **Windows API** kräver ofta konvertering mellan olika strängkodningar. Denna fil tillhandahåller en vital hjälpfunktion för att konvertera strängar från **wide-character** (`std::wstring_view`, används för bibliotekets inmatningar) till **ANSI/8-bit** strängar (`std::string`), som krävs för **WinAPI**-funktioner som fungerar med `char*` (som `CreateProcessA` eller `GetProcAddress`).

```cpp
#pragma once

#include <string>
#include <string_view>
#include <windows.h> // Nödvändigt för WideCharToMultiByte

namespace Utils {
    inline std::string Wide_To_Local_8Bit(std::wstring_view wstr) {
        if (wstr.empty())
            return "";
        
        // Bestämmer storleken som behövs för bufferten för den resulterande strängen i char
        int size = WideCharToMultiByte(CP_ACP, // ANSI Code Page (beroende av det lokala systemet)
            0, // Inga ytterligare flaggor
            wstr.data(), 
            static_cast<int>(wstr.size()), 
            nullptr, // Beräknar storlek, fyller inte bufferten
            0, // Storlek 0, endast för beräkning
            nullptr, // Standardtecken för icke-representerbara tecken
            nullptr); // Pekare till bool som indikerar om ett standardtecken användes

        if (size <= 0) // Returnerar en tom sträng vid fel eller ogiltig storlek
            return "";

        std::string result(size, 0); // Allokerar strängen med den bestämda storleken
        // Utför den faktiska konverteringen, fyller bufferten 'result'
        WideCharToMultiByte(CP_ACP, 
            0, 
            wstr.data(), 
            static_cast<int>(wstr.size()), 
            result.data(), // Destinationsbuffer
            size, // Storlek på destinationsbufferten
            nullptr, 
            nullptr);

        return result;
    }
}
```

> [!IMPORTANT] Kodning Är Viktig!
> `CP_ACP` **(ANSI Code Page)** som används i `WideCharToMultiByte` är systemets standardkodningssida i **Windows**. Detta innebär att konverteringen kan variera beroende på användarens språkinställningar i systemet. För de flesta användningsfall av filnamn och kommandoradsargument i **SA-MP**/**OMP** (som historiskt sett hanterar **ANSI**-strängar bra), är denna metod generellt tillräcklig. Men i scenarier som kräver fullständig **Unicode**-kompatibilitet med externa system eller globala inmatningar, skulle konverteringar till **UTF-8** (`CP_UTF8`) eller andra kodningssidor behövas. För detta projekts omfattning är `CP_ACP` den fungerande standarden.

### `error_utils.hpp`

En grundläggande komponent för bibliotekets användbarhet, ansvarig för att ge **tydlig feedback** till användaren vid fel. Den centraliserar logiken för att hämta systemfelmeddelanden och visa dialogrutor.

```cpp
#pragma once

#include <string>
#include <string_view>
#include <windows.h> // För FormatMessageW och MessageBoxW
//
#include "types.hpp"
#include "constants.hpp"

namespace Utils {
    // Returnerar systemets felmeddelande för en specifik felkod
    inline std::wstring Get_System_Error_Message(DWORD error_code) {
        wchar_t buffer[512] = {0}; // Buffer för meddelandet
        // FormatMessageW fyller bufferten med systemets felbeskrivning
        DWORD result = FormatMessageW(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, 
            nullptr, // Källa till meddelandet (från systemet)
            error_code, 
            0, // Språk (använd standard)
            buffer, 
            512, // Buffertstorlek
            nullptr);
        
        // Om funktionen lyckades, returnera strängen från bufferten; annars en generisk meddelande
        return result ? std::wstring(buffer) : L"Okänt fel (Kod: " + std::to_wstring(error_code) + L")";
    }

    // Visar en felmeddelanderuta till användaren
    inline void Show_Error(std::wstring_view message, Types::Inject_Type injectType) {
        // Väljer dialogrutans titel baserat på injektionstypen
        std::wstring title = (injectType == Types::Inject_Type::SAMP) ? Constants::ERROR_TITLE_SAMP : Constants::ERROR_TITLE_OMP;
        MessageBoxW(nullptr, // Handtag för föräldrafönstret (nullptr för skrivbordet)
            message.data(), 
            title.c_str(), 
            MB_OK | MB_ICONERROR); // OK-knapp och felikon
    }
}
```

> [!NOTE] Formatering av Felmeddelanden
> Funktionen `FormatMessageW` är en kraftfull **Windows API** som hämtar den textuella beskrivningen av en systemfelkod. Den hanterar lokalisering och ger tydliga meddelanden som är avgörande för effektiv **diagnostik**, och omvandlar en `DWORD` som `ERROR_FILE_NOT_FOUND` (2) till `L"Systemet kan inte hitta den angivna filen."`.

### `resource_handle.hpp`

Säker hantering av resurser (som `HANDLE`s i **Windows**) är avgörande för att undvika resursläckor och odefinierade beteenden. Denna fil definierar en `UniqueResource` som använder `std::unique_ptr` och en anpassad funktion för `CloseHandle`. Detta följer principen **RAII (Resource Acquisition Is Initialization)**, vilket säkerställer att `HANDLE`s automatiskt stängs när deras **wrappers** går ur scope, även vid undantag.

```cpp
#pragma once

#include <memory> // För std::unique_ptr
#include <functional> // För std::function
#include <windows.h> // För HANDLE och CloseHandle

namespace Utils {
    // Typalias för en std::unique_ptr som hanterar en HANDLE (eller pekare) med en anpassad deleter
    // T: Typen av resurs som ska hanteras (ex: HANDLE, LPVOID)
    // Deleter: En klass eller lambda som vet hur man frigör resursen
    template<typename T, typename Deleter>
    using UniqueResource = std::unique_ptr<std::remove_pointer_t<T>, Deleter>;

    // Hjälpfunktion för att skapa en instans av UniqueResource för HANDLEs
    // Den antar att T är en handtagstyp och använder CloseHandle som deleter.
    template<typename T>
    inline auto Make_Unique_Handle(T handle) {
        return UniqueResource<T, std::function<void(T)>>(handle, [](T h) {
            // Villkor för att säkerställa att handtaget är giltigt innan det försöker stängas
            // 0 och INVALID_HANDLE_VALUE anses ogiltiga för de flesta handtag
            if (h && h != INVALID_HANDLE_VALUE)
                CloseHandle(h); // Frigör HANDLET från operativsystemet
        });
    }
}
```

> [!IMPORTANT]
> Användningen av `UniqueResource` är en demonstration av bästa praxis i **modernt C++** och säker utveckling i **Windows**. Det förenklar drastiskt hanteringen av livscykler för **handtag**, som, om de inte stängs korrekt, kan leda till minnesläckor eller resursläckor i **kärnan**, vilket påverkar systemets stabilitet över tid.

### `validation.hpp`

Injektionens robusthet börjar med validering av användarens inmatningar och kontroll av filberoenden. Denna modul innehåller funktioner som säkerställer att alla förutsättningar och parametrar är korrekta innan man försöker starta injektionsprocessen, vilket förhindrar mer komplexa fel längre fram.

```cpp
#pragma once

#include <string>
#include <string_view>
#include <filesystem> // För std::filesystem::exists
//
#include "constants.hpp"
#include "types.hpp"
#include "string_utils.hpp" // För Wide_To_Local_8Bit
#include "error_utils.hpp" // För Show_Error

namespace Utils {
    // Validerar om en portsträng är ett giltigt nummer och ligger inom det tillåtna intervallet
    inline bool Validate_Port(std::wstring_view port_str, std::wstring& error_message) {
        try {
            // Försöker konvertera strängen från wide-character till std::string och sedan till int
            int port_num = std::stoi(Wide_To_Local_8Bit(port_str));

            // Kontrollerar om porten ligger inom det giltiga intervallet (1-65535)
            if (port_num < Constants::MIN_PORT || port_num > Constants::MAX_PORT)
                return (error_message = L"Det angivna portnumret (" + std::wstring(port_str) + 
                L") ligger utanför det giltiga intervallet " +  std::to_wstring(Constants::MIN_PORT) + 
                L" till " + std::to_wstring(Constants::MAX_PORT) + 
                L". Ange en giltig port.", false);

            return true;
        }
        catch (...) { // Fångar upp eventuella undantag (som std::invalid_argument för icke-numeriskt)
            return (error_message = L"Ogiltigt portformat. Porten måste vara ett numeriskt värde. Ange ett giltigt heltal för porten.", false);
        }
    }

    // Validerar smeknamnet, kontrollerar att det inte är tomt och att längden är acceptabel
    inline bool Validate_Nickname(std::wstring_view nickname_str, std::wstring& error_message) {
        if (nickname_str.empty())
            return (error_message = L"Smeknamnet får inte vara tomt. Ange ett giltigt smeknamn.", false);
        
        if (nickname_str.size() > Constants::MAX_NICKNAME_LENGTH)
            return (error_message = L"Smeknamnets längd överstiger det maximalt tillåtna på " + 
                std::to_wstring(Constants::MAX_NICKNAME_LENGTH) + 
                L" tecken. Använd ett kortare smeknamn.", false);

        return true;
    }

    // Validerar existensen av kritiska filer (gta_sa.exe, samp.dll, omp-client.dll)
    inline bool Validate_Files(const std::filesystem::path& game_path, 
        const std::filesystem::path& samp_DLL_path, 
        const std::filesystem::path& omp_DLL_path, 
        Types::Inject_Type inject_type) {
        std::wstring error_message_local; // Använder en lokal variabel här innan den skickas till Show_Error
        
        // Kontrollerar existensen av spelets exekverbara fil
        if (!std::filesystem::exists(game_path)) {
            error_message_local = L"Spel-exekverbar hittades inte. Säkerställ att 'gta_sa.exe' finns på den angivna sökvägen: " + game_path.wstring();
            Show_Error(error_message_local, inject_type);
            return false;
        }

        // Kontrollerar existensen av samp.dll (nödvändig för båda injektionstyperna)
        if (!std::filesystem::exists(samp_DLL_path)) {
            error_message_local = L"SA-MP-bibliotek hittades inte. Säkerställ att 'samp.dll' finns på den angivna sökvägen: " + samp_DLL_path.wstring();
            Show_Error(error_message_local, inject_type);

            return false;
        }

        // Om injektionstypen är OMP, kontrollerar existensen av omp-client.dll
        if (inject_type == Types::Inject_Type::OMP && !std::filesystem::exists(omp_DLL_path)) {
            error_message_local = L"OMP-bibliotek hittades inte. Säkerställ att 'omp-client.dll' finns på den angivna sökvägen för OMP-injektion: " + omp_DLL_path.wstring();
            Show_Error(error_message_local, inject_type);

            return false;
        }

        return true; // Alla nödvändiga filer hittades
    }
}
```

> [!NOTE] C++17 `std::filesystem`
> Användningen av `std::filesystem` är ett modernt tillägg i **C++17** som erbjuder ett kraftfullt och plattformsoberoende sätt att interagera med filsystemet. För detta projekt i **Windows** förenklar det hanteringen av sökvägar och kontrollen av filers existens jämfört med äldre **WinAPI**:er.
>
> Säkerställ att din kompilator stöder **C++17** för att använda `std::filesystem`. Du behöver konfigurera ditt projekt för att använda standarden **C++17** (`/std:c++17` i **Visual Studio**).

### `process.hpp`

Detta är den huvudsakliga modulen ansvarig för direkt interaktion med **Windows API:er** på låg nivå för att manipulera processer. Den kapslar in de kritiska operationerna för processkapande och **DLL-injektion**, och hanterar **handtag**, **minne** och **trådar**.

```cpp
#pragma once

#include <string_view>
#include <optional> // För std::optional
#include <functional> // För std::function (används i UniqueResource)
#include <windows.h> // Windows API:er
#include <memory> // För std::unique_ptr
#include <vector> // För std::vector (buffer för args)
//
#include "resource_handle.hpp" // Vår wrapper för HANDLEs
#include "error_utils.hpp" // För Get_System_Error_Message och Show_Error
#include "constants.hpp" // Globala konstanter
#include "types.hpp" // Injektionstyper

class Process {
    public:
        // Konstruktorer/Destruktorer och tilldelningsoperatorer
        // Explicit default och delete för att garantera värdesemantik och move-only.
        Process() = default;
        Process(const Process&) = delete; // Ingen kopiering
        Process& operator=(const Process&) = delete; // Ingen kopieringstilldelning
        Process(Process&&) = default; // Flyttsemantik
        Process& operator=(Process&&) = default; // Flytttilldelning
        ~Process() = default;

        // Struktur för att lagra handtagen för processen och tråden, hanterade av UniqueResource
        struct Process_Info {
            Utils::UniqueResource<HANDLE, std::function<void(HANDLE)>> process_handle;
            Utils::UniqueResource<HANDLE, std::function<void(HANDLE)>> thread_handle;
        };

        // Skapar spelprocessen GTA:SA i ett suspenderat tillstånd
        std::optional<Process_Info> Create_Game_Process(std::string_view game_path, std::string_view command_args, std::string_view working_dir) {
            STARTUPINFOA startup_info{}; // Struktur för processens startinformation
            startup_info.cb = sizeof(STARTUPINFOA); // Anger strukturens storlek

            PROCESS_INFORMATION process_info{}; // Struktur som tar emot information om den nya processen

            // Skapar en muterbar buffer för kommandoradsargumenten.
            // CreateProcessA modifierar kommandoradsbufferten, så std::string_view fungerar inte direkt.
            std::vector<char> args_buffer(command_args.size() + 1); // +1 för nollterminatorn

            if (!command_args.empty()) {
                std::memcpy(args_buffer.data(), command_args.data(), command_args.size());
                args_buffer[command_args.size()] = '\0'; // Säkerställer nollterminator
            }

            // Skapar processen
            bool success = CreateProcessA(game_path.data(), // Namn på den exekverbara modulen
                args_buffer.empty() ? nullptr : args_buffer.data(), // Kommandoradsargument
                nullptr, // Säkerhetsattribut för processen
                nullptr, // Säkerhetsattribut för tråden
                FALSE, // Ärva inte handtag
                Constants::PROCESS_CREATION_FLAGS, // CREATE_SUSPENDED | DETACHED_PROCESS
                nullptr, // Miljö för den nya processen
                working_dir.empty() ? nullptr : working_dir.data(), // Arbetskatalog
                &startup_info, // Startinformation
                &process_info); // Information om den skapade processen

            if (!success) {
                // Om det misslyckades, hämta och visa systemets felmeddelande
                std::wstring error_msg = Utils::Get_System_Error_Message(GetLastError());
                Utils::Show_Error(L"Misslyckades med att skapa spelprocessen. Säkerställ att 'gta_sa.exe' inte körs och att du har tillräckliga behörigheter för att köra filen. Systemfel: " + error_msg, Types::Inject_Type::SAMP); // Använder SAMP som fallback för titeln
                
                return std::nullopt; // Returnerar ett tomt optional
            }

            Process_Info result;
            // Lagrar process- och trådhandtagen i UniqueResource för automatisk hantering
            result.process_handle = Utils::Make_Unique_Handle(process_info.hProcess);
            result.thread_handle = Utils::Make_Unique_Handle(process_info.hThread);

            return result; // Returnerar strukturen med de hanterade handtagen
        }

        // Injicerar en DLL i den fjärrprocessen
        bool Inject_DLL(HANDLE process, std::string_view DLL_path, std::wstring& error_message) {
            // Allokerar minne i den fjärrprocessen för DLL-sökvägen
            LPVOID remote_memory = VirtualAllocEx(process, // Handtag för målprocessen
            nullptr, // Föredragen adress (nullptr för att låta systemet välja)
            DLL_path.size() + 1, // Storlek på sökvägen + nollterminator
            Constants::MEMORY_ALLOCATION_TYPE, // MEM_COMMIT | MEM_RESERVE
            Constants::MEMORY_PROTECTION); // PAGE_READWRITE

            if (!remote_memory)
                return (error_message = L"Misslyckades med att allokera minne i målprocessen. Detta kan bero på otillräckliga behörigheter eller processkyddsmekanismer.", false);

            // Resurshantering för det fjärrallokerade minnet.
            // Frigörs automatiskt när det går ur scope.
            auto memory_guard = Utils::UniqueResource<LPVOID, std::function<void(LPVOID)>>(remote_memory, 
                [process](LPVOID ptr) { // Lambda som deleter
                    if (ptr)
                        VirtualFreeEx(process, ptr, 0, MEM_RELEASE); // Frigör det allokerade minnet
                }
            );

            // Skriver DLL-sökvägen till det fjärrallokerade minnet
            if (!WriteProcessMemory(process, remote_memory, DLL_path.data(), DLL_path.size() + 1, nullptr))
                return (error_message = L"Misslyckades med att skriva DLL-sökvägen till målprocessens minne. Verifiera processbehörigheter och säkerställ att DLL-sökvägen är åtkomlig.", false);

            // Hämtar handtaget för kernel32.dll (som är laddad i injektorprocessen)
            HMODULE kernel32 = GetModuleHandleA(Constants::KERNEL32_DLL);
            
            if (!kernel32)
                return (error_message = L"Misslyckades med att få ett handtag till kernel32.dll. Detta är en viktig systembibliotek och detta fel indikerar ett allvarligt systemproblem.", false);

            // Hämtar adressen till funktionen LoadLibraryA i kernel32.dll.
            // Denna adress är konsekvent mellan processer i samma OS och är nyckeln till injektionen.
            LPVOID load_library_addr = reinterpret_cast<LPVOID>(GetProcAddress(kernel32, Constants::LOAD_LIBRARY_FUNC));

            if (!load_library_addr)
                return (error_message = L"Misslyckades med att hitta adressen till funktionen LoadLibraryA i kernel32.dll. Detta är avgörande för att injicera DLL:en.", false);

            // Skapar en fjärrtråd i målprocessen för att köra LoadLibraryA
            // Argumentet till LoadLibraryA kommer att vara den fjärradressen till DLL-sökvägen
            HANDLE remote_thread = CreateRemoteThread(process, // Handtag för målprocessen
                nullptr, // Säkerhetsattribut för tråden
                0, // Stackstorlek (0 för standard)
                reinterpret_cast<LPTHREAD_START_ROUTINE>(load_library_addr), // Adress till LoadLibraryA
                remote_memory, // Argument till LoadLibraryA (DLL-sökvägen)
                0, // Skapningsflaggor (0 för att starta omedelbart)
                nullptr); // Tråd-ID (nullptr för att inte returnera)

            if (!remote_thread)
                return (error_message = L"Misslyckades med att skapa en fjärrtråd i målprocessen för att utföra DLL-injektionen. Detta kan bero på säkerhetsrestriktioner eller processens tillstånd. Systemfel: " + Utils::Get_System_Error_Message(GetLastError()), false);

            // Resurshantering för handtaget till den fjärrtråden
            auto thread_guard = Utils::Make_Unique_Handle(remote_thread);

            // Väntar på att den fjärrtråden (DLL-injektionen) ska slutföras eller nå en timeout
            DWORD wait_result = WaitForSingleObject(remote_thread, Constants::DLL_INJECTION_TIMEOUT_MS);

            if (wait_result != WAIT_OBJECT_0) {
                return (error_message = L"Timeout eller fel vid väntan på att DLL-injektionen ska slutföras. Systemfel: " + Utils::Get_System_Error_Message(GetLastError()), false);

            // Hämtar utgångskoden för den fjärrtråden.
            // För LoadLibraryA betyder en utgångskod på 0 misslyckande (kunde inte ladda DLL:en).
            DWORD exit_code = 0;

            if (!GetExitCodeThread(remote_thread, &exit_code) || exit_code == 0)
                return (error_message = L"DLL-injektionen misslyckades eller returnerade ett fel. LoadLibrary-anropet kan ha misslyckats i målprocessen.", false);

            return true; // Injektionen lyckades
        }
};
```

> [!NOTE] Robust Design med `std::optional` och RAII
> Modulen `process.hpp` visar en robust och säker design. Funktionen `Create_Game_Process` returnerar en `std::optional<Process_Info>`. Detta gör det möjligt för funktionen att explicit och elegant signalera misslyckanden vid processkapande (genom att returnera ett `std::nullopt`) utan att använda undantag eller tvetydiga felkoder i sitt primära returvärde.
>
> Ännu viktigare är att strukturen `Process_Info` använder `Utils::UniqueResource<HANDLE, std::function<void(HANDLE)>>` för att kapsla in **handtagen** för processen och **tråden**. Detta är ett exempel på mönstret **RAII (Resource Acquisition Is Initialization)**, som garanterar att operativsystemets `HANDLE`s (som `hProcess` och `hThread`) automatiskt stängs via `CloseHandle` när objektet `Process_Info` går ur scope. Detta eliminerar läckor av **handtag**, som är en vanlig källa till instabilitet och överdriven resursförbrukning i **Windows-applikationer** som körs under lång tid.
>
> På liknande sätt, inom funktionen `Inject_DLL`, används `UniqueResource` för att hantera det fjärrallokerade minnet (`VirtualAllocEx`), vilket säkerställer att det frigörs (`VirtualFreeEx`) så snart det inte längre behövs eller vid misslyckande. Denna rigorösa resurshantering bidrar avsevärt till **SA-MP Injector C++**:s tillförlitlighet och stabilitet.

### `injector_core.hpp`

Detta är den orkestrerande klassen som binder samman alla funktioner från de tidigare modulerna. Den koordinerar validering, konstruktion av kommandoradsargument, processkapande och anrop för **DLL-injektion**.

```cpp
#pragma once

#include <string_view>
#include <sstream> // För att bygga strängar med stringstream
#include <filesystem> // För hantering av sökvägar
//
#include "process.hpp" // Funktioner för processkapande/injektion
#include "validation.hpp" // Funktioner för validering av inmatningar
#include "string_utils.hpp" // Funktioner för strängkonvertering
#include "error_utils.hpp" // Funktioner för felhantering
#include "constants.hpp" // Bibliotekets konstanter
#include "types.hpp" // Injektionstyper

namespace Injector {
    class Injector_Core {
        public:
            // Konstruktorer/Destruktorer för flyttsemantik
            Injector_Core() = default;
            Injector_Core(const Injector_Core&) = delete; // Inaktiverar kopiering
            Injector_Core& operator=(const Injector_Core&) = delete; // Inaktiverar kopieringstilldelning
            Injector_Core(Injector_Core&&) = default; // Aktiverar flytt
            Injector_Core& operator=(Injector_Core&&) = default; // Aktiverar flytttilldelning
            ~Injector_Core() = default;

            // Huvudfunktion som orkestrerar initialisering och injektion av spelet
            bool Initialize_Game(Types::Inject_Type inject_type, std::wstring_view folder, 
                std::wstring_view nickname, 
                std::wstring_view ip, 
                std::wstring_view port, 
                std::wstring_view password) {
                namespace fs = std::filesystem; // Alias för std::filesystem

                // Bygger de fullständiga sökvägarna till de väsentliga filerna
                fs::path game_path = fs::path(folder) / Constants::GAME_EXE_NAME; // Ex: C:\GTA\gta_sa.exe
                fs::path samp_DLL_path = fs::path(folder) / Constants::SAMP_DLL_NAME; // Ex: C:\GTA\samp.dll
                fs::path omp_DLL_path = fs::path(folder) / Constants::OMP_DLL_NAME; // Ex: C:\GTA\omp-client.dll

                // 1. Validering av Filer
                if (!Utils::Validate_Files(game_path, samp_DLL_path, omp_DLL_path, inject_type))
                    return false; // Fel har redan visats av valideringsfunktionen
                
                std::wstring error_message_local; // För att ta emot felmeddelanden från valideringar

                // 2. Validering av Port
                if (!Utils::Validate_Port(port, error_message_local))
                    return (Utils::Show_Error(error_message_local, inject_type), false);

                // 3. Validering av Smeknamn
                if (!Utils::Validate_Nickname(nickname, error_message_local))
                    return (Utils::Show_Error(error_message_local, inject_type), false);

                // 4. Konvertering från Wide-char till Local 8-bit (nödvändigt för ANSI API:er)
                std::string nickname_str = Utils::Wide_To_Local_8Bit(nickname);
                std::string ip_str = Utils::Wide_To_Local_8Bit(ip);
                std::string port_str = Utils::Wide_To_Local_8Bit(port);
                std::string password_str = Utils::Wide_To_Local_8Bit(password);
                // Konverterar också sökvägarna till std::string (krävs av CreateProcessA som char*)
                std::string game_path_str = Utils::Wide_To_Local_8Bit(game_path.wstring());
                std::string folder_str = Utils::Wide_To_Local_8Bit(folder);
                std::string samp_DLL_path_str = Utils::Wide_To_Local_8Bit(samp_DLL_path.wstring());
                std::string omp_DLL_path_str = Utils::Wide_To_Local_8Bit(omp_DLL_path.wstring());

                // 5. Konstruktion av Kommandoradsargument
                std::string args = Build_Command_Args(nickname_str, ip_str, port_str, password_str);

                // Instansierar klassen Process för att hantera processoperationer
                Process process_core;
                
                // 6. Skapande av Spelprocessen (Suspenderad)
                auto process_info_opt = process_core.Create_Game_Process(game_path_str, args, folder_str);

                if (!process_info_opt)
                    return false; // Fel har redan visats av funktionen för processkapande

                // Derefererar optional för att få strukturen Process_Info
                auto& process_info = *process_info_opt; 
                std::wstring inject_error_message; // För att ta emot felmeddelanden från injektionen

                // 7. Injektion av samp.dll
                if (!process_core.Inject_DLL(process_info.process_handle.get(), samp_DLL_path_str, inject_error_message))
                    return (Utils::Show_Error(L"Misslyckades med att injicera samp.dll: " + inject_error_message, inject_type), false);

                // 8. Villkorlig injektion av omp-client.dll (endast om det är OMP)
                if (inject_type == Types::Inject_Type::OMP) {
                    if (!process_core.Inject_DLL(process_info.process_handle.get(), omp_DLL_path_str, inject_error_message))
                        return (Utils::Show_Error(L"Misslyckades med att injicera omp-client.dll: " + inject_error_message, inject_type), false);
                }

                // 9. Återuppta Spelprocessen
                // Processen skapades i ett suspenderat tillstånd för att möjliggöra injektion.
                // Nu när DLL:erna har injicerats kan den återupptas.
                if (ResumeThread(process_info.thread_handle.get()) == static_cast<DWORD>(-1))
                    return (Utils::Show_Error(L"Misslyckades med att återuppta spelprocessens tråd: " + Utils::Get_System_Error_Message(GetLastError()), inject_type), false);

                return true; // Framgång i alla steg!
            }
        private:
            // Bygger strängen för kommandoradsargumenten till spelets exekverbara fil
            std::string Build_Command_Args(const std::string& nickname, const std::string& ip, const std::string& port, const std::string& password) {
                std::stringstream command_args_stream; // Använder stringstream för effektiv konstruktion

                // SA-MP och OMP förväntar sig argumenten "-c -n [smeknamn] -h [ip] -p [port]"
                command_args_stream << Constants::CMD_ARG_CONFIG << " " 
                    << Constants::CMD_ARG_NICKNAME << " " << nickname << " " 
                    << Constants::CMD_ARG_HOST << " " << ip << " " 
                    << Constants::CMD_ARG_PORT << " " << port;

                // Lägger till lösenordet endast om det inte är tomt
                if (!password.empty())
                    command_args_stream << " " << Constants::CMD_ARG_PASSWORD << " " << password;

                return command_args_stream.str();
            }
    };
}
```

> [!CAUTION] Dubbel Injektion (SA-MP och OMP)
> Även om processen för **OMP** innebär att injicera `omp-client.dll` *utöver* `samp.dll`, är detta i linje med hur **OMP** vanligtvis fungerar. Klienten **OMP** använder ofta `samp.dll` som **bas** eller **proxy** för vissa funktioner, medan `omp-client.dll` utökar eller skriver över beteenden.
>
> Det är avgörande att **båda DLL:erna** är närvarande och fungerande i spelmappen för att **OMP-injektionen** ska lyckas. Om en misslyckas kan spelet inte starta korrekt eller så laddas inte multiplayer-klienten.

### `injector.hpp`

Detta är bibliotekets gränssnittsfil. Det är den enda filen som slutanvändaren behöver inkludera för att använda **SA-MP Injector C++**. Den fungerar som en wrapper för klassen `Injector::Injector_Core`, och förenklar gränssnittet till en enda global funktion, `Initialize_Game`.

```cpp
#pragma once

#include <string_view>
//
#include "injector_core.hpp" // Huvudklassen med logiken
#include "error_utils.hpp" // För visning av fel (vid ogiltig injektionstyp)
#include "types.hpp" // Uppräkning av typer
#include "constants.hpp" // Konstanter (för namn på injektionstyper)

// Hög nivå-gränssnittet för biblioteket.
// Förenklar användningen genom att endast exponera denna globala funktion.
inline bool Initialize_Game(std::wstring_view inject_type_str, std::wstring_view folder, 
    std::wstring_view nickname, 
    std::wstring_view ip, 
    std::wstring_view port, 
    std::wstring_view password) {
    Types::Inject_Type type; // Variabel för att lagra injektionstypen

    // Konverterar strängen för injektionstypen till enum Inject_Type
    if (inject_type_str == Constants::INJECT_TYPE_SAMP)
        type = Types::Inject_Type::SAMP;
    
    else if (inject_type_str == Constants::INJECT_TYPE_OMP)
        type = Types::Inject_Type::OMP;
    
    else
        // Om strängen för injektionstypen är ogiltig, visa ett fel och returnera falskt
        return (Utils::Show_Error(L"Ogiltigt injektionsläge angivet. Använd 'samp' eller 'omp'.", Types::Inject_Type::SAMP), false); // Använder SAMP som fallback för titeln

    Injector::Injector_Core injector; // Instansierar objektet som innehåller den centrala logiken
    
    // Delegerar anropet till funktionen Initialize_Game i klassen Injector_Core
    return injector.Initialize_Game(type, folder, nickname, ip, port, password);
}
```

> [!NOTE] Design `inline` för `header-only`
> Användningen av nyckelordet `inline` för alla funktioner i denna fil och andra verktygsfiler gör att biblioteket är `header-only`. `inline` föreslår för kompilatorn att funktionens kropp ska infogas direkt vid anropspunkterna, men dess huvudsakliga effekt här är att mildra **One Definition Rule (ODR)** så att funktionen kan definieras i flera `.obj`-filer (vilket skulle hända om flera `.cpp`-filer inkluderar `injector.hpp`). **Linkningssteget** säkerställer att endast en slutlig version finns i den exekverbara filen.

## Omfattande Användningsexempel

För att integrera **SA-MP Injector C++** i ditt projekt, följ instruktionerna och analysera scenarierna nedan.

### 1. Förberedelse av Utvecklingsmiljön

- **C++-Kompilator**: Rekommenderas en kompilator som **stöder C++17**. **Visual Studio** med `vcpkg` (för `std::filesystem`) eller **GCC/Clang (version 17+)** är alternativ.
- **Projektkonfiguration**:
  - Skapa ett nytt **C++-projekt** (t.ex. ett konsolprojekt).
  - Kopiera **alla** `.hpp`-filer från **SA-MP Injector C++** till en mapp som är tillgänglig för ditt projekt (t.ex. i mappen för **headers**).
  - Säkerställ att **C++-standarden** är inställd på **C++17**. Det är viktigt att hålla denna version för maximal kompatibilitet med bibliotek för **SA-MP** och **OMP**. I **Visual Studio**: `Project Properties > Configuration Properties > C/C++ > Language > C++ Language Standard -> "ISO C++17 Standard (/std:c++17)"`
- **Behörigheter**: Din exekverbara fil behöver troligen köras som **Administratör (inte nödvändigtvis)** för att skapa processer och **injicera DLL:er** i systemmiljön. I **Visual Studio** kan detta göras i: `Project Properties > Configuration Properties > Linker > Manifest File > UAC Execution Level -> "requireAdministrator (/LEVEL='requireAdministrator')"`

### 2. Grundläggande Scenario: Ansluta till en SA-MP Server

Detta är det vanligaste användningsfallet, att starta **GTA:SA** och ansluta till en **SA-MP**-server med ett specifikt **smeknamn** och **IP**/**port**.

```cpp
// main.cpp
#include <iostream>
#include <string>
#include <codecvt> // För std::wstring_convert (äldre, men fungerar för detta fall)
#include <locale> // För std::codecvt_utf8_to_utf16
//
#include "injector.hpp" // Den enda nödvändiga inkluderingen från biblioteket!

int Main(int argc, char* argv[]) {
    // Definiera konfigurationsvariablerna
    // Ändra dessa sökvägar och serverdetaljer för att matcha din lokala konfiguration
    std::wstring folder = L"C:\\Spel\\GTA San Andreas"; // Där gta_sa.exe, samp.dll finns
    std::wstring nickname = L"Namn";
    std::wstring ip = L"127.0.0.1"; // Exempel: din lokala server
    std::wstring port = L"7777";
    std::wstring password = L""; // Lämna tomt om inget lösenord

    // Valfritt: Tillåt användaren att ange konfigurationer via kommandoraden (förenklad)
    // För en mer robust hantering av args, använd ett bibliotek för argumentparsning.
    if (argc > 1) {
        // Exempel: om första arg är en sökväg
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

    std::wcout << L"Startar SA-MP..." << std::endl;
    std::wcout << L"Spelmapp: " << folder << std::endl;
    std::wcout << L"Smeknamn: " << nickname << std::endl;
    std::wcout << L"Server: " << ip << L":" << port << std::endl;

    // Anrop till bibliotekets funktion för att starta spelet
    if (Initialize_Game(L"samp", // Injektionstyp: SA-MP
        folder, // Sökväg till spelmappen
        nickname, // Önskat smeknamn
        ip, // Serverns IP
        port, // Serverns port (sträng)
        password)) { // Serverns lösenord (sträng, kan vara tomt)
        std::wcout << L"\n--- SA-MP startades framgångsrikt! ---" << std::endl;
        std::wcout << L"Spelet startades i en separat process." << std::endl;
    }
    else {
        std::wcout << L"\n--- MISSLYCKADES med att starta SA-MP! ---" << std::endl;
        std::wcout << L"Kontrollera de visade felmeddelandena." << std::endl;
    }

    // Håller konsolen öppen för att visa utmatningsmeddelanden
    std::wcout << L"\nTryck på Enter för att stänga programmet." << std::endl;
    std::wcin.ignore();

    return 0;
}
```

**För att kompilera och köra:**

```bash
# Exempel med g++ (Linux/MinGW/MSYS2) - Kräver libstdc++fs för filesystem
# Det är viktigt att säkerställa att verktygs kedjan inte använder en C++-version
# som introducerar inkompatibiliteter i injektionsprocessen.
# Kontrollera dokumentationen för din specifika kompilator för flaggor för binär kompatibilitet (ABI).
g++ main.cpp -o my_launcher -std=c++17 -Wall -lstdc++fs -municode -lkernel32

# Exempel med MSVC (Visual Studio Developer Command Prompt)
# Flaggan '/std:c++17' säkerställer överensstämmelse med C++17.
cl /EHsc /std:c++17 /permissive- /FS /utf-8 main.cpp /link /OUT:my_launcher.exe
```

> [!NOTE] Kompilator och C++ Kompatibilitet
> **SA-MP** och **OMP**, som äldre projekt, är kompilerade med specifika verktyg som definierar deras **Application Binary Interface (ABI)**. Även om detta bibliotek använder **C++17**, **är det avgörande att DLL:erna för SA-MP och OMP som det interagerar med också är kompatibla med din kompilators ABI och den använda versionen av C++ runtime (CRT)**.
>
> Att använda en kompilator eller **C++**-version som är mycket annorlunda än den som användes för att **bygga DLL:erna** för spelet kan leda till subtila problem (t.ex. med minnesallokering eller parameteröverföring) som inte är lätt **diagnostiserbara** och inte resulterar i ett explicit fel från injektorn. Av denna anledning är **C++17 den högsta rekommenderade versionen**, eftersom senare versioner kan introducera förändringar i **ABI** eller **CRT** som inte tolereras av äldre spelmoduler.

### 3. Avancerat Scenario: Ansluta till en OMP Server

För **OMP** är logiken identisk med **SA-MP**, men du anger `L"omp"` som `inject_type` och säkerställer att `omp-client.dll` finns i spelmappen.

```cpp
// main.cpp
#include <iostream>
#include <string>
#include <codecvt> // För std::wstring_convert (äldre, men fungerar för detta fall)
#include <locale> // För std::codecvt_utf8_to_utf16
//
#include "injector.hpp" // Den enda nödvändiga inkluderingen från biblioteket!

int Main() {
    // Definiera konfigurationsvariablerna
    // Ändra dessa sökvägar och serverdetaljer för att matcha din lokala konfiguration
    std::wstring folder = L"C:\\Spel\\GTA San Andreas"; // Där gta_sa.exe, samp.dll och omp-client.dll finns
    std::wstring nickname = L"Namn";
    std::wstring ip = L"127.0.0.1"; // Exempel: din lokala server
    std::wstring port = L"7777";
    std::wstring password = L""; // Lämna tomt om inget lösenord

    // Valfritt: Tillåt användaren att ange konfigurationer via kommandoraden (förenklad)
    // För en mer robust hantering av args, använd ett bibliotek för argumentparsning.
    if (argc > 1) {
        // Exempel: om första arg är en sökväg
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

    std::wcout << L"Startar OMP..." << std::endl;
    std::wcout << L"Spelmapp: " << folder << std::endl;
    std::wcout << L"Smeknamn: " << nickname << std::endl;
    std::wcout << L"Server: " << ip << L":" << port << std::endl;

    // Anrop till bibliotekets funktion för att starta spelet
    if (Initialize_Game(L"omp", // Injektionstyp: OMP
        folder, // Sökväg till spelmappen
        nickname, // Önskat smeknamn
        ip, // Serverns IP
        port, // Serverns port (sträng)
        password)) { // Serverns lösenord (sträng, kan vara tomt)
        std::wcout << L"\n--- OMP startades framgångsrikt! ---" << std::endl;
        std::wcout << L"Spelet startades i en separat process." << std::endl;
    }
    else {
        std::wcout << L"\n--- MISSLYCKADES med att starta OMP! ---" << std::endl;
        std::wcout << L"Kontrollera de visade felmeddelandena." << std::endl;
    }

    // Håller konsolen öppen för att visa utmatningsmeddelanden
    std::wcout << L"\nTryck på Enter för att stänga programmet." << std::endl;
    std::wcin.ignore();

    return 0;
}
```

## Hantering av Vanliga Fel och Meddelanden

**SA-MP Injector C++** prioriterar användbarhet, och en viktig del av detta är att tillhandahålla **tydlig feedback** till användaren vid fel. Felmeddelanden presenteras genom **Windows dialogrutor** (`MessageBoxW`) och kategoriseras efter typen av **injektion (SA-MP eller OMP)** för bättre kontext. Detta säkerställer att du vet exakt vad som gick fel och hur du kan lösa det.

Här är några av de vanligaste felen du kan stöta på och deras sannolika orsaker/lösningar, tillsammans med visuella exempel på hur dessa dialogrutor visas för slutanvändaren:

### 1. Ogiltig Injektionstyp

Om `inject_type` som anges i funktionen `Initialize_Game` inte är `L"samp"` eller `L"omp"`, kommer biblioteket inte att veta vilken multiplayer-klient du avser att initialisera.

![Error 1](screenshots/error_1.png)

- **Visat Felmeddelande**: `"Ogiltigt injektionsläge angivet. Använd 'samp' eller 'omp'."`
- **Orsak**: Det första argumentet i funktionen `Initialize_Game` (`std::wstring_view inject_type`) matchar inte de förväntade värdena `L"samp"` eller `L"omp"`. Det kan vara ett skrivfel, en tom sträng eller ett okänt värde.
- **Lösning**: Kontrollera att `std::wstring_view inject_type_str` är korrekt satt till `L"samp"` eller `L"omp"`. Det är viktigt att använda prefixet `L` för **wide-character (breda tecken)** litteraler för kompatibilitet med bibliotekets konstanter.
    ```cpp
    // Korrekt:
    Initialize_Game(L"samp", /* andra parametrar */);
    Initialize_Game(L"omp", /* andra parametrar */);

    // Felaktigt (orsakar fel):
    // Initialize_Game(L"invalid", /* andra parametrar */);
    // Initialize_Game(L"", /* andra parametrar */);
    ```

### 2. Ogiltig Serverport (Format eller Intervall)

Porten är en viktig numerisk parameter för serveranslutning. Detta fel uppstår om värdet inte kan tolkas som ett giltigt nummer eller ligger utanför det acceptabla intervallet **(1 till 65535)**.

#### 2.1. Icke-Numeriskt Portformat

![Error 2](screenshots/error_2.png)

- **Visat Felmeddelande**: `"Ogiltigt portformat. Porten måste vara ett numeriskt värde. Ange ett giltigt heltal för porten."`
- **Orsak**: Argumentet `port` (`std::wstring_view`) innehåller tecken som inte är numeriska siffror eller kan inte konverteras till ett heltal.
- **Lösning**: Ange en sträng som endast innehåller siffror och representerar ett giltigt heltal.
    ```cpp
    // Korrekt:
    Initialize_Game(/* andra parametrar */, L"7777", /* andra parametrar */);

    // Felaktigt (ogiltigt format):
    // Initialize_Game(/* andra parametrar */, L"port7777", /* andra parametrar */);

    // Felaktigt (ogiltigt):
    // Initialize_Game(/* andra parametrar */, L"invalid", /* andra parametrar */);
    ```

#### 2.2. Port Utanför Giltigt Intervall

![Error 3](screenshots/error_3.png)

- **Visat Felmeddelande**: `"Det angivna portnumret (XXXX) ligger utanför det giltiga intervallet 1 till 65535. Ange en giltig port."` (**XXXX** kommer att vara det värde du försökte använda).
- **Orsak**: Den angivna porten är ett giltigt nummer, men ligger under `1` (reserverat eller ej användbart) eller över `65535` (maximalt gräns för **TCP/UDP-portar**).
- **Lösning**: Ange en port som ligger inom intervallet `1` till `65535`. Vanliga portar för **SA-MP**/**OMP** är `7777` eller `7778`.
    ```cpp
    // Korrekt:
    Initialize_Game(/* andra parametrar */, L"7777", /* andra parametrar */);

    // Felaktigt (utanför intervallet):
    // Initialize_Game(/* andra parametrar */, L"0", /* andra parametrar */); // För lågt
    // Initialize_Game(/* andra parametrar */, L"65536", /* andra parametrar */); // För högt
    // Initialize_Game(/* andra parametrar */, L"-1", /* andra parametrar */); // Negativt värde
    ```

### 3. Ogiltigt Smeknamn (Tomt eller För Långt)

Spelarens **smeknamn** valideras för att säkerställa att spelklienten accepterar det.

#### 3.1. Tomt Smeknamn

![Error 4](screenshots/error_4.png)

- **Visat Felmeddelande**: `"Smeknamnet får inte vara tomt. Ange ett giltigt smeknamn."`
- **Orsak**: Argumentet `nickname` (`std::wstring_view`) angavs som en tom sträng.
- **Lösning**: Säkerställ att smeknamnet inte är tomt.
    ```cpp
    // Korrekt:
    Initialize_Game(/* andra parametrar */, L"Namn", /* andra parametrar */);

    // Felaktigt (tomt):
    // Initialize_Game(/* andra parametrar */, L"", /* andra parametrar */);
    ```

#### 3.2. För Långt Smeknamn

![Error 5](screenshots/error_5.png)

- **Visat Felmeddelande**: `"Smeknamnets längd överstiger det maximalt tillåtna på 20 tecken. Använd ett kortare smeknamn."`
- **Orsak**: Längden på det angivna **smeknamnet** överstiger `Constants::MAX_NICKNAME_LENGTH`, vilket är `20` tecken.
- **Lösning**: Använd ett **smeknamn** som har högst `20` tecken.
    ```cpp
    // Korrekt:
    Initialize_Game(/* andra parametrar */, L"Namn", /* andra parametrar */);

    // Felaktigt (för långt):
    // Initialize_Game(/* andra parametrar */, L"DettaSmeknamnÄrFörLångtOchÖverskriderTjugoTecken", /* andra parametrar */);
    ```

### 4. Spelfiler eller DLL:er Hittades Inte

Detta är en av de vanligaste orsakerna till misslyckanden. Biblioteket kräver att `gta_sa.exe`, `samp.dll` och, för **OMP**, `omp-client.dll` finns på de förväntade platserna.

#### 4.1. Spel-Exekverbar (`gta_sa.exe`) Hittades Inte

![Error 6](screenshots/error_6.png)

- **Visat Felmeddelande**: `"Spel-exekverbar hittades inte. Säkerställ att 'gta_sa.exe' finns på den angivna sökvägen: [fullständig sökväg]"`. Den `[fullständiga sökvägen]` kommer att inkludera mappen och filnamnet.
- **Orsak**: Filen `gta_sa.exe` hittades inte i mappen som angavs i argumentet `folder`.
- **Lösning**:
  1. Kontrollera att `folder` (`std::wstring_view`) pekar på den korrekta installationsmappen för **GTA San Andreas**.
  2. Bekräfta att `gta_sa.exe` finns i den mappen och att dess namn inte har ändrats.

#### 4.2. SA-MP Bibliotek (`samp.dll`) Hittades Inte

![Error 7](screenshots/error_7.png)

- **Visat Felmeddelande**: `"SA-MP-bibliotek hittades inte. Säkerställ att 'samp.dll' finns på den angivna sökvägen: [fullständig sökväg]"`.
- **Orsak**: Filen `samp.dll` hittades inte i mappen som angavs i argumentet `folder`. **Denna DLL** är ett krav för **båda** injektionstyperna (`samp` och `omp`).
- **Lösning**: Säkerställ att `samp.dll` finns i installationsmappen för **GTA San Andreas**.

#### 4.3. OMP Bibliotek (`omp-client.dll`) Hittades Inte (endast för OMP-injektion)

![Error 8](screenshots/error_8.png)

- **Visat Felmeddelande**: `"OMP-bibliotek hittades inte. Säkerställ att 'omp-client.dll' finns på den angivna sökvägen för OMP-injektion: [fullständig sökväg]"`.
- **Orsak**: Om du angav `L"omp"` som injektionstyp, men filen `omp-client.dll` hittades inte i den angivna mappen.
- **Lösning**: Ladda ner den senaste **OMP**-klienten och säkerställ att `omp-client.dll` (och `samp.dll`) finns i installationsmappen för **GTA San Andreas**.

### 5. Misslyckande vid Skapande av Spelprocess

Detta är ett mer komplext fel eftersom det involverar **operativsystemets behörigheter** och det aktuella tillståndet för `gta_sa.exe`.

![Error 9](screenshots/error_9.png)

- **Visat Felmeddelande**: `"Misslyckades med att skapa spelprocessen. Säkerställ att 'gta_sa.exe' inte körs och att du har tillräckliga behörigheter för att köra filen. Systemfel: [Systemets felmeddelande]"`. Systemets meddelande läggs till av `GetLastError()` (t.ex. `Åtkomst nekad.` eller `Den begärda operationen kräver förhöjning.`).
- **Orsak**: Anropet `CreateProcessA` för att starta `gta_sa.exe` misslyckades. Vanliga orsaker inkluderar:
  - **Process redan igång**: En instans av `gta_sa.exe` är redan aktiv och blockerar en ny körning.
  - **Otillräckliga behörigheter**: Din applikation har inte de nödvändiga privilegierna (t.ex. administratör) för att skapa en process i vissa systemkonfigurationer (**UAC** aktiverat, skyddade mappar, etc.).
  - **Problem med exekverbar**: `gta_sa.exe` kan vara korrupt eller blockerad av ett annat program (t.ex. ett felkonfigurerat antivirusprogram).
- **Lösning**:
  1. Kontrollera Aktivitetshanteraren och säkerställ att ingen instans av `gta_sa.exe` körs. Avsluta någon om det finns.
  2. Kör din applikation som använder biblioteket med **Administratörsprivilegier**. Högerklicka på den exekverbara filen och välj **"Kör som administratör"**.
  3. Om ett **antivirusprogram** eller **säkerhetsprogram** stör, lägg till din applikation och/eller mappen för **GTA:SA** till undantagen i antivirusprogrammet (gör detta med försiktighet och endast om du är säker på filernas integritet).

### 6. Misslyckande med minnesallokering i målprocessen

Biblioteket försöker allokera ett litet minnesutrymme i `gta_sa.exe` för att kopiera **sökvägen till DLL:en**.

![Error 10](screenshots/error_10.png)

- **Visat felmeddelande**: `"Failed to allocate memory in the target process. This might be due to insufficient permissions or process protection mechanisms."`
- **Orsak**: Funktionen `VirtualAllocEx` (används för att allokera minne i en annan process) misslyckades. Detta är mer troligt om:
  - Processen för **GTA:SA** (även om den är i viloläge) har säkerhetsförsvar eller **anti-injektionspatchar** som förhindrar minnesallokering från externa processer.
  - Din applikation saknar de nödvändiga förhöjda behörigheterna för att manipulera minnet i en annan process.
  - (Mindre vanligt) Det finns en extrem brist på virtuellt minne i systemet.
- **Lösning**:
  1. Kör din applikation med **administratörsbehörighet**.
  2. Se till att spelet inte har några modifieringar eller **säkerhetspatchar** som kan blockera försök till injektion eller minnesmanipulation (detta är vanligare i modifierade miljöer eller med vissa tredjeparts anti-fuskverktyg).

### 7. Misslyckande med att skriva DLL-sökvägen till processens minne

Efter att ha allokerat minnet försöker biblioteket kopiera **sökvägen till DLL:en** till det.

![Error 11](screenshots/error_11.png)

- **Visat felmeddelande**: `"Failed to write DLL path to the target process memory. Verify process permissions and ensure the DLL path is accessible."`
- **Orsak**: Funktionen `WriteProcessMemory` misslyckades med att kopiera **DLL-sökvägens bytes** till det allokerade fjärrminnet i `gta_sa.exe`. Detta pekar vanligtvis på:
  - **Skrivbehörigheter**: Din applikation har inte behörighet att skriva till denna minnesregion eller i processen för **GTA:SA**.
  - **Ogiltigt handtag**: Processens **handtag** (`process_handle`) blev på något sätt ogiltigt mellan allokeringen och skrivningen, vilket är mycket sällsynt på grund av användningen av `UniqueResource` men kan inträffa under extrema systemförhållanden.
  - **Minneskyddsproblem**: Något minnesskydd (antingen från **operativsystemet** eller spelets modifieringar) förhindrade skrivningen.
- **Lösning**: Kör som **administratör**. Kontrollera att `gta_sa.exe` och dess miljö är "rena" från verktyg som kan blockera minnesoperationer.

### 8. Misslyckande med att hitta viktiga systemfunktioner

Dessa är **API:er** som är avgörande för **Windows**; fel här indikerar ett grundläggande problem med operativsystemet eller körningsmiljön.

#### 8.1. `kernel32.dll` Hittades Inte

![Error 12](screenshots/error_12.png)

- **Visat felmeddelande**: `"Failed to obtain a handle to kernel32.dll. This is an essential system library and this error indicates a severe system issue."`
- **Orsak**: `kernel32.dll` är en av de mest grundläggande **DLL:erna** i **Windows**, som innehåller viktiga funktioner som `CreateProcess`, `VirtualAllocEx`, etc. Om `GetModuleHandleA` inte kan få ett **handtag** till den, har operativsystemet mycket allvarliga problem.
- **Lösning**: Detta är ett **kritiskt** fel som sällan orsakas av biblioteket eller din applikation. Det tyder på korruption av systemfiler, allvarliga problem med **Windows**, eller en mycket ovanlig installation av **operativsystemet**. Rekommenderas att köra systemintegritetskontroller (som `sfc /scannow` i **Kommandotolken** som **administratör**) eller, i sista hand, ominstallera **Windows**.

#### 8.2. `LoadLibraryA` Hittades Inte

![Error 13](screenshots/error_13.png)

- **Visat felmeddelande**: `"Failed to find the address of the LoadLibraryA function in kernel32.dll. This is critical for injecting the DLL."`
- **Orsak**: Även om `kernel32.dll` hittades, kunde funktionen `LoadLibraryA` inte lösas via `GetProcAddress`. Även om det är extremt ovanligt, kan det bero på korruption av **DLL-filen** för `kernel32.dll` eller en mycket icke-standardiserad körningsmiljö.
- **Lösning**: Precis som felet med `kernel32.dll` ovan indikerar detta ett allvarligt problem i operativsystemet.

### 9. Misslyckande med att skapa fjärrtråd för injektion

Efter att ha förberett fjärrmiljön och kopierat **sökvägen till DLL:en**, skapas en ny **tråd** i spelets process för att "anropa" `LoadLibraryA`.

![Error 14](screenshots/error_14.png)

- **Visat felmeddelande**: `"Failed to create a remote thread in the target process to execute the DLL injection. This could be due to security restrictions or process state. System Error: [Operativsystemets felmeddelande]"`.
- **Orsak**: Anropet `CreateRemoteThread` misslyckades. Detta fel är vanligt i system med robusta **anti-injektionsförsvar** eller när ett program intensivt övervakar processens beteende:
  - **Säkerhetsmekanismer**: **Anti-fuskverktyg**, **säkerhetsprogram** eller vissa **Windows**-policyer kan upptäcka och blockera försök att skapa **trådar** i tredjepartsprocesser.
  - **Inkonsekvent målprocess**: Om processen för **GTA:SA** är i ett oväntat eller instabilt tillstånd (även om den startades i `CREATE_SUSPENDED`), kan detta påverka möjligheten att skapa **trådar** i den.
- **Lösning**:
  1. Kör din applikation med **administratörsbehörighet**.
  2. Kontrollera att det inte finns några **anti-fuskverktyg**, **aggressiva antivirusprogram** eller **brandväggar** konfigurerade för att inspektera och blockera processmanipulation som kan vara i konflikt. Lägg till din applikation och `gta_sa.exe` till undantag, om tillämpligt (med försiktighet).
  3. Systemets felmeddelande (`GetLastError()`) kan ge ytterligare detaljer för att undersöka den specifika orsaken (ex: **"En process har nekats åtkomst att skapa trådar för andra processer."**).

### 10. Timeout eller misslyckande med att slutföra injektionen

Efter att ha skapat den **fjärrtråden**, väntar injektorn på att den ska slutföra **laddningen av DLL:en**.

![Error 15](screenshots/error_15.png)

- **Visat felmeddelande**: `"Timeout or error waiting for DLL injection to complete. System Error: [Operativsystemets felmeddelande]"`.
- **Orsak**: Den **fjärrtråd** som kör `LoadLibraryA` tog längre tid än `Constants::DLL_INJECTION_TIMEOUT_MS` (10 sekunder) att returnera, eller så misslyckades den och `GetExitCodeThread` returnerade 0. Möjliga orsaker inkluderar:
  - **Problem med den injicerade DLL:en**: `DllMain` i `samp.dll` eller `omp-client.dll` tar för lång tid att köra, innehåller en **oändlig loop**, en **krasch**, eller ett fel som **förhindrar DLL:en** från att laddas korrekt (ex: **saknade DLL-beroenden**).
  - **Tyst blockering**: Ett säkerhetsmekanism kan ha blockerat `LoadLibraryA` men inte meddelat med ett tydligt fel vid skapandet av **tråden**.
- **Lösning**:
  1. Kontrollera integriteten hos filerna `samp.dll` och `omp-client.dll`. De kan vara korrupta eller av en version som är inkompatibel med din `gta_sa.exe`.
  2. Säkerställ **att den injicerade DLL:en** inte är beroende av **andra DLL:er** som kan saknas eller vara otillgängliga i systemet.

### 11. Misslyckande med att återuppta spelets processtråd

Detta är det sista steget för att starta spelet efter **att DLL:erna** har injicerats.

![Error 16](screenshots/error_16.png)

- **Visat felmeddelande**: `"Failed to resume the game process thread: [Operativsystemets felmeddelande]"`.
- **Orsak**: Anropet `ResumeThread` misslyckades, vilket innebär att den **huvudsakliga tråden** i `gta_sa.exe` inte kunde aktiveras för att starta spelets körning. Detta är ett sällsynt fel, men kan inträffa om:
  - **Handtaget** för processens **tråd** blev ogiltigt.
  - Operativsystemet förhindrade återupptagandet av någon anledning, möjligen relaterat till en säkerhetsavbrott eller ett inkonsekvent processtillstånd.
  - Processen kan ha avslutats externt mellan **injektionen av DLL:en** och försöket att återuppta den **huvudsakliga tråden**.
- **Lösning**: Om alla tidigare steg lyckades och endast `ResumeThread` misslyckades, kan det vara ett problem med operativsystemet, med själva installationen av **GTA:SA**, eller med ett annat **säkerhetsprogram** som är mycket strikt. Granska tillståndet för `gta_sa.exe` via **Aktivitetshanteraren** strax före och efter felet. Att starta om datorn kan lösa tillfälliga systemtillståndsproblem.

> [!TIP] Diagnostikverktyg
> I komplexa felsökningsscenarier kan verktyg som **Process Monitor (Sysinternals Suite)** eller en debugger (som **Visual Studio Debugger**, **WinDbg**, **OllyDbg**) vara ovärderliga. De kan hjälpa till att observera **API-anrop**, kontrollera åtkomstfel, spåra tillståndet för **handtag** och till och med inspektera processens minne, vilket ger en djupgående insikt i vad som händer bakom kulisserna.

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