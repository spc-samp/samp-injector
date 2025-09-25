# SA-MP Injector

[![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](https://opensource.org/licenses/MIT)
[![SA-MP | OMP](https://img.shields.io/badge/Support-SA--MP%20%7C%20OMP-yellow)](https://github.com/spc-samp/samp-injector)
[![x86 Only](https://img.shields.io/badge/Architecture-x86%20(32--bit)-orange)](https://github.com/spc-samp/samp-injector)

**SA-MP Injector** ist ein vielseitiges Tool, das für **SA-MP (San Andreas Multiplayer)** und **OMP (Open Multiplayer)** entwickelt wurde und als **Kommandozeilenprogramm**, **dynamische Bibliothek (DLL)** und **Sammlung von Bibliotheken für verschiedene Programmiersprachen** fungiert. Seine Hauptfunktion besteht darin, die `samp.dll` (im Fall von **SA-MP**) oder sowohl `samp.dll` als auch `omp-client.dll` (im Fall von **OMP**) in den Prozess von **GTA:SA** zu injizieren, wodurch das Spiel mit benutzerdefinierten Parametern gestartet werden kann, um eine direkte Verbindung zu einem Server zu ermöglichen.

## Sprachen

- Português: [README](../../)
- English: [README](../English/README.md)
- Español: [README](../Espanol/README.md)
- Français: [README](../Francais/README.md)
- Italiano: [README](../Italiano/README.md)
- Polski: [README](../Polski/README.md)
- Русский: [README](../Русский/README.md)
- Svenska: [README](../Svenska/README.md)
- Türkçe: [README](../Turkce/README.md)

## Inhaltsverzeichnis

- [SA-MP Injector](#sa-mp-injector)
  - [Sprachen](#sprachen)
  - [Inhaltsverzeichnis](#inhaltsverzeichnis)
  - [Executable](#executable)
    - [Funktionalität](#funktionalität)
    - [Verwendung (Kommandozeile)](#verwendung-kommandozeile)
      - [SA-MP-Modus](#sa-mp-modus)
      - [OMP-Modus](#omp-modus)
      - [Parameter](#parameter)
    - [Verwendung (Eingebettet in Anwendungen)](#verwendung-eingebettet-in-anwendungen)
    - [Verwendung der C++-Bibliothek im Executable](#verwendung-der-c-bibliothek-im-executable)
    - [Kompilierung](#kompilierung)
      - [Voraussetzungen](#voraussetzungen)
      - [Kompilierungsschritte](#kompilierungsschritte)
  - [Dynamische Bibliothek (**DLL**)](#dynamische-bibliothek-dll)
    - [Funktionalität](#funktionalität-1)
    - [Verwendung (API-Aufruf)](#verwendung-api-aufruf)
      - [Vertrag der Funktion `Launch_Game`](#vertrag-der-funktion-launch_game)
      - [Parameter](#parameter-1)
    - [Verwendung (Eingebettet in Anwendungen)](#verwendung-eingebettet-in-anwendungen-1)
    - [Verwendung der C++-Bibliothek in der **DLL**](#verwendung-der-c-bibliothek-in-der-dll)
    - [Kompilierung](#kompilierung-1)
      - [Anforderungen](#anforderungen)
      - [Kompilierungsschritte](#kompilierungsschritte-1)
  - [Bibliotheken](#bibliotheken)
    - [Überblick](#überblick)
    - [Liste der Bibliotheken](#liste-der-bibliotheken)
  - [Lizenz](#lizenz)
    - [Nutzungsbedingungen](#nutzungsbedingungen)
      - [1. Gewährte Berechtigungen](#1-gewährte-berechtigungen)
      - [2. Verpflichtende Bedingungen](#2-verpflichtende-bedingungen)
      - [3. Urheberrecht](#3-urheberrecht)
      - [4. Gewährleistungsausschluss und Haftungsbeschränkung](#4-gewährleistungsausschluss-und-haftungsbeschränkung)

## Executable

Das Executable `samp-injector.exe` bietet eine Kommandozeilen-Schnittstelle, um **GTA:SA** mit **SA-MP** oder **OMP** zu starten und die Verbindung zu einem Server automatisch zu konfigurieren. Es kapselt die Logik der **DLL-Injektion** und die Übergabe von Spielparametern.

### Funktionalität

Das `samp-injector.exe` fungiert als automatisierter Spiele-Starter, der die Komplexität der Konfiguration und DLL-Injektion abstrahiert:

1. **Umgebungsprüfung:** Überprüft das Vorhandensein der essentiellen Dateien (`gta_sa.exe`, `samp.dll`, `omp-client.dll`) im angegebenen Verzeichnis sowie die Validität der bereitgestellten Verbindungsparameter.
2. **Erstellung eines suspendierten Prozesses:** Startet `gta_sa.exe` in einem suspendierten Zustand, was eine Voraussetzung für die sichere **Injektion von DLLs** ist, bevor der Hauptprozess des Spiels ausgeführt wird.
3. **Dynamische DLL-Injektion:**
   - Für den **SA-MP**-Modus wird `samp.dll` injiziert.
   - Für den **OMP**-Modus werden `samp.dll` und `omp-client.dll` injiziert. Die Injektion wird durch den entfernten Aufruf der Funktion `LoadLibraryA` erleichtert, wodurch GTA:SA die Multiplayer-Module lädt und die Verbindung initialisiert.
4. **Konfiguration der Argumente:** Kommandozeilenargumente wie **Nickname**, **Server-IP**, **Port** und **Passwort (falls angegeben)** werden vorbereitet und an `gta_sa.exe` übergeben.
5. **Fortsetzung des Prozesses:** Nach erfolgreicher **DLL-Injektion** wird der Spielprozess fortgesetzt, sodass **GTA:SA** sich direkt mit dem Server verbindet.

### Verwendung (Kommandozeile)

Um das Executable zu verwenden, rufen Sie es über die **Eingabeaufforderung (CMD)**, **PowerShell** oder ein **Terminal** mit den erforderlichen Parametern auf.

Das grundlegende Format lautet:
```bash
samp-injector.exe <Modus> <Spielverzeichnis> <Nickname> <Server-IP> <Server-Port> <Server-Passwort (optional)>
```

#### SA-MP-Modus

Für die ausschließliche Injektion von `samp.dll`:
```bash
samp-injector.exe "samp" "C:\Games\GTA San Andreas" "Name" "127.0.0.1" "7777" "Passwort (optional)"
```

#### OMP-Modus

Für die Injektion von `samp.dll` und `omp-client.dll`:
```bash
samp-injector.exe "omp" "C:\Games\GTA San Andreas" "Name" "127.0.0.1" "7777" "Passwort (optional)"
```

#### Parameter

- `<Modus>`: Definiert den Injektionstyp.
   - `samp`: Für **SA-MP** (`samp.dll`).
   - `omp`: Für **OMP** (`samp.dll` und `omp-client.dll`).
- `<Spielverzeichnis>`: Der vollständige Pfad zum **GTA:SA**-Verzeichnis. Dieses Verzeichnis muss `gta_sa.exe` und die entsprechenden **DLL**-Dateien enthalten.
- `<Nickname>`: Ihr Spiel-Nickname (maximal **20 Zeichen**).
- `<Server-IP>`: Die **IP-Adresse** oder der **Domainname** des Servers.
- `<Server-Port>`: Der Verbindungsport des Servers (ein **numerischer Wert** zwischen **1** und **65535**).
- `<Server-Passwort>`: Das Passwort, das für die Verbindung zum Server erforderlich ist **(falls der Server kein Passwort benötigt, ist dieser Parameter nicht erforderlich)**.

Falls die Argumente falsch oder unvollständig sind, wird eine Nutzungsmeldung angezeigt.

### Verwendung (Eingebettet in Anwendungen)

Das `samp-injector.exe` ist ideal für die Integration in Drittanbieter-Anwendungen wie benutzerdefinierte Launcher, die den Prozess des Spielstarts mit vordefinierten Einstellungen automatisieren möchten.

Beispiel für den Aufruf von `samp-injector.exe` aus einer **C#-Anwendung**:
```csharp
using System;
using System.Diagnostics;
using System.Windows.Forms;

public class Launcher {
    public static void Main(string[] args) {
        string inject_mode = "omp"; 
        string folder = "C:\\Games\\GTA San Andreas";
        string nickname = "Name";
        string ip = "127.0.0.1";
        string port = "7777";
        string password = "Passwort (optional)";

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
                    MessageBox.Show($"Der SA-MP Injector hat einen Fehler zurückgegeben (Code: {process.ExitCode}). Das Spiel wurde möglicherweise nicht korrekt gestartet.", "Fehler beim Start", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }
        catch (Exception ex) {
            MessageBox.Show($"Beim Starten des Spiels ist ein Fehler aufgetreten: {ex.Message}", "Fehler", MessageBoxButtons.OK, MessageBoxIcon.Error);
        }
    }
}
```

### Verwendung der C++-Bibliothek im Executable

Das Executable `samp-injector.exe` basiert auf der Bibliothek [SA-MP Injector C++](https://github.com/spc-samp/samp-injector/tree/main/libraries/cpp), die sich im Verzeichnis `libraries/cpp/` befindet. Die `main.cpp`-Datei des Executables verwendet die Funktionalitäten dieser Bibliothek, um die Injektion und den Spielstart durchzuführen.

Die Hauptheader-Datei der **C++**-Bibliothek, die eingebunden werden muss, ist `libraries/samp-injector/cpp/injector.hpp`. Da die Bibliothek [SA-MP Injector C++](https://github.com/spc-samp/samp-injector/tree/main/libraries/cpp) **header-only** ist, ist für ihre Nutzung lediglich das Einbinden dieses Headers im Quellcode erforderlich, ohne dass eine `.lib`-Datei verlinkt werden muss.

Der relevante Abschnitt der `main.cpp`, der die Integration zeigt, ist wie folgt:
```cpp
// Extrahiert die Kommandozeilenargumente
int argc;
std::unique_ptr<LPWSTR[], decltype(&LocalFree)> argv(CommandLineToArgvW(GetCommandLineW(), &argc), &LocalFree);

// ... (Validierung der Anzahl der Argumente und des Injektionsmodus) ...

// Extrahiert die Parameter in Wide-String-Variablen
std::wstring folder = argv[2];
std::wstring nickname = argv[3];
std::wstring ip = argv[4];
std::wstring port = argv[5];
std::wstring password = (argc == 7) ? argv[6] : L"";

// Delegiert die Injektionslogik an die Funktion "Initialize_Game" der Bibliothek
// Beachten Sie, dass "injector.hpp" zuvor in "main.cpp" eingebunden wurde
if (!Initialize_Game(inject_type, folder, nickname, ip, port, password))
    return 1;

Sleep(10000); // Wartet, bevor das Executable beendet wird
```

Die Funktion `Initialize_Game` dient als High-Level-Schnittstelle der Bibliothek und orchestriert alle Operationen zur Validierung, Prozesserstellung und **DLL-Injektion**.

### Kompilierung

Sie können das `samp-injector.exe` aus dem Quellcode kompilieren. Wenn Sie nicht kompilieren möchten, können Sie die vorkompilierten Versionen im Abschnitt [Releases](https://github.com/spc-samp/samp-injector/releases) herunterladen.

#### Voraussetzungen

- **Visual Studio:** Es wird **Visual Studio 2022** oder höher mit der **Workload "Desktop-Entwicklung mit C++"** empfohlen.
- **Git:** Zum Klonen des Repositories (oder laden Sie es einfach über diesen Link herunter: [Download](https://github.com/spc-samp/samp-injector/archive/refs/heads/main.zip)).

#### Kompilierungsschritte

1. **Repository klonen:**
   ```bash
   git clone https://github.com/spc-samp/samp-injector.git
   cd samp-injector
   ```
2. **Lösung öffnen:**
   Navigieren Sie zum Ordner `executable` und öffnen Sie die Lösungsdatei `.sln`:
   ```bash
   cd executable
   start samp-injector.sln
   ```
   Dies öffnet das Projekt in **Visual Studio**.
3. **Build konfigurieren:**
   - Überprüfen Sie in **Visual Studio** die Lösungskonfiguration. Es wird empfohlen, die Modi `Release` und `x86` **(32-Bit)** zu verwenden. Im Kontext von **GTA:SA** und **SA-MP**/**OMP** ist die **x86 (32-Bit)**-Architektur zwingend erforderlich.
4. **Kompilieren:**
   - Klicken Sie im Menü `Build` auf `Build Solution` oder `Build samp-injector`.
   - Alternativ können Sie die Tastenkombinationen verwenden:
      - `Strg + Umschalt + B`, um die gesamte Lösung zu kompilieren.
      - `Strg + B` (falls konfiguriert), um das aktuelle Projekt zu kompilieren.
   - Wenn alles korrekt konfiguriert ist, wird das Executable `samp-injector.exe` im Verzeichnis `executable\Release` (oder `executable\Debug`, je nach Ihrer **Build**-Konfiguration) generiert.

## Dynamische Bibliothek (**DLL**)

Die Bibliothek `samp-injector.dll` bietet eine **API (Application Programming Interface)**, um **GTA:SA** mit **SA-MP** oder **OMP** programmgesteuert zu starten. Sie ist die ideale Alternative zum ausführbaren Programm für Entwickler von Launchern, die eine sauberere und direktere Integration wünschen, indem sie eine Funktion aufrufen, anstatt einen externen Prozess zu starten.

### Funktionalität

Die `samp-injector.dll` löst denselben robusten Arbeitsablauf wie die interne Bibliothek aus und kapselt die Komplexitäten der Injektion und Initialisierung des Spiels:

1. **Erstellung eines suspendierten Prozesses:** Beim Aufruf wird `gta_sa.exe` in einem suspendierten Zustand gestartet.
2. **Dynamische Injektion von DLLs:**
   - Für den **SA-MP**-Modus wird `samp.dll` injiziert.
   - Für den **OMP**-Modus werden `samp.dll` und `omp-client.dll` injiziert.
3. **Konfiguration von Argumenten:** Die Funktionsparameter wie **Nickname**, **IP**, **Port** und **Passwort** werden für `gta_sa.exe` vorbereitet.
4. **Fortsetzung des Prozesses:** Nach der Injektion wird der Spielprozess fortgesetzt, um die Ausführung zu ermöglichen und sich direkt mit dem Server zu verbinden.

### Verwendung (API-Aufruf)

Um die Bibliothek zu verwenden, müssen Sie die `samp-injector.dll` in Ihre Anwendung laden und die exportierte Funktion `Launch_Game` aufrufen.

#### Vertrag der Funktion `Launch_Game`

- **DLL-Datei:** `samp-injector.dll`
- **Exportierter Funktionsname:** `Launch_Game`
- **Aufrufkonvention:** `__stdcall`
- **Rückgabetyp:** `int`
   - `0`: **Erfolg.** Die Anforderung zum Starten des Spiels wurde an einen Hintergrundthread gesendet.
   - `1`: **Ungültige Argumente.** Ein erforderlicher Parameter war null oder der Modus war ungültig. Eine Fehlermeldung wird angezeigt.
   - `2`: **Thread-Fehler.** Ein kritischer Fehler trat beim Versuch auf, den Initialisierungs-Thread zu erstellen. Eine Fehlermeldung wird angezeigt.

#### Parameter

Alle Parameter sind Zeichenfolgen im Unicode-Format (Wide-Character-Strings).

- `mode` (`LPCWSTR`): Definiert die Art der Injektion (`L"samp"` oder `L"omp"`).
- `folder` (`LPCWSTR`): Der vollständige Pfad zum Verzeichnis von **GTA:SA**.
- `nickname` (`LPCWSTR`): Ihr Spitzname im Spiel.
- `ip` (`LPCWSTR`): Die **IP**-Adresse oder der **Domainname** des Servers.
- `port` (`LPCWSTR`): Der Verbindungsport des Servers.
- `password` (`LPCWSTR`): Das Passwort für die Verbindung zum Server. **(Dieser Parameter ist optional. Sie können `null` oder eine leere Zeichenfolge `L""` übergeben, wenn kein Passwort vorhanden ist)**.

### Verwendung (Eingebettet in Anwendungen)

Beispielaufruf der Funktion `Launch_Game` aus einer **C#-Anwendung**:
```csharp
using System;
using System.Runtime.InteropServices;
using System.Windows.Forms;

public class Launcher {
    // Importiert die Funktion aus der DLL und gibt den API-Vertrag an.
    [DllImport("samp-injector.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.StdCall, EntryPoint = "Launch_Game")]
    private static extern int Launch_Game(string mode, string folder, string nickname, string ip, string port, string password);

    public static void Main(string[] args) {
        string inject_mode = "samp"; 
        string gta_folder = "C:\\Games\\GTA San Andreas"; // Achtung: Verwenden Sie den echten Pfad!
        string nickname = "Name";
        string ip = "127.0.0.1";
        string port = "7777";
        string password = "Passwort (optional)"; // oder null oder "" wenn keines vorhanden ist

        try {
            int result = Launch_Game(inject_mode, gta_folder, nickname, ip, port, password);
            
            if (result != 0) {
                // Die DLL zeigt bereits eine detaillierte Fehlermeldung an,
                // aber Sie können hier eine weitere Nachricht protokollieren oder anzeigen.
                MessageBox.Show($"Der Aufruf der DLL hat einen Fehlercode zurückgegeben: {result}", "Fehler im Launcher", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }
        catch (DllNotFoundException) {
            MessageBox.Show("Fehler: samp-injector.dll nicht gefunden! Überprüfen Sie, ob sie sich im selben Ordner wie der Launcher befindet.", "Fehler", MessageBoxButtons.OK, MessageBoxIcon.Error);
        }
        catch (Exception ex) {
            MessageBox.Show($"Ein unerwarteter Fehler ist aufgetreten: {ex.Message}", "Fehler", MessageBoxButtons.OK, MessageBoxIcon.Error);
        }
    }
}
```

### Verwendung der C++-Bibliothek in der **DLL**

Wie beim ausführbaren Programm basiert auch die `samp-injector.dll` auf der Bibliothek [SA-MP Injector C++](https://github.com/spc-samp/samp-injector/tree/main/libraries/cpp), die sich im Verzeichnis `libraries/cpp/` befindet. Die exportierte Funktion `Launch_Game` fungiert als Wrapper, validiert die Parameter und delegiert die Hauptlogik der Injektion an die Funktion `Initialize_Game` der Bibliothek.

Die Hauptdatei der **C++**-Bibliothek, die eingebunden werden muss, ist `libraries/samp-injector/cpp/injector.hpp`. Da die Bibliothek [SA-MP Injector C++](https://github.com/spc-samp/samp-injector/tree/main/libraries/cpp) **header-only** ist, erfordert ihre Nutzung lediglich das Einbinden dieses Headers im Quellcode, ohne dass eine `.lib`-Datei verlinkt werden muss.

Der folgende Codeabschnitt aus `main.cpp` der **DLL** zeigt, wie die Aufgabe an einen separaten Thread delegiert wird:
```cpp
// Worker-Funktion, die in einem Hintergrundthread läuft
void Game_Thread_Worker(const std::wstring& mode, const std::wstring& folder, const std::wstring& nickname, const std::wstring& ip, const std::wstring& port, const std::wstring& password) {
    // Die Injektionslogik wird an die Funktion "Initialize_Game" der Bibliothek delegiert.
    Initialize_Game(mode, folder, nickname, ip, port, password);
}

// Innerhalb der exportierten Funktion `Launch_Game` wird der Thread erstellt:
try {
    std::thread(Game_Thread_Worker, mode_str, folder_str, nickname_str, ip_str, port_str, password_str).detach();
}
// ...
```

Dies zeigt, dass die **DLL** im Wesentlichen eine API-Schnittstelle für dieselbe Kernfunktionalität ist, die vom ausführbaren Programm verwendet wird.

### Kompilierung

Sie können die `samp-injector.dll` aus dem Quellcode kompilieren. Wenn Sie nicht kompilieren möchten, können Sie die vorkompilierten Versionen im Abschnitt [Releases](https://github.com/spc-samp/samp-injector/releases) herunterladen.

#### Anforderungen

- **Visual Studio:** Es wird **Visual Studio 2022** oder höher mit der Workload **"Desktop-Entwicklung mit C++"** empfohlen.
- **Git:** Zum Klonen des Repositories (oder laden Sie es einfach über diesen Link herunter: [Download](https://github.com/spc-samp/samp-injector/archive/refs/heads/main.zip)).

#### Kompilierungsschritte

1. **Repository klonen:**
   ```bash
   git clone https://github.com/spc-samp/samp-injector.git
   cd samp-injector
   ```
2. **Lösung öffnen:**
   Navigieren Sie zum Ordner `dll` und öffnen Sie die Lösungsdatei `.sln`:
   ```bash
   cd dll
   start samp-injector.sln
   ```
   Dies öffnet das Projekt in **Visual Studio**.
3. **Build konfigurieren:**
   - Überprüfen Sie in **Visual Studio** die Lösungskonfiguration. Es wird empfohlen, die Modi `Release` und `x86` **(32-Bit)** zu verwenden. Im Kontext von **GTA:SA** und **SA-MP**/**OMP** ist die **x86 (32-Bit)**-Architektur zwingend erforderlich.
4. **Kompilieren:**
   - Im Menü `Compilation` klicken Sie auf `Compile Solution` oder auf `Build samp-injector`.
   - Alternativ können Sie die folgenden Tastenkombinationen verwenden:
      - `Ctrl + Shift + B`, um die gesamte Lösung zu kompilieren.
      - `Ctrl + B` (sofern konfiguriert), um das aktuelle Projekt zu kompilieren.
   - Wenn alles korrekt konfiguriert ist, wird die Bibliothek `samp-injector.dll` im Verzeichnis `dll\Release` (oder `dll\Debug`, abhängig von Ihrer **build**-Konfiguration) erzeugt.

## Bibliotheken

Die Bibliotheken sind die grundlegenden Komponenten des **SA-MP Injector** und enthalten die zentrale Logik für Prozessmanipulation, **DLL-Injektion** und Parameterprüfung. Der Hauptvorteil der Verwendung dieser Bibliotheken liegt in der einfachen Initialisierung und Injektion, in der Regel durch einen einzigen Funktionsaufruf (oder Aufrufe mit spezifischen Parametern für Skriptsprachen).

### Überblick

Das Projekt basiert auf Bibliotheken, die die kritischen Funktionalitäten kapseln. Dies ermöglicht es anderen Projekten, die Fähigkeit, **GTA:SA** mit den erforderlichen **Multiplayer**-Modulen zu starten, einfach zu integrieren.

### Liste der Bibliotheken

| Sprache    | Name                   | Link zur Bibliothek/Dokumentation                |
| ---------- | ---------------------- | ------------------------------------------------ |
| C++        | **SA-MP Injector C++** | [Bibliothek ansehen](../../libraries/cpp)        |
| C#         | **SA-MP Injector C#**  | [Bibliothek ansehen](../../libraries/csharp)     |
| PowerShell | **SA-MP Injector PS**  | [Bibliothek ansehen](../../libraries/powershell) |

> [!WARNING]
> Die **PowerShell**-Bibliothek wurde eingestellt und erhält keine weiteren Updates oder Wartung. Dies geschah, weil die **Filter** von **GitHub** die Bibliothek als potenziell **schädlich** einstufen, da sie **Low-Level**-Operationen ausführt. In diesem Fall können sowohl das Konto des **Autors** als auch das Profil der **SPC** **gesperrt** und **markiert** werden. **Keine Sorge**: Die **PowerShell**-Bibliothek bleibt weiterhin verfügbar, sie wird jedoch **nicht mehr aktualisiert**.

## Lizenz

Copyright © **SA-MP Programming Community**

Diese Software ist unter den Bedingungen der MIT-Lizenz ("Lizenz") lizenziert; Sie dürfen diese Software gemäß den Lizenzbedingungen nutzen. Eine Kopie der Lizenz finden Sie unter: [MIT License](https://opensource.org/licenses/MIT)

### Nutzungsbedingungen

#### 1. Gewährte Berechtigungen

Diese Lizenz gewährt jeder Person, die eine Kopie dieser Software und der zugehörigen Dokumentationsdateien erhält, kostenlos folgende Rechte:
* Die Software ohne Einschränkungen zu nutzen, zu kopieren, zu modifizieren, zusammenzuführen, zu veröffentlichen, zu verteilen, zu unterlizenzieren und/oder zu verkaufen
* Personen, denen die Software zur Verfügung gestellt wird, dies unter den folgenden Bedingungen zu gestatten

#### 2. Verpflichtende Bedingungen

Alle Kopien oder wesentliche Teile der Software müssen enthalten:
* Den obigen Urheberrechtshinweis
* Diesen Erlaubnishinweis
* Den nachstehenden Haftungsausschluss

#### 3. Urheberrecht

Die Software und alle zugehörige Dokumentation sind durch Urheberrechtsgesetze geschützt. Die **SA-MP Programming Community** behält die ursprünglichen Urheberrechte an der Software.

#### 4. Gewährleistungsausschluss und Haftungsbeschränkung

DIE SOFTWARE WIRD "WIE BESEHEN" ZUR VERFÜGUNG GESTELLT, OHNE JEGLICHE AUSDRÜCKLICHE ODER IMPLIZITE GEWÄHRLEISTUNG, EINSCHLIESSLICH, ABER NICHT BESCHRÄNKT AUF DIE GEWÄHRLEISTUNG DER MARKTGÄNGIGKEIT, DER EIGNUNG FÜR EINEN BESTIMMTEN ZWECK UND DER NICHTVERLETZUNG VON RECHTEN DRITTER.

DIE AUTOREN ODER URHEBERRECHTSINHABER SIND IN KEINEM FALL HAFTBAR FÜR ANSPRÜCHE, SCHÄDEN ODER ANDERE VERPFLICHTUNGEN, OB IN EINER VERTRAGS- ODER DELIKTKLAGE, DIE AUS ODER IN VERBINDUNG MIT DER SOFTWARE ODER DER NUTZUNG ODER ANDEREN GESCHÄFTEN MIT DER SOFTWARE ENTSTEHEN.

---

For detailed information about the MIT License, visit: https://opensource.org/licenses/MIT