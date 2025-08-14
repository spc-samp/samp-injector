# SA-MP Injector C++

![License](https://img.shields.io/badge/License-MIT-yellow.svg?style=flat)
![C++17](https://img.shields.io/badge/C%2B%2B-17-blue.svg?style=flat&logo=cplusplus)
![Platform](https://img.shields.io/badge/Platform-Windows-0078D6.svg?style=flat&logo=windows)
[![SA-MP | OMP](https://img.shields.io/badge/Support-SA--MP%20%7C%20OMP-yellow)](https://github.com/spc-samp/samp-injector)
![Code Quality](https://img.shields.io/badge/Code%20Quality-High-brightgreen.svg?style=flat)

**SA-MP Injector C++**, basit bir **DLL enjeksiyon aracı** tanımını aşan bir araçtır. Bu, **Grand Theft Auto: San Andreas** (**GTA:SA**) oyununun programlı bir şekilde başlatılmasını ve özellikle **SA-MP (San Andreas Multiplayer)** ve **OMP (Open Multiplayer)** istemcileriyle birlikte çalışmasını sağlamak için titizlikle tasarlanmış bir **C++ kütüphanesidir**. Temel amacı, oyunun başlatılma sürecini basitleştirerek işletim sistemi süreçlerinin doğrudan manipülasyonu ve komut satırı argümanlarının geçirilmesiyle ilgili karmaşıklığı ortadan kaldırmaktır.

Maksimum esneklik ve kolay entegrasyon sağlamak amacıyla geliştirilen bu `header-only` kütüphane, karmaşık ön derlemelere olan ihtiyacı ortadan kaldırır ve geliştiricilerin kütüphaneyi doğrudan **C++ projelerine** entegre etmesine olanak tanır. Kütüphane, yalnızca çok oyunculu istemci DLL'lerinin (**samp.dll** veya **omp-client.dll**) temel **enjeksiyonunu** yönetmekle kalmaz, aynı zamanda bağlantı için gerekli tüm parametreleri (**kullanıcı adı**, **IP adresi**, **port** ve **şifre**) akıllıca yönetir ve **Windows API**'sinin doğal özelliklerini kullanarak yerel bir başlatma işlemini simüle eder.

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
  - [Temel Kavramlar ve Motivasyon](#temel-kavramlar-ve-motivasyon)
    - [Neden DLL Enjeksiyonu?](#neden-dll-enjeksiyonu)
    - [SA-MP ve OMP: Farklılıklar ve Benzerlikler](#sa-mp-ve-omp-farklılıklar-ve-benzerlikler)
  - [Kütüphanenin İç Mimarisi: Derinlemesine Bir İnceleme](#kütüphanenin-i̇ç-mimarisi-derinlemesine-bir-i̇nceleme)
    - [`constants.hpp`](#constantshpp)
    - [`types.hpp`](#typeshpp)
    - [`string_utils.hpp`](#string_utilshpp)
    - [`error_utils.hpp`](#error_utilshpp)
    - [`resource_handle.hpp`](#resource_handlehpp)
    - [`validation.hpp`](#validationhpp)
    - [`process.hpp`](#processhpp)
    - [`injector_core.hpp`](#injector_corehpp)
    - [`injector.hpp`](#injectorhpp)
  - [Kapsamlı Kullanım Örnekleri](#kapsamlı-kullanım-örnekleri)
    - [1. Geliştirme Ortamının Hazırlanması](#1-geliştirme-ortamının-hazırlanması)
    - [2. Temel Senaryo: Bir SA-MP Sunucusuna Bağlanma](#2-temel-senaryo-bir-sa-mp-sunucusuna-bağlanma)
    - [3. Gelişmiş Senaryo: Bir OMP Sunucusuna Bağlanma](#3-gelişmiş-senaryo-bir-omp-sunucusuna-bağlanma)
  - [Yaygın Hataların ve Mesajların Ele Alınması](#yaygın-hataların-ve-mesajların-ele-alınması)
    - [1. Geçersiz Enjeksiyon Türü](#1-geçersiz-enjeksiyon-türü)
    - [2. Geçersiz Sunucu Portu (Format veya Aralık)](#2-geçersiz-sunucu-portu-format-veya-aralık)
      - [2.1. Sayısal Olmayan Port Formatı](#21-sayısal-olmayan-port-formatı)
      - [2.2. Geçerli Aralık Dışında Port](#22-geçerli-aralık-dışında-port)
    - [3. Geçersiz Kullanıcı Adı (Boş veya Çok Uzun)](#3-geçersiz-kullanıcı-adı-boş-veya-çok-uzun)
      - [3.1. Boş Kullanıcı Adı](#31-boş-kullanıcı-adı)
      - [3.2. Çok Uzun Kullanıcı Adı](#32-çok-uzun-kullanıcı-adı)
    - [4. Oyun veya DLL Dosyaları Bulunamadı](#4-oyun-veya-dll-dosyaları-bulunamadı)
      - [4.1. Oyun Yürütülebilir Dosyası (`gta_sa.exe`) Bulunamadı](#41-oyun-yürütülebilir-dosyası-gta_saexe-bulunamadı)
      - [4.2. SA-MP Kütüphanesi (`samp.dll`) Bulunamadı](#42-sa-mp-kütüphanesi-sampdll-bulunamadı)
      - [4.3. OMP Kütüphanesi (`omp-client.dll`) Bulunamadı (yalnızca OMP enjeksiyonu için)](#43-omp-kütüphanesi-omp-clientdll-bulunamadı-yalnızca-omp-enjeksiyonu-için)
    - [5. Oyun Sürecinin Oluşturulmasında Hata](#5-oyun-sürecinin-oluşturulmasında-hata)
    - [6. Hedef Süreçte Bellek Ayırmada Hata](#6-hedef-süreçte-bellek-ayırmada-hata)
    - [7. İşlem Belleğine DLL Yolunun Yazılmasında Hata](#7-i̇şlem-belleğine-dll-yolunun-yazılmasında-hata)
    - [8. Temel Sistem Fonksiyonlarının Bulunmasında Hata](#8-temel-sistem-fonksiyonlarının-bulunmasında-hata)
      - [8.1. `kernel32.dll` Bulunamadı](#81-kernel32dll-bulunamadı)
      - [8.2. `LoadLibraryA` Bulunamadı](#82-loadlibrarya-bulunamadı)
    - [9. Enjeksiyon için Uzak Thread Oluşturmada Hata](#9-enjeksiyon-için-uzak-thread-oluşturmada-hata)
    - [10. Enjeksiyonun Tamamlanmasında Zaman Aşımı veya Hata](#10-enjeksiyonun-tamamlanmasında-zaman-aşımı-veya-hata)
    - [11. Oyun İşlemi Thread'inin Devam Ettirilmesinde Hata](#11-oyun-i̇şlemi-threadinin-devam-ettirilmesinde-hata)
  - [Lisans](#lisans)
    - [Kullanım Şartları ve Koşulları](#kullanım-şartları-ve-koşulları)
      - [1. Verilen İzinler](#1-verilen-i̇zinler)
      - [2. Zorunlu Koşullar](#2-zorunlu-koşullar)
      - [3. Telif Hakları](#3-telif-hakları)
      - [4. Garanti Reddi ve Sorumluluk Sınırlaması](#4-garanti-reddi-ve-sorumluluk-sınırlaması)

## Temel Kavramlar ve Motivasyon

### Neden DLL Enjeksiyonu?

> [!NOTE]
> **DLL (Dynamic Link Library) enjeksiyonu**, **Microsoft Windows** işletim sistemlerinde başka bir çalışan sürecin bellek alanına kod çalıştırmayı sağlayan bir yöntemdir. Hata ayıklama ve program izlemeden, uygulamaların davranışlarını değiştirerek işlevselliklerini genişletmeye kadar birçok meşru uygulamaya sahip güçlü bir tekniktir.

**GTA San Andreas** gibi orijinal olarak çok oyunculu işlevsellik için geliştirilmemiş oyunlar bağlamında, **DLL enjeksiyonu**, **SA-MP** ve **OMP** gibi çok oyunculu istemcilerin varlığının temelini oluşturur. Bu istemciler, `gta_sa.exe` sürecine enjekte edildiğinde kontrolü ele alan, oyunun işlevlerini kesen ve çok oyunculu sunucularla iletişim kuran **DLL'ler** olarak uygulanır.

Dış bir başlatıcıya veya oyunun yürütülebilir dosyasını doğrudan değiştirmeye bağımlı olmak yerine, **DLL enjeksiyonu**, özellikle belirli sunuculara önceden tanımlanmış yapılandırmalarla bağlanmayı otomatikleştirmek istenen ortamlarda daha esnek ve programlanabilir bir başlatma sağlar.

### SA-MP ve OMP: Farklılıklar ve Benzerlikler

**SA-MP** ve **OMP**, **GTA San Andreas** için iki ana çok oyunculu platformdur. Her ikisi de temel oyunu çok oyunculu bir çevrimiçi ortama dönüştüren modifikasyonlar olarak işlev görür.

- **SA-MP (San Andreas Multiplayer)**: Uzun yıllardır yaygın olarak kullanılan orijinal ve en köklü istemcidir. Çalışması için `samp.dll` gerekir.
- **OMP (Open Multiplayer)**: Açık kaynaklı bir proje olup genellikle **SA-MP**'nin daha modern bir alternatifi veya halefi olarak görülür; performans, kararlılık ve ek özellikler açısından iyileştirmeler sunar. `omp-client.dll` gerektirir.

Her ikisi de benzer şekilde çalışsa da (**GTA:SA** sürecine bir **DLL** enjekte ederek), **SA-MP Injector C++** kütüphanesi, her iki DLL'yi de desteklemek için özenle geliştirilmiştir ve dosya adlarındaki farklılıkları tanır. Bu, geliştiricinin bir yapılandırma parametresi aracılığıyla istenen çok oyunculu istemciyi seçmesine olanak tanır ve kütüphanenin çok çeşitli sunucular ve her iki platforma dayalı projelerle kullanılabilmesini sağlar.

## Kütüphanenin İç Mimarisi: Derinlemesine Bir İnceleme

**SA-MP Injector C++**, enjeksiyon sürecinin karmaşıklığını yönetmek için modüler ve nesne yönelimli (uygun olduğunda) bir yaklaşım benimser. Her başlık dosyası, genel işlevselliğin belirli bir parçasından sorumlu özel bir modüldür; bu, kodun netliğini, bakım kolaylığını ve genişletilebilirliğini teşvik eder.

### `constants.hpp`

Bu dosya, kütüphanenin tüm sabit yapılandırmalarının temelini oluşturur. Tüm sabitleri kapsüllemek için bir `Constants` ad alanı tanımlar ve küresel kapsam kirliliğini önler. `inline constexpr` kullanımı burada çok önemlidir: `constexpr`, değerlerin derleme zamanında değerlendirildiğini ve performansı optimize ederek değişmezliği garanti ettiğini belirtir; `inline` ise dosyanın birden fazla derleme biriminde dahil edilmesi durumunda yeniden tanımlama sorunlarını önler.

```cpp
#pragma once

namespace Constants {
    // Game related constants
    inline constexpr int MIN_PORT = 1;
    inline constexpr int MAX_PORT = 65535;
    inline constexpr int MAX_NICKNAME_LENGTH = 23;
    
    // File names
    inline constexpr const wchar_t* SAMP_DLL_NAME = L"samp.dll";
    inline constexpr const wchar_t* OMP_DLL_NAME = L"omp-client.dll";
    inline constexpr const wchar_t* GAME_EXE_NAME = L"gta_sa.exe";
    
    // System libraries and functions
    inline constexpr const char* KERNEL32_DLL = "kernel32.dll";
    inline constexpr const char* LOAD_LIBRARY_FUNC = "LoadLibraryA"; // 'A' için ANSI/8-bit sürümü
    
    // Command line arguments used by SA-MP/OMP clients
    inline constexpr const char* CMD_ARG_CONFIG = "-c";
    inline constexpr const char* CMD_ARG_NICKNAME = "-n";
    inline constexpr const char* CMD_ARG_HOST = "-h";
    inline constexpr const char* CMD_ARG_PORT = "-p";
    inline constexpr const char* CMD_ARG_PASSWORD = "-z";
    
    // Injection types as strings (wide-character)
    inline constexpr const wchar_t* INJECT_TYPE_SAMP = L"samp";
    inline constexpr const wchar_t* INJECT_TYPE_OMP = L"omp";
    
    // Error message titles for MessageBoxW
    inline constexpr const wchar_t* ERROR_TITLE_SAMP = L"SA-MP Injector Error - SPC";
    inline constexpr const wchar_t* ERROR_TITLE_OMP = L"OMP Injector Error - SPC";
    
    // Process creation flags for CreateProcessA
    inline constexpr DWORD PROCESS_CREATION_FLAGS = CREATE_SUSPENDED | DETACHED_PROCESS;
    
    // Timeouts for WaitForSingleObject (e.g., waiting for DLL injection)
    inline constexpr DWORD DLL_INJECTION_TIMEOUT_MS = 10000; // 10 saniye
    
    // Memory allocation flags for VirtualAllocEx
    inline constexpr DWORD MEMORY_ALLOCATION_TYPE = MEM_COMMIT | MEM_RESERVE;
    inline constexpr DWORD MEMORY_PROTECTION = PAGE_READWRITE; // DLL yolunu yazmak için gerekli
}
```

> [!TIP]
> **Windows geliştirme** ortamında dosya adları ve hata mesajı başlıkları için `wchar_t` kullanımı önerilen bir uygulamadır. Bu, tüm diller ve karakter setleriyle uyumluluğu garanti eder, özellikle **Unicode karakterler** içeren dosya yolları için kullanışlıdır. `LoadLibraryA` gibi `char` bekleyen **API'ler** için dönüşüm `string_utils.hpp` içinde açıkça yapılır.

### `types.hpp`

Desteklenen enjeksiyon türlerini kategorize eden bir numaralandırma tanımlayan kısa ama temel bir modüldür. Bu, kodun okunabilirliğini ve tür güvenliğini artırır, dize veya sihirli sayı hatalarını önler.

```cpp
#pragma once

namespace Types {
    // Desteklenen enjeksiyon türleri için numaralandırmalar
    enum class Inject_Type {
        SAMP, // San Andreas Multiplayer
        OMP // Open Multiplayer
    };
}
```

### `string_utils.hpp`

**Windows API** ile çalışmak genellikle farklı dize kodlamaları arasında dönüşüm yapmayı gerektirir. Bu dosya, kütüphanenin girişlerinde kullanılan **geniş karakter** dizilerinden (`std::wstring_view`) **ANSI/8-bit** dizilere (`std::string`) dönüşüm yapmak için hayati bir yardımcı işlev sağlar; bu, `CreateProcessA` veya `GetProcAddress` gibi `char*` bekleyen **WinAPI** işlevleri için gereklidir.

```cpp
#pragma once

#include <string>
#include <string_view>
#include <windows.h> // WideCharToMultiByte için gerekli

namespace Utils {
    inline std::string Wide_To_Local_8Bit(std::wstring_view wstr) {
        if (wstr.empty())
            return "";
        
        // Sonuç dizesi için gereken tampon boyutunu belirler
        int size = WideCharToMultiByte(CP_ACP, // ANSI Kod Sayfası (yerel sisteme bağlı)
            0, // Ek bayrak yok
            wstr.data(), 
            static_cast<int>(wstr.size()), 
            nullptr, // Boyut hesaplanır, tampon doldurulmaz
            0, // Boyut 0, sadece hesaplama için
            nullptr, // Temsil edilemeyen karakterler için varsayılan karakter
            nullptr); // Varsayılan karakterin kullanıldığını belirten bool işaretçisi

        if (size <= 0) // Hata veya geçersiz boyut durumunda boş dize döndür
            return "";

        std::string result(size, 0); // Belirlenen boyutta dize ayır
        // Gerçek dönüşümü gerçekleştir ve 'result' tamponunu doldur
        WideCharToMultiByte(CP_ACP, 
            0, 
            wstr.data(), 
            static_cast<int>(wstr.size()), 
            result.data(), // Hedef tampon
            size, // Hedef tamponun boyutu
            nullptr, 
            nullptr);

        return result;
    }
}
```

> [!IMPORTANT]
> `WideCharToMultiByte` içinde kullanılan `CP_ACP` **(ANSI Kod Sayfası)**, **Windows** sisteminin varsayılan kod sayfasıdır. Bu, dönüşümün kullanıcının sistem dil ayarlarına bağlı olarak değişebileceği anlamına gelir. **SA-MP**/**OMP**'nin dosya adları ve komut satırı argümanları için (tarihsel olarak **ANSI** dizelerle iyi çalışır) bu yaklaşım genellikle yeterlidir. Ancak, harici sistemler veya küresel girişlerle tam **Unicode** uyumluluğu gerektiren senaryolarda, **UTF-8** (`CP_UTF8`) veya diğer kod sayfalarına dönüşüm gerekli olabilir. Bu projenin kapsamı için `CP_ACP`, işlevsel varsayılandır.

### `error_utils.hpp`

Kütüphanenin kullanılabilirliği için temel bir bileşen olan bu dosya, sistem hata mesajlarını alma ve diyalog kutuları görüntüleme mantığını merkezileştirir.

```cpp
#pragma once

#include <string>
#include <string_view>
#include <windows.h> // FormatMessageW ve MessageBoxW için
//
#include "types.hpp"
#include "constants.hpp"

namespace Utils {
    // Belirli bir hata kodu için Windows sistem hata mesajını döndürür
    inline std::wstring Get_System_Error_Message(DWORD error_code) {
        wchar_t buffer[512] = {0}; // Mesaj için tampon
        // FormatMessageW, sistemin hata açıklamasıyla tamponu doldurur
        DWORD result = FormatMessageW(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, 
            nullptr, // Mesaj kaynağı (sistemden)
            error_code, 
            0, // Dil (varsayılan kullan)
            buffer, 
            512, // Tampon boyutu
            nullptr);
        
        // İşlev başarılı olursa tampon dizesini döndür; aksi takdirde genel bir mesaj
        return result ? std::wstring(buffer) : L"Unknown error (Code: " + std::to_wstring(error_code) + L")";
    }

    // Kullanıcıya hata mesajı kutusu gösterir
    inline void Show_Error(std::wstring_view message, Types::Inject_Type injectType) {
        // Enjeksiyon türüne bağlı olarak diyalog kutusu başlığını seç
        std::wstring title = (injectType == Types::Inject_Type::SAMP) ? Constants::ERROR_TITLE_SAMP : Constants::ERROR_TITLE_OMP;
        MessageBoxW(nullptr, // Üst pencere tutamacı (nullptr masaüstü için)
            message.data(), 
            title.c_str(), 
            MB_OK | MB_ICONERROR); // Tamam düğmesi ve hata simgesi
    }
}
```

> [!NOTE]
> `FormatMessageW`, sistem hata kodunun metinsel açıklamasını alan güçlü bir **Windows API**'sidir. Etkili **tanılama** için net mesajlar sağlar ve `DWORD` gibi `ERROR_FILE_NOT_FOUND` (2) kodunu `L"Sistem belirtilen dosyayı bulamıyor."` gibi bir mesaja dönüştürür.

### `resource_handle.hpp`

**Windows** **tutamaçlarının** (`HANDLE`) güvenli yönetimi, kaynak sızıntılarını ve tanımsız davranışları önlemek için kritik öneme sahiptir. Bu dosya, `CloseHandle` için özel bir işlevle `std::unique_ptr` kullanan bir `UniqueResource` tanımlar. Bu, **RAII (Resource Acquisition Is Initialization)** ilkesini takip eder ve **tutamaçların** nesne kapsam dışına çıktığında otomatik olarak kapatılmasını sağlar, hatta istisnalar durumunda bile.

```cpp
#pragma once

#include <memory> // std::unique_ptr için
#include <functional> // std::function için
#include <windows.h> // HANDLE ve CloseHandle için

namespace Utils {
    // HANDLE veya işaretçi yöneten std::unique_ptr için tür takma adı
    // T: Yönetilecek kaynak türü (ör: HANDLE, LPVOID)
    // Deleter: Kaynağı nasıl serbest bırakacağını bilen bir sınıf veya lambda
    template<typename T, typename Deleter>
    using UniqueResource = std::unique_ptr<std::remove_pointer_t<T>, Deleter>;

    // HANDLE'lar için UniqueResource örneği oluşturan yardımcı işlev
    // T'nin bir tutamaç türü olduğunu varsayar ve CloseHandle'ı deleter olarak kullanır.
    template<typename T>
    inline auto Make_Unique_Handle(T handle) {
        return UniqueResource<T, std::function<void(T)>>(handle, [](T h) {
            // Tutamacın geçerli olduğunu kontrol eden koşul
            // Çoğu tutamaç için 0 ve INVALID_HANDLE_VALUE geçersizdir
            if (h && h != INVALID_HANDLE_VALUE)
                CloseHandle(h); // İşletim sistemi tutamacını serbest bırakır
        });
    }
}
```

> [!IMPORTANT]
> `UniqueResource` kullanımı, **modern C++** ve güvenli **Windows** geliştirmedeki iyi uygulamaları gösterir. **Tutamaçların** yaşam döngüsünü büyük ölçüde basitleştirir; düzgün kapatılmadığında sistem kararlılığını uzun vadede etkileyebilecek **bellek** veya **çekirdek kaynak** sızıntılarına yol açabilir.

### `validation.hpp`

Enjeksiyonun sağlamlığı, kullanıcı girişlerinin doğrulanması ve dosya bağımlılıklarının kontrol edilmesiyle başlar. Bu modül, enjeksiyon sürecine başlamadan önce tüm ön koşullar ve parametrelerin doğru olduğunu garanti eden işlevler içerir ve daha karmaşık hataları önler.

```cpp
#pragma once

#include <string>
#include <string_view>
#include <filesystem> // std::filesystem::exists için
//
#include "constants.hpp"
#include "types.hpp"
#include "string_utils.hpp" // Wide_To_Local_8Bit için
#include "error_utils.hpp" // Show_Error için

namespace Utils {
    // Port dizesinin geçerli bir sayı olup olmadığını ve izin verilen aralıkta olup olmadığını doğrular
    inline bool Validate_Port(std::wstring_view port_str, std::wstring& error_message) {
        try {
            // Geniş karakter dizesini std::string'e ve ardından int'e dönüştürmeyi dener
            int port_num = std::stoi(Wide_To_Local_8Bit(port_str));

            // Portun geçerli aralıkta (1-65535) olup olmadığını kontrol eder
            if (port_num < Constants::MIN_PORT || port_num > Constants::MAX_PORT)
                return (error_message = L"Belirtilen port numarası (" + std::wstring(port_str) + 
                L") geçerli aralığın dışında: " +  std::to_wstring(Constants::MIN_PORT) + 
                L" ile " + std::to_wstring(Constants::MAX_PORT) + 
                L". Lütfen geçerli bir port sağlayın.", false);

            return true;
        }
        catch (...) { // Herhangi bir istisna yakalar (örneğin sayısal olmayan için std::invalid_argument)
            return (error_message = L"Geçersiz port formatı. Port sayısal bir değer olmalıdır. Lütfen port için geçerli bir tamsayı sağlayın.", false);
        }
    }

    // Kullanıcı adının boş olmadığını ve kabul edilebilir uzunlukta olduğunu doğrular
    inline bool Validate_Nickname(std::wstring_view nickname_str, std::wstring& error_message) {
        if (nickname_str.empty())
            return (error_message = L"Kullanıcı adı boş olamaz. Lütfen geçerli bir kullanıcı adı sağlayın.", false);
        
        if (nickname_str.size() > Constants::MAX_NICKNAME_LENGTH)
            return (error_message = L"Kullanıcı adı uzunluğu, izin verilen maksimum " + 
                std::to_wstring(Constants::MAX_NICKNAME_LENGTH) + 
                L" karakteri aşıyor. Lütfen daha kısa bir kullanıcı adı kullanın.", false);

        return true;
    }

    // Kritik dosyaların (gta_sa.exe, samp.dll, omp-client.dll) varlığını doğrular
    inline bool Validate_Files(const std::filesystem::path& game_path, 
        const std::filesystem::path& samp_DLL_path, 
        const std::filesystem::path& omp_DLL_path, 
        Types::Inject_Type inject_type) {
        std::wstring error_message_local; // Show_Error'a geçmeden önce yerel bir değişken kullanır
        
        // Oyun yürütülebilir dosyasının varlığını kontrol eder
        if (!std::filesystem::exists(game_path)) {
            error_message_local = L"Oyun yürütülebilir dosyası bulunamadı. Lütfen 'gta_sa.exe' dosyasının belirtilen yolda mevcut olduğundan emin olun: " + game_path.wstring();
            Show_Error(error_message_local, inject_type);
            
            return false;
        }

        // samp.dll dosyasının varlığını kontrol eder (her iki enjeksiyon türü için gerekli)
        if (!std::filesystem::exists(samp_DLL_path)) {
            error_message_local = L"SA-MP kütüphanesi bulunamadı. Lütfen 'samp.dll' dosyasının belirtilen yolda mevcut olduğundan emin olun: " + samp_DLL_path.wstring();
            Show_Error(error_message_local, inject_type);

            return false;
        }

        // Enjeksiyon türü OMP ise omp-client.dll dosyasının varlığını kontrol eder
        if (inject_type == Types::Inject_Type::OMP && !std::filesystem::exists(omp_DLL_path)) {
            error_message_local = L"OMP kütüphanesi bulunamadı. OMP enjeksiyonu için lütfen 'omp-client.dll' dosyasının belirtilen yolda mevcut olduğundan emin olun: " + omp_DLL_path.wstring();
            Show_Error(error_message_local, inject_type);

            return false;
        }

        return true; // Gerekli tüm dosyalar bulundu
    }
}
```

> [!NOTE]
> `std::filesystem`, **C++17**'nin güçlü ve platformdan bağımsız bir şekilde dosya sistemiyle etkileşim kurmayı sağlayan modern bir ekidir. **Windows** için bu proje bağlamında, eski **WinAPI**'lere kıyasla dosya yollarının işlenmesini ve dosya varlığının kontrolünü basitleştirir.
>
> `std::filesystem`'i kullanmak için derleyicinizin **C++17**'yi desteklediğinden emin olun. Projenizi **C++17** standardını kullanacak şekilde yapılandırmanız gerekir (**Visual Studio**'da `/std:c++17`).

### `process.hpp`

Bu, düşük seviyeli **Windows API**'leriyle doğrudan etkileşim kurarak süreçleri manipüle etmekten sorumlu ana modüldür. Süreç oluşturma ve **DLL enjeksiyonu** için kritik işlemleri kapsar; **tutamaçlar**, **bellek** ve **iş parçacıkları** ile ilgilenir.

```cpp
#pragma once

#include <string_view>
#include <optional> // std::optional için
#include <functional> // std::function için (UniqueResource'da kullanılır)
#include <windows.h> // Windows API'leri
#include <memory> // std::unique_ptr için
#include <vector> // std::vector için (argüman tamponu)
//
#include "resource_handle.hpp" // Tutamaçlar için sarmalayıcımız
#include "error_utils.hpp" // Get_System_Error_Message ve Show_Error için
#include "constants.hpp" // Genel sabitler
#include "types.hpp" // Enjeksiyon türleri

class Process {
    public:
        // Yapıcılar/Yıkıcılar ve atama operatörleri
        // Değer semantiği ve yalnızca hareket semantiği için açıkça varsayılan ve silinmiş.
        Process() = default;
        Process(const Process&) = delete; // Kopyalama yok
        Process& operator=(const Process&) = delete; // Kopya atama yok
        Process(Process&&) = default; // Hareket semantiği
        Process& operator=(Process&&) = default; // Hareket atama
        ~Process() = default;

        // Süreç ve iş parçacığı tutamaçlarını UniqueResource ile yönetilen bir yapıda saklar
        struct Process_Info {
            Resource_Handle::UniqueResource<HANDLE, std::function<void(HANDLE)>> process_handle;
            Resource_Handle::UniqueResource<HANDLE, std::function<void(HANDLE)>> thread_handle;
        };

        // GTA:SA oyun sürecini askıya alınmış durumda oluşturur
        std::optional<Process_Info> Create_Game_Process(std::string_view game_path, std::string_view command_args, std::string_view working_dir) {
            STARTUPINFOA startup_info{}; // Süreç başlatma bilgileri için yapı
            startup_info.cb = sizeof(STARTUPINFOA); // Yapının boyutunu belirler

            PROCESS_INFORMATION process_info{}; // Yeni süreç hakkında bilgi alacak yapı

            // Komut satırı argümanları için değiştirilebilir bir tampon oluşturur.
            // CreateProcessA, komut satırı tamponunu değiştirir, bu yüzden doğrudan std::string_view kullanılamaz.
            std::vector<char> args_buffer(command_args.size() + 1); // +1 sıfır sonlandırıcı için

            if (!command_args.empty()) {
                std::memcpy(args_buffer.data(), command_args.data(), command_args.size());
                args_buffer[command_args.size()] = '\0'; // Sıfır sonlandırıcıyı garanti eder
            }

            // Süreci oluştur
            bool success = CreateProcessA(game_path.data(), // Yürütülebilir modül adı
                args_buffer.empty() ? nullptr : args_buffer.data(), // Komut satırı argümanları
                nullptr, // Süreç güvenlik öznitelikleri
                nullptr, // İş parçacığı güvenlik öznitelikleri
                FALSE, // Tutamaçları devralma
                Constants::PROCESS_CREATION_FLAGS, // CREATE_SUSPENDED | DETACHED_PROCESS
                nullptr, // Yeni sürecin ortamı
                working_dir.empty() ? nullptr : working_dir.data(), // Çalışma dizini
                &startup_info, // Başlatma bilgileri
                &process_info); // Oluşturulan süreç bilgileri

            if (!success) {
                // Başarısız olursa, sistem hata mesajını al ve göster
                std::wstring error_msg = Error_Utils::Get_System_Error_Message(GetLastError());
                Error_Utils::Show_Error(L"Oyun süreci oluşturulamadı. 'gta_sa.exe' dosyasının çalışmadığından ve dosyayı yürütmek için yeterli izniniz olduğundan emin olun. Sistem Hatası: " + error_msg, Types::Inject_Type::SAMP); // Başlık için SAMP varsayılan olarak kullanılır
                
                return std::nullopt; // Boş bir optional döndür
            }

            Process_Info result;
            // Süreç ve iş parçacığı tutamaçlarını otomatik yönetim için UniqueResource'a depolar
            result.process_handle = Resource_Handle::Make_Unique_Handle(process_info.hProcess);
            result.thread_handle = Resource_Handle::Make_Unique_Handle(process_info.hThread);

            return result; // Yönetilen tutamaçlarla yapıyı döndür
        }

        // Uzak sürece bir DLL enjekte eder
        bool Inject_DLL(HANDLE process, std::string_view DLL_path, std::wstring& error_message) {
            // DLL yolu için uzak süreçte bellek ayır
            LPVOID remote_memory = VirtualAllocEx(process, // Hedef süreç tutamacı
            nullptr, // Tercih edilen adres (nullptr sistemin seçmesine izin verir)
            DLL_path.size() + 1, // Yol boyutu + sıfır sonlandırıcı
            Constants::MEMORY_ALLOCATION_TYPE, // MEM_COMMIT | MEM_RESERVE
            Constants::MEMORY_PROTECTION); // PAGE_READWRITE

            if (!remote_memory)
                return (error_message = L"Hedef süreçte bellek ayırma başarısız oldu. Bu, yetersiz izinler veya süreç koruma mekanizmaları nedeniyle olabilir.", false);

            // Uzakta ayrılan bellek için kaynak yönetimi.
            // Kapsam dışına çıktığında otomatik olarak serbest bırakılır.
            auto memory_guard = Resource_Handle::UniqueResource<LPVOID, std::function<void(LPVOID)>>(remote_memory, 
                [process](LPVOID ptr) { // Deleter olarak lambda
                    if (ptr)
                        VirtualFreeEx(process, ptr, 0, MEM_RELEASE); // Ayrılan belleği serbest bırak
                }
            );

            // DLL yolunu uzak ayrılan belleğe yazar
            if (!WriteProcessMemory(process, remote_memory, DLL_path.data(), DLL_path.size() + 1, nullptr))
                return (error_message = L"DLL yolu hedef süreç belleğine yazılamadı. Süreç izinlerini doğrulayın ve DLL yolunun erişilebilir olduğundan emin olun.", false);

            // Enjektör sürecinde zaten yüklü olan kernel32.dll için tutamaç alır
            HMODULE kernel32 = GetModuleHandleA(Constants::KERNEL32_DLL);
            
            if (!kernel32)
                return (error_message = L"kernel32.dll için tutamaç alınamadı. Bu temel bir sistem kütüphanesidir ve bu hata ciddi bir sistem sorununu işaret eder.", false);

            // kernel32.dll içinde LoadLibraryA işlevinin adresini alır.
            // Bu adres, aynı işletim sisteminde süreçler arasında tutarlıdır ve enjeksiyonun anahtarıdır.
            LPVOID load_library_addr = reinterpret_cast<LPVOID>(GetProcAddress(kernel32, Constants::LOAD_LIBRARY_FUNC));

            if (!load_library_addr)
                return (error_message = L"kernel32.dll içinde LoadLibraryA işlevinin adresi bulunamadı. Bu, DLL enjeksiyonu için kritik öneme sahiptir.", false);

            // LoadLibraryA'yı yürütmek için hedef süreçte uzak bir iş parçacığı oluşturur
            // LoadLibraryA için argüman, DLL yolunun uzak adresi olacaktır
            HANDLE remote_thread = CreateRemoteThread(process, // Hedef süreç tutamacı
                nullptr, // İş parçacığı güvenlik öznitelikleri
                0, // Yığın boyutu (0 varsayılan için)
                reinterpret_cast<LPTHREAD_START_ROUTINE>(load_library_addr), // LoadLibraryA adresi
                remote_memory, // LoadLibraryA için argüman (DLL yolu)
                0, // Oluşturma bayrakları (hemen başlatmak için 0)
                nullptr); // İş parçacığı kimliği (dönmemesi için nullptr)

            if (!remote_thread)
                return (error_message = L"DLL enjeksiyonunu yürütmek için hedef süreçte uzak iş parçacığı oluşturulamadı. Bu, güvenlik kısıtlamaları veya süreç durumu nedeniyle olabilir. Sistem Hatası: " + Error_Utils::Get_System_Error_Message(GetLastError()), false);

            // Uzak iş parçacığı tutamacı için kaynak yönetimi
            auto thread_guard = Resource_Handle::Make_Unique_Handle(remote_thread);

            // Uzak iş parçacığının (DLL enjeksiyonu) tamamlanmasını veya zaman aşımına uğramasını bekler
            DWORD wait_result = WaitForSingleObject(remote_thread, Constants::DLL_INJECTION_TIMEOUT_MS);

            if (wait_result != WAIT_OBJECT_0) {
                return (error_message = L"DLL enjeksiyonunun tamamlanması için beklerken zaman aşımı veya hata oluştu. Sistem Hatası: " + Error_Utils::Get_System_Error_Message(GetLastError()), false);

            // Uzak iş parçacığının çıkış kodunu alır.
            // LoadLibraryA için 0 çıkış kodu başarısızlık anlamına gelir (DLL yüklenemedi).
            DWORD exit_code = 0;

            if (!GetExitCodeThread(remote_thread, &exit_code) || exit_code == 0)
                return (error_message = L"DLL enjeksiyonu başarısız oldu veya bir hata döndürdü. Hedef süreçte LoadLibrary çağrısı başarısız olmuş olabilir.", false);

            return true; // Enjeksiyon başarılı
        }
};
```

> [!NOTE]
> `process.hpp` modülü, sağlam ve güvenli bir tasarımı sergiler. `Create_Game_Process` işlevi, bir `std::optional<Process_Info>` döndürür. Bu, işlevin süreç oluşturma başarısızlıklarını açık ve zarif bir şekilde (bir `std::nullopt` döndürerek) sinyalize etmesini sağlar, istisnalar veya belirsiz hata kodlarına başvurmadan.
>
> Daha da önemlisi, `Process_Info` yapısı, **süreç** ve **iş parçacığı** tutamaçlarını kapsüllemek için `Resource_Handle::UniqueResource<HANDLE, std::function<void(HANDLE)>>` kullanır. Bu, **RAII (Resource Acquisition Is Initialization)** deseninin bir örneğidir ve `hProcess` ve `hThread` gibi işletim sistemi **tutamaçlarının** `Process_Info` nesnesi kapsam dışına çıktığında otomatik olarak `CloseHandle` ile kapatılmasını sağlar. Bu, **Windows uygulamalarında** uzun süre çalışan uygulamalarda kaynak tüketimi ve kararsızlığa yol açabilecek **tutamaç sızıntılarını** ortadan kaldırır.
>
> Benzer şekilde, `Inject_DLL` işlevinde, `UniqueResource`, uzaktan ayrılan belleği (`VirtualAllocEx`) yönetir ve artık ihtiyaç duyulmadığında veya başarısızlık durumunda `VirtualFreeEx` ile serbest bırakılmasını sağlar. Bu titiz kaynak yönetimi, **SA-MP Injector C++**'nin güvenilirliğine ve kararlılığına önemli ölçüde katkıda bulunur.

### `injector_core.hpp`

Bu, önceki modüllerin tüm işlevselliklerini bir araya getiren orkestratör sınıftır. Doğrulama, komut satırı argümanlarının oluşturulması, süreç oluşturma ve **DLL enjeksiyonu** çağrılarını koordine eder.

```cpp
#pragma once

#include <string_view>
#include <sstream> // stringstream ile dizeler oluşturmak için
#include <filesystem> // Yol manipülasyonu için
//
#include "process.hpp" // Süreç oluşturma/enjeksiyon işlevleri
#include "validation.hpp" // Giriş doğrulama işlevleri
#include "string_utils.hpp" // Dize dönüşüm işlevleri
#include "error_utils.hpp" // Hata işleme işlevleri
#include "constants.hpp" // Kütüphane sabitleri
#include "types.hpp" // Enjeksiyon türleri

namespace Injector {
    class Injector_Core {
        public:
            // Hareket semantiği için yapıcılar/yıkıcılar
            Injector_Core() = default;
            Injector_Core(const Injector_Core&) = delete; // Kopyalama devre dışı
            Injector_Core& operator=(const Injector_Core&) = delete; // Kopya atama devre dışı
            Injector_Core(Injector_Core&&) = default; // Hareket etkin
            Injector_Core& operator=(Injector_Core&&) = default; // Hareket atama etkin
            ~Injector_Core() = default;

            // Oyunu başlatma ve enjeksiyonu orkestre eden ana işlev
            bool Initialize_Game(Types::Inject_Type inject_type, std::wstring_view folder, std::wstring_view nickname, std::wstring_view ip, std::wstring_view port, std::wstring_view password) {
                namespace fs = std::filesystem; // std::filesystem için takma ad

                // Temel dosyalar için tam yolları oluştur
                fs::path game_path = fs::path(folder) / Constants::GAME_EXE_NAME; // Ör: C:\GTA\gta_sa.exe
                fs::path samp_DLL_path = fs::path(folder) / Constants::SAMP_DLL_NAME; // Ör: C:\GTA\samp.dll
                fs::path omp_DLL_path = fs::path(folder) / Constants::OMP_DLL_NAME; // Ör: C:\GTA\omp-client.dll

                // 1. Dosya Doğrulama
                if (!Validation::Validate_Files(game_path, samp_DLL_path, omp_DLL_path, inject_type))
                    return false; // Hata zaten doğrulama işlevi tarafından gösterildi
                
                std::wstring error_message_local; // Doğrulama hata mesajlarını almak için

                // 2. Port Doğrulama
                if (!Validation::Validate_Port(port, error_message_local))
                    return (Error_Utils::Show_Error(error_message_local, inject_type), false);

                // 3. Kullanıcı Adı Doğrulama
                if (!Validation::Validate_Nickname(nickname, error_message_local))
                    return (Error_Utils::Show_Error(error_message_local, inject_type), false);

                // 4. Geniş karakterden yerel 8-bit'e dönüşüm (ANSI API'leri için gerekli)
                std::string nickname_str = String_Utils::Wide_To_Local_8Bit(nickname);
                std::string ip_str = String_Utils::Wide_To_Local_8Bit(ip);
                std::string port_str = String_Utils::Wide_To_Local_8Bit(port);
                std::string password_str = String_Utils::Wide_To_Local_8Bit(password);
                // Yollar da CreateProcessA için char* gerektirdiğinden std::string'e dönüştürülür
                std::string game_path_str = String_Utils::Wide_To_Local_8Bit(game_path.wstring());
                std::string folder_str = String_Utils::Wide_To_Local_8Bit(folder);
                std::string samp_DLL_path_str = String_Utils::Wide_To_Local_8Bit(samp_DLL_path.wstring());
                std::string omp_DLL_path_str = String_Utils::Wide_To_Local_8Bit(omp_DLL_path.wstring());

                // 5. Komut Satırı Argümanlarının Oluşturulması
                std::string args = Build_Command_Args(nickname_str, ip_str, port_str, password_str);

                // Süreç işlemlerini yönetmek için Process sınıfını başlat
                Process process_core;
                
                // 6. Oyun Sürecinin Oluşturulması (Askıya Alınmış)
                auto process_info_opt = process_core.Create_Game_Process(game_path_str, args, folder_str);

                if (!process_info_opt)
                    return false; // Hata zaten süreç oluşturma işlevi tarafından gösterildi

                // Optional'ı çözümleyerek Process_Info yapısını elde et
                auto& process_info = *process_info_opt; 
                std::wstring inject_error_message; // Enjeksiyon hata mesajlarını almak için

                // 7. samp.dll Enjeksiyonu
                if (!process_core.Inject_DLL(process_info.process_handle.get(), samp_DLL_path_str, inject_error_message))
                    return (Error_Utils::Show_Error(L"samp.dll enjeksiyonu başarısız: " + inject_error_message, inject_type), false);

                // 8. omp-client.dll Koşullu Enjeksiyonu (yalnızca OMP için)
                if (inject_type == Types::Inject_Type::OMP) {
                    if (!process_core.Inject_DLL(process_info.process_handle.get(), omp_DLL_path_str, inject_error_message))
                        return (Error_Utils::Show_Error(L"omp-client.dll enjeksiyonu başarısız: " + inject_error_message, inject_type), false);
                }

                // 9. Oyun Sürecini Sürdürme
                // Süreç, enjeksiyona izin vermek için askıya alınmış durumda oluşturuldu.
                // DLL'ler enjekte edildiğine göre süreç devam ettirilebilir.
                if (ResumeThread(process_info.thread_handle.get()) == static_cast<DWORD>(-1))
                    return (Error_Utils::Show_Error(L"Oyun süreci iş parçacığını sürdürme başarısız: " + Error_Utils::Get_System_Error_Message(GetLastError()), inject_type), false);

                return true; // Tüm adımlarda başarı!
            }
        private:
            // Oyun yürütülebilir dosyası için komut satırı argüman dizesini oluşturur
            std::string Build_Command_Args(const std::string& nickname, const std::string& ip, const std::string& port, const std::string& password) {
                std::stringstream command_args_stream; // Verimli oluşturma için stringstream kullan

                // SA-MP ve OMP, "-c -n [kullanıcı adı] -h [ip] -p [port]" argümanlarını bekler
                command_args_stream << Constants::CMD_ARG_CONFIG << " " 
                    << Constants::CMD_ARG_NICKNAME << " " << nickname << " " 
                    << Constants::CMD_ARG_HOST << " " << ip << " " 
                    << Constants::CMD_ARG_PORT << " " << port;

                // Şifre boş değilse eklenir
                if (!password.empty())
                    command_args_stream << " " << Constants::CMD_ARG_PASSWORD << " " << password;

                return command_args_stream.str();
            }
    };
}
```

> [!CAUTION]
> **OMP** için süreç, `samp.dll`'ye ek olarak `omp-client.dll`'yi enjekte etmeyi içerir; bu, **OMP**'nin genellikle çalışma şekline uygundur. **OMP** istemcisi, bazı işlevsellikler için genellikle `samp.dll`'yi **temel** veya **vekil** olarak kullanır, `omp-client.dll` ise davranışları genişletir veya üzerine yazar.
>
> **OMP enjeksiyonunun** başarılı olması için her iki **DLL**'nin de oyun dizininde mevcut ve işlevsel olması çok önemlidir. Biri başarısız olursa, oyun düzgün başlatılamayabilir veya çok oyunculu istemci yüklenmeyebilir.

### `injector.hpp`

Bu, kütüphanenin arabirim dosyasıdır. Kullanıcıların **SA-MP Injector C++**'yi kullanmak için yalnızca bu dosyayı dahil etmesi gerekir. `Injector::Injector_Core` sınıfı için bir sarmalayıcı görevi görerek arabirimi tek bir global işlev olan `Initialize_Game` ile basitleştirir.

```cpp
#pragma once

#include <string_view>
//
#include "injector_core.hpp" // Ana mantığı içeren sınıf
#include "error_utils.hpp" // Hata gösterimi için (geçersiz enjeksiyon türü durumunda)
#include "types.hpp" // Tür numaralandırması
#include "constants.hpp" // Sabitler (enjeksiyon türü adları için)

// Kütüphane için üst düzey arabirim.
// Kullanımı basitleştirmek için yalnızca bu global işlevi sunar.
inline bool Initialize_Game(std::wstring_view inject_type_str, std::wstring_view folder, std::wstring_view nickname, std::wstring_view ip, std::wstring_view port, std::wstring_view password) {
    Types::Inject_Type type; // Enjeksiyon türünü saklamak için değişken

    // Enjeksiyon türü dizesini Inject_Type numaralandırmasına dönüştür
    if (inject_type_str == Constants::INJECT_TYPE_SAMP)
        type = Types::Inject_Type::SAMP;
    
    else if (inject_type_str == Constants::INJECT_TYPE_OMP)
        type = Types::Inject_Type::OMP;
    
    else
        // Geçersiz enjeksiyon türü dizesi durumunda hata göster ve false döndür
        return (Error_Utils::Show_Error(L"Geçersiz enjeksiyon modu belirtildi. Lütfen 'samp' veya 'omp' kullanın.", Types::Inject_Type::SAMP), false); // Başlık için SAMP varsayılan olarak kullanılır

    Injector::Injector_Core injector; // Merkezi mantığı içeren nesneyi başlat
    
    // Injector_Core sınıfının Initialize_Game işlevine çağrıyı devret
    return injector.Initialize_Game(type, folder, nickname, ip, port, password);
}
```

> [!NOTE]
> Bu dosyadaki ve diğer yardımcı işlevlerdeki tüm işlevler için `inline` anahtar kelimesinin kullanımı, kütüphanenin `header-only` olmasını sağlar. `inline`, işlev gövdesinin çağrı noktalarına doğrudan eklenmesini önerir, ancak buradaki asıl etkisi, **One Definition Rule (ODR)**'yi gevşeterek işlevin birden çok `.obj` dosyasında tanımlanabilmesini sağlamaktır (birden çok `.cpp` dosyası `injector.hpp`'yi dahil ederse). **Bağlama** aşaması, yürütülebilir dosyada yalnızca tek bir nihai sürümün bulunmasını sağlar.

## Kapsamlı Kullanım Örnekleri

**SA-MP Injector C++**'yi projenize entegre etmek için aşağıdaki talimatları ve senaryoları izleyin.

### 1. Geliştirme Ortamının Hazırlanması

- **C++ Derleyicisi**: **C++17**'yi destekleyen bir derleyici önerilir. `vcpkg` ile **Visual Studio** (dosya sistemi için `std::filesystem`) veya **GCC/Clang (sürüm 17+)** uygun seçeneklerdir.
- **Proje Yapılandırması**:
  - Yeni bir **C++ projesi** oluşturun (örneğin, bir konsol projesi).
  - **SA-MP Injector C++**'nin tüm `.hpp` dosyalarını projenizin erişebileceği bir klasöre kopyalayın (örneğin, **başlık** klasörüne).
  - **C++ standardının** **C++17** olarak ayarlandığından emin olun. **SA-MP** ve **OMP** kütüphaneleriyle maksimum uyumluluk için bu sürüm kritik öneme sahiptir. **Visual Studio**'da: `Project Properties > Configuration Properties > C/C++ > Language > C++ Language Standard -> "ISO C++17 Standard (/std:c++17)"`
- **İzinler**: Yürütülebilir dosyanız, süreç oluşturmak ve **DLL enjeksiyonu** yapmak için muhtemelen **Yönetici** olarak çalıştırılmalıdır (zorunlu değildir). **Visual Studio**'da bu, şu şekilde yapılabilir: `Project Properties > Configuration Properties > Linker > Manifest File > UAC Execution Level -> "requireAdministrator (/LEVEL='requireAdministrator')"`

### 2. Temel Senaryo: Bir SA-MP Sunucusuna Bağlanma

Bu, **GTA:SA**'yı başlatıp belirli bir **kullanıcı adı** ve **IP**/**port** ile bir **SA-MP** sunucusuna bağlanmanın en yaygın kullanım durumudur.

```cpp
// main.cpp
#include <iostream>
#include <string>
#include <codecvt> // std::wstring_convert için (eski ama bu durumda işlevsel)
#include <locale> // std::codecvt_utf8_to_utf16 için
//
#include "injector.hpp" // Kütüphaneden gereken tek dahil etme!

int Main(int argc, char* argv[]) {
    // Yapılandırma değişkenlerini tanımla
    // Yerel yapılandırmanıza uygun yolları ve sunucu detaylarını değiştirin
    std::wstring folder = L"C:\\Oyunlar\\GTA San Andreas"; // gta_sa.exe, samp.dll'nin bulunduğu yer
    std::wstring nickname = L"İsim";
    std::wstring ip = L"127.0.0.1"; // Örnek: yerel sunucunuz
    std::wstring port = L"7777";
    std::wstring password = L""; // Şifre yoksa boş bırakın

    // İsteğe bağlı: Kullanıcının komut satırı üzerinden yapılandırma sağlamasına izin ver (basitleştirilmiş)
    // Daha sağlam argüman ayrıştırma için bir argüman ayrıştırma kütüphanesi kullanın.
    if (argc > 1) {
        // Örnek: ilk argüman bir yol ise
        if (argc > 1)
            folder = std::wstring_convert<std::codecvt_utf8_to_utf16>().from_bytes(argv[1]);
        
        if (argc > 2)
            nickname = std::wstring_convert<std::codecvt_utf8_to_utf16>().from_bytes(argv[2]);

        if (argc > 3)
            ip = std::wstring_convert<std::codecvt_utf8_to_utf16>().from_bytes(argv[3]);

        if (argc > 4)
            port = std::wstring_convert<std::codecvt_utf8_to_utf16>().from_bytes(argv[4]);
        
        if (argc > 5)
            password = std::wstring_convert<std::codecvt_utf8_to_utf16>().from_bytes(argv[5]);
    }

    std::wcout << L"SA-MP başlatılıyor..." << std::endl;
    std::wcout << L"Oyun klasörü: " << folder << std::endl;
    std::wcout << L"Kullanıcı adı: " << nickname << std::endl;
    std::wcout << L"Sunucu: " << ip << L":" << port << std::endl;

    // Oyunu başlatmak için kütüphane işlevini çağır
    if (Initialize_Game(L"samp", // Enjeksiyon türü: SA-MP
        folder, // Oyun klasörünün yolu
        nickname, // İstenen kullanıcı adı
        ip, // Sunucu IP'si
        port, // Sunucu portu (dize)
        password)) { // Sunucu şifresi (dize, boş olabilir)
        std::wcout << L"\n--- SA-MP başarıyla başlatıldı! ---" << std::endl;
        std::wcout << L"Oyun ayrı bir süreçte başlatıldı." << std::endl;
    }
    else {
        std::wcout << L"\n--- SA-MP başlatılamadı! ---" << std::endl;
        std::wcout << L"Görüntülenen hata mesajlarını kontrol edin." << std::endl;
    }

    // Çıkış mesajlarını görmek için konsolu açık tut
    std::wcout << L"\nProgramı kapatmak için Enter'a basın." << std::endl;
    std::wcin.ignore();

    return 0;
}
```

**Derleme ve çalıştırma için:**

```bash
# g++ ile örnek (Linux/MinGW/MSYS2) - dosya sistemi için libstdc++fs gerekir
# Derleyici zincirinizin, enjeksiyon sürecinde uyumsuzluklar yaratabilecek bir C++ sürümü kullanmadığından emin olun.
# İkili uyumluluk (ABI) için derleyicinizin belgelerine bakın.
g++ main.cpp -o my_launcher -std=c++17 -Wall -lstdc++fs -municode -lkernel32

# MSVC ile örnek (Visual Studio Geliştirici Komut İstemi)
# '/std:c++17' bayrağı, C++17 uyumluluğunu sağlar.
cl /EHsc /std:c++17 /permissive- /FS /utf-8 main.cpp /link /OUT:my_launcher.exe
```

> [!NOTE]
> **SA-MP** ve **OMP**, belirli araçlarla derlenen eski projelerdir ve **Application Binary Interface (ABI)**'lerini tanımlar. Bu kütüphane **C++17** kullanırken, **oyun DLL'leriyle** etkileşimde bulunan **SA-MP** ve **OMP** DLL'lerinin, derleyicinizin ve kullandığı C++ çalışma zamanı (CRT) sürümüyle uyumlu olması çok önemlidir.
>
> **DLL'lerin** oluşturulduğu derleyici veya **C++** sürümünden çok farklı bir derleyici kullanmak, **bellek ayırma** veya **parametre geçişinde** kolayca teşhis edilemeyen ince sorunlara yol açabilir ve enjektörden açık bir hata çıkmayabilir. Bu nedenle, **C++17** maksimum önerilen sürümdür, çünkü daha yeni sürümler **ABI** veya **CRT**'de eski oyun modüllerinin tolere edemeyeceği değişiklikler getirebilir.

### 3. Gelişmiş Senaryo: Bir OMP Sunucusuna Bağlanma

**OMP** için mantık, **SA-MP** ile aynıdır, ancak `inject_type` olarak `L"omp"` belirtilir ve oyun dizininde `omp-client.dll`'nin mevcut olduğundan emin olunur.

```cpp
// main.cpp
#include <iostream>
#include <string>
#include <codecvt> // std::wstring_convert için (eski ama bu durumda işlevsel)
#include <locale> // std::codecvt_utf8_to_utf16 için
//
#include "injector.hpp" // Kütüphaneden gereken tek dahil etme!

int Main(int argc, char* argv[]) {
    // Yapılandırma değişkenlerini tanımla
    // Yerel yapılandırmanıza uygun yolları ve sunucu detaylarını değiştirin
    std::wstring folder = L"C:\\Oyunlar\\GTA San Andreas"; // gta_sa.exe, samp.dll ve omp-client.dll'nin bulunduğu yer
    std::wstring nickname = L"İsim";
    std::wstring ip = L"127.0.0.1"; // Örnek: yerel sunucunuz
    std::wstring port = L"7777";
    std::wstring password = L""; // Şifre yoksa boş bırakın

    // İsteğe bağlı: Kullanıcının komut satırı üzerinden yapılandırma sağlamasına izin ver (basitleştirilmiş)
    // Daha sağlam argüman ayrıştırma için bir argüman ayrıştırma kütüphanesi kullanın.
    if (argc > 1) {
        // Örnek: ilk argüman bir yol ise
        if (argc > 1)
            folder = std::wstring_convert<std::codecvt_utf8_to_utf16>().from_bytes(argv[1]);
        
        if (argc > 2)
            nickname = std::wstring_convert<std::codecvt_utf8_to_utf16>().from_bytes(argv[2]);

        if (argc > 3)
            ip = std::wstring_convert<std::codecvt_utf8_to_utf16>().from_bytes(argv[3]);

        if (argc > 4)
            port = std::wstring_convert<std::codecvt_utf8_to_utf16>().from_bytes(argv[4]);
        
        if (argc > 5)
            password = std::wstring_convert<std::codecvt_utf8_to_utf16>().from_bytes(argv[5]);
    }

    std::wcout << L"OMP başlatılıyor..." << std::endl;
    std::wcout << L"Oyun klasörü: " << folder << std::endl;
    std::wcout << L"Kullanıcı adı: " << nickname << std::endl;
    std::wcout << L"Sunucu: " << ip << L":" << port << std::endl;

    // Oyunu başlatmak için kütüphane işlevini çağır
    if (Initialize_Game(L"omp", // Enjeksiyon türü: OMP
        folder, // Oyun klasörünün yolu
        nickname, // İstenen kullanıcı adı
        ip, // Sunucu IP'si
        port, // Sunucu portu (dize)
        password)) { // Sunucu şifresi (dize, boş olabilir)
        std::wcout << L"\n--- OMP başarıyla başlatıldı! ---" << std::endl;
        std::wcout << L"Oyun ayrı bir süreçte başlatıldı." << std::endl;
    }
    else {
        std::wcout << L"\n--- OMP başlatılamadı! ---" << std::endl;
        std::wcout << L"Görüntülenen hata mesajlarını kontrol edin." << std::endl;
    }

    // Çıkış mesajlarını görmek için konsolu açık tut
    std::wcout << L"\nProgramı kapatmak için Enter'a basın." << std::endl;
    std::wcin.ignore();

    return 0;
}
```

## Yaygın Hataların ve Mesajların Ele Alınması

**SA-MP Injector C++**, kullanılabilirliği önceliklendirir ve bunun temel bir parçası, başarısızlık durumunda kullanıcıya net **geri bildirim** sağlamaktır. Hata mesajları, **Windows diyalog kutuları** (`MessageBoxW`) aracılığıyla sunulur ve daha fazla bağlam için enjeksiyon türüne (**SA-MP** veya **OMP**) göre kategorize edilir. Bu, neyin yanlış gittiğini ve nasıl çözüleceğini tam olarak bilmenizi sağlar.

Karşılaşabileceğiniz bazı yaygın hatalar, olası nedenleri ve çözümleri, bu diyalog kutularının son kullanıcı için nasıl göründüğüne dair görsel örneklerle birlikte aşağıda listelenmiştir:

### 1. Geçersiz Enjeksiyon Türü

`Initialize_Game` işlevine sağlanan `inject_type` `L"samp"` veya `L"omp"` değilse, kütüphane hangi çok oyunculu istemciyi başlatmak istediğinizi bilemez.

![Error 1](../../screenshots/error_1.png)

- **Görüntülenen Hata Mesajı**: `"Invalid injection mode specified. Please use 'samp' or 'omp'."`
- **Neden**: `Initialize_Game` işlevinin ilk argümanı (`std::wstring_view inject_type`) beklenen `L"samp"` veya `L"omp"` değerleriyle eşleşmiyor. Bu, bir yazım hatası, boş bir dize veya tanınmayan bir değer olabilir.
- **Çözüm**: `std::wstring_view inject_type_str` öğesinin `L"samp"` veya `L"omp"` olarak doğru şekilde ayarlandığından emin olun. Kütüphane sabitleriyle uyumluluk için **geniş karakter** (wide-character) literalleri için `L` önekini kullanmak çok önemlidir.
    ```cpp
    // Doğru:
    Initialize_Game(L"samp", /* diğer parametreler */);
    Initialize_Game(L"omp", /* diğer parametreler */);

    // Yanlış (hataya neden olur):
    // Initialize_Game(L"invalid", /* diğer parametreler */);
    // Initialize_Game(L"", /* diğer parametreler */);
    ```

### 2. Geçersiz Sunucu Portu (Format veya Aralık)

Port, sunucuya bağlantı için gerekli bir sayısal parametredir. Bu hata, değer geçerli bir sayı olarak yorumlanamazsa veya kabul edilebilir aralığın (**1 ila 65535**) dışında ise oluşur.

#### 2.1. Sayısal Olmayan Port Formatı

![Error 2](../../screenshots/error_2.png)

- **Görüntülenen Hata Mesajı**: `"Invalid port format. The port must be a numeric value. Please provide a valid integer for the port."`
- **Neden**: `port` argümanı (`std::wstring_view`) sayısal olmayan karakterler içeriyor veya tamsayıya dönüştürülemiyor.
- **Çözüm**: Yalnızca rakamlardan oluşan ve geçerli bir tamsayıyı temsil eden bir dize sağlayın.
    ```cpp
    // Doğru:
    Initialize_Game(/* diğer parametreler */, L"7777", /* diğer parametreler */);

    // Yanlış (geçersiz format):
    // Initialize_Game(/* diğer parametreler */, L"port7777", /* diğer parametreler */);

    // Yanlış (geçersiz):
    // Initialize_Game(/* diğer parametreler */, L"invalid", /* diğer parametreler */);
    ```

#### 2.2. Geçerli Aralık Dışında Port

![Error 3](../../screenshots/error_3.png)

- **Görüntülenen Hata Mesajı**: `"The specified port number (XXXX) is outside the valid range of 1 to 65535. Please provide a valid port."` (**XXXX**, kullanmaya çalıştığınız değer olacaktır).
- **Neden**: Sağlanan port geçerli bir sayıdır ancak `1` altında (rezerve veya kullanılamaz) veya `65535` üzerinde (**TCP/UDP portları** için maksimum sınır).
- **Çözüm**: `1` ile `65535` aralığında bir port sağlayın. **SA-MP**/**OMP** için yaygın portlar `7777` veya `7778`'dir.
    ```cpp
    // Doğru:
    Initialize_Game(/* diğer parametreler */, L"7777", /* diğer parametreler */);

    // Yanlış (aralık dışında):
    // Initialize_Game(/* diğer parametreler */, L"0", /* diğer parametreler */); // Çok düşük
    // Initialize_Game(/* diğer parametreler */, L"65536", /* diğer parametreler */); // Çok yüksek
    // Initialize_Game(/* diğer parametreler */, L"-1", /* diğer parametreler */); // Negatif değer
    ```

### 3. Geçersiz Kullanıcı Adı (Boş veya Çok Uzun)

Oyuncunun **kullanıcı adı**, istemci tarafından kabul edilebilir olduğundan emin olmak için doğrulanır.

#### 3.1. Boş Kullanıcı Adı

![Error 4](../../screenshots/error_4.png)

- **Görüntülenen Hata Mesajı**: `"Nickname cannot be empty. Please provide a valid nickname."`
- **Neden**: `nickname` argümanı (`std::wstring_view`) boş bir dize olarak sağlandı.
- **Çözüm**: Kullanıcı adının boş olmadığından emin olun.
    ```cpp
    // Doğru:
    Initialize_Game(/* diğer parametreler */, L"İsim", /* diğer parametreler */);

    // Yanlış (boş):
    // Initialize_Game(/* diğer parametreler */, L"", /* diğer parametreler */);
    ```

#### 3.2. Çok Uzun Kullanıcı Adı

![Error 5](../../screenshots/error_5.png)

- **Görüntülenen Hata Mesajı**: `"Nickname length exceeds the maximum allowed of 23 characters. Please use a shorter nickname."`
- **Neden**: Sağlanan **kullanıcı adının** uzunluğu `Constants::MAX_NICKNAME_LENGTH` olan `23` karakteri aşıyor.
- **Çözüm**: En fazla `23` karakterden oluşan bir **kullanıcı adı** kullanın.
    ```cpp
    // Doğru:
    Initialize_Game(/* diğer parametreler */, L"İsim", /* diğer parametreler */);

    // Yanlış (çok uzun):
    // Initialize_Game(/* diğer parametreler */, L"BuKullanıcıAdıÇokUzunVeYirmiKarakteriAşıyor", /* diğer parametreler */);
    ```

### 4. Oyun veya DLL Dosyaları Bulunamadı

Bu, en yaygın başarısızlık nedenlerinden biridir. Kütüphane, `gta_sa.exe`, `samp.dll` ve **OMP** için `omp-client.dll` dosyalarının beklenen konumlarda olmasını gerektirir.

#### 4.1. Oyun Yürütülebilir Dosyası (`gta_sa.exe`) Bulunamadı

![Error 6](../../screenshots/error_6.png)

- **Görüntülenen Hata Mesajı**: `"Game executable not found. Please ensure 'gta_sa.exe' exists at the specified path: [tam yol]"`. `[tam yol]`, klasör ve dosya adını içerecektir.
- **Neden**: `folder` argümanında belirtilen klasörde `gta_sa.exe` dosyası bulunamadı.
- **Çözüm**:
  1. `folder` (`std::wstring_view`) öğesinin **GTA San Andreas**'ın doğru kurulum dizinine işaret ettiğinden emin olun.
  2. `gta_sa.exe` dosyasının bu klasörde mevcut olduğunu ve adının değiştirilmediğini doğrulayın.

#### 4.2. SA-MP Kütüphanesi (`samp.dll`) Bulunamadı

![Error 7](../../screenshots/error_7.png)

- **Görüntülenen Hata Mesajı**: `"SA-MP library not found. Please ensure 'samp.dll' exists at the specified path: [tam yol]"`.
- **Neden**: `folder` argümanında belirtilen klasörde `samp.dll` dosyası bulunamadı. Bu **DLL**, hem `samp` hem de `omp` enjeksiyon türleri için bir gerekliliktir.
- **Çözüm**: **GTA San Andreas** kurulum klasöründe `samp.dll` dosyasının mevcut olduğundan emin olun.

#### 4.3. OMP Kütüphanesi (`omp-client.dll`) Bulunamadı (yalnızca OMP enjeksiyonu için)

![Error 8](../../screenshots/error_8.png)

- **Görüntülenen Hata Mesajı**: `"OMP library not found. Please ensure 'omp-client.dll' exists at the specified path for OMP injection: [tam yol]"`.
- **Neden**: `L"omp"` enjeksiyon türü olarak belirtildi, ancak `folder` argümanında belirtilen klasörde `omp-client.dll` dosyası bulunamadı.
- **Çözüm**: En son **OMP** istemcisini indirin ve `omp-client.dll` (ve `samp.dll`) dosyasının **GTA San Andreas** kurulum klasöründe mevcut olduğundan emin olun.

### 5. Oyun Sürecinin Oluşturulmasında Hata

Bu, **işletim sistemi izinleri** ve `gta_sa.exe`'nin mevcut durumuyla ilgili daha karmaşık bir hatadır.

![Error 9](../../screenshots/error_9.png)

- **Görüntülenen Hata Mesajı**: `"Failed to create game process. Ensure 'gta_sa.exe' is not running and you have sufficient permissions to execute the file. System Error: [işletim sistemi hata mesajı]"`. Sistem mesajı `GetLastError()` tarafından eklenir (örneğin, `Access is denied.` veya `The requested operation requires elevation.`).
- **Neden**: `gta_sa.exe`'yi başlatmak için `CreateProcessA` çağrısı başarısız oldu. Yaygın nedenler şunlardır:
  - **Süreç zaten çalışıyor**: `gta_sa.exe`'nin bir örneği zaten aktif ve yeni bir yürütmeyi engelliyor.
  - **Yetersiz izinler**: Uygulamanız, belirli sistem yapılandırmalarında (**UAC** etkin, korumalı klasörler vb.) süreç oluşturmak için gerekli ayrıcalıklara sahip değil.
  - **Yürütülebilir dosya sorunları**: `gta_sa.exe` bozulmuş veya başka bir program tarafından engelleniyor olabilir (örneğin, yanlış yapılandırılmış bir antivirüs).
- **Çözüm**:
  1. Görev Yöneticisi'ni kontrol edin ve `gta_sa.exe`'nin çalışan bir örneği olmadığından emin olun. Varsa, bunu sonlandırın.
  2. Kütüphaneyi kullanan uygulamanızı **Yönetici** ayrıcalıklarıyla çalıştırın. Yürütülebilir dosyaya sağ tıklayın ve **"Yönetici olarak çalıştır"** seçeneğini seçin.
  3. Bir **antivirüs** veya **güvenlik yazılımı** müdahale ediyorsa, uygulamanızı ve/veya **GTA:SA** klasörünü antivirüs istisnalarına ekleyin (dosyalarınızın bütünlüğünden emin olarak dikkatli bir şekilde yapın).

### 6. Hedef Süreçte Bellek Ayırmada Hata

Kütüphane, **DLL yolunu** kopyalamak için `gta_sa.exe` içinde küçük bir bellek alanı ayırmaya çalışır.

![Error 10](../../screenshots/error_10.png)

- **Görüntülenen Hata Mesajı**: `"Failed to allocate memory in the target process. This might be due to insufficient permissions or process protection mechanisms."`
- **Neden**: Uzak süreçte bellek ayırmak için kullanılan `VirtualAllocEx` işlevi başarısız oldu. Bu, aşağıdakilerden kaynaklanabilir:
  - **GTA:SA** süreci (askıya alınmış durumda olsa bile), dış süreçler tarafından bellek ayırmayı engelleyen güvenlik savunmalarına veya **enjeksiyon karşıtı yamalar**a sahip.
  - Uygulamanız, başka bir sürecin belleğini manipüle etmek için gerekli yükseltilmiş izinlere sahip değil.
  - (Daha az yaygın) Sistemde aşırı sanal bellek kıtlığı var.
- **Çözüm**:
  1. Uygulamanızı **Yönetici** ayrıcalıklarıyla çalıştırın.
  2. Oyunun, enjeksiyon veya bellek manipülasyonu girişimlerini engelleyebilecek herhangi bir modifikasyon veya **güvenlik yaması** olmadığından emin olun (bu, değiştirilmiş ortamlar veya bazı üçüncü taraf hile önleme araçlarında daha yaygındır).

### 7. İşlem Belleğine DLL Yolunun Yazılmasında Hata

Bellek ayrıldıktan sonra, kütüphane **DLL yolunu** buraya kopyalamaya çalışır.

![Error 11](../../screenshots/error_11.png)

- **Görüntülenen Hata Mesajı**: `"Failed to write DLL path to the target process memory. Verify process permissions and ensure the DLL path is accessible."`
- **Neden**: `WriteProcessMemory` fonksiyonu, **DLL yolunun baytlarını** `gta_sa.exe` içinde ayrılan uzak belleğe kopyalamaya çalışırken başarısız oldu. Bu genellikle şu durumlara işaret eder:
  - **Yazma İzinleri**: Uygulamanız, bu bellek bölgesine veya **GTA:SA** işlemine yazma iznine sahip değil.
  - **Geçersiz Handle**: İşlemin **handle**'ı (`process_handle`), ayırma ve yazma arasında bir şekilde geçersiz hale geldi; bu, `UniqueResource` kullanımı nedeniyle çok nadirdir ancak sistemin aşırı koşullarında gerçekleşebilir.
  - **Bellek Koruma Sorunları**: İşletim sistemi (**SO**) veya oyunun modifikasyonlarından kaynaklanan bir bellek koruma mekanizması yazmayı engelledi.
- **Çözüm**: Uygulamayı **Yönetici** olarak çalıştırın. `gta_sa.exe` ve ortamının, bellek işlemlerini engelleyebilecek araçlardan "temiz" olduğundan emin olun.

### 8. Temel Sistem Fonksiyonlarının Bulunmasında Hata

Bunlar, **Windows**'un kritik **API**'leridir; buradaki hatalar, işletim sistemi veya yürütme ortamıyla ilgili temel bir sorunu işaret eder.

#### 8.1. `kernel32.dll` Bulunamadı

![Error 12](../../screenshots/error_12.png)

- **Görüntülenen Hata Mesajı**: `"Failed to obtain a handle to kernel32.dll. This is an essential system library and this error indicates a severe system issue."`
- **Neden**: `kernel32.dll`, **Windows**'un en temel **DLL**'lerinden biridir ve `CreateProcess`, `VirtualAllocEx` gibi temel fonksiyonları içerir. Eğer `GetModuleHandleA`, bu DLL için bir **handle** elde edemezse, işletim sistemi çok ciddi sorunlarla karşı karşıyadır.
- **Çözüm**: Bu, kütüphane veya uygulamanızdan kaynaklanan bir hata olmaktan ziyade **kritik** bir hatadır. Sistem dosyalarında bozulma, **Windows** ile ilgili ciddi sorunlar veya oldukça alışılmadık bir **SO** kurulumu olduğunu gösterir. Sistem bütünlüğünü kontrol etmek için (**Komut İstemi**'nde **Yönetici** olarak `sfc /scannow` komutunu çalıştırmak) veya son çare olarak **Windows**'u yeniden yüklemek önerilir.

#### 8.2. `LoadLibraryA` Bulunamadı

![Error 13](../../screenshots/error_13.png)

- **Görüntülenen Hata Mesajı**: `"Failed to find the address of the LoadLibraryA function in kernel32.dll. This is critical for injecting the DLL."`
- **Neden**: `kernel32.dll` bulunmuş olsa da, `LoadLibraryA` fonksiyonu `GetProcAddress` ile çözülemedi. Bu, son derece nadir olsa da, `kernel32.dll` **DLL dosyasının** bozulması veya oldukça standart dışı bir yürütme ortamından kaynaklanabilir.
- **Çözüm**: Yukarıdaki `kernel32.dll` hatasına benzer şekilde, bu da işletim sisteminde ciddi bir sorunu işaret eder.

### 9. Enjeksiyon için Uzak Thread Oluşturmada Hata

Uzak ortam hazırlandıktan ve **DLL yolu** kopyalandıktan sonra, `LoadLibraryA`'yı "çağırmak" için oyunun işleminde yeni bir **thread** oluşturulur.

![Error 14](../../screenshots/error_14.png)

- **Görüntülenen Hata Mesajı**: `"Failed to create a remote thread in the target process to execute the DLL injection. This could be due to security restrictions or process state. System Error: [İşletim sistemi hata mesajı]"`.
- **Neden**: `CreateRemoteThread` çağrısı başarısız oldu. Bu hata, güçlü **enjeksiyon karşıtı** savunmalara sahip sistemlerde veya bir programın işlemin davranışını yoğun bir şekilde izlediği durumlarda yaygın olabilir:
  - **Güvenlik Mekanizmaları**: **Hile karşıtı** araçlar, **güvenlik yazılımları** veya belirli **Windows** politikaları, üçüncü taraf işlemlerinde **thread** oluşturma girişimlerini tespit edip engelleyebilir.
  - **Hedef İşlem Tutarsızlığı**: **GTA:SA** işlemi, `CREATE_SUSPENDED` durumunda başlatılmış olsa da beklenmedik veya kararsız bir durumda olabilir, bu da **thread** oluşturma yeteneğini etkileyebilir.
- **Çözüm**:
  1. Uygulamanızı **Yönetici** ayrıcalıklarıyla çalıştırın.
  2. **Hile karşıtı araçlar**, **agresif antivirüsler** veya işlem manipülasyonunu denetleyen ve engelleyen **güvenlik duvarlarının** olup olmadığını kontrol edin. Uygulamanızı ve `gta_sa.exe`'yi, varsa istisnalara ekleyin (dikkatli bir şekilde).
  3. Sistem hata mesajı (`GetLastError()`) belirli bir neden hakkında ek bilgiler sağlayabilir (örneğin: **"Bir işlem, diğer işlemler için thread oluşturma erişimine reddedildi."**).

### 10. Enjeksiyonun Tamamlanmasında Zaman Aşımı veya Hata

Uzak **thread** oluşturulduktan sonra, enjektör, **DLL yüklemesinin** tamamlanmasını bekler.

![Error 15](../../screenshots/error_15.png)

- **Görüntülenen Hata Mesajı**: `"Timeout or error waiting for DLL injection to complete. System Error: [İşletim sistemi hata mesajı]"`.
- **Neden**: `LoadLibraryA`'yı çalıştıran uzak **thread**, `Constants::DLL_INJECTION_TIMEOUT_MS` (10 saniye) süresinden fazla zaman aldı veya başarısız oldu ve `GetExitCodeThread` 0 döndürdü. Olası nedenler şunlardır:
  - **Enjekte Edilen DLL'deki Sorunlar**: `samp.dll` veya `omp-client.dll` içindeki `DllMain`, çok uzun sürüyor, bir **sonsuz döngü**, **çökme** içeriyor veya **DLL'nin** düzgün yüklenmesini engelleyen bir hata var (örneğin: eksik **DLL bağımlılıkları**).
  - **Sessiz Engelleme**: Bir güvenlik mekanizması, `LoadLibraryA`'yı engellemiş olabilir ancak açık bir **thread** oluşturma hatası bildirmedi.
- **Çözüm**:
  1. `samp.dll` ve `omp-client.dll` dosyalarının bütünlüğünü kontrol edin. Bunlar bozulmuş veya `gta_sa.exe` ile uyumsuz bir sürüm olabilir.
  2. **Enjekte edilen DLL**'nin, sistemde eksik veya erişilemeyen **diğer DLL'lere** bağımlı olmadığından emin olun.

### 11. Oyun İşlemi Thread'inin Devam Ettirilmesinde Hata

Bu, **DLL'ler** enjekte edildikten sonra oyunu başlatmak için son adımdır.

![Error 16](../../screenshots/error_16.png)

- **Görüntülenen Hata Mesajı**: `"Failed to resume the game process thread: [İşletim sistemi hata mesajı]"`.
- **Neden**: `ResumeThread` çağrısı başarısız oldu, yani `gta_sa.exe`'nin ana **thread**'i, oyunun yürütülmesini başlatmak için etkinleştirilemedi. Bu nadir bir hatadır, ancak şu durumlarda gerçekleşebilir:
  - İşlemin **thread handle**'ı geçersiz hale geldi.
  - İşletim sistemi, güvenlik kesintisi veya işlemin tutarsız durumu nedeniyle devam etmeyi engelledi.
  - İşlem, **DLL enjeksiyonu** ile ana **thread**'in devam ettirilmesi girişimi arasında harici olarak sonlandırılmış olabilir.
- **Çözüm**: Eğer önceki tüm adımlar başarılı olduysa ve yalnızca `ResumeThread` başarısız olduysa, bu, işletim sistemi, **GTA:SA** kurulumu veya aşırı katı bir başka **güvenlik yazılımı** ile ilgili bir sorun olabilir. Hata öncesi ve sonrası `gta_sa.exe`'nin durumunu **Görev Yöneticisi** ile yeniden inceleyin. Bilgisayarı yeniden başlatmak, geçici sistem durumu sorunlarını çözebilir.

> [!TIP]
> Karmaşık hata ayıklama senaryolarında, **Process Monitor (Sysinternals Suite)** veya bir hata ayıklayıcı (örneğin **Visual Studio Debugger**, **WinDbg**, **OllyDbg**) gibi araçlar çok değerli olabilir. Bunlar, **API** çağrılarını gözlemlemeye, erişim hatalarını kontrol etmeye, **handle** durumlarını izlemeye ve hatta işlem belleğini incelemeye yardımcı olarak, perde arkasında neler olup bittiğine dair derinlemesine bir görüş sağlar.

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