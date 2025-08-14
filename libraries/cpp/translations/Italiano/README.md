# SA-MP Injector C++

![License](https://img.shields.io/badge/License-MIT-yellow.svg?style=flat)
![C++17](https://img.shields.io/badge/C%2B%2B-17-blue.svg?style=flat&logo=cplusplus)
![Platform](https://img.shields.io/badge/Platform-Windows-0078D6.svg?style=flat&logo=windows)
[![SA-MP | OMP](https://img.shields.io/badge/Support-SA--MP%20%7C%20OMP-yellow)](https://github.com/spc-samp/samp-injector)
![Code Quality](https://img.shields.io/badge/Code%20Quality-High-brightgreen.svg?style=flat)

Il **SA-MP Injector C++** trascende la definizione di un semplice strumento di **iniezione di DLL**. È una **libreria C++** accuratamente progettata, sviluppata per fornire una soluzione robusta e completa per l'avvio programmatico del gioco **Grand Theft Auto: San Andreas** (**GTA:SA**) in combinazione con i suoi client multiplayer, in particolare **SA-MP (San Andreas Multiplayer)** e **OMP (Open Multiplayer)**. Il suo obiettivo principale è semplificare il processo di avvio del gioco, eliminando la complessità intrinseca nella manipolazione diretta dei processi del sistema operativo e nel passaggio di argomenti da riga di comando.

Sviluppata con l'intento di offrire la massima flessibilità e un'integrazione facilitata, questa libreria `header-only` elimina la necessità di compilazioni complesse, permettendo agli sviluppatori di incorporarla direttamente nei loro **progetti C++**. Non solo orchestra l'**iniezione fondamentale delle DLL** del client multiplayer (`samp.dll` o `omp-client.dll`), ma gestisce anche in modo intelligente tutti i parametri essenziali per la connessione (**nickname**, **indirizzo IP**, **porta** e **password**), simulando un avvio nativo attraverso le risorse intrinseche dell'**API di Windows**.

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
  - [Concetti Fondamentali e Motivazione](#concetti-fondamentali-e-motivazione)
    - [Perché Iniettare DLL?](#perché-iniettare-dll)
    - [SA-MP e OMP: Distinzioni e Somiglianze](#sa-mp-e-omp-distinzioni-e-somiglianze)
  - [Architettura Interna della Libreria: Un'Analisi Approfondita](#architettura-interna-della-libreria-unanalisi-approfondita)
    - [`constants.hpp`](#constantshpp)
    - [`types.hpp`](#typeshpp)
    - [`string_utils.hpp`](#string_utilshpp)
    - [`error_utils.hpp`](#error_utilshpp)
    - [`resource_handle.hpp`](#resource_handlehpp)
    - [`validation.hpp`](#validationhpp)
    - [`process.hpp`](#processhpp)
    - [`injector_core.hpp`](#injector_corehpp)
    - [`injector.hpp`](#injectorhpp)
  - [Esempi Completi di Utilizzo](#esempi-completi-di-utilizzo)
    - [1. Preparazione dell'Ambiente di Sviluppo](#1-preparazione-dellambiente-di-sviluppo)
    - [2. Scenario Base: Connessione a un Server SA-MP](#2-scenario-base-connessione-a-un-server-sa-mp)
    - [3. Scenario Avanzato: Connessione a un Server OMP](#3-scenario-avanzato-connessione-a-un-server-omp)
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
    - [6. Fallimento nell'Allocazione della Memoria nel Processo Target](#6-fallimento-nellallocazione-della-memoria-nel-processo-target)
    - [7. Fallimento nella Scrittura del Percorso della DLL nella Memoria del Processo](#7-fallimento-nella-scrittura-del-percorso-della-dll-nella-memoria-del-processo)
    - [8. Fallimento nel Trovare Funzioni Essenziali del Sistema](#8-fallimento-nel-trovare-funzioni-essenziali-del-sistema)
      - [8.1. `kernel32.dll` Non Trovato](#81-kernel32dll-non-trovato)
      - [8.2. `LoadLibraryA` Non Trovato](#82-loadlibrarya-non-trovato)
    - [9. Fallimento nella Creazione di un Thread Remoto per l'Iniezione](#9-fallimento-nella-creazione-di-un-thread-remoto-per-liniezione)
    - [10. Timeout o Fallimento nel Completamento dell'Iniezione](#10-timeout-o-fallimento-nel-completamento-delliniezione)
    - [11. Fallimento nel Ripristino del Thread del Processo del Gioco](#11-fallimento-nel-ripristino-del-thread-del-processo-del-gioco)
  - [Licenza](#licenza)
    - [Termini e Condizioni d'Uso](#termini-e-condizioni-duso)
      - [1. Permessi Concessi](#1-permessi-concessi)
      - [2. Condizioni Obbligatorie](#2-condizioni-obbligatorie)
      - [3. Diritti d'Autore](#3-diritti-dautore)
      - [4. Esclusione di Garanzia e Limitazione di Responsabilità](#4-esclusione-di-garanzia-e-limitazione-di-responsabilità)

## Concetti Fondamentali e Motivazione

### Perché Iniettare DLL?

> [!NOTE]
> L'**iniezione di DLL (Dynamic Link Library)** è un metodo utilizzato nei sistemi operativi **Microsoft Windows** che consente l'esecuzione di codice all'interno dello spazio di memoria di un altro processo in esecuzione. È una tecnica potente con diverse applicazioni legittime, dalla debug e monitoraggio di programmi alla modifica del comportamento delle applicazioni per estenderne le funzionalità.

Nel contesto di giochi come il **GTA San Andreas**, che non sono stati originariamente sviluppati con funzionalità multiplayer integrate, l'**iniezione di DLL** è la base per l'esistenza di client multiplayer come **SA-MP** e **OMP**. Questi client sono implementati come **DLL** che, una volta iniettate nel processo del `gta_sa.exe`, assumono il controllo, intercettano funzioni del gioco e stabiliscono la comunicazione con i server multiplayer.

Invece di dipendere da un launcher esterno o dalla modifica diretta dell'eseguibile del gioco, l'**iniezione di DLL** consente un avvio più flessibile e programmabile, particolarmente utile in ambienti in cui si desidera automatizzare il processo di connessione a server specifici con configurazioni predefinite.

### SA-MP e OMP: Distinzioni e Somiglianze

Il **SA-MP** e l'**OMP** sono le due principali piattaforme multiplayer per **GTA San Andreas**. Entrambi funzionano come modifiche del gioco base, trasformandolo in un ambiente multiplayer massivo online.

- **SA-MP (San Andreas Multiplayer)**: Il client originale e più consolidato, ampiamente utilizzato per molti anni. La sua architettura richiede la `samp.dll` per funzionare.
- **OMP (Open Multiplayer)**: Un progetto open-source, generalmente visto come un successore o un'alternativa più moderna a **SA-MP**, che offre miglioramenti in termini di prestazioni, stabilità e funzionalità aggiuntive. Richiede la `omp-client.dll`.

Sebbene operino in modo simile (**iniettando una DLL** nel processo del **GTA:SA**), la libreria **SA-MP Injector C++** è stata accuratamente sviluppata per supportare **entrambe le DLL**, riconoscendo le loro distinzioni nei nomi dei file e permettendo allo sviluppatore di scegliere il client multiplayer desiderato tramite un parametro di configurazione. Questo assicura che la libreria possa essere utilizzata con la vasta gamma di server e progetti basati su entrambe le piattaforme.

## Architettura Interna della Libreria: Un'Analisi Approfondita

Il **SA-MP Injector C++** adotta un approccio modulare e orientato agli oggetti (dove applicabile) per gestire la complessità del processo di iniezione. Ogni file di intestazione è un modulo specializzato, responsabile di una specifica fetta della funzionalità complessiva, promuovendo la chiarezza del codice, la manutenibilità e l'espandibilità.

### `constants.hpp`

Questo file è la base di tutte le configurazioni fisse della libreria. Definisce un namespace `Constants` per incapsulare tutte le letterali, garantendo che non ci sia inquinamento dello scope globale. L'uso di `inline constexpr` è cruciale qui: `constexpr` indica che i valori sono valutati in fase di compilazione, ottimizzando le prestazioni e garantendo l'immutabilità, mentre `inline` evita problemi di ridefinizione quando il file viene incluso in più unità di compilazione.

```cpp
#pragma once

namespace Constants {
    // Game related constants
    inline constexpr int MIN_PORT = 1;
    inline constexpr int MAX_PORT = 65535;
    inline constexpr int MAX_NICKNAME_LENGTH = 23;
    
    // File names
    inline constexpr const wchar_t* SAMP_DLL_NAME = L"samp.dll";
    inline constexpr const wchar_t* OMP_DLL_NAME = L"omp-client.dll";
    inline constexpr const wchar_t* GAME_EXE_NAME = L"gta_sa.exe";
    
    // System libraries and functions
    inline constexpr const char* KERNEL32_DLL = "kernel32.dll";
    inline constexpr const char* LOAD_LIBRARY_FUNC = "LoadLibraryA"; // 'A' per la versione ANSI/8-bit
    
    // Command line arguments used by SA-MP/OMP clients
    inline constexpr const char* CMD_ARG_CONFIG = "-c";
    inline constexpr const char* CMD_ARG_NICKNAME = "-n";
    inline constexpr const char* CMD_ARG_HOST = "-h";
    inline constexpr const char* CMD_ARG_PORT = "-p";
    inline constexpr const char* CMD_ARG_PASSWORD = "-z";
    
    // Injection types as strings (wide-character)
    inline constexpr const wchar_t* INJECT_TYPE_SAMP = L"samp";
    inline constexpr const wchar_t* INJECT_TYPE_OMP = L"omp";
    
    // Error message titles for MessageBoxW
    inline constexpr const wchar_t* ERROR_TITLE_SAMP = L"SA-MP Injector Error - SPC";
    inline constexpr const wchar_t* ERROR_TITLE_OMP = L"OMP Injector Error - SPC";
    
    // Process creation flags for CreateProcessA
    inline constexpr DWORD PROCESS_CREATION_FLAGS = CREATE_SUSPENDED | DETACHED_PROCESS;
    
    // Timeouts for WaitForSingleObject (e.g., waiting for DLL injection)
    inline constexpr DWORD DLL_INJECTION_TIMEOUT_MS = 10000; // 10 seconds
    
    // Memory allocation flags for VirtualAllocEx
    inline constexpr DWORD MEMORY_ALLOCATION_TYPE = MEM_COMMIT | MEM_RESERVE;
    inline constexpr DWORD MEMORY_PROTECTION = PAGE_READWRITE; // Necessario per scrivere il percorso della DLL
}
```

> [!TIP]
> L'uso di `wchar_t` per i nomi dei file e i titoli dei messaggi di errore è una pratica consigliata nello **sviluppo per Windows**. Ciò garantisce la compatibilità con tutte le lingue e set di caratteri, specialmente utile per i percorsi dei file che possono contenere **caratteri Unicode**. Per le **API** che si aspettano `char` (come `LoadLibraryA`), la conversione viene eseguita esplicitamente in `string_utils.hpp`.

### `types.hpp`

Un modulo conciso ma essenziale, per definire l'enumerazione che categorizza i tipi di iniezione supportati. Questo migliora la leggibilità e la sicurezza del tipo del codice, prevenendo errori di stringhe o numeri magici.

```cpp
#pragma once

namespace Types {
    // Enumerazioni per i tipi di iniezione supportati
    enum class Inject_Type {
        SAMP, // San Andreas Multiplayer
        OMP // Open Multiplayer
    };
}
```

### `string_utils.hpp`

Operare con l'**API di Windows** richiede spesso la conversione tra diverse codifiche di stringhe. Questo file fornisce una funzione di utilità vitale per convertire stringhe da **caratteri larghi** (`std::wstring_view`, utilizzate negli input della libreria) a stringhe **ANSI/8-bit** (`std::string`), necessarie per le funzioni **WinAPI** che operano con `char*` (come `CreateProcessA` o `GetProcAddress`).

```cpp
#pragma once

#include <string>
#include <string_view>
#include <windows.h> // Necessario per WideCharToMultiByte

namespace Utils {
    inline std::string Wide_To_Local_8Bit(std::wstring_view wstr) {
        if (wstr.empty())
            return "";
        
        // Determina la dimensione necessaria per il buffer della stringa risultante in char
        int size = WideCharToMultiByte(CP_ACP, // Code Page ANSI (dipendente dal sistema locale)
            0, // Senza flag aggiuntive
            wstr.data(), 
            static_cast<int>(wstr.size()), 
            nullptr, // Calcola la dimensione, non riempie il buffer
            0, // Dimensione 0, solo per il calcolo
            nullptr, // Carattere predefinito per caratteri non rappresentabili
            nullptr); // Puntatore al bool che indica se è stato utilizzato un carattere predefinito

        if (size <= 0) // Restituisce una stringa vuota in caso di errore o dimensione non valida
            return "";

        std::string result(size, 0); // Alloca la stringa con la dimensione determinata
        // Esegue la conversione effettiva, riempiendo il buffer 'result'
        WideCharToMultiByte(CP_ACP, 
            0, 
            wstr.data(), 
            static_cast<int>(wstr.size()), 
            result.data(), // Buffer di destinazione
            size, // Dimensione del buffer di destinazione
            nullptr, 
            nullptr);

        return result;
    }
}
```

> [!IMPORTANT]
> Il `CP_ACP` **(ANSI Code Page)** utilizzato in `WideCharToMultiByte` è la pagina di codice predefinita del sistema **Windows**. Ciò significa che la conversione può variare a seconda della configurazione linguistica del sistema dell'utente. Per la maggior parte dei casi d'uso di nomi di file e argomenti da riga di comando in **SA-MP**/**OMP** (che storicamente gestiscono bene le stringhe **ANSI**), questo approccio è generalmente sufficiente. Tuttavia, in scenari che richiedono una compatibilità **Unicode** completa con sistemi esterni o input globali, sarebbe necessaria una conversione in **UTF-8** (`CP_UTF8`) o altre pagine di codice. Per lo scopo di questo progetto, il `CP_ACP` è lo standard funzionale.

### `error_utils.hpp`

Un componente fondamentale per l'usabilità della libreria, responsabile di fornire un **feedback** chiaro all'utente in caso di errore. Centralizza la logica di ottenimento dei messaggi di errore del sistema e la visualizzazione di finestre di dialogo.

```cpp
#pragma once

#include <string>
#include <string_view>
#include <windows.h> // Per FormatMessageW e MessageBoxW
//
#include "types.hpp"
#include "constants.hpp"

namespace Utils {
    // Restituisce il messaggio di errore del sistema Windows per un codice di errore specifico
    inline std::wstring Get_System_Error_Message(DWORD error_code) {
        wchar_t buffer[512] = {0}; // Buffer per il messaggio
        // FormatMessageW riempie il buffer con la descrizione dell'errore del sistema
        DWORD result = FormatMessageW(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, 
            nullptr, // Fonte del messaggio (dal sistema)
            error_code, 
            0, // Lingua (usa quella predefinita)
            buffer, 
            512, // Dimensione del buffer
            nullptr);
        
        // Se la funzione ha avuto successo, restituisce la stringa del buffer; altrimenti, un messaggio generico
        return result ? std::wstring(buffer) : L"Errore sconosciuto (Codice: " + std::to_wstring(error_code) + L")";
    }

    // Visualizza una finestra di messaggio di errore all'utente
    inline void Show_Error(std::wstring_view message, Types::Inject_Type injectType) {
        // Sceglie il titolo della finestra di dialogo in base al tipo di iniezione
        std::wstring title = (injectType == Types::Inject_Type::SAMP) ? Constants::ERROR_TITLE_SAMP : Constants::ERROR_TITLE_OMP;
        MessageBoxW(nullptr, // Handle della finestra genitore (nullptr per il desktop)
            message.data(), 
            title.c_str(), 
            MB_OK | MB_ICONERROR); // Pulsante OK e icona di errore
    }
}
```

> [!NOTE]
> La funzione `FormatMessageW` è una potente **API di Windows** che recupera la descrizione testuale di un codice di errore del sistema. Gestisce la localizzazione e fornisce messaggi chiari che sono essenziali per una **diagnosi** efficace, trasformando un `DWORD` come `ERROR_FILE_NOT_FOUND` (2) in `L"Il sistema non può trovare il file specificato."`.

### `resource_handle.hpp`

La gestione sicura delle risorse (come gli `HANDLE` di **Windows**) è cruciale per evitare perdite di risorse e comportamenti indefiniti. Questo file definisce un `UniqueResource` utilizzando `std::unique_ptr` e una funzione personalizzata per `CloseHandle`. Ciò segue il principio **RAII (Resource Acquisition Is Initialization)**, garantendo che gli `HANDLE` vengano automaticamente chiusi quando i loro **wrapper** escono dallo scope, anche in caso di eccezioni.

```cpp
#pragma once

#include <memory> // Per std::unique_ptr
#include <functional> // Per std::function
#include <windows.h> // Per HANDLE e CloseHandle

namespace Utils {
    // Alias di tipo per un std::unique_ptr che gestisce un HANDLE (o puntatore) con un deleter personalizzato
    // T: Il tipo di risorsa da gestire (es: HANDLE, LPVOID)
    // Deleter: Una classe o lambda che sa come liberare la risorsa
    template<typename T, typename Deleter>
    using UniqueResource = std::unique_ptr<std::remove_pointer_t<T>, Deleter>;

    // Funzione ausiliaria per creare un'istanza di UniqueResource per HANDLE
    // Assume che T sia un tipo di handle e utilizza CloseHandle come deleter.
    template<typename T>
    inline auto Make_Unique_Handle(T handle) {
        return UniqueResource<T, std::function<void(T)>>(handle, [](T h) {
            // Condizione per garantire che l'handle sia valido prima di tentare di chiuderlo
            // 0 e INVALID_HANDLE_VALUE sono considerati non validi per la maggior parte degli handle
            if (h && h != INVALID_HANDLE_VALUE)
                CloseHandle(h); // Libera l'HANDLE del sistema operativo
        });
    }
}
```

> [!IMPORTANT]
> L'uso di `UniqueResource` è una dimostrazione di buone pratiche di **C++ moderno** e sviluppo sicuro in **Windows**. Semplifica drasticamente la gestione del ciclo di vita degli **handle**, che, se non chiusi correttamente, possono portare a perdite di memoria o risorse del **kernel**, influenzando la stabilità del sistema nel tempo.

### `validation.hpp`

La robustezza dell'iniezione inizia con la validazione degli input dell'utente e la verifica delle dipendenze dei file. Questo modulo contiene funzioni che garantiscono che tutti i prerequisiti e i parametri siano corretti prima di tentare di avviare il processo di iniezione, prevenendo errori più complessi in seguito.

```cpp
#pragma once

#include <string>
#include <string_view>
#include <filesystem> // Per std::filesystem::exists
//
#include "constants.hpp"
#include "types.hpp"
#include "string_utils.hpp" // Per Wide_To_Local_8Bit
#include "error_utils.hpp" // Per Show_Error

namespace Utils {
    // Valida se una stringa di porta è un numero valido ed è all'interno dell'intervallo permesso
    inline bool Validate_Port(std::wstring_view port_str, std::wstring& error_message) {
        try {
            // Tenta di convertire la stringa di caratteri larghi in std::string e poi in int
            int port_num = std::stoi(Wide_To_Local_8Bit(port_str));

            // Verifica se la porta è all'interno dell'intervallo valido (1-65535)
            if (port_num < Constants::MIN_PORT || port_num > Constants::MAX_PORT)
                return (error_message = L"Il numero di porta specificato (" + std::wstring(port_str) + 
                L") è fuori dall'intervallo valido di " +  std::to_wstring(Constants::MIN_PORT) + 
                L" a " + std::to_wstring(Constants::MAX_PORT) + 
                L". Per favore, fornisci una porta valida.", false);

            return true;
        }
        catch (...) { // Cattura qualsiasi eccezione (come std::invalid_argument per non numerico)
            return (error_message = L"Formato della porta non valido. La porta deve essere un valore numerico. Per favore, fornisci un numero intero valido per la porta.", false);
        }
    }

    // Valida il nickname, verificando che non sia vuoto e che la lunghezza sia accettabile
    inline bool Validate_Nickname(std::wstring_view nickname_str, std::wstring& error_message) {
        if (nickname_str.empty())
            return (error_message = L"Il nickname non può essere vuoto. Per favore, fornisci un nickname valido.", false);
        
        if (nickname_str.size() > Constants::MAX_NICKNAME_LENGTH)
            return (error_message = L"La lunghezza del nickname supera il massimo consentito di " + 
                std::to_wstring(Constants::MAX_NICKNAME_LENGTH) + 
                L" caratteri. Per favore, usa un nickname più corto.", false);

        return true;
    }

    // Valida l'esistenza dei file critici (gta_sa.exe, samp.dll, omp-client.dll)
    inline bool Validate_Files(const std::filesystem::path& game_path, 
        const std::filesystem::path& samp_DLL_path, 
        const std::filesystem::path& omp_DLL_path, 
        Types::Inject_Type inject_type) {
        std::wstring error_message_local; // Usiamo una variabile locale qui prima di passare a Show_Error
        
        // Verifica l'esistenza dell'eseguibile del gioco
        if (!std::filesystem::exists(game_path)) {
            error_message_local = L"Eseguibile del gioco non trovato. Per favore, assicurati che 'gta_sa.exe' esista nel percorso specificato: " + game_path.wstring();
            Show_Error(error_message_local, inject_type);
            
            return false;
        }

        // Verifica l'esistenza della samp.dll (essenziale per entrambi i tipi di iniezione)
        if (!std::filesystem::exists(samp_DLL_path)) {
            error_message_local = L"Libreria SA-MP non trovata. Per favore, assicurati che 'samp.dll' esista nel percorso specificato: " + samp_DLL_path.wstring();
            Show_Error(error_message_local, inject_type);

            return false;
        }

        // Se il tipo di iniezione è OMP, verifica l'esistenza della omp-client.dll
        if (inject_type == Types::Inject_Type::OMP && !std::filesystem::exists(omp_DLL_path)) {
            error_message_local = L"Libreria OMP non trovata. Per favore, assicurati che 'omp-client.dll' esista nel percorso specificato per l'iniezione OMP: " + omp_DLL_path.wstring();
            Show_Error(error_message_local, inject_type);

            return false;
        }

        return true; // Tutti i file necessari sono stati trovati
    }
}
```

> [!NOTE]
> L'utilizzo di `std::filesystem` è un'aggiunta moderna al **C++17** che offre un modo potente e indipendente dalla piattaforma per interagire con il sistema di file. Per questo progetto su **Windows**, semplifica la gestione dei percorsi e la verifica dell'esistenza dei file rispetto alle **API** più vecchie di **WinAPI**.
>
> Assicurati che il tuo compilatore supporti **C++17** per utilizzare `std::filesystem`. Dovrai configurare il tuo progetto per utilizzare lo standard **C++17** (`/std:c++17` in **Visual Studio**).

### `process.hpp`

Questo è il modulo principale responsabile dell'interazione diretta con le **API** di basso livello di **Windows** per manipolare i processi. Incapsula le operazioni cruciali di creazione del processo e **iniezione di DLL**, gestendo **handle**, **memoria** e **thread**.

```cpp
#pragma once

#include <string_view>
#include <optional> // Per std::optional
#include <functional> // Per std::function (usato in UniqueResource)
#include <windows.h> // API di Windows
#include <memory> // Per std::unique_ptr
#include <vector> // Per std::vector (buffer di args)
//
#include "resource_handle.hpp" // Il nostro wrapper per gli HANDLE
#include "error_utils.hpp" // Per Get_System_Error_Message e Show_Error
#include "constants.hpp" // Costanti globali
#include "types.hpp" // Tipi di iniezione

class Process {
    public:
        // Costruttori/Distruttori e operatori di assegnazione
        // Esplicitamente default e delete per garantire semantica di valore e solo spostamento.
        Process() = default;
        Process(const Process&) = delete; // Senza copia
        Process& operator=(const Process&) = delete; // Senza assegnazione di copia
        Process(Process&&) = default; // Semantica di spostamento
        Process& operator=(Process&&) = default; // Assegnazione di spostamento
        ~Process() = default;

        // Struttura per memorizzare gli handle del processo e del thread, gestiti da UniqueResource
        struct Process_Info {
            Resource_Handle::UniqueResource<HANDLE, std::function<void(HANDLE)>> process_handle;
            Resource_Handle::UniqueResource<HANDLE, std::function<void(HANDLE)>> thread_handle;
        };

        // Crea il processo del gioco GTA:SA in stato sospeso
        std::optional<Process_Info> Create_Game_Process(std::string_view game_path, std::string_view command_args, std::string_view working_dir) {
            STARTUPINFOA startup_info{}; // Struttura per le informazioni di avvio del processo
            startup_info.cb = sizeof(STARTUPINFOA); // Definisce la dimensione della struttura

            PROCESS_INFORMATION process_info{}; // Struttura che riceverà informazioni sul nuovo processo

            // Crea un buffer mutabile per gli argomenti della riga di comando.
            // CreateProcessA modifica il buffer della riga di comando, quindi std::string_view diretto non funziona.
            std::vector<char> args_buffer(command_args.size() + 1); // +1 per il terminatore nullo

            if (!command_args.empty()) {
                std::memcpy(args_buffer.data(), command_args.data(), command_args.size());
                args_buffer[command_args.size()] = '\0'; // Garantisce il terminatore nullo
            }

            // Crea il processo
            bool success = CreateProcessA(game_path.data(), // Nome del modulo eseguibile
                args_buffer.empty() ? nullptr : args_buffer.data(), // Argomenti della riga di comando
                nullptr, // Attributi di sicurezza del processo
                nullptr, // Attributi di sicurezza del thread
                FALSE, // Non ereditare gli handle
                Constants::PROCESS_CREATION_FLAGS, // CREATE_SUSPENDED | DETACHED_PROCESS
                nullptr, // Ambiente del nuovo processo
                working_dir.empty() ? nullptr : working_dir.data(), // Directory di lavoro
                &startup_info, // Informazioni di avvio
                &process_info); // Informazioni del processo creato

            if (!success) {
                // Se fallisce, ottiene e visualizza il messaggio di errore del sistema
                std::wstring error_msg = Error_Utils::Get_System_Error_Message(GetLastError());
                Error_Utils::Show_Error(L"Impossibile creare il processo del gioco. Assicurati che 'gta_sa.exe' non sia in esecuzione e che tu abbia " L"sufficienti permessi per eseguire il file. Errore di sistema: " + error_msg, Types::Inject_Type::SAMP); // Usa SAMP come fallback per il titolo
                
                return std::nullopt; // Restituisce un optional vuoto
            }

            Process_Info result;
            // Memorizza gli handle del processo e del thread in UniqueResource per una gestione automatica
            result.process_handle = Resource_Handle::Make_Unique_Handle(process_info.hProcess);
            result.thread_handle = Resource_Handle::Make_Unique_Handle(process_info.hThread);

            return result; // Restituisce la struttura con gli handle gestiti
        }

        // Inietta una DLL nel processo remoto
        bool Inject_DLL(HANDLE process, std::string_view DLL_path, std::wstring& error_message) {
            // Alloca memoria nel processo remoto per il percorso della DLL
            LPVOID remote_memory = VirtualAllocEx(process, // Handle del processo target
            nullptr, // Indirizzo preferenziale (nullptr per lasciare che il sistema scelga)
            DLL_path.size() + 1, // Dimensione del percorso + terminatore nullo
            Constants::MEMORY_ALLOCATION_TYPE, // MEM_COMMIT | MEM_RESERVE
            Constants::MEMORY_PROTECTION); // PAGE_READWRITE

            if (!remote_memory)
                return (error_message = L"Impossibile allocare memoria nel processo target. Questo potrebbe essere dovuto a " L"permessi insufficienti o meccanismi di protezione del processo.", false);

            // Gestione delle risorse per la memoria allocata remotamente.
            // Verrà automaticamente liberata quando esce dallo scope.
            auto memory_guard = Resource_Handle::UniqueResource<LPVOID, std::function<void(LPVOID)>>(remote_memory, 
                [process](LPVOID ptr) { // Lambda come deleter
                    if (ptr)
                        VirtualFreeEx(process, ptr, 0, MEM_RELEASE); // Libera la memoria allocata
                }
            );

            // Scrive il percorso della DLL nella memoria allocata remotamente
            if (!WriteProcessMemory(process, remote_memory, DLL_path.data(), DLL_path.size() + 1, nullptr))
                return (error_message = L"Impossibile scrivere il percorso della DLL nella memoria del processo target. Verifica i permessi del processo " L"e assicurati che il percorso della DLL sia accessibile.", false);

            // Ottiene l'handle per kernel32.dll (che è caricato nel processo dell'iniettore stesso)
            HMODULE kernel32 = GetModuleHandleA(Constants::KERNEL32_DLL);
            
            if (!kernel32)
                return (error_message = L"Impossibile ottenere un handle per kernel32.dll. Questa è una libreria di sistema essenziale " L"e questo errore indica un grave problema di sistema.", false);

            // Ottiene l'indirizzo della funzione LoadLibraryA in kernel32.dll.
            // Questo indirizzo è coerente tra i processi nello stesso sistema operativo ed è la chiave dell'iniezione.
            LPVOID load_library_addr = reinterpret_cast<LPVOID>(GetProcAddress(kernel32, Constants::LOAD_LIBRARY_FUNC));

            if (!load_library_addr)
                return (error_message = L"Impossibile trovare l'indirizzo della funzione LoadLibraryA in kernel32.dll. " L"Questo è critico per l'iniezione della DLL.", false);

            // Crea un thread remoto nel processo target per eseguire LoadLibraryA
            // L'argomento per LoadLibraryA sarà l'indirizzo remoto del percorso della DLL
            HANDLE remote_thread = CreateRemoteThread(process, // Handle del processo target
                nullptr, // Attributi di sicurezza del thread
                0, // Dimensione dello stack (0 per default)
                reinterpret_cast<LPTHREAD_START_ROUTINE>(load_library_addr), // Indirizzo di LoadLibraryA
                remote_memory, // Argomento per LoadLibraryA (percorso della DLL)
                0, // Flag di creazione (0 per iniziare immediatamente)
                nullptr); // ID del thread (nullptr per non restituire)

            if (!remote_thread)
                return (error_message = L"Impossibile creare un thread remoto nel processo target per eseguire l'iniezione della DLL. Questo potrebbe essere dovuto a restrizioni di sicurezza o stato del processo. Errore di sistema: " + Error_Utils::Get_System_Error_Message(GetLastError()), false);

            // Gestione delle risorse per l'handle del thread remoto
            auto thread_guard = Resource_Handle::Make_Unique_Handle(remote_thread);

            // Attende che il thread remoto (iniezione della DLL) sia completato o raggiunga un timeout
            DWORD wait_result = WaitForSingleObject(remote_thread, Constants::DLL_INJECTION_TIMEOUT_MS);

            if (wait_result != WAIT_OBJECT_0) {
                return (error_message = L"Timeout o errore in attesa del completamento dell'iniezione della DLL. " L"Errore di sistema: " + Error_Utils::Get_System_Error_Message(GetLastError()), false);

            // Ottiene il codice di uscita del thread remoto.
            // Per LoadLibraryA, un codice di uscita 0 significa fallimento (non è riuscito a caricare la DLL).
            DWORD exit_code = 0;

            if (!GetExitCodeThread(remote_thread, &exit_code) || exit_code == 0)
                return (error_message = L"L'iniezione della DLL è fallita o ha restituito un errore. La chiamata a LoadLibrary potrebbe essere fallita nel processo target.", false);

            return true; // Iniezione riuscita
        }
};
```

> [!NOTE]
> Il modulo `process.hpp` dimostra un design robusto e sicuro. La funzione `Create_Game_Process` restituisce un `std::optional<Process_Info>`. Ciò consente alla funzione di segnalare fallimenti nella creazione del processo in modo esplicito ed elegante (restituendo un `std::nullopt`) senza ricorrere a eccezioni o codici di errore ambigui nel suo ritorno principale.
>
> Più cruciale, la struttura `Process_Info` utilizza `Resource_Handle::UniqueResource<HANDLE, std::function<void(HANDLE)>>` per incapsulare gli **handle** del processo e del **thread**. Questo è un esempio del modello **RAII (Resource Acquisition Is Initialization)**, che garantisce che gli `HANDLE` del sistema operativo (come `hProcess` e `hThread`) vengano automaticamente chiusi tramite `CloseHandle` quando l'oggetto `Process_Info` esce dallo scope. Ciò elimina perdite di **handle**, che sono una fonte comune di instabilità e consumo eccessivo di risorse in **applicazioni Windows** di lunga durata.
>
> In modo simile, all'interno della funzione `Inject_DLL`, `UniqueResource` viene utilizzato per gestire la memoria allocata remotamente (`VirtualAllocEx`), garantendo che venga liberata (`VirtualFreeEx`) non appena non è più necessaria o in caso di fallimento. Questa rigorosa gestione delle risorse contribuisce significativamente alla affidabilità e stabilità del **SA-MP Injector C++**.

### `injector_core.hpp`

Questa è la classe orchestratrice che unisce tutte le funzionalità dei moduli precedenti. Coordina la validazione, la costruzione degli argomenti della riga di comando, la creazione del processo e le chiamate di **iniezione della DLL**.

```cpp
#pragma once

#include <string_view>
#include <sstream> // Per costruire stringhe con stringstream
#include <filesystem> // Per la manipolazione dei percorsi
//
#include "process.hpp" // Funzioni di creazione/iniezione del processo
#include "validation.hpp" // Funzioni di validazione degli input
#include "string_utils.hpp" // Funzioni di conversione delle stringhe
#include "error_utils.hpp" // Funzioni di gestione degli errori
#include "constants.hpp" // Costanti della libreria
#include "types.hpp" // Tipi di iniezione

namespace Injector {
    class Injector_Core {
        public:
            // Costruttori/Distruttori per la semantica di spostamento
            Injector_Core() = default;
            Injector_Core(const Injector_Core&) = delete; // Disabilita la copia
            Injector_Core& operator=(const Injector_Core&) = delete; // Disabilita l'assegnazione di copia
            Injector_Core(Injector_Core&&) = default; // Abilita lo spostamento
            Injector_Core& operator=(Injector_Core&&) = default; // Abilita l'assegnazione di spostamento
            ~Injector_Core() = default;

            // Funzione principale che orchestra l'inizializzazione e l'iniezione del gioco
            bool Initialize_Game(Types::Inject_Type inject_type, std::wstring_view folder, std::wstring_view nickname, std::wstring_view ip, std::wstring_view port, std::wstring_view password) {
                namespace fs = std::filesystem; // Alias per std::filesystem

                // Costruisce i percorsi completi per i file essenziali
                fs::path game_path = fs::path(folder) / Constants::GAME_EXE_NAME; // Es: C:\GTA\gta_sa.exe
                fs::path samp_DLL_path = fs::path(folder) / Constants::SAMP_DLL_NAME; // Es: C:\GTA\samp.dll
                fs::path omp_DLL_path = fs::path(folder) / Constants::OMP_DLL_NAME; // Es: C:\GTA\omp-client.dll

                // 1. Validazione dei File
                if (!Validation::Validate_Files(game_path, samp_DLL_path, omp_DLL_path, inject_type))
                    return false; // L'errore è già stato visualizzato dalla funzione di validazione
                
                std::wstring error_message_local; // Per ricevere i messaggi di errore delle validazioni

                // 2. Validazione della Porta
                if (!Validation::Validate_Port(port, error_message_local))
                    return (Error_Utils::Show_Error(error_message_local, inject_type), false);

                // 3. Validazione del Nickname
                if (!Validation::Validate_Nickname(nickname, error_message_local))
                    return (Error_Utils::Show_Error(error_message_local, inject_type), false);

                // 4. Conversione da Wide-char a Local 8-bit (necessario per le API ANSI)
                std::string nickname_str = String_Utils::Wide_To_Local_8Bit(nickname);
                std::string ip_str = String_Utils::Wide_To_Local_8Bit(ip);
                std::string port_str = String_Utils::Wide_To_Local_8Bit(port);
                std::string password_str = String_Utils::Wide_To_Local_8Bit(password);
                // Converte anche i percorsi in std::string (richiesti da CreateProcessA come char*)
                std::string game_path_str = String_Utils::Wide_To_Local_8Bit(game_path.wstring());
                std::string folder_str = String_Utils::Wide_To_Local_8Bit(folder);
                std::string samp_DLL_path_str = String_Utils::Wide_To_Local_8Bit(samp_DLL_path.wstring());
                std::string omp_DLL_path_str = String_Utils::Wide_To_Local_8Bit(omp_DLL_path.wstring());

                // 5. Costruzione degli Argomenti della Riga di Comando
                std::string args = Build_Command_Args(nickname_str, ip_str, port_str, password_str);

                // Istanzia la classe Process per gestire le operazioni di processo
                Process process_core;
                
                // 6. Creazione del Processo del Gioco (Sospeso)
                auto process_info_opt = process_core.Create_Game_Process(game_path_str, args, folder_str);

                if (!process_info_opt)
                    return false; // L'errore è già stato visualizzato dalla funzione di creazione del processo

                // Derefenzia l'optional per ottenere la struttura Process_Info
                auto& process_info = *process_info_opt; 
                std::wstring inject_error_message; // Per ricevere i messaggi di errore dell'iniezione

                // 7. Iniezione della samp.dll
                if (!process_core.Inject_DLL(process_info.process_handle.get(), samp_DLL_path_str, inject_error_message))
                    return (Error_Utils::Show_Error(L"Impossibile iniettare samp.dll: " + inject_error_message, inject_type), false);

                // 8. Iniezione condizionale della omp-client.dll (solo se è OMP)
                if (inject_type == Types::Inject_Type::OMP) {
                    if (!process_core.Inject_DLL(process_info.process_handle.get(), omp_DLL_path_str, inject_error_message))
                        return (Error_Utils::Show_Error(L"Impossibile iniettare omp-client.dll: " + inject_error_message, inject_type), false);
                }

                // 9. Ripristino del Processo del Gioco
                // Il processo è stato creato in stato sospeso per consentire l'iniezione.
                // Ora che le DLL sono state iniettate, può essere ripreso.
                if (ResumeThread(process_info.thread_handle.get()) == static_cast<DWORD>(-1))
                    return (Error_Utils::Show_Error(L"Impossibile riprendere il thread del processo del gioco: " + Error_Utils::Get_System_Error_Message(GetLastError()), inject_type), false);

                return true; // Successo in tutte le fasi!
            }
        private:
            // Costruisce la stringa degli argomenti della riga di comando per l'eseguibile del gioco
            std::string Build_Command_Args(const std::string& nickname, const std::string& ip, const std::string& port, const std::string& password) {
                std::stringstream command_args_stream; // Usa stringstream per una costruzione efficiente

                // SA-MP e OMP si aspettano gli argomenti "-c -n [nickname] -h [ip] -p [port]"
                command_args_stream << Constants::CMD_ARG_CONFIG << " " 
                    << Constants::CMD_ARG_NICKNAME << " " << nickname << " " 
                    << Constants::CMD_ARG_HOST << " " << ip << " " 
                    << Constants::CMD_ARG_PORT << " " << port;

                // Aggiunge la password solo se non è vuota
                if (!password.empty())
                    command_args_stream << " " << Constants::CMD_ARG_PASSWORD << " " << password;

                return command_args_stream.str();
            }
    };
}
```

> [!CAUTION]
> Sebbene il processo per **OMP** comporti l'iniezione della `omp-client.dll` *in aggiunta* alla `samp.dll`, ciò è in linea con il modo in cui **OMP** generalmente funziona. Il client **OMP** spesso utilizza la `samp.dll` come **base** o **proxy** per alcune funzionalità, mentre la `omp-client.dll` estende o sovrascrive i comportamenti.
>
> È cruciale che **entrambe le DLL** siano presenti e funzionanti nella directory del gioco affinché l'**iniezione OMP** abbia successo. Se una fallisce, il gioco potrebbe non avviarsi correttamente o il client multiplayer potrebbe non caricarsi.

### `injector.hpp`

Questo è il file di interfaccia della libreria. È l'unico file che l'utente finale dovrà includere per utilizzare il **SA-MP Injector C++**. Funge da involucro per la classe `Injector::Injector_Core`, semplificando l'interfaccia in una singola funzione globale, `Initialize_Game`.

```cpp
#pragma once

#include <string_view>
//
#include "injector_core.hpp" // La classe principale con la logica
#include "error_utils.hpp" // Per la visualizzazione degli errori (in caso di tipo di iniezione non valido)
#include "types.hpp" // Enumerazione dei tipi
#include "constants.hpp" // Costanti (per i nomi dei tipi di iniezione)

// L'interfaccia di alto livello per la libreria.
// Semplifica l'uso esponendo solo questa funzione globale.
inline bool Initialize_Game(std::wstring_view inject_type_str, std::wstring_view folder, std::wstring_view nickname, std::wstring_view ip, std::wstring_view port, std::wstring_view password) {
    Types::Inject_Type type; // Variabile per memorizzare il tipo di iniezione

    // Converte la stringa del tipo di iniezione nell'enum Inject_Type
    if (inject_type_str == Constants::INJECT_TYPE_SAMP)
        type = Types::Inject_Type::SAMP;
    
    else if (inject_type_str == Constants::INJECT_TYPE_OMP)
        type = Types::Inject_Type::OMP;
    
    else
        // Se la stringa del tipo di iniezione è non valida, visualizza un errore e restituisce false
        return (Error_Utils::Show_Error(L"Modalità di iniezione specificata non valida. Per favore, usa 'samp' o 'omp'.", Types::Inject_Type::SAMP), false); // Usa SAMP come fallback per il titolo

    Injector::Injector_Core injector; // Istanzia l'oggetto che contiene la logica centrale
    
    // Delega la chiamata alla funzione Initialize_Game della classe Injector_Core
    return injector.Initialize_Game(type, folder, nickname, ip, port, password);
}
```

> [!NOTE]
> L'uso della parola chiave `inline` per tutte le funzioni in questo file e in altri file di utilità consente alla libreria di essere `header-only`. `inline` suggerisce al compilatore che il corpo della funzione deve essere inserito direttamente nei punti di chiamata, ma il suo effetto principale qui è rilassare la **One Definition Rule (ODR)** in modo che la funzione possa essere definita in più file `.obj` (che accadrebbe se più `.cpp` includessero `injector.hpp`). La fase di **linkage** garantirà che esista solo una versione finale nell'eseguibile.

## Esempi Completi di Utilizzo

Per integrare il **SA-MP Injector C++** nel tuo progetto, segui le istruzioni e analizza gli scenari qui sotto.

### 1. Preparazione dell'Ambiente di Sviluppo

- **Compilatore C++**: Si raccomanda un compilatore che **supporti C++17**. **Visual Studio** con `vcpkg` (per `std::filesystem`) o **GCC/Clang (versione 17+)** sono opzioni.
- **Configurazione del Progetto**:
  - Crea un nuovo progetto **C++** (ad esempio, un progetto di console).
  - Copia **tutti** i file `.hpp` del **SA-MP Injector C++** in una cartella accessibile al tuo progetto (es: nella cartella degli **header**).
  - Assicurati che lo **standard C++** sia configurato su **C++17**. È fondamentale mantenere questa versione per la massima compatibilità con le librerie di **SA-MP** e **OMP**. In **Visual Studio**: `Proprietà del Progetto > Proprietà di Configurazione > C/C++ > Lingua > Standard Linguaggio C++ -> "ISO C++17 Standard (/std:c++17)"`
- **Permessi**: Il tuo eseguibile probabilmente dovrà essere eseguito come **Amministratore (non necessariamente)** per creare processi e **iniettare DLL** nell'ambiente del sistema. In **Visual Studio**, questo può essere fatto in: `Proprietà del Progetto > Proprietà di Configurazione > Linker > File Manifesto > Livello di Esecuzione UAC -> "requireAdministrator (/LEVEL='requireAdministrator')"`

### 2. Scenario Base: Connessione a un Server SA-MP

Questo è il caso d'uso più comune, avviando il **GTA:SA** e connettendosi a un server **SA-MP** con un **nickname** e **IP**/**porta** specifici.

```cpp
// main.cpp
#include <iostream>
#include <string>
#include <codecvt> // Per std::wstring_convert (legacy, ma funzionale per questo caso)
#include <locale> // Per std::codecvt_utf8_to_utf16
//
#include "injector.hpp" // L'unica inclusione necessaria della libreria!

int Main(int argc, char* argv[]) {
    // Definire le variabili di configurazione
    // Modifica questi percorsi e dettagli del server per corrispondere alla tua configurazione locale
    std::wstring folder = L"C:\\Giochi\\GTA San Andreas"; // Dove si trovano gta_sa.exe, samp.dll
    std::wstring nickname = L"Nome";
    std::wstring ip = L"127.0.0.1"; // Esempio: il tuo server locale
    std::wstring port = L"7777";
    std::wstring password = L""; // Lascia vuoto se non c'è password

    // Opzionale: Permetti all'utente di fornire configurazioni tramite riga di comando (semplificato)
    // Per una gestione degli args più robusta, usa una libreria di parsing degli argomenti.
    if (argc > 1) {
        // Esempio: se il primo argomento è un percorso
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

    std::wcout << L"Avviando SA-MP..." << std::endl;
    std::wcout << L"Cartella del gioco: " << folder << std::endl;
    std::wcout << L"Nickname: " << nickname << std::endl;
    std::wcout << L"Server: " << ip << L":" << port << std::endl;

    // Chiamata alla funzione della libreria per avviare il gioco
    if (Initialize_Game(L"samp", // Tipo di iniezione: SA-MP
        folder, // Percorso della cartella del gioco
        nickname, // Nickname desiderato
        ip, // IP del server
        port, // Porta del server (stringa)
        password)) { // Password del server (stringa, può essere vuota)
        std::wcout << L"\n--- SA-MP avviato con successo! ---" << std::endl;
        std::wcout << L"Il gioco è stato avviato in un processo separato." << std::endl;
    }
    else {
        std::wcout << L"\n--- FALLIMENTO nell'avvio di SA-MP! ---" << std::endl;
        std::wcout << L"Verifica i messaggi di errore visualizzati." << std::endl;
    }

    // Mantiene la console aperta per visualizzare i messaggi di output
    std::wcout << L"\nPremi Invio per chiudere il programma." << std::endl;
    std::wcin.ignore();

    return 0;
}
```

**Per compilare ed eseguire:**

```bash
# Esempio con g++ (Linux/MinGW/MSYS2) - Richiede libstdc++fs per filesystem
# È importante garantire che il toolchain non utilizzi una versione di C++
# che introduca incompatibilità nel processo di iniezione.
# Verifica la documentazione specifica del tuo compilatore per le flag di compatibilità binaria (ABI).
g++ main.cpp -o my_launcher -std=c++17 -Wall -lstdc++fs -municode -lkernel32

# Esempio con MSVC (Prompt dei Comandi per Sviluppatori di Visual Studio)
# La flag '/std:c++17' garantisce la conformità con C++17.
cl /EHsc /std:c++17 /permissive- /FS /utf-8 main.cpp /link /OUT:my_launcher.exe
```

> [!NOTE]
> Il **SA-MP** e **OMP**, come progetti legacy, sono compilati con strumenti specifici che definiscono la loro **Application Binary Interface (ABI)**. Sebbene questa libreria utilizzi **C++17**, **è cruciale che le DLL di SA-MP e OMP con cui interagisce siano compatibili con l'ABI del tuo compilatore e della versione di runtime del C++ (CRT) che utilizzi**.
>
> Utilizzare un compilatore o una versione di **C++** molto diversa da quella usata per **costruire le DLL** del gioco può portare a problemi sottili (ad esempio, con l'allocazione della memoria o il passaggio dei parametri) che non sono facilmente **diagnosticabili** e non risulteranno in un errore esplicito dell'iniettore. Per questa ragione, **il C++17 è la versione massima consigliata**, poiché versioni più recenti potrebbero introdurre cambiamenti nell'**ABI** o nella **CRT** che non sono tollerati dai moduli di gioco più vecchi.

### 3. Scenario Avanzato: Connessione a un Server OMP

Per l'**OMP**, la logica è identica a quella di **SA-MP**, ma specifichi `L"omp"` come `inject_type` e assicuri che la `omp-client.dll` sia presente nella directory del gioco.

```cpp
// main.cpp
#include <iostream>
#include <string>
#include <codecvt> // Per std::wstring_convert (legacy, ma funzionale per questo caso)
#include <locale> // Per std::codecvt_utf8_to_utf16
//
#include "injector.hpp" // L'unica inclusione necessaria della libreria!

int Main() {
    // Definire le variabili di configurazione
    // Modifica questi percorsi e dettagli del server per corrispondere alla tua configurazione locale
    std::wstring folder = L"C:\\Giochi\\GTA San Andreas"; // Dove si trovano gta_sa.exe, samp.dll e omp-client.dll
    std::wstring nickname = L"Nome";
    std::wstring ip = L"127.0.0.1"; // Esempio: il tuo server locale
    std::wstring port = L"7777";
    std::wstring password = L""; // Lascia vuoto se non c'è password

    // Opzionale: Permetti all'utente di fornire configurazioni tramite riga di comando (semplificato)
    // Per una gestione degli args più robusta, usa una libreria di parsing degli argomenti.
    if (argc > 1) {
        // Esempio: se il primo argomento è un percorso
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

    std::wcout << L"Avviando OMP..." << std::endl;
    std::wcout << L"Cartella del gioco: " << folder << std::endl;
    std::wcout << L"Nickname: " << nickname << std::endl;
    std::wcout << L"Server: " << ip << L":" << port << std::endl;

    // Chiamata alla funzione della libreria per avviare il gioco
    if (Initialize_Game(L"omp", // Tipo di iniezione: OMP
        folder, // Percorso della cartella del gioco
        nickname, // Nickname desiderato
        ip, // IP del server
        port, // Porta del server (stringa)
        password)) { // Password del server (stringa, può essere vuota)
        std::wcout << L"\n--- OMP avviato con successo! ---" << std::endl;
        std::wcout << L"Il gioco è stato avviato in un processo separato." << std::endl;
    }
    else {
        std::wcout << L"\n--- FALLIMENTO nell'avvio di OMP! ---" << std::endl;
        std::wcout << L"Verifica i messaggi di errore visualizzati." << std::endl;
    }

    // Mantiene la console aperta per visualizzare i messaggi di output
    std::wcout << L"\nPremi Invio per chiudere il programma." << std::endl;
    std::wcin.ignore();

    return 0;
}
```

## Gestione degli Errori Comuni e Messaggi

Il **SA-MP Injector C++** dà priorità all'usabilità, e una parte fondamentale di ciò è fornire un **feedback** chiaro all'utente in caso di errore. I messaggi di errore vengono presentati attraverso finestre di **dialogo di Windows** (`MessageBoxW`) e sono categorizzati per tipo di **iniezione (SA-MP o OMP)** per un maggiore contesto. Questo garantisce che tu sappia esattamente cosa è andato storto e come affrontare la risoluzione.

Qui ci sono alcuni degli errori comuni che potresti incontrare e le loro probabili cause/soluzioni, accompagnati da esempi visivi di come appaiono queste finestre di dialogo per l'utente finale:

### 1. Tipo di Iniezione Non Valido

Se il `inject_type` fornito nella funzione `Initialize_Game` non è `L"samp"` o `L"omp"`, la libreria non saprà quale client multiplayer intendi avviare.

![Error 1](../../screenshots/error_1.png)

- **Messaggio di Errore Visualizzato**: `"Modalità di iniezione specificata non valida. Per favore, usa 'samp' o 'omp'."`
- **Causa**: Il primo argomento della funzione `Initialize_Game` (`std::wstring_view inject_type`) non corrisponde ai valori attesi di `L"samp"` o `L"omp"`. Potrebbe essere un errore di battitura, una stringa vuota o un valore non riconosciuto.
- **Soluzione**: Verifica che il `std::wstring_view inject_type_str` sia definito correttamente come `L"samp"` o `L"omp"`. È fondamentale usare il prefisso `L` per i letterali di **caratteri larghi** per garantire la compatibilità con le costanti della libreria.
    ```cpp
    // Corretto:
    Initialize_Game(L"samp", /* altri parametri */);
    Initialize_Game(L"omp", /* altri parametri */);

    // Errato (causerà un errore):
    // Initialize_Game(L"invalid", /* altri parametri */);
    // Initialize_Game(L"", /* altri parametri */);
    ```

### 2. Porta del Server Non Valida (Formato o Intervallo)

La porta è un parametro numerico essenziale per la connessione al server. Questo errore si verifica se il valore non può essere interpretato come un numero valido o è fuori dall'intervallo accettabile **(da 1 a 65535)**.

#### 2.1. Formato della Porta Non Numerico

![Error 2](../../screenshots/error_2.png)

- **Messaggio di Errore Visualizzato**: `"Formato della porta non valido. La porta deve essere un valore numerico. Per favore, fornisci un numero intero valido per la porta."`
- **Causa**: L'argomento `port` (`std::wstring_view`) contiene caratteri che non sono cifre numeriche o non può essere convertito in un numero intero.
- **Soluzione**: Fornisci una stringa che contenga solo cifre e rappresenti un numero intero valido.
    ```cpp
    // Corretto:
    Initialize_Game(/* altri parametri */, L"7777", /* altri parametri */);

    // Errato (formato non valido):
    // Initialize_Game(/* altri parametri */, L"port7777", /* altri parametri */);

    // Errato (non valido):
    // Initialize_Game(/* altri parametri */, L"invalid", /* altri parametri */);
    ```

#### 2.2. Porta Fuori dall'Intervallo Valido

![Error 3](../../screenshots/error_3.png)

- **Messaggio di Errore Visualizzato**: `"Il numero di porta specificato (XXXX) è fuori dall'intervallo valido di 1 a 65535. Per favore, fornisci una porta valida."` (Il **XXXX** sarà il valore che hai provato a usare).
- **Causa**: La porta fornita è un numero valido, ma è inferiore a `1` (riservato o non utilizzabile) o superiore a `65535` (limite massimo per le **porte TCP/UDP**).
- **Soluzione**: Fornisci una porta che sia all'interno dell'intervallo da `1` a `65535`. Le porte comuni per **SA-MP**/**OMP** sono `7777` o `7778`.
    ```cpp
    // Corretto:
    Initialize_Game(/* altri parametri */, L"7777", /* altri parametri */);

    // Errato (fuori dall'intervallo):
    // Initialize_Game(/* altri parametri */, L"0", /* altri parametri */); // Troppo basso
    // Initialize_Game(/* altri parametri */, L"65536", /* altri parametri */); // Troppo alto
    // Initialize_Game(/* altri parametri */, L"-1", /* altri parametri */); // Valore negativo
    ```

### 3. Nickname Non Valido (Vuoto o Troppo Lungo)

Il **nickname** del giocatore viene validato per garantire che il client del gioco lo accetti.

#### 3.1. Nickname Vuoto

![Error 4](../../screenshots/error_4.png)

- **Messaggio di Errore Visualizzato**: `"Il nickname non può essere vuoto. Per favore, fornisci un nickname valido."`
- **Causa**: L'argomento `nickname` (`std::wstring_view`) è stato fornito come una stringa vuota.
- **Soluzione**: Assicurati che il nickname non sia vuoto.
    ```cpp
    // Corretto:
    Initialize_Game(/* altri parametri */, L"Nome", /* altri parametri */);

    // Errato (vuoto):
    // Initialize_Game(/* altri parametri */, L"", /* altri parametri */);
    ```

#### 3.2. Nickname Troppo Lungo

![Error 5](../../screenshots/error_5.png)

- **Messaggio di Errore Visualizzato**: `"La lunghezza del nickname supera il massimo consentito di 23 caratteri. Per favore, usa un nickname più corto."`
- **Causa**: La lunghezza del **nickname** fornito supera `Constants::MAX_NICKNAME_LENGTH`, che è `23` caratteri.
- **Soluzione**: Usa un **nickname** che abbia al massimo `23` caratteri.
    ```cpp
    // Corretto:
    Initialize_Game(/* altri parametri */, L"Nome", /* altri parametri */);

    // Errato (troppo lungo):
    // Initialize_Game(/* altri parametri */, L"QuestoNicknameÈTroppoLungoESuperaVentiCaratteri", /* altri parametri */);
    ```

### 4. File del Gioco o DLL Non Trovati

Questa è una delle cause più comuni di fallimento. La libreria richiede che `gta_sa.exe`, `samp.dll` e, per **OMP**, `omp-client.dll` siano presenti nei luoghi attesi.

#### 4.1. Eseguibile del Gioco (`gta_sa.exe`) Non Trovato

![Error 6](../../screenshots/error_6.png)

- **Messaggio di Errore Visualizzato**: `"Eseguibile del gioco non trovato. Per favore, assicurati che 'gta_sa.exe' esista nel percorso specificato: [percorso completo]"`. Il `[percorso completo]` includerà la cartella e il nome del file.
- **Causa**: Il file `gta_sa.exe` non è stato trovato nella cartella fornita nell'argomento `folder`.
- **Soluzione**:
  1. Verifica che il `folder` (`std::wstring_view`) punti alla directory corretta di installazione del **GTA San Andreas**.
  2. Conferma che `gta_sa.exe` esista all'interno di quella cartella e che il suo nome non sia stato modificato.

#### 4.2. Libreria SA-MP (`samp.dll`) Non Trovata

![Error 7](../../screenshots/error_7.png)

- **Messaggio di Errore Visualizzato**: `"Libreria SA-MP non trovata. Per favore, assicurati che 'samp.dll' esista nel percorso specificato: [percorso completo]"`.
- **Causa**: Il file `samp.dll` non è stato trovato nella cartella fornita nell'argomento `folder`. **Questa DLL** è un requisito per **entrambi** i tipi di iniezione (`samp` e `omp`).
- **Soluzione**: Assicurati che il `samp.dll` sia presente nella cartella di installazione del **GTA San Andreas**.

#### 4.3. Libreria OMP (`omp-client.dll`) Non Trovata (solo per iniezione OMP)

![Error 8](../../screenshots/error_8.png)

- **Messaggio di Errore Visualizzato**: `"Libreria OMP non trovata. Per favore, assicurati che 'omp-client.dll' esista nel percorso specificato per l'iniezione OMP: [percorso completo]"`.
- **Causa**: Se hai specificato `L"omp"` come tipo di iniezione, ma il file `omp-client.dll` non è stato trovato nella cartella fornita.
- **Soluzione**: Scarica il client **OMP** più recente e assicurati che `omp-client.dll` (e `samp.dll`) siano presenti nella cartella di installazione del **GTA San Andreas**.

### 5. Fallimento nella Creazione del Processo del Gioco

Questo è un errore più complesso, poiché coinvolge **permessi del sistema operativo** e lo stato attuale del `gta_sa.exe`.

![Error 9](../../screenshots/error_9.png)

- **Messaggio di Errore Visualizzato**: `"Impossibile creare il processo del gioco. Assicurati che 'gta_sa.exe' non sia in esecuzione e che tu abbia sufficienti permessi per eseguire il file. Errore di sistema: [Messaggio di errore del sistema operativo]"`. Il messaggio del sistema sarà aggiunto da `GetLastError()` (es: `Accesso negato.` o `L'operazione richiesta richiede elevazione.`).
- **Causa**: La chiamata `CreateProcessA` per avviare il `gta_sa.exe` è fallita. Le cause comuni includono:
  - **Processo già in esecuzione**: Un'istanza di `gta_sa.exe` è già attiva e blocca una nuova esecuzione.
  - **Permessi insufficienti**: La tua applicazione non ha i privilegi necessari (es. amministratore) per creare un processo in determinate configurazioni di sistema (**UAC** attivato, cartelle protette, ecc.).
  - **Problemi con l'eseguibile**: Il `gta_sa.exe` potrebbe essere corrotto o bloccato da un altro programma (es: un antivirus mal configurato).
- **Soluzione**:
  1. Verifica nel Gestore delle Attività e assicurati che non ci siano istanze di `gta_sa.exe` in esecuzione. Termina qualsiasi istanza se presente.
  2. Esegui la tua applicazione che utilizza la libreria con privilegi di **Amministratore**. Fai clic con il tasto destro sull'eseguibile e seleziona **"Esegui come amministratore"**.
  3. Se un **antivirus** o un **software** di sicurezza sta interferendo, aggiungi la tua applicazione e/o la cartella del **GTA:SA** alle eccezioni dell'antivirus (fai questo con cautela e solo se sei sicuro dell'integrità dei tuoi file).

### 6. Fallimento nell'Allocazione della Memoria nel Processo Target

La libreria tenta di allocare un piccolo spazio di memoria nel `gta_sa.exe` per copiare il **percorso della DLL**.

![Error 10](../../screenshots/error_10.png)

- **Messaggio di Errore Visualizzato**: `"Impossibile allocare memoria nel processo target. Questo potrebbe essere dovuto a permessi insufficienti o meccanismi di protezione del processo."`
- **Causa**: La funzione `VirtualAllocEx` (utilizzata per allocare memoria all'interno di un altro processo) è fallita. Ciò è più probabile se:
  - Il processo del **GTA:SA** (anche se in stato sospeso) ha difese di sicurezza o **patch anti-iniezione** che impediscono l'allocazione di memoria da parte di processi esterni.
  - La tua applicazione non ha i permessi elevati necessari per manipolare la memoria di un altro processo.
  - (Meno comune) C'è un'estrema scarsità di memoria virtuale nel sistema.
- **Soluzione**:
  1. Esegui la tua applicazione con privilegi di **Amministratore**.
  2. Assicurati che il gioco non abbia modifiche o **patch di sicurezza** che potrebbero bloccare tentativi di iniezione o manipolazione della memoria (questo è più comune in ambienti modificati o con certe strumenti anti-cheat di terze parti).

### 7. Fallimento nella Scrittura del Percorso della DLL nella Memoria del Processo

Dopo aver allocato la memoria, la libreria tenta di copiare il **percorso della DLL** in essa.

![Error 11](../../screenshots/error_11.png)

- **Messaggio di Errore Visualizzato**: `"Impossibile scrivere il percorso della DLL nella memoria del processo target. Verifica i permessi del processo e assicurati che il percorso della DLL sia accessibile."`
- **Causa**: La funzione `WriteProcessMemory` è fallita nel tentativo di copiare i **byte del percorso della DLL** nella memoria remota allocata nel `gta_sa.exe`. Ciò generalmente indica:
  - **Permessi di scrittura**: La tua applicazione non ha il permesso di scrivere in quella regione di memoria o nel processo del **GTA:SA**.
  - **Handle non valido**: L'**handle** del processo (`process_handle`) è diventato in qualche modo non valido tra l'allocazione e la scrittura, il che è molto raro grazie all'uso di `UniqueResource` ma può verificarsi in condizioni estreme del sistema.
  - **Problemi di Protezione della Memoria**: Qualche protezione della memoria (del **SO** o delle modifiche del gioco) ha impedito la scrittura.
- **Soluzione**: Esegui come **Amministratore**. Verifica che il `gta_sa.exe` e il suo ambiente siano "puliti" da strumenti che potrebbero bloccare le operazioni di memoria.

### 8. Fallimento nel Trovare Funzioni Essenziali del Sistema

Queste sono **API** cruciali di **Windows**; errori qui indicano un problema fondamentale con il sistema operativo o l'ambiente di esecuzione.

#### 8.1. `kernel32.dll` Non Trovato

![Error 12](../../screenshots/error_12.png)

- **Messaggio di Errore Visualizzato**: `"Failed to obtain a handle to kernel32.dll. This is an essential system library and this error indicates a severe system issue."`
- **Causa**: Il `kernel32.dll` è una delle **DLL** più basilari di **Windows**, contenente funzioni essenziali come `CreateProcess`, `VirtualAllocEx`, ecc. Se `GetModuleHandleA` non riesce a ottenere un **handle** per essa, il sistema operativo ha problemi molto seri.
- **Soluzione**: Questo è un errore **critico** che raramente è causato dalla libreria o dalla tua applicazione. Suggerisce una corruzione dei file di sistema, problemi gravi con **Windows**, o un'installazione altamente insolita del **SO**. Si consiglia di eseguire controlli di integrità del sistema (come `sfc /scannow` nel **Prompt dei Comandi** come **Amministratore**) o, in ultima analisi, reinstallare **Windows**.

#### 8.2. `LoadLibraryA` Non Trovato

![Error 13](../../screenshots/error_13.png)

- **Messaggio di Errore Visualizzato**: `"Failed to find the address of the LoadLibraryA function in kernel32.dll. This is critical for injecting the DLL."`
- **Causa**: Sebbene `kernel32.dll` sia stato trovato, la funzione `LoadLibraryA` non è stata risolta tramite `GetProcAddress`. Sebbene estremamente raro, può essere il risultato di una corruzione del **file DLL** di `kernel32.dll` o di un ambiente di esecuzione altamente non standard.
- **Soluzione**: Come per l'errore di `kernel32.dll` sopra, questo indica un problema serio nel sistema operativo.

### 9. Fallimento nella Creazione di un Thread Remoto per l'Iniezione

Dopo aver preparato l'ambiente remoto e copiato il **percorso della DLL**, viene creato un nuovo **thread** nel processo del gioco per "chiamare" la `LoadLibraryA`.

![Error 14](../../screenshots/error_14.png)

- **Messaggio di Errore Visualizzato**: `"Failed to create a remote thread in the target process to execute the DLL injection. This could be due to security restrictions or process state. System Error: [Messaggio di errore del sistema operativo]"`.
- **Causa**: La chiamata `CreateRemoteThread` è fallita. Questo errore è comune in sistemi con difese **anti-iniezione** robuste o quando un programma monitora intensamente il comportamento del processo:
  - **Meccanismi di Sicurezza**: Strumenti **anti-cheat**, **software** di sicurezza o alcune politiche di **Windows** possono rilevare e bloccare tentativi di creare **thread** in processi di terze parti.
  - **Processo Target Incoerente**: Se il processo di **GTA:SA** si trova in uno stato imprevisto o instabile (sebbene avviato in `CREATE_SUSPENDED`), ciò può influire sulla capacità di creare **thread** in esso.
- **Soluzione**:
  1. Esegui la tua applicazione con privilegi di **Amministratore**.
  2. Verifica che non ci siano strumenti **anti-cheat**, **antivirus aggressivi** o **firewall** configurati per ispezionare e bloccare la manipolazione dei processi che possano essere in conflitto. Aggiungi la tua applicazione e il `gta_sa.exe` alle eccezioni, se applicabile (con cautela).
  3. Il messaggio di errore del sistema (`GetLastError()`) può fornire dettagli aggiuntivi per indagare sulla causa specifica (es: **"A process has been denied access to create threads for other processes."**).

### 10. Timeout o Fallimento nel Completamento dell'Iniezione

Dopo aver creato il **thread** remoto, l'iniettore aspetta che completi il **caricamento della DLL**.

![Error 15](../../screenshots/error_15.png)

- **Messaggio di Errore Visualizzato**: `"Timeout or error waiting for DLL injection to complete. System Error: [Messaggio di errore del sistema operativo]"`.
- **Causa**: Il **thread** remoto che esegue `LoadLibraryA` ha impiegato più di `Constants::DLL_INJECTION_TIMEOUT_MS` (10 secondi) per rispondere, oppure è fallito e `GetExitCodeThread` ha restituito 0. Le cause potenziali includono:
  - **Problemi nella DLL Iniettata**: La `DllMain` di `samp.dll` o `omp-client.dll` sta impiegando troppo tempo per eseguirsi, contiene un **ciclo infinito**, un **crash**, o un errore che **impedisce alla DLL** di caricarsi correttamente (es: **dipendenze di DLL** mancanti).
  - **Blocco Silenzioso**: Un meccanismo di sicurezza potrebbe aver bloccato `LoadLibraryA` senza notificare un errore evidente di creazione del **thread**.
- **Soluzione**:
  1. Verifica l'integrità dei file `samp.dll` e `omp-client.dll`. Potrebbero essere corrotti o di una versione incompatibile con il tuo `gta_sa.exe`.
  2. Assicurati che la **DLL iniettata** non dipenda da **altre DLL** che potrebbero essere mancanti o inaccessibili nel sistema.

### 11. Fallimento nel Ripristino del Thread del Processo del Gioco

Questo è il passo finale per avviare il gioco dopo che **le DLL** sono state iniettate.

![Error 16](../../screenshots/error_16.png)

- **Messaggio di Errore Visualizzato**: `"Failed to resume the game process thread: [Messaggio di errore del sistema operativo]"`.
- **Causa**: La chiamata `ResumeThread` è fallita, il che significa che il **thread** principale di `gta_sa.exe` non è stato attivato per avviare l'esecuzione del gioco. Questo è un errore raro, ma può verificarsi se:
  - Il **handle** del **thread** del processo è diventato non valido.
  - Il sistema operativo ha impedito la ripresa per qualche motivo, possibilmente legato a un'interruzione di sicurezza o a uno stato incoerente del processo.
  - Il processo potrebbe essere stato terminato esternamente tra l'**iniezione della DLL** e il tentativo di ripresa del **thread** principale.
- **Soluzione**: Se tutte le fasi precedenti hanno avuto successo e solo `ResumeThread` è fallito, potrebbe essere un problema con il sistema operativo, con l'installazione stessa di **GTA:SA**, o con un altro **software** di sicurezza molto rigoroso. Rivedi lo stato di `gta_sa.exe` tramite il **Task Manager** subito prima e dopo l'errore. Riavviare il computer potrebbe risolvere problemi temporanei dello stato del sistema.

> [!TIP]
> In scenari di debug complessi, strumenti come **Process Monitor (Sysinternals Suite)** o un debugger (come **Visual Studio Debugger**, **WinDbg**, **OllyDbg**) possono essere preziosi. Possono aiutare a osservare le chiamate di **API**, verificare errori di accesso, tracciare lo stato dei **handle** e persino ispezionare la memoria del processo, fornendo una visione approfondita di ciò che sta accadendo dietro le quinte.

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