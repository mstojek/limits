include $(TOPDIR)/rules.mk

PKG_NAME:=typesizes
PKG_VERSION:=1.0.0
PKG_RELEASE:=1
PKG_LICENSE:=MIT
PKG_LICENSE_FILES:=LICENSE

include $(INCLUDE_DIR)/package.mk

define Package/typesizes
  SECTION:=utils
  CATEGORY:=Utilities
  TITLE:=Data type and pointer size inspection tool
  URL:=https://github.com/mstojek/typesizes
endef

define Package/typesizes/description
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

define Package/typesizes/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/typesizes $(1)/usr/bin/typesizes
endef

$(eval $(call BuildPackage,typesizes))
