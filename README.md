# SA-MP Injector

[![License](https://img.shields.io/badge/License-MIT-blue.svg)](https://opensource.org/licenses/MIT)
[![SA-MP | OMP](https://img.shields.io/badge/Support-SA--MP%20%7C%20OMP-yellow)](https://github.com/spc-samp/samp-injector)
[![x86 Only](https://img.shields.io/badge/Architecture-x86%20(32--bit)-orange)](https://github.com/spc-samp/samp-injector)

**SA-MP Injector** é uma ferramenta versátil projetada para o **SA-MP (San Andreas Multiplayer)** e o **OMP (Open Multiplayer)**, funcionando como um **executável de linha de comando**, uma **biblioteca dinâmica (DLL)** e um **conjunto de bibliotecas para diferentes linguagens de programação**. Sua principal função é injetar a `samp.dll` (no caso do **SA-MP**) ou ambas `samp.dll` e `omp-client.dll` (no caso do **OMP**) no processo do **GTA\:SA**, permitindo que o jogo seja iniciado com parâmetros personalizados, possibilitando a conexão direta a um servidor.

## Idiomas

- Deutsch: [README](translations/Deutsch/README.md)
- English: [README](translations/English/README.md)
- Español: [README](translations/Espanol/README.md)
- Français: [README](translations/Francais/README.md)
- Italiano: [README](translations/Italiano/README.md)
- Polski: [README](translations/Polski/README.md)
- Русский: [README](translations/Русский/README.md)
- Svenska: [README](translations/Svenska/README.md)
- Türkçe: [README](translations/Turkce/README.md)

## Índice

- [SA-MP Injector](#sa-mp-injector)
  - [Idiomas](#idiomas)
  - [Índice](#índice)
  - [Executável](#executável)
    - [Funcionalidade](#funcionalidade)
    - [Como Usar (Linha de Comando)](#como-usar-linha-de-comando)
      - [Modo SA-MP](#modo-sa-mp)
      - [Modo OMP](#modo-omp)
      - [Parâmetros](#parâmetros)
    - [Como Usar (Embutido em Aplicações)](#como-usar-embutido-em-aplicações)
    - [Utilizando a Biblioteca C++ no Executável](#utilizando-a-biblioteca-c-no-executável)
    - [Como Compilar](#como-compilar)
      - [Requisitos](#requisitos)
      - [Passos de Compilação](#passos-de-compilação)
  - [Biblioteca Dinâmica (**DLL**)](#biblioteca-dinâmica-dll)
    - [Funcionalidade](#funcionalidade-1)
    - [Como Usar (Chamada de API)](#como-usar-chamada-de-api)
      - [Contrato da Função `Launch_Game`](#contrato-da-função-launch_game)
      - [Parâmetros](#parâmetros-1)
    - [Como Usar (Embutido em Aplicações)](#como-usar-embutido-em-aplicações-1)
    - [Utilizando a Biblioteca C++ na **DLL**](#utilizando-a-biblioteca-c-na-dll)
    - [Como Compilar](#como-compilar-1)
      - [Requisitos](#requisitos-1)
      - [Passos de Compilação](#passos-de-compilação-1)
  - [Bibliotecas](#bibliotecas)
    - [Visão Geral](#visão-geral)
    - [Listagem de Bibliotecas](#listagem-de-bibliotecas)
  - [Licença](#licença)
    - [Termos e Condições de Uso](#termos-e-condições-de-uso)
      - [1. Permissões Concedidas](#1-permissões-concedidas)
      - [2. Condições Obrigatórias](#2-condições-obrigatórias)
      - [3. Direitos Autorais](#3-direitos-autorais)
      - [4. Isenção de Garantias e Limitação de Responsabilidade](#4-isenção-de-garantias-e-limitação-de-responsabilidade)

## Executável

O executável `samp-injector.exe` oferece uma interface de linha de comando para iniciar o **GTA:SA** com **SA-MP** ou **OMP**, configurando automaticamente a conexão a um servidor. Ele encapsula a lógica de **injeção de DLLs** e a passagem de parâmetros do jogo.

### Funcionalidade

O `samp-injector.exe` opera como um iniciador de jogo automatizado, abstraindo as complexidades de configuração e injeção de **DLL**:

1. **Validação de Ambiente:** Verifica a existência dos arquivos essenciais (`gta_sa.exe`, `samp.dll`, `omp-client.dll`) no diretório especificado, além de validar os parâmetros de conexão fornecidos.
2. **Criação de Processo Suspenso:** Inicia `gta_sa.exe` em estado suspenso, um pré-requisito para **injetar as DLLs** de forma segura antes que o processo principal do jogo seja executado.
3. **Injeção Dinâmica de DLLs:**
   - Para o modo **SA-MP**, `samp.dll` é injetada.
   - Para o modo **OMP**, `samp.dll` e `omp-client.dll` são injetadas. A injeção é facilitada pela invocação da função `LoadLibraryA` remotamente, permitindo que o GTA: SA carregue os módulos multiplayer e inicialize a conexão.
4. **Configuração de Argumentos:** Argumentos de linha de comando, como **nickname**, **IP do servidor**, **porta** e **senha (se fornecida)**, são preparados e passados para o `gta_sa.exe`.
5. **Retomada do Processo:** Após a **injeção bem-sucedida das DLLs**, o processo do jogo é retomado para execução normal, levando o **GTA:SA** a conectar-se diretamente ao servidor.

### Como Usar (Linha de Comando)

Para utilizar o executável, invoque-o a partir do **Prompt de Comando (CMD)**, **PowerShell** ou **terminal**, fornecendo os parâmetros necessários.

O formato básico é:
```bash
samp-injector.exe <modo> <diretorio_jogo> <nickname> <IP_servidor> <porta_servidor> <senha_servidor (opcional)>
```

#### Modo SA-MP

Para injeção exclusiva de `samp.dll`:
```bash
samp-injector.exe "samp" "C:\Games\GTA San Andreas" "Nome" "127.0.0.1" "7777" "senha (opcional)"
```

#### Modo OMP

Para injeção de `samp.dll` e `omp-client.dll`:
```bash
samp-injector.exe "omp" "C:\Games\GTA San Andreas" "Nome" "127.0.0.1" "7777" "senha (opcional)"
```

#### Parâmetros

- `<modo>`: Define o tipo de injeção.
   - `samp`: Para **SA-MP** (`samp.dll`).
   - `omp`: Para **OMP** (`samp.dll` e `omp-client.dll`).
- `<diretorio_jogo>`: O caminho completo para o diretório do **GTA:SA**. Este diretório deve conter `gta_sa.exe` e os respectivos arquivos de **DLL**.
- `<nickname>`: Seu apelido no jogo (máximo de **20 caracteres**).
- `<IP_servidor>`: O endereço **IP** ou nome de **domínio** do servidor.
- `<porta_servidor>`: A porta de conexão do servidor (um **valor numérico** entre **1** e **65535**).
- `<senha_servidor>`: A senha necessária para conectar-se ao servidor **(se o servidor não tiver senha, não é necessário adicionar esse parâmetro)**.

Caso os argumentos estejam incorretos ou insuficientes, uma mensagem de uso será exibida.

### Como Usar (Embutido em Aplicações)

O `samp-injector.exe` é ideal para integração em aplicações de terceiros, como launchers personalizados, que desejam automatizar o processo de iniciar o jogo com configurações predefinidas.

Exemplo de invocação do `samp-injector.exe` a partir de uma **aplicação C#**:
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
        string password = "senha (opcional)";

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
                    MessageBox.Show($"O SA-MP Injector retornou um erro (Código: {process.ExitCode}). O jogo pode não ter sido iniciado corretamente.", "Erro no Lançamento", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }
        catch (Exception ex) {
            MessageBox.Show($"Ocorreu um erro ao iniciar o jogo: {ex.Message}", "Erro", MessageBoxButtons.OK, MessageBoxIcon.Error);
        }
    }
}
```

### Utilizando a Biblioteca C++ no Executável

O executável `samp-injector.exe` é construído sobre a biblioteca [SA-MP Injector C++](https://github.com/spc-samp/samp-injector/tree/main/libraries/cpp), que reside no diretório `libraries/cpp/`. O `main.cpp` do executável invoca as funcionalidades dessa biblioteca para realizar a injeção e o lançamento do jogo.

O principal arquivo de cabeçalho da biblioteca **C++** a ser incluído é `libraries/samp-injector/cpp/injector.hpp`. Como a biblioteca [SA-MP Injector C++](https://github.com/spc-samp/samp-injector/tree/main/libraries/cpp) é **header-only**, sua utilização requer apenas a inclusão desse cabeçalho no código-fonte, sem a necessidade de linkar um arquivo `.lib`.

O trecho relevante do `main.cpp` que demonstra a integração é o seguinte:
```cpp
// Extrai os argumentos da linha de comando
int argc;
std::unique_ptr<LPWSTR[], decltype(&LocalFree)> argv(CommandLineToArgvW(GetCommandLineW(), &argc), &LocalFree);

// ... (validação do número de argumentos e modo de injeção) ...

// Extrai os parâmetros para as variáveis wide string
std::wstring folder = argv[2];
std::wstring nickname = argv[3];
std::wstring ip = argv[4];
std::wstring port = argv[5];
std::wstring password = (argc == 7) ? argv[6] : L"";

// Delega a lógica de injeção para a função "Initialize_Game" da biblioteca
// Observe que "injector.hpp" foi incluído previamente no "main.cpp"
if (!Initialize_Game(inject_type, folder, nickname, ip, port, password))
    return 1;

Sleep(10000); // Aguarda antes de finalizar o executável
```

A função `Initialize_Game` atua como a interface de alto nível da biblioteca, orquestrando todas as operações de validação, criação de processo e **injeção de DLLs**.

### Como Compilar

Você pode compilar o `samp-injector.exe` a partir do código fonte. Se você não deseja compilar, pode baixar as versões pré-compiladas na seção de [Releases](https://github.com/spc-samp/samp-injector/releases).

#### Requisitos

- **Visual Studio:** Recomenda-se **Visual Studio 2022** ou superior com a **workload "Desenvolvimento para desktop com C++"** instalada.
- **Git:** Para clonar o repositório (ou simplesmente fazer o download acessando este link:  [Donwload](https://github.com/spc-samp/samp-injector/archive/refs/heads/main.zip)).

#### Passos de Compilação

1. **Clone o Repositório:**
   ```bash
   git clone https://github.com/spc-samp/samp-injector.git
   cd samp-injector
   ```
2. **Abra a Solução:**
   Navegue até a pasta `executable` e abra o arquivo de solução `.sln`:
   ```bash
   cd executable
   start samp-injector.sln
   ```
   Isso abrirá o projeto no **Visual Studio**.
3. **Configurar Build:**
   - No **Visual Studio**, verifique a configuração da solução. Recomenda-se utilizar os modos `Release` e `x86` **(32 bits)**. No contexto do **GTA:SA** e **SA-MP**/**OMP**, a **arquitetura x86 (32 bits)** é obrigatória.
4. **Compilar:**
   - No menu `Compilation`, clique em `Compile Solution` ou em `Build samp-injector`.
   - Alternativamente, você pode usar os atalhos:
      - `Ctrl + Shift + B` para compilar a solução completa.
      - `Ctrl + B` (caso esteja configurado) para compilar o projeto atual.
   - Se tudo estiver configurado corretamente, o executável `samp-injector.exe` será gerado no diretório `executable\Release` (ou `executable\Debug`, dependendo da sua configuração de **build**).

## Biblioteca Dinâmica (**DLL**)

A biblioteca `samp-injector.dll` oferece uma **API (Application Programming Interface)** para iniciar o **GTA:SA** com **SA-MP** ou **OMP**, de forma programática. Ela é a alternativa ideal ao executável para desenvolvedores de launchers que desejam uma integração mais limpa e direta, chamando uma função em vez de iniciar um processo externo.

### Funcionalidade

A `samp-injector.dll` aciona o mesmo fluxo de trabalho robusto da biblioteca interna, encapsulando as complexidades de injeção e inicialização do jogo:

1. **Criação de Processo Suspenso:** Ao ser chamada, inicia `gta_sa.exe` em estado suspenso.
2. **Injeção Dinâmica de DLLs:**
   - Para o modo **SA-MP**, `samp.dll` é injetada.
   - Para o modo **OMP**, `samp.dll` e `omp-client.dll` são injetadas.
3. **Configuração de Argumentos:** Os parâmetros da função, como **nickname**, **IP**, **porta** e **senha**, são preparados para o `gta_sa.exe`.
4. **Retomada do Processo:** Após a injeção, o processo do jogo é retomado para execução, conectando-se diretamente ao servidor.

### Como Usar (Chamada de API)

Para utilizar a biblioteca, é necessário carregar a `samp-injector.dll` em sua aplicação e chamar a função `Launch_Game` exportada por ela.

#### Contrato da Função `Launch_Game`

- **Arquivo DLL:** `samp-injector.dll`
- **Nome da Função Exportada:** `Launch_Game`
- **Convenção de Chamada:** `__stdcall`
- **Tipo de Retorno:** `int`
   - `0`: **Sucesso.** A solicitação de inicialização do jogo foi enviada para uma thread em segundo plano.
   - `1`: **Argumentos Inválidos.** Um parâmetro obrigatório era nulo ou o modo era inválido. Uma mensagem de erro será exibida.
   - `2`: **Falha na Thread.** Ocorreu um erro crítico ao tentar criar a thread de inicialização. Uma mensagem de erro será exibida.

#### Parâmetros

Todos os parâmetros são strings de caracteres largos (Unicode).

- `mode` (`LPCWSTR`): Define o tipo de injeção (`L"samp"` ou `L"omp"`).
- `folder` (`LPCWSTR`): O caminho completo para o diretório do **GTA:SA**.
- `nickname` (`LPCWSTR`): Seu apelido no jogo.
- `ip` (`LPCWSTR`): O endereço **IP** ou nome de **domínio** do servidor.
- `port` (`LPCWSTR`): A porta de conexão do servidor.
- `password` (`LPCWSTR`): A senha para conectar ao servidor. **(Este parâmetro é opcional. Pode-se passar `null` ou uma string vazia `L""` se não houver senha)**.

### Como Usar (Embutido em Aplicações)

Exemplo de chamada da função `Launch_Game` a partir de uma **aplicação C#**:
```csharp
using System;
using System.Runtime.InteropServices;
using System.Windows.Forms;

public class Launcher {
    // Importa a função da DLL, especificando o contrato da API.
    [DllImport("samp-injector.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.StdCall, EntryPoint = "Launch_Game")]
    private static extern int Launch_Game(string mode, string folder, string nickname, string ip, string port, string password);

    public static void Main(string[] args) {
        string inject_mode = "samp"; 
        string gta_folder = "C:\\Games\\GTA San Andreas"; // Atenção: Use o caminho real!
        string nickname = "Nome";
        string ip = "127.0.0.1";
        string port = "7777";
        string password = "senha (opcional)"; // ou null, ou "" se não houver

        try {
            int result = Launch_Game(inject_mode, gta_folder, nickname, ip, port, password);
            
            if (result != 0) {
                // A DLL já exibe uma mensagem de erro detalhada,
                // mas você pode logar ou mostrar outra mensagem aqui.
                MessageBox.Show($"A chamada para a DLL retornou um código de erro: {result}", "Erro no Launcher", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }
        catch (DllNotFoundException) {
            MessageBox.Show("Erro: samp-injector.dll não encontrada! Verifique se ela está na mesma pasta do launcher.", "Erro", MessageBoxButtons.OK, MessageBoxIcon.Error);
        }
        catch (Exception ex) {
            MessageBox.Show($"Ocorreu um erro inesperado: {ex.Message}", "Erro", MessageBoxButtons.OK, MessageBoxIcon.Error);
        }
    }
}
```

### Utilizando a Biblioteca C++ na **DLL**

Assim como o executável, a `samp-injector.dll` também é construída sobre a biblioteca [SA-MP Injector C++](https://github.com/spc-samp/samp-injector/tree/main/libraries/cpp), que reside no diretório `libraries/cpp/`. A função exportada `Launch_Game` atua como um invólucro (wrapper), validando os parâmetros e delegando a lógica principal de injeção para a função `Initialize_Game` da biblioteca.

O principal arquivo de cabeçalho da biblioteca **C++** a ser incluído é `libraries/samp-injector/cpp/injector.hpp`. Como a biblioteca [SA-MP Injector C++](https://github.com/spc-samp/samp-injector/tree/main/libraries/cpp) é **header-only**, sua utilização requer apenas a inclusão desse cabeçalho no código-fonte, sem a necessidade de linkar um arquivo `.lib`.

O trecho de código a seguir, do `main.cpp` da **DLL**, demonstra como a tarefa é delegada para ser executada em uma thread separada:
```cpp
// Função worker que roda em uma thread em segundo plano
void Game_Thread_Worker(const std::wstring& mode, const std::wstring& folder, const std::wstring& nickname, const std::wstring& ip, const std::wstring& port, const std::wstring& password) {
    // A lógica de injeção é delegada para a função "Initialize_Game" da biblioteca.
    Initialize_Game(mode, folder, nickname, ip, port, password);
}

// Dentro da função exportada `Launch_Game`, a thread é criada:
try {
    std::thread(Game_Thread_Worker, mode_str, folder_str, nickname_str, ip_str, port_str, password_str).detach();
}
// ...
```

Isso mostra que a **DLL** é, essencialmente, uma interface de API para a mesma funcionalidade central usada pelo executável.

### Como Compilar

Você pode compilar a `samp-injector.dll` a partir do código fonte. Se não deseja compilar, pode baixar as versões pré-compiladas na seção de [Releases](https://github.com/spc-samp/samp-injector/releases).

#### Requisitos

- **Visual Studio:** Recomenda-se **Visual Studio 2022** ou superior com a **workload "Desenvolvimento para desktop com C++"** instalada.
- **Git:** Para clonar o repositório (ou simplesmente fazer o download acessando este link: [Donwload](https://github.com/spc-samp/samp-injector/archive/refs/heads/main.zip)).

#### Passos de Compilação

1. **Clone o Repositório:**
   ```bash
   git clone https://github.com/spc-samp/samp-injector.git
   cd samp-injector
   ```
2. **Abra a Solução:**
   Navegue até a pasta `dll` e abra o arquivo de solução `.sln`:
   ```bash
   cd dll
   start samp-injector.sln
   ```
   Isso abrirá o projeto no **Visual Studio**.
3. **Configurar Build:**
   - No **Visual Studio**, verifique a configuração da solução. Recomenda-se utilizar os modos `Release` e `x86` **(32 bits)**. No contexto do **GTA:SA** e **SA-MP**/**OMP**, a **arquitetura x86 (32 bits)** é obrigatória.
4. **Compilar:**
   - No menu `Compilation`, clique em `Compile Solution` ou em `Build samp-injector`.
   - Alternativamente, você pode usar os atalhos:
      - `Ctrl + Shift + B` para compilar a solução completa.
      - `Ctrl + B` (caso esteja configurado) para compilar o projeto atual.
   - Se tudo estiver configurado corretamente, a biblioteca `samp-injector.dll` será gerada no diretório `dll\Release` (ou `dll\Debug`, dependendo da sua configuração de **build**).

## Bibliotecas

As bibliotecas são os componentes fundamentais do **SA-MP Injector**, contendo a lógica central para manipulação de processos, **injeção de DLLs** e validação de parâmetros. A principal vantagem de usar essas bibliotecas é a facilidade na inicialização e injeção, geralmente através de uma única função (ou chamadas com parâmetros específicos para linguagens de script).

### Visão Geral

O projeto é construído sobre bibliotecas que encapsulam as funcionalidades críticas. Isso permite que outros projetos integrem facilmente a capacidade de iniciar o **GTA:SA** com os módulos **multiplayer** necessários.

### Listagem de Bibliotecas

| Linguagem     | Nome                       | Link para Biblioteca/Documentação           |
| ------------- | -------------------------- | ------------------------------------------- |
| C++           | **SA-MP Injector C++**     | [Conferir Biblioteca](libraries/cpp)        |
| C             | **SA-MP Injector C**       | (Em breve)                                  |
| C#            | **SA-MP Injector C#**      | (Em breve)                                  |
| Java          | **SA-MP Injector Java**    | (Em breve)                                  |
| Python        | **SA-MP Injector Python**  | (Em breve)                                  |
| Go (Golang)   | **SA-MP Injector Go**      | (Em breve)                                  |
| Rust          | **SA-MP Injector Rust**    | (Em breve)                                  |
| Kotlin        | **SA-MP Injector Kotlin**  | (Em breve)                                  |
| Scala         | **SA-MP Injector Scala**   | (Em breve)                                  |
| Lua           | **SA-MP Injector Lua**     | (Em breve)                                  |
| Ruby          | **SA-MP Injector Ruby**    | (Em breve)                                  |
| Visual Basic  | **SA-MP Injector VB**      | (Em breve)                                  |
| F#            | **SA-MP Injector F#**      | (Em breve)                                  |
| Pascal        | **SA-MP Injector Pascal**  | (Em breve)                                  |
| Delphi        | **SA-MP Injector Delphi**  | (Em breve)                                  |
| PowerShell    | **SA-MP Injector PS**      | [Conferir Biblioteca](libraries/powershell) |
| D (Dlang)     | **SA-MP Injector D**       | (Em breve)                                  |
| Nim           | **SA-MP Injector Nim**     | (Em breve)                                  |
| Zig           | **SA-MP Injector Zig**     | (Em breve)                                  |
| V (VLang)     | **SA-MP Injector V**       | (Em breve)                                  |
| Crystal       | **SA-MP Injector Crystal** | (Em breve)                                  |
| Perl          | **SA-MP Injector Perl**    | (Em breve)                                  |
| Racket (Lisp) | **SA-MP Injector Racket**  | (Em breve)                                  |
| Haskell       | **SA-MP Injector Haskell** | (Em breve)                                  |
| OCaml         | **SA-MP Injector OCaml**   | (Em breve)                                  |

> [!TIP]
> A documentação detalhada para cada biblioteca estará disponível em seu **respectivo diretório**.

## Licença

Copyright © **SA-MP Programming Community**

Este software é licenciado sob os termos da Licença MIT ("Licença"); você pode utilizar este software de acordo com as condições da Licença. Uma cópia da Licença pode ser obtida em: [MIT License](https://opensource.org/licenses/MIT)

### Termos e Condições de Uso

#### 1. Permissões Concedidas

A presente licença concede, gratuitamente, a qualquer pessoa que obtenha uma cópia deste software e arquivos de documentação associados, os seguintes direitos:
* Utilizar, copiar, modificar, mesclar, publicar, distribuir, sublicenciar e/ou vender cópias do software sem restrições
* Permitir que pessoas para as quais o software é fornecido façam o mesmo, desde que sujeitas às condições a seguir

#### 2. Condições Obrigatórias

Todas as cópias ou partes substanciais do software devem incluir:
* O aviso de direitos autorais acima
* Este aviso de permissão
* O aviso de isenção de responsabilidade abaixo

#### 3. Direitos Autorais

O software e toda a documentação associada são protegidos por leis de direitos autorais. A **SA-MP Programming Community** mantém a titularidade dos direitos autorais originais do software.

#### 4. Isenção de Garantias e Limitação de Responsabilidade

O SOFTWARE É FORNECIDO "COMO ESTÁ", SEM GARANTIA DE QUALQUER TIPO, EXPRESSA OU IMPLÍCITA, INCLUINDO, MAS NÃO SE LIMITANDO ÀS GARANTIAS DE COMERCIALIZAÇÃO, ADEQUAÇÃO A UM DETERMINADO FIM E NÃO VIOLAÇÃO. 

EM NENHUMA CIRCUNSTÂNCIA OS AUTORES OU TITULARES DOS DIREITOS AUTORAIS SERÃO RESPONSÁVEIS POR QUALQUER REIVINDICAÇÃO, DANOS OU OUTRA RESPONSABILIDADE, SEJA EM AÇÃO DE CONTRATO, DELITO OU DE OUTRA FORMA, DECORRENTE DE, FORA DE OU EM CONEXÃO COM O SOFTWARE OU O USO OU OUTRAS NEGOCIAÇÕES NO SOFTWARE.

---

Para informações detalhadas sobre a Licença MIT, consulte: https://opensource.org/licenses/MIT