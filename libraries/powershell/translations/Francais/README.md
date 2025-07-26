# SA-MP Injector PowerShell

![License](https://img.shields.io/badge/License-MIT-yellow.svg?style=flat)
![PowerShell](https://img.shields.io/badge/PowerShell-5.1%2B-blue.svg?style=flat&logo=powershell)
![Platform](https://img.shields.io/badge/Platform-Windows-0078D6.svg?style=flat&logo=windows)
[![SA-MP | OMP](https://img.shields.io/badge/Support-SA--MP%20%7C%20OMP-yellow)](https://github.com/spc-samp/samp-injector)
![Code Quality](https://img.shields.io/badge/Code%20Quality-High-brightgreen.svg?style=flat)

Le **SA-MP Injector PowerShell** est plus qu'un simple script d'**injection de DLL**. Il représente une **bibliothèque de fonctions et de classes PowerShell** développée pour offrir une solution robuste et complète pour le lancement programmatique du jeu **Grand Theft Auto: San Andreas** (**GTA:SA**) en conjonction avec ses clients multijoueurs, spécifiquement **SA-MP (San Andreas Multiplayer)** et **OMP (Open Multiplayer)**. Son objectif principal est de simplifier le processus de lancement du jeu, en éliminant la complexité inhérente à la manipulation directe des processus du système d'exploitation et à la transmission d'arguments en ligne de commande.

Développée pour offrir une flexibilité maximale et une intégration facile, cette bibliothèque permet aux développeurs de l'incorporer directement dans leurs **projets et scripts PowerShell**. Elle orchestre non seulement l'**injection fondamentale des DLLs** du client multijoueur (`samp.dll` ou `omp-client.dll`), mais gère également intelligemment tous les paramètres de connexion essentiels (**pseudonyme**, **adresse IP**, **port** et **mot de passe**), simulant un lancement natif via les ressources intrinsèques de l'**API Windows**, qui sont accédées directement via **PowerShell**.

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

## Sommaire

- [SA-MP Injector PowerShell](#sa-mp-injector-powershell)
  - [Langues](#langues)
  - [Sommaire](#sommaire)
  - [Concepts Fondamentaux et Motivation](#concepts-fondamentaux-et-motivation)
    - [Pourquoi Injecter des DLLs?](#pourquoi-injecter-des-dlls)
    - [SA-MP et OMP: Distinctions et Similitudes](#sa-mp-et-omp-distinctions-et-similitudes)
    - [Injection de DLLs en PowerShell: Une Approche Directe avec WinAPI](#injection-de-dlls-en-powershell-une-approche-directe-avec-winapi)
  - [Architecture Interne de la Bibliothèque: Une Plongée Approfondie](#architecture-interne-de-la-bibliothèque-une-plongée-approfondie)
    - [`Constants.ps1`](#constantsps1)
    - [`CustomTypes.ps1`](#customtypesps1)
    - [`StringUtils.ps1`](#stringutilsps1)
    - [`ErrorUtils.ps1`](#errorutilsps1)
    - [`Process.ps1`](#processps1)
    - [`InjectorCore.ps1`](#injectorcoreps1)
    - [`Injector.ps1`](#injectorps1)
    - [`Cleanup.ps1`](#cleanupps1)
  - [Exemples Complets d'Utilisation](#exemples-complets-dutilisation)
    - [1. Préparation de l'Environnement de Développement](#1-préparation-de-lenvironnement-de-développement)
    - [2. Scénario de Base: Connexion à un Serveur SA-MP](#2-scénario-de-base-connexion-à-un-serveur-sa-mp)
    - [3. Scénario Avancé: Connexion à un Serveur OMP](#3-scénario-avancé-connexion-à-un-serveur-omp)
    - [4. Exécution à partir d'un Script Parent](#4-exécution-à-partir-dun-script-parent)
  - [Gestion des Erreurs Courantes et Messages](#gestion-des-erreurs-courantes-et-messages)
    - [1. Type d'Injection Invalide](#1-type-dinjection-invalide)
    - [2. Port du Serveur Invalide (Format ou Plage)](#2-port-du-serveur-invalide-format-ou-plage)
      - [2.1. Format de Port Non Numérique](#21-format-de-port-non-numérique)
      - [2.2. Port en Dehors de la Plage Valide](#22-port-en-dehors-de-la-plage-valide)
    - [3. Pseudonyme Invalide (Vide ou Trop Long)](#3-pseudonyme-invalide-vide-ou-trop-long)
      - [3.1. Pseudonyme Vide](#31-pseudonyme-vide)
      - [3.2. Pseudonyme Trop Long](#32-pseudonyme-trop-long)
    - [4. Fichiers du Jeu ou DLL Non Trouvés](#4-fichiers-du-jeu-ou-dll-non-trouvés)
      - [4.1. Exécutable du Jeu (`gta_sa.exe`) Non Trouvé](#41-exécutable-du-jeu-gta_saexe-non-trouvé)
      - [4.2. Bibliothèque SA-MP (`samp.dll`) Non Trouvée](#42-bibliothèque-sa-mp-sampdll-non-trouvée)
      - [4.3. Bibliothèque OMP (`omp-client.dll`) Non Trouvée (uniquement pour l'injection OMP)](#43-bibliothèque-omp-omp-clientdll-non-trouvée-uniquement-pour-linjection-omp)
    - [5. Échec de la Création du Processus du Jeu](#5-échec-de-la-création-du-processus-du-jeu)
    - [6. Échec de l'Allocation de Mémoire dans le Processus Cible](#6-échec-de-lallocation-de-mémoire-dans-le-processus-cible)
    - [7. Échec de l'Écriture du Chemin de la DLL dans la Mémoire du Processus](#7-échec-de-lécriture-du-chemin-de-la-dll-dans-la-mémoire-du-processus)
    - [8. Échec de la Recherche des Fonctions Essentielles du Système](#8-échec-de-la-recherche-des-fonctions-essentielles-du-système)
      - [8.1. `kernel32.dll` Non Trouvé](#81-kernel32dll-non-trouvé)
      - [8.2. `LoadLibraryA` Non Trouvé](#82-loadlibrarya-non-trouvé)
    - [9. Échec de la Création d'un Thread Distant pour l'Injection](#9-échec-de-la-création-dun-thread-distant-pour-linjection)
    - [10. Délai d'Attente ou Échec de la Finalisation de l'Injection](#10-délai-dattente-ou-échec-de-la-finalisation-de-linjection)
    - [11. Échec de la Reprise du Thread du Processus du Jeu](#11-échec-de-la-reprise-du-thread-du-processus-du-jeu)
  - [Licence](#licence)
    - [Conditions Générales d'Utilisation](#conditions-générales-dutilisation)
      - [1. Autorisations Accordées](#1-autorisations-accordées)
      - [2. Conditions Obligatoires](#2-conditions-obligatoires)
      - [3. Droits d'Auteur](#3-droits-dauteur)
      - [4. Exclusion de Garantie et Limitation de Responsabilité](#4-exclusion-de-garantie-et-limitation-de-responsabilité)

## Concepts Fondamentaux et Motivation

### Pourquoi Injecter des DLLs?

> [!NOTE]
> L'**injection de DLL (Dynamic Link Library)** est une méthode utilisée dans les systèmes d'exploitation **Microsoft Windows** qui permet l'exécution de code dans l'espace mémoire d'un autre processus en cours d'exécution. C'est une technique puissante avec diverses applications légitimes, allant du débogage et de la surveillance de programmes à la modification du comportement d'applications pour étendre leurs fonctionnalités.

Dans le contexte de jeux comme **GTA San Andreas**, qui n'ont pas été développés à l'origine avec une fonctionnalité multijoueur intégrée, l'**injection de DLLs** est la base de l'existence de clients multijoueurs comme **SA-MP** et **OMP**. Ces clients sont implémentés sous forme de **DLLs** qui, une fois injectées dans le processus de `gta_sa.exe`, prennent le contrôle, interceptent des fonctions du jeu et établissent la communication avec des serveurs multijoueurs.

Au lieu de dépendre d'un lanceur externe ou de la modification directe de l'exécutable du jeu, l'**injection de DLL** permet un démarrage plus flexible et programmable, particulièrement utile dans les environnements où l'on souhaite automatiser le processus de connexion à des serveurs spécifiques avec des configurations prédéfinies.

### SA-MP et OMP: Distinctions et Similitudes

**SA-MP** et **OMP** sont les deux principales plateformes multijoueurs pour **GTA San Andreas**. Tous deux fonctionnent comme des modifications du jeu de base, le transformant en un environnement en ligne massivement multijoueur.

- **SA-MP (San Andreas Multiplayer)**: Le client original et le plus consolidé, largement utilisé depuis de nombreuses années. Son architecture nécessite la `samp.dll` pour fonctionner.
- **OMP (Open Multiplayer)**: Un projet open source, souvent considéré comme un successeur ou une alternative plus moderne à **SA-MP**, offrant des améliorations de performance, de stabilité et des fonctionnalités supplémentaires. Il nécessite la `omp-client.dll`.

Bien qu'ils fonctionnent de manière similaire (**en injectant une DLL** dans le processus de **GTA:SA**), la bibliothèque **SA-MP Injector PowerShell** a été soigneusement développée pour prendre en charge **les deux DLLs**, reconnaissant leurs distinctions de noms de fichiers et permettant au développeur de choisir le client multijoueur souhaité via un paramètre de configuration. Cela garantit que la bibliothèque peut être utilisée avec la vaste gamme de serveurs et de projets basés sur l'une ou l'autre plateforme.

### Injection de DLLs en PowerShell: Une Approche Directe avec WinAPI

PowerShell est un langage de script puissant pour l'automatisation sous Windows, mais la manipulation de processus et l'injection de DLLs à un niveau aussi bas du système n'est pas sa fonction principale. Pour atteindre cet objectif, la bibliothèque **SA-MP Injector PowerShell** utilise intensivement la commande `Add-Type` pour invoquer directement les fonctions de l'**API Windows (WinAPI)**.

`Add-Type` permet de définir et de compiler du code C# (ou d'autres langages .NET) à la volée dans l'environnement PowerShell. Ce code C# agit comme un "pont" vers les fonctions natives de la WinAPI (`DllImport`), permettant des opérations telles que:

- **`CreateProcessA`**: Pour démarrer le processus de GTA:SA.
- **`VirtualAllocEx`**: Pour allouer de la mémoire dans le processus distant.
- **`WriteProcessMemory`**: Pour copier le chemin de la DLL dans la mémoire allouée.
- **`GetModuleHandleA` et `GetProcAddress`**: Pour obtenir l'adresse de la fonction `LoadLibraryA` dans `kernel32.dll`.
- **`CreateRemoteThread`**: Pour créer un thread dans le processus distant qui exécute `LoadLibraryA`, chargeant ainsi efficacement la DLL.
- **`WaitForSingleObject` et `GetExitCodeThread`**: Pour surveiller le succès de l'injection.
- **`ResumeThread`**: Pour réactiver le processus du jeu après l'injection.
- **`CloseHandle`**: Pour fermer les handles de ressources système et éviter les fuites.
- **`MessageBoxW`**: Pour afficher des messages d'erreur informatifs à l'utilisateur.

Cette approche directe avec la WinAPI permet à PowerShell d'effectuer les mêmes opérations de bas niveau qu'une application compilée en **C++** le ferait, avec la commodité d'un environnement de script.

## Architecture Interne de la Bibliothèque: Une Plongée Approfondie

La bibliothèque **SA-MP Injector PowerShell** adopte une approche modulaire pour gérer la complexité du processus d'injection. Chaque script est un module spécialisé, responsable d'une partie spécifique de la fonctionnalité globale, favorisant la clarté du code, la maintenabilité et l'extensibilité.

### `Constants.ps1`

Ce script est la base de toutes les configurations fixes de la bibliothèque. Il définit une table de hachage globale (`$global:CONSTANTS`) qui stocke toutes les littérales et les valeurs numériques utilisées, telles que les limites de port, les noms de fichiers DLL, les références aux API système et les drapeaux pour les opérations comme la création de processus et l'allocation de mémoire.

```powershell
$global:CONSTANTS = @{
    # Limites de validation du port
    MIN_PORT = 1
    MAX_PORT = 65535
    
    # Contraintes du pseudonyme
    MAX_NICKNAME_LENGTH = 23
    
    # Noms de fichiers requis
    SAMP_DLL_NAME = "samp.dll"
    OMP_DLL_NAME = "omp-client.dll"
    GAME_EXE_NAME = "gta_sa.exe"
    
    # Références API système
    KERNEL32_DLL = "kernel32.dll"
    USER32_DLL = "user32.dll" # Utilisé pour MessageBoxW
    LOAD_LIBRARY_FUNC = "LoadLibraryA"
    
    # Préfixes des arguments de ligne de commande
    CMD_ARG_CONFIG = "-c"
    CMD_ARG_NICKNAME = "-n"
    CMD_ARG_HOST = "-h"
    CMD_ARG_PORT = "-p"
    CMD_ARG_PASSWORD = "-z"
    
    # Identifiants de type d'injection
    INJECT_TYPE_SAMP = "samp"
    INJECT_TYPE_OMP = "omp"
    
    # Titres des boîtes de dialogue d'erreur
    ERROR_TITLE_SAMP = "SA-MP Injector Error - SPC"
    ERROR_TITLE_OMP = "OMP Injector Error - SPC"
    
    # Drapeaux de création de processus (CREATE_SUSPENDED | DETACHED_PROCESS)
    # 0x00000104 = CREATE_SUSPENDED (0x4) + DETACHED_PROCESS (0x100)
    PROCESS_CREATION_FLAGS = 0x00000104
    
    # Délais d'attente des opérations
    DLL_INJECTION_TIMEOUT_MS = 10000 # 10 secondes
    
    # Constantes d'allocation de mémoire
    # 0x00003000 = MEM_COMMIT (0x1000) + MEM_RESERVE (0x2000)
    MEMORY_ALLOCATION_TYPE = 0x00003000
    # 0x00000004 = PAGE_READWRITE
    MEMORY_PROTECTION = 0x00000004
    # 0x00008000 = MEM_RELEASE
    MEMORY_FREE_TYPE = 0x00008000
    
    # Résultats d'attente d'objet (API Windows)
    WAIT_OBJECT_0 = 0x00000000
    WAIT_TIMEOUT = 0x00000102
    WAIT_FAILED = 0xFFFFFFFF
    
    # Indicateur d'erreur de reprise de thread (API Windows)
    THREAD_RESUME_ERROR = 0xFFFFFFFF # ResumeThread retourne -1 en cas d'échec
    
    # Constantes MessageBox (API Windows)
    MB_OK = 0x00000000
    MB_ICONERROR = 0x00000010
    MB_TOPMOST = 0x00040000
}
```

> [!TIP]
> L'utilisation d'une table de hachage globale pour les constantes est une pratique courante dans les scripts PowerShell. Elle centralise les configurations et évite les "nombres magiques" et les chaînes de caractères répétées, rendant le code plus lisible et facile à maintenir. Les valeurs des drapeaux (`0x...`) correspondent aux valeurs décimales des constantes définies dans l'API Windows.

### `CustomTypes.ps1`

Ce script est fondamental pour l'interaction avec l'API Windows. Il définit des types C# à la volée en utilisant `Add-Type`, incluant:

- **`Inject_Type` enum**: Pour catégoriser le type d'injection (SAMP ou OMP), améliorant la sécurité des types.
- **`WinAPI` class**: Une classe statique qui importe et expose les fonctions de l'API Windows nécessaires pour l'injection. Chaque méthode de cette classe correspond à une fonction de l'API (`DllImport`), avec la signature et le jeu de caractères (`CharSet`) corrects.
- **`Startup_Info` struct et `Process_Information` struct**: Structures de données C# qui répliquent les structures `STARTUPINFO` et `PROCESS_INFORMATION` utilisées par la fonction `CreateProcessA` de l'API Windows.
- **`Process_Info` class**: Une classe simple en C# qui agit comme un conteneur pour les handles du processus et du thread retournés après la création réussie d'un processus, facilitant le transport et la gestion de ces handles dans l'environnement PowerShell.

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
        using System.Text; // Requis pour Marshal.GetLastWin32Error
        
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
            
            // Structure C# pour STARTUPINFO
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
            
            // Structure C# pour PROCESS_INFORMATION
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
        
        // Classe auxiliaire pour transporter les handles de processus et de thread
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
> L'injection de DLLs 32 bits (comme `samp.dll` et `omp-client.dll`) dans un processus 32 bits (`gta_sa.exe`) **exige que l'environnement PowerShell soit également en 32 bits**. Le **SA-MP Injector PowerShell** gère cela automatiquement en se redémarrant dans un shell PowerShell x86 s'il détecte qu'il est exécuté dans un environnement x64. C'est crucial pour garantir la compatibilité de la taille des pointeurs et le bon fonctionnement de l'injection.
>
> La directive `if (-not ([System.Management.Automation.PSTypeName]'TypeName').Type)` garantit que les types C# ne sont ajoutés à l'environnement PowerShell qu'une seule fois, évitant ainsi les erreurs de redéfinition si le script est exécuté plusieurs fois dans la même session.

### `StringUtils.ps1`

Ce module fournit une fonction utilitaire essentielle pour la manipulation de chaînes de caractères, spécifiquement pour gérer les encodages de caractères nécessaires lors de l'interaction avec l'API Windows héritée (fonctions "A" de char*).

```powershell
function Convert_Wide_To_Local_8Bit {
    param([Parameter(Mandatory = $false)] [AllowEmptyString()] [string]$wide_string)
    
    if ([string]::IsNullOrEmpty($wide_string)) {
        return [string]::Empty
    }

    try {
        # Obtient la page de codes ANSI locale du système
        $ansi_code_page = [System.Globalization.CultureInfo]::CurrentCulture.TextInfo.ANSICodePage
        $encoding = [System.Text.Encoding]::GetEncoding($ansi_code_page)
        
        # Convertit la chaîne Unicode (wide) en octets dans l'encodage ANSI local
        $bytes = $encoding.GetBytes($wide_string)

        # Convertit les octets en une chaîne en utilisant le même encodage ANSI
        # Cela garantit que la chaîne est compatible avec les API qui attendent un encodage 8 bits (ANSI)
        return $encoding.GetString($bytes)
    }
    catch {
        # En cas d'erreur de conversion (par ex., des caractères qui ne peuvent pas être mappés),
        # retourne la chaîne originale comme solution de repli, bien que cela puisse causer des problèmes
        # si elle contient des caractères non pris en charge par les API ANSI.
        return $wide_string
    }
}
```

> [!IMPORTANT]
> La fonction `Convert_Wide_To_Local_8Bit` est cruciale car de nombreuses fonctions de l'API Windows avec le suffixe "A" (`CreateProcessA`, `LoadLibraryA`, `GetModuleHandleA`, `GetProcAddress`) attendent des chaînes encodées en ANSI (8 bits), qui dépendent de la page de codes du système local. Par défaut, les chaînes dans PowerShell sont Unicode. Cette fonction effectue la conversion nécessaire. Si le nom de fichier ou un argument de ligne de commande contient des caractères en dehors de la page de codes ANSI du système, la conversion peut entraîner des caractères incorrects ou une perte de données. Pour ce projet, qui vise à interagir avec des programmes anciens, cette approche ANSI est généralement suffisante et nécessaire.

### `ErrorUtils.ps1`

Ce module est responsable de fournir un retour clair à l'utilisateur en cas d'échec. Il centralise la logique d'obtention des messages d'erreur du système et l'affichage des boîtes de dialogue standard de Windows.

```powershell
function Get_System_Error_Message {
    param([Parameter(Mandatory = $true)][int]$error_code)
    
    try {
        # Utilise Win32Exception pour obtenir le message d'erreur formaté par le système
        $exception = New-Object System.ComponentModel.Win32Exception($error_code)
        
        return $exception.Message
    }
    catch {
        # Solution de repli pour un message d'erreur inconnu
        return "Unknown error (Code: $error_code)"
    }
}

function Show_Error {
    param([Parameter(Mandatory = $true)][string]$message, [Parameter(Mandatory = $true)][Inject_Type]$inject_type)
    
    # Détermine le titre de la boîte de dialogue en fonction du type d'injection
    $title = if ($inject_type -eq [Inject_Type]::SAMP) {
        $global:CONSTANTS.ERROR_TITLE_SAMP
    }
    else {
        $global:CONSTANTS.ERROR_TITLE_OMP
    }
    
    try {
        # Combine les drapeaux pour MessageBoxW (OK, Icône d'Erreur, Toujours au premier plan)
        $message_box_flags = $global:CONSTANTS.MB_OK -bor $global:CONSTANTS.MB_ICONERROR -bor $global:CONSTANTS.MB_TOPMOST
        
        # Appelle la fonction MessageBoxW importée via Add-Type
        [void][WinAPI]::MessageBoxW([System.IntPtr]::Zero, $message, $title, $message_box_flags)
    }
    catch {
        # En cas d'échec d'affichage de la MessageBox (par ex., dans des environnements sans interface utilisateur), écrit dans la console
        Write-Host "[$title] $message" -ForegroundColor Red
    }
}
```

> [!NOTE]
> `Get_System_Error_Message` utilise `System.ComponentModel.Win32Exception` de .NET pour convertir un code d'erreur numérique de l'API Windows (`GetLastError()`) en une description textuelle lisible par l'utilisateur, qui peut être localisée dans la langue du système d'exploitation.
>
> `Show_Error` utilise la fonction `MessageBoxW` importée de `user32.dll` via `Add-Type` (`CustomTypes.ps1`) pour afficher une boîte de dialogue informative. Les drapeaux comme `MB_OK` et `MB_ICONERROR` sont importés des constantes de la WinAPI.

### `Process.ps1`

C'est le module principal responsable de l'interaction directe avec les API de bas niveau de Windows pour manipuler les processus. Il encapsule les opérations cruciales de création de processus et d'injection de DLL, en gérant les handles, la mémoire et les threads.

```powershell
class Process {
    # Libère les handles de processus et de thread, prévenant les fuites de ressources
    [void] Close_Process_Info([Process_Info]$process_info) {
        if ($null -ne $process_info) {
            # Ferme le handle du processus s'il est valide
            if ($process_info.ProcessHandle -ne [System.IntPtr]::Zero -and $process_info.ProcessHandle -ne [System.IntPtr]::new(-1)) {
                [void][WinAPI]::CloseHandle($process_info.ProcessHandle)
                $process_info.ProcessHandle = [System.IntPtr]::Zero # Marque comme fermé
            }

            # Ferme le handle du thread s'il est valide
            if ($process_info.ThreadHandle -ne [System.IntPtr]::Zero -and $process_info.ThreadHandle -ne [System.IntPtr]::new(-1)) {
                [void][WinAPI]::CloseHandle($process_info.ThreadHandle)
                $process_info.ThreadHandle = [System.IntPtr]::Zero # Marque comme fermé
            }
        }
    }

    # Crée le processus du jeu GTA:SA en état suspendu
    [Process_Info] Create_Game_Process([string]$game_path, [string]$command_args, [string]$working_dir) {
        $startup_info = New-Object WinAPI+Startup_Info
        # Définit la taille de la structure, cruciale pour les API Windows
        $startup_info.cb = [System.Runtime.InteropServices.Marshal]::SizeOf($startup_info)
        
        $process_information = New-Object WinAPI+Process_Information
        
        $command_line_bytes = $null

        if (-not [string]::IsNullOrEmpty($command_args)) {
            # Convertit les arguments de la ligne de commande en un tableau d'octets ANSI avec un terminateur nul
            $command_line_bytes = [System.Text.Encoding]::Default.GetBytes($command_args + "`0")
        }
        
        # Définit le répertoire de travail, null si vide
        $current_directory = if ([string]::IsNullOrEmpty($working_dir)) {
            $null
        }
        else {
            $working_dir
        }
        
        # Appelle la fonction CreateProcessA de l'API Windows
        $success = [WinAPI]::CreateProcessA($game_path, $command_line_bytes, [System.IntPtr]::Zero, [System.IntPtr]::Zero, $false, $global:CONSTANTS.PROCESS_CREATION_FLAGS, 
            [System.IntPtr]::Zero, $current_directory, [ref]$startup_info, [ref]$process_information)
        
        if (-not $success) {
            # En cas d'échec, obtient la dernière erreur du système et l'affiche
            $error_code = [System.Runtime.InteropServices.Marshal]::GetLastWin32Error()
            $error_message = Get_System_Error_Message $error_code
            Show_Error "Failed to create game process. Ensure 'gta_sa.exe' is not running and you have sufficient permissions to execute the file. System Error: $error_message" ([Inject_Type]::SAMP)

            return $null # Retourne null en cas d'échec
        }
        
        # Retourne un objet Process_Info contenant les handles du processus et du thread
        $result = New-Object Process_Info
        $result.ProcessHandle = $process_information.hProcess
        $result.ThreadHandle = $process_information.hThread
        
        return $result
    }
    
    # Injecte une DLL dans le processus distant
    [bool] Inject_DLL([IntPtr]$process_handle, [string]$dll_path, [ref]$error_message) {
        if ($process_handle -eq [System.IntPtr]::Zero) {
            $error_message.Value = "Invalid process handle provided for DLL injection."

            return $false
        }
        
        if ([string]::IsNullOrEmpty($dll_path)) {
            $error_message.Value = "DLL path cannot be empty."

            return $false
        }
        
        # Convertit le chemin de la DLL en octets ASCII (ANSI 8 bits) avec un terminateur nul
        $dll_path_bytes = [System.Text.Encoding]::ASCII.GetBytes($dll_path + "`0")
        $dll_path_size = $dll_path_bytes.Length
        
        # Alloue de la mémoire dans le processus distant pour le chemin de la DLL
        $remote_memory = [WinAPI]::VirtualAllocEx($process_handle, [System.IntPtr]::Zero, $dll_path_size, $global:CONSTANTS.MEMORY_ALLOCATION_TYPE, $global:CONSTANTS.MEMORY_PROTECTION)
        
        if ($remote_memory -eq [System.IntPtr]::Zero) {
            $error_code = [System.Runtime.InteropServices.Marshal]::GetLastWin32Error()
            $error_message.Value = "Failed to allocate memory in the target process. This might be due to insufficient permissions or process protection mechanisms. System Error: $(Get_System_Error_Message $error_code)"

            return $false
        }
        
        # Utilise un bloc try/finally pour garantir que la mémoire distante est libérée
        try {
            $bytes_written = [System.IntPtr]::Zero
            # Écrit le chemin de la DLL dans la mémoire distante
            $write_success = [WinAPI]::WriteProcessMemory($process_handle, $remote_memory, $dll_path_bytes, $dll_path_size, [ref]$bytes_written)
            
            if (-not $write_success) {
                $error_code = [System.Runtime.InteropServices.Marshal]::GetLastWin32Error()
                $error_message.Value = "Failed to write DLL path to the target process memory. Verify process permissions and ensure the DLL path is accessible. System Error: $(Get_System_Error_Message $error_code)"
                
                return $false
            }
            
            # Obtient le handle pour kernel32.dll (qui est chargé dans tous les processus)
            $kernel32_handle = [WinAPI]::GetModuleHandleA($global:CONSTANTS.KERNEL32_DLL)

            if ($kernel32_handle -eq [System.IntPtr]::Zero) {
                $error_code = [System.Runtime.InteropServices.Marshal]::GetLastWin32Error()
                $error_message.Value = "Failed to obtain a handle to kernel32.dll. This is an essential system library and this error indicates a severe system issue. System Error: $(Get_System_Error_Message $error_code)"
                
                return $false
            }
            
            # Obtient l'adresse de la fonction LoadLibraryA dans kernel32.dll.
            # Cette adresse est cohérente entre les processus sur le même OS.
            $load_library_address = [WinAPI]::GetProcAddress($kernel32_handle, $global:CONSTANTS.LOAD_LIBRARY_FUNC)

            if ($load_library_address -eq [System.IntPtr]::Zero) {
                $error_code = [System.Runtime.InteropServices.Marshal]::GetLastWin32Error()
                $error_message.Value = "Failed to find the address of the LoadLibraryA function in kernel32.dll. This is critical for injecting the DLL. System Error: $(Get_System_Error_Message $error_code)"
                
                return $false
            }
            
            $thread_id = [System.IntPtr]::Zero
            # Crée un thread distant dans le processus cible pour exécuter LoadLibraryA
            $remote_thread_handle = [WinAPI]::CreateRemoteThread($process_handle, [System.IntPtr]::Zero, 0, $load_library_address, $remote_memory, 0, [ref]$thread_id)
            
            if ($remote_thread_handle -eq [System.IntPtr]::Zero) {
                $error_code = [System.Runtime.InteropServices.Marshal]::GetLastWin32Error()
                $error_message.Value = "Failed to create a remote thread in the target process to execute the DLL injection. This could be due to security restrictions or process state. System Error: $(Get_System_Error_Message $error_code)"
                
                return $false
            }
            
            # Utilise un bloc try/finally pour garantir que le handle du thread distant est fermé
            try {
                # Attend que le thread distant (injection de DLL) se termine ou atteigne un délai d'attente
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
                # Obtient le code de sortie du thread distant. Pour LoadLibraryA, 0 signifie échec.
                $get_exit_code_success = [WinAPI]::GetExitCodeThread($remote_thread_handle, [ref]$exit_code)
                
                if (-not $get_exit_code_success -or $exit_code -eq 0) {
                    $error_code = [System.Runtime.InteropServices.Marshal]::GetLastWin32Error()
                    $error_message.Value = "DLL injection failed or returned an error. The LoadLibrary call may have failed in the target process. Exit Code: $exit_code. System Error: $(Get_System_Error_Message $error_code)"

                    return $false
                }
                
                return $true # Injection réussie
            }
            finally {
                # S'assure que le handle du thread distant est fermé
                [void][WinAPI]::CloseHandle($remote_thread_handle)
            }
        }
        finally {
            # S'assure que la mémoire allouée à distance est libérée
            # 0 pour dwSize dans MEM_RELEASE libère toute la région allouée par VirtualAllocEx
            [void][WinAPI]::VirtualFreeEx($process_handle, $remote_memory, 0, $global:CONSTANTS.MEMORY_FREE_TYPE)
        }
    }
}
```

> [!NOTE]
> La classe `Process` utilise `[System.IntPtr]` pour représenter les handles de Windows. Il est important de noter l'utilisation extensive de `try/finally` pour garantir que les handles (`ProcessHandle`, `ThreadHandle`, `remote_memory`, `remote_thread_handle`) sont fermés et que la mémoire est libérée correctement, même en cas d'erreur. C'est la manière PowerShell d'implémenter le principe **RAII** (Resource Acquisition Is Initialization), bien que moins intégrée dans la syntaxe du langage.

### `InjectorCore.ps1`

C'est la classe orchestratrice qui réunit toutes les fonctionnalités des modules précédents. Elle coordonne la validation, la construction des arguments de ligne de commande, la création du processus et les appels d'injection de DLL.

```powershell
class Injector_Core {
    # Fonction principale qui orchestre l'initialisation et l'injection du jeu
    [bool] Initialize_Game([Inject_Type]$inject_type, [string]$folder, [string]$nickname, [string]$ip, [string]$port, [string]$password) {
        # Construit les chemins complets vers les fichiers essentiels
        $game_path = Join-Path -Path $folder -ChildPath $global:CONSTANTS.GAME_EXE_NAME
        $samp_dll_path = Join-Path -Path $folder -ChildPath $global:CONSTANTS.SAMP_DLL_NAME
        $omp_dll_path = Join-Path -Path $folder -ChildPath $global:CONSTANTS.OMP_DLL_NAME
        
        $validation_error = [string]::Empty # Variable pour capturer les messages d'erreur de validation
        
        # 1. Validation des Fichiers
        if (-not (Validate_Files $game_path $samp_dll_path $omp_dll_path $inject_type)) {
            # L'erreur a déjà été affichée par la fonction de validation
            return $false
        }

        # 2. Validation du Port
        if (-not (Validate_Port $port ([ref]$validation_error))) {
            Show_Error $validation_error $inject_type
            return $false
        }
        
        # 3. Validation du Pseudonyme
        if (-not (Validate_Nickname $nickname ([ref]$validation_error))) {
            Show_Error $validation_error $inject_type
            return $false
        }
        
        # 4. Conversion des Chaînes en Encodage ANSI/8-bit (nécessaire pour les API héritées)
        $converted_nickname = Convert_Wide_To_Local_8Bit $nickname
        $converted_ip = Convert_Wide_To_Local_8Bit $ip
        $converted_port = Convert_Wide_To_Local_8Bit $port
        $converted_password = Convert_Wide_To_Local_8Bit $password
        $converted_game_path = Convert_Wide_To_Local_8Bit $game_path
        $converted_folder = Convert_Wide_To_Local_8Bit $folder
        $converted_samp_dll_path = Convert_Wide_To_Local_8Bit $samp_dll_path
        $converted_omp_dll_path = Convert_Wide_To_Local_8Bit $omp_dll_path
        
        # 5. Construction des Arguments de la Ligne de Commande
        $command_arguments = $this.Build_Command_Args($converted_nickname, $converted_ip, $converted_port, $converted_password)
        
        $process_manager = New-Object Process # Instancie la classe Process
        $process_info = $null # Variable pour stocker les informations du processus créé
        
        # Utilise un bloc try/finally pour garantir que les handles du processus sont fermés
        try {
            # 6. Création du Processus du Jeu (Suspendu)
            $process_info = $process_manager.Create_Game_Process($converted_game_path, $command_arguments, $converted_folder)
            
            if ($null -eq $process_info) {
                # L'erreur a déjà été affichée par la fonction de création de processus
                return $false
            }

            $injection_error = [string]::Empty # Variable pour capturer les messages d'erreur d'injection
            
            # 7. Injection de la samp.dll
            if (-not $process_manager.Inject_DLL($process_info.ProcessHandle, $converted_samp_dll_path, ([ref]$injection_error))) {
                Show_Error "Failed to inject samp.dll: $injection_error" $inject_type
                return $false
            }
            
            # 8. Injection conditionnelle de la omp-client.dll (uniquement si le type d'injection est OMP)
            if ($inject_type -eq [Inject_Type]::OMP) {
                if (-not $process_manager.Inject_DLL($process_info.ProcessHandle, $converted_omp_dll_path, ([ref]$injection_error))) {
                    Show_Error "Failed to inject omp-client.dll: $injection_error" $inject_type
                    return $false
                }
            }
            
            # 9. Reprise du Processus du Jeu
            # Le processus a été créé en état suspendu pour permettre l'injection.
            # Maintenant que les DLLs ont été injectées, il peut être repris.
            $resume_result = [WinAPI]::ResumeThread($process_info.ThreadHandle)

            if ($resume_result -eq $global:CONSTANTS.THREAD_RESUME_ERROR) {
                $error_code = [System.Runtime.InteropServices.Marshal]::GetLastWin32Error()
                $error_message = Get_System_Error_Message $error_code
                Show_Error "Failed to resume the game process thread: $error_message" $inject_type

                return $false
            }
            
            return $true # Succès à toutes les étapes!
        }
        finally {
            # S'assure que les handles du processus sont fermés à la fin,
            # indépendamment du succès ou de l'échec.
            if ($null -ne $process_info) {
                $process_manager.Close_Process_Info($process_info)
            }
        }
    }
    
    # Construit la chaîne d'arguments de la ligne de commande pour l'exécutable du jeu
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
> Pour **OMP**, l'injection implique la `omp-client.dll` *en plus* de la `samp.dll`. Ceci est conforme à la manière dont **OMP** fonctionne généralement, car il peut utiliser la `samp.dll` comme base et étendre les fonctionnalités avec `omp-client.dll`. Il est crucial que **les deux DLLs** soient présentes et fonctionnelles dans le répertoire du jeu pour que l'injection OMP réussisse. Si l'une échoue, le jeu risque de ne pas démarrer correctement ou le client multijoueur pourrait ne pas se charger.
>
> Notez que, comme PowerShell ne possède pas de `std::optional` ou de garantie **RAII** native de la même manière que C++, le code utilise un bloc `try/finally` explicite dans la fonction `Initialize_Game` pour garantir que `Close_Process_Info` est appelé et que les handles sont libérés, même si une erreur se produit. C'est une bonne pratique de nettoyage des ressources en PowerShell.

### `Injector.ps1`

C'est le script d'entrée principal de la bibliothèque. Il gère le chargement des autres modules, la validation de l'environnement PowerShell (en vérifiant s'il est x86 pour la compatibilité de l'injection) et l'initialisation de la classe `Injector_Core`. C'est le script que l'utilisateur final exécutera.

```powershell
param([Parameter(Mandatory = $true, Position = 0)][ValidateNotNullOrEmpty()][string]$inject_type,
    [Parameter(Mandatory = $true, Position = 1)][ValidateNotNullOrEmpty()][string]$folder,
    [Parameter(Mandatory = $true, Position = 2)][ValidateNotNullOrEmpty()][string]$nickname,
    [Parameter(Mandatory = $true, Position = 3)][ValidateNotNullOrEmpty()][string]$ip,
    [Parameter(Mandatory = $true, Position = 4)][ValidateNotNullOrEmpty()][string]$port,
    [Parameter(Position = 5)][AllowEmptyString()][string]$password = "",
    [switch]$restarted_x86) # Indicateur interne pour signaler que le script a déjà été redémarré en x86

$ErrorActionPreference = 'Stop' # S'assure que les erreurs non-terminating se comportent comme des erreurs terminating
# Cela permet aux blocs catch de capturer plus d'erreurs et empêche le script de continuer de manière inattendue.

# Obtient le chemin complet du script actuel, essentiel pour charger les modules auxiliaires
$script_path = $MyInvocation.MyCommand.Path

if ([string]::IsNullOrEmpty($script_path)) {
    # Dans les cas où le script est invoqué de manière spéciale (par ex. depuis un pipeline), $MyInvocation.MyCommand.Path peut être vide
    $script_path = Join-Path -Path (Get-Location) -ChildPath $MyInvocation.MyCommand.Name
}

$script_directory = Split-Path -Parent $script_path # Répertoire de base de la bibliothèque
$exit_code = 1 # Code de sortie par défaut (échec)

try {
    # Charge tous les modules de la bibliothèque (constantes, types personnalisés, utilitaires, etc.)
    . (Join-Path -Path $script_directory -ChildPath "Constants.ps1")
    . (Join-Path -Path $script_directory -ChildPath "CustomTypes.ps1")
    . (Join-Path -Path $script_directory -ChildPath "StringUtils.ps1")
    . (Join-Path -Path $script_directory -ChildPath "ErrorUtils.ps1")
    . (Join-Path -Path $script_directory -ChildPath "Validation.ps1")
    . (Join-Path -Path $script_directory -ChildPath "Process.ps1")
    . (Join-Path -Path $script_directory -ChildPath "InjectorCore.ps1")

    # Définit la fonction d'interface principale pour l'utilisateur.
    # C'est un wrapper pour la classe Injector_Core.
    function Initialize_Game {
        param([string]$inject_type, [string]$folder, [string]$nickname, [string]$ip, [string]$port, [string]$password = "")

        # Vérifie si l'environnement PowerShell est x64 et s'il n'a pas encore été redémarré en x86
        if ([IntPtr]::Size -eq 8 -and -not $restarted_x86) {
            Write-Host "Detected PowerShell x64 environment. Restarting on PowerShell x86 for DLL injection compatibility (32-bit)..." -ForegroundColor Yellow

            # Localise l'exécutable de PowerShell 32 bits
            $powershell_x86_path = Join-Path -Path $env:windir -ChildPath "SysWOW64\WindowsPowerShell\v1.0\powershell.exe"

            if (-not (Test-Path -Path $powershell_x86_path)) {
                Write-Host "Could not find powershell.exe (x86) at '$powershell_x86_path'. 32-bit DLL injection may fail." -ForegroundColor Red
                return $false
            }

            # Prépare la liste des arguments pour le nouveau processus PowerShell x86
            $argument_list = @("-NoProfile", "-NonInteractive", "-ExecutionPolicy", "Bypass", "-File", $script_path, $inject_type, $folder, $nickname, $ip, $port)
            
            if (-not [string]::IsNullOrEmpty($password)) {
                $argument_list += $password
            }
            # Ajoute l'indicateur pour signaler qu'il a déjà été redémarré
            $argument_list += "-restarted_x86"
            
            try {
                $process_start_info = New-Object System.Diagnostics.ProcessStartInfo
                $process_start_info.FileName = $powershell_x86_path
                # Joint les arguments en une chaîne pour StartInfo.Arguments
                $process_start_info.Arguments = ($argument_list | ForEach-Object { "`"$_`"" }) -join " " # Met les arguments entre guillemets pour gérer les espaces
                $process_start_info.RedirectStandardOutput = $true # Redirige la sortie du processus enfant
                $process_start_info.RedirectStandardError = $true   # Redirige les erreurs du processus enfant
                $process_start_info.UseShellExecute = $false     # N'utilise pas ShellExecute (exécute directement PowerShell.exe)
                $process_start_info.CreateNoWindow = $true       # Ne crée pas de nouvelle fenêtre pour le processus enfant

                $child_process = New-Object System.Diagnostics.Process
                $child_process.StartInfo = $process_start_info
                
                # Démarre le processus enfant et attend sa fin
                [void]$child_process.Start()
                $child_process.WaitForExit()
                
                # Capture et affiche la sortie/les erreurs du processus enfant
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
        
        # Logique d'initialisation réelle, atteinte uniquement si l'environnement est x86 ou a déjà été redémarré
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

        $injector_core = New-Object Injector_Core # Instancie la classe principale d'injection

        # Délègue l'appel à la fonction Initialize_Game de la classe Injector_Core
        return $injector_core.Initialize_Game($injection_type, $folder, $nickname, $ip, $port, $password)
    }

    # Paramètres passés à la fonction principale
    $initialization_parameters = @{
        inject_type = $inject_type
        folder = $folder
        nickname = $nickname
        ip = $ip
        port = $port
        password = $password
    }

    # Appel pour démarrer le processus d'injection
    $game_initialization_result = Initialize_Game @initialization_parameters

    if ($game_initialization_result) {
        $exit_code = 0 # Succès
    }
    else {
        $exit_code = 1 # Échec
    }
}
catch {
    Write-Host "Critical error during execution: '$($_.Exception.Message)'" -ForegroundColor Red
    $exit_code = 1
}
finally {
    # S'assure que le script de nettoyage est exécuté à la fin, indépendamment du succès ou de l'échec
    try {
        . (Join-Path -Path $script_directory -ChildPath "Cleanup.ps1")
    }
    catch {
        Write-Host "Warning: Cleanup script execution failed: '$($_.Exception.Message)'" -ForegroundColor Yellow
    }
    
    exit $exit_code # Sort avec le code de statut approprié
}
```

> [!NOTE]
> Ce script est le point d'entrée principal pour l'injection. Il est responsable de:
> - Définir les **paramètres de ligne de commande** que l'utilisateur final utilisera.
> - Définir `$ErrorActionPreference = 'Stop'` pour un contrôle plus strict des erreurs.
> - **Charger** tous les scripts auxiliaires en utilisant le "dot-sourcing" (`. `), garantissant que leurs fonctions et classes sont disponibles dans la session actuelle.
> - Implémenter la logique de **redémarrage pour l'environnement x86**: Si PowerShell s'exécute en 64 bits, il se relance automatiquement dans une instance 32 bits (SysWOW64) et passe les mêmes arguments, car l'injection de DLLs 32 bits est plus fiable (et, dans de nombreux cas, obligatoire) depuis un processus 32 bits. C'est une distinction clé de PowerShell par rapport à une application C++ compilée directement pour x86.
> - Appeler la fonction `Initialize_Game` pour démarrer le processus d'injection.
> - Gérer le code de sortie du script (0 pour succès, 1 pour échec).
> - Appeler le script `Cleanup.ps1` dans le bloc `finally`.

### `Cleanup.ps1`

Ce script est responsable de la suppression des fonctions et des variables globales chargées par la bibliothèque de la session PowerShell actuelle. C'est une bonne pratique pour éviter de polluer l'environnement et pour s'assurer que les exécutions ultérieures du script avec des configurations différentes ne rencontrent pas d'états inattendus des sessions précédentes.

```powershell
$functions_to_remove = @(
    '*Initialize_Game*', # Utilise un joker pour supprimer des fonctions (peut avoir des alias)
    '*Get_System_Error_Message*',
    '*Show_Error*',
    '*Convert_Wide_To_Local_8Bit*',
    '*Validate_*', # Supprime toutes les fonctions qui commencent par 'Validate_'
    '*Build_Command_Args*'
)

# Itère sur les motifs et supprime les fonctions
foreach ($pattern in $functions_to_remove) {
    Get-Command -CommandType Function -Name $pattern -ErrorAction SilentlyContinue | ForEach-Object {
        try {
            Remove-Item -Path "Function:$($_.Name)" -Force -ErrorAction SilentlyContinue
        }
        catch {} # Ignore les erreurs si la fonction ne peut pas être supprimée pour une raison quelconque
    }
}

$global_variables_to_remove = @(
    'CONSTANTS',
    'CAN_SHOW_MESSAGE_BOX' # Ajoutez ici si d'autres variables globales sont introduites
)

# Itère sur les variables globales et les supprime
foreach ($variable_name in $global_variables_to_remove) {
    try {
        Remove-Variable -Name $variable_name -Scope Global -Force -ErrorAction SilentlyContinue
    }
    catch {} # Ignore les erreurs
}

$variable_patterns_to_remove = @(
    '*_Core*', # Supprime les variables qui se terminent par '_Core' (par ex., $injector_core)
    '*Process*' # Supprime les variables qui se terminent par 'Process' (par ex., $process_manager)
)

# Supprime les variables dans différentes portées en utilisant des motifs
foreach ($scope in @('Script', 'Local')) {
    foreach ($pattern in $variable_patterns_to_remove) {
        Get-Variable -Scope $scope -Name $pattern -ErrorAction SilentlyContinue | ForEach-Object {
            try {
                Remove-Variable -Name $_.Name -Scope $scope -Force -ErrorAction SilentlyContinue
            }
            catch {} # Ignore les erreurs
        }
    }
}
```

> [!TIP]
> Le nettoyage est crucial dans les scripts PowerShell qui importent de nombreux éléments dans la session. `Remove-Item -Path "Function:..."` et `Remove-Variable` sont utilisés pour désallouer ces éléments. L'utilisation de `ErrorAction SilentlyContinue` et de `try/catch` vides dans les boucles de suppression garantit que le script de nettoyage n'échoue pas si un élément a déjà été supprimé ou n'existe pas.

## Exemples Complets d'Utilisation

Pour intégrer le **SA-MP Injector PowerShell** dans votre projet ou l'utiliser directement, suivez les instructions et analysez les scénarios ci-dessous.

### 1. Préparation de l'Environnement de Développement

- **PowerShell Version**: **PowerShell 5.1** ou supérieur est recommandé (compatible avec `Add-Type` pour les classes).
- **Permissions d'Exécution**: PowerShell a des politiques d'exécution. Vous devrez autoriser l'exécution de scripts locaux. Ouvrez PowerShell en tant qu'**Administrateur** et exécutez:
   ```powershell
   Set-ExecutionPolicy -ExecutionPolicy RemoteSigned -Scope CurrentUser
   ```
   Cela permettra aux scripts signés de s'exécuter, et aux scripts que vous avez créés (non téléchargés d'Internet) de s'exécuter localement sans signature.
- **Copier les Fichiers**: Placez tous les fichiers `.ps1` de la bibliothèque (`Injector.ps1`, `Constants.ps1`, `CustomTypes.ps1`, `StringUtils.ps1`, `ErrorUtils.ps1`, `Validation.ps1`, `Process.ps1`, `InjectorCore.ps1`, `Cleanup.ps1`) dans un seul répertoire.
- **Permissions de Processus**: Votre script aura besoin de privilèges d'**Administrateur** pour créer des processus et injecter des DLLs dans un autre processus. Exécutez toujours **PowerShell en tant qu'Administrateur** lorsque vous utilisez cette bibliothèque.

### 2. Scénario de Base: Connexion à un Serveur SA-MP

C'est le cas d'utilisation le plus courant, démarrant GTA:SA et se connectant à un serveur SA-MP avec un pseudonyme et une adresse IP/port spécifiques.

```powershell
# Créez un nouveau script, par exemple, "StartSAMP.ps1"

# Importe la fonction principale de la bibliothèque SA-MP Injector PowerShell
# Assurez-vous que le chemin ci-dessous reflète l'emplacement de Injector.ps1.
# Par exemple, si Injector.ps1 se trouve dans le même dossier que ce script:
$injector_path = Join-Path -Path $PSScriptRoot -ChildPath "Injector.ps1"

# Ou, s'il se trouve dans un sous-répertoire:
# $injector_path = Join-Path -Path $PSScriptRoot -ChildPath "SA-MP-Injector-PowerShell\Injector.ps1"

# Importe la fonction Injector.ps1 en utilisant le dot-sourcing pour que ses fonctions
# soient disponibles dans la portée actuelle.
. $injector_path

# Définir les variables de configuration
# Modifiez ces chemins et détails de serveur pour correspondre à votre configuration locale.
$game_folder = "C:\Games\GTA San Andreas" # Où se trouvent gta_sa.exe, samp.dll
$player_nickname = "Nom"
$server_ip = "127.0.0.1" # Exemple: votre serveur local
$server_port = "7777"
$server_password = "" # Laissez vide s'il n'y a pas de mot de passe

Write-Host "Démarrage de SA-MP..." -ForegroundColor Cyan
Write-Host "Dossier du jeu: $game_folder" -ForegroundColor Gray
Write-Host "Pseudonyme: $player_nickname" -ForegroundColor Gray
Write-Host "Serveur: $server_ip:$server_port" -ForegroundColor Gray

# Appel à la fonction de la bibliothèque pour démarrer le jeu
$result = Initialize_Game `
    -inject_type "samp" ` # Type d'injection: "samp" ou "omp"
    -folder $game_folder ` # Chemin du dossier du jeu
    -nickname $player_nickname ` # Pseudonyme souhaité
    -ip $server_ip ` # IP du serveur
    -port $server_port ` # Port du serveur (chaîne)
    -password $server_password # Mot de passe du serveur (chaîne, peut être vide)

if ($result) {
    Write-Host "`n--- SA-MP initialisé avec succès ! ---" -ForegroundColor Green
    Write-Host "Le jeu a été démarré dans un processus séparé." -ForegroundColor Green
}
else {
    Write-Host "`n--- ÉCHEC de l'initialisation de SA-MP ! ---" -ForegroundColor Red
    Write-Host "Vérifiez les messages d'erreur affichés (pop-ups ou console)." -ForegroundColor Red
}

# Garde la console ouverte pour visualiser les messages de sortie
Read-Host "`nAppuyez sur Entrée pour fermer le programme."
```

**Pour exécuter le script:**
1.  **Sauvegardez** le code ci-dessus sous le nom `StartSAMP.ps1` (ou tout autre nom, tant qu'il se termine par `.ps1`).
2.  **Sauvegardez** tous les fichiers de la bibliothèque **SA-MP Injector PowerShell** dans le même dossier ou dans une structure de sous-dossiers que vous gérez avec `$injector_path`.
3.  **Ouvrez PowerShell en tant qu'Administrateur**.
4.  Naviguez jusqu'au répertoire où vous avez sauvegardé `StartSAMP.ps1`.
5.  Exécutez le script:
   ```powershell
   .\StartSAMP.ps1
   ```
   (Rappelez-vous que `.` avant le nom du script est nécessaire pour les scripts dans le répertoire courant, sauf si vous l'ajoutez au PATH).

### 3. Scénario Avancé: Connexion à un Serveur OMP

Pour OMP, la logique est identique à celle de SA-MP, mais vous spécifiez `"omp"` comme `inject_type` et vous vous assurez que `omp-client.dll` est présent dans le répertoire du jeu.

```powershell
# Créez un nouveau script, par exemple, "StartOMP.ps1"

# Importe la fonction principale de la bibliothèque SA-MP Injector PowerShell
$injector_path = Join-Path -Path $PSScriptRoot -ChildPath "Injector.ps1"
. $injector_path

# Définir les variables de configuration pour OMP
$game_folder = "C:\Games\GTA San Andreas" # Où se trouvent gta_sa.exe, samp.dll et omp-client.dll
$player_nickname = "Nom"
$server_ip = "127.0.0.1" # Exemple: votre serveur local
$server_port = "7777"
$server_password = "" # Laissez vide s'il n'y a pas de mot de passe

Write-Host "Démarrage d'OMP..." -ForegroundColor Cyan
Write-Host "Dossier du jeu: $game_folder" -ForegroundColor Gray
Write-Host "Pseudonyme: $player_nickname" -ForegroundColor Gray
Write-Host "Serveur: $server_ip:$server_port" -ForegroundColor Gray

# Appel à la fonction de la bibliothèque pour démarrer le jeu
$result = Initialize_Game `
    -inject_type "omp" `   # Type d'injection: "omp"
    -folder $game_folder `
    -nickname $player_nickname `
    -ip $server_ip `
    -port $server_port `
    -password $server_password

if ($result) {
    Write-Host "`n--- OMP initialisé avec succès ! ---" -ForegroundColor Green
    Write-Host "Le jeu a été démarré dans un processus séparé." -ForegroundColor Green
}
else {
    Write-Host "`n--- ÉCHEC de l'initialisation d'OMP ! ---" -ForegroundColor Red
    Write-Host "Vérifiez les messages d'erreur affichés (pop-ups ou console)." -ForegroundColor Red
}

Read-Host "`nAppuyez sur Entrée pour fermer le programme."
```

**Pour exécuter le script:**

Suivez les mêmes étapes que dans la section précédente, en remplaçant `StartSAMP.ps1` par `StartOMP.ps1`.

### 4. Exécution à partir d'un Script Parent

Il est possible de créer un script plus complexe qui invoque la bibliothèque et gère les paramètres ou les conditions de manière plus avancée. Le concept central reste le même: `Injector.ps1` doit être "dot-sourcé" dans le script parent.

```powershell
# Launcher.ps1
param(
    [string]$type = "samp",
    [string]$game_dir = "C:\Games\GTA San Andreas",
    [string]$player_nickname = "Nom",
    [string]$server_ip = "127.0.0.1",
    [string]$server_port = "7777",
    [string]$server_password = ""
)

# Charge Injector.ps1
$injector_script = Join-Path -Path $PSScriptRoot -ChildPath "Injector.ps1"

# Vérifie si le script principal de l'injecteur existe avant de le charger
if (-not (Test-Path $injector_script -PathType Leaf)) {
    Write-Error "Injector.ps1 non trouvé dans $injector_script. Veuillez vérifier le chemin."
    
    exit 1
}

. $injector_script # Utilise le dot-sourcing pour charger les fonctions

Write-Host "Tentative de démarrage du jeu avec les paramètres fournis..." -ForegroundColor Yellow

$success = Initialize_Game -inject_type $type `
    -folder $game_dir `
    -nickname $player_nickname `
    -ip $server_ip `
    -port $server_port `
    -password $server_password

if ($success) {
    Write-Host "`nRapport du lanceur: Jeu démarré avec succès !" -ForegroundColor Green
}
else {
    Write-Host "`nRapport du lanceur: Échec du démarrage du jeu !" -ForegroundColor Red
}

Read-Host "`nAppuyez sur Entrée pour quitter."
```

**Exécution de `Launcher.ps1`:**

```powershell
# Exécute avec les valeurs par défaut
.\Launcher.ps1

# Exécute pour OMP avec une IP et un port spécifiques
.\Launcher.ps1 -type "omp" -server_ip "omp.server.com" -server_port "7777" -player_nickname "Nom" -server_password "secure123"
```

## Gestion des Erreurs Courantes et Messages

Le **SA-MP Injector PowerShell** donne la priorité à la convivialité, et une partie fondamentale de cela est de fournir un retour clair à l'utilisateur en cas d'échec. Les messages d'erreur sont présentés via des **boîtes de dialogue Windows** (`MessageBoxW`) ou directement dans la console PowerShell, et sont catégorisés par type d'**injection (SA-MP ou OMP)** pour plus de contexte. Cela garantit que vous savez exactement ce qui n'a pas fonctionné et comment aborder la résolution.

Voici quelques-unes des erreurs courantes que vous pouvez rencontrer et leurs causes/solutions probables, accompagnées d'exemples visuels de la façon dont ces boîtes de dialogue apparaissent pour l'utilisateur final:

### 1. Type d'Injection Invalide

Si le `inject_type` fourni n'est pas `"samp"` ou `"omp"`, la bibliothèque ne saura pas quel client multijoueur vous avez l'intention d'initialiser.

![Erreur 1](screenshots/error_1.png)

- **Message d'Erreur Affiché**: `"Invalid injection mode specified. Please use 'samp' or 'omp'."`
- **Cause**: L'argument `inject_type` ne correspond pas aux valeurs attendues de `"samp"` ou `"omp"`. Il peut s'agir d'une faute de frappe, d'une chaîne vide ou d'une valeur non reconnue.
- **Solution**: Vérifiez que `$inject_type` est correctement défini sur `"samp"` ou `"omp"`. Il est important que la chaîne corresponde exactement (bien que le code utilise `ToLower()` pour la comparaison).
   ```powershell
   # Correct:
   Initialize_Game -inject_type "samp" ...
   Initialize_Game -inject_type "omp" ...

   # Incorrect (causera une erreur):
   # Initialize_Game -inject_type "invalid" ...
   # Initialize_Game -inject_type "" ...
   ```

### 2. Port du Serveur Invalide (Format ou Plage)

Le port est un paramètre numérique essentiel pour la connexion au serveur. Cette erreur se produit si la valeur ne peut pas être interprétée comme un nombre valide ou si elle est en dehors de la plage acceptable (**1 à 65535**).

#### 2.1. Format de Port Non Numérique

![Erreur 2](screenshots/error_2.png)

- **Message d'Erreur Affiché**: `"Invalid port format. The port must be a numeric value. Please provide a valid integer for the port."`
- **Cause**: L'argument `port` contient des caractères qui ne sont pas des chiffres numériques ou ne peut pas être converti en un nombre entier valide (par ex., `"abc"`, `"7777a"`).
- **Solution**: Fournissez une chaîne qui ne contient que des chiffres et représente un nombre entier valide.
   ```powershell
   # Correct:
   Initialize_Game ... -port "7777" ...
   
   # Incorrect (format invalide):
   # Initialize_Game ... -port "port7777" ...
   # Initialize_Game ... -port "invalid" ...
   ```

#### 2.2. Port en Dehors de la Plage Valide

![Erreur 3](screenshots/error_3.png)

- **Message d'Erreur Affiché**: `"The specified port number (XXXX) is outside the valid range of 1 to 65535. Please provide a valid port."` (Le **XXXX** sera la valeur que vous avez essayé d'utiliser).
- **Cause**: Le port fourni est un nombre valide, mais il est inférieur à `1` (réservé ou non utilisable) ou supérieur à `65535` (limite maximale pour les **ports TCP/UDP**).
- **Solution**: Fournissez un port qui se situe dans la plage de `1` à `65535`. Les ports courants pour **SA-MP**/**OMP** sont `7777`.
   ```powershell
   # Correct:
   Initialize_Game ... -port "7777" ...

   # Incorrect (hors de la plage):
   # Initialize_Game ... -port "0" ...      # Trop bas
   # Initialize_Game ... -port "65536" ...  # Trop élevé
   # Initialize_Game ... -port "-1" ...     # Valeur négative
   ```

### 3. Pseudonyme Invalide (Vide ou Trop Long)

Le **pseudonyme** du joueur est validé pour s'assurer que le client du jeu l'accepte.

#### 3.1. Pseudonyme Vide

![Erreur 4](screenshots/error_4.png)

- **Message d'Erreur Affiché**: `"Nickname cannot be empty. Please provide a valid nickname."`
- **Cause**: L'argument `nickname` a été fourni comme une chaîne vide.
- **Solution**: Assurez-vous que le pseudonyme n'est pas vide.
   ```powershell
   # Correct:
   Initialize_Game ... -nickname "MonPseudo" ...

   # Incorrect (vide):
   # Initialize_Game ... -nickname "" ...
   ```

#### 3.2. Pseudonyme Trop Long

![Erreur 5](screenshots/error_5.png)

- **Message d'Erreur Affiché**: `"Nickname length exceeds the maximum allowed of 23 characters. Please use a shorter nickname."`
- **Cause**: La longueur du **pseudonyme** fourni dépasse `$global:CONSTANTS.MAX_NICKNAME_LENGTH`, qui est de `23` caractères.
- **Solution**: Utilisez un **pseudonyme** qui a au maximum `23` caractères.
   ```powershell
   # Correct:
   Initialize_Game ... -nickname "Court" ...

   # Incorrect (trop long):
   # Initialize_Game ... -nickname "CeNomDeJoueurEstBeaucoupTropLongPourEtreUtiliseIci" ...
   ```

### 4. Fichiers du Jeu ou DLL Non Trouvés

C'est l'une des causes les plus fréquentes d'échec. La bibliothèque a besoin que `gta_sa.exe`, `samp.dll` et, pour **OMP**, `omp-client.dll` soient présents aux emplacements attendus.

#### 4.1. Exécutable du Jeu (`gta_sa.exe`) Non Trouvé

![Erreur 6](screenshots/error_6.png)

- **Message d'Erreur Affiché**: `"Game executable not found. Please ensure 'gta_sa.exe' exists at the specified path: [chemin complet]"`. Le `[chemin complet]` inclura le dossier et le nom du fichier.
- **Cause**: Le fichier `gta_sa.exe` n'a pas été trouvé dans le dossier fourni dans l'argument `folder`.
- **Solution**:
   1. Vérifiez que `$folder` pointe vers le bon répertoire d'installation de **GTA San Andreas**.
   2. Confirmez que `gta_sa.exe` existe dans ce dossier et que son nom n'a pas été modifié.

#### 4.2. Bibliothèque SA-MP (`samp.dll`) Non Trouvée

![Erreur 7](screenshots/error_7.png)

- **Message d'Erreur Affiché**: `"SA-MP library not found. Please ensure 'samp.dll' exists at the specified path: [chemin complet]"`.
- **Cause**: Le fichier `samp.dll` n'a pas été trouvé dans le dossier fourni dans l'argument `folder`. **Cette DLL** est une exigence pour **les deux** types d'injection (`samp` et `omp`).
- **Solution**: Assurez-vous que `samp.dll` est présent dans le dossier d'installation de **GTA San Andreas**.

#### 4.3. Bibliothèque OMP (`omp-client.dll`) Non Trouvée (uniquement pour l'injection OMP)

![Erreur 8](screenshots/error_8.png)

- **Message d'Erreur Affiché**: `"OMP library not found. Please ensure 'omp-client.dll' exists at the specified path for OMP injection: [chemin complet]"`.
- **Cause**: Si vous avez spécifié `"omp"` comme type d'injection, mais que le fichier `omp-client.dll` n'a pas été trouvé dans le dossier fourni.
- **Solution**: Téléchargez le client **OMP** le plus récent et assurez-vous que `omp-client.dll` (et `samp.dll`) sont présents dans le dossier d'installation de **GTA San Andreas**.

### 5. Échec de la Création du Processus du Jeu

C'est une erreur plus complexe, car elle implique des **permissions du système d'exploitation** et l'état actuel de `gta_sa.exe`.

![Erreur 9](screenshots/error_9.png)

- **Message d'Erreur Affiché**: `"Failed to create game process. Ensure 'gta_sa.exe' is not running and you have sufficient permissions to execute the file. System Error: [Message d'erreur du système d'exploitation]"`. Le message système sera ajouté par `Get_System_Error_Message` (ex: `Access is denied.` ou `The requested operation requires elevation.`).
- **Cause**: L'appel `CreateProcessA` pour démarrer `gta_sa.exe` a échoué. Les causes courantes incluent:
   - **Processus déjà en cours d'exécution**: Une instance de `gta_sa.exe` est déjà active et bloque une nouvelle exécution.
   - **Permissions insuffisantes**: Votre script n'a pas les privilèges nécessaires (par ex., administrateur) pour créer un processus dans certaines configurations système (**UAC** activé, dossiers protégés, etc.).
   - **Problèmes avec l'exécutable**: Le `gta_sa.exe` peut être corrompu ou bloqué par un autre programme (par ex., un antivirus mal configuré).
- **Solution**:
   1. Vérifiez le Gestionnaire des tâches et assurez-vous qu'aucune instance de `gta_sa.exe` n'est en cours d'exécution. Terminez-en une le cas échéant.
   2. Exécutez le script **PowerShell en tant qu'Administrateur**. Faites un clic droit sur l'icône de PowerShell et sélectionnez **"Exécuter en tant qu'administrateur"**, ou lancez-le à partir d'un raccourci configuré pour cela.
   3. Si un **antivirus** ou un **logiciel** de sécurité interfère, ajoutez votre script et/ou le dossier de **GTA:SA** aux exceptions de l'antivirus (faites-le avec prudence et uniquement si vous êtes sûr de l'intégrité de vos fichiers).

### 6. Échec de l'Allocation de Mémoire dans le Processus Cible

La bibliothèque tente d'allouer un petit espace mémoire dans `gta_sa.exe` pour copier le **chemin de la DLL**.

![Erreur 10](screenshots/error_10.png)

- **Message d'Erreur Affiché**: `"Failed to allocate memory in the target process. This might be due to insufficient permissions or process protection mechanisms. System Error: [Message d'erreur du système d'exploitation]"`.
- **Cause**: La fonction `VirtualAllocEx` (utilisée pour allouer de la mémoire dans un autre processus) a échoué. C'est plus probable si:
   - Le processus de **GTA:SA** (même en état suspendu) possède des défenses de sécurité ou des **patchs anti-injection** qui empêchent l'allocation de mémoire par des processus externes.
   - Votre script n'a pas les permissions élevées nécessaires pour manipuler la mémoire d'un autre processus.
   - (Moins courant) Il y a une pénurie extrême de mémoire virtuelle sur le système.
- **Solution**:
   1. Exécutez votre script avec des privilèges d'**Administrateur**.
   2. Assurez-vous que le jeu ne possède aucune modification ou **patch de sécurité** qui pourrait bloquer les tentatives d'injection ou de manipulation de la mémoire (c'est plus courant dans des environnements modifiés ou avec certains outils anti-triche tiers).

### 7. Échec de l'Écriture du Chemin de la DLL dans la Mémoire du Processus

Après avoir alloué la mémoire, la bibliothèque tente d'y copier le **chemin de la DLL**.

![Erreur 11](screenshots/error_11.png)

- **Message d'Erreur Affiché**: `"Failed to write DLL path to the target process memory. Verify process permissions and ensure the DLL path is accessible. System Error: [Message d'erreur du système d'exploitation]"`.
- **Cause**: La fonction `WriteProcessMemory` a échoué en essayant de copier les **octets du chemin de la DLL** dans la mémoire distante allouée dans `gta_sa.exe`. Cela indique généralement:
   - **Permissions d'écriture**: Votre script n'a pas la permission d'écrire dans cette région de mémoire ou dans le processus de **GTA:SA**.
   - **Handle invalide**: Le **handle** du processus est devenu invalide d'une manière ou d'une autre (moins courant, mais possible dans des conditions système extrêmes).
   - **Problèmes de Protection de la Mémoire**: Une protection de la mémoire (soit du **SE** ou de modifications du jeu) a empêché l'écriture.
- **Solution**: Exécutez en tant qu'**Administrateur**. Vérifiez que `gta_sa.exe` et son environnement sont "propres" de tout outil qui pourrait bloquer les opérations de mémoire.

### 8. Échec de la Recherche des Fonctions Essentielles du Système

Ce sont des API Windows cruciales ; des erreurs ici indiquent un problème fondamental avec le système d'exploitation ou l'environnement d'exécution.

#### 8.1. `kernel32.dll` Non Trouvé

![Erreur 12](screenshots/error_12.png)

- **Message d'Erreur Affiché**: `"Failed to obtain a handle to kernel32.dll. This is an essential system library and this error indicates a severe system issue. System Error: [Message d'erreur du système d'exploitation]"`.
- **Cause**: `kernel32.dll` est l'une des DLL les plus fondamentales de Windows, contenant des fonctions essentielles. Si `GetModuleHandleA` ne peut pas obtenir un **handle** pour elle, le système d'exploitation a de très graves problèmes.
- **Solution**: C'est une erreur **critique** qui est rarement causée par la bibliothèque ou votre script. Elle suggère une corruption des fichiers système, de graves problèmes avec **Windows**, ou une installation très inhabituelle du **SE**. Il est recommandé d'exécuter des vérifications d'intégrité du système (comme `sfc /scannow` dans l'**Invite de Commandes** en tant qu'**Administrateur**) ou, en dernier recours, de réinstaller **Windows**.

#### 8.2. `LoadLibraryA` Non Trouvé

![Erreur 13](screenshots/error_13.png)

- **Message d'Erreur Affiché**: `"Failed to find the address of the LoadLibraryA function in kernel32.dll. This is critical for injecting the DLL. System Error: [Message d'erreur du système d'exploitation]"`.
- **Cause**: Bien que `kernel32.dll` ait été trouvé, la fonction `LoadLibraryA` n'a pas pu être résolue via `GetProcAddress`. Bien qu'extrêmement rare, cela peut résulter d'une corruption du **fichier DLL** de `kernel32.dll` ou d'un environnement d'exécution très non standard.
- **Solution**: Tout comme l'erreur de `kernel32.dll` ci-dessus, cela indique un problème sérieux au niveau du système d'exploitation.

### 9. Échec de la Création d'un Thread Distant pour l'Injection

Après avoir préparé l'environnement distant et copié le **chemin de la DLL**, un nouveau **thread** est créé dans le processus du jeu pour "appeler" `LoadLibraryA`.

![Erreur 14](screenshots/error_14.png)

- **Message d'Erreur Affiché**: `"Failed to create a remote thread in the target process to execute the DLL injection. This could be due to security restrictions or process state. System Error: [Message d'erreur du système d'exploitation]"`.
- **Cause**: L'appel `CreateRemoteThread` a échoué. Cette erreur est fréquente sur les systèmes dotés de défenses **anti-injection** robustes ou lorsqu'un programme surveille intensivement le comportement du processus:
   - **Mécanismes de Sécurité**: Les outils **anti-triche**, les **logiciels** de sécurité ou certaines politiques **Windows** peuvent détecter et bloquer les tentatives de création de **threads** dans des processus tiers.
   - **Processus Cible Incohérent**: Si le processus de **GTA:SA** est dans un état inattendu ou instable (bien que démarré en `CREATE_SUSPENDED`), cela peut affecter la capacité à y créer des **threads**.
- **Solution**:
   1. Exécutez votre script avec des privilèges d'**Administrateur**.
   2. Vérifiez qu'il n'y a pas d'outils **anti-triche**, d'**antivirus agressifs** ou de **pare-feu** configurés pour inspecter et bloquer la manipulation de processus qui pourraient être en conflit. Ajoutez votre script et `gta_sa.exe` aux exceptions, si applicable (avec précaution).
   3. Le message d'erreur du système peut fournir des détails supplémentaires pour enquêter sur la cause spécifique (par ex. **"A process has been denied access to create threads for other processes."**).

### 10. Délai d'Attente ou Échec de la Finalisation de l'Injection

Après avoir créé le **thread** distant, l'injecteur attend qu'il termine le **chargement de la DLL**.

![Erreur 15](screenshots/error_15.png)

- **Message d'Erreur Affiché**: `"Timeout or error waiting for DLL injection to complete (timeout). System Error: [Message d'erreur du système d'exploitation]"`.
- **Cause**: Le **thread** distant qui exécute `LoadLibraryA` a mis plus de `$global:CONSTANTS.DLL_INJECTION_TIMEOUT_MS` (10 secondes) pour retourner, ou il a échoué et `GetExitCodeThread` a retourné 0. Les causes potentielles incluent:
   - **Problèmes dans la DLL Injectée**: Le `DllMain` de `samp.dll` ou `omp-client.dll` met trop de temps à s'exécuter, contient une **boucle infinie**, un **plantage**, ou une erreur qui **empêche la DLL** de se charger correctement (par ex. des **dépendances de DLLs** manquantes).
   - **Blocage Silencieux**: Un mécanisme de sécurité a peut-être bloqué `LoadLibraryA` mais ne l'a pas notifié avec une erreur évidente de création de **thread**.
- **Solution**:
   1. Vérifiez l'intégrité des fichiers `samp.dll` et `omp-client.dll`. Ils peuvent être corrompus ou d'une version incompatible avec votre `gta_sa.exe`.
   2. Assurez-vous **que la DLL injectée** ne dépend pas d'**autres DLLs** qui pourraient être manquantes ou inaccessibles sur le système.

### 11. Échec de la Reprise du Thread du Processus du Jeu

C'est la dernière étape pour démarrer le jeu après **que les DLLs** sont injectées.

![Erreur 16](screenshots/error_16.png)

- **Message d'Erreur Affiché**: `"Failed to resume the game process thread: [Message d'erreur du système d'exploitation]"`.
- **Cause**: L'appel `ResumeThread` a échoué, ce qui signifie que le **thread** principal de `gta_sa.exe` n'a pas pu être activé pour démarrer l'exécution du jeu. C'est une erreur rare, mais elle peut se produire si:
   - Le **handle** du **thread** du processus est devenu invalide.
   - Le système d'exploitation a empêché la reprise pour une raison quelconque, possiblement liée à une interruption de sécurité ou à un état incohérent du processus.
   - Le processus a peut-être été terminé de l'extérieur entre l'**injection de la DLL** et la tentative de reprise du **thread** principal.
- **Solution**: Si toutes les étapes précédentes ont réussi et que seul `ResumeThread` a échoué, il peut s'agir d'un problème avec le système d'exploitation, avec l'installation de **GTA:SA** elle-même, ou avec un autre **logiciel** de sécurité très strict. Réexaminez l'état de `gta_sa.exe` via le **Gestionnaire des tâches** juste avant et après l'erreur. Tenter de redémarrer l'ordinateur peut résoudre des problèmes d'état temporaires du système.

> [!TIP]
> Dans des scénarios de débogage complexes, des outils comme **Process Monitor (Sysinternals Suite)** ou un débogueur (comme **WinDbg**) peuvent être inestimables. Ils peuvent aider à observer les appels d'**API**, vérifier les erreurs d'accès, suivre l'état des **handles** et même inspecter la mémoire du processus, fournissant une vue approfondie de ce qui se passe en coulisses.
>
> Pour déboguer des scripts PowerShell qui utilisent `Add-Type` et interagissent avec la WinAPI à bas niveau, des outils comme **PowerShell Integrated Scripting Environment (ISE)** ou **Visual Studio Code** avec l'extension PowerShell sont utiles, permettant de placer des points d'arrêt et d'inspecter des variables. Rappelez-vous toujours de les exécuter **en tant qu'Administrateur**.

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