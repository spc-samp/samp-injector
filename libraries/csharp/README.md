# SA-MP Injector C#

<div align="center">

![C#](https://img.shields.io/badge/C%23-11.0%2B-512BD4?style=for-the-badge&logo=csharp&logoColor=white)
![.NET](https://img.shields.io/badge/.NET-7.0%2B-512BD4?style=for-the-badge&logo=dotnet&logoColor=white)
![Platform](https://img.shields.io/badge/Platform-Windows-blue?style=for-the-badge&logo=windows&logoColor=white)
![Architecture](https://img.shields.io/badge/Architecture-x86%20(32--bit)-lightgrey?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)

**Uma biblioteca C# para injeção programática de DLLs em processos SA-MP e OMP, permitindo a conexão automatizada a servidores.**

</div>

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

- [SA-MP Injector C#](#sa-mp-injector-c)
  - [Idiomas](#idiomas)
  - [Índice](#índice)
  - [Introdução e Propósito](#introdução-e-propósito)
  - [Filosofia de Design](#filosofia-de-design)
    - [Interoperabilidade (P/Invoke)](#interoperabilidade-pinvoke)
    - [Gerenciamento de Recursos (`SafeHandle`)](#gerenciamento-de-recursos-safehandle)
    - [Segurança e Robustez](#segurança-e-robustez)
  - [Requisitos do Sistema](#requisitos-do-sistema)
    - [Ambiente de Desenvolvimento](#ambiente-de-desenvolvimento)
    - [Ambiente de Execução](#ambiente-de-execução)
  - [Instalação e Uso Básico](#instalação-e-uso-básico)
    - [Adicionando ao Seu Projeto](#adicionando-ao-seu-projeto)
    - [Exemplo de Uso](#exemplo-de-uso)
  - [Componentes da Biblioteca](#componentes-da-biblioteca)
    - [1. `Constants.cs`](#1-constantscs)
    - [2. `InjectionType.cs`](#2-injectiontypecs)
    - [3. `Injector.cs`](#3-injectorcs)
    - [4. `InjectorCore.cs`](#4-injectorcorecs)
    - [5. `InputValidator.cs`](#5-inputvalidatorcs)
    - [6. `NativeImports.cs`](#6-nativeimportscs)
    - [7. `ProcessHandler.cs`](#7-processhandlercs)
    - [8. `SafeHandles.cs`](#8-safehandlescs)
  - [Ciclo de Injeção de DLL Detalhado](#ciclo-de-injeção-de-dll-detalhado)
    - [1. Validação de Entrada](#1-validação-de-entrada)
    - [2. Criação do Processo do Jogo (Suspenso)](#2-criação-do-processo-do-jogo-suspenso)
    - [3. Injeção de `samp.dll`](#3-injeção-de-sampdll)
    - [4. Injeção de `omp-client.dll` (Opcional, Dependente de SA-MP)](#4-injeção-de-omp-clientdll-opcional-dependente-de-sa-mp)
    - [Retomar a Thread Principal do Jogo](#retomar-a-thread-principal-do-jogo)
  - [Tratamento de Erros e Casos de Falha](#tratamento-de-erros-e-casos-de-falha)
    - [Erros de Validação de Entrada](#erros-de-validação-de-entrada)
      - [Nickname Inválido](#nickname-inválido)
      - [Porta Inválida](#porta-inválida)
      - [Arquivos de Jogo/DLLs Ausentes](#arquivos-de-jogodlls-ausentes)
    - [Erros na Criação do Processo](#erros-na-criação-do-processo)
      - [Falha ao Criar o Processo](#falha-ao-criar-o-processo)
    - [Erros na Injeção da DLL](#erros-na-injeção-da-dll)
      - [Handle `kernel32.dll` Indisponível](#handle-kernel32dll-indisponível)
      - [Função `LoadLibraryA` Indisponível](#função-loadlibrarya-indisponível)
      - [Falha na Alocação de Memória Remota](#falha-na-alocação-de-memória-remota)
      - [Falha na Escrita na Memória do Processo](#falha-na-escrita-na-memória-do-processo)
      - [Falha na Criação da Thread Remota](#falha-na-criação-da-thread-remota)
      - [Timeout ou Erro na Espera pela Injeção](#timeout-ou-erro-na-espera-pela-injeção)
      - [Injeção da DLL Falhou ou Retornou Erro](#injeção-da-dll-falhou-ou-retornou-erro)
    - [Erro ao Retomar a Thread do Jogo](#erro-ao-retomar-a-thread-do-jogo)
  - [Licença](#licença)
    - [Termos e Condições de Uso](#termos-e-condições-de-uso)
      - [1. Permissões Concedidas](#1-permissões-concedidas)
      - [2. Condições Obrigatórias](#2-condições-obrigatórias)
      - [3. Direitos Autorais](#3-direitos-autorais)
      - [4. Isenção de Garantias e Limitação de Responsabilidade](#4-isenção-de-garantias-e-limitação-de-responsabilidade)

## Introdução e Propósito

A biblioteca **SA-MP Injector C#** é uma solução em C# projetada para simplificar a inicialização e conexão automatizada de clientes San Andreas Multiplayer (SA-MP) e Open Multiplayer (OMP) a servidores. Ela atua como uma ferramenta de injeção de DLL (Dynamic Link Library), carregando programaticamente as bibliotecas `samp.dll` ou `omp-client.dll` no processo do jogo Grand Theft Auto: San Andreas (`gta_sa.exe`).

O principal objetivo desta biblioteca é permitir que outras aplicações C# (como launchers personalizados, ferramentas de gerenciamento de servidor ou utilitários) possam iniciar o jogo com parâmetros específicos (apelido, IP, porta e senha) de forma transparente para o usuário, automatizando o processo de conexão a um servidor de SA-MP/OMP.

## Filosofia de Design

O design do **SA-MP Injector C#** foca em robustez, segurança e uma interface de uso simplificada, encapsulando as complexidades das operações de baixo nível do sistema.

### Interoperabilidade (P/Invoke)

A funcionalidade central da injeção de DLL e criação de processos suspensos é intrinsecamente uma operação de sistema operacional de baixo nível. Para isso, a biblioteca faz uso extensivo do recurso **P/Invoke (Platform Invoke)** do .NET, permitindo a chamada de funções nativas da API do Windows (principalmente da `kernel32.dll`) diretamente do código C#. Isso é evidente na declaração de métodos `partial` e na utilização do atributo `[LibraryImport(KERNEL32, SetLastError = true)]`.

### Gerenciamento de Recursos (`SafeHandle`)

Operações com recursos do sistema operacional, como "handles" de processos e threads, exigem gerenciamento cuidadoso para evitar vazamentos de memória ou recursos. A biblioteca emprega classes derivadas de `SafeHandle` (`SafeProcessHandle` e `SafeThreadHandle`) para garantir que esses recursos sejam sempre liberados corretamente, mesmo em caso de exceções. Isso adere ao princípio de **RAII (Resource Acquisition Is Initialization)** do C++ e o estende para o ambiente .NET.

### Segurança e Robustez

A biblioteca incorpora várias camadas de segurança:
- **Validação de Entrada:** Todas as entradas fornecidas pelo usuário são rigorosamente validadas antes de qualquer operação crítica ser iniciada, minimizando o risco de erros de runtime ou comportamentos inesperados.
- **Tratamento de Erros:** As chamadas de API nativas são acompanhadas de verificações de erro (`SetLastError = true` e `Marshal.GetLastWin32Error()`) para fornecer mensagens de erro detalhadas e compreensíveis.
- **Finalização de Processo:** Em caso de falha durante o processo de injeção, o processo do jogo recém-criado é automaticamente encerrado para evitar que processos "zumbis" fiquem em execução.

## Requisitos do Sistema

### Ambiente de Desenvolvimento

- **.NET SDK 7.0 ou superior:** A biblioteca é construída para `net7.0-windows`.
- **C# 11.0 ou superior:** Necessário para recursos como `ImplicitUsings`, `Nullable`, `AllowUnsafeBlocks` e `LibraryImport`.
- **Visual Studio 2022 ou ambiente de desenvolvimento compatível:** Para construir e integrar a biblioteca.
- **Plataforma de Compilação:** `x86 (32-bit)` é o alvo obrigatório devido à arquitetura do `gta_sa.exe` e das DLLs SA-MP/OMP.

```xml
<!-- samp-injector-csharp.csproj -->
<Project Sdk="Microsoft.NET.Sdk">
    <PropertyGroup>
        <TargetFrameworks>net7.0-windows</TargetFrameworks>
        <PlatformTarget>x86</PlatformTarget> <!-- CRÍTICO: Deve ser x86 -->
        <ImplicitUsings>enable</ImplicitUsings>
        <Nullable>enable</Nullable>
        <UseWindowsForms>true</UseWindowsForms>
        <AllowUnsafeBlocks>true</AllowUnsafeBlocks> <!-- Necessário para P/Invoke avançado -->
    </PropertyGroup>
</Project>
```

### Ambiente de Execução

- **Sistema Operacional:** Windows (qualquer versão moderna compatível com .NET 7.0+).
- **Grand Theft Auto: San Andreas (GTA: SA):** A instalação do jogo é necessária.
- **SA-MP ou OMP Client DLLs:** `samp.dll` ou `omp-client.dll` devem estar presentes no diretório raiz do jogo, dependendo do tipo de injeção desejado.

## Instalação e Uso Básico

### Adicionando ao Seu Projeto

A forma mais simples de usar esta biblioteca é adicionar o projeto `Samp_Injector_CSharp` como uma referência em seu próprio projeto C#.

1. Clone ou baixe o repositório da biblioteca.
2. No Visual Studio, clique com o botão direito do mouse em "Dependencies" (ou "Referências") no seu projeto.
3. Selecione "Add Project Reference...".
4. Navegue até o diretório da biblioteca e adicione o projeto `samp-injector-csharp.csproj`.

### Exemplo de Uso

Para iniciar o jogo e conectar-se a um servidor, basta chamar o método estático `Injector.Initialize_Game`.

```csharp
using Samp_Injector_CSharp;
using System;
using System.Windows.Forms; // Para MessageBox, se não for um projeto WinForms

namespace Launcher {
    public partial class Main : Form {
        public Main() {
            InitializeComponent();
        }

        private void Connect(object sender, EventArgs e) {
            string inject_type = "SAMP"; // "SAMP" ou "OMP"
            string game_folder = @"C:\Games\GTA San Andreas"; // Caminho para a pasta do GTA: SA
            string nickname = "Nome";
            string ip = "127.0.0.1";
            string port = "7777";
            string password = ""; // Deixe vazio se não houver senha

            // Exemplo de injeção SA-MP
            Injector.Initialize_Game(inject_type, game_folder, nickname, ip, port, password);

            // Se for OMP, altere inject_type:
            // inject_type = "OMP";
            // Injector.Initialize_Game(inject_type, game_folder, nickname, ip, port, password);
        }
    }
}
```

## Componentes da Biblioteca

A biblioteca é estruturada em vários arquivos, cada um com uma responsabilidade clara e bem definida, o que promove a organização, a manutenibilidade e a separação de responsabilidades. A seguir, uma descrição detalhada de cada componente.

### 1. `Constants.cs`

Este arquivo é um repositório centralizado de todas as constantes e valores imutáveis que são utilizados em toda a biblioteca. Sua existência promove a manutenção do código, a legibilidade e a consistência, garantindo que valores críticos sejam definidos em um único local.

A organização das constantes por categoria facilita a compreensão de seu propósito:

- **Game Related Constants**
   - `MIN_PORT`: Define o valor mínimo permitido para a porta de conexão de um servidor (1).
   - `MAX_PORT`: Define o valor máximo permitido para a porta de conexão de um servidor (65535).
   - `MAX_NICKNAME_LENGTH`: Especifica o comprimento máximo permitido para o apelido do jogador (23 caracteres), um limite imposto pelo próprio cliente SA-MP/OMP.

- **File Names**
   - `SAMP_DLL_NAME`: O nome do arquivo da biblioteca principal do cliente SA-MP (`"samp.dll"`).
   - `OMP_DLL_NAME`: O nome do arquivo da biblioteca do cliente Open Multiplayer (`"omp-client.dll"`), utilizada em injeções do tipo OMP.
   - `GAME_EXE_NAME`: O nome do arquivo executável do jogo Grand Theft Auto: San Andreas (`"gta_sa.exe"`).

- **System Libraries and Functions**
   - `KERNEL32_DLL`: O nome da biblioteca do sistema Windows que contém funções essenciais para manipulação de processos e memória (`"kernel32.dll"`).
   - `LOAD_LIBRARY_FUNC`: O nome da função dentro de `kernel32.dll` responsável por carregar dinamicamente uma biblioteca (`"LoadLibraryA"`).

- **Command Line Arguments**
   - `CMD_ARGS_PART1`: Parte inicial dos argumentos de linha de comando para o jogo (`"-c -n "`).
   - `CMD_ARGS_PART2`: Separador para o endereço IP (`" -h "`).
   - `CMD_ARGS_PART3`: Separador para a porta (`" -p "`).
   - `CMD_ARGS_PART4_PASSWORD`: Prefixo para o argumento de senha (`" -z "`), usado apenas se uma senha for fornecida.
   - `CMD_ARGS_BASE_LENGTH`: O comprimento predefinido das partes constantes da linha de comando, excluindo o executável e os valores do usuário (14 caracteres).
   - `CMD_ARG_PASSWORD_LENGTH`: O comprimento do prefixo do argumento de senha (4 caracteres).

- **Error Message Titles**
   - `ERROR_TITLE_SAMP`: Título padrão para caixas de diálogo de erro relacionadas a falhas de SA-MP (`"SA-MP Injector Error - SPC"`).
   - `ERROR_TITLE_OMP`: Título padrão para caixas de diálogo de erro relacionadas a falhas de OMP (`"OMP Injector Error - SPC"`).

- **Process Creation Flags**
   - `CREATE_SUSPENDED`: Flag que instrui o sistema operacional a criar um processo e sua thread principal em um estado suspenso (`0x00000004`). Isso é fundamental para a injeção da DLL antes que o jogo comece a ser executado.
   - `PROCESS_CREATION_FLAGS`: Uma combinação de flags de criação de processo, atualmente definida apenas como `CREATE_SUSPENDED`.

- **Timeouts**
   - `DLL_INJECTION_TIMEOUT_MS`: O tempo máximo (em milissegundos) que a biblioteca aguardará pela conclusão da thread remota responsável pela injeção da DLL (10000ms = 10 segundos).

- **Memory Allocation Flags**
   - `MEM_COMMIT`: Flag que reserva páginas na memória virtual e as "commita" (aloca memória física) (`0x1000`).
   - `MEM_RESERVE`: Flag que apenas reserva um intervalo de espaço de endereço virtual para uso posterior (`0x2000`).
   - `MEM_RELEASE`: Flag que descommita e libera uma região de páginas (`0x8000`).
   - `MEMORY_ALLOCATION_TYPE`: Uma combinação de `MEM_COMMIT` e `MEM_RESERVE`, usada para alocar memória para o caminho da DLL no processo remoto.
   - `MEMORY_PROTECTION`: Define as permissões de proteção de memória (atualmente `0x04`, que corresponde a `PAGE_READWRITE` no Windows API, permitindo leitura e escrita na memória alocada).

### 2. `InjectionType.cs`

Este arquivo define um enumerador simples para fornecer uma forma segura e clara de especificar o tipo de injeção a ser realizada. O uso de um `enum` em vez de strings (`"samp"`, `"omp"`) previne erros de digitação e torna o código mais legível e robusto.

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

Este arquivo é a fachada (Facade) pública da biblioteca, servindo como o único ponto de entrada para aplicações consumidoras. Ele abstrai toda a complexidade interna do processo de injeção em um único método estático.

- **Responsabilidade Principal:** O método `Initialize_Game` recebe todos os parâmetros necessários como strings, determina o tipo de injeção e delega o trabalho para o `Injector_Core`. Ele também é responsável por capturar o resultado da operação e apresentar mensagens de erro ao usuário final através de `MessageBox`, tornando a interação com o usuário final consistente.

```csharp
// Trecho de Injector.cs
public static class Injector {
    private static readonly Injector_Core s_core = new();

    public static void Initialize_Game(string inject_type_str, string folder, string nickname, string ip, string port, string password) {
        // ... Lógica para converter inject_type_str para Injection_Type ...

        if (!s_core.Try_Initialize_Game(type, folder, nickname, ip, port, password, out string error_message)) {
            string error_title = (type == Injection_Type.OMP) ? Constants.ERROR_TITLE_OMP : Constants.ERROR_TITLE_SAMP;
            MessageBox.Show(error_message, error_title, MessageBoxButtons.OK, MessageBoxIcon.Error);
        }
    }
}
```

### 4. `InjectorCore.cs`

Este é o "cérebro" da biblioteca, onde a sequência de operações de injeção é orquestrada. Ele conecta os validadores de entrada com os manipuladores de processo para executar o fluxo de trabalho completo.

- **Responsabilidade Principal:** O método `Try_Initialize_Game` define a lógica passo a passo: valida as entradas, cria o processo do jogo em estado suspenso, injeta as DLLs necessárias (`samp.dll` e, opcionalmente, `omp-client.dll`) e, se tudo for bem-sucedido, retoma a thread do jogo. Um aspecto crucial é o bloco `finally`, que garante que o processo do jogo seja terminado (`Kill()`) em caso de qualquer falha durante as etapas de injeção, evitando processos "zumbis".

```csharp
// Trecho de InjectorCore.cs
internal sealed class Injector_Core {
    public bool Try_Initialize_Game(...) {
        // ... Validação de entrada ...

        using Process_Handler.Process_Info process_info = Process_Handler.Create_Game_Process(...);
        
        // ...
        bool success = false;
        try {
            // ... Injeção de samp.dll ...
            // ... Injeção opcional de omp-client.dll ...
            // ... Retomada da thread do jogo ...
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

Atua como a primeira linha de defesa da biblioteca, garantindo que apenas dados válidos e seguros sejam processados. A validação prévia previne exceções de baixo nível e permite que a biblioteca forneça mensagens de erro claras e acionáveis.

- **Responsabilidade Principal:** O método estático `Try_Validate` executa uma série de verificações, incluindo o formato do apelido, o intervalo numérico da porta e, crucialmente, a existência dos arquivos essenciais (`gta_sa.exe`, `samp.dll`, etc.) no diretório especificado. Se qualquer verificação falhar, ele retorna `false` e preenche uma `out string` com a descrição do erro.

```csharp
// Trecho de InputValidator.cs
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

Este arquivo é a ponte entre o código gerenciado do C# e as APIs nativas não gerenciadas do Windows. Ele utiliza o recurso de interoperabilidade P/Invoke para declarar assinaturas de funções da `kernel32.dll`.

- **Responsabilidade Principal:** Declarar métodos `extern` com os atributos `[LibraryImport]` ou `[DllImport]` que correspondem a funções da API do Windows, como `CreateProcessA`, `VirtualAllocEx` e `CreateRemoteThread`. Ele também define as estruturas de dados (`Startup_Info`, `Process_Information`) com layout de memória compatível com o código nativo. Para otimização, os handles para `kernel32.dll` e o endereço da função `LoadLibraryA` são carregados estaticamente na inicialização.

```csharp
// Trecho de NativeImports.cs
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

É a camada de baixo nível que executa as operações de manipulação de processos. Ele utiliza as funções importadas de `NativeImports.cs` para interagir diretamente com o sistema operacional.

- **Responsabilidades Principais:**
   1. **`Create_Game_Process`**: Constrói a linha de comando e inicia o `gta_sa.exe` com a flag `CREATE_SUSPENDED`.
   2. **`Inject_DLL`**: Implementa a técnica de injeção de DLL através da criação de uma thread remota. Esta é a função mais crítica, orquestrando a alocação de memória, escrita e execução remota de `LoadLibraryA`.
   3. **`Resume_Game_Thread`**: Realiza a etapa final de "descongelar" a thread principal do jogo.

```csharp
// Trecho de ProcessHandler.cs
internal static bool Inject_DLL(SafeProcessHandle process_handle, string dll_path, out string error_message) {
    // ... Alocação e escrita na memória remota ...

    IntPtr remote_thread = Native_Imports.CreateRemoteThread(process_handle, IntPtr.Zero, 0, Native_Imports.load_library_address, remote_memory, 0, IntPtr.Zero);

    if (remote_thread == IntPtr.Zero)
        return (error_message = $"Failed to create a remote thread...") != null && false;
    
    // ... Espera pela conclusão e verifica o resultado ...
    return true;
}
```

### 8. `SafeHandles.cs`

Este arquivo implementa uma prática recomendada de interoperabilidade: o uso de `SafeHandle` para gerenciar recursos não gerenciados. Isso garante que os "handles" de processo e thread do Windows sejam liberados de forma determinística e segura.

- **Responsabilidade Principal:** As classes `SafeProcessHandle` and `SafeThreadHandle` herdam de `SafeHandleZeroOrMinusOneIsInvalid`. Elas encapsulam um `IntPtr` que representa o handle nativo. A principal vantagem é a implementação do método `ReleaseHandle`, que é garantido pelo runtime do .NET para ser chamado quando o objeto é descartado (por exemplo, ao final de um bloco `using`), prevenindo vazamentos de recursos.

```csharp
// Trecho de SafeHandles.cs
internal sealed class SafeProcessHandle : SafeHandleZeroOrminusOneIsInvalid {
    // ... Construtores ...

    protected override bool ReleaseHandle() {
        // Esta chamada é garantida pelo .NET para liberar o handle nativo.
        return Native_Imports.CloseHandle(handle);
    }
}
```

## Ciclo de Injeção de DLL Detalhado

O processo de injeção de DLL é uma sequência de etapas críticas que precisam ser executadas com precisão para serem bem-sucedidas. A biblioteca **SA-MP Injector C#** orquestra isso da seguinte forma:

### 1. Validação de Entrada

Antes de qualquer interação com o sistema, todos os parâmetros fornecidos pelo usuário (caminho da pasta do jogo, apelido, IP, porta e senha) são verificados por `Input_Validator`. Isso inclui:
- Verificar se o apelido está dentro dos limites de comprimento e não está vazio.
- Garantir que a porta seja um número válido e esteja na faixa aceitável (1-65535).
- Confirmar que `gta_sa.exe`, `samp.dll` e `omp-client.dll` (se `Injection_Type` for OMP) existem nos caminhos esperados.

> [!NOTE]
> Essa etapa preventiva é fundamental para evitar falhas inesperadas de API e fornecer feedback claro ao usuário.

### 2. Criação do Processo do Jogo (Suspenso)

A biblioteca utiliza `Native_Imports.CreateProcessA` para iniciar o `gta_sa.exe`. No entanto, um detalhe crucial é o uso da flag `Constants.CREATE_SUSPENDED`.
- **Criação Suspensa:** Esta flag faz com que o Windows crie o processo e sua thread principal, mas a coloca em um estado suspenso, impedindo que o código do jogo comece a ser executado.
- **Linha de Comando:** A linha de comando é cuidadosamente construída por `Process_Handler.Build_Full_Command_Args_ANSI` para incluir todos os parâmetros de conexão do servidor (`-c -n <nickname> -h <ip> -p <port> -z <password>`).
- **Handles de Processo/Thread:** `CreateProcessA` retorna os handles para o processo e a thread principal, que são encapsulados em `SafeProcessHandle` e `SafeThreadHandle` para gerenciamento seguro de recursos.

> [!IMPORTANT]
> A criação suspensa é vital para a injeção. Se o jogo começasse a ser executado antes da injeção, ele poderia inicializar seus próprios mecanismos de segurança ou a `samp.dll`/`omp-client.dll` poderia ser carregada antes do nosso controle, tornando a injeção mais complexa ou ineficaz.

### 3. Injeção de `samp.dll`

Com o processo do jogo suspenso, a função `Process_Handler.Inject_DLL` executa as seguintes etapas:
1. **Obter `LoadLibraryA`:** O endereço da função `LoadLibraryA` (do `kernel32.dll`) no processo do jogo é obtido. Esta é a função que o Windows usa para carregar DLLs.
2. **Alocação de Memória Remota:** `Native_Imports.VirtualAllocEx` é usada para alocar um bloco de memória dentro do espaço de endereço virtual do processo `gta_sa.exe`. O tamanho do bloco é suficiente para armazenar o caminho completo da `samp.dll`.
3. **Escrita do Caminho da DLL:** O caminho completo do arquivo `samp.dll` é gravado na memória recém-alocada no processo do jogo usando `Native_Imports.WriteProcessMemory`.
4. **Criação de Thread Remota:** `Native_Imports.CreateRemoteThread` é chamada para criar uma nova thread no processo `gta_sa.exe`. Esta thread é instruída a executar `LoadLibraryA` com o endereço da string do caminho da DLL como seu único argumento.
5. **Aguardar Conclusão:** A biblioteca aguarda um tempo limite (`Constants.DLL_INJECTION_TIMEOUT_MS`) para que a thread remota conclua sua execução, indicando que `LoadLibraryA` tentou carregar a DLL.
6. **Verificar Resultado:** O código de saída da thread remota é verificado. Se `LoadLibraryA` foi bem-sucedida, ela retorna o endereço base da DLL carregada. Um valor zero ou falha na obtenção do código de saída indica que a injeção falhou.
7. **Limpeza:** A memória remota alocada é liberada (`Native_Imports.VirtualFreeEx`) e o handle da thread remota é fechado (`Native_Imports.CloseHandle`).

### 4. Injeção de `omp-client.dll` (Opcional, Dependente de SA-MP)

> [!TIP]
> A injeção de `omp-client.dll` **sempre ocorre após a injeção bem-sucedida de `samp.dll`**. O cliente OMP utiliza a infraestrutura do SA-MP, portanto, `samp.dll` é um requisito.

Se o `Injection_Type` especificado for `OMP`, a etapa 3 é repetida para injetar a `omp-client.dll`. A lógica é idêntica, garantindo que ambas as bibliotecas necessárias para o OMP sejam carregadas antes do jogo iniciar completamente.

### Retomar a Thread Principal do Jogo

Finalmente, após todas as DLLs necessárias terem sido injetadas com sucesso, a função `Process_Handler.Resume_Game_Thread` é chamada. Esta função utiliza `Native_Imports.ResumeThread` para permitir que a thread principal do `gta_sa.exe` continue sua execução. O jogo agora inicia com as DLLs SA-MP/OMP já carregadas e os argumentos de linha de comando para conexão ao servidor aplicados.

## Tratamento de Erros e Casos de Falha

A biblioteca foi projetada para fornecer feedback claro em caso de falha. A maioria dos erros é capturada e uma `error_message` descritiva é retornada para ser apresentada ao usuário, geralmente por um `MessageBox`.

### Erros de Validação de Entrada

Estes erros ocorrem antes de qualquer operação de sistema e são detectados pelo `Input_Validator`.

#### Nickname Inválido

- **Mensagem de Erro (Exemplo 1):** `"Nickname cannot be empty. Please provide a valid nickname."`
- **Mensagem de Erro (Exemplo 2):** `"Nickname length exceeds the maximum allowed of 23 characters. Please use a shorter nickname."`
- **Por Quê:** O campo de apelido está vazio ou excede o limite máximo de 23 caracteres.
- **Solução:** O usuário deve fornecer um apelido válido e que respeite o limite de caracteres.

#### Porta Inválida

- **Mensagem de Erro (Exemplo 1):** `"Invalid port format. The port must be a numeric value. Please provide a valid integer for the port."`
- **Mensagem de Erro (Exemplo 2):** `"The specified port number (70000) is outside the valid range of 1 to 65535. Please provide a valid port."`
- **Por Quê:** A porta fornecida não é um número inteiro, ou está fora do intervalo válido de 1 a 65535.
- **Solução:** O usuário deve inserir um número de porta válido e dentro do intervalo especificado.

#### Arquivos de Jogo/DLLs Ausentes

- **Mensagem de Erro (Exemplo 1):** `"Game executable not found. Please ensure 'gta_sa.exe' exists at the specified path: C:\Program Files (x86)\Rockstar Games\GTA San Andreas\gta_sa.exe"`
- **Mensagem de Erro (Exemplo 2):** `"SA-MP library not found. Please ensure 'samp.dll' exists at the specified path: C:\Program Files (x86)\Rockstar Games\GTA San Andreas\samp.dll"`
- **Mensagem de Erro (Exemplo 3, OMP):** `"OMP library not found. Please ensure 'omp-client.dll' exists at the specified path for OMP injection: C:\Program Files (x86)\Rockstar Games\GTA San Andreas\omp-client.dll"`
- **Por Quê:** O arquivo executável do jogo (`gta_sa.exe`), a DLL do SA-MP (`samp.dll`) ou a DLL do OMP (`omp-client.dll`) não foram encontrados na pasta do jogo especificada.
- **Solução:** O usuário deve verificar o caminho da pasta do jogo e garantir que todos os arquivos necessários estão presentes.

### Erros na Criação do Processo

Estes erros ocorrem quando a biblioteca tenta iniciar o `gta_sa.exe`.

#### Falha ao Criar o Processo

- **Mensagem de Erro (Exemplo):** `"Failed to create game process. Ensure 'gta_sa.exe' is not running and you have sufficient permissions to execute the file. System Error: Access is denied."`
- **Por Quê:**
   - **Arquivo em Uso:** O `gta_sa.exe` já pode estar em execução, impedindo que uma nova instância seja criada, ou que o sistema operacional tenha um bloqueio sobre o arquivo.
   - **Permissões:** O usuário que executa a aplicação pode não ter permissões suficientes para iniciar um novo processo ou para acessar o executável do jogo.
   - **Caminho Inválido/Corrompido:** Embora a validação básica verifique a existência, pode haver problemas de permissão de leitura/execução ou o executável estar corrompido.
- **Solução:** Certifique-se de que nenhuma outra instância de `gta_sa.exe` esteja em execução. Execute a aplicação como administrador, se possível. Verifique a integridade do arquivo `gta_sa.exe`.

### Erros na Injeção da DLL

Estes são os erros mais críticos e ocorrem durante a tentativa de injetar `samp.dll` ou `omp-client.dll` no processo do jogo.

#### Handle `kernel32.dll` Indisponível

- **Mensagem de Erro:** `"Failed to obtain a handle to kernel32.dll. This is an essential system library and this error indicates a severe system issue."`
- **Por Quê:** A biblioteca `kernel32.dll`, fundamental para operações de sistema no Windows, não pôde ser carregada ou seu handle não pôde ser obtido. Isso é extremamente raro e sugere um problema grave no sistema operacional.
- **Solução:** Reiniciar o sistema pode resolver. Caso contrário, indica um problema mais profundo com a instalação do Windows.

#### Função `LoadLibraryA` Indisponível

- **Mensagem de Erro:** `"Failed to find the address of the LoadLibraryA function in kernel32.dll. This is critical for injecting the DLL."`
- **Por Quê:** A função `LoadLibraryA`, essencial para carregar DLLs dinamicamente, não pôde ser encontrada em `kernel32.dll`. Assim como o erro anterior, é um problema de baixo nível raro.
- **Solução:** Similar à indisponibilidade do handle de `kernel32.dll`.

#### Falha na Alocação de Memória Remota

- **Mensagem de Erro:** `"Failed to allocate memory in the target process. This might be due to insufficient permissions or process protection mechanisms."`
- **Por Quê:** A biblioteca não conseguiu alocar um bloco de memória no espaço de endereço do `gta_sa.exe`.
   - **Permissões:** A aplicação pode não ter as permissões necessárias para modificar o espaço de memória de outro processo.
   - **Proteção do Processo:** O processo `gta_sa.exe` ou o sistema operacional pode estar aplicando proteções contra injeção de código.
   - **Espaço de Endereço:** Em casos extremos, o espaço de endereço do processo pode estar fragmentado ou sem memória contígua suficiente, embora improvável para o tamanho de uma string de caminho de DLL.
- **Solução:** Execute a aplicação como administrador. Verifique se há software de segurança (antivírus, anti-cheat) que possa estar bloqueando a alocação de memória em outros processos.

#### Falha na Escrita na Memória do Processo

- **Mensagem de Erro:** `"Failed to write DLL path to the target process memory. Verify process permissions and ensure the DLL path is accessible."`
- **Por Quê:** A biblioteca alocou memória no processo do jogo, mas não conseguiu gravar o caminho da DLL nesse local.
   - **Permissões:** Semelhante à falha de alocação de memória, pode ser um problema de permissão de escrita.
   - **Proteção:** Proteção de memória do sistema operacional ou anti-cheat pode estar impedindo a gravação.
- **Solução:** Verifique permissões e software de segurança.

#### Falha na Criação da Thread Remota

- **Mensagem de Erro (Exemplo):** `"Failed to create a remote thread in the target process to execute the DLL injection. This could be due to security restrictions or process state. System Error: Not enough memory resources are available to process this command."`
- **Por Quê:** A API `CreateRemoteThread` falhou ao criar uma nova thread no processo `gta_sa.exe` para chamar `LoadLibraryA`.
   - **Proteção de Processo/Anti-Cheat:** Muitos sistemas anti-cheat e proteções de sistema operacional monitoram e bloqueiam a criação de threads remotas, pois é uma técnica comum de injeção.
   - **Estado do Processo:** O processo do jogo pode estar em um estado inconsistente que impede a criação de threads.
- **Solução:** Desative temporariamente qualquer software anti-cheat ou antivírus. Tente executar a aplicação como administrador.

#### Timeout ou Erro na Espera pela Injeção

- **Mensagem de Erro (Exemplo):** `"Timeout or error waiting for DLL injection to complete. System Error: The wait operation timed out."`
- **Por Quê:** A thread remota (que chama `LoadLibraryA`) não terminou sua execução dentro do tempo limite especificado (10 segundos).
   - **Congelamento:** `LoadLibraryA` pode ter travado ou demorado excessivamente.
   - **Bloqueio:** Algum mecanismo de segurança pode ter interceptado e bloqueado a execução de `LoadLibraryA` indefinidamente.
- **Solução:** Pode indicar que a DLL está demorando muito para carregar ou que algo a está impedindo. Verificar logs do sistema ou do próprio SA-MP/OMP (se existirem) pode ajudar.

#### Injeção da DLL Falhou ou Retornou Erro

- **Mensagem de Erro:** `"DLL injection failed or returned an error. The LoadLibrary call may have failed in the target process."`
- **Por Quê:** A thread remota foi concluída, mas o código de saída de `LoadLibraryA` indicou falha (geralmente `0` ou `NULL`).
   - **DLL Inexistente/Corrompida:** Apesar da validação inicial, a DLL pode ter sido movida ou corrompida entre a validação e a injeção.
   - **Dependências da DLL Ausentes:** A `samp.dll` ou `omp-client.dll` pode depender de outras DLLs que não estão presentes no diretório do jogo ou no PATH do sistema.
   - **Erro Interno da DLL:** A própria DLL pode ter um erro interno que a impede de carregar corretamente.
- **Solução:** Verifique a integridade da `samp.dll`/`omp-client.dll`. Certifique-se de que todas as dependências da DLL estejam presentes.

### Erro ao Retomar a Thread do Jogo

Este é o último erro possível no ciclo de injeção.

- **Mensagem de Erro (Exemplo):** `"Failed to resume the game process thread: Invalid handle."`
- **Por Quê:** A API `ResumeThread` falhou ao reiniciar a thread principal do `gta_sa.exe`.
   - **Handle Inválido:** O handle da thread pode ter sido invalidado por algum motivo.
   - **Problema de Permissão:** A aplicação pode não ter permissão para modificar o estado da thread.
- **Solução:** Tente executar a aplicação como administrador. Se persistir, pode indicar um problema mais profundo de estabilidade do sistema ou do processo do jogo.

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