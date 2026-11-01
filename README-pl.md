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

## 🎯 Pliki wyjściowe i architektury CPU

W OpenWrt pakiety binarne są kompilowane pod **architekturę procesora (CPU Architecture)**. Dzięki temu jeden plik binarny pasuje do wszystkich urządzeń opartych na danej architekturze.

W wyniku automatycznego budowania (Release) powstają **4 gotowe pliki pakietów**:

| Nazwa pliku w Release | Architektura CPU | Format | Wydanie OpenWrt | Obsługiwane routery |
|---|---|---|---|---|
| **`limits_1.0.0-1_mipsel_24kc.ipk`** | `mipsel_24kc` (ramips/mt7621) | `.ipk` (opkg) | OpenWrt 23.05 (stabilna) | **Netgear R6220**, **Xiaomi Mi Router 4A Gigabit** |
| **`limits-1.0.0-r1_mipsel_24kc.apk`** | `mipsel_24kc` (ramips/mt7621) | `.apk` (apk) | OpenWrt 25.12 (nowoczesna) | **Netgear R6220**, **Xiaomi Mi Router 4A Gigabit** |
| **`limits_1.0.0-1_aarch64_cortex-a53.ipk`** | `aarch64_cortex-a53` (filogic) | `.ipk` (opkg) | OpenWrt 23.05 (stabilna) | **Cudy WR3000** (warianty s, h, p), Cudy M3000, RE3000 |
| **`limits-1.0.0-r1_aarch64_cortex-a53.apk`** | `aarch64_cortex-a53` (filogic) | `.apk` (apk) | OpenWrt 25.12 (nowoczesna) | **Cudy WR3000** (warianty s, h, p), Cudy M3000, RE3000 |

### Dlaczego nazwy to `mipsel_24kc` i `aarch64_cortex-a53`?
- **`mipsel_24kc`**: procesor MediaTek MT7621 to 32-bitowy rdzeń MIPS 1004Kc (little-endian). Jest to standardowa nazwa architektury w OpenWrt dla takich urządzeń jak Netgear R6220 oraz Xiaomi Mi Router 4A Gigabit.
- **`aarch64_cortex-a53`**: procesor MediaTek Filogic 820 / MT7981B w routerach Cudy WR3000 to 64-bitowy procesor ARM Cortex-A53.
- Pliki `.ipk` generują ten sufiks domyślnie w OpenWrt SDK. Dla plików `.apk` workflow automatycznie dopisuje nazwę architektury, aby zapobiec nadpisaniu plików w GitHub Releases.

---

## 🚀 Jak działa automatyczne budowanie (GitHub Actions)

Workflow (`.github/workflows/build.yml`) jest wyzwalany na dwa sposoby:

1. **Automatycznie po dodaniu i wypchnięciu nowego tagu do repozytorium**:
   ```bash
   git tag v1.0.0
   git push origin v1.0.0
   ```
   Kompilowane są pakiety dla wszystkich skonfigurowanych architektur, a komplet 4 plików `.ipk` i `.apk` zostaje opublikowany w sekcji **Releases** na GitHubie.

2. **Ręcznie przez GitHub Actions (`workflow_dispatch`)**:
   - W repozytorium przejdź do zakładki **Actions** -> **Build OpenWrt Package**.
   - Kliknij przycisk **Run workflow**.
   - Z listy rozwijanej wybierz konkretną architekturę (np. `ramips-mt7621-23.05.3`) lub opcję `all` (wszystkie).
   - Skompilowane pliki będą dostępne do pobrania jako **Artifacts** danego uruchomienia.

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
- `qualcommax-ipq807x-24.10.0` (dla routerów na procesorach Qualcomm Wi-Fi 6)

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
scp limits-1.0.0-r1_mipsel_24kc.apk root@192.168.1.1:/tmp/
```
Zaloguj się przez SSH i zainstaluj:
```bash
ssh root@192.168.1.1
apk add --allow-untrusted /tmp/limits-1.0.0-r1_mipsel_24kc.apk
```

### 3. Uruchomienie programu
Po instalacji program jest dostępny w ścieżce systemowej jako `/usr/bin/limits`. Wystarczy wpisać:
```bash
limits
```

Przykładowy wynik programu dla architektury 32-bitowej (`mipsel_24kc` - Netgear R6220 / Xiaomi 4A Gigabit):
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

Przykładowy wynik programu dla architektury 64-bitowej (`aarch64_cortex-a53` - Cudy WR3000):
```text
=== Rozmiary podstawowe ===
Rozmiar short:       2 bajt(y)
Rozmiar int:         4 bajt(y)
Rozmiar long:        8 bajt(y)
Rozmiar float:       4 bajt(y)
Rozmiar long long:   8 bajt(y)
Rozmiar double:      8 bajt(y)
Rozmiar long double: 16 bajt(y)
Rozmiar ptrdiff_t:   8 bajt(y)
Rozmiar char:        1 bajt(y)
Rozmiar wskaznika:   8 bajt(y)
Rozmiar size_t:      8 bajt(y)
Rozmiar bool:        1 bajt(y)
```
