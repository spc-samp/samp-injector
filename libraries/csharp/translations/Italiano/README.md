# SA-MP Injector C#

<div align="center">

![C#](https://img.shields.io/badge/C%23-11.0%2B-512BD4?style=for-the-badge&logo=csharp&logoColor=white)
![.NET](https://img.shields.io/badge/.NET-7.0%2B-512BD4?style=for-the-badge&logo=dotnet&logoColor=white)
![Platform](https://img.shields.io/badge/Platform-Windows-blue?style=for-the-badge&logo=windows&logoColor=white)
![Architecture](https://img.shields.io/badge/Architecture-x86%20(32--bit)-lightgrey?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)

**Una libreria C# per l'iniezione programmatica di DLL in processi SA-MP e OMP, permettendo la connessione automatizzata a server.**

</div>

## Lingue

- Português: [README](../../)
- Deutsch: [README](../Deutsch/README.md)
- English: [README](../English/README.md)
- Español: [README](../Espanol/README.md)
- Français: [README](../Francais/README.md)
- Polski: [README](../Polski/README.md)
- Русский: [README](../Русский/README.md)
- Svenska: [README](../Svenska/README.md)
- Türkçe: [README](../Turkce/README.md)

## Indice

- [SA-MP Injector C#](#sa-mp-injector-c)
  - [Lingue](#lingue)
  - [Indice](#indice)
  - [Introduzione e Scopo](#introduzione-e-scopo)
  - [Filosofia di Progettazione](#filosofia-di-progettazione)
    - [Interoperabilità (P/Invoke)](#interoperabilità-pinvoke)
    - [Gestione delle Risorse (`SafeHandle`)](#gestione-delle-risorse-safehandle)
    - [Sicurezza e Robustezza](#sicurezza-e-robustezza)
  - [Requisiti di Sistema](#requisiti-di-sistema)
    - [Ambiente di Sviluppo](#ambiente-di-sviluppo)
    - [Ambiente di Esecuzione](#ambiente-di-esecuzione)
  - [Installazione e Uso di Base](#installazione-e-uso-di-base)
    - [Aggiungere al Tuo Progetto](#aggiungere-al-tuo-progetto)
    - [Esempio di Utilizzo](#esempio-di-utilizzo)
  - [Componenti della Libreria](#componenti-della-libreria)
    - [1. `Constants.cs`](#1-constantscs)
    - [2. `InjectionType.cs`](#2-injectiontypecs)
    - [3. `Injector.cs`](#3-injectorcs)
    - [4. `InjectorCore.cs`](#4-injectorcorecs)
    - [5. `InputValidator.cs`](#5-inputvalidatorcs)
    - [6. `NativeImports.cs`](#6-nativeimportscs)
    - [7. `ProcessHandler.cs`](#7-processhandlercs)
    - [8. `SafeHandles.cs`](#8-safehandlescs)
  - [Ciclo Dettagliato di Iniezione della DLL](#ciclo-dettagliato-di-iniezione-della-dll)
    - [1. Validazione dell'Input](#1-validazione-dellinput)
    - [2. Creazione del Processo del Gioco (Sospeso)](#2-creazione-del-processo-del-gioco-sospeso)
    - [3. Iniezione di `samp.dll`](#3-iniezione-di-sampdll)
    - [4. Iniezione di `omp-client.dll` (Opzionale, Dipendente da SA-MP)](#4-iniezione-di-omp-clientdll-opzionale-dipendente-da-sa-mp)
    - [Riprendere il Thread Principale del Gioco](#riprendere-il-thread-principale-del-gioco)
  - [Gestione degli Errori e Casi di Fallimento](#gestione-degli-errori-e-casi-di-fallimento)
    - [Errori di Validazione dell'Input](#errori-di-validazione-dellinput)
      - [Nickname non valido](#nickname-non-valido)
      - [Porta non valida](#porta-non-valida)
      - [File di Gioco/DLL Mancanti](#file-di-giocodll-mancanti)
    - [Errori nella Creazione del Processo](#errori-nella-creazione-del-processo)
      - [Fallimento nella Creazione del Processo](#fallimento-nella-creazione-del-processo)
    - [Errori nell'Iniezione della DLL](#errori-nelliniezione-della-dll)
      - [Handle `kernel32.dll` non disponibile](#handle-kernel32dll-non-disponibile)
      - [Funzione `LoadLibraryA` non disponibile](#funzione-loadlibrarya-non-disponibile)
      - [Fallimento nell'Allocazione di Memoria Remota](#fallimento-nellallocazione-di-memoria-remota)
      - [Fallimento nella Scrittura nella Memoria del Processo](#fallimento-nella-scrittura-nella-memoria-del-processo)
      - [Fallimento nella Creazione del Thread Remoto](#fallimento-nella-creazione-del-thread-remoto)
      - [Timeout o Errore nell'Attesa dell'Iniezione](#timeout-o-errore-nellattesa-delliniezione)
      - [L'Iniezione della DLL è fallita o ha restituito un errore](#liniezione-della-dll-è-fallita-o-ha-restituito-un-errore)
    - [Errore nel Riprendere il Thread del Gioco](#errore-nel-riprendere-il-thread-del-gioco)
  - [Licenza](#licenza)
    - [Termini e Condizioni d'Uso](#termini-e-condizioni-duso)
      - [1. Permessi Concessi](#1-permessi-concessi)
      - [2. Condizioni Obbligatorie](#2-condizioni-obbligatorie)
      - [3. Diritti d'Autore](#3-diritti-dautore)
      - [4. Esclusione di Garanzia e Limitazione di Responsabilità](#4-esclusione-di-garanzia-e-limitazione-di-responsabilità)

## Introduzione e Scopo

La libreria **SA-MP Injector C#** è una soluzione in C# progettata per semplificare l'avvio e la connessione automatizzata dei client San Andreas Multiplayer (SA-MP) e Open Multiplayer (OMP) ai server. Funziona come uno strumento di iniezione di DLL (Dynamic Link Library), caricando programmaticamente le librerie `samp.dll` o `omp-client.dll` nel processo del gioco Grand Theft Auto: San Andreas (`gta_sa.exe`).

L'obiettivo principale di questa libreria è permettere ad altre applicazioni C# (come launcher personalizzati, strumenti di gestione del server o utility) di avviare il gioco con parametri specifici (nickname, IP, porta e password) in modo trasparente per l'utente, automatizzando il processo di connessione a un server SA-MP/OMP.

## Filosofia di Progettazione

Il design di **SA-MP Injector C#** si concentra su robustezza, sicurezza e un'interfaccia di utilizzo semplificata, incapsulando le complessità delle operazioni di basso livello del sistema.

### Interoperabilità (P/Invoke)

La funzionalità centrale dell'iniezione di DLL e della creazione di processi sospesi è intrinsecamente un'operazione di sistema operativo di basso livello. Per questo, la libreria fa ampio uso della funzionalità **P/Invoke (Platform Invoke)** di .NET, permettendo la chiamata di funzioni native dell'API di Windows (principalmente da `kernel32.dll`) direttamente dal codice C#. Questo è evidente nella dichiarazione di metodi `partial` e nell'utilizzo dell'attributo `[LibraryImport(KERNEL32, SetLastError = true)]`.

### Gestione delle Risorse (`SafeHandle`)

Le operazioni con risorse del sistema operativo, come gli "handle" di processi e thread, richiedono una gestione attenta per evitare perdite di memoria o risorse. La libreria impiega classi derivate da `SafeHandle` (`SafeProcessHandle` e `SafeThreadHandle`) per garantire che queste risorse siano sempre rilasciate correttamente, anche in caso di eccezioni. Ciò aderisce al principio di **RAII (Resource Acquisition Is Initialization)** di C++ e lo estende all'ambiente .NET.

### Sicurezza e Robustezza

La libreria incorpora vari livelli di sicurezza:
- **Validazione dell'Input:** Tutti gli input forniti dall'utente sono rigorosamente validati prima che qualsiasi operazione critica venga avviata, minimizzando il rischio di errori di runtime o comportamenti imprevisti.
- **Gestione degli Errori:** Le chiamate API native sono accompagnate da controlli di errore (`SetLastError = true` e `Marshal.GetLastWin32Error()`) per fornire messaggi di errore dettagliati e comprensibili.
- **Terminazione del Processo:** In caso di fallimento durante il processo di iniezione, il processo del gioco appena creato viene automaticamente terminato per evitare che processi "zombie" rimangano in esecuzione.

## Requisiti di Sistema

### Ambiente di Sviluppo

- **.NET SDK 7.0 o superiore:** La libreria è costruita per `net7.0-windows`.
- **C# 11.0 o superiore:** Necessario per funzionalità come `ImplicitUsings`, `Nullable`, `AllowUnsafeBlocks` e `LibraryImport`.
- **Visual Studio 2022 o ambiente di sviluppo compatibile:** Per costruire e integrare la libreria.
- **Piattaforma di Compilazione:** `x86 (32-bit)` è il target obbligatorio a causa dell'architettura di `gta_sa.exe` e delle DLL SA-MP/OMP.

```xml
<!-- samp-injector-csharp.csproj -->
<Project Sdk="Microsoft.NET.Sdk">
    <PropertyGroup>
        <TargetFrameworks>net7.0-windows</TargetFrameworks>
        <PlatformTarget>x86</PlatformTarget> <!-- CRITICO: Deve essere x86 -->
        <ImplicitUsings>enable</ImplicitUsings>
        <Nullable>enable</Nullable>
        <UseWindowsForms>true</UseWindowsForms>
        <AllowUnsafeBlocks>true</AllowUnsafeBlocks> <!-- Necessario per P/Invoke avanzato -->
    </PropertyGroup>
</Project>
```

### Ambiente di Esecuzione

- **Sistema Operativo:** Windows (qualsiasi versione moderna compatibile con .NET 7.0+).
- **Grand Theft Auto: San Andreas (GTA: SA):** È necessaria l'installazione del gioco.
- **SA-MP o OMP Client DLLs:** `samp.dll` o `omp-client.dll` devono essere presenti nella directory principale del gioco, a seconda del tipo di iniezione desiderato.

## Installazione e Uso di Base

### Aggiungere al Tuo Progetto

Il modo più semplice per utilizzare questa libreria è aggiungere il progetto `Samp_Injector_CSharp` come riferimento nel tuo progetto C#.

1. Clona o scarica il repository della libreria.
2. In Visual Studio, fai clic con il pulsante destro del mouse su "Dependencies" (o "Riferimenti") nel tuo progetto.
3. Seleziona "Add Project Reference...".
4. Naviga fino alla directory della libreria e aggiungi il progetto `samp-injector-csharp.csproj`.

### Esempio di Utilizzo

Per avviare il gioco e connettersi a un server, è sufficiente chiamare il metodo statico `Injector.Initialize_Game`.

```csharp
using Samp_Injector_CSharp;
using System;
using System.Windows.Forms; // Per MessageBox, se non è un progetto WinForms

namespace Launcher {
    public partial class Main : Form {
        public Main() {
            InitializeComponent();
        }

        private void Connect(object sender, EventArgs e) {
            string inject_type = "SAMP"; // "SAMP" o "OMP"
            string game_folder = @"C:\Games\GTA San Andreas"; // Percorso della cartella di GTA: SA
            string nickname = "Nome";
            string ip = "127.0.0.1";
            string port = "7777";
            string password = ""; // Lasciare vuoto se non c'è password

            // Esempio di iniezione SA-MP
            Injector.Initialize_Game(inject_type, game_folder, nickname, ip, port, password);

            // Se è OMP, cambia inject_type:
            // inject_type = "OMP";
            // Injector.Initialize_Game(inject_type, game_folder, nickname, ip, port, password);
        }
    }
}
```

## Componenti della Libreria

La libreria è strutturata in vari file, ognuno con una responsabilità chiara e ben definita, il che promuove l'organizzazione, la manutenibilità e la separazione delle responsabilità. Di seguito, una descrizione dettagliata di ciascun componente.

### 1. `Constants.cs`

Questo file è un repository centralizzato di tutte le costanti e i valori immutabili che vengono utilizzati in tutta la libreria. La sua esistenza promuove la manutenzione del codice, la leggibilità e la coerenza, garantendo che i valori critici siano definiti in un unico luogo.

L'organizzazione delle costanti per categoria facilita la comprensione del loro scopo:

- **Game Related Constants**
   - `MIN_PORT`: Definisce il valore minimo consentito per la porta di connessione di un server (1).
   - `MAX_PORT`: Definisce il valore massimo consentito per la porta di connessione di un server (65535).
   - `MAX_NICKNAME_LENGTH`: Specifica la lunghezza massima consentita per il nickname del giocatore (23 caratteri), un limite imposto dal client SA-MP/OMP stesso.

- **File Names**
   - `SAMP_DLL_NAME`: Il nome del file della libreria principale del client SA-MP (`"samp.dll"`).
   - `OMP_DLL_NAME`: Il nome del file della libreria del client Open Multiplayer (`"omp-client.dll"`), utilizzata in iniezioni di tipo OMP.
   - `GAME_EXE_NAME`: Il nome del file eseguibile del gioco Grand Theft Auto: San Andreas (`"gta_sa.exe"`).

- **System Libraries and Functions**
   - `KERNEL32_DLL`: Il nome della libreria di sistema di Windows che contiene funzioni essenziali per la manipolazione di processi e memoria (`"kernel32.dll"`).
   - `LOAD_LIBRARY_FUNC`: Il nome della funzione all'interno di `kernel32.dll` responsabile del caricamento dinamico di una libreria (`"LoadLibraryA"`).

- **Command Line Arguments**
   - `CMD_ARGS_PART1`: Parte iniziale degli argomenti della riga di comando per il gioco (`"-c -n "`).
   - `CMD_ARGS_PART2`: Separatore per l'indirizzo IP (`" -h "`).
   - `CMD_ARGS_PART3`: Separatore per la porta (`" -p "`).
   - `CMD_ARGS_PART4_PASSWORD`: Prefisso per l'argomento della password (`" -z "`), usato solo se viene fornita una password.
   - `CMD_ARGS_BASE_LENGTH`: La lunghezza predefinita delle parti costanti della riga di comando, escludendo l'eseguibile e i valori dell'utente (14 caratteri).
   - `CMD_ARG_PASSWORD_LENGTH`: La lunghezza del prefisso dell'argomento della password (4 caratteri).

- **Error Message Titles**
   - `ERROR_TITLE_SAMP`: Titolo predefinito per le finestre di dialogo di errore relative a fallimenti di SA-MP (`"SA-MP Injector Error - SPC"`).
   - `ERROR_TITLE_OMP`: Titolo predefinito per le finestre di dialogo di errore relative a fallimenti di OMP (`"OMP Injector Error - SPC"`).

- **Process Creation Flags**
   - `CREATE_SUSPENDED`: Flag che istruisce il sistema operativo a creare un processo e il suo thread principale in uno stato sospeso (`0x00000004`). Questo è fondamentale per l'iniezione della DLL prima che il gioco inizi a essere eseguito.
   - `PROCESS_CREATION_FLAGS`: Una combinazione di flag di creazione del processo, attualmente definita solo come `CREATE_SUSPENDED`.

- **Timeouts**
   - `DLL_INJECTION_TIMEOUT_MS`: Il tempo massimo (in millisecondi) che la libreria attenderà per il completamento del thread remoto responsabile dell'iniezione della DLL (10000ms = 10 secondi).

- **Memory Allocation Flags**
   - `MEM_COMMIT`: Flag che riserva pagine nella memoria virtuale e le "committa" (alloca memoria fisica) (`0x1000`).
   - `MEM_RESERVE`: Flag che riserva solo un intervallo di spazio di indirizzi virtuale per uso futuro (`0x2000`).
   - `MEM_RELEASE`: Flag che decommitta e rilascia una regione di pagine (`0x8000`).
   - `MEMORY_ALLOCATION_TYPE`: Una combinazione di `MEM_COMMIT` e `MEM_RESERVE`, utilizzata per allocare memoria per il percorso della DLL nel processo remoto.
   - `MEMORY_PROTECTION`: Definisce i permessi di protezione della memoria (attualmente `0x04`, che corrisponde a `PAGE_READWRITE` nell'API di Windows, permettendo lettura e scrittura nella memoria allocata).

### 2. `InjectionType.cs`

Questo file definisce un semplice enumeratore per fornire un modo sicuro e chiaro di specificare il tipo di iniezione da eseguire. L'uso di un `enum` invece di stringhe (`"samp"`, `"omp"`) previene errori di battitura e rende il codice più leggibile e robusto.

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

Questo file è la facciata (Facade) pubblica della libreria, che funge da unico punto di ingresso per le applicazioni client. Astrae tutta la complessità interna del processo di iniezione in un unico metodo statico.

- **Responsabilità Principale:** Il metodo `Initialize_Game` riceve tutti i parametri necessari come stringhe, determina il tipo di iniezione e delega il lavoro a `Injector_Core`. È anche responsabile di catturare il risultato dell'operazione e presentare messaggi di errore all'utente finale tramite `MessageBox`, rendendo l'interazione con l'utente finale coerente.

```csharp
// Estratto da Injector.cs
public static class Injector {
    private static readonly Injector_Core s_core = new();

    public static void Initialize_Game(string inject_type_str, string folder, string nickname, string ip, string port, string password) {
        // ... Logica per convertire inject_type_str in Injection_Type ...

        if (!s_core.Try_Initialize_Game(type, folder, nickname, ip, port, password, out string error_message)) {
            string error_title = (type == Injection_Type.OMP) ? Constants.ERROR_TITLE_OMP : Constants.ERROR_TITLE_SAMP;
            MessageBox.Show(error_message, error_title, MessageBoxButtons.OK, MessageBoxIcon.Error);
        }
    }
}
```

### 4. `InjectorCore.cs`

Questo è il "cervello" della libreria, dove viene orchestrata la sequenza di operazioni di iniezione. Collega i validatori di input con i gestori di processo per eseguire il flusso di lavoro completo.

- **Responsabilità Principale:** Il metodo `Try_Initialize_Game` definisce la logica passo-passo: valida gli input, crea il processo del gioco in stato sospeso, inietta le DLL necessarie (`samp.dll` e, opzionalmente, `omp-client.dll`) e, se tutto va a buon fine, riprende il thread del gioco. Un aspetto cruciale è il blocco `finally`, che garantisce che il processo del gioco venga terminato (`Kill()`) in caso di qualsiasi fallimento durante le fasi di iniezione, evitando processi "zombie".

```csharp
// Estratto da InjectorCore.cs
internal sealed class Injector_Core {
    public bool Try_Initialize_Game(...) {
        // ... Validazione dell'input ...

        using Process_Handler.Process_Info process_info = Process_Handler.Create_Game_Process(...);
        
        // ...
        bool success = false;
        try {
            // ... Iniezione di samp.dll ...
            // ... Iniezione opzionale di omp-client.dll ...
            // ... Ripresa del thread del gioco ...
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

Agisce come la prima linea di difesa della libreria, garantendo che solo dati validi e sicuri vengano elaborati. La validazione preventiva previene eccezioni di basso livello e consente alla libreria di fornire messaggi di errore chiari e attuabili.

- **Responsabilità Principale:** Il metodo statico `Try_Validate` esegue una serie di controlli, tra cui il formato del nickname, l'intervallo numerico della porta e, soprattutto, l'esistenza dei file essenziali (`gta_sa.exe`, `samp.dll`, ecc.) nella directory specificata. Se un controllo fallisce, restituisce `false` e popola una `out string` con la descrizione dell'errore.

```csharp
// Estratto da InputValidator.cs
internal static class Input_Validator {
    public static bool Try_Validate(...) {
        if (nickname.Length > Constants.MAX_NICKNAME_LENGTH)
            return (error_message = $"La lunghezza del nickname supera il massimo...") != null && false;

        string game_exe_path = Path.Combine(folder_path, Constants.GAME_EXE_NAME);
        if (!File.Exists(game_exe_path))
            return (error_message = $"Eseguibile del gioco non trovato...") != null && false;
        
        // ...
        return true;
    }
}
```

### 6. `NativeImports.cs`

Questo file è il ponte tra il codice gestito di C# e le API native non gestite di Windows. Utilizza la funzionalità di interoperabilità P/Invoke per dichiarare le firme delle funzioni di `kernel32.dll`.

- **Responsabilità Principale:** Dichiarare metodi `extern` con gli attributi `[LibraryImport]` o `[DllImport]` che corrispondono a funzioni dell'API di Windows, come `CreateProcessA`, `VirtualAllocEx` e `CreateRemoteThread`. Definisce anche le strutture dati (`Startup_Info`, `Process_Information`) con un layout di memoria compatibile con il codice nativo. Per l'ottimizzazione, gli handle per `kernel32.dll` e l'indirizzo della funzione `LoadLibraryA` vengono caricati staticamente all'inizializzazione.

```csharp
// Estratto da NativeImports.cs
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

È lo strato di basso livello che esegue le operazioni di manipolazione dei processi. Utilizza le funzioni importate da `NativeImports.cs` per interagire direttamente con il sistema operativo.

- **Responsabilità Principali:**
   1. **`Create_Game_Process`**: Costruisce la riga di comando e avvia `gta_sa.exe` con il flag `CREATE_SUSPENDED`.
   2. **`Inject_DLL`**: Implementa la tecnica di iniezione di DLL attraverso la creazione di un thread remoto. Questa è la funzione più critica, che orchestra l'allocazione di memoria, la scrittura e l'esecuzione remota di `LoadLibraryA`.
   3. **`Resume_Game_Thread`**: Esegue il passo finale di "scongelare" il thread principale del gioco.

```csharp
// Estratto da ProcessHandler.cs
internal static bool Inject_DLL(SafeProcessHandle process_handle, string dll_path, out string error_message) {
    // ... Allocazione e scrittura nella memoria remota ...

    IntPtr remote_thread = Native_Imports.CreateRemoteThread(process_handle, IntPtr.Zero, 0, Native_Imports.load_library_address, remote_memory, 0, IntPtr.Zero);

    if (remote_thread == IntPtr.Zero)
        return (error_message = $"Impossibile creare un thread remoto...") != null && false;
    
    // ... Attesa del completamento e verifica del risultato ...
    return true;
}
```

### 8. `SafeHandles.cs`

Questo file implementa una pratica raccomandata di interoperabilità: l'uso di `SafeHandle` per gestire risorse non gestite. Ciò garantisce che gli "handle" di processo e thread di Windows vengano rilasciati in modo deterministico e sicuro.

- **Responsabilità Principale:** Le classi `SafeProcessHandle` e `SafeThreadHandle` ereditano da `SafeHandleZeroOrMinusOneIsInvalid`. Incapsulano un `IntPtr` che rappresenta l'handle nativo. Il vantaggio principale è l'implementazione del metodo `ReleaseHandle`, che è garantito dal runtime di .NET di essere chiamato quando l'oggetto viene scartato (ad esempio, alla fine di un blocco `using`), prevenendo perdite di risorse.

```csharp
// Estratto da SafeHandles.cs
internal sealed class SafeProcessHandle : SafeHandleZeroOrminusOneIsInvalid {
    // ... Costruttori ...

    protected override bool ReleaseHandle() {
        // Questa chiamata è garantita da .NET per rilasciare l'handle nativo.
        return Native_Imports.CloseHandle(handle);
    }
}
```

## Ciclo Dettagliato di Iniezione della DLL

Il processo di iniezione della DLL è una sequenza di passaggi critici che devono essere eseguiti con precisione per avere successo. La libreria **SA-MP Injector C#** orchestra questo nel seguente modo:

### 1. Validazione dell'Input

Prima di qualsiasi interazione con il sistema, tutti i parametri forniti dall'utente (percorso della cartella del gioco, nickname, IP, porta e password) vengono verificati da `Input_Validator`. Questo include:
- Verificare che il nickname rientri nei limiti di lunghezza e non sia vuoto.
- Garantire che la porta sia un numero valido e si trovi nell'intervallo accettabile (1-65535).
- Confermare che `gta_sa.exe`, `samp.dll` e `omp-client.dll` (se `Injection_Type` è OMP) esistano nei percorsi previsti.

> [!NOTE]
> Questo passaggio preventivo è fondamentale per evitare fallimenti imprevisti delle API e fornire un feedback chiaro all'utente.

### 2. Creazione del Processo del Gioco (Sospeso)

La libreria utilizza `Native_Imports.CreateProcessA` per avviare `gta_sa.exe`. Tuttavia, un dettaglio cruciale è l'uso del flag `Constants.CREATE_SUSPENDED`.
- **Creazione Sospesa:** Questo flag fa sì che Windows crei il processo e il suo thread principale, ma lo metta in uno stato sospeso, impedendo che il codice del gioco inizi a essere eseguito.
- **Riga di Comando:** La riga di comando viene attentamente costruita da `Process_Handler.Build_Full_Command_Args_ANSI` per includere tutti i parametri di connessione del server (`-c -n <nickname> -h <ip> -p <port> -z <password>`).
- **Handle di Processo/Thread:** `CreateProcessA` restituisce gli handle per il processo e il thread principale, che vengono incapsulati in `SafeProcessHandle` e `SafeThreadHandle` per una gestione sicura delle risorse.

> [!IMPORTANT]
> La creazione sospesa è vitale per l'iniezione. Se il gioco iniziasse a essere eseguito prima dell'iniezione, potrebbe inizializzare i propri meccanismi di sicurezza o la `samp.dll`/`omp-client.dll` potrebbe essere caricata prima del nostro controllo, rendendo l'iniezione più complessa o inefficace.

### 3. Iniezione di `samp.dll`

Con il processo del gioco sospeso, la funzione `Process_Handler.Inject_DLL` esegue i seguenti passaggi:
1. **Ottenere `LoadLibraryA`:** Viene ottenuto l'indirizzo della funzione `LoadLibraryA` (da `kernel32.dll`) nel processo del gioco. Questa è la funzione che Windows usa per caricare le DLL.
2. **Allocazione di Memoria Remota:** `Native_Imports.VirtualAllocEx` viene utilizzata per allocare un blocco di memoria all'interno dello spazio degli indirizzi virtuali del processo `gta_sa.exe`. La dimensione del blocco è sufficiente per memorizzare il percorso completo di `samp.dll`.
3. **Scrittura del Percorso della DLL:** Il percorso completo del file `samp.dll` viene scritto nella memoria appena allocata nel processo del gioco usando `Native_Imports.WriteProcessMemory`.
4. **Creazione di un Thread Remoto:** `Native_Imports.CreateRemoteThread` viene chiamata per creare un nuovo thread nel processo `gta_sa.exe`. Questo thread è istruito a eseguire `LoadLibraryA` con l'indirizzo della stringa del percorso della DLL come unico argomento.
5. **Attendere il Completamento:** La libreria attende un timeout (`Constants.DLL_INJECTION_TIMEOUT_MS`) affinché il thread remoto completi la sua esecuzione, indicando che `LoadLibraryA` ha tentato di caricare la DLL.
6. **Verificare il Risultato:** Viene verificato il codice di uscita del thread remoto. Se `LoadLibraryA` ha avuto successo, restituisce l'indirizzo di base della DLL caricata. Un valore zero o un fallimento nell'ottenere il codice di uscita indica che l'iniezione è fallita.
7. **Pulizia:** La memoria remota allocata viene liberata (`Native_Imports.VirtualFreeEx`) e l'handle del thread remoto viene chiuso (`Native_Imports.CloseHandle`).

### 4. Iniezione di `omp-client.dll` (Opzionale, Dipendente da SA-MP)

> [!TIP]
> L'iniezione di `omp-client.dll` **avviene sempre dopo l'iniezione riuscita di `samp.dll`**. Il client OMP utilizza l'infrastruttura di SA-MP, quindi `samp.dll` è un requisito.

Se l'`Injection_Type` specificato è `OMP`, il passaggio 3 viene ripetuto per iniettare `omp-client.dll`. La logica è identica, garantendo che entrambe le librerie necessarie per OMP vengano caricate prima che il gioco si avvii completamente.

### Riprendere il Thread Principale del Gioco

Infine, dopo che tutte le DLL necessarie sono state iniettate con successo, viene chiamata la funzione `Process_Handler.Resume_Game_Thread`. Questa funzione utilizza `Native_Imports.ResumeThread` per consentire al thread principale di `gta_sa.exe` di continuare la sua esecuzione. Il gioco ora si avvia con le DLL SA-MP/OMP già caricate e gli argomenti della riga di comando per la connessione al server applicati.

## Gestione degli Errori e Casi di Fallimento

La libreria è stata progettata per fornire un feedback chiaro in caso di fallimento. La maggior parte degli errori viene catturata e una `error_message` descrittiva viene restituita per essere presentata all'utente, di solito tramite un `MessageBox`.

### Errori di Validazione dell'Input

Questi errori si verificano prima di qualsiasi operazione di sistema e vengono rilevati da `Input_Validator`.

#### Nickname non valido

- **Messaggio di Errore (Esempio 1):** `"Il nickname non può essere vuoto. Fornisci un nickname valido."`
- **Messaggio di Errore (Esempio 2):** `"La lunghezza del nickname supera il massimo consentito di 23 caratteri. Usa un nickname più corto."`
- **Perché:** Il campo del nickname è vuoto o supera il limite massimo di 23 caratteri.
- **Soluzione:** L'utente deve fornire un nickname valido che rispetti il limite di caratteri.

#### Porta non valida

- **Messaggio di Errore (Esempio 1):** `"Formato porta non valido. La porta deve essere un valore numerico. Fornisci un intero valido per la porta."`
- **Messaggio di Errore (Esempio 2):** `"Il numero di porta specificato (70000) è al di fuori dell'intervallo valido da 1 a 65535. Fornisci una porta valida."`
- **Perché:** La porta fornita non è un numero intero, o è al di fuori dell'intervallo valido da 1 a 65535.
- **Soluzione:** L'utente deve inserire un numero di porta valido e all'interno dell'intervallo specificato.

#### File di Gioco/DLL Mancanti

- **Messaggio di Errore (Esempio 1):** `"Eseguibile del gioco non trovato. Assicurati che 'gta_sa.exe' esista nel percorso specificato: C:\Program Files (x86)\Rockstar Games\GTA San Andreas\gta_sa.exe"`
- **Messaggio di Errore (Esempio 2):** `"Libreria SA-MP non trovata. Assicurati che 'samp.dll' esista nel percorso specificato: C:\Program Files (x86)\Rockstar Games\GTA San Andreas\samp.dll"`
- **Messaggio di Errore (Esempio 3, OMP):** `"Libreria OMP non trovata. Assicurati che 'omp-client.dll' esista nel percorso specificato per l'iniezione OMP: C:\Program Files (x86)\Rockstar Games\GTA San Andreas\omp-client.dll"`
- **Perché:** Il file eseguibile del gioco (`gta_sa.exe`), la DLL di SA-MP (`samp.dll`) o la DLL di OMP (`omp-client.dll`) non sono stati trovati nella cartella del gioco specificata.
- **Soluzione:** L'utente deve verificare il percorso della cartella del gioco e assicurarsi che tutti i file necessari siano presenti.

### Errori nella Creazione del Processo

Questi errori si verificano quando la libreria tenta di avviare `gta_sa.exe`.

#### Fallimento nella Creazione del Processo

- **Messaggio di Errore (Esempio):** `"Impossibile creare il processo del gioco. Assicurati che 'gta_sa.exe' non sia in esecuzione e di avere i permessi sufficienti per eseguire il file. Errore di Sistema: Accesso negato."`
- **Perché:**
   - **File in Uso:** `gta_sa.exe` potrebbe essere già in esecuzione, impedendo la creazione di una nuova istanza, o il sistema operativo potrebbe avere un blocco sul file.
   - **Permessi:** L'utente che esegue l'applicazione potrebbe non avere i permessi sufficienti per avviare un nuovo processo o per accedere all'eseguibile del gioco.
   - **Percorso non Valido/Corrotto:** Sebbene la validazione di base verifichi l'esistenza, potrebbero esserci problemi di autorizzazione di lettura/esecuzione o l'eseguibile potrebbe essere corrotto.
- **Soluzione:** Assicurati che nessun'altra istanza di `gta_sa.exe` sia in esecuzione. Esegui l'applicazione come amministratore, se possibile. Verifica l'integrità del file `gta_sa.exe`.

### Errori nell'Iniezione della DLL

Questi sono gli errori più critici e si verificano durante il tentativo di iniettare `samp.dll` o `omp-client.dll` nel processo del gioco.

#### Handle `kernel32.dll` non disponibile

- **Messaggio di Errore:** `"Impossibile ottenere un handle per kernel32.dll. Questa è una libreria di sistema essenziale e questo errore indica un grave problema di sistema."`
- **Perché:** La libreria `kernel32.dll`, fondamentale per le operazioni di sistema in Windows, non ha potuto essere caricata o il suo handle non ha potuto essere ottenuto. Questo è estremamente raro e suggerisce un grave problema nel sistema operativo.
- **Soluzione:** Riavviare il sistema potrebbe risolvere. Altrimenti, indica un problema più profondo con l'installazione di Windows.

#### Funzione `LoadLibraryA` non disponibile

- **Messaggio di Errore:** `"Impossibile trovare l'indirizzo della funzione LoadLibraryA in kernel32.dll. Questo è fondamentale per iniettare la DLL."`
- **Perché:** La funzione `LoadLibraryA`, essenziale per caricare dinamicamente le DLL, non è stata trovata in `kernel32.dll`. Come l'errore precedente, è un raro problema di basso livello.
- **Soluzione:** Simile all'indisponibilità dell'handle di `kernel32.dll`.

#### Fallimento nell'Allocazione di Memoria Remota

- **Messaggio di Errore:** `"Impossibile allocare memoria nel processo di destinazione. Ciò potrebbe essere dovuto a permessi insufficienti o a meccanismi di protezione del processo."`
- **Perché:** La libreria non è riuscita ad allocare un blocco di memoria nello spazio degli indirizzi di `gta_sa.exe`.
   - **Permessi:** L'applicazione potrebbe non avere i permessi necessari per modificare lo spazio di memoria di un altro processo.
   - **Protezione del Processo:** Il processo `gta_sa.exe` o il sistema operativo potrebbero applicare protezioni contro l'iniezione di codice.
   - **Spazio degli Indirizzi:** In casi estremi, lo spazio degli indirizzi del processo potrebbe essere frammentato o senza memoria contigua sufficiente, anche se improbabile per la dimensione di una stringa di percorso di una DLL.
- **Soluzione:** Esegui l'applicazione come amministratore. Verifica la presenza di software di sicurezza (antivirus, anti-cheat) che potrebbero bloccare l'allocazione di memoria in altri processi.

#### Fallimento nella Scrittura nella Memoria del Processo

- **Messaggio di Errore:** `"Impossibile scrivere il percorso della DLL nella memoria del processo di destinazione. Verifica i permessi del processo e assicurati che il percorso della DLL sia accessibile."`
- **Perché:** La libreria ha allocato memoria nel processo del gioco, ma non è riuscita a scrivere il percorso della DLL in quella posizione.
   - **Permessi:** Simile al fallimento dell'allocazione di memoria, potrebbe essere un problema di permesso di scrittura.
   - **Protezione:** La protezione della memoria del sistema operativo o l'anti-cheat potrebbero impedire la scrittura.
- **Soluzione:** Verifica i permessi e il software di sicurezza.

#### Fallimento nella Creazione del Thread Remoto

- **Messaggio di Errore (Esempio):** `"Impossibile creare un thread remoto nel processo di destinazione per eseguire l'iniezione della DLL. Ciò potrebbe essere dovuto a restrizioni di sicurezza o allo stato del processo. Errore di Sistema: Risorse di memoria insufficienti per elaborare questo comando."`
- **Perché:** L'API `CreateRemoteThread` non è riuscita a creare un nuovo thread nel processo `gta_sa.exe` per chiamare `LoadLibraryA`.
   - **Protezione del Processo/Anti-Cheat:** Molti sistemi anti-cheat e protezioni del sistema operativo monitorano e bloccano la creazione di thread remoti, poiché è una tecnica comune di iniezione.
   - **Stato del Processo:** Il processo del gioco potrebbe trovarsi in uno stato inconsistente che impedisce la creazione di thread.
- **Soluzione:** Disattiva temporaneamente qualsiasi software anti-cheat o antivirus. Prova a eseguire l'applicazione come amministratore.

#### Timeout o Errore nell'Attesa dell'Iniezione

- **Messaggio di Errore (Esempio):** `"Timeout o errore durante l'attesa del completamento dell'iniezione della DLL. Errore di Sistema: L'operazione di attesa è scaduta."`
- **Perché:** Il thread remoto (che chiama `LoadLibraryA`) non ha terminato la sua esecuzione entro il timeout specificato (10 secondi).
   - **Blocco:** `LoadLibraryA` potrebbe essersi bloccato o aver impiegato troppo tempo.
   - **Intercettazione:** Qualche meccanismo di sicurezza potrebbe aver intercettato e bloccato l'esecuzione di `LoadLibraryA` a tempo indeterminato.
- **Soluzione:** Può indicare che la DLL sta impiegando troppo tempo per caricarsi o che qualcosa la sta impedendo. Controllare i log di sistema o di SA-MP/OMP (se esistono) potrebbe aiutare.

#### L'Iniezione della DLL è fallita o ha restituito un errore

- **Messaggio di Errore:** `"L'iniezione della DLL è fallita o ha restituito un errore. La chiamata a LoadLibrary potrebbe essere fallita nel processo di destinazione."`
- **Perché:** Il thread remoto è stato completato, ma il codice di uscita di `LoadLibraryA` ha indicato un fallimento (generalmente `0` o `NULL`).
   - **DLL Inesistente/Corrotta:** Nonostante la validazione iniziale, la DLL potrebbe essere stata spostata o corrotta tra la validazione и l'iniezione.
   - **Dipendenze della DLL Mancanti:** La `samp.dll` o `omp-client.dll` potrebbe dipendere da altre DLL che non sono presenti nella directory del gioco o nel PATH di sistema.
   - **Errore Interno della DLL:** La DLL stessa potrebbe avere un errore interno che ne impedisce il corretto caricamento.
- **Soluzione:** Verifica l'integrità di `samp.dll`/`omp-client.dll`. Assicurati che tutte le dipendenze della DLL siano presenti.

### Errore nel Riprendere il Thread del Gioco

Questo è l'ultimo errore possibile nel ciclo di iniezione.

- **Messaggio di Errore (Esempio):** `"Impossibile riprendere il thread del processo del gioco: Handle non valido."`
- **Perché:** L'API `ResumeThread` non è riuscita a riavviare il thread principale di `gta_sa.exe`.
   - **Handle non Valido:** L'handle del thread potrebbe essere stato invalidato per qualche motivo.
   - **Problema di Permessi:** L'applicazione potrebbe non avere il permesso di modificare lo stato del thread.
- **Soluzione:** Prova a eseguire l'applicazione come amministratore. Se persiste, potrebbe indicare un problema più profondo di stabilità del sistema o del processo del gioco.

## Licenza

Copyright © **SA-MP Programming Community**

Questo software è concesso in licenza secondo i termini della Licenza MIT ("Licenza"); è possibile utilizzare questo software in conformità con le condizioni della Licenza. Una copia della Licenza può essere ottenuta su: [MIT License](https://opensource.org/licenses/MIT)

### Termini e Condizioni d'Uso

#### 1. Permessi Concessi

La presente licenza concede gratuitamente a chiunque ottenga una copia di questo software e dei file di documentazione associati i seguenti diritti:
* Utilizzare, copiare, modificare, unire, pubblicare, distribuire, sublicenziare e/o vendere copie del software senza restrizioni
* Permettere alle persone a cui il software viene fornito di fare lo stesso, soggetto alle seguenti condizioni

#### 2. Condizioni Obbligatorie

Tutte le copie o parti sostanziali del software devono includere:
* L'avviso di copyright sopra riportato
* Questo avviso di permesso
* L'avviso di esclusione di responsabilità sotto riportato

#### 3. Diritti d'Autore

Il software e tutta la documentazione associata sono protetti dalle leggi sul diritto d'autore. La **SA-MP Programming Community** mantiene la titolarità dei diritti d'autore originali del software.

#### 4. Esclusione di Garanzia e Limitazione di Responsabilità

IL SOFTWARE VIENE FORNITO "COSÌ COM'È", SENZA GARANZIE DI ALCUN TIPO, ESPLICITE O IMPLICITE, INCLUSE, MA NON LIMITATE A, LE GARANZIE DI COMMERCIABILITÀ, IDONEITÀ PER UN PARTICOLARE SCOPO E NON VIOLAZIONE.

IN NESSUN CASO GLI AUTORI O I TITOLARI DEL COPYRIGHT SARANNO RESPONSABILI PER QUALSIASI RECLAMO, DANNO O ALTRA RESPONSABILITÀ, SIA IN UN'AZIONE DI CONTRATTO, ILLECITO O ALTRO, DERIVANTE DA, FUORI O IN CONNESSIONE CON IL SOFTWARE O L'USO O ALTRE OPERAZIONI NEL SOFTWARE.

---

Per informazioni dettagliate sulla Licenza MIT, consultare: https://opensource.org/licenses/MIT