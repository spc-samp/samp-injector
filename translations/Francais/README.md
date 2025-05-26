# SA-MP Injector

[![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](https://opensource.org/licenses/MIT)
[![SA-MP | OMP](https://img.shields.io/badge/Support-SA--MP%20%7C%20OMP-yellow)](https://github.com/spc-samp/samp-injector)
[![x86 Only](https://img.shields.io/badge/Architecture-x86%20(32--bit)-orange)](https://github.com/spc-samp/samp-injector)

SA-MP Injector est un outil polyvalent conçu pour **SA-MP (San Andreas Multiplayer)** et **OMP (Open Multiplayer)**, fonctionnant à la fois comme un **exécutable en ligne de commande** et comme une **bibliothèque pour différents langages**. Sa fonction principale est d'injecter `samp.dll` (pour **SA-MP**) ou à la fois `samp.dll` et `omp-client.dll` (pour **OMP**) dans le processus de **GTA:SA**, permettant au jeu de démarrer avec des paramètres personnalisés pour une connexion directe à un serveur.

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

- [SA-MP Injector](#sa-mp-injector)
  - [Langues](#langues)
  - [Table des matières](#table-des-matières)
  - [Exécutable](#exécutable)
    - [Fonctionnalité](#fonctionnalité)
    - [Comment utiliser (Ligne de commande)](#comment-utiliser-ligne-de-commande)
      - [Mode SA-MP](#mode-sa-mp)
      - [Mode OMP](#mode-omp)
      - [Paramètres](#paramètres)
    - [Comment utiliser (Intégré dans des applications)](#comment-utiliser-intégré-dans-des-applications)
    - [Utilisation de la bibliothèque C++ dans l'exécutable](#utilisation-de-la-bibliothèque-c-dans-lexécutable)
    - [Comment compiler](#comment-compiler)
      - [Prérequis](#prérequis)
      - [Étapes de compilation](#étapes-de-compilation)
  - [Bibliothèques](#bibliothèques)
    - [Aperçu](#aperçu)
    - [Liste des bibliothèques](#liste-des-bibliothèques)
  - [Licence](#licence)
    - [Conditions Générales d'Utilisation](#conditions-générales-dutilisation)
      - [1. Autorisations Accordées](#1-autorisations-accordées)
      - [2. Conditions Obligatoires](#2-conditions-obligatoires)
      - [3. Droits d'Auteur](#3-droits-dauteur)
      - [4. Exclusion de Garantie et Limitation de Responsabilité](#4-exclusion-de-garantie-et-limitation-de-responsabilité)

## Exécutable

L'exécutable `samp-injector.exe` fournit une interface en ligne de commande pour lancer **GTA:SA** avec **SA-MP** ou **OMP**, en configurant automatiquement la connexion à un serveur. Il encapsule la logique de l'**injection de DLLs** et la transmission des paramètres du jeu.

### Fonctionnalité

Le `samp-injector.exe` fonctionne comme un lanceur de jeu automatisé, en abstrayant les complexités de la configuration et de l'**injection de DLLs**:

1. **Validation de l'environnement:** Vérifie l'existence des fichiers essentiels (`gta_sa.exe`, `samp.dll`, `omp-client.dll`) dans le répertoire spécifié, ainsi que la validité des paramètres de connexion fournis.
2. **Création d'un processus suspendu:** Lance `gta_sa.exe` dans un état suspendu, une condition préalable pour **injecter les DLLs** de manière sécurisée avant l'exécution du processus principal du jeu.
3. **Injection dynamique de DLLs:**
    - Pour le mode **SA-MP**, `samp.dll` est injecté.
    - Pour le mode **OMP**, `samp.dll` et `omp-client.dll` sont injectés.
    L'injection est facilitée par l'invocation à distance de la fonction `LoadLibraryA`, permettant à GTA:SA de charger les modules multijoueurs et d'initialiser la connexion.
4. **Configuration des arguments:** Les arguments de la ligne de commande, tels que le **pseudonyme**, l'**IP du serveur**, le **port** et le **mot de passe (si fourni)**, sont préparés et transmis à `gta_sa.exe`.
5. **Reprise du processus:** Après une **injection réussie des DLLs**, le processus du jeu est repris pour une exécution normale, ce qui conduit **GTA:SA** à se connecter directement au serveur.

### Comment utiliser (Ligne de commande)

Pour utiliser l'exécutable, invoquez-le depuis l'**Invite de commandes (CMD)**, **PowerShell** ou un **terminal**, en fournissant les paramètres nécessaires.

Le format de base est:

```bash
samp-injector.exe <mode> <répertoire_jeu> <pseudonyme> <ip_serveur> <port_serveur> <mot_de_passe_serveur (facultatif)>
```

#### Mode SA-MP

Pour l'injection exclusive de `samp.dll`:

```bash
samp-injector.exe "samp" "C:\Games\GTA San Andreas" "Nom" "127.0.0.1" "7777" "mot de passe (facultatif)"
```

#### Mode OMP

Pour l'injection de `samp.dll` et `omp-client.dll`:

```bash
samp-injector.exe "omp" "C:\Games\GTA San Andreas" "Nom" "127.0.0.1" "7777" "mot de passe (facultatif)"
```

#### Paramètres

- `<mode>`: Définit le type d'injection.
    - `samp`: Pour **SA-MP** (`samp.dll`).
    - `omp`: Pour **OMP** (`samp.dll` et `omp-client.dll`).
- `<répertoire_jeu>`: Le chemin complet vers le répertoire de **GTA:SA**. Ce répertoire doit contenir `gta_sa.exe` et les fichiers **DLL** respectifs.
- `<pseudonyme>`: Votre pseudonyme dans le jeu (maximum **20 caractères**).
- `<ip_serveur>`: L'**adresse IP** ou le **nom de domaine** du serveur.
- `<port_serveur>`: Le port de connexion du serveur (une **valeur numérique** entre **1** et **65535**).
- `<mot_de_passe_serveur>`: Le mot de passe requis pour se connecter au serveur **(si le serveur n'exige pas de mot de passe, ce paramètre n'est pas nécessaire)**.

Si les arguments sont incorrects ou insuffisants, un message d'utilisation sera affiché.

### Comment utiliser (Intégré dans des applications)

Le `samp-injector.exe` est idéal pour l'intégration dans des applications tierces, telles que des lanceurs personnalisés, qui souhaitent automatiser le processus de lancement du jeu avec des configurations prédéfinies.

Exemple d'invocation de `samp-injector.exe` depuis une **application C#**:

```csharp
using System;
using System.Diagnostics;
using System.Windows.Forms;

public class Launcher {
    public static void Main(string[] args) {
        string inject_mode = "omp"; 
        string folder = "C:\\Games\\GTA San Andreas";
        string nickname = "Nom";
        string ip = "127.0.0.1";
        string port = "7777";
        string password = "mot de passe (facultatif)";

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
                    MessageBox.Show($"L'injecteur SA-MP a renvoyé une erreur (Code: {process.ExitCode}). Le jeu n'a peut-être pas démarré correctement.", "Erreur de lancement", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }
        catch (Exception ex) {
            MessageBox.Show($"Une erreur s'est produite lors du lancement du jeu: {ex.Message}", "Erreur", MessageBoxButtons.OK, MessageBoxIcon.Error);
        }
    }
}
```

### Utilisation de la bibliothèque C++ dans l'exécutable

L'exécutable `samp-injector.exe` est construit sur la bibliothèque [SA-MP Injector C++](https://github.com/spc-samp/samp-injector/tree/main/libraries/cpp), située dans le répertoire `libraries/cpp/`. Le fichier `main.cpp` de l'exécutable invoque les fonctionnalités de cette bibliothèque pour effectuer l'injection et le lancement du jeu.

Le fichier d'en-tête principal de la bibliothèque **C++** à inclure est `libraries/samp-injector/cpp/injector.hpp`. Comme la bibliothèque [SA-MP Injector C++](https://github.com/spc-samp/samp-injector/tree/main/libraries/cpp) est **header-only**, son utilisation nécessite uniquement l'inclusion de cet en-tête dans le code source, sans avoir besoin de lier un fichier `.lib`.

Le fragment pertinent de `main.cpp` qui démontre l'intégration est le suivant:

```cpp
// Extrait les arguments de la ligne de commande
int argc;
std::unique_ptr<LPWSTR[], decltype(&LocalFree)> argv(CommandLineToArgvW(GetCommandLineW(), &argc), &LocalFree);

// ... (validation du nombre d'arguments et du mode d'injection) ...

// Extrait les paramètres dans des variables de chaîne large
std::wstring folder = argv[2];
std::wstring nickname = argv[3];
std::wstring ip = argv[4];
std::wstring port = argv[5];
std::wstring password = (argc == 7) ? argv[6] : L"";

// Délègue la logique d'injection à la fonction "Initialize_Game" de la bibliothèque
// Notez que "injector.hpp" a été inclus précédemment dans "main.cpp"
if (!Initialize_Game(inject_type, folder, nickname, ip, port, password))
    return 1;

Sleep(10000); // Attend avant de terminer l'exécutable
```

La fonction `Initialize_Game` agit comme l'interface de haut niveau de la bibliothèque, orchestrant toutes les opérations de validation, de création de processus et d'**injection de DLLs**.

### Comment compiler

Vous pouvez compiler le `samp-injector.exe` à partir du code source. Si vous ne souhaitez pas compiler, vous pouvez télécharger les versions précompilées dans la section [Releases](https://github.com/spc-samp/samp-injector/releases).

#### Prérequis

- **Visual Studio:** **Visual Studio 2022** ou supérieur avec la **charge de travail "Développement de bureau avec C++"** installée est recommandé.
- **Git:** Pour cloner le dépôt (ou téléchargez-le simplement en accédant à ce lien: [Download](https://github.com/spc-samp/samp-injector/archive/refs/heads/main.zip)).

#### Étapes de compilation

1. **Cloner le dépôt:**
    ```bash
    git clone https://github.com/spc-samp/samp-injector.git
    cd samp-injector
    ```
2. **Ouvrir la solution:**
   
    Naviguez vers le dossier `executable` et ouvrez le fichier de solution `.sln`:
    ```bash
    cd executable
    start samp-injector.sln
    ```
    Cela ouvrira le projet dans **Visual Studio**.
3. **Configurer la compilation:**
    - Dans **Visual Studio**, vérifiez la configuration de la solution. Il est recommandé d'utiliser les modes `Release` et `x86` **(32 bits)**. Dans le contexte de **GTA:SA** et **SA-MP**/**OMP**, l'**architecture x86 (32 bits)** est obligatoire.
4. **Compiler:**
   - Dans le menu `Build`, cliquez sur `Build Solution` ou `Build samp-injector`.
   - Alternativement, vous pouvez utiliser les raccourcis:
     - `Ctrl + Shift + B` pour compiler la solution complète.
     - `Ctrl + B` (si configuré) pour compiler le projet actuel.
    - Si tout est configuré correctement, l'exécutable `samp-injector.exe` sera généré dans le répertoire `executable\Release` (ou `executable\Debug`, selon votre configuration de **build**).

## Bibliothèques

Les bibliothèques sont les composants fondamentaux du `SA-MP Injector`, contenant la logique centrale pour la manipulation des processus, l'**injection de DLLs** et la validation des paramètres. L'avantage principal de l'utilisation de ces bibliothèques est la facilité d'initialisation et d'injection, généralement via une seule fonction (ou des appels avec des paramètres spécifiques pour les langages de script).

### Aperçu

Le projet est construit sur des bibliothèques qui encapsulent les fonctionnalités critiques. Cela permet à d'autres projets d'intégrer facilement la capacité de lancer **GTA:SA** avec les modules **multijoueurs** nécessaires.

### Liste des bibliothèques

| Langage       | Nom                        | Lien vers la bibliothèque/Documentation |
| ------------- | -------------------------- | --------------------------------------- |
| C++           | **SA-MP Injector C++**     | [Voir la bibliothèque](libraries/cpp)   |
| C             | **SA-MP Injector C**       | (Bientôt disponible)                    |
| C#            | **SA-MP Injector C#**      | (Bientôt disponible)                    |
| Java          | **SA-MP Injector Java**    | (Bientôt disponible)                    |
| Python        | **SA-MP Injector Python**  | (Bientôt disponible)                    |
| Go (Golang)   | **SA-MP Injector Go**      | (Bientôt disponible)                    |
| Rust          | **SA-MP Injector Rust**    | (Bientôt disponible)                    |
| Kotlin        | **SA-MP Injector Kotlin**  | (Bientôt disponible)                    |
| Scala         | **SA-MP Injector Scala**   | (Bientôt disponible)                    |
| Lua           | **SA-MP Injector Lua**     | (Bientôt disponible)                    |
| Ruby          | **SA-MP Injector Ruby**    | (Bientôt disponible)                    |
| Visual Basic  | **SA-MP Injector VB**      | (Bientôt disponible)                    |
| F#            | **SA-MP Injector F#**      | (Bientôt disponible)                    |
| Pascal/Delphi | **SA-MP Injector P/D**     | (Bientôt disponible)                    |
| PowerShell    | **SA-MP Injector PS**      | (Bientôt disponible)                    |
| D (Dlang)     | **SA-MP Injector D**       | (Bientôt disponible)                    |
| Nim           | **SA-MP Injector Nim**     | (Bientôt disponible)                    |
| Zig           | **SA-MP Injector Zig**     | (Bientôt disponible)                    |
| V (VLang)     | **SA-MP Injector V**       | (Bientôt disponible)                    |
| Crystal       | **SA-MP Injector Crystal** | (Bientôt disponible)                    |
| Perl          | **SA-MP Injector Perl**    | (Bientôt disponible)                    |
| Racket (Lisp) | **SA-MP Injector Racket**  | (Bientôt disponible)                    |
| Haskell       | **SA-MP Injector Haskell** | (Bientôt disponible)                    |
| OCaml         | **SA-MP Injector OCaml**   | (Bientôt disponible)                    |

> [!TIP]
> La documentation détaillée pour chaque bibliothèque sera disponible dans son **répertoire respectif**.

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