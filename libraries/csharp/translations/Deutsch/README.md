# SA-MP Injector C#

<div align="center">

![C#](https://img.shields.io/badge/C%23-11.0%2B-512BD4?style=for-the-badge&logo=csharp&logoColor=white)
![.NET](https://img.shields.io/badge/.NET-7.0%2B-512BD4?style=for-the-badge&logo=dotnet&logoColor=white)
![Platform](https://img.shields.io/badge/Platform-Windows-blue?style=for-the-badge&logo=windows&logoColor=white)
![Architecture](https://img.shields.io/badge/Architecture-x86%20(32--bit)-lightgrey?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)

**Eine C#-Bibliothek zur programmgesteuerten Injektion von DLLs in SA-MP- und OMP-Prozesse, die eine automatisierte Verbindung zu Servern ermöglicht.**

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

- [SA-MP Injector C#](#sa-mp-injector-c)
  - [Sprachen](#sprachen)
  - [Inhaltsverzeichnis](#inhaltsverzeichnis)
  - [Einführung und Zweck](#einführung-und-zweck)
  - [Designphilosophie](#designphilosophie)
    - [Interoperabilität (P/Invoke)](#interoperabilität-pinvoke)
    - [Ressourcenverwaltung (`SafeHandle`)](#ressourcenverwaltung-safehandle)
    - [Sicherheit und Robustheit](#sicherheit-und-robustheit)
  - [Systemanforderungen](#systemanforderungen)
    - [Entwicklungsumgebung](#entwicklungsumgebung)
    - [Laufzeitumgebung](#laufzeitumgebung)
  - [Installation und grundlegende Verwendung](#installation-und-grundlegende-verwendung)
    - [Hinzufügen zu Ihrem Projekt](#hinzufügen-zu-ihrem-projekt)
    - [Anwendungsbeispiel](#anwendungsbeispiel)
  - [Bibliothekskomponenten](#bibliothekskomponenten)
    - [1. `Constants.cs`](#1-constantscs)
    - [2. `InjectionType.cs`](#2-injectiontypecs)
    - [3. `Injector.cs`](#3-injectorcs)
    - [4. `InjectorCore.cs`](#4-injectorcorecs)
    - [5. `InputValidator.cs`](#5-inputvalidatorcs)
    - [6. `NativeImports.cs`](#6-nativeimportscs)
    - [7. `ProcessHandler.cs`](#7-processhandlercs)
    - [8. `SafeHandles.cs`](#8-safehandlescs)
  - [Detaillierter DLL-Injektionszyklus](#detaillierter-dll-injektionszyklus)
    - [1. Eingabevalidierung](#1-eingabevalidierung)
    - [2. Erstellung des Spielprozesses (Angehalten)](#2-erstellung-des-spielprozesses-angehalten)
    - [3. Injektion von `samp.dll`](#3-injektion-von-sampdll)
    - [4. Injektion von `omp-client.dll` (Optional, abhängig von SA-MP)](#4-injektion-von-omp-clientdll-optional-abhängig-von-sa-mp)
    - [Wiederaufnahme des Hauptthreads des Spiels](#wiederaufnahme-des-hauptthreads-des-spiels)
  - [Fehlerbehandlung und Fehlerfälle](#fehlerbehandlung-und-fehlerfälle)
    - [Fehler bei der Eingabevalidierung](#fehler-bei-der-eingabevalidierung)
      - [Ungültiger Nickname](#ungültiger-nickname)
      - [Ungültiger Port](#ungültiger-port)
      - [Fehlende Spiel-/DLL-Dateien](#fehlende-spiel-dll-dateien)
    - [Fehler bei der Prozesserstellung](#fehler-bei-der-prozesserstellung)
      - [Fehler beim Erstellen des Prozesses](#fehler-beim-erstellen-des-prozesses)
    - [Fehler bei der DLL-Injektion](#fehler-bei-der-dll-injektion)
      - [`kernel32.dll`-Handle nicht verfügbar](#kernel32dll-handle-nicht-verfügbar)
      - [Funktion `LoadLibraryA` nicht verfügbar](#funktion-loadlibrarya-nicht-verfügbar)
      - [Fehler bei der Zuweisung von Remotespeicher](#fehler-bei-der-zuweisung-von-remotespeicher)
      - [Fehler beim Schreiben in den Prozessspeicher](#fehler-beim-schreiben-in-den-prozessspeicher)
      - [Fehler beim Erstellen des Remote-Threads](#fehler-beim-erstellen-des-remote-threads)
      - [Timeout oder Fehler beim Warten auf die Injektion](#timeout-oder-fehler-beim-warten-auf-die-injektion)
      - [DLL-Injektion fehlgeschlagen oder hat einen Fehler zurückgegeben](#dll-injektion-fehlgeschlagen-oder-hat-einen-fehler-zurückgegeben)
    - [Fehler beim Wiederaufnehmen des Spiel-Threads](#fehler-beim-wiederaufnehmen-des-spiel-threads)
  - [Lizenz](#lizenz)
    - [Nutzungsbedingungen](#nutzungsbedingungen)
      - [1. Gewährte Berechtigungen](#1-gewährte-berechtigungen)
      - [2. Verpflichtende Bedingungen](#2-verpflichtende-bedingungen)
      - [3. Urheberrecht](#3-urheberrecht)
      - [4. Gewährleistungsausschluss und Haftungsbeschränkung](#4-gewährleistungsausschluss-und-haftungsbeschränkung)

## Einführung und Zweck

Die **SA-MP Injector C#** Bibliothek ist eine C#-Lösung, die entwickelt wurde, um das Starten und die automatisierte Verbindung von San Andreas Multiplayer (SA-MP) und Open Multiplayer (OMP) Clients mit Servern zu vereinfachen. Sie fungiert als Werkzeug zur Injektion von DLLs (Dynamic Link Library), indem sie die Bibliotheken `samp.dll` oder `omp-client.dll` programmgesteuert in den Prozess des Spiels Grand Theft Auto: San Andreas (`gta_sa.exe`) lädt.

Das Hauptziel dieser Bibliothek ist es, anderen C#-Anwendungen (wie benutzerdefinierten Launchern, Server-Management-Tools oder Dienstprogrammen) zu ermöglichen, das Spiel mit spezifischen Parametern (Nickname, IP, Port und Passwort) für den Benutzer transparent zu starten und den Prozess der Verbindung zu einem SA-MP/OMP-Server zu automatisieren.

## Designphilosophie

Das Design von **SA-MP Injector C#** konzentriert sich auf Robustheit, Sicherheit und eine vereinfachte Benutzeroberfläche, die die Komplexität von Low-Level-Systemoperationen kapselt.

### Interoperabilität (P/Invoke)

Die Kernfunktionalität der DLL-Injektion und der Erstellung angehaltener Prozesse ist eine inhärent systemnahe Betriebssystemoperation. Dafür nutzt die Bibliothek ausgiebig die **P/Invoke (Platform Invoke)**-Funktion von .NET, die den direkten Aufruf nativer Windows-API-Funktionen (hauptsächlich aus `kernel32.dll`) aus dem C#-Code ermöglicht. Dies zeigt sich in der Deklaration von `partial`-Methoden und der Verwendung des `[LibraryImport(KERNEL32, SetLastError = true)]`-Attributs.

### Ressourcenverwaltung (`SafeHandle`)

Operationen mit Betriebssystemressourcen, wie "Handles" für Prozesse und Threads, erfordern eine sorgfältige Verwaltung, um Speicher- oder Ressourcenlecks zu vermeiden. Die Bibliothek verwendet von `SafeHandle` abgeleitete Klassen (`SafeProcessHandle` und `SafeThreadHandle`), um sicherzustellen, dass diese Ressourcen immer korrekt freigegeben werden, auch im Falle von Ausnahmen. Dies folgt dem **RAII (Resource Acquisition Is Initialization)**-Prinzip von C++ und erweitert es auf die .NET-Umgebung.

### Sicherheit und Robustheit

Die Bibliothek enthält mehrere Sicherheitsebenen:
- **Eingabevalidierung:** Alle vom Benutzer bereitgestellten Eingaben werden streng validiert, bevor kritische Operationen gestartet werden, um das Risiko von Laufzeitfehlern oder unerwartetem Verhalten zu minimieren.
- **Fehlerbehandlung:** Die Aufrufe nativer APIs werden von Fehlerprüfungen begleitet (`SetLastError = true` und `Marshal.GetLastWin32Error()`), um detaillierte und verständliche Fehlermeldungen zu liefern.
- **Prozessbeendigung:** Im Falle eines Fehlers während des Injektionsprozesses wird der neu erstellte Spielprozess automatisch beendet, um zu verhindern, dass "Zombie"-Prozesse weiterlaufen.

## Systemanforderungen

### Entwicklungsumgebung

- **.NET SDK 7.0 oder höher:** Die Bibliothek ist für `net7.0-windows` erstellt.
- **C# 11.0 oder höher:** Erforderlich für Funktionen wie `ImplicitUsings`, `Nullable`, `AllowUnsafeBlocks` und `LibraryImport`.
- **Visual Studio 2022 oder eine kompatible Entwicklungsumgebung:** Zum Erstellen und Integrieren der Bibliothek.
- **Kompilierungsplattform:** `x86 (32-Bit)` ist das obligatorische Ziel aufgrund der Architektur von `gta_sa.exe` und den SA-MP/OMP-DLLs.

```xml
<!-- samp-injector-csharp.csproj -->
<Project Sdk="Microsoft.NET.Sdk">
    <PropertyGroup>
        <TargetFrameworks>net7.0-windows</TargetFrameworks>
        <PlatformTarget>x86</PlatformTarget> <!-- KRITISCH: Muss x86 sein -->
        <ImplicitUsings>enable</ImplicitUsings>
        <Nullable>enable</Nullable>
        <UseWindowsForms>true</UseWindowsForms>
        <AllowUnsafeBlocks>true</AllowUnsafeBlocks> <!-- Notwendig für fortgeschrittenes P/Invoke -->
    </PropertyGroup>
</Project>
```

### Laufzeitumgebung

- **Betriebssystem:** Windows (jede moderne Version, die mit .NET 7.0+ kompatibel ist).
- **Grand Theft Auto: San Andreas (GTA: SA):** Die Installation des Spiels ist erforderlich.
- **SA-MP oder OMP Client DLLs:** `samp.dll` oder `omp-client.dll` müssen im Stammverzeichnis des Spiels vorhanden sein, je nach gewünschtem Injektionstyp.

## Installation und grundlegende Verwendung

### Hinzufügen zu Ihrem Projekt

Die einfachste Möglichkeit, diese Bibliothek zu verwenden, besteht darin, das Projekt `Samp_Injector_CSharp` als Referenz zu Ihrem eigenen C#-Projekt hinzuzufügen.

1. Klonen oder laden Sie das Repository der Bibliothek herunter.
2. Klicken Sie in Visual Studio mit der rechten Maustaste auf "Dependencies" (oder "Verweise") in Ihrem Projekt.
3. Wählen Sie "Add Project Reference...".
4. Navigieren Sie zum Verzeichnis der Bibliothek und fügen Sie das Projekt `samp-injector-csharp.csproj` hinzu.

### Anwendungsbeispiel

Um das Spiel zu starten und sich mit einem Server zu verbinden, rufen Sie einfach die statische Methode `Injector.Initialize_Game` auf.

```csharp
using Samp_Injector_CSharp;
using System;
using System.Windows.Forms; // Für MessageBox, wenn es kein WinForms-Projekt ist

namespace Launcher {
    public partial class Main : Form {
        public Main() {
            InitializeComponent();
        }

        private void Connect(object sender, EventArgs e) {
            string inject_type = "SAMP"; // "SAMP" oder "OMP"
            string game_folder = @"C:\Games\GTA San Andreas"; // Pfad zum GTA: SA-Ordner
            string nickname = "Name";
            string ip = "127.0.0.1";
            string port = "7777";
            string password = ""; // Leer lassen, wenn kein Passwort vorhanden ist

            // Beispiel für SA-MP-Injektion
            Injector.Initialize_Game(inject_type, game_folder, nickname, ip, port, password);

            // Wenn OMP, ändere inject_type:
            // inject_type = "OMP";
            // Injector.Initialize_Game(inject_type, game_folder, nickname, ip, port, password);
        }
    }
}
```

## Bibliothekskomponenten

Die Bibliothek ist in mehrere Dateien strukturiert, von denen jede eine klare und gut definierte Verantwortung hat, was die Organisation, Wartbarkeit und Trennung der Verantwortlichkeiten fördert. Im Folgenden eine detaillierte Beschreibung jeder Komponente.

### 1. `Constants.cs`

Diese Datei ist ein zentrales Repository für alle Konstanten und unveränderlichen Werte, die in der gesamten Bibliothek verwendet werden. Ihre Existenz fördert die Wartbarkeit des Codes, die Lesbarkeit und die Konsistenz, indem sichergestellt wird, dass kritische Werte an einem einzigen Ort definiert sind.

Die Organisation der Konstanten nach Kategorien erleichtert das Verständnis ihres Zwecks:

- **Game Related Constants**
   - `MIN_PORT`: Definiert den minimal zulässigen Wert für den Verbindungsport eines Servers (1).
   - `MAX_PORT`: Definiert den maximal zulässigen Wert für den Verbindungsport eines Servers (65535).
   - `MAX_NICKNAME_LENGTH`: Gibt die maximal zulässige Länge für den Nicknamen des Spielers an (23 Zeichen), eine vom SA-MP/OMP-Client selbst auferlegte Grenze.

- **File Names**
   - `SAMP_DLL_NAME`: Der Dateiname der Hauptbibliothek des SA-MP-Clients (`"samp.dll"`).
   - `OMP_DLL_NAME`: Der Dateiname der Bibliothek des Open Multiplayer-Clients (`"omp-client.dll"`), die bei OMP-Injektionen verwendet wird.
   - `GAME_EXE_NAME`: Der Name der ausführbaren Datei des Spiels Grand Theft Auto: San Andreas (`"gta_sa.exe"`).

- **System Libraries and Functions**
   - `KERNEL32_DLL`: Der Name der Windows-Systembibliothek, die wesentliche Funktionen zur Prozess- und Speicherverwaltung enthält (`"kernel32.dll"`).
   - `LOAD_LIBRARY_FUNC`: Der Name der Funktion in `kernel32.dll`, die für das dynamische Laden einer Bibliothek verantwortlich ist (`"LoadLibraryA"`).

- **Command Line Arguments**
   - `CMD_ARGS_PART1`: Anfangsteil der Befehlszeilenargumente für das Spiel (`"-c -n "`).
   - `CMD_ARGS_PART2`: Trennzeichen für die IP-Adresse (`" -h "`).
   - `CMD_ARGS_PART3`: Trennzeichen für den Port (`" -p "`).
   - `CMD_ARGS_PART4_PASSWORD`: Präfix für das Passwort-Argument (`" -z "`), wird nur verwendet, wenn ein Passwort angegeben wird.
   - `CMD_ARGS_BASE_LENGTH`: Die vordefinierte Länge der konstanten Teile der Befehlszeile, ohne die ausführbare Datei und die Benutzerwerte (14 Zeichen).
   - `CMD_ARG_PASSWORD_LENGTH`: Die Länge des Präfixes für das Passwort-Argument (4 Zeichen).

- **Error Message Titles**
   - `ERROR_TITLE_SAMP`: Standardtitel für Fehlerdialogfelder im Zusammenhang mit SA-MP-Fehlern (`"SA-MP Injector Error - SPC"`).
   - `ERROR_TITLE_OMP`: Standardtitel für Fehlerdialogfelder im Zusammenhang mit OMP-Fehlern (`"OMP Injector Error - SPC"`).

- **Process Creation Flags**
   - `CREATE_SUSPENDED`: Flag, das das Betriebssystem anweist, einen Prozess und seinen Hauptthread in einem angehaltenen Zustand zu erstellen (`0x00000004`). Dies ist entscheidend für die Injektion der DLL, bevor das Spiel ausgeführt wird.
   - `PROCESS_CREATION_FLAGS`: Eine Kombination von Prozesserstellungs-Flags, derzeit nur als `CREATE_SUSPENDED` definiert.

- **Timeouts**
   - `DLL_INJECTION_TIMEOUT_MS`: Die maximale Zeit (in Millisekunden), die die Bibliothek auf den Abschluss des Remote-Threads wartet, der für die DLL-Injektion verantwortlich ist (10000ms = 10 Sekunden).

- **Memory Allocation Flags**
   - `MEM_COMMIT`: Flag, das Seiten im virtuellen Speicher reserviert und sie "committet" (physischen Speicher zuweist) (`0x1000`).
   - `MEM_RESERVE`: Flag, das nur einen Bereich des virtuellen Adressraums für eine spätere Verwendung reserviert (`0x2000`).
   - `MEM_RELEASE`: Flag, das eine Region von Seiten decommittet und freigibt (`0x8000`).
   - `MEMORY_ALLOCATION_TYPE`: Eine Kombination aus `MEM_COMMIT` und `MEM_RESERVE`, die verwendet wird, um Speicher für den DLL-Pfad im Remote-Prozess zuzuweisen.
   - `MEMORY_PROTECTION`: Definiert die Speicherschutzberechtigungen (derzeit `0x04`, was `PAGE_READWRITE` in der Windows-API entspricht und Lese- und Schreibzugriff auf den zugewiesenen Speicher ermöglicht).

### 2. `InjectionType.cs`

Diese Datei definiert eine einfache Enumeration, um eine sichere und klare Möglichkeit zu bieten, den Typ der durchzuführenden Injektion anzugeben. Die Verwendung eines `enum` anstelle von Strings (`"samp"`, `"omp"`) verhindert Tippfehler und macht den Code lesbarer und robuster.

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

Diese Datei ist die öffentliche Fassade (Facade) der Bibliothek und dient als einziger Einstiegspunkt für konsumierende Anwendungen. Sie abstrahiert die gesamte interne Komplexität des Injektionsprozesses in einer einzigen statischen Methode.

- **Hauptverantwortung:** Die Methode `Initialize_Game` empfängt alle erforderlichen Parameter als Strings, bestimmt den Injektionstyp und delegiert die Arbeit an den `Injector_Core`. Sie ist auch dafür verantwortlich, das Ergebnis der Operation zu erfassen und Fehlermeldungen über `MessageBox` an den Endbenutzer auszugeben, was die Interaktion mit dem Endbenutzer konsistent macht.

```csharp
// Ausschnitt aus Injector.cs
public static class Injector {
    private static readonly Injector_Core s_core = new();

    public static void Initialize_Game(string inject_type_str, string folder, string nickname, string ip, string port, string password) {
        // ... Logik zur Konvertierung von inject_type_str in Injection_Type ...

        if (!s_core.Try_Initialize_Game(type, folder, nickname, ip, port, password, out string error_message)) {
            string error_title = (type == Injection_Type.OMP) ? Constants.ERROR_TITLE_OMP : Constants.ERROR_TITLE_SAMP;
            MessageBox.Show(error_message, error_title, MessageBoxButtons.OK, MessageBoxIcon.Error);
        }
    }
}
```

### 4. `InjectorCore.cs`

Dies ist das "Gehirn" der Bibliothek, in dem die Abfolge der Injektionsoperationen orchestriert wird. Es verbindet die Eingabevalidierer mit den Prozesshandlern, um den gesamten Arbeitsablauf auszuführen.

- **Hauptverantwortung:** Die Methode `Try_Initialize_Game` definiert die schrittweise Logik: Sie validiert die Eingaben, erstellt den Spielprozess im angehaltenen Zustand, injiziert die erforderlichen DLLs (`samp.dll` und optional `omp-client.dll`) und nimmt, wenn alles erfolgreich ist, den Spiel-Thread wieder auf. Ein entscheidender Aspekt ist der `finally`-Block, der sicherstellt, dass der Spielprozess im Falle eines Fehlers während der Injektionsschritte beendet (`Kill()`) wird, um "Zombie"-Prozesse zu vermeiden.

```csharp
// Ausschnitt aus InjectorCore.cs
internal sealed class Injector_Core {
    public bool Try_Initialize_Game(...) {
        // ... Eingabevalidierung ...

        using Process_Handler.Process_Info process_info = Process_Handler.Create_Game_Process(...);
        
        // ...
        bool success = false;
        try {
            // ... Injektion von samp.dll ...
            // ... Optionale Injektion von omp-client.dll ...
            // ... Wiederaufnahme des Spiel-Threads ...
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

Fungiert als erste Verteidigungslinie der Bibliothek und stellt sicher, dass nur gültige und sichere Daten verarbeitet werden. Die vorherige Validierung verhindert Low-Level-Ausnahmen und ermöglicht es der Bibliothek, klare und umsetzbare Fehlermeldungen zu liefern.

- **Hauptverantwortung:** Die statische Methode `Try_Validate` führt eine Reihe von Prüfungen durch, einschließlich des Formats des Nicknamens, des numerischen Bereichs des Ports und, entscheidend, der Existenz der wesentlichen Dateien (`gta_sa.exe`, `samp.dll`, etc.) im angegebenen Verzeichnis. Wenn eine Prüfung fehlschlägt, gibt sie `false` zurück und füllt einen `out string` mit der Fehlerbeschreibung.

```csharp
// Ausschnitt aus InputValidator.cs
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

Diese Datei ist die Brücke zwischen dem verwalteten C#-Code und den nicht verwalteten nativen Windows-APIs. Sie verwendet die P/Invoke-Interoperabilitätsfunktion, um Signaturen von Funktionen aus `kernel32.dll` zu deklarieren.

- **Hauptverantwortung:** Deklaration von `extern`-Methoden mit den Attributen `[LibraryImport]` oder `[DllImport]`, die Funktionen der Windows-API wie `CreateProcessA`, `VirtualAllocEx` und `CreateRemoteThread` entsprechen. Sie definiert auch die Datenstrukturen (`Startup_Info`, `Process_Information`) mit einem zum nativen Code kompatiblen Speicherlayout. Zur Optimierung werden die Handles für `kernel32.dll` und die Adresse der Funktion `LoadLibraryA` beim Start statisch geladen.

```csharp
// Ausschnitt aus NativeImports.cs
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

Dies ist die Low-Level-Schicht, die die Operationen zur Prozessmanipulation ausführt. Sie verwendet die aus `NativeImports.cs` importierten Funktionen, um direkt mit dem Betriebssystem zu interagieren.

- **Hauptverantwortlichkeiten:**
   1. **`Create_Game_Process`**: Erstellt die Befehlszeile und startet `gta_sa.exe` mit dem `CREATE_SUSPENDED`-Flag.
   2. **`Inject_DLL`**: Implementiert die Technik der DLL-Injektion durch die Erstellung eines Remote-Threads. Dies ist die kritischste Funktion, die die Speicherzuweisung, das Schreiben und die Remote-Ausführung von `LoadLibraryA` orchestriert.
   3. **`Resume_Game_Thread`**: Führt den letzten Schritt des "Auftauens" des Hauptthreads des Spiels durch.

```csharp
// Ausschnitt aus ProcessHandler.cs
internal static bool Inject_DLL(SafeProcessHandle process_handle, string dll_path, out string error_message) {
    // ... Zuweisung und Schreiben in den Remotespeicher ...

    IntPtr remote_thread = Native_Imports.CreateRemoteThread(process_handle, IntPtr.Zero, 0, Native_Imports.load_library_address, remote_memory, 0, IntPtr.Zero);

    if (remote_thread == IntPtr.Zero)
        return (error_message = $"Failed to create a remote thread...") != null && false;
    
    // ... Warten auf Abschluss und Überprüfung des Ergebnisses ...
    return true;
}
```

### 8. `SafeHandles.cs`

Diese Datei implementiert eine empfohlene Praxis der Interoperabilität: die Verwendung von `SafeHandle` zur Verwaltung nicht verwalteter Ressourcen. Dies stellt sicher, dass die Windows-Prozess- und Thread-"Handles" deterministisch und sicher freigegeben werden.

- **Hauptverantwortung:** Die Klassen `SafeProcessHandle` und `SafeThreadHandle` erben von `SafeHandleZeroOrMinusOneIsInvalid`. Sie kapseln einen `IntPtr`, der das native Handle darstellt. Der Hauptvorteil ist die Implementierung der `ReleaseHandle`-Methode, die von der .NET-Laufzeit garantiert aufgerufen wird, wenn das Objekt verworfen wird (z. B. am Ende eines `using`-Blocks), wodurch Ressourcenlecks verhindert werden.

```csharp
// Ausschnitt aus SafeHandles.cs
internal sealed class SafeProcessHandle : SafeHandleZeroOrMinusOneIsInvalid {
    // ... Konstruktoren ...

    protected override bool ReleaseHandle() {
        // Dieser Aufruf wird von .NET garantiert, um das native Handle freizugeben.
        return Native_Imports.CloseHandle(handle);
    }
}
```

## Detaillierter DLL-Injektionszyklus

Der Prozess der DLL-Injektion ist eine Abfolge kritischer Schritte, die präzise ausgeführt werden müssen, um erfolgreich zu sein. Die **SA-MP Injector C#** Bibliothek orchestriert dies wie folgt:

### 1. Eingabevalidierung

Vor jeder Interaktion mit dem System werden alle vom Benutzer bereitgestellten Parameter (Spielordnerpfad, Nickname, IP, Port und Passwort) vom `Input_Validator` überprüft. Dies umfasst:
- Überprüfung, ob der Nickname innerhalb der Längengrenzen liegt und nicht leer ist.
- Sicherstellung, dass der Port eine gültige Zahl ist und im zulässigen Bereich (1-65535) liegt.
- Bestätigung, dass `gta_sa.exe`, `samp.dll` und `omp-client.dll` (wenn `Injection_Type` OMP ist) an den erwarteten Pfaden existieren.

> [!NOTE]
> Dieser präventive Schritt ist entscheidend, um unerwartete API-Fehler zu vermeiden und dem Benutzer klares Feedback zu geben.

### 2. Erstellung des Spielprozesses (Angehalten)

Die Bibliothek verwendet `Native_Imports.CreateProcessA`, um `gta_sa.exe` zu starten. Ein entscheidendes Detail ist jedoch die Verwendung des `Constants.CREATE_SUSPENDED`-Flags.
- **Angehaltene Erstellung:** Dieses Flag veranlasst Windows, den Prozess und seinen Hauptthread zu erstellen, ihn aber in einen angehaltenen Zustand zu versetzen, wodurch verhindert wird, dass der Spielcode ausgeführt wird.
- **Befehlszeile:** Die Befehlszeile wird sorgfältig von `Process_Handler.Build_Full_Command_Args_ANSI` erstellt, um alle Serververbindungsparameter (`-c -n <nickname> -h <ip> -p <port> -z <password>`) einzuschließen.
- **Prozess-/Thread-Handles:** `CreateProcessA` gibt die Handles für den Prozess und den Hauptthread zurück, die zur sicheren Ressourcenverwaltung in `SafeProcessHandle` und `SafeThreadHandle` gekapselt werden.

> [!IMPORTANT]
> Die angehaltene Erstellung ist für die Injektion unerlässlich. Wenn das Spiel vor der Injektion starten würde, könnte es seine eigenen Sicherheitsmechanismen initialisieren oder die `samp.dll`/`omp-client.dll` könnte vor unserer Kontrolle geladen werden, was die Injektion komplexer oder unwirksam machen würde.

### 3. Injektion von `samp.dll`

Mit dem angehaltenen Spielprozess führt die Funktion `Process_Handler.Inject_DLL` die folgenden Schritte aus:
1. **`LoadLibraryA` abrufen:** Die Adresse der Funktion `LoadLibraryA` (aus `kernel32.dll`) im Spielprozess wird abgerufen. Dies ist die Funktion, die Windows zum Laden von DLLs verwendet.
2. **Zuweisung von Remotespeicher:** `Native_Imports.VirtualAllocEx` wird verwendet, um einen Speicherblock im virtuellen Adressraum des `gta_sa.exe`-Prozesses zuzuweisen. Die Größe des Blocks reicht aus, um den vollständigen Pfad der `samp.dll` zu speichern.
3. **Schreiben des DLL-Pfads:** Der vollständige Pfad der `samp.dll`-Datei wird mit `Native_Imports.WriteProcessMemory` in den neu zugewiesenen Speicher im Spielprozess geschrieben.
4. **Erstellung eines Remote-Threads:** `Native_Imports.CreateRemoteThread` wird aufgerufen, um einen neuen Thread im `gta_sa.exe`-Prozess zu erstellen. Dieser Thread wird angewiesen, `LoadLibraryA` mit der Adresse des DLL-Pfad-Strings als einzigem Argument auszuführen.
5. **Warten auf Abschluss:** Die Bibliothek wartet ein Zeitlimit (`Constants.DLL_INJECTION_TIMEOUT_MS`) ab, bis der Remote-Thread seine Ausführung abgeschlossen hat, was anzeigt, dass `LoadLibraryA` versucht hat, die DLL zu laden.
6. **Ergebnis überprüfen:** Der Exit-Code des Remote-Threads wird überprüft. Wenn `LoadLibraryA` erfolgreich war, gibt sie die Basisadresse der geladenen DLL zurück. Ein Nullwert oder ein Fehler beim Abrufen des Exit-Codes zeigt an, dass die Injektion fehlgeschlagen ist.
7. **Bereinigung:** Der zugewiesene Remotespeicher wird freigegeben (`Native_Imports.VirtualFreeEx`) und das Handle des Remote-Threads wird geschlossen (`Native_Imports.CloseHandle`).

### 4. Injektion von `omp-client.dll` (Optional, abhängig von SA-MP)

> [!TIP]
> Die Injektion von `omp-client.dll` erfolgt **immer nach der erfolgreichen Injektion von `samp.dll`**. Der OMP-Client verwendet die Infrastruktur von SA-MP, daher ist `samp.dll` eine Voraussetzung.

Wenn der angegebene `Injection_Type` `OMP` ist, wird Schritt 3 wiederholt, um `omp-client.dll` zu injizieren. Die Logik ist identisch und stellt sicher, dass beide für OMP erforderlichen Bibliotheken geladen werden, bevor das Spiel vollständig startet.

### Wiederaufnahme des Hauptthreads des Spiels

Schließlich, nachdem alle erforderlichen DLLs erfolgreich injiziert wurden, wird die Funktion `Process_Handler.Resume_Game_Thread` aufgerufen. Diese Funktion verwendet `Native_Imports.ResumeThread`, um dem Hauptthread von `gta_sa.exe` die Fortsetzung seiner Ausführung zu ermöglichen. Das Spiel startet nun mit den bereits geladenen SA-MP/OMP-DLLs und den angewendeten Befehlszeilenargumenten für die Serververbindung.

## Fehlerbehandlung und Fehlerfälle

Die Bibliothek wurde entwickelt, um im Fehlerfall klares Feedback zu geben. Die meisten Fehler werden abgefangen und eine beschreibende `error_message` wird zurückgegeben, um dem Benutzer angezeigt zu werden, normalerweise über eine `MessageBox`.

### Fehler bei der Eingabevalidierung

Diese Fehler treten vor jeder Systemoperation auf und werden vom `Input_Validator` erkannt.

#### Ungültiger Nickname

- **Fehlermeldung (Beispiel 1):** `"Nickname cannot be empty. Please provide a valid nickname."`
- **Fehlermeldung (Beispiel 2):** `"Nickname length exceeds the maximum allowed of 23 characters. Please use a shorter nickname."`
- **Warum:** Das Nickname-Feld ist leer oder überschreitet die maximale Grenze von 23 Zeichen.
- **Lösung:** Der Benutzer muss einen gültigen Nicknamen angeben, der die Zeichenbegrenzung einhält.

#### Ungültiger Port

- **Fehlermeldung (Beispiel 1):** `"Invalid port format. The port must be a numeric value. Please provide a valid integer for the port."`
- **Fehlermeldung (Beispiel 2):** `"The specified port number (70000) is outside the valid range of 1 to 65535. Please provide a valid port."`
- **Warum:** Der angegebene Port ist keine ganze Zahl oder liegt außerhalb des gültigen Bereichs von 1 bis 65535.
- **Lösung:** Der Benutzer muss eine gültige Portnummer innerhalb des angegebenen Bereichs eingeben.

#### Fehlende Spiel-/DLL-Dateien

- **Fehlermeldung (Beispiel 1):** `"Game executable not found. Please ensure 'gta_sa.exe' exists at the specified path: C:\Program Files (x86)\Rockstar Games\GTA San Andreas\gta_sa.exe"`
- **Fehlermeldung (Beispiel 2):** `"SA-MP library not found. Please ensure 'samp.dll' exists at the specified path: C:\Program Files (x86)\Rockstar Games\GTA San Andreas\samp.dll"`
- **Fehlermeldung (Beispiel 3, OMP):** `"OMP library not found. Please ensure 'omp-client.dll' exists at the specified path for OMP injection: C:\Program Files (x86)\Rockstar Games\GTA San Andreas\omp-client.dll"`
- **Warum:** Die ausführbare Datei des Spiels (`gta_sa.exe`), die SA-MP-DLL (`samp.dll`) oder die OMP-DLL (`omp-client.dll`) wurde im angegebenen Spielordner nicht gefunden.
- **Lösung:** Der Benutzer sollte den Pfad zum Spielordner überprüfen und sicherstellen, dass alle erforderlichen Dateien vorhanden sind.

### Fehler bei der Prozesserstellung

Diese Fehler treten auf, wenn die Bibliothek versucht, `gta_sa.exe` zu starten.

#### Fehler beim Erstellen des Prozesses

- **Fehlermeldung (Beispiel):** `"Failed to create game process. Ensure 'gta_sa.exe' is not running and you have sufficient permissions to execute the file. System Error: Access is denied."`
- **Warum:**
   - **Datei in Verwendung:** `gta_sa.exe` könnte bereits ausgeführt werden, was die Erstellung einer neuen Instanz verhindert, oder das Betriebssystem hat eine Sperre für die Datei.
   - **Berechtigungen:** Der Benutzer, der die Anwendung ausführt, hat möglicherweise nicht die erforderlichen Berechtigungen, um einen neuen Prozess zu starten oder auf die ausführbare Datei des Spiels zuzugreifen.
   - **Ungültiger/Beschädigter Pfad:** Obwohl die grundlegende Validierung die Existenz prüft, kann es Probleme mit Lese-/Ausführungsberechtigungen geben oder die ausführbare Datei ist beschädigt.
- **Lösung:** Stellen Sie sicher, dass keine andere Instanz von `gta_sa.exe` ausgeführt wird. Führen Sie die Anwendung nach Möglichkeit als Administrator aus. Überprüfen Sie die Integrität der Datei `gta_sa.exe`.

### Fehler bei der DLL-Injektion

Dies sind die kritischsten Fehler und treten während des Versuchs auf, `samp.dll` oder `omp-client.dll` in den Spielprozess zu injizieren.

#### `kernel32.dll`-Handle nicht verfügbar

- **Fehlermeldung:** `"Failed to obtain a handle to kernel32.dll. This is an essential system library and this error indicates a severe system issue."`
- **Warum:** Die Bibliothek `kernel32.dll`, die für Systemoperationen in Windows unerlässlich ist, konnte nicht geladen werden oder ihr Handle konnte nicht abgerufen werden. Dies ist äußerst selten und deutet auf ein schwerwiegendes Problem mit dem Betriebssystem hin.
- **Lösung:** Ein Neustart des Systems könnte das Problem lösen. Andernfalls deutet es auf ein tiefer liegendes Problem mit der Windows-Installation hin.

#### Funktion `LoadLibraryA` nicht verfügbar

- **Fehlermeldung:** `"Failed to find the address of the LoadLibraryA function in kernel32.dll. This is critical for injecting the DLL."`
- **Warum:** Die Funktion `LoadLibraryA`, die für das dynamische Laden von DLLs unerlässlich ist, konnte in `kernel32.dll` nicht gefunden werden. Wie der vorherige Fehler ist dies ein seltenes Low-Level-Problem.
- **Lösung:** Ähnlich wie bei der Nichtverfügbarkeit des `kernel32.dll`-Handles.

#### Fehler bei der Zuweisung von Remotespeicher

- **Fehlermeldung:** `"Failed to allocate memory in the target process. This might be due to insufficient permissions or process protection mechanisms."`
- **Warum:** Die Bibliothek konnte keinen Speicherblock im Adressraum von `gta_sa.exe` zuweisen.
   - **Berechtigungen:** Die Anwendung hat möglicherweise nicht die erforderlichen Berechtigungen, um den Speicherplatz eines anderen Prozesses zu ändern.
   - **Prozessschutz:** Der `gta_sa.exe`-Prozess oder das Betriebssystem wendet möglicherweise Schutzmechanismen gegen Code-Injektion an.
   - **Adressraum:** In extremen Fällen könnte der Adressraum des Prozesses fragmentiert sein oder nicht genügend zusammenhängenden Speicher haben, obwohl dies für die Größe eines DLL-Pfad-Strings unwahrscheinlich ist.
- **Lösung:** Führen Sie die Anwendung als Administrator aus. Überprüfen Sie, ob Sicherheitssoftware (Antivirus, Anti-Cheat) die Speicherzuweisung in anderen Prozessen blockiert.

#### Fehler beim Schreiben in den Prozessspeicher

- **Fehlermeldung:** `"Failed to write DLL path to the target process memory. Verify process permissions and ensure the DLL path is accessible."`
- **Warum:** Die Bibliothek hat Speicher im Spielprozess zugewiesen, konnte aber den DLL-Pfad nicht an diesen Ort schreiben.
   - **Berechtigungen:** Ähnlich wie beim Fehler bei der Speicherzuweisung kann es sich um ein Problem mit der Schreibberechtigung handeln.
   - **Schutz:** Speicherschutz des Betriebssystems oder Anti-Cheat könnte das Schreiben verhindern.
- **Lösung:** Überprüfen Sie die Berechtigungen und die Sicherheitssoftware.

#### Fehler beim Erstellen des Remote-Threads

- **Fehlermeldung (Beispiel):** `"Failed to create a remote thread in the target process to execute the DLL injection. This could be due to security restrictions or process state. System Error: Not enough memory resources are available to process this command."`
- **Warum:** Die `CreateRemoteThread`-API konnte keinen neuen Thread im `gta_sa.exe`-Prozess erstellen, um `LoadLibraryA` aufzurufen.
   - **Prozessschutz/Anti-Cheat:** Viele Anti-Cheat-Systeme und Betriebssystemschutzmechanismen überwachen und blockieren die Erstellung von Remote-Threads, da dies eine gängige Injektionstechnik ist.
   - **Prozesszustand:** Der Spielprozess befindet sich möglicherweise in einem inkonsistenten Zustand, der die Erstellung von Threads verhindert.
- **Lösung:** Deaktivieren Sie vorübergehend jegliche Anti-Cheat- oder Antivirensoftware. Versuchen Sie, die Anwendung als Administrator auszuführen.

#### Timeout oder Fehler beim Warten auf die Injektion

- **Fehlermeldung (Beispiel):** `"Timeout or error waiting for DLL injection to complete. System Error: The wait operation timed out."`
- **Warum:** Der Remote-Thread (der `LoadLibraryA` aufruft) hat seine Ausführung nicht innerhalb des angegebenen Zeitlimits (10 Sekunden) beendet.
   - **Einfrieren:** `LoadLibraryA` könnte hängen geblieben sein oder übermäßig lange gedauert haben.
   - **Blockierung:** Ein Sicherheitsmechanismus könnte die Ausführung von `LoadLibraryA` abgefangen und auf unbestimmte Zeit blockiert haben.
- **Lösung:** Dies kann darauf hindeuten, dass die DLL zu lange zum Laden braucht oder etwas sie daran hindert. Die Überprüfung von Systemprotokollen oder SA-MP/OMP-eigenen Protokollen (falls vorhanden) kann helfen.

#### DLL-Injektion fehlgeschlagen oder hat einen Fehler zurückgegeben

- **Fehlermeldung:** `"DLL injection failed or returned an error. The LoadLibrary call may have failed in the target process."`
- **Warum:** Der Remote-Thread wurde abgeschlossen, aber der Exit-Code von `LoadLibraryA` deutete auf einen Fehler hin (normalerweise `0` oder `NULL`).
   - **Nicht existierende/Beschädigte DLL:** Trotz der anfänglichen Validierung könnte die DLL zwischen der Validierung und der Injektion verschoben oder beschädigt worden sein.
   - **Fehlende DLL-Abhängigkeiten:** `samp.dll` oder `omp-client.dll` können von anderen DLLs abhängen, die nicht im Spielverzeichnis oder im System-PATH vorhanden sind.
   - **Interner DLL-Fehler:** Die DLL selbst kann einen internen Fehler haben, der das korrekte Laden verhindert.
- **Lösung:** Überprüfen Sie die Integrität von `samp.dll`/`omp-client.dll`. Stellen Sie sicher, dass alle DLL-Abhängigkeiten vorhanden sind.

### Fehler beim Wiederaufnehmen des Spiel-Threads

Dies ist der letzte mögliche Fehler im Injektionszyklus.

- **Fehlermeldung (Beispiel):** `"Failed to resume the game process thread: Invalid handle."`
- **Warum:** Die `ResumeThread`-API konnte den Hauptthread von `gta_sa.exe` nicht neu starten.
   - **Ungültiges Handle:** Das Thread-Handle könnte aus irgendeinem Grund ungültig geworden sein.
   - **Berechtigungsproblem:** Die Anwendung hat möglicherweise nicht die Berechtigung, den Zustand des Threads zu ändern.
- **Lösung:** Versuchen Sie, die Anwendung als Administrator auszuführen. Wenn das Problem weiterhin besteht, kann dies auf ein tiefer liegendes Stabilitätsproblem des Systems oder des Spielprozesses hindeuten.

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