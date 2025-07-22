# SA-MP Injector

[![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](https://opensource.org/licenses/MIT)
[![SA-MP | OMP](https://img.shields.io/badge/Support-SA--MP%20%7C%20OMP-yellow)](https://github.com/spc-samp/samp-injector)
[![x86 Only](https://img.shields.io/badge/Architecture-x86%20(32--bit)-orange)](https://github.com/spc-samp/samp-injector)

**SA-MP Injector** è uno strumento versatile progettato per **SA-MP (San Andreas Multiplayer)** e **OMP (Open Multiplayer)**, che funziona come un **eseguibile da riga di comando**, una **libreria dinamica (DLL)** e un **insieme di librerie per diversi linguaggi di programmazione**. La sua funzione principale è quella di iniettare la `samp.dll` (nel caso di **SA-MP**) o entrambe `samp.dll` e `omp-client.dll` (nel caso di **OMP**) nel processo di **GTA:SA**, consentendo di avviare il gioco con parametri personalizzati, permettendo una connessione diretta a un server.

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

- [SA-MP Injector](#sa-mp-injector)
  - [Lingue](#lingue)
  - [Indice](#indice)
  - [Eseguibile](#eseguibile)
    - [Funzionalità](#funzionalità)
    - [Come utilizzare (Riga di comando)](#come-utilizzare-riga-di-comando)
      - [Modalità SA-MP](#modalità-sa-mp)
      - [Modalità OMP](#modalità-omp)
      - [Parametri](#parametri)
    - [Come utilizzare (Integrato in applicazioni)](#come-utilizzare-integrato-in-applicazioni)
    - [Utilizzo della libreria C++ nell'eseguibile](#utilizzo-della-libreria-c-nelleseguibile)
    - [Come compilare](#come-compilare)
      - [Requisiti](#requisiti)
      - [Fasi di compilazione](#fasi-di-compilazione)
  - [Libreria Dinamica (**DLL**)](#libreria-dinamica-dll)
    - [Funzionalità](#funzionalità-1)
    - [Come Utilizzare (Chiamata API)](#come-utilizzare-chiamata-api)
      - [Contratto della Funzione `Launch_Game`](#contratto-della-funzione-launch_game)
      - [Parametri](#parametri-1)
    - [Come Utilizzare (Incorporato nelle Applicazioni)](#come-utilizzare-incorporato-nelle-applicazioni)
    - [Utilizzo della Libreria C++ nella **DLL**](#utilizzo-della-libreria-c-nella-dll)
    - [Come Compilare](#come-compilare-1)
      - [Requisiti](#requisiti-1)
      - [Passaggi di Compilazione](#passaggi-di-compilazione)
  - [Librerie](#librerie)
    - [Panoramica](#panoramica)
    - [Elenco delle librerie](#elenco-delle-librerie)
  - [Licenza](#licenza)
    - [Termini e Condizioni d'Uso](#termini-e-condizioni-duso)
      - [1. Permessi Concessi](#1-permessi-concessi)
      - [2. Condizioni Obbligatorie](#2-condizioni-obbligatorie)
      - [3. Diritti d'Autore](#3-diritti-dautore)
      - [4. Esclusione di Garanzia e Limitazione di Responsabilità](#4-esclusione-di-garanzia-e-limitazione-di-responsabilità)

## Eseguibile

L'eseguibile `samp-injector.exe` offre un'interfaccia a riga di comando per avviare **GTA:SA** con **SA-MP** o **OMP**, configurando automaticamente la connessione a un server. Incapsula la logica dell'**iniezione di DLL** e il passaggio dei parametri del gioco.

### Funzionalità

Il `samp-injector.exe` opera come un launcher di gioco automatizzato, astrando le complessità della configurazione e dell'**iniezione di DLL**:

1. **Validazione dell'ambiente:** Verifica l'esistenza dei file essenziali (`gta_sa.exe`, `samp.dll`, `omp-client.dll`) nella directory specificata, oltre a validare i parametri di connessione forniti.
2. **Creazione di un processo sospeso:** Avvia `gta_sa.exe` in uno stato sospeso, un prerequisito per **iniettare le DLL** in modo sicuro prima che il processo principale del gioco venga eseguito.
3. **Iniezione dinamica di DLL:**
   - Per la modalità **SA-MP**, viene iniettata `samp.dll`.
   - Per la modalità **OMP**, vengono iniettate sia `samp.dll` che `omp-client.dll`. L'iniezione è facilitata dall'invocazione remota della funzione `LoadLibraryA`, che consente a GTA:SA di caricare i moduli multiplayer e inizializzare la connessione.
4. **Configurazione degli argomenti:** Gli argomenti della riga di comando, come **nickname**, **IP del server**, **porta** e **password (se fornita)**, vengono preparati e passati a `gta_sa.exe`.
5. **Ripresa del processo:** Dopo l'**iniezione riuscita delle DLL**, il processo del gioco viene ripreso per l'esecuzione normale, portando **GTA:SA** a connettersi direttamente al server.

### Come utilizzare (Riga di comando)

Per utilizzare l'eseguibile, invocalo dal **Prompt dei comandi (CMD)**, **PowerShell** o un **terminale**, fornendo i parametri necessari.

Il formato di base è:
```bash
samp-injector.exe <modalità> <directory_gioco> <nickname> <ip_server> <porta_server> <password_server (opzionale)>
```

#### Modalità SA-MP

Per l'iniezione esclusiva di `samp.dll`:
```bash
samp-injector.exe "samp" "C:\Games\GTA San Andreas" "Nome" "127.0.0.1" "7777" "password (opzionale)"
```

#### Modalità OMP

Per l'iniezione di `samp.dll` e `omp-client.dll`:
```bash
samp-injector.exe "omp" "C:\Games\GTA San Andreas" "Nome" "127.0.0.1" "7777" "password (opzionale)"
```

#### Parametri

- `<modalità>`: Definisce il tipo di iniezione.
   - `samp`: Per **SA-MP** (`samp.dll`).
   - `omp`: Per **OMP** (`samp.dll` e `omp-client.dll`).
- `<directory_gioco>`: Il percorso completo della directory di **GTA:SA**. Questa directory deve contenere `gta_sa.exe` e i rispettivi file **DLL**.
- `<nickname>`: Il tuo nickname nel gioco (massimo **20 caratteri**).
- `<ip_server>`: L'**indirizzo IP** o il **nome di dominio** del server.
- `<porta_server>`: La porta di connessione del server (un **valore numerico** compreso tra **1** e **65535**).
- `<password_server>`: La password necessaria per connettersi al server **(se il server non richiede una password, questo parametro non è necessario)**.

Se gli argomenti sono errati o insufficienti, verrà visualizzato un messaggio di utilizzo.

### Come utilizzare (Integrato in applicazioni)

Il `samp-injector.exe` è ideale per l'integrazione in applicazioni di terze parti, come launcher personalizzati, che desiderano automatizzare il processo di avvio del gioco con impostazioni predefinite.

Esempio di invocazione di `samp-injector.exe` da un'**applicazione C#**:
```csharp
using System;
using System.Diagnostics;
using System.Windows.Forms;

public class Launcher {
    public static void Main(string[] args) {
        string inject_mode = "omp"; 
        string folder = "C:\\Games\\GTA San Andreas";
        string nickname = "Nome";
        string ip = "127.0.0.1";
        string port = "7777";
        string password = "password (opzionale)";

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
                    MessageBox.Show($"L'iniettore SA-MP ha restituito un errore (Codice: {process.ExitCode}). Il gioco potrebbe non essere stato avviato correttamente.", "Errore di avvio", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }
        catch (Exception ex) {
            MessageBox.Show($"Si è verificato un errore durante l'avvio del gioco: {ex.Message}", "Errore", MessageBoxButtons.OK, MessageBoxIcon.Error);
        }
    }
}
```

### Utilizzo della libreria C++ nell'eseguibile

L'eseguibile `samp-injector.exe` è costruito sulla libreria [SA-MP Injector C++](https://github.com/spc-samp/samp-injector/tree/main/libraries/cpp), situata nella directory `libraries/cpp/`. Il file `main.cpp` dell'eseguibile invoca le funzionalità di questa libreria per eseguire l'iniezione e l'avvio del gioco.

Il file di intestazione principale della libreria **C++** da includere è `libraries/samp-injector/cpp/injector.hpp`. Poiché la libreria [SA-MP Injector C++](https://github.com/spc-samp/samp-injector/tree/main/libraries/cpp) è **header-only**, il suo utilizzo richiede solo l'inclusione di questa intestazione nel codice sorgente, senza la necessità di collegare un file `.lib`.

Il frammento rilevante di `main.cpp` che dimostra l'integrazione è il seguente:
```cpp
// Estrae gli argomenti della riga di comando
int argc;
std::unique_ptr<LPWSTR[], decltype(&LocalFree)> argv(CommandLineToArgvW(GetCommandLineW(), &argc), &LocalFree);

// ... (validazione del numero di argomenti e della modalità di iniezione) ...

// Estrae i parametri in variabili di stringa larga
std::wstring folder = argv[2];
std::wstring nickname = argv[3];
std::wstring ip = argv[4];
std::wstring port = argv[5];
std::wstring password = (argc == 7) ? argv[6] : L"";

// Delega la logica di iniezione alla funzione "Initialize_Game" della libreria
// Nota che "injector.hpp" è stato precedentemente incluso in "main.cpp"
if (!Initialize_Game(inject_type, folder, nickname, ip, port, password))
    return 1;

Sleep(10000); // Attende prima di terminare l'eseguibile
```

La funzione `Initialize_Game` funge da interfaccia di alto livello della libreria, orchestrando tutte le operazioni di validazione, creazione del processo e **iniezione di DLL**.

### Come compilare

Puoi compilare il `samp-injector.exe` dal codice sorgente. Se non desideri compilare, puoi scaricare le versioni precompilate nella sezione [Releases](https://github.com/spc-samp/samp-injector/releases).

#### Requisiti

- **Visual Studio:** Si consiglia **Visual Studio 2022** o superiore con il **carico di lavoro "Sviluppo desktop con C++"** installato.
- **Git:** Per clonare il repository (o scaricalo semplicemente accedendo a questo link: [Download](https://github.com/spc-samp/samp-injector/archive/refs/heads/main.zip)).

#### Fasi di compilazione

1. **Clonare il repository:**
   ```bash
   git clone https://github.com/spc-samp/samp-injector.git
   cd samp-injector
   ```
2. **Aprire la soluzione:**
   Naviga nella cartella `executable` e apri il file di soluzione `.sln`:
   ```bash
   cd executable
   start samp-injector.sln
   ```
   Questo aprirà il progetto in **Visual Studio**.
3. **Configurare la compilazione:**
   - In **Visual Studio**, verifica la configurazione della soluzione. Si consiglia di utilizzare le modalità `Release` e `x86` **(32 bit)**. Nel contesto di **GTA:SA** e **SA-MP**/**OMP**, l'**architettura x86 (32 bit)** è obbligatoria.
4. **Compilare:**
   - Nel menu `Compila`, fai clic su `Compila soluzione` o `Compila samp-injector`.
   - In alternativa, puoi utilizzare le scorciatoie:
      - `Ctrl + Shift + B` per compilare l'intera soluzione.
      - `Ctrl + B` (se configurato) per compilare il progetto corrente.
   - Se tutto è configurato correttamente, l'eseguibile `samp-injector.exe` verrà generato nella directory `executable\Release` (o `executable\Debug`, a seconda della configurazione di **build**).

## Libreria Dinamica (**DLL**)

La libreria `samp-injector.dll` offre un'**API (Interfaccia di Programmazione delle Applicazioni)** per avviare **GTA:SA** con **SA-MP** o **OMP** in modo programmatico. È l'alternativa ideale all'eseguibile per gli sviluppatori di launcher che desiderano un'integrazione più pulita e diretta, chiamando una funzione invece di avviare un processo esterno.

### Funzionalità

La `samp-injector.dll` attiva lo stesso flusso di lavoro robusto della libreria interna, incapsulando le complessità dell'iniezione e dell'inizializzazione del gioco:

1. **Creazione di un Processo Sospeso:** Quando viene chiamata, avvia `gta_sa.exe` in uno stato sospeso.
2. **Iniezione Dinamica di DLL:**
   - Per la modalità **SA-MP**, viene iniettata `samp.dll`.
   - Per la modalità **OMP**, vengono iniettate `samp.dll` e `omp-client.dll`.
3. **Configurazione degli Argomenti:** I parametri della funzione, come **nickname**, **IP**, **porta** e **password**, vengono preparati per `gta_sa.exe`.
4. **Ripresa del Processo:** Dopo l'iniezione, il processo del gioco viene ripreso per l'esecuzione, connettendosi direttamente al server.

### Come Utilizzare (Chiamata API)

Per utilizzare la libreria, è necessario caricare la `samp-injector.dll` nella propria applicazione e chiamare la funzione esportata `Launch_Game`.

#### Contratto della Funzione `Launch_Game`

- **File DLL:** `samp-injector.dll`
- **Nome della Funzione Esportata:** `Launch_Game`
- **Convenzione di Chiamata:** `__stdcall`
- **Tipo di Ritorno:** `int`
   - `0`: **Successo.** La richiesta di avvio del gioco è stata inviata a un thread in background.
   - `1`: **Argomenti Non Validi.** Un parametro obbligatorio era nullo o la modalità era non valida. Verrà mostrato un messaggio di errore.
   - `2`: **Errore del Thread.** Si è verificato un errore critico durante il tentativo di creare il thread di inizializzazione. Verrà mostrato un messaggio di errore.

#### Parametri

Tutti i parametri sono stringhe di caratteri larghi (Unicode).

- `mode` (`LPCWSTR`): Definisce il tipo di iniezione (`L"samp"` o `L"omp"`).
- `folder` (`LPCWSTR`): Il percorso completo della directory di **GTA:SA**.
- `nickname` (`LPCWSTR`): Il tuo nickname nel gioco.
- `ip` (`LPCWSTR`): L'indirizzo **IP** o il **nome di dominio** del server.
- `port` (`LPCWSTR`): La porta di connessione del server.
- `password` (`LPCWSTR`): La password per connettersi al server. **(Questo parametro è opzionale. Puoi passare `null` o una stringa vuota `L""` se non c'è password)**.

### Come Utilizzare (Incorporato nelle Applicazioni)

Esempio di chiamata della funzione `Launch_Game` da un'**applicazione C#**:
```csharp
using System;
using System.Runtime.InteropServices;
using System.Windows.Forms;

public class Launcher {
    // Importa la funzione dalla DLL, specificando il contratto dell'API.
    [DllImport("samp-injector.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.StdCall, EntryPoint = "Launch_Game")]
    private static extern int Launch_Game(string mode, string folder, string nickname, string ip, string port, string password);

    public static void Main(string[] args) {
        string inject_mode = "samp"; 
        string gta_folder = "C:\\Games\\GTA San Andreas"; // Attenzione: Usa il percorso reale!
        string nickname = "Nome";
        string ip = "127.0.0.1";
        string port = "7777";
        string password = "password (opzionale)"; // o null, o "" se non c'è

        try {
            int result = Launch_Game(inject_mode, gta_folder, nickname, ip, port, password);
            
            if (result != 0) {
                // La DLL mostra già un messaggio di errore dettagliato,
                // ma puoi registrare o mostrare un altro messaggio qui.
                MessageBox.Show($"La chiamata alla DLL ha restituito un codice di errore: {result}", "Errore nel Launcher", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }
        catch (DllNotFoundException) {
            MessageBox.Show("Errore: samp-injector.dll non trovata! Verifica se si trova nella stessa cartella del launcher.", "Errore", MessageBoxButtons.OK, MessageBoxIcon.Error);
        }
        catch (Exception ex) {
            MessageBox.Show($"Si è verificato un errore imprevisto: {ex.Message}", "Errore", MessageBoxButtons.OK, MessageBoxIcon.Error);
        }
    }
}
```

### Utilizzo della Libreria C++ nella **DLL**

Come per l'eseguibile, anche la `samp-injector.dll` è costruita sulla libreria [SA-MP Injector C++](https://github.com/spc-samp/samp-injector/tree/main/libraries/cpp), che si trova nella directory `libraries/cpp/`. La funzione esportata `Launch_Game` funge da wrapper, validando i parametri e delegando la logica principale di iniezione alla funzione `Initialize_Game` della libreria.

Il file di intestazione principale della libreria **C++** da includere è `libraries/samp-injector/cpp/injector.hpp`. Poiché la libreria [SA-MP Injector C++](https://github.com/spc-samp/samp-injector/tree/main/libraries/cpp) è **header-only**, il suo utilizzo richiede solo l'inclusione di questo file di intestazione nel codice sorgente, senza la necessità di collegare un file `.lib`.

Il seguente frammento di codice, tratto da `main.cpp` della **DLL**, dimostra come l'attività viene delegata per essere eseguita in un thread separato:
```cpp
// Funzione worker che viene eseguita in un thread in background
void Game_Thread_Worker(const std::wstring& mode, const std::wstring& folder, const std::wstring& nickname, const std::wstring& ip, const std::wstring& port, const std::wstring& password) {
    // La logica di iniezione viene delegata alla funzione "Initialize_Game" della libreria.
    Initialize_Game(mode, folder, nickname, ip, port, password);
}

// All'interno della funzione esportata `Launch_Game`, viene creato il thread:
try {
    std::thread(Game_Thread_Worker, mode_str, folder_str, nickname_str, ip_str, port_str, password_str).detach();
}
// ...
```

Questo dimostra che la **DLL** è, in sostanza, un'interfaccia API per la stessa funzionalità di base utilizzata dall'eseguibile.

### Come Compilare

Puoi compilare la `samp-injector.dll` dal codice sorgente. Se non desideri compilare, puoi scaricare le versioni precompilate nella sezione [Releases](https://github.com/spc-samp/samp-injector/releases).

#### Requisiti

- **Visual Studio:** Si raccomanda **Visual Studio 2022** o superiore con il carico di lavoro **"Sviluppo desktop con C++"** installato.
- **Git:** Per clonare il repository (o semplicemente scaricalo accedendo a questo link: [Download](https://github.com/spc-samp/samp-injector/archive/refs/heads/main.zip)).

#### Passaggi di Compilazione

1. **Clonare il Repository:**
   ```bash
   git clone https://github.com/spc-samp/samp-injector.git
   cd samp-injector
   ```
2. **Aprire la Soluzione:**
   Naviga nella cartella `dll` e apri il file di soluzione `.sln`:
   ```bash
   cd dll
   start samp-injector.sln
   ```
   Questo aprirà il progetto in **Visual Studio**.
3. **Configurare la Compilazione:**
   - In **Visual Studio**, verifica la configurazione della soluzione. Si raccomanda di utilizzare le modalità `Release` e `x86` **(32 bit)**. Nel contesto di **GTA:SA** e **SA-MP**/**OMP**, l'architettura **x86 (32 bit)** è obbligatoria.
4. **Compilare:**
   - Nel menu `Compilation`, fai clic su `Compile Solution` o su `Build samp-injector`.
   - In alternativa, puoi usare le scorciatoie:
      - `Ctrl + Shift + B` per compilare l'intera soluzione.
      - `Ctrl + B` (se configurato) per compilare il progetto attuale.
   - Se tutto è configurato correttamente, la libreria `samp-injector.dll` verrà generata nella directory `dll\Release` (o `dll\Debug`, a seconda della configurazione di **build**).

## Librerie

Le librerie sono i componenti fondamentali del **SA-MP Injector**, contenenti la logica centrale per la manipolazione dei processi, l'**iniezione di DLL** e la validazione dei parametri. Il principale vantaggio dell'uso di queste librerie è la facilità di inizializzazione e iniezione, generalmente attraverso una singola funzione (o chiamate con parametri specifici per i linguaggi di scripting).

### Panoramica

Il progetto è costruito su librerie che incapsulano le funzionalità critiche. Ciò consente ad altri progetti di integrare facilmente la capacità di avviare **GTA:SA** con i moduli **multiplayer** necessari.

### Elenco delle librerie

| Linguaggio    | Nome                       | Link alla libreria/Documentazione     |
| ------------- | -------------------------- | ------------------------------------- |
| C++           | **SA-MP Injector C++**     | [Vedi libreria](libraries/cpp)        |
| C             | **SA-MP Injector C**       | (Prossimamente)                       |
| C#            | **SA-MP Injector C#**      | (Prossimamente)                       |
| Java          | **SA-MP Injector Java**    | (Prossimamente)                       |
| Python        | **SA-MP Injector Python**  | (Prossimamente)                       |
| Go (Golang)   | **SA-MP Injector Go**      | (Prossimamente)                       |
| Rust          | **SA-MP Injector Rust**    | (Prossimamente)                       |
| Kotlin        | **SA-MP Injector Kotlin**  | (Prossimamente)                       |
| Scala         | **SA-MP Injector Scala**   | (Prossimamente)                       |
| Lua           | **SA-MP Injector Lua**     | (Prossimamente)                       |
| Ruby          | **SA-MP Injector Ruby**    | (Prossimamente)                       |
| Visual Basic  | **SA-MP Injector VB**      | (Prossimamente)                       |
| F#            | **SA-MP Injector F#**      | (Prossimamente)                       |
| Pascal        | **SA-MP Injector Pascal**  | (Prossimamente)                       |
| Delphi        | **SA-MP Injector Delphi**  | (Prossimamente)                       |
| PowerShell    | **SA-MP Injector PS**      | [Vedi libreria](libraries/powershell) |
| D (Dlang)     | **SA-MP Injector D**       | (Prossimamente)                       |
| Nim           | **SA-MP Injector Nim**     | (Prossimamente)                       |
| Zig           | **SA-MP Injector Zig**     | (Prossimamente)                       |
| V (VLang)     | **SA-MP Injector V**       | (Prossimamente)                       |
| Crystal       | **SA-MP Injector Crystal** | (Prossimamente)                       |
| Perl          | **SA-MP Injector Perl**    | (Prossimamente)                       |
| Racket (Lisp) | **SA-MP Injector Racket**  | (Prossimamente)                       |
| Haskell       | **SA-MP Injector Haskell** | (Prossimamente)                       |
| OCaml         | **SA-MP Injector OCaml**   | (Prossimamente)                       |

> [!TIP]
> La documentazione dettagliata per ogni libreria sarà disponibile nella sua **rispettiva directory**.

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