# SA-MP Injector C#

<div align="center">

![C#](https://img.shields.io/badge/C%23-11.0%2B-512BD4?style=for-the-badge&logo=csharp&logoColor=white)
![.NET](https://img.shields.io/badge/.NET-7.0%2B-512BD4?style=for-the-badge&logo=dotnet&logoColor=white)
![Platform](https://img.shields.io/badge/Platform-Windows-blue?style=for-the-badge&logo=windows&logoColor=white)
![Architecture](https://img.shields.io/badge/Architecture-x86%20(32--bit)-lightgrey?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)

**Une bibliothèque C# pour l'injection programmatique de DLL dans les processus SA-MP et OMP, permettant la connexion automatisée aux serveurs.**

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

- [SA-MP Injector C#](#sa-mp-injector-c)
  - [Langues](#langues)
  - [Table des matières](#table-des-matières)
  - [Introduction et Objectif](#introduction-et-objectif)
  - [Philosophie de Conception](#philosophie-de-conception)
    - [Interopérabilité (P/Invoke)](#interopérabilité-pinvoke)
    - [Gestion des Ressources (`SafeHandle`)](#gestion-des-ressources-safehandle)
    - [Sécurité et Robustesse](#sécurité-et-robustesse)
  - [Configuration Requise](#configuration-requise)
    - [Environnement de Développement](#environnement-de-développement)
    - [Environnement d'Exécution](#environnement-dexécution)
  - [Installation et Utilisation de Base](#installation-et-utilisation-de-base)
    - [Ajout à Votre Projet](#ajout-à-votre-projet)
    - [Exemple d'Utilisation](#exemple-dutilisation)
  - [Composants de la Bibliothèque](#composants-de-la-bibliothèque)
    - [1. `Constants.cs`](#1-constantscs)
    - [2. `InjectionType.cs`](#2-injectiontypecs)
    - [3. `Injector.cs`](#3-injectorcs)
    - [4. `InjectorCore.cs`](#4-injectorcorecs)
    - [5. `InputValidator.cs`](#5-inputvalidatorcs)
    - [6. `NativeImports.cs`](#6-nativeimportscs)
    - [7. `ProcessHandler.cs`](#7-processhandlercs)
    - [8. `SafeHandles.cs`](#8-safehandlescs)
  - [Cycle d'Injection de DLL Détaillé](#cycle-dinjection-de-dll-détaillé)
    - [1. Validation des Entrées](#1-validation-des-entrées)
    - [2. Création du Processus du Jeu (Suspendu)](#2-création-du-processus-du-jeu-suspendu)
    - [3. Injection de `samp.dll`](#3-injection-de-sampdll)
    - [4. Injection de `omp-client.dll` (Optionnel, Dépendant de SA-MP)](#4-injection-de-omp-clientdll-optionnel-dépendant-de-sa-mp)
    - [Reprendre le Thread Principal du Jeu](#reprendre-le-thread-principal-du-jeu)
  - [Gestion des Erreurs et Cas de Défaillance](#gestion-des-erreurs-et-cas-de-défaillance)
    - [Erreurs de Validation des Entrées](#erreurs-de-validation-des-entrées)
      - [Pseudo Invalide](#pseudo-invalide)
      - [Port Invalide](#port-invalide)
      - [Fichiers de Jeu/DLLs Manquants](#fichiers-de-jeudlls-manquants)
    - [Erreurs lors de la Création du Processus](#erreurs-lors-de-la-création-du-processus)
      - [Échec de la Création du Processus](#échec-de-la-création-du-processus)
    - [Erreurs lors de l'Injection de la DLL](#erreurs-lors-de-linjection-de-la-dll)
      - [Handle `kernel32.dll` Indisponible](#handle-kernel32dll-indisponible)
      - [Fonction `LoadLibraryA` Indisponible](#fonction-loadlibrarya-indisponible)
      - [Échec de l'Allocation de Mémoire à Distance](#échec-de-lallocation-de-mémoire-à-distance)
      - [Échec de l'Écriture dans la Mémoire du Processus](#échec-de-lécriture-dans-la-mémoire-du-processus)
      - [Échec de la Création du Thread à Distance](#échec-de-la-création-du-thread-à-distance)
      - [Timeout ou Erreur lors de l'Attente de l'Injection](#timeout-ou-erreur-lors-de-lattente-de-linjection)
      - [L'Injection de la DLL a Échoué ou a Retourné une Erreur](#linjection-de-la-dll-a-échoué-ou-a-retourné-une-erreur)
    - [Erreur lors de la Reprise du Thread du Jeu](#erreur-lors-de-la-reprise-du-thread-du-jeu)
  - [Licence](#licence)
    - [Conditions Générales d'Utilisation](#conditions-générales-dutilisation)
      - [1. Autorisations Accordées](#1-autorisations-accordées)
      - [2. Conditions Obligatoires](#2-conditions-obligatoires)
      - [3. Droits d'Auteur](#3-droits-dauteur)
      - [4. Exclusion de Garantie et Limitation de Responsabilité](#4-exclusion-de-garantie-et-limitation-de-responsabilité)

## Introduction et Objectif

La bibliothèque **SA-MP Injector C#** est une solution en C# conçue pour simplifier le lancement et la connexion automatisée des clients San Andreas Multiplayer (SA-MP) et Open Multiplayer (OMP) aux serveurs. Elle agit comme un outil d'injection de DLL (Dynamic Link Library), chargeant par programmation les bibliothèques `samp.dll` ou `omp-client.dll` dans le processus du jeu Grand Theft Auto: San Andreas (`gta_sa.exe`).

L'objectif principal de cette bibliothèque est de permettre à d'autres applications C# (telles que des lanceurs personnalisés, des outils de gestion de serveur ou des utilitaires) de démarrer le jeu avec des paramètres spécifiques (pseudo, IP, port et mot de passe) de manière transparente pour l'utilisateur, automatisant ainsi le processus de connexion à un serveur SA-MP/OMP.

## Philosophie de Conception

La conception de **SA-MP Injector C#** se concentre sur la robustesse, la sécurité et une interface d'utilisation simplifiée, encapsulant les complexités des opérations de bas niveau du système.

### Interopérabilité (P/Invoke)

La fonctionnalité centrale de l'injection de DLL et de la création de processus suspendus est intrinsèquement une opération de système d'exploitation de bas niveau. Pour cela, la bibliothèque utilise largement la fonctionnalité **P/Invoke (Platform Invoke)** de .NET, permettant d'appeler des fonctions natives de l'API Windows (principalement de `kernel32.dll`) directement depuis le code C#. Cela est évident dans la déclaration des méthodes `partial` et l'utilisation de l'attribut `[LibraryImport(KERNEL32, SetLastError = true)]`.

### Gestion des Ressources (`SafeHandle`)

Les opérations avec les ressources du système d'exploitation, telles que les "handles" de processus et de threads, nécessitent une gestion minutieuse pour éviter les fuites de mémoire ou de ressources. La bibliothèque utilise des classes dérivées de `SafeHandle` (`SafeProcessHandle` et `SafeThreadHandle`) pour garantir que ces ressources sont toujours libérées correctement, même en cas d'exceptions. Cela adhère au principe de **RAII (Resource Acquisition Is Initialization)** de C++ et l'étend à l'environnement .NET.

### Sécurité et Robustesse

La bibliothèque intègre plusieurs couches de sécurité :
- **Validation des Entrées :** Toutes les entrées fournies par l'utilisateur sont rigoureusement validées avant le début de toute opération critique, minimisant ainsi le risque d'erreurs d'exécution ou de comportements inattendus.
- **Gestion des Erreurs :** Les appels d'API natives sont accompagnés de vérifications d'erreurs (`SetLastError = true` et `Marshal.GetLastWin32Error()`) pour fournir des messages d'erreur détaillés et compréhensibles.
- **Terminaison du Processus :** En cas d'échec pendant le processus d'injection, le processus de jeu nouvellement créé est automatiquement terminé pour éviter que des processus "zombies" ne restent en cours d'exécution.

## Configuration Requise

### Environnement de Développement

- **.NET SDK 7.0 ou supérieur :** La bibliothèque est construite pour `net7.0-windows`.
- **C# 11.0 ou supérieur :** Nécessaire pour des fonctionnalités telles que `ImplicitUsings`, `Nullable`, `AllowUnsafeBlocks` et `LibraryImport`.
- **Visual Studio 2022 ou un environnement de développement compatible :** Pour construire et intégrer la bibliothèque.
- **Plateforme de Compilation :** `x86 (32-bit)` est la cible obligatoire en raison de l'architecture de `gta_sa.exe` et des DLLs SA-MP/OMP.

```xml
<!-- samp-injector-csharp.csproj -->
<Project Sdk="Microsoft.NET.Sdk">
    <PropertyGroup>
        <TargetFrameworks>net7.0-windows</TargetFrameworks>
        <PlatformTarget>x86</PlatformTarget> <!-- CRITIQUE : Doit être x86 -->
        <ImplicitUsings>enable</ImplicitUsings>
        <Nullable>enable</Nullable>
        <UseWindowsForms>true</UseWindowsForms>
        <AllowUnsafeBlocks>true</AllowUnsafeBlocks> <!-- Nécessaire pour P/Invoke avancé -->
    </PropertyGroup>
</Project>
```

### Environnement d'Exécution

- **Système d'Exploitation :** Windows (toute version moderne compatible avec .NET 7.0+).
- **Grand Theft Auto: San Andreas (GTA: SA) :** L'installation du jeu est requise.
- **DLLs du Client SA-MP ou OMP :** `samp.dll` ou `omp-client.dll` doivent être présents dans le répertoire racine du jeu, selon le type d'injection souhaité.

## Installation et Utilisation de Base

### Ajout à Votre Projet

La manière la plus simple d'utiliser cette bibliothèque est d'ajouter le projet `Samp_Injector_CSharp` comme référence dans votre propre projet C#.

1. Clonez ou téléchargez le dépôt de la bibliothèque.
2. Dans Visual Studio, faites un clic droit sur "Dependencies" (ou "Références") dans votre projet.
3. Sélectionnez "Add Project Reference...".
4. Naviguez jusqu'au répertoire de la bibliothèque et ajoutez le projet `samp-injector-csharp.csproj`.

### Exemple d'Utilisation

Pour démarrer le jeu et vous connecter à un serveur, il suffit d'appeler la méthode statique `Injector.Initialize_Game`.

```csharp
using Samp_Injector_CSharp;
using System;
using System.Windows.Forms; // Pour MessageBox, si ce n'est pas un projet WinForms

namespace Launcher {
    public partial class Main : Form {
        public Main() {
            InitializeComponent();
        }

        private void Connect(object sender, EventArgs e) {
            string inject_type = "SAMP"; // "SAMP" ou "OMP"
            string game_folder = @"C:\Games\GTA San Andreas"; // Chemin vers le dossier de GTA: SA
            string nickname = "Nom";
            string ip = "127.0.0.1";
            string port = "7777";
            string password = ""; // Laissez vide s'il n'y a pas de mot de passe

            // Exemple d'injection SA-MP
            Injector.Initialize_Game(inject_type, game_folder, nickname, ip, port, password);

            // S'il s'agit d'OMP, modifiez inject_type :
            // inject_type = "OMP";
            // Injector.Initialize_Game(inject_type, game_folder, nickname, ip, port, password);
        }
    }
}
```

## Composants de la Bibliothèque

La bibliothèque est structurée en plusieurs fichiers, chacun avec une responsabilité claire et bien définie, ce qui favorise l'organisation, la maintenabilité et la séparation des responsabilités. Voici une description détaillée de chaque composant.

### 1. `Constants.cs`

Ce fichier est un dépôt centralisé de toutes les constantes et valeurs immuables utilisées dans toute la bibliothèque. Son existence favorise la maintenance du code, la lisibilité et la cohérence, en garantissant que les valeurs critiques sont définies à un seul endroit.

L'organisation des constantes par catégorie facilite la compréhension de leur objectif :

- **Game Related Constants**
   - `MIN_PORT` : Définit la valeur minimale autorisée pour le port de connexion d'un serveur (1).
   - `MAX_PORT` : Définit la valeur maximale autorisée pour le port de connexion d'un serveur (65535).
   - `MAX_NICKNAME_LENGTH` : Spécifie la longueur maximale autorisée pour le pseudo du joueur (23 caractères), une limite imposée par le client SA-MP/OMP lui-même.

- **File Names**
   - `SAMP_DLL_NAME` : Le nom du fichier de la bibliothèque principale du client SA-MP (`"samp.dll"`).
   - `OMP_DLL_NAME` : Le nom du fichier de la bibliothèque du client Open Multiplayer (`"omp-client.dll"`), utilisé dans les injections de type OMP.
   - `GAME_EXE_NAME` : Le nom du fichier exécutable du jeu Grand Theft Auto: San Andreas (`"gta_sa.exe"`).

- **System Libraries and Functions**
   - `KERNEL32_DLL` : Le nom de la bibliothèque système de Windows qui contient des fonctions essentielles pour la manipulation des processus et de la mémoire (`"kernel32.dll"`).
   - `LOAD_LIBRARY_FUNC` : Le nom de la fonction dans `kernel32.dll` responsable du chargement dynamique d'une bibliothèque (`"LoadLibraryA"`).

- **Command Line Arguments**
   - `CMD_ARGS_PART1` : Partie initiale des arguments de ligne de commande pour le jeu (`"-c -n "`).
   - `CMD_ARGS_PART2` : Séparateur pour l'adresse IP (`" -h "`).
   - `CMD_ARGS_PART3` : Séparateur pour le port (`" -p "`).
   - `CMD_ARGS_PART4_PASSWORD` : Préfixe pour l'argument du mot de passe (`" -z "`), utilisé uniquement si un mot de passe est fourni.
   - `CMD_ARGS_BASE_LENGTH` : La longueur prédéfinie des parties constantes de la ligne de commande, à l'exclusion de l'exécutable et des valeurs de l'utilisateur (14 caractères).
   - `CMD_ARG_PASSWORD_LENGTH` : La longueur du préfixe de l'argument du mot de passe (4 caractères).

- **Error Message Titles**
   - `ERROR_TITLE_SAMP` : Titre par défaut pour les boîtes de dialogue d'erreur liées aux échecs de SA-MP (`"SA-MP Injector Error - SPC"`).
   - `ERROR_TITLE_OMP` : Titre par défaut pour les boîtes de dialogue d'erreur liées aux échecs de OMP (`"OMP Injector Error - SPC"`).

- **Process Creation Flags**
   - `CREATE_SUSPENDED` : Drapeau qui ordonne au système d'exploitation de créer un processus et son thread principal dans un état suspendu (`0x00000004`). Ceci est fondamental pour l'injection de la DLL avant que le jeu ne commence à s'exécuter.
   - `PROCESS_CREATION_FLAGS` : Une combinaison de drapeaux de création de processus, actuellement définie uniquement comme `CREATE_SUSPENDED`.

- **Timeouts**
   - `DLL_INJECTION_TIMEOUT_MS` : Le temps maximum (en millisecondes) que la bibliothèque attendra pour la fin du thread distant responsable de l'injection de la DLL (10000ms = 10 secondes).

- **Memory Allocation Flags**
   - `MEM_COMMIT` : Drapeau qui réserve des pages dans la mémoire virtuelle et les "commit" (alloue de la mémoire physique) (`0x1000`).
   - `MEM_RESERVE` : Drapeau qui réserve simplement une plage d'espace d'adressage virtuel pour une utilisation ultérieure (`0x2000`).
   - `MEM_RELEASE` : Drapeau qui décommite et libère une région de pages (`0x8000`).
   - `MEMORY_ALLOCATION_TYPE` : Une combinaison de `MEM_COMMIT` et `MEM_RESERVE`, utilisée pour allouer de la mémoire pour le chemin de la DLL dans le processus distant.
   - `MEMORY_PROTECTION` : Définit les autorisations de protection de la mémoire (actuellement `0x04`, ce qui correspond à `PAGE_READWRITE` dans l'API Windows, permettant la lecture et l'écriture dans la mémoire allouée).

### 2. `InjectionType.cs`

Ce fichier définit un énumérateur simple pour fournir un moyen sûr et clair de spécifier le type d'injection à effectuer. L'utilisation d'un `enum` au lieu de chaînes de caractères (`"samp"`, `"omp"`) prévient les fautes de frappe et rend le code plus lisible et robuste.

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

Ce fichier est la façade (Facade) publique de la bibliothèque, servant de point d'entrée unique pour les applications consommatrices. Il abstrait toute la complexité interne du processus d'injection en une seule méthode statique.

- **Responsabilité Principale :** La méthode `Initialize_Game` reçoit tous les paramètres nécessaires sous forme de chaînes de caractères, détermine le type d'injection et délègue le travail à `Injector_Core`. Elle est également responsable de capturer le résultat de l'opération et de présenter des messages d'erreur à l'utilisateur final via `MessageBox`, rendant l'interaction avec l'utilisateur final cohérente.

```csharp
// Extrait de Injector.cs
public static class Injector {
    private static readonly Injector_Core s_core = new();

    public static void Initialize_Game(string inject_type_str, string folder, string nickname, string ip, string port, string password) {
        // ... Logique pour convertir inject_type_str en Injection_Type ...

        if (!s_core.Try_Initialize_Game(type, folder, nickname, ip, port, password, out string error_message)) {
            string error_title = (type == Injection_Type.OMP) ? Constants.ERROR_TITLE_OMP : Constants.ERROR_TITLE_SAMP;
            MessageBox.Show(error_message, error_title, MessageBoxButtons.OK, MessageBoxIcon.Error);
        }
    }
}
```

### 4. `InjectorCore.cs`

C'est le "cerveau" de la bibliothèque, où la séquence des opérations d'injection est orchestrée. Il relie les validateurs d'entrée aux gestionnaires de processus pour exécuter le flux de travail complet.

- **Responsabilité Principale :** La méthode `Try_Initialize_Game` définit la logique étape par étape : elle valide les entrées, crée le processus du jeu en état suspendu, injecte les DLL nécessaires (`samp.dll` et, optionnellement, `omp-client.dll`) et, si tout réussit, reprend le thread du jeu. Un aspect crucial est le bloc `finally`, qui garantit que le processus du jeu est terminé (`Kill()`) en cas de défaillance pendant les étapes d'injection, évitant ainsi les processus "zombies".

```csharp
// Extrait de InjectorCore.cs
internal sealed class Injector_Core {
    public bool Try_Initialize_Game(...) {
        // ... Validation des entrées ...

        using Process_Handler.Process_Info process_info = Process_Handler.Create_Game_Process(...);
        
        // ...
        bool success = false;
        try {
            // ... Injection de samp.dll ...
            // ... Injection optionnelle de omp-client.dll ...
            // ... Reprise du thread du jeu ...
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

Agit comme la première ligne de défense de la bibliothèque, garantissant que seules des données valides et sûres sont traitées. La validation préalable prévient les exceptions de bas niveau et permet à la bibliothèque de fournir des messages d'erreur clairs et exploitables.

- **Responsabilité Principale :** La méthode statique `Try_Validate` exécute une série de vérifications, y compris le format du pseudo, l'intervalle numérique du port et, de manière cruciale, l'existence des fichiers essentiels (`gta_sa.exe`, `samp.dll`, etc.) dans le répertoire spécifié. Si une vérification échoue, elle retourne `false` et remplit une `out string` avec la description de l'erreur.

```csharp
// Extrait de InputValidator.cs
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

Ce fichier est le pont entre le code managé de C# et les API natives non managées de Windows. Il utilise la fonctionnalité d'interopérabilité P/Invoke pour déclarer les signatures de fonctions de `kernel32.dll`.

- **Responsabilité Principale :** Déclarer des méthodes `extern` avec les attributs `[LibraryImport]` ou `[DllImport]` qui correspondent aux fonctions de l'API Windows, telles que `CreateProcessA`, `VirtualAllocEx` et `CreateRemoteThread`. Il définit également les structures de données (`Startup_Info`, `Process_Information`) avec une disposition de mémoire compatible avec le code natif. Pour l'optimisation, les handles pour `kernel32.dll` et l'adresse de la fonction `LoadLibraryA` sont chargés statiquement à l'initialisation.

```csharp
// Extrait de NativeImports.cs
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

C'est la couche de bas niveau qui exécute les opérations de manipulation de processus. Il utilise les fonctions importées de `NativeImports.cs` pour interagir directement avec le système d'exploitation.

- **Responsabilités Principales :**
   1. **`Create_Game_Process`** : Construit la ligne de commande et démarre `gta_sa.exe` avec le drapeau `CREATE_SUSPENDED`.
   2. **`Inject_DLL`** : Implémente la technique d'injection de DLL via la création d'un thread distant. C'est la fonction la plus critique, orchestrant l'allocation de mémoire, l'écriture et l'exécution à distance de `LoadLibraryA`.
   3. **`Resume_Game_Thread`** : Réalise l'étape finale de "dégeler" le thread principal du jeu.

```csharp
// Extrait de ProcessHandler.cs
internal static bool Inject_DLL(SafeProcessHandle process_handle, string dll_path, out string error_message) {
    // ... Allocation et écriture dans la mémoire distante ...

    IntPtr remote_thread = Native_Imports.CreateRemoteThread(process_handle, IntPtr.Zero, 0, Native_Imports.load_library_address, remote_memory, 0, IntPtr.Zero);

    if (remote_thread == IntPtr.Zero)
        return (error_message = $"Failed to create a remote thread...") != null && false;
    
    // ... Attente de la fin et vérification du résultat ...
    return true;
}
```

### 8. `SafeHandles.cs`

Ce fichier met en œuvre une pratique recommandée d'interopérabilité : l'utilisation de `SafeHandle` pour gérer les ressources non managées. Cela garantit que les "handles" de processus et de thread de Windows sont libérés de manière déterministe et sûre.

- **Responsabilité Principale :** Les classes `SafeProcessHandle` et `SafeThreadHandle` héritent de `SafeHandleZeroOrMinusOneIsInvalid`. Elles encapsulent un `IntPtr` qui représente le handle natif. Le principal avantage est l'implémentation de la méthode `ReleaseHandle`, qui est garantie par le runtime .NET d'être appelée lorsque l'objet est détruit (par exemple, à la fin d'un bloc `using`), prévenant ainsi les fuites de ressources.

```csharp
// Extrait de SafeHandles.cs
internal sealed class SafeProcessHandle : SafeHandleZeroOrMinusOneIsInvalid {
    // ... Constructeurs ...

    protected override bool ReleaseHandle() {
        // Cet appel est garanti par .NET pour libérer le handle natif.
        return Native_Imports.CloseHandle(handle);
    }
}
```

## Cycle d'Injection de DLL Détaillé

Le processus d'injection de DLL est une séquence d'étapes critiques qui doivent être exécutées avec précision pour réussir. La bibliothèque **SA-MP Injector C#** orchestre cela de la manière suivante :

### 1. Validation des Entrées

Avant toute interaction avec le système, tous les paramètres fournis par l'utilisateur (chemin du dossier du jeu, pseudo, IP, port et mot de passe) sont vérifiés par `Input_Validator`. Cela inclut :
- Vérifier que le pseudo respecte les limites de longueur et n'est pas vide.
- S'assurer que le port est un nombre valide et se situe dans la plage acceptable (1-65535).
- Confirmer que `gta_sa.exe`, `samp.dll` et `omp-client.dll` (si `Injection_Type` est OMP) existent aux chemins attendus.

> [!NOTE]
> Cette étape préventive est fondamentale pour éviter les échecs inattendus de l'API et fournir un retour clair à l'utilisateur.

### 2. Création du Processus du Jeu (Suspendu)

La bibliothèque utilise `Native_Imports.CreateProcessA` pour démarrer `gta_sa.exe`. Cependant, un détail crucial est l'utilisation du drapeau `Constants.CREATE_SUSPENDED`.
- **Création Suspendue :** Ce drapeau fait en sorte que Windows crée le processus et son thread principal, mais le place dans un état suspendu, empêchant le code du jeu de commencer à s'exécuter.
- **Ligne de Commande :** La ligne de commande est soigneusement construite par `Process_Handler.Build_Full_Command_Args_ANSI` pour inclure tous les paramètres de connexion au serveur (`-c -n <nickname> -h <ip> -p <port> -z <password>`).
- **Handles de Processus/Thread :** `CreateProcessA` retourne les handles pour le processus et le thread principal, qui sont encapsulés dans `SafeProcessHandle` et `SafeThreadHandle` pour une gestion sûre des ressources.

> [!IMPORTANT]
> La création suspendue est vitale pour l'injection. Si le jeu commençait à s'exécuter avant l'injection, il pourrait initialiser ses propres mécanismes de sécurité ou la `samp.dll`/`omp-client.dll` pourrait être chargée avant notre contrôle, rendant l'injection plus complexe ou inefficace.

### 3. Injection de `samp.dll`

Avec le processus du jeu suspendu, la fonction `Process_Handler.Inject_DLL` exécute les étapes suivantes :
1.  **Obtenir `LoadLibraryA` :** L'adresse de la fonction `LoadLibraryA` (de `kernel32.dll`) dans le processus du jeu est obtenue. C'est la fonction que Windows utilise pour charger les DLLs.
2.  **Allocation de Mémoire à Distance :** `Native_Imports.VirtualAllocEx` est utilisée pour allouer un bloc de mémoire dans l'espace d'adressage virtuel du processus `gta_sa.exe`. La taille du bloc est suffisante pour stocker le chemin complet de `samp.dll`.
3.  **Écriture du Chemin de la DLL :** Le chemin complet du fichier `samp.dll` est écrit dans la mémoire nouvellement allouée dans le processus du jeu en utilisant `Native_Imports.WriteProcessMemory`.
4.  **Création d'un Thread à Distance :** `Native_Imports.CreateRemoteThread` est appelée pour créer un nouveau thread dans le processus `gta_sa.exe`. Ce thread est instruit d'exécuter `LoadLibraryA` avec l'adresse de la chaîne de caractères du chemin de la DLL comme unique argument.
5.  **Attendre la Fin :** La bibliothèque attend un délai d'attente (`Constants.DLL_INJECTION_TIMEOUT_MS`) pour que le thread distant termine son exécution, indiquant que `LoadLibraryA` a tenté de charger la DLL.
6.  **Vérifier le Résultat :** Le code de sortie du thread distant est vérifié. Si `LoadLibraryA` a réussi, elle retourne l'adresse de base de la DLL chargée. Une valeur nulle ou un échec dans l'obtention du code de sortie indique que l'injection a échoué.
7.  **Nettoyage :** La mémoire distante allouée est libérée (`Native_Imports.VirtualFreeEx`) et le handle du thread distant est fermé (`Native_Imports.CloseHandle`).

### 4. Injection de `omp-client.dll` (Optionnel, Dépendant de SA-MP)

> [!TIP]
> L'injection de `omp-client.dll` **a toujours lieu après l'injection réussie de `samp.dll`**. Le client OMP utilise l'infrastructure de SA-MP, donc `samp.dll` est une exigence.

Si le `Injection_Type` spécifié est `OMP`, l'étape 3 est répétée pour injecter `omp-client.dll`. La logique est identique, garantissant que les deux bibliothèques nécessaires pour OMP sont chargées avant que le jeu ne démarre complètement.

### Reprendre le Thread Principal du Jeu

Enfin, après que toutes les DLL nécessaires ont été injectées avec succès, la fonction `Process_Handler.Resume_Game_Thread` est appelée. Cette fonction utilise `Native_Imports.ResumeThread` pour permettre au thread principal de `gta_sa.exe` de continuer son exécution. Le jeu démarre maintenant avec les DLLs SA-MP/OMP déjà chargées et les arguments de ligne de commande pour la connexion au serveur appliqués.

## Gestion des Erreurs et Cas de Défaillance

La bibliothèque a été conçue pour fournir un retour clair en cas d'échec. La plupart des erreurs sont capturées et un `error_message` descriptif est retourné pour être présenté à l'utilisateur, généralement via une `MessageBox`.

### Erreurs de Validation des Entrées

Ces erreurs se produisent avant toute opération système et sont détectées par `Input_Validator`.

#### Pseudo Invalide

- **Message d'Erreur (Exemple 1) :** `"Nickname cannot be empty. Please provide a valid nickname."`
- **Message d'Erreur (Exemple 2) :** `"Nickname length exceeds the maximum allowed of 23 characters. Please use a shorter nickname."`
- **Pourquoi :** Le champ du pseudo est vide ou dépasse la limite maximale de 23 caractères.
- **Solution :** L'utilisateur doit fournir un pseudo valide qui respecte la limite de caractères.

#### Port Invalide

- **Message d'Erreur (Exemple 1) :** `"Invalid port format. The port must be a numeric value. Please provide a valid integer for the port."`
- **Message d'Erreur (Exemple 2) :** `"The specified port number (70000) is outside the valid range of 1 to 65535. Please provide a valid port."`
- **Pourquoi :** Le port fourni n'est pas un nombre entier, ou il est en dehors de la plage valide de 1 à 65535.
- **Solution :** L'utilisateur doit saisir un numéro de port valide et dans la plage spécifiée.

#### Fichiers de Jeu/DLLs Manquants

- **Message d'Erreur (Exemple 1) :** `"Game executable not found. Please ensure 'gta_sa.exe' exists at the specified path: C:\Program Files (x86)\Rockstar Games\GTA San Andreas\gta_sa.exe"`
- **Message d'Erreur (Exemple 2) :** `"SA-MP library not found. Please ensure 'samp.dll' exists at the specified path: C:\Program Files (x86)\Rockstar Games\GTA San Andreas\samp.dll"`
- **Message d'Erreur (Exemple 3, OMP) :** `"OMP library not found. Please ensure 'omp-client.dll' exists at the specified path for OMP injection: C:\Program Files (x86)\Rockstar Games\GTA San Andreas\omp-client.dll"`
- **Pourquoi :** Le fichier exécutable du jeu (`gta_sa.exe`), la DLL de SA-MP (`samp.dll`) ou la DLL de OMP (`omp-client.dll`) n'ont pas été trouvés dans le dossier du jeu spécifié.
- **Solution :** L'utilisateur doit vérifier le chemin du dossier du jeu et s'assurer que tous les fichiers nécessaires sont présents.

### Erreurs lors de la Création du Processus

Ces erreurs se produisent lorsque la bibliothèque tente de démarrer `gta_sa.exe`.

#### Échec de la Création du Processus

- **Message d'Erreur (Exemple) :** `"Failed to create game process. Ensure 'gta_sa.exe' is not running and you have sufficient permissions to execute the file. System Error: Access is denied."`
- **Pourquoi :**
   - **Fichier en cours d'utilisation :** `gta_sa.exe` est peut-être déjà en cours d'exécution, empêchant la création d'une nouvelle instance, ou le système d'exploitation a un verrou sur le fichier.
   - **Permissions :** L'utilisateur qui exécute l'application peut ne pas avoir les autorisations suffisantes pour démarrer un nouveau processus ou pour accéder à l'exécutable du jeu.
   - **Chemin Invalide/Corrompu :** Bien que la validation de base vérifie l'existence, il peut y avoir des problèmes d'autorisation de lecture/exécution ou l'exécutable peut être corrompu.
- **Solution :** Assurez-vous qu'aucune autre instance de `gta_sa.exe` n'est en cours d'exécution. Exécutez l'application en tant qu'administrateur, si possible. Vérifiez l'intégrité du fichier `gta_sa.exe`.

### Erreurs lors de l'Injection de la DLL

Ce sont les erreurs les plus critiques et elles se produisent lors de la tentative d'injection de `samp.dll` ou `omp-client.dll` dans le processus du jeu.

#### Handle `kernel32.dll` Indisponible

- **Message d'Erreur :** `"Failed to obtain a handle to kernel32.dll. This is an essential system library and this error indicates a severe system issue."`
- **Pourquoi :** La bibliothèque `kernel32.dll`, fondamentale pour les opérations système sous Windows, n'a pas pu être chargée ou son handle n'a pas pu être obtenu. C'est extrêmement rare et suggère un problème grave du système d'exploitation.
- **Solution :** Redémarrer le système peut résoudre le problème. Sinon, cela indique un problème plus profond avec l'installation de Windows.

#### Fonction `LoadLibraryA` Indisponible

- **Message d'Erreur :** `"Failed to find the address of the LoadLibraryA function in kernel32.dll. This is critical for injecting the DLL."`
- **Pourquoi :** La fonction `LoadLibraryA`, essentielle pour charger dynamiquement les DLLs, n'a pas pu être trouvée dans `kernel32.dll`. Comme l'erreur précédente, c'est un problème de bas niveau rare.
- **Solution :** Similaire à l'indisponibilité du handle de `kernel32.dll`.

#### Échec de l'Allocation de Mémoire à Distance

- **Message d'Erreur :** `"Failed to allocate memory in the target process. This might be due to insufficient permissions or process protection mechanisms."`
- **Pourquoi :** La bibliothèque n'a pas pu allouer un bloc de mémoire dans l'espace d'adressage de `gta_sa.exe`.
   - **Permissions :** L'application peut ne pas avoir les autorisations nécessaires pour modifier l'espace mémoire d'un autre processus.
   - **Protection du Processus :** Le processus `gta_sa.exe` ou le système d'exploitation peut appliquer des protections contre l'injection de code.
   - **Espace d'Adressage :** Dans des cas extrêmes, l'espace d'adressage du processus peut être fragmenté ou manquer de mémoire contiguë suffisante, bien que cela soit peu probable pour la taille d'une chaîne de chemin de DLL.
- **Solution :** Exécutez l'application en tant qu'administrateur. Vérifiez s'il existe un logiciel de sécurité (antivirus, anti-triche) qui pourrait bloquer l'allocation de mémoire dans d'autres processus.

#### Échec de l'Écriture dans la Mémoire du Processus

- **Message d'Erreur :** `"Failed to write DLL path to the target process memory. Verify process permissions and ensure the DLL path is accessible."`
- **Pourquoi :** La bibliothèque a alloué de la mémoire dans le processus du jeu, mais n'a pas pu y écrire le chemin de la DLL.
   - **Permissions :** Similaire à l'échec de l'allocation de mémoire, cela peut être un problème d'autorisation d'écriture.
   - **Protection :** La protection de la mémoire du système d'exploitation ou un anti-triche peut empêcher l'écriture.
- **Solution :** Vérifiez les autorisations et les logiciels de sécurité.

#### Échec de la Création du Thread à Distance

- **Message d'Erreur (Exemple) :** `"Failed to create a remote thread in the target process to execute the DLL injection. This could be due to security restrictions or process state. System Error: Not enough memory resources are available to process this command."`
- **Pourquoi :** L'API `CreateRemoteThread` a échoué à créer un nouveau thread dans le processus `gta_sa.exe` pour appeler `LoadLibraryA`.
   - **Protection du Processus/Anti-Triche :** De nombreux systèmes anti-triche et protections du système d'exploitation surveillent et bloquent la création de threads distants, car c'est une technique courante d'injection.
   - **État du Processus :** Le processus du jeu peut être dans un état incohérent qui empêche la création de threads.
- **Solution :** Désactivez temporairement tout logiciel anti-triche ou antivirus. Essayez d'exécuter l'application en tant qu'administrateur.

#### Timeout ou Erreur lors de l'Attente de l'Injection

- **Message d'Erreur (Exemple) :** `"Timeout or error waiting for DLL injection to complete. System Error: The wait operation timed out."`
- **Pourquoi :** Le thread distant (qui appelle `LoadLibraryA`) n'a pas terminé son exécution dans le délai spécifié (10 secondes).
   - **Gel :** `LoadLibraryA` peut s'être bloqué ou avoir pris trop de temps.
   - **Blocage :** Un mécanisme de sécurité a peut-être intercepté et bloqué l'exécution de `LoadLibraryA` indéfiniment.
- **Solution :** Peut indiquer que la DLL met trop de temps à se charger ou que quelque chose l'en empêche. La vérification des journaux système ou de SA-MP/OMP (s'ils existent) peut aider.

#### L'Injection de la DLL a Échoué ou a Retourné une Erreur

- **Message d'Erreur :** `"DLL injection failed or returned an error. The LoadLibrary call may have failed in the target process."`
- **Pourquoi :** Le thread distant s'est terminé, mais le code de sortie de `LoadLibraryA` a indiqué un échec (généralement `0` ou `NULL`).
   - **DLL Inexistante/Corrompue :** Malgré la validation initiale, la DLL a peut-être été déplacée ou corrompue entre la validation et l'injection.
   - **Dépendances de la DLL Manquantes :** `samp.dll` ou `omp-client.dll` peuvent dépendre d'autres DLL qui ne sont pas présentes dans le répertoire du jeu ou dans le PATH du système.
   - **Erreur Interne de la DLL :** La DLL elle-même peut avoir une erreur interne qui l'empêche de se charger correctement.
- **Solution :** Vérifiez l'intégrité de `samp.dll`/`omp-client.dll`. Assurez-vous que toutes les dépendances de la DLL sont présentes.

### Erreur lors de la Reprise du Thread du Jeu

C'est la dernière erreur possible dans le cycle d'injection.

- **Message d'Erreur (Exemple) :** `"Failed to resume the game process thread: Invalid handle."`
- **Pourquoi :** L'API `ResumeThread` a échoué à redémarrer le thread principal de `gta_sa.exe`.
   - **Handle Invalide :** Le handle du thread a peut-être été invalidé pour une raison quelconque.
   - **Problème de Permission :** L'application peut ne pas avoir la permission de modifier l'état du thread.
- **Solution :** Essayez d'exécuter l'application en tant qu'administrateur. Si le problème persiste, cela peut indiquer un problème plus profond de stabilité du système ou du processus du jeu.

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