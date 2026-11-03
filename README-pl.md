# typesizes

Narzędzie dla OpenWrt wyświetlające rozmiary podstawowych typów danych w C oraz wskaźników dla architektury procesora danego routera.

Projekt zawiera w pełni zautomatyzowany proces budowania pakietów w formatach **`.ipk`** (dla OpenWrt z menedżerem pakietów `opkg`) oraz **`.apk`** (dla nowszych wydań OpenWrt z menedżerem `apk-tools`) przy użyciu GitHub Actions oraz oficjalnego OpenWrt SDK.

---

## 📁 Struktura repozytorium

```text
.
├── .github/
│   └── workflows/
│       └── build.yml       # Konfiguracja GitHub Actions budująca pakiety ipk i apk
├── typesizes/
│   ├── Makefile            # Główny Makefile pakietu dla OpenWrt SDK
│   └── src/
│       ├── Makefile        # Wewnętrzny Makefile kompilujący program typesizes
│       └── typesizes.c     # Kod źródłowy w C z obsługą języka angielskiego i polskiego
├── LICENSE
├── README.md               # Dokumentacja w języku angielskim
└── README-pl.md            # Dokumentacja w języku polskim
```

---

## 🎯 Obsługiwane platformy i nazwy pakietów

Pakiety w sekcji GitHub Releases są nazywane jednoznacznie według platformy docelowej (**`typesizes_<target>.<ext>`**):

| Nazwa pliku w Release | Target OpenWrt | Format | Wydanie OpenWrt | Obsługiwane routery / urządzenia | Architektura CPU |
|---|---|---|---|---|---|
| **`typesizes_ramips-mt7621.ipk`** | `ramips-mt7621` | `.ipk` (opkg) | OpenWrt 23.05 (stabilna) | **Netgear R6220**, **Xiaomi Mi Router 4A Gigabit** | MIPS 1004Kc (`mipsel_24kc`) |
| **`typesizes_ramips-mt7621.apk`** | `ramips-mt7621` | `.apk` (apk) | OpenWrt 25.12 (nowoczesna) | **Netgear R6220**, **Xiaomi Mi Router 4A Gigabit** | MIPS 1004Kc (`mipsel_24kc`) |
| **`typesizes_mediatek-filogic.apk`** | `mediatek-filogic` | `.apk` (apk) | OpenWrt 25.12 (nowoczesna) | **Cudy WR3000** (warianty s, h, p), Cudy M3000, RE3000 | ARM Cortex-A53 64-bit |
| **`typesizes_ath79-generic.ipk`** | `ath79-generic` | `.ipk` (opkg) | OpenWrt 23.05 (stabilna) | Klasyczne routery TP-Link (Archer C7, TL-WR1043ND itp.) | MIPS 24Kc / 74Kc (`mips_24kc`) |
| **`typesizes_ath79-generic.apk`** | `ath79-generic` | `.apk` (apk) | OpenWrt 25.12 (nowoczesna) | Klasyczne routery TP-Link | MIPS 24Kc / 74Kc (`mips_24kc`) |
| **`typesizes_x86-64.apk`** | `x86-64` | `.apk` (apk) | OpenWrt 25.12 (nowoczesna) | Komputery PC x86_64, mini-PC, Proxmox, VMware, VirtualBox | AMD64 / Intel 64-bit |
| **`typesizes_qualcommax-ipq807x.apk`** | `qualcommax-ipq807x` | `.apk` (apk) | OpenWrt 25.12 (nowoczesna) | Routery Qualcomm Wi-Fi 6 (Xiaomi AX3600, AX9000 itp.) | ARM Cortex-A53 64-bit |
| **`typesizes_qualcommax-ipq60xx.apk`** | `qualcommax-ipq60xx` | `.apk` (apk) | OpenWrt 25.12 (nowoczesna) | Urządzenia Qualcomm Wi-Fi 6 IPQ60xx | ARM Cortex-A53 64-bit |
| **`typesizes_bcm27xx-bcm2711.apk`** | `bcm27xx-bcm2711` | `.apk` (apk) | OpenWrt 25.12 (nowoczesna) | Raspberry Pi 4 | ARM Cortex-A72 64-bit |

---

## 🚀 Jak działa automatyczne budowanie (GitHub Actions)

Workflow (`.github/workflows/build.yml`) jest wyzwalany na dwa sposoby:

1. **Automatycznie po dodaniu i wypchnięciu nowego tagu do repozytorium**:
   ```bash
   git tag v1.0.0
   git push origin v1.0.0
   ```
   Kompilowane są pakiety dla wszystkich skonfigurowanych architektur, a komplet gotowych plików `.ipk` i `.apk` zostaje opublikowany w sekcji **Releases** na GitHubie.

2. **Ręcznie przez GitHub Actions (`workflow_dispatch`)**:
   - W repozytorium przejdź do zakładki **Actions** -> **Build OpenWrt Package**.
   - Kliknij przycisk **Run workflow**.
   - Z listy rozwijanej wybierz konkretną platformę lub opcję `all` (wszystkie).
   - Skompilowane pliki będą dostępne do pobrania jako **Artifacts** danego uruchomienia.

---

## 🔧 Jak dodać nową platformę lub nową wersję OpenWrt (np. 26.xx)?

Wszystkie definicje platform znajdują się w pliku `.github/workflows/build.yml`. Aby dodać nową architekturę lub nową wersję OpenWrt, wystarczy edytować ten plik w dwóch miejscach:

### 1. Format nazwy SDK
Format parametru `ARCH` dla kontenerów OpenWrt SDK to:
`[target]-[subtarget]-[wersja]`

Przykłady:
- `ramips-mt7621-26.01.0` (dla przyszłego wydania 26.xx na MT7621)
- `x86-64-26.01.0` (dla przyszłego wydania na x86_64)

Dostępne tagi kontenerów SDK można sprawdzić w oficjalnym rejestrze Docker Hub: [hub.docker.com/r/openwrt/sdk/tags](https://hub.docker.com/r/openwrt/sdk/tags).

### 2. Edycja `.github/workflows/build.yml`
1. Dodaj nową pozycję do listy wyboru w sekcji `workflow_dispatch -> inputs -> target_arch -> options`.
2. Dodaj nową wartość do listy `ALL_ARCHES` w kroku `set-matrix`.

---

## 📦 Jak zainstalować i uruchomić pakiet na routerze?

### 1. Instalacja pakietu `.ipk` (OpenWrt <= 23.05, menedżer `opkg`)
Prześlij plik `.ipk` na router (np. przez `scp`):
```bash
scp typesizes_ramips-mt7621.ipk root@192.168.1.1:/tmp/
```
Zaloguj się przez SSH na router i zainstaluj:
```bash
ssh root@192.168.1.1
opkg install /tmp/typesizes_ramips-mt7621.ipk
```

### 2. Instalacja pakietu `.apk` (OpenWrt 24.10 / 25.x / nowsze, menedżer `apk`)
Prześlij plik `.apk` na router:
```bash
scp typesizes_mediatek-filogic.apk root@192.168.1.1:/tmp/
```
Zaloguj się przez SSH i zainstaluj:
```bash
ssh root@192.168.1.1
apk add --allow-untrusted /tmp/typesizes_mediatek-filogic.apk
```

### 3. Uruchomienie programu
Po instalacji program jest dostępny w ścieżce systemowej jako `/usr/bin/typesizes`. Wystarczy wpisać:
```bash
typesizes
```
Program automatycznie wykrywa język polski w zmiennych `LANG` / `LC_ALL`, a domyślnie wypisuje informacje po angielsku.
