# SA-MP Injector C++

![License](https://img.shields.io/badge/License-MIT-yellow.svg?style=flat)
![C++17](https://img.shields.io/badge/C%2B%2B-17-blue.svg?style=flat&logo=cplusplus)
![Platform](https://img.shields.io/badge/Platform-Windows-0078D6.svg?style=flat&logo=windows)
[![SA-MP | OMP](https://img.shields.io/badge/Support-SA--MP%20%7C%20OMP-yellow)](https://github.com/spc-samp/samp-injector)
![Code Quality](https://img.shields.io/badge/Code%20Quality-High-brightgreen.svg?style=flat)

Der **SA-MP Injector C++** geht über die Definition eines einfachen **DLL-Injection-Tools** hinaus. Es handelt sich um eine sorgfältig gestaltete **C++-Bibliothek**, die entwickelt wurde, um eine robuste und umfassende Lösung für die programmgesteuerte Initialisierung des Spiels **Grand Theft Auto: San Andreas** (**GTA:SA**) in Verbindung mit seinen Multiplayer-Clients, insbesondere **SA-MP (San Andreas Multiplayer)** und **OMP (Open Multiplayer)**, bereitzustellen. Sein Hauptziel ist es, den Startprozess des Spiels zu vereinfachen und die inhärente Komplexität der direkten Manipulation von Betriebssystemprozessen und der Übergabe von Kommandozeilenargumenten zu eliminieren.

Die Bibliothek wurde mit dem Ziel entwickelt, maximale Flexibilität und einfache Integration zu bieten. Diese `header-only`-Bibliothek macht komplizierte vorherige Kompilierungen überflüssig und ermöglicht es Entwicklern, sie direkt in ihre **C++-Projekte** zu integrieren. Sie orchestriert nicht nur die **grundlegende DLL-Injection** der Multiplayer-Client-DLLs (`samp.dll` oder `omp-client.dll`), sondern verwaltet auch intelligent alle wesentlichen Verbindungsparameter (**Nickname**, **IP-Adresse**, **Port** und **Passwort**) und simuliert eine native Initialisierung durch die intrinsischen Funktionen der **Windows-API**.

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
  - [Grundlegende Konzepte und Motivation](#grundlegende-konzepte-und-motivation)
    - [Warum DLLs injizieren?](#warum-dlls-injizieren)
    - [SA-MP und OMP: Unterschiede und Gemeinsamkeiten](#sa-mp-und-omp-unterschiede-und-gemeinsamkeiten)
  - [Interne Architektur der Bibliothek: Ein tiefgehender Einblick](#interne-architektur-der-bibliothek-ein-tiefgehender-einblick)
    - [`constants.hpp`](#constantshpp)
    - [`types.hpp`](#typeshpp)
    - [`string_utils.hpp`](#string_utilshpp)
    - [`error_utils.hpp`](#error_utilshpp)
    - [`resource_handle.hpp`](#resource_handlehpp)
    - [`validation.hpp`](#validationhpp)
    - [`process.hpp`](#processhpp)
    - [`injector_core.hpp`](#injector_corehpp)
    - [`injector.hpp`](#injectorhpp)
  - [Umfassende Anwendungsbeispiele](#umfassende-anwendungsbeispiele)
    - [1. Vorbereitung der Entwicklungsumgebung](#1-vorbereitung-der-entwicklungsumgebung)
    - [2. Basisszenario: Verbindung zu einem SA-MP-Server](#2-basisszenario-verbindung-zu-einem-sa-mp-server)
    - [3. Fortgeschrittenes Szenario: Verbindung zu einem OMP-Server](#3-fortgeschrittenes-szenario-verbindung-zu-einem-omp-server)
  - [Behandlung häufiger Fehler und Meldungen](#behandlung-häufiger-fehler-und-meldungen)
    - [1. Ungültiger Injektionstyp](#1-ungültiger-injektionstyp)
    - [2. Ungültiger Server-Port (Format oder Bereich)](#2-ungültiger-server-port-format-oder-bereich)
      - [2.1. Nicht-numerisches Port-Format](#21-nicht-numerisches-port-format)
      - [2.2. Port außerhalb des gültigen Bereichs](#22-port-außerhalb-des-gültigen-bereichs)
    - [3. Ungültiger Nickname (Leer oder zu lang)](#3-ungültiger-nickname-leer-oder-zu-lang)
      - [3.1. Leerer Nickname](#31-leerer-nickname)
      - [3.2. Zu langer Nickname](#32-zu-langer-nickname)
    - [4. Spiel- oder DLL-Dateien nicht gefunden](#4-spiel--oder-dll-dateien-nicht-gefunden)
      - [4.1. Spielausführbare Datei (`gta_sa.exe`) nicht gefunden](#41-spielausführbare-datei-gta_saexe-nicht-gefunden)
      - [4.2. SA-MP-Bibliothek (`samp.dll`) nicht gefunden](#42-sa-mp-bibliothek-sampdll-nicht-gefunden)
      - [4.3. OMP-Bibliothek (`omp-client.dll`) nicht gefunden (nur für OMP-Injektion)](#43-omp-bibliothek-omp-clientdll-nicht-gefunden-nur-für-omp-injektion)
    - [5. Fehler beim Erstellen des Spielprozesses](#5-fehler-beim-erstellen-des-spielprozesses)
    - [6. Fehler bei der Speicherzuweisung im Zielprozess](#6-fehler-bei-der-speicherzuweisung-im-zielprozess)
    - [7. Fehler beim Schreiben des DLL-Pfads in den Speicher des Prozesses](#7-fehler-beim-schreiben-des-dll-pfads-in-den-speicher-des-prozesses)
    - [8. Fehler beim Finden essentieller Systemfunktionen](#8-fehler-beim-finden-essentieller-systemfunktionen)
      - [8.1. `kernel32.dll` nicht gefunden](#81-kernel32dll-nicht-gefunden)
      - [8.2. `LoadLibraryA` nicht gefunden](#82-loadlibrarya-nicht-gefunden)
    - [9. Fehler beim Erstellen eines Remote-Threads für die Injektion](#9-fehler-beim-erstellen-eines-remote-threads-für-die-injektion)
    - [10. Timeout oder Fehler beim Abschluss der Injektion](#10-timeout-oder-fehler-beim-abschluss-der-injektion)
    - [11. Fehler beim Fortsetzen des Threads des Spielprozesses](#11-fehler-beim-fortsetzen-des-threads-des-spielprozesses)
  - [Lizenz](#lizenz)
    - [Nutzungsbedingungen](#nutzungsbedingungen)
      - [1. Gewährte Berechtigungen](#1-gewährte-berechtigungen)
      - [2. Verpflichtende Bedingungen](#2-verpflichtende-bedingungen)
      - [3. Urheberrecht](#3-urheberrecht)
      - [4. Gewährleistungsausschluss und Haftungsbeschränkung](#4-gewährleistungsausschluss-und-haftungsbeschränkung)

## Grundlegende Konzepte und Motivation

### Warum DLLs injizieren?

> [!NOTE] DLL-Injektion: Der Kern des dynamischen Ladens.
> Die **DLL-Injektion (Dynamic Link Library)** ist eine Methode, die in **Microsoft Windows**-Betriebssystemen verwendet wird und es ermöglicht, Code innerhalb des Speicherbereichs eines anderen laufenden Prozesses auszuführen. Es handelt sich um eine leistungsstarke Technik mit zahlreichen legitimen Anwendungen, von der Fehlersuche und Überwachung von Programmen bis hin zur Modifikation des Verhaltens von Anwendungen, um deren Funktionalitäten zu erweitern.

Im Kontext von Spielen wie **GTA San Andreas**, das ursprünglich nicht mit integrierter Multiplayer-Funktionalität entwickelt wurde, ist die **DLL-Injektion** die Grundlage für die Existenz von Multiplayer-Clients wie **SA-MP** und **OMP**. Diese Clients werden als **DLLs** implementiert, die, sobald sie in den Prozess von `gta_sa.exe` injiziert werden, die Kontrolle übernehmen, Spiel-Funktionen abfangen und die Kommunikation mit Multiplayer-Servern herstellen.

Anstatt auf einen externen Launcher oder eine direkte Modifikation der ausführbaren Spieldatei angewiesen zu sein, ermöglicht die **DLL-Injektion** eine flexiblere und programmierbare Initialisierung, was besonders in Umgebungen nützlich ist, in denen der Verbindungsprozess zu bestimmten Servern mit vordefinierten Konfigurationen automatisiert werden soll.

### SA-MP und OMP: Unterschiede und Gemeinsamkeiten

**SA-MP** und **OMP** sind die beiden wichtigsten Multiplayer-Plattformen für **GTA San Andreas**. Beide fungieren als Modifikationen des Basisspiels und verwandeln es in eine massiv-multiplayer-fähige Online-Umgebung.

- **SA-MP (San Andreas Multiplayer)**: Der ursprüngliche und am weitesten verbreitete Client, der über viele Jahre hinweg genutzt wurde. Seine Architektur erfordert die `samp.dll`, um zu funktionieren.
- **OMP (Open Multiplayer)**: Ein Open-Source-Projekt, das oft als moderner Nachfolger oder Alternative zu **SA-MP** betrachtet wird und Verbesserungen in Leistung, Stabilität und zusätzlichen Funktionen bietet. Es erfordert die `omp-client.dll`.

Obwohl sie auf ähnliche Weise funktionieren (**durch Injektion einer DLL** in den Prozess von **GTA:SA**), wurde die **SA-MP Injector C++**-Bibliothek sorgfältig entwickelt, um **beide DLLs** zu unterstützen, wobei die Unterschiede in den Dateinamen berücksichtigt werden und der Entwickler den gewünschten Multiplayer-Client über einen Konfigurationsparameter auswählen kann. Dies stellt sicher, dass die Bibliothek mit der breiten Palette von Servern und Projekten verwendet werden kann, die auf einer der beiden Plattformen basieren.

## Interne Architektur der Bibliothek: Ein tiefgehender Einblick

Der **SA-MP Injector C++** verfolgt einen modularen und objektorientierten (wo anwendbar) Ansatz, um die Komplexität des Injektionsprozesses zu bewältigen. Jede Header-Datei ist ein spezialisiertes Modul, das für einen bestimmten Teil der Gesamtfunctionalität verantwortlich ist, was die Klarheit, Wartbarkeit und Erweiterbarkeit des Codes fördert.

### `constants.hpp`

Diese Datei bildet die Grundlage aller festen Konfigurationen der Bibliothek. Sie definiert einen Namespace `Constants`, um alle Literale zu kapseln und eine Verschmutzung des globalen Bereichs zu vermeiden. Die Verwendung von `inline constexpr` ist hier entscheidend: `constexpr` stellt sicher, dass die Werte zur Kompilierungszeit ausgewertet werden, was die Leistung optimiert und die Unveränderbarkeit gewährleistet, während `inline` Probleme mit der Mehrfachdefinition beim Einbinden der Datei in mehrere Kompilierungseinheiten verhindert.

```cpp
#pragma once

namespace Constants {
    // Spielbezogene Konstanten
    inline constexpr int MIN_PORT = 1;
    inline constexpr int MAX_PORT = 65535;
    inline constexpr int MAX_NICKNAME_LENGTH = 20;
    
    // Dateinamen
    inline constexpr const wchar_t* SAMP_DLL_NAME = L"samp.dll";
    inline constexpr const wchar_t* OMP_DLL_NAME = L"omp-client.dll";
    inline constexpr const wchar_t* GAME_EXE_NAME = L"gta_sa.exe";
    
    // Systembibliotheken und Funktionen
    inline constexpr const char* KERNEL32_DLL = "kernel32.dll";
    inline constexpr const char* LOAD_LIBRARY_FUNC = "LoadLibraryA"; // 'A' für ANSI/8-Bit-Version
    
    // Kommandozeilenargumente, die von SA-MP/OMP-Clients verwendet werden
    inline constexpr const char* CMD_ARG_CONFIG = "-c";
    inline constexpr const char* CMD_ARG_NICKNAME = "-n";
    inline constexpr const char* CMD_ARG_HOST = "-h";
    inline constexpr const char* CMD_ARG_PORT = "-p";
    inline constexpr const char* CMD_ARG_PASSWORD = "-z";
    
    // Injektionstypen als Strings (Wide-Character)
    inline constexpr const wchar_t* INJECT_TYPE_SAMP = L"samp";
    inline constexpr const wchar_t* INJECT_TYPE_OMP = L"omp";
    
    // Fehlermeldungstitel für MessageBoxW
    inline constexpr const wchar_t* ERROR_TITLE_SAMP = L"SA-MP Injector Fehler - SPC";
    inline constexpr const wchar_t* ERROR_TITLE_OMP = L"OMP Injector Fehler - SPC";
    
    // Prozess-Erstellungsflags für CreateProcessA
    inline constexpr DWORD PROCESS_CREATION_FLAGS = CREATE_SUSPENDED | DETACHED_PROCESS;
    
    // Timeouts für WaitForSingleObject (z.B. Warten auf DLL-Injektion)
    inline constexpr DWORD DLL_INJECTION_TIMEOUT_MS = 10000; // 10 Sekunden
    
    // Speicherzuweisungsflags für VirtualAllocEx
    inline constexpr DWORD MEMORY_ALLOCATION_TYPE = MEM_COMMIT | MEM_RESERVE;
    inline constexpr DWORD MEMORY_PROTECTION = PAGE_READWRITE; // Benötigt für das Schreiben des DLL-Pfads
}
```

> [!TIP]
> Die Verwendung von `wchar_t` für Dateinamen und Fehlermeldungstitel ist eine bewährte Praxis im **Windows-Entwicklungsbereich**. Dies gewährleistet die Kompatibilität mit allen Sprachen und Zeichensätzen, insbesondere für Dateipfade, die **Unicode-Zeichen** enthalten können. Für **APIs**, die `char` erwarten (wie `LoadLibraryA`), wird die Konvertierung explizit in `string_utils.hpp` durchgeführt.

### `types.hpp`

Ein prägnantes, aber essentielles Modul zur Definition der Aufzählung, die die unterstützten Injektionstypen kategorisiert. Dies verbessert die Lesbarkeit und Typsicherheit des Codes und verhindert Fehler durch String- oder Magic-Number-Fehler.

```cpp
#pragma once

namespace Types {
    // Aufzählungen für unterstützte Injektionstypen
    enum class Inject_Type {
        SAMP, // San Andreas Multiplayer
        OMP // Open Multiplayer
    };
}
```

### `string_utils.hpp`

Die Arbeit mit der **Windows-API** erfordert häufig die Konvertierung zwischen verschiedenen String-Codierungen. Diese Datei bietet eine entscheidende Hilfsfunktion zur Konvertierung von **Wide-Character**-Strings (`std::wstring_view`, verwendet für die Eingaben der Bibliothek) in **ANSI/8-Bit**-Strings (`std::string`), die für **WinAPI**-Funktionen erforderlich sind, die mit `char*` arbeiten (wie `CreateProcessA` oder `GetProcAddress`).

```cpp
#pragma once

#include <string>
#include <string_view>
#include <windows.h> // Benötigt für WideCharToMultiByte

namespace Utils {
    inline std::string Wide_To_Local_8Bit(std::wstring_view wstr) {
        if (wstr.empty())
            return "";
        
        // Bestimmt die benötigte Größe für den Puffer des resultierenden Strings in char
        int size = WideCharToMultiByte(CP_ACP, // ANSI-Codepage (abhängig vom lokalen System)
            0, // Keine zusätzlichen Flags
            wstr.data(), 
            static_cast<int>(wstr.size()), 
            nullptr, // Berechnet die Größe, füllt keinen Puffer
            0, // Größe 0, nur für Berechnung
            nullptr, // Standardzeichen für nicht darstellbare Zeichen
            nullptr); // Zeiger auf bool, das angibt, ob ein Standardzeichen verwendet wurde

        if (size <= 0) // Gibt einen leeren String bei Fehler oder ungültiger Größe zurück
            return "";

        std::string result(size, 0); // Allokiert den String mit der bestimmten Größe
        // Führt die tatsächliche Konvertierung durch und füllt den Puffer 'result'
        WideCharToMultiByte(CP_ACP, 
            0, 
            wstr.data(), 
            static_cast<int>(wstr.size()), 
            result.data(), // Zielpuffer
            size, // Größe des Zielpuffers
            nullptr, 
            nullptr);

        return result;
    }
}
```

> [!IMPORTANT] Kodierung ist wichtig!
> Die in `WideCharToMultiByte` verwendete `CP_ACP` **(ANSI-Codepage)** ist die Standard-Codepage des **Windows**-Systems. Dies bedeutet, dass die Konvertierung je nach Sprachkonfiguration des Benutzersystems variieren kann. Für die meisten Anwendungsfälle von Dateinamen und Kommandozeilenargumenten in **SA-MP**/**OMP** (die historisch gut mit **ANSI**-Strings umgehen), ist dieser Ansatz in der Regel ausreichend. In Szenarien, die vollständige **Unicode**-Kompatibilität mit externen Systemen oder globalen Eingaben erfordern, wären Konvertierungen in **UTF-8** (`CP_UTF8`) oder andere Codepages erforderlich. Für den Umfang dieses Projekts ist `CP_ACP` der funktionale Standard.

### `error_utils.hpp`

Eine grundlegende Komponente für die Benutzerfreundlichkeit der Bibliothek, verantwortlich für die Bereitstellung von **klaren Rückmeldungen** an den Benutzer im Falle eines Fehlers. Sie zentralisiert die Logik zum Abrufen von Systemfehlermeldungen und das Anzeigen von Dialogfenstern.

```cpp
#pragma once

#include <string>
#include <string_view>
#include <windows.h> // Für FormatMessageW und MessageBoxW
//
#include "types.hpp"
#include "constants.hpp"

namespace Utils {
    // Gibt die Systemfehlermeldung für einen bestimmten Fehlercode zurück
    inline std::wstring Get_System_Error_Message(DWORD error_code) {
        wchar_t buffer[512] = {0}; // Puffer für die Nachricht
        // FormatMessageW füllt den Puffer mit der Beschreibung des Systemfehlers
        DWORD result = FormatMessageW(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, 
            nullptr, // Quelle der Nachricht (vom System)
            error_code, 
            0, // Sprache (Standard verwenden)
            buffer, 
            512, // Puffergröße
            nullptr);
        
        // Wenn die Funktion erfolgreich war, gibt den String aus dem Puffer zurück; andernfalls eine generische Nachricht
        return result ? std::wstring(buffer) : L"Unbekannter Fehler (Code: " + std::to_wstring(error_code) + L")";
    }

    // Zeigt dem Benutzer ein Fehlermeldungsfenster an
    inline void Show_Error(std::wstring_view message, Types::Inject_Type injectType) {
        // Wählt den Titel des Dialogfensters basierend auf dem Injektionstyp
        std::wstring title = (injectType == Types::Inject_Type::SAMP) ? Constants::ERROR_TITLE_SAMP : Constants::ERROR_TITLE_OMP;
        MessageBoxW(nullptr, // Handle des übergeordneten Fensters (nullptr für Desktop)
            message.data(), 
            title.c_str(), 
            MB_OK | MB_ICONERROR); // OK-Button und Fehler-Symbol
    }
}
```

> [!NOTE] Formatierung von Fehlermeldungen
> Die Funktion `FormatMessageW` ist eine leistungsstarke **Windows-API**, die die textuelle Beschreibung eines Systemfehlercodes abruft. Sie berücksichtigt die Lokalisierung und liefert klare Meldungen, die für eine effektive **Diagnose** unerlässlich sind, indem sie einen `DWORD` wie `ERROR_FILE_NOT_FOUND` (2) in `L"Das System kann die angegebene Datei nicht finden."` umwandelt.

### `resource_handle.hpp`

Die sichere Verwaltung von Ressourcen (wie `HANDLE`s in **Windows**) ist entscheidend, um Ressourcenlecks und undefiniertes Verhalten zu vermeiden. Diese Datei definiert ein `UniqueResource` unter Verwendung von `std::unique_ptr` und einer benutzerdefinierten Funktion für `CloseHandle`. Dies folgt dem **RAII-Prinzip (Resource Acquisition Is Initialization)**, das sicherstellt, dass `HANDLE`s automatisch geschlossen werden, wenn ihre **Wrapper** den Gültigkeitsbereich verlassen, selbst bei Ausnahmen.

```cpp
#pragma once

#include <memory> // Für std::unique_ptr
#include <functional> // Für std::function
#include <windows.h> // Für HANDLE und CloseHandle

namespace Utils {
    // Typ-Alias für ein std::unique_ptr, das ein HANDLE (oder Zeiger) mit einem benutzerdefinierten Deleter verwaltet
    // T: Der Typ der zu verwaltenden Ressource (z.B. HANDLE, LPVOID)
    // Deleter: Eine Klasse oder Lambda, die weiß, wie die Ressource freigegeben wird
    template<typename T, typename Deleter>
    using UniqueResource = std::unique_ptr<std::remove_pointer_t<T>, Deleter>;

    // Hilfsfunktion zum Erstellen einer Instanz von UniqueResource für HANDLEs
    // Sie nimmt an, dass T ein Handle-Typ ist und verwendet CloseHandle als Deleter.
    template<typename T>
    inline auto Make_Unique_Handle(T handle) {
        return UniqueResource<T, std::function<void(T)>>(handle, [](T h) {
            // Bedingung, um sicherzustellen, dass das Handle gültig ist, bevor versucht wird, es zu schließen
            // 0 und INVALID_HANDLE_VALUE gelten für die meisten Handles als ungültig
            if (h && h != INVALID_HANDLE_VALUE)
                CloseHandle(h); // Gibt das HANDLE des Betriebssystems frei
        });
    }
}
```

> [!IMPORTANT]
> Die Verwendung von `UniqueResource` ist eine Demonstration moderner **C++-Best Practices** und sicherer Entwicklung unter **Windows**. Es vereinfacht die Verwaltung von **Handle-Lebenszyklen** erheblich, die, wenn sie nicht korrekt geschlossen werden, zu Speicher- oder Kernel-Ressourcenlecks führen können, die die Systemstabilität im Laufe der Zeit beeinträchtigen.

### `validation.hpp`

Die Robustheit der Injektion beginnt mit der Validierung der Benutzereingaben und der Überprüfung der Dateiabhängigkeiten. Dieses Modul enthält Funktionen, die sicherstellen, dass alle Voraussetzungen und Parameter korrekt sind, bevor der Injektionsprozess gestartet wird, um komplexere Fehler später zu vermeiden.

```cpp
#pragma once

#include <string>
#include <string_view>
#include <filesystem> // Für std::filesystem::exists
//
#include "constants.hpp"
#include "types.hpp"
#include "string_utils.hpp" // Für Wide_To_Local_8Bit
#include "error_utils.hpp" // Für Show_Error

namespace Utils {
    // Validiert, ob ein Port-String eine gültige Zahl ist und innerhalb des zulässigen Bereichs liegt
    inline bool Validate_Port(std::wstring_view port_str, std::wstring& error_message) {
        try {
            // Versucht, den Wide-Character-String in std::string und dann in int zu konvertieren
            int port_num = std::stoi(Wide_To_Local_8Bit(port_str));

            // Überprüft, ob der Port im gültigen Bereich (1-65535) liegt
            if (port_num < Constants::MIN_PORT || port_num > Constants::MAX_PORT)
                return (error_message = L"Die angegebene Portnummer (" + std::wstring(port_str) + 
                L") liegt außerhalb des gültigen Bereichs von " +  std::to_wstring(Constants::MIN_PORT) + 
                L" bis " + std::to_wstring(Constants::MAX_PORT) + 
                L". Bitte geben Sie einen gültigen Port ein.", false);

            return true;
        }
        catch (...) { // Fängt jede Ausnahme ab (z.B. std::invalid_argument für nicht-numerisch)
            return (error_message = L"Ungültiges Portformat. Der Port muss ein numerischer Wert sein. Bitte geben Sie eine gültige Ganzzahl für den Port ein.", false);
        }
    }

    // Validiert den Nickname, überprüft, ob er nicht leer ist und die Länge akzeptabel ist
    inline bool Validate_Nickname(std::wstring_view nickname_str, std::wstring& error_message) {
        if (nickname_str.empty())
            return (error_message = L"Nickname darf nicht leer sein. Bitte geben Sie einen gültigen Nickname ein.", false);
        
        if (nickname_str.size() > Constants::MAX_NICKNAME_LENGTH)
            return (error_message = L"Die Länge des Nicknames überschreitet das erlaubte Maximum von " + 
                std::to_wstring(Constants::MAX_NICKNAME_LENGTH) + 
                L" Zeichen. Bitte verwenden Sie einen kürzeren Nickname.", false);

        return true;
    }

    // Validiert die Existenz kritischer Dateien (gta_sa.exe, samp.dll, omp-client.dll)
    inline bool Validate_Files(const std::filesystem::path& game_path, 
        const std::filesystem::path& samp_DLL_path, 
        const std::filesystem::path& omp_DLL_path, 
        Types::Inject_Type inject_type) {
        std::wstring error_message_local; // Lokale Variable hier, bevor sie an Show_Error übergeben wird
        
        // Überprüft die Existenz der ausführbaren Spieldatei
        if (!std::filesystem::exists(game_path)) {
            error_message_local = L"Spielausführbare Datei nicht gefunden. Bitte stellen Sie sicher, dass 'gta_sa.exe' am angegebenen Pfad existiert: " + game_path.wstring();
            Show_Error(error_message_local, inject_type);
            return false;
        }

        // Überprüft die Existenz von samp.dll (erforderlich für beide Injektionstypen)
        if (!std::filesystem::exists(samp_DLL_path)) {
            error_message_local = L"SA-MP-Bibliothek nicht gefunden. Bitte stellen Sie sicher, dass 'samp.dll' am angegebenen Pfad existiert: " + samp_DLL_path.wstring();
            Show_Error(error_message_local, inject_type);

            return false;
        }

        // Wenn der Injektionstyp OMP ist, überprüft die Existenz von omp-client.dll
        if (inject_type == Types::Inject_Type::OMP && !std::filesystem::exists(omp_DLL_path)) {
            error_message_local = L"OMP-Bibliothek nicht gefunden. Bitte stellen Sie sicher, dass 'omp-client.dll' am angegebenen Pfad für die OMP-Injektion existiert: " + omp_DLL_path.wstring();
            Show_Error(error_message_local, inject_type);

            return false;
        }

        return true; // Alle erforderlichen Dateien wurden gefunden
    }
}
```

> [!NOTE] C++17 `std::filesystem`
> Die Verwendung von `std::filesystem` ist eine moderne Ergänzung zu **C++17**, die eine leistungsstarke und plattformunabhängige Möglichkeit bietet, mit dem Dateisystem zu interagieren. Für dieses Projekt unter **Windows** vereinfacht sie die Handhabung von Pfaden und die Überprüfung der Existenz von Dateien im Vergleich zu älteren **WinAPI**-Funktionen.
>
> Stellen Sie sicher, dass Ihr Compiler **C++17** unterstützt, um `std::filesystem` zu verwenden. Sie müssen Ihr Projekt so konfigurieren, dass es den **C++17**-Standard verwendet (`/std:c++17` in **Visual Studio**).

### `process.hpp`

Dies ist das Hauptmodul, das für die direkte Interaktion mit den **Low-Level-APIs** von **Windows** zur Prozessmanipulation verantwortlich ist. Es kapselt die entscheidenden Operationen der Prozesserstellung und **DLL-Injektion**, einschließlich der Handhabung von **Handles**, **Speicher** und **Threads**.

```cpp
#pragma once

#include <string_view>
#include <optional> // Für std::optional
#include <functional> // Für std::function (verwendet in UniqueResource)
#include <windows.h> // Windows-APIs
#include <memory> // Für std::unique_ptr
#include <vector> // Für std::vector (Puffer für Argumente)
//
#include "resource_handle.hpp" // Unser Wrapper für HANDLEs
#include "error_utils.hpp" // Für Get_System_Error_Message und Show_Error
#include "constants.hpp" // Globale Konstanten
#include "types.hpp" // Injektionstypen

class Process {
    public:
        // Konstruktoren/Destruktoren und Zuweisungsoperatoren
        // Explizit default und delete, um Wert-Semantik und move-only zu gewährleisten.
        Process() = default;
        Process(const Process&) = delete; // Kein Kopieren
        Process& operator=(const Process&) = delete; // Keine Kopierzuweisung
        Process(Process&&) = default; // Move-Semantik
        Process& operator=(Process&&) = default; // Move-Zuweisung
        ~Process() = default;

        // Struktur zur Speicherung der Prozess- und Thread-Handles, verwaltet durch UniqueResource
        struct Process_Info {
            Utils::UniqueResource<HANDLE, std::function<void(HANDLE)>> process_handle;
            Utils::UniqueResource<HANDLE, std::function<void(HANDLE)>> thread_handle;
        };

        // Erstellt den Spielprozess GTA:SA im suspendierten Zustand
        std::optional<Process_Info> Create_Game_Process(std::string_view game_path, std::string_view command_args, std::string_view working_dir) {
            STARTUPINFOA startup_info{}; // Struktur für Prozessstartinformationen
            startup_info.cb = sizeof(STARTUPINFOA); // Setzt die Größe der Struktur

            PROCESS_INFORMATION process_info{}; // Struktur, die Informationen über den neuen Prozess erhält

            // Erstellt einen veränderbaren Puffer für die Kommandozeilenargumente.
            // CreateProcessA verändert den Kommandozeilenpuffer, daher funktioniert std::string_view direkt nicht.
            std::vector<char> args_buffer(command_args.size() + 1); // +1 für den Null-Terminator

            if (!command_args.empty()) {
                std::memcpy(args_buffer.data(), command_args.data(), command_args.size());
                args_buffer[command_args.size()] = '\0'; // Gewährleistet Null-Terminator
            }

            // Erstellt den Prozess
            bool success = CreateProcessA(game_path.data(), // Name des ausführbaren Moduls
                args_buffer.empty() ? nullptr : args_buffer.data(), // Kommandozeilenargumente
                nullptr, // Sicherheitsattribute des Prozesses
                nullptr, // Sicherheitsattribute des Threads
                FALSE, // Keine Vererbung von Handles
                Constants::PROCESS_CREATION_FLAGS, // CREATE_SUSPENDED | DETACHED_PROCESS
                nullptr, // Umgebung des neuen Prozesses
                working_dir.empty() ? nullptr : working_dir.data(), // Arbeitsverzeichnis
                &startup_info, // Startinformationen
                &process_info); // Informationen über den erstellten Prozess

            if (!success) {
                // Bei Misserfolg die Systemfehlermeldung abrufen und anzeigen
                std::wstring error_msg = Utils::Get_System_Error_Message(GetLastError());
                Utils::Show_Error(L"Fehler beim Erstellen des Spielprozesses. Stellen Sie sicher, dass 'gta_sa.exe' nicht läuft und Sie ausreichende Berechtigungen haben, die Datei auszuführen. Systemfehler: " + error_msg, Types::Inject_Type::SAMP); // Fallback auf SAMP für den Titel
                
                return std::nullopt; // Gibt ein leeres optional zurück
            }

            Process_Info result;
            // Speichert die Prozess- und Thread-Handles in UniqueResource für automatisches Management
            result.process_handle = Utils::Make_Unique_Handle(process_info.hProcess);
            result.thread_handle = Utils::Make_Unique_Handle(process_info.hThread);

            return result; // Gibt die Struktur mit den verwalteten Handles zurück
        }

        // Injiziert eine DLL in den Remote-Prozess
        bool Inject_DLL(HANDLE process, std::string_view DLL_path, std::wstring& error_message) {
            // Allokiert Speicher im Remote-Prozess für den DLL-Pfad
            LPVOID remote_memory = VirtualAllocEx(process, // Handle des Zielprozesses
            nullptr, // Bevorzugte Adresse (nullptr, um das System wählen zu lassen)
            DLL_path.size() + 1, // Größe des Pfads + Null-Terminator
            Constants::MEMORY_ALLOCATION_TYPE, // MEM_COMMIT | MEM_RESERVE
            Constants::MEMORY_PROTECTION); // PAGE_READWRITE

            if (!remote_memory)
                return (error_message = L"Fehler bei der Speicherzuweisung im Zielprozess. Dies kann auf unzureichende Berechtigungen oder Prozessschutzmechanismen zurückzuführen sein.", false);

            // Ressourcenmanagement für den allokierten Remote-Speicher.
            // Wird automatisch freigegeben, wenn der Scope verlassen wird.
            auto memory_guard = Utils::UniqueResource<LPVOID, std::function<void(LPVOID)>>(remote_memory, 
                [process](LPVOID ptr) { // Lambda als Deleter
                    if (ptr)
                        VirtualFreeEx(process, ptr, 0, MEM_RELEASE); // Gibt den allokierten Speicher frei
                }
            );

            // Schreibt den DLL-Pfad in den allokierten Remote-Speicher
            if (!WriteProcessMemory(process, remote_memory, DLL_path.data(), DLL_path.size() + 1, nullptr))
                return (error_message = L"Fehler beim Schreiben des DLL-Pfads in den Speicher des Zielprozesses. Überprüfen Sie die Prozessberechtigungen und stellen Sie sicher, dass der DLL-Pfad zugänglich ist.", false);

            // Ermittelt das Handle für kernel32.dll (die im eigenen Prozess des Injektors geladen ist)
            HMODULE kernel32 = GetModuleHandleA(Constants::KERNEL32_DLL);
            
            if (!kernel32)
                return (error_message = L"Fehler beim Abrufen eines Handles für kernel32.dll. Dies ist eine essenzielle Systembibliothek, und dieser Fehler deutet auf ein schwerwiegendes Systemproblem hin.",ទ
            return (error_message = L"Fehler beim Abrufen eines Handles für kernel32.dll. Dies ist eine essenzielle Systembibliothek, und dieser Fehler deutet auf ein schwerwiegendes Systemproblem hin.", false);

            // Ermittelt die Adresse der Funktion LoadLibraryA in kernel32.dll.
            // Diese Adresse ist zwischen Prozessen im gleichen Betriebssystem konsistent und der Schlüssel zur Injektion.
            LPVOID load_library_addr = reinterpret_cast<LPVOID>(GetProcAddress(kernel32, Constants::LOAD_LIBRARY_FUNC));

            if (!load_library_addr)
                return (error_message = L"Fehler beim Finden der Adresse der Funktion LoadLibraryA in kernel32.dll. Dies ist entscheidend für die DLL-Injektion.", false);

            // Erstellt einen Remote-Thread im Zielprozess, um LoadLibraryA auszuführen
            // Das Argument für LoadLibraryA ist die Adresse des DLL-Pfads im Remote-Speicher
            HANDLE remote_thread = CreateRemoteThread(process, // Handle des Zielprozesses
                nullptr, // Sicherheitsattribute des Threads
                0, // Stapelgröße (0 für Standard)
                reinterpret_cast<LPTHREAD_START_ROUTINE>(load_library_addr), // Adresse von LoadLibraryA
                remote_memory, // Argument für LoadLibraryA (DLL-Pfad)
                0, // Erstellungsflags (0 für sofortigen Start)
                nullptr); // Thread-ID (nullptr, um nicht zurückzugeben)

            if (!remote_thread)
                return (error_message = L"Fehler beim Erstellen eines Remote-Threads im Zielprozess zur Ausführung der DLL-Injektion. Dies könnte auf Sicherheitsbeschränkungen oder den Prozesszustand zurückzuführen sein. Systemfehler: " + Utils::Get_System_Error_Message(GetLastError()), false);

            // Ressourcenmanagement für das Handle des Remote-Threads
            auto thread_guard = Utils::Make_Unique_Handle(remote_thread);

            // Wartet, bis der Remote-Thread (DLL-Injektion) abgeschlossen ist oder ein Timeout erreicht
            DWORD wait_result = WaitForSingleObject(remote_thread, Constants::DLL_INJECTION_TIMEOUT_MS);

            if (wait_result != WAIT_OBJECT_0) {
                return (error_message = L"Timeout oder Fehler beim Warten auf den Abschluss der DLL-Injektion. Systemfehler: " + Utils::Get_System_Error_Message(GetLastError()), false);

            // Ermittelt den Exit-Code des Remote-Threads.
            // Für LoadLibraryA bedeutet ein Exit-Code von 0 einen Fehler (konnte die DLL nicht laden).
            DWORD exit_code = 0;

            if (!GetExitCodeThread(remote_thread, &exit_code) || exit_code == 0)
                return (error_message = L"Die DLL-Injektion ist fehlgeschlagen oder hat einen Fehler zurückgegeben. Der Aufruf von LoadLibrary hat im Zielprozess möglicherweise nicht funktioniert.", false);

            return true; // Erfolgreiche Injektion
        }
};
```

> [!NOTE] Robuster Entwurf mit `std::optional` und RAII
> Das Modul `process.hpp` demonstriert einen robusten und sicheren Entwurf. Die Funktion `Create_Game_Process` gibt ein `std::optional<Process_Info>` zurück. Dies ermöglicht es der Funktion, Fehler bei der Prozesserstellung explizit und elegant zu signalisieren (durch Rückgabe eines `std::nullopt`), ohne auf Ausnahmen oder mehrdeutige Fehlercodes im Haupt-Rückgabewert zurückzugreifen.
>
> Noch entscheidender ist, dass die Struktur `Process_Info` `Utils::UniqueResource<HANDLE, std::function<void(HANDLE)>>` verwendet, um die **Handles** des Prozesses und des **Threads** zu kapseln. Dies ist ein Beispiel für das **RAII-Prinzip (Resource Acquisition Is Initialization)**, das sicherstellt, dass die `HANDLE`s des Betriebssystems (wie `hProcess` und `hThread`) automatisch über `CloseHandle` geschlossen werden, wenn das `Process_Info`-Objekt den Gültigkeitsbereich verlässt. Dies eliminiert Handle-Lecks, die eine häufige Ursache für Instabilität und übermäßigen Ressourcenverbrauch in langlaufenden **Windows-Anwendungen** sind.
>
> Ähnlich wird in der Funktion `Inject_DLL` `UniqueResource` verwendet, um den allokierten Remote-Speicher (`VirtualAllocEx`) zu verwalten, sodass er (`VirtualFreeEx`) sofort freigegeben wird, wenn er nicht mehr benötigt wird oder bei einem Fehler. Dieses rigorose Ressourcenmanagement trägt erheblich zur Zuverlässigkeit und Stabilität des **SA-MP Injector C++** bei.

### `injector_core.hpp`

Dies ist die Orchestrierungsklasse, die alle Funktionalitäten der vorherigen Module vereint. Sie koordiniert die Validierung, den Aufbau von Kommandozeilenargumenten, die Prozesserstellung und die **DLL-Injektionsaufrufe**.

```cpp
#pragma once

#include <string_view>
#include <sstream> // Für den Aufbau von Strings mit stringstream
#include <filesystem> // Für die Pfadmanipulation
//
#include "process.hpp" // Funktionen für Prozesserstellung/Injektion
#include "validation.hpp" // Validierungsfunktionen
#include "string_utils.hpp" // String-Konvertierungsfunktionen
#include "error_utils.hpp" // Fehlerbehandlungsfunktionen
#include "constants.hpp" // Globale Konstanten
#include "types.hpp" // Injektionstypen

namespace Injector {
    class Injector_Core {
        public:
            // Konstruktoren/Destruktoren für Move-Semantik
            Injector_Core() = default;
            Injector_Core(const Injector_Core&) = delete; // Kopieren deaktivieren
            Injector_Core& operator=(const Injector_Core&) = delete; // Kopierzuweisung deaktivieren
            Injector_Core(Injector_Core&&) = default; // Move-Semantik aktivieren
            Injector_Core& operator=(Injector_Core&&) = default; // Move-Zuweisung aktivieren
            ~Injector_Core() = default;

            // Hauptfunktion, die die Initialisierung und Injektion des Spiels orchestriert
            bool Initialize_Game(Types::Inject_Type inject_type, std::wstring_view folder, 
                std::wstring_view nickname, 
                std::wstring_view ip, 
                std::wstring_view port, 
                std::wstring_view password) {
                namespace fs = std::filesystem; // Alias für std::filesystem

                // Baut die vollständigen Pfade für die essentiellen Dateien
                fs::path game_path = fs::path(folder) / Constants::GAME_EXE_NAME; // z.B. C:\GTA\gta_sa.exe
                fs::path samp_DLL_path = fs::path(folder) / Constants::SAMP_DLL_NAME; // z.B. C:\GTA\samp.dll
                fs::path omp_DLL_path = fs::path(folder) / Constants::OMP_DLL_NAME; // z.B. C:\GTA\omp-client.dll

                // 1. Dateivalidierung
                if (!Utils::Validate_Files(game_path, samp_DLL_path, omp_DLL_path, inject_type))
                    return false; // Fehler wurde bereits von der Validierungsfunktion angezeigt
                
                std::wstring error_message_local; // Für Fehlermeldungen der Validierungen

                // 2. Portvalidierung
                if (!Utils::Validate_Port(port, error_message_local))
                    return (Utils::Show_Error(error_message_local, inject_type), false);

                // 3. Nickname-Validierung
                if (!Utils::Validate_Nickname(nickname, error_message_local))
                    return (Utils::Show_Error(error_message_local, inject_type), false);

                // 4. Konvertierung von Wide-Char in Local 8-Bit (erforderlich für ANSI-APIs)
                std::string nickname_str = Utils::Wide_To_Local_8Bit(nickname);
                std::string ip_str = Utils::Wide_To_Local_8Bit(ip);
                std::string port_str = Utils::Wide_To_Local_8Bit(port);
                std::string password_str = Utils::Wide_To_Local_8Bit(password);
                // Konvertiert auch die Pfade in std::string (erforderlich für CreateProcessA als char*)
                std::string game_path_str = Utils::Wide_To_Local_8Bit(game_path.wstring());
                std::string folder_str = Utils::Wide_To_Local_8Bit(folder);
                std::string samp_DLL_path_str = Utils::Wide_To_Local_8Bit(samp_DLL_path.wstring());
                std::string omp_DLL_path_str = Utils::Wide_To_Local_8Bit(omp_DLL_path.wstring());

                // 5. Aufbau der Kommandozeilenargumente
                std::string args = Build_Command_Args(nickname_str, ip_str, port_str, password_str);

                // Instanziiert die Process-Klasse zur Verwaltung der Prozessoperationen
                Process process_core;
                
                // 6. Erstellung des Spielprozesses (suspendiert)
                auto process_info_opt = process_core.Create_Game_Process(game_path_str, args, folder_str);

                if (!process_info_opt)
                    return false; // Fehler wurde bereits von der Prozesserstellungsfunktion angezeigt

                // Dereferenziert das optional, um die Process_Info-Struktur zu erhalten
                auto& process_info = *process_info_opt; 
                std::wstring inject_error_message; // Für Fehlermeldungen der Injektion

                // 7. Injektion von samp.dll
                if (!process_core.Inject_DLL(process_info.process_handle.get(), samp_DLL_path_str, inject_error_message))
                    return (Utils::Show_Error(L"Fehler beim Injizieren von samp.dll: " + inject_error_message, inject_type), false);

                // 8. Bedingte Injektion von omp-client.dll (nur für OMP)
                if (inject_type == Types::Inject_Type::OMP) {
                    if (!process_core.Inject_DLL(process_info.process_handle.get(), omp_DLL_path_str, inject_error_message))
                        return (Utils::Show_Error(L"Fehler beim Injizieren von omp-client.dll: " + inject_error_message, inject_type), false);
                }

                // 9. Fortsetzen des Spielprozesses
                // Der Prozess wurde im suspendierten Zustand erstellt, um die Injektion zu ermöglichen.
                // Nachdem die DLLs injiziert wurden, kann er fortgesetzt werden.
                if (ResumeThread(process_info.thread_handle.get()) == static_cast<DWORD>(-1))
                    return (Utils::Show_Error(L"Fehler beim Fortsetzen des Threads des Spielprozesses: " + Utils::Get_System_Error_Message(GetLastError()), inject_type), false);

                return true; // Erfolg in allen Schritten!
            }
        private:
            // Baut den String der Kommandozeilenargumente für das Spiel-Executable
            std::string Build_Command_Args(const std::string& nickname, const std::string& ip, const std::string& port, const std::string& password) {
                std::stringstream command_args_stream; // Verwendet stringstream für effizienten Aufbau

                // SA-MP und OMP erwarten die Argumente "-c -n [nickname] -h [ip] -p [port]"
                command_args_stream << Constants::CMD_ARG_CONFIG << " " 
                    << Constants::CMD_ARG_NICKNAME << " " << nickname << " " 
                    << Constants::CMD_ARG_HOST << " " << ip << " " 
                    << Constants::CMD_ARG_PORT << " " << port;

                // Fügt das Passwort nur hinzu, wenn es nicht leer ist
                if (!password.empty())
                    command_args_stream << " " << Constants::CMD_ARG_PASSWORD << " " << password;

                return command_args_stream.str();
            }
    };
}
```

> [!CAUTION] Doppelte Injektion (SA-MP und OMP)
> Obwohl der Prozess für **OMP** das Injizieren der `omp-client.dll` *zusätzlich* zur `samp.dll` umfasst, entspricht dies der Funktionsweise von **OMP**. Der **OMP**-Client verwendet oft die `samp.dll` als **Basis** oder **Proxy** für bestimmte Funktionen, während `omp-client.dll` das Verhalten erweitert oder überschreibt.
>
> Es ist entscheidend, dass **beide DLLs** im Spielverzeichnis vorhanden und funktionsfähig sind, damit die **OMP-Injektion** erfolgreich ist. Wenn eine fehlschlägt, kann das Spiel möglicherweise nicht korrekt initialisiert werden oder der Multiplayer-Client wird nicht geladen.

### `injector.hpp`

Dies ist die Schnittstellen-Datei der Bibliothek. Sie ist die einzige Datei, die der Endbenutzer einbinden muss, um den **SA-MP Injector C++** zu verwenden. Sie fungiert als Wrapper für die Klasse `Injector::Injector_Core` und vereinfacht die Schnittstelle zu einer einzigen globalen Funktion, `Initialize_Game`.

```cpp
#pragma once

#include <string_view>
//
#include "injector_core.hpp" // Die Hauptklasse mit der Logik
#include "error_utils.hpp" // Für die Fehleranzeige (bei ungültigem Injektionstyp)
#include "types.hpp" // Aufzählung der Typen
#include "constants.hpp" // Konstanten (für Namen der Injektionstypen)

// Die High-Level-Schnittstelle der Bibliothek.
// Vereinfacht die Nutzung, indem nur diese globale Funktion bereitgestellt wird.
inline bool Initialize_Game(std::wstring_view inject_type_str, std::wstring_view folder, 
    std::wstring_view nickname, 
    std::wstring_view ip, 
    std::wstring_view port, 
    std::wstring_view password) {
    Types::Inject_Type type; // Variable zur Speicherung des Injektionstyps

    // Konvertiert den Injektionstyp-String in das Inject_Type-Enum
    if (inject_type_str == Constants::INJECT_TYPE_SAMP)
        type = Types::Inject_Type::SAMP;
    
    else if (inject_type_str == Constants::INJECT_TYPE_OMP)
        type = Types::Inject_Type::OMP;
    
    else
        // Wenn der Injektionstyp-String ungültig ist, zeigt einen Fehler an und gibt false zurück
        return (Utils::Show_Error(L"Ungültiger Injektionsmodus angegeben. Bitte verwenden Sie 'samp' oder 'omp'.", Types::Inject_Type::SAMP), false); // Fallback auf SAMP für den Titel

    Injector::Injector_Core injector; // Instanziiert das Objekt mit der zentralen Logik
    
    // Delegiert den Aufruf an die Initialize_Game-Funktion der Injector_Core-Klasse
    return injector.Initialize_Game(type, folder, nickname, ip, port, password);
}
```

> [!NOTE] Inline-Design für `header-only`
> Die Verwendung des Schlüsselworts `inline` für alle Funktionen in dieser Datei und anderen Utility-Dateien ermöglicht es, dass die Bibliothek `header-only` ist. `inline` schlägt dem Compiler vor, den Funktionskörper direkt an den Aufrufstellen einzufügen, aber der Haupteffekt hier ist die Lockerung der **One Definition Rule (ODR)**, sodass die Funktion in mehreren `.obj`-Dateien definiert werden kann (was passiert, wenn mehrere `.cpp`-Dateien `injector.hpp` einbinden). Die **Linkage**-Phase stellt sicher, dass nur eine endgültige Version im ausführbaren Programm existiert.

## Umfassende Anwendungsbeispiele

Um den **SA-MP Injector C++** in Ihr Projekt zu integrieren, folgen Sie den Anweisungen und analysieren Sie die folgenden Szenarien.

### 1. Vorbereitung der Entwicklungsumgebung

- **C++-Compiler**: Es wird ein Compiler empfohlen, der **C++17** unterstützt. **Visual Studio** mit `vcpkg` (für `std::filesystem`) oder **GCC/Clang (Version 17+)** sind geeignete Optionen.
- **Projektkonfiguration**:
  - Erstellen Sie ein neues **C++**-Projekt (z.B. ein Konsolenprojekt).
  - Kopieren Sie **alle** `.hpp`-Dateien des **SA-MP Injector C++** in einen für Ihr Projekt zugänglichen Ordner (z.B. in den **Header**-Ordner).
  - Stellen Sie sicher, dass der **C++-Standard** auf **C++17** eingestellt ist. Dies ist entscheidend für die maximale Kompatibilität mit den **SA-MP**- und **OMP**-Bibliotheken. In **Visual Studio**: `Projekteigenschaften > Konfigurationseigenschaften > C/C++ > Sprache > C++-Sprachstandard -> "ISO C++17 Standard (/std:c++17)"`
- **Berechtigungen**: Ihr ausführbares Programm benötigt möglicherweise **Administratorrechte (nicht zwingend)**, um Prozesse zu erstellen und **DLLs zu injizieren** im Systemumfeld. In **Visual Studio** kann dies eingestellt werden unter: `Projekteigenschaften > Konfigurationseigenschaften > Linker > Manifestdatei > UAC-Ausführungsebene -> "requireAdministrator (/LEVEL='requireAdministrator')"`

### 2. Basisszenario: Verbindung zu einem SA-MP-Server

Dies ist der häufigste Anwendungsfall, bei dem **GTA:SA** gestartet und mit einem bestimmten **Nickname** und **IP**/**Port** mit einem **SA-MP**-Server verbunden wird.

```cpp
// main.cpp
#include <iostream>
#include <string>
#include <codecvt> // Für std::wstring_convert (veraltet, aber für diesen Fall funktional)
#include <locale> // Für std::codecvt_utf8_to_utf16
//
#include "injector.hpp" // Die einzige erforderliche Einbindung der Bibliothek!

int Main(int argc, char* argv[]) {
    // Definition der Konfigurationsvariablen
    // Ändern Sie diese Pfade und Serverdetails entsprechend Ihrer lokalen Konfiguration
    std::wstring folder = L"C:\\Spiele\\GTA San Andreas"; // Wo sich gta_sa.exe, samp.dll befinden
    std::wstring nickname = L"Name";
    std::wstring ip = L"127.0.0.1"; // Beispiel: Ihr lokaler Server
    std::wstring port = L"7777";
    std::wstring password = L""; // Leer lassen, wenn kein Passwort vorhanden ist

    // Optional: Ermöglicht dem Benutzer, Konfigurationen über die Kommandozeile anzugeben (vereinfacht)
    // Für eine robustere Behandlung von Argumenten verwenden Sie eine Argument-Parsing-Bibliothek.
    if (argc > 1) {
        // Beispiel: Wenn das erste Argument ein Pfad ist
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

    std::wcout << L"Starte SA-MP..." << std::endl;
    std::wcout << L"Spielordner: " << folder << std::endl;
    std::wcout << L"Nickname: " << nickname << std::endl;
    std::wcout << L"Server: " << ip << L":" << port << std::endl;

    // Aufruf der Bibliotheksfunktion zum Starten des Spiels
    if (Initialize_Game(L"samp", // Injektionstyp: SA-MP
        folder, // Pfad zum Spielordner
        nickname, // Gewünschter Nickname
        ip, // Server-IP
        port, // Server-Port (String)
        password)) { // Server-Passwort (String, kann leer sein)
        std::wcout << L"\n--- SA-MP erfolgreich gestartet! ---" << std::endl;
        std::wcout << L"Das Spiel wurde in einem separaten Prozess gestartet." << std::endl;
    }
    else {
        std::wcout << L"\n--- FEHLER beim Starten von SA-MP! ---" << std::endl;
        std::wcout << L"Überprüfen Sie die angezeigten Fehlermeldungen." << std::endl;
    }

    // Hält die Konsole offen, um die Ausgaben anzuzeigen
    std::wcout << L"\nDrücken Sie Enter, um das Programm zu schließen." << std::endl;
    std::wcin.ignore();

    return 0;
}
```

**Zum Kompilieren und Ausführen:**

```bash
# Beispiel mit g++ (Linux/MinGW/MSYS2) - Erfordert libstdc++fs für filesystem
# Es ist wichtig sicherzustellen, dass die Toolchain keine C++-Version verwendet,
# die Inkompatibilitäten im Injektionsprozess verursacht.
# Überprüfen Sie die Dokumentation Ihres Compilers für Flags zur binären Kompatibilität (ABI).
g++ main.cpp -o my_launcher -std=c++17 -Wall -lstdc++fs -municode -lkernel32

# Beispiel mit MSVC (Visual Studio Developer Command Prompt)
# Die Flag '/std:c++17' gewährleistet die Konformität mit C++17.
cl /EHsc /std:c++17 /permissive- /FS /utf-8 main.cpp /link /OUT:my_launcher.exe
```

> [!NOTE] Compiler- und C++-Kompatibilität
> **SA-MP** und **OMP** sind als Legacy-Projekte mit spezifischen Tools kompiliert, die ihre **Application Binary Interface (ABI)** definieren. Obwohl diese Bibliothek **C++17** verwendet, **ist es entscheidend, dass die DLLs von SA-MP und OMP, mit denen sie interagiert, auch mit der ABI Ihres Compilers und der verwendeten C++-Laufzeitversion (CRT) kompatibel sind**.
>
> Die Verwendung eines Compilers oder einer **C++**-Version, die sich stark von der unterscheidet, die zum **Erstellen der DLLs** des Spiels verwendet wurde, kann zu subtilen Problemen führen (z.B. bei der Speicherzuweisung oder Parameterübergabe), die nicht leicht **diagnostizierbar** sind und keinen expliziten Fehler des Injektors verursachen. Aus diesem Grund ist **C++17 die maximal empfohlene Version**, da neuere Versionen Änderungen in der **ABI** oder **CRT** einführen können, die von älteren Spielmodulen nicht toleriert werden.

### 3. Fortgeschrittenes Szenario: Verbindung zu einem OMP-Server

Für **OMP** ist die Logik identisch mit der von **SA-MP**, aber Sie geben `L"omp"` als `inject_type` an und stellen sicher, dass die `omp-client.dll` im Spielverzeichnis vorhanden ist.

```cpp
// main.cpp
#include <iostream>
#include <string>
#include <codecvt> // Für std::wstring_convert (veraltet, aber für diesen Fall funktional)
#include <locale> // Für std::codecvt_utf8_to_utf16
//
#include "injector.hpp" // Die einzige erforderliche Einbindung der Bibliothek!

int Main() {
    // Definition der Konfigurationsvariablen
    // Ändern Sie diese Pfade und Serverdetails entsprechend Ihrer lokalen Konfiguration
    std::wstring folder = L"C:\\Spiele\\GTA San Andreas"; // Wo sich gta_sa.exe, samp.dll und omp-client.dll befinden
    std::wstring nickname = L"Name";
    std::wstring ip = L"127.0.0.1"; // Beispiel: Ihr lokaler Server
    std::wstring port = L"7777";
    std::wstring password = L""; // Leer lassen, wenn kein Passwort vorhanden ist

    // Optional: Ermöglicht dem Benutzer, Konfigurationen über die Kommandozeile anzugeben (vereinfacht)
    // Für eine robustere Behandlung von Argumenten verwenden Sie eine Argument-Parsing-Bibliothek.
    if (argc > 1) {
        // Beispiel: Wenn das erste Argument ein Pfad ist
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

    std::wcout << L"Starte OMP..." << std::endl;
    std::wcout << L"Spielordner: " << folder << std::endl;
    std::wcout << L"Nickname: " << nickname << std::endl;
    std::wcout << L"Server: " << ip << L":" << port << std::endl;

    // Aufruf der Bibliotheksfunktion zum Starten des Spiels
    if (Initialize_Game(L"omp", // Injektionstyp: OMP
        folder, // Pfad zum Spielordner
        nickname, // Gewünschter Nickname
        ip, // Server-IP
        port, // Server-Port (String)
        password)) { // Server-Passwort (String, kann leer sein)
        std::wcout << L"\n--- OMP erfolgreich gestartet! ---" << std::endl;
        std::wcout << L"Das Spiel wurde in einem separaten Prozess gestartet." << std::endl;
    }
    else {
        std::wcout << L"\n--- FEHLER beim Starten von OMP! ---" << std::endl;
        std::wcout << L"Überprüfen Sie die angezeigten Fehlermeldungen." << std::endl;
    }

    // Hält die Konsole offen, um die Ausgaben anzuzeigen
    std::wcout << L"\nDrücken Sie Enter, um das Programm zu schließen." << std::endl;
    std::wcin.ignore();

    return 0;
}
```

## Behandlung häufiger Fehler und Meldungen

Der **SA-MP Injector C++** legt großen Wert auf Benutzerfreundlichkeit, und ein wesentlicher Teil davon ist die Bereitstellung von **klaren Rückmeldungen** im Falle eines Fehlers. Die Fehlermeldungen werden durch **Windows-Dialogfenster** (`MessageBoxW`) angezeigt und sind nach dem Typ der **Injektion (SA-MP oder OMP)** kategorisiert, um mehr Kontext zu bieten. Dies stellt sicher, dass Sie genau wissen, was schiefgelaufen ist und wie Sie das Problem beheben können.

Hier sind einige der häufigsten Fehler, auf die Sie stoßen könnten, zusammen mit ihren wahrscheinlichen Ursachen/Lösungen, begleitet von visuellen Beispielen, wie diese Dialogfenster für den Endbenutzer aussehen:

### 1. Ungültiger Injektionstyp

Wenn der in der Funktion `Initialize_Game` angegebene `inject_type` weder `L"samp"` noch `L"omp"` ist, weiß die Bibliothek nicht, welchen Multiplayer-Client Sie initialisieren möchten.

![Fehler 1](screenshots/error_1.png)

- **Angezeigte Fehlermeldung**: `"Ungültiger Injektionsmodus angegeben. Bitte verwenden Sie 'samp' oder 'omp'."`
- **Ursache**: Das erste Argument der Funktion `Initialize_Game` (`std::wstring_view inject_type`) entspricht nicht den erwarteten Werten `L"samp"` oder `L"omp"`. Dies kann ein Tippfehler, ein leerer String oder ein unbekannter Wert sein.
- **Lösung**: Überprüfen Sie, ob `std::wstring_view inject_type_str` korrekt auf `L"samp"` oder `L"omp"` gesetzt ist. Es ist wichtig, das Präfix `L` für **Wide-Character-Literale** zu verwenden, um die Kompatibilität mit den Konstanten der Bibliothek zu gewährleisten.
    ```cpp
    // Korrekt:
    Initialize_Game(L"samp", /* andere Parameter */);
    Initialize_Game(L"omp", /* andere Parameter */);

    // Falsch (verursacht Fehler):
    // Initialize_Game(L"invalid", /* andere Parameter */);
    // Initialize_Game(L"", /* andere Parameter */);
    ```

### 2. Ungültiger Server-Port (Format oder Bereich)

Der Port ist ein essentieller numerischer Parameter für die Serververbindung. Dieser Fehler tritt auf, wenn der Wert nicht als gültige Zahl interpretiert werden kann oder außerhalb des akzeptablen Bereichs **(1 bis 65535)** liegt.

#### 2.1. Nicht-numerisches Port-Format

![Fehler 2](screenshots/error_2.png)

- **Angezeigte Fehlermeldung**: `"Ungültiges Portformat. Der Port muss ein numerischer Wert sein. Bitte geben Sie eine gültige Ganzzahl für den Port ein."`
- **Ursache**: Das Argument `port` (`std::wstring_view`) enthält Zeichen, die keine numerischen Ziffern sind oder nicht in eine Ganzzahl konvertiert werden können.
- **Lösung**: Geben Sie einen String an, der nur Ziffern enthält und eine gültige Ganzzahl darstellt.
    ```cpp
    // Korrekt:
    Initialize_Game(/* andere Parameter */, L"7777", /* andere Parameter */);

    // Falsch (ungültiges Format):
    // Initialize_Game(/* andere Parameter */, L"port7777", /* andere Parameter */);

    // Falsch (ungültig):
    // Initialize_Game(/* andere Parameter */, L"invalid", /* andere Parameter */);
    ```

#### 2.2. Port außerhalb des gültigen Bereichs

![Fehler 3](screenshots/error_3.png)

- **Angezeigte Fehlermeldung**: `"Die angegebene Portnummer (XXXX) liegt außerhalb des gültigen Bereichs von 1 bis 65535. Bitte geben Sie einen gültigen Port ein."` (Das **XXXX** wird der von Ihnen verwendete Wert sein).
- **Ursache**: Der angegebene Port ist eine gültige Zahl, liegt aber unter `1` (reserviert oder nicht nutzbar) oder über `65535` (maximaler Bereich für **TCP/UDP-Ports**).
- **Lösung**: Geben Sie einen Port an, der im Bereich von `1` bis `65535` liegt. Häufige Ports für **SA-MP**/**OMP** sind `7777` oder `7778`.
    ```cpp
    // Korrekt:
    Initialize_Game(/* andere Parameter */, L"7777", /* andere Parameter */);

    // Falsch (außerhalb des Bereichs):
    // Initialize_Game(/* andere Parameter */, L"0", /* andere Parameter */); // Zu niedrig
    // Initialize_Game(/* andere Parameter */, L"65536", /* andere Parameter */); // Zu hoch
    // Initialize_Game(/* andere Parameter */, L"-1", /* andere Parameter */); // Negativer Wert
    ```

### 3. Ungültiger Nickname (Leer oder zu lang)

Der **Nickname** des Spielers wird validiert, um sicherzustellen, dass der Spiel-Client ihn akzeptiert.

#### 3.1. Leerer Nickname

![Fehler 4](screenshots/error_4.png)

- **Angezeigte Fehlermeldung**: `"Nickname darf nicht leer sein. Bitte geben Sie einen gültigen Nickname ein."`
- **Ursache**: Das Argument `nickname` (`std::wstring_view`) wurde als leerer String angegeben.
- **Lösung**: Stellen Sie sicher, dass der Nickname nicht leer ist.
    ```cpp
    // Korrekt:
    Initialize_Game(/* andere Parameter */, L"Name", /* andere Parameter */);

    // Falsch (leer):
    // Initialize_Game(/* andere Parameter */, L"", /* andere Parameter */);
    ```

#### 3.2. Zu langer Nickname

![Fehler 5](screenshots/error_5.png)

- **Angezeigte Fehlermeldung**: `"Die Länge des Nicknames überschreitet das erlaubte Maximum von 20 Zeichen. Bitte verwenden Sie einen kürzeren Nickname."`
- **Ursache**: Die Länge des angegebenen **Nicknames** überschreitet `Constants::MAX_NICKNAME_LENGTH`, das sind `20` Zeichen.
- **Lösung**: Verwenden Sie einen **Nickname**, der maximal `20` Zeichen lang ist.
    ```cpp
    // Korrekt:
    Initialize_Game(/* andere Parameter */, L"Name", /* andere Parameter */);

    // Falsch (zu lang):
    // Initialize_Game(/* andere Parameter */, L"DieserNicknameIstVielZuLangUndÜberschreitetZwanzigZeichen", /* andere Parameter */);
    ```

### 4. Spiel- oder DLL-Dateien nicht gefunden

Dies ist eine der häufigsten Ursachen für einen Fehler. Die Bibliothek benötigt `gta_sa.exe`, `samp.dll` und für **OMP** auch `omp-client.dll` an den erwarteten Orten.

#### 4.1. Spielausführbare Datei (`gta_sa.exe`) nicht gefunden

![Fehler 6](screenshots/error_6.png)

- **Angezeigte Fehlermeldung**: `"Spielausführbare Datei nicht gefunden. Bitte stellen Sie sicher, dass 'gta_sa.exe' am angegebenen Pfad existiert: [vollständiger Pfad]"`. Der `[vollständige Pfad]` enthält den Ordner und den Dateinamen.
- **Ursache**: Die Datei `gta_sa.exe` wurde im angegebenen Ordner im Argument `folder` nicht gefunden.
- **Lösung**:
  1. Überprüfen Sie, ob der `folder` (`std::wstring_view`) auf das korrekte Installationsverzeichnis von **GTA San Andreas** zeigt.
  2. Bestätigen Sie, dass `gta_sa.exe` in diesem Ordner existiert und der Name nicht geändert wurde.

#### 4.2. SA-MP-Bibliothek (`samp.dll`) nicht gefunden

![Fehler 7](screenshots/error_7.png)

- **Angezeigte Fehlermeldung**: `"SA-MP-Bibliothek nicht gefunden. Bitte stellen Sie sicher, dass 'samp.dll' am angegebenen Pfad existiert: [vollständiger Pfad]"`.
- **Ursache**: Die Datei `samp.dll` wurde im angegebenen Ordner im Argument `folder` nicht gefunden. **Diese DLL** ist eine Voraussetzung für **beide** Injektionstypen (`samp` und `omp`).
- **Lösung**: Stellen Sie sicher, dass `samp.dll` im Installationsordner von **GTA San Andreas** vorhanden ist.

#### 4.3. OMP-Bibliothek (`omp-client.dll`) nicht gefunden (nur für OMP-Injektion)

![Fehler 8](screenshots/error_8.png)

- **Angezeigte Fehlermeldung**: `"OMP-Bibliothek nicht gefunden. Bitte stellen Sie sicher, dass 'omp-client.dll' am angegebenen Pfad für die OMP-Injektion existiert: [vollständiger Pfad]"`.
- **Ursache**: Wenn Sie `L"omp"` als Injektionstyp angegeben haben, aber die Datei `omp-client.dll` im angegebenen Ordner nicht gefunden wurde.
- **Lösung**: Laden Sie den neuesten **OMP**-Client herunter und stellen Sie sicher, dass `omp-client.dll` (und `samp.dll`) im Installationsordner von **GTA San Andreas** vorhanden sind.

### 5. Fehler beim Erstellen des Spielprozesses

Dies ist ein komplexerer Fehler, da er **Berechtigungen des Betriebssystems** und den aktuellen Zustand von `gta_sa.exe` betrifft.

![Error 9](screenshots/error_9.png)

- **Angezeigte Fehlermeldung**: `"Failed to create game process. Ensure 'gta_sa.exe' is not running and you have sufficient permissions to execute the file. System Error: [Fehlermeldung des Betriebssystems]"`. Die Systemmeldung wird durch `GetLastError()` hinzugefügt (z. B. `Access is denied.` oder `The requested operation requires elevation.`).
- **Ursache**: Der Aufruf von `CreateProcessA`, um `gta_sa.exe` zu starten, ist fehlgeschlagen. Häufige Ursachen sind:
  - **Prozess bereits aktiv**: Eine Instanz von `gta_sa.exe` läuft bereits und blockiert eine neue Ausführung.
  - **Unzureichende Berechtigungen**: Ihre Anwendung hat nicht die erforderlichen Berechtigungen (z. B. Administrator), um einen Prozess unter bestimmten Systemkonfigurationen zu erstellen (**UAC** aktiviert, geschützte Ordner usw.).
  - **Probleme mit der ausführbaren Datei**: `gta_sa.exe` könnte beschädigt oder durch ein anderes Programm blockiert sein (z. B. ein falsch konfiguriertes Antivirenprogramm).
- **Lösung**:
  1. Überprüfen Sie den Task-Manager und stellen Sie sicher, dass keine Instanz von `gta_sa.exe` läuft. Beenden Sie jede Instanz, falls vorhanden.
  2. Führen Sie Ihre Anwendung, die die Bibliothek verwendet, mit **Administratorrechten** aus. Klicken Sie mit der rechten Maustaste auf die ausführbare Datei und wählen Sie **"Als Administrator ausführen"**.
  3. Falls ein **Antivirenprogramm** oder eine **Sicherheitssoftware** stört, fügen Sie Ihre Anwendung und/oder den Ordner von **GTA:SA** zu den Ausnahmen des Antivirenprogramms hinzu (gehen Sie dabei vorsichtig vor und nur, wenn Sie sicher sind, dass Ihre Dateien integer sind).

### 6. Fehler bei der Speicherzuweisung im Zielprozess

Die Bibliothek versucht, einen kleinen Speicherbereich in `gta_sa.exe` zuzuweisen, um den **Pfad der DLL** zu kopieren.

![Error 10](screenshots/error_10.png)

- **Angezeigte Fehlermeldung**: `"Failed to allocate memory in the target process. This might be due to insufficient permissions or process protection mechanisms."`
- **Ursache**: Die Funktion `VirtualAllocEx` (verwendet, um Speicher in einem anderen Prozess zuzuweisen) ist fehlgeschlagen. Dies ist wahrscheinlicher, wenn:
  - Der **GTA:SA**-Prozess (auch im angehaltenen Zustand) Sicherheitsmechanismen oder **Anti-Injection-Patches** besitzt, die die Speicherzuweisung durch externe Prozesse verhindern.
  - Ihre Anwendung nicht die erforderlichen erhöhten Berechtigungen hat, um den Speicher eines anderen Prozesses zu manipulieren.
  - (Weniger häufig) Es gibt eine extreme Knappheit an virtuellem Speicher im System.
- **Lösung**:
  1. Führen Sie Ihre Anwendung mit **Administratorrechten** aus.
  2. Stellen Sie sicher, dass das Spiel keine Modifikationen oder **Sicherheits-Patches** hat, die Versuche der Speichermanipulation oder -injektion blockieren könnten (dies ist häufiger in modifizierten Umgebungen oder mit bestimmten Drittanbieter-Anti-Cheat-Tools).

### 7. Fehler beim Schreiben des DLL-Pfads in den Speicher des Prozesses

Nach der Speicherzuweisung versucht die Bibliothek, den **Pfad der DLL** in diesen zu kopieren.

![Error 11](screenshots/error_11.png)

- **Angezeigte Fehlermeldung**: `"Failed to write DLL path to the target process memory. Verify process permissions and ensure the DLL path is accessible."`
- **Ursache**: Die Funktion `WriteProcessMemory` konnte die **Bytes des DLL-Pfads** nicht in den zugewiesenen Speicher von `gta_sa.exe` kopieren. Dies deutet normalerweise auf Folgendes hin:
  - **Schreibrechte**: Ihre Anwendung hat keine Berechtigung, in diesen Speicherbereich oder den **GTA:SA**-Prozess zu schreiben.
  - **Ungültiges Handle**: Das **Handle** des Prozesses (`process_handle`) wurde zwischen Zuweisung und Schreiben ungültig, was aufgrund der Verwendung von `UniqueResource` sehr selten ist, aber unter extremen Systembedingungen auftreten kann.
  - **Speicherschutzprobleme**: Ein Speicherschutz (entweder vom **Betriebssystem** oder von Spielmodifikationen) hat das Schreiben verhindert.
- **Lösung**: Führen Sie die Anwendung als **Administrator** aus. Überprüfen Sie, ob `gta_sa.exe` und seine Umgebung frei von Tools sind, die Speicheroperationen blockieren könnten.

### 8. Fehler beim Finden essentieller Systemfunktionen

Dies sind **APIs**, die für **Windows** entscheidend sind; Fehler hier deuten auf ein grundlegendes Problem mit dem Betriebssystem oder der Ausführungsumgebung hin.

#### 8.1. `kernel32.dll` nicht gefunden

![Error 12](screenshots/error_12.png)

- **Angezeigte Fehlermeldung**: `"Failed to obtain a handle to kernel32.dll. This is an essential system library and this error indicates a severe system issue."`
- **Ursache**: `kernel32.dll` ist eine der grundlegendsten **DLLs** von **Windows** und enthält essentielle Funktionen wie `CreateProcess`, `VirtualAllocEx` usw. Wenn `GetModuleHandleA` kein **Handle** für sie erhält, hat das Betriebssystem sehr ernste Probleme.
- **Lösung**: Dies ist ein **kritischer** Fehler, der selten durch die Bibliothek oder Ihre Anwendung verursacht wird. Er deutet auf eine Beschädigung von Systemdateien, schwerwiegende Probleme mit **Windows** oder eine hochgradig ungewöhnliche **Betriebssysteminstallation** hin. Es wird empfohlen, Integritätsprüfungen des Systems durchzuführen (z. B. `sfc /scannow` in der **Eingabeaufforderung** als **Administrator**) oder im schlimmsten Fall **Windows** neu zu installieren.

#### 8.2. `LoadLibraryA` nicht gefunden

![Error 13](screenshots/error_13.png)

- **Angezeigte Fehlermeldung**: `"Failed to find the address of the LoadLibraryA function in kernel32.dll. This is critical for injecting the DLL."`
- **Ursache**: Obwohl `kernel32.dll` gefunden wurde, konnte die Funktion `LoadLibraryA` über `GetProcAddress` nicht aufgelöst werden. Obwohl extrem selten, kann dies das Ergebnis einer Beschädigung der **DLL-Datei** von `kernel32.dll` oder einer hochgradig nicht standardmäßigen Ausführungsumgebung sein.
- **Lösung**: Wie beim obigen Fehler von `kernel32.dll` deutet dies auf ein ernsthaftes Problem im Betriebssystem hin.

### 9. Fehler beim Erstellen eines Remote-Threads für die Injektion

Nach der Vorbereitung der Remote-Umgebung und dem Kopieren des **DLL-Pfads** wird ein neuer **Thread** im Spielprozess erstellt, um `LoadLibraryA` aufzurufen.

![Error 14](screenshots/error_14.png)

- **Angezeigte Fehlermeldung**: `"Failed to create a remote thread in the target process to execute the DLL injection. This could be due to security restrictions or process state. System Error: [Fehlermeldung des Betriebssystems]"`.
- **Ursache**: Der Aufruf von `CreateRemoteThread` ist fehlgeschlagen. Dieser Fehler tritt häufig in Systemen mit robusten **Anti-Injection**-Mechanismen auf oder wenn ein Programm das Verhalten des Prozesses intensiv überwacht:
  - **Sicherheitsmechanismen**: **Anti-Cheat**-Tools, **Sicherheitssoftware** oder bestimmte **Windows**-Richtlinien können Versuche erkennen und blockieren, **Threads** in Prozessen von Drittanbietern zu erstellen.
  - **Inkonsistenter Zielprozess**: Wenn der **GTA:SA**-Prozess in einem unerwarteten oder instabilen Zustand ist (obwohl in `CREATE_SUSPENDED` gestartet), kann dies die Fähigkeit beeinträchtigen, **Threads** zu erstellen.
- **Lösung**:
  1. Führen Sie Ihre Anwendung mit **Administratorrechten** aus.
  2. Überprüfen Sie, ob keine **Anti-Cheat**-Tools, **aggressiven Antivirenprogramme** oder **Firewalls** konfiguriert sind, um die Prozessmanipulation zu überprüfen und zu blockieren. Fügen Sie Ihre Anwendung und `gta_sa.exe` gegebenenfalls zu den Ausnahmen hinzu (mit Vorsicht).
  3. Die Fehlermeldung des Systems (`GetLastError()`) kann zusätzliche Details zur Untersuchung der spezifischen Ursache liefern (z. B. **"Ein Prozess wurde daran gehindert, Threads für andere Prozesse zu erstellen."**).

### 10. Timeout oder Fehler beim Abschluss der Injektion

Nach dem Erstellen des **Remote-Threads** wartet der Injektor darauf, dass dieser die **Ladung der DLL** abschließt.

![Error 15](screenshots/error_15.png)

- **Angezeigte Fehlermeldung**: `"Timeout or error waiting for DLL injection to complete. System Error: [Fehlermeldung des Betriebssystems]"`.
- **Ursache**: Der **Remote-Thread**, der `LoadLibraryA` ausführt, hat länger als `Constants::DLL_INJECTION_TIMEOUT_MS` (10 Sekunden) benötigt, um zurückzukehren, oder er ist fehlgeschlagen und `GetExitCodeThread` hat 0 zurückgegeben. Mögliche Ursachen sind:
  - **Probleme mit der injizierten DLL**: Die `DllMain` von `samp.dll` oder `omp-client.dll` dauert zu lange, enthält eine **Endlosschleife**, einen **Absturz** oder einen Fehler, der das ordnungsgemäße Laden der **DLL** verhindert (z. B. fehlende **DLL-Abhängigkeiten**).
  - **Stilles Blockieren**: Ein Sicherheitsmechanismus hat `LoadLibraryA` möglicherweise blockiert, ohne einen offensichtlichen Fehler bei der Thread-Erstellung zu melden.
- **Lösung**:
  1. Überprüfen Sie die Integrität der Dateien `samp.dll` und `omp-client.dll`. Sie könnten beschädigt sein oder eine Version verwenden, die mit Ihrem `gta_sa.exe` inkompatibel ist.
  2. Stellen Sie sicher, dass die **injizierte DLL** nicht von **anderen DLLs** abhängt, die im System fehlen oder nicht zugänglich sind.

### 11. Fehler beim Fortsetzen des Threads des Spielprozesses

Dies ist der letzte Schritt, um das Spiel zu starten, nachdem die **DLLs** injiziert wurden.

![Error 16](screenshots/error_16.png)

- **Angezeigte Fehlermeldung**: `"Failed to resume the game process thread: [Fehlermeldung des Betriebssystems]"`.
- **Ursache**: Der Aufruf von `ResumeThread` ist fehlgeschlagen, was bedeutet, dass der **Haupt-Thread** von `gta_sa.exe` nicht aktiviert werden konnte, um die Ausführung des Spiels zu starten. Dies ist ein seltener Fehler, kann aber auftreten, wenn:
  - Das **Handle** des **Threads** des Prozesses ungültig wurde.
  - Das Betriebssystem die Wiederaufnahme aus irgendeinem Grund verhindert hat, möglicherweise aufgrund einer Sicherheitsunterbrechung oder eines inkonsistenten Prozesszustands.
  - Der Prozess wurde möglicherweise extern zwischen der **DLL-Injektion** und dem Versuch, den **Haupt-Thread** fortzusetzen, beendet.
- **Lösung**: Wenn alle vorherigen Schritte erfolgreich waren und nur `ResumeThread` fehlgeschlagen ist, könnte es sich um ein Problem mit dem Betriebssystem, der Installation von **GTA:SA** oder einer sehr strengen **Sicherheitssoftware** handeln. Überprüfen Sie den Zustand von `gta_sa.exe` über den **Task-Manager** unmittelbar vor und nach dem Fehler. Ein Neustart des Computers kann temporäre Systemzustandsprobleme beheben.

> [!TIP] Diagnosetools
> In komplexen Debugging-Szenarien können Tools wie **Process Monitor (Sysinternals Suite)** oder ein Debugger (wie **Visual Studio Debugger**, **WinDbg**, **OllyDbg**) von unschätzbarem Wert sein. Sie können helfen, **API**-Aufrufe zu beobachten, Zugriffsfehler zu überprüfen, den Zustand von **Handles** zu verfolgen und sogar den Prozessspeicher zu inspizieren, um eine detaillierte Sicht darauf zu geben, was unter der Haube passiert.

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