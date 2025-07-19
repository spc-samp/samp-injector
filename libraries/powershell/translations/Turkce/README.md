# SA-MP Injector PowerShell

![License](https://img.shields.io/badge/License-MIT-yellow.svg?style=flat)
![PowerShell](https://img.shields.io/badge/PowerShell-5.1%2B-blue.svg?style=flat&logo=powershell)
![Platform](https://img.shields.io/badge/Platform-Windows-0078D6.svg?style=flat&logo=windows)
[![SA-MP | OMP](https://img.shields.io/badge/Support-SA--MP%20%7C%20OMP-yellow)](https://github.com/spc-samp/samp-injector)
![Code Quality](https://img.shields.io/badge/Code%20Quality-High-brightgreen.svg?style=flat)

**SA-MP Injector PowerShell**, bir **DLL enjeksiyon** betiğinden daha fazlasıdır. **Grand Theft Auto: San Andreas** (**GTA:SA**) oyununun, çok oyunculu istemcileri olan **SA-MP (San Andreas Multiplayer)** ve **OMP (Open Multiplayer)** ile birlikte programlı olarak başlatılması için sağlam ve eksiksiz bir çözüm sunmak üzere geliştirilmiş bir **PowerShell fonksiyon ve sınıf kütüphanesini** temsil eder. Temel amacı, işletim sistemi süreçlerinin doğrudan manipülasyonu ve komut satırı argümanlarının geçirilmesiyle ilgili karmaşıklığı ortadan kaldırarak oyun başlatma sürecini basitleştirmektir.

Maksimum esneklik ve kolay entegrasyon sunmak üzere geliştirilen bu kütüphane, geliştiricilerin onu doğrudan **PowerShell projelerine ve betiklerine** dahil etmelerine olanak tanır. Sadece çok oyunculu istemci DLL'lerinin (`samp.dll` veya `omp-client.dll`) **temel enjeksiyonunu** yönetmekle kalmaz, aynı zamanda tüm temel bağlantı parametrelerini (**takma ad**, **IP adresi**, **port** ve **şifre**) akıllıca yönetir ve **PowerShell** aracılığıyla doğrudan erişilen **Windows API**'nin içsel kaynakları aracılığıyla yerel bir başlatmayı simüle eder.

## Diller

- Português: [README](../../)
- Deutsch: [README](../Deutsch/README.md)
- English: [README](../English/README.md)
- Español: [README](../Espanol/README.md)
- Français: [README](../Francais/README.md)
- Italiano: [README](../Italiano/README.md)
- Polski: [README](../Polski/README.md)
- Русский: [README](../Русский/README.md)
- Svenska: [README](../Svenska/README.md)

## İçindekiler

- [SA-MP Injector PowerShell](#sa-mp-injector-powershell)
  - [Diller](#diller)
  - [İçindekiler](#i̇çindekiler)
  - [Temel Kavramlar ve Motivasyon](#temel-kavramlar-ve-motivasyon)
    - [Neden DLL Enjekte Edilir?](#neden-dll-enjekte-edilir)
    - [SA-MP ve OMP: Farklılıklar ve Benzerlikler](#sa-mp-ve-omp-farklılıklar-ve-benzerlikler)
    - [PowerShell'de DLL Enjeksiyonu: WinAPI ile Doğrudan Bir Yaklaşım](#powershellde-dll-enjeksiyonu-winapi-ile-doğrudan-bir-yaklaşım)
  - [Kütüphanenin Dahili Mimarisi: Derinlemesine Bir Bakış](#kütüphanenin-dahili-mimarisi-derinlemesine-bir-bakış)
    - [`Constants.ps1`](#constantsps1)
    - [`CustomTypes.ps1`](#customtypesps1)
    - [`StringUtils.ps1`](#stringutilsps1)
    - [`ErrorUtils.ps1`](#errorutilsps1)
    - [`Process.ps1`](#processps1)
    - [`InjectorCore.ps1`](#injectorcoreps1)
    - [`Injector.ps1`](#injectorps1)
    - [`Cleanup.ps1`](#cleanupps1)
  - [Kapsamlı Kullanım Örnekleri](#kapsamlı-kullanım-örnekleri)
    - [1. Geliştirme Ortamının Hazırlanması](#1-geliştirme-ortamının-hazırlanması)
    - [2. Temel Senaryo: Bir SA-MP Sunucusuna Bağlanma](#2-temel-senaryo-bir-sa-mp-sunucusuna-bağlanma)
    - [3. Gelişmiş Senaryo: Bir OMP Sunucusuna Bağlanma](#3-gelişmiş-senaryo-bir-omp-sunucusuna-bağlanma)
    - [4. Bir Ana Betikten Çalıştırma](#4-bir-ana-betikten-çalıştırma)
  - [Yaygın Hatalar ve Mesajların Ele Alınması](#yaygın-hatalar-ve-mesajların-ele-alınması)
    - [1. Geçersiz Enjeksiyon Türü](#1-geçersiz-enjeksiyon-türü)
    - [2. Geçersiz Sunucu Portu (Format veya Aralık)](#2-geçersiz-sunucu-portu-format-veya-aralık)
      - [2.1. Sayısal Olmayan Port Formatı](#21-sayısal-olmayan-port-formatı)
      - [2.2. Geçerli Aralık Dışında Port](#22-geçerli-aralık-dışında-port)
    - [3. Geçersiz Takma Ad (Boş veya Çok Uzun)](#3-geçersiz-takma-ad-boş-veya-çok-uzun)
      - [3.1. Boş Takma Ad](#31-boş-takma-ad)
      - [3.2. Çok Uzun Takma Ad](#32-çok-uzun-takma-ad)
    - [4. Oyun Dosyaları veya DLL Bulunamadı](#4-oyun-dosyaları-veya-dll-bulunamadı)
      - [4.1. Oyun Yürütülebilir Dosyası (`gta_sa.exe`) Bulunamadı](#41-oyun-yürütülebilir-dosyası-gta_saexe-bulunamadı)
      - [4.2. SA-MP Kütüphanesi (`samp.dll`) Bulunamadı](#42-sa-mp-kütüphanesi-sampdll-bulunamadı)
      - [4.3. OMP Kütüphanesi (`omp-client.dll`) Bulunamadı (sadece OMP enjeksiyonu için)](#43-omp-kütüphanesi-omp-clientdll-bulunamadı-sadece-omp-enjeksiyonu-için)
    - [5. Oyun Süreci Oluşturulamadı](#5-oyun-süreci-oluşturulamadı)
    - [6. Hedef Süreçte Bellek Ayrılamadı](#6-hedef-süreçte-bellek-ayrılamadı)
    - [7. DLL Yolunu Süreç Belleğine Yazma Hatası](#7-dll-yolunu-süreç-belleğine-yazma-hatası)
    - [8. Temel Sistem Fonksiyonları Bulunamadı](#8-temel-sistem-fonksiyonları-bulunamadı)
      - [8.1. `kernel32.dll` Bulunamadı](#81-kernel32dll-bulunamadı)
      - [8.2. `LoadLibraryA` Bulunamadı](#82-loadlibrarya-bulunamadı)
    - [9. Enjeksiyon için Uzak İş Parçacığı Oluşturulamadı](#9-enjeksiyon-için-uzak-i̇ş-parçacığı-oluşturulamadı)
    - [10. Zaman Aşımı veya Enjeksiyon Tamamlanamadı](#10-zaman-aşımı-veya-enjeksiyon-tamamlanamadı)
    - [11. Oyun Süreci İş Parçacığını Sürdürme Hatası](#11-oyun-süreci-i̇ş-parçacığını-sürdürme-hatası)
  - [Lisans](#lisans)
    - [Kullanım Şartları ve Koşulları](#kullanım-şartları-ve-koşulları)
      - [1. Verilen İzinler](#1-verilen-i̇zinler)
      - [2. Zorunlu Koşullar](#2-zorunlu-koşullar)
      - [3. Telif Hakları](#3-telif-hakları)
      - [4. Garanti Reddi ve Sorumluluk Sınırlaması](#4-garanti-reddi-ve-sorumluluk-sınırlaması)

## Temel Kavramlar ve Motivasyon

### Neden DLL Enjekte Edilir?

> [!NOTE]
> **DLL (Dynamic Link Library) enjeksiyonu**, **Microsoft Windows** işletim sistemlerinde kullanılan ve bir kod parçasının çalışan başka bir sürecin bellek alanı içinde yürütülmesine olanak tanıyan bir yöntemdir. Programların davranışını izleme ve hata ayıklamadan, işlevselliklerini genişletmek için uygulamaların davranışını değiştirmeye kadar çeşitli meşru uygulamaları olan güçlü bir tekniktir.

**GTA San Andreas** gibi, başlangıçta entegre çok oyunculu işlevsellikle geliştirilmemiş oyunlar bağlamında, **DLL enjeksiyonu**, **SA-MP** ve **OMP** gibi çok oyunculu istemcilerin varlığının temelidir. Bu istemciler, `gta_sa.exe` sürecine enjekte edildikten sonra kontrolü ele alan, oyun fonksiyonlarını kesen ve çok oyunculu sunucularla iletişim kuran **DLL'ler** olarak uygulanır.

Harici bir başlatıcıya veya oyunun yürütülebilir dosyasının doğrudan değiştirilmesine bağlı kalmak yerine, **DLL enjeksiyonu**, özellikle önceden tanımlanmış ayarlarla belirli sunuculara bağlantı sürecini otomatikleştirmek istenen ortamlarda daha esnek ve programlanabilir bir başlatma sağlar.

### SA-MP ve OMP: Farklılıklar ve Benzerlikler

**SA-MP** ve **OMP**, **GTA San Andreas** için iki ana çok oyunculu platformdur. Her ikisi de temel oyunu devasa çok oyunculu bir çevrimiçi ortama dönüştüren modifikasyonlar olarak çalışır.

- **SA-MP (San Andreas Multiplayer)**: Orijinal ve en köklü istemci, uzun yıllardır yaygın olarak kullanılmaktadır. Mimarisi çalışmak için `samp.dll` gerektirir.
- **OMP (Open Multiplayer)**: Genellikle **SA-MP**'nin bir halefi veya daha modern bir alternatifi olarak görülen, performans, kararlılık ve ek işlevsellik iyileştirmeleri sunan açık kaynaklı bir proje. `omp-client.dll` gerektirir.

Benzer şekilde çalışmalarına rağmen (**GTA:SA** sürecine bir **DLL enjekte ederek**), **SA-MP Injector PowerShell** kütüphanesi, dosya adı farklılıklarını tanıyarak ve geliştiricinin bir yapılandırma parametresi aracılığıyla istenen çok oyunculu istemciyi seçmesine izin vererek **her iki DLL'yi de** destekleyecek şekilde dikkatlice geliştirilmiştir. Bu, kütüphanenin her iki platforma dayalı geniş bir sunucu ve proje yelpazesiyle kullanılabilmesini sağlar.

### PowerShell'de DLL Enjeksiyonu: WinAPI ile Doğrudan Bir Yaklaşım

PowerShell, Windows'ta otomasyon için güçlü bir betik dilidir, ancak süreçleri manipüle etmek ve bu kadar düşük sistem seviyesinde DLL enjekte etmek birincil işlevi değildir. Bu hedefe ulaşmak için, **SA-MP Injector PowerShell** kütüphanesi, **Windows API (WinAPI)** fonksiyonlarını doğrudan çağırmak için `Add-Type` komutunu kapsamlı bir şekilde kullanır.

`Add-Type`, PowerShell ortamında C# kodunu (veya diğer .NET dillerini) çalışma zamanında tanımlamaya ve derlemeye olanak tanır. Bu C# kodu, yerel WinAPI fonksiyonlarına (`DllImport`) bir "köprü" görevi görür ve aşağıdaki gibi işlemleri mümkün kılar:

- **`CreateProcessA`**: GTA:SA sürecini başlatmak için.
- **`VirtualAllocEx`**: Uzak süreç içinde bellek ayırmak için.
- **`WriteProcessMemory`**: DLL yolunu ayrılan belleğe kopyalamak için.
- **`GetModuleHandleA` ve `GetProcAddress`**: `kernel32.dll` içindeki `LoadLibraryA` fonksiyonunun adresini almak için.
- **`CreateRemoteThread`**: Uzak süreçte `LoadLibraryA`'yı çalıştıran bir iş parçacığı oluşturarak DLL'yi etkili bir şekilde yüklemek için.
- **`WaitForSingleObject` ve `GetExitCodeThread`**: Enjeksiyonun başarısını izlemek için.
- **`ResumeThread`**: Enjeksiyondan sonra oyun sürecini yeniden etkinleştirmek için.
- **`CloseHandle`**: Sistem kaynaklarının tanıtıcılarını kapatmak ve sızıntıları önlemek için.
- **`MessageBoxW`**: Kullanıcıya bilgilendirici hata mesajları göstermek için.

WinAPI ile bu doğrudan yaklaşım, PowerShell'in derlenmiş bir **C++** uygulamasının yapacağı aynı düşük seviyeli işlemleri bir betik ortamının rahatlığıyla gerçekleştirmesini sağlar.

## Kütüphanenin Dahili Mimarisi: Derinlemesine Bir Bakış

**SA-MP Injector PowerShell** kütüphanesi, enjeksiyon sürecinin karmaşıklığını yönetmek için modüler bir yaklaşım benimser. Her betik, genel işlevselliğin belirli bir bölümünden sorumlu olan uzmanlaşmış bir modüldür ve kodun netliğini, sürdürülebilirliğini ve genişletilebilirliğini teşvik eder.

### `Constants.ps1`

Bu betik, kütüphanenin tüm sabit yapılandırmalarının temelidir. Port limitleri, DLL dosya adları, sistem API'lerine referanslar ve süreç oluşturma ve bellek ayırma gibi işlemler için bayraklar gibi kullanılan tüm değişmezleri ve sayısal değerleri depolayan genel bir hash tablosu (`$global:CONSTANTS`) tanımlar.

```powershell
$global:CONSTANTS = @{
    # Port doğrulama limitleri
    MIN_PORT = 1
    MAX_PORT = 65535
    
    # Takma ad kısıtlamaları
    MAX_NICKNAME_LENGTH = 20
    
    # Gerekli dosya adları
    SAMP_DLL_NAME = "samp.dll"
    OMP_DLL_NAME = "omp-client.dll"
    GAME_EXE_NAME = "gta_sa.exe"
    
    # Sistem API referansları
    KERNEL32_DLL = "kernel32.dll"
    USER32_DLL = "user32.dll" # MessageBoxW için kullanılır
    LOAD_LIBRARY_FUNC = "LoadLibraryA"
    
    # Komut satırı argümanı önekleri
    CMD_ARG_CONFIG = "-c"
    CMD_ARG_NICKNAME = "-n"
    CMD_ARG_HOST = "-h"
    CMD_ARG_PORT = "-p"
    CMD_ARG_PASSWORD = "-z"
    
    # Enjeksiyon tipi tanımlayıcıları
    INJECT_TYPE_SAMP = "samp"
    INJECT_TYPE_OMP = "omp"
    
    # Hata diyalog başlıkları
    ERROR_TITLE_SAMP = "SA-MP Injector Error - SPC"
    ERROR_TITLE_OMP = "OMP Injector Error - SPC"
    
    # Süreç oluşturma bayrakları (CREATE_SUSPENDED | DETACHED_PROCESS)
    # 0x00000104 = CREATE_SUSPENDED (0x4) + DETACHED_PROCESS (0x100)
    PROCESS_CREATION_FLAGS = 0x00000104
    
    # İşlem zaman aşımları
    DLL_INJECTION_TIMEOUT_MS = 10000 # 10 saniye
    
    # Bellek ayırma sabitleri
    # 0x00003000 = MEM_COMMIT (0x1000) + MEM_RESERVE (0x2000)
    MEMORY_ALLOCATION_TYPE = 0x00003000
    # 0x00000004 = PAGE_READWRITE
    MEMORY_PROTECTION = 0x00000004
    # 0x00008000 = MEM_RELEASE
    MEMORY_FREE_TYPE = 0x00008000
    
    # Bekleme nesnesi sonuçları (Windows API)
    WAIT_OBJECT_0 = 0x00000000
    WAIT_TIMEOUT = 0x00000102
    WAIT_FAILED = 0xFFFFFFFF
    
    # İş parçacığı sürdürme hata göstergesi (Windows API)
    THREAD_RESUME_ERROR = 0xFFFFFFFF # ResumeThread başarısız olduğunda -1 döndürür
    
    # MessageBox sabitleri (Windows API)
    MB_OK = 0x00000000
    MB_ICONERROR = 0x00000010
    MB_TOPMOST = 0x00040000
}
```

> [!TIP]
> Sabitler için genel bir hash tablosu kullanmak, PowerShell betiklerinde yaygın bir uygulamadır. Ayarları merkezileştirir ve "sihirli sayıları" ve tekrarlanan dizeleri önleyerek kodu daha okunaklı ve bakımı kolay hale getirir. Bayrakların değerleri (`0x...`), Windows API'de tanımlanan sabitlerin ondalık değerlerine karşılık gelir.

### `CustomTypes.ps1`

Bu betik, Windows API ile etkileşim için temeldir. `Add-Type` kullanarak çalışma zamanında C# türleri tanımlar, bunlar şunları içerir:

- **`Inject_Type` enum**: Enjeksiyon türünü (SAMP veya OMP) kategorize etmek için, tür güvenliğini artırır.
- **`WinAPI` class**: Enjeksiyon için gerekli olan Windows API fonksiyonlarını içe aktaran ve sunan statik bir sınıf. Bu sınıftaki her yöntem, doğru imza ve karakter seti (`CharSet`) ile bir API fonksiyonuna (`DllImport`) karşılık gelir.
- **`Startup_Info` struct ve `Process_Information` struct**: Windows API'nin `CreateProcessA` fonksiyonu tarafından kullanılan `STARTUPINFO` ve `PROCESS_INFORMATION` yapılarını kopyalayan C# veri yapıları.
- **`Process_Info` class**: Başarılı bir süreç oluşturulduktan sonra döndürülen süreç ve iş parçacığı tanıtıcıları için bir kapsayıcı görevi gören basit bir C# sınıfı, bu tanıtıcıların PowerShell ortamında taşınmasını ve yönetilmesini kolaylaştırır.

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
        using System.Text; // Marshal.GetLastWin32Error için gerekli
        
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
            
            // STARTUPINFO için C# yapısı
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
            
            // PROCESS_INFORMATION için C# yapısı
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
        
        // Süreç ve iş parçacığı tanıtıcılarını taşımak için yardımcı sınıf
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
> 32 bitlik DLL'lerin (`samp.dll` ve `omp-client.dll`) 32 bitlik bir sürece (`gta_sa.exe`) enjekte edilmesi, **PowerShell ortamının da 32 bit olmasını gerektirir**. **SA-MP Injector PowerShell**, x64 bir ortamda çalıştığını tespit ederse kendisini otomatik olarak bir PowerShell x86 kabuğunda yeniden başlatarak bu durumu yönetir. Bu, işaretçi boyutlarının uyumluluğunu ve enjeksiyonun doğru çalışmasını sağlamak için çok önemlidir.
>
> `if (-not ([System.Management.Automation.PSTypeName]'TypeName').Type)` yönergesi, C# türlerinin PowerShell ortamına yalnızca bir kez eklenmesini sağlar, betiğin aynı oturumda birden çok kez çalıştırılması durumunda yeniden tanımlama hatalarını önler.

### `StringUtils.ps1`

Bu modül, eski Windows API ("A" char* fonksiyonları) ile etkileşim kurarken gerekli olan karakter kodlamalarını işlemek için özellikle dizelerin manipülasyonu için temel bir yardımcı fonksiyon sağlar.

```powershell
function Convert_Wide_To_Local_8Bit {
    param([Parameter(Mandatory = $false)] [AllowEmptyString()] [string]$wide_string)
    
    if ([string]::IsNullOrEmpty($wide_string)) {
        return [string]::Empty
    }

    try {
        # Sistemin yerel ANSI kod sayfasını al
        $ansi_code_page = [System.Globalization.CultureInfo]::CurrentCulture.TextInfo.ANSICodePage
        $encoding = [System.Text.Encoding]::GetEncoding($ansi_code_page)
        
        # Unicode (geniş) dizeyi yerel ANSI kodlamasında baytlara dönüştür
        $bytes = $encoding.GetBytes($wide_string)

        # Baytları aynı ANSI kodlamasını kullanarak tekrar bir dizeye dönüştür
        # Bu, dizenin 8 bit (ANSI) kodlama bekleyen API'lerle uyumlu olmasını sağlar
        return $encoding.GetString($bytes)
    }
    catch {
        # Dönüştürme hatası durumunda (ör. eşlenemeyen karakterler),
        # orijinal dizeyi bir geri dönüş olarak döndürür, ancak ANSI API'leri tarafından desteklenmeyen karakterler içeriyorsa sorunlara neden olabilir.
        return $wide_string
    }
}
```

> [!IMPORTANT]
> `Convert_Wide_To_Local_8Bit` fonksiyonu çok önemlidir çünkü "A" sonekli birçok Windows API fonksiyonu (`CreateProcessA`, `LoadLibraryA`, `GetModuleHandleA`, `GetProcAddress`), yerel sistem kod sayfasına bağlı olan ANSI (8-bit) kodlanmış dizeler bekler. Varsayılan olarak, PowerShell'deki dizeler Unicode'dur. Bu fonksiyon gerekli dönüşümü gerçekleştirir. Dosya adı veya komut satırı argümanı, sistemin ANSI kod sayfası dışındaki karakterleri içeriyorsa, dönüşüm yanlış karakterlere veya veri kaybına neden olabilir. Eski programlarla etkileşim kurmayı amaçlayan bu proje için bu ANSI yaklaşımı genellikle yeterli ve gereklidir.

### `ErrorUtils.ps1`

Bu modül, bir arıza durumunda kullanıcıya net geri bildirim sağlamaktan sorumludur. Sistemden hata mesajlarını alma ve standart Windows diyalog kutularını görüntüleme mantığını merkezileştirir.

```powershell
function Get_System_Error_Message {
    param([Parameter(Mandatory = $true)][int]$error_code)
    
    try {
        # Sistem tarafından biçimlendirilmiş hata mesajını almak için Win32Exception kullan
        $exception = New-Object System.ComponentModel.Win32Exception($error_code)
        
        return $exception.Message
    }
    catch {
        # Bilinmeyen hata mesajı için geri dönüş
        return "Unknown error (Code: $error_code)"
    }
}

function Show_Error {
    param([Parameter(Mandatory = $true)][string]$message, [Parameter(Mandatory = $true)][Inject_Type]$inject_type)
    
    # Enjeksiyon türüne göre diyalog kutusu başlığını belirle
    $title = if ($inject_type -eq [Inject_Type]::SAMP) {
        $global:CONSTANTS.ERROR_TITLE_SAMP
    }
    else {
        $global:CONSTANTS.ERROR_TITLE_OMP
    }
    
    try {
        # MessageBoxW için bayrakları birleştir (OK, Hata Simgesi, AlwaysOnTop)
        $message_box_flags = $global:CONSTANTS.MB_OK -bor $global:CONSTANTS.MB_ICONERROR -bor $global:CONSTANTS.MB_TOPMOST
        
        # Add-Type aracılığıyla içe aktarılan MessageBoxW fonksiyonunu çağır
        [void][WinAPI]::MessageBoxW([System.IntPtr]::Zero, $message, $title, $message_box_flags)
    }
    catch {
        # MessageBox'ı gösterirken hata olması durumunda (ör. UI olmayan ortamlarda), konsola yaz
        Write-Host "[$title] $message" -ForegroundColor Red
    }
}
```

> [!NOTE]
> `Get_System_Error_Message`, bir Windows API sayısal hata kodunu (`GetLastError()`) kullanıcı tarafından okunabilir bir metin açıklamasına dönüştürmek için .NET'in `System.ComponentModel.Win32Exception`'ını kullanır, bu açıklama işletim sisteminin dilinde yerelleştirilmiş olabilir.
>
> `Show_Error`, bilgilendirici bir diyalog kutusu görüntülemek için `user32.dll`'den `Add-Type` (`CustomTypes.ps1`) aracılığıyla içe aktarılan `MessageBoxW` fonksiyonunu kullanır. `MB_OK` ve `MB_ICONERROR` gibi bayraklar WinAPI sabitlerinden içe aktarılır.

### `Process.ps1`

Bu, süreçleri işlemek için düşük seviyeli Windows API'leri ile doğrudan etkileşimden sorumlu ana modüldür. Süreç oluşturma ve DLL enjeksiyonunun kritik operasyonlarını kapsar, tanıtıcıları, belleği ve iş parçacıklarını yönetir.

```powershell
class Process {
    # Süreç ve iş parçacığı tanıtıcılarını serbest bırakır, kaynak sızıntılarını önler
    [void] Close_Process_Info([Process_Info]$process_info) {
        if ($null -ne $process_info) {
            # Geçerliyse süreç tanıtıcısını kapat
            if ($process_info.ProcessHandle -ne [System.IntPtr]::Zero -and $process_info.ProcessHandle -ne [System.IntPtr]::new(-1)) {
                [void][WinAPI]::CloseHandle($process_info.ProcessHandle)
                $process_info.ProcessHandle = [System.IntPtr]::Zero # Kapalı olarak işaretle
            }

            # Geçerliyse iş parçacığı tanıtıcısını kapat
            if ($process_info.ThreadHandle -ne [System.IntPtr]::Zero -and $process_info.ThreadHandle -ne [System.IntPtr]::new(-1)) {
                [void][WinAPI]::CloseHandle($process_info.ThreadHandle)
                $process_info.ThreadHandle = [System.IntPtr]::Zero # Kapalı olarak işaretle
            }
        }
    }

    # GTA:SA oyun sürecini askıya alınmış durumda oluşturur
    [Process_Info] Create_Game_Process([string]$game_path, [string]$command_args, [string]$working_dir) {
        $startup_info = New-Object WinAPI+Startup_Info
        # Yapının boyutunu ayarla, Windows API'leri için çok önemli
        $startup_info.cb = [System.Runtime.InteropServices.Marshal]::SizeOf($startup_info)
        
        $process_information = New-Object WinAPI+Process_Information
        
        $command_line_bytes = $null

        if (-not [string]::IsNullOrEmpty($command_args)) {
            # Komut satırı argümanlarını null sonlandırıcı ile bir ANSI bayt dizisine dönüştür
            $command_line_bytes = [System.Text.Encoding]::Default.GetBytes($command_args + "`0")
        }
        
        # Çalışma dizinini ayarla, boşsa null
        $current_directory = if ([string]::IsNullOrEmpty($working_dir)) {
            $null
        }
        else {
            $working_dir
        }
        
        # Windows API'nin CreateProcessA fonksiyonunu çağır
        $success = [WinAPI]::CreateProcessA($game_path, $command_line_bytes, [System.IntPtr]::Zero, [System.IntPtr]::Zero, $false, $global:CONSTANTS.PROCESS_CREATION_FLAGS, 
            [System.IntPtr]::Zero, $current_directory, [ref]$startup_info, [ref]$process_information)
        
        if (-not $success) {
            # Başarısızlık durumunda, sistemin son hatasını al ve göster
            $error_code = [System.Runtime.InteropServices.Marshal]::GetLastWin32Error()
            $error_message = Get_System_Error_Message $error_code
            Show_Error "Failed to create game process. Ensure 'gta_sa.exe' is not running and you have sufficient permissions to execute the file. System Error: $error_message" ([Inject_Type]::SAMP)

            return $null # Başarısızlık durumunda null döndür
        }
        
        # Süreç ve iş parçacığı tanıtıcılarını içeren bir Process_Info nesnesi döndür
        $result = New-Object Process_Info
        $result.ProcessHandle = $process_information.hProcess
        $result.ThreadHandle = $process_information.hThread
        
        return $result
    }
    
    # Uzak sürece bir DLL enjekte eder
    [bool] Inject_DLL([IntPtr]$process_handle, [string]$dll_path, [ref]$error_message) {
        if ($process_handle -eq [System.IntPtr]::Zero) {
            $error_message.Value = "Invalid process handle provided for DLL injection."

            return $false
        }
        
        if ([string]::IsNullOrEmpty($dll_path)) {
            $error_message.Value = "DLL path cannot be empty."

            return $false
        }
        
        # DLL yolunu null sonlandırıcı ile ASCII (ANSI 8-bit) baytlarına dönüştür
        $dll_path_bytes = [System.Text.Encoding]::ASCII.GetBytes($dll_path + "`0")
        $dll_path_size = $dll_path_bytes.Length
        
        # DLL yolu için uzak süreçte bellek ayır
        $remote_memory = [WinAPI]::VirtualAllocEx($process_handle, [System.IntPtr]::Zero, $dll_path_size, $global:CONSTANTS.MEMORY_ALLOCATION_TYPE, $global:CONSTANTS.MEMORY_PROTECTION)
        
        if ($remote_memory -eq [System.IntPtr]::Zero) {
            $error_code = [System.Runtime.InteropServices.Marshal]::GetLastWin32Error()
            $error_message.Value = "Failed to allocate memory in the target process. This might be due to insufficient permissions or process protection mechanisms. System Error: $(Get_System_Error_Message $error_code)"

            return $false
        }
        
        # Uzak belleğin serbest bırakılmasını sağlamak için bir try/finally bloğu kullan
        try {
            $bytes_written = [System.IntPtr]::Zero
            # DLL yolunu uzak belleğe yaz
            $write_success = [WinAPI]::WriteProcessMemory($process_handle, $remote_memory, $dll_path_bytes, $dll_path_size, [ref]$bytes_written)
            
            if (-not $write_success) {
                $error_code = [System.Runtime.InteropServices.Marshal]::GetLastWin32Error()
                $error_message.Value = "Failed to write DLL path to the target process memory. Verify process permissions and ensure the DLL path is accessible. System Error: $(Get_System_Error_Message $error_code)"
                
                return $false
            }
            
            # kernel32.dll için tanıtıcı al (tüm süreçlerde yüklüdür)
            $kernel32_handle = [WinAPI]::GetModuleHandleA($global:CONSTANTS.KERNEL32_DLL)

            if ($kernel32_handle -eq [System.IntPtr]::Zero) {
                $error_code = [System.Runtime.InteropServices.Marshal]::GetLastWin32Error()
                $error_message.Value = "Failed to obtain a handle to kernel32.dll. This is an essential system library and this error indicates a severe system issue. System Error: $(Get_System_Error_Message $error_code)"
                
                return $false
            }
            
            # kernel32.dll'deki LoadLibraryA fonksiyonunun adresini al.
            # Bu adres aynı işletim sistemindeki süreçler arasında tutarlıdır.
            $load_library_address = [WinAPI]::GetProcAddress($kernel32_handle, $global:CONSTANTS.LOAD_LIBRARY_FUNC)

            if ($load_library_address -eq [System.IntPtr]::Zero) {
                $error_code = [System.Runtime.InteropServices.Marshal]::GetLastWin32Error()
                $error_message.Value = "Failed to find the address of the LoadLibraryA function in kernel32.dll. This is critical for injecting the DLL. System Error: $(Get_System_Error_Message $error_code)"
                
                return $false
            }
            
            $thread_id = [System.IntPtr]::Zero
            # LoadLibraryA'yı çalıştırmak için hedef süreçte uzak bir iş parçacığı oluştur
            $remote_thread_handle = [WinAPI]::CreateRemoteThread($process_handle, [System.IntPtr]::Zero, 0, $load_library_address, $remote_memory, 0, [ref]$thread_id)
            
            if ($remote_thread_handle -eq [System.IntPtr]::Zero) {
                $error_code = [System.Runtime.InteropServices.Marshal]::GetLastWin32Error()
                $error_message.Value = "Failed to create a remote thread in the target process to execute the DLL injection. This could be due to security restrictions or process state. System Error: $(Get_System_Error_Message $error_code)"
                
                return $false
            }
            
            # Uzak iş parçacığı tanıtıcısının kapatılmasını sağlamak için bir try/finally bloğu kullan
            try {
                # Uzak iş parçacığının (DLL enjeksiyonu) tamamlanmasını veya bir zaman aşımına ulaşmasını bekle
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
                # Uzak iş parçacığının çıkış kodunu al. LoadLibraryA için 0 başarısızlık anlamına gelir.
                $get_exit_code_success = [WinAPI]::GetExitCodeThread($remote_thread_handle, [ref]$exit_code)
                
                if (-not $get_exit_code_success -or $exit_code -eq 0) {
                    $error_code = [System.Runtime.InteropServices.Marshal]::GetLastWin32Error()
                    $error_message.Value = "DLL injection failed or returned an error. The LoadLibrary call may have failed in the target process. Exit Code: $exit_code. System Error: $(Get_System_Error_Message $error_code)"

                    return $false
                }
                
                return $true # Enjeksiyon başarılı
            }
            finally {
                # Uzak iş parçacığı tanıtıcısının kapatılmasını sağla
                [void][WinAPI]::CloseHandle($remote_thread_handle)
            }
        }
        finally {
            # Uzaktan ayrılan belleğin serbest bırakılmasını sağla
            # MEM_RELEASE'de dwSize için 0, VirtualAllocEx tarafından ayrılan tüm bölgeyi serbest bırakır
            [void][WinAPI]::VirtualFreeEx($process_handle, $remote_memory, 0, $global:CONSTANTS.MEMORY_FREE_TYPE)
        }
    }
}
```

> [!NOTE]
> `Process` sınıfı, Windows tanıtıcılarını temsil etmek için `[System.IntPtr]` kullanır. Tanıtıcıların (`ProcessHandle`, `ThreadHandle`, `remote_memory`, `remote_thread_handle`) kapatıldığından ve belleğin hata durumunda bile doğru bir şekilde serbest bırakıldığından emin olmak için `try/finally`'nin kapsamlı kullanımına dikkat etmek önemlidir. Bu, PowerShell'de **RAII** (Resource Acquisition Is Initialization) ilkesini uygulamanın bir yoludur, ancak dilin sözdizimine daha az entegre edilmiştir.

### `InjectorCore.ps1`

Bu, önceki modüllerin tüm işlevlerini bir araya getiren düzenleyici sınıftır. Doğrulama, komut satırı argümanlarının oluşturulması, süreç oluşturma ve DLL enjeksiyonu çağrılarını koordine eder.

```powershell
class Injector_Core {
    # Oyunun başlatılmasını ve enjeksiyonunu düzenleyen ana fonksiyon
    [bool] Initialize_Game([Inject_Type]$inject_type, [string]$folder, [string]$nickname, [string]$ip, [string]$port, [string]$password) {
        # Temel dosyalar için tam yolları oluştur
        $game_path = Join-Path -Path $folder -ChildPath $global:CONSTANTS.GAME_EXE_NAME
        $samp_dll_path = Join-Path -Path $folder -ChildPath $global:CONSTANTS.SAMP_DLL_NAME
        $omp_dll_path = Join-Path -Path $folder -ChildPath $global:CONSTANTS.OMP_DLL_NAME
        
        $validation_error = [string]::Empty # Doğrulama hata mesajlarını yakalamak için değişken
        
        # 1. Dosya Doğrulaması
        if (-not (Validate_Files $game_path $samp_dll_path $omp_dll_path $inject_type)) {
            # Hata zaten doğrulama fonksiyonu tarafından gösterildi
            return $false
        }

        # 2. Port Doğrulaması
        if (-not (Validate_Port $port ([ref]$validation_error))) {
            Show_Error $validation_error $inject_type
            return $false
        }
        
        # 3. Takma Ad Doğrulaması
        if (-not (Validate_Nickname $nickname ([ref]$validation_error))) {
            Show_Error $validation_error $inject_type
            return $false
        }
        
        # 4. Dizelerin ANSI/8-bit Kodlamasına Dönüştürülmesi (eski API'ler için gerekli)
        $converted_nickname = Convert_Wide_To_Local_8Bit $nickname
        $converted_ip = Convert_Wide_To_Local_8Bit $ip
        $converted_port = Convert_Wide_To_Local_8Bit $port
        $converted_password = Convert_Wide_To_Local_8Bit $password
        $converted_game_path = Convert_Wide_To_Local_8Bit $game_path
        $converted_folder = Convert_Wide_To_Local_8Bit $folder
        $converted_samp_dll_path = Convert_Wide_To_Local_8Bit $samp_dll_path
        $converted_omp_dll_path = Convert_Wide_To_Local_8Bit $omp_dll_path
        
        # 5. Komut Satırı Argümanlarının Oluşturulması
        $command_arguments = $this.Build_Command_Args($converted_nickname, $converted_ip, $converted_port, $converted_password)
        
        $process_manager = New-Object Process # Process sınıfını örneklendir
        $process_info = $null # Oluşturulan süreç bilgilerini saklamak için değişken
        
        # Süreç tanıtıcılarının kapatılmasını sağlamak için bir try/finally bloğu kullan
        try {
            # 6. Oyun Sürecinin Oluşturulması (Askıya Alınmış)
            $process_info = $process_manager.Create_Game_Process($converted_game_path, $command_arguments, $converted_folder)
            
            if ($null -eq $process_info) {
                # Hata zaten süreç oluşturma fonksiyonu tarafından gösterildi
                return $false
            }

            $injection_error = [string]::Empty # Enjeksiyon hata mesajlarını yakalamak için değişken
            
            # 7. samp.dll'in Enjeksiyonu
            if (-not $process_manager.Inject_DLL($process_info.ProcessHandle, $converted_samp_dll_path, ([ref]$injection_error))) {
                Show_Error "Failed to inject samp.dll: $injection_error" $inject_type
                return $false
            }
            
            # 8. omp-client.dll'in koşullu enjeksiyonu (sadece enjeksiyon türü OMP ise)
            if ($inject_type -eq [Inject_Type]::OMP) {
                if (-not $process_manager.Inject_DLL($process_info.ProcessHandle, $converted_omp_dll_path, ([ref]$injection_error))) {
                    Show_Error "Failed to inject omp-client.dll: $injection_error" $inject_type
                    return $false
                }
            }
            
            # 9. Oyun Sürecini Sürdür
            # Süreç, enjeksiyona izin vermek için askıya alınmış durumda oluşturuldu.
            # Şimdi DLL'ler enjekte edildiğine göre, devam ettirilebilir.
            $resume_result = [WinAPI]::ResumeThread($process_info.ThreadHandle)

            if ($resume_result -eq $global:CONSTANTS.THREAD_RESUME_ERROR) {
                $error_code = [System.Runtime.InteropServices.Marshal]::GetLastWin32Error()
                $error_message = Get_System_Error_Message $error_code
                Show_Error "Failed to resume the game process thread: $error_message" $inject_type

                return $false
            }
            
            return $true # Tüm adımlarda başarılı!
        }
        finally {
            # Süreç tanıtıcılarının sonunda kapatılmasını sağla,
            # başarı veya başarısızlığa bakılmaksızın.
            if ($null -ne $process_info) {
                $process_manager.Close_Process_Info($process_info)
            }
        }
    }
    
    # Oyun yürütülebilir dosyası için komut satırı argümanları dizesini oluşturur
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
> **OMP** için enjeksiyon, `samp.dll`'nin *yanı sıra* `omp-client.dll`'yi de içerir. Bu, **OMP**'nin genellikle çalışma şekline uygundur, çünkü `samp.dll`'yi temel olarak kullanabilir ve `omp-client.dll` ile işlevselliği genişletebilir. OMP enjeksiyonunun başarılı olması için **her iki DLL'nin de** oyun dizininde mevcut ve işlevsel olması çok önemlidir. Biri başarısız olursa, oyun doğru şekilde başlamayabilir veya çok oyunculu istemci yüklenmeyebilir.
>
> PowerShell'in C++ gibi yerel bir `std::optional` veya **RAII** garantisine sahip olmaması nedeniyle, kodun `Initialize_Game` fonksiyonunda `Close_Process_Info`'nun çağrıldığından ve bir hata oluşsa bile tanıtıcıların serbest bırakıldığından emin olmak için açık bir `try/finally` bloğu kullandığına dikkat edin. Bu, PowerShell'de kaynak temizliği için iyi bir uygulamadır.

### `Injector.ps1`

Bu, kütüphanenin ana giriş betiğidir. Diğer modüllerin yüklenmesini, PowerShell ortamının doğrulanmasını (enjeksiyon uyumluluğu için x86 olup olmadığını kontrol ederek) ve `Injector_Core` sınıfının başlatılmasını yönetir. Son kullanıcının çalıştıracağı betiktir.

```powershell
param([Parameter(Mandatory = $true, Position = 0)][ValidateNotNullOrEmpty()][string]$inject_type,
    [Parameter(Mandatory = $true, Position = 1)][ValidateNotNullOrEmpty()][string]$folder,
    [Parameter(Mandatory = $true, Position = 2)][ValidateNotNullOrEmpty()][string]$nickname,
    [Parameter(Mandatory = $true, Position = 3)][ValidateNotNullOrEmpty()][string]$ip,
    [Parameter(Mandatory = $true, Position = 4)][ValidateNotNullOrEmpty()][string]$port,
    [Parameter(Position = 5)][AllowEmptyString()][string]$password = "",
    [switch]$restarted_x86) # Betiğin zaten x86'da yeniden başlatıldığını belirtmek için dahili bayrak

$ErrorActionPreference = 'Stop' # Sonlandırıcı olmayan hataların sonlandırıcı hatalar gibi davranmasını sağlar
# Bu, catch bloklarının daha fazla hata yakalamasını ve betiğin beklenmedik şekilde devam etmesini önler.

# Mevcut betiğin tam yolunu al, yardımcı modülleri yüklemek için gerekli
$script_path = $MyInvocation.MyCommand.Path

if ([string]::IsNullOrEmpty($script_path)) {
    # Betiğin özel bir şekilde çağrıldığı durumlarda (ör. boru hattından), $MyInvocation.MyCommand.Path boş olabilir
    $script_path = Join-Path -Path (Get-Location) -ChildPath $MyInvocation.MyCommand.Name
}

$script_directory = Split-Path -Parent $script_path # Kütüphanenin temel dizini
$exit_code = 1 # Varsayılan çıkış kodu (başarısız)

try {
    # Kütüphanenin tüm modüllerini yükle (sabitler, özel türler, yardımcı programlar, vb.)
    . (Join-Path -Path $script_directory -ChildPath "Constants.ps1")
    . (Join-Path -Path $script_directory -ChildPath "CustomTypes.ps1")
    . (Join-Path -Path $script_directory -ChildPath "StringUtils.ps1")
    . (Join-Path -Path $script_directory -ChildPath "ErrorUtils.ps1")
    . (Join-Path -Path $script_directory -ChildPath "Validation.ps1")
    . (Join-Path -Path $script_directory -ChildPath "Process.ps1")
    . (Join-Path -Path $script_directory -ChildPath "InjectorCore.ps1")

    # Kullanıcı için ana arayüz fonksiyonunu tanımla.
    # Bu, Injector_Core sınıfı için bir sarmalayıcıdır.
    function Initialize_Game {
        param([string]$inject_type, [string]$folder, [string]$nickname, [string]$ip, [string]$port, [string]$password = "")

        # PowerShell ortamının x64 olup olmadığını ve henüz x86'da yeniden başlatılıp başlatılmadığını kontrol et
        if ([IntPtr]::Size -eq 8 -and -not $restarted_x86) {
            Write-Host "Detected PowerShell x64 environment. Restarting on PowerShell x86 for DLL injection compatibility (32-bit)..." -ForegroundColor Yellow

            # 32 bit PowerShell yürütülebilir dosyasını bul
            $powershell_x86_path = Join-Path -Path $env:windir -ChildPath "SysWOW64\WindowsPowerShell\v1.0\powershell.exe"

            if (-not (Test-Path -Path $powershell_x86_path)) {
                Write-Host "Could not find powershell.exe (x86) at '$powershell_x86_path'. 32-bit DLL injection may fail." -ForegroundColor Red
                return $false
            }

            # Yeni PowerShell x86 süreci için argüman listesini hazırla
            $argument_list = @("-NoProfile", "-NonInteractive", "-ExecutionPolicy", "Bypass", "-File", $script_path, $inject_type, $folder, $nickname, $ip, $port)
            
            if (-not [string]::IsNullOrEmpty($password)) {
                $argument_list += $password
            }
            # Zaten yeniden başlatıldığını belirtmek için bayrağı ekle
            $argument_list += "-restarted_x86"
            
            try {
                $process_start_info = New-Object System.Diagnostics.ProcessStartInfo
                $process_start_info.FileName = $powershell_x86_path
                # Argümanları StartInfo.Arguments için bir dizeye birleştir
                $process_start_info.Arguments = ($argument_list | ForEach-Object { "`"$_`"" }) -join " " # Boşlukları işlemek için argümanları tırnak içine al
                $process_start_info.RedirectStandardOutput = $true # Alt sürecin çıktısını yönlendir
                $process_start_info.RedirectStandardError = $true   # Alt sürecin hatalarını yönlendir
                $process_start_info.UseShellExecute = $false     # ShellExecute kullanma (doğrudan PowerShell.exe'yi çalıştır)
                $process_start_info.CreateNoWindow = $true       # Alt süreç için yeni bir pencere oluşturma

                $child_process = New-Object System.Diagnostics.Process
                $child_process.StartInfo = $process_start_info
                
                # Alt süreci başlat ve tamamlanmasını bekle
                [void]$child_process.Start()
                $child_process.WaitForExit()
                
                # Alt sürecin çıktısını/hatalarını yakala ve göster
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
        
        # Gerçek başlatma mantığı, yalnızca ortam x86 ise veya zaten yeniden başlatılmışsa ulaşılır
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

        $injector_core = New-Object Injector_Core # Ana enjeksiyon sınıfını örneklendir

        # Çağrıyı Injector_Core sınıfının Initialize_Game fonksiyonuna devret
        return $injector_core.Initialize_Game($injection_type, $folder, $nickname, $ip, $port, $password)
    }

    # Ana fonksiyona geçirilen parametreler
    $initialization_parameters = @{
        inject_type = $inject_type
        folder = $folder
        nickname = $nickname
        ip = $ip
        port = $port
        password = $password
    }

    # Enjeksiyon sürecini başlatmak için çağrı
    $game_initialization_result = Initialize_Game @initialization_parameters

    if ($game_initialization_result) {
        $exit_code = 0 # Başarılı
    }
    else {
        $exit_code = 1 # Başarısız
    }
}
catch {
    Write-Host "Critical error during execution: '$($_.Exception.Message)'" -ForegroundColor Red
    $exit_code = 1
}
finally {
    # Temizleme betiğinin sonunda, başarı veya başarısızlığa bakılmaksızın çalıştırılmasını sağla
    try {
        . (Join-Path -Path $script_directory -ChildPath "Cleanup.ps1")
    }
    catch {
        Write-Host "Warning: Cleanup script execution failed: '$($_.Exception.Message)'" -ForegroundColor Yellow
    }
    
    exit $exit_code # Uygun durum koduyla çık
}
```

> [!NOTE]
> Bu betik, enjeksiyon için ana giriş noktasıdır. Sorumlulukları şunlardır:
> - Son kullanıcının kullanacağı **komut satırı parametrelerini** tanımlamak.
> - Daha sıkı bir hata kontrolü için `$ErrorActionPreference = 'Stop'` ayarlamak.
> - "Dot-sourcing" (`. `) kullanarak tüm yardımcı betikleri **yüklemek**, fonksiyonlarının ve sınıflarının mevcut oturumda kullanılabilir olmasını sağlamak.
> - **x86 ortamı için yeniden başlatma** mantığını uygulamak: PowerShell 64 bit'te çalışıyorsa, kendisini otomatik olarak 32 bit bir örnekte (SysWOW64) yeniden başlatır ve aynı argümanları geçirir, çünkü 32 bit DLL'lerin enjeksiyonu 32 bit bir süreçten daha güvenilirdir (ve birçok durumda zorunludur). Bu, PowerShell'i doğrudan x86 için derlenmiş bir C++ uygulamasından ayıran önemli bir özelliktir.
> - Enjeksiyon sürecini başlatmak için `Initialize_Game` fonksiyonunu çağırmak.
> - Betiğin çıkış kodunu yönetmek (0 başarılı, 1 başarısız).
> - `finally` bloğunda `Cleanup.ps1` betiğini çağırmak.

### `Cleanup.ps1`

Bu betik, kütüphane tarafından yüklenen fonksiyonları ve genel değişkenleri mevcut PowerShell oturumundan kaldırmaktan sorumludur. Bu, ortam kirliliğini önlemek ve farklı ayarlarla sonraki betik çalıştırmalarının önceki oturumlardan beklenmedik durumlarla karşılaşmamasını sağlamak için iyi bir uygulamadır.

```powershell
$functions_to_remove = @(
    '*Initialize_Game*', # Fonksiyonları kaldırmak için joker karakter kullanır (takma adları olabilir)
    '*Get_System_Error_Message*',
    '*Show_Error*',
    '*Convert_Wide_To_Local_8Bit*',
    '*Validate_*', # 'Validate_' ile başlayan tüm fonksiyonları kaldır
    '*Build_Command_Args*'
)

# Desenler üzerinde döngü yap ve fonksiyonları kaldır
foreach ($pattern in $functions_to_remove) {
    Get-Command -CommandType Function -Name $pattern -ErrorAction SilentlyContinue | ForEach-Object {
        try {
            Remove-Item -Path "Function:$($_.Name)" -Force -ErrorAction SilentlyContinue
        }
        catch {} # Fonksiyon bir nedenle kaldırılamazsa hataları yoksay
    }
}

$global_variables_to_remove = @(
    'CONSTANTS',
    'CAN_SHOW_MESSAGE_BOX' # Daha fazla genel değişken tanıtılırsa buraya ekleyin
)

# Genel değişkenler üzerinde döngü yap ve onları kaldır
foreach ($variable_name in $global_variables_to_remove) {
    try {
        Remove-Variable -Name $variable_name -Scope Global -Force -ErrorAction SilentlyContinue
    }
    catch {} # Hataları yoksay
}

$variable_patterns_to_remove = @(
    '*_Core*', # '_Core' ile biten değişkenleri kaldır (ör. $injector_core)
    '*Process*' # 'Process' ile biten değişkenleri kaldır (ör. $process_manager)
)

# Farklı kapsamlardaki değişkenleri desenler kullanarak kaldır
foreach ($scope in @('Script', 'Local')) {
    foreach ($pattern in $variable_patterns_to_remove) {
        Get-Variable -Scope $scope -Name $pattern -ErrorAction SilentlyContinue | ForEach-Object {
            try {
                Remove-Variable -Name $_.Name -Scope $scope -Force -ErrorAction SilentlyContinue
            }
            catch {} # Hataları yoksay
        }
    }
}
```

> [!TIP]
> Temizlik, oturuma birçok öğe içe aktaran PowerShell betiklerinde çok önemlidir. `Remove-Item -Path "Function:..."` ve `Remove-Variable`, bu öğeleri serbest bırakmak için kullanılır. Kaldırma döngülerinde `ErrorAction SilentlyContinue` ve boş `try/catch` kullanımı, bir öğe zaten kaldırılmışsa veya mevcut değilse temizleme betiğinin başarısız olmamasını sağlar.

## Kapsamlı Kullanım Örnekleri

**SA-MP Injector PowerShell**'i projenize entegre etmek veya doğrudan kullanmak için aşağıdaki talimatları izleyin ve senaryoları analiz edin.

### 1. Geliştirme Ortamının Hazırlanması

- **PowerShell Version**: **PowerShell 5.1** veya üstü önerilir (sınıflar için `Add-Type` ile uyumlu).
- **Yürütme İzinleri**: PowerShell'in yürütme politikaları vardır. Yerel betiklerin yürütülmesine izin vermeniz gerekecektir. PowerShell'i **Yönetici** olarak açın ve şunu çalıştırın:
   ```powershell
   Set-ExecutionPolicy -ExecutionPolicy RemoteSigned -Scope CurrentUser
   ```
   Bu, imzalı betiklerin çalışmasına ve oluşturduğunuz (internetten indirilmemiş) betiklerin imzasız olarak yerel olarak çalışmasına izin verecektir.
- **Dosyaları Kopyala**: Kütüphanenin tüm `.ps1` dosyalarını (`Injector.ps1`, `Constants.ps1`, `CustomTypes.ps1`, `StringUtils.ps1`, `ErrorUtils.ps1`, `Validation.ps1`, `Process.ps1`, `InjectorCore.ps1`, `Cleanup.ps1`) tek bir dizine yerleştirin.
- **Süreç İzinleri**: Betiğinizin süreçler oluşturmak ve başka bir sürece DLL enjekte etmek için **Yönetici** ayrıcalıklarına ihtiyacı olacaktır. Bu kütüphaneyi kullanırken PowerShell'i her zaman **Yönetici olarak çalıştırın**.

### 2. Temel Senaryo: Bir SA-MP Sunucusuna Bağlanma

Bu en yaygın kullanım durumudur, GTA:SA'yı başlatır ve belirli bir takma ad ve IP/port ile bir SA-MP sunucusuna bağlanır.

```powershell
# Örneğin, "StartSAMP.ps1" adında yeni bir betik oluşturun

# SA-MP Injector PowerShell kütüphanesinden ana fonksiyonu içe aktar
# Aşağıdaki yolun Injector.ps1'in bulunduğu yeri yansıttığından emin olun.
# Örneğin, Injector.ps1 bu betikle aynı klasördeyse:
$injector_path = Join-Path -Path $PSScriptRoot -ChildPath "Injector.ps1"

# Veya bir alt dizindeyse:
# $injector_path = Join-Path -Path $PSScriptRoot -ChildPath "SA-MP-Injector-PowerShell\Injector.ps1"

# Injector.ps1 fonksiyonunu dot-sourcing kullanarak içe aktararak fonksiyonlarının
# mevcut kapsamda kullanılabilir olmasını sağlayın.
. $injector_path

# Yapılandırma değişkenlerini tanımlayın
# Bu yolları ve sunucu ayrıntılarını yerel yapılandırmanızla eşleşecek şekilde değiştirin.
$game_folder = "C:\Games\GTA San Andreas" # gta_sa.exe, samp.dll'in bulunduğu yer
$player_nickname = "Isim"
$server_ip = "127.0.0.1" # Örnek: yerel sunucunuz
$server_port = "7777"
$server_password = "" # Şifre yoksa boş bırakın

Write-Host "SA-MP başlatılıyor..." -ForegroundColor Cyan
Write-Host "Oyun klasörü: $game_folder" -ForegroundColor Gray
Write-Host "Takma ad: $player_nickname" -ForegroundColor Gray
Write-Host "Sunucu: $server_ip:$server_port" -ForegroundColor Gray

# Oyunu başlatmak için kütüphane fonksiyonuna çağrı
$result = Initialize_Game `
    -inject_type "samp" ` # Enjeksiyon türü: "samp" veya "omp"
    -folder $game_folder ` # Oyun klasörünün yolu
    -nickname $player_nickname ` # İstenen takma ad
    -ip $server_ip ` # Sunucu IP'si
    -port $server_port ` # Sunucu portu (dize)
    -password $server_password # Sunucu şifresi (dize, boş olabilir)

if ($result) {
    Write-Host "`n--- SA-MP başarıyla başlatıldı! ---" -ForegroundColor Green
    Write-Host "Oyun ayrı bir süreçte başlatıldı." -ForegroundColor Green
}
else {
    Write-Host "`n--- SA-MP BAŞLATILAMADI! ---" -ForegroundColor Red
    Write-Host "Görüntülenen hata mesajlarını (açılır pencereler veya konsol) kontrol edin." -ForegroundColor Red
}

# Çıkış mesajlarını görüntülemek için konsolu açık tutun
Read-Host "`nProgramı kapatmak için Enter'a basın."
```

**Betiği çalıştırmak için:**
1.  Yukarıdaki kodu `StartSAMP.ps1` olarak (veya `.ps1` ile bittiği sürece herhangi bir adla) **kaydedin**.
2.  **SA-MP Injector PowerShell** kütüphanesinin tüm dosyalarını aynı klasöre veya `$injector_path` ile yöneteceğiniz bir alt klasör yapısına **kaydedin**.
3.  **PowerShell'i Yönetici olarak açın**.
4.  `StartSAMP.ps1`'i kaydettiğiniz dizine gidin.
5.  Betiği çalıştırın:
   ```powershell
   .\StartSAMP.ps1
   ```
   (Mevcut dizindeki betikler için betik adının önündeki `.` gereklidir, eğer onu PATH'e eklemediyseniz).

### 3. Gelişmiş Senaryo: Bir OMP Sunucusuna Bağlanma

OMP için mantık, SA-MP ile aynıdır, ancak `inject_type` olarak `"omp"` belirtirsiniz ve `omp-client.dll`'nin oyun dizininde bulunduğundan emin olursunuz.

```powershell
# Örneğin, "StartOMP.ps1" adında yeni bir betik oluşturun

# SA-MP Injector PowerShell kütüphanesinden ana fonksiyonu içe aktar
$injector_path = Join-Path -Path $PSScriptRoot -ChildPath "Injector.ps1"
. $injector_path

# OMP için yapılandırma değişkenlerini tanımlayın
$game_folder = "C:\Games\GTA San Andreas" # gta_sa.exe, samp.dll ve omp-client.dll'in bulunduğu yer
$player_nickname = "Isim"
$server_ip = "127.0.0.1" # Örnek: yerel sunucunuz
$server_port = "7777"
$server_password = "" # Şifre yoksa boş bırakın

Write-Host "OMP başlatılıyor..." -ForegroundColor Cyan
Write-Host "Oyun klasörü: $game_folder" -ForegroundColor Gray
Write-Host "Takma ad: $player_nickname" -ForegroundColor Gray
Write-Host "Sunucu: $server_ip:$server_port" -ForegroundColor Gray

# Oyunu başlatmak için kütüphane fonksiyonuna çağrı
$result = Initialize_Game `
    -inject_type "omp" `   # Enjeksiyon türü: "omp"
    -folder $game_folder `
    -nickname $player_nickname `
    -ip $server_ip `
    -port $server_port `
    -password $server_password

if ($result) {
    Write-Host "`n--- OMP başarıyla başlatıldı! ---" -ForegroundColor Green
    Write-Host "Oyun ayrı bir süreçte başlatıldı." -ForegroundColor Green
}
else {
    Write-Host "`n--- OMP BAŞLATILAMADI! ---" -ForegroundColor Red
    Write-Host "Görüntülenen hata mesajlarını (açılır pencereler veya konsol) kontrol edin." -ForegroundColor Red
}

Read-Host "`nProgramı kapatmak için Enter'a basın."
```

**Betiği çalıştırmak için:**

Önceki bölümdeki adımları izleyin, `StartSAMP.ps1` yerine `StartOMP.ps1` kullanın.

### 4. Bir Ana Betikten Çalıştırma

Kütüphaneyi çağıran ve parametreleri veya koşulları daha gelişmiş bir şekilde işleyen daha karmaşık bir betik oluşturmak mümkündür. Temel kavram aynı kalır: `Injector.ps1` ana betikte "dot-sourced" edilmelidir.

```powershell
# Launcher.ps1
param(
    [string]$type = "samp",
    [string]$game_dir = "C:\Games\GTA San Andreas",
    [string]$player_nickname = "Isim",
    [string]$server_ip = "127.0.0.1",
    [string]$server_port = "7777",
    [string]$server_password = ""
)

# Injector.ps1'i yükle
$injector_script = Join-Path -Path $PSScriptRoot -ChildPath "Injector.ps1"

# Enjektörün ana betiğinin yüklenmeden önce var olup olmadığını kontrol et
if (-not (Test-Path $injector_script -PathType Leaf)) {
    Write-Error "Injector.ps1, $injector_script konumunda bulunamadı. Lütfen yolu kontrol edin."
    
    exit 1
}

. $injector_script # Fonksiyonları yüklemek için dot-sourcing kullan

Write-Host "Sağlanan parametrelerle oyunu başlatmaya çalışılıyor..." -ForegroundColor Yellow

$success = Initialize_Game -inject_type $type `
    -folder $game_dir `
    -nickname $player_nickname `
    -ip $server_ip `
    -port $server_port `
    -password $server_password

if ($success) {
    Write-Host "`nBaşlatıcı raporu: Oyun başarıyla başlatıldı!" -ForegroundColor Green
}
else {
    Write-Host "`nBaşlatıcı raporu: Oyun başlatılamadı!" -ForegroundColor Red
}

Read-Host "`nÇıkmak için Enter'a basın."
```

**`Launcher.ps1`'in çalıştırılması:**

```powershell
# Varsayılan değerlerle çalıştır
.\Launcher.ps1

# Belirli IP ve port ile OMP için çalıştır
.\Launcher.ps1 -type "omp" -server_ip "omp.server.com" -server_port "7777" -player_nickname "Isim" -server_password "secure123"
```

## Yaygın Hatalar ve Mesajların Ele Alınması

**SA-MP Injector PowerShell**, kullanılabilirliğe öncelik verir ve bunun temel bir parçası, bir arıza durumunda kullanıcıya net geri bildirim sağlamaktır. Hata mesajları, **Windows diyalog kutuları** (`MessageBoxW`) veya doğrudan PowerShell konsolu aracılığıyla sunulur ve daha fazla bağlam için **enjeksiyon türüne (SA-MP veya OMP)** göre kategorize edilir. Bu, tam olarak neyin yanlış gittiğini ve çözüme nasıl yaklaşacağınızı bilmenizi sağlar.

İşte karşılaşabileceğiniz yaygın hatalardan bazıları ve olası nedenleri/çözümleri, bu diyalog kutularının son kullanıcıya nasıl göründüğüne dair görsel örneklerle birlikte:

### 1. Geçersiz Enjeksiyon Türü

Sağlanan `inject_type` `"samp"` veya `"omp"` değilse, kütüphane hangi çok oyunculu istemciyi başlatmayı düşündüğünüzü bilemez.

![Error 1](screenshots/error_1.png)

- **Görüntülenen Hata Mesajı**: `"Invalid injection mode specified. Please use 'samp' or 'omp'."`
- **Neden**: `inject_type` argümanı beklenen `"samp"` veya `"omp"` değerleriyle eşleşmiyor. Bir yazım hatası, boş bir dize veya tanınmayan bir değer olabilir.
- **Çözüm**: `$inject_type`'ın doğru şekilde `"samp"` veya `"omp"` olarak ayarlandığını kontrol edin. Dizenin tam olarak eşleşmesi önemlidir (kod karşılaştırma için `ToLower()` kullansa da).
   ```powershell
   # Doğru:
   Initialize_Game -inject_type "samp" ...
   Initialize_Game -inject_type "omp" ...

   # Yanlış (hataya neden olur):
   # Initialize_Game -inject_type "invalid" ...
   # Initialize_Game -inject_type "" ...
   ```

### 2. Geçersiz Sunucu Portu (Format veya Aralık)

Port, sunucuya bağlantı için temel bir sayısal parametredir. Bu hata, değer geçerli bir sayı olarak yorumlanamazsa veya kabul edilebilir aralığın (**1 ila 65535**) dışındaysa oluşur.

#### 2.1. Sayısal Olmayan Port Formatı

![Error 2](screenshots/error_2.png)

- **Görüntülenen Hata Mesajı**: `"Invalid port format. The port must be a numeric value. Please provide a valid integer for the port."`
- **Neden**: `port` argümanı sayısal rakam olmayan karakterler içeriyor veya geçerli bir tamsayıya dönüştürülemiyor (ör. `"abc"`, `"7777a"`).
- **Çözüm**: Yalnızca rakam içeren ve geçerli bir tamsayıyı temsil eden bir dize sağlayın.
   ```powershell
   # Doğru:
   Initialize_Game ... -port "7777" ...
   
   # Yanlış (geçersiz format):
   # Initialize_Game ... -port "port7777" ...
   # Initialize_Game ... -port "invalid" ...
   ```

#### 2.2. Geçerli Aralık Dışında Port

![Error 3](screenshots/error_3.png)

- **Görüntülenen Hata Mesajı**: `"The specified port number (XXXX) is outside the valid range of 1 to 65535. Please provide a valid port."` (**XXXX**, kullanmaya çalıştığınız değer olacaktır).
- **Neden**: Sağlanan port geçerli bir sayıdır, ancak `1`'den (ayrılmış veya kullanılamaz) düşük veya `65535`'ten (**TCP/UDP portları** için maksimum sınır) yüksektir.
- **Çözüm**: `1` ila `65535` aralığında bir port sağlayın. **SA-MP**/**OMP** için yaygın portlar `7777`'dir.
   ```powershell
   # Doğru:
   Initialize_Game ... -port "7777" ...

   # Yanlış (aralık dışında):
   # Initialize_Game ... -port "0" ...      # Çok düşük
   # Initialize_Game ... -port "65536" ...  # Çok yüksek
   # Initialize_Game ... -port "-1" ...     # Negatif değer
   ```

### 3. Geçersiz Takma Ad (Boş veya Çok Uzun)

Oyuncunun **takma adı**, oyun istemcisinin onu kabul etmesini sağlamak için doğrulanır.

#### 3.1. Boş Takma Ad

![Error 4](screenshots/error_4.png)

- **Görüntülenen Hata Mesajı**: `"Nickname cannot be empty. Please provide a valid nickname."`
- **Neden**: `nickname` argümanı boş bir dize olarak sağlandı.
- **Çözüm**: Takma adın boş olmadığından emin olun.
   ```powershell
   # Doğru:
   Initialize_Game ... -nickname "BenimAdim" ...

   # Yanlış (boş):
   # Initialize_Game ... -nickname "" ...
   ```

#### 3.2. Çok Uzun Takma Ad

![Error 5](screenshots/error_5.png)

- **Görüntülenen Hata Mesajı**: `"Nickname length exceeds the maximum allowed of 20 characters. Please use a shorter nickname."`
- **Neden**: Sağlanan **takma adın** uzunluğu `$global:CONSTANTS.MAX_NICKNAME_LENGTH` olan `20` karakteri aşıyor.
- **Çözüm**: En fazla `20` karakter uzunluğunda bir **takma ad** kullanın.
   ```powershell
   # Doğru:
   Initialize_Game ... -nickname "Kisa" ...

   # Yanlış (çok uzun):
   # Initialize_Game ... -nickname "BuOyuncuAdiBuradaKullanmakIcinCokUzun" ...
   ```

### 4. Oyun Dosyaları veya DLL Bulunamadı

Bu, en yaygın arıza nedenlerinden biridir. Kütüphanenin `gta_sa.exe`, `samp.dll` ve **OMP** için `omp-client.dll`'nin beklenen konumlarda bulunmasına ihtiyacı vardır.

#### 4.1. Oyun Yürütülebilir Dosyası (`gta_sa.exe`) Bulunamadı

![Error 6](screenshots/error_6.png)

- **Görüntülenen Hata Mesajı**: `"Game executable not found. Please ensure 'gta_sa.exe' exists at the specified path: [tam yol]"`. `[tam yol]` klasörü ve dosya adını içerecektir.
- **Neden**: `gta_sa.exe` dosyası `folder` argümanında sağlanan klasörde bulunamadı.
- **Çözüm**:
   1. `$folder`'ın doğru **GTA San Andreas** kurulum dizinine işaret ettiğini kontrol edin.
   2. `gta_sa.exe`'nin bu klasörde bulunduğunu ve adının değiştirilmediğini onaylayın.

#### 4.2. SA-MP Kütüphanesi (`samp.dll`) Bulunamadı

![Error 7](screenshots/error_7.png)

- **Görüntülenen Hata Mesajı**: `"SA-MP library not found. Please ensure 'samp.dll' exists at the specified path: [tam yol]"`.
- **Neden**: `samp.dll` dosyası `folder` argümanında sağlanan klasörde bulunamadı. **Bu DLL**, **her iki** enjeksiyon türü (`samp` ve `omp`) için de bir gerekliliktir.
- **Çözüm**: `samp.dll`'nin **GTA San Andreas** kurulum klasöründe bulunduğundan emin olun.

#### 4.3. OMP Kütüphanesi (`omp-client.dll`) Bulunamadı (sadece OMP enjeksiyonu için)

![Error 8](screenshots/error_8.png)

- **Görüntülenen Hata Mesajı**: `"OMP library not found. Please ensure 'omp-client.dll' exists at the specified path for OMP injection: [tam yol]"`.
- **Neden**: Enjeksiyon türü olarak `"omp"` belirttiyseniz, ancak `omp-client.dll` dosyası sağlanan klasörde bulunamadıysa.
- **Çözüm**: En son **OMP** istemcisini indirin ve `omp-client.dll`'nin (ve `samp.dll`'nin) **GTA San Andreas** kurulum klasöründe bulunduğundan emin olun.

### 5. Oyun Süreci Oluşturulamadı

Bu daha karmaşık bir hatadır, çünkü **işletim sistemi izinlerini** ve `gta_sa.exe`'nin mevcut durumunu içerir.

![Error 9](screenshots/error_9.png)

- **Görüntülenen Hata Mesajı**: `"Failed to create game process. Ensure 'gta_sa.exe' is not running and you have sufficient permissions to execute the file. System Error: [İşletim sistemi hata mesajı]"`. Sistem mesajı `Get_System_Error_Message` tarafından eklenecektir (ör: `Access is denied.` veya `The requested operation requires elevation.`).
- **Neden**: `gta_sa.exe`'yi başlatmak için `CreateProcessA` çağrısı başarısız oldu. Yaygın nedenler şunlardır:
   - **Süreç zaten çalışıyor**: Bir `gta_sa.exe` örneği zaten etkin ve yeni bir yürütmeyi engelliyor.
   - **Yetersiz izinler**: Betiğinizin belirli sistem ayarlarında (**UAC** etkin, korumalı klasörler, vb.) bir süreç oluşturmak için gerekli ayrıcalıklara (ör. yönetici) sahip değil.
   - **Yürütülebilir dosya ile ilgili sorunlar**: `gta_sa.exe` bozuk olabilir veya başka bir program tarafından (ör. yanlış yapılandırılmış bir antivirüs) engelleniyor olabilir.
- **Çözüm**:
   1. Görev Yöneticisi'ni kontrol edin ve çalışan hiçbir `gta_sa.exe` örneği olmadığından emin olun. Varsa herhangi birini sonlandırın.
   2. **PowerShell betiğini Yönetici olarak çalıştırın**. PowerShell simgesine sağ tıklayın ve **"Yönetici olarak çalıştır"**ı seçin veya bunun için yapılandırılmış bir kısayoldan başlatın.
   3. Bir **antivirüs** veya **güvenlik yazılımı** müdahale ediyorsa, betiğinizi ve/veya **GTA:SA** klasörünü antivirüs istisnalarına ekleyin (bunu dikkatli bir şekilde ve yalnızca dosyalarınızın bütünlüğünden eminseniz yapın).

### 6. Hedef Süreçte Bellek Ayrılamadı

Kütüphane, **DLL yolunu** kopyalamak için `gta_sa.exe`'de küçük bir bellek alanı ayırmaya çalışır.

![Error 10](screenshots/error_10.png)

- **Görüntülenen Hata Mesajı**: `"Failed to allocate memory in the target process. This might be due to insufficient permissions or process protection mechanisms. System Error: [İşletim sistemi hata mesajı]"`.
- **Neden**: `VirtualAllocEx` fonksiyonu (başka bir süreç içinde bellek ayırmak için kullanılır) başarısız oldu. Bu, büyük olasılıkla şu durumlarda olur:
   - **GTA:SA** süreci (askıya alınmış durumda olsa bile) harici süreçler tarafından bellek ayrılmasını önleyen güvenlik savunmalarına veya **anti-enjeksiyon yamalarına** sahiptir.
   - Betiğinizin başka bir sürecin belleğini manipüle etmek için gerekli yükseltilmiş izinlere sahip değil.
   - (Daha az yaygın) Sistemde aşırı bir sanal bellek kıtlığı var.
- **Çözüm**:
   1. Betiğinizi **Yönetici** ayrıcalıklarıyla çalıştırın.
   2. Oyunun enjeksiyon veya bellek manipülasyonu girişimlerini engelleyebilecek herhangi bir modifikasyon veya **güvenlik yaması** içermediğinden emin olun (bu, modifiye edilmiş ortamlarda veya belirli üçüncü taraf anti-hile araçlarıyla daha yaygındır).

### 7. DLL Yolunu Süreç Belleğine Yazma Hatası

Belleği ayırdıktan sonra, kütüphane **DLL yolunu** oraya kopyalamaya çalışır.

![Error 11](screenshots/error_11.png)

- **Görüntülenen Hata Mesajı**: `"Failed to write DLL path to the target process memory. Verify process permissions and ensure the DLL path is accessible. System Error: [İşletim sistemi hata mesajı]"`.
- **Neden**: `WriteProcessMemory` fonksiyonu, **DLL yolu baytlarını** `gta_sa.exe`'de ayrılan uzak belleğe kopyalamaya çalışırken başarısız oldu. Bu genellikle şunlara işaret eder:
   - **Yazma izinleri**: Betiğinizin bu bellek bölgesine veya **GTA:SA** sürecine yazma izni yok.
   - **Geçersiz tanıtıcı**: Süreç **tanıtıcısı** bir şekilde geçersiz hale geldi (daha az yaygın, ancak aşırı sistem koşullarında mümkün).
   - **Bellek Koruma Sorunları**: Bazı bellek korumaları (**İS** veya oyun modifikasyonları) yazmayı engelledi.
- **Çözüm**: **Yönetici olarak çalıştırın**. `gta_sa.exe`'nin ve ortamının bellek işlemlerini engelleyebilecek araçlardan "temiz" olduğunu kontrol edin.

### 8. Temel Sistem Fonksiyonları Bulunamadı

Bunlar kritik Windows API'leridir; buradaki hatalar işletim sistemi veya yürütme ortamıyla ilgili temel bir soruna işaret eder.

#### 8.1. `kernel32.dll` Bulunamadı

![Error 12](screenshots/error_12.png)

- **Görüntülenen Hata Mesajı**: `"Failed to obtain a handle to kernel32.dll. This is an essential system library and this error indicates a severe system issue. System Error: [İşletim sistemi hata mesajı]"`.
- **Neden**: `kernel32.dll`, temel fonksiyonları içeren en temel Windows DLL'lerinden biridir. Eğer `GetModuleHandleA` ona bir **tanıtıcı** alamazsa, işletim sisteminde çok ciddi sorunlar var demektir.
- **Çözüm**: Bu, nadiren kütüphane veya betiğiniz tarafından neden olunan **kritik** bir hatadır. Sistem dosyası bozulması, **Windows** ile ilgili ciddi sorunlar veya oldukça alışılmadık bir **İS** kurulumu olduğunu gösterir. Sistem bütünlüğü denetimlerini (örneğin **Komut İstemi**'nde **Yönetici** olarak `sfc /scannow`) çalıştırmanız veya son çare olarak **Windows**'u yeniden yüklemeniz önerilir.

#### 8.2. `LoadLibraryA` Bulunamadı

![Error 13](screenshots/error_13.png)

- **Görüntülenen Hata Mesajı**: `"Failed to find the address of the LoadLibraryA function in kernel32.dll. This is critical for injecting the DLL. System Error: [İşletim sistemi hata mesajı]"`.
- **Neden**: `kernel32.dll` bulunsa da, `LoadLibraryA` fonksiyonu `GetProcAddress` aracılığıyla çözümlenemedi. Son derece nadir olmakla birlikte, `kernel32.dll` **DLL dosyasının** bozulması veya oldukça standart dışı bir yürütme ortamının bir sonucu olabilir.
- **Çözüm**: Yukarıdaki `kernel32.dll` hatası gibi, bu da işletim sisteminde ciddi bir soruna işaret eder.

### 9. Enjeksiyon için Uzak İş Parçacığı Oluşturulamadı

Uzak ortamı hazırlayıp **DLL yolunu** kopyaladıktan sonra, `LoadLibraryA`'yı "çağırmak" için oyun sürecinde yeni bir **iş parçacığı** oluşturulur.

![Error 14](screenshots/error_14.png)

- **Görüntülenen Hata Mesajı**: `"Failed to create a remote thread in the target process to execute the DLL injection. This could be due to security restrictions or process state. System Error: [İşletim sistemi hata mesajı]"`.
- **Neden**: `CreateRemoteThread` çağrısı başarısız oldu. Bu hata, sağlam **anti-enjeksiyon** savunmalarına sahip sistemlerde veya bir programın süreç davranışını yoğun bir şekilde izlediği durumlarda yaygındır:
   - **Güvenlik Mekanizmaları**: **Anti-hile** araçları, **güvenlik yazılımları** veya belirli **Windows** politikaları, üçüncü taraf süreçlerde **iş parçacığı** oluşturma girişimlerini algılayabilir ve engelleyebilir.
   - **Tutarsız Hedef Süreç**: **GTA:SA** süreci beklenmedik veya kararsız bir durumdaysa (`CREATE_SUSPENDED`'de başlatılmış olsa bile), bu, içinde **iş parçacığı** oluşturma yeteneğini etkileyebilir.
- **Çözüm**:
   1. Betiğinizi **Yönetici** ayrıcalıklarıyla çalıştırın.
   2. **Anti-hile** araçları, **agresif antivirüsler** veya süreç manipülasyonunu denetlemek ve engellemek için yapılandırılmış **güvenlik duvarları** gibi çakışabilecek araçların olmadığından emin olun. Varsa, betiğinizi ve `gta_sa.exe`'yi istisnalara ekleyin (dikkatli bir şekilde).
   3. Sistem hata mesajı, belirli nedeni araştırmak için ek ayrıntılar sağlayabilir (ör: **"A process has been denied access to create threads for other processes."**).

### 10. Zaman Aşımı veya Enjeksiyon Tamamlanamadı

Uzak **iş parçacığını** oluşturduktan sonra, enjektör onun **DLL yüklemesini** tamamlamasını bekler.

![Error 15](screenshots/error_15.png)

- **Görüntülenen Hata Mesajı**: `"Timeout or error waiting for DLL injection to complete (timeout). System Error: [İşletim sistemi hata mesajı]"`.
- **Neden**: `LoadLibraryA`'yı yürüten uzak **iş parçacığı**, geri dönmek için `$global:CONSTANTS.DLL_INJECTION_TIMEOUT_MS`'den (10 saniye) daha uzun sürdü veya başarısız oldu ve `GetExitCodeThread` 0 döndürdü. Potansiyel nedenler şunlardır:
   - **Enjekte Edilen DLL'de Sorunlar**: `samp.dll` veya `omp-client.dll`'nin `DllMain`'i çok uzun sürüyor, bir **sonsuz döngü**, bir **çökme** veya **DLL'nin** doğru şekilde yüklenmesini engelleyen bir hata içeriyor (ör. eksik **DLL bağımlılıkları**).
   - **Sessiz Engelleme**: Bir güvenlik mekanizması `LoadLibraryA`'yı engellemiş olabilir ancak açık bir **iş parçacığı** oluşturma hatasıyla bildirmemiş olabilir.
- **Çözüm**:
   1. `samp.dll` ve `omp-client.dll` dosyalarının bütünlüğünü kontrol edin. Bozuk olabilirler veya `gta_sa.exe`'nizle uyumsuz bir sürüm olabilirler.
   2. **Enjekte edilen DLL'nin**, sistemde eksik veya erişilemez olabilecek **diğer DLL'lere** bağlı olmadığından emin olun.

### 11. Oyun Süreci İş Parçacığını Sürdürme Hatası

Bu, **DLL'ler** enjekte edildikten sonra oyunu başlatmak için son adımdır.

![Error 16](screenshots/error_16.png)

- **Görüntülenen Hata Mesajı**: `"Failed to resume the game process thread: [İşletim sistemi hata mesajı]"`.
- **Neden**: `ResumeThread` çağrısı başarısız oldu, bu da `gta_sa.exe`'nin ana **iş parçacığının** oyunun yürütülmesini başlatmak için etkinleştirilemediği anlamına gelir. Bu nadir bir hatadır, ancak şu durumlarda olabilir:
   - Sürecin **iş parçacığı** **tanıtıcısı** geçersiz hale geldi.
   - İşletim sistemi, muhtemelen bir güvenlik kesintisi veya tutarsız süreç durumuyla ilgili bir nedenle devam etmeyi engelledi.
   - Süreç, **DLL enjeksiyonu** ile ana **iş parçacığının** devam ettirilme girişimi arasında harici olarak sonlandırılmış olabilir.
- **Çözüm**: Önceki tüm adımlar başarılı olduysa ve yalnızca `ResumeThread` başarısız olduysa, bu işletim sistemi, **GTA:SA** kurulumunun kendisi veya çok katı başka bir **güvenlik yazılımı** ile ilgili bir sorun olabilir. Hatadan hemen önce ve sonra **Görev Yöneticisi** aracılığıyla `gta_sa.exe`'nin durumunu yeniden inceleyin. Bilgisayarı yeniden başlatmak, geçici sistem durumu sorunlarını çözebilir.

> [!TIP]
> Karmaşık hata ayıklama senaryolarında, **Process Monitor (Sysinternals Suite)** veya bir hata ayıklayıcı (örneğin **WinDbg**) gibi araçlar paha biçilmez olabilir. **API** çağrılarını gözlemlemeye, erişim hatalarını kontrol etmeye, **tanıtıcıların** durumunu izlemeye ve hatta sürecin belleğini incelemeye yardımcı olabilirler, bu da perde arkasında neler olup bittiğine dair derinlemesine bir görüş sağlar.
>
> `Add-Type` kullanan ve düşük seviyede WinAPI ile etkileşimde bulunan PowerShell betiklerini hata ayıklamak için, **PowerShell Integrated Scripting Environment (ISE)** veya PowerShell uzantılı **Visual Studio Code** gibi araçlar kullanışlıdır, kesme noktaları koymaya ve değişkenleri incelemeye olanak tanır. Bunları her zaman **Yönetici olarak** çalıştırmayı unutmayın.

## Lisans

Copyright © **SA-MP Programming Community**

Bu yazılım MIT Lisansı ("Lisans") şartları altında lisanslanmıştır; bu yazılımı Lisans şartlarına uygun olarak kullanabilirsiniz. Lisansın bir kopyasını şu adresten edinebilirsiniz: [MIT License](https://opensource.org/licenses/MIT)

### Kullanım Şartları ve Koşulları

#### 1. Verilen İzinler

Bu lisans, bu yazılımın ve ilgili dokümantasyon dosyalarının bir kopyasını edinen herhangi bir kişiye ücretsiz olarak aşağıdaki hakları vermektedir:
* Yazılımın kopyalarını kullanma, kopyalama, değiştirme, birleştirme, yayınlama, dağıtma, alt lisans verme ve/veya satma hakkı
* Yazılımın sağlandığı kişilerin de aynısını yapmasına izin verme hakkı (aşağıdaki koşullara tabi olmak kaydıyla)

#### 2. Zorunlu Koşullar

Yazılımın tüm kopyaları veya önemli parçaları şunları içermelidir:
* Yukarıdaki telif hakkı bildirimi
* Bu izin bildirimi
* Aşağıdaki sorumluluk reddi

#### 3. Telif Hakları

Yazılım ve ilgili tüm dokümantasyon telif hakkı yasaları ile korunmaktadır. **SA-MP Programming Community** yazılımın orijinal telif haklarını elinde tutmaktadır.

#### 4. Garanti Reddi ve Sorumluluk Sınırlaması

YAZILIM "OLDUĞU GİBİ" SAĞLANMAKTADIR, HİÇBİR TÜRDE GARANTİ VERİLMEMEKTEDİR, AÇIK VEYA ZIMNİ, TİCARİ ELVERİŞLİLİK, BELİRLİ BİR AMACA UYGUNLUK VE İHLAL ETMEME GARANTİLERİ DAHİL ANCAK BUNLARLA SINIRLI OLMAMAK ÜZERE.

HİÇBİR KOŞULDA YAZARLAR VEYA TELİF HAKKI SAHİPLERİ HERHANGİ BİR İDDİA, HASAR VEYA DİĞER YÜKÜMLÜLÜKLERDEN SORUMLU TUTULAMAZ, İSTER SÖZLEŞME KAPSAMINDA, HAKSIZ FİİL VEYA BAŞKA BİR ŞEKİLDE OLSUN, YAZILIMDAN VEYA YAZILIMIN KULLANIMINDAN VEYA DİĞER İŞLEMLERDEN KAYNAKLANAN DURUMLAR İÇİN.

---

MIT Lisansı hakkında detaylı bilgi için: https://opensource.org/licenses/MIT