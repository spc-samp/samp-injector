# SA-MP Injector PowerShell

![License](https://img.shields.io/badge/License-MIT-yellow.svg?style=flat)
![PowerShell](https://img.shields.io/badge/PowerShell-5.1%2B-blue.svg?style=flat&logo=powershell)
![Platform](https://img.shields.io/badge/Platform-Windows-0078D6.svg?style=flat&logo=windows)
[![SA-MP | OMP](https://img.shields.io/badge/Support-SA--MP%20%7C%20OMP-yellow)](https://github.com/spc-samp/samp-injector)
![Code Quality](https://img.shields.io/badge/Code%20Quality-High-brightgreen.svg?style=flat)

L'**SA-MP Injector PowerShell** è più di un semplice script di **iniezione di DLL**. Rappresenta una **libreria di funzioni e classi PowerShell** sviluppata per offrire una soluzione robusta e completa per l'avvio programmatico del gioco **Grand Theft Auto: San Andreas** (**GTA:SA**) insieme ai suoi client multiplayer, specificamente **SA-MP (San Andreas Multiplayer)** e **OMP (Open Multiplayer)**. Il suo scopo principale è semplificare il processo di avvio del gioco, eliminando la complessità intrinseca alla manipolazione diretta dei processi del sistema operativo e al passaggio di argomenti dalla riga di comando.

Sviluppata per offrire la massima flessibilità e una facile integrazione, questa libreria consente agli sviluppatori di incorporarla direttamente nei loro **progetti e script PowerShell**. Non solo orchestra l'**iniezione fondamentale delle DLL** del client multiplayer (`samp.dll` o `omp-client.dll`), ma gestisce anche in modo intelligente tutti i parametri di connessione essenziali (**nickname**, **indirizzo IP**, **porta** e **password**), simulando un avvio nativo attraverso le risorse intrinseche della **Windows API**, a cui si accede direttamente tramite **PowerShell**.

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

- [SA-MP Injector PowerShell](#sa-mp-injector-powershell)
  - [Lingue](#lingue)
  - [Indice](#indice)
  - [Concetti Fondamentali e Motivazione](#concetti-fondamentali-e-motivazione)
    - [Perché Iniettare le DLL?](#perché-iniettare-le-dll)
    - [SA-MP e OMP: Distinzioni e Somiglianze](#sa-mp-e-omp-distinzioni-e-somiglianze)
    - [Iniezione di DLL in PowerShell: Un Approccio Diretto con WinAPI](#iniezione-di-dll-in-powershell-un-approccio-diretto-con-winapi)
  - [Architettura Interna della Libreria: Un'Analisi Approfondita](#architettura-interna-della-libreria-unanalisi-approfondita)
    - [`Constants.ps1`](#constantsps1)
    - [`CustomTypes.ps1`](#customtypesps1)
    - [`StringUtils.ps1`](#stringutilsps1)
    - [`ErrorUtils.ps1`](#errorutilsps1)
    - [`Process.ps1`](#processps1)
    - [`InjectorCore.ps1`](#injectorcoreps1)
    - [`Injector.ps1`](#injectorps1)
    - [`Cleanup.ps1`](#cleanupps1)
  - [Esempi Completi di Utilizzo](#esempi-completi-di-utilizzo)
    - [1. Preparazione dell'Ambiente di Sviluppo](#1-preparazione-dellambiente-di-sviluppo)
    - [2. Scenario di Base: Connessione a un Server SA-MP](#2-scenario-di-base-connessione-a-un-server-sa-mp)
    - [3. Scenario Avanzato: Connessione a un Server OMP](#3-scenario-avanzato-connessione-a-un-server-omp)
    - [4. Esecuzione da uno Script Padre](#4-esecuzione-da-uno-script-padre)
  - [Gestione degli Errori Comuni e Messaggi](#gestione-degli-errori-comuni-e-messaggi)
    - [1. Tipo di Iniezione Non Valido](#1-tipo-di-iniezione-non-valido)
    - [2. Porta del Server Non Valida (Formato o Intervallo)](#2-porta-del-server-non-valida-formato-o-intervallo)
      - [2.1. Formato della Porta Non Numerico](#21-formato-della-porta-non-numerico)
      - [2.2. Porta Fuori dall'Intervallo Valido](#22-porta-fuori-dallintervallo-valido)
    - [3. Nickname Non Valido (Vuoto o Troppo Lungo)](#3-nickname-non-valido-vuoto-o-troppo-lungo)
      - [3.1. Nickname Vuoto](#31-nickname-vuoto)
      - [3.2. Nickname Troppo Lungo](#32-nickname-troppo-lungo)
    - [4. File del Gioco o DLL Non Trovati](#4-file-del-gioco-o-dll-non-trovati)
      - [4.1. Eseguibile del Gioco (`gta_sa.exe`) Non Trovato](#41-eseguibile-del-gioco-gta_saexe-non-trovato)
      - [4.2. Libreria SA-MP (`samp.dll`) Non Trovata](#42-libreria-sa-mp-sampdll-non-trovata)
      - [4.3. Libreria OMP (`omp-client.dll`) Non Trovata (solo per iniezione OMP)](#43-libreria-omp-omp-clientdll-non-trovata-solo-per-iniezione-omp)
    - [5. Fallimento nella Creazione del Processo del Gioco](#5-fallimento-nella-creazione-del-processo-del-gioco)
    - [6. Fallimento nell'Allocazione di Memoria nel Processo di Destinazione](#6-fallimento-nellallocazione-di-memoria-nel-processo-di-destinazione)
    - [7. Fallimento nella Scrittura del Percorso della DLL nella Memoria del Processo](#7-fallimento-nella-scrittura-del-percorso-della-dll-nella-memoria-del-processo)
    - [8. Fallimento nel Trovare Funzioni Essenziali del Sistema](#8-fallimento-nel-trovare-funzioni-essenziali-del-sistema)
      - [8.1. `kernel32.dll` Non Trovato](#81-kernel32dll-non-trovato)
      - [8.2. `LoadLibraryA` Non Trovato](#82-loadlibrarya-non-trovato)
    - [9. Fallimento nella Creazione di un Thread Remoto per l'Iniezione](#9-fallimento-nella-creazione-di-un-thread-remoto-per-liniezione)
    - [10. Timeout o Fallimento nel Completamento dell'Iniezione](#10-timeout-o-fallimento-nel-completamento-delliniezione)
    - [11. Fallimento nel Riprendere il Thread del Processo del Gioco](#11-fallimento-nel-riprendere-il-thread-del-processo-del-gioco)
  - [Licenza](#licenza)
    - [Termini e Condizioni d'Uso](#termini-e-condizioni-duso)
      - [1. Permessi Concessi](#1-permessi-concessi)
      - [2. Condizioni Obbligatorie](#2-condizioni-obbligatorie)
      - [3. Diritti d'Autore](#3-diritti-dautore)
      - [4. Esclusione di Garanzia e Limitazione di Responsabilità](#4-esclusione-di-garanzia-e-limitazione-di-responsabilità)

## Concetti Fondamentali e Motivazione

### Perché Iniettare le DLL?

> [!NOTE]
> L'**iniezione di DLL (Dynamic Link Library)** è un metodo utilizzato nei sistemi operativi **Microsoft Windows** che consente l'esecuzione di codice all'interno dello spazio di memoria di un altro processo in esecuzione. È una tecnica potente con diverse applicazioni legittime, dal debug e monitoraggio di programmi alla modifica del comportamento delle applicazioni per estenderne le funzionalità.

Nel contesto di giochi come **GTA San Andreas**, che non sono stati originariamente sviluppati con funzionalità multiplayer integrate, l'**iniezione di DLL** è la base per l'esistenza di client multiplayer come **SA-MP** e **OMP**. Questi client sono implementati come **DLL** che, una volta iniettate nel processo `gta_sa.exe`, ne assumono il controllo, intercettano funzioni del gioco e stabiliscono la comunicazione con i server multiplayer.

Invece di dipendere da un launcher esterno o dalla modifica diretta dell'eseguibile del gioco, l'**iniezione di DLL** consente un avvio più flessibile e programmabile, particolarmente utile in ambienti in cui si desidera automatizzare il processo di connessione a server specifici con configurazioni predefinite.

### SA-MP e OMP: Distinzioni e Somiglianze

**SA-MP** e **OMP** sono le due principali piattaforme multiplayer per **GTA San Andreas**. Entrambi funzionano come modifiche del gioco base, trasformandolo in un ambiente online multigiocatore di massa.

- **SA-MP (San Andreas Multiplayer)**: Il client originale e più consolidato, ampiamente utilizzato per molti anni. La sua architettura richiede la `samp.dll` per funzionare.
- **OMP (Open Multiplayer)**: Un progetto open source, generalmente visto come un successore o un'alternativa più moderna a **SA-MP**, che offre miglioramenti in termini di prestazioni, stabilità e funzionalità aggiuntive. Richiede la `omp-client.dll`.

Sebbene operino in modo simile (**iniettando una DLL** nel processo di **GTA:SA**), la libreria **SA-MP Injector PowerShell** è stata attentamente sviluppata per supportare **entrambe le DLL**, riconoscendo le loro distinzioni nei nomi dei file e consentendo allo sviluppatore di scegliere il client multiplayer desiderato tramite un parametro di configurazione. Ciò garantisce che la libreria possa essere utilizzata con la vasta gamma di server e progetti basati su una delle due piattaforme.

### Iniezione di DLL in PowerShell: Un Approccio Diretto con WinAPI

PowerShell è un potente linguaggio di scripting per l'automazione in Windows, ma la manipolazione dei processi e l'iniezione di DLL a un livello così basso di sistema non è la sua funzione primaria. Per raggiungere questo obiettivo, la libreria **SA-MP Injector PowerShell** fa un uso estensivo del comando `Add-Type` per invocare direttamente le funzioni della **Windows API (WinAPI)**.

`Add-Type` consente di definire e compilare codice C# (o altri linguaggi .NET) in fase di esecuzione nell'ambiente PowerShell. Questo codice C# agisce come un "ponte" per le funzioni native della WinAPI (`DllImport`), rendendo possibili operazioni come:

- **`CreateProcessA`**: Per avviare il processo di GTA:SA.
- **`VirtualAllocEx`**: Per allocare memoria all'interno del processo remoto.
- **`WriteProcessMemory`**: Per copiare il percorso della DLL nella memoria allocata.
- **`GetModuleHandleA` e `GetProcAddress`**: Per ottenere l'indirizzo della funzione `LoadLibraryA` in `kernel32.dll`.
- **`CreateRemoteThread`**: Per creare un thread nel processo remoto che esegue `LoadLibraryA`, caricando di fatto la DLL.
- **`WaitForSingleObject` e `GetExitCodeThread`**: Per monitorare il successo dell'iniezione.
- **`ResumeThread`**: Per riattivare il processo del gioco dopo l'iniezione.
- **`CloseHandle`**: Per chiudere gli handle delle risorse di sistema e prevenire perdite.
- **`MessageBoxW`**: Per visualizzare messaggi di errore informativi all'utente.

Questo approccio diretto con la WinAPI consente a PowerShell di eseguire le stesse operazioni di basso livello che farebbe un'applicazione compilata in **C++**, con la comodità di un ambiente di scripting.

## Architettura Interna della Libreria: Un'Analisi Approfondita

La libreria **SA-MP Injector PowerShell** adotta un approccio modulare per gestire la complessità del processo di iniezione. Ogni script è un modulo specializzato, responsabile di una fetta specifica della funzionalità generale, promuovendo la chiarezza del codice, la manutenibilità e l'espandibilità.

### `Constants.ps1`

Questo script è la base di tutte le configurazioni fisse della libreria. Definisce una tabella hash globale (`$global:CONSTANTS`) che memorizza tutti i letterali e i valori numerici utilizzati, come limiti di porta, nomi di file DLL, riferimenti a API di sistema e flag per operazioni come la creazione di processi e l'allocazione di memoria.

```powershell
$global:CONSTANTS = @{
    # Limiti di validazione della porta
    MIN_PORT = 1
    MAX_PORT = 65535
    
    # Vincoli del nickname
    MAX_NICKNAME_LENGTH = 23
    
    # Nomi dei file richiesti
    SAMP_DLL_NAME = "samp.dll"
    OMP_DLL_NAME = "omp-client.dll"
    GAME_EXE_NAME = "gta_sa.exe"
    
    # Riferimenti API di sistema
    KERNEL32_DLL = "kernel32.dll"
    USER32_DLL = "user32.dll" # Utilizzato per MessageBoxW
    LOAD_LIBRARY_FUNC = "LoadLibraryA"
    
    # Prefissi degli argomenti della riga di comando
    CMD_ARG_CONFIG = "-c"
    CMD_ARG_NICKNAME = "-n"
    CMD_ARG_HOST = "-h"
    CMD_ARG_PORT = "-p"
    CMD_ARG_PASSWORD = "-z"
    
    # Identificatori del tipo di iniezione
    INJECT_TYPE_SAMP = "samp"
    INJECT_TYPE_OMP = "omp"
    
    # Titoli delle finestre di dialogo di errore
    ERROR_TITLE_SAMP = "SA-MP Injector Error - SPC"
    ERROR_TITLE_OMP = "OMP Injector Error - SPC"
    
    # Flag di creazione del processo (CREATE_SUSPENDED | DETACHED_PROCESS)
    # 0x00000104 = CREATE_SUSPENDED (0x4) + DETACHED_PROCESS (0x100)
    PROCESS_CREATION_FLAGS = 0x00000104
    
    # Timeout delle operazioni
    DLL_INJECTION_TIMEOUT_MS = 10000 # 10 secondi
    
    # Costanti di allocazione della memoria
    # 0x00003000 = MEM_COMMIT (0x1000) + MEM_RESERVE (0x2000)
    MEMORY_ALLOCATION_TYPE = 0x00003000
    # 0x00000004 = PAGE_READWRITE
    MEMORY_PROTECTION = 0x00000004
    # 0x00008000 = MEM_RELEASE
    MEMORY_FREE_TYPE = 0x00008000
    
    # Risultati di attesa degli oggetti (Windows API)
    WAIT_OBJECT_0 = 0x00000000
    WAIT_TIMEOUT = 0x00000102
    WAIT_FAILED = 0xFFFFFFFF
    
    # Indicatore di errore nella ripresa del thread (Windows API)
    THREAD_RESUME_ERROR = 0xFFFFFFFF # ResumeThread restituisce -1 in caso di fallimento
    
    # Costanti di MessageBox (Windows API)
    MB_OK = 0x00000000
    MB_ICONERROR = 0x00000010
    MB_TOPMOST = 0x00040000
}
```

> [!TIP]
> L'uso di una tabella hash globale per le costanti è una pratica comune negli script PowerShell. Centralizza le configurazioni ed evita "magic number" e stringhe ripetute, rendendo il codice più leggibile e facile da mantenere. I valori dei flag (`0x...`) corrispondono ai valori decimali delle costanti definite nella Windows API.

### `CustomTypes.ps1`

Questo script è fondamentale per l'interazione con la Windows API. Definisce tipi C# in fase di esecuzione utilizzando `Add-Type`, tra cui:

- **`Inject_Type` enum**: Per categorizzare il tipo di iniezione (SAMP o OMP), migliorando la sicurezza dei tipi.
- **`WinAPI` class**: Una classe statica che importa ed espone le funzioni della Windows API necessarie per l'iniezione. Ogni metodo in questa classe corrisponde a una funzione dell'API (`DllImport`), con la firma e il set di caratteri (`CharSet`) corretti.
- **`Startup_Info` struct e `Process_Information` struct**: Strutture di dati C# che replicano le strutture `STARTUPINFO` e `PROCESS_INFORMATION` utilizzate dalla funzione `CreateProcessA` della Windows API.
- **`Process_Info` class**: Una semplice classe in C# che agisce come contenitore per gli handle del processo e del thread restituiti dopo la creazione riuscita di un processo, facilitando il trasporto e la gestione di questi handle all'interno dell'ambiente PowerShell.

```powershell
if (-not ([System.Management.Automation.PSTypeName]'Inject_Type').Type) {
    Add-Type -TypeDefinition @'
        public enum Inject_Type {
            SAMP = 0,
            OMP = 1
        }
'@
}

if (-not ([System.Management.Automation.PSTypeName]'WinAPI').Type) {
    Add-Type -TypeDefinition @'
        using System;
        using System.Runtime.InteropServices;
        using System.Text; // Necessario per Marshal.GetLastWin32Error
        
        public class WinAPI {
            [DllImport("kernel32.dll", SetLastError = true, CharSet = CharSet.Ansi)]
            public static extern bool CreateProcessA(string lpApplicationName, [In, Out] byte[] lpCommandLine, IntPtr lpProcessAttributes, IntPtr lpThreadAttributes, bool bInheritHandles, 
                uint dwCreationFlags, IntPtr lpEnvironment, string lpCurrentDirectory, [In, Out] ref Startup_Info lpStartupInfo, out Process_Information lpProcessInformation);
            
            [DllImport("kernel32.dll", SetLastError = true)]
            public static extern IntPtr VirtualAllocEx(IntPtr hProcess, IntPtr lpAddress, uint dwSize, uint flAllocationType, uint flProtect);
            
            [DllImport("kernel32.dll", SetLastError = true)]
            public static extern bool VirtualFreeEx(IntPtr hProcess, IntPtr lpAddress, uint dwSize, uint dwFreeType);
            
            [DllImport("kernel32.dll", SetLastError = true)]
            public static extern bool WriteProcessMemory(IntPtr hProcess, IntPtr lpBaseAddress, byte[] lpBuffer, uint nSize, out IntPtr lpNumberOfBytesWritten);
            
            [DllImport("kernel32.dll", SetLastError = true, CharSet = CharSet.Ansi)]
            public static extern IntPtr GetModuleHandleA(string lpModuleName);
            
            [DllImport("kernel32.dll", SetLastError = true, CharSet = CharSet.Ansi)]
            public static extern IntPtr GetProcAddress(IntPtr hModule, string lpProcName);
            
            [DllImport("kernel32.dll", SetLastError = true)]
            public static extern IntPtr CreateRemoteThread(IntPtr hProcess, IntPtr lpThreadAttributes, uint dwStackSize, IntPtr lpStartAddress, IntPtr lpParameter, uint dwCreationFlags, 
                out IntPtr lpThreadId);
            
            [DllImport("kernel32.dll", SetLastError = true)]
            public static extern uint WaitForSingleObject(IntPtr hHandle, uint dwMilliseconds);
            
            [DllImport("kernel32.dll", SetLastError = true)]
            public static extern bool GetExitCodeThread(IntPtr hThread, out uint lpExitCode);
            
            [DllImport("kernel32.dll", SetLastError = true)]
            public static extern uint ResumeThread(IntPtr hThread);
            
            [DllImport("kernel32.dll", SetLastError = true)]
            public static extern bool CloseHandle(IntPtr hObject);
            
            [DllImport("user32.dll", SetLastError = true, CharSet = CharSet.Unicode)]
            public static extern int MessageBoxW(IntPtr hWnd, string lpText, string lpCaption, uint uType);
            
            // Struttura C# per STARTUPINFO
            [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi)]
            public struct Startup_Info {
                public uint cb;
                public string lpReserved;
                public string lpDesktop;
                public string lpTitle;
                public uint dwX;
                public uint dwY;
                public uint dwXSize;
                public uint dwYSize;
                public uint dwXCountChars;
                public uint dwYCountChars;
                public uint dwFillAttribute;
                public uint dwFlags;
                public short wShowWindow;
                public short cbReserved2;
                public IntPtr lpReserved2;
                public IntPtr hStdInput;
                public IntPtr hStdOutput;
                public IntPtr hStdError;
            }
            
            // Struttura C# per PROCESS_INFORMATION
            [StructLayout(LayoutKind.Sequential)]
            public struct Process_Information {
                public IntPtr hProcess;
                public IntPtr hThread;
                public uint dwProcessId;
                public uint dwThreadId;
            }
        }
'@
}

if (-not ([System.Management.Automation.PSTypeName]'Process_Info').Type) {
    Add-Type -TypeDefinition @'
        using System;
        
        // Classe ausiliaria per trasportare gli handle di processo e thread
        public class Process_Info {
            public IntPtr ProcessHandle { get; set; }
            public IntPtr ThreadHandle { get; set; }
            
            public Process_Info() {
                ProcessHandle = IntPtr.Zero;
                ThreadHandle = IntPtr.Zero;
            }
        }
'@
}
```

> [!IMPORTANT]
> L'iniezione di DLL a 32 bit (come `samp.dll` e `omp-client.dll`) in un processo a 32 bit (`gta_sa.exe`) **richiede che anche l'ambiente PowerShell sia a 32 bit**. L'**SA-MP Injector PowerShell** gestisce questo automaticamente riavviandosi in una shell PowerShell x86 se rileva di essere in esecuzione in un ambiente x64. Questo è cruciale per garantire la compatibilità delle dimensioni dei puntatori e il corretto funzionamento dell'iniezione.
>
> La direttiva `if (-not ([System.Management.Automation.PSTypeName]'TypeName').Type)` garantisce che i tipi C# vengano aggiunti all'ambiente PowerShell solo una volta, evitando errori di ridefinizione se lo script viene eseguito più volte nella stessa sessione.

### `StringUtils.ps1`

Questo modulo fornisce una funzione di utilità essenziale per la manipolazione delle stringhe, specificamente per gestire le codifiche dei caratteri necessarie quando si interagisce con la Windows API legacy (funzioni "A" di char*).

```powershell
function Convert_Wide_To_Local_8Bit {
    param([Parameter(Mandatory = $false)] [AllowEmptyString()] [string]$wide_string)
    
    if ([string]::IsNullOrEmpty($wide_string)) {
        return [string]::Empty
    }

    try {
        # Ottiene la codepage ANSI locale del sistema
        $ansi_code_page = [System.Globalization.CultureInfo]::CurrentCulture.TextInfo.ANSICodePage
        $encoding = [System.Text.Encoding]::GetEncoding($ansi_code_page)
        
        # Converte la stringa Unicode (wide) in byte nella codifica ANSI locale
        $bytes = $encoding.GetBytes($wide_string)

        # Riconverte i byte in una stringa utilizzando la stessa codifica ANSI
        # Questo garantisce che la stringa sia compatibile con le API che si aspettano una codifica a 8 bit (ANSI)
        return $encoding.GetString($bytes)
    }
    catch {
        # In caso di errore di conversione (es. caratteri che non possono essere mappati),
        # restituisce la stringa originale come fallback, anche se potrebbe causare problemi
        # se contiene caratteri non supportati dalle API ANSI.
        return $wide_string
    }
}
```

> [!IMPORTANT]
> La funzione `Convert_Wide_To_Local_8Bit` è cruciale perché molte funzioni della Windows API con suffisso "A" (`CreateProcessA`, `LoadLibraryA`, `GetModuleHandleA`, `GetProcAddress`) si aspettano stringhe codificate in ANSI (8-bit), che dipendono dalla codepage del sistema locale. Per impostazione predefinita, le stringhe in PowerShell sono Unicode. Questa funzione esegue la conversione necessaria. Se il nome del file o un argomento della riga di comando contiene caratteri al di fuori della codepage ANSI del sistema, la conversione può risultare in caratteri errati o perdita di dati. Per questo progetto, che mira a interagire con programmi più vecchi, questo approccio ANSI è tipicamente sufficiente e necessario.

### `ErrorUtils.ps1`

Questo modulo è responsabile di fornire un feedback chiaro all'utente in caso di fallimento. Centralizza la logica per ottenere i messaggi di errore di sistema e la visualizzazione di finestre di dialogo standard di Windows.

```powershell
function Get_System_Error_Message {
    param([Parameter(Mandatory = $true)][int]$error_code)
    
    try {
        # Usa Win32Exception per ottenere il messaggio di errore formattato dal sistema
        $exception = New-Object System.ComponentModel.Win32Exception($error_code)
        
        return $exception.Message
    }
    catch {
        # Fallback per messaggio di errore sconosciuto
        return "Unknown error (Code: $error_code)"
    }
}

function Show_Error {
    param([Parameter(Mandatory = $true)][string]$message, [Parameter(Mandatory = $true)][Inject_Type]$inject_type)
    
    # Determina il titolo della finestra di dialogo in base al tipo di iniezione
    $title = if ($inject_type -eq [Inject_Type]::SAMP) {
        $global:CONSTANTS.ERROR_TITLE_SAMP
    }
    else {
        $global:CONSTANTS.ERROR_TITLE_OMP
    }
    
    try {
        # Combina i flag per MessageBoxW (OK, Icona di Errore, Sempre in Primo Piano)
        $message_box_flags = $global:CONSTANTS.MB_OK -bor $global:CONSTANTS.MB_ICONERROR -bor $global:CONSTANTS.MB_TOPMOST
        
        # Chiama la funzione MessageBoxW importata tramite Add-Type
        [void][WinAPI]::MessageBoxW([System.IntPtr]::Zero, $message, $title, $message_box_flags)
    }
    catch {
        # In caso di fallimento nella visualizzazione di MessageBox (es. in ambienti senza UI), scrive sulla console
        Write-Host "[$title] $message" -ForegroundColor Red
    }
}
```

> [!NOTE]
> `Get_System_Error_Message` utilizza `System.ComponentModel.Win32Exception` di .NET per convertire un codice di errore numerico della Windows API (`GetLastError()`) in una descrizione testuale leggibile dall'utente, che potrebbe essere localizzata nella lingua del sistema operativo.
>
> `Show_Error` utilizza la funzione `MessageBoxW` importata da `user32.dll` tramite `Add-Type` (`CustomTypes.ps1`) per visualizzare una finestra di dialogo informativa. I flag come `MB_OK` e `MB_ICONERROR` sono importati dalle costanti della WinAPI.

### `Process.ps1`

Questo è il modulo principale responsabile dell'interazione diretta con le API di basso livello di Windows per manipolare i processi. Incapsula le operazioni cruciali di creazione del processo e iniezione di DLL, gestendo handle, memoria e thread.

```powershell
class Process {
    # Rilascia gli handle del processo e del thread, prevenendo perdite di risorse
    [void] Close_Process_Info([Process_Info]$process_info) {
        if ($null -ne $process_info) {
            # Chiude l'handle del processo se è valido
            if ($process_info.ProcessHandle -ne [System.IntPtr]::Zero -and $process_info.ProcessHandle -ne [System.IntPtr]::new(-1)) {
                [void][WinAPI]::CloseHandle($process_info.ProcessHandle)
                $process_info.ProcessHandle = [System.IntPtr]::Zero # Contrassegna come chiuso
            }

            # Chiude l'handle del thread se è valido
            if ($process_info.ThreadHandle -ne [System.IntPtr]::Zero -and $process_info.ThreadHandle -ne [System.IntPtr]::new(-1)) {
                [void][WinAPI]::CloseHandle($process_info.ThreadHandle)
                $process_info.ThreadHandle = [System.IntPtr]::Zero # Contrassegna come chiuso
            }
        }
    }

    # Crea il processo del gioco GTA:SA in stato sospeso
    [Process_Info] Create_Game_Process([string]$game_path, [string]$command_args, [string]$working_dir) {
        $startup_info = New-Object WinAPI+Startup_Info
        # Definisce la dimensione della struttura, cruciale per le API di Windows
        $startup_info.cb = [System.Runtime.InteropServices.Marshal]::SizeOf($startup_info)
        
        $process_information = New-Object WinAPI+Process_Information
        
        $command_line_bytes = $null

        if (-not [string]::IsNullOrEmpty($command_args)) {
            # Converte gli argomenti della riga di comando in un array di byte ANSI con terminatore nullo
            $command_line_bytes = [System.Text.Encoding]::Default.GetBytes($command_args + "`0")
        }
        
        # Imposta la directory di lavoro, null se vuota
        $current_directory = if ([string]::IsNullOrEmpty($working_dir)) {
            $null
        }
        else {
            $working_dir
        }
        
        # Chiama la funzione CreateProcessA della Windows API
        $success = [WinAPI]::CreateProcessA($game_path, $command_line_bytes, [System.IntPtr]::Zero, [System.IntPtr]::Zero, $false, $global:CONSTANTS.PROCESS_CREATION_FLAGS, 
            [System.IntPtr]::Zero, $current_directory, [ref]$startup_info, [ref]$process_information)
        
        if (-not $success) {
            # In caso di fallimento, ottiene l'ultimo errore di sistema e lo visualizza
            $error_code = [System.Runtime.InteropServices.Marshal]::GetLastWin32Error()
            $error_message = Get_System_Error_Message $error_code
            Show_Error "Failed to create game process. Ensure 'gta_sa.exe' is not running and you have sufficient permissions to execute the file. System Error: $error_message" ([Inject_Type]::SAMP)

            return $null # Restituisce null in caso di fallimento
        }
        
        # Restituisce un oggetto Process_Info contenente gli handle del processo e del thread
        $result = New-Object Process_Info
        $result.ProcessHandle = $process_information.hProcess
        $result.ThreadHandle = $process_information.hThread
        
        return $result
    }
    
    # Inietta una DLL nel processo remoto
    [bool] Inject_DLL([IntPtr]$process_handle, [string]$dll_path, [ref]$error_message) {
        if ($process_handle -eq [System.IntPtr]::Zero) {
            $error_message.Value = "Invalid process handle provided for DLL injection."

            return $false
        }
        
        if ([string]::IsNullOrEmpty($dll_path)) {
            $error_message.Value = "DLL path cannot be empty."

            return $false
        }
        
        # Converte il percorso della DLL in byte ASCII (ANSI 8-bit) con terminatore nullo
        $dll_path_bytes = [System.Text.Encoding]::ASCII.GetBytes($dll_path + "`0")
        $dll_path_size = $dll_path_bytes.Length
        
        # Alloca memoria nel processo remoto per il percorso della DLL
        $remote_memory = [WinAPI]::VirtualAllocEx($process_handle, [System.IntPtr]::Zero, $dll_path_size, $global:CONSTANTS.MEMORY_ALLOCATION_TYPE, $global:CONSTANTS.MEMORY_PROTECTION)
        
        if ($remote_memory -eq [System.IntPtr]::Zero) {
            $error_code = [System.Runtime.InteropServices.Marshal]::GetLastWin32Error()
            $error_message.Value = "Failed to allocate memory in the target process. This might be due to insufficient permissions or process protection mechanisms. System Error: $(Get_System_Error_Message $error_code)"

            return $false
        }
        
        # Usa un blocco try/finally per garantire che la memoria remota venga rilasciata
        try {
            $bytes_written = [System.IntPtr]::Zero
            # Scrive il percorso della DLL nella memoria remota
            $write_success = [WinAPI]::WriteProcessMemory($process_handle, $remote_memory, $dll_path_bytes, $dll_path_size, [ref]$bytes_written)
            
            if (-not $write_success) {
                $error_code = [System.Runtime.InteropServices.Marshal]::GetLastWin32Error()
                $error_message.Value = "Failed to write DLL path to the target process memory. Verify process permissions and ensure the DLL path is accessible. System Error: $(Get_System_Error_Message $error_code)"
                
                return $false
            }
            
            # Ottiene l'handle per kernel32.dll (che è caricato in tutti i processi)
            $kernel32_handle = [WinAPI]::GetModuleHandleA($global:CONSTANTS.KERNEL32_DLL)

            if ($kernel32_handle -eq [System.IntPtr]::Zero) {
                $error_code = [System.Runtime.InteropServices.Marshal]::GetLastWin32Error()
                $error_message.Value = "Failed to obtain a handle to kernel32.dll. This is an essential system library and this error indicates a severe system issue. System Error: $(Get_System_Error_Message $error_code)"
                
                return $false
            }
            
            # Ottiene l'indirizzo della funzione LoadLibraryA in kernel32.dll.
            # Questo indirizzo è coerente tra i processi nello stesso SO.
            $load_library_address = [WinAPI]::GetProcAddress($kernel32_handle, $global:CONSTANTS.LOAD_LIBRARY_FUNC)

            if ($load_library_address -eq [System.IntPtr]::Zero) {
                $error_code = [System.Runtime.InteropServices.Marshal]::GetLastWin32Error()
                $error_message.Value = "Failed to find the address of the LoadLibraryA function in kernel32.dll. This is critical for injecting the DLL. System Error: $(Get_System_Error_Message $error_code)"
                
                return $false
            }
            
            $thread_id = [System.IntPtr]::Zero
            # Crea un thread remoto nel processo di destinazione per eseguire LoadLibraryA
            $remote_thread_handle = [WinAPI]::CreateRemoteThread($process_handle, [System.IntPtr]::Zero, 0, $load_library_address, $remote_memory, 0, [ref]$thread_id)
            
            if ($remote_thread_handle -eq [System.IntPtr]::Zero) {
                $error_code = [System.Runtime.InteropServices.Marshal]::GetLastWin32Error()
                $error_message.Value = "Failed to create a remote thread in the target process to execute the DLL injection. This could be due to security restrictions or process state. System Error: $(Get_System_Error_Message $error_code)"
                
                return $false
            }
            
            # Usa un blocco try/finally per garantire che l'handle del thread remoto venga chiuso
            try {
                # Attende che il thread remoto (iniezione di DLL) sia completato o raggiunga un timeout
                $wait_result = [WinAPI]::WaitForSingleObject($remote_thread_handle, $global:CONSTANTS.DLL_INJECTION_TIMEOUT_MS)
                
                if ($wait_result -ne $global:CONSTANTS.WAIT_OBJECT_0) {
                    $error_code = [System.Runtime.InteropServices.Marshal]::GetLastWin32Error()

                    $wait_result_message = switch ($wait_result) {
                        $global:CONSTANTS.WAIT_TIMEOUT { "timeout" }
                        $global:CONSTANTS.WAIT_FAILED { "wait failed" }
                        default { "unknown wait result ($wait_result)" }
                    }

                    $error_message.Value = "Timeout or error waiting for DLL injection to complete ($wait_result_message). System Error: $(Get_System_Error_Message $error_code)"

                    return $false
                }
                
                $exit_code = 0
                # Ottiene il codice di uscita del thread remoto. Per LoadLibraryA, 0 significa fallimento.
                $get_exit_code_success = [WinAPI]::GetExitCodeThread($remote_thread_handle, [ref]$exit_code)
                
                if (-not $get_exit_code_success -or $exit_code -eq 0) {
                    $error_code = [System.Runtime.InteropServices.Marshal]::GetLastWin32Error()
                    $error_message.Value = "DLL injection failed or returned an error. The LoadLibrary call may have failed in the target process. Exit Code: $exit_code. System Error: $(Get_System_Error_Message $error_code)"

                    return $false
                }
                
                return $true # Iniezione riuscita
            }
            finally {
                # Garantisce che l'handle del thread remoto venga chiuso
                [void][WinAPI]::CloseHandle($remote_thread_handle)
            }
        }
        finally {
            # Garantisce che la memoria allocata in remoto venga liberata
            # 0 per dwSize in MEM_RELEASE libera l'intera regione allocata da VirtualAllocEx
            [void][WinAPI]::VirtualFreeEx($process_handle, $remote_memory, 0, $global:CONSTANTS.MEMORY_FREE_TYPE)
        }
    }
}
```

> [!NOTE]
> La classe `Process` usa `[System.IntPtr]` per rappresentare gli handle di Windows. È importante notare l'uso estensivo di `try/finally` per garantire che gli handle (`ProcessHandle`, `ThreadHandle`, `remote_memory`, `remote_thread_handle`) siano chiusi e la memoria liberata correttamente, anche in caso di errori. Questo è il modo PowerShell di implementare il principio **RAII** (Resource Acquisition Is Initialization), sebbene meno integrato nella sintassi del linguaggio.

### `InjectorCore.ps1`

Questa è la classe orchestratrice che unisce tutte le funzionalità dei moduli precedenti. Coordina la validazione, la costruzione degli argomenti della riga di comando, la creazione del processo e le chiamate di iniezione di DLL.

```powershell
class Injector_Core {
    # Funzione principale che orchestra l'inizializzazione e l'iniezione del gioco
    [bool] Initialize_Game([Inject_Type]$inject_type, [string]$folder, [string]$nickname, [string]$ip, [string]$port, [string]$password) {
        # Costruisce i percorsi completi per i file essenziali
        $game_path = Join-Path -Path $folder -ChildPath $global:CONSTANTS.GAME_EXE_NAME
        $samp_dll_path = Join-Path -Path $folder -ChildPath $global:CONSTANTS.SAMP_DLL_NAME
        $omp_dll_path = Join-Path -Path $folder -ChildPath $global:CONSTANTS.OMP_DLL_NAME
        
        $validation_error = [string]::Empty # Variabile per catturare i messaggi di errore di convalida
        
        # 1. Convalida dei file
        if (-not (Validate_Files $game_path $samp_dll_path $omp_dll_path $inject_type)) {
            # L'errore è già stato visualizzato dalla funzione di convalida
            return $false
        }

        # 2. Convalida della porta
        if (-not (Validate_Port $port ([ref]$validation_error))) {
            Show_Error $validation_error $inject_type
            return $false
        }
        
        # 3. Convalida del nickname
        if (-not (Validate_Nickname $nickname ([ref]$validation_error))) {
            Show_Error $validation_error $inject_type
            return $false
        }
        
        # 4. Conversione delle stringhe in codifica ANSI/8-bit (necessario per API legacy)
        $converted_nickname = Convert_Wide_To_Local_8Bit $nickname
        $converted_ip = Convert_Wide_To_Local_8Bit $ip
        $converted_port = Convert_Wide_To_Local_8Bit $port
        $converted_password = Convert_Wide_To_Local_8Bit $password
        $converted_game_path = Convert_Wide_To_Local_8Bit $game_path
        $converted_folder = Convert_Wide_To_Local_8Bit $folder
        $converted_samp_dll_path = Convert_Wide_To_Local_8Bit $samp_dll_path
        $converted_omp_dll_path = Convert_Wide_To_Local_8Bit $omp_dll_path
        
        # 5. Costruzione degli argomenti della riga di comando
        $command_arguments = $this.Build_Command_Args($converted_nickname, $converted_ip, $converted_port, $converted_password)
        
        $process_manager = New-Object Process # Istanzia la classe Process
        $process_info = $null # Variabile per memorizzare le informazioni del processo creato
        
        # Usa un blocco try/finally per garantire che gli handle del processo vengano chiusi
        try {
            # 6. Creazione del processo del gioco (sospeso)
            $process_info = $process_manager.Create_Game_Process($converted_game_path, $command_arguments, $converted_folder)
            
            if ($null -eq $process_info) {
                # L'errore è già stato visualizzato dalla funzione di creazione del processo
                return $false
            }

            $injection_error = [string]::Empty # Variabile per catturare i messaggi di errore di iniezione
            
            # 7. Iniezione della samp.dll
            if (-not $process_manager.Inject_DLL($process_info.ProcessHandle, $converted_samp_dll_path, ([ref]$injection_error))) {
                Show_Error "Failed to inject samp.dll: $injection_error" $inject_type
                return $false
            }
            
            # 8. Iniezione condizionale della omp-client.dll (solo se il tipo di iniezione è OMP)
            if ($inject_type -eq [Inject_Type]::OMP) {
                if (-not $process_manager.Inject_DLL($process_info.ProcessHandle, $converted_omp_dll_path, ([ref]$injection_error))) {
                    Show_Error "Failed to inject omp-client.dll: $injection_error" $inject_type
                    return $false
                }
            }
            
            # 9. Ripresa del processo del gioco
            # Il processo è stato creato in stato sospeso per consentire l'iniezione.
            # Ora che le DLL sono state iniettate, può essere ripreso.
            $resume_result = [WinAPI]::ResumeThread($process_info.ThreadHandle)

            if ($resume_result -eq $global:CONSTANTS.THREAD_RESUME_ERROR) {
                $error_code = [System.Runtime.InteropServices.Marshal]::GetLastWin32Error()
                $error_message = Get_System_Error_Message $error_code
                Show_Error "Failed to resume the game process thread: $error_message" $inject_type

                return $false
            }
            
            return $true # Successo in tutte le fasi!
        }
        finally {
            # Garantisce che gli handle del processo vengano chiusi alla fine,
            # indipendentemente dal successo o dal fallimento.
            if ($null -ne $process_info) {
                $process_manager.Close_Process_Info($process_info)
            }
        }
    }
    
    # Costruisce la stringa degli argomenti della riga di comando per l'eseguibile del gioco
    [string] Build_Command_Args([string]$nickname, [string]$ip, [string]$port, [string]$password) {
        $arguments = @(
            $global:CONSTANTS.CMD_ARG_CONFIG,
            $global:CONSTANTS.CMD_ARG_NICKNAME, $nickname,
            $global:CONSTANTS.CMD_ARG_HOST, $ip, 
            $global:CONSTANTS.CMD_ARG_PORT, $port
        )
        
        if (-not [string]::IsNullOrEmpty($password)) {
            $arguments += @($global:CONSTANTS.CMD_ARG_PASSWORD, $password)
        }

        return $arguments -join ' '
    }
}
```

> [!CAUTION]
> Per **OMP**, l'iniezione coinvolge la `omp-client.dll` *oltre* alla `samp.dll`. Questo è in linea con il modo in cui **OMP** funziona generalmente, poiché può usare `samp.dll` come base ed estendere le funzionalità con `omp-client.dll`. È cruciale che **entrambe le DLL** siano presenti e funzionanti nella directory del gioco affinché l'iniezione OMP abbia successo. Se una fallisce, il gioco potrebbe non avviarsi correttamente o il client multiplayer potrebbe non caricarsi.
>
> Si noti che, poiché PowerShell non ha un `std::optional` o una garanzia di **RAII** nativa come C++, il codice utilizza un blocco `try/finally` esplicito nella funzione `Initialize_Game` per garantire che `Close_Process_Info` venga chiamato e gli handle vengano rilasciati, anche se si verifica un errore. Questa è una buona pratica di pulizia delle risorse in PowerShell.

### `Injector.ps1`

Questo è lo script di ingresso principale della libreria. Gestisce il caricamento degli altri moduli, la convalida dell'ambiente PowerShell (verificando se è x86 per la compatibilità dell'iniezione) e l'inizializzazione della classe `Injector_Core`. È lo script che l'utente finale eseguirà.

```powershell
param([Parameter(Mandatory = $true, Position = 0)][ValidateNotNullOrEmpty()][string]$inject_type,
    [Parameter(Mandatory = $true, Position = 1)][ValidateNotNullOrEmpty()][string]$folder,
    [Parameter(Mandatory = $true, Position = 2)][ValidateNotNullOrEmpty()][string]$nickname,
    [Parameter(Mandatory = $true, Position = 3)][ValidateNotNullOrEmpty()][string]$ip,
    [Parameter(Mandatory = $true, Position = 4)][ValidateNotNullOrEmpty()][string]$port,
    [Parameter(Position = 5)][AllowEmptyString()][string]$password = "",
    [switch]$restarted_x86) # Flag interna per indicare che lo script è già stato riavviato in x86

$ErrorActionPreference = 'Stop' # Garantisce che gli errori non terminanti si comportino come errori terminanti
# Questo fa sì che i blocchi catch catturino più errori e impedisce che lo script continui inaspettatamente.

# Ottiene il percorso completo dello script corrente, essenziale per caricare i moduli ausiliari
$script_path = $MyInvocation.MyCommand.Path

if ([string]::IsNullOrEmpty($script_path)) {
    # Nei casi in cui lo script viene invocato in modo speciale (es. da pipeline), $MyInvocation.MyCommand.Path può essere vuoto
    $script_path = Join-Path -Path (Get-Location) -ChildPath $MyInvocation.MyCommand.Name
}

$script_directory = Split-Path -Parent $script_path # Directory di base della libreria
$exit_code = 1 # Codice di uscita predefinito (fallimento)

try {
    # Carica tutti i moduli della libreria (costanti, tipi personalizzati, utilità, ecc.)
    . (Join-Path -Path $script_directory -ChildPath "Constants.ps1")
    . (Join-Path -Path $script_directory -ChildPath "CustomTypes.ps1")
    . (Join-Path -Path $script_directory -ChildPath "StringUtils.ps1")
    . (Join-Path -Path $script_directory -ChildPath "ErrorUtils.ps1")
    . (Join-Path -Path $script_directory -ChildPath "Validation.ps1")
    . (Join-Path -Path $script_directory -ChildPath "Process.ps1")
    . (Join-Path -Path $script_directory -ChildPath "InjectorCore.ps1")

    # Definisce la funzione di interfaccia principale per l'utente.
    # È un wrapper per la classe Injector_Core.
    function Initialize_Game {
        param([string]$inject_type, [string]$folder, [string]$nickname, [string]$ip, [string]$port, [string]$password = "")

        # Verifica se l'ambiente PowerShell è x64 e se non è ancora stato riavviato in x86
        if ([IntPtr]::Size -eq 8 -and -not $restarted_x86) {
            Write-Host "Detected PowerShell x64 environment. Restarting on PowerShell x86 for DLL injection compatibility (32-bit)..." -ForegroundColor Yellow

            # Localizza l'eseguibile di PowerShell a 32 bit
            $powershell_x86_path = Join-Path -Path $env:windir -ChildPath "SysWOW64\WindowsPowerShell\v1.0\powershell.exe"

            if (-not (Test-Path -Path $powershell_x86_path)) {
                Write-Host "Could not find powershell.exe (x86) at '$powershell_x86_path'. 32-bit DLL injection may fail." -ForegroundColor Red
                return $false
            }

            # Prepara la lista di argomenti per il nuovo processo PowerShell x86
            $argument_list = @("-NoProfile", "-NonInteractive", "-ExecutionPolicy", "Bypass", "-File", $script_path, $inject_type, $folder, $nickname, $ip, $port)
            
            if (-not [string]::IsNullOrEmpty($password)) {
                $argument_list += $password
            }
            # Aggiunge la flag per indicare che è già stato riavviato
            $argument_list += "-restarted_x86"
            
            try {
                $process_start_info = New-Object System.Diagnostics.ProcessStartInfo
                $process_start_info.FileName = $powershell_x86_path
                # Unisce gli argomenti in una stringa per StartInfo.Arguments
                $process_start_info.Arguments = ($argument_list | ForEach-Object { "`"$_`"" }) -join " " # Racchiude gli argomenti tra virgolette per gestire gli spazi
                $process_start_info.RedirectStandardOutput = $true # Reindirizza l'output del processo figlio
                $process_start_info.RedirectStandardError = $true   # Reindirizza gli errori del processo figlio
                $process_start_info.UseShellExecute = $false     # Non usa ShellExecute (esegue direttamente PowerShell.exe)
                $process_start_info.CreateNoWindow = $true       # Non crea una nuova finestra per il processo figlio

                $child_process = New-Object System.Diagnostics.Process
                $child_process.StartInfo = $process_start_info
                
                # Avvia il processo figlio e attende il completamento
                [void]$child_process.Start()
                $child_process.WaitForExit()
                
                # Cattura e visualizza l'output/errori del processo figlio
                $standard_output = $child_process.StandardOutput.ReadToEnd()
                $standard_error = $child_process.StandardError.ReadToEnd()

                if (-not [string]::IsNullOrEmpty($standard_output)) { Write-Host $standard_output }
                if (-not [string]::IsNullOrEmpty($standard_error)) { Write-Host $standard_error -ForegroundColor Red }

                $child_exit_code = $child_process.ExitCode
                
                if ($child_exit_code -eq 0) {
                    Write-Host "PowerShell x86 process completed with code 0 (Success)." -ForegroundColor Green
                    return $true
                }
                else {
                    Write-Host "PowerShell x86 process completed with error code: '$child_exit_code'." -ForegroundColor Red
                    return $false
                }
            }
            catch {
                Write-Host "Failed to start PowerShell x86: '$($_.Exception.Message)'" -ForegroundColor Red
                return $false
            }
        }
        
        # Logica di inizializzazione reale, viene raggiunta solo se l'ambiente è x86 o è già stato riavviato
        $injection_type = $null

        switch ($inject_type.ToLower()) {
            $global:CONSTANTS.INJECT_TYPE_SAMP {
                $injection_type = [Inject_Type]::SAMP
            }
            $global:CONSTANTS.INJECT_TYPE_OMP {
                $injection_type = [Inject_Type]::OMP
            }
            default {
                Show_Error "Invalid injection mode specified. Please use 'samp' or 'omp'." ([Inject_Type]::SAMP)
                return $false
            }
        }

        $injector_core = New-Object Injector_Core # Istanzia la classe principale di iniezione

        # Delega la chiamata alla funzione Initialize_Game della classe Injector_Core
        return $injector_core.Initialize_Game($injection_type, $folder, $nickname, $ip, $port, $password)
    }

    # Parametri passati alla funzione principale
    $initialization_parameters = @{
        inject_type = $inject_type
        folder = $folder
        nickname = $nickname
        ip = $ip
        port = $port
        password = $password
    }

    # Chiamata per avviare il processo di iniezione
    $game_initialization_result = Initialize_Game @initialization_parameters

    if ($game_initialization_result) {
        $exit_code = 0 # Successo
    }
    else {
        $exit_code = 1 # Fallimento
    }
}
catch {
    Write-Host "Critical error during execution: '$($_.Exception.Message)'" -ForegroundColor Red
    $exit_code = 1
}
finally {
    # Garantisce che lo script di pulizia venga eseguito alla fine, indipendentemente dal successo o dal fallimento
    try {
        . (Join-Path -Path $script_directory -ChildPath "Cleanup.ps1")
    }
    catch {
        Write-Host "Warning: Cleanup script execution failed: '$($_.Exception.Message)'" -ForegroundColor Yellow
    }
    
    exit $exit_code # Esce con il codice di stato appropriato
}
```

> [!NOTE]
> Questo script è il punto di ingresso principale per l'iniezione. È responsabile di:
> - Definire i **parametri della riga di comando** che l'utente finale utilizzerà.
> - Impostare `$ErrorActionPreference = 'Stop'` per un controllo più rigido degli errori.
> - **Caricare** tutti gli script ausiliari utilizzando il "dot-sourcing" (`. `), garantendo che le loro funzioni e classi siano disponibili nella sessione corrente.
> - Implementare la logica di **riavvio per l'ambiente x86**: se PowerShell è in esecuzione a 64 bit, si riavvia automaticamente in un'istanza a 32 bit (SysWOW64) e passa gli stessi argomenti, poiché l'iniezione di DLL a 32 bit è più affidabile (e, in molti casi, obbligatoria) da un processo a 32 bit. Questa è una distinzione chiave di PowerShell rispetto a un'applicazione C++ compilata direttamente per x86.
> - Chiamare la funzione `Initialize_Game` per avviare il processo di iniezione.
> - Gestire il codice di uscita dello script (0 per successo, 1 per fallimento).
> - Chiamare lo script `Cleanup.ps1` nel blocco `finally`.

### `Cleanup.ps1`

Questo script è responsabile della rimozione delle funzioni e delle variabili globali caricate dalla libreria dalla sessione corrente di PowerShell. Questa è una buona pratica per evitare l'inquinamento dell'ambiente e garantire che le esecuzioni successive dello script con diverse configurazioni non incontrino stati imprevisti delle sessioni precedenti.

```powershell
$functions_to_remove = @(
    '*Initialize_Game*', # Usa wildcard per rimuovere le funzioni (potrebbe avere alias)
    '*Get_System_Error_Message*',
    '*Show_Error*',
    '*Convert_Wide_To_Local_8Bit*',
    '*Validate_*', # Rimuove tutte le funzioni che iniziano con 'Validate_'
    '*Build_Command_Args*'
)

# Itera sui pattern e rimuove le funzioni
foreach ($pattern in $functions_to_remove) {
    Get-Command -CommandType Function -Name $pattern -ErrorAction SilentlyContinue | ForEach-Object {
        try {
            Remove-Item -Path "Function:$($_.Name)" -Force -ErrorAction SilentlyContinue
        }
        catch {} # Ignora gli errori se la funzione non può essere rimossa per qualche motivo
    }
}

$global_variables_to_remove = @(
    'CONSTANTS',
    'CAN_SHOW_MESSAGE_BOX' # Aggiungere qui se vengono introdotte più variabili globali
)

# Itera sulle variabili globali e le rimuove
foreach ($variable_name in $global_variables_to_remove) {
    try {
        Remove-Variable -Name $variable_name -Scope Global -Force -ErrorAction SilentlyContinue
    }
    catch {} # Ignora gli errori
}

$variable_patterns_to_remove = @(
    '*_Core*', # Rimuove le variabili che terminano con '_Core' (es. $injector_core)
    '*Process*' # Rimuove le variabili che terminano con 'Process' (es. $process_manager)
)

# Rimuove le variabili in diversi ambiti utilizzando i pattern
foreach ($scope in @('Script', 'Local')) {
    foreach ($pattern in $variable_patterns_to_remove) {
        Get-Variable -Scope $scope -Name $pattern -ErrorAction SilentlyContinue | ForEach-Object {
            try {
                Remove-Variable -Name $_.Name -Scope $scope -Force -ErrorAction SilentlyContinue
            }
            catch {} # Ignora gli errori
        }
    }
}
```

> [!TIP]
> La pulizia è cruciale negli script PowerShell che importano molti elementi nella sessione. `Remove-Item -Path "Function:..."` e `Remove-Variable` vengono utilizzati per deallocare questi elementi. L'uso di `ErrorAction SilentlyContinue` e `try/catch` vuoti nei cicli di rimozione garantisce che lo script di pulizia non fallisca nel caso in cui un elemento sia già stato rimosso o non esista.

## Esempi Completi di Utilizzo

Per integrare l'**SA-MP Injector PowerShell** nel tuo progetto o usarlo direttamente, segui le istruzioni e analizza gli scenari seguenti.

### 1. Preparazione dell'Ambiente di Sviluppo

- **Versione di PowerShell**: Si consiglia **PowerShell 5.1** o superiore (compatibile con `Add-Type` per le classi).
- **Permessi di Esecuzione**: PowerShell ha policy di esecuzione. Dovrai consentire l'esecuzione di script locali. Apri PowerShell come **Amministratore** ed esegui:
   ```powershell
   Set-ExecutionPolicy -ExecutionPolicy RemoteSigned -Scope CurrentUser
   ```
   Questo consentirà l'esecuzione di script firmati e di script che hai creato tu (non scaricati da internet) localmente senza firma.
- **Copia dei File**: Metti tutti i file `.ps1` della libreria (`Injector.ps1`, `Constants.ps1`, `CustomTypes.ps1`, `StringUtils.ps1`, `ErrorUtils.ps1`, `Validation.ps1`, `Process.ps1`, `InjectorCore.ps1`, `Cleanup.ps1`) in un'unica directory.
- **Permessi di Processo**: Il tuo script avrà bisogno dei privilegi di **Amministratore** per creare processi e iniettare DLL in un altro processo. Esegui sempre **PowerShell come Amministratore** quando usi questa libreria.

### 2. Scenario di Base: Connessione a un Server SA-MP

Questo è il caso d'uso più comune, avviare GTA:SA e connettersi a un server SA-MP con un nickname e un IP/porta specifici.

```powershell
# Crea un nuovo script, ad esempio, "StartSAMP.ps1"

# Importa la funzione principale della libreria SA-MP Injector PowerShell
# Assicurati che il percorso seguente rifletta dove si trova Injector.ps1.
# Ad esempio, se Injector.ps1 si trova nella stessa cartella di questo script:
$injector_path = Join-Path -Path $PSScriptRoot -ChildPath "Injector.ps1"

# Oppure, se si trova in una sottodirectory:
# $injector_path = Join-Path -Path $PSScriptRoot -ChildPath "SA-MP-Injector-PowerShell\Injector.ps1"

# Importa la funzione Injector.ps1 usando il dot-sourcing in modo che le sue funzioni
# siano disponibili nell'ambito corrente.
. $injector_path

# Definire le variabili di configurazione
# Modifica questi percorsi e dettagli del server per farli corrispondere alla tua configurazione locale.
$game_folder = "C:\Games\GTA San Andreas" # Dove si trovano gta_sa.exe, samp.dll
$player_nickname = "Nome"
$server_ip = "127.0.0.1" # Esempio: il tuo server locale
$server_port = "7777"
$server_password = "" # Lascia vuoto se non c'è password

Write-Host "Avvio di SA-MP..." -ForegroundColor Cyan
Write-Host "Cartella del gioco: $game_folder" -ForegroundColor Gray
Write-Host "Nickname: $player_nickname" -ForegroundColor Gray
Write-Host "Server: $server_ip:$server_port" -ForegroundColor Gray

# Chiamata alla funzione della libreria per avviare il gioco
$result = Initialize_Game `
    -inject_type "samp" ` # Tipo di iniezione: "samp" o "omp"
    -folder $game_folder ` # Percorso della cartella del gioco
    -nickname $player_nickname ` # Nickname desiderato
    -ip $server_ip ` # IP del server
    -port $server_port ` # Porta del server (stringa)
    -password $server_password # Password del server (stringa, può essere vuota)

if ($result) {
    Write-Host "`n--- SA-MP inizializzato con successo! ---" -ForegroundColor Green
    Write-Host "Il gioco è stato avviato in un processo separato." -ForegroundColor Green
}
else {
    Write-Host "`n--- FALLIMENTO nell'avvio di SA-MP! ---" -ForegroundColor Red
    Write-Host "Controlla i messaggi di errore visualizzati (pop-up o console)." -ForegroundColor Red
}

# Mantiene la console aperta per visualizzare i messaggi di output
Read-Host "`nPremere Invio per chiudere il programma."
```

**Per eseguire lo script:**
1. **Salva** il codice sopra come `StartSAMP.ps1` (o qualsiasi nome, purché termini con `.ps1`).
2. **Salva** tutti i file della libreria **SA-MP Injector PowerShell** nella stessa cartella o in una struttura di sottocartelle che gestisci con `$injector_path`.
3. **Apri PowerShell come Amministratore**.
4. Naviga fino alla directory in cui hai salvato `StartSAMP.ps1`.
5. Esegui lo script:
   ```powershell
   .\StartSAMP.ps1
   ```
   (Ricorda che `.` prima del nome dello script è necessario per gli script nella directory corrente, a meno che non lo aggiungi al PATH).

### 3. Scenario Avanzato: Connessione a un Server OMP

Per OMP, la logica è identica a quella di SA-MP, ma si specifica `"omp"` come `inject_type` e ci si assicura che `omp-client.dll` sia presente nella directory del gioco.

```powershell
# Crea un nuovo script, ad esempio, "StartOMP.ps1"

# Importa la funzione principale della libreria SA-MP Injector PowerShell
$injector_path = Join-Path -Path $PSScriptRoot -ChildPath "Injector.ps1"
. $injector_path

# Definire le variabili di configurazione per OMP
$game_folder = "C:\Games\GTA San Andreas" # Dove si trovano gta_sa.exe, samp.dll e omp-client.dll
$player_nickname = "Nome"
$server_ip = "127.0.0.1" # Esempio: il tuo server locale
$server_port = "7777"
$server_password = "" # Lascia vuoto se non c'è password

Write-Host "Avvio di OMP..." -ForegroundColor Cyan
Write-Host "Cartella del gioco: $game_folder" -ForegroundColor Gray
Write-Host "Nickname: $player_nickname" -ForegroundColor Gray
Write-Host "Server: $server_ip:$server_port" -ForegroundColor Gray

# Chiamata alla funzione della libreria per avviare il gioco
$result = Initialize_Game `
    -inject_type "omp" `   # Tipo di iniezione: "omp"
    -folder $game_folder `
    -nickname $player_nickname `
    -ip $server_ip `
    -port $server_port `
    -password $server_password

if ($result) {
    Write-Host "`n--- OMP inizializzato con successo! ---" -ForegroundColor Green
    Write-Host "Il gioco è stato avviato in un processo separato." -ForegroundColor Green
}
else {
    Write-Host "`n--- FALLIMENTO nell'avvio di OMP! ---" -ForegroundColor Red
    Write-Host "Controlla i messaggi di errore visualizzati (pop-up o console)." -ForegroundColor Red
}

Read-Host "`nPremere Invio per chiudere il programma."
```

**Per eseguire lo script:**

Segui gli stessi passaggi della sezione precedente, sostituendo `StartSAMP.ps1` con `StartOMP.ps1`.

### 4. Esecuzione da uno Script Padre

È possibile creare uno script più complesso che invoca la libreria e gestisce parametri o condizioni in modo più avanzato. Il concetto centrale rimane lo stesso: `Injector.ps1` deve essere "dot-sourced" nello script padre.

```powershell
# Launcher.ps1
param(
    [string]$type = "samp",
    [string]$game_dir = "C:\Games\GTA San Andreas",
    [string]$player_nickname = "Nome",
    [string]$server_ip = "127.0.0.1",
    [string]$server_port = "7777",
    [string]$server_password = ""
)

# Carica Injector.ps1
$injector_script = Join-Path -Path $PSScriptRoot -ChildPath "Injector.ps1"

# Verifica se lo script principale dell'iniettore esiste prima di caricarlo
if (-not (Test-Path $injector_script -PathType Leaf)) {
    Write-Error "Injector.ps1 non trovato in $injector_script. Si prega di verificare il percorso."
    
    exit 1
}

. $injector_script # Usa il dot-sourcing per caricare le funzioni

Write-Host "Tentativo di avviare il gioco con i parametri forniti..." -ForegroundColor Yellow

$success = Initialize_Game -inject_type $type `
    -folder $game_dir `
    -nickname $player_nickname `
    -ip $server_ip `
    -port $server_port `
    -password $server_password

if ($success) {
    Write-Host "`nRapporto del launcher: Gioco avviato con successo!" -ForegroundColor Green
}
else {
    Write-Host "`nRapporto del launcher: Fallimento nell'avvio del gioco!" -ForegroundColor Red
}

Read-Host "`nPremere Invio per uscire."
```

**Esecuzione di `Launcher.ps1`:**

```powershell
# Esegue con i valori predefiniti
.\Launcher.ps1

# Esegue per OMP con IP e porta specifici
.\Launcher.ps1 -type "omp" -server_ip "omp.server.com" -server_port "7777" -player_nickname "Nome" -server_password "secure123"
```

## Gestione degli Errori Comuni e Messaggi

L'**SA-MP Injector PowerShell** dà la priorità all'usabilità, e una parte fondamentale di ciò è fornire un feedback chiaro all'utente in caso di fallimento. I messaggi di errore vengono presentati tramite finestre di **dialogo di Windows** (`MessageBoxW`) o direttamente nella console di PowerShell, e sono categorizzati per tipo di **iniezione (SA-MP o OMP)** per un maggiore contesto. Ciò garantisce che tu sappia esattamente cosa è andato storto e come affrontare la risoluzione.

Ecco alcuni degli errori comuni che potresti incontrare e le loro probabili cause/soluzioni, accompagnate da esempi visivi di come queste finestre di dialogo appaiono all'utente finale:

### 1. Tipo di Iniezione Non Valido

Se l'`inject_type` fornito non è `"samp"` o `"omp"`, la libreria non saprà quale client multiplayer intendi avviare.

![Error 1](screenshots/error_1.png)

- **Messaggio di Errore Visualizzato**: `"Invalid injection mode specified. Please use 'samp' or 'omp'."`
- **Causa**: L'argomento `inject_type` non corrisponde ai valori attesi di `"samp"` o `"omp"`. Potrebbe essere un errore di battitura, una stringa vuota o un valore non riconosciuto.
- **Soluzione**: Verifica che `$inject_type` sia impostato correttamente su `"samp"` o `"omp"`. È importante che la stringa corrisponda esattamente (sebbene il codice usi `ToLower()` per il confronto).
   ```powershell
   # Corretto:
   Initialize_Game -inject_type "samp" ...
   Initialize_Game -inject_type "omp" ...

   # Errato (causerà un errore):
   # Initialize_Game -inject_type "invalid" ...
   # Initialize_Game -inject_type "" ...
   ```

### 2. Porta del Server Non Valida (Formato o Intervallo)

La porta è un parametro numerico essenziale per la connessione al server. Questo errore si verifica se il valore non può essere interpretato come un numero valido o è al di fuori dell'intervallo accettabile (**1 a 65535**).

#### 2.1. Formato della Porta Non Numerico

![Error 2](screenshots/error_2.png)

- **Messaggio di Errore Visualizzato**: `"Invalid port format. The port must be a numeric value. Please provide a valid integer for the port."`
- **Causa**: L'argomento `port` contiene caratteri che non sono cifre numeriche o non può essere convertito in un numero intero valido (es. `"abc"`, `"7777a"`).
- **Soluzione**: Fornisci una stringa che contenga solo cifre e rappresenti un numero intero valido.
   ```powershell
   # Corretto:
   Initialize_Game ... -port "7777" ...
   
   # Errato (formato non valido):
   # Initialize_Game ... -port "port7777" ...
   # Initialize_Game ... -port "invalid" ...
   ```

#### 2.2. Porta Fuori dall'Intervallo Valido

![Error 3](screenshots/error_3.png)

- **Messaggio di Errore Visualizzato**: `"The specified port number (XXXX) is outside the valid range of 1 to 65535. Please provide a valid port."` (XXXX sarà il valore che hai provato a usare).
- **Causa**: La porta fornita è un numero valido, ma è inferiore a `1` (riservata o non utilizzabile) o superiore a `65535` (limite massimo per le **porte TCP/UDP**).
- **Soluzione**: Fornisci una porta che sia nell'intervallo da `1` a `65535`. Le porte comuni per **SA-MP**/**OMP** sono `7777`.
   ```powershell
   # Corretto:
   Initialize_Game ... -port "7777" ...

   # Errato (fuori dall'intervallo):
   # Initialize_Game ... -port "0" ...      # Troppo basso
   # Initialize_Game ... -port "65536" ...  # Troppo alto
   # Initialize_Game ... -port "-1" ...     # Valore negativo
   ```

### 3. Nickname Non Valido (Vuoto o Troppo Lungo)

Il **nickname** del giocatore viene convalidato per garantire che il client del gioco lo accetti.

#### 3.1. Nickname Vuoto

![Error 4](screenshots/error_4.png)

- **Messaggio di Errore Visualizzato**: `"Nickname cannot be empty. Please provide a valid nickname."`
- **Causa**: L'argomento `nickname` è stato fornito come stringa vuota.
- **Soluzione**: Assicurati che il nickname non sia vuoto.
   ```powershell
   # Corretto:
   Initialize_Game ... -nickname "MioNome" ...

   # Errato (vuoto):
   # Initialize_Game ... -nickname "" ...
   ```

#### 3.2. Nickname Troppo Lungo

![Error 5](screenshots/error_5.png)

- **Messaggio di Errore Visualizzato**: `"Nickname length exceeds the maximum allowed of 23 characters. Please use a shorter nickname."`
- **Causa**: La lunghezza del **nickname** fornito supera `$global:CONSTANTS.MAX_NICKNAME_LENGTH`, che è di `23` caratteri.
- **Soluzione**: Usa un **nickname** che abbia al massimo `23` caratteri.
   ```powershell
   # Corretto:
   Initialize_Game ... -nickname "Corto" ...

   # Errato (troppo lungo):
   # Initialize_Game ... -nickname "QuestoNomeGiocatoreÈTroppoLungoDaUsareQui" ...
   ```

### 4. File del Gioco o DLL Non Trovati

Questa è una delle cause più comuni di fallimento. La libreria richiede che `gta_sa.exe`, `samp.dll` e, per **OMP**, `omp-client.dll` siano presenti nelle posizioni previste.

#### 4.1. Eseguibile del Gioco (`gta_sa.exe`) Non Trovato

![Error 6](screenshots/error_6.png)

- **Messaggio di Errore Visualizzato**: `"Game executable not found. Please ensure 'gta_sa.exe' exists at the specified path: [percorso completo]"`. Il `[percorso completo]` includerà la cartella e il nome del file.
- **Causa**: Il file `gta_sa.exe` non è stato trovato nella cartella fornita nell'argomento `folder`.
- **Soluzione**:
   1. Verifica che `$folder` punti alla directory di installazione corretta di **GTA San Andreas**.
   2. Conferma che `gta_sa.exe` esista all'interno di quella cartella e che il suo nome non sia stato modificato.

#### 4.2. Libreria SA-MP (`samp.dll`) Non Trovata

![Error 7](screenshots/error_7.png)

- **Messaggio di Errore Visualizzato**: `"SA-MP library not found. Please ensure 'samp.dll' exists at the specified path: [percorso completo]"`.
- **Causa**: Il file `samp.dll` non è stato trovato nella cartella fornita nell'argomento `folder`. **Questa DLL** è un requisito per **entrambi** i tipi di iniezione (`samp` e `omp`).
- **Soluzione**: Assicurati che `samp.dll` sia presente nella cartella di installazione di **GTA San Andreas**.

#### 4.3. Libreria OMP (`omp-client.dll`) Non Trovata (solo per iniezione OMP)

![Error 8](screenshots/error_8.png)

- **Messaggio di Errore Visualizzato**: `"OMP library not found. Please ensure 'omp-client.dll' exists at the specified path for OMP injection: [percorso completo]"`.
- **Causa**: Se hai specificato `"omp"` come tipo di iniezione, ma il file `omp-client.dll` non è stato trovato nella cartella fornita.
- **Soluzione**: Scarica il client **OMP** più recente e assicurati che `omp-client.dll` (e `samp.dll`) siano presenti nella cartella di installazione di **GTA San Andreas**.

### 5. Fallimento nella Creazione del Processo del Gioco

Questo è un errore più complesso, poiché coinvolge i **permessi del sistema operativo** e lo stato attuale di `gta_sa.exe`.

![Error 9](screenshots/error_9.png)

- **Messaggio di Errore Visualizzato**: `"Failed to create game process. Ensure 'gta_sa.exe' is not running and you have sufficient permissions to execute the file. System Error: [Messaggio di errore del sistema operativo]"`. Il messaggio di sistema sarà aggiunto da `Get_System_Error_Message` (es. `Access is denied.` o `The requested operation requires elevation.`).
- **Causa**: La chiamata `CreateProcessA` per avviare `gta_sa.exe` è fallita. Le cause comuni includono:
   - **Processo già in esecuzione**: Un'istanza di `gta_sa.exe` è già attiva e blocca una nuova esecuzione.
   - **Permessi insufficienti**: Il tuo script non ha i privilegi necessari (es. amministratore) per creare un processo in determinate configurazioni di sistema (**UAC** attivato, cartelle protette, ecc.).
   - **Problemi con l'eseguibile**: `gta_sa.exe` potrebbe essere corrotto o bloccato da un altro programma (es. un antivirus mal configurato).
- **Soluzione**:
   1. Controlla il Task Manager e assicurati che non ci siano istanze di `gta_sa.exe` in esecuzione. Chiudine eventualmente.
   2. Esegui lo script **PowerShell come Amministratore**. Clicca con il pulsante destro sull'icona di PowerShell e seleziona **"Esegui come amministratore"**, o avvialo da un collegamento configurato per farlo.
   3. Se un **antivirus** o un **software** di sicurezza sta interferendo, aggiungi il tuo script e/o la cartella di **GTA:SA** alle eccezioni dell'antivirus (fallo con cautela e solo se sei sicuro dell'integrità dei tuoi file).

### 6. Fallimento nell'Allocazione di Memoria nel Processo di Destinazione

La libreria tenta di allocare un piccolo spazio di memoria in `gta_sa.exe` per copiare il **percorso della DLL**.

![Error 10](screenshots/error_10.png)

- **Messaggio di Errore Visualizzato**: `"Failed to allocate memory in the target process. This might be due to insufficient permissions or process protection mechanisms. System Error: [Messaggio di errore del sistema operativo]"`.
- **Causa**: La funzione `VirtualAllocEx` (usata per allocare memoria all'interno di un altro processo) è fallita. Questo è più probabile se:
   - Il processo di **GTA:SA** (anche se in stato sospeso) ha difese di sicurezza o **patch anti-iniezione** che impediscono l'allocazione di memoria da parte di processi esterni.
   - Il tuo script non ha i permessi elevati necessari per manipolare la memoria di un altro processo.
   - (Meno comune) C'è una scarsità estrema di memoria virtuale nel sistema.
- **Soluzione**:
   1. Esegui il tuo script con privilegi di **Amministratore**.
   2. Assicurati che il gioco non abbia modifiche o **patch di sicurezza** che possano bloccare tentativi di iniezione o manipolazione della memoria (questo è più comune in ambienti modificati o con certi strumenti anti-cheat di terze parti).

### 7. Fallimento nella Scrittura del Percorso della DLL nella Memoria del Processo

Dopo aver allocato la memoria, la libreria tenta di copiarvi il **percorso della DLL**.

![Error 11](screenshots/error_11.png)

- **Messaggio di Errore Visualizzato**: `"Failed to write DLL path to the target process memory. Verify process permissions and ensure the DLL path is accessible. System Error: [Messaggio di errore del sistema operativo]"`.
- **Causa**: La funzione `WriteProcessMemory` è fallita nel tentativo di copiare i **byte del percorso della DLL** nella memoria remota allocata in `gta_sa.exe`. Questo di solito indica:
   - **Permessi di scrittura**: Il tuo script non ha il permesso di scrivere in quella regione di memoria o nel processo di **GTA:SA**.
   - **Handle non valido**: L'**handle** del processo è diventato in qualche modo non valido (meno comune, ma possibile in condizioni di sistema estreme).
   - **Problemi di Protezione della Memoria**: Una qualche protezione della memoria (sia del **SO** che di modifiche del gioco) ha impedito la scrittura.
- **Soluzione**: Esegui come **Amministratore**. Verifica che `gta_sa.exe` e il suo ambiente siano "puliti" da strumenti che potrebbero bloccare le operazioni di memoria.

### 8. Fallimento nel Trovare Funzioni Essenziali del Sistema

Queste sono API cruciali di Windows; errori qui indicano un problema fondamentale con il sistema operativo o l'ambiente di esecuzione.

#### 8.1. `kernel32.dll` Non Trovato

![Error 12](screenshots/error_12.png)

- **Messaggio di Errore Visualizzato**: `"Failed to obtain a handle to kernel32.dll. This is an essential system library and this error indicates a severe system issue. System Error: [Messaggio di errore del sistema operativo]"`.
- **Causa**: `kernel32.dll` è una delle DLL più basilari di Windows, contenente funzioni essenziali. Se `GetModuleHandleA` non riesce a ottenerne un **handle**, il sistema operativo ha problemi molto seri.
- **Soluzione**: Questo è un errore **critico** che raramente è causato dalla libreria o dal tuo script. Suggerisce corruzione dei file di sistema, problemi gravi con **Windows**, o un'installazione altamente insolita del **SO**. Si consiglia di eseguire controlli di integrità del sistema (come `sfc /scannow` nel **Prompt dei comandi** come **Amministratore**) o, in ultima istanza, di reinstallare **Windows**.

#### 8.2. `LoadLibraryA` Non Trovato

![Error 13](screenshots/error_13.png)

- **Messaggio di Errore Visualizzato**: `"Failed to find the address of the LoadLibraryA function in kernel32.dll. This is critical for injecting the DLL. System Error: [Messaggio di errore del sistema operativo]"`.
- **Causa**: Sebbene `kernel32.dll` sia stato trovato, la funzione `LoadLibraryA` non è stata risolta tramite `GetProcAddress`. Sebbene estremamente raro, può essere il risultato di corruzione del **file DLL** di `kernel32.dll` o di un ambiente di esecuzione altamente non standard.
- **Soluzione**: Come per l'errore di `kernel32.dll` sopra, questo indica un problema serio nel sistema operativo.

### 9. Fallimento nella Creazione di un Thread Remoto per l'Iniezione

Dopo aver preparato l'ambiente remoto e copiato il **percorso della DLL**, un nuovo **thread** viene creato nel processo del gioco per "chiamare" `LoadLibraryA`.

![Error 14](screenshots/error_14.png)

- **Messaggio di Errore Visualizzato**: `"Failed to create a remote thread in the target process to execute the DLL injection. This could be due to security restrictions or process state. System Error: [Messaggio di errore del sistema operativo]"`.
- **Causa**: La chiamata `CreateRemoteThread` è fallita. Questo errore è comune su sistemi con robuste difese **anti-iniezione** o quando un programma sta monitorando intensamente il comportamento del processo:
   - **Meccanismi di Sicurezza**: Strumenti **anti-cheat**, **software** di sicurezza o alcune policy di **Windows** possono rilevare e bloccare i tentativi di creare **thread** in processi di terze parti.
   - **Processo di Destinazione Incoerente**: Se il processo di **GTA:SA** si trova in uno stato inatteso o instabile (anche se avviato in `CREATE_SUSPENDED`), ciò può influire sulla capacità di creare **thread** al suo interno.
- **Soluzione**:
   1. Esegui il tuo script con privilegi di **Amministratore**.
   2. Verifica che non ci siano strumenti **anti-cheat**, **antivirus aggressivi** o **firewall** configurati per ispezionare e bloccare la manipolazione dei processi che possano essere in conflitto. Aggiungi il tuo script e `gta_sa.exe` alle eccezioni, se applicabile (con cautela).
   3. Il messaggio di errore di sistema può fornire dettagli aggiuntivi per investigare la causa specifica (es. **"A process has been denied access to create threads for other processes."**).

### 10. Timeout o Fallimento nel Completamento dell'Iniezione

Dopo aver creato il **thread** remoto, l'iniettore attende che esso completi il **caricamento della DLL**.

![Error 15](screenshots/error_15.png)

- **Messaggio di Errore Visualizzato**: `"Timeout or error waiting for DLL injection to complete (timeout). System Error: [Messaggio di errore del sistema operativo]"`.
- **Causa**: Il **thread** remoto che sta eseguendo `LoadLibraryA` ha impiegato più di `$global:CONSTANTS.DLL_INJECTION_TIMEOUT_MS` (10 secondi) per tornare, oppure è fallito e `GetExitCodeThread` ha restituito 0. Le cause potenziali includono:
   - **Problemi nella DLL Iniettata**: La `DllMain` di `samp.dll` o `omp-client.dll` impiega troppo tempo per essere eseguita, contiene un **loop infinito**, un **crash**, o un errore che **impedisce alla DLL** di caricarsi correttamente (es. **dipendenze di DLL** mancanti).
   - **Blocco Silenzioso**: Un meccanismo di sicurezza potrebbe aver bloccato `LoadLibraryA` ma non ha notificato con un errore ovvio di creazione di **thread**.
- **Soluzione**:
   1. Verifica l'integrità dei file `samp.dll` e `omp-client.dll`. Potrebbero essere corrotti o di una versione incompatibile con il tuo `gta_sa.exe`.
   2. Assicurati **che la DLL iniettata** non dipenda da **altre DLL** che potrebbero essere mancanti o inaccessibili nel sistema.

### 11. Fallimento nel Riprendere il Thread del Processo del Gioco

Questo è il passo finale per avviare il gioco dopo che **le DLL** sono state iniettate.

![Error 16](screenshots/error_16.png)

- **Messaggio di Errore Visualizzato**: `"Failed to resume the game process thread: [Messaggio di errore del sistema operativo]"`.
- **Causa**: La chiamata `ResumeThread` è fallita, il che significa che il **thread** principale di `gta_sa.exe` non è stato attivato per avviare l'esecuzione del gioco. Questo è un errore raro, ma può accadere se:
   - L'**handle** del **thread** del processo è diventato non valido.
   - Il sistema operativo ha impedito la ripresa per qualche motivo, possibilmente legato a un'interruzione di sicurezza o a uno stato incoerente del processo.
   - Il processo potrebbe essere stato terminato esternamente tra l'**iniezione della DLL** e il tentativo di ripresa del **thread** principale.
- **Soluzione**: Se tutti i passaggi precedenti sono andati a buon fine e solo `ResumeThread` è fallito, potrebbe essere un problema con il sistema operativo, con l'installazione stessa di **GTA:SA**, o con un altro **software** di sicurezza molto rigoroso. Riesamina lo stato di `gta_sa.exe` tramite il **Task Manager** subito prima e dopo l'errore. Riavviare il computer potrebbe risolvere problemi di stato temporaneo del sistema.

> [!TIP]
> In scenari di debug complessi, strumenti come **Process Monitor (Sysinternals Suite)** o un debugger (come **WinDbg**) possono essere inestimabili. Possono aiutare a osservare le chiamate **API**, verificare errori di accesso, tracciare lo stato degli **handle** e persino ispezionare la memoria del processo, fornendo una visione approfondita di ciò che sta accadendo dietro le quinte.
>
> Per eseguire il debug di script PowerShell che utilizzano `Add-Type` e interagiscono con la WinAPI a basso livello, strumenti come **PowerShell Integrated Scripting Environment (ISE)** o **Visual Studio Code** con l'estensione PowerShell sono utili, consentendo di inserire breakpoint e ispezionare le variabili. Ricorda sempre di eseguirli **come Amministratore**.

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