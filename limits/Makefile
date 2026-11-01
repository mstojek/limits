include $(TOPDIR)/rules.mk

PKG_NAME:=limits
PKG_VERSION:=1.0.0
PKG_RELEASE:=1
PKG_LICENSE:=MIT
PKG_LICENSE_FILES:=LICENSE

include $(INCLUDE_DIR)/package.mk

define Package/limits
  SECTION:=utils
  CATEGORY:=Utilities
  TITLE:=Data type and pointer size inspection tool
  URL:=https://github.com/mstojek/limits
endef

define Package/limits/description
  A small C utility to display the byte sizes of various C data types and pointers on OpenWrt architectures.
endef

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
	$(CP) ./src/* $(PKG_BUILD_DIR)/
endef

define Build/Compile
	$(MAKE) -C $(PKG_BUILD_DIR) \
		CC="$(TARGET_CC)" \
		CFLAGS="$(TARGET_CFLAGS)" \
		LDFLAGS="$(TARGET_LDFLAGS)"
endef

define Package/limits/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/limits $(1)/usr/bin/limits
endef

$(eval $(call BuildPackage,limits))
