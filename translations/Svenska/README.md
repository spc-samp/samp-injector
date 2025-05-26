# SA-MP Injector

[![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](https://opensource.org/licenses/MIT)
[![SA-MP | OMP](https://img.shields.io/badge/Support-SA--MP%20%7C%20OMP-yellow)](https://github.com/spc-samp/samp-injector)
[![x86 Only](https://img.shields.io/badge/Architecture-x86%20(32--bit)-orange)](https://github.com/spc-samp/samp-injector)

SA-MP Injector är ett mångsidigt verktyg designat för **SA-MP (San Andreas Multiplayer)** och **OMP (Open Multiplayer)**, som fungerar både som en **körbar kommandoradsfil** och en **bibliotek för olika programmeringsspråk**. Dess huvudsakliga funktion är att injicera `samp.dll` (för **SA-MP**) eller både `samp.dll` och `omp-client.dll` (för **OMP**) i processen för **GTA:SA**, vilket gör det möjligt att starta spelet med anpassade parametrar för direkt anslutning till en server.

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
    - För **OMP**-läget injiceras både `samp.dll` och `omp-client.dll`.
    Injektionen underlättas genom fjärranrop av funktionen `LoadLibraryA`, vilket gör att GTA: SA kan ladda multiplayer-modulerna och initiera anslutningen.
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

## Bibliotek

Biblioteken är de grundläggande komponenterna i `SA-MP Injector` och innehåller den centrala logiken för processhantering, **injektion av DLL:er** och parameter-validering. Den största fördelen med att använda dessa bibliotek är enkelheten i initiering och injektion, vanligtvis genom en enda funktion (eller anrop med specifika parametrar för skriptspråk).

### Översikt

Projektet bygger på bibliotek som kapslar in de kritiska funktionerna. Detta gör det möjligt för andra projekt att enkelt integrera möjligheten att starta **GTA:SA** med de nödvändiga **multiplayer**-modulerna.

### Lista över bibliotek

| Språk         | Namn                       | Länk till bibliotek/Dokumentation  |
| ------------- | -------------------------- | ---------------------------------- |
| C++           | **SA-MP Injector C++**     | [Kolla biblioteket](libraries/cpp) |
| C             | **SA-MP Injector C**       | (Kommer snart)                     |
| C#            | **SA-MP Injector C#**      | (Kommer snart)                     |
| Java          | **SA-MP Injector Java**    | (Kommer snart)                     |
| Python        | **SA-MP Injector Python**  | (Kommer snart)                     |
| Go (Golang)   | **SA-MP Injector Go**      | (Kommer snart)                     |
| Rust          | **SA-MP Injector Rust**    | (Kommer snart)                     |
| Kotlin        | **SA-MP Injector Kotlin**  | (Kommer snart)                     |
| Scala         | **SA-MP Injector Scala**   | (Kommer snart)                     |
| Lua           | **SA-MP Injector Lua**     | (Kommer snart)                     |
| Ruby          | **SA-MP Injector Ruby**    | (Kommer snart)                     |
| Visual Basic  | **SA-MP Injector VB**      | (Kommer snart)                     |
| F#            | **SA-MP Injector F#**      | (Kommer snart)                     |
| Pascal/Delphi | **SA-MP Injector P/D**     | (Kommer snart)                     |
| PowerShell    | **SA-MP Injector PS**      | (Kommer snart)                     |
| D (Dlang)     | **SA-MP Injector D**       | (Kommer snart)                     |
| Nim           | **SA-MP Injector Nim**     | (Kommer snart)                     |
| Zig           | **SA-MP Injector Zig**     | (Kommer snart)                     |
| V (VLang)     | **SA-MP Injector V**       | (Kommer snart)                     |
| Crystal       | **SA-MP Injector Crystal** | (Kommer snart)                     |
| Perl          | **SA-MP Injector Perl**    | (Kommer snart)                     |
| Racket (Lisp) | **SA-MP Injector Racket**  | (Kommer snart)                     |
| Haskell       | **SA-MP Injector Haskell** | (Kommer snart)                     |
| OCaml         | **SA-MP Injector OCaml**   | (Kommer snart)                     |

> [!TIP]
> Detaljerad dokumentation för varje bibliotek kommer att finnas tillgänglig i dess **respektive katalog**.

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