# SA-MP Injector C++

<div align="center">

![C++](https://img.shields.io/badge/C%2B%2B-14%2F17%2F20-00599C?style=for-the-badge&logo=cplusplus)
![Platform](https://img.shields.io/badge/Platform-Windows-blue?style=for-the-badge&logo=windows&logoColor=white)
![Architecture](https://img.shields.io/badge/Architecture-x86%20(32--bit)-lightgrey?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)

**Eine C++ Bibliothek zum Starten und Automatisieren der Verbindung von SA-MP- und OMP-Clients mit Servern durch DLL-Injektion.**

</div>

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

- [SA-MP Injector C++](#sa-mp-injector-c)
  - [Sprachen](#sprachen)
  - [Inhaltsverzeichnis](#inhaltsverzeichnis)
  - [Überblick und Zweck](#überblick-und-zweck)
  - [Designprinzipien](#designprinzipien)
    - [Vollständig `Header-Only`](#vollständig-header-only)
    - [Sichere Ressourcenverwaltung (RAII)](#sichere-ressourcenverwaltung-raii)
    - [Robustheit und Fehlerüberprüfung](#robustheit-und-fehlerüberprüfung)
    - [Flexibilität der C++-Standards](#flexibilität-der-c-standards)
  - [Systemanforderungen](#systemanforderungen)
    - [Für die Entwicklungsumgebung](#für-die-entwicklungsumgebung)
    - [Für die Laufzeitumgebung](#für-die-laufzeitumgebung)
  - [Schnellstart](#schnellstart)
    - [Integration in das Projekt](#integration-in-das-projekt)
    - [Vereinfachtes Anwendungsbeispiel](#vereinfachtes-anwendungsbeispiel)
  - [Struktur der Bibliothek](#struktur-der-bibliothek)
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
  - [Der detaillierte Injektionsprozess](#der-detaillierte-injektionsprozess)
    - [1. Initialisierungsanforderung](#1-initialisierungsanforderung)
    - [2. Vorbereitung der Umgebung](#2-vorbereitung-der-umgebung)
    - [3. Überprüfung der Integrität und der Parameter](#3-überprüfung-der-integrität-und-der-parameter)
    - [4. Vorbereitung der Argumente für das Spiel](#4-vorbereitung-der-argumente-für-das-spiel)
    - [5. Initialisierung des Spielprozesses (Angehalten)](#5-initialisierung-des-spielprozesses-angehalten)
    - [6. Injektion der SA-MP-Bibliothek (`samp.dll`)](#6-injektion-der-sa-mp-bibliothek-sampdll)
    - [7. Injektion der OMP-Bibliothek (`omp-client.dll`) - Bedingt](#7-injektion-der-omp-bibliothek-omp-clientdll---bedingt)
    - [8. Aktivierung des Spiels](#8-aktivierung-des-spiels)
  - [Diagnose von Fehlern und Ausfällen](#diagnose-von-fehlern-und-ausfällen)
    - [Fehler bei der Eingabevalidierung](#fehler-bei-der-eingabevalidierung)
      - [Ungültiger Benutzername](#ungültiger-benutzername)
      - [Ungültiger Verbindungsport](#ungültiger-verbindungsport)
      - [Fehlende wesentliche Ressourcen](#fehlende-wesentliche-ressourcen)
    - [Fehler bei der Prozessverwaltung](#fehler-bei-der-prozessverwaltung)
      - [Schwierigkeiten beim Starten des Spielprozesses](#schwierigkeiten-beim-starten-des-spielprozesses)
    - [Probleme bei der DLL-Injektion](#probleme-bei-der-dll-injektion)
      - [`LoadLibraryW` kann nicht gefunden werden](#loadlibraryw-kann-nicht-gefunden-werden)
      - [Fehler bei der Reservierung von Remote-Speicher](#fehler-bei-der-reservierung-von-remote-speicher)
      - [Daten können nicht in den Prozess geschrieben werden](#daten-können-nicht-in-den-prozess-geschrieben-werden)
      - [Fehler beim Erstellen des Injektions-Threads](#fehler-beim-erstellen-des-injektions-threads)
      - [Zeitüberschreitung oder Fehler beim Warten auf die Injektion](#zeitüberschreitung-oder-fehler-beim-warten-auf-die-injektion)
      - [Interner Fehler bei der DLL-Injektion](#interner-fehler-bei-der-dll-injektion)
    - [Schwierigkeiten bei der Wiederaufnahme der Spielausführung](#schwierigkeiten-bei-der-wiederaufnahme-der-spielausführung)
  - [Lizenz](#lizenz)
    - [Nutzungsbedingungen](#nutzungsbedingungen)
      - [1. Gewährte Berechtigungen](#1-gewährte-berechtigungen)
      - [2. Verpflichtende Bedingungen](#2-verpflichtende-bedingungen)
      - [3. Urheberrecht](#3-urheberrecht)
      - [4. Gewährleistungsausschluss und Haftungsbeschränkung](#4-gewährleistungsausschluss-und-haftungsbeschränkung)

## Überblick und Zweck

**SA-MP Injector C++** ist eine kompakte und leicht integrierbare C++-Bibliothek, die entwickelt wurde, um den Prozess des Startens und der Verbindung mit San Andreas Multiplayer (SA-MP) und Open Multiplayer (OMP) Servern zu automatisieren. Anstatt die `gta_sa.exe` direkt zu starten, lädt diese Lösung die Bibliotheken `samp.dll` oder `omp-client.dll` programmgesteuert und kontrolliert in den Prozess des Spiels Grand Theft Auto: San Andreas.

Ihr Hauptziel ist es, C++-Entwicklern zu ermöglichen, benutzerdefinierte `Launcher`, Community-Verwaltungstools oder Dienstprogramme zu erstellen, die GTA:SA mit vordefinierten Verbindungsparametern (wie Benutzername, IP-Adresse, Port und Passwort) starten müssen und dabei eine flüssige und automatisierte Benutzererfahrung bieten.

## Designprinzipien

Die Architektur von **SA-MP Injector C++** basiert auf modernen Designprinzipien, die auf Sicherheit, Effizienz und Benutzerfreundlichkeit ausgerichtet sind.

### Vollständig `Header-Only`

Diese Bibliothek wird ausschließlich über Header-Dateien (`.hpp`) verteilt. Dies vereinfacht die Integration in C++-Projekte erheblich, da keine separaten Bibliotheken kompiliert, `Linker` konfiguriert oder Binärabhängigkeiten verwaltet werden müssen.
- **Sofortige Integration:** Fügen Sie einfach die relevanten `Header` ein.
- **Tiefgreifende Optimierung:** Der Compiler kann aggressives `Inlining` und `Link-Time`-Optimierungen durchführen, was zu einem kompakteren und schnelleren Endcode führt.

### Sichere Ressourcenverwaltung (RAII)

Die Bibliothek verwendet das **RAII (Resource Acquisition Is Initialization)**-Muster ausgiebig. Kritische Systemressourcen wie `Handles` von Prozessen und `Threads` unter Windows werden von `std::unique_ptr` mit benutzerdefinierten `Deleters` gekapselt. Dies stellt sicher, dass Ressourcen unabhängig vom Ausführungsfluss oder dem Auftreten von Ausnahmen immer korrekt freigegeben werden, wodurch Lecks vermieden und die Stabilität der Anwendung verbessert wird.

### Robustheit und Fehlerüberprüfung

Jeder kritische Schritt der Injektion wird von strengen Validierungen vorangegangen und von Fehlerprüfungen der Windows-API gefolgt. Detaillierte Fehlermeldungen werden dem Endbenutzer über Dialogfelder bereitgestellt, wann immer möglich mit Systembeschreibungen (`GetLastError()`). Dieser Ansatz minimiert die Wahrscheinlichkeit von undefiniertem Verhalten und bietet eine klare Diagnose im Fehlerfall.

### Flexibilität der C++-Standards

Die Bibliothek wurde so konzipiert, dass sie mit verschiedenen C++-Standards von C++14 bis C++20 kompatibel ist. Dies wird durch bedingte Makros erreicht, die die Verwendung moderner Funktionen (wie `std::string_view`, `std::filesystem` und `std::optional` aus C++17+) ermöglichen, wenn diese verfügbar sind, während ein `Fallback` auf äquivalente Konstrukte in C++14 beibehalten wird. Dieser Ansatz gewährleistet eine breite Kompatibilität, ohne auf Modernität zu verzichten.

## Systemanforderungen

### Für die Entwicklungsumgebung

- **C++-Compiler:** Kompatibel mit **C++14 oder höher**.
   - Microsoft Visual C++ (Visual Studio 2015, 2017, 2019, 2022)
   - GCC (Version 5 oder neuer)
   - Clang (Version 3.6 oder neuer)
- **Betriebssystem:** **Windows**.
- **Windows SDK:** Erforderlich für den Zugriff auf die Betriebssystem-APIs.
- **Kompilierungsarchitektur:** **x86 (32-Bit)**. Dies ist eine strikte Anforderung, da `gta_sa.exe` und die SA-MP/OMP-DLLs ausschließlich auf dieser Architektur laufen.

### Für die Laufzeitumgebung

- **Betriebssystem:** Jede moderne **Windows**-Version, die mit der kompilierten Binärdatei kompatibel ist.
- **Grand Theft Auto: San Andreas (GTA:SA):** Eine gültige Installation des Spiels ist zwingend erforderlich.
- **DLLs des SA-MP- oder OMP-Clients:** Die Dateien `samp.dll` oder `omp-client.dll` müssen im Hauptverzeichnis des Spiels vorhanden sein, entsprechend dem gewünschten Injektionstyp.

## Schnellstart

Die `Header-Only`-Natur der Bibliothek erleichtert ihre Einbindung in jedes C++-Projekt.

### Integration in das Projekt

1. **Header herunterladen:** Holen Sie sich die `.hpp`-Dateien der Bibliothek (durch Klonen des Repositorys oder direktes Herunterladen).
2. **Dateien organisieren:** Es wird empfohlen, einen Unterordner in Ihrem Projekt für die `Header` der Bibliothek zu erstellen, z. B. `MeinProjekt/libraries/samp-injector/`.
3. **Architektur festlegen:** Konfigurieren Sie Ihr Projekt so, dass es für die **x86 (32-Bit)**-Architektur kompiliert wird.

```cpp
// Beispiel für eine Verzeichnisstruktur
MeinProjekt/
├── src/
│   └── main.cpp
├── libraries/
│   └── samp-injector/
│       ├── constants.hpp
│       ├── error_utils.hpp
│       ├── injector.hpp // Der einzubindende Haupt-Header
│       └── ... (andere Header)
└── built/ (Ihr Ausgabeverzeichnis)
```

### Vereinfachtes Anwendungsbeispiel

Um die Verbindung zu einem Server zu automatisieren, rufen Sie einfach die Funktion `Initialize_Game` auf und geben Sie die Details an.

```cpp
#include <iostream>
#include <string>
//
#include "samp-launcher/injector.hpp" // Binden Sie den Haupt-Header ein

int main() {
    // Parameter für den Spielstart und die Verbindung
    std::wstring inject_type = L"samp"; // Oder L"omp" für Open Multiplayer
    std::wstring game_folder = L"C:\\Games\\GTA San Andreas"; // Vollständiger Pfad zum GTA:SA-Ordner
    std::wstring nickname = L"Name";
    std::wstring ip = L"127.0.0.1";
    std::wstring port = L"7777";
    std::wstring password = L""; // Leer lassen, wenn kein Passwort vorhanden ist

    // Der Hauptaufruf zum Starten des Spiels und Injizieren der DLL
    Initialize_Game(inject_type, game_folder, nickname, ip, port, password);

    // Im Fehlerfall wird automatisch eine Windows-Fehlermeldungsbox angezeigt.

    return 0;
}
```

## Struktur der Bibliothek

Die Bibliothek ist sorgfältig in mehrere Header-Dateien modularisiert, von denen jede klar definierte Verantwortlichkeiten hat, was die Organisation, Wartung und Wiederverwendbarkeit erleichtert.

### 1. `constants.hpp`

Diese Datei ist das **zentrale Repository** der Bibliothek und dient als zentralisierte Ablage für alle festen und unveränderlichen Werte, die das Verhalten und die Interoperabilität von **SA-MP Injector C++** bestimmen. Ihre Organisation nach logischen Kategorien fördert nicht nur die Klarheit und Lesbarkeit des Codes, sondern erleichtert auch die Wartung und gewährleistet eine strenge Konsistenz im gesamten Ökosystem der Bibliothek.

Jede Konstante wird mit `CONSTEXPR_VAR` definiert, was sich zu `inline constexpr` (für C++17+) oder `static constexpr` (für C++14) erweitert und sicherstellt, dass diese Werte zur Kompilierzeit ausgewertet werden, was die Leistung und Typsicherheit optimiert.

Die Organisation der Konstanten nach Kategorien erleichtert das Verständnis ihres Zwecks:

- **Spielbezogene Konstanten (`Game Related Constants`)**
   - `MIN_PORT`: Ein `int`, der die kleinste gültige Portnummer für die Verbindung zu einem Server definiert (Wert: `1`).
   - `MAX_PORT`: Ein `int`, der die größte gültige Portnummer für die Verbindung zu einem Server festlegt (Wert: `65535`).
   - `MAX_NICKNAME_LENGTH`: Ein `int`, der die maximal zulässige Länge für den Spielernamen angibt (Wert: `23` Zeichen), eine Grenze, die durch die Spezifikationen des SA-MP/OMP-Clients auferlegt wird.

- **Namen wesentlicher Dateien (`File Names`)**
   - `SAMP_DLL_NAME`: Ein `const wchar_t*`, der den Dateinamen der Hauptbibliothek des SA-MP-Clients enthält (Wert: `L"samp.dll"`). Unverzichtbar für die Injektion des klassischen Clients.
   - `OMP_DLL_NAME`: Ein `const wchar_t*`, der den Dateinamen der Bibliothek des Open Multiplayer-Clients enthält (Wert: `L"omp-client.dll"`). Wird speziell verwendet, wenn die Injektion vom Typ OMP ist.
   - `GAME_EXE_NAME`: Ein `const wchar_t*`, der den Namen der ausführbaren Datei des Basisspiels Grand Theft Auto: San Andreas speichert (Wert: `L"gta_sa.exe"`). Das Hauptziel der Injektion.

- **System-APIs und -Funktionen (`System Libraries and Functions`)**
   - `KERNEL32_DLL`: Ein `const wchar_t*`, der den Namen der Windows-Systembibliothek (`L"kernel32.dll"`) definiert. Diese DLL ist von entscheidender Bedeutung, da sie die vom Injector verwendeten Funktionen zur Prozess- und Speicherverwaltung beherbergt. Die Verwendung von `wchar_t` gewährleistet die Kompatibilität mit API-Funktionen, die Breitzeichen verarbeiten, wie `GetModuleHandleW`.
   - `LOAD_LIBRARY_FUNC`: Ein `const char*` mit dem Namen der Funktion zum dynamischen Laden einer DLL (Wert: `"LoadLibraryW"`). Obwohl die Bibliothek hauptsächlich mit Breitzeichen arbeitet, erfordert die `GetProcAddress`-Funktion der Windows-API einen Funktionsnamen im ANSI-Format (`char*`).

- **Befehlszeilenargumente (`Command Line Arguments`)**
   - Diese Konstanten definieren die Präfixe für die Argumente, die an die `gta_sa.exe` übergeben werden, um die Client-Verbindung zu konfigurieren. Sie werden in `Wide Character` (`const wchar_t*`) für die Kompatibilität mit `CreateProcessW` bereitgestellt.
      - `CMD_ARG_CONFIG`: Argument für allgemeine Konfigurationen (Wert: `L"-c"`).
      - `CMD_ARG_NICKNAME`: Argument für den Spielernamen (Wert: `L"-n"`).
      - `CMD_ARG_HOST`: Argument für die IP-Adresse des Servers (Wert: `L"-h"`).
      - `CMD_ARG_PORT`: Argument für den Port des Servers (Wert: `L"-p"`).
      - `CMD_ARG_PASSWORD`: Argument für das Passwort des Servers (Wert: `L"-z"`). Wird nur verwendet, wenn ein Passwort angegeben wird.

- **Bezeichner für Injektionstypen (`Injection types as strings`)**
   - `INJECT_TYPE_SAMP`: Ein `const wchar_t*` für die String-Repräsentation des SA-MP-Injektionstyps (Wert: `L"samp"`).
   - `INJECT_TYPE_OMP`: Ein `const wchar_t*` für die String-Repräsentation des OMP-Injektionstyps (Wert: `L"omp"`).

- **Titel für Fehlermeldungen (`Error message titles`)**
   - `ERROR_TITLE_SAMP`: Ein `const wchar_t*`, der den Standardtitel für Fehlerdialogfelder im Zusammenhang mit SA-MP-Fehlern definiert (Wert: `L"SA-MP Injector Error - SPC"`).
   - `ERROR_TITLE_OMP`: Ein `const wchar_t*`, der den Standardtitel für Fehlerdialogfelder im Zusammenhang mit OMP-Fehlern definiert (Wert: `L"OMP Injector Error - SPC"`).

- **Flags zur Prozesserstellung (`Process creation`)**
   - `PROCESS_CREATION_FLAGS`: Ein `DWORD`, das die Flags kapselt, die an `CreateProcessW` übergeben werden. Entscheidend ist, dass es `CREATE_SUSPENDED` (`0x00000004`) enthält, das den Spielprozess in einem angehaltenen Zustand startet, und `DETACHED_PROCESS` (`0x00000008`), das den neuen Prozess von der Konsole des übergeordneten Prozesses entkoppelt.

- **Zeitüberschreitungen (`Timeouts`)**
   - `DLL_INJECTION_TIMEOUT_MS`: Ein `DWORD`, das die maximale Zeit (in Millisekunden) angibt, die die Bibliothek auf den Abschluss des Remote-`Threads` wartet, der für die DLL-Injektion verantwortlich ist (Wert: `10000ms` oder 10 Sekunden).

- **Flags für die Speicherzuweisung (`Memory allocation`)**
   - Diese Konstanten werden für die API-Aufrufe zur Speicherverwaltung wie `VirtualAllocEx` und `VirtualProtect` verwendet.
      - `MEM_COMMIT`: Ein `DWORD`, das Seiten im virtuellen Speicher reserviert und sie "committet" (physischen Speicher zuweist) (Wert: `0x1000`).
      - `MEM_RESERVE`: Ein `DWORD`, das nur einen Bereich des virtuellen Adressraums für die spätere Verwendung reserviert (Wert: `0x2000`).
      - `MEM_RELEASE`: Ein `DWORD`, das eine Region von Seiten decommittet und freigibt (Wert: `0x8000`).
      - `MEMORY_ALLOCATION_TYPE`: Eine Kombination aus `MEM_COMMIT` und `MEM_RESERVE`, die verwendet wird, um den anfänglichen Speicher für den DLL-Pfad im Remote-Prozess zuzuweisen.
      - `MEMORY_PROTECTION`: Ein `DWORD`, das die Speicherschutzberechtigungen definiert (Wert: `PAGE_READWRITE` oder `0x04` in der Windows-API), was Lese- und Schreibzugriff auf den zugewiesenen Speicher ermöglicht.

### 2. `types.hpp`

Diese prägnante Datei führt eine `enum class` ein, um die verschiedenen Injektionsmodalitäten zu typisieren. Die Verwendung eines Aufzählungstyps anstelle von Zeichenkettenliteralen erhöht die Codesicherheit, verhindert Tippfehler und verbessert die Lesbarkeit.

- **`Inject_Type`:** Eine `enum class` mit zwei Mitgliedern: `SAMP` und `OMP`, die die zu injizierenden Client-Typen repräsentieren.

```cpp
// Beispiel für types.hpp
namespace Types {
    enum class Inject_Type {
        SAMP, // Zeigt die Injektion für den SA-MP-Client an
        OMP // Zeigt die Injektion für den Open Multiplayer-Client an
    };
}
```

### 3. `version.hpp`

Als Kompatibilitätsadapter erkennt dieser Header dynamisch den vom Compiler verwendeten C++-Standard. Er definiert bedingte Makros (`SAMP_INJECTOR_CXX_14`, `SAMP_INJECTOR_CXX_MODERN`), die die Bibliothek anweisen, die fortschrittlichsten C++-Funktionalitäten (wie `std::string_view` oder `std::filesystem`) zu verwenden, wenn diese verfügbar sind, während die volle Funktionalität in C++14-Umgebungen sichergestellt wird.

- **`SAMP_INJECTOR_CXX_14`:** Definiert, wenn der C++-Standard C++14 ist.
- **`SAMP_INJECTOR_CXX_MODERN`:** Definiert für C++17 oder höher, was neuere Sprachfunktionen aktiviert.
- **`SAMP_INJECTOR_NODISCARD`:** Passt das `[[nodiscard]]`-Attribut an die C++-Versionen an, die es unterstützen, und fördert die Überprüfung von Rückgabewerten.

```cpp
// Beispiel eines relevanten Ausschnitts aus version.hpp
#if (defined(_MSC_VER) && _MSVC_LANG >= 201703L) || __cplusplus >= 201703L
    #define SAMP_INJECTOR_CXX_MODERN // Aktiviert moderne Funktionen von C++17+
#endif

#if defined(SAMP_INJECTOR_CXX_MODERN)
    #define SAMP_INJECTOR_NODISCARD [[nodiscard]] // Verwendet das nodiscard-Attribut von C++17
#elif defined(SAMP_INJECTOR_CXX_14)
    #define SAMP_INJECTOR_NODISCARD // Für C++14 ist das Attribut deaktiviert
#endif
```

### 4. `error_utils.hpp`

Dieses Dienstprogramm widmet sich der Verwaltung und Präsentation von Fehlerrückmeldungen. Es abstrahiert die Windows-Mechanismen zum Abrufen von Systemfehlermeldungen und bietet eine einheitliche Schnittstelle, um den Benutzer über Probleme zu informieren.

- **`Get_System_Error_Message`:** Übersetzt einen Windows-Fehlercode (`GetLastError()`) in eine lesbare `std::wstring`, was für eine präzise Diagnose entscheidend ist.
- **`Show_Error`:** Zeigt ein Dialogfeld (`MessageBoxW`) an, das die bereitgestellte Fehlermeldung mit einem spezifischen Titel für SA-MP oder OMP enthält, um eine klare Kommunikation mit dem Benutzer zu gewährleisten.

```cpp
// Beispiel eines relevanten Ausschnitts aus error_utils.hpp
namespace Error_Utils {
    SAMP_INJECTOR_NODISCARD
    inline std::wstring Get_System_Error_Message(DWORD error_code) {
        if (error_code == 0)
            return L"No error occurred.";
        
        // ... Logik zur Formatierung der Systemnachricht ...
    }

    inline void Show_Error(std::wstring_view message, Types::Inject_Type inject_type) {
        const std::wstring title = (inject_type == Types::Inject_Type::SAMP) ? Constants::ERROR_TITLE_SAMP : Constants::ERROR_TITLE_OMP;
        MessageBoxW(nullptr, message.data(), title.c_str(), MB_OK | MB_ICONERROR);
    }
}
```

### 5. `validation.hpp`

Als vorderste Front der Robustheit der Bibliothek bietet dieser Header strenge Routinen zur Überprüfung der Gültigkeit von Eingabedaten und der Anwesenheit der erforderlichen Dateien. Diese Prüfungen werden vor jeder Low-Level-Interaktion mit dem System durchgeführt, um Laufzeitrisiken zu minimieren und proaktives Feedback zu geben.

- **`Validate_Port`:** Validiert, ob die Port-Zeichenkette eine Ganzzahl darstellt und ob diese sich innerhalb des konfigurierten Bereichs (`MIN_PORT` bis `MAX_PORT`) befindet.
- **`Validate_Nickname`:** Überprüft, ob der Nickname nicht leer ist und seine Länge `MAX_NICKNAME_LENGTH` nicht überschreitet.
- **`Validate_Files`:** Bestätigt die physische Existenz von `gta_sa.exe`, `samp.dll` und, bedingt für die OMP-Injektion, `omp-client.dll`. Die Implementierung passt sich an `std::filesystem` (C++17+) oder `GetFileAttributesW` (C++14) an.

```cpp
// Beispiel eines relevanten Ausschnitts aus validation.hpp
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
        
        // ... Weitere Dateiüberprüfungen ...
        return true;
    }
}
```

### 6. `resource_handle.hpp`

Implementiert eine elegante und sichere Strategie für die Verwaltung von Betriebssystemressourcen wie den `HANDLE`s von Windows. Durch die Verwendung des RAII-Prinzips wird sichergestellt, dass alle zugewiesenen Ressourcen ordnungsgemäß freigegeben werden, um Lecks zu vermeiden und die Stabilität der Anwendung zu erhöhen.

- **`Unique_Resource`:** Ein `alias template`, das `std::unique_ptr` anpasst, um mit benutzerdefinierten `Deleters` zu arbeiten, was die Verwaltung jeder Art von Ressource ermöglicht, die eine spezifische Freigabefunktion benötigt.
- **`Make_Unique_Handle`:** Eine praktische `Factory`-Funktion, die einen vorkonfigurierten `Unique_Resource` für Windows-`HANDLE`s erstellt und zurückgibt. Der zugehörige `Deleter` ruft `CloseHandle` automatisch auf, wenn der `Unique_Resource` aus dem Geltungsbereich gerät, und gewährleistet so die sofortige Freigabe der Ressource.

```cpp
// Beispiel eines relevanten Ausschnitts aus resource_handle.hpp
namespace Resource_Handle {
    // Ein benutzerdefinierter std::unique_ptr zur Verwaltung von Systemressourcen.
    template<typename T, typename Deleter>
    using Unique_Resource = std::unique_ptr<std::remove_pointer_t<T>, Deleter>;

    // Erstellt einen Unique_Resource für einen HANDLE mit einem Deleter, der CloseHandle aufruft.
    template<typename T>
    inline auto Make_Unique_Handle(T handle) {
        return Unique_Resource<T, std::function<void(T)>>(handle, [](T h) {
            if (h && h != INVALID_HANDLE_VALUE) // Stellt sicher, dass das Handle gültig ist, bevor es geschlossen wird
                CloseHandle(h);
        });
    }
}
```

### 7. `privileges.hpp`

Diese Komponente ist für die Konfiguration der Sicherheitsumgebung des Anwendungsprozesses verantwortlich. Sie enthält die Funktionalität zur Erhöhung der Berechtigungen, insbesondere die Aktivierung des Debug-Privilegs (`SE_DEBUG_NAME`), was eine grundlegende Voraussetzung dafür ist, dass die Bibliothek DLL-Injektionsoperationen in externen Windows-Prozessen durchführen kann.

- **`Enable_Debug_Privilege`:** Diese Funktion versucht, das `SE_DEBUG_NAME`-Privileg für den laufenden Prozess zu erwerben und zu aktivieren. Es ist ein entscheidender erster Schritt, um der Anwendung die notwendigen Berechtigungen zu gewähren, um andere Prozesse zu manipulieren, wie z. B. Speicher zuzuweisen und Remote-`Threads` zu erstellen. Gibt `true` bei Erfolg zurück.

```cpp
// Beispiel eines relevanten Ausschnitts aus privileges.hpp
namespace Privileges {
    inline bool Enable_Debug_Privilege() {
        HANDLE token_handle;

        // Versucht, das Token des aktuellen Prozesses zu öffnen, um Berechtigungen anzupassen
        if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &token_handle))
            return false;

        auto handle_guard = Resource_Handle::Make_Unique_Handle(token_handle); // Sichere Verwaltung des Handles

        TOKEN_PRIVILEGES tp;
        LUID luid;

        // Sucht den LUID-Wert für das SE_DEBUG_NAME-Privileg
        if (!LookupPrivilegeValue(nullptr, SE_DEBUG_NAME, &luid))
            return false;
        
        tp.PrivilegeCount = 1;
        tp.Privileges[0].Luid = luid;
        tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED; // Aktiviert das Privileg

        // Passt die Berechtigungen des Prozesses an
        if (!AdjustTokenPrivileges(token_handle, FALSE, &tp, sizeof(TOKEN_PRIVILEGES), nullptr, nullptr))
            return false;

        return GetLastError() == ERROR_SUCCESS; // Gibt true zurück, wenn die Operation erfolgreich war (kein ausstehender Fehler)
    }
}
```

### 8. `process.hpp`

Dies ist eine der kritischsten Komponenten der Bibliothek, die die Low-Level-Implementierung für die Interaktion mit Windows-Prozessen enthält. Sie kapselt die komplexen Operationen der Erstellung des Spielprozesses, der Speicherzuweisung, des Schreibens von Daten und der Technik der DLL-Injektion durch die Erstellung von Remote-`Threads`.

- **`Process_Info` struct:** Eine interne Struktur, die die `Unique_Resource`s für das `HANDLE` des Prozesses (`process_handle`) und das `HANDLE` des Haupt-`Threads` (`thread_handle`) des Spiels speichert. Enthält eine `Resume()`-Methode, um den Haupt-`Thread` des Spiels wieder zu aktivieren, wenn die Injektion abgeschlossen ist.
- **`Injection_Status` enum class:** Definiert eine detaillierte Liste möglicher Ergebnisse für die DLL-Injektionsoperation, was eine präzise Fehlerdiagnose ermöglicht.
- **`Create_Game_Process`:**
   - Verwendet die `CreateProcessW`-Funktion der Windows-API, um die ausführbare Datei `gta_sa.exe` zu starten.
   - Es ist von entscheidender Bedeutung, dass der Prozess mit dem Flag `CREATE_SUSPENDED` (enthalten in `Constants::PROCESS_CREATION_FLAGS`) erstellt wird. Dies stellt sicher, dass das Spiel sofort nach seiner Erstellung angehalten wird, bevor irgendein Code ausgeführt wird, was eine sichere DLL-Injektion in einem stabilen Zustand ermöglicht.
   - Gibt ein `std::optional<Process_Info>` (für C++17+) oder ein `std::unique_ptr<Process_Info>` (für C++14) zurück, das die gekapselten `Handles` des Prozesses und des `Threads` enthält.
- **`Inject_DLL`:**
   - Implementiert die Standardtechnik der DLL-Injektion über `CreateRemoteThread`:
      1. **Abrufen der Adresse:** Unter Verwendung der Konstanten aus `constants.hpp` wird die Adresse der Funktion `LoadLibraryW` (aus `kernel32.dll`) ermittelt, die Windows zum dynamischen Laden von Bibliotheken verwendet.
      2. **Speicherzuweisung:** `VirtualAllocEx` wird verwendet, um einen Speicherblock im virtuellen Speicher des Spielprozesses (`gta_sa.exe`) zu reservieren. Dieser Block ist so dimensioniert, dass er den vollständigen Pfad der zu injizierenden DLL aufnehmen kann.
      3. **Schreiben des Pfads:** Der DLL-Pfad (z. B. `L"C:\\pfad\\zu\\samp.dll"`) wird dann über `WriteProcessMemory` in den remote zugewiesenen Speicher im Spielprozess kopiert.
      4. **Erstellen des Remote-Threads:** `CreateRemoteThread` startet einen neuen `Thread` im Kontext des Spielprozesses. Der Einstiegspunkt dieses `Threads` ist die Adresse von `LoadLibraryW`, und das übergebene Argument ist die Adresse der Zeichenkette des DLL-Pfads, die wir gerade geschrieben haben.
      5. **Überwachung:** Die Ausführung des Remote-`Threads` wird von `WaitForSingleObject` überwacht, bis er abgeschlossen ist oder der `DLL_INJECTION_TIMEOUT_MS` erreicht ist.
      6. **Erfolgsüberprüfung:** `GetExitCodeThread` wird verwendet, um den Rückgabewert des Remote-`Threads` zu überprüfen. Wenn `LoadLibraryW` erfolgreich war, gibt es die Basisadresse der geladenen DLL zurück (ein Wert ungleich null).
      7. **Bereinigung:** Der im Remote-Prozess zugewiesene Speicher wird mit `VirtualFreeEx` freigegeben.
   - Gibt einen `Injection_Status` zurück, der den Erfolg oder den spezifischen Fehlertyp der Injektion anzeigt.

```cpp
// Beispiel eines relevanten Ausschnitts aus process.hpp
class Process {
public:
    struct Process_Info {
        Resource_Handle::Unique_Resource<HANDLE, std::function<void(HANDLE)>> process_handle; // Prozess-Handle mit RAII-Verwaltung
        Resource_Handle::Unique_Resource<HANDLE, std::function<void(HANDLE)>> thread_handle; // Thread-Handle mit RAII-Verwaltung

        bool Resume() { // Setzt die Ausführung des Haupt-Threads des Spiels fort
            return thread_handle && ResumeThread(thread_handle.get()) != static_cast<DWORD>(-1);
        }
    };
    
    enum class Injection_Status { // Detaillierte Statuscodes für die DLL-Injektion
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

    // Erstellt den Spielprozess in einem angehaltenen Zustand
    std::optional<Process_Info> Create_Game_Process(const std::wstring& game_path, std::wstring& command_args, const std::wstring& working_dir) {
        // ... Logik von CreateProcessW mit CREATE_SUSPENDED ...
    }
    
    SAMP_INJECTOR_NODISCARD // Stellt sicher, dass der Rückgabewert verwendet wird
    Injection_Status Inject_DLL(HANDLE process, const std::wstring& DLL_path) {
        static const LPVOID load_library_addr = reinterpret_cast<LPVOID>(GetProcAddress(GetModuleHandleW(Constants::KERNEL32_DLL), Constants::LOAD_LIBRARY_FUNC));

        if (!load_library_addr)
            return Injection_Status::LOADLIBRARY_ADDRESS_FAILED;

        LPVOID remote_memory = VirtualAllocEx(process, nullptr, (DLL_path.length() + 1) * sizeof(wchar_t), Constants::MEMORY_ALLOCATION_TYPE, Constants::MEMORY_PROTECTION);

        if (!remote_memory)
            return Injection_Status::ALLOCATION_FAILED;

        auto memory_guard = Resource_Handle::Unique_Resource<LPVOID, std::function<void(LPVOID)>>(remote_memory, [process](LPVOID ptr) {
            if (ptr)
                VirtualFreeEx(process, ptr, 0, MEM_RELEASE); // Gibt den Speicher im Remote-Prozess frei
        });

        if (!WriteProcessMemory(process, remote_memory, DLL_path.c_str(), (DLL_path.length() + 1) * sizeof(wchar_t), nullptr))
            return Injection_Status::WRITE_FAILED;

        HANDLE remote_thread = CreateRemoteThread(process, nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(load_library_addr), remote_memory, 0, nullptr);

        if (!remote_thread)
            return Injection_Status::THREAD_CREATION_FAILED;

        auto thread_guard = Resource_Handle::Make_Unique_Handle(remote_thread); // Sichere Verwaltung des Remote-Thread-Handles

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

Dieser Header definiert die `Injector_Core`-Klasse, die als Kommandozentrale der Bibliothek dient. Sie orchestriert die logische Abfolge der Injektionsoperationen und verbindet die Module für Eingabevalidierung, Berechtigungsverwaltung und Prozessmanipulation. Hier wird der gesamte Arbeitsablauf der Injektion definiert.

- **`Injector_Core`:** Der Konstruktor dieser Klasse ist der Punkt, an dem `Privileges::Enable_Debug_Privilege()` aufgerufen wird. Dies stellt sicher, dass der Anwendungsprozess die notwendigen Berechtigungen für DLL-Injektionsoperationen besitzt, bevor irgendeine andere kritische Logik ausgeführt wird.
- **`Initialize_Game`:**
   1. **Umfassende Validierung:** Beginnt mit dem Aufruf der Validierungsfunktionen (`Validation::Validate_Port`, `Validation::Validate_Nickname`, `Validation::Validate_Files`), um sicherzustellen, dass alle Parameter und wesentlichen Ressourcen in Ordnung sind. Wenn eine Validierung fehlschlägt, wird sofort ein Fehler gemeldet.
   2. **Vorbereitung der Argumente:** Erstellt die vollständige Befehlszeile (`std::wstring`), die an `gta_sa.exe` übergeben wird und den Nicknamen, die IP, den Port und das bereitgestellte Passwort enthält.
   3. **Erstellung des angehaltenen Prozesses:** Ruft `Process::Create_Game_Process` auf, um `gta_sa.exe` in einem angehaltenen Zustand zu starten und die `Handles` des Prozesses und des Haupt-`Threads` zu erhalten.
   4. **Injektion von `samp.dll`:** Ruft `Inject_DLL_With_Status_Check` auf, um `samp.dll` in den Spielprozess zu injizieren. Diese Wrapper-Funktion ist auch dafür verantwortlich, den zurückgegebenen `Injection_Status` zu interpretieren und informative Fehlermeldungen anzuzeigen.
   5. **Bedingte Injektion von `omp-client.dll`:** Wenn der `inject_type` `Types::Inject_Type::OMP` ist, wird `omp-client.dll` auf die gleiche Weise wie `samp.dll` injiziert.
   6. **Wiederaufnahme des Spiels:** Nach allen erfolgreichen Injektionen wird `process_info.Resume()` aufgerufen, um dem Haupt-`Thread` des Spiels die Fortsetzung seiner Ausführung zu ermöglichen.
   7. **Fehlerbehandlung im Zyklus:** Jeder Fehler in einem dieser kritischen Schritte führt zu einem Aufruf von `Error_Utils::Show_Error`, der dem Benutzer klares Feedback gibt und sicherstellt, dass der Prozess ordnungsgemäß beendet wird (die `Handles` werden automatisch durch die `Unique_Resource`s freigegeben).
- **`Build_Command_Args`:** Eine Hilfsfunktion, die die Befehlszeilenargumente organisiert und verknüpft und bei Bedarf Anführungszeichen für Parameter hinzufügt, die Leerzeichen enthalten.
- **`Inject_DLL_With_Status_Check`:** Eine private Funktion, die als Wrapper für `Process::Inject_DLL` fungiert. Sie ordnet die verschiedenen `Injection_Status` verständlichen Fehlermeldungen zu, was die Fehlerbehandlung und die Kommunikation mit dem Benutzer erleichtert.

```cpp
// Beispiel eines relevanten Ausschnitts aus injector_core.hpp
namespace Injector {
    class Injector_Core {
    public:
        Injector_Core() { // Der Konstruktor aktiviert das Debug-Privileg
            Privileges::Enable_Debug_Privilege();
        }

        bool Initialize_Game(Types::Inject_Type inject_type, std::wstring_view folder, std::wstring_view nickname, std::wstring_view ip, std::wstring_view port, std::wstring_view password) {
            std::wstring error_message;

            // Sequenz der Eingabevalidierungen
            if (!Validation::Validate_Port(port, error_message))
                return (Error_Utils::Show_Error(error_message, inject_type), false);
            // ... andere Validierungen ...

            // Erstellt die Befehlszeilenargumente
            std::wstring args = Build_Command_Args({
                Command_Arg{Constants::CMD_ARG_NICKNAME, std::wstring(nickname)},
                // ... andere Argumente ...
            });

            Process process_core;
            // Erstellt den Spielprozess in einem angehaltenen Zustand
            auto process_info_opt = process_core.Create_Game_Process(game_path, args, std::wstring(folder));

            if (!process_info_opt)
                return false;

            auto& process_info = *process_info_opt;

            // Injiziert samp.dll und, bedingt, omp-client.dll
            if (!Inject_DLL_With_Status_Check(process_core, process_info.process_handle.get(), Constants::SAMP_DLL_NAME, samp_DLL_path.wstring(), inject_type))
                return false;
            
            if (inject_type == Types::Inject_Type::OMP) {
                if (!Inject_DLL_With_Status_Check(process_core, process_info.process_handle.get(), Constants::OMP_DLL_NAME, omp_DLL_path.wstring(), inject_type))
                    return false;
            }
            
            // Setzt den Haupt-Thread des Spiels fort
            if (!process_info.Resume())
                return (Error_Utils::Show_Error(L"Failed to resume the game process thread: " + Error_Utils::Get_System_Error_Message(GetLastError()), inject_type), false);

            return true;
        }
    };
}
```

### 10. `injector.hpp`

Dieser Header fungiert als Hauptfassade (`Facade`) der Bibliothek und bietet einen vereinfachten Einstiegspunkt für jede Anwendung, die die Injektionsfunktionalität nutzen möchte. Er abstrahiert die interne Komplexität von `Injector_Core` in einer einzigen, praktischen Funktion.

- **`Initialize_Game`:**
   - Diese statische Funktion ist die öffentliche Schnittstelle der Bibliothek.
   - Zuerst validiert sie die `inject_type_str` (ob `L"samp"` oder `L"omp"`) und konvertiert sie in die `enum class Types::Inject_Type`. Bei einer ungültigen Zeichenkette wird ein Fehler angezeigt und die Funktion beendet.
   - Anschließend erstellt sie eine Instanz von `Injector::Injector_Core`.
   - Schließlich delegiert sie die Ausführung der Hauptlogik an `Injector_Core::Initialize_Game`, wo der gesamte Prozess der Validierung, Prozesserstellung und DLL-Injektion orchestriert wird.

```cpp
// Beispiel eines relevanten Ausschnitts aus injector.hpp
// Die öffentliche Schnittstelle zum Starten des Spiels
#if defined(SAMP_INJECTOR_CXX_MODERN)
inline bool Initialize_Game(std::wstring_view inject_type, std::wstring_view folder, std::wstring_view nickname, std::wstring_view ip, std::wstring_view port, std::wstring_view password) {
#elif defined(SAMP_INJECTOR_CXX_14)
inline bool Initialize_Game(const std::wstring& inject_type, const std::wstring& folder, const std::wstring& nickname, const std::wstring& ip, const std::wstring& port, const std::wstring& password) {
#endif
    Types::Inject_Type type;

    // Konvertiert die Injektionstyp-Zeichenkette in das entsprechende Enum
    if (inject_type == Constants::INJECT_TYPE_SAMP)
        type = Types::Inject_Type::SAMP;
    else if (inject_type == Constants::INJECT_TYPE_OMP)
        type = Types::Inject_Type::OMP;
    else
        // Zeigt einen Fehler an, wenn der Injektionstyp ungültig ist
        return (Error_Utils::Show_Error(L"Ungültiger Injektionsmodus. Verwenden Sie 'samp' oder 'omp'.", Types::Inject_Type::SAMP), false);

    Injector::Injector_Core injector; // Erstellt die Instanz des Injector-Kerns

    // Delegiert die Hauptlogik an den Injector_Core
    return injector.Initialize_Game(type, folder, nickname, ip, port, password);
}
```

## Der detaillierte Injektionsprozess

Die Kernfunktionalität dieser Bibliothek besteht darin, eine präzise Abfolge von Operationen zu orchestrieren, um die DLLs des SA-MP- oder OMP-Clients in den GTA:SA-Prozess zu injizieren. Dieser Zyklus ist sorgfältig geplant, um Stabilität und Kompatibilität zu gewährleisten.

### 1. Initialisierungsanforderung

Der Prozess beginnt mit dem Aufruf der globalen Funktion `Initialize_Game` (`injector.hpp`), die als Hauptkontaktpunkt für die Anwendung dient, die die Bibliothek verwendet. Diese Funktion empfängt alle entscheidenden Parameter, wie den gewünschten Injektionstyp (SA-MP oder OMP), das Spielverzeichnis und die Serververbindungsdaten (Nickname, IP, Port, Passwort).

### 2. Vorbereitung der Umgebung

Bei ihrem Aufruf erstellt die Funktion `Initialize_Game` eine Instanz von `Injector::Injector_Core`. Im Konstruktor dieser Klasse (`injector_core.hpp`) wird der erste und wesentliche Schritt zur Konfiguration der Umgebung ausgeführt: die Erhöhung der Berechtigungen.

> [!NOTE]
> `Privileges::Enable_Debug_Privilege()`: Dieser Aufruf (`privileges.hpp`) gewährt dem Anwendungsprozess das `SE_DEBUG_NAME`-Privileg. Dieses Privileg ist von entscheidender Bedeutung, da es der Anwendung ermöglicht, Low-Level-Operationen in anderen Windows-Prozessen durchzuführen, wie das Lesen und Schreiben in deren Speicher und das Erstellen von Remote-`Threads` – grundlegende Aktionen für die DLL-Injektionstechnik.

### 3. Überprüfung der Integrität und der Parameter

Nach der Anpassung der Berechtigungen führt die Methode `Injector_Core::Initialize_Game` eine Reihe strenger Validierungen durch. Dies ist eine präventive Phase, die die Wahrscheinlichkeit von Fehlern in späteren Schritten minimiert und dem Benutzer sofortiges Feedback gibt.

- **Port-Validierung:** `Validation::Validate_Port` überprüft, ob die Verbindungsportnummer korrekt formatiert ist und sich im Bereich von `1` bis `65535` (`constants.hpp`) befindet.
- **Nickname-Validierung:** `Validation::Validate_Nickname` stellt sicher, dass der Spieler-Nickname nicht leer ist und die Grenze von `23` Zeichen nicht überschreitet.
- **Überprüfung wesentlicher Dateien:** `Validation::Validate_Files` inspiziert das Spielverzeichnis, um die Anwesenheit von `gta_sa.exe`, `samp.dll` und, falls die Injektion vom Typ OMP ist, auch `omp-client.dll` zu bestätigen.

> [!WARNING]
> Jeder Fehler in diesem Schritt führt zur sofortigen Anzeige einer `MessageBox` mit einer detaillierten Fehlermeldung (`error_utils.hpp`) und zur Unterbrechung des Injektionsprozesses. Dies vermeidet vergebliche Versuche, mit einer ungültigen Konfiguration fortzufahren.

### 4. Vorbereitung der Argumente für das Spiel

Nach erfolgreicher Validierung ist die Funktion `Injector_Core::Build_Command_Args` dafür verantwortlich, die formatierte Befehlszeile zu erstellen, die an `gta_sa.exe` übergeben wird. Diese Befehlszeile enthält alle notwendigen Parameter, damit sich der SA-MP/OMP-Client automatisch mit einem Server verbinden kann, wie `-n "nickname" -h "IP" -p "Port" -z "Passwort"`.

### 5. Initialisierung des Spielprozesses (Angehalten)

Die Komponente `Process` (`process.hpp`) ist dann dafür verantwortlich, die ausführbare Datei von GTA:SA zu starten.

> [!IMPORTANT]
> Die Funktion `Process::Create_Game_Process` verwendet das Flag `CREATE_SUSPENDED` (`constants.hpp`) beim Aufruf der Windows-API `CreateProcessW`. Dies ist eine kritische Designmaßnahme: Das Spiel wird in den Speicher geladen und sein Haupt-`Thread` wird erstellt, aber seine Ausführung wird **angehalten**. Dies schafft eine kontrollierte und stabile Umgebung, ideal für die Injektion von DLLs, bevor das Spiel seine eigenen Abwehrmechanismen oder interne Logik initialisieren kann. Die `Handles` des Prozesses und des `Threads` werden sicher über `Resource_Handle::Unique_Resource` abgerufen und verwaltet.

### 6. Injektion der SA-MP-Bibliothek (`samp.dll`)

Mit dem Spielprozess im angehaltenen Zustand kann die Injektion von `samp.dll` sicher durchgeführt werden. Die Methode `Injector_Core::Inject_DLL_With_Status_Check` delegiert diese Aufgabe an `Process::Inject_DLL`, das die folgenden Schritte der `Remote-Thread-Injektion`-Technik ausführt:

1. **Lokalisierung der Funktion `LoadLibraryW`:** Die Adresse der Funktion `LoadLibraryW` wird identifiziert. Diese Operation verwendet die Konstanten `Constants::KERNEL32_DLL` und `Constants::LOAD_LIBRARY_FUNC`, um ein `Handle` für die `kernel32.dll` zu erhalten und dann die Adresse der Funktion zum Laden dynamischer Bibliotheken zu finden.
2. **Remote-Speicherzuweisung:** `VirtualAllocEx` wird verwendet, um einen Speicherblock im virtuellen Adressraum des `gta_sa.exe`-Prozesses (der angehalten ist) zu reservieren. Die Größe dieses Blocks ist ausreichend, um den vollständigen Pfad von `samp.dll` zu speichern.
3. **Schreiben des DLL-Pfads:** Der vollständige Pfad der Datei `samp.dll` wird über `WriteProcessMemory` in diesen neu zugewiesenen Remote-Speicher geschrieben.
4. **Erstellung eines Remote-Threads:** `CreateRemoteThread` wird aufgerufen, um einen neuen `Thread` innerhalb des `gta_sa.exe`-Prozesses zu erstellen. Der Einstiegspunkt dieses neuen `Threads` ist die Adresse von `LoadLibraryW`, und das Argument, das er erhält, ist der Zeiger auf den Pfad der DLL, den wir gerade geschrieben haben.
5. **Überwachung der Injektion:** Die Ausführung des Remote-`Threads` wird von `WaitForSingleObject` für einen durch `Constants::DLL_INJECTION_TIMEOUT_MS` definierten Zeitraum überwacht.
6. **Überprüfung des Ergebnisses:** Der Exit-Code des Remote-`Threads` wird über `GetExitCodeThread` abgerufen. Ein Rückgabewert ungleich null zeigt an, dass `LoadLibraryW` erfolgreich `samp.dll` geladen hat.

> [!WARNING]
> Im Falle eines Fehlers während der Injektion von `samp.dll` wird eine spezifische Fehlermeldung (`error_utils.hpp`) angezeigt, der Injektionsprozess abgebrochen und die Ressourcen freigegeben.

### 7. Injektion der OMP-Bibliothek (`omp-client.dll`) - Bedingt

Wenn der angegebene Injektionstyp `OMP` ist, werden die in Punkt 6 beschriebenen Schritte für `omp-client.dll` wiederholt.

> [!TIP]
> Die Injektion von `omp-client.dll` erfolgt immer nach der erfolgreichen Injektion von `samp.dll`. Dies liegt daran, dass der Open Multiplayer-Client auf der von `samp.dll` bereitgestellten Infrastruktur aufbaut.

### 8. Aktivierung des Spiels

Schließlich, wenn alle Injektionen erfolgreich abgeschlossen wurden, wird die Methode `process_info.Resume()` aufgerufen. Dieser Aufruf führt `ResumeThread` auf dem Haupt-`Thread` von `gta_sa.exe` aus. In diesem Moment wird das Spiel aktiviert und beginnt seine normale Ausführung, jedoch bereits mit den SA-MP/OMP-DLLs in seinem Speicher geladen und mit den konfigurierten Verbindungsparametern, was eine automatisierte Verbindung zum Server ermöglicht.

> [!WARNING]
> Wenn die Wiederaufnahme des Spiel-`Threads` fehlschlägt, wird dem Benutzer eine letzte Fehlermeldung angezeigt.

## Diagnose von Fehlern und Ausfällen

Die Bibliothek ist sorgfältig konzipiert, um alle Probleme, die während des Initialisierungs- und Injektionsprozesses auftreten können, klar zu kommunizieren. An jedem Fehlerpunkt wird dem Benutzer eine `MessageBox` mit einer detaillierten Beschreibung angezeigt, oft ergänzt durch Fehlermeldungen des Betriebssystems.

### Fehler bei der Eingabevalidierung

Diese Fehler werden in der Anfangsphase (`validation.hpp`) erkannt, bevor eine Low-Level-Interaktion mit dem System stattfindet, und weisen auf Probleme mit den vom Benutzer bereitgestellten Daten oder der Umgebungskonfiguration hin.

#### Ungültiger Benutzername

- **Fehlermeldung (Beispiel 1):** `"Nickname cannot be empty. Please provide a valid nickname."`
- **Fehlermeldung (Beispiel 2):** `"Nickname length exceeds the maximum allowed of 23 characters. Please use a shorter nickname."`
- **Grund:** Der angegebene Benutzername (`nickname`) ist leer oder überschreitet die von den SA-MP/OMP-Clients erlaubte maximale Länge von 23 Zeichen.
- **Lösung:** Der Benutzer muss einen gültigen Benutzernamen eingeben, der die Längenkriterien erfüllt.

#### Ungültiger Verbindungsport

- **Fehlermeldung (Beispiel 1):** `"Invalid port format. The port must be a numeric value. Please provide a valid integer for the port."`
- **Fehlermeldung (Beispiel 2):** `"The specified port number (70000) is outside the valid range of 1 to 65535. Please provide a valid port."`
- **Grund:** Der für den Port angegebene Wert ist keine ganze Zahl oder liegt außerhalb des gültigen Bereichs (1 bis 65535).
- **Lösung:** Der Benutzer muss eine gültige Portnummer innerhalb des angegebenen Bereichs angeben.

#### Fehlende wesentliche Ressourcen

- **Fehlermeldung (Beispiel 1):** `"Game executable not found. Please ensure 'gta_sa.exe' exists at the specified path: C:\Games\GTA San Andreas\gta_sa.exe"`
- **Fehlermeldung (Beispiel 2):** `"SA-MP library not found. Please ensure 'samp.dll' exists at the specified path: C:\Games\GTA San Andreas\samp.dll"`
- **Fehlermeldung (Beispiel 3, für OMP):** `"OMP library not found. Please ensure 'omp-client.dll' exists at the specified path for OMP injection: C:\Games\GTA San Andreas\omp-client.dll"`
- **Grund:** Eine oder mehrere entscheidende Dateien (`gta_sa.exe`, `samp.dll`, `omp-client.dll`) wurden im angegebenen Spielverzeichnis nicht gefunden.
- **Lösung:** Überprüfen Sie den Pfad des Spielordners und stellen Sie sicher, dass alle erforderlichen Dateien vorhanden und zugänglich sind.

### Fehler bei der Prozessverwaltung

Diese Fehler treten auf, wenn die Bibliothek versucht, die ausführbare Datei des Spiels (`gta_sa.exe`) zu starten.

#### Schwierigkeiten beim Starten des Spielprozesses

- **Fehlermeldung (Beispiel):** `"Failed to create game process. Ensure 'gta_sa.exe' is not running and you have sufficient permissions to execute the file. System Error: Access is denied."`
- **Grund:**
   - **Ausführbare Datei in Gebrauch:** `gta_sa.exe` läuft möglicherweise bereits, oder es gibt eine Betriebssystem-Sperre, die die Erstellung einer neuen Instanz verhindert.
   - **Unzureichende Berechtigungen:** Die Anwendung hat möglicherweise nicht die entsprechenden Berechtigungen, um `gta_sa.exe` zu starten oder auf die Datei zuzugreifen.
   - **Beschädigte ausführbare Datei:** Obwohl die grundlegende Validierung die Existenz der Datei überprüft, kann sie beschädigt oder unzugänglich sein.
- **Lösung:** Stellen Sie sicher, dass keine Instanz von `gta_sa.exe` aktiv ist. Versuchen Sie, Ihre Anwendung als Administrator auszuführen. Überprüfen Sie die Integrität der Datei `gta_sa.exe`.

### Probleme bei der DLL-Injektion

Dies sind die kritischsten und detailliertesten Fehler, die beim Versuch auftreten, `samp.dll` oder `omp-client.dll` in den angehaltenen Prozess des Spiels zu injizieren. Die Fehlermeldungen beginnen normalerweise mit `"Failed to inject <DLL_NAME>:\n"` und werden von einer spezifischen Beschreibung und einem Systemfehlercode gefolgt.

#### `LoadLibraryW` kann nicht gefunden werden

- **Fehlermeldung (Teil):** `"Failed to find the address of LoadLibraryW in kernel32.dll."`
- **Grund:** Die Funktion `LoadLibraryW`, eine grundlegende Windows-API zum dynamischen Laden von DLLs, konnte in `kernel32.dll` nicht gefunden werden. Dies ist ein extrem seltenes Low-Level-Problem, das auf eine mögliche Beschädigung des Betriebssystems oder eine sehr ungewöhnliche Laufzeitumgebung hindeutet.
- **Lösung:** Ein Neustart des Systems kann das Problem lösen. Wenn es weiterhin besteht, kann dies auf ein ernsteres Problem mit der Windows-Installation hinweisen.

#### Fehler bei der Reservierung von Remote-Speicher

- **Fehlermeldung (Teil):** `"Failed to allocate memory in the target process (VirtualAllocEx). System Error: Not enough storage is available to process this command."`
- **Grund:** Die Bibliothek konnte keinen Speicherblock im Adressraum des `gta_sa.exe`-Prozesses zuweisen.
   - **Berechtigungen:** Ihre Anwendung hat möglicherweise nicht genügend Berechtigungen, um den Speicherbereich eines anderen Prozesses zu ändern.
   - **Prozessschutz:** Sicherheitsmechanismen des Betriebssystems oder Anti-Cheat-Software können die Speicherzuweisung in externen Prozessen blockieren.
- **Lösung:** Führen Sie Ihre Anwendung als Administrator aus. Überprüfen Sie, ob Sicherheitsprogramme (Antivirus, Anti-Cheat) stören, und deaktivieren Sie sie gegebenenfalls vorübergehend zum Testen.

#### Daten können nicht in den Prozess geschrieben werden

- **Fehlermeldung (Teil):** `"Failed to write DLL path to process memory (WriteProcessMemory). System Error: Access is denied."`
- **Grund:** Speicher wurde im Spielprozess zugewiesen, aber die Bibliothek konnte den DLL-Pfad nicht an diesen Ort schreiben.
   - **Berechtigungen/Schutz:** Ähnlich wie beim Fehler bei der Speicherzuweisung kann es sich um ein Problem mit Schreibberechtigungen oder einen aktiven Speicherschutz handeln.
- **Lösung:** Es gelten dieselben Lösungen wie für den Fehler bei der Speicherzuweisung.

#### Fehler beim Erstellen des Injektions-Threads

- **Fehlermeldung (Teil):** `"Failed to create remote thread (CreateRemoteThread). System Error: The parameter is incorrect."`
- **Grund:** Die API `CreateRemoteThread` ist beim Starten eines neuen `Threads` im `gta_sa.exe`-Prozess zum Aufrufen von `LoadLibraryW` fehlgeschlagen.
   - **Sicherheit:** Viele Anti-Cheat-Systeme und Betriebssystemschutzmechanismen überwachen und blockieren die Erstellung von Remote-`Threads`, da dies eine gängige Injektionstechnik ist.
   - **Prozesszustand:** Der Spielprozess befindet sich möglicherweise in einem instabilen Zustand, der die Erstellung von `Threads` verhindert.
- **Lösung:** Deaktivieren Sie vorübergehend jegliche Anti-Cheat- oder Antivirensoftware. Versuchen Sie, die Anwendung als Administrator auszuführen.

#### Zeitüberschreitung oder Fehler beim Warten auf die Injektion

- **Fehlermeldung (Teil):** `"Timeout or error waiting for remote thread (WaitForSingleObject). System Error: The wait operation timed out."`
- **Grund:** Der Remote-`Thread` (der `LoadLibraryW` aufruft) hat seine Ausführung nicht innerhalb des festgelegten Zeitlimits (10 Sekunden) abgeschlossen.
   - **Einfrieren:** `LoadLibraryW` könnte hängengeblieben sein, übermäßig lange gedauert haben oder abgefangen/blockiert worden sein.
- **Lösung:** Dies könnte darauf hindeuten, dass die DLL Schwierigkeiten beim Laden hat oder etwas sie daran hindert. Die Überprüfung von System- oder SA-MP/OMP-Protokollen (falls verfügbar) kann weitere Hinweise geben.

#### Interner Fehler bei der DLL-Injektion

- **Fehlermeldung (Teil):** `"LoadLibraryW call failed in the target process. The DLL might be corrupt, missing dependencies, or blocked by security software."`
- **Grund:** Der Remote-`Thread` wurde abgeschlossen, aber der Rückgabewert von `LoadLibraryW` war `0` (oder `NULL`), was darauf hindeutet, dass die DLL nicht erfolgreich geladen wurde.
   - **Beschädigte/Fehlende DLL:** Die DLL wurde möglicherweise nach der anfänglichen Validierung verschoben, gelöscht oder beschädigt.
   - **Fehlende Abhängigkeiten:** `samp.dll` oder `omp-client.dll` haben möglicherweise Abhängigkeiten (andere DLLs), die nicht im Spielverzeichnis oder im System-`PATH` vorhanden sind.
   - **Interner Fehler der DLL:** Die DLL selbst kann einen internen Fehler haben, der das Laden verhindert.
- **Lösung:** Überprüfen Sie die Integrität der Dateien `samp.dll`/`omp-client.dll`. Stellen Sie sicher, dass alle ihre Abhängigkeiten vorhanden sind.

### Schwierigkeiten bei der Wiederaufnahme der Spielausführung

Dies ist der letzte mögliche Fehlerpunkt im Injektionszyklus.

- **Fehlermeldung (Beispiel):** `"Failed to resume the game process thread: Invalid handle."`
- **Grund:** Die API `ResumeThread` ist bei der Wiederaktivierung des Haupt-`Threads` von `gta_sa.exe` fehlgeschlagen.
   - **Ungültiges Handle:** Das `Handle` des `Threads` wurde möglicherweise durch ein unerwartetes Ereignis ungültig.
   - **Berechtigung:** Die Anwendung hat möglicherweise keine Berechtigung, den Zustand des `Threads` zu ändern.
- **Lösung:** Versuchen Sie, die Anwendung als Administrator auszuführen. Wenn das Problem weiterhin besteht, kann dies auf ein tieferliegendes Stabilitätsproblem im System oder im Spielprozess hinweisen.

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