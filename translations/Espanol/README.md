# SA-MP Injector

[![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](https://opensource.org/licenses/MIT)
[![SA-MP | OMP](https://img.shields.io/badge/Support-SA--MP%20%7C%20OMP-yellow)](https://github.com/spc-samp/samp-injector)
[![x86 Only](https://img.shields.io/badge/Architecture-x86%20(32--bit)-orange)](https://github.com/spc-samp/samp-injector)

SA-MP Injector es una herramienta versátil diseñada para **SA-MP (San Andreas Multiplayer)** y **OMP (Open Multiplayer)**, que funciona tanto como un **ejecutable de línea de comandos** como una **biblioteca para diferentes lenguajes**. Su función principal es inyectar `samp.dll` (para **SA-MP**) o tanto `samp.dll` como `omp-client.dll` (para **OMP**) en el proceso de **GTA:SA**, permitiendo que el juego se inicie con parámetros personalizados para una conexión directa a un servidor.

## Idiomas

- Português: [README](../../)
- Deutsch: [README](../Deutsch/README.md)
- English: [README](../English/README.md)
- Français: [README](../Francais/README.md)
- Italiano: [README](../Italiano/README.md)
- Polski: [README](../Polski/README.md)
- Русский: [README](../Русский/README.md)
- Svenska: [README](../Svenska/README.md)
- Türkçe: [README](../Turkce/README.md)

## Índice

- [SA-MP Injector](#sa-mp-injector)
  - [Idiomas](#idiomas)
  - [Índice](#índice)
  - [Ejecutable](#ejecutable)
    - [Funcionalidad](#funcionalidad)
    - [Cómo Usar (Línea de Comandos)](#cómo-usar-línea-de-comandos)
      - [Modo SA-MP](#modo-sa-mp)
      - [Modo OMP](#modo-omp)
      - [Parámetros](#parámetros)
    - [Cómo Usar (Integrado en Aplicaciones)](#cómo-usar-integrado-en-aplicaciones)
    - [Uso de la Biblioteca C++ en el Ejecutable](#uso-de-la-biblioteca-c-en-el-ejecutable)
    - [Cómo Compilar](#cómo-compilar)
      - [Requisitos](#requisitos)
      - [Pasos de Compilación](#pasos-de-compilación)
  - [Bibliotecas](#bibliotecas)
    - [Visión General](#visión-general)
    - [Listado de Bibliotecas](#listado-de-bibliotecas)
  - [Licencia](#licencia)
    - [Términos y Condiciones de Uso](#términos-y-condiciones-de-uso)
      - [1. Permisos Otorgados](#1-permisos-otorgados)
      - [2. Condiciones Obligatorias](#2-condiciones-obligatorias)
      - [3. Derechos de Autor](#3-derechos-de-autor)
      - [4. Exención de Garantías y Limitación de Responsabilidad](#4-exención-de-garantías-y-limitación-de-responsabilidad)

## Ejecutable

El ejecutable `samp-injector.exe` ofrece una interfaz de línea de comandos para iniciar **GTA:SA** con **SA-MP** o **OMP**, configurando automáticamente la conexión a un servidor. Encapsula la lógica de **inyección de DLLs** y la transmisión de parámetros del juego.

### Funcionalidad

El `samp-injector.exe` opera como un lanzador de juegos automatizado, abstrayendo las complejidades de la configuración y la **inyección de DLLs**:

1. **Validación de Entorno:** Verifica la existencia de los archivos esenciales (`gta_sa.exe`, `samp.dll`, `omp-client.dll`) en el directorio especificado, además de validar los parámetros de conexión proporcionados.
2. **Creación de un Proceso Suspendido:** Inicia `gta_sa.exe` en un estado suspendido, un requisito previo para **inyectar las DLLs** de manera segura antes de que se ejecute el proceso principal del juego.
3. **Inyección Dinámica de DLLs:**
    - Para el modo **SA-MP**, se inyecta `samp.dll`.
    - Para el modo **OMP**, se inyectan tanto `samp.dll` como `omp-client.dll`.
    La inyección se facilita mediante la invocación remota de la función `LoadLibraryA`, lo que permite que GTA:SA cargue los módulos multijugador e inicialice la conexión.
4. **Configuración de Argumentos:** Los argumentos de la línea de comandos, como **apodo**, **IP del servidor**, **puerto** y **contraseña (si se proporciona)**, se preparan y se pasan a `gta_sa.exe`.
5. **Reanudación del Proceso:** Tras la **inyección exitosa de las DLLs**, el proceso del juego se reanuda para su ejecución normal, lo que lleva a **GTA:SA** a conectarse directamente al servidor.

### Cómo Usar (Línea de Comandos)

Para utilizar el ejecutable, invóquelo desde el **Símbolo del sistema (CMD)**, **PowerShell** o **terminal**, proporcionando los parámetros necesarios.

El formato básico es:

```bash
samp-injector.exe <modo> <directorio_juego> <apodo> <ip_servidor> <puerto_servidor> <contraseña_servidor (opcional)>
```

#### Modo SA-MP

Para la inyección exclusiva de `samp.dll`:

```bash
samp-injector.exe "samp" "C:\Games\GTA San Andreas" "Nombre" "127.0.0.1" "7777" "contraseña (opcional)"
```

#### Modo OMP

Para la inyección de `samp.dll` y `omp-client.dll`:

```bash
samp-injector.exe "omp" "C:\Games\GTA San Andreas" "Nombre" "127.0.0.1" "7777" "contraseña (opcional)"
```

#### Parámetros

- `<modo>`: Define el tipo de inyección.
    - `samp`: Para **SA-MP** (`samp.dll`).
    - `omp`: Para **OMP** (`samp.dll` y `omp-client.dll`).
- `<directorio_juego>`: La ruta completa al directorio de **GTA:SA**. Este directorio debe contener `gta_sa.exe` y los respectivos archivos **DLL**.
- `<apodo>`: Su apodo en el juego (máximo de **20 caracteres**).
- `<ip_servidor>`: La **dirección IP** o el **nombre de dominio** del servidor.
- `<puerto_servidor>`: El puerto de conexión del servidor (un **valor numérico** entre **1** y **65535**).
- `<contraseña_servidor>`: La contraseña necesaria para conectarse al servidor **(si el servidor no requiere contraseña, no es necesario agregar este parámetro)**.

Si los argumentos son incorrectos o insuficientes, se mostrará un mensaje de uso.

### Cómo Usar (Integrado en Aplicaciones)

El `samp-injector.exe` es ideal para la integración en aplicaciones de terceros, como lanzadores personalizados, que desean automatizar el proceso de iniciar el juego con configuraciones predefinidas.

Ejemplo de invocación de `samp-injector.exe` desde una **aplicación en C#**:

```csharp
using System;
using System.Diagnostics;
using System.Windows.Forms;

public class Launcher {
    public static void Main(string[] args) {
        string inject_mode = "omp"; 
        string folder = "C:\\Games\\GTA San Andreas";
        string nickname = "Nombre";
        string ip = "127.0.0.1";
        string port = "7777";
        string password = "contraseña (opcional)";

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
                    MessageBox.Show($"El SA-MP Injector devolvió un error (Código: {process.ExitCode}). El juego podría no haberse iniciado correctamente.", "Error de Lanzamiento", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }
        catch (Exception ex) {
            MessageBox.Show($"Ocurrió un error al iniciar el juego: {ex.Message}", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
        }
    }
}
```

### Uso de la Biblioteca C++ en el Ejecutable

El ejecutable `samp-injector.exe` está construido sobre la biblioteca [SA-MP Injector C++](https://github.com/spc-samp/samp-injector/tree/main/libraries/cpp), que se encuentra en el directorio `libraries/cpp/`. El archivo `main.cpp` del ejecutable invoca las funcionalidades de esta biblioteca para realizar la inyección y el lanzamiento del juego.

El archivo de cabecera principal de la biblioteca **C++** que debe incluirse es `libraries/samp-injector/cpp/injector.hpp`. Dado que la biblioteca [SA-MP Injector C++](https://github.com/spc-samp/samp-injector/tree/main/libraries/cpp) es **header-only**, su uso requiere solo incluir este encabezado en el código fuente, sin necesidad de vincular un archivo `.lib`.

El fragmento relevante de `main.cpp` que demuestra la integración es el siguiente:

```cpp
// Extrae los argumentos de la línea de comandos
int argc;
std::unique_ptr<LPWSTR[], decltype(&LocalFree)> argv(CommandLineToArgvW(GetCommandLineW(), &argc), &LocalFree);

// ... (validación del número de argumentos y modo de inyección) ...

// Extrae los parámetros en variables de cadena ancha
std::wstring folder = argv[2];
std::wstring nickname = argv[3];
std::wstring ip = argv[4];
std::wstring port = argv[5];
std::wstring password = (argc == 7) ? argv[6] : L"";

// Delega la lógica de inyección a la función "Initialize_Game" de la biblioteca
// Observe que "injector.hpp" fue incluido previamente en "main.cpp"
if (!Initialize_Game(inject_type, folder, nickname, ip, port, password))
    return 1;

Sleep(10000); // Espera antes de finalizar el ejecutable
```

La función `Initialize_Game` actúa como la interfaz de alto nivel de la biblioteca, orquestando todas las operaciones de validación, creación de procesos e **inyección de DLLs**.

### Cómo Compilar

Puede compilar el `samp-injector.exe` desde el código fuente. Si no desea compilar, puede descargar las versiones precompiladas en la sección de [Releases](https://github.com/spc-samp/samp-injector/releases).

#### Requisitos

- **Visual Studio:** Se recomienda **Visual Studio 2022** o superior con la **carga de trabajo "Desarrollo de escritorio con C++"** instalada.
- **Git:** Para clonar el repositorio (o simplemente descárguelo accediendo a este enlace: [Download](https://github.com/spc-samp/samp-injector/archive/refs/heads/main.zip)).

#### Pasos de Compilación

1. **Clonar el Repositorio:**
    ```bash
    git clone https://github.com/spc-samp/samp-injector.git
    cd samp-injector
    ```
2. **Abrir la Solución:**
   
    Navegue hasta la carpeta `executable` y abra el archivo de solución `.sln`:
    ```bash
    cd executable
    start samp-injector.sln
    ```
    Esto abrirá el proyecto en **Visual Studio**.
3. **Configurar la Compilación:**
    - En **Visual Studio**, verifique la configuración de la solución. Se recomienda utilizar los modos `Release` y `x86` **(32 bits)**. En el contexto de **GTA:SA** y **SA-MP**/**OMP**, la **arquitectura x86 (32 bits)** es obligatoria.
4. **Compilar:**
   - En el menú `Compilar`, haga clic en `Compilar Solución` o en `Compilar samp-injector`.
   - Alternativamente, puede usar los atajos:
     - `Ctrl + Shift + B` para compilar la solución completa.
     - `Ctrl + B` (si está configurado) para compilar el proyecto actual.
    - Si todo está configurado correctamente, el ejecutable `samp-injector.exe` se generará en el directorio `executable\Release` (o `executable\Debug`, dependiendo de su configuración de **compilación**).

## Bibliotecas

Las bibliotecas son los componentes fundamentales del `SA-MP Injector`, que contienen la lógica central para la manipulación de procesos, **inyección de DLLs** y la validación de parámetros. La principal ventaja de usar estas bibliotecas es la facilidad en la inicialización e inyección, generalmente a través de una única función (o llamadas con parámetros específicos para lenguajes de scripting).

### Visión General

El proyecto está construido sobre bibliotecas que encapsulan las funcionalidades críticas. Esto permite que otros proyectos integren fácilmente la capacidad de iniciar **GTA:SA** con los módulos **multijugador** necesarios.

### Listado de Bibliotecas

| Lenguaje      | Nombre                     | Enlace a la Biblioteca/Documentación |
| ------------- | -------------------------- | ------------------------------------ |
| C++           | **SA-MP Injector C++**     | [Ver Biblioteca](libraries/cpp)      |
| C             | **SA-MP Injector C**       | (Próximamente)                       |
| C#            | **SA-MP Injector C#**      | (Próximamente)                       |
| Java          | **SA-MP Injector Java**    | (Próximamente)                       |
| Python        | **SA-MP Injector Python**  | (Próximamente)                       |
| Go (Golang)   | **SA-MP Injector Go**      | (Próximamente)                       |
| Rust          | **SA-MP Injector Rust**    | (Próximamente)                       |
| Kotlin        | **SA-MP Injector Kotlin**  | (Próximamente)                       |
| Scala         | **SA-MP Injector Scala**   | (Próximamente)                       |
| Lua           | **SA-MP Injector Lua**     | (Próximamente)                       |
| Ruby          | **SA-MP Injector Ruby**    | (Próximamente)                       |
| Visual Basic  | **SA-MP Injector VB**      | (Próximamente)                       |
| F#            | **SA-MP Injector F#**      | (Próximamente)                       |
| Pascal/Delphi | **SA-MP Injector P/D**     | (Próximamente)                       |
| PowerShell    | **SA-MP Injector PS**      | (Próximamente)                       |
| D (Dlang)     | **SA-MP Injector D**       | (Próximamente)                       |
| Nim           | **SA-MP Injector Nim**     | (Próximamente)                       |
| Zig           | **SA-MP Injector Zig**     | (Próximamente)                       |
| V (VLang)     | **SA-MP Injector V**       | (Próximamente)                       |
| Crystal       | **SA-MP Injector Crystal** | (Próximamente)                       |
| Perl          | **SA-MP Injector Perl**    | (Próximamente)                       |
| Racket (Lisp) | **SA-MP Injector Racket**  | (Próximamente)                       |
| Haskell       | **SA-MP Injector Haskell** | (Próximamente)                       |
| OCaml         | **SA-MP Injector OCaml**   | (Próximamente)                       |

> [!TIP]
> La documentación detallada para cada biblioteca estará disponible en su **respectivo directorio**.

## Licencia

Copyright © **SA-MP Programming Community**

Este software está licenciado bajo los términos de la Licencia MIT ("Licencia"); puede utilizar este software de acuerdo con las condiciones de la Licencia. Puede obtener una copia de la Licencia en: [MIT License](https://opensource.org/licenses/MIT)

### Términos y Condiciones de Uso

#### 1. Permisos Otorgados

La presente licencia otorga, gratuitamente, a cualquier persona que obtenga una copia de este software y archivos de documentación asociados, los siguientes derechos:
* Usar, copiar, modificar, fusionar, publicar, distribuir, sublicenciar y/o vender copias del software sin restricciones
* Permitir que las personas a las que se les proporciona el software hagan lo mismo, sujeto a las siguientes condiciones

#### 2. Condiciones Obligatorias

Todas las copias o partes sustanciales del software deben incluir:
* El aviso de derechos de autor anterior
* Este aviso de permiso
* El aviso de exención de responsabilidad a continuación

#### 3. Derechos de Autor

El software y toda la documentación asociada están protegidos por leyes de derechos de autor. La **SA-MP Programming Community** mantiene la titularidad de los derechos de autor originales del software.

#### 4. Exención de Garantías y Limitación de Responsabilidad

EL SOFTWARE SE PROPORCIONA "TAL CUAL", SIN GARANTÍA DE NINGÚN TIPO, EXPRESA O IMPLÍCITA, INCLUYENDO PERO NO LIMITADO A LAS GARANTÍAS DE COMERCIABILIDAD, IDONEIDAD PARA UN PROPÓSITO PARTICULAR Y NO INFRACCIÓN.

EN NINGÚN CASO LOS AUTORES O TITULARES DE LOS DERECHOS DE AUTOR SERÁN RESPONSABLES DE CUALQUIER RECLAMACIÓN, DAÑOS U OTRA RESPONSABILIDAD, YA SEA EN UNA ACCIÓN DE CONTRATO, AGRAVIO O DE OTRO MODO, QUE SURJA DE, FUERA DE O EN CONEXIÓN CON EL SOFTWARE O EL USO U OTROS TRATOS EN EL SOFTWARE.

---

Para información detallada sobre la Licencia MIT, consulte: https://opensource.org/licenses/MIT