# SA-MP Injector C++

<div align="center">

![C++](https://img.shields.io/badge/C%2B%2B-14%2F17%2F20-00599C?style=for-the-badge&logo=cplusplus)
![Platform](https://img.shields.io/badge/Platform-Windows-blue?style=for-the-badge&logo=windows&logoColor=white)
![Architecture](https://img.shields.io/badge/Architecture-x86%20(32--bit)-lightgrey?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)

**SA-MP ve OMP istemcilerinin DLL enjeksiyonu yoluyla sunuculara bağlantısını başlatmak ve otomatikleştirmek için bir C++ kütüphanesi.**

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

- [SA-MP Injector C++](#sa-mp-injector-c)
  - [Diller](#diller)
  - [İçindekiler](#i̇çindekiler)
  - [Genel Bakış ve Amaç](#genel-bakış-ve-amaç)
  - [Tasarım İlkeleri](#tasarım-i̇lkeleri)
    - [Tamamen `Header-Only`](#tamamen-header-only)
    - [Güvenli Kaynak Yönetimi (RAII)](#güvenli-kaynak-yönetimi-raii)
    - [Sağlamlık ve Hata Kontrolü](#sağlamlık-ve-hata-kontrolü)
    - [C++ Standartları Esnekliği](#c-standartları-esnekliği)
  - [Gerekli Ortam](#gerekli-ortam)
    - [Geliştirme İçin](#geliştirme-i̇çin)
    - [Çalıştırma İçin](#çalıştırma-i̇çin)
  - [Hızlı Başlangıç](#hızlı-başlangıç)
    - [Projeye Entegrasyon](#projeye-entegrasyon)
    - [Basitleştirilmiş Kullanım Örneği](#basitleştirilmiş-kullanım-örneği)
  - [Kütüphane Yapısı](#kütüphane-yapısı)
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
  - [Detaylı Enjeksiyon Süreci](#detaylı-enjeksiyon-süreci)
    - [1. Başlatma İsteği](#1-başlatma-i̇steği)
    - [2. Ortam Hazırlığı](#2-ortam-hazırlığı)
    - [3. Bütünlük ve Parametrelerin Kontrolü](#3-bütünlük-ve-parametrelerin-kontrolü)
    - [4. Oyun İçin Argümanların Hazırlanması](#4-oyun-i̇çin-argümanların-hazırlanması)
    - [5. Oyun Sürecinin Başlatılması (Askıya Alınmış)](#5-oyun-sürecinin-başlatılması-askıya-alınmış)
    - [6. SA-MP Kütüphanesinin Enjeksiyonu (`samp.dll`)](#6-sa-mp-kütüphanesinin-enjeksiyonu-sampdll)
    - [7. OMP Kütüphanesinin Enjeksiyonu (`omp-client.dll`) - Koşullu](#7-omp-kütüphanesinin-enjeksiyonu-omp-clientdll---koşullu)
    - [8. Oyunun Etkinleştirilmesi](#8-oyunun-etkinleştirilmesi)
  - [Hata ve Arıza Teşhisi](#hata-ve-arıza-teşhisi)
    - [Giriş Doğrulama Hataları](#giriş-doğrulama-hataları)
      - [Geçersiz Kullanıcı Adı](#geçersiz-kullanıcı-adı)
      - [Geçersiz Bağlantı Portu](#geçersiz-bağlantı-portu)
      - [Eksik Temel Kaynaklar](#eksik-temel-kaynaklar)
    - [Süreç Yönetimi Hataları](#süreç-yönetimi-hataları)
      - [Oyun Sürecini Başlatmada Zorluk](#oyun-sürecini-başlatmada-zorluk)
    - [DLL Enjeksiyonu Sorunları](#dll-enjeksiyonu-sorunları)
      - [`LoadLibraryW` Bulunamıyor](#loadlibraryw-bulunamıyor)
      - [Uzak Bellek Ayırma Hatası](#uzak-bellek-ayırma-hatası)
      - [Sürece Veri Yazılamaması](#sürece-veri-yazılamaması)
      - [Enjeksiyon Thread'i Oluşturma Hatası](#enjeksiyon-threadi-oluşturma-hatası)
      - [Enjeksiyon Beklenirken Zaman Aşımı veya Hata](#enjeksiyon-beklenirken-zaman-aşımı-veya-hata)
      - [DLL Enjeksiyonunda Dahili Hata](#dll-enjeksiyonunda-dahili-hata)
    - [Oyunun Yürütülmesine Devam Etmede Zorluk](#oyunun-yürütülmesine-devam-etmede-zorluk)
  - [Lisans](#lisans)
    - [Kullanım Şartları ve Koşulları](#kullanım-şartları-ve-koşulları)
      - [1. Verilen İzinler](#1-verilen-i̇zinler)
      - [2. Zorunlu Koşullar](#2-zorunlu-koşullar)
      - [3. Telif Hakları](#3-telif-hakları)
      - [4. Garanti Reddi ve Sorumluluk Sınırlaması](#4-garanti-reddi-ve-sorumluluk-sınırlaması)

## Genel Bakış ve Amaç

**SA-MP Injector C++**, San Andreas Multiplayer (SA-MP) ve Open Multiplayer (OMP) sunucularına başlatma ve bağlanma sürecini otomatikleştirmek için tasarlanmış, kompakt ve kolay entegre edilebilir bir C++ kütüphanesidir. `gta_sa.exe`'yi doğrudan başlatmaktan farklı olarak, bu çözüm `samp.dll` veya `omp-client.dll` kütüphanelerini programlı bir şekilde Grand Theft Auto: San Andreas oyun sürecine kontrollü bir biçimde yükler.

Ana amacı, C++ geliştiricilerinin özel `launcher`lar, topluluk yönetim araçları veya önceden tanımlanmış bağlantı parametreleriyle (kullanıcı adı, IP adresi, port ve şifre gibi) GTA:SA'yı başlatması gereken yardımcı programlar oluşturmalarını sağlamak, böylece akıcı ve otomatikleştirilmiş bir kullanıcı deneyimi sunmaktır.

## Tasarım İlkeleri

**SA-MP Injector C++**'ın mimarisi, güvenlik, verimlilik ve kullanım kolaylığına odaklanan modern tasarım ilkelerine dayanmaktadır.

### Tamamen `Header-Only`

Bu kütüphane yalnızca başlık dosyaları (`.hpp`) aracılığıyla dağıtılır. Bu, ayrı kütüphaneleri derleme, `linker`ları yapılandırma veya ikili bağımlılıkları yönetme ihtiyacını ortadan kaldırarak C++ projelerine entegrasyonu büyük ölçüde basitleştirir.
- **Anında Entegrasyon:** İlgili `header`ları dahil etmeniz yeterlidir.
- **Derin Optimizasyon:** Derleyici, daha kompakt ve hızlı bir nihai kodla sonuçlanan agresif `inlining` ve `link-time` optimizasyonları yapabilir.

### Güvenli Kaynak Yönetimi (RAII)

Kütüphane, **RAII (Resource Acquisition Is Initialization)** standardını kapsamlı bir şekilde kullanır. Windows'un süreç ve `thread` `handle`ları gibi kritik sistem kaynakları, özel `deleter`lara sahip `std::unique_ptr` ile sarmalanır. Bu, yürütme akışından veya istisnaların meydana gelmesinden bağımsız olarak, kaynakların her zaman doğru şekilde serbest bırakılmasını sağlar, sızıntıları önler ve uygulamanın kararlılığını artırır.

### Sağlamlık ve Hata Kontrolü

Enjeksiyonun her kritik adımı, katı doğrulamalardan önce gelir ve Windows API hata kontrolleri ile takip edilir. Detaylı hata mesajları, mümkün olduğunda sistem açıklamaları (`GetLastError()`) ile birlikte diyalog kutuları aracılığıyla son kullanıcıya sunulur. Bu yaklaşım, tanımsız davranış olasılığını en aza indirir ve bir arıza durumunda net bir teşhis sunar.

### C++ Standartları Esnekliği

Kütüphane, C++14'ten C++20'ye kadar farklı C++ standartlarıyla uyumlu olacak şekilde oluşturulmuştur. Bu, mevcut olduğunda modern özellikleri (C++17+'dan `std::string_view`, `std::filesystem` ve `std::optional` gibi) kullanmaya izin veren, aynı zamanda C++14'teki eşdeğer yapılar için bir `fallback` sağlayan koşullu makrolar aracılığıyla başarılır. Bu yaklaşım, modernlikten ödün vermeden geniş uyumluluk sağlar.

## Gerekli Ortam

### Geliştirme İçin

- **C++ Derleyicisi:** **C++14 veya üstü** ile uyumlu.
   - Microsoft Visual C++ (Visual Studio 2015, 2017, 2019, 2022)
   - GCC (sürüm 5 veya daha yeni)
   - Clang (sürüm 3.6 veya daha yeni)
- **İşletim Sistemi:** **Windows**.
- **Windows SDK:** İşletim sistemi API'lerine erişim için gereklidir.
- **Derleme Mimarisi:** **x86 (32-bit)**. Bu, `gta_sa.exe` ve SA-MP/OMP DLL'lerinin yalnızca bu mimaride çalışması nedeniyle katı bir gerekliliktir.

### Çalıştırma İçin

- **İşletim Sistemi:** Derlenmiş ikili ile uyumlu herhangi bir modern **Windows** sürümü.
- **Grand Theft Auto: San Andreas (GTA:SA):** Oyunun geçerli bir kurulumu zorunludur.
- **SA-MP veya OMP İstemci DLL'leri:** `samp.dll` veya `omp-client.dll` dosyaları, istenen enjeksiyon türüne karşılık gelecek şekilde oyunun kök dizininde bulunmalıdır.

## Hızlı Başlangıç

Kütüphanenin `header-only` doğası, herhangi bir C++ projesine dahil edilmesini kolaylaştırır.

### Projeye Entegrasyon

1.  **Header'ları İndirin:** Kütüphanenin `.hpp` dosyalarını edinin (depoyu klonlayarak veya doğrudan indirerek).
2.  **Dosyaları Düzenleyin:** Projenizde kütüphane `header`ları için bir alt klasör oluşturmanız önerilir, örneğin, `Projem/libraries/samp-injector/`.
3.  **Mimarisi Tanımlayın:** Projenizi **x86 (32-bit)** mimarisi için derlenecek şekilde yapılandırın.

```cpp
// Dizin yapısı örneği
Projem/
├── src/
│   └── main.cpp
├── libraries/
│   └── samp-injector/
│       ├── constants.hpp
│       ├── error_utils.hpp
│       ├── injector.hpp // Dahil edilecek ana başlık
│       └── ... (diğer başlıklar)
└── built/ (çıkış dizininiz)
```

### Basitleştirilmiş Kullanım Örneği

Bir sunucuya bağlantıyı otomatikleştirmek için, sadece `Initialize_Game` fonksiyonunu çağırın ve ayrıntıları sağlayın.

```cpp
#include <iostream>
#include <string>
//
#include "samp-launcher/injector.hpp" // Ana başlığı dahil edin

int main() {
    // Oyun başlatma ve bağlantı için parametreler
    std::wstring inject_type = L"samp"; // Veya Open Multiplayer için L"omp"
    std::wstring game_folder = L"C:\\Games\\GTA San Andreas"; // GTA:SA klasörünün tam yolu
    std::wstring nickname = L"İsim";
    std::wstring ip = L"127.0.0.1";
    std::wstring port = L"7777";
    std::wstring password = L""; // Şifre yoksa boş bırakın

    // Oyunu başlatmak ve DLL'i enjekte etmek için ana çağrı
    Initialize_Game(inject_type, game_folder, nickname, ip, port, password);

    // Başarısızlık durumunda, bir Windows hata mesajı kutusu otomatik olarak görüntülenir.

    return 0;
}
```

## Kütüphane Yapısı

Kütüphane, her biri iyi tanımlanmış sorumluluklara sahip, organizasyonu, bakımı ve yeniden kullanılabilirliği kolaylaştıran birkaç başlık dosyasına dikkatlice modülerleştirilmiştir.

### 1. `constants.hpp`

Bu dosya, **SA-MP Injector C++**'ın davranışını ve birlikte çalışabilirliğini belirleyen tüm sabit ve değişmez değerlerin merkezi bir deposu olarak hizmet veren kütüphanenin **merkezi deposudur**. Mantıksal kategorilere göre organizasyonu, sadece kodun açıklığını ve okunabilirliğini artırmakla kalmaz, aynı zamanda bakımı kolaylaştırır ve kütüphane ekosistemi boyunca sıkı bir tutarlılık sağlar.

Her sabit, `CONSTEXPR_VAR` ile tanımlanır, bu da `inline constexpr` (C++17+ için) veya `static constexpr` (C++14 için) olarak genişler, bu değerlerin derleme zamanında değerlendirilmesini sağlar, performansı ve tür güvenliğini optimize eder.

Sabitlerin kategoriye göre düzenlenmesi, amaçlarının anlaşılmasını kolaylaştırır:

- **Oyunla İlgili Sabitler (`Game Related Constants`)**
   - `MIN_PORT`: Bir sunucuya bağlanmak için geçerli en düşük port numarasını tanımlayan bir `int` (değer: `1`).
   - `MAX_PORT`: Bir sunucuya bağlanmak için geçerli en yüksek port numarasını belirleyen bir `int` (değer: `65535`).
   - `MAX_NICKNAME_LENGTH`: Oyuncunun takma adı için izin verilen maksimum uzunluğu belirten bir `int` (değer: `23` karakter), SA-MP/OMP istemci özelliklerinin getirdiği bir sınırdır.

- **Temel Dosya Adları (`File Names`)**
   - `SAMP_DLL_NAME`: SA-MP istemcisinin ana kütüphane dosyasının adını içeren bir `const wchar_t*` (değer: `L"samp.dll"`). Klasik istemcinin enjeksiyonu için esastır.
   - `OMP_DLL_NAME`: Open Multiplayer istemci kütüphanesinin dosya adını içeren bir `const wchar_t*` (değer: `L"omp-client.dll"`). Özellikle OMP türü enjeksiyonlarda kullanılır.
   - `GAME_EXE_NAME`: Temel Grand Theft Auto: San Andreas oyununun çalıştırılabilir dosyasının adını saklayan bir `const wchar_t*` (değer: `L"gta_sa.exe"`). Enjeksiyonun ana hedefi.

- **Sistem API'leri ve Fonksiyonları (`System Libraries and Functions`)**
   - `KERNEL32_DLL`: Windows sistem kütüphanesinin adını tanımlayan bir `const wchar_t*` (değer: `L"kernel32.dll"`). Bu DLL, enjektörün kullandığı süreç ve bellek işleme fonksiyonlarını barındırdığı için hayati önem taşır. `wchar_t` kullanımı, `GetModuleHandleW` gibi geniş karakterleri işleyen API fonksiyonlarıyla uyumluluğu garanti eder.
   - `LOAD_LIBRARY_FUNC`: Bir DLL'i dinamik olarak yüklemek için fonksiyonun adını içeren bir `const char*` (değer: `"LoadLibraryW"`). Kütüphane öncelikle geniş karakterlerle çalışsa da, Windows API'sinin `GetProcAddress` fonksiyonu ANSI formatında (`char*`) bir fonksiyon adı gerektirir.

- **Komut Satırı Argümanları (`Command Line Arguments`)**
   - Bu sabitler, istemci bağlantısını yapılandırmak için `gta_sa.exe`'ye geçirilen argümanların öneklerini tanımlar. `CreateProcessW` ile uyumluluk için `Wide Character` (`const wchar_t*`) olarak sağlanırlar.
      - `CMD_ARG_CONFIG`: Genel ayarlar için argüman (değer: `L"-c"`).
      - `CMD_ARG_NICKNAME`: Oyuncu takma adı için argüman (değer: `L"-n"`).
      - `CMD_ARG_HOST`: Sunucu IP adresi için argüman (değer: `L"-h"`).
      - `CMD_ARG_PORT`: Sunucu portu için argüman (değer: `L"-p"`).
      - `CMD_ARG_PASSWORD`: Sunucu şifresi için argüman (değer: `L"-z"`). Yalnızca bir şifre sağlandığında kullanılır.

- **Enjeksiyon Türü Tanımlayıcıları (`Injection types as strings`)**
   - `INJECT_TYPE_SAMP`: SA-MP enjeksiyon türünün string temsilcisi için bir `const wchar_t*` (değer: `L"samp"`).
   - `INJECT_TYPE_OMP`: OMP enjeksiyon türünün string temsilcisi için bir `const wchar_t*` (değer: `L"omp"`).

- **Hata Mesajı Başlıkları (`Error message titles`)**
   - `ERROR_TITLE_SAMP`: SA-MP hatalarıyla ilgili hata diyalog kutuları için varsayılan başlığı tanımlayan bir `const wchar_t*` (değer: `L"SA-MP Injector Error - SPC"`).
   - `ERROR_TITLE_OMP`: OMP hatalarıyla ilgili hata diyalog kutuları için varsayılan başlığı tanımlayan bir `const wchar_t*` (değer: `L"OMP Injector Error - SPC"`).

- **Süreç Oluşturma Bayrakları (`Process creation`)**
   - `PROCESS_CREATION_FLAGS`: `CreateProcessW`'e geçirilen bayrakları kapsayan bir `DWORD`. Özellikle, oyun sürecini duraklatılmış bir durumda başlatan `CREATE_SUSPENDED` (`0x00000004`) ve yeni süreci ana sürecin konsolundan ayıran `DETACHED_PROCESS` (`0x00000008`) içerir.

- **Zaman Aşımları (`Timeouts`)**
   - `DLL_INJECTION_TIMEOUT_MS`: Kütüphanenin, DLL enjeksiyonundan sorumlu uzak `thread`in tamamlanmasını bekleyeceği maksimum süreyi (milisaniye cinsinden) belirten bir `DWORD` (değer: `10000ms` veya 10 saniye).

- **Bellek Ayırma Bayrakları (`Memory allocation`)**
   - Bu sabitler, `VirtualAllocEx` ve `VirtualProtect` gibi bellek işleme API çağrıları için kullanılır.
      - `MEM_COMMIT`: Sanal bellekte sayfaları ayırır ve onları "commitle" (fiziksel bellek ayırır) (değer: `0x1000`).
      - `MEM_RESERVE`: Yalnızca daha sonra kullanılmak üzere bir sanal adres alanı aralığını ayırır (değer: `0x2000`).
      - `MEM_RELEASE`: Bir sayfa bölgesini "decommit" eder ve serbest bırakır (değer: `0x8000`).
      - `MEMORY_ALLOCATION_TYPE`: Uzak süreçteki DLL yolu için başlangıç belleğini ayırmak için kullanılan `MEM_COMMIT` ve `MEM_RESERVE` kombinasyonu.
      - `MEMORY_PROTECTION`: Bellek koruma izinlerini tanımlayan bir `DWORD` (değer: `PAGE_READWRITE` veya Windows API'de `0x04`), ayrılan bellekte okuma ve yazmaya izin verir.

### 2. `types.hpp`

Bu kısa dosya, farklı enjeksiyon yöntemlerini tipleştirmek için bir `enum class` sunar. String sabitleri yerine numaralandırılmış bir türün kullanılması, kod güvenliğini artırır, yazım hatalarını önler ve okunabilirliği iyileştirir.

- **`Inject_Type`:** `SAMP` ve `OMP` olmak üzere iki üyeli bir `enum class`, enjekte edilecek istemci türlerini temsil eder.

```cpp
// types.hpp örneği
namespace Types {
    enum class Inject_Type {
        SAMP, // SA-MP istemcisi için enjeksiyonu belirtir
        OMP // Open Multiplayer istemcisi için enjeksiyonu belirtir
    };
}
```

### 3. `version.hpp`

Bir uyumluluk adaptörü olarak hareket eden bu başlık, derleyici tarafından kullanılan C++ standardını dinamik olarak algılar. Kütüphaneyi, mevcut olduğunda en gelişmiş C++ özelliklerini (örneğin `std::string_view` veya `std::filesystem`) kullanmaya yönlendiren koşullu makrolar (`SAMP_INJECTOR_CXX_14`, `SAMP_INJECTOR_CXX_MODERN`) tanımlarken, C++14 ortamlarında tam işlevsellik sağlar.

- **`SAMP_INJECTOR_CXX_14`:** C++ standardı C++14 ise tanımlanır.
- **`SAMP_INJECTOR_CXX_MODERN`:** C++17 veya üstü için tanımlanır, daha yeni dil özelliklerini etkinleştirir.
- **`SAMP_INJECTOR_NODISCARD`:** `[[nodiscard]]` özniteliğini destekleyen C++ sürümlerine uyarlar, dönüş değerlerinin kontrol edilmesini teşvik eder.

```cpp
// version.hpp'den ilgili bölüm örneği
#if (defined(_MSC_VER) && _MSVC_LANG >= 201703L) || __cplusplus >= 201703L
    #define SAMP_INJECTOR_CXX_MODERN // C++17+ modern özelliklerini etkinleştirir
#endif

#if defined(SAMP_INJECTOR_CXX_MODERN)
    #define SAMP_INJECTOR_NODISCARD [[nodiscard]] // C++17'nin nodiscard özniteliğini kullanır
#elif defined(SAMP_INJECTOR_CXX_14)
    #define SAMP_INJECTOR_NODISCARD // C++14 için öznitelik devre dışı bırakılır
#endif
```

### 4. `error_utils.hpp`

Bu yardımcı program, hata geri bildiriminin yönetimine ve sunumuna adanmıştır. Sistem hata mesajlarını kurtarmak için Windows mekanizmalarını soyutlar ve kullanıcıyı sorunlar hakkında bilgilendirmek için birleşik bir arayüz sunar.

- **`Get_System_Error_Message`:** Bir Windows hata kodunu (`GetLastError()`) okunabilir bir `std::wstring`'e çevirir, bu da doğru teşhis için çok önemlidir.
- **`Show_Error`:** SA-MP veya OMP için özel bir başlıkla sağlanan hata mesajını içeren bir diyalog kutusu (`MessageBoxW`) sunar, kullanıcıyla net bir iletişim sağlar.

```cpp
// error_utils.hpp'den ilgili bölüm örneği
namespace Error_Utils {
    SAMP_INJECTOR_NODISCARD
    inline std::wstring Get_System_Error_Message(DWORD error_code) {
        if (error_code == 0)
            return L"No error occurred.";
        
        // ... Sistem mesajını biçimlendirme mantığı ...
    }

    inline void Show_Error(std::wstring_view message, Types::Inject_Type inject_type) {
        const std::wstring title = (inject_type == Types::Inject_Type::SAMP) ? Constants::ERROR_TITLE_SAMP : Constants::ERROR_TITLE_OMP;
        MessageBoxW(nullptr, message.data(), title.c_str(), MB_OK | MB_ICONERROR);
    }
}
```

### 5. `validation.hpp`

Kütüphanenin sağlamlığının ön saflarında yer alan bu başlık, giriş verilerinin geçerliliğini ve gerekli dosyaların varlığını kontrol etmek için sıkı rutinler sağlar. Bu kontroller, sistemle herhangi bir alt düzey etkileşimden önce gerçekleştirilir, `runtime` risklerini azaltır ve proaktif geri bildirim sağlar.

- **`Validate_Port`:** Port dizesinin bir tamsayıyı temsil edip etmediğini ve yapılandırılmış aralıkta (`MIN_PORT` ile `MAX_PORT` arasında) olup olmadığını doğrular.
- **`Validate_Nickname`:** Takma adın boş olmadığını ve uzunluğunun `MAX_NICKNAME_LENGTH`'ı aşmadığını kontrol eder.
- **`Validate_Files`:** `gta_sa.exe`, `samp.dll` ve koşullu olarak OMP enjeksiyonu için `omp-client.dll`'nin fiziksel varlığını doğrular. Uygulama, `std::filesystem` (C++17+) veya `GetFileAttributesW` (C++14) 'e uyum sağlar.

```cpp
// validation.hpp'den ilgili bölüm örneği
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
        
        // ... Diğer dosya kontrolleri ...
        return true;
    }
}
```

### 6. `resource_handle.hpp`

Windows'un `HANDLE`'ları gibi işletim sistemi kaynaklarının yönetimi için zarif ve güvenli bir strateji uygular. RAII ilkesini kullanarak, ayrılan tüm kaynakların uygun şekilde serbest bırakılmasını sağlar, sızıntıları önler ve uygulamanın kararlılığını güçlendirir.

- **`Unique_Resource`:** `std::unique_ptr`'ı özel `deleter`larla çalışacak şekilde uyarlayan bir `alias template`, belirli bir serbest bırakma fonksiyonu gerektiren her türlü kaynağın yönetilmesine olanak tanır.
- **`Make_Unique_Handle`:** Windows `HANDLE`'ları için önceden yapılandırılmış bir `Unique_Resource` oluşturan ve döndüren kullanışlı bir `factory` fonksiyonu. İlişkili `deleter`, `Unique_Resource` kapsam dışına çıktığında otomatik olarak `CloseHandle`'ı çağırır, kaynağın anında boşaltılmasını sağlar.

```cpp
// resource_handle.hpp'den ilgili bölüm örneği
namespace Resource_Handle {
    // Sistem kaynaklarını yönetmek için özel bir std::unique_ptr.
    template<typename T, typename Deleter>
    using Unique_Resource = std::unique_ptr<std::remove_pointer_t<T>, Deleter>;

    // Bir HANDLE için CloseHandle çağıran bir deleter ile Unique_Resource oluşturur.
    template<typename T>
    inline auto Make_Unique_Handle(T handle) {
        return Unique_Resource<T, std::function<void(T)>>(handle, [](T h) {
            if (h && h != INVALID_HANDLE_VALUE) // Kapatmadan önce handle'ın geçerli olduğundan emin olur
                CloseHandle(h);
        });
    }
}
```

### 7. `privileges.hpp`

Bu bileşen, uygulamanın süreç güvenlik ortamını yapılandırmaktan sorumludur. Kütüphanenin Windows'un harici süreçlerinde DLL enjeksiyonu işlemleri gerçekleştirebilmesi için temel bir gereklilik olan hata ayıklama ayrıcalığını (`SE_DEBUG_NAME`) etkinleştirerek ayrıcalıkları yükseltme işlevselliğini içerir.

- **`Enable_Debug_Privilege`:** Bu fonksiyon, çalışan süreç için `SE_DEBUG_NAME` ayrıcalığını edinmeye ve etkinleştirmeye çalışır. Uygulamaya, bellek ayırma ve uzaktan `thread` oluşturma gibi diğer süreçleri işlemek için gerekli izinleri vermek için çok önemli bir başlangıç adımıdır. Başarılı olursa `true` döner.

```cpp
// privileges.hpp'den ilgili bölüm örneği
namespace Privileges {
    inline bool Enable_Debug_Privilege() {
        HANDLE token_handle;

        // Ayrıcalıkları ayarlamak için mevcut sürecin token'ını açmaya çalışır
        if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &token_handle))
            return false;

        auto handle_guard = Resource_Handle::Make_Unique_Handle(token_handle); // Handle'ın güvenli yönetimi

        TOKEN_PRIVILEGES tp;
        LUID luid;

        // SE_DEBUG_NAME ayrıcalığı için LUID değerini arar
        if (!LookupPrivilegeValue(nullptr, SE_DEBUG_NAME, &luid))
            return false;
        
        tp.PrivilegeCount = 1;
        tp.Privileges[0].Luid = luid;
        tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED; // Ayrıcalığı etkinleştirir

        // Sürecin ayrıcalıklarını ayarlar
        if (!AdjustTokenPrivileges(token_handle, FALSE, &tp, sizeof(TOKEN_PRIVILEGES), nullptr, nullptr))
            return false;

        return GetLastError() == ERROR_SUCCESS; // İşlem başarılıysa (bekleyen hata yoksa) true döner
    }
}
```

### 8. `process.hpp`

Bu, kütüphanenin en kritik bileşenlerinden biridir ve Windows süreçleriyle etkileşim için alt düzey uygulamayı içerir. Oyun sürecini oluşturma, bellek ayırma, veri yazma ve uzaktan `thread` oluşturma yoluyla DLL enjeksiyon tekniği gibi karmaşık işlemleri kapsar.

- **`Process_Info` struct:** Oyunun süreç `HANDLE`'ı (`process_handle`) ve ana `thread`'in `HANDLE`'ı (`thread_handle`) için `Unique_Resource`'ları saklayan bir iç yapı. Enjeksiyon tamamlandığında oyunun ana `thread`ini yeniden etkinleştirmek için bir `Resume()` metodu içerir.
- **`Injection_Status` enum class:** DLL enjeksiyon işlemi için olası sonuçların ayrıntılı bir listesini tanımlar, arızaların hassas bir şekilde teşhis edilmesini sağlar.
- **`Create_Game_Process`:**
   - `gta_sa.exe` çalıştırılabilir dosyasını başlatmak için Windows API'sinin `CreateProcessW` fonksiyonunu kullanır.
   - Sürecin `CREATE_SUSPENDED` bayrağıyla (`Constants::PROCESS_CREATION_FLAGS` içinde bulunur) oluşturulması esastır. Bu, oyunun oluşturulduktan hemen sonra, herhangi bir kod çalıştırılmadan önce duraklatılmasını sağlar, böylece DLL enjeksiyonunun güvenli bir durumda gerçekleşmesine olanak tanır.
   - Süreç ve `thread`'in kapsüllenmiş `handle`'larını içeren bir `std::optional<Process_Info>` (C++17+ için) veya bir `std::unique_ptr<Process_Info>` (C++14 için) döndürür.
- **`Inject_DLL`:**
   - `CreateRemoteThread` aracılığıyla standart DLL enjeksiyon tekniğini uygular:
      1.  **Adres Alımı:** `constants.hpp`'deki sabitleri kullanarak, Windows'un dinamik kütüphaneleri yüklemek için kullandığı `LoadLibraryW` fonksiyonunun (`kernel32.dll`'den) adresini bulur.
      2.  **Bellek Ayırma:** `VirtualAllocEx`, oyun süreci (`gta_sa.exe`) içinde sanal bir bellek bloğu ayırmak için kullanılır. Bu blok, enjekte edilecek DLL'nin tam yolunu içerecek şekilde boyutlandırılır.
      3.  **Yolun Yazılması:** DLL'nin yolu (örneğin, `L"C:\\yol\\için\\samp.dll"`) daha sonra `WriteProcessMemory` aracılığıyla oyun sürecinde uzaktan ayrılan belleğe kopyalanır.
      4.  **Uzak Thread Oluşturma:** `CreateRemoteThread`, oyun sürecinin bağlamında yeni bir `thread` başlatır. Bu `thread`'in giriş noktası `LoadLibraryW`'nin adresidir ve geçirilen argüman, az önce yazdığımız DLL yolu dizesinin adresidir.
      5.  **İzleme:** Uzak `thread`'in yürütülmesi, tamamlanana veya `DLL_INJECTION_TIMEOUT_MS`'e ulaşılana kadar `WaitForSingleObject` tarafından izlenir.
      6.  **Başarı Kontrolü:** `GetExitCodeThread`, uzak `thread`'in dönüş değerini kontrol etmek için kullanılır. Eğer `LoadLibraryW` başarılı olduysa, yüklenen DLL'nin taban adresini (sıfırdan farklı bir değer) döndürür.
      7.  **Temizlik:** Uzak süreçte ayrılan bellek `VirtualFreeEx` tarafından serbest bırakılır.
   - Enjeksiyonun başarısını veya belirli bir arıza türünü belirten bir `Injection_Status` döndürür.

```cpp
// process.hpp'den ilgili bölüm örneği
class Process {
public:
    struct Process_Info {
        Resource_Handle::Unique_Resource<HANDLE, std::function<void(HANDLE)>> process_handle; // RAII yönetimi ile süreç handle'ı
        Resource_Handle::Unique_Resource<HANDLE, std::function<void(HANDLE)>> thread_handle; // RAII yönetimi ile thread handle'ı

        bool Resume() { // Oyunun ana thread'inin yürütülmesine devam eder
            return thread_handle && ResumeThread(thread_handle.get()) != static_cast<DWORD>(-1);
        }
    };
    
    enum class Injection_Status { // DLL enjeksiyonu için ayrıntılı durum kodları
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

    // Oyun sürecini askıya alınmış durumda oluşturur
    std::optional<Process_Info> Create_Game_Process(const std::wstring& game_path, std::wstring& command_args, const std::wstring& working_dir) {
        // ... CREATE_SUSPENDED ile CreateProcessW mantığı ...
    }
    
    SAMP_INJECTOR_NODISCARD // Dönüş değerinin kullanılmasını sağlar
    Injection_Status Inject_DLL(HANDLE process, const std::wstring& DLL_path) {
        static const LPVOID load_library_addr = reinterpret_cast<LPVOID>(GetProcAddress(GetModuleHandleW(Constants::KERNEL32_DLL), Constants::LOAD_LIBRARY_FUNC));

        if (!load_library_addr)
            return Injection_Status::LOADLIBRARY_ADDRESS_FAILED;

        LPVOID remote_memory = VirtualAllocEx(process, nullptr, (DLL_path.length() + 1) * sizeof(wchar_t), Constants::MEMORY_ALLOCATION_TYPE, Constants::MEMORY_PROTECTION);

        if (!remote_memory)
            return Injection_Status::ALLOCATION_FAILED;

        auto memory_guard = Resource_Handle::Unique_Resource<LPVOID, std::function<void(LPVOID)>>(remote_memory, [process](LPVOID ptr) {
            if (ptr)
                VirtualFreeEx(process, ptr, 0, MEM_RELEASE); // Uzak süreçteki belleği serbest bırakır
        });

        if (!WriteProcessMemory(process, remote_memory, DLL_path.c_str(), (DLL_path.length() + 1) * sizeof(wchar_t), nullptr))
            return Injection_Status::WRITE_FAILED;

        HANDLE remote_thread = CreateRemoteThread(process, nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(load_library_addr), remote_memory, 0, nullptr);

        if (!remote_thread)
            return Injection_Status::THREAD_CREATION_FAILED;

        auto thread_guard = Resource_Handle::Make_Unique_Handle(remote_thread); // Uzak thread handle'ının güvenli yönetimi

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

Bu başlık, kütüphanenin komuta merkezi olarak hizmet veren `Injector_Core` sınıfını tanımlar. Giriş doğrulama, ayrıcalık yönetimi ve süreç işleme modüllerini birbirine bağlayarak enjeksiyon işlemlerinin mantıksal sırasını düzenler. Enjeksiyonun tam iş akışı burada tanımlanır.

- **`Injector_Core`:** Bu sınıfın yapıcısı, `Privileges::Enable_Debug_Privilege()`'in çağrıldığı noktadır. Bu, uygulamanın sürecinin, başka herhangi bir kritik mantık yürütülmeden önce DLL enjeksiyon işlemleri gerçekleştirmek için gerekli ayrıcalıklara sahip olmasını sağlar.
- **`Initialize_Game`:**
   1.  **Kapsamlı Doğrulama:** Tüm parametrelerin ve temel kaynakların düzenli olduğundan emin olmak için doğrulama fonksiyonlarını (`Validation::Validate_Port`, `Validation::Validate_Nickname`, `Validation::Validate_Files`) çağırarak başlar. Herhangi bir doğrulama başarısız olursa, bir hata hemen bildirilir.
   2.  **Argümanların Hazırlanması:** Sağlanan takma ad, IP, port ve şifreyi içeren `gta_sa.exe`'ye geçirilecek tam komut satırını (`std::wstring`) oluşturur.
   3.  **Askıya Alınmış Süreç Oluşturma:** `gta_sa.exe`'yi askıya alınmış bir durumda başlatmak için `Process::Create_Game_Process`'i çağırır, süreç ve ana `thread`'in `handle`'larını alır.
   4.  **`samp.dll` Enjeksiyonu:** `samp.dll`'yi oyun sürecine enjekte etmek için `Inject_DLL_With_Status_Check`'i çağırır. Bu sarmalayıcı fonksiyon aynı zamanda döndürülen `Injection_Status`'ı yorumlamaktan ve bilgilendirici hata mesajları göstermekten sorumludur.
   5.  **`omp-client.dll` Koşullu Enjeksiyonu:** `inject_type` `Types::Inject_Type::OMP` ise, `omp-client.dll` de `samp.dll` ile aynı şekilde enjekte edilir.
   6.  **Oyunun Devam Ettirilmesi:** Tüm enjeksiyonlar başarılı olduktan sonra, oyunun ana `thread`'inin yürütülmesine devam etmesine izin vermek için `process_info.Resume()` çağrılır.
   7.  **Döngüde Hata İşleme:** Bu kritik adımlardan herhangi birinde meydana gelen herhangi bir arıza, `Error_Utils::Show_Error`'a bir çağrı ile sonuçlanır, kullanıcıya net geri bildirim sağlar ve sürecin doğru şekilde sonlandırılmasını garanti eder (`handle`'lar `Unique_Resource`'lar tarafından otomatik olarak serbest bırakılır).
- **`Build_Command_Args`:** Boşluk içeren parametreler için gerektiğinde tırnak işaretleri ekleyerek komut satırı argümanlarını düzenleyen ve birleştiren bir yardımcı fonksiyon.
- **`Inject_DLL_With_Status_Check`:** `Process::Inject_DLL` için bir sarmalayıcı görevi gören özel bir fonksiyon. Farklı `Injection_Status`'ları anlaşılır hata mesajlarına eşler, hata işlemeyi ve kullanıcıyla iletişimi kolaylaştırır.

```cpp
// injector_core.hpp'den ilgili bölüm örneği
namespace Injector {
    class Injector_Core {
    public:
        Injector_Core() { // Yapıcı, hata ayıklama ayrıcalığını etkinleştirir
            Privileges::Enable_Debug_Privilege();
        }

        bool Initialize_Game(Types::Inject_Type inject_type, std::wstring_view folder, std::wstring_view nickname, std::wstring_view ip, std::wstring_view port, std::wstring_view password) {
            std::wstring error_message;

            // Giriş doğrulamaları dizisi
            if (!Validation::Validate_Port(port, error_message))
                return (Error_Utils::Show_Error(error_message, inject_type), false);
            // ... diğer doğrulamalar ...

            // Komut satırı argümanlarını oluşturur
            std::wstring args = Build_Command_Args({
                Command_Arg{Constants::CMD_ARG_NICKNAME, std::wstring(nickname)},
                // ... diğer argümanlar ...
            });

            Process process_core;
            // Oyun sürecini askıya alınmış durumda oluşturur
            auto process_info_opt = process_core.Create_Game_Process(game_path, args, std::wstring(folder));

            if (!process_info_opt)
                return false;

            auto& process_info = *process_info_opt;

            // samp.dll'i ve koşullu olarak omp-client.dll'i enjekte eder
            if (!Inject_DLL_With_Status_Check(process_core, process_info.process_handle.get(), Constants::SAMP_DLL_NAME, samp_DLL_path.wstring(), inject_type))
                return false;
            
            if (inject_type == Types::Inject_Type::OMP) {
                if (!Inject_DLL_With_Status_Check(process_core, process_info.process_handle.get(), Constants::OMP_DLL_NAME, omp_DLL_path.wstring(), inject_type))
                    return false;
            }
            
            // Oyunun ana thread'ini devam ettirir
            if (!process_info.Resume())
                return (Error_Utils::Show_Error(L"Failed to resume the game process thread: " + Error_Utils::Get_System_Error_Message(GetLastError()), inject_type), false);

            return true;
        }
    };
}
```

### 10. `injector.hpp`

Bu başlık, kütüphanenin ana cephesi (`Facade`) olarak işlev görür ve enjeksiyon işlevselliğini kullanmak isteyen herhangi bir uygulama için basitleştirilmiş bir giriş noktası sunar. `Injector_Core`'un iç karmaşıklığını tek ve kullanışlı bir fonksiyonda soyutlar.

- **`Initialize_Game`:**
   - Bu statik fonksiyon, kütüphanenin genel arayüzüdür.
   - Öncelikle, `inject_type_str`'ı doğrular (`L"samp"` veya `L"omp"` olup olmadığını) ve `enum class Types::Inject_Type`'a dönüştürür. Geçersiz bir dize durumunda, bir hata görüntüler ve sonlanır.
   - Ardından, `Injector::Injector_Core`'un bir örneğini oluşturur.
   - Son olarak, tüm doğrulama, süreç oluşturma ve DLL enjeksiyon sürecinin düzenlendiği `Injector_Core::Initialize_Game`'e ana mantığın yürütülmesini devreder.

```cpp
// injector.hpp'den ilgili bölüm örneği
// Oyunu başlatmak için genel arayüz
#if defined(SAMP_INJECTOR_CXX_MODERN)
inline bool Initialize_Game(std::wstring_view inject_type, std::wstring_view folder, std::wstring_view nickname, std::wstring_view ip, std::wstring_view port, std::wstring_view password) {
#elif defined(SAMP_INJECTOR_CXX_14)
inline bool Initialize_Game(const std::wstring& inject_type, const std::wstring& folder, const std::wstring& nickname, const std::wstring& ip, const std::wstring& port, const std::wstring& password) {
#endif
    Types::Inject_Type type;

    // Enjeksiyon türü dizesini ilgili enum'a dönüştürür
    if (inject_type == Constants::INJECT_TYPE_SAMP)
        type = Types::Inject_Type::SAMP;
    else if (inject_type == Constants::INJECT_TYPE_OMP)
        type = Types::Inject_Type::OMP;
    else
        // Enjeksiyon türü geçersizse hata gösterir
        return (Error_Utils::Show_Error(L"Geçersiz enjeksiyon modu. 'samp' veya 'omp' kullanın.", Types::Inject_Type::SAMP), false);

    Injector::Injector_Core injector; // Enjektör çekirdeğinin örneğini oluşturur

    // Ana mantığı Injector_Core'a devreder
    return injector.Initialize_Game(type, folder, nickname, ip, port, password);
}
```

## Detaylı Enjeksiyon Süreci

Bu kütüphanenin temel işlevselliği, SA-MP veya OMP istemci DLL'lerini GTA:SA sürecine enjekte etmek için hassas bir işlem sırasını düzenlemektir. Bu döngü, kararlılık ve uyumluluk sağlamak için dikkatlice planlanmıştır.

### 1. Başlatma İsteği

Süreç, kütüphaneyi kullanan uygulama için ana temas noktası olarak işlev gören genel `Initialize_Game` (`injector.hpp`) fonksiyonuna yapılan çağrı ile başlar. Bu fonksiyon, istenen enjeksiyon türü (SA-MP veya OMP), oyun dizini ve sunucu bağlantı verileri (takma ad, IP, port, şifre) gibi tüm önemli parametreleri alır.

### 2. Ortam Hazırlığı

Çağrıldığında, `Initialize_Game` fonksiyonu bir `Injector::Injector_Core` örneği oluşturur. Bu sınıfın yapıcısında (`injector_core.hpp`), ortam yapılandırmasının ilk ve temel adımı yürütülür: ayrıcalıkların yükseltilmesi.

> [!NOTE]
> `Privileges::Enable_Debug_Privilege()`: Bu çağrı (`privileges.hpp`), uygulama sürecine `SE_DEBUG_NAME` ayrıcalığını verir. Bu ayrıcalık hayati önem taşır, çünkü uygulamanın Windows'un diğer süreçlerinde bellek okuma ve yazma, uzaktan `thread` oluşturma gibi alt düzey işlemler yapmasına olanak tanır - bu eylemler DLL enjeksiyon tekniği için temeldir.

### 3. Bütünlük ve Parametrelerin Kontrolü

Ayrıcalıklar ayarlandıktan sonra, `Injector_Core::Initialize_Game` metodu bir dizi sıkı doğrulama ile devam eder. Bu, sonraki adımlarda meydana gelebilecek arıza olasılığını en aza indiren ve kullanıcıya anında geri bildirim sağlayan önleyici bir aşamadır.

- **Port Doğrulaması:** `Validation::Validate_Port`, bağlantı port numarasının doğru biçimlendirilip biçimlendirilmediğini ve `1` ile `65535` aralığında olup olmadığını kontrol eder (`constants.hpp`).
- **Takma Ad Doğrulaması:** `Validation::Validate_Nickname`, oyuncu takma adının boş olmadığını ve `23` karakter sınırını aşmadığını garanti eder.
- **Temel Dosyaların Kontrolü:** `Validation::Validate_Files`, oyun dizinini `gta_sa.exe`, `samp.dll` ve enjeksiyon OMP türündeyse `omp-client.dll`'nin varlığını doğrulamak için denetler.

> [!WARNING]
> Bu aşamadaki herhangi bir arıza, ayrıntılı bir hata mesajı içeren bir `MessageBox`'ın (`error_utils.hpp`) anında görüntülenmesine ve enjeksiyon sürecinin kesilmesine neden olur. Bu, geçersiz bir yapılandırmayla devam etme girişimlerini önler.

### 4. Oyun İçin Argümanların Hazırlanması

Başarılı doğrulamadan sonra, `Injector_Core::Build_Command_Args` fonksiyonu, `gta_sa.exe`'ye geçirilecek biçimlendirilmiş komut satırını oluşturmaktan sorumludur. Bu komut satırı, SA-MP/OMP istemcisinin bir sunucuya otomatik olarak bağlanması için gereken tüm parametreleri içerir, örneğin `-n "takma ad" -h "IP" -p "Port" -z "Şifre"`.

### 5. Oyun Sürecinin Başlatılması (Askıya Alınmış)

Daha sonra `Process` (`process.hpp`) bileşeni, GTA:SA çalıştırılabilir dosyasını başlatmakla görevlendirilir.

> [!IMPORTANT]
> `Process::Create_Game_Process` fonksiyonu, Windows'un `CreateProcessW` API'sini çağırırken `CREATE_SUSPENDED` (`constants.hpp`) bayrağını kullanır. Bu, kritik bir tasarım önlemidir: oyun belleğe yüklenir ve ana `thread`'i oluşturulur, ancak yürütülmesi **duraklatılır**. Bu, oyunun kendi savunmalarını veya iç mantığını başlatmasından önce, DLL'lerin enjeksiyonu için ideal olan kontrollü ve kararlı bir ortam yaratır. Süreç ve `thread` `handle`'ları alınır ve `Resource_Handle::Unique_Resource` aracılığıyla güvenli bir şekilde yönetilir.

### 6. SA-MP Kütüphanesinin Enjeksiyonu (`samp.dll`)

Oyun süreci askıya alınmış durumdayken, `samp.dll` enjeksiyonu güvenli bir şekilde gerçekleştirilebilir. `Injector_Core::Inject_DLL_With_Status_Check` metodu bu görevi, `remote thread injection` tekniğinin aşağıdaki adımlarını yürüten `Process::Inject_DLL`'e devreder:

1.  **`LoadLibraryW` Fonksiyonunun Yerini Bulma:** `LoadLibraryW` fonksiyonunun adresi belirlenir. Bu işlem, `kernel32.dll` için bir `handle` almak ve ardından dinamik kütüphane yükleme fonksiyonunun adresini bulmak için `Constants::KERNEL32_DLL` ve `Constants::LOAD_LIBRARY_FUNC` sabitlerini kullanır.
2.  **Uzak Bellek Ayırma:** `VirtualAllocEx`, askıya alınmış olan `gta_sa.exe` sürecinin sanal adres alanında bir bellek bloğu ayırmak için kullanılır. Bu bloğun boyutu, `samp.dll`'nin tam yolunu saklamak için yeterlidir.
3.  **DLL Yolunun Yazılması:** `samp.dll` dosyasının tam yolu, `WriteProcessMemory` tarafından bu yeni ayrılan uzak belleğe yazılır.
4.  **Uzak Thread Oluşturma:** `CreateRemoteThread`, `gta_sa.exe` süreci içinde yeni bir `thread` oluşturmak için çağrılır. Bu yeni `thread`'in giriş noktası `LoadLibraryW`'nin adresidir ve aldığı argüman, az önce yazdığımız DLL yoluna işaret eden bir işaretçidir.
5.  **Enjeksiyonun İzlenmesi:** Uzak `thread`'in yürütülmesi, `Constants::DLL_INJECTION_TIMEOUT_MS` tarafından belirlenen bir süre boyunca `WaitForSingleObject` tarafından izlenir.
6.  **Sonucun Kontrol Edilmesi:** Uzak `thread`'in çıkış kodu `GetExitCodeThread` aracılığıyla alınır. Sıfırdan farklı bir dönüş değeri, `LoadLibraryW`'nin `samp.dll`'yi başarıyla yüklediğini gösterir.

> [!WARNING]
> `samp.dll` enjeksiyonu sırasında herhangi bir arıza durumunda, belirli bir hata mesajı (`error_utils.hpp`) görüntülenir, enjeksiyon süreci iptal edilir ve kaynaklar serbest bırakılır.

### 7. OMP Kütüphanesinin Enjeksiyonu (`omp-client.dll`) - Koşullu

Belirtilen enjeksiyon türü `OMP` ise, 6. noktada ayrıntıları verilen adımlar `omp-client.dll` için tekrarlanır.

> [!TIP]
> `omp-client.dll` enjeksiyonu her zaman `samp.dll`'nin başarılı enjeksiyonundan sonra gerçekleşir. Bunun nedeni, Open Multiplayer istemcisinin `samp.dll` tarafından sağlanan altyapıya dayanmasıdır.

### 8. Oyunun Etkinleştirilmesi

Son olarak, tüm enjeksiyonlar başarıyla tamamlandıysa, `process_info.Resume()` metodu çağrılır. Bu çağrı, `gta_sa.exe`'nin ana `thread`'inde `ResumeThread`'i çalıştırır. Bu noktada, oyun etkinleştirilir ve normal yürütülmesine başlar, ancak SA-MP/OMP DLL'leri belleğine zaten yüklenmiş ve bağlantı parametreleri yapılandırılmış durumdadır, bu da sunucuya otomatik bir bağlantı sağlar.

> [!WARNING]
> Oyun `thread`'inin devam ettirilmesi başarısız olursa, kullanıcıya son bir hata mesajı sunulur.

## Hata ve Arıza Teşhisi

Kütüphane, başlatma ve enjeksiyon süreci sırasında ortaya çıkabilecek herhangi bir sorunu net bir şekilde bildirmek için titizlikle tasarlanmıştır. Herhangi bir arıza noktasında, kullanıcıya ayrıntılı bir açıklama içeren bir `MessageBox` sunulur, bu genellikle işletim sisteminden gelen hata mesajlarıyla tamamlanır.

### Giriş Doğrulama Hataları

Bu hatalar, sistemle herhangi bir alt düzey etkileşimden önce, ilk aşamada (`validation.hpp`) tespit edilir ve kullanıcı tarafından sağlanan verilerle veya ortam yapılandırmasıyla ilgili sorunları gösterir.

#### Geçersiz Kullanıcı Adı

- **Hata Mesajı (Örnek 1):** `"Nickname cannot be empty. Please provide a valid nickname."`
- **Hata Mesajı (Örnek 2):** `"Nickname length exceeds the maximum allowed of 23 characters. Please use a shorter nickname."`
- **Neden:** Sağlanan kullanıcı adı (`nickname`) boş veya SA-MP/OMP istemcilerinin izin verdiği maksimum 23 karakter sınırını aşıyor.
- **Çözüm:** Kullanıcı, uzunluk kriterlerine uyan geçerli bir kullanıcı adı girmelidir.

#### Geçersiz Bağlantı Portu

- **Hata Mesajı (Örnek 1):** `"Invalid port format. The port must be a numeric value. Please provide a valid integer for the port."`
- **Hata Mesajı (Örnek 2):** `"The specified port number (70000) is outside the valid range of 1 to 65535. Please provide a valid port."`
- **Neden:** Port için sağlanan değer bir tamsayı değil veya geçerli aralığın (1 ila 65535) dışında.
- **Çözüm:** Kullanıcının geçerli ve belirtilen aralıkta bir port numarası sağlaması gerekir.

#### Eksik Temel Kaynaklar

- **Hata Mesajı (Örnek 1):** `"Game executable not found. Please ensure 'gta_sa.exe' exists at the specified path: C:\Games\GTA San Andreas\gta_sa.exe"`
- **Hata Mesajı (Örnek 2):** `"SA-MP library not found. Please ensure 'samp.dll' exists at the specified path: C:\Games\GTA San Andreas\samp.dll"`
- **Hata Mesajı (Örnek 3, OMP için):** `"OMP library not found. Please ensure 'omp-client.dll' exists at the specified path for OMP injection: C:\Games\GTA San Andreas\omp-client.dll"`
- **Neden:** Belirtilen oyun dizininde bir veya daha fazla önemli dosya (`gta_sa.exe`, `samp.dll`, `omp-client.dll`) bulunamadı.
- **Çözüm:** Oyun klasörünün yolunu kontrol edin ve gerekli tüm dosyaların mevcut ve erişilebilir olduğundan emin olun.

### Süreç Yönetimi Hataları

Bu hatalar, kütüphane oyunun çalıştırılabilir dosyasını (`gta_sa.exe`) başlatmaya çalıştığında meydana gelir.

#### Oyun Sürecini Başlatmada Zorluk

- **Hata Mesajı (Örnek):** `"Failed to create game process. Ensure 'gta_sa.exe' is not running and you have sufficient permissions to execute the file. System Error: Access is denied."`
- **Neden:**
   - **Çalıştırılabilir Dosya Kullanımda:** `gta_sa.exe` zaten çalışıyor olabilir veya işletim sisteminin yeni bir örnek oluşturmasını engelleyen bir kilit olabilir.
   - **Yetersiz İzinler:** Uygulamanın `gta_sa.exe`'yi başlatmak veya dosyaya erişmek için uygun izinleri olmayabilir.
   - **Bozuk Çalıştırılabilir Dosya:** Temel doğrulama dosyanın varlığını kontrol etse de, bozuk veya erişilemez olabilir.
- **Çözüm:** Hiçbir `gta_sa.exe` örneğinin aktif olmadığından emin olun. Uygulamanızı yönetici olarak çalıştırmayı deneyin. `gta_sa.exe` dosyasının bütünlüğünü kontrol edin.

### DLL Enjeksiyonu Sorunları

Bunlar, oyunun askıya alınmış sürecine `samp.dll` veya `omp-client.dll` enjekte etme girişimi sırasında meydana gelen en kritik ve ayrıntılı hatalardır. Hata mesajları genellikle `"Failed to inject <DLL_NAME>:\n"` ile başlar ve ardından belirli bir açıklama ve bir sistem hata kodu gelir.

#### `LoadLibraryW` Bulunamıyor

- **Hata Mesajı (Bölüm):** `"Failed to find the address of LoadLibraryW in kernel32.dll."`
- **Neden:** DLL'lerin dinamik olarak yüklenmesi için temel bir Windows API'si olan `LoadLibraryW` fonksiyonu, `kernel32.dll`'de bulunamadı. Bu, işletim sisteminde olası bir bozulmaya veya son derece alışılmadık bir yürütme ortamına işaret eden son derece nadir bir alt düzey sorundur.
- **Çözüm:** Sistemin yeniden başlatılması sorunu çözebilir. Devam ederse, Windows kurulumunda daha ciddi bir soruna işaret edebilir.

#### Uzak Bellek Ayırma Hatası

- **Hata Mesajı (Bölüm):** `"Failed to allocate memory in the target process (VirtualAllocEx). System Error: Not enough storage is available to process this command."`
- **Neden:** Kütüphane, `gta_sa.exe` sürecinin sanal adres alanında bir bellek bloğu ayıramadı.
   - **İzinler:** Uygulamanızın başka bir sürecin bellek alanını değiştirme izni olmayabilir.
   - **Süreç Koruması:** İşletim sistemi güvenlik mekanizmaları veya anti-cheat yazılımları, harici süreçlerde bellek ayrılmasını engelliyor olabilir.
- **Çözüm:** Uygulamanızı yönetici olarak çalıştırın. Güvenlik programlarının (antivirüs, anti-cheat) müdahale edip etmediğini kontrol edin ve mümkünse test etmek için geçici olarak devre dışı bırakın.

#### Sürece Veri Yazılamaması

- **Hata Mesajı (Bölüm):** `"Failed to write DLL path to process memory (WriteProcessMemory). System Error: Access is denied."`
- **Neden:** Oyun sürecinde bellek ayrıldı, ancak kütüphane DLL yolunu bu konuma yazamadı.
   - **İzinler/Koruma:** Bellek ayırma hatasına benzer şekilde, bu bir yazma izni sorunu veya aktif bir bellek koruması olabilir.
- **Çözüm:** Bellek ayırma hatası için geçerli olan aynı çözümler burada da geçerlidir.

#### Enjeksiyon Thread'i Oluşturma Hatası

- **Hata Mesajı (Bölüm):** `"Failed to create remote thread (CreateRemoteThread). System Error: The parameter is incorrect."`
- **Neden:** `CreateRemoteThread` API'si, `LoadLibraryW`'yi çağırmak için `gta_sa.exe` sürecinde yeni bir `thread` başlatamadı.
   - **Güvenlik:** Birçok anti-cheat sistemi ve işletim sistemi koruması, yaygın bir enjeksiyon tekniği olduğu için uzaktan `thread` oluşturulmasını izler ve engeller.
   - **Süreç Durumu:** Oyun süreci, `thread` oluşturulmasını engelleyen kararsız bir durumda olabilir.
- **Çözüm:** Herhangi bir anti-cheat veya antivirüs yazılımını geçici olarak devre dışı bırakın. Uygulamayı yönetici olarak çalıştırmayı deneyin.

#### Enjeksiyon Beklenirken Zaman Aşımı veya Hata

- **Hata Mesajı (Bölüm):** `"Timeout or error waiting for remote thread (WaitForSingleObject). System Error: The wait operation timed out."`
- **Neden:** Uzak `thread` (`LoadLibraryW`'yi çağıran), belirlenen zaman aşımı süresi içinde (10 saniye) yürütülmesini tamamlamadı.
   - **Donma:** `LoadLibraryW` donmuş, aşırı uzun sürmüş veya engellenmiş/durdurulmuş olabilir.
- **Çözüm:** Bu, DLL'nin yüklenmekte zorlandığını veya bir şeyin onu engellediğini gösterebilir. Sistem veya SA-MP/OMP'nin kendi günlüklerini (varsa) kontrol etmek daha fazla ipucu sunabilir.

#### DLL Enjeksiyonunda Dahili Hata

- **Hata Mesajı (Bölüm):** `"LoadLibraryW call failed in the target process. The DLL might be corrupt, missing dependencies, or blocked by security software."`
- **Neden:** Uzak `thread` tamamlandı, ancak `LoadLibraryW`'nin dönüş değeri `0` (veya `NULL`) oldu, bu da DLL'nin başarıyla yüklenmediğini gösterir.
   - **Bozuk/Eksik DLL:** DLL, ilk doğrulamadan sonra taşınmış, silinmiş veya bozulmuş olabilir.
   - **Eksik Bağımlılıklar:** `samp.dll` veya `omp-client.dll`, oyun dizininde veya sistemin `PATH`'inde bulunmayan bağımlılıklara (diğer DLL'ler) sahip olabilir.
   - **DLL Dahili Hatası:** DLL'nin kendisi, yüklenmesini engelleyen bir dahili hataya sahip olabilir.
- **Çözüm:** `samp.dll`/`omp-client.dll` dosyalarının bütünlüğünü kontrol edin. Tüm bağımlılıklarının mevcut olduğundan emin olun.

### Oyunun Yürütülmesine Devam Etmede Zorluk

Bu, enjeksiyon döngüsündeki son olası arıza noktasıdır.

- **Hata Mesajı (Örnek):** `"Failed to resume the game process thread: Invalid handle."`
- **Neden:** `ResumeThread` API'si, `gta_sa.exe`'nin ana `thread`'ini yeniden etkinleştiremedi.
   - **Geçersiz Handle:** `thread`'in `handle`'ı beklenmedik bir olay nedeniyle geçersiz kılınmış olabilir.
   - **İzin:** Uygulamanın `thread`'in durumunu değiştirme izni olmayabilir.
- **Çözüm:** Uygulamayı yönetici olarak çalıştırmayı deneyin. Sorun devam ederse, sistemde veya oyun sürecinde daha derin bir kararlılık sorununa işaret edebilir.

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