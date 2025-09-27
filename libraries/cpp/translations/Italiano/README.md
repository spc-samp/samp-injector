# SA-MP Injector C++

<div align="center">

![C++](https://img.shields.io/badge/C%2B%2B-14%2F17%2F20-00599C?style=for-the-badge&logo=cplusplus)
![Platform](https://img.shields.io/badge/Platform-Windows-blue?style=for-the-badge&logo=windows&logoColor=white)
![Architecture](https://img.shields.io/badge/Architecture-x86%20(32--bit)-lightgrey?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)

**Una libreria C++ per avviare e automatizzare la connessione di client SA-MP e OMP a server, tramite iniezione di DLL.**

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

- [SA-MP Injector C++](#sa-mp-injector-c)
  - [Lingue](#lingue)
  - [Indice](#indice)
  - [Panoramica e Scopo](#panoramica-e-scopo)
  - [Principi di Progettazione](#principi-di-progettazione)
    - [Completamente `Header-Only`](#completamente-header-only)
    - [Gestione Sicura delle Risorse (RAII)](#gestione-sicura-delle-risorse-raii)
    - [Robustezza e Controllo degli Errori](#robustezza-e-controllo-degli-errori)
    - [Flessibilità degli Standard C++](#flessibilità-degli-standard-c)
  - [Ambiente Richiesto](#ambiente-richiesto)
    - [Per lo Sviluppo](#per-lo-sviluppo)
    - [Per l'Esecuzione](#per-lesecuzione)
  - [Avvio Rapido](#avvio-rapido)
    - [Integrazione nel Progetto](#integrazione-nel-progetto)
    - [Esempio di Utilizzo Semplificato](#esempio-di-utilizzo-semplificato)
  - [Struttura della Libreria](#struttura-della-libreria)
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
  - [Il Processo Dettagliato di Iniezione](#il-processo-dettagliato-di-iniezione)
    - [1. Richiesta di Inizializzazione](#1-richiesta-di-inizializzazione)
    - [2. Preparazione dell'Ambiente](#2-preparazione-dellambiente)
    - [3. Verifica di Integrità e Parametri](#3-verifica-di-integrità-e-parametri)
    - [4. Preparazione degli Argomenti per il Gioco](#4-preparazione-degli-argomenti-per-il-gioco)
    - [5. Inizializzazione del Processo del Gioco (Sospeso)](#5-inizializzazione-del-processo-del-gioco-sospeso)
    - [6. Iniezione della Libreria SA-MP (`samp.dll`)](#6-iniezione-della-libreria-sa-mp-sampdll)
    - [7. Iniezione della Libreria OMP (`omp-client.dll`) - Condizionale](#7-iniezione-della-libreria-omp-omp-clientdll---condizionale)
    - [8. Attivazione del Gioco](#8-attivazione-del-gioco)
  - [Diagnostica di Errori e Guasti](#diagnostica-di-errori-e-guasti)
    - [Errori di Convalida dell'Input](#errori-di-convalida-dellinput)
      - [Nome Utente Non Valido](#nome-utente-non-valido)
      - [Porta di Connessione Non Valida](#porta-di-connessione-non-valida)
      - [Risorse Essenziali Mancanti](#risorse-essenziali-mancanti)
    - [Errori nella Gestione del Processo](#errori-nella-gestione-del-processo)
      - [Difficoltà nell'Avviare il Processo del Gioco](#difficoltà-nellavviare-il-processo-del-gioco)
    - [Problemi nell'Iniezione della DLL](#problemi-nelliniezione-della-dll)
      - [Impossibile Trovare `LoadLibraryW`](#impossibile-trovare-loadlibraryw)
      - [Fallimento nell'Allocazione di Memoria Remota](#fallimento-nellallocazione-di-memoria-remota)
      - [Incapacità di Scrivere Dati nel Processo](#incapacità-di-scrivere-dati-nel-processo)
      - [Fallimento nella Creazione del Thread di Iniezione](#fallimento-nella-creazione-del-thread-di-iniezione)
      - [Timeout Scaduto o Errore nell'Attesa dell'Iniezione](#timeout-scaduto-o-errore-nellattesa-delliniezione)
      - [Fallimento Interno nell'Iniezione della DLL](#fallimento-interno-nelliniezione-della-dll)
    - [Difficoltà nel Riprendere l'Esecuzione del Gioco](#difficoltà-nel-riprendere-lesecuzione-del-gioco)
  - [Licenza](#licenza)
    - [Termini e Condizioni d'Uso](#termini-e-condizioni-duso)
      - [1. Permessi Concessi](#1-permessi-concessi)
      - [2. Condizioni Obbligatorie](#2-condizioni-obbligatorie)
      - [3. Diritti d'Autore](#3-diritti-dautore)
      - [4. Esclusione di Garanzia e Limitazione di Responsabilità](#4-esclusione-di-garanzia-e-limitazione-di-responsabilità)

## Panoramica e Scopo

**SA-MP Injector C++** è una libreria C++ compatta e di facile integrazione, progettata per automatizzare il processo di inizializzazione e connessione a server di San Andreas Multiplayer (SA-MP) e Open Multiplayer (OMP). A differenza dell'avvio diretto di `gta_sa.exe`, questa soluzione carica programmaticamente le librerie `samp.dll` o `omp-client.dll` nel processo del gioco Grand Theft Auto: San Andreas in modo controllato.

Il suo obiettivo principale è consentire agli sviluppatori C++ di creare `launcher` personalizzati, strumenti di gestione della community o utility che necessitano di avviare GTA:SA con parametri di connessione predefiniti (come nome utente, indirizzo IP, porta e password), offrendo un'esperienza utente fluida e automatizzata.

## Principi di Progettazione

L'architettura di **SA-MP Injector C++** si basa su principi di progettazione moderni, concentrandosi su sicurezza, efficienza e facilità d'uso.

### Completamente `Header-Only`

Questa libreria è distribuita esclusivamente tramite file di intestazione (`.hpp`). Ciò semplifica drasticamente l'integrazione nei progetti C++, eliminando la necessità di compilare librerie separate, configurare `linker` o gestire dipendenze binarie.
- **Integrazione Istantanea:** Basta includere gli `header` pertinenti.
- **Ottimizzazione Profonda:** Il compilatore può eseguire `inlining` aggressivo e ottimizzazioni di `link-time` che si traducono in un codice finale più compatto e veloce.

### Gestione Sicura delle Risorse (RAII)

La libreria utilizza ampiamente il pattern **RAII (Resource Acquisition Is Initialization)**. Le risorse critiche del sistema, come gli `handle` di processi e `thread` di Windows, sono incapsulate da `std::unique_ptr` con `deleter` personalizzati. Ciò garantisce che, indipendentemente dal flusso di esecuzione o dal verificarsi di eccezioni, le risorse vengano sempre rilasciate correttamente, prevenendo perdite e migliorando la stabilità dell'applicazione.

### Robustezza e Controllo degli Errori

Ogni fase critica dell'iniezione è preceduta da convalide rigorose e seguita da controlli degli errori dell'API di Windows. Messaggi di errore dettagliati vengono forniti all'utente finale tramite finestre di dialogo, con descrizioni del sistema (`GetLastError()`) quando possibile. Questo approccio riduce al minimo la possibilità di comportamenti indefiniti e offre una diagnosi chiara in caso di fallimento.

### Flessibilità degli Standard C++

La libreria è stata costruita per essere compatibile con diversi standard C++, da C++14 a C++20. Ciò è ottenuto tramite macro condizionali che consentono l'uso di funzionalità moderne (come `std::string_view`, `std::filesystem` e `std::optional` da C++17+) quando disponibili, mantenendo un `fallback` a costrutti equivalenti in C++14. Questo approccio garantisce un'ampia compatibilità senza sacrificare la modernità.

## Ambiente Richiesto

### Per lo Sviluppo

- **Compilatore C++:** Compatibile con **C++14 o superiore**.
   - Microsoft Visual C++ (Visual Studio 2015, 2017, 2019, 2022)
   - GCC (versione 5 o successiva)
   - Clang (versione 3.6 o successiva)
- **Sistema Operativo:** **Windows**.
- **Windows SDK:** Necessario per l'accesso alle API del sistema operativo.
- **Architettura di Compilazione:** **x86 (32-bit)**. Questo è un requisito stretto, poiché `gta_sa.exe` e le DLL SA-MP/OMP operano esclusivamente su questa architettura.

### Per l'Esecuzione

- **Sistema Operativo:** Qualsiasi versione moderna di **Windows** compatibile con il binario compilato.
- **Grand Theft Auto: San Andreas (GTA:SA):** È obbligatoria un'installazione valida del gioco.
- **DLL del Client SA-MP o OMP:** I file `samp.dll` o `omp-client.dll` devono essere presenti nella directory principale del gioco, corrispondendo al tipo di iniezione desiderato.

## Avvio Rapido

La natura `header-only` della libreria facilita la sua incorporazione in qualsiasi progetto C++.

### Integrazione nel Progetto

1. **Scarica gli Header:** Ottieni i file `.hpp` della libreria (clonando il repository o scaricandoli direttamente).
2. **Organizza i File:** Si consiglia di creare una sottocartella nel tuo progetto per gli `header` della libreria, ad esempio, `MioProgetto/libraries/samp-injector/`.
3. **Definisci l'Architettura:** Configura il tuo progetto per compilare per l'architettura **x86 (32-bit)**.

```cpp
// Esempio di struttura delle directory
MioProgetto/
├── src/
│   └── main.cpp
├── libraries/
│   └── samp-injector/
│       ├── constants.hpp
│       ├── error_utils.hpp
│       ├── injector.hpp // L'header principale da includere
│       └── ... (altri header)
└── built/ (la tua directory di output)
```

### Esempio di Utilizzo Semplificato

Per automatizzare la connessione a un server, è sufficiente invocare la funzione `Initialize_Game` e fornire i dettagli.

```cpp
#include <iostream>
#include <string>
//
#include "samp-launcher/injector.hpp" // Includi l'header principale

int main() {
    // Parametri per l'inizializzazione del gioco e la connessione
    std::wstring inject_type = L"samp"; // O L"omp" per Open Multiplayer
    std::wstring game_folder = L"C:\\Games\\GTA San Andreas"; // Percorso completo della cartella di GTA:SA
    std::wstring nickname = L"Nome";
    std::wstring ip = L"127.0.0.1";
    std::wstring port = L"7777";
    std::wstring password = L""; // Lascia vuoto se non c'è password

    // La chiamata principale per avviare il gioco e iniettare la DLL
    Initialize_Game(inject_type, game_folder, nickname, ip, port, password);

    // In caso di fallimento, viene visualizzata automaticamente una finestra di messaggio di errore di Windows.

    return 0;
}
```

## Struttura della Libreria

La libreria è attentamente modularizzata in diversi file di intestazione, ognuno con responsabilità ben definite, facilitando l'organizzazione, la manutenzione e la riutilizzabilità.

### 1. `constants.hpp`

Questo file è il **repository centrale** della libreria, fungendo da repository centralizzato di tutti i valori fissi e immutabili che dettano il comportamento e l'interoperabilità di **SA-MP Injector C++**. La sua organizzazione per categorie logiche promuove non solo la chiarezza e la leggibilità del codice, ma facilita anche la manutenzione e garantisce una coerenza rigorosa in tutto l'ecosistema della libreria.

Ogni costante è definita con `CONSTEXPR_VAR`, che si espande in `inline constexpr` (per C++17+) o `static constexpr` (per C++14), assicurando che questi valori siano valutati in fase di compilazione, ottimizzando le prestazioni e la sicurezza dei tipi.

L'organizzazione delle costanti per categoria facilita la comprensione del loro scopo:

- **Costanti Relative al Gioco (`Game Related Constants`)**
   - `MIN_PORT`: Un `int` che definisce il numero di porta valido più basso per la connessione a un server (valore: `1`).
   - `MAX_PORT`: Un `int` che stabilisce il numero di porta valido più alto per la connessione a un server (valore: `65535`).
   - `MAX_NICKNAME_LENGTH`: Un `int` che specifica la lunghezza massima consentita per il nickname del giocatore (valore: `23` caratteri), un limite imposto dalle specifiche del client SA-MP/OMP.

- **Nomi di File Essenziali (`File Names`)**
   - `SAMP_DLL_NAME`: Un `const wchar_t*` che contiene il nome del file della libreria principale del client SA-MP (valore: `L"samp.dll"`). Essenziale per l'iniezione del client classico.
   - `OMP_DLL_NAME`: Un `const wchar_t*` che contiene il nome del file della libreria del client Open Multiplayer (valore: `L"omp-client.dll"`). Utilizzato specificamente quando l'iniezione è di tipo OMP.
   - `GAME_EXE_NAME`: Un `const wchar_t*` che memorizza il nome del file eseguibile del gioco base Grand Theft Auto: San Andreas (valore: `L"gta_sa.exe"`). Il target principale dell'iniezione.

- **API e Funzioni di Sistema (`System Libraries and Functions`)**
   - `KERNEL32_DLL`: Un `const wchar_t*` che definisce il nome della libreria di sistema di Windows (`L"kernel32.dll"`). Questa DLL è vitale, poiché ospita le funzioni di manipolazione dei processi e della memoria che l'iniettore utilizza. L'uso di `wchar_t` garantisce la compatibilità con le funzioni API che manipolano caratteri larghi, come `GetModuleHandleW`.
   - `LOAD_LIBRARY_FUNC`: Un `const char*` con il nome della funzione per caricare dinamicamente una DLL (valore: `"LoadLibraryW"`). Sebbene la libreria operi principalmente con caratteri larghi, la funzione `GetProcAddress` dell'API di Windows richiede un nome di funzione in formato ANSI (`char*`).

- **Argomenti della Riga di Comando (`Command Line Arguments`)**
   - Queste costanti definiscono i prefissi per gli argomenti che vengono passati a `gta_sa.exe` per configurare la connessione del client. Sono fornite in `Wide Character` (`const wchar_t*`) per la compatibilità con `CreateProcessW`.
      - `CMD_ARG_CONFIG`: Argomento per le impostazioni generali (valore: `L"-c"`).
      - `CMD_ARG_NICKNAME`: Argomento per il nickname del giocatore (valore: `L"-n"`).
      - `CMD_ARG_HOST`: Argomento per l'indirizzo IP del server (valore: `L"-h"`).
      - `CMD_ARG_PORT`: Argomento per la porta del server (valore: `L"-p"`).
      - `CMD_ARG_PASSWORD`: Argomento per la password del server (valore: `L"-z"`). Utilizzato solo se viene fornita una password.

- **Identificatori del Tipo di Iniezione (`Injection types as strings`)**
   - `INJECT_TYPE_SAMP`: Un `const wchar_t*` per la rappresentazione in stringa del tipo di iniezione SA-MP (valore: `L"samp"`).
   - `INJECT_TYPE_OMP`: Un `const wchar_t*` per la rappresentazione in stringa del tipo di iniezione OMP (valore: `L"omp"`).

- **Titoli per i Messaggi di Errore (`Error message titles`)**
   - `ERROR_TITLE_SAMP`: Un `const wchar_t*` che definisce il titolo predefinito per le finestre di dialogo di errore relative a fallimenti di SA-MP (valore: `L"SA-MP Injector Error - SPC"`).
   - `ERROR_TITLE_OMP`: Un `const wchar_t*` che definisce il titolo predefinito per le finestre di dialogo di errore relative a fallimenti di OMP (valore: `L"OMP Injector Error - SPC"`).

- **Flag di Creazione del Processo (`Process creation`)**
   - `PROCESS_CREATION_FLAGS`: Un `DWORD` che incapsula i flag passati a `CreateProcessW`. Fondamentalmente, include `CREATE_SUSPENDED` (`0x00000004`), che avvia il processo del gioco in uno stato sospeso, e `DETACHED_PROCESS` (`0x00000008`), che scollega il nuovo processo dalla console del processo padre.

- **Timeout (`Timeouts`)**
   - `DLL_INJECTION_TIMEOUT_MS`: Un `DWORD` che specifica il tempo massimo (in millisecondi) che la libreria attenderà per il completamento del `thread` remoto responsabile dell'iniezione della DLL (valore: `10000ms`, o 10 secondi).

- **Flag di Allocazione della Memoria (`Memory allocation`)**
   - Queste costanti sono utilizzate per le chiamate API di manipolazione della memoria, come `VirtualAllocEx` e `VirtualProtect`.
      - `MEM_COMMIT`: Un `DWORD` che riserva pagine nella memoria virtuale e le "committa" (alloca memoria fisica) (valore: `0x1000`).
      - `MEM_RESERVE`: Un `DWORD` che riserva solo un intervallo di spazio di indirizzi virtuale per un uso successivo (valore: `0x2000`).
      - `MEM_RELEASE`: Un `DWORD` che decommitta e libera una regione di pagine (valore: `0x8000`).
      - `MEMORY_ALLOCATION_TYPE`: Una combinazione di `MEM_COMMIT` e `MEM_RESERVE`, utilizzata per allocare la memoria iniziale per il percorso della DLL nel processo remoto.
      - `MEMORY_PROTECTION`: Un `DWORD` che definisce i permessi di protezione della memoria (valore: `PAGE_READWRITE` o `0x04` nell'API di Windows), consentendo la lettura e la scrittura nella memoria allocata.

### 2. `types.hpp`

Questo file conciso introduce un `enum class` per tipizzare le diverse modalità di iniezione. L'uso di un tipo enumerato, anziché di stringhe letterali, aumenta la sicurezza del codice, previene errori di battitura e migliora la leggibilità.

- **`Inject_Type`:** Un `enum class` con due membri: `SAMP` e `OMP`, che rappresentano i tipi di client da iniettare.

```cpp
// Esempio di types.hpp
namespace Types {
    enum class Inject_Type {
        SAMP, // Indica iniezione per il client SA-MP
        OMP // Indica iniezione per il client Open Multiplayer
    };
}
```

### 3. `version.hpp`

Agendo come un adattatore di compatibilità, questo header rileva dinamicamente lo standard C++ in uso dal compilatore. Definisce macro condizionali (`SAMP_INJECTOR_CXX_14`, `SAMP_INJECTOR_CXX_MODERN`) che guidano la libreria a impiegare le funzionalità C++ più avanzate (come `std::string_view` o `std::filesystem`) quando disponibili, garantendo al contempo la piena funzionalità in ambienti C++14.

- **`SAMP_INJECTOR_CXX_14`:** Definita se lo standard C++ è C++14.
- **`SAMP_INJECTOR_CXX_MODERN`:** Definita per C++17 o superiore, abilitando funzionalità del linguaggio più recenti.
- **`SAMP_INJECTOR_NODISCARD`:** Adatta l'attributo `[[nodiscard]]` per le versioni di C++ che lo supportano, incoraggiando il controllo dei valori di ritorno.

```cpp
// Esempio di estratto rilevante di version.hpp
#if (defined(_MSC_VER) && _MSVC_LANG >= 201703L) || __cplusplus >= 201703L
    #define SAMP_INJECTOR_CXX_MODERN // Abilita funzionalità moderne di C++17+
#endif

#if defined(SAMP_INJECTOR_CXX_MODERN)
    #define SAMP_INJECTOR_NODISCARD [[nodiscard]] // Usa l'attributo nodiscard di C++17
#elif defined(SAMP_INJECTOR_CXX_14)
    #define SAMP_INJECTOR_NODISCARD // Per C++14, l'attributo è disattivato
#endif
```

### 4. `error_utils.hpp`

Questa utility è dedicata alla gestione e presentazione del feedback degli errori. Astrae i meccanismi di Windows per recuperare i messaggi di errore del sistema e offre un'interfaccia unificata per notificare all'utente i problemi.

- **`Get_System_Error_Message`:** Traduce un codice di errore di Windows (`GetLastError()`) in una `std::wstring` leggibile, cruciale per una diagnosi precisa.
- **`Show_Error`:** Presenta una finestra di dialogo (`MessageBoxW`) contenente il messaggio di errore fornito, con un titolo specifico per SA-MP o OMP, garantendo una comunicazione chiara con l'utente.

```cpp
// Esempio di estratto rilevante di error_utils.hpp
namespace Error_Utils {
    SAMP_INJECTOR_NODISCARD
    inline std::wstring Get_System_Error_Message(DWORD error_code) {
        if (error_code == 0)
            return L"No error occurred.";
        
        // ... Logica per formattare il messaggio di sistema ...
    }

    inline void Show_Error(std::wstring_view message, Types::Inject_Type inject_type) {
        const std::wstring title = (inject_type == Types::Inject_Type::SAMP) ? Constants::ERROR_TITLE_SAMP : Constants::ERROR_TITLE_OMP;
        MessageBoxW(nullptr, message.data(), title.c_str(), MB_OK | MB_ICONERROR);
    }
}
```

### 5. `validation.hpp`

Agendo come prima linea di robustezza della libreria, questo header fornisce routine rigorose per verificare la validità dei dati di input e la presenza dei file necessari. Queste verifiche vengono eseguite prima di qualsiasi interazione a basso livello con il sistema, mitigando i rischi di `runtime` e fornendo un feedback proattivo.

- **`Validate_Port`:** Valida se la stringa della porta rappresenta un numero intero e se questo si trova nell'intervallo configurato (da `MIN_PORT` a `MAX_PORT`).
- **`Validate_Nickname`:** Verifica che il nickname non sia vuoto e che la sua lunghezza non superi `MAX_NICKNAME_LENGTH`.
- **`Validate_Files`:** Conferma l'esistenza fisica di `gta_sa.exe`, `samp.dll` e, condizionatamente per l'iniezione OMP, `omp-client.dll`. L'implementazione si adatta a `std::filesystem` (C++17+) o `GetFileAttributesW` (C++14).

```cpp
// Esempio di estratto rilevante di validation.hpp
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
        
        // ... Altre verifiche di file ...
        return true;
    }
}
```

### 6. `resource_handle.hpp`

Implementa una strategia elegante e sicura per la gestione delle risorse del sistema operativo, come gli `HANDLE` di Windows. Utilizzando il principio RAII, garantisce che tutte le risorse allocate vengano rilasciate correttamente, prevenendo perdite e rafforzando la stabilità dell'applicazione.

- **`Unique_Resource`:** Un `alias template` che adatta `std::unique_ptr` per funzionare con `deleter` personalizzati, consentendo la gestione di qualsiasi tipo di risorsa che necessiti di una funzione di rilascio specifica.
- **`Make_Unique_Handle`:** Una comoda funzione `factory` che costruisce e restituisce un `Unique_Resource` preconfigurato per gli `HANDLE` di Windows. Il `deleter` associato invoca `CloseHandle` automaticamente quando `Unique_Resource` esce dallo scope, garantendo il rilascio immediato della risorsa.

```cpp
// Esempio di estratto rilevante di resource_handle.hpp
namespace Resource_Handle {
    // Un std::unique_ptr personalizzato per gestire le risorse di sistema.
    template<typename T, typename Deleter>
    using Unique_Resource = std::unique_ptr<std::remove_pointer_t<T>, Deleter>;

    // Crea un Unique_Resource per un HANDLE, con un deleter che chiama CloseHandle.
    template<typename T>
    inline auto Make_Unique_Handle(T handle) {
        return Unique_Resource<T, std::function<void(T)>>(handle, [](T h) {
            if (h && h != INVALID_HANDLE_VALUE) // Assicura che l'handle sia valido prima di chiuderlo
                CloseHandle(h);
        });
    }
}
```

### 7. `privileges.hpp`

Questo componente è responsabile della configurazione dell'ambiente di sicurezza del processo dell'applicazione. Contiene la funzionalità per elevare i privilegi, in particolare abilitando il privilegio di debug (`SE_DEBUG_NAME`), che è un requisito fondamentale affinché la libreria possa eseguire operazioni di iniezione di DLL in processi esterni di Windows.

- **`Enable_Debug_Privilege`:** Questa funzione tenta di acquisire e attivare il privilegio `SE_DEBUG_NAME` per il processo in esecuzione. È un passaggio iniziale cruciale per concedere all'applicazione i permessi necessari per manipolare altri processi, come allocare memoria e creare `thread` remoti. Restituisce `true` in caso di successo.

```cpp
// Esempio di estratto rilevante di privileges.hpp
namespace Privileges {
    inline bool Enable_Debug_Privilege() {
        HANDLE token_handle;

        // Tenta di aprire il token del processo corrente per regolare i privilegi
        if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &token_handle))
            return false;

        auto handle_guard = Resource_Handle::Make_Unique_Handle(token_handle); // Gestione sicura dell'handle

        TOKEN_PRIVILEGES tp;
        LUID luid;

        // Cerca il valore LUID per il privilegio SE_DEBUG_NAME
        if (!LookupPrivilegeValue(nullptr, SE_DEBUG_NAME, &luid))
            return false;
        
        tp.PrivilegeCount = 1;
        tp.Privileges[0].Luid = luid;
        tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED; // Abilita il privilegio

        // Regola i privilegi del processo
        if (!AdjustTokenPrivileges(token_handle, FALSE, &tp, sizeof(TOKEN_PRIVILEGES), nullptr, nullptr))
            return false;

        return GetLastError() == ERROR_SUCCESS; // Restituisce true se l'operazione ha avuto successo (nessun errore in sospeso)
    }
}
```

### 8. `process.hpp`

Questo è uno dei componenti più critici della libreria, contenente l'implementazione a basso livello per interagire con i processi di Windows. Incapsula le complesse operazioni di creazione del processo di gioco, allocazione della memoria, scrittura dei dati e la tecnica di iniezione di DLL tramite la creazione di `thread` remoti.

- **`Process_Info` struct:** Una struttura interna che memorizza gli `Unique_Resource` per l' `HANDLE` del processo (`process_handle`) e l' `HANDLE` del `thread` principale (`thread_handle`) del gioco. Include un metodo `Resume()` per riattivare il `thread` principale del gioco quando l'iniezione è completa.
- **`Injection_Status` enum class:** Definisce un elenco dettagliato dei possibili risultati per l'operazione di iniezione di DLL, consentendo una diagnosi precisa dei fallimenti.
- **`Create_Game_Process`:**
   - Utilizza la funzione `CreateProcessW` dell'API di Windows per avviare l'eseguibile `gta_sa.exe`.
   - È fondamentale che il processo venga creato con il flag `CREATE_SUSPENDED` (incluso in `Constants::PROCESS_CREATION_FLAGS`). Ciò garantisce che il gioco venga messo in pausa immediatamente dopo la sua creazione, prima che qualsiasi codice venga eseguito, consentendo all'iniezione della DLL di avvenire in uno stato sicuro.
   - Restituisce un `std::optional<Process_Info>` (per C++17+) o un `std::unique_ptr<Process_Info>` (per C++14), contenente gli `handle` incapsulati del processo e del `thread`.
- **`Inject_DLL`:**
   - Implementa la tecnica standard di iniezione di DLL tramite `CreateRemoteThread`:
      1. **Ottenimento dell'Indirizzo:** Utilizzando le costanti di `constants.hpp`, individua l'indirizzo della funzione `LoadLibraryW` (di `kernel32.dll`), che Windows utilizza per caricare dinamicamente le librerie.
      2. **Allocazione della Memoria:** `VirtualAllocEx` viene utilizzata per riservare un blocco di memoria virtuale all'interno del processo del gioco (`gta_sa.exe`). Questo blocco è dimensionato per contenere il percorso completo della DLL da iniettare.
      3. **Scrittura del Percorso:** Il percorso della DLL (es. `L"C:\\percorso\\per\\samp.dll"`) viene quindi copiato nella memoria allocata remotamente nel processo del gioco tramite `WriteProcessMemory`.
      4. **Creazione del Thread Remoto:** `CreateRemoteThread` avvia un nuovo `thread` nel contesto del processo del gioco. Il punto di ingresso di questo `thread` è l'indirizzo di `LoadLibraryW` e l'argomento passato è l'indirizzo della stringa del percorso della DLL che abbiamo appena scritto.
      5. **Monitoraggio:** L'esecuzione del `thread` remoto è monitorata da `WaitForSingleObject` fino al suo completamento o al raggiungimento di `DLL_INJECTION_TIMEOUT_MS`.
      6. **Verifica del Successo:** `GetExitCodeThread` viene utilizzata per verificare il valore di ritorno del `thread` remoto. Se `LoadLibraryW` ha avuto successo, restituirà l'indirizzo di base della DLL caricata (un valore diverso da zero).
      7. **Pulizia:** La memoria allocata nel processo remoto viene liberata da `VirtualFreeEx`.
   - Restituisce un `Injection_Status` che indica il successo o il tipo specifico di fallimento dell'iniezione.

```cpp
// Esempio di estratto rilevante di process.hpp
class Process {
public:
    struct Process_Info {
        Resource_Handle::Unique_Resource<HANDLE, std::function<void(HANDLE)>> process_handle; // Handle del processo con gestione RAII
        Resource_Handle::Unique_Resource<HANDLE, std::function<void(HANDLE)>> thread_handle; // Handle del thread con gestione RAII

        bool Resume() { // Riprende l'esecuzione del thread principale del gioco
            return thread_handle && ResumeThread(thread_handle.get()) != static_cast<DWORD>(-1);
        }
    };
    
    enum class Injection_Status { // Codici di stato dettagliati per l'iniezione di DLL
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

    // Crea il processo del gioco in stato sospeso
    std::optional<Process_Info> Create_Game_Process(const std::wstring& game_path, std::wstring& command_args, const std::wstring& working_dir) {
        // ... Logica di CreateProcessW con CREATE_SUSPENDED ...
    }
    
    SAMP_INJECTOR_NODISCARD // Assicura che il valore di ritorno venga utilizzato
    Injection_Status Inject_DLL(HANDLE process, const std::wstring& DLL_path) {
        static const LPVOID load_library_addr = reinterpret_cast<LPVOID>(GetProcAddress(GetModuleHandleW(Constants::KERNEL32_DLL), Constants::LOAD_LIBRARY_FUNC));

        if (!load_library_addr)
            return Injection_Status::LOADLIBRARY_ADDRESS_FAILED;

        LPVOID remote_memory = VirtualAllocEx(process, nullptr, (DLL_path.length() + 1) * sizeof(wchar_t), Constants::MEMORY_ALLOCATION_TYPE, Constants::MEMORY_PROTECTION);

        if (!remote_memory)
            return Injection_Status::ALLOCATION_FAILED;

        auto memory_guard = Resource_Handle::Unique_Resource<LPVOID, std::function<void(LPVOID)>>(remote_memory, [process](LPVOID ptr) {
            if (ptr)
                VirtualFreeEx(process, ptr, 0, MEM_RELEASE); // Libera la memoria nel processo remoto
        });

        if (!WriteProcessMemory(process, remote_memory, DLL_path.c_str(), (DLL_path.length() + 1) * sizeof(wchar_t), nullptr))
            return Injection_Status::WRITE_FAILED;

        HANDLE remote_thread = CreateRemoteThread(process, nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(load_library_addr), remote_memory, 0, nullptr);

        if (!remote_thread)
            return Injection_Status::THREAD_CREATION_FAILED;

        auto thread_guard = Resource_Handle::Make_Unique_Handle(remote_thread); // Gestione sicura dell'handle del thread remoto

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

Questo header definisce la classe `Injector_Core`, che funge da centro di comando della libreria. Orchestra la sequenza logica delle operazioni di iniezione, collegando i moduli di convalida dell'input, gestione dei privilegi e manipolazione dei processi. È qui che viene definito il flusso di lavoro completo dell'iniezione.

- **`Injector_Core`:** Il costruttore di questa classe è il punto in cui viene chiamato `Privileges::Enable_Debug_Privilege()`. Ciò garantisce che il processo dell'applicazione possieda i privilegi necessari per eseguire operazioni di iniezione di DLL prima che venga eseguita qualsiasi altra logica critica.
- **`Initialize_Game`:**
   1. **Convalida Completa:** Inizia chiamando le funzioni di convalida (`Validation::Validate_Port`, `Validation::Validate_Nickname`, `Validation::Validate_Files`) per assicurare che tutti i parametri e le risorse essenziali siano in ordine. Se una qualsiasi convalida fallisce, viene immediatamente segnalato un errore.
   2. **Preparazione degli Argomenti:** Costruisce la riga di comando completa (`std::wstring`) che sarà passata a `gta_sa.exe`, incorporando il nickname, l'IP, la porta e la password forniti.
   3. **Creazione del Processo Sospeso:** Invoca `Process::Create_Game_Process` per avviare `gta_sa.exe` in uno stato sospeso, ottenendo gli `handle` del processo e del `thread` principale.
   4. **Iniezione di `samp.dll`:** Chiama `Inject_DLL_With_Status_Check` per iniettare `samp.dll` nel processo del gioco. Questa funzione wrapper è anche responsabile dell'interpretazione dell' `Injection_Status` restituito e della visualizzazione di messaggi di errore informativi.
   5. **Iniezione Condizionale di `omp-client.dll`:** Se `inject_type` è `Types::Inject_Type::OMP`, `omp-client.dll` viene quindi iniettata allo stesso modo di `samp.dll`.
   6. **Ripresa del Gioco:** Dopo tutte le iniezioni riuscite, viene chiamata `process_info.Resume()` per consentire al `thread` principale del gioco di continuare la sua esecuzione.
   7. **Gestione degli Errori nel Ciclo:** Qualsiasi fallimento in una di queste fasi critiche comporterà una chiamata a `Error_Utils::Show_Error`, fornendo un feedback chiaro all'utente e garantendo che il processo venga terminato correttamente (gli `handle` vengono liberati automaticamente dagli `Unique_Resource`).
- **`Build_Command_Args`:** Una funzione ausiliaria che organizza e concatena gli argomenti della riga di comando, aggiungendo virgolette dove necessario per i parametri che contengono spazi.
- **`Inject_DLL_With_Status_Check`:** Una funzione privata che agisce come un involucro per `Process::Inject_DLL`. Mappa i diversi `Injection_Status` a messaggi di errore comprensibili, facilitando la gestione degli errori e la comunicazione con l'utente.

```cpp
// Esempio di estratto rilevante di injector_core.hpp
namespace Injector {
    class Injector_Core {
    public:
        Injector_Core() { // Il costruttore abilita il privilegio di debug
            Privileges::Enable_Debug_Privilege();
        }

        bool Initialize_Game(Types::Inject_Type inject_type, std::wstring_view folder, std::wstring_view nickname, std::wstring_view ip, std::wstring_view port, std::wstring_view password) {
            std::wstring error_message;

            // Sequenza di convalide dell'input
            if (!Validation::Validate_Port(port, error_message))
                return (Error_Utils::Show_Error(error_message, inject_type), false);
            // ... altre convalide ...

            // Costruisce gli argomenti della riga di comando
            std::wstring args = Build_Command_Args({
                Command_Arg{Constants::CMD_ARG_NICKNAME, std::wstring(nickname)},
                // ... altri argomenti ...
            });

            Process process_core;
            // Crea il processo del gioco in stato sospeso
            auto process_info_opt = process_core.Create_Game_Process(game_path, args, std::wstring(folder));

            if (!process_info_opt)
                return false;

            auto& process_info = *process_info_opt;

            // Inietta samp.dll e, condizionatamente, omp-client.dll
            if (!Inject_DLL_With_Status_Check(process_core, process_info.process_handle.get(), Constants::SAMP_DLL_NAME, samp_DLL_path.wstring(), inject_type))
                return false;
            
            if (inject_type == Types::Inject_Type::OMP) {
                if (!Inject_DLL_With_Status_Check(process_core, process_info.process_handle.get(), Constants::OMP_DLL_NAME, omp_DLL_path.wstring(), inject_type))
                    return false;
            }
            
            // Riprende il thread principale del gioco
            if (!process_info.Resume())
                return (Error_Utils::Show_Error(L"Failed to resume the game process thread: " + Error_Utils::Get_System_Error_Message(GetLastError()), inject_type), false);

            return true;
        }
    };
}
```

### 10. `injector.hpp`

Questo header agisce come la facciata (`Facade`) principale della libreria, offrendo un punto di ingresso semplificato per qualsiasi applicazione che desideri utilizzare la funzionalità di iniezione. Astrae la complessità interna di `Injector_Core` in un'unica e comoda funzione.

- **`Initialize_Game`:**
   - Questa funzione statica è l'interfaccia pubblica della libreria.
   - Per prima cosa, convalida `inject_type_str` (se è `L"samp"` o `L"omp"`) e la converte nell' `enum class Types::Inject_Type`. In caso di stringa non valida, visualizza un errore e termina.
   - Successivamente, crea un'istanza di `Injector::Injector_Core`.
   - Infine, delega l'esecuzione della logica principale a `Injector_Core::Initialize_Game`, che è dove viene orchestrato l'intero processo di convalida, creazione del processo e iniezione della DLL.

```cpp
// Esempio di estratto rilevante di injector.hpp
// L'interfaccia pubblica per avviare il gioco
#if defined(SAMP_INJECTOR_CXX_MODERN)
inline bool Initialize_Game(std::wstring_view inject_type, std::wstring_view folder, std::wstring_view nickname, std::wstring_view ip, std::wstring_view port, std::wstring_view password) {
#elif defined(SAMP_INJECTOR_CXX_14)
inline bool Initialize_Game(const std::wstring& inject_type, const std::wstring& folder, const std::wstring& nickname, const std::wstring& ip, const std::wstring& port, const std::wstring& password) {
#endif
    Types::Inject_Type type;

    // Converte la stringa del tipo di iniezione nell'enum corrispondente
    if (inject_type == Constants::INJECT_TYPE_SAMP)
        type = Types::Inject_Type::SAMP;
    else if (inject_type == Constants::INJECT_TYPE_OMP)
        type = Types::Inject_Type::OMP;
    else
        // Visualizza un errore se il tipo di iniezione non è valido
        return (Error_Utils::Show_Error(L"Modalità di iniezione non valida. Usa 'samp' o 'omp'.", Types::Inject_Type::SAMP), false);

    Injector::Injector_Core injector; // Crea l'istanza del nucleo dell'iniettore

    // Delega la logica principale a Injector_Core
    return injector.Initialize_Game(type, folder, nickname, ip, port, password);
}
```

## Il Processo Dettagliato di Iniezione

La funzionalità centrale di questa libreria è orchestrare una sequenza precisa di operazioni per iniettare le DLL del client SA-MP o OMP nel processo di GTA:SA. Questo ciclo è attentamente pianificato per garantire stabilità e compatibilità.

### 1. Richiesta di Inizializzazione

Il processo inizia con la chiamata alla funzione globale `Initialize_Game` (`injector.hpp`), che funge da punto di contatto principale per l'applicazione che utilizza la libreria. Questa funzione riceve tutti i parametri cruciali, come il tipo di iniezione desiderato (SA-MP o OMP), la directory del gioco e i dati di connessione al server (nickname, IP, porta, password).

### 2. Preparazione dell'Ambiente

Quando viene invocata, la funzione `Initialize_Game` crea un'istanza di `Injector::Injector_Core`. Nel costruttore di questa classe (`injector_core.hpp`), viene eseguita la prima ed essenziale fase di configurazione dell'ambiente: l'elevazione dei privilegi.

> [!NOTE]
> `Privileges::Enable_Debug_Privilege()`: Questa chiamata (`privileges.hpp`) concede al processo dell'applicazione il privilegio `SE_DEBUG_NAME`. Questo privilegio è vitale, poiché consente all'applicazione di eseguire operazioni a basso livello su altri processi di Windows, come leggere e scrivere nella loro memoria e creare `thread` remoti – azioni fondamentali per la tecnica di iniezione di DLL.

### 3. Verifica di Integrità e Parametri

Con i privilegi regolati, il metodo `Injector_Core::Initialize_Game` procede con una serie di convalide rigorose. Questa è una fase preventiva che riduce al minimo la possibilità di fallimenti nelle fasi successive e fornisce un feedback immediato all'utente.

- **Convalida della Porta:** `Validation::Validate_Port` verifica che il numero della porta di connessione sia formattato correttamente e si trovi nell'intervallo da `1` a `65535` (`constants.hpp`).
- **Convalida del Nickname:** `Validation::Validate_Nickname` garantisce che il nickname del giocatore non sia vuoto e non superi il limite di `23` caratteri.
- **Verifica dei File Essenziali:** `Validation::Validate_Files` ispeziona la directory del gioco per confermare la presenza di `gta_sa.exe`, `samp.dll` e, se l'iniezione è di tipo OMP, anche `omp-client.dll`.

> [!WARNING]
> Qualsiasi fallimento in questa fase comporta la visualizzazione immediata di una `MessageBox` con un messaggio di errore dettagliato (`error_utils.hpp`) e l'interruzione del processo di iniezione. Ciò evita tentativi inutili di procedere con una configurazione non valida.

### 4. Preparazione degli Argomenti per il Gioco

Dopo la convalida riuscita, la funzione `Injector_Core::Build_Command_Args` è responsabile della costruzione della riga di comando formattata che sarà passata a `gta_sa.exe`. Questa riga di comando include tutti i parametri necessari affinché il client SA-MP/OMP si connetta automaticamente a un server, come `-n "nickname" -h "IP" -p "Porta" -z "Password"`.

### 5. Inizializzazione del Processo del Gioco (Sospeso)

Il componente `Process` (`process.hpp`) è quindi incaricato di avviare l'eseguibile di GTA:SA.

> [!IMPORTANT]
> La funzione `Process::Create_Game_Process` utilizza il flag `CREATE_SUSPENDED` (`constants.hpp`) quando chiama l'API `CreateProcessW` di Windows. Questa è una misura di progettazione critica: il gioco viene caricato in memoria e il suo `thread` principale viene creato, ma la sua esecuzione è **messa in pausa**. Ciò crea un ambiente controllato e stabile, ideale per l'iniezione di DLL, prima che il gioco possa inizializzare le proprie difese o logiche interne. Gli `handle` del processo e del `thread` vengono ottenuti e gestiti in modo sicuro tramite `Resource_Handle::Unique_Resource`.

### 6. Iniezione della Libreria SA-MP (`samp.dll`)

Con il processo del gioco in stato di sospensione, l'iniezione di `samp.dll` può essere eseguita in modo sicuro. Il metodo `Injector_Core::Inject_DLL_With_Status_Check` delega questo compito a `Process::Inject_DLL`, che esegue i seguenti passaggi della tecnica di `remote thread injection`:

1. **Localizzazione della Funzione `LoadLibraryW`:** Viene identificato l'indirizzo della funzione `LoadLibraryW`. Questa operazione utilizza le costanti `Constants::KERNEL32_DLL` e `Constants::LOAD_LIBRARY_FUNC` per ottenere un `handle` a `kernel32.dll` e, successivamente, individuare l'indirizzo della funzione di caricamento delle librerie dinamiche.
2. **Allocazione di Memoria Remota:** `VirtualAllocEx` viene utilizzata per riservare un blocco di memoria nello spazio degli indirizzi virtuali del processo `gta_sa.exe` (che è sospeso). La dimensione di questo blocco è sufficiente per memorizzare il percorso completo di `samp.dll`.
3. **Scrittura del Percorso della DLL:** Il percorso completo del file `samp.dll` viene scritto in questa memoria remota appena allocata tramite `WriteProcessMemory`.
4. **Creazione di un Thread Remoto:** `CreateRemoteThread` viene chiamata per creare un nuovo `thread` all'interno del processo `gta_sa.exe`. Il punto di ingresso di questo nuovo `thread` è l'indirizzo di `LoadLibraryW`, e l'argomento che riceve è il puntatore al percorso della DLL che abbiamo appena scritto.
5. **Monitoraggio dell'Iniezione:** L'esecuzione del `thread` remoto è monitorata da `WaitForSingleObject` per un periodo definito da `Constants::DLL_INJECTION_TIMEOUT_MS`.
6. **Verifica del Risultato:** Il codice di uscita del `thread` remoto viene ottenuto tramite `GetExitCodeThread`. Un valore di ritorno diverso da zero indica che `LoadLibraryW` ha caricato con successo `samp.dll`.

> [!WARNING]
> In caso di qualsiasi fallimento durante l'iniezione di `samp.dll`, viene visualizzato un messaggio di errore specifico (`error_utils.hpp`), il processo di iniezione viene interrotto e le risorse vengono rilasciate.

### 7. Iniezione della Libreria OMP (`omp-client.dll`) - Condizionale

Se il tipo di iniezione specificato è `OMP`, i passaggi dettagliati al punto 6 vengono ripetuti per `omp-client.dll`.

> [!TIP]
> L'iniezione di `omp-client.dll` avviene sempre dopo l'iniezione riuscita di `samp.dll`. Ciò è dovuto al fatto che il client Open Multiplayer si basa sull'infrastruttura fornita da `samp.dll`.

### 8. Attivazione del Gioco

Infine, se tutte le iniezioni sono state completate con successo, viene invocato il metodo `process_info.Resume()`. Questa chiamata esegue `ResumeThread` sul `thread` principale di `gta_sa.exe`. A questo punto, il gioco viene attivato e inizia la sua esecuzione normale, ma già con le DLL di SA-MP/OMP caricate nella sua memoria e con i parametri di connessione configurati, consentendo una connessione automatizzata al server.

> [!WARNING]
> Se la ripresa del `thread` del gioco fallisce, viene presentato un ultimo messaggio di errore all'utente.

## Diagnostica di Errori e Guasti

La libreria è meticolosamente progettata per comunicare chiaramente qualsiasi problema che possa sorgere durante il processo di inizializzazione e iniezione. In qualsiasi punto di fallimento, viene presentata all'utente una `MessageBox` con una descrizione dettagliata, spesso completata con messaggi di errore del sistema operativo.

### Errori di Convalida dell'Input

Questi errori vengono rilevati nella fase iniziale (`validation.hpp`), prima di qualsiasi interazione a basso livello con il sistema, e indicano problemi con i dati forniti dall'utente o con la configurazione dell'ambiente.

#### Nome Utente Non Valido

- **Messaggio di Errore (Esempio 1):** `"Nickname cannot be empty. Please provide a valid nickname."`
- **Messaggio di Errore (Esempio 2):** `"Nickname length exceeds the maximum allowed of 23 characters. Please use a shorter nickname."`
- **Motivo:** Il nome utente (`nickname`) fornito è vuoto o supera il limite massimo di 23 caratteri consentito dai client SA-MP/OMP.
- **Soluzione:** L'utente deve inserire un nome utente valido che rispetti i criteri di lunghezza.

#### Porta di Connessione Non Valida

- **Messaggio di Errore (Esempio 1):** `"Invalid port format. The port must be a numeric value. Please provide a valid integer for the port."`
- **Messaggio di Errore (Esempio 2):** `"The specified port number (70000) is outside the valid range of 1 to 65535. Please provide a valid port."`
- **Motivo:** Il valore fornito per la porta non è un numero intero o è al di fuori dell'intervallo valido (da 1 a 65535).
- **Soluzione:** L'utente deve fornire un numero di porta valido e all'interno dell'intervallo specificato.

#### Risorse Essenziali Mancanti

- **Messaggio di Errore (Esempio 1):** `"Game executable not found. Please ensure 'gta_sa.exe' exists at the specified path: C:\Games\GTA San Andreas\gta_sa.exe"`
- **Messaggio di Errore (Esempio 2):** `"SA-MP library not found. Please ensure 'samp.dll' exists at the specified path: C:\Games\GTA San Andreas\samp.dll"`
- **Messaggio di Errore (Esempio 3, per OMP):** `"OMP library not found. Please ensure 'omp-client.dll' exists at the specified path for OMP injection: C:\Games\GTA San Andreas\omp-client.dll"`
- **Motivo:** Uno o più file cruciali (`gta_sa.exe`, `samp.dll`, `omp-client.dll`) non sono stati trovati nella directory del gioco specificata.
- **Soluzione:** Verificare il percorso della cartella del gioco e assicurarsi che tutti i file necessari siano presenti e accessibili.

### Errori nella Gestione del Processo

Questi errori si verificano quando la libreria tenta di avviare l'eseguibile del gioco (`gta_sa.exe`).

#### Difficoltà nell'Avviare il Processo del Gioco

- **Messaggio di Errore (Esempio):** `"Failed to create game process. Ensure 'gta_sa.exe' is not running and you have sufficient permissions to execute the file. System Error: Access is denied."`
- **Motivo:**
   - **Eseguibile in Uso:** `gta_sa.exe` potrebbe essere già in esecuzione, o c'è un blocco del sistema operativo che impedisce la creazione di una nuova istanza.
   - **Permessi Insufficienti:** L'applicazione potrebbe non avere i permessi adeguati per avviare `gta_sa.exe` o per accedere al file.
   - **Eseguibile Corrotto:** Sebbene la convalida di base verifichi l'esistenza del file, potrebbe essere corrotto o inaccessibile.
- **Soluzione:** Assicurarsi che nessuna istanza di `gta_sa.exe` sia attiva. Provare a eseguire l'applicazione come amministratore. Verificare l'integrità del file `gta_sa.exe`.

### Problemi nell'Iniezione della DLL

Questi sono gli errori più critici e dettagliati, che si verificano durante il tentativo di iniettare `samp.dll` o `omp-client.dll` nel processo sospeso del gioco. I messaggi di errore di solito iniziano con `"Failed to inject <DLL_NAME>:\n"` e sono seguiti da una descrizione specifica e un codice di errore del sistema.

#### Impossibile Trovare `LoadLibraryW`

- **Messaggio di Errore (Parte):** `"Failed to find the address of LoadLibraryW in kernel32.dll."`
- **Motivo:** La funzione `LoadLibraryW`, un'API fondamentale di Windows per il caricamento dinamico di DLL, non è stata trovata in `kernel32.dll`. Questo è un problema a basso livello estremamente raro, che indica una possibile corruzione del sistema operativo o un ambiente di esecuzione molto insolito.
- **Soluzione:** Un riavvio del sistema potrebbe risolvere il problema. Se persiste, potrebbe indicare un problema più grave nell'installazione di Windows.

#### Fallimento nell'Allocazione di Memoria Remota

- **Messaggio di Errore (Parte):** `"Failed to allocate memory in the target process (VirtualAllocEx). System Error: Not enough storage is available to process this command."`
- **Motivo:** La libreria non è riuscita ad allocare un blocco di memoria nello spazio degli indirizzi virtuali del processo `gta_sa.exe`.
   - **Permessi:** L'applicazione potrebbe non avere permessi sufficienti per modificare lo spazio di memoria di un altro processo.
   - **Protezione del Processo:** Meccanismi di sicurezza del sistema operativo o software anti-cheat potrebbero bloccare l'allocazione di memoria in processi esterni.
- **Soluzione:** Eseguire l'applicazione come amministratore. Verificare se programmi di sicurezza (antivirus, anti-cheat) stanno interferendo e, se possibile, disattivarli temporaneamente per un test.

#### Incapacità di Scrivere Dati nel Processo

- **Messaggio di Errore (Parte):** `"Failed to write DLL path to process memory (WriteProcessMemory). System Error: Access is denied."`
- **Motivo:** La memoria è stata allocata nel processo del gioco, ma la libreria non è riuscita a scrivere il percorso della DLL in quella posizione.
   - **Permessi/Protezione:** Simile al fallimento dell'allocazione di memoria, potrebbe essere un problema di permesso di scrittura o una protezione di memoria attiva.
- **Soluzione:** Si applicano le stesse soluzioni per il fallimento dell'allocazione di memoria.

#### Fallimento nella Creazione del Thread di Iniezione

- **Messaggio di Errore (Parte):** `"Failed to create remote thread (CreateRemoteThread). System Error: The parameter is incorrect."`
- **Motivo:** L'API `CreateRemoteThread` non è riuscita ad avviare un nuovo `thread` nel processo `gta_sa.exe` per invocare `LoadLibraryW`.
   - **Sicurezza:** Molti sistemi anti-cheat e protezioni del SO monitorano e bloccano la creazione di `thread` remoti, poiché è una tecnica comune di iniezione.
   - **Stato del Processo:** Il processo del gioco potrebbe trovarsi in uno stato instabile che impedisce la creazione di `thread`.
- **Soluzione:** Disattivare temporaneamente qualsiasi software anti-cheat o antivirus. Provare a eseguire l'applicazione come amministratore.

#### Timeout Scaduto o Errore nell'Attesa dell'Iniezione

- **Messaggio di Errore (Parte):** `"Timeout or error waiting for remote thread (WaitForSingleObject). System Error: The wait operation timed out."`
- **Motivo:** Il `thread` remoto (che chiama `LoadLibraryW`) non ha completato la sua esecuzione entro il tempo limite stabilito (10 secondi).
   - **Blocco:** `LoadLibraryW` potrebbe essersi bloccato, aver impiegato troppo tempo, o essere stato intercettato/bloccato.
- **Soluzione:** Ciò potrebbe indicare che la DLL ha difficoltà a caricarsi o che qualcosa la sta impedendo. Controllare i log di sistema o di SA-MP/OMP (se disponibili) potrebbe offrire maggiori indizi.

#### Fallimento Interno nell'Iniezione della DLL

- **Messaggio di Errore (Parte):** `"LoadLibraryW call failed in the target process. The DLL might be corrupt, missing dependencies, or blocked by security software."`
- **Motivo:** Il `thread` remoto è stato completato, ma il valore di ritorno di `LoadLibraryW` è stato `0` (o `NULL`), indicando che la DLL non è stata caricata con successo.
   - **DLL Corrotta/Inesistente:** La DLL potrebbe essere stata spostata, eliminata o corrotta dopo la convalida iniziale.
   - **Dipendenze Mancanti:** `samp.dll` o `omp-client.dll` potrebbero avere dipendenze (altre DLL) che non sono presenti nella directory del gioco o nel `PATH` di sistema.
   - **Errore Interno della DLL:** La stessa DLL potrebbe avere un errore interno che ne impedisce il caricamento.
- **Soluzione:** Verificare l'integrità dei file `samp.dll`/`omp-client.dll`. Assicurarsi che tutte le loro dipendenze siano presenti.

### Difficoltà nel Riprendere l'Esecuzione del Gioco

Questo è l'ultimo punto di possibile fallimento nel ciclo di iniezione.

- **Messaggio di Errore (Esempio):** `"Failed to resume the game process thread: Invalid handle."`
- **Motivo:** L'API `ResumeThread` non è riuscita a riattivare il `thread` principale di `gta_sa.exe`.
   - **Handle Non Valido:** L' `handle` del `thread` potrebbe essere stato invalidato da un evento imprevisto.
   - **Permesso:** L'applicazione potrebbe non avere il permesso di modificare lo stato del `thread`.
- **Soluzione:** Provare a eseguire l'applicazione come amministratore. Se il problema persiste, potrebbe indicare un problema di stabilità più profondo nel sistema o nel processo del gioco.

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