# typesizes

OpenWrt utility tool to display sizes of basic C data types and pointers for the router's target CPU architecture.

This project features automated package building for both **`.ipk`** (legacy format using `opkg` in OpenWrt <= 23.05) and **`.apk`** (modern format using `apk-tools` in OpenWrt 24.10 / 25.x / future releases) via GitHub Actions and the official OpenWrt SDK.

---

## 📁 Repository Structure

```text
.
├── .github/
│   └── workflows/
│       └── build.yml       # GitHub Actions workflow for building ipk and apk packages
├── typesizes/
│   ├── Makefile            # Main OpenWrt SDK package Makefile
│   └── src/
│       ├── Makefile        # Inner Makefile compiling the typesizes binary
│       └── typesizes.c     # C source code
├── LICENSE
├── README.md               # English documentation
└── README-pl.md            # Polish documentation
```

---

## 🎯 Target Architectures & Generated Packages

In OpenWrt, binary packages are built against the **CPU architecture**. A single compiled binary runs on all devices sharing the same architecture.

The GitHub Actions workflow produces **4 package files** in the Release:

| Release File Name | CPU Architecture | Format | OpenWrt Release | Supported Devices |
|---|---|---|---|---|
| **`typesizes_1.0.0-1_mipsel_24kc.ipk`** | `mipsel_24kc` (ramips/mt7621) | `.ipk` (opkg) | OpenWrt 23.05 (stable) | **Netgear R6220**, **Xiaomi Mi Router 4A Gigabit** |
| **`typesizes-1.0.0-r1_mipsel_24kc.apk`** | `mipsel_24kc` (ramips/mt7621) | `.apk` (apk) | OpenWrt 25.12 (modern) | **Netgear R6220**, **Xiaomi Mi Router 4A Gigabit** |
| **`typesizes_1.0.0-1_aarch64_cortex-a53.ipk`** | `aarch64_cortex-a53` (filogic) | `.ipk` (opkg) | OpenWrt 23.05 (stable) | **Cudy WR3000** (s, h, p), M3000, RE3000 |
| **`typesizes-1.0.0-r1_aarch64_cortex-a53.apk`** | `aarch64_cortex-a53` (filogic) | `.apk` (apk) | OpenWrt 25.12 (modern) | **Cudy WR3000** (s, h, p), M3000, RE3000 |

### Why `mipsel_24kc` and `aarch64_cortex-a53`?
- **`mipsel_24kc`**: The MediaTek MT7621 SoC features a 32-bit MIPS 1004Kc CPU core (little-endian). This is standard OpenWrt architecture naming.
- **`aarch64_cortex-a53`**: The MediaTek Filogic 820 / MT7981B SoC in Cudy WR3000 series features a 64-bit ARM Cortex-A53 CPU.
- OpenWrt SDK automatically includes the architecture in `.ipk` filenames. For `.apk` files, our workflow appends the architecture suffix so both `.apk` files can coexist in GitHub Releases without overwriting each other.

---

## 🚀 How GitHub Actions Automation Works

The workflow (`.github/workflows/build.yml`) is triggered in two ways:

1. **Automatically on Git tag push**:
   ```bash
   git tag v1.0.0
   git push origin v1.0.0
   ```
   Compiles packages for all configured architectures and publishes all 4 `.ipk` and `.apk` files to the GitHub Release.

2. **Manually via GitHub Actions (`workflow_dispatch`)**:
   - Go to the **Actions** tab -> **Build OpenWrt Package**.
   - Click **Run workflow**.
   - Choose a target architecture (e.g., `ramips-mt7621-23.05.3`) or `all`.
   - Built packages will be saved and downloadable under job **Artifacts**.

---

## 🔧 How to Add New Architectures or New OpenWrt Releases (e.g., 26.xx)

All targets are configured in `.github/workflows/build.yml`.

### 1. SDK Name Format
The `ARCH` parameter corresponds to:
`[target]-[subtarget]-[version]`

Examples:
- `ramips-mt7621-26.01.0` (for a future 26.xx release)
- `x86-64-23.05.3` (for x86_64 PCs / VMs)
- `ath79-generic-23.05.3` (for Qualcomm Atheros MIPS devices)

You can check available Docker SDK tags at: [hub.docker.com/r/openwrt/sdk/tags](https://hub.docker.com/r/openwrt/sdk/tags).

### 2. Update `.github/workflows/build.yml`

In `.github/workflows/build.yml`:
1. Add the new entry to `workflow_dispatch -> inputs -> target_arch -> options`.
2. Add the new string to `ALL_ARCHES` in the `set-matrix` step.

---

## 📦 Installation & Usage

### Installing `.ipk` (OpenWrt <= 23.05, `opkg`)
```bash
scp typesizes_1.0.0-1_mipsel_24kc.ipk root@192.168.1.1:/tmp/
ssh root@192.168.1.1
opkg install /tmp/typesizes_1.0.0-1_mipsel_24kc.ipk
```

### Installing `.apk` (OpenWrt >= 24.10, `apk`)
```bash
scp typesizes-1.0.0-r1_mipsel_24kc.apk root@192.168.1.1:/tmp/
ssh root@192.168.1.1
apk add --allow-untrusted /tmp/typesizes-1.0.0-r1_mipsel_24kc.apk
```

### Running the tool
Run the binary anywhere on the router:
```bash
typesizes
```
