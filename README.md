# limits

OpenWrt utility tool to display sizes of basic C data types and pointers for the router's target CPU architecture.

This project features automated package building for both **`.ipk`** (legacy format using `opkg` in OpenWrt <= 23.05) and **`.apk`** (modern format using `apk-tools` in OpenWrt 24.10 / 25.x / future releases) via GitHub Actions and the official OpenWrt SDK.

---

## 📁 Repository Structure

```text
.
├── .github/
│   └── workflows/
│       └── build.yml       # GitHub Actions workflow for building ipk and apk packages
├── limits/
│   ├── Makefile            # Main OpenWrt SDK package Makefile
│   └── src/
│       ├── Makefile        # Inner Makefile compiling the limits binary
│       └── limits.c        # C source code
├── LICENSE
├── README.md               # English documentation
└── README-pl.md            # Polish documentation
```

---

## 🚀 How GitHub Actions Automation Works

The workflow (`.github/workflows/build.yml`) is triggered in two ways:

1. **Automatically on Git tag push**:
   ```bash
   git tag v1.0.0
   git push origin v1.0.0
   ```
   Compiles packages for all configured architectures and publishes `.ipk` and `.apk` files to a GitHub Release.

2. **Manually via GitHub Actions (`workflow_dispatch`)**:
   - Go to the **Actions** tab -> **Build OpenWrt Package**.
   - Click **Run workflow**.
   - Choose a target architecture (e.g., `ramips-mt7621-23.05.3`) or `all`.
   - Built packages will be saved and downloadable under job **Artifacts**.

---

## 🎯 Target Architectures & Devices

| Target (OpenWrt SDK) | OpenWrt Version | Package Format | Example Devices | CPU Architecture |
|---|---|---|---|---|
| `ramips-mt7621-23.05.3` | OpenWrt 23.05 (stable) | `.ipk` | **Netgear R6220**, **Xiaomi Mi Router 4A Gigabit** | MIPS 1004Kc (`mipsel_24kc`) |
| `ramips-mt7621-25.12.2` | OpenWrt 25.12 (modern) | `.apk` | **Netgear R6220**, **Xiaomi Mi Router 4A Gigabit** | MIPS 1004Kc (`mipsel_24kc`) |
| `mediatek-filogic-23.05.3` | OpenWrt 23.05 (stable) | `.ipk` | **Cudy WR3000** (s, h, p variants), M3000, RE3000 | ARM Cortex-A53 64-bit (`aarch64_cortex-a53`) |
| `mediatek-filogic-25.12.2` | OpenWrt 25.12 (modern) | `.apk` | **Cudy WR3000** (s, h, p variants), M3000, RE3000 | ARM Cortex-A53 64-bit (`aarch64_cortex-a53`) |

> **Note**: In OpenWrt, packages are built per target architecture. Therefore, one `ramips-mt7621` binary runs on both Netgear R6220 and Xiaomi Mi 4A Gigabit, while one `mediatek-filogic` binary runs on all Cudy WR3000 series devices.

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
scp limits_1.0.0-1_mipsel_24kc.ipk root@192.168.1.1:/tmp/
ssh root@192.168.1.1
opkg install /tmp/limits_1.0.0-1_mipsel_24kc.ipk
```

### Installing `.apk` (OpenWrt >= 24.10, `apk`)
```bash
scp limits-1.0.0-r1.apk root@192.168.1.1:/tmp/
ssh root@192.168.1.1
apk add --allow-untrusted /tmp/limits-1.0.0-r1.apk
```

### Running the tool
Run the binary anywhere on the router:
```bash
limits
```
