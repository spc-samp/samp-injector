# SA-MP Injector C++

![License](https://img.shields.io/badge/License-MIT-yellow.svg?style=flat)
![C++17](https://img.shields.io/badge/C%2B%2B-17-blue.svg?style=flat&logo=cplusplus)
![Platform](https://img.shields.io/badge/Platform-Windows-0078D6.svg?style=flat&logo=windows)
[![SA-MP | OMP](https://img.shields.io/badge/Support-SA--MP%20%7C%20OMP-yellow)](https://github.com/spc-samp/samp-injector)
![Code Quality](https://img.shields.io/badge/Code%20Quality-High-brightgreen.svg?style=flat)

**SA-MP Injector C++** transcende la définition d’un simple outil d’**injection de DLL**. Il s’agit d’une **bibliothèque C++** soigneusement conçue, développée pour fournir une solution robuste et complète pour le lancement programmatique du jeu **Grand Theft Auto: San Andreas** (**GTA:SA**) en conjonction avec ses clients multijoueurs, spécifiquement **SA-MP (San Andreas Multiplayer)** et **OMP (Open Multiplayer)**. Son objectif principal est de simplifier le processus de lancement du jeu, en éliminant la complexité inhérente à la manipulation directe des processus du système d’exploitation et à la transmission des arguments en ligne de commande.

Développée dans le but d’offrir une flexibilité maximale et une intégration facilitée, cette bibliothèque **header-only** élimine le besoin de compilations préalables complexes, permettant aux développeurs de l’intégrer directement dans leurs **projets C++**. Elle orchestre non seulement l’**injection fondamentale des DLL** du client multijoueur (`samp.dll` ou `omp-client.dll`), mais gère également de manière intelligente tous les paramètres essentiels de connexion (**pseudonyme**, **adresse IP**, **port** et **mot de passe**), simulant un lancement natif grâce aux ressources intrinsèques de l’**API Windows**.

## Langues

- Português: [README](../../)
- Deutsch: [README](../Deutsch/README.md)
- English: [README](../English/README.md)
- Español: [README](../Espanol/README.md)
- Italiano: [README](../Italiano/README.md)
- Polski: [README](../Polski/README.md)
- Русский: [README](../Русский/README.md)
- Svenska: [README](../Svenska/README.md)
- Türkçe: [README](../Turkce/README.md)

## Table des matières

- [SA-MP Injector C++](#sa-mp-injector-c)
  - [Langues](#langues)
  - [Table des matières](#table-des-matières)
  - [Concepts fondamentaux et motivation](#concepts-fondamentaux-et-motivation)
    - [Pourquoi injecter des DLL ?](#pourquoi-injecter-des-dll-)
    - [SA-MP et OMP : Distinctions et similarités](#sa-mp-et-omp--distinctions-et-similarités)
  - [Architecture interne de la bibliothèque : Une immersion approfondie](#architecture-interne-de-la-bibliothèque--une-immersion-approfondie)
    - [`constants.hpp`](#constantshpp)
    - [`types.hpp`](#typeshpp)
    - [`string_utils.hpp`](#string_utilshpp)
    - [`error_utils.hpp`](#error_utilshpp)
    - [`resource_handle.hpp`](#resource_handlehpp)
    - [`validation.hpp`](#validationhpp)
    - [`process.hpp`](#processhpp)
    - [`injector_core.hpp`](#injector_corehpp)
    - [`injector.hpp`](#injectorhpp)
  - [Exemples complets d’utilisation](#exemples-complets-dutilisation)
    - [1. Préparation de l’environnement de développement](#1-préparation-de-lenvironnement-de-développement)
    - [2. Scénario de base : Connexion à un serveur SA-MP](#2-scénario-de-base--connexion-à-un-serveur-sa-mp)
    - [3. Scénario avancé : Connexion à un serveur OMP](#3-scénario-avancé--connexion-à-un-serveur-omp)
  - [Gestion des erreurs courantes et messages](#gestion-des-erreurs-courantes-et-messages)
    - [1. Type d’injection invalide](#1-type-dinjection-invalide)
    - [2. Port du serveur invalide (format ou plage)](#2-port-du-serveur-invalide-format-ou-plage)
      - [2.1. Format de port non numérique](#21-format-de-port-non-numérique)
      - [2.2. Port hors de la plage valide](#22-port-hors-de-la-plage-valide)
    - [3. Pseudonyme invalide (vide ou trop long)](#3-pseudonyme-invalide-vide-ou-trop-long)
      - [3.1. Pseudonyme vide](#31-pseudonyme-vide)
      - [3.2. Pseudonyme trop long](#32-pseudonyme-trop-long)
    - [4. Fichiers du jeu ou DLL introuvables](#4-fichiers-du-jeu-ou-dll-introuvables)
      - [4.1. Exécutable du jeu (`gta_sa.exe`) introuvable](#41-exécutable-du-jeu-gta_saexe-introuvable)
      - [4.2. Bibliothèque SA-MP (`samp.dll`) introuvable](#42-bibliothèque-sa-mp-sampdll-introuvable)
      - [4.3. Bibliothèque OMP (`omp-client.dll`) introuvable (uniquement pour l’injection OMP)](#43-bibliothèque-omp-omp-clientdll-introuvable-uniquement-pour-linjection-omp)
    - [5. Échec de la création du processus du jeu](#5-échec-de-la-création-du-processus-du-jeu)
    - [6. Échec de l’allocation de mémoire dans le processus cible](#6-échec-de-lallocation-de-mémoire-dans-le-processus-cible)
    - [7. Échec de l’écriture du chemin de la DLL dans la mémoire du processus](#7-échec-de-lécriture-du-chemin-de-la-dll-dans-la-mémoire-du-processus)
    - [8. Échec de la recherche des fonctions essentielles du système](#8-échec-de-la-recherche-des-fonctions-essentielles-du-système)
      - [8.1. `kernel32.dll` non trouvé](#81-kernel32dll-non-trouvé)
      - [8.2. `LoadLibraryA` non trouvé](#82-loadlibrarya-non-trouvé)
    - [9. Échec de la création d'un thread distant pour l'injection](#9-échec-de-la-création-dun-thread-distant-pour-linjection)
    - [10. Délai d'attente ou échec de la finalisation de l'injection](#10-délai-dattente-ou-échec-de-la-finalisation-de-linjection)
    - [11. Échec de la reprise du thread du processus du jeu](#11-échec-de-la-reprise-du-thread-du-processus-du-jeu)
  - [Licence](#licence)
    - [Conditions Générales d'Utilisation](#conditions-générales-dutilisation)
      - [1. Autorisations Accordées](#1-autorisations-accordées)
      - [2. Conditions Obligatoires](#2-conditions-obligatoires)
      - [3. Droits d'Auteur](#3-droits-dauteur)
      - [4. Exclusion de Garantie et Limitation de Responsabilité](#4-exclusion-de-garantie-et-limitation-de-responsabilité)

## Concepts fondamentaux et motivation

### Pourquoi injecter des DLL ?

> [!NOTE]
> L’**injection de DLL (Dynamic Link Library)** est une méthode utilisée dans les systèmes d’exploitation **Microsoft Windows** qui permet l’exécution de code à l’intérieur de l’espace mémoire d’un autre processus en cours d’exécution. C’est une technique puissante avec diverses applications légitimes, allant du débogage et de la surveillance de programmes à la modification du comportement des applications pour étendre leurs fonctionnalités.

Dans le contexte de jeux comme **GTA San Andreas**, qui n’ont pas été initialement développés avec une fonctionnalité multijoueur intégrée, l’**injection de DLL** est la base des clients multijoueurs comme **SA-MP** et **OMP**. Ces clients sont implémentés sous forme de **DLL** qui, une fois injectées dans le processus du `gta_sa.exe`, prennent le contrôle, interceptent les fonctions du jeu et établissent une communication avec les serveurs multijoueurs.

Au lieu de dépendre d’un lanceur externe ou de la modification directe de l’exécutable du jeu, l’**injection de DLL** permet un lancement plus flexible et programmable, particulièrement utile dans les environnements où l’on souhaite automatiser le processus de connexion à des serveurs spécifiques avec des configurations prédéfinies.

### SA-MP et OMP : Distinctions et similarités

**SA-MP** et **OMP** sont les deux principales plateformes multijoueurs pour **GTA San Andreas**. Tous deux fonctionnent comme des modifications du jeu de base, le transformant en un environnement multijoueur en ligne massivement connecté.

- **SA-MP (San Andreas Multiplayer)** : Le client original et le plus établi, largement utilisé depuis de nombreuses années. Son architecture nécessite la `samp.dll` pour fonctionner.
- **OMP (Open Multiplayer)** : Un projet open-source, généralement considéré comme un successeur ou une alternative plus moderne à **SA-MP**, offrant des améliorations en termes de performance, de stabilité et de fonctionnalités supplémentaires. Il nécessite la `omp-client.dll`.

Bien qu’ils fonctionnent de manière similaire (**en injectant une DLL** dans le processus du **GTA:SA**), la bibliothèque **SA-MP Injector C++** a été soigneusement développée pour prendre en charge **les deux DLL**, en reconnaissant leurs distinctions de noms de fichiers et en permettant au développeur de choisir le client multijoueur souhaité via un paramètre de configuration. Cela garantit que la bibliothèque peut être utilisée avec une vaste gamme de serveurs et de projets basés sur l’une ou l’autre des plateformes.

## Architecture interne de la bibliothèque : Une immersion approfondie

**SA-MP Injector C++** adopte une approche modulaire et orientée objet (lorsque cela est applicable) pour gérer la complexité du processus d’injection. Chaque fichier d’en-tête est un module spécialisé, responsable d’une partie spécifique de la fonctionnalité globale, favorisant la clarté du code, la maintenabilité et l’extensibilité.

### `constants.hpp`

Ce fichier constitue la base de toutes les configurations fixes de la bibliothèque. Il définit un espace de noms `Constants` pour encapsuler toutes les littérales, garantissant qu’il n’y a pas de pollution de l’espace de noms global. L’utilisation de `inline constexpr` est cruciale ici : `constexpr` indique que les valeurs sont évaluées au moment de la compilation, optimisant les performances et garantissant l’immutabilité, tandis que `inline` évite les problèmes de redéfinition lors de l’inclusion du fichier dans plusieurs unités de compilation.

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
    inline constexpr const char* LOAD_LIBRARY_FUNC = "LoadLibraryA"; // 'A' pour la version ANSI/8-bit
    
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
    inline constexpr const wchar_t* ERROR_TITLE_SAMP = L"Erreur de l'Injecteur SA-MP - SPC";
    inline constexpr const wchar_t* ERROR_TITLE_OMP = L"Erreur de l'Injecteur OMP - SPC";
    
    // Process creation flags for CreateProcessA
    inline constexpr DWORD PROCESS_CREATION_FLAGS = CREATE_SUSPENDED | DETACHED_PROCESS;
    
    // Timeouts for WaitForSingleObject (e.g., waiting for DLL injection)
    inline constexpr DWORD DLL_INJECTION_TIMEOUT_MS = 10000; // 10 secondes
    
    // Memory allocation flags for VirtualAllocEx
    inline constexpr DWORD MEMORY_ALLOCATION_TYPE = MEM_COMMIT | MEM_RESERVE;
    inline constexpr DWORD MEMORY_PROTECTION = PAGE_READWRITE; // Nécessaire pour écrire le chemin de la DLL
}
```

> [!TIP]
> L’utilisation de `wchar_t` pour les noms de fichiers et les titres des messages d’erreur est une pratique recommandée dans le **développement Windows**. Cela garantit la compatibilité avec toutes les langues et ensembles de caractères, particulièrement utile pour les chemins de fichiers pouvant contenir des **caractères Unicode**. Pour les **API** qui attendent `char` (comme `LoadLibraryA`), la conversion est effectuée explicitement dans `string_utils.hpp`.

### `types.hpp`

Un module concis, mais essentiel, pour définir l’énumération qui catégorise les types d’injection pris en charge. Cela améliore la lisibilité et la sécurité du type du code, en évitant les erreurs de chaînes ou d’entiers magiques.

```cpp
#pragma once

namespace Types {
    // Énumérations pour les types d’injection pris en charge
    enum class Inject_Type {
        SAMP, // San Andreas Multiplayer
        OMP // Open Multiplayer
    };
}
```

### `string_utils.hpp`

L’opération avec l’**API Windows** nécessite souvent la conversion entre différentes encodages de chaînes. Ce fichier fournit une fonction utilitaire vitale pour convertir des chaînes de **caractères larges** (`std::wstring_view`, utilisées dans les entrées de la bibliothèque) en chaînes **ANSI/8-bit** (`std::string`), nécessaires pour les fonctions **WinAPI** qui fonctionnent avec `char*` (comme `CreateProcessA` ou `GetProcAddress`).

```cpp
#pragma once

#include <string>
#include <string_view>
#include <windows.h> // Nécessaire pour WideCharToMultiByte

namespace Utils {
    inline std::string Wide_To_Local_8Bit(std::wstring_view wstr) {
        if (wstr.empty())
            return "";
        
        // Détermine la taille nécessaire pour le buffer de la chaîne résultante en char
        int size = WideCharToMultiByte(CP_ACP, // Page de code ANSI (dépendante du système local)
            0, // Pas de drapeaux supplémentaires
            wstr.data(), 
            static_cast<int>(wstr.size()), 
            nullptr, // Calcule la taille, ne remplit pas le buffer
            0, // Taille 0, uniquement pour le calcul
            nullptr, // Caractère par défaut pour les caractères non représentables
            nullptr); // Pointeur vers un booléen indiquant si un caractère par défaut a été utilisé

        if (size <= 0) // Retourne une chaîne vide en cas d’erreur ou de taille invalide
            return "";

        std::string result(size, 0); // Alloue la chaîne avec la taille déterminée
        // Effectue la conversion réelle, en remplissant le buffer 'result'
        WideCharToMultiByte(CP_ACP, 
            0, 
            wstr.data(), 
            static_cast<int>(wstr.size()), 
            result.data(), // Buffer de destination
            size, // Taille du buffer de destination
            nullptr, 
            nullptr);

        return result;
    }
}
```

> [!IMPORTANT]
> Le `CP_ACP` **(Page de code ANSI)** utilisé dans `WideCharToMultiByte` est la page de code par défaut du système **Windows**. Cela signifie que la conversion peut varier en fonction de la configuration linguistique du système de l’utilisateur. Pour la plupart des cas d’utilisation des noms de fichiers et des arguments en ligne de commande dans **SA-MP**/**OMP** (qui gèrent historiquement bien les chaînes **ANSI**), cette approche est généralement suffisante. Cependant, dans les scénarios nécessitant une compatibilité **Unicode** complète avec des systèmes externes ou des entrées globales, il serait nécessaire de convertir en **UTF-8** (`CP_UTF8`) ou d’autres pages de code. Pour l’étendue de ce projet, le `CP_ACP` est la norme fonctionnelle.

### `error_utils.hpp`

Un composant fondamental pour l’ergonomie de la bibliothèque, responsable de fournir un **retour clair** à l’utilisateur en cas d’échec. Il centralise la logique d’obtention des messages d’erreur du système et l’affichage des boîtes de dialogue.

```cpp
#pragma once

#include <string>
#include <string_view>
#include <windows.h> // Pour FormatMessageW et MessageBoxW
//
#include "types.hpp"
#include "constants.hpp"

namespace Utils {
    // Retourne le message d’erreur du système Windows pour un code d’erreur spécifique
    inline std::wstring Get_System_Error_Message(DWORD error_code) {
        wchar_t buffer[512] = {0}; // Buffer pour le message
        // FormatMessageW remplit le buffer avec la description de l’erreur du système
        DWORD result = FormatMessageW(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, 
            nullptr, // Source du message (du système)
            error_code, 
            0, // Langue (utiliser la langue par défaut)
            buffer, 
            512, // Taille du buffer
            nullptr);
        
        // Si la fonction réussit, retourne la chaîne du buffer ; sinon, un message générique
        return result ? std::wstring(buffer) : L"Erreur inconnue (Code : " + std::to_wstring(error_code) + L")";
    }

    // Affiche une boîte de message d’erreur à l’utilisateur
    inline void Show_Error(std::wstring_view message, Types::Inject_Type injectType) {
        // Choisit le titre de la boîte de dialogue en fonction du type d’injection
        std::wstring title = (injectType == Types::Inject_Type::SAMP) ? Constants::ERROR_TITLE_SAMP : Constants::ERROR_TITLE_OMP;
        MessageBoxW(nullptr, // Handle de la fenêtre parent (nullptr pour le bureau)
            message.data(), 
            title.c_str(), 
            MB_OK | MB_ICONERROR); // Bouton OK et icône d’erreur
    }
}
```

> [!NOTE]
> La fonction `FormatMessageW` est une **API Windows** puissante qui récupère la description textuelle d’un code d’erreur du système. Elle gère la localisation et fournit des messages clairs essentiels pour un **diagnostic** efficace, transformant un `DWORD` comme `ERROR_FILE_NOT_FOUND` (2) en `L"Le système ne peut pas trouver le fichier spécifié."`.

### `resource_handle.hpp`

La gestion sécurisée des ressources (comme les `HANDLE` de **Windows**) est cruciale pour éviter les fuites de ressources et les comportements indéfinis. Ce fichier définit un `UniqueResource` utilisant `std::unique_ptr` et une fonction personnalisée pour `CloseHandle`. Cela suit le principe **RAII (Resource Acquisition Is Initialization)**, garantissant que les `HANDLE` sont automatiquement fermés lorsque leurs **wrappers** sortent du champ d’application, même en cas d’exceptions.

```cpp
#pragma once

#include <memory> // Pour std::unique_ptr
#include <functional> // Pour std::function
#include <windows.h> // Pour HANDLE et CloseHandle

namespace Utils {
    // Alias de type pour un std::unique_ptr qui gère un HANDLE (ou pointeur) avec un destructeur personnalisé
    // T : Le type de ressource à gérer (ex : HANDLE, LPVOID)
    // Deleter : Une classe ou lambda qui sait comment libérer la ressource
    template<typename T, typename Deleter>
    using UniqueResource = std::unique_ptr<std::remove_pointer_t<T>, Deleter>;

    // Fonction auxiliaire pour créer une instance de UniqueResource pour les HANDLEs
    // Elle suppose que T est un type de handle et utilise CloseHandle comme destructeur.
    template<typename T>
    inline auto Make_Unique_Handle(T handle) {
        return UniqueResource<T, std::function<void(T)>>(handle, [](T h) {
            // Condition pour garantir que le handle est valide avant de tenter de le fermer
            // 0 et INVALID_HANDLE_VALUE sont considérés comme invalides pour la plupart des handles
            if (h && h != INVALID_HANDLE_VALUE)
                CloseHandle(h); // Libère le HANDLE du système d’exploitation
        });
    }
}
```

> [!IMPORTANT]
> L’utilisation de `UniqueResource` est une démonstration des bonnes pratiques du **C++ moderne** et du développement sécurisé sous **Windows**. Elle simplifie considérablement la gestion des cycles de vie des **handles**, qui, s’ils ne sont pas correctement fermés, peuvent entraîner des fuites de mémoire ou de ressources du **kernel**, affectant la stabilité du système à long terme.

### `validation.hpp`

La robustesse de l’injection commence par la validation des entrées de l’utilisateur et la vérification des dépendances des fichiers. Ce module contient des fonctions qui garantissent que tous les prérequis et paramètres sont corrects avant de tenter de lancer le processus d’injection, évitant ainsi des erreurs plus complexes par la suite.

```cpp
#pragma once

#include <string>
#include <string_view>
#include <filesystem> // Pour std::filesystem::exists
//
#include "constants.hpp"
#include "types.hpp"
#include "string_utils.hpp" // Pour Wide_To_Local_8Bit
#include "error_utils.hpp" // Pour Show_Error

namespace Utils {
    // Valide si une chaîne de port est un nombre valide et se trouve dans la plage autorisée
    inline bool Validate_Port(std::wstring_view port_str, std::wstring& error_message) {
        try {
            // Tente de convertir la chaîne de caractères larges en std::string, puis en int
            int port_num = std::stoi(Wide_To_Local_8Bit(port_str));

            // Vérifie si le port est dans la plage valide (1-65535)
            if (port_num < Constants::MIN_PORT || port_num > Constants::MAX_PORT)
                return (error_message = L"Le numéro de port spécifié (" + std::wstring(port_str) + 
                L") est hors de la plage valide de " +  std::to_wstring(Constants::MIN_PORT) + 
                L" à " + std::to_wstring(Constants::MAX_PORT) + 
                L". Veuillez fournir un port valide.", false);

            return true;
        }
        catch (...) { // Capture toute exception (comme std::invalid_argument pour non numérique)
            return (error_message = L"Format de port invalide. Le port doit être une valeur numérique. Veuillez fournir un entier valide pour le port.", false);
        }
    }

    // Valide le pseudonyme, vérifiant s’il n’est pas vide et si sa longueur est acceptable
    inline bool Validate_Nickname(std::wstring_view nickname_str, std::wstring& error_message) {
        if (nickname_str.empty())
            return (error_message = L"Le pseudonyme ne peut pas être vide. Veuillez fournir un pseudonyme valide.", false);
        
        if (nickname_str.size() > Constants::MAX_NICKNAME_LENGTH)
            return (error_message = L"La longueur du pseudonyme dépasse le maximum autorisé de " + 
                std::to_wstring(Constants::MAX_NICKNAME_LENGTH) + 
                L" caractères. Veuillez utiliser un pseudonyme plus court.", false);

        return true;
    }

    // Valide l’existence des fichiers critiques (gta_sa.exe, samp.dll, omp-client.dll)
    inline bool Validate_Files(const std::filesystem::path& game_path, 
        const std::filesystem::path& samp_DLL_path, 
        const std::filesystem::path& omp_DLL_path, 
        Types::Inject_Type inject_type) {
        std::wstring error_message_local; // Utilisons une variable locale ici avant de passer à Show_Error
        
        // Vérifie l’existence de l’exécutable du jeu
        if (!std::filesystem::exists(game_path)) {
            error_message_local = L"Exécutable du jeu introuvable. Veuillez vous assurer que 'gta_sa.exe' existe au chemin spécifié : " + game_path.wstring();
            Show_Error(error_message_local, inject_type);
            
            return false;
        }

        // Vérifie l’existence de samp.dll (essentiel pour les deux types d’injection)
        if (!std::filesystem::exists(samp_DLL_path)) {
            error_message_local = L"Bibliothèque SA-MP introuvable. Veuillez vous assurer que 'samp.dll' existe au chemin spécifié : " + samp_DLL_path.wstring();
            Show_Error(error_message_local, inject_type);

            return false;
        }

        // Si le type d’injection est OMP, vérifie l’existence de omp-client.dll
        if (inject_type == Types::Inject_Type::OMP && !std::filesystem::exists(omp_DLL_path)) {
            error_message_local = L"Bibliothèque OMP introuvable. Veuillez vous assurer que 'omp-client.dll' existe au chemin spécifié pour l’injection OMP : " + omp_DLL_path.wstring();
            Show_Error(error_message_local, inject_type);

            return false;
        }

        return true; // Tous les fichiers nécessaires ont été trouvés
    }
}
```

> [!NOTE]
> L’utilisation de `std::filesystem` est une addition moderne à **C++17** qui offre une manière puissante et indépendante de la plateforme d’interagir avec le système de fichiers. Pour ce projet sous **Windows**, elle simplifie le traitement des chemins et la vérification de l’existence des fichiers par rapport aux **API** plus anciennes de **WinAPI**.
>
> Assurez-vous que votre compilateur prend en charge **C++17** pour utiliser `std::filesystem`. Vous devrez configurer votre projet pour utiliser un standard **C++17** (`/std:c++17` dans **Visual Studio**).

### `process.hpp`

Ce module est le principal responsable de l’interaction directe avec les **API** de bas niveau de **Windows** pour manipuler les processus. Il encapsule les opérations cruciales de création de processus et d’**injection de DLL**, gérant les **handles**, la **mémoire** et les **threads**.

```cpp
#pragma once

#include <string_view>
#include <optional> // Pour std::optional
#include <functional> // Pour std::function (utilisé dans UniqueResource)
#include <windows.h> // API de Windows
#include <memory> // Pour std::unique_ptr
#include <vector> // Pour std::vector (buffer d’arguments)
//
#include "resource_handle.hpp" // Notre wrapper pour les HANDLEs
#include "error_utils.hpp" // Pour Get_System_Error_Message et Show_Error
#include "constants.hpp" // Constantes globales
#include "types.hpp" // Types d’injection

class Process {
    public:
        // Constructeurs/Destructeurs et opérateurs d’affectation
        // Explicitement par défaut et supprimés pour garantir la sémantique de valeur et uniquement mobile.
        Process() = default;
        Process(const Process&) = delete; // Pas de copie
        Process& operator=(const Process&) = delete; // Pas d’affectation de copie
        Process(Process&&) = default; // Sémantique de déplacement
        Process& operator=(Process&&) = default; // Affectation de déplacement
        ~Process() = default;

        // Structure pour stocker les handles du processus et du thread, gérés par UniqueResource
        struct Process_Info {
            Resource_Handle::UniqueResource<HANDLE, std::function<void(HANDLE)>> process_handle;
            Resource_Handle::UniqueResource<HANDLE, std::function<void(HANDLE)>> thread_handle;
        };

        // Crée le processus du jeu GTA:SA en état suspendu
        std::optional<Process_Info> Create_Game_Process(std::string_view game_path, std::string_view command_args, std::string_view working_dir) {
            STARTUPINFOA startup_info{}; // Structure pour les informations d’initialisation du processus
            startup_info.cb = sizeof(STARTUPINFOA); // Définit la taille de la structure

            PROCESS_INFORMATION process_info{}; // Structure qui recevra les informations sur le nouveau processus

            // Crée un buffer mutable pour les arguments de la ligne de commande.
            // CreateProcessA modifie le buffer de la ligne de commande, donc std::string_view directement ne fonctionne pas.
            std::vector<char> args_buffer(command_args.size() + 1); // +1 pour le terminateur nul

            if (!command_args.empty()) {
                std::memcpy(args_buffer.data(), command_args.data(), command_args.size());
                args_buffer[command_args.size()] = '\0'; // Garantit un terminateur nul
            }

            // Crée le processus
            bool success = CreateProcessA(game_path.data(), // Nom du module exécutable
                args_buffer.empty() ? nullptr : args_buffer.data(), // Arguments de la ligne de commande
                nullptr, // Attributs de sécurité du processus
                nullptr, // Attributs de sécurité du thread
                FALSE, // Ne pas hériter des handles
                Constants::PROCESS_CREATION_FLAGS, // CREATE_SUSPENDED | DETACHED_PROCESS
                nullptr, // Environnement du nouveau processus
                working_dir.empty() ? nullptr : working_dir.data(), // Répertoire de travail
                &startup_info, // Informations d’initialisation
                &process_info); // Informations du processus créé

            if (!success) {
                // Si échoué, obtient et affiche le message d’erreur du système
                std::wstring error_msg = Error_Utils::Get_System_Error_Message(GetLastError());
                Error_Utils::Show_Error(L"Échec de la création du processus du jeu. Assurez-vous que 'gta_sa.exe' n’est pas en cours d’exécution et que vous avez " L"les permissions suffisantes pour exécuter le fichier. Erreur système : " + error_msg, Types::Inject_Type::SAMP); // Utilise SAMP comme titre de secours
                
                return std::nullopt; // Retourne un optional vide
            }

            Process_Info result;
            // Stocke les handles du processus et du thread dans UniqueResource pour une gestion automatique
            result.process_handle = Resource_Handle::Make_Unique_Handle(process_info.hProcess);
            result.thread_handle = Resource_Handle::Make_Unique_Handle(process_info.hThread);

            return result; // Retourne la structure avec les handles gérés
        }

        // Injecte une DLL dans le processus distant
        bool Inject_DLL(HANDLE process, std::string_view DLL_path, std::wstring& error_message) {
            // Alloue de la mémoire dans le processus distant pour le chemin de la DLL
            LPVOID remote_memory = VirtualAllocEx(process, // Handle du processus cible
            nullptr, // Adresse préférentielle (nullptr pour laisser le système choisir)
            DLL_path.size() + 1, // Taille du chemin + terminateur nul
            Constants::MEMORY_ALLOCATION_TYPE, // MEM_COMMIT | MEM_RESERVE
            Constants::MEMORY_PROTECTION); // PAGE_READWRITE

            if (!remote_memory)
                return (error_message = L"Échec de l’allocation de mémoire dans le processus cible. Cela peut être dû à " L"des permissions insuffisantes ou à des mécanismes de protection du processus.", false);

            // Gestion des ressources pour la mémoire allouée à distance.
            // Sera automatiquement libérée à la sortie du champ d’application.
            auto memory_guard = Resource_Handle::UniqueResource<LPVOID, std::function<void(LPVOID)>>(remote_memory, 
                [process](LPVOID ptr) { // Lambda comme destructeur
                    if (ptr)
                        VirtualFreeEx(process, ptr, 0, MEM_RELEASE); // Libère la mémoire allouée
                }
            );

            // Écrit le chemin de la DLL dans la mémoire allouée à distance
            if (!WriteProcessMemory(process, remote_memory, DLL_path.data(), DLL_path.size() + 1, nullptr))
                return (error_message = L"Échec de l’écriture du chemin de la DLL dans la mémoire du processus cible. Vérifiez les permissions du processus " L"et assurez-vous que le chemin de la DLL est accessible.", false);

            // Obtient le handle pour kernel32.dll (qui est chargé dans le propre processus de l’injecteur)
            HMODULE kernel32 = GetModuleHandleA(Constants::KERNEL32_DLL);
            
            if (!kernel32)
                return (error_message = L"Échec de l’obtention d’un handle pour kernel32.dll. C’est une bibliothèque système essentielle et cette erreur indique un problème système grave.", false);

            // Obtient l’adresse de la fonction LoadLibraryA dans kernel32.dll.
            // Cette adresse est cohérente entre les processus dans le même système d’exploitation et est la clé de l’injection.
            LPVOID load_library_addr = reinterpret_cast<LPVOID>(GetProcAddress(kernel32, Constants::LOAD_LIBRARY_FUNC));

            if (!load_library_addr)
                return (error_message = L"Échec de la recherche de l’adresse de la fonction LoadLibraryA dans kernel32.dll. " L"Ceci est critique pour injecter la DLL.", false);

            // Crée un thread distant dans le processus cible pour exécuter LoadLibraryA
            // L’argument pour LoadLibraryA sera l’adresse distante du chemin de la DLL
            HANDLE remote_thread = CreateRemoteThread(process, // Handle du processus cible
                nullptr, // Attributs de sécurité du thread
                0, // Taille de la pile (0 pour par défaut)
                reinterpret_cast<LPTHREAD_START_ROUTINE>(load_library_addr), // Adresse de LoadLibraryA
                remote_memory, // Argument pour LoadLibraryA (chemin de la DLL)
                0, // Drapeaux de création (0 pour démarrer immédiatement)
                nullptr); // ID du thread (nullptr pour ne pas retourner)

            if (!remote_thread)
                return (error_message = L"Échec de la création d’un thread distant dans le processus cible pour exécuter " L"l’injection de DLL. Cela peut être dû à des restrictions de sécurité ou à l’état du processus. "
                    L"Erreur système : " + Error_Utils::Get_System_Error_Message(GetLastError()), false);

            // Gestion des ressources pour le handle du thread distant
            auto thread_guard = Resource_Handle::Make_Unique_Handle(remote_thread);

            // Attend que le thread distant (injection de DLL) soit terminé ou atteigne un timeout
            DWORD wait_result = WaitForSingleObject(remote_thread, Constants::DLL_INJECTION_TIMEOUT_MS);

            if (wait_result != WAIT_OBJECT_0) {
                return (error_message = L"Timeout ou erreur en attendant que l’injection de DLL soit terminée. " L"Erreur système : " + Error_Utils::Get_System_Error_Message(GetLastError()), false);

            // Obtient le code de sortie du thread distant.
            // Pour LoadLibraryA, un code de sortie 0 signifie un échec (impossible de charger la DLL).
            DWORD exit_code = 0;

            if (!GetExitCodeThread(remote_thread, &exit_code) || exit_code == 0)
                return (error_message = L"Échec de l’injection de DLL ou erreur retournée. L’appel à LoadLibrary " L"a peut-être échoué dans le processus cible.", false);

            return true; // Injection réussie
        }
};
```

> [!NOTE]
> Le module `process.hpp` démontre une conception robuste et sécurisée. La fonction `Create_Game_Process` retourne un `std::optional<Process_Info>`. Cela permet à la fonction de signaler explicitement et élégamment les échecs de création de processus (en retournant un `std::nullopt`) sans recourir à des exceptions ou à des codes d’erreur ambigus dans son retour principal.
>
> Plus crucial encore, la structure `Process_Info` utilise `Resource_Handle::UniqueResource<HANDLE, std::function<void(HANDLE)>>` pour encapsuler les **handles** du processus et du **thread**. C’est un exemple du modèle **RAII (Resource Acquisition Is Initialization)**, qui garantit que les `HANDLE` du système d’exploitation (comme `hProcess` et `hThread`) sont automatiquement fermés via `CloseHandle` lorsque l’objet `Process_Info` sort du champ d’application. Cela élimine les fuites de **handles**, qui sont une source courante d’instabilité et de consommation excessive de ressources dans les **applications Windows** à longue durée de vie.
>
> De manière similaire, dans la fonction `Inject_DLL`, `UniqueResource` est utilisé pour gérer la mémoire allouée à distance (`VirtualAllocEx`), garantissant qu’elle soit libérée (`VirtualFreeEx`) dès qu’elle n’est plus nécessaire ou en cas d’échec. Cette gestion rigoureuse des ressources contribue de manière significative à la fiabilité et à la stabilité de **SA-MP Injector C++**.

### `injector_core.hpp`

Cette classe est l’orchestrateur qui unit toutes les fonctionnalités des modules précédents. Elle coordonne la validation, la construction des arguments en ligne de commande, la création du processus et les appels d’**injection de DLL**.

```cpp
#pragma once

#include <string_view>
#include <sstream> // Pour construire des chaînes avec stringstream
#include <filesystem> // Pour la manipulation des chemins
//
#include "process.hpp" // Fonctions de création/injection de processus
#include "validation.hpp" // Fonctions de validation des entrées
#include "string_utils.hpp" // Fonctions de conversion de chaînes
#include "error_utils.hpp" // Fonctions de gestion des erreurs
#include "constants.hpp" // Constantes de la bibliothèque
#include "types.hpp" // Types d’injection

namespace Injector {
    class Injector_Core {
        public:
            // Constructeurs/Destructeurs pour la sémantique de déplacement
            Injector_Core() = default;
            Injector_Core(const Injector_Core&) = delete; // Désactive la copie
            Injector_Core& operator=(const Injector_Core&) = delete; // Désactive l’affectation de copie
            Injector_Core(Injector_Core&&) = default; // Active le déplacement
            Injector_Core& operator=(Injector_Core&&) = default; // Active l’affectation de déplacement
            ~Injector_Core() = default;

            // Fonction principale qui orchestre l’initialisation et l’injection du jeu
            bool Initialize_Game(Types::Inject_Type inject_type, std::wstring_view folder, std::wstring_view nickname, std::wstring_view ip, std::wstring_view port, std::wstring_view password) {
                namespace fs = std::filesystem; // Alias pour std::filesystem

                // Construit les chemins complets pour les fichiers essentiels
                fs::path game_path = fs::path(folder) / Constants::GAME_EXE_NAME; // Ex : C:\GTA\gta_sa.exe
                fs::path samp_DLL_path = fs::path(folder) / Constants::SAMP_DLL_NAME; // Ex : C:\GTA\samp.dll
                fs::path omp_DLL_path = fs::path(folder) / Constants::OMP_DLL_NAME; // Ex : C:\GTA\omp-client.dll

                // 1. Validation des fichiers
                if (!Validation::Validate_Files(game_path, samp_DLL_path, omp_DLL_path, inject_type))
                    return false; // L’erreur a déjà été affichée par la fonction de validation
                
                std::wstring error_message_local; // Pour recevoir les messages d’erreur des validations

                // 2. Validation du port
                if (!Validation::Validate_Port(port, error_message_local))
                    return (Error_Utils::Show_Error(error_message_local, inject_type), false);

                // 3. Validation du pseudonyme
                if (!Validation::Validate_Nickname(nickname, error_message_local))
                    return (Error_Utils::Show_Error(error_message_local, inject_type), false);

                // 4. Conversion de Wide-char en Local 8-bit (nécessaire pour les API ANSI)
                std::string nickname_str = String_Utils::Wide_To_Local_8Bit(nickname);
                std::string ip_str = String_Utils::Wide_To_Local_8Bit(ip);
                std::string port_str = String_Utils::Wide_To_Local_8Bit(port);
                std::string password_str = String_Utils::Wide_To_Local_8Bit(password);
                // Convertit également les chemins en std::string (requis par CreateProcessA comme char*)
                std::string game_path_str = String_Utils::Wide_To_Local_8Bit(game_path.wstring());
                std::string folder_str = String_Utils::Wide_To_Local_8Bit(folder);
                std::string samp_DLL_path_str = String_Utils::Wide_To_Local_8Bit(samp_DLL_path.wstring());
                std::string omp_DLL_path_str = String_Utils::Wide_To_Local_8Bit(omp_DLL_path.wstring());

                // 5. Construction des arguments de la ligne de commande
                std::string args = Build_Command_Args(nickname_str, ip_str, port_str, password_str);

                // Instancie la classe Process pour gérer les opérations de processus
                Process process_core;
                
                // 6. Création du processus du jeu (suspendu)
                auto process_info_opt = process_core.Create_Game_Process(game_path_str, args, folder_str);

                if (!process_info_opt)
                    return false; // L’erreur a déjà été affichée par la fonction de création de processus

                // Déréférence l’optional pour obtenir la structure Process_Info
                auto& process_info = *process_info_opt; 
                std::wstring inject_error_message; // Pour recevoir les messages d’erreur de l’injection

                // 7. Injection de samp.dll
                if (!process_core.Inject_DLL(process_info.process_handle.get(), samp_DLL_path_str, inject_error_message))
                    return (Error_Utils::Show_Error(L"Échec de l’injection de samp.dll : " + inject_error_message, inject_type), false);

                // 8. Injection conditionnelle de omp-client.dll (uniquement si OMP)
                if (inject_type == Types::Inject_Type::OMP) {
                    if (!process_core.Inject_DLL(process_info.process_handle.get(), omp_DLL_path_str, inject_error_message))
                        return (Error_Utils::Show_Error(L"Échec de l’injection de omp-client.dll : " + inject_error_message, inject_type), false);
                }

                // 9. Reprise du processus du jeu
                // Le processus a été créé en état suspendu pour permettre l’injection.
                // Maintenant que les DLL ont été injectées, il peut être repris.
                if (ResumeThread(process_info.thread_handle.get()) == static_cast<DWORD>(-1))
                    return (Error_Utils::Show_Error(L"Échec de la reprise du thread du processus du jeu : " + Error_Utils::Get_System_Error_Message(GetLastError()), inject_type), false);

                return true; // Succès à toutes les étapes !
            }
        private:
            // Construit la chaîne d’arguments de la ligne de commande pour l’exécutable du jeu
            std::string Build_Command_Args(const std::string& nickname, const std::string& ip, const std::string& port, const std::string& password) {
                std::stringstream command_args_stream; // Utilise stringstream pour une construction efficace

                // SA-MP et OMP attendent les arguments "-c -n [pseudonyme] -h [ip] -p [port]"
                command_args_stream << Constants::CMD_ARG_CONFIG << " " 
                    << Constants::CMD_ARG_NICKNAME << " " << nickname << " " 
                    << Constants::CMD_ARG_HOST << " " << ip << " " 
                    << Constants::CMD_ARG_PORT << " " << port;

                // Ajoute le mot de passe uniquement s’il n’est pas vide
                if (!password.empty())
                    command_args_stream << " " << Constants::CMD_ARG_PASSWORD << " " << password;

                return command_args_stream.str();
            }
    };
}
```

> [!CAUTION]
> Bien que le processus pour **OMP** implique d’injecter `omp-client.dll` *en plus* de `samp.dll`, cela est conforme à la manière dont **OMP** fonctionne généralement. Le client **OMP** utilise souvent `samp.dll` comme **base** ou **proxy** pour certaines fonctionnalités, tandis que `omp-client.dll` étend ou remplace les comportements.
>
> Il est crucial que **les deux DLL** soient présentes et fonctionnelles dans le répertoire du jeu pour que l’**injection OMP** réussisse. Si l’une échoue, le jeu peut ne pas s’initialiser correctement ou le client multijoueur peut ne pas se charger.

### `injector.hpp`

Ceci est le fichier d’interface de la bibliothèque. C’est le seul fichier que l’utilisateur final devra inclure pour utiliser **SA-MP Injector C++**. Il agit comme un wrapper pour la classe `Injector::Injector_Core`, simplifiant l’interface à une seule fonction globale, `Initialize_Game`.

```cpp
#pragma once

#include <string_view>
//
#include "injector_core.hpp" // La classe principale avec la logique
#include "error_utils.hpp" // Pour l’affichage des erreurs (en cas de type d’injection invalide)
#include "types.hpp" // Énumération des types
#include "constants.hpp" // Constantes (pour les noms des types d’injection)

// L’interface de haut niveau pour la bibliothèque.
// Simplifie l’utilisation en exposant uniquement cette fonction globale.
inline bool Initialize_Game(std::wstring_view inject_type_str, std::wstring_view folder, std::wstring_view nickname, std::wstring_view ip, std::wstring_view port, std::wstring_view password) {
    Types::Inject_Type type; // Variable pour stocker le type d’injection

    // Convertit la chaîne du type d’injection en l’énum Inject_Type
    if (inject_type_str == Constants::INJECT_TYPE_SAMP)
        type = Types::Inject_Type::SAMP;
    
    else if (inject_type_str == Constants::INJECT_TYPE_OMP)
        type = Types::Inject_Type::OMP;
    
    else
        // Si la chaîne du type d’injection est invalide, affiche une erreur et retourne false
        return (Error_Utils::Show_Error(L"Mode d’injection spécifié invalide. Veuillez utiliser 'samp' ou 'omp'.", Types::Inject_Type::SAMP), false); // Utilise SAMP comme titre de secours

    Injector::Injector_Core injector; // Instancie l’objet qui contient la logique centrale
    
    // Délègue l’appel à la fonction Initialize_Game de la classe Injector_Core
    return injector.Initialize_Game(type, folder, nickname, ip, port, password);
}
```

> [!NOTE]
> L’utilisation du mot-clé `inline` pour toutes les fonctions dans ce fichier et dans d’autres utilitaires permet à la bibliothèque d’être `header-only`. `inline` suggère au compilateur que le corps de la fonction doit être inséré directement aux points d’appel, mais son effet principal ici est de relâcher la **One Definition Rule (ODR)** pour que la fonction puisse être définie dans plusieurs fichiers `.obj` (ce qui arriverait si plusieurs `.cpp` incluaient `injector.hpp`). L’étape de **linkage** garantira qu’une seule version finale existe dans l’exécutable.

## Exemples complets d’utilisation

Pour intégrer **SA-MP Injector C++** dans votre projet, suivez les instructions et analysez les scénarios ci-dessous.

### 1. Préparation de l’environnement de développement

- **Compilateur C++** : Il est recommandé d’utiliser un compilateur qui **prend en charge C++17**. **Visual Studio** avec `vcpkg` (pour `std::filesystem`) ou **GCC/Clang (version 17+)** sont des options.
- **Configuration du projet** :
  - Créez un nouveau projet **C++** (par exemple, un projet de console).
  - Copiez **tous** les fichiers `.hpp` de **SA-MP Injector C++** dans un dossier accessible à votre projet (ex : dans le dossier des **headers**).
  - Assurez-vous que le **standard C++** est configuré pour **C++17**. Il est fondamental de maintenir cette version pour une compatibilité maximale avec les bibliothèques de **SA-MP** et **OMP**. Dans **Visual Studio** : `Propriétés du projet > Propriétés de configuration > C/C++ > Langage > Standard de langage C++ -> "ISO C++17 Standard (/std:c++17)"`
- **Permissions** : Votre exécutable devra probablement être exécuté en tant qu’**Administrateur (pas nécessairement)** pour créer des processus et **injecter des DLL** dans l’environnement du système. Dans **Visual Studio**, cela peut être fait dans : `Propriétés du projet > Propriétés de configuration > Linker > Fichier manifeste > Niveau d’exécution UAC -> "requireAdministrator (/LEVEL='requireAdministrator')"`

### 2. Scénario de base : Connexion à un serveur SA-MP

C’est le cas d’utilisation le plus courant, lançant **GTA:SA** et se connectant à un serveur **SA-MP** avec un **pseudonyme** et une **IP**/**port** spécifiques.

```cpp
// main.cpp
#include <iostream>
#include <string>
#include <codecvt> // Pour std::wstring_convert (héritage, mais fonctionnel pour ce cas)
#include <locale> // Pour std::codecvt_utf8_to_utf16
//
#include "injector.hpp" // La seule inclusion nécessaire de la bibliothèque !

int Main(int argc, char* argv[]) {
    // Définir les variables de configuration
    // Modifiez ces chemins et détails du serveur pour correspondre à votre configuration locale
    std::wstring folder = L"C:\\Jeux\\GTA San Andreas"; // Où se trouvent gta_sa.exe, samp.dll
    std::wstring nickname = L"Nom";
    std::wstring ip = L"127.0.0.1"; // Exemple : votre serveur local
    std::wstring port = L"7777";
    std::wstring password = L""; // Laissez vide s’il n’y a pas de mot de passe

    // Optionnel : Permettre à l’utilisateur de fournir des configurations via la ligne de commande (simplifié)
    // Pour un traitement plus robuste des arguments, utilisez une bibliothèque de parsing d’arguments.
    if (argc > 1) {
        // Exemple : si le premier argument est un chemin
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

    std::wcout << L"Démarrage de SA-MP..." << std::endl;
    std::wcout << L"Dossier du jeu : " << folder << std::endl;
    std::wcout << L"Pseudonyme : " << nickname << std::endl;
    std::wcout << L"Serveur : " << ip << L":" << port << std::endl;

    // Appel à la fonction de la bibliothèque pour démarrer le jeu
    if (Initialize_Game(L"samp", // Type d’injection : SA-MP
        folder, // Chemin du dossier du jeu
        nickname, // Pseudonyme souhaité
        ip, // IP du serveur
        port, // Port du serveur (chaîne)
        password)) { // Mot de passe du serveur (chaîne, peut être vide)
        std::wcout << L"\n--- SA-MP démarré avec succès ! ---" << std::endl;
        std::wcout << L"Le jeu a été lancé dans un processus séparé." << std::endl;
    }
    else {
        std::wcout << L"\n--- ÉCHEC du démarrage de SA-MP ! ---" << std::endl;
        std::wcout << L"Vérifiez les messages d’erreur affichés." << std::endl;
    }

    // Maintient la console ouverte pour visualiser les messages de sortie
    std::wcout << L"\nAppuyez sur Entrée pour fermer le programme." << std::endl;
    std::wcin.ignore();

    return 0;
}
```

**Pour compiler et exécuter :**

```bash
# Exemple avec g++ (Linux/MinGW/MSYS2) - Requiert libstdc++fs pour filesystem
# Il est important de s’assurer que la chaîne d’outils n’utilise pas une version de C++
# qui introduit des incompatibilités dans le processus d’injection.
# Vérifiez la documentation spécifique de votre compilateur pour les drapeaux de compatibilité binaire (ABI).
g++ main.cpp -o my_launcher -std=c++17 -Wall -lstdc++fs -municode -lkernel32

# Exemple avec MSVC (Invite de commande pour développeurs Visual Studio)
# Le drapeau '/std:c++17' garantit la conformité avec C++17.
cl /EHsc /std:c++17 /permissive- /FS /utf-8 main.cpp /link /OUT:my_launcher.exe
```

> [!NOTE]
> **SA-MP** et **OMP**, en tant que projets hérités, sont compilés avec des outils spécifiques qui définissent leur **Interface Binaire d’Application (ABI)**. Bien que cette bibliothèque utilise **C++17**, **il est crucial que les DLL de SA-MP et OMP avec lesquelles elle interagit soient également compatibles avec l’ABI de votre compilateur et de la version de la bibliothèque d’exécution C++ (CRT) que vous utilisez**.
>
> L’utilisation d’un compilateur ou d’une version de **C++** très différente de celle utilisée pour **construire les DLL** du jeu peut entraîner des problèmes subtils (par exemple, avec l’allocation de mémoire ou le passage de paramètres) qui ne sont pas facilement **diagnostiquables** et ne provoqueront pas une erreur explicite de l’injecteur. Pour cette raison, **C++17 est la version maximale recommandée**, car des versions plus récentes peuvent introduire des changements dans l’**ABI** ou la **CRT** qui ne sont pas tolérés par les modules de jeu plus anciens.

### 3. Scénario avancé : Connexion à un serveur OMP

Pour **OMP**, la logique est identique à celle de **SA-MP**, mais vous spécifiez `L"omp"` comme `inject_type` et vous assurez que `omp-client.dll` est présent dans le répertoire du jeu.

```cpp
// main.cpp
#include <iostream>
#include <string>
#include <codecvt> // Pour std::wstring_convert (héritage, mais fonctionnel pour ce cas)
#include <locale> // Pour std::codecvt_utf8_to_utf16
//
#include "injector.hpp" // La seule inclusion nécessaire de la bibliothèque !

int Main() {
    // Définir les variables de configuration
    // Modifiez ces chemins et détails du serveur pour correspondre à votre configuration locale
    std::wstring folder = L"C:\\Jeux\\GTA San Andreas"; // Où se trouvent gta_sa.exe, samp.dll et omp-client.dll
    std::wstring nickname = L"Nom";
    std::wstring ip = L"127.0.0.1"; // Exemple : votre serveur local
    std::wstring port = L"7777";
    std::wstring password = L""; // Laissez vide s’il n’y a pas de mot de passe

    // Optionnel : Permettre à l’utilisateur de fournir des configurations via la ligne de commande (simplifié)
    // Pour un traitement plus robuste des arguments, utilisez une bibliothèque de parsing d’arguments.
    if (argc > 1) {
        // Exemple : si le premier argument est un chemin
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

    std::wcout << L"Démarrage de OMP..." << std::endl;
    std::wcout << L"Dossier du jeu : " << folder << std::endl;
    std::wcout << L"Pseudonyme : " << nickname << std::endl;
    std::wcout << L"Serveur : " << ip << L":" << port << std::endl;

    // Appel à la fonction de la bibliothèque pour démarrer le jeu
    if (Initialize_Game(L"omp", // Type d’injection : OMP
        folder, // Chemin du dossier du jeu
        nickname, // Pseudonyme souhaité
        ip, // IP du serveur
        port, // Port du serveur (chaîne)
        password)) { // Mot de passe du serveur (chaîne, peut être vide)
        std::wcout << L"\n--- OMP démarré avec succès ! ---" << std::endl;
        std::wcout << L"Le jeu a été lancé dans un processus séparé." << std::endl;
    }
    else {
        std::wcout << L"\n--- ÉCHEC du démarrage de OMP ! ---" << std::endl;
        std::wcout << L"Vérifiez les messages d’erreur affichés." << std::endl;
    }

    // Maintient la console ouverte pour visualiser les messages de sortie
    std::wcout << L"\nAppuyez sur Entrée pour fermer le programme." << std::endl;
    std::wcin.ignore();

    return 0;
}
```

## Gestion des erreurs courantes et messages

**SA-MP Injector C++** privilégie l’ergonomie, et une partie essentielle de cela est de fournir un **retour clair** à l’utilisateur en cas d’échec. Les messages d’erreur sont présentés via des boîtes de **dialogue Windows** (`MessageBoxW`) et sont catégorisés par le type d’**injection (SA-MP ou OMP)** pour plus de contexte. Cela garantit que vous sachiez exactement ce qui a mal tourné et comment résoudre le problème.

Voici quelques-unes des erreurs courantes que vous pouvez rencontrer et leurs causes probables/solutions, accompagnées d’exemples visuels de l’apparence de ces boîtes de dialogue pour l’utilisateur final :

### 1. Type d’injection invalide

Si le `inject_type` fourni dans la fonction `Initialize_Game` n’est pas `L"samp"` ou `L"omp"`, la bibliothèque ne saura pas quel client multijoueur vous souhaitez initialiser.

![Error 1](../../screenshots/error_1.png)

- **Message d’erreur affiché** : `"Mode d’injection spécifié invalide. Veuillez utiliser 'samp' ou 'omp'."`
- **Cause** : Le premier argument de la fonction `Initialize_Game` (`std::wstring_view inject_type`) ne correspond pas aux valeurs attendues de `L"samp"` ou `L"omp"`. Cela peut être une erreur de frappe, une chaîne vide ou une valeur non reconnue.
- **Solution** : Vérifiez que le `std::wstring_view inject_type_str` est correctement défini comme `L"samp"` ou `L"omp"`. Il est essentiel d’utiliser le préfixe `L` pour les littéraux de **caractères larges** lors de la définition des chaînes pour la compatibilité avec les constantes de la bibliothèque.
    ```cpp
    // Correct :
    Initialize_Game(L"samp", /* autres paramètres */);
    Initialize_Game(L"omp", /* autres paramètres */);

    // Incorrect (provoquera une erreur) :
    // Initialize_Game(L"invalid", /* autres paramètres */);
    // Initialize_Game(L"", /* autres paramètres */);
    ```

### 2. Port du serveur invalide (format ou plage)

Le port est un paramètre numérique essentiel pour la connexion au serveur. Cette erreur se produit si la valeur ne peut pas être interprétée comme un nombre valide ou si elle est hors de la plage acceptable **(1 à 65535)**.

#### 2.1. Format de port non numérique

![Error 2](../../screenshots/error_2.png)

- **Message d’erreur affiché** : `"Format de port invalide. Le port doit être une valeur numérique. Veuillez fournir un entier valide pour le port."`
- **Cause** : L’argument `port` (`std::wstring_view`) contient des caractères qui ne sont pas des chiffres numériques ou ne peut pas être converti en un nombre entier.
- **Solution** : Fournissez une chaîne contenant uniquement des chiffres et représentant un nombre entier valide.
    ```cpp
    // Correct :
    Initialize_Game(/* autres paramètres */, L"7777", /* autres paramètres */);

    // Incorrect (format invalide) :
    // Initialize_Game(/* autres paramètres */, L"port7777", /* autres paramètres */);

    // Incorrect (invalide) :
    // Initialize_Game(/* autres paramètres */, L"invalid", /* autres paramètres */);
    ```

#### 2.2. Port hors de la plage valide

![Error 3](../../screenshots/error_3.png)

- **Message d’erreur affiché** : `"Le numéro de port spécifié (XXXX) est hors de la plage valide de 1 à 65535. Veuillez fournir un port valide."` (Le **XXXX** sera la valeur que vous avez essayé d’utiliser).
- **Cause** : Le port fourni est un nombre valide, mais il est inférieur à `1` (réservé ou non utilisable) ou supérieur à `65535` (limite maximale pour les **ports TCP/UDP**).
- **Solution** : Fournissez un port qui se trouve dans la plage de `1` à `65535`. Les ports courants pour **SA-MP**/**OMP** sont `7777` ou `7778`.
    ```cpp
    // Correct :
    Initialize_Game(/* autres paramètres */, L"7777", /* autres paramètres */);

    // Incorrect (hors plage) :
    // Initialize_Game(/* autres paramètres */, L"0", /* autres paramètres */); // Trop bas
    // Initialize_Game(/* autres paramètres */, L"65536", /* autres paramètres */); // Trop haut
    // Initialize_Game(/* autres paramètres */, L"-1", /* autres paramètres */); // Valeur négative
    ```

### 3. Pseudonyme invalide (vide ou trop long)

Le **pseudonyme** du joueur est validé pour garantir qu’il soit accepté par le client du jeu.

#### 3.1. Pseudonyme vide

![Error 4](../../screenshots/error_4.png)

- **Message d’erreur affiché** : `"Le pseudonyme ne peut pas être vide. Veuillez fournir un pseudonyme valide."`
- **Cause** : L’argument `nickname` (`std::wstring_view`) a été fourni comme une chaîne vide.
- **Solution** : Assurez-vous que le pseudonyme ne soit pas vide.
    ```cpp
    // Correct :
    Initialize_Game(/* autres paramètres */, L"Nom", /* autres paramètres */);

    // Incorrect (vide) :
    // Initialize_Game(/* autres paramètres */, L"", /* autres paramètres */);
    ```

#### 3.2. Pseudonyme trop long

![Error 5](../../screenshots/error_5.png)

- **Message d’erreur affiché** : `"La longueur du pseudonyme dépasse le maximum autorisé de 23 caractères. Veuillez utiliser un pseudonyme plus court."`
- **Cause** : La longueur du **pseudonyme** fourni dépasse `Constants::MAX_NICKNAME_LENGTH`, qui est de `23` caractères.
- **Solution** : Utilisez un **pseudonyme** qui a au maximum `23` caractères.
    ```cpp
    // Correct :
    Initialize_Game(/* autres paramètres */, L"Nom", /* autres paramètres */);

    // Incorrect (trop long) :
    // Initialize_Game(/* autres paramètres */, L"CePseudoEstTropLongEtDepasseVingtCaracteres", /* autres paramètres */);
    ```

### 4. Fichiers du jeu ou DLL introuvables

C’est l’une des causes les plus courantes d’échec. La bibliothèque nécessite que `gta_sa.exe`, `samp.dll` et, pour **OMP**, `omp-client.dll` soient présents aux emplacements attendus.

#### 4.1. Exécutable du jeu (`gta_sa.exe`) introuvable

![Error 6](../../screenshots/error_6.png)

- **Message d’erreur affiché** : `"Exécutable du jeu introuvable. Veuillez vous assurer que 'gta_sa.exe' existe au chemin spécifié : [chemin complet]"`. Le `[chemin complet]` inclura le dossier et le nom du fichier.
- **Cause** : Le fichier `gta_sa.exe` n’a pas été trouvé dans le dossier fourni dans l’argument `folder`.
- **Solution** :
  1. Vérifiez que le `folder` (`std::wstring_view`) pointe vers le répertoire correct de l’installation de **GTA San Andreas**.
  2. Confirmez que `gta_sa.exe` existe dans ce dossier et que son nom n’a pas été modifié.

#### 4.2. Bibliothèque SA-MP (`samp.dll`) introuvable

![Error 7](../../screenshots/error_7.png)

- **Message d’erreur affiché** : `"Bibliothèque SA-MP introuvable. Veuillez vous assurer que 'samp.dll' existe au chemin spécifié : [chemin complet]"`.
- **Cause** : Le fichier `samp.dll` n’a pas été trouvé dans le dossier fourni dans l’argument `folder`. **Cette DLL** est un prérequis pour **les deux** types d’injection (`samp` et `omp`).
- **Solution** : Assurez-vous que `samp.dll` est présent dans le dossier d’installation de **GTA San Andreas**.

#### 4.3. Bibliothèque OMP (`omp-client.dll`) introuvable (uniquement pour l’injection OMP)

![Error 8](../../screenshots/error_8.png)

- **Message d’erreur affiché** : `"Bibliothèque OMP introuvable. Veuillez vous assurer que 'omp-client.dll' existe au chemin spécifié pour l’injection OMP : [chemin complet]"`.
- **Cause** : Si vous avez spécifié `L"omp"` comme type d’injection, mais que le fichier `omp-client.dll` n’a pas été trouvé dans le dossier fourni.
- **Solution** : Téléchargez le client **OMP** le plus récent et assurez-vous que `omp-client.dll` (et `samp.dll`) soient présents dans le dossier d’installation de **GTA San Andreas**.

### 5. Échec de la création du processus du jeu

C’est une erreur plus complexe, car elle implique les **permissions du système d’exploitation** et l’état actuel de `gta_sa.exe`.

![Error 9](../../screenshots/error_9.png)

- **Message d’erreur affiché** : `"Échec de la création du processus du jeu. Assurez-vous que 'gta_sa.exe' n’est pas en cours d’exécution et que vous avez les permissions suffisantes pour exécuter le fichier. Erreur système : [Message d’erreur du système d’exploitation]"`. Le message du système sera ajouté par `GetLastError()` (ex : `Accès refusé.` ou `L’opération demandée nécessite une élévation.`).
- **Cause** : L’appel `CreateProcessA` pour démarrer `gta_sa.exe` a échoué. Les causes courantes incluent :
  - **Processus déjà en cours d’exécution** : Une instance de `gta_sa.exe` est déjà active et bloque une nouvelle exécution.
  - **Permissions insuffisantes** : Votre application n’a pas les privilèges nécessaires (ex : administrateur) pour créer un processus dans certaines configurations du système (**UAC** activé, dossiers protégés, etc.).
  - **Problèmes avec l’exécutable** : `gta_sa.exe` peut être corrompu ou bloqué par un autre programme (ex : un antivirus mal configuré).
- **Solution** :
  1. Vérifiez le Gestionnaire des tâches et assurez-vous qu’aucune instance de `gta_sa.exe` n’est en cours d’exécution. Terminez-en une s’il y en a.
  2. Exécutez votre application qui utilise la bibliothèque avec des privilèges d’**Administrateur**. Cliquez avec le bouton droit sur l’exécutable et sélectionnez **"Exécuter en tant qu’administrateur"**.
  3. Si un **antivirus** ou un **logiciel** de sécurité interfère, ajoutez votre application et/ou le dossier de **GTA:SA** aux exceptions de l’antivirus (faites cela avec prudence et uniquement si vous êtes sûr de l’intégrité de vos fichiers).

### 6. Échec de l’allocation de mémoire dans le processus cible

La bibliothèque tente d’allouer un petit espace de mémoire dans `gta_sa.exe` pour copier le **chemin de la DLL**.

![Error 10](../../screenshots/error_10.png)

- **Message d’erreur affiché** : `"Échec de l’allocation de mémoire dans le processus cible. Cela peut être dû à des permissions insuffisantes ou à des mécanismes de protection du processus."`
- **Cause** : La fonction `VirtualAllocEx` (utilisée pour allouer de la mémoire dans un autre processus) a échoué. Cela est plus probable si :
  - Le processus de **GTA:SA** (même en état suspendu) possède des défenses de sécurité ou des **patches anti-injection** qui empêchent l’allocation de mémoire par des processus externes.
  - Votre application n’a pas les permissions élevées nécessaires pour manipuler la mémoire d’un autre processus.
  - (Moins courant) Il y a une pénurie extrême de mémoire virtuelle dans le système.
- **Solution** :
  1. Exécutez votre application avec des privilèges d’**Administrateur**.
  2. Assurez-vous que le jeu n’a pas de modifications ou de **patchs de sécurité** qui pourraient bloquer les tentatives d’injection ou de manipulation de mémoire (cela est plus courant dans les environnements modifiés ou avec certaines outils anti-triche tiers).

### 7. Échec de l’écriture du chemin de la DLL dans la mémoire du processus

Après avoir alloué la mémoire, la bibliothèque tente de copier le **chemin de la DLL** dans celle-ci.

![Error 11](../../screenshots/error_11.png)

- **Message d’erreur affiché** : `"Échec de l’écriture du chemin de la DLL dans la mémoire du processus cible. Vérifiez les permissions du processus et assurez-vous que le chemin de la DLL est accessible."`
- **Cause** : La fonction `WriteProcessMemory` a échoué à copier les **octets du chemin de la DLL** dans la mémoire distante allouée dans `gta_sa.exe`. Cela indique généralement :
  - **Permissions d’écriture** : Votre application n’a pas la permission d’écrire dans cette région de mémoire ou dans le processus de **GTA:SA**.
  - **Handle invalide** : Le **handle** du processus (`process_handle`) est devenu invalide entre l’allocation et l’écriture, ce qui est très rare grâce à l’utilisation de `UniqueResource`, mais peut se produire dans des conditions extrêmes du système.
  - **Problèmes de protection de mémoire** : Une protection de mémoire (soit du **système d’exploitation**, soit des modifications du jeu) a empêché l’écriture.
- **Solution** : Exécutez en tant qu’**Administrateur**. Vérifiez que `gta_sa.exe` et son environnement sont "propres" de tout logiciel qui pourrait bloquer les opérations de mémoire.

### 8. Échec de la recherche des fonctions essentielles du système

Ce sont des **APIs** cruciales de **Windows** ; des erreurs ici indiquent un problème fondamental avec le système d'exploitation ou l'environnement d'exécution.

#### 8.1. `kernel32.dll` non trouvé

![Error 12](../../screenshots/error_12.png)

- **Message d'erreur affiché** : `"Failed to obtain a handle to kernel32.dll. This is an essential system library and this error indicates a severe system issue."`
- **Cause** : Le `kernel32.dll` est l'une des **DLLs** les plus fondamentales de **Windows**, contenant des fonctions essentielles telles que `CreateProcess`, `VirtualAllocEx`, etc. Si `GetModuleHandleA` ne parvient pas à obtenir un **handle** pour celle-ci, le système d'exploitation présente des problèmes très graves.
- **Solution** : Il s'agit d'une erreur **critique** rarement causée par la bibliothèque ou votre application. Elle suggère une corruption des fichiers système, des problèmes graves avec **Windows**, ou une installation hautement inhabituelle du **système d'exploitation**. Il est recommandé d'exécuter des vérifications de l'intégrité du système (comme `sfc /scannow` dans l'**Invite de commandes** en tant qu'**Administrateur**) ou, en dernier recours, de réinstaller **Windows**.

#### 8.2. `LoadLibraryA` non trouvé

![Error 13](../../screenshots/error_13.png)

- **Message d'erreur affiché** : `"Failed to find the address of the LoadLibraryA function in kernel32.dll. This is critical for injecting the DLL."`
- **Cause** : Bien que `kernel32.dll` ait été trouvé, la fonction `LoadLibraryA` n'a pas pu être résolue via `GetProcAddress`. Bien que cela soit extrêmement rare, cela peut résulter d'une corruption du **fichier DLL** de `kernel32.dll` ou d'un environnement d'exécution hautement non standard.
- **Solution** : Comme pour l'erreur de `kernel32.dll` ci-dessus, cela indique un problème sérieux dans le système d'exploitation.

### 9. Échec de la création d'un thread distant pour l'injection

Après avoir préparé l'environnement distant et copié le **chemin de la DLL**, un nouveau **thread** est créé dans le processus du jeu pour "appeler" la `LoadLibraryA`.

![Error 14](../../screenshots/error_14.png)

- **Message d'erreur affiché** : `"Failed to create a remote thread in the target process to execute the DLL injection. This could be due to security restrictions or process state. System Error: [Message d'erreur du système d'exploitation]"`.
- **Cause** : L'appel `CreateRemoteThread` a échoué. Cette erreur est courante dans les systèmes avec des défenses **anti-injection** robustes ou lorsqu'un programme surveille intensément le comportement du processus :
  - **Mécanismes de sécurité** : Les outils **anti-triche**, les **logiciels** de sécurité ou certaines politiques de **Windows** peuvent détecter et bloquer les tentatives de création de **threads** dans des processus tiers.
  - **Processus cible incohérent** : Si le processus de **GTA:SA** est dans un état inattendu ou instable (bien que démarré en `CREATE_SUSPENDED`), cela peut affecter la capacité à créer des **threads** dans celui-ci.
- **Solution** :
  1. Exécutez votre application avec des privilèges d'**Administrateur**.
  2. Vérifiez qu'il n'y a pas d'outils **anti-triche**, d'**antivirus agressifs** ou de **pare-feu** configurés pour inspecter et bloquer la manipulation des processus qui pourraient être en conflit. Ajoutez votre application et `gta_sa.exe` aux exceptions, si applicable (avec précaution).
  3. Le message d'erreur du système (`GetLastError()`) peut fournir des détails supplémentaires pour enquêter sur la cause spécifique (ex : **"A process has been denied access to create threads for other processes."**).

### 10. Délai d'attente ou échec de la finalisation de l'injection

Après avoir créé le **thread** distant, l'injecteur attend qu'il termine le **chargement de la DLL**.

![Error 15](../../screenshots/error_15.png)

- **Message d'erreur affiché** : `"Timeout or error waiting for DLL injection to complete. System Error: [Message d'erreur du système d'exploitation]"`.
- **Cause** : Le **thread** distant qui exécute `LoadLibraryA` a pris plus de `Constants::DLL_INJECTION_TIMEOUT_MS` (10 secondes) pour retourner, ou il a échoué et `GetExitCodeThread` a retourné 0. Les causes potentielles incluent :
  - **Problèmes dans la DLL injectée** : La `DllMain` de `samp.dll` ou `omp-client.dll` prend trop de temps à s'exécuter, contient une **boucle infinie**, un **plantage**, ou une erreur qui **empêche la DLL** de se charger correctement (ex : **dépendances de DLLs** manquantes).
  - **Blocage silencieux** : Un mécanisme de sécurité peut avoir bloqué `LoadLibraryA` sans notifier d'erreur évidente de création de **thread**.
- **Solution** :
  1. Vérifiez l'intégrité des fichiers `samp.dll` et `omp-client.dll`. Ils peuvent être corrompus ou provenir d'une version incompatible avec votre `gta_sa.exe`.
  2. Assurez-vous que **la DLL injectée** ne dépend pas d'**autres DLLs** qui pourraient être manquantes ou inaccessibles dans le système.

### 11. Échec de la reprise du thread du processus du jeu

C'est l'étape finale pour démarrer le jeu après que **les DLLs** ont été injectées.

![Error 16](../../screenshots/error_16.png)

- **Message d'erreur affiché** : `"Failed to resume the game process thread: [Message d'erreur du système d'exploitation]"`.
- **Cause** : L'appel `ResumeThread` a échoué, ce qui signifie que le **thread** principal de `gta_sa.exe` n'a pas pu être activé pour démarrer l'exécution du jeu. C'est une erreur rare, mais elle peut survenir si :
  - Le **handle** du **thread** du processus est devenu invalide.
  - Le système d'exploitation a empêché la reprise pour une raison quelconque, peut-être liée à une interruption de sécurité ou à un état incohérent du processus.
  - Le processus peut avoir été terminé de manière externe entre l'**injection de la DLL** et la tentative de reprise du **thread** principal.
- **Solution** : Si toutes les étapes précédentes ont réussi et que seul `ResumeThread` a échoué, cela peut être un problème avec le système d'exploitation, avec l'installation même de **GTA:SA**, ou avec un autre **logiciel** de sécurité très strict. Réexaminez l'état de `gta_sa.exe` via le **Gestionnaire des tâches** juste avant et après l'erreur. Redémarrer l'ordinateur peut résoudre les problèmes d'état temporaire du système.

> [!TIP]
> Dans les scénarios de débogage complexes, des outils comme **Process Monitor (Sysinternals Suite)** ou un débogueur (comme **Visual Studio Debugger**, **WinDbg**, **OllyDbg**) peuvent être inestimables. Ils peuvent aider à observer les appels d'**API**, vérifier les erreurs d'accès, suivre l'état des **handles** et même inspecter la mémoire du processus, offrant une vue approfondie de ce qui se passe en coulisses.

## Licence

Copyright © **SA-MP Programming Community**

Ce logiciel est sous licence selon les termes de la Licence MIT ("Licence"); vous pouvez utiliser ce logiciel conformément aux conditions de la Licence. Une copie de la Licence peut être obtenue à: [MIT License](https://opensource.org/licenses/MIT)

### Conditions Générales d'Utilisation

#### 1. Autorisations Accordées

La présente licence accorde gratuitement à toute personne obtenant une copie de ce logiciel et des fichiers de documentation associés les droits suivants:
* Utiliser, copier, modifier, fusionner, publier, distribuer, sous-licencier et/ou vendre des copies du logiciel sans restriction
* Permettre aux personnes à qui le logiciel est fourni de faire de même, sous réserve des conditions suivantes

#### 2. Conditions Obligatoires

Toutes les copies ou parties substantielles du logiciel doivent inclure:
* L'avis de droit d'auteur ci-dessus
* Cet avis d'autorisation
* L'avis de non-responsabilité ci-dessous

#### 3. Droits d'Auteur

Le logiciel et toute la documentation associée sont protégés par les lois sur le droit d'auteur. La **SA-MP Programming Community** conserve la propriété des droits d'auteur originaux du logiciel.

#### 4. Exclusion de Garantie et Limitation de Responsabilité

LE LOGICIEL EST FOURNI "TEL QUEL", SANS GARANTIE D'AUCUNE SORTE, EXPRESSE OU IMPLICITE, Y COMPRIS MAIS NON LIMITÉ AUX GARANTIES DE COMMERCIALISATION, D'ADÉQUATION À UN USAGE PARTICULIER ET DE NON-VIOLATION.

EN AUCUN CAS LES AUTEURS OU LES DÉTENTEURS DES DROITS D'AUTEUR NE SERONT RESPONSABLES DE TOUTE RÉCLAMATION, DOMMAGE OU AUTRE RESPONSABILITÉ, QUE CE SOIT DANS UNE ACTION DE CONTRAT, UN DÉLIT OU AUTRE, DÉCOULANT DE, HORS DE OU EN RELATION AVEC LE LOGICIEL OU L'UTILISATION OU D'AUTRES TRANSACTIONS DANS LE LOGICIEL.

---

Pour des informations détaillées sur la Licence MIT, consultez: https://opensource.org/licenses/MIT