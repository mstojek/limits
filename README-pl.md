# limits

Narzędzie dla OpenWrt wyświetlające rozmiary podstawowych typów danych w C oraz wskaźników dla architektury procesora danego routera.

Projekt zawiera w pełni zautomatyzowany proces budowania pakietów w formatach **`.ipk`** (dla OpenWrt z menedżerem pakietów `opkg`) oraz **`.apk`** (dla nowszych wydań OpenWrt z menedżerem `apk-tools`) przy użyciu GitHub Actions oraz oficjalnego OpenWrt SDK.

---

## 📁 Struktura repozytorium

```text
.
├── .github/
│   └── workflows/
│       └── build.yml       # Konfiguracja GitHub Actions budująca pakiety ipk i apk
├── limits/
│   ├── Makefile            # Główny Makefile pakietu dla OpenWrt SDK
│   └── src/
│       ├── Makefile        # Wewnętrzny Makefile kompilujący program limits
│       └── limits.c        # Kod źródłowy w języku C
├── LICENSE
├── README.md               # Dokumentacja w języku angielskim
└── README-pl.md            # Dokumentacja w języku polskim
```

---

## 🚀 Jak działa automatyczne budowanie (GitHub Actions)

Workflow (`.github/workflows/build.yml`) jest wyzwalany na dwa sposoby:

1. **Automatycznie po dodaniu i wypchnięciu nowego tagu do repozytorium**:
   ```bash
   git tag v1.0.0
   git push origin v1.0.0
   ```
   Kompilowane są pakiety dla wszystkich skonfigurowanych architektur, a gotowe pliki `.ipk` i `.apk` zostają opublikowane w sekcji **Releases** na GitHubie.

2. **Ręcznie przez GitHub Actions (`workflow_dispatch`)**:
   - W repozytorium przejdź do zakładki **Actions** -> **Build OpenWrt Package**.
   - Kliknij przycisk **Run workflow**.
   - Z listy rozwijanej wybierz konkretną architekturę (np. `ramips-mt7621-23.05.3`) lub opcję `all` (wszystkie).
   - Skompilowane pliki będą dostępne do pobrania jako **Artifacts** danego uruchomienia.

---

## 🎯 Obsługiwane architektury i urządzenia

| Cel (Target OpenWrt SDK) | Wersja OpenWrt | Format pakietu | Przykładowe urządzenia / modele | Architektura procesora |
|---|---|---|---|---|
| `ramips-mt7621-23.05.3` | OpenWrt 23.05 (stabilna) | `.ipk` | **Netgear R6220**, **Xiaomi Mi Router 4A Gigabit** | MIPS 1004Kc (`mipsel_24kc`) |
| `ramips-mt7621-25.12.2` | OpenWrt 25.12 (nowoczesna) | `.apk` | **Netgear R6220**, **Xiaomi Mi Router 4A Gigabit** | MIPS 1004Kc (`mipsel_24kc`) |
| `mediatek-filogic-23.05.3` | OpenWrt 23.05 (stabilna) | `.ipk` | **Cudy WR3000** (warianty s, h, p), Cudy M3000, RE3000 itp. | ARM Cortex-A53 64-bit (`aarch64_cortex-a53`) |
| `mediatek-filogic-25.12.2` | OpenWrt 25.12 (nowoczesna) | `.apk` | **Cudy WR3000** (warianty s, h, p), Cudy M3000, RE3000 itp. | ARM Cortex-A53 64-bit (`aarch64_cortex-a53`) |

> **Uwaga**: W OpenWrt pakiety binarne są kompilowane pod architekturę procesora/target. Dzięki temu jeden pakiet `ramips-mt7621` pasuje jednocześnie do routera Netgear R6220 oraz Xiaomi 4A Gigabit, a pakiet `mediatek-filogic` pasuje do całej rodziny urządzeń Cudy WR3000.

---

## 🔧 Jak dodać nową architekturę lub nową wersję OpenWrt (np. 26.xx)?

Wszystkie definicje platform znajdują się w pliku `.github/workflows/build.yml`. Aby dodać nową architekturę lub nową wersję OpenWrt, wystarczy edytować ten plik w dwóch miejscach:

### 1. Format nazwy SDK
Format parametru `ARCH` dla kontenerów OpenWrt SDK to:
`[target]-[subtarget]-[wersja]`

Przykłady:
- `ramips-mt7621-26.01.0` (dla przyszłego wydania 26.xx na MT7621)
- `x86-64-23.05.3` (dla komputerów / maszyn wirtualnych x86_64)
- `ath79-generic-23.05.3` (dla starszych procesorów Qualcomm Atheros MIPS)
- `qualcommax-ipq807x-24.10.0` (dla nowoczesnych routerów na procesorach Qualcomm Wi-Fi 6)

Dostępne tagi kontenerów SDK można sprawdzić w oficjalnym rejestrze Docker Hub: [hub.docker.com/r/openwrt/sdk/tags](https://hub.docker.com/r/openwrt/sdk/tags).

### 2. Edycja `.github/workflows/build.yml`

W pliku `.github/workflows/build.yml`:

1. Dodaj nową pozycję do listy wyboru w sekcji `workflow_dispatch -> inputs -> target_arch -> options`:
   ```yaml
   options:
     - 'all'
     - 'ramips-mt7621-23.05.3'
     - 'ramips-mt7621-25.12.2'
     - 'mediatek-filogic-23.05.3'
     - 'mediatek-filogic-25.12.2'
     - 'ramips-mt7621-26.01.0'        # <--- Dodaj tutaj (np. nowa wersja)
     - 'x86-64-23.05.3'              # <--- Dodaj tutaj (np. nowa architektura)
   ```

2. Dodaj nową wartość do zmiennej `ALL_ARCHES` w kroku `set-matrix`:
   ```bash
   ALL_ARCHES='["ramips-mt7621-23.05.3", "ramips-mt7621-25.12.2", "mediatek-filogic-23.05.3", "mediatek-filogic-25.12.2", "ramips-mt7621-26.01.0", "x86-64-23.05.3"]'
   ```

Po zapisaniu zmian i wypchnięciu commita workflow natychmiast zacznie obsługiwać nowo dodaną architekturę!

---

## 📦 Jak zainstalować i uruchomić pakiet na routerze?

### 1. Instalacja pakietu `.ipk` (OpenWrt <= 23.05, menedżer `opkg`)
Prześlij plik `.ipk` na router (np. przez `scp`):
```bash
scp limits_1.0.0-1_mipsel_24kc.ipk root@192.168.1.1:/tmp/
```
Zaloguj się przez SSH na router i zainstaluj:
```bash
ssh root@192.168.1.1
opkg install /tmp/limits_1.0.0-1_mipsel_24kc.ipk
```

### 2. Instalacja pakietu `.apk` (OpenWrt 24.10 / 25.x / nowsze, menedżer `apk`)
Prześlij plik `.apk` na router:
```bash
scp limits-1.0.0-r1.apk root@192.168.1.1:/tmp/
```
Zaloguj się przez SSH i zainstaluj:
```bash
ssh root@192.168.1.1
apk add --allow-untrusted /tmp/limits-1.0.0-r1.apk
```

### 3. Uruchomienie programu
Po instalacji program jest dostępny w ścieżce systemowej jako `/usr/bin/limits`. Wystarczy wpisać:
```bash
limits
```

Przykładowy wynik programu:
```text
=== Rozmiary podstawowe ===
Rozmiar short:       2 bajt(y)
Rozmiar int:         4 bajt(y)
Rozmiar long:        4 bajt(y)
Rozmiar float:       4 bajt(y)
Rozmiar long long:   8 bajt(y)
Rozmiar double:      8 bajt(y)
Rozmiar long double: 8 bajt(y)
Rozmiar ptrdiff_t:   4 bajt(y)
Rozmiar char:        1 bajt(y)
Rozmiar wskaznika:   4 bajt(y)
Rozmiar size_t:      4 bajt(y)
Rozmiar bool:        1 bajt(y)
```
*(Na architekturze 64-bitowej, np. ARM64 w Cudy WR3000, `Rozmiar wskaznika`, `long` oraz `size_t` wyniosą 8 bajtów).*
