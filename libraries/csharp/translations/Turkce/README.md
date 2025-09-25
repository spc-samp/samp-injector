# SA-MP Injector C#

<div align="center">

![C#](https://img.shields.io/badge/C%23-11.0%2B-512BD4?style=for-the-badge&logo=csharp&logoColor=white)
![.NET](https://img.shields.io/badge/.NET-7.0%2B-512BD4?style=for-the-badge&logo=dotnet&logoColor=white)
![Platform](https://img.shields.io/badge/Platform-Windows-blue?style=for-the-badge&logo=windows&logoColor=white)
![Architecture](https://img.shields.io/badge/Architecture-x86%20(32--bit)-lightgrey?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)

**SA-MP ve OMP süreçlerine programatik olarak DLL enjekte etmek için kullanılan, sunuculara otomatik bağlantı sağlayan bir C# kütüphanesi.**

</div>

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

- [SA-MP Injector C#](#sa-mp-injector-c)
  - [Diller](#diller)
  - [İçindekiler](#i̇çindekiler)
  - [Giriş ve Amaç](#giriş-ve-amaç)
  - [Tasarım Felsefesi](#tasarım-felsefesi)
    - [Birlikte Çalışabilirlik (P/Invoke)](#birlikte-çalışabilirlik-pinvoke)
    - [Kaynak Yönetimi (`SafeHandle`)](#kaynak-yönetimi-safehandle)
    - [Güvenlik ve Sağlamlık](#güvenlik-ve-sağlamlık)
  - [Sistem Gereksinimleri](#sistem-gereksinimleri)
    - [Geliştirme Ortamı](#geliştirme-ortamı)
    - [Çalışma Ortamı](#çalışma-ortamı)
  - [Kurulum ve Temel Kullanım](#kurulum-ve-temel-kullanım)
    - [Projenize Ekleme](#projenize-ekleme)
    - [Kullanım Örneği](#kullanım-örneği)
  - [Kütüphane Bileşenleri](#kütüphane-bileşenleri)
    - [1. `Constants.cs`](#1-constantscs)
    - [2. `InjectionType.cs`](#2-injectiontypecs)
    - [3. `Injector.cs`](#3-injectorcs)
    - [4. `InjectorCore.cs`](#4-injectorcorecs)
    - [5. `InputValidator.cs`](#5-inputvalidatorcs)
    - [6. `NativeImports.cs`](#6-nativeimportscs)
    - [7. `ProcessHandler.cs`](#7-processhandlercs)
    - [8. `SafeHandles.cs`](#8-safehandlescs)
  - [Ayrıntılı DLL Enjeksiyon Döngüsü](#ayrıntılı-dll-enjeksiyon-döngüsü)
    - [1. Giriş Doğrulaması](#1-giriş-doğrulaması)
    - [2. Oyun Sürecinin Oluşturulması (Askıya Alınmış)](#2-oyun-sürecinin-oluşturulması-askıya-alınmış)
    - [3. `samp.dll` Enjeksiyonu](#3-sampdll-enjeksiyonu)
    - [4. `omp-client.dll` Enjeksiyonu (İsteğe Bağlı, SA-MP'ye Bağımlı)](#4-omp-clientdll-enjeksiyonu-i̇steğe-bağlı-sa-mpye-bağımlı)
    - [Oyunun Ana Thread'ini Sürdürme](#oyunun-ana-threadini-sürdürme)
  - [Hata Yönetimi ve Başarısızlık Durumları](#hata-yönetimi-ve-başarısızlık-durumları)
    - [Giriş Doğrulama Hataları](#giriş-doğrulama-hataları)
      - [Geçersiz Nickname](#geçersiz-nickname)
      - [Geçersiz Port](#geçersiz-port)
      - [Eksik Oyun/DLLs Dosyaları](#eksik-oyundlls-dosyaları)
    - [Süreç Oluşturma Hataları](#süreç-oluşturma-hataları)
      - [Süreç Oluşturulamadı](#süreç-oluşturulamadı)
    - [DLL Enjeksiyon Hataları](#dll-enjeksiyon-hataları)
      - [Kullanılamayan `kernel32.dll` Handle'ı](#kullanılamayan-kernel32dll-handleı)
      - [Kullanılamayan `LoadLibraryA` Fonksiyonu](#kullanılamayan-loadlibrarya-fonksiyonu)
      - [Uzak Bellek Ayırma Hatası](#uzak-bellek-ayırma-hatası)
      - [Süreç Belleğine Yazma Hatası](#süreç-belleğine-yazma-hatası)
      - [Uzak Thread Oluşturma Hatası](#uzak-thread-oluşturma-hatası)
      - [Enjeksiyon Beklemesinde Zaman Aşımı veya Hata](#enjeksiyon-beklemesinde-zaman-aşımı-veya-hata)
      - [DLL Enjeksiyonu Başarısız Oldu veya Hata Döndürdü](#dll-enjeksiyonu-başarısız-oldu-veya-hata-döndürdü)
    - [Oyun Thread'ini Sürdürürken Hata](#oyun-threadini-sürdürürken-hata)
  - [Lisans](#lisans)
    - [Kullanım Şartları ve Koşulları](#kullanım-şartları-ve-koşulları)
      - [1. Verilen İzinler](#1-verilen-i̇zinler)
      - [2. Zorunlu Koşullar](#2-zorunlu-koşullar)
      - [3. Telif Hakları](#3-telif-hakları)
      - [4. Garanti Reddi ve Sorumluluk Sınırlaması](#4-garanti-reddi-ve-sorumluluk-sınırlaması)

## Giriş ve Amaç

**SA-MP Injector C#** kütüphanesi, San Andreas Multiplayer (SA-MP) ve Open Multiplayer (OMP) istemcilerinin sunuculara otomatik olarak başlatılmasını ve bağlanmasını basitleştirmek için tasarlanmış bir C# çözümüdür. Grand Theft Auto: San Andreas (`gta_sa.exe`) oyun sürecine `samp.dll` veya `omp-client.dll` kütüphanelerini programatik olarak yükleyen bir DLL (Dynamic Link Library) enjeksiyon aracı olarak işlev görür.

Bu kütüphanenin temel amacı, diğer C# uygulamalarının (özel başlatıcılar, sunucu yönetim araçları veya yardımcı programlar gibi) oyunu belirli parametrelerle (takma ad, IP, port ve şifre) kullanıcı için şeffaf bir şekilde başlatmasını sağlamak ve bir SA-MP/OMP sunucusuna bağlanma sürecini otomatikleştirmektir.

## Tasarım Felsefesi

**SA-MP Injector C#**'ın tasarımı, düşük seviyeli sistem operasyonlarının karmaşıklıklarını kapsülleyerek sağlamlık, güvenlik ve basitleştirilmiş bir kullanım arayüzüne odaklanır.

### Birlikte Çalışabilirlik (P/Invoke)

DLL enjeksiyonunun ve askıya alınmış süreç oluşturmanın temel işlevselliği, doğası gereği düşük seviyeli bir işletim sistemi operasyonudur. Bu amaçla, kütüphane .NET'in **P/Invoke (Platform Invoke)** özelliğinden kapsamlı bir şekilde yararlanır ve Windows API'sinin yerel işlevlerini (özellikle `kernel32.dll`'den) doğrudan C# kodundan çağırmaya olanak tanır. Bu, `partial` metotların bildiriminde ve `[LibraryImport(KERNEL32, SetLastError = true)]` özniteliğinin kullanımında belirgindir.

### Kaynak Yönetimi (`SafeHandle`)

Süreç ve thread "handle"ları gibi işletim sistemi kaynaklarıyla yapılan işlemler, bellek veya kaynak sızıntılarını önlemek için dikkatli bir yönetim gerektirir. Kütüphane, bu kaynakların istisnalar durumunda bile her zaman doğru şekilde serbest bırakılmasını sağlamak için `SafeHandle`'dan türetilmiş sınıflar (`SafeProcessHandle` ve `SafeThreadHandle`) kullanır. Bu, C++'ın **RAII (Resource Acquisition Is Initialization)** ilkesine uyar ve bunu .NET ortamına genişletir.

### Güvenlik ve Sağlamlık

Kütüphane, birkaç güvenlik katmanı içerir:
- **Giriş Doğrulaması:** Kullanıcı tarafından sağlanan tüm girdiler, herhangi bir kritik işlem başlatılmadan önce sıkı bir şekilde doğrulanır, bu da çalışma zamanı hataları veya beklenmedik davranışlar riskini en aza indirir.
- **Hata Yönetimi:** Yerel API çağrıları, ayrıntılı ve anlaşılır hata mesajları sağlamak için hata kontrolleri (`SetLastError = true` ve `Marshal.GetLastWin32Error()`) ile birlikte gelir.
- **Süreç Sonlandırma:** Enjeksiyon işlemi sırasında bir hata olması durumunda, yeni oluşturulan oyun süreci "zombi" süreçlerin çalışmasını önlemek için otomatik olarak sonlandırılır.

## Sistem Gereksinimleri

### Geliştirme Ortamı

- **.NET SDK 7.0 veya üstü:** Kütüphane `net7.0-windows` için oluşturulmuştur.
- **C# 11.0 veya üstü:** `ImplicitUsings`, `Nullable`, `AllowUnsafeBlocks` ve `LibraryImport` gibi özellikler için gereklidir.
- **Visual Studio 2022 veya uyumlu bir geliştirme ortamı:** Kütüphaneyi oluşturmak ve entegre etmek için.
- **Derleme Platformu:** `gta_sa.exe` ve SA-MP/OMP DLL'lerinin mimarisi nedeniyle `x86 (32-bit)` zorunlu hedeftir.

```xml
<!-- samp-injector-csharp.csproj -->
<Project Sdk="Microsoft.NET.Sdk">
    <PropertyGroup>
        <TargetFrameworks>net7.0-windows</TargetFrameworks>
        <PlatformTarget>x86</PlatformTarget> <!-- KRİTİK: x86 olmalıdır -->
        <ImplicitUsings>enable</ImplicitUsings>
        <Nullable>enable</Nullable>
        <UseWindowsForms>true</UseWindowsForms>
        <AllowUnsafeBlocks>true</AllowUnsafeBlocks> <!-- Gelişmiş P/Invoke için gereklidir -->
    </PropertyGroup>
</Project>
```

### Çalışma Ortamı

- **İşletim Sistemi:** Windows (.NET 7.0+ ile uyumlu herhangi bir modern sürüm).
- **Grand Theft Auto: San Andreas (GTA: SA):** Oyunun yüklü olması gerekmektedir.
- **SA-MP veya OMP Client DLL'leri:** İstenen enjeksiyon türüne bağlı olarak `samp.dll` veya `omp-client.dll` oyunun kök dizininde bulunmalıdır.

## Kurulum ve Temel Kullanım

### Projenize Ekleme

Bu kütüphaneyi kullanmanın en basit yolu, `Samp_Injector_CSharp` projesini kendi C# projenize bir referans olarak eklemektir.

1. Kütüphane deposunu klonlayın veya indirin.
2. Visual Studio'da, projenizdeki "Dependencies" (veya "Referanslar") üzerine sağ tıklayın.
3. "Add Project Reference..." seçeneğini belirleyin.
4. Kütüphane dizinine gidin ve `samp-injector-csharp.csproj` projesini ekleyin.

### Kullanım Örneği

Oyunu başlatmak ve bir sunucuya bağlanmak için `Injector.Initialize_Game` statik metodunu çağırmanız yeterlidir.

```csharp
using Samp_Injector_CSharp;
using System;
using System.Windows.Forms; // MessageBox için, eğer bir WinForms projesi değilse

namespace Launcher {
    public partial class Main : Form {
        public Main() {
            InitializeComponent();
        }

        private void Connect(object sender, EventArgs e) {
            string inject_type = "SAMP"; // "SAMP" veya "OMP"
            string game_folder = @"C:\Games\GTA San Andreas"; // GTA: SA klasörünün yolu
            string nickname = "İsim";
            string ip = "127.0.0.1";
            string port = "7777";
            string password = ""; // Şifre yoksa boş bırakın

            // SA-MP enjeksiyon örneği
            Injector.Initialize_Game(inject_type, game_folder, nickname, ip, port, password);

            // Eğer OMP ise, inject_type'ı değiştirin:
            // inject_type = "OMP";
            // Injector.Initialize_Game(inject_type, game_folder, nickname, ip, port, password);
        }
    }
}
```

## Kütüphane Bileşenleri

Kütüphane, her biri açık ve iyi tanımlanmış bir sorumluluğa sahip birkaç dosyada yapılandırılmıştır, bu da organizasyonu, sürdürülebilirliği ve sorumlulukların ayrılmasını teşvik eder. Aşağıda her bir bileşenin ayrıntılı bir açıklaması bulunmaktadır.

### 1. `Constants.cs`

Bu dosya, kütüphane genelinde kullanılan tüm sabitlerin ve değişmez değerlerin merkezi bir deposudur. Varlığı, kodun bakımını, okunabilirliğini ve tutarlılığını teşvik eder ve kritik değerlerin tek bir yerde tanımlanmasını sağlar.

Sabitlerin kategoriye göre düzenlenmesi, amaçlarının anlaşılmasını kolaylaştırır:

- **Game Related Constants**
   - `MIN_PORT`: Bir sunucu bağlantı portu için izin verilen minimum değeri tanımlar (1).
   - `MAX_PORT`: Bir sunucu bağlantı portu için izin verilen maksimum değeri tanımlar (65535).
   - `MAX_NICKNAME_LENGTH`: Oyuncu takma adı için izin verilen maksimum uzunluğu belirtir (23 karakter), bu SA-MP/OMP istemcisi tarafından uygulanan bir sınırdır.

- **File Names**
   - `SAMP_DLL_NAME`: SA-MP istemcisinin ana kütüphane dosyasının adı (`"samp.dll"`).
   - `OMP_DLL_NAME`: OMP türü enjeksiyonlarda kullanılan Open Multiplayer istemci kütüphanesinin dosya adı (`"omp-client.dll"`).
   - `GAME_EXE_NAME`: Grand Theft Auto: San Andreas oyununun çalıştırılabilir dosyasının adı (`"gta_sa.exe"`).

- **System Libraries and Functions**
   - `KERNEL32_DLL`: Süreç ve bellek manipülasyonu için temel işlevleri içeren Windows sistem kütüphanesinin adı (`"kernel32.dll"`).
   - `LOAD_LIBRARY_FUNC`: `kernel32.dll` içinde bir kütüphaneyi dinamik olarak yüklemekten sorumlu işlevin adı (`"LoadLibraryA"`).

- **Command Line Arguments**
   - `CMD_ARGS_PART1`: Oyun için komut satırı argümanlarının başlangıç kısmı (`"-c -n "`).
   - `CMD_ARGS_PART2`: IP adresi için ayırıcı (`" -h "`).
   - `CMD_ARGS_PART3`: Port için ayırıcı (`" -p "`).
   - `CMD_ARGS_PART4_PASSWORD`: Şifre argümanı için önek (`" -z "`), yalnızca bir şifre sağlandığında kullanılır.
   - `CMD_ARGS_BASE_LENGTH`: Çalıştırılabilir dosya ve kullanıcı değerleri hariç, komut satırının sabit kısımlarının önceden tanımlanmış uzunluğu (14 karakter).
   - `CMD_ARG_PASSWORD_LENGTH`: Şifre argümanı önekinin uzunluğu (4 karakter).

- **Error Message Titles**
   - `ERROR_TITLE_SAMP`: SA-MP hatalarıyla ilgili hata iletişim kutuları için varsayılan başlık (`"SA-MP Injector Error - SPC"`).
   - `ERROR_TITLE_OMP`: OMP hatalarıyla ilgili hata iletişim kutuları için varsayılan başlık (`"OMP Injector Error - SPC"`).

- **Process Creation Flags**
   - `CREATE_SUSPENDED`: İşletim sistemine bir süreci ve ana thread'ini askıya alınmış bir durumda oluşturmasını bildiren bayrak (`0x00000004`). Bu, oyun çalışmaya başlamadan önce DLL'in enjekte edilmesi için temel bir özelliktir.
   - `PROCESS_CREATION_FLAGS`: Süreç oluşturma bayraklarının bir kombinasyonu, şu anda yalnızca `CREATE_SUSPENDED` olarak tanımlanmıştır.

- **Timeouts**
   - `DLL_INJECTION_TIMEOUT_MS`: Kütüphanenin DLL enjeksiyonundan sorumlu uzak thread'in tamamlanmasını bekleyeceği maksimum süre (milisaniye cinsinden) (10000ms = 10 saniye).

- **Memory Allocation Flags**
   - `MEM_COMMIT`: Sanal bellekte sayfaları rezerve eden ve bunları "taahhüt eden" (fiziksel bellek ayırır) bayrak (`0x1000`).
   - `MEM_RESERVE`: Yalnızca daha sonra kullanılmak üzere bir sanal adres alanı aralığı rezerve eden bayrak (`0x2000`).
   - `MEM_RELEASE`: Bir sayfa bölgesini taahhütten çıkarıp serbest bırakan bayrak (`0x8000`).
   - `MEMORY_ALLOCATION_TYPE`: Uzak süreçteki DLL yolu için bellek ayırmak amacıyla kullanılan `MEM_COMMIT` ve `MEM_RESERVE` kombinasyonu.
   - `MEMORY_PROTECTION`: Bellek koruma izinlerini tanımlar (şu anda `0x04`, bu da Windows API'de `PAGE_READWRITE`'a karşılık gelir ve ayrılan bellekte okuma ve yazma izni verir).

### 2. `InjectionType.cs`

Bu dosya, gerçekleştirilecek enjeksiyon türünü güvenli ve açık bir şekilde belirtmek için basit bir enum tanımlar. String'ler (`"samp"`, `"omp"`) yerine bir `enum` kullanmak, yazım hatalarını önler ve kodu daha okunabilir ve sağlam hale getirir.

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

Bu dosya, kütüphanenin genel (public) cephesidir (Facade) ve tüketici uygulamalar için tek giriş noktası olarak hizmet eder. Enjeksiyon sürecinin tüm iç karmaşıklığını tek bir statik yöntemde soyutlar.

- **Ana Sorumluluk:** `Initialize_Game` metodu, gerekli tüm parametreleri string olarak alır, enjeksiyon türünü belirler ve işi `Injector_Core`'a devreder. Ayrıca, işlemin sonucunu yakalamaktan ve son kullanıcıya `MessageBox` aracılığıyla hata mesajları sunmaktan sorumludur, bu da son kullanıcı ile etkileşimi tutarlı hale getirir.

```csharp
// Injector.cs'den bir kesit
public static class Injector {
    private static readonly Injector_Core s_core = new();

    public static void Initialize_Game(string inject_type_str, string folder, string nickname, string ip, string port, string password) {
        // ... inject_type_str'yi Injection_Type'a dönüştürme mantığı ...

        if (!s_core.Try_Initialize_Game(type, folder, nickname, ip, port, password, out string error_message)) {
            string error_title = (type == Injection_Type.OMP) ? Constants.ERROR_TITLE_OMP : Constants.ERROR_TITLE_SAMP;
            MessageBox.Show(error_message, error_title, MessageBoxButtons.OK, MessageBoxIcon.Error);
        }
    }
}
```

### 4. `InjectorCore.cs`

Bu, enjeksiyon operasyonları dizisinin düzenlendiği kütüphanenin "beynidir". Tam iş akışını yürütmek için giriş doğrulayıcılarını süreç işleyicileriyle birleştirir.

- **Ana Sorumluluk:** `Try_Initialize_Game` metodu, adım adım mantığı tanımlar: girdileri doğrular, oyun sürecini askıya alınmış durumda oluşturur, gerekli DLL'leri (`samp.dll` ve isteğe bağlı olarak `omp-client.dll`) enjekte eder ve her şey başarılı olursa oyun thread'ini sürdürür. Önemli bir yönü, enjeksiyon adımları sırasında herhangi bir arıza durumunda "zombi" süreçleri önlemek için oyun sürecinin sonlandırılmasını (`Kill()`) garanti eden `finally` bloğudur.

```csharp
// InjectorCore.cs'den bir kesit
internal sealed class Injector_Core {
    public bool Try_Initialize_Game(...) {
        // ... Giriş doğrulaması ...

        using Process_Handler.Process_Info process_info = Process_Handler.Create_Game_Process(...);
        
        // ...
        bool success = false;
        try {
            // ... samp.dll enjeksiyonu ...
            // ... isteğe bağlı omp-client.dll enjeksiyonu ...
            // ... oyun thread'inin sürdürülmesi ...
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

Kütüphanenin ilk savunma hattı olarak görev yapar ve yalnızca geçerli ve güvenli verilerin işlenmesini sağlar. Ön doğrulama, düşük seviyeli istisnaları önler ve kütüphanenin açık ve eyleme geçirilebilir hata mesajları sunmasına olanak tanır.

- **Ana Sorumluluk:** `Try_Validate` statik metodu, takma adın biçimi, portun sayısal aralığı ve en önemlisi, belirtilen dizinde temel dosyaların (`gta_sa.exe`, `samp.dll`, vb.) varlığı dahil olmak üzere bir dizi kontrol gerçekleştirir. Herhangi bir kontrol başarısız olursa, `false` döndürür ve bir `out string`'i hatanın açıklamasıyla doldurur.

```csharp
// InputValidator.cs'den bir kesit
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

Bu dosya, C#'ın yönetilen kodu ile Windows'un yönetilmeyen yerel API'leri arasındaki köprüdür. `kernel32.dll`'den fonksiyon imzalarını bildirmek için P/Invoke birlikte çalışabilirlik özelliğini kullanır.

- **Ana Sorumluluk:** `CreateProcessA`, `VirtualAllocEx` ve `CreateRemoteThread` gibi Windows API işlevlerine karşılık gelen `[LibraryImport]` veya `[DllImport]` özniteliklerine sahip `extern` metotları bildirmek. Ayrıca, yerel kodla uyumlu bellek düzenine sahip veri yapılarını (`Startup_Info`, `Process_Information`) tanımlar. Optimizasyon için, `kernel32.dll` handle'ları ve `LoadLibraryA` fonksiyon adresi başlangıçta statik olarak yüklenir.

```csharp
// NativeImports.cs'den bir kesit
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

Süreç manipülasyonu operasyonlarını yürüten düşük seviyeli katmandır. İşletim sistemiyle doğrudan etkileşim kurmak için `NativeImports.cs`'den içe aktarılan işlevleri kullanır.

- **Ana Sorumluluklar:**
   1. **`Create_Game_Process`**: Komut satırını oluşturur ve `gta_sa.exe`'yi `CREATE_SUSPENDED` bayrağıyla başlatır.
   2. **`Inject_DLL`**: Uzak bir thread oluşturarak DLL enjeksiyon tekniğini uygular. Bu, bellek ayırma, yazma ve `LoadLibraryA`'nın uzaktan yürütülmesini düzenleyen en kritik işlevdir.
   3. **`Resume_Game_Thread`**: Oyunun ana thread'ini "çözme"nin son adımını gerçekleştirir.

```csharp
// ProcessHandler.cs'den bir kesit
internal static bool Inject_DLL(SafeProcessHandle process_handle, string dll_path, out string error_message) {
    // ... Uzak bellekte ayırma ve yazma ...

    IntPtr remote_thread = Native_Imports.CreateRemoteThread(process_handle, IntPtr.Zero, 0, Native_Imports.load_library_address, remote_memory, 0, IntPtr.Zero);

    if (remote_thread == IntPtr.Zero)
        return (error_message = $"Failed to create a remote thread...") != null && false;
    
    // ... Tamamlanmasını bekle ve sonucu kontrol et ...
    return true;
}
```

### 8. `SafeHandles.cs`

Bu dosya, birlikte çalışabilirlik için önerilen bir uygulamayı uygular: yönetilmeyen kaynakları yönetmek için `SafeHandle` kullanımı. Bu, Windows süreç ve thread "handle"larının belirleyici ve güvenli bir şekilde serbest bırakılmasını sağlar.

- **Ana Sorumluluk:** `SafeProcessHandle` ve `SafeThreadHandle` sınıfları `SafeHandleZeroOrMinusOneIsInvalid`'den miras alır. Yerel handle'ı temsil eden bir `IntPtr`'ı kapsüllerler. Temel avantajı, nesne atıldığında (örneğin, bir `using` bloğunun sonunda) .NET çalışma zamanı tarafından çağrılması garanti edilen `ReleaseHandle` yönteminin uygulanmasıdır, bu da kaynak sızıntılarını önler.

```csharp
// SafeHandles.cs'den bir kesit
internal sealed class SafeProcessHandle : SafeHandleZeroOrminusOneIsInvalid {
    // ... Kurucular ...

    protected override bool ReleaseHandle() {
        // Bu çağrı, yerel handle'ı serbest bırakmak için .NET tarafından garanti edilir.
        return Native_Imports.CloseHandle(handle);
    }
}
```

## Ayrıntılı DLL Enjeksiyon Döngüsü

DLL enjeksiyon süreci, başarılı olmak için hassasiyetle yürütülmesi gereken bir dizi kritik adımdır. **SA-MP Injector C#** kütüphanesi bunu aşağıdaki şekilde düzenler:

### 1. Giriş Doğrulaması

Sistemle herhangi bir etkileşimden önce, kullanıcı tarafından sağlanan tüm parametreler (oyun klasörü yolu, takma ad, IP, port ve şifre) `Input_Validator` tarafından kontrol edilir. Bu şunları içerir:
- Takma adın uzunluk sınırları içinde ve boş olup olmadığını kontrol etmek.
- Portun geçerli bir sayı olduğundan ve kabul edilebilir aralıkta (1-65535) olduğundan emin olmak.
- `gta_sa.exe`, `samp.dll` ve `omp-client.dll`'nin (`Injection_Type` OMP ise) beklenen yollarda mevcut olduğunu doğrulamak.

> [!NOTE]
> Bu önleyici adım, beklenmedik API hatalarını önlemek ve kullanıcıya net geri bildirim sağlamak için temeldir.

### 2. Oyun Sürecinin Oluşturulması (Askıya Alınmış)

Kütüphane, `gta_sa.exe`'yi başlatmak için `Native_Imports.CreateProcessA`'yı kullanır. Ancak, önemli bir detay `Constants.CREATE_SUSPENDED` bayrağının kullanılmasıdır.
- **Askıya Alınmış Oluşturma:** Bu bayrak, Windows'un süreci ve ana thread'ini oluşturmasını ancak onu askıya alınmış bir duruma getirmesini sağlar, bu da oyun kodunun çalışmaya başlamasını engeller.
- **Komut Satırı:** Komut satırı, tüm sunucu bağlantı parametrelerini (`-c -n <nickname> -h <ip> -p <port> -z <password>`) içerecek şekilde `Process_Handler.Build_Full_Command_Args_ANSI` tarafından dikkatlice oluşturulur.
- **Süreç/Thread Handle'ları:** `CreateProcessA`, güvenli kaynak yönetimi için `SafeProcessHandle` ve `SafeThreadHandle`'da kapsüllenen süreç ve ana thread'in handle'larını döndürür.

> [!IMPORTANT]
> Askıya alınmış oluşturma, enjeksiyon için hayati önem taşır. Eğer oyun enjeksiyondan önce çalışmaya başlasaydı, kendi güvenlik mekanizmalarını başlatabilir veya `samp.dll`/`omp-client.dll` bizim kontrolümüzden önce yüklenebilir, bu da enjeksiyonu daha karmaşık veya etkisiz hale getirirdi.

### 3. `samp.dll` Enjeksiyonu

Oyun süreci askıya alınmış durumdayken, `Process_Handler.Inject_DLL` işlevi aşağıdaki adımları gerçekleştirir:
1. **`LoadLibraryA`'yı Al:** Oyun sürecindeki `LoadLibraryA` (`kernel32.dll`'den) işlevinin adresi alınır. Bu, Windows'un DLL'leri yüklemek için kullandığı işlevdir.
2. **Uzak Bellek Ayırma:** `Native_Imports.VirtualAllocEx`, `gta_sa.exe` sürecinin sanal adres alanı içinde bir bellek bloğu ayırmak için kullanılır. Bloğun boyutu, `samp.dll`'nin tam yolunu saklamak için yeterlidir.
3. **DLL Yolunu Yazma:** `samp.dll` dosyasının tam yolu, `Native_Imports.WriteProcessMemory` kullanılarak oyun sürecindeki yeni ayrılan belleğe yazılır.
4. **Uzak Thread Oluşturma:** `Native_Imports.CreateRemoteThread`, `gta_sa.exe` sürecinde yeni bir thread oluşturmak için çağrılır. Bu thread, tek argümanı olarak DLL yolu dizesinin adresiyle `LoadLibraryA`'yı yürütmesi için yönlendirilir.
5. **Tamamlanmasını Bekleme:** Kütüphane, uzak thread'in yürütmesini tamamlaması için bir zaman aşımı süresi (`Constants.DLL_INJECTION_TIMEOUT_MS`) bekler, bu da `LoadLibraryA`'nın DLL'i yüklemeye çalıştığını gösterir.
6. **Sonucu Kontrol Et:** Uzak thread'in çıkış kodu kontrol edilir. `LoadLibraryA` başarılı olursa, yüklenen DLL'in temel adresini döndürür. Sıfır değeri veya çıkış kodunu alamama, enjeksiyonun başarısız olduğunu gösterir.
7. **Temizlik:** Ayrılan uzak bellek serbest bırakılır (`Native_Imports.VirtualFreeEx`) ve uzak thread'in handle'ı kapatılır (`Native_Imports.CloseHandle`).

### 4. `omp-client.dll` Enjeksiyonu (İsteğe Bağlı, SA-MP'ye Bağımlı)

> [!TIP]
> `omp-client.dll` enjeksiyonu **her zaman `samp.dll`'nin başarılı enjeksiyonundan sonra gerçekleşir**. OMP istemcisi, SA-MP'nin altyapısını kullandığından, `samp.dll` bir gerekliliktir.

Belirtilen `Injection_Type` `OMP` ise, `omp-client.dll`'yi enjekte etmek için 3. adım tekrarlanır. Mantık aynıdır, bu da OMP için gerekli olan her iki kütüphanenin de oyun tamamen başlamadan önce yüklenmesini sağlar.

### Oyunun Ana Thread'ini Sürdürme

Son olarak, gerekli tüm DLL'ler başarıyla enjekte edildikten sonra `Process_Handler.Resume_Game_Thread` işlevi çağrılır. Bu işlev, `gta_sa.exe`'nin ana thread'inin yürütmesine devam etmesine izin vermek için `Native_Imports.ResumeThread`'i kullanır. Oyun şimdi SA-MP/OMP DLL'leri zaten yüklenmiş ve sunucuya bağlanmak için komut satırı argümanları uygulanmış olarak başlar.

## Hata Yönetimi ve Başarısızlık Durumları

Kütüphane, bir hata durumunda net geri bildirim sağlamak üzere tasarlanmıştır. Çoğu hata yakalanır ve kullanıcıya genellikle bir `MessageBox` aracılığıyla sunulmak üzere açıklayıcı bir `error_message` döndürülür.

### Giriş Doğrulama Hataları

Bu hatalar, herhangi bir sistem işleminden önce meydana gelir ve `Input_Validator` tarafından tespit edilir.

#### Geçersiz Nickname

- **Hata Mesajı (Örnek 1):** `"Nickname cannot be empty. Please provide a valid nickname."`
- **Hata Mesajı (Örnek 2):** `"Nickname length exceeds the maximum allowed of 23 characters. Please use a shorter nickname."`
- **Neden:** Takma ad alanı boş veya izin verilen maksimum 23 karakter sınırını aşıyor.
- **Çözüm:** Kullanıcı, geçerli ve karakter sınırına uyan bir takma ad sağlamalıdır.

#### Geçersiz Port

- **Hata Mesajı (Örnek 1):** `"Invalid port format. The port must be a numeric value. Please provide a valid integer for the port."`
- **Hata Mesajı (Örnek 2):** `"The specified port number (70000) is outside the valid range of 1 to 65535. Please provide a valid port."`
- **Neden:** Sağlanan port bir tamsayı değil veya 1 ile 65535 arasındaki geçerli aralığın dışında.
- **Çözüm:** Kullanıcı, geçerli ve belirtilen aralıkta bir port numarası girmelidir.

#### Eksik Oyun/DLLs Dosyaları

- **Hata Mesajı (Örnek 1):** `"Game executable not found. Please ensure 'gta_sa.exe' exists at the specified path: C:\Program Files (x86)\Rockstar Games\GTA San Andreas\gta_sa.exe"`
- **Hata Mesajı (Örnek 2):** `"SA-MP library not found. Please ensure 'samp.dll' exists at the specified path: C:\Program Files (x86)\Rockstar Games\GTA San Andreas\samp.dll"`
- **Hata Mesajı (Örnek 3, OMP):** `"OMP library not found. Please ensure 'omp-client.dll' exists at the specified path for OMP injection: C:\Program Files (x86)\Rockstar Games\GTA San Andreas\omp-client.dll"`
- **Neden:** Oyunun çalıştırılabilir dosyası (`gta_sa.exe`), SA-MP DLL'i (`samp.dll`) veya OMP DLL'i (`omp-client.dll`) belirtilen oyun klasöründe bulunamadı.
- **Çözüm:** Kullanıcı, oyun klasörünün yolunu kontrol etmeli ve gerekli tüm dosyaların mevcut olduğundan emin olmalıdır.

### Süreç Oluşturma Hataları

Bu hatalar, kütüphane `gta_sa.exe`'yi başlatmaya çalıştığında meydana gelir.

#### Süreç Oluşturulamadı

- **Hata Mesajı (Örnek):** `"Failed to create game process. Ensure 'gta_sa.exe' is not running and you have sufficient permissions to execute the file. System Error: Access is denied."`
- **Neden:**
   - **Dosya Kullanımda:** `gta_sa.exe` zaten çalışıyor olabilir, bu da yeni bir örneğin oluşturulmasını veya işletim sisteminin dosya üzerinde bir kilit bulundurmasını engelleyebilir.
   - **İzinler:** Uygulamayı çalıştıran kullanıcının yeni bir süreç başlatmak veya oyunun çalıştırılabilir dosyasına erişmek için yeterli izni olmayabilir.
   - **Geçersiz/Bozuk Yol:** Temel doğrulama varlığını kontrol etse de, okuma/yürütme izni sorunları olabilir veya çalıştırılabilir dosya bozuk olabilir.
- **Çözüm:** Başka bir `gta_sa.exe` örneğinin çalışmadığından emin olun. Mümkünse uygulamayı yönetici olarak çalıştırın. `gta_sa.exe` dosyasının bütünlüğünü kontrol edin.

### DLL Enjeksiyon Hataları

Bunlar en kritik hatalardır ve `samp.dll` veya `omp-client.dll`'yi oyun sürecine enjekte etme girişimi sırasında meydana gelirler.

#### Kullanılamayan `kernel32.dll` Handle'ı

- **Hata Mesajı:** `"Failed to obtain a handle to kernel32.dll. This is an essential system library and this error indicates a severe system issue."`
- **Neden:** Windows'taki sistem işlemleri için temel olan `kernel32.dll` kütüphanesi yüklenemedi veya handle'ı alınamadı. Bu son derece nadirdir ve ciddi bir işletim sistemi sorununa işaret eder.
- **Çözüm:** Sistemi yeniden başlatmak sorunu çözebilir. Aksi takdirde, Windows kurulumuyla ilgili daha derin bir soruna işaret eder.

#### Kullanılamayan `LoadLibraryA` Fonksiyonu

- **Hata Mesajı:** `"Failed to find the address of the LoadLibraryA function in kernel32.dll. This is critical for injecting the DLL."`
- **Neden:** DLL'leri dinamik olarak yüklemek için gerekli olan `LoadLibraryA` fonksiyonu `kernel32.dll`'de bulunamadı. Önceki hata gibi, bu da nadir görülen düşük seviyeli bir sorundur.
- **Çözüm:** `kernel32.dll` handle'ının kullanılamamasına benzer.

#### Uzak Bellek Ayırma Hatası

- **Hata Mesajı:** `"Failed to allocate memory in the target process. This might be due to insufficient permissions or process protection mechanisms."`
- **Neden:** Kütüphane, `gta_sa.exe`'nin adres alanında bir bellek bloğu ayıramadı.
   - **İzinler:** Uygulamanın başka bir sürecin bellek alanını değiştirmek için gerekli izinlere sahip olmayabilir.
   - **Süreç Koruması:** `gta_sa.exe` süreci veya işletim sistemi, kod enjeksiyonuna karşı korumalar uyguluyor olabilir.
   - **Adres Alanı:** Aşırı durumlarda, sürecin adres alanı parçalanmış veya yeterli bitişik belleğe sahip olmayabilir, ancak bir DLL yolu dizesinin boyutu için bu olası değildir.
- **Çözüm:** Uygulamayı yönetici olarak çalıştırın. Diğer süreçlerde bellek ayırmayı engelleyebilecek güvenlik yazılımlarını (antivirüs, anti-hile) kontrol edin.

#### Süreç Belleğine Yazma Hatası

- **Hata Mesajı:** `"Failed to write DLL path to the target process memory. Verify process permissions and ensure the DLL path is accessible."`
- **Neden:** Kütüphane oyun sürecinde bellek ayırdı, ancak DLL yolunu o konuma yazamadı.
   - **İzinler:** Bellek ayırma hatasına benzer şekilde, bu bir yazma izni sorunu olabilir.
   - **Koruma:** İşletim sistemi bellek koruması veya anti-hile yazılımı yazmayı engelliyor olabilir.
- **Çözüm:** İzinleri ve güvenlik yazılımlarını kontrol edin.

#### Uzak Thread Oluşturma Hatası

- **Hata Mesajı (Örnek):** `"Failed to create a remote thread in the target process to execute the DLL injection. This could be due to security restrictions or process state. System Error: Not enough memory resources are available to process this command."`
- **Neden:** `CreateRemoteThread` API'si, `LoadLibraryA`'yı çağırmak için `gta_sa.exe` sürecinde yeni bir thread oluşturamadı.
   - **Süreç Koruması/Anti-Hile:** Birçok anti-hile sistemi ve işletim sistemi koruması, yaygın bir enjeksiyon tekniği olduğu için uzak thread'lerin oluşturulmasını izler ve engeller.
   - **Süreç Durumu:** Oyun süreci, thread oluşturulmasını engelleyen tutarsız bir durumda olabilir.
- **Çözüm:** Herhangi bir anti-hile veya antivirüs yazılımını geçici olarak devre dışı bırakın. Uygulamayı yönetici olarak çalıştırmayı deneyin.

#### Enjeksiyon Beklemesinde Zaman Aşımı veya Hata

- **Hata Mesajı (Örnek):** `"Timeout or error waiting for DLL injection to complete. System Error: The wait operation timed out."`
- **Neden:** Uzak thread (`LoadLibraryA`'yı çağıran), belirtilen zaman aşımı süresi içinde (10 saniye) yürütmesini tamamlamadı.
   - **Donma:** `LoadLibraryA` kilitlenmiş veya aşırı uzun sürmüş olabilir.
   - **Engelleme:** Bazı güvenlik mekanizmaları `LoadLibraryA`'nın yürütülmesini engellemiş ve süresiz olarak bloke etmiş olabilir.
- **Çözüm:** DLL'in yüklenmesinin çok uzun sürdüğünü veya bir şeyin onu engellediğini gösterebilir. Sistem veya SA-MP/OMP günlüklerini (varsa) kontrol etmek yardımcı olabilir.

#### DLL Enjeksiyonu Başarısız Oldu veya Hata Döndürdü

- **Hata Mesajı:** `"DLL injection failed or returned an error. The LoadLibrary call may have failed in the target process."`
- **Neden:** Uzak thread tamamlandı, ancak `LoadLibraryA`'nın çıkış kodu başarısız olduğunu gösterdi (genellikle `0` veya `NULL`).
   - **Mevcut Olmayan/Bozuk DLL:** İlk doğrulamaya rağmen, DLL doğrulama ile enjeksiyon arasında taşınmış veya bozulmuş olabilir.
   - **Eksik DLL Bağımlılıkları:** `samp.dll` veya `omp-client.dll`, oyun dizininde veya sistemin PATH'inde bulunmayan diğer DLL'lere bağlı olabilir.
   - **DLL İç Hatası:** DLL'in kendisi, doğru şekilde yüklenmesini engelleyen bir iç hataya sahip olabilir.
- **Çözüm:** `samp.dll`/`omp-client.dll`'nin bütünlüğünü kontrol edin. DLL'in tüm bağımlılıklarının mevcut olduğundan emin olun.

### Oyun Thread'ini Sürdürürken Hata

Bu, enjeksiyon döngüsündeki olası son hatadır.

- **Hata Mesajı (Örnek):** `"Failed to resume the game process thread: Invalid handle."`
- **Neden:** `ResumeThread` API'si, `gta_sa.exe`'nin ana thread'ini yeniden başlatamadı.
   - **Geçersiz Handle:** Thread'in handle'ı bir nedenle geçersiz kılınmış olabilir.
   - **İzin Sorunu:** Uygulamanın thread'in durumunu değiştirme izni olmayabilir.
- **Çözüm:** Uygulamayı yönetici olarak çalıştırmayı deneyin. Devam ederse, sistemin veya oyun sürecinin kararlılığıyla ilgili daha derin bir soruna işaret edebilir.

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