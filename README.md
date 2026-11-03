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
│       └── typesizes.c     # C source code with bilingual Polish/English output
├── LICENSE
├── README.md               # English documentation
└── README-pl.md            # Polish documentation
```

---

## 🎯 Target Platforms & Generated Packages

Packages in GitHub Releases are named cleanly using the target platform name (**`typesizes_<target>.<ext>`**):

| Release File Name | OpenWrt Target | Format | OpenWrt Release | Supported Hardware / Devices | CPU Architecture |
|---|---|---|---|---|---|
| **`typesizes_ramips-mt7621.ipk`** | `ramips-mt7621` | `.ipk` (opkg) | OpenWrt 23.05 (stable) | **Netgear R6220**, **Xiaomi Mi Router 4A Gigabit** | MIPS 1004Kc (`mipsel_24kc`) |
| **`typesizes_ramips-mt7621.apk`** | `ramips-mt7621` | `.apk` (apk) | OpenWrt 25.12 (modern) | **Netgear R6220**, **Xiaomi Mi Router 4A Gigabit** | MIPS 1004Kc (`mipsel_24kc`) |
| **`typesizes_mediatek-filogic.apk`** | `mediatek-filogic` | `.apk` (apk) | OpenWrt 25.12 (modern) | **Cudy WR3000** (s, h, p), M3000, RE3000 | ARM Cortex-A53 64-bit |
| **`typesizes_ath79-generic.ipk`** | `ath79-generic` | `.ipk` (opkg) | OpenWrt 23.05 (stable) | Classic TP-Link routers (Archer C7, TL-WR1043ND, etc.) | MIPS 24Kc / 74Kc (`mips_24kc`) |
| **`typesizes_ath79-generic.apk`** | `ath79-generic` | `.apk` (apk) | OpenWrt 25.12 (modern) | Classic TP-Link routers | MIPS 24Kc / 74Kc (`mips_24kc`) |
| **`typesizes_x86-64.apk`** | `x86-64` | `.apk` (apk) | OpenWrt 25.12 (modern) | x86_64 PCs, mini-PCs, Proxmox, VMware, VirtualBox | AMD64 / Intel 64-bit |
| **`typesizes_qualcommax-ipq807x.apk`** | `qualcommax-ipq807x`| `.apk` (apk) | OpenWrt 25.12 (modern) | Qualcomm Wi-Fi 6 routers (Xiaomi AX3600, AX9000, etc.) | ARM Cortex-A53 64-bit |
| **`typesizes_qualcommax-ipq60xx.apk`** | `qualcommax-ipq60xx`| `.apk` (apk) | OpenWrt 25.12 (modern) | Qualcomm Wi-Fi 6 IPQ60xx devices | ARM Cortex-A53 64-bit |
| **`typesizes_bcm27xx-bcm2711.apk`** | `bcm27xx-bcm2711` | `.apk` (apk) | OpenWrt 25.12 (modern) | Raspberry Pi 4 | ARM Cortex-A72 64-bit |

---

## 🚀 How GitHub Actions Automation Works

The workflow (`.github/workflows/build.yml`) is triggered in two ways:

1. **Automatically on Git tag push**:
   ```bash
   git tag v1.0.0
   git push origin v1.0.0
   ```
   Compiles packages for all configured architectures and publishes all generated `.ipk` and `.apk` files to the GitHub Release.

2. **Manually via GitHub Actions (`workflow_dispatch`)**:
   - Go to the **Actions** tab -> **Build OpenWrt Package**.
   - Click **Run workflow**.
   - Choose a target architecture or `all`.
   - Built packages will be saved and downloadable under job **Artifacts**.

---

## 🔧 How to Add New Targets or OpenWrt Releases (e.g., 26.xx)

All targets are configured in `.github/workflows/build.yml`.

### 1. SDK Name Format
The `ARCH` parameter corresponds to:
`[target]-[subtarget]-[version]`

You can check available Docker SDK tags at: [hub.docker.com/r/openwrt/sdk/tags](https://hub.docker.com/r/openwrt/sdk/tags).

### 2. Update `.github/workflows/build.yml`
1. Add the new entry to `workflow_dispatch -> inputs -> target_arch -> options`.
2. Add the new string to `ALL_ARCHES` in the `set-matrix` step.

---

## 📦 Installation & Usage

### Installing `.ipk` (OpenWrt <= 23.05, `opkg`)
```bash
scp typesizes_ramips-mt7621.ipk root@192.168.1.1:/tmp/
ssh root@192.168.1.1
opkg install /tmp/typesizes_ramips-mt7621.ipk
```

### Installing `.apk` (OpenWrt >= 24.10, `apk`)
```bash
scp typesizes_mediatek-filogic.apk root@192.168.1.1:/tmp/
ssh root@192.168.1.1
apk add --allow-untrusted /tmp/typesizes_mediatek-filogic.apk
```

### Running the tool
Run the binary anywhere on the router:
```bash
typesizes
```
*(The tool prints in English by default, or in Polish if `LANG` or `LC_ALL` is set to Polish).*
