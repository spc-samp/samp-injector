# SA-MP Injector C++

<div align="center">

![C++](https://img.shields.io/badge/C%2B%2B-14%2F17%2F20-00599C?style=for-the-badge&logo=cplusplus)
![Platform](https://img.shields.io/badge/Platform-Windows-blue?style=for-the-badge&logo=windows&logoColor=white)
![Architecture](https://img.shields.io/badge/Architecture-x86%20(32--bit)-lightgrey?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)

**Uma biblioteca C++ para iniciar e automatizar a conexão de clientes SA-MP e OMP a servidores, via injeção de DLLs.**

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

- [SA-MP Injector C++](#sa-mp-injector-c)
  - [Idiomas](#idiomas)
  - [Índice](#índice)
  - [Visão Geral e Propósito](#visão-geral-e-propósito)
  - [Princípios de Design](#princípios-de-design)
    - [Totalmente `Header-Only`](#totalmente-header-only)
    - [Gestão Segura de Recursos (RAII)](#gestão-segura-de-recursos-raii)
    - [Robustez e Verificação de Erros](#robustez-e-verificação-de-erros)
    - [Flexibilidade de Padrões C++](#flexibilidade-de-padrões-c)
  - [Ambiente Necessário](#ambiente-necessário)
    - [Para Desenvolvimento](#para-desenvolvimento)
    - [Para Execução](#para-execução)
  - [Início Rápido](#início-rápido)
    - [Integração ao Projeto](#integração-ao-projeto)
    - [Exemplo de Uso Simplificado](#exemplo-de-uso-simplificado)
  - [Estrutura da Biblioteca](#estrutura-da-biblioteca)
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
  - [O Processo Detalhado de Injeção](#o-processo-detalhado-de-injeção)
    - [1. Solicitação de Inicialização](#1-solicitação-de-inicialização)
    - [2. Preparação do Ambiente](#2-preparação-do-ambiente)
    - [3. Verificação de Integridade e Parâmetros](#3-verificação-de-integridade-e-parâmetros)
    - [4. Preparação dos Argumentos para o Jogo](#4-preparação-dos-argumentos-para-o-jogo)
    - [5. Inicialização do Processo do Jogo (Suspenso)](#5-inicialização-do-processo-do-jogo-suspenso)
    - [6. Injeção da Biblioteca SA-MP (`samp.dll`)](#6-injeção-da-biblioteca-sa-mp-sampdll)
    - [7. Injeção da Biblioteca OMP (`omp-client.dll`) - Condicional](#7-injeção-da-biblioteca-omp-omp-clientdll---condicional)
    - [8. Ativação do Jogo](#8-ativação-do-jogo)
  - [Diagnóstico de Erros e Falhas](#diagnóstico-de-erros-e-falhas)
    - [Falhas de Validação de Entrada](#falhas-de-validação-de-entrada)
      - [Nome de Usuário Inválido](#nome-de-usuário-inválido)
      - [Porta de Conexão Inválida](#porta-de-conexão-inválida)
      - [Recursos Essenciais Ausentes](#recursos-essenciais-ausentes)
    - [Falhas na Gestão do Processo](#falhas-na-gestão-do-processo)
      - [Dificuldade ao Iniciar o Processo do Jogo](#dificuldade-ao-iniciar-o-processo-do-jogo)
    - [Problemas na Injeção da DLL](#problemas-na-injeção-da-dll)
      - [Impossível Localizar `LoadLibraryW`](#impossível-localizar-loadlibraryw)
      - [Falha na Reserva de Memória Remota](#falha-na-reserva-de-memória-remota)
      - [Incapacidade de Gravar Dados no Processo](#incapacidade-de-gravar-dados-no-processo)
      - [Falha ao Criar Thread de Injeção](#falha-ao-criar-thread-de-injeção)
      - [Tempo Limite Excedido ou Erro na Espera pela Injeção](#tempo-limite-excedido-ou-erro-na-espera-pela-injeção)
      - [Falha Interna na Injeção da DLL](#falha-interna-na-injeção-da-dll)
    - [Dificuldade ao Retomar a Execução do Jogo](#dificuldade-ao-retomar-a-execução-do-jogo)
  - [Licença](#licença)
    - [Termos e Condições de Uso](#termos-e-condições-de-uso)
      - [1. Permissões Concedidas](#1-permissões-concedidas)
      - [2. Condições Obrigatórias](#2-condições-obrigatórias)
      - [3. Direitos Autorais](#3-direitos-autorais)
      - [4. Isenção de Garantias e Limitação de Responsabilidade](#4-isenção-de-garantias-e-limitação-de-responsabilidade)

## Visão Geral e Propósito

O **SA-MP Injector C++** é uma biblioteca C++ compacta e de fácil integração, projetada para automatizar o processo de inicialização e conexão a servidores de San Andreas Multiplayer (SA-MP) e Open Multiplayer (OMP). Diferentemente de iniciar o `gta_sa.exe` diretamente, esta solução carrega programaticamente as bibliotecas `samp.dll` ou `omp-client.dll` no processo do jogo Grand Theft Auto: San Andreas de forma controlada.

Seu objetivo principal é capacitar desenvolvedores C++ a criar `launchers` personalizados, ferramentas de gerenciamento de comunidade ou utilitários que necessitem iniciar o GTA:SA com parâmetros de conexão predefinidos (como nome de usuário, endereço IP, porta e senha), oferecendo uma experiência de usuário fluida e automatizada.

## Princípios de Design

A arquitetura do **SA-MP Injector C++** é fundamentada em princípios de design modernos, focando em segurança, eficiência e facilidade de uso.

### Totalmente `Header-Only`

Esta biblioteca é distribuída exclusivamente através de arquivos de cabeçalho (`.hpp`). Isso simplifica drasticamente a integração em projetos C++, eliminando a necessidade de compilar bibliotecas separadas, configurar `linkers` ou gerenciar dependências de binários.
- **Integração Instantânea:** Basta incluir os `headers` relevantes.
- **Otimização Profunda:** O compilador pode realizar `inlining` agressivo e otimizações de `link-time` que resultam em um código final mais compacto e veloz.

### Gestão Segura de Recursos (RAII)

A biblioteca emprega o padrão **RAII (Resource Acquisition Is Initialization)** de forma extensiva. Recursos críticos do sistema, como `handles` de processos e `threads` do Windows, são encapsulados por `std::unique_ptr` com `deleters` personalizados. Isso assegura que, independentemente do fluxo de execução ou da ocorrência de exceções, os recursos sejam sempre liberados corretamente, prevenindo vazamentos e melhorando a estabilidade da aplicação.

### Robustez e Verificação de Erros

Cada etapa crítica da injeção é precedida por validações rigorosas e seguida por verificações de erros da API do Windows. Mensagens de erro detalhadas são fornecidas ao usuário final através de caixas de diálogo, com descrições do sistema (`GetLastError()`) sempre que possível. Essa abordagem minimiza a chance de comportamentos indefinidos e oferece um diagnóstico claro em caso de falha.

### Flexibilidade de Padrões C++

A biblioteca foi construída para ser compatível com diferentes padrões C++, do C++14 ao C++20. Isso é alcançado através de macros condicionais que permitem a utilização de recursos modernos (como `std::string_view`, `std::filesystem` e `std::optional` do C++17+) quando disponíveis, enquanto mantém um `fallback` para construções equivalentes em C++14. Essa abordagem garante ampla compatibilidade sem sacrificar a modernidade.

## Ambiente Necessário

### Para Desenvolvimento

- **Compilador C++:** Compatível com **C++14 ou superior**.
   - Microsoft Visual C++ (Visual Studio 2015, 2017, 2019, 2022)
   - GCC (versão 5 ou mais recente)
   - Clang (versão 3.6 ou mais recente)
- **Sistema Operacional:** **Windows**.
- **Windows SDK:** Necessário para acesso às APIs do sistema operacional.
- **Arquitetura de Compilação:** **x86 (32-bit)**. Esta é uma exigência estrita, pois o `gta_sa.exe` e as DLLs SA-MP/OMP operam exclusivamente nesta arquitetura.

### Para Execução

- **Sistema Operacional:** Qualquer versão moderna do **Windows** compatível com o binário compilado.
- **Grand Theft Auto: San Andreas (GTA:SA):** Uma instalação válida do jogo é obrigatória.
- **DLLs do Cliente SA-MP ou OMP:** Os arquivos `samp.dll` ou `omp-client.dll` devem estar presentes no diretório raiz do jogo, correspondendo ao tipo de injeção desejado.

## Início Rápido

A natureza `header-only` da biblioteca facilita sua incorporação em qualquer projeto C++.

### Integração ao Projeto

1. **Baixe os Headers:** Obtenha os arquivos `.hpp` da biblioteca (clonando o repositório ou baixando-os diretamente).
2. **Organize os Arquivos:** Recomenda-se criar uma subpasta no seu projeto para os `headers` da biblioteca, por exemplo, `MeuProjeto/libraries/samp-injector/`.
3. **Defina a Arquitetura:** Configure seu projeto para compilar para a arquitetura **x86 (32-bit)**.

```cpp
// Exemplo de estrutura de diretórios
MeuProjeto/
├── src/
│   └── main.cpp
├── libraries/
│   └── samp-injector/
│       ├── constants.hpp
│       ├── error_utils.hpp
│       ├── injector.hpp // O cabeçalho principal a ser incluído
│       └── ... (outros cabeçalhos)
└── built/ (seu diretório de saída)
```

### Exemplo de Uso Simplificado

Para automatizar a conexão a um servidor, basta invocar a função `Initialize_Game` e fornecer os detalhes.

```cpp
#include <iostream>
#include <string>
//
#include "samp-launcher/injector.hpp" // Inclua o cabeçalho principal

int main() {
    // Parâmetros para a inicialização do jogo e conexão
    std::wstring inject_type = L"samp"; // Ou L"omp" para Open Multiplayer
    std::wstring game_folder = L"C:\\Games\\GTA San Andreas"; // Caminho completo da pasta do GTA:SA
    std::wstring nickname = L"Nome";
    std::wstring ip = L"127.0.0.1";
    std::wstring port = L"7777";
    std::wstring password = L""; // Deixe vazio se não houver senha

    // A chamada principal para iniciar o jogo e injetar a DLL
    Initialize_Game(inject_type, game_folder, nickname, ip, port, password);

    // Em caso de falha, uma caixa de mensagem de erro do Windows é exibida automaticamente.

    return 0;
}
```

## Estrutura da Biblioteca

A biblioteca é cuidadosamente modularizada em diversos arquivos de cabeçalho, cada um com responsabilidades bem definidas, facilitando a organização, manutenção e reusabilidade.

### 1. `constants.hpp`

Este arquivo é o **repositório central** da biblioteca, servindo como um repositório centralizado de todos os valores fixos e inalteráveis que ditam o comportamento e a interoperabilidade do **SA-MP Injector C++**. Sua organização por categorias lógicas promove não apenas a clareza e a legibilidade do código, mas também facilita a manutenção e garante uma consistência rigorosa em todo o ecossistema da biblioteca.

Cada constante é definida com `CONSTEXPR_VAR`, que se expande para `inline constexpr` (para C++17+) ou `static constexpr` (para C++14), assegurando que esses valores sejam avaliados em tempo de compilação, otimizando o desempenho e a segurança de tipo.

A organização das constantes por categoria facilita a compreensão de seu propósito:

- **Constantes Relacionadas ao Jogo (`Game Related Constants`)**
   - `MIN_PORT`: Um `int` que define o menor número de porta válido para conexão a um servidor (valor: `1`).
   - `MAX_PORT`: Um `int` que estabelece o maior número de porta válido para conexão a um servidor (valor: `65535`).
   - `MAX_NICKNAME_LENGTH`: Um `int` que especifica o comprimento máximo permitido para o nickname do jogador (valor: `23` caracteres), um limite imposto pelas especificações do cliente SA-MP/OMP.

- **Nomes de Arquivos Essenciais (`File Names`)**
   - `SAMP_DLL_NAME`: Um `const wchar_t*` que contém o nome do arquivo da biblioteca principal do cliente SA-MP (valor: `L"samp.dll"`). Essencial para a injeção do cliente clássico.
   - `OMP_DLL_NAME`: Um `const wchar_t*` que contém o nome do arquivo da biblioteca do cliente Open Multiplayer (valor: `L"omp-client.dll"`). Utilizado especificamente quando a injeção é do tipo OMP.
   - `GAME_EXE_NAME`: Um `const wchar_t*` que armazena o nome do arquivo executável do jogo base Grand Theft Auto: San Andreas (valor: `L"gta_sa.exe"`). O alvo principal da injeção.

- **APIs e Funções do Sistema (`System Libraries and Functions`)**
   - `KERNEL32_DLL`: Um `const wchar_t*` que define o nome da biblioteca de sistema do Windows (`L"kernel32.dll"`). Esta DLL é vital, pois hospeda as funções de manipulação de processos e memória que o injetor utiliza. O uso de `wchar_t` garante compatibilidade com as funções de API que manipulam caracteres largos, como `GetModuleHandleW`.
   - `LOAD_LIBRARY_FUNC`: Um `const char*` com o nome da função para carregar uma DLL dinamicamente (valor: `"LoadLibraryW"`). Embora a biblioteca opere primariamente com caracteres largos, a função `GetProcAddress` da API do Windows requer um nome de função em formato ANSI (`char*`).

- **Argumentos de Linha de Comando (`Command Line Arguments`)**
   - Estas constantes definem os prefixos para os argumentos que são passados ao `gta_sa.exe` para configurar a conexão do cliente. São fornecidas em `Wide Character` (`const wchar_t*`) para compatibilidade com `CreateProcessW`.
      - `CMD_ARG_CONFIG`: Argumento para configurações gerais (valor: `L"-c"`).
      - `CMD_ARG_NICKNAME`: Argumento para o nickname do jogador (valor: `L"-n"`).
      - `CMD_ARG_HOST`: Argumento para o endereço IP do servidor (valor: `L"-h"`).
      - `CMD_ARG_PORT`: Argumento para a porta do servidor (valor: `L"-p"`).
      - `CMD_ARG_PASSWORD`: Argumento para a senha do servidor (valor: `L"-z"`). Utilizado apenas se uma senha for fornecida.

- **Identificadores de Tipo de Injeção (`Injection types as strings`)**
   - `INJECT_TYPE_SAMP`: Um `const wchar_t*` para a representação em string do tipo de injeção SA-MP (valor: `L"samp"`).
   - `INJECT_TYPE_OMP`: Um `const wchar_t*` para a representação em string do tipo de injeção OMP (valor: `L"omp"`).

- **Títulos para Mensagens de Erro (`Error message titles`)**
   - `ERROR_TITLE_SAMP`: Um `const wchar_t*` que define o título padrão para caixas de diálogo de erro relacionadas a falhas de SA-MP (valor: `L"SA-MP Injector Error - SPC"`).
   - `ERROR_TITLE_OMP`: Um `const wchar_t*` que define o título padrão para caixas de diálogo de erro relacionadas a falhas de OMP (valor: `L"OMP Injector Error - SPC"`).

- **Flags de Criação de Processo (`Process creation`)**
   - `PROCESS_CREATION_FLAGS`: Um `DWORD` que encapsula as bandeiras passadas para `CreateProcessW`. Crucialmente, inclui `CREATE_SUSPENDED` (`0x00000004`), que inicia o processo do jogo em um estado pausado, e `DETACHED_PROCESS` (`0x00000008`), que desvincula o novo processo do console do processo pai.

- **Tempos Limite (`Timeouts`)**
   - `DLL_INJECTION_TIMEOUT_MS`: Um `DWORD` que especifica o tempo máximo (em milissegundos) que a biblioteca aguardará pela conclusão da `thread` remota responsável pela injeção da DLL (valor: `10000ms`, ou 10 segundos).

- **Flags de Alocação de Memória (`Memory allocation`)**
   - Estas constantes são utilizadas para as chamadas de API de manipulação de memória, como `VirtualAllocEx` e `VirtualProtect`.
      - `MEM_COMMIT`: Um `DWORD` que reserva páginas na memória virtual e as "commita" (aloca memória física) (valor: `0x1000`).
      - `MEM_RESERVE`: Um `DWORD` que apenas reserva um intervalo de espaço de endereço virtual para uso posterior (valor: `0x2000`).
      - `MEM_RELEASE`: Um `DWORD` que descommita e libera uma região de páginas (valor: `0x8000`).
      - `MEMORY_ALLOCATION_TYPE`: Uma combinação de `MEM_COMMIT` e `MEM_RESERVE`, usada para alocar a memória inicial para o caminho da DLL no processo remoto.
      - `MEMORY_PROTECTION`: Um `DWORD` que define as permissões de proteção de memória (valor: `PAGE_READWRITE` ou `0x04` no Windows API), permitindo leitura e escrita na memória alocada.

### 2. `types.hpp`

Este arquivo conciso introduz um `enum class` para tipificar as diferentes modalidades de injeção. A utilização de um tipo enumerado, ao invés de strings literais, eleva a segurança do código, previne erros de digitação e melhora a legibilidade.

- **`Inject_Type`:** Um `enum class` com dois membros: `SAMP` e `OMP`, representando os tipos de cliente a serem injetados.

```cpp
// Exemplo de types.hpp
namespace Types {
    enum class Inject_Type {
        SAMP, // Indica injeção para o cliente SA-MP
        OMP // Indica injeção para o cliente Open Multiplayer
    };
}
```

### 3. `version.hpp`

Atuando como um adaptador de compatibilidade, este cabeçalho detecta dinamicamente o padrão C++ em uso pelo compilador. Ele define macros condicionais (`SAMP_INJECTOR_CXX_14`, `SAMP_INJECTOR_CXX_MODERN`) que guiam a biblioteca a empregar as funcionalidades mais avançadas do C++ (como `std::string_view` ou `std::filesystem`) quando disponíveis, enquanto assegura total funcionalidade em ambientes C++14.

- **`SAMP_INJECTOR_CXX_14`:** Definida se o padrão C++ for C++14.
- **`SAMP_INJECTOR_CXX_MODERN`:** Definida para C++17 ou superior, habilitando recursos de linguagem mais recentes.
- **`SAMP_INJECTOR_NODISCARD`:** Adapta o atributo `[[nodiscard]]` para as versões de C++ que o suportam, incentivando a verificação de valores de retorno.

```cpp
// Exemplo de trecho relevante de version.hpp
#if (defined(_MSC_VER) && _MSVC_LANG >= 201703L) || __cplusplus >= 201703L
    #define SAMP_INJECTOR_CXX_MODERN // Habilita recursos modernos de C++17+
#endif

#if defined(SAMP_INJECTOR_CXX_MODERN)
    #define SAMP_INJECTOR_NODISCARD [[nodiscard]] // Usa o atributo nodiscard de C++17
#elif defined(SAMP_INJECTOR_CXX_14)
    #define SAMP_INJECTOR_NODISCARD // Para C++14, o atributo é desativado
#endif
```

### 4. `error_utils.hpp`

Este utilitário é dedicado à gestão e apresentação de feedback de erro. Ele abstrai os mecanismos do Windows para recuperar mensagens de erro do sistema e oferece uma interface unificada para notificar o usuário sobre problemas.

- **`Get_System_Error_Message`:** Traduz um código de erro do Windows (`GetLastError()`) em uma `std::wstring` legível, crucial para o diagnóstico preciso.
- **`Show_Error`:** Apresenta uma caixa de diálogo (`MessageBoxW`) contendo a mensagem de erro fornecida, com um título específico para SA-MP ou OMP, garantindo uma comunicação clara com o usuário.

```cpp
// Exemplo de trecho relevante de error_utils.hpp
namespace Error_Utils {
    SAMP_INJECTOR_NODISCARD
    inline std::wstring Get_System_Error_Message(DWORD error_code) {
        if (error_code == 0)
            return L"No error occurred.";
        
        // ... Lógica para formatar a mensagem do sistema ...
    }

    inline void Show_Error(std::wstring_view message, Types::Inject_Type inject_type) {
        const std::wstring title = (inject_type == Types::Inject_Type::SAMP) ? Constants::ERROR_TITLE_SAMP : Constants::ERROR_TITLE_OMP;
        MessageBoxW(nullptr, message.data(), title.c_str(), MB_OK | MB_ICONERROR);
    }
}
```

### 5. `validation.hpp`

Atuando como a linha de frente da robustez da biblioteca, este cabeçalho fornece rotinas rigorosas para verificar a validade dos dados de entrada e a presença dos arquivos necessários. Estas verificações são realizadas antes de qualquer interação de baixo nível com o sistema, mitigando riscos de `runtime` e fornecendo feedback proativo.

- **`Validate_Port`:** Valida se a string da porta representa um número inteiro e se este se encontra dentro do intervalo configurado (`MIN_PORT` a `MAX_PORT`).
- **`Validate_Nickname`:** Verifica se o nickname não está vazio e se sua extensão não excede o `MAX_NICKNAME_LENGTH`.
- **`Validate_Files`:** Confirma a existência física de `gta_sa.exe`, `samp.dll` e, condicionalmente para injeção OMP, `omp-client.dll`. A implementação se adapta a `std::filesystem` (C++17+) ou `GetFileAttributesW` (C++14).

```cpp
// Exemplo de trecho relevante de validation.hpp
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
        
        // ... Outras verificações de arquivos ...
        return true;
    }
}
```

### 6. `resource_handle.hpp`

Implementa uma estratégia elegante e segura para o gerenciamento de recursos do sistema operacional, como os `HANDLE`s do Windows. Utilizando o princípio RAII, garante que todos os recursos alocados sejam devidamente liberados, prevenindo vazamentos e fortalecendo a estabilidade da aplicação.

- **`Unique_Resource`:** Um `alias template` que adapta `std::unique_ptr` para trabalhar com `deleters` personalizados, permitindo o gerenciamento de qualquer tipo de recurso que necessite de uma função de liberação específica.
- **`Make_Unique_Handle`:** Uma função `factory` conveniente que constrói e retorna um `Unique_Resource` pré-configurado para `HANDLE`s do Windows. O `deleter` associado invoca `CloseHandle` automaticamente quando o `Unique_Resource` sai de escopo, garantindo a desocupação imediata do recurso.

```cpp
// Exemplo de trecho relevante de resource_handle.hpp
namespace Resource_Handle {
    // Um std::unique_ptr personalizado para gerenciar recursos do sistema.
    template<typename T, typename Deleter>
    using Unique_Resource = std::unique_ptr<std::remove_pointer_t<T>, Deleter>;

    // Cria um Unique_Resource para um HANDLE, com um deleter que chama CloseHandle.
    template<typename T>
    inline auto Make_Unique_Handle(T handle) {
        return Unique_Resource<T, std::function<void(T)>>(handle, [](T h) {
            if (h && h != INVALID_HANDLE_VALUE) // Garante que o handle seja válido antes de fechar
                CloseHandle(h);
        });
    }
}
```

### 7. `privileges.hpp`

Este componente é responsável por configurar o ambiente de segurança do processo da aplicação. Ele contém a funcionalidade para elevar os privilégios, especificamente habilitando o privilégio de depuração (`SE_DEBUG_NAME`), que é um requisito fundamental para que a biblioteca possa realizar operações de injeção de DLL em processos externos do Windows.

- **`Enable_Debug_Privilege`:** Esta função tenta adquirir e ativar o privilégio `SE_DEBUG_NAME` para o processo em execução. É uma etapa inicial crucial para conceder à aplicação as permissões necessárias para manipular outros processos, como alocar memória e criar `threads` remotas. Retorna `true` em caso de sucesso.

```cpp
// Exemplo de trecho relevante de privileges.hpp
namespace Privileges {
    inline bool Enable_Debug_Privilege() {
        HANDLE token_handle;

        // Tenta abrir o token do processo atual para ajustar privilégios
        if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &token_handle))
            return false;

        auto handle_guard = Resource_Handle::Make_Unique_Handle(token_handle); // Gerenciamento seguro do handle

        TOKEN_PRIVILEGES tp;
        LUID luid;

        // Procura o valor LUID para o privilégio SE_DEBUG_NAME
        if (!LookupPrivilegeValue(nullptr, SE_DEBUG_NAME, &luid))
            return false;
        
        tp.PrivilegeCount = 1;
        tp.Privileges[0].Luid = luid;
        tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED; // Habilita o privilégio

        // Ajusta os privilégios do processo
        if (!AdjustTokenPrivileges(token_handle, FALSE, &tp, sizeof(TOKEN_PRIVILEGES), nullptr, nullptr))
            return false;

        return GetLastError() == ERROR_SUCCESS; // Retorna true se a operação foi bem-sucedida (nenhum erro pendente)
    }
}
```

### 8. `process.hpp`

Este é um dos componentes mais críticos da biblioteca, contendo a implementação de baixo nível para interagir com processos do Windows. Ele encapsula as complexas operações de criação do processo do jogo, alocação de memória, escrita de dados e a técnica de injeção de DLL através da criação de `threads` remotas.

- **`Process_Info` struct:** Uma estrutura interna que armazena os `Unique_Resource`s para o `HANDLE` do processo (`process_handle`) e do `HANDLE` da `thread` principal (`thread_handle`) do jogo. Inclui um método `Resume()` para reativar a `thread` principal do jogo quando a injeção estiver completa.
- **`Injection_Status` enum class:** Define uma lista detalhada de resultados possíveis para a operação de injeção de DLL, permitindo um diagnóstico preciso de falhas.
- **`Create_Game_Process`:**
   - Utiliza a função `CreateProcessW` da API do Windows para iniciar o executável `gta_sa.exe`.
   - É fundamental que o processo seja criado com a flag `CREATE_SUSPENDED` (incluída em `Constants::PROCESS_CREATION_FLAGS`). Isso garante que o jogo seja pausado imediatamente após sua criação, antes de qualquer código ser executado, permitindo que a injeção da DLL ocorra em um estado seguro.
   - Retorna um `std::optional<Process_Info>` (para C++17+) ou um `std::unique_ptr<Process_Info>` (para C++14), contendo os `handles` encapsulados do processo e da `thread`.
- **`Inject_DLL`:**
   - Implementa a técnica padrão de injeção de DLL via `CreateRemoteThread`:
      1. **Obtenção do Endereço:** Utilizando as constantes de `constants.hpp`, localiza o endereço da função `LoadLibraryW` (do `kernel32.dll`), que o Windows utiliza para carregar bibliotecas dinamicamente.
      2. **Alocação de Memória:** `VirtualAllocEx` é utilizada para reservar um bloco de memória virtual dentro do processo do jogo (`gta_sa.exe`). Este bloco é dimensionado para conter o caminho completo da DLL a ser injetada.
      3. **Escrita do Caminho:** O caminho da DLL (e.g., `L"C:\\caminho\\para\\samp.dll"`) é então copiado para a memória remotamente alocada no processo do jogo através de `WriteProcessMemory`.
      4. **Criação da Thread Remota:** `CreateRemoteThread` inicia uma nova `thread` no contexto do processo do jogo. O ponto de entrada desta `thread` é o endereço de `LoadLibraryW`, e o argumento passado é o endereço da string do caminho da DLL que acabamos de gravar.
      5. **Monitoramento:** A execução da `thread` remota é monitorada por `WaitForSingleObject` até que ela seja concluída ou o `DLL_INJECTION_TIMEOUT_MS` seja atingido.
      6. **Verificação de Sucesso:** `GetExitCodeThread` é usada para verificar o valor de retorno da `thread` remota. Se `LoadLibraryW` foi bem-sucedida, ela retornará o endereço base da DLL carregada (um valor diferente de zero).
      7. **Limpeza:** A memória alocada no processo remoto é liberada por `VirtualFreeEx`.
   - Retorna um `Injection_Status` indicando o sucesso ou o tipo específico de falha da injeção.

```cpp
// Exemplo de trecho relevante de process.hpp
class Process {
public:
    struct Process_Info {
        Resource_Handle::Unique_Resource<HANDLE, std::function<void(HANDLE)>> process_handle; // Handle do processo com gerenciamento RAII
        Resource_Handle::Unique_Resource<HANDLE, std::function<void(HANDLE)>> thread_handle; // Handle da thread com gerenciamento RAII

        bool Resume() { // Retoma a execução da thread principal do jogo
            return thread_handle && ResumeThread(thread_handle.get()) != static_cast<DWORD>(-1);
        }
    };
    
    enum class Injection_Status { // Códigos de status detalhados para a injeção de DLL
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

    // Cria o processo do jogo em estado suspenso
    std::optional<Process_Info> Create_Game_Process(const std::wstring& game_path, std::wstring& command_args, const std::wstring& working_dir) {
        // ... Lógica de CreateProcessW com CREATE_SUSPENDED ...
    }
    
    SAMP_INJECTOR_NODISCARD // Garante que o valor de retorno seja utilizado
    Injection_Status Inject_DLL(HANDLE process, const std::wstring& DLL_path) {
        static const LPVOID load_library_addr = reinterpret_cast<LPVOID>(GetProcAddress(GetModuleHandleW(Constants::KERNEL32_DLL), Constants::LOAD_LIBRARY_FUNC));

        if (!load_library_addr)
            return Injection_Status::LOADLIBRARY_ADDRESS_FAILED;

        LPVOID remote_memory = VirtualAllocEx(process, nullptr, (DLL_path.length() + 1) * sizeof(wchar_t), Constants::MEMORY_ALLOCATION_TYPE, Constants::MEMORY_PROTECTION);

        if (!remote_memory)
            return Injection_Status::ALLOCATION_FAILED;

        auto memory_guard = Resource_Handle::Unique_Resource<LPVOID, std::function<void(LPVOID)>>(remote_memory, [process](LPVOID ptr) {
            if (ptr)
                VirtualFreeEx(process, ptr, 0, MEM_RELEASE); // Libera a memória no processo remoto
        });

        if (!WriteProcessMemory(process, remote_memory, DLL_path.c_str(), (DLL_path.length() + 1) * sizeof(wchar_t), nullptr))
            return Injection_Status::WRITE_FAILED;

        HANDLE remote_thread = CreateRemoteThread(process, nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(load_library_addr), remote_memory, 0, nullptr);

        if (!remote_thread)
            return Injection_Status::THREAD_CREATION_FAILED;

        auto thread_guard = Resource_Handle::Make_Unique_Handle(remote_thread); // Gerenciamento seguro do handle da thread remota

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

Este cabeçalho define a classe `Injector_Core`, que serve como o centro de comando da biblioteca. Ela orquestra a sequência lógica das operações de injeção, conectando os módulos de validação de entrada, gerenciamento de privilégios e manipulação de processos. É aqui que o fluxo de trabalho completo da injeção é definido.

- **`Injector_Core`:** O construtor desta classe é o ponto onde `Privileges::Enable_Debug_Privilege()` é chamado. Isso garante que o processo da aplicação possua os privilégios necessários para realizar operações de injeção de DLL antes que qualquer outra lógica crítica seja executada.
- **`Initialize_Game`:**
   1. **Validação Abrangente:** Inicia chamando as funções de validação (`Validation::Validate_Port`, `Validation::Validate_Nickname`, `Validation::Validate_Files`) para assegurar que todos os parâmetros e recursos essenciais estejam em ordem. Se qualquer validação falhar, um erro é imediatamente reportado.
   2. **Preparação de Argumentos:** Constrói a linha de comando completa (`std::wstring`) que será passada ao `gta_sa.exe`, incorporando o nickname, IP, porta e senha fornecidos.
   3. **Criação do Processo Suspenso:** Invoca `Process::Create_Game_Process` para iniciar o `gta_sa.exe` em um estado suspenso, obtendo os `handles` do processo e da `thread` principal.
   4. **Injeção de `samp.dll`:** Chama `Inject_DLL_With_Status_Check` para injetar o `samp.dll` no processo do jogo. Esta função wrapper também é responsável por interpretar o `Injection_Status` retornado e exibir mensagens de erro informativas.
   5. **Injeção Condicional de `omp-client.dll`:** Se o `inject_type` for `Types::Inject_Type::OMP`, o `omp-client.dll` é então injetada da mesma forma que `samp.dll`.
   6. **Retomada do Jogo:** Após todas as injeções bem-sucedidas, `process_info.Resume()` é chamada para permitir que a `thread` principal do jogo continue sua execução.
   7. **Tratamento de Erros no Ciclo:** Qualquer falha em qualquer uma dessas etapas críticas resultará em uma chamada para `Error_Utils::Show_Error`, fornecendo feedback claro ao usuário e garantindo que o processo seja encerrado corretamente (os `handles` são liberados automaticamente pelos `Unique_Resource`s).
- **`Build_Command_Args`:** Uma função auxiliar que organiza e concatena os argumentos de linha de comando, adicionando aspas onde necessário para parâmetros que contenham espaços.
- **`Inject_DLL_With_Status_Check`:** Uma função privada que atua como um invólucro para `Process::Inject_DLL`. Ela mapeia os diferentes `Injection_Status` para mensagens de erro compreensíveis, facilitando o tratamento de erros e a comunicação com o usuário.

```cpp
// Exemplo de trecho relevante de injector_core.hpp
namespace Injector {
    class Injector_Core {
    public:
        Injector_Core() { // O construtor habilita o privilégio de depuração
            Privileges::Enable_Debug_Privilege();
        }

        bool Initialize_Game(Types::Inject_Type inject_type, std::wstring_view folder, std::wstring_view nickname, std::wstring_view ip, std::wstring_view port, std::wstring_view password) {
            std::wstring error_message;

            // Sequência de validações de entrada
            if (!Validation::Validate_Port(port, error_message))
                return (Error_Utils::Show_Error(error_message, inject_type), false);
            // ... outras validações ...

            // Constrói os argumentos da linha de comando
            std::wstring args = Build_Command_Args({
                Command_Arg{Constants::CMD_ARG_NICKNAME, std::wstring(nickname)},
                // ... outros argumentos ...
            });

            Process process_core;
            // Cria o processo do jogo em estado suspenso
            auto process_info_opt = process_core.Create_Game_Process(game_path, args, std::wstring(folder));

            if (!process_info_opt)
                return false;

            auto& process_info = *process_info_opt;

            // Injeta samp.dll e, condicionalmente, omp-client.dll
            if (!Inject_DLL_With_Status_Check(process_core, process_info.process_handle.get(), Constants::SAMP_DLL_NAME, samp_DLL_path.wstring(), inject_type))
                return false;
            
            if (inject_type == Types::Inject_Type::OMP) {
                if (!Inject_DLL_With_Status_Check(process_core, process_info.process_handle.get(), Constants::OMP_DLL_NAME, omp_DLL_path.wstring(), inject_type))
                    return false;
            }
            
            // Retoma a thread principal do jogo
            if (!process_info.Resume())
                return (Error_Utils::Show_Error(L"Failed to resume the game process thread: " + Error_Utils::Get_System_Error_Message(GetLastError()), inject_type), false);

            return true;
        }
    };
}
```

### 10. `injector.hpp`

Este cabeçalho atua como a fachada (`Facade`) principal da biblioteca, oferecendo um ponto de entrada simplificado para qualquer aplicação que deseje utilizar a funcionalidade de injeção. Ele abstrai a complexidade interna da `Injector_Core` em uma única e conveniente função.

- **`Initialize_Game`:**
   - Esta função estática é a interface pública da biblioteca.
   - Primeiramente, ela valida a `inject_type_str` (se é `L"samp"` ou `L"omp"`) e a converte para o `enum class Types::Inject_Type`. Em caso de string inválida, exibe um erro e termina.
   - Em seguida, cria uma instância da `Injector::Injector_Core`.
   - Finalmente, delega a execução da lógica principal para `Injector_Core::Initialize_Game`, que é onde todo o processo de validação, criação de processo e injeção de DLL é orquestrado.

```cpp
// Exemplo de trecho relevante de injector.hpp
// A interface pública para iniciar o jogo
#if defined(SAMP_INJECTOR_CXX_MODERN)
inline bool Initialize_Game(std::wstring_view inject_type, std::wstring_view folder, std::wstring_view nickname, std::wstring_view ip, std::wstring_view port, std::wstring_view password) {
#elif defined(SAMP_INJECTOR_CXX_14)
inline bool Initialize_Game(const std::wstring& inject_type, const std::wstring& folder, const std::wstring& nickname, const std::wstring& ip, const std::wstring& port, const std::wstring& password) {
#endif
    Types::Inject_Type type;

    // Converte a string de tipo de injeção para o enum correspondente
    if (inject_type == Constants::INJECT_TYPE_SAMP)
        type = Types::Inject_Type::SAMP;
    else if (inject_type == Constants::INJECT_TYPE_OMP)
        type = Types::Inject_Type::OMP;
    else
        // Exibe erro se o tipo de injeção for inválido
        return (Error_Utils::Show_Error(L"Modo de injeção inválido. Use 'samp' ou 'omp'.", Types::Inject_Type::SAMP), false);

    Injector::Injector_Core injector; // Cria a instância do núcleo do injetor

    // Delega a lógica principal para o Injector_Core
    return injector.Initialize_Game(type, folder, nickname, ip, port, password);
}
```

## O Processo Detalhado de Injeção

A funcionalidade central desta biblioteca é orquestrar uma sequência precisa de operações para injetar as DLLs do cliente SA-MP ou OMP no processo do GTA:SA. Este ciclo é cuidadosamente planejado para garantir estabilidade e compatibilidade.

### 1. Solicitação de Inicialização

O processo se inicia com a chamada à função global `Initialize_Game` (`injector.hpp`), que atua como o principal ponto de contato para a aplicação que utiliza a biblioteca. Esta função recebe todos os parâmetros cruciais, como o tipo de injeção desejado (SA-MP ou OMP), o diretório do jogo e os dados de conexão ao servidor (nickname, IP, porta, senha).

### 2. Preparação do Ambiente

Ao ser invocada, a função `Initialize_Game` cria uma instância de `Injector::Injector_Core`. No construtor desta classe (`injector_core.hpp`), a primeira e essencial etapa de configuração do ambiente é executada: a elevação de privilégios.

> [!NOTE]
> `Privileges::Enable_Debug_Privilege()`: Esta chamada (`privileges.hpp`) concede ao processo da aplicação o privilégio `SE_DEBUG_NAME`. Este privilégio é vital, pois permite que o aplicativo execute operações de baixo nível em outros processos do Windows, como ler e escrever em sua memória e criar `threads` remotas – ações fundamentais para a técnica de injeção de DLL.

### 3. Verificação de Integridade e Parâmetros

Com os privilégios ajustados, o método `Injector_Core::Initialize_Game` procede com uma série de validações rigorosas. Esta é uma fase preventiva que minimiza a chance de falhas em etapas posteriores e fornece feedback imediato ao usuário.

- **Validação da Porta:** `Validation::Validate_Port` verifica se o número da porta de conexão está formatado corretamente e se encontra dentro do intervalo de `1` a `65535` (`constants.hpp`).
- **Validação do nickname:** `Validation::Validate_Nickname` garante que o nickname do jogador não esteja vazio e não exceda o limite de `23` caracteres.
- **Verificação de Arquivos Essenciais:** `Validation::Validate_Files` inspeciona o diretório do jogo para confirmar a presença de `gta_sa.exe`, `samp.dll` e, se a injeção for do tipo OMP, também `omp-client.dll`.

> [!WARNING]
> Qualquer falha nesta etapa resulta na exibição imediata de uma `MessageBox` com uma mensagem de erro detalhada (`error_utils.hpp`) e a interrupção do processo de injeção. Isso evita tentativas inúteis de prosseguir com uma configuração inválida.

### 4. Preparação dos Argumentos para o Jogo

Após a validação bem-sucedida, a função `Injector_Core::Build_Command_Args` é responsável por construir a linha de comando formatada que será passada ao `gta_sa.exe`. Esta linha de comando inclui todos os parâmetros necessários para que o cliente SA-MP/OMP se conecte automaticamente a um servidor, como `-n "nickname" -h "IP" -p "Porta" -z "Senha"`.

### 5. Inicialização do Processo do Jogo (Suspenso)

O componente `Process` (`process.hpp`) é então encarregado de iniciar o executável do GTA:SA.

> [!IMPORTANT]
> A função `Process::Create_Game_Process` utiliza a flag `CREATE_SUSPENDED` (`constants.hpp`) ao chamar a API `CreateProcessW` do Windows. Esta é uma medida de design crítica: o jogo é carregado na memória e sua `thread` principal é criada, mas sua execução é **pausada**. Isso cria um ambiente controlado e estável, ideal para a injeção de DLLs, antes que o jogo possa inicializar suas próprias defesas ou lógicas internas. Os `handles` do processo e da `thread` são obtidos e gerenciados com segurança via `Resource_Handle::Unique_Resource`.

### 6. Injeção da Biblioteca SA-MP (`samp.dll`)

Com o processo do jogo em estado de suspensão, a injeção do `samp.dll` pode ser realizada de forma segura. O método `Injector_Core::Inject_DLL_With_Status_Check` delega esta tarefa ao `Process::Inject_DLL`, que executa os seguintes passos da técnica de `remote thread injection`:

1. **Localização da Função `LoadLibraryW`:** O endereço da função `LoadLibraryW` é identificado. Esta operação utiliza as constantes `Constants::KERNEL32_DLL` e `Constants::LOAD_LIBRARY_FUNC` para obter um `handle` para a `kernel32.dll` e, em seguida, localizar o endereço da função de carregamento de bibliotecas dinâmicas.
2. **Alocação de Memória Remota:** `VirtualAllocEx` é utilizada para reservar um bloco de memória no espaço de endereço virtual do processo `gta_sa.exe` (que está suspenso). O tamanho deste bloco é suficiente para armazenar o caminho completo do `samp.dll`.
3. **Escrita do Caminho da DLL:** O caminho completo do arquivo `samp.dll` é gravado nesta memória remota recém-alocada por `WriteProcessMemory`.
4. **Criação de Thread Remota:** `CreateRemoteThread` é chamada para criar uma nova `thread` dentro do processo `gta_sa.exe`. O ponto de entrada desta nova `thread` é o endereço de `LoadLibraryW`, e o argumento que ela recebe é o ponteiro para o caminho da DLL que acabamos de gravar.
5. **Monitoramento da Injeção:** A execução da `thread` remota é monitorada por `WaitForSingleObject` por um período definido por `Constants::DLL_INJECTION_TIMEOUT_MS`.
6. **Verificação do Resultado:** O código de saída da `thread` remota é obtido via `GetExitCodeThread`. Um valor de retorno diferente de zero indica que `LoadLibraryW` foi bem-sucedida em carregar o `samp.dll`.

> [!WARNING]
> Em caso de qualquer falha durante a injeção do `samp.dll`, uma mensagem de erro específica (`error_utils.hpp`) é exibida, o processo de injeção é abortado, e os recursos são liberados.

### 7. Injeção da Biblioteca OMP (`omp-client.dll`) - Condicional

Se o tipo de injeção especificado for `OMP`, as etapas detalhadas no ponto 6 são repetidas para o `omp-client.dll`.

> [!TIP]
> A injeção de `omp-client.dll` sempre ocorre após a injeção bem-sucedida de `samp.dll`. Isso se deve ao fato de que o cliente Open Multiplayer se baseia na infraestrutura fornecida pelo `samp.dll`.

### 8. Ativação do Jogo

Finalmente, se todas as injeções foram concluídas com sucesso, o método `process_info.Resume()` é invocado. Esta chamada executa `ResumeThread` na `thread` principal do `gta_sa.exe`. Neste momento, o jogo é ativado e inicia sua execução normal, mas já com as DLLs do SA-MP/OMP carregadas em sua memória e com os parâmetros de conexão configurados, permitindo uma conexão automatizada ao servidor.

> [!WARNING]
> Se a retomada da `thread` do jogo falhar, uma última mensagem de erro é apresentada ao usuário.

## Diagnóstico de Erros e Falhas

A biblioteca é meticulosamente projetada para comunicar claramente qualquer problema que possa surgir durante o processo de inicialização e injeção. Em qualquer ponto de falha, uma `MessageBox` com uma descrição detalhada é apresentada ao usuário, muitas vezes complementada com mensagens de erro do sistema operacional.

### Falhas de Validação de Entrada

Estes erros são detectados na fase inicial (`validation.hpp`), antes de qualquer interação de baixo nível com o sistema, e indicam problemas com os dados fornecidos pelo usuário ou com a configuração do ambiente.

#### Nome de Usuário Inválido

- **Mensagem de Erro (Exemplo 1):** `"Nickname cannot be empty. Please provide a valid nickname."`
- **Mensagem de Erro (Exemplo 2):** `"Nickname length exceeds the maximum allowed of 23 characters. Please use a shorter nickname."`
- **Razão:** O nome de usuário (`nickname`) fornecido está vazio ou ultrapassa o limite máximo de 23 caracteres permitido pelos clientes SA-MP/OMP.
- **Solução:** O usuário deve inserir um nome de usuário válido que respeite os critérios de comprimento.

#### Porta de Conexão Inválida

- **Mensagem de Erro (Exemplo 1):** `"Invalid port format. The port must be a numeric value. Please provide a valid integer for the port."`
- **Mensagem de Erro (Exemplo 2):** `"The specified port number (70000) is outside the valid range of 1 to 65535. Please provide a valid port."`
- **Razão:** O valor fornecido para a porta não é um número inteiro ou está fora do intervalo válido (1 a 65535).
- **Solução:** O usuário precisa fornecer um número de porta válido e dentro do intervalo especificado.

#### Recursos Essenciais Ausentes

- **Mensagem de Erro (Exemplo 1):** `"Game executable not found. Please ensure 'gta_sa.exe' exists at the specified path: C:\Games\GTA San Andreas\gta_sa.exe"`
- **Mensagem de Erro (Exemplo 2):** `"SA-MP library not found. Please ensure 'samp.dll' exists at the specified path: C:\Games\GTA San Andreas\samp.dll"`
- **Mensagem de Erro (Exemplo 3, para OMP):** `"OMP library not found. Please ensure 'omp-client.dll' exists at the specified path for OMP injection: C:\Games\GTA San Andreas\omp-client.dll"`
- **Razão:** Um ou mais arquivos cruciais (`gta_sa.exe`, `samp.dll`, `omp-client.dll`) não foram encontrados no diretório do jogo especificado.
- **Solução:** Verifique o caminho da pasta do jogo e garanta que todos os arquivos necessários estejam presentes e acessíveis.

### Falhas na Gestão do Processo

Estes erros ocorrem quando a biblioteca tenta iniciar o executável do jogo (`gta_sa.exe`).

#### Dificuldade ao Iniciar o Processo do Jogo

- **Mensagem de Erro (Exemplo):** `"Failed to create game process. Ensure 'gta_sa.exe' is not running and you have sufficient permissions to execute the file. System Error: Access is denied."`
- **Razão:**
   - **Executável em Uso:** `gta_sa.exe` já pode estar em execução, ou há algum bloqueio do sistema operacional que impede a criação de uma nova instância.
   - **Permissões Insuficientes:** A aplicação pode não ter as permissões adequadas para iniciar o `gta_sa.exe` ou para acessar o arquivo.
   - **Executável Corrompido:** Embora a validação básica verifique a existência do arquivo, ele pode estar corrompido ou inacessível.
- **Solução:** Certifique-se de que nenhuma instância de `gta_sa.exe` esteja ativa. Tente executar sua aplicação como administrador. Verifique a integridade do arquivo `gta_sa.exe`.

### Problemas na Injeção da DLL

Estes são os erros mais críticos e detalhados, ocorrendo durante a tentativa de injetar `samp.dll` ou `omp-client.dll` no processo suspenso do jogo. As mensagens de erro geralmente começam com `"Failed to inject <DLL_NAME>:\n"` e são seguidas por uma descrição específica e um código de erro do sistema.

#### Impossível Localizar `LoadLibraryW`

- **Mensagem de Erro (Parte):** `"Failed to find the address of LoadLibraryW in kernel32.dll."`
- **Razão:** A função `LoadLibraryW`, uma API fundamental do Windows para carregamento dinâmico de DLLs, não pôde ser encontrada na `kernel32.dll`. Este é um problema de baixo nível extremamente raro, que aponta para uma possível corrupção do sistema operacional ou um ambiente de execução altamente incomum.
- **Solução:** Uma reinicialização do sistema pode resolver. Se persistir, pode indicar um problema mais grave na instalação do Windows.

#### Falha na Reserva de Memória Remota

- **Mensagem de Erro (Parte):** `"Failed to allocate memory in the target process (VirtualAllocEx). System Error: Not enough storage is available to process this command."`
- **Razão:** A biblioteca não conseguiu alocar um bloco de memória no espaço de endereço virtual do processo `gta_sa.exe`.
   - **Permissões:** Sua aplicação pode não ter permissões suficientes para modificar o espaço de memória de outro processo.
   - **Proteção de Processo:** Mecanismos de segurança do sistema operacional ou softwares anti-cheat podem estar bloqueando a alocação de memória em processos externos.
- **Solução:** Execute sua aplicação como administrador. Verifique se programas de segurança (antivírus, anti-cheat) estão interferindo e, se possível, desative-os temporariamente para testar.

#### Incapacidade de Gravar Dados no Processo

- **Mensagem de Erro (Parte):** `"Failed to write DLL path to process memory (WriteProcessMemory). System Error: Access is denied."`
- **Razão:** Memória foi alocada no processo do jogo, mas a biblioteca não conseguiu gravar o caminho da DLL nesse local.
   - **Permissões/Proteção:** Similar à falha de alocação de memória, pode ser um problema de permissão de escrita ou uma proteção de memória ativa.
- **Solução:** As mesmas soluções para a falha de alocação de memória se aplicam.

#### Falha ao Criar Thread de Injeção

- **Mensagem de Erro (Parte):** `"Failed to create remote thread (CreateRemoteThread). System Error: The parameter is incorrect."`
- **Razão:** A API `CreateRemoteThread` falhou ao iniciar uma nova `thread` no processo `gta_sa.exe` para invocar `LoadLibraryW`.
   - **Segurança:** Muitos sistemas anti-cheat e proteções de SO monitoram e bloqueiam a criação de `threads` remotas, pois é uma técnica comum de injeção.
   - **Estado do Processo:** O processo do jogo pode estar em um estado instável que impede a criação de `threads`.
- **Solução:** Desative temporariamente qualquer software anti-cheat ou antivírus. Tente executar a aplicação como administrador.

#### Tempo Limite Excedido ou Erro na Espera pela Injeção

- **Mensagem de Erro (Parte):** `"Timeout or error waiting for remote thread (WaitForSingleObject). System Error: The wait operation timed out."`
- **Razão:** A `thread` remota (que chama `LoadLibraryW`) não concluiu sua execução dentro do tempo limite estabelecido (10 segundos).
   - **Congelamento:** `LoadLibraryW` pode ter travado, demorado excessivamente, ou ter sido interceptada/bloqueada.
- **Solução:** Isso pode indicar que a DLL está com dificuldades para carregar ou que algo a está impedindo. Verificar logs do sistema ou do próprio SA-MP/OMP (se disponíveis) pode oferecer mais pistas.

#### Falha Interna na Injeção da DLL

- **Mensagem de Erro (Parte):** `"LoadLibraryW call failed in the target process. The DLL might be corrupt, missing dependencies, or blocked by security software."`
- **Razão:** A `thread` remota foi concluída, mas o valor de retorno de `LoadLibraryW` foi `0` (ou `NULL`), indicando que a DLL não foi carregada com sucesso.
   - **DLL Corrompida/Inexistente:** A DLL pode ter sido movida, excluída ou corrompida após a validação inicial.
   - **Dependências Ausentes:** `samp.dll` ou `omp-client.dll` podem ter dependências (outras DLLs) que não estão presentes no diretório do jogo ou no `PATH` do sistema.
   - **Erro Interno da DLL:** A própria DLL pode ter um erro interno que impede seu carregamento.
- **Solução:** Verifique a integridade dos arquivos `samp.dll`/`omp-client.dll`. Certifique-se de que todas as suas dependências estejam presentes.

### Dificuldade ao Retomar a Execução do Jogo

Este é o último ponto de falha possível no ciclo de injeção.

- **Mensagem de Erro (Exemplo):** `"Failed to resume the game process thread: Invalid handle."`
- **Razão:** A API `ResumeThread` falhou ao reativar a `thread` principal do `gta_sa.exe`.
   - **Handle Inválido:** O `handle` da `thread` pode ter sido invalidado por algum evento inesperado.
   - **Permissão:** A aplicação pode não ter permissão para alterar o estado da `thread`.
- **Solução:** Tente executar a aplicação como administrador. Se o problema persistir, pode indicar um problema de estabilidade mais profundo no sistema ou no processo do jogo.

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