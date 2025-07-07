# SA-MP Injector

[![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](https://opensource.org/licenses/MIT)
[![SA-MP | OMP](https://img.shields.io/badge/Support-SA--MP%20%7C%20OMP-yellow)](https://github.com/spc-samp/samp-injector)
[![x86 Only](https://img.shields.io/badge/Architecture-x86%20(32--bit)-orange)](https://github.com/spc-samp/samp-injector)

**SA-MP Injector**, **SA-MP (San Andreas Multiplayer)** ve **OMP (Open Multiplayer)** için tasarlanmış çok yönlü bir araçtır ve bir **komut satırı çalıştırılabilir dosyası**, bir **dinamik kütüphane (DLL)** ve farklı programlama dilleri için bir **kütüphane seti** olarak işlev görür. Ana işlevi, **GTA:SA** sürecine `samp.dll` (**SA-MP** durumunda) veya hem `samp.dll` hem de `omp-client.dll` (**OMP** durumunda) enjekte ederek oyunun özelleştirilmiş parametrelerle başlatılmasını sağlamaktır, bu da bir sunucuya doğrudan bağlantı kurmayı mümkün kılar.

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

- [SA-MP Injector](#sa-mp-injector)
  - [Diller](#diller)
  - [İçindekiler](#i̇çindekiler)
  - [Çalıştırılabilir Dosya](#çalıştırılabilir-dosya)
    - [İşlevsellik](#i̇şlevsellik)
    - [Nasıl Kullanılır (Komut Satırı)](#nasıl-kullanılır-komut-satırı)
      - [SA-MP Modu](#sa-mp-modu)
      - [OMP Modu](#omp-modu)
      - [Parametreler](#parametreler)
    - [Nasıl Kullanılır (Uygulamalara Entegre Edilmiş)](#nasıl-kullanılır-uygulamalara-entegre-edilmiş)
    - [Çalıştırılabilir Dosyada C++ Kütüphanesinin Kullanımı](#çalıştırılabilir-dosyada-c-kütüphanesinin-kullanımı)
    - [Nasıl Derlenir](#nasıl-derlenir)
      - [Gereksinimler](#gereksinimler)
      - [Derleme Adımları](#derleme-adımları)
  - [Dinamik Kütüphane (**DLL**)](#dinamik-kütüphane-dll)
    - [İşlevsellik](#i̇şlevsellik-1)
    - [Kullanımı (API Çağrısı)](#kullanımı-api-çağrısı)
      - [`Launch_Game` Fonksiyon Sözleşmesi](#launch_game-fonksiyon-sözleşmesi)
      - [Parametreler](#parametreler-1)
    - [Kullanımı (Uygulamalara Gömülü)](#kullanımı-uygulamalara-gömülü)
    - [**DLL** İçinde C++ Kütüphanesinin Kullanımı](#dll-i̇çinde-c-kütüphanesinin-kullanımı)
    - [Nasıl Derlenir](#nasıl-derlenir-1)
      - [Gereksinimler](#gereksinimler-1)
      - [Derleme Adımları](#derleme-adımları-1)
  - [Kütüphaneler](#kütüphaneler)
    - [Genel Bakış](#genel-bakış)
    - [Kütüphane Listesi](#kütüphane-listesi)
  - [Lisans](#lisans)
    - [Kullanım Şartları ve Koşulları](#kullanım-şartları-ve-koşulları)
      - [1. Verilen İzinler](#1-verilen-i̇zinler)
      - [2. Zorunlu Koşullar](#2-zorunlu-koşullar)
      - [3. Telif Hakları](#3-telif-hakları)
      - [4. Garanti Reddi ve Sorumluluk Sınırlaması](#4-garanti-reddi-ve-sorumluluk-sınırlaması)

## Çalıştırılabilir Dosya

Çalıştırılabilir dosya `samp-injector.exe`, **GTA:SA**'yı **SA-MP** veya **OMP** ile başlatmak için bir komut satırı arayüzü sunar ve sunucuya bağlantıyı otomatik olarak yapılandırır. **DLL enjeksiyonu** ve oyun parametrelerinin aktarılması mantığını kapsüller.

### İşlevsellik

`samp-injector.exe`, oyun başlatma sürecini otomatikleştiren bir istemci olarak çalışır ve **DLL** konfigürasyonu ve enjeksiyonunun karmaşıklığını soyutlar:

1. **Ortam Doğrulaması:** Belirtilen dizinde gerekli dosyaların (`gta_sa.exe`, `samp.dll`, `omp-client.dll`) varlığını ve sağlanan bağlantı parametrelerinin doğruluğunu kontrol eder.
2. **Askıya Alınmış Süreç Oluşturma:** `gta_sa.exe`'yi askıya alınmış bir durumda başlatır; bu, oyunun ana süreci çalıştırılmadan önce **DLL'lerin güvenli bir şekilde enjekte edilmesi** için bir ön koşuldur.
3. **Dinamik DLL Enjeksiyonu:**
   - **SA-MP** modu için sadece `samp.dll` enjekte edilir.
   - **OMP** modu için hem `samp.dll` hem de `omp-client.dll` enjekte edilir. Enjeksiyon, `LoadLibraryA` fonksiyonunun uzaktan çağrılmasıyla kolaylaştırılır, bu da GTA: SA'nın çok oyunculu modülleri yüklemesini ve bağlantıyı başlatmasını sağlar.
4. **Argümanların Yapılandırılması:** Komut satırı argümanları, örneğin **kullanıcı adı**, **sunucu IP'si**, **port** ve **şifre (eğer sağlanmışsa)**, hazırlanır ve `gta_sa.exe`'ye aktarılır.
5. **Sürecin Devam Ettirilmesi:** **DLL'lerin başarılı bir şekilde enjekte edilmesinden** sonra, oyun süreci normal çalışmaya devam ettirilir ve **GTA:SA** doğrudan sunucuya bağlanır.

### Nasıl Kullanılır (Komut Satırı)

Çalıştırılabilir dosyayı kullanmak için, gerekli parametreleri sağlayarak **Komut İstemi (CMD)**, **PowerShell** veya **terminal** üzerinden çağırın.

Temel format şöyledir:
```bash
samp-injector.exe <mod> <oyun_dizini> <kullanıcı_adı> <sunucu_IP> <sunucu_portu> <sunucu_şifresi (isteğe bağlı)>
```

#### SA-MP Modu

Sadece `samp.dll` enjeksiyonu için:
```bash
samp-injector.exe "samp" "C:\Games\GTA San Andreas" "İsim" "127.0.0.1" "7777" "şifre (isteğe bağlı)"
```

#### OMP Modu

`samp.dll` ve `omp-client.dll` enjeksiyonu için:
```bash
samp-injector.exe "omp" "C:\Games\GTA San Andreas" "İsim" "127.0.0.1" "7777" "şifre (isteğe bağlı)"
```

#### Parametreler

- `<mod>`: Enjeksiyon türünü belirler.
   - `samp`: **SA-MP** için (`samp.dll`).
   - `omp`: **OMP** için (`samp.dll` ve `omp-client.dll`).
- `<oyun_dizini>`: **GTA:SA** dizinine tam yol. Bu dizin, `gta_sa.exe` ve ilgili **DLL** dosyalarını içermelidir.
- `<kullanıcı_adı>`: Oyundaki kullanıcı adınız (en fazla **20 karakter**).
- `<sunucu_IP>`: Sunucunun **IP adresi** veya **alan adı**.
- `<sunucu_portu>`: Sunucu bağlantı portu (**1** ile **65535** arasında **sayısal bir değer**).
- `<sunucu_şifresi>`: Sunucuya bağlanmak için gereken şifre **(eğer sunucunun şifresi yoksa, bu parametre eklenmeyebilir)**.

Argümanlar yanlış veya eksikse, bir kullanım mesajı görüntülenir.

### Nasıl Kullanılır (Uygulamalara Entegre Edilmiş)

`samp-injector.exe`, özelleştirilmiş başlatıcılar gibi üçüncü taraf uygulamalara entegre edilerek oyunu önceden tanımlı ayarlarla başlatma sürecini otomatikleştirmek için idealdir.

**C#** uygulamasından `samp-injector.exe`'yi çağırma örneği:
```csharp
using System;
using System.Diagnostics;
using System.Windows.Forms;

public class Launcher {
    public static void Main(string[] args) {
        string inject_mode = "omp"; 
        string folder = "C:\\Games\\GTA San Andreas";
        string nickname = "İsim";
        string ip = "127.0.0.1";
        string port = "7777";
        string password = "şifre (isteğe bağlı)";

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
                    MessageBox.Show($"SA-MP Injector bir hata döndürdü (Kod: {process.ExitCode}). Oyun doğru şekilde başlatılamamış olabilir.", "Başlatma Hatası", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }
        catch (Exception ex) {
            MessageBox.Show($"Oyunu başlatırken bir hata oluştu: {ex.Message}", "Hata", MessageBoxButtons.OK, MessageBoxIcon.Error);
        }
    }
}
```

### Çalıştırılabilir Dosyada C++ Kütüphanesinin Kullanımı

Çalıştırılabilir dosya `samp-injector.exe`, `libraries/cpp/` dizininde bulunan [SA-MP Injector C++](https://github.com/spc-samp/samp-injector/tree/main/libraries/cpp) kütüphanesine dayanır. Çalıştırılabilir dosyanın `main.cpp` dosyası, enjeksiyon ve oyunun başlatılması için bu kütüphanenin işlevlerini kullanır.

**C++** kütüphanesinin dahil edilmesi gereken ana başlık dosyası `libraries/samp-injector/cpp/injector.hpp` dosyasıdır. [SA-MP Injector C++](https://github.com/spc-samp/samp-injector/tree/main/libraries/cpp) kütüphanesi **header-only** olduğundan, kullanımı yalnızca bu başlığın kaynak koda dahil edilmesini gerektirir ve `.lib` dosyasına bağlanma ihtiyacı yoktur.

`main.cpp` dosyasındaki entegrasyonu gösteren ilgili bölüm şöyledir:
```cpp
// Komut satırı argümanlarını çıkarır
int argc;
std::unique_ptr<LPWSTR[], decltype(&LocalFree)> argv(CommandLineToArgvW(GetCommandLineW(), &argc), &LocalFree);

// ... (argüman sayısı ve enjeksiyon modu doğrulaması) ...

// Parametreleri geniş dize değişkenlerine çıkarır
std::wstring folder = argv[2];
std::wstring nickname = argv[3];
std::wstring ip = argv[4];
std::wstring port = argv[5];
std::wstring password = (argc == 7) ? argv[6] : L"";

// Enjeksiyon mantığını kütüphanenin "Initialize_Game" fonksiyonuna devreder
// Not: "injector.hpp" daha önce "main.cpp" dosyasına dahil edilmiştir
if (!Initialize_Game(inject_type, folder, nickname, ip, port, password))
    return 1;

Sleep(10000); // Çalıştırılabilir dosyanın kapanmasından önce bekler
```

`Initialize_Game` fonksiyonu, kütüphanenin yüksek seviyeli arayüzü olarak çalışır ve doğrulama, süreç oluşturma ve **DLL enjeksiyonu** gibi tüm işlemleri koordine eder.

### Nasıl Derlenir

`samp-injector.exe`'yi kaynak kodundan derleyebilirsiniz. Derlemek istemiyorsanız, [Releases](https://github.com/spc-samp/samp-injector/releases) bölümünden önceden derlenmiş sürümleri indirebilirsiniz.

#### Gereksinimler

- **Visual Studio:** **Visual Studio 2022** veya daha yeni bir sürüm ve **"C++ ile masaüstü geliştirme"** iş yükü yüklü olması önerilir.
- **Git:** Depoyu klonlamak için (veya bu bağlantıya tıklayarak doğrudan indirin: [İndir](https://github.com/spc-samp/samp-injector/archive/refs/heads/main.zip)).

#### Derleme Adımları

1. **Depoyu klonlayın:**
   ```bash
   git clone https://github.com/spc-samp/samp-injector.git
   cd samp-injector
   ```
2. **Çözümü açın:**
   `executable` klasörüne gidin ve `.sln` çözüm dosyasını açın:
   ```bash
   cd executable
   start samp-injector.sln
   ```
   Bu, projeyi **Visual Studio**'da açar.
3. **Derlemeyi yapılandırın:**
   - **Visual Studio**'da çözüm yapılandırmasını kontrol edin. `Release` ve `x86` **(32-bit)** modlarının kullanılması önerilir. **GTA:SA** ve **SA-MP**/**OMP** bağlamında **x86 (32-bit)** mimarisi zorunludur.
4. **Derleyin:**
   - `Derleme` menüsünde `Çözümü Derle` veya `samp-injector'ı Derle` seçeneğine tıklayın.
   - Alternatif olarak, şu kısayolları kullanabilirsiniz:
      - `Ctrl + Shift + B` tüm çözümü derlemek için.
      - `Ctrl + B` (eğer yapılandırılmışsa) mevcut projeyi derlemek için.
   - Her şey doğru yapılandırılmışsa, `samp-injector.exe` çalıştırılabilir dosyası `executable\Release` dizininde (veya yapılandırmanıza bağlı olarak `executable\Debug` dizininde) oluşturulur.

## Dinamik Kütüphane (**DLL**)

`samp-injector.dll` kütüphanesi, **GTA:SA**'yı **SA-MP** veya **OMP** ile programatik olarak başlatmak için bir **API (Uygulama Programlama Arayüzü)** sunar. Bu, daha temiz ve doğrudan bir entegrasyon isteyen launcher geliştiricileri için çalıştırılabilir dosyanın ideal alternatifidir; bir fonksiyon çağırarak harici bir süreç başlatmak yerine kullanılır.

### İşlevsellik

`samp-injector.dll`, iç kütüphanenin aynı sağlam iş akışını tetikler ve enjeksiyon ile oyun başlatma karmaşıklıklarını kapsüller:

1. **Askıya Alınmış Süreç Oluşturma:** Çağrıldığında, `gta_sa.exe` askıya alınmış bir durumda başlatılır.
2. **Dinamik DLL Enjeksiyonu:**
   - **SA-MP** modu için `samp.dll` enjekte edilir.
   - **OMP** modu için `samp.dll` ve `omp-client.dll` enjekte edilir.
3. **Argüman Yapılandırması:** Fonksiyon parametreleri, örneğin **takma ad**, **IP**, **port** ve **şifre**, `gta_sa.exe` için hazırlanır.
4. **Sürecin Devam Ettirilmesi:** Enjeksiyondan sonra oyun süreci yürütme için devam ettirilir ve doğrudan sunucuya bağlanır.

### Kullanımı (API Çağrısı)

Kütüphaneyi kullanmak için, `samp-injector.dll` dosyasını uygulamanıza yüklemeniz ve dışa aktarılmış `Launch_Game` fonksiyonunu çağırmanız gerekir.

#### `Launch_Game` Fonksiyon Sözleşmesi

- **DLL Dosyası:** `samp-injector.dll`
- **Dışa Aktarılmış Fonksiyon Adı:** `Launch_Game`
- **Çağrı Kuralı:** `__stdcall`
- **Dönüş Türü:** `int`
   - `0`: **Başarı.** Oyun başlatma isteği bir arka plan iş parçacığına gönderildi.
   - `1`: **Geçersiz Argümanlar.** Zorunlu bir parametre null idi veya mod geçersizdi. Bir hata mesajı görüntülenecek.
   - `2`: **İş Parçacığı Hatası.** Başlatma iş parçacığını oluşturma girişimi sırasında kritik bir hata oluştu. Bir hata mesajı görüntülenecek.

#### Parametreler

Tüm parametreler geniş karakter (Unicode) dizeleridir.

- `mode` (`LPCWSTR`): Enjeksiyon türünü tanımlar (`L"samp"` veya `L"omp"`).
- `folder` (`LPCWSTR`): **GTA:SA** dizinine tam yol.
- `nickname` (`LPCWSTR`): Oyundaki takma adınız.
- `ip` (`LPCWSTR`): Sunucunun **IP** adresi veya **alan adı**.
- `port` (`LPCWSTR`): Sunucunun bağlantı portu.
- `password` (`LPCWSTR`): Sunucuya bağlanmak için şifre. **(Bu parametre isteğe bağlıdır. Şifre yoksa `null` veya boş bir dize `L""` geçirilebilir)**.

### Kullanımı (Uygulamalara Gömülü)

**C# uygulamasından** `Launch_Game` fonksiyonunun çağrılma örneği:
```csharp
using System;
using System.Runtime.InteropServices;
using System.Windows.Forms;

public class Launcher {
    // DLL'den fonksiyonu içe aktarır ve API sözleşmesini belirtir.
    [DllImport("samp-injector.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.StdCall, EntryPoint = "Launch_Game")]
    private static extern int Launch_Game(string mode, string folder, string nickname, string ip, string port, string password);

    public static void Main(string[] args) {
        string inject_mode = "samp"; 
        string gta_folder = "C:\\Games\\GTA San Andreas"; // Dikkat: Gerçek yolu kullanın!
        string nickname = "İsim";
        string ip = "127.0.0.1";
        string port = "7777";
        string password = "şifre (isteğe bağlı)"; // veya null, ya da "" eğer yoksa

        try {
            int result = Launch_Game(inject_mode, gta_folder, nickname, ip, port, password);
            
            if (result != 0) {
                // DLL zaten ayrıntılı bir hata mesajı gösterir,
                // ancak burada başka bir mesaj kaydedebilir veya görüntüleyebilirsiniz.
                MessageBox.Show($"DLL çağrısı bir hata kodu döndürdü: {result}", "Launcher Hatası", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }
        catch (DllNotFoundException) {
            MessageBox.Show("Hata: samp-injector.dll bulunamadı! Launcher ile aynı klasörde olup olmadığını kontrol edin.", "Hata", MessageBoxButtons.OK, MessageBoxIcon.Error);
        }
        catch (Exception ex) {
            MessageBox.Show($"Beklenmeyen bir hata oluştu: {ex.Message}", "Hata", MessageBoxButtons.OK, MessageBoxIcon.Error);
        }
    }
}
```

### **DLL** İçinde C++ Kütüphanesinin Kullanımı

Çalıştırılabilir dosya gibi, `samp-injector.dll` de `libraries/cpp/` dizininde bulunan [SA-MP Injector C++](https://github.com/spc-samp/samp-injector/tree/main/libraries/cpp) kütüphanesine dayanır. Dışa aktarılmış `Launch_Game` fonksiyonu bir sarmalayıcı (wrapper) olarak işlev görür, parametreleri doğrular ve ana enjeksiyon mantığını kütüphanenin `Initialize_Game` fonksiyonuna devreder.

**C++** kütüphanesinin dahil edilmesi gereken ana başlık dosyası `libraries/samp-injector/cpp/injector.hpp` dosyasıdır. [SA-MP Injector C++](https://github.com/spc-samp/samp-injector/tree/main/libraries/cpp) kütüphanesi **header-only** olduğu için, kullanımı yalnızca bu başlığın kaynak koda dahil edilmesini gerektirir ve bir `.lib` dosyasına bağlanma ihtiyacı yoktur.

Aşağıdaki kod parçası, **DLL**'nin `main.cpp` dosyasından, görevin ayrı bir iş parçacığında nasıl devredildiğini gösterir:
```cpp
// Arka planda çalışan iş parçacığı fonksiyonu
void Game_Thread_Worker(const std::wstring& mode, const std::wstring& folder, const std::wstring& nickname, const std::wstring& ip, const std::wstring& port, const std::wstring& password) {
    // Enjeksiyon mantığı kütüphanenin "Initialize_Game" fonksiyonuna devredilir.
    Initialize_Game(mode, folder, nickname, ip, port, password);
}

// Dışa aktarılmış `Launch_Game` fonksiyonu içinde iş parçacığı oluşturulur:
try {
    std::thread(Game_Thread_Worker, mode_str, folder_str, nickname_str, ip_str, port_str, password_str).detach();
}
// ...
```

Bu, **DLL**'nin temel olarak çalıştırılabilir dosya tarafından kullanılan aynı temel işlevsellik için bir API arayüzü olduğunu gösterir.

### Nasıl Derlenir

`samp-injector.dll` dosyasını kaynak koddan derleyebilirsiniz. Derlemek istemiyorsanız, [Releases](https://github.com/spc-samp/samp-injector/releases) bölümünden önceden derlenmiş sürümleri indirebilirsiniz.

#### Gereksinimler

- **Visual Studio:** **Visual Studio 2022** veya daha üstü, **"C++ ile Masaüstü Geliştirme"** iş yükü yüklü olarak önerilir.
- **Git:** Depoyu klonlamak için (veya bu bağlantıdan basitçe indirin: [İndir](https://github.com/spc-samp/samp-injector/archive/refs/heads/main.zip)).

#### Derleme Adımları

1. **Depoyu Klonlayın:**
   ```bash
   git clone https://github.com/spc-samp/samp-injector.git
   cd samp-injector
   ```
2. **Çözümü Açın:**
   `dll` klasörüne gidin ve `.sln` çözüm dosyasını açın:
   ```bash
   cd dll
   start samp-injector.sln
   ```
   Bu, projeyi **Visual Studio**'da açacaktır.
3. **Derlemeyi Yapılandırın:**
   - **Visual Studio**'da çözüm yapılandırmasını kontrol edin. `Release` ve `x86` **(32-bit)** modlarının kullanılması önerilir. **GTA:SA** ve **SA-MP**/**OMP** bağlamında, **x86 (32-bit)** mimarisi zorunludur.
4. **Derleyin:**
   - `Compilation` menüsünde `Compile Solution` veya `Build samp-injector` seçeneğine tıklayın.
   - Alternatif olarak şu kısayolları kullanabilirsiniz:
      - Tüm çözümü derlemek için `Ctrl + Shift + B`.
      - Mevcut projeyi derlemek için (ayarlandıysa) `Ctrl + B`.
   - Her şey doğru şekilde yapılandırılmışsa, `samp-injector.dll` kütüphanesi `dll\Release` (veya yapılandırmanıza bağlı olarak `dll\Debug`) dizininde oluşturulacaktır.

## Kütüphaneler

Kütüphaneler, **SA-MP Injector**'ın temel bileşenleridir ve süreç yönetimi, **DLL enjeksiyonu** ve parametre doğrulaması için temel mantığı içerir. Bu kütüphaneleri kullanmanın temel avantajı, genellikle tek bir fonksiyon (veya komut dosyası dilleri için belirli parametrelerle çağrılar) aracılığıyla başlatma ve enjeksiyonun kolaylığıdır.

### Genel Bakış

Proje, kritik işlevleri kapsülleyen kütüphanelere dayanır. Bu, diğer projelerin **GTA:SA**'yı gerekli **çok oyunculu** modüllerle başlatma yeteneğini kolayca entegre etmesini sağlar.

### Kütüphane Listesi

| Dil           | İsim                       | Kütüphane/Dokumentasyon Bağlantısı  |
| ------------- | -------------------------- | ----------------------------------- |
| C++           | **SA-MP Injector C++**     | [Kütüphaneyi İncele](libraries/cpp) |
| C             | **SA-MP Injector C**       | (Yakında)                           |
| C#            | **SA-MP Injector C#**      | (Yakında)                           |
| Java          | **SA-MP Injector Java**    | (Yakında)                           |
| Python        | **SA-MP Injector Python**  | (Yakında)                           |
| Go (Golang)   | **SA-MP Injector Go**      | (Yakında)                           |
| Rust          | **SA-MP Injector Rust**    | (Yakında)                           |
| Kotlin        | **SA-MP Injector Kotlin**  | (Yakında)                           |
| Scala         | **SA-MP Injector Scala**   | (Yakında)                           |
| Lua           | **SA-MP Injector Lua**     | (Yakında)                           |
| Ruby          | **SA-MP Injector Ruby**    | (Yakında)                           |
| Visual Basic  | **SA-MP Injector VB**      | (Yakında)                           |
| F#            | **SA-MP Injector F#**      | (Yakında)                           |
| Pascal/Delphi | **SA-MP Injector P/D**     | (Yakında)                           |
| PowerShell    | **SA-MP Injector PS**      | (Yakında)                           |
| D (Dlang)     | **SA-MP Injector D**       | (Yakında)                           |
| Nim           | **SA-MP Injector Nim**     | (Yakında)                           |
| Zig           | **SA-MP Injector Zig**     | (Yakında)                           |
| V (VLang)     | **SA-MP Injector V**       | (Yakında)                           |
| Crystal       | **SA-MP Injector Crystal** | (Yakında)                           |
| Perl          | **SA-MP Injector Perl**    | (Yakında)                           |
| Racket (Lisp) | **SA-MP Injector Racket**  | (Yakında)                           |
| Haskell       | **SA-MP Injector Haskell** | (Yakında)                           |
| OCaml         | **SA-MP Injector OCaml**   | (Yakında)                           |

> [!TIP]
> Her kütüphane için ayrıntılı dokümantasyon, ilgili **dizininde** bulunacaktır.

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