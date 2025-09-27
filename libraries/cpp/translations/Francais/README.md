# SA-MP Injector C++

<div align="center">

![C++](https://img.shields.io/badge/C%2B%2B-14%2F17%2F20-00599C?style=for-the-badge&logo=cplusplus)
![Platform](https://img.shields.io/badge/Platform-Windows-blue?style=for-the-badge&logo=windows&logoColor=white)
![Architecture](https://img.shields.io/badge/Architecture-x86%20(32--bit)-lightgrey?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)

**Une bibliothèque C++ pour démarrer et automatiser la connexion des clients SA-MP et OMP aux serveurs, via l'injection de DLLs.**

</div>

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
  - [Aperçu Général et Objectif](#aperçu-général-et-objectif)
  - [Principes de Conception](#principes-de-conception)
    - [Entièrement `Header-Only`](#entièrement-header-only)
    - [Gestion Sécurisée des Ressources (RAII)](#gestion-sécurisée-des-ressources-raii)
    - [Robustesse et Vérification des Erreurs](#robustesse-et-vérification-des-erreurs)
    - [Flexibilité des Normes C++](#flexibilité-des-normes-c)
  - [Environnement Requis](#environnement-requis)
    - [Pour le Développement](#pour-le-développement)
    - [Pour l'Exécution](#pour-lexécution)
  - [Démarrage Rapide](#démarrage-rapide)
    - [Intégration au Projet](#intégration-au-projet)
    - [Exemple d'Utilisation Simplifié](#exemple-dutilisation-simplifié)
  - [Structure de la Bibliothèque](#structure-de-la-bibliothèque)
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
  - [Le Processus Détaillé d'Injection](#le-processus-détaillé-dinjection)
    - [1. Demande d'Initialisation](#1-demande-dinitialisation)
    - [2. Préparation de l'Environnement](#2-préparation-de-lenvironnement)
    - [3. Vérification de l'Intégrité et des Paramètres](#3-vérification-de-lintégrité-et-des-paramètres)
    - [4. Préparation des Arguments pour le Jeu](#4-préparation-des-arguments-pour-le-jeu)
    - [5. Initialisation du Processus du Jeu (Suspendu)](#5-initialisation-du-processus-du-jeu-suspendu)
    - [6. Injection de la Bibliothèque SA-MP (`samp.dll`)](#6-injection-de-la-bibliothèque-sa-mp-sampdll)
    - [7. Injection de la Bibliothèque OMP (`omp-client.dll`) - Conditionnelle](#7-injection-de-la-bibliothèque-omp-omp-clientdll---conditionnelle)
    - [8. Activation du Jeu](#8-activation-du-jeu)
  - [Diagnostic des Erreurs et des Pannes](#diagnostic-des-erreurs-et-des-pannes)
    - [Échecs de Validation des Entrées](#échecs-de-validation-des-entrées)
      - [Nom d'utilisateur Invalide](#nom-dutilisateur-invalide)
      - [Port de Connexion Invalide](#port-de-connexion-invalide)
      - [Ressources Essentielles Manquantes](#ressources-essentielles-manquantes)
    - [Échecs dans la Gestion du Processus](#échecs-dans-la-gestion-du-processus)
      - [Difficulté à Démarrer le Processus du Jeu](#difficulté-à-démarrer-le-processus-du-jeu)
    - [Problèmes d'Injection de la DLL](#problèmes-dinjection-de-la-dll)
      - [Impossible de Localiser `LoadLibraryW`](#impossible-de-localiser-loadlibraryw)
      - [Échec de la Réservation de Mémoire à Distance](#échec-de-la-réservation-de-mémoire-à-distance)
      - [Incapacité d'Écrire des Données dans le Processus](#incapacité-décrire-des-données-dans-le-processus)
      - [Échec de la Création du Thread d'Injection](#échec-de-la-création-du-thread-dinjection)
      - [Délai d'Attente Dépassé ou Erreur lors de l'Attente de l'Injection](#délai-dattente-dépassé-ou-erreur-lors-de-lattente-de-linjection)
      - [Échec Interne de l'Injection de la DLL](#échec-interne-de-linjection-de-la-dll)
    - [Difficulté à Reprendre l'Exécution du Jeu](#difficulté-à-reprendre-lexécution-du-jeu)
  - [Licence](#licence)
    - [Conditions Générales d'Utilisation](#conditions-générales-dutilisation)
      - [1. Autorisations Accordées](#1-autorisations-accordées)
      - [2. Conditions Obligatoires](#2-conditions-obligatoires)
      - [3. Droits d'Auteur](#3-droits-dauteur)
      - [4. Exclusion de Garantie et Limitation de Responsabilité](#4-exclusion-de-garantie-et-limitation-de-responsabilité)

## Aperçu Général et Objectif

**SA-MP Injector C++** est une bibliothèque C++ compacte et facile à intégrer, conçue pour automatiser le processus de démarrage et de connexion aux serveurs San Andreas Multiplayer (SA-MP) et Open Multiplayer (OMP). Contrairement au démarrage direct de `gta_sa.exe`, cette solution charge programmatiquement les bibliothèques `samp.dll` ou `omp-client.dll` dans le processus du jeu Grand Theft Auto: San Andreas de manière contrôlée.

Son objectif principal est de permettre aux développeurs C++ de créer des `launchers` personnalisés, des outils de gestion de communauté ou des utilitaires qui nécessitent de lancer GTA:SA avec des paramètres de connexion prédéfinis (comme le nom d'utilisateur, l'adresse IP, le port et le mot de passe), offrant une expérience utilisateur fluide et automatisée.

## Principes de Conception

L'architecture de **SA-MP Injector C++** est basée sur des principes de conception modernes, axés sur la sécurité, l'efficacité et la facilité d'utilisation.

### Entièrement `Header-Only`

Cette bibliothèque est distribuée exclusivement via des fichiers d'en-tête (`.hpp`). Cela simplifie considérablement l'intégration dans les projets C++, en éliminant le besoin de compiler des bibliothèques séparées, de configurer des `linkers` ou de gérer des dépendances binaires.
- **Intégration Instantanée :** Il suffit d'inclure les `headers` pertinents.
- **Optimisation Approfondie :** Le compilateur peut effectuer des `inlining` agressifs et des optimisations de `link-time` qui se traduisent par un code final plus compact et plus rapide.

### Gestion Sécurisée des Ressources (RAII)

La bibliothèque utilise abondamment le modèle **RAII (Resource Acquisition Is Initialization)**. Les ressources système critiques, telles que les `handles` de processus et de `threads` Windows, sont encapsulées par `std::unique_ptr` avec des `deleters` personnalisés. Cela garantit que, quel que soit le flux d'exécution ou la survenue d'exceptions, les ressources sont toujours libérées correctement, prévenant ainsi les fuites et améliorant la stabilité de l'application.

### Robustesse et Vérification des Erreurs

Chaque étape critique de l'injection est précédée de validations rigoureuses et suivie de vérifications d'erreurs de l'API Windows. Des messages d'erreur détaillés sont fournis à l'utilisateur final via des boîtes de dialogue, avec des descriptions système (`GetLastError()`) chaque fois que possible. Cette approche minimise les risques de comportements indéfinis et offre un diagnostic clair en cas d'échec.

### Flexibilité des Normes C++

La bibliothèque a été conçue pour être compatible avec différentes normes C++, de C++14 à C++20. Ceci est réalisé grâce à des macros conditionnelles qui permettent l'utilisation de fonctionnalités modernes (comme `std::string_view`, `std::filesystem` et `std::optional` de C++17+) lorsqu'elles sont disponibles, tout en maintenant un `fallback` vers des constructions équivalentes en C++14. Cette approche garantit une large compatibilité sans sacrifier la modernité.

## Environnement Requis

### Pour le Développement

- **Compilateur C++ :** Compatible avec **C++14 ou supérieur**.
   - Microsoft Visual C++ (Visual Studio 2015, 2017, 2019, 2022)
   - GCC (version 5 ou plus récente)
   - Clang (version 3.6 ou plus récente)
- **Système d'Exploitation :** **Windows**.
- **Windows SDK :** Nécessaire pour accéder aux API du système d'exploitation.
- **Architecture de Compilation :** **x86 (32-bit)**. C'est une exigence stricte, car `gta_sa.exe` et les DLLs SA-MP/OMP fonctionnent exclusivement dans cette architecture.

### Pour l'Exécution

- **Système d'Exploitation :** Toute version moderne de **Windows** compatible avec le binaire compilé.
- **Grand Theft Auto: San Andreas (GTA:SA) :** Une installation valide du jeu est obligatoire.
- **DLLs du Client SA-MP ou OMP :** Les fichiers `samp.dll` ou `omp-client.dll` doivent être présents dans le répertoire racine du jeu, correspondant au type d'injection souhaité.

## Démarrage Rapide

La nature `header-only` de la bibliothèque facilite son intégration dans n'importe quel projet C++.

### Intégration au Projet

1.  **Téléchargez les Headers :** Obtenez les fichiers `.hpp` de la bibliothèque (en clonant le dépôt ou en les téléchargeant directement).
2.  **Organisez les Fichiers :** Il est recommandé de créer un sous-dossier dans votre projet pour les `headers` de la bibliothèque, par exemple, `MonProjet/libraries/samp-injector/`.
3.  **Définissez l'Architecture :** Configurez votre projet pour compiler pour l'architecture **x86 (32-bit)**.

```cpp
// Exemple de structure de répertoires
MonProjet/
├── src/
│   └── main.cpp
├── libraries/
│   └── samp-injector/
│       ├── constants.hpp
│       ├── error_utils.hpp
│       ├── injector.hpp // L'en-tête principal à inclure
│       └── ... (autres en-têtes)
└── built/ (votre répertoire de sortie)
```

### Exemple d'Utilisation Simplifié

Pour automatiser la connexion à un serveur, il suffit d'appeler la fonction `Initialize_Game` et de fournir les détails.

```cpp
#include <iostream>
#include <string>
//
#include "samp-launcher/injector.hpp" // Inclure l'en-tête principal

int main() {
    // Paramètres pour l'initialisation du jeu et la connexion
    std::wstring inject_type = L"samp"; // Ou L"omp" pour Open Multiplayer
    std::wstring game_folder = L"C:\\Games\\GTA San Andreas"; // Chemin complet du dossier de GTA:SA
    std::wstring nickname = L"Nom";
    std::wstring ip = L"127.0.0.1";
    std::wstring port = L"7777";
    std::wstring password = L""; // Laisser vide s'il n'y a pas de mot de passe

    // L'appel principal pour démarrer le jeu et injecter la DLL
    Initialize_Game(inject_type, game_folder, nickname, ip, port, password);

    // En cas d'échec, une boîte de message d'erreur Windows est affichée automatiquement.

    return 0;
}
```

## Structure de la Bibliothèque

La bibliothèque est soigneusement modularisée en plusieurs fichiers d'en-tête, chacun ayant des responsabilités bien définies, facilitant l'organisation, la maintenance et la réutilisation.

### 1. `constants.hpp`

Ce fichier est le **dépôt central** de la bibliothèque, servant de référentiel centralisé pour toutes les valeurs fixes et immuables qui dictent le comportement et l'interopérabilité de **SA-MP Injector C++**. Son organisation par catégories logiques favorise non seulement la clarté et la lisibilité du code, mais facilite également la maintenance et garantit une cohérence rigoureuse dans tout l'écosystème de la bibliothèque.

Chaque constante est définie avec `CONSTEXPR_VAR`, qui se développe en `inline constexpr` (pour C++17+) ou `static constexpr` (pour C++14), garantissant que ces valeurs sont évaluées au moment de la compilation, optimisant les performances et la sécurité des types.

L'organisation des constantes par catégorie facilite la compréhension de leur objectif :

- **Constantes liées au Jeu (`Game Related Constants`)**
   - `MIN_PORT` : Un `int` qui définit le plus petit numéro de port valide pour la connexion à un serveur (valeur : `1`).
   - `MAX_PORT` : Un `int` qui établit le plus grand numéro de port valide pour la connexion à un serveur (valeur : `65535`).
   - `MAX_NICKNAME_LENGTH` : Un `int` qui spécifie la longueur maximale autorisée pour le pseudonyme du joueur (valeur : `23` caractères), une limite imposée par les spécifications du client SA-MP/OMP.

- **Noms de Fichiers Essentiels (`File Names`)**
   - `SAMP_DLL_NAME` : Un `const wchar_t*` qui contient le nom du fichier de la bibliothèque principale du client SA-MP (valeur : `L"samp.dll"`). Essentiel pour l'injection du client classique.
   - `OMP_DLL_NAME` : Un `const wchar_t*` qui contient le nom du fichier de la bibliothèque du client Open Multiplayer (valeur : `L"omp-client.dll"`). Utilisé spécifiquement lorsque l'injection est de type OMP.
   - `GAME_EXE_NAME` : Un `const wchar_t*` qui stocke le nom du fichier exécutable du jeu de base Grand Theft Auto: San Andreas (valeur : `L"gta_sa.exe"`). La cible principale de l'injection.

- **API et Fonctions Système (`System Libraries and Functions`)**
   - `KERNEL32_DLL` : Un `const wchar_t*` qui définit le nom de la bibliothèque système de Windows (`L"kernel32.dll"`). Cette DLL est vitale, car elle héberge les fonctions de manipulation de processus et de mémoire que l'injecteur utilise. L'utilisation de `wchar_t` garantit la compatibilité avec les fonctions de l'API qui manipulent des caractères larges, comme `GetModuleHandleW`.
   - `LOAD_LIBRARY_FUNC` : Un `const char*` avec le nom de la fonction pour charger une DLL dynamiquement (valeur : `"LoadLibraryW"`). Bien que la bibliothèque fonctionne principalement avec des caractères larges, la fonction `GetProcAddress` de l'API Windows nécessite un nom de fonction au format ANSI (`char*`).

- **Arguments de Ligne de Commande (`Command Line Arguments`)**
   - Ces constantes définissent les préfixes pour les arguments qui sont passés à `gta_sa.exe` pour configurer la connexion du client. Elles sont fournies en `Wide Character` (`const wchar_t*`) pour la compatibilité avec `CreateProcessW`.
      - `CMD_ARG_CONFIG` : Argument pour les configurations générales (valeur : `L"-c"`).
      - `CMD_ARG_NICKNAME` : Argument pour le pseudonyme du joueur (valeur : `L"-n"`).
      - `CMD_ARG_HOST` : Argument pour l'adresse IP du serveur (valeur : `L"-h"`).
      - `CMD_ARG_PORT` : Argument pour le port du serveur (valeur : `L"-p"`).
      - `CMD_ARG_PASSWORD` : Argument pour le mot de passe du serveur (valeur : `L"-z"`). Utilisé uniquement si un mot de passe est fourni.

- **Identifiants de Type d'Injection (`Injection types as strings`)**
   - `INJECT_TYPE_SAMP` : Un `const wchar_t*` pour la représentation en chaîne du type d'injection SA-MP (valeur : `L"samp"`).
   - `INJECT_TYPE_OMP` : Un `const wchar_t*` pour la représentation en chaîne du type d'injection OMP (valeur : `L"omp"`).

- **Titres pour les Messages d'Erreur (`Error message titles`)**
   - `ERROR_TITLE_SAMP` : Un `const wchar_t*` qui définit le titre par défaut pour les boîtes de dialogue d'erreur liées aux échecs de SA-MP (valeur : `L"SA-MP Injector Error - SPC"`).
   - `ERROR_TITLE_OMP` : Un `const wchar_t*` qui définit le titre par défaut pour les boîtes de dialogue d'erreur liées aux échecs de OMP (valeur : `L"OMP Injector Error - SPC"`).

- **Drapeaux de Création de Processus (`Process creation`)**
   - `PROCESS_CREATION_FLAGS` : Un `DWORD` qui encapsule les drapeaux passés à `CreateProcessW`. Crucialement, il inclut `CREATE_SUSPENDED` (`0x00000004`), qui démarre le processus du jeu dans un état suspendu, et `DETACHED_PROCESS` (`0x00000008`), qui détache le nouveau processus de la console du processus parent.

- **Délais d'Attente (`Timeouts`)**
   - `DLL_INJECTION_TIMEOUT_MS` : Un `DWORD` qui spécifie le temps maximum (en millisecondes) que la bibliothèque attendra pour la fin du `thread` distant responsable de l'injection de la DLL (valeur : `10000ms`, soit 10 secondes).

- **Drapeaux d'Allocation de Mémoire (`Memory allocation`)**
   - Ces constantes sont utilisées pour les appels d'API de manipulation de la mémoire, comme `VirtualAllocEx` et `VirtualProtect`.
      - `MEM_COMMIT` : Un `DWORD` qui réserve des pages dans la mémoire virtuelle et les "committe" (alloue de la mémoire physique) (valeur : `0x1000`).
      - `MEM_RESERVE` : Un `DWORD` qui réserve simplement une plage d'espace d'adressage virtuel pour une utilisation ultérieure (valeur : `0x2000`).
      - `MEM_RELEASE` : Un `DWORD` qui décommitte et libère une région de pages (valeur : `0x8000`).
      - `MEMORY_ALLOCATION_TYPE` : Une combinaison de `MEM_COMMIT` et `MEM_RESERVE`, utilisée pour allouer la mémoire initiale pour le chemin de la DLL dans le processus distant.
      - `MEMORY_PROTECTION` : Un `DWORD` qui définit les autorisations de protection de la mémoire (valeur : `PAGE_READWRITE` ou `0x04` dans l'API Windows), permettant la lecture et l'écriture dans la mémoire allouée.

### 2. `types.hpp`

Ce fichier concis introduit une `enum class` pour typer les différentes modalités d'injection. L'utilisation d'un type énuméré, plutôt que de chaînes littérales, augmente la sécurité du code, prévient les fautes de frappe et améliore la lisibilité.

- **`Inject_Type` :** Une `enum class` avec deux membres : `SAMP` et `OMP`, représentant les types de client à injecter.

```cpp
// Exemple de types.hpp
namespace Types {
    enum class Inject_Type {
        SAMP, // Indique une injection pour le client SA-MP
        OMP // Indique une injection pour le client Open Multiplayer
    };
}
```

### 3. `version.hpp`

Agissant comme un adaptateur de compatibilité, cet en-tête détecte dynamiquement la norme C++ utilisée par le compilateur. Il définit des macros conditionnelles (`SAMP_INJECTOR_CXX_14`, `SAMP_INJECTOR_CXX_MODERN`) qui guident la bibliothèque à utiliser les fonctionnalités les plus avancées de C++ (comme `std::string_view` ou `std::filesystem`) lorsqu'elles sont disponibles, tout en assurant une fonctionnalité complète dans les environnements C++14.

- **`SAMP_INJECTOR_CXX_14` :** Définie si la norme C++ est C++14.
- **`SAMP_INJECTOR_CXX_MODERN` :** Définie pour C++17 ou supérieur, activant des fonctionnalités de langage plus récentes.
- **`SAMP_INJECTOR_NODISCARD` :** Adapte l'attribut `[[nodiscard]]` pour les versions de C++ qui le supportent, encourageant la vérification des valeurs de retour.

```cpp
// Exemple d'extrait pertinent de version.hpp
#if (defined(_MSC_VER) && _MSVC_LANG >= 201703L) || __cplusplus >= 201703L
    #define SAMP_INJECTOR_CXX_MODERN // Active les fonctionnalités modernes de C++17+
#endif

#if defined(SAMP_INJECTOR_CXX_MODERN)
    #define SAMP_INJECTOR_NODISCARD [[nodiscard]] // Utilise l'attribut nodiscard de C++17
#elif defined(SAMP_INJECTOR_CXX_14)
    #define SAMP_INJECTOR_NODISCARD // Pour C++14, l'attribut est désactivé
#endif
```

### 4. `error_utils.hpp`

Cet utilitaire est dédié à la gestion et à la présentation des retours d'erreur. Il abstrait les mécanismes de Windows pour récupérer les messages d'erreur du système et offre une interface unifiée pour notifier l'utilisateur des problèmes.

- **`Get_System_Error_Message` :** Traduit un code d'erreur Windows (`GetLastError()`) en une `std::wstring` lisible, cruciale pour un diagnostic précis.
- **`Show_Error` :** Affiche une boîte de dialogue (`MessageBoxW`) contenant le message d'erreur fourni, avec un titre spécifique pour SA-MP ou OMP, garantissant une communication claire avec l'utilisateur.

```cpp
// Exemple d'extrait pertinent de error_utils.hpp
namespace Error_Utils {
    SAMP_INJECTOR_NODISCARD
    inline std::wstring Get_System_Error_Message(DWORD error_code) {
        if (error_code == 0)
            return L"No error occurred.";
        
        // ... Logique pour formater le message du système ...
    }

    inline void Show_Error(std::wstring_view message, Types::Inject_Type inject_type) {
        const std::wstring title = (inject_type == Types::Inject_Type::SAMP) ? Constants::ERROR_TITLE_SAMP : Constants::ERROR_TITLE_OMP;
        MessageBoxW(nullptr, message.data(), title.c_str(), MB_OK | MB_ICONERROR);
    }
}
```

### 5. `validation.hpp`

Agissant comme la première ligne de défense de la robustesse de la bibliothèque, cet en-tête fournit des routines rigoureuses pour vérifier la validité des données d'entrée et la présence des fichiers nécessaires. Ces vérifications sont effectuées avant toute interaction de bas niveau avec le système, atténuant les risques de `runtime` et fournissant un retour proactif.

- **`Validate_Port` :** Valide si la chaîne du port représente un nombre entier et si celui-ci se trouve dans la plage configurée (`MIN_PORT` à `MAX_PORT`).
- **`Validate_Nickname` :** Vérifie si le pseudonyme n'est pas vide et si sa longueur ne dépasse pas `MAX_NICKNAME_LENGTH`.
- **`Validate_Files` :** Confirme l'existence physique de `gta_sa.exe`, `samp.dll` et, conditionnellement pour l'injection OMP, `omp-client.dll`. L'implémentation s'adapte à `std::filesystem` (C++17+) ou `GetFileAttributesW` (C++14).

```cpp
// Exemple d'extrait pertinent de validation.hpp
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
        
        // ... Autres vérifications de fichiers ...
        return true;
    }
}
```

### 6. `resource_handle.hpp`

Implémente une stratégie élégante et sécurisée pour la gestion des ressources du système d'exploitation, comme les `HANDLE`s de Windows. En utilisant le principe RAII, il garantit que toutes les ressources allouées sont correctement libérées, prévenant les fuites et renforçant la stabilité de l'application.

- **`Unique_Resource` :** Un `alias template` qui adapte `std::unique_ptr` pour fonctionner avec des `deleters` personnalisés, permettant la gestion de tout type de ressource nécessitant une fonction de libération spécifique.
- **`Make_Unique_Handle` :** Une fonction `factory` pratique qui construit et retourne un `Unique_Resource` préconfiguré pour les `HANDLE`s de Windows. Le `deleter` associé appelle `CloseHandle` automatiquement lorsque le `Unique_Resource` sort de portée, garantissant la libération immédiate de la ressource.

```cpp
// Exemple d'extrait pertinent de resource_handle.hpp
namespace Resource_Handle {
    // Un std::unique_ptr personnalisé pour gérer les ressources du système.
    template<typename T, typename Deleter>
    using Unique_Resource = std::unique_ptr<std::remove_pointer_t<T>, Deleter>;

    // Crée un Unique_Resource pour un HANDLE, avec un deleter qui appelle CloseHandle.
    template<typename T>
    inline auto Make_Unique_Handle(T handle) {
        return Unique_Resource<T, std::function<void(T)>>(handle, [](T h) {
            if (h && h != INVALID_HANDLE_VALUE) // S'assure que le handle est valide avant de le fermer
                CloseHandle(h);
        });
    }
}
```

### 7. `privileges.hpp`

Ce composant est responsable de la configuration de l'environnement de sécurité du processus de l'application. Il contient la fonctionnalité pour élever les privilèges, en activant spécifiquement le privilège de débogage (`SE_DEBUG_NAME`), qui est une exigence fondamentale pour que la bibliothèque puisse effectuer des opérations d'injection de DLL dans des processus externes de Windows.

- **`Enable_Debug_Privilege` :** Cette fonction tente d'acquérir et d'activer le privilège `SE_DEBUG_NAME` pour le processus en cours. C'est une étape initiale cruciale pour accorder à l'application les permissions nécessaires pour manipuler d'autres processus, comme allouer de la mémoire et créer des `threads` distants. Elle retourne `true` en cas de succès.

```cpp
// Exemple d'extrait pertinent de privileges.hpp
namespace Privileges {
    inline bool Enable_Debug_Privilege() {
        HANDLE token_handle;

        // Tente d'ouvrir le jeton du processus actuel pour ajuster les privilèges
        if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &token_handle))
            return false;

        auto handle_guard = Resource_Handle::Make_Unique_Handle(token_handle); // Gestion sécurisée du handle

        TOKEN_PRIVILEGES tp;
        LUID luid;

        // Recherche la valeur LUID pour le privilège SE_DEBUG_NAME
        if (!LookupPrivilegeValue(nullptr, SE_DEBUG_NAME, &luid))
            return false;
        
        tp.PrivilegeCount = 1;
        tp.Privileges[0].Luid = luid;
        tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED; // Active le privilège

        // Ajuste les privilèges du processus
        if (!AdjustTokenPrivileges(token_handle, FALSE, &tp, sizeof(TOKEN_PRIVILEGES), nullptr, nullptr))
            return false;

        return GetLastError() == ERROR_SUCCESS; // Retourne true si l'opération a réussi (aucune erreur en attente)
    }
}
```

### 8. `process.hpp`

C'est l'un des composants les plus critiques de la bibliothèque, contenant l'implémentation de bas niveau pour interagir avec les processus de Windows. Il encapsule les opérations complexes de création du processus du jeu, d'allocation de mémoire, d'écriture de données et la technique d'injection de DLL via la création de `threads` distants.

- **`Process_Info` struct :** Une structure interne qui stocke les `Unique_Resource`s pour le `HANDLE` du processus (`process_handle`) et du `HANDLE` du `thread` principal (`thread_handle`) du jeu. Inclut une méthode `Resume()` pour réactiver le `thread` principal du jeu lorsque l'injection est terminée.
- **`Injection_Status` enum class :** Définit une liste détaillée des résultats possibles pour l'opération d'injection de DLL, permettant un diagnostic précis des échecs.
- **`Create_Game_Process` :**
   - Utilise la fonction `CreateProcessW` de l'API Windows pour démarrer l'exécutable `gta_sa.exe`.
   - Il est fondamental que le processus soit créé avec le drapeau `CREATE_SUSPENDED` (inclus dans `Constants::PROCESS_CREATION_FLAGS`). Cela garantit que le jeu est mis en pause immédiatement après sa création, avant qu'aucun code ne soit exécuté, permettant à l'injection de la DLL de se produire dans un état sûr.
   - Retourne un `std::optional<Process_Info>` (pour C++17+) ou un `std::unique_ptr<Process_Info>` (pour C++14), contenant les `handles` encapsulés du processus et du `thread`.
- **`Inject_DLL` :**
   - Implémente la technique standard d'injection de DLL via `CreateRemoteThread` :
      1.  **Obtention de l'Adresse :** En utilisant les constantes de `constants.hpp`, localise l'adresse de la fonction `LoadLibraryW` (de `kernel32.dll`), que Windows utilise pour charger dynamiquement les bibliothèques.
      2.  **Allocation de Mémoire :** `VirtualAllocEx` est utilisée pour réserver un bloc de mémoire virtuelle à l'intérieur du processus du jeu (`gta_sa.exe`). Ce bloc est dimensionné pour contenir le chemin complet de la DLL à injecter.
      3.  **Écriture du Chemin :** Le chemin de la DLL (par ex., `L"C:\\chemin\\vers\\samp.dll"`) est ensuite copié dans la mémoire allouée à distance dans le processus du jeu via `WriteProcessMemory`.
      4.  **Création du Thread Distant :** `CreateRemoteThread` démarre un nouveau `thread` dans le contexte du processus du jeu. Le point d'entrée de ce `thread` est l'adresse de `LoadLibraryW`, et l'argument passé est l'adresse de la chaîne du chemin de la DLL que nous venons d'écrire.
      5.  **Surveillance :** L'exécution du `thread` distant est surveillée par `WaitForSingleObject` jusqu'à ce qu'il se termine ou que le `DLL_INJECTION_TIMEOUT_MS` soit atteint.
      6.  **Vérification du Succès :** `GetExitCodeThread` est utilisée pour vérifier la valeur de retour du `thread` distant. Si `LoadLibraryW` a réussi, elle retournera l'adresse de base de la DLL chargée (une valeur non nulle).
      7.  **Nettoyage :** La mémoire allouée dans le processus distant est libérée par `VirtualFreeEx`.
   - Retourne un `Injection_Status` indiquant le succès ou le type spécifique d'échec de l'injection.

```cpp
// Exemple d'extrait pertinent de process.hpp
class Process {
public:
    struct Process_Info {
        Resource_Handle::Unique_Resource<HANDLE, std::function<void(HANDLE)>> process_handle; // Handle du processus avec gestion RAII
        Resource_Handle::Unique_Resource<HANDLE, std::function<void(HANDLE)>> thread_handle; // Handle du thread avec gestion RAII

        bool Resume() { // Reprend l'exécution du thread principal du jeu
            return thread_handle && ResumeThread(thread_handle.get()) != static_cast<DWORD>(-1);
        }
    };
    
    enum class Injection_Status { // Codes de statut détaillés pour l'injection de DLL
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

    // Crée le processus du jeu en état suspendu
    std::optional<Process_Info> Create_Game_Process(const std::wstring& game_path, std::wstring& command_args, const std::wstring& working_dir) {
        // ... Logique de CreateProcessW avec CREATE_SUSPENDED ...
    }
    
    SAMP_INJECTOR_NODISCARD // S'assure que la valeur de retour est utilisée
    Injection_Status Inject_DLL(HANDLE process, const std::wstring& DLL_path) {
        static const LPVOID load_library_addr = reinterpret_cast<LPVOID>(GetProcAddress(GetModuleHandleW(Constants::KERNEL32_DLL), Constants::LOAD_LIBRARY_FUNC));

        if (!load_library_addr)
            return Injection_Status::LOADLIBRARY_ADDRESS_FAILED;

        LPVOID remote_memory = VirtualAllocEx(process, nullptr, (DLL_path.length() + 1) * sizeof(wchar_t), Constants::MEMORY_ALLOCATION_TYPE, Constants::MEMORY_PROTECTION);

        if (!remote_memory)
            return Injection_Status::ALLOCATION_FAILED;

        auto memory_guard = Resource_Handle::Unique_Resource<LPVOID, std::function<void(LPVOID)>>(remote_memory, [process](LPVOID ptr) {
            if (ptr)
                VirtualFreeEx(process, ptr, 0, MEM_RELEASE); // Libère la mémoire dans le processus distant
        });

        if (!WriteProcessMemory(process, remote_memory, DLL_path.c_str(), (DLL_path.length() + 1) * sizeof(wchar_t), nullptr))
            return Injection_Status::WRITE_FAILED;

        HANDLE remote_thread = CreateRemoteThread(process, nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(load_library_addr), remote_memory, 0, nullptr);

        if (!remote_thread)
            return Injection_Status::THREAD_CREATION_FAILED;

        auto thread_guard = Resource_Handle::Make_Unique_Handle(remote_thread); // Gestion sécurisée du handle du thread distant

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

Cet en-tête définit la classe `Injector_Core`, qui sert de centre de commande de la bibliothèque. Elle orchestre la séquence logique des opérations d'injection, connectant les modules de validation d'entrée, de gestion des privilèges et de manipulation des processus. C'est ici que le flux de travail complet de l'injection est défini.

- **`Injector_Core` :** Le constructeur de cette classe est le point où `Privileges::Enable_Debug_Privilege()` est appelé. Cela garantit que le processus de l'application possède les privilèges nécessaires pour effectuer des opérations d'injection de DLL avant que toute autre logique critique ne soit exécutée.
- **`Initialize_Game` :**
   1.  **Validation Complète :** Commence par appeler les fonctions de validation (`Validation::Validate_Port`, `Validation::Validate_Nickname`, `Validation::Validate_Files`) pour s'assurer que tous les paramètres et ressources essentiels sont en ordre. Si une validation échoue, une erreur est immédiatement signalée.
   2.  **Préparation des Arguments :** Construit la ligne de commande complète (`std::wstring`) qui sera passée à `gta_sa.exe`, intégrant le pseudonyme, l'IP, le port et le mot de passe fournis.
   3.  **Création du Processus Suspendu :** Appelle `Process::Create_Game_Process` pour démarrer `gta_sa.exe` dans un état suspendu, obtenant les `handles` du processus et du `thread` principal.
   4.  **Injection de `samp.dll` :** Appelle `Inject_DLL_With_Status_Check` pour injecter `samp.dll` dans le processus du jeu. Cette fonction wrapper est également responsable de l'interprétation du `Injection_Status` retourné et de l'affichage de messages d'erreur informatifs.
   5.  **Injection Conditionnelle de `omp-client.dll` :** Si le `inject_type` est `Types::Inject_Type::OMP`, `omp-client.dll` est alors injectée de la même manière que `samp.dll`.
   6.  **Reprise du Jeu :** Après toutes les injections réussies, `process_info.Resume()` est appelée pour permettre au `thread` principal du jeu de continuer son exécution.
   7.  **Gestion des Erreurs dans le Cycle :** Tout échec à l'une de ces étapes critiques entraînera un appel à `Error_Utils::Show_Error`, fournissant un retour clair à l'utilisateur et garantissant que le processus est terminé correctement (les `handles` sont libérés automatiquement par les `Unique_Resource`s).
- **`Build_Command_Args` :** Une fonction auxiliaire qui organise et concatène les arguments de la ligne de commande, ajoutant des guillemets là où c'est nécessaire pour les paramètres contenant des espaces.
- **`Inject_DLL_With_Status_Check` :** Une fonction privée qui agit comme une enveloppe pour `Process::Inject_DLL`. Elle mappe les différents `Injection_Status` à des messages d'erreur compréhensibles, facilitant la gestion des erreurs et la communication avec l'utilisateur.

```cpp
// Exemple d'extrait pertinent de injector_core.hpp
namespace Injector {
    class Injector_Core {
    public:
        Injector_Core() { // Le constructeur active le privilège de débogage
            Privileges::Enable_Debug_Privilege();
        }

        bool Initialize_Game(Types::Inject_Type inject_type, std::wstring_view folder, std::wstring_view nickname, std::wstring_view ip, std::wstring_view port, std::wstring_view password) {
            std::wstring error_message;

            // Séquence de validations des entrées
            if (!Validation::Validate_Port(port, error_message))
                return (Error_Utils::Show_Error(error_message, inject_type), false);
            // ... autres validations ...

            // Construit les arguments de la ligne de commande
            std::wstring args = Build_Command_Args({
                Command_Arg{Constants::CMD_ARG_NICKNAME, std::wstring(nickname)},
                // ... autres arguments ...
            });

            Process process_core;
            // Crée le processus du jeu en état suspendu
            auto process_info_opt = process_core.Create_Game_Process(game_path, args, std::wstring(folder));

            if (!process_info_opt)
                return false;

            auto& process_info = *process_info_opt;

            // Injecte samp.dll et, conditionnellement, omp-client.dll
            if (!Inject_DLL_With_Status_Check(process_core, process_info.process_handle.get(), Constants::SAMP_DLL_NAME, samp_DLL_path.wstring(), inject_type))
                return false;
            
            if (inject_type == Types::Inject_Type::OMP) {
                if (!Inject_DLL_With_Status_Check(process_core, process_info.process_handle.get(), Constants::OMP_DLL_NAME, omp_DLL_path.wstring(), inject_type))
                    return false;
            }
            
            // Reprend le thread principal du jeu
            if (!process_info.Resume())
                return (Error_Utils::Show_Error(L"Failed to resume the game process thread: " + Error_Utils::Get_System_Error_Message(GetLastError()), inject_type), false);

            return true;
        }
    };
}
```

### 10. `injector.hpp`

Cet en-tête agit comme la façade (`Facade`) principale de la bibliothèque, offrant un point d'entrée simplifié pour toute application souhaitant utiliser la fonctionnalité d'injection. Il abstrait la complexité interne de `Injector_Core` en une seule fonction pratique.

- **`Initialize_Game` :**
   - Cette fonction statique est l'interface publique de la bibliothèque.
   - Premièrement, elle valide la `inject_type_str` (si c'est `L"samp"` ou `L"omp"`) et la convertit en `enum class Types::Inject_Type`. En cas de chaîne invalide, elle affiche une erreur et se termine.
   - Ensuite, elle crée une instance de `Injector::Injector_Core`.
   - Enfin, elle délègue l'exécution de la logique principale à `Injector_Core::Initialize_Game`, où tout le processus de validation, de création de processus et d'injection de DLL est orchestré.

```cpp
// Exemple d'extrait pertinent de injector.hpp
// L'interface publique pour démarrer le jeu
#if defined(SAMP_INJECTOR_CXX_MODERN)
inline bool Initialize_Game(std::wstring_view inject_type, std::wstring_view folder, std::wstring_view nickname, std::wstring_view ip, std::wstring_view port, std::wstring_view password) {
#elif defined(SAMP_INJECTOR_CXX_14)
inline bool Initialize_Game(const std::wstring& inject_type, const std::wstring& folder, const std::wstring& nickname, const std::wstring& ip, const std::wstring& port, const std::wstring& password) {
#endif
    Types::Inject_Type type;

    // Convertit la chaîne de type d'injection en l'enum correspondant
    if (inject_type == Constants::INJECT_TYPE_SAMP)
        type = Types::Inject_Type::SAMP;
    else if (inject_type == Constants::INJECT_TYPE_OMP)
        type = Types::Inject_Type::OMP;
    else
        // Affiche une erreur si le type d'injection est invalide
        return (Error_Utils::Show_Error(L"Mode d'injection invalide. Utilisez 'samp' ou 'omp'.", Types::Inject_Type::SAMP), false);

    Injector::Injector_Core injector; // Crée l'instance du noyau de l'injecteur

    // Délègue la logique principale à l'Injector_Core
    return injector.Initialize_Game(type, folder, nickname, ip, port, password);
}
```

## Le Processus Détaillé d'Injection

La fonctionnalité centrale de cette bibliothèque est d'orchestrer une séquence précise d'opérations pour injecter les DLLs du client SA-MP ou OMP dans le processus de GTA:SA. Ce cycle est soigneusement planifié pour garantir la stabilité et la compatibilité.

### 1. Demande d'Initialisation

Le processus commence par l'appel à la fonction globale `Initialize_Game` (`injector.hpp`), qui sert de point de contact principal pour l'application utilisant la bibliothèque. Cette fonction reçoit tous les paramètres cruciaux, tels que le type d'injection souhaité (SA-MP ou OMP), le répertoire du jeu et les données de connexion au serveur (pseudonyme, IP, port, mot de passe).

### 2. Préparation de l'Environnement

Lorsqu'elle est invoquée, la fonction `Initialize_Game` crée une instance de `Injector::Injector_Core`. Dans le constructeur de cette classe (`injector_core.hpp`), la première et essentielle étape de configuration de l'environnement est exécutée : l'élévation des privilèges.

> [!NOTE]
> `Privileges::Enable_Debug_Privilege()` : Cet appel (`privileges.hpp`) accorde au processus de l'application le privilège `SE_DEBUG_NAME`. Ce privilège est vital, car il permet à l'application d'effectuer des opérations de bas niveau sur d'autres processus de Windows, comme lire et écrire dans leur mémoire et créer des `threads` distants – des actions fondamentales pour la technique d'injection de DLL.

### 3. Vérification de l'Intégrité et des Paramètres

Avec les privilèges ajustés, la méthode `Injector_Core::Initialize_Game` procède à une série de validations rigoureuses. C'est une phase préventive qui minimise les risques d'échec dans les étapes ultérieures et fournit un retour immédiat à l'utilisateur.

- **Validation du Port :** `Validation::Validate_Port` vérifie si le numéro du port de connexion est correctement formaté et se trouve dans la plage de `1` à `65535` (`constants.hpp`).
- **Validation du Pseudonyme :** `Validation::Validate_Nickname` garantit que le pseudonyme du joueur n'est pas vide et ne dépasse pas la limite de `23` caractères.
- **Vérification des Fichiers Essentiels :** `Validation::Validate_Files` inspecte le répertoire du jeu pour confirmer la présence de `gta_sa.exe`, `samp.dll` et, si l'injection est de type OMP, également `omp-client.dll`.

> [!WARNING]
> Tout échec à cette étape entraîne l'affichage immédiat d'une `MessageBox` avec un message d'erreur détaillé (`error_utils.hpp`) et l'interruption du processus d'injection. Cela évite les tentatives inutiles de continuer avec une configuration invalide.

### 4. Préparation des Arguments pour le Jeu

Après une validation réussie, la fonction `Injector_Core::Build_Command_Args` est responsable de la construction de la ligne de commande formatée qui sera passée à `gta_sa.exe`. Cette ligne de commande inclut tous les paramètres nécessaires pour que le client SA-MP/OMP se connecte automatiquement à un serveur, comme `-n "pseudonyme" -h "IP" -p "Port" -z "MotDePasse"`.

### 5. Initialisation du Processus du Jeu (Suspendu)

Le composant `Process` (`process.hpp`) est alors chargé de démarrer l'exécutable de GTA:SA.

> [!IMPORTANT]
> La fonction `Process::Create_Game_Process` utilise le drapeau `CREATE_SUSPENDED` (`constants.hpp`) lors de l'appel à l'API `CreateProcessW` de Windows. C'est une mesure de conception critique : le jeu est chargé en mémoire et son `thread` principal est créé, mais son exécution est **mise en pause**. Cela crée un environnement contrôlé et stable, idéal pour l'injection de DLLs, avant que le jeu ne puisse initialiser ses propres défenses ou logiques internes. Les `handles` du processus et du `thread` sont obtenus et gérés en toute sécurité via `Resource_Handle::Unique_Resource`.

### 6. Injection de la Bibliothèque SA-MP (`samp.dll`)

Avec le processus du jeu en état de suspension, l'injection de `samp.dll` peut être réalisée en toute sécurité. La méthode `Injector_Core::Inject_DLL_With_Status_Check` délègue cette tâche à `Process::Inject_DLL`, qui exécute les étapes suivantes de la technique de `remote thread injection` :

1.  **Localisation de la Fonction `LoadLibraryW` :** L'adresse de la fonction `LoadLibraryW` est identifiée. Cette opération utilise les constantes `Constants::KERNEL32_DLL` et `Constants::LOAD_LIBRARY_FUNC` pour obtenir un `handle` pour `kernel32.dll` et, ensuite, localiser l'adresse de la fonction de chargement de bibliothèques dynamiques.
2.  **Allocation de Mémoire à Distance :** `VirtualAllocEx` est utilisée pour réserver un bloc de mémoire dans l'espace d'adressage virtuel du processus `gta_sa.exe` (qui est suspendu). La taille de ce bloc est suffisante pour stocker le chemin complet de `samp.dll`.
3.  **Écriture du Chemin de la DLL :** Le chemin complet du fichier `samp.dll` est écrit dans cette mémoire distante nouvellement allouée via `WriteProcessMemory`.
4.  **Création de Thread Distant :** `CreateRemoteThread` est appelée pour créer un nouveau `thread` à l'intérieur du processus `gta_sa.exe`. Le point d'entrée de ce nouveau `thread` est l'adresse de `LoadLibraryW`, et l'argument qu'il reçoit est le pointeur vers le chemin de la DLL que nous venons d'écrire.
5.  **Surveillance de l'Injection :** L'exécution du `thread` distant est surveillée par `WaitForSingleObject` pendant une période définie par `Constants::DLL_INJECTION_TIMEOUT_MS`.
6.  **Vérification du Résultat :** Le code de sortie du `thread` distant est obtenu via `GetExitCodeThread`. Une valeur de retour non nulle indique que `LoadLibraryW` a réussi à charger `samp.dll`.

> [!WARNING]
> En cas d'échec lors de l'injection de `samp.dll`, un message d'erreur spécifique (`error_utils.hpp`) est affiché, le processus d'injection est interrompu, et les ressources sont libérées.

### 7. Injection de la Bibliothèque OMP (`omp-client.dll`) - Conditionnelle

Si le type d'injection spécifié est `OMP`, les étapes détaillées au point 6 sont répétées pour `omp-client.dll`.

> [!TIP]
> L'injection de `omp-client.dll` se produit toujours après l'injection réussie de `samp.dll`. Cela est dû au fait que le client Open Multiplayer s'appuie sur l'infrastructure fournie par `samp.dll`.

### 8. Activation du Jeu

Enfin, si toutes les injections ont été terminées avec succès, la méthode `process_info.Resume()` est invoquée. Cet appel exécute `ResumeThread` sur le `thread` principal de `gta_sa.exe`. À ce moment, le jeu est activé et commence son exécution normale, mais déjà avec les DLLs de SA-MP/OMP chargées dans sa mémoire et avec les paramètres de connexion configurés, permettant une connexion automatisée au serveur.

> [!WARNING]
> Si la reprise du `thread` du jeu échoue, un dernier message d'erreur est présenté à l'utilisateur.

## Diagnostic des Erreurs et des Pannes

La bibliothèque est méticuleusement conçue pour communiquer clairement tout problème qui pourrait survenir pendant le processus d'initialisation et d'injection. À n'importe quel point d'échec, une `MessageBox` avec une description détaillée est présentée à l'utilisateur, souvent complétée par des messages d'erreur du système d'exploitation.

### Échecs de Validation des Entrées

Ces erreurs sont détectées dans la phase initiale (`validation.hpp`), avant toute interaction de bas niveau avec le système, et indiquent des problèmes avec les données fournies par l'utilisateur ou avec la configuration de l'environnement.

#### Nom d'utilisateur Invalide

- **Message d'Erreur (Exemple 1) :** `"Nickname cannot be empty. Please provide a valid nickname."`
- **Message d'Erreur (Exemple 2) :** `"Nickname length exceeds the maximum allowed of 23 characters. Please use a shorter nickname."`
- **Raison :** Le nom d'utilisateur (`nickname`) fourni est vide ou dépasse la limite maximale de 23 caractères autorisée par les clients SA-MP/OMP.
- **Solution :** L'utilisateur doit saisir un nom d'utilisateur valide qui respecte les critères de longueur.

#### Port de Connexion Invalide

- **Message d'Erreur (Exemple 1) :** `"Invalid port format. The port must be a numeric value. Please provide a valid integer for the port."`
- **Message d'Erreur (Exemple 2) :** `"The specified port number (70000) is outside the valid range of 1 to 65535. Please provide a valid port."`
- **Raison :** La valeur fournie pour le port n'est pas un nombre entier ou se situe en dehors de la plage valide (1 à 65535).
- **Solution :** L'utilisateur doit fournir un numéro de port valide et dans la plage spécifiée.

#### Ressources Essentielles Manquantes

- **Message d'Erreur (Exemple 1) :** `"Game executable not found. Please ensure 'gta_sa.exe' exists at the specified path: C:\Games\GTA San Andreas\gta_sa.exe"`
- **Message d'Erreur (Exemple 2) :** `"SA-MP library not found. Please ensure 'samp.dll' exists at the specified path: C:\Games\GTA San Andreas\samp.dll"`
- **Message d'Erreur (Exemple 3, pour OMP) :** `"OMP library not found. Please ensure 'omp-client.dll' exists at the specified path for OMP injection: C:\Games\GTA San Andreas\omp-client.dll"`
- **Raison :** Un ou plusieurs fichiers cruciaux (`gta_sa.exe`, `samp.dll`, `omp-client.dll`) n'ont pas été trouvés dans le répertoire du jeu spécifié.
- **Solution :** Vérifiez le chemin du dossier du jeu et assurez-vous que tous les fichiers nécessaires sont présents et accessibles.

### Échecs dans la Gestion du Processus

Ces erreurs se produisent lorsque la bibliothèque tente de démarrer l'exécutable du jeu (`gta_sa.exe`).

#### Difficulté à Démarrer le Processus du Jeu

- **Message d'Erreur (Exemple) :** `"Failed to create game process. Ensure 'gta_sa.exe' is not running and you have sufficient permissions to execute the file. System Error: Access is denied."`
- **Raison :**
   - **Exécutable en cours d'utilisation :** `gta_sa.exe` peut déjà être en cours d'exécution, ou il y a un blocage du système d'exploitation qui empêche la création d'une nouvelle instance.
   - **Permissions Insuffisantes :** L'application peut ne pas avoir les autorisations appropriées pour démarrer `gta_sa.exe` ou pour accéder au fichier.
   - **Exécutable Corrompu :** Bien que la validation de base vérifie l'existence du fichier, il peut être corrompu ou inaccessible.
- **Solution :** Assurez-vous qu'aucune instance de `gta_sa.exe` n'est active. Essayez d'exécuter votre application en tant qu'administrateur. Vérifiez l'intégrité du fichier `gta_sa.exe`.

### Problèmes d'Injection de la DLL

Ce sont les erreurs les plus critiques et détaillées, survenant lors de la tentative d'injection de `samp.dll` ou `omp-client.dll` dans le processus suspendu du jeu. Les messages d'erreur commencent généralement par `"Failed to inject <DLL_NAME>:\n"` et sont suivis d'une description spécifique et d'un code d'erreur système.

#### Impossible de Localiser `LoadLibraryW`

- **Message d'Erreur (Partie) :** `"Failed to find the address of LoadLibraryW in kernel32.dll."`
- **Raison :** La fonction `LoadLibraryW`, une API fondamentale de Windows pour le chargement dynamique de DLLs, n'a pas pu être trouvée dans `kernel32.dll`. C'est un problème de bas niveau extrêmement rare, qui indique une possible corruption du système d'exploitation ou un environnement d'exécution très inhabituel.
- **Solution :** Un redémarrage du système peut résoudre le problème. Si cela persiste, cela peut indiquer un problème plus grave dans l'installation de Windows.

#### Échec de la Réservation de Mémoire à Distance

- **Message d'Erreur (Partie) :** `"Failed to allocate memory in the target process (VirtualAllocEx). System Error: Not enough storage is available to process this command."`
- **Raison :** La bibliothèque n'a pas pu allouer un bloc de mémoire dans l'espace d'adressage virtuel du processus `gta_sa.exe`.
   - **Permissions :** Votre application peut ne pas avoir les autorisations suffisantes pour modifier l'espace mémoire d'un autre processus.
   - **Protection de Processus :** Des mécanismes de sécurité du système d'exploitation ou des logiciels anti-triche peuvent bloquer l'allocation de mémoire dans des processus externes.
- **Solution :** Exécutez votre application en tant qu'administrateur. Vérifiez si des programmes de sécurité (antivirus, anti-triche) interfèrent et, si possible, désactivez-les temporairement pour tester.

#### Incapacité d'Écrire des Données dans le Processus

- **Message d'Erreur (Partie) :** `"Failed to write DLL path to process memory (WriteProcessMemory). System Error: Access is denied."`
- **Raison :** La mémoire a été allouée dans le processus du jeu, mais la bibliothèque n'a pas pu y écrire le chemin de la DLL.
   - **Permissions/Protection :** Similaire à l'échec d'allocation de mémoire, cela peut être un problème d'autorisation d'écriture ou une protection de mémoire active.
- **Solution :** Les mêmes solutions que pour l'échec d'allocation de mémoire s'appliquent.

#### Échec de la Création du Thread d'Injection

- **Message d'Erreur (Partie) :** `"Failed to create remote thread (CreateRemoteThread). System Error: The parameter is incorrect."`
- **Raison :** L'API `CreateRemoteThread` n'a pas réussi à démarrer un nouveau `thread` dans le processus `gta_sa.exe` pour appeler `LoadLibraryW`.
   - **Sécurité :** De nombreux systèmes anti-triche et protections de l'OS surveillent et bloquent la création de `threads` distants, car c'est une technique d'injection courante.
   - **État du Processus :** Le processus du jeu peut être dans un état instable qui empêche la création de `threads`.
- **Solution :** Désactivez temporairement tout logiciel anti-triche ou antivirus. Essayez d'exécuter l'application en tant qu'administrateur.

#### Délai d'Attente Dépassé ou Erreur lors de l'Attente de l'Injection

- **Message d'Erreur (Partie) :** `"Timeout or error waiting for remote thread (WaitForSingleObject). System Error: The wait operation timed out."`
- **Raison :** Le `thread` distant (qui appelle `LoadLibraryW`) n'a pas terminé son exécution dans le délai imparti (10 secondes).
   - **Blocage :** `LoadLibraryW` peut s'être bloqué, avoir pris trop de temps, ou avoir été intercepté/bloqué.
- **Solution :** Cela peut indiquer que la DLL a des difficultés à se charger ou que quelque chose l'en empêche. La vérification des journaux système ou de SA-MP/OMP (si disponibles) peut offrir plus d'indices.

#### Échec Interne de l'Injection de la DLL

- **Message d'Erreur (Partie) :** `"LoadLibraryW call failed in the target process. The DLL might be corrupt, missing dependencies, or blocked by security software."`
- **Raison :** Le `thread` distant s'est terminé, mais la valeur de retour de `LoadLibraryW` était `0` (ou `NULL`), indiquant que la DLL n'a pas été chargée avec succès.
   - **DLL Corrompue/Inexistante :** La DLL a peut-être été déplacée, supprimée ou corrompue après la validation initiale.
   - **Dépendances Manquantes :** `samp.dll` ou `omp-client.dll` peuvent avoir des dépendances (d'autres DLLs) qui ne sont pas présentes dans le répertoire du jeu ou dans le `PATH` système.
   - **Erreur Interne de la DLL :** La DLL elle-même peut avoir une erreur interne qui empêche son chargement.
- **Solution :** Vérifiez l'intégrité des fichiers `samp.dll`/`omp-client.dll`. Assurez-vous que toutes leurs dépendances sont présentes.

### Difficulté à Reprendre l'Exécution du Jeu

C'est le dernier point de défaillance possible dans le cycle d'injection.

- **Message d'Erreur (Exemple) :** `"Failed to resume the game process thread: Invalid handle."`
- **Raison :** L'API `ResumeThread` n'a pas réussi à réactiver le `thread` principal de `gta_sa.exe`.
   - **Handle Invalide :** Le `handle` du `thread` a peut-être été invalidé par un événement inattendu.
   - **Permission :** L'application peut ne pas avoir la permission de modifier l'état du `thread`.
- **Solution :** Essayez d'exécuter l'application en tant qu'administrateur. Si le problème persiste, cela peut indiquer un problème de stabilité plus profond dans le système ou dans le processus du jeu.

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