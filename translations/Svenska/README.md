# SA-MP Injector

[![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](https://opensource.org/licenses/MIT)
[![SA-MP | OMP](https://img.shields.io/badge/Support-SA--MP%20%7C%20OMP-yellow)](https://github.com/spc-samp/samp-injector)
[![x86 Only](https://img.shields.io/badge/Architecture-x86%20(32--bit)-orange)](https://github.com/spc-samp/samp-injector)

**SA-MP Injector** är ett mångsidigt verktyg designat för **SA-MP (San Andreas Multiplayer)** och **OMP (Open Multiplayer)**, som fungerar som ett **kommandoradsexekverbart program**, en **dynamisk bibliotek (DLL)** och en **samling bibliotek för olika programmeringsspråk**. Dess huvudsakliga funktion är att injicera `samp.dll` (i fallet med **SA-MP**) eller både `samp.dll` och `omp-client.dll` (i fallet med **OMP**) i processen för **GTA:SA**, vilket gör det möjligt att starta spelet med anpassade parametrar och möjliggöra direkt anslutning till en server.

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

- [SA-MP Injector](#sa-mp-injector)
  - [Språk](#språk)
  - [Innehållsförteckning](#innehållsförteckning)
  - [Körbar fil](#körbar-fil)
    - [Funktionalitet](#funktionalitet)
    - [Hur man använder (Kommandorad)](#hur-man-använder-kommandorad)
      - [SA-MP-läge](#sa-mp-läge)
      - [OMP-läge](#omp-läge)
      - [Parametrar](#parametrar)
    - [Hur man använder (Inbyggd i applikationer)](#hur-man-använder-inbyggd-i-applikationer)
    - [Användning av C++-biblioteket i den körbara filen](#användning-av-c-biblioteket-i-den-körbara-filen)
    - [Hur man kompilerar](#hur-man-kompilerar)
      - [Krav](#krav)
      - [Kompileringssteg](#kompileringssteg)
  - [Dynamiskt Bibliotek (**DLL**)](#dynamiskt-bibliotek-dll)
    - [Funktionalitet](#funktionalitet-1)
    - [Hur man använder (API-anrop)](#hur-man-använder-api-anrop)
      - [Kontrakt för Funktionen `Launch_Game`](#kontrakt-för-funktionen-launch_game)
      - [Parametrar](#parametrar-1)
    - [Hur man använder (Inbäddat i Applikationer)](#hur-man-använder-inbäddat-i-applikationer)
    - [Användning av C++-biblioteket i **DLL**](#användning-av-c-biblioteket-i-dll)
    - [Hur man kompilerar](#hur-man-kompilerar-1)
      - [Krav](#krav-1)
      - [Kompileringssteg](#kompileringssteg-1)
  - [Bibliotek](#bibliotek)
    - [Översikt](#översikt)
    - [Lista över bibliotek](#lista-över-bibliotek)
  - [Licens](#licens)
    - [Användarvillkor](#användarvillkor)
      - [1. Beviljade rättigheter](#1-beviljade-rättigheter)
      - [2. Obligatoriska villkor](#2-obligatoriska-villkor)
      - [3. Upphovsrätt](#3-upphovsrätt)
      - [4. Garantifriskrivning och ansvarsbegränsning](#4-garantifriskrivning-och-ansvarsbegränsning)

## Körbar fil

Den körbara filen `samp-injector.exe` erbjuder ett kommandoradsgränssnitt för att starta **GTA:SA** med **SA-MP** eller **OMP**, och konfigurerar automatiskt anslutningen till en server. Den kapslar in logiken för **injektion av DLL:er** och överföring av spelparametrar.

### Funktionalitet

`samp-injector.exe` fungerar som en automatiserad spellanseringsklient som abstraherar komplexiteten i konfiguration och injektion av **DLL:er**:

1. **Miljövalidering:** Kontrollerar existensen av nödvändiga filer (`gta_sa.exe`, `samp.dll`, `omp-client.dll`) i den angivna katalogen samt validerar de angivna anslutningsparametrarna.
2. **Skapande av suspenderad process:** Startar `gta_sa.exe` i ett suspenderat tillstånd, vilket är ett krav för att **säkert injicera DLL:er** innan spelets huvudprocess körs.
3. **Dynamisk injektion av DLL:er:**
   - För **SA-MP**-läget injiceras `samp.dll`.
   - För **OMP**-läget injiceras både `samp.dll` och `omp-client.dll`. Injektionen underlättas genom fjärranrop av funktionen `LoadLibraryA`, vilket gör att GTA: SA kan ladda multiplayer-modulerna och initiera anslutningen.
4. **Konfiguration av argument:** Kommandoradsargument, såsom **smeknamn**, **serverns IP**, **port** och **lösenord (om angivet)**, förbereds och överförs till `gta_sa.exe`.
5. **Återupptagande av processen:** Efter **lyckad injektion av DLL:er** återupptas spelprocessen för normal körning, vilket gör att **GTA:SA** ansluter direkt till servern.

### Hur man använder (Kommandorad)

För att använda den körbara filen, anropa den från **Kommandotolken (CMD)**, **PowerShell** eller **terminalen** och ange de nödvändiga parametrarna.

Det grundläggande formatet är:
```bash
samp-injector.exe <läge> <spelkatalog> <smeknamn> <server_IP> <server_port> <server_lösenord (valfritt)>
```

#### SA-MP-läge

För exklusiv injektion av `samp.dll`:
```bash
samp-injector.exe "samp" "C:\Games\GTA San Andreas" "Namn" "127.0.0.1" "7777" "lösenord (valfritt)"
```

#### OMP-läge

För injektion av `samp.dll` och `omp-client.dll`:
```bash
samp-injector.exe "omp" "C:\Games\GTA San Andreas" "Namn" "127.0.0.1" "7777" "lösenord (valfritt)"
```

#### Parametrar

- `<läge>`: Anger typen av injektion.
   - `samp`: För **SA-MP** (`samp.dll`).
   - `omp`: För **OMP** (`samp.dll` och `omp-client.dll`).
- `<spelkatalog>`: Den fullständiga sökvägen till **GTA:SA**-katalogen. Denna katalog måste innehålla `gta_sa.exe` och de respektive **DLL**-filerna.
- `<smeknamn>`: Ditt smeknamn i spelet (max **20 tecken**).
- `<server_IP>`: Serverns **IP-adress** eller **domännamn**.
- `<server_port>`: Serverns anslutningsport (ett **numeriskt värde** mellan **1** och **65535**).
- `<server_lösenord>`: Lösenordet som krävs för att ansluta till servern **(om servern inte har något lösenord behöver denna parameter inte anges)**.

Om argumenten är felaktiga eller otillräckliga visas ett användningsmeddelande.

### Hur man använder (Inbyggd i applikationer)

`samp-injector.exe` är idealisk för integration i tredjepartsapplikationer, såsom anpassade launchers, som vill automatisera processen att starta spelet med fördefinierade inställningar.

Exempel på anrop av `samp-injector.exe` från en **C#**-applikation:
```csharp
using System;
using System.Diagnostics;
using System.Windows.Forms;

public class Launcher {
    public static void Main(string[] args) {
        string inject_mode = "omp"; 
        string folder = "C:\\Games\\GTA San Andreas";
        string nickname = "Namn";
        string ip = "127.0.0.1";
        string port = "7777";
        string password = "lösenord (valfritt)";

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
                    MessageBox.Show($"SA-MP Injector returnerade ett fel (Kod: {process.ExitCode}). Spelet kanske inte startades korrekt.", "Startfel", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }
        catch (Exception ex) {
            MessageBox.Show($"Ett fel uppstod vid start av spelet: {ex.Message}", "Fel", MessageBoxButtons.OK, MessageBoxIcon.Error);
        }
    }
}
```

### Användning av C++-biblioteket i den körbara filen

Den körbara filen `samp-injector.exe` är byggd på biblioteket [SA-MP Injector C++](https://github.com/spc-samp/samp-injector/tree/main/libraries/cpp), som finns i katalogen `libraries/cpp/`. Filen `main.cpp` i den körbara filen använder funktionerna i detta bibliotek för att utföra injektion och lansering av spelet.

Det huvudsakliga rubrikfilen för **C++**-biblioteket som ska inkluderas är `libraries/samp-injector/cpp/injector.hpp`. Eftersom biblioteket [SA-MP Injector C++](https://github.com/spc-samp/samp-injector/tree/main/libraries/cpp) är **header-only**, kräver dess användning endast inkludering av denna rubrik i källkoden, utan behov av att länka en `.lib`-fil.

Det relevanta avsnittet av `main.cpp` som visar integrationen är följande:
```cpp
// Extraherar kommandoradsargument
int argc;
std::unique_ptr<LPWSTR[], decltype(&LocalFree)> argv(CommandLineToArgvW(GetCommandLineW(), &argc), &LocalFree);

// ... (validering av antalet argument och injektionsläge) ...

// Extraherar parametrarna till variabler av typen wide string
std::wstring folder = argv[2];
std::wstring nickname = argv[3];
std::wstring ip = argv[4];
std::wstring port = argv[5];
std::wstring password = (argc == 7) ? argv[6] : L"";

// Delegerar injektionslogiken till funktionen "Initialize_Game" i biblioteket
// Observera att "injector.hpp" tidigare inkluderades i "main.cpp"
if (!Initialize_Game(inject_type, folder, nickname, ip, port, password))
    return 1;

Sleep(10000); // Väntar innan den körbara filen avslutas
```

Funktionen `Initialize_Game` fungerar som bibliotekets högnivågränssnitt och orkestrerar alla operationer för validering, processkapande och **injektion av DLL:er**.

### Hur man kompilerar

Du kan kompilera `samp-injector.exe` från källkoden. Om du inte vill kompilera kan du ladda ner förkompilerade versioner i avsnittet [Releases](https://github.com/spc-samp/samp-injector/releases).

#### Krav

- **Visual Studio:** Rekommenderas **Visual Studio 2022** eller senare med arbetsbelastningen **"Utveckling för skrivbordsapplikationer med C++"** installerad.
- **Git:** För att klona repositoriet (eller ladda ner det direkt via denna länk: [Ladda ner](https://github.com/spc-samp/samp-injector/archive/refs/heads/main.zip)).

#### Kompileringssteg

1. **Klona repositoriet:**
   ```bash
   git clone https://github.com/spc-samp/samp-injector.git
   cd samp-injector
   ```
2. **Öppna lösningen:**
   Navigera till mappen `executable` och öppna lösningsfilen `.sln`:
   ```bash
   cd executable
   start samp-injector.sln
   ```
   Detta öppnar projektet i **Visual Studio**.
3. **Konfigurera bygget:**
   - I **Visual Studio**, kontrollera lösningens konfiguration. Det rekommenderas att använda lägena `Release` och `x86` **(32-bit)**. I sammanhanget för **GTA:SA** och **SA-MP**/**OMP** är **x86 (32-bit)**-arkitekturen obligatorisk.
4. **Kompilera:**
   - I menyn `Bygg` klicka på `Kompilera lösning` eller `Bygg samp-injector`.
   - Alternativt kan du använda genvägarna:
      - `Ctrl + Shift + B` för att kompilera hela lösningen.
      - `Ctrl + B` (om konfigurerat) för att kompilera det aktuella projektet.
   - Om allt är korrekt konfigurerat genereras den körbara filen `samp-injector.exe` i katalogen `executable\Release` (eller `executable\Debug`, beroende på din **byggkonfiguration**).

## Dynamiskt Bibliotek (**DLL**)

Biblioteket `samp-injector.dll` erbjuder ett **API (Application Programming Interface)** för att programmatiskt starta **GTA:SA** med **SA-MP** eller **OMP**. Det är det perfekta alternativet till det exekverbara programmet för utvecklare av launchers som vill ha en renare och mer direkt integration genom att anropa en funktion istället för att starta en extern process.

### Funktionalitet

`samp-injector.dll` aktiverar samma robusta arbetsflöde som det interna biblioteket och kapslar in komplexiteten i injektion och spelinitialisering:

1. **Skapande av en Suspenderad Process:** När den anropas startar den `gta_sa.exe` i ett suspenderat tillstånd.
2. **Dynamisk DLL-injektion:**
   - För **SA-MP**-läget injiceras `samp.dll`.
   - För **OMP**-läget injiceras både `samp.dll` och `omp-client.dll`.
3. **Konfiguration av Argument:** Funktionsparametrarna, såsom **smeknamn**, **IP**, **port** och **lösenord**, förbereds för `gta_sa.exe`.
4. **Återupptagning av Processen:** Efter injektionen återupptas spelprocessen för körning och ansluter direkt till servern.

### Hur man använder (API-anrop)

För att använda biblioteket behöver du ladda `samp-injector.dll` i din applikation och anropa den exporterade funktionen `Launch_Game`.

#### Kontrakt för Funktionen `Launch_Game`

- **DLL-fil:** `samp-injector.dll`
- **Exporterat Funktionsnamn:** `Launch_Game`
- **Anropskonvention:** `__stdcall`
- **Returtyp:** `int`
   - `0`: **Framgång.** Begäran om att starta spelet skickades till en bakgrundstråd.
   - `1`: **Ogiltiga Argument.** En obligatorisk parameter var null eller läget var ogiltigt. Ett felmeddelande visas.
   - `2`: **Trådfel.** Ett kritiskt fel uppstod vid försök att skapa initialiseringstråden. Ett felmeddelande visas.

#### Parametrar

Alla parametrar är breda teckensträngar (Unicode).

- `mode` (`LPCWSTR`): Definierar typen av injektion (`L"samp"` eller `L"omp"`).
- `folder` (`LPCWSTR`): Den fullständiga sökvägen till **GTA:SA**-katalogen.
- `nickname` (`LPCWSTR`): Ditt smeknamn i spelet.
- `ip` (`LPCWSTR`): **IP**-adressen eller **domännamnet** för servern.
- `port` (`LPCWSTR`): Serverns anslutningsport.
- `password` (`LPCWSTR`): Lösenordet för att ansluta till servern. **(Denna parameter är valfri. Du kan skicka `null` eller en tom sträng `L""` om det inte finns något lösenord)**.

### Hur man använder (Inbäddat i Applikationer)

Exempel på anrop av funktionen `Launch_Game` från en **C#-applikation**:
```csharp
using System;
using System.Runtime.InteropServices;
using System.Windows.Forms;

public class Launcher {
    // Importerar funktionen från DLL:en och specificerar API-kontraktet.
    [DllImport("samp-injector.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.StdCall, EntryPoint = "Launch_Game")]
    private static extern int Launch_Game(string mode, string folder, string nickname, string ip, string port, string password);

    public static void Main(string[] args) {
        string inject_mode = "samp"; 
        string gta_folder = "C:\\Games\\GTA San Andreas"; // Obs: Använd den faktiska sökvägen!
        string nickname = "Namn";
        string ip = "127.0.0.1";
        string port = "7777";
        string password = "lösenord (valfritt)"; // eller null, eller "" om inget finns

        try {
            int result = Launch_Game(inject_mode, gta_folder, nickname, ip, port, password);
            
            if (result != 0) {
                // DLL:en visar redan ett detaljerat felmeddelande,
                // men du kan logga eller visa ett annat meddelande här.
                MessageBox.Show($"Anropet till DLL returnerade en felkod: {result}", "Fel i Launcher", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }
        catch (DllNotFoundException) {
            MessageBox.Show("Fel: samp-injector.dll hittades inte! Kontrollera om den finns i samma mapp som launchern.", "Fel", MessageBoxButtons.OK, MessageBoxIcon.Error);
        }
        catch (Exception ex) {
            MessageBox.Show($"Ett oväntat fel uppstod: {ex.Message}", "Fel", MessageBoxButtons.OK, MessageBoxIcon.Error);
        }
    }
}
```

### Användning av C++-biblioteket i **DLL**

Liksom det exekverbara programmet är även `samp-injector.dll` byggd på biblioteket [SA-MP Injector C++](https://github.com/spc-samp/samp-injector/tree/main/libraries/cpp), som finns i katalogen `libraries/cpp/`. Den exporterade funktionen `Launch_Game` fungerar som en wrapper, validerar parametrarna och delegerar den huvudsakliga injektionslogiken till funktionen `Initialize_Game` i biblioteket.

Den huvudsakliga header-filen för **C++**-biblioteket som ska inkluderas är `libraries/samp-injector/cpp/injector.hpp`. Eftersom biblioteket [SA-MP Injector C++](https://github.com/spc-samp/samp-injector/tree/main/libraries/cpp) är **header-only**, kräver dess användning endast inkludering av denna header i källkoden, utan behov av att länka en `.lib`-fil.

Följande kodsnutt från `main.cpp` i **DLL** visar hur uppgiften delegeras till en separat tråd:
```cpp
// Arbetarfunktion som körs i en bakgrundstråd
void Game_Thread_Worker(const std::wstring& mode, const std::wstring& folder, const std::wstring& nickname, const std::wstring& ip, const std::wstring& port, const std::wstring& password) {
    // Injektionslogiken delegeras till funktionen "Initialize_Game" i biblioteket.
    Initialize_Game(mode, folder, nickname, ip, port, password);
}

// Inom den exporterade funktionen `Launch_Game` skapas tråden:
try {
    std::thread(Game_Thread_Worker, mode_str, folder_str, nickname_str, ip_str, port_str, password_str).detach();
}
// ...
```

Detta visar att **DLL**:en i grunden är ett API-gränssnitt för samma kärnfunktionalitet som används av det exekverbara programmet.

### Hur man kompilerar

Du kan kompilera `samp-injector.dll` från källkoden. Om du inte vill kompilera kan du ladda ner förkompilerade versioner från sektionen [Releases](https://github.com/spc-samp/samp-injector/releases).

#### Krav

- **Visual Studio:** **Visual Studio 2022** eller senare med arbetsbelastningen **"Skrivbordsutveckling med C++"** installerad rekommenderas.
- **Git:** För att klona repositoriet (eller ladda ner det enkelt via denna länk: [Ladda ner](https://github.com/spc-samp/samp-injector/archive/refs/heads/main.zip)).

#### Kompileringssteg

1. **Klona Repositoriet:**
   ```bash
   git clone https://github.com/spc-samp/samp-injector.git
   cd samp-injector
   ```
2. **Öppna Lösningen:**
   Navigera till mappen `dll` och öppna lösningsfilen `.sln`:
   ```bash
   cd dll
   start samp-injector.sln
   ```
   Detta öppnar projektet i **Visual Studio**.
3. **Konfigurera Bygget:**
   - I **Visual Studio**, kontrollera lösningskonfigurationen. Det rekommenderas att använda lägena `Release` och `x86` **(32-bit)**. I sammanhanget för **GTA:SA** och **SA-MP**/**OMP** är **x86 (32-bit)**-arkitekturen obligatorisk.
4. **Kompilera:**
   - I menyn `Compilation`, klicka på `Compile Solution` eller `Build samp-injector`.
   - Alternativt kan du använda genvägarna:
      - `Ctrl + Shift + B` för att kompilera hela lösningen.
      - `Ctrl + B` (om det är konfigurerat) för att kompilera det aktuella projektet.
   - Om allt är korrekt konfigurerat kommer biblioteket `samp-injector.dll` att genereras i katalogen `dll\Release` (eller `dll\Debug`, beroende på din **build**-konfiguration).

## Bibliotek

Biblioteken är de grundläggande komponenterna i **SA-MP Injector** och innehåller den centrala logiken för processhantering, **injektion av DLL:er** och parameter-validering. Den största fördelen med att använda dessa bibliotek är enkelheten i initiering och injektion, vanligtvis genom en enda funktion (eller anrop med specifika parametrar för skriptspråk).

### Översikt

Projektet bygger på bibliotek som kapslar in de kritiska funktionerna. Detta gör det möjligt för andra projekt att enkelt integrera möjligheten att starta **GTA:SA** med de nödvändiga **multiplayer**-modulerna.

### Lista över bibliotek

| Språk      | Namn                   | Länk till bibliotek/Dokumentation               |
| ---------- | ---------------------- | ----------------------------------------------- |
| C++        | **SA-MP Injector C++** | [Kolla biblioteket](../../libraries/cpp)        |
| C#         | **SA-MP Injector C#**  | [Kolla biblioteket](../../libraries/csharp)     |
| PowerShell | **SA-MP Injector PS**  | [Kolla biblioteket](../../libraries/powershell) |

> [!WARNING]
> **PowerShell**-biblioteket har avvecklats och kommer inte längre att få uppdateringar eller underhåll. Detta beror på att **GitHubs filter** anser att biblioteket innehåller potentiellt **skadligt** beteende, eftersom det utför **lågnivå**-operationer. När detta händer kan både **författarens** konto och **SPC**-profilen bli **avstängda** och **flaggade**. Men **oroa dig inte**: **PowerShell**-biblioteket kommer fortfarande att vara tillgängligt för användning, det kommer bara **inte att få nya uppdateringar**.

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