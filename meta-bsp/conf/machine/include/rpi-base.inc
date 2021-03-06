SOC_FAMILY = "rpi"
include conf/machine/include/soc-family.inc

WKS_FILE ?= "sdimage-raspberrypi.wks"

# Inputs for machine-conf-runtime recipe
MACHINE_FEATURES += "headless"

PREFERRED_PROVIDER_virtual/kernel ?= "linux-raspberrypi"

RPI_KERNEL_DEVICETREE_OVERLAYS = " \
    overlays/ads7846-overlay.dtb \
    overlays/pitft28-capacitive-overlay.dtb \
    overlays/pitft35-resistive-overlay.dtb \
    overlays/rpi-display-overlay.dtb \
    overlays/mcp2515-can0-overlay.dtb \
    overlays/mcp2515-can1-overlay.dtb \
    overlays/rpi-ft5406-overlay.dtb \
"

KERNEL_PACKAGES ?= "kernel-image kernel-modules"
KERNEL_IMAGETYPE ?= "zImage"
RPI_KERNEL_DEVICETREE ?= " \
    ${RPI_KERNEL_DEVICETREE_DTB} \
    ${RPI_KERNEL_DEVICETREE_OVERLAYS} \
"

PREFERRED_PROVIDER_virtual/bootloader ?= "u-boot-venus"
PREFERRED_VERSION_u-boot-fw-utils ?= "venus"
UBOOT_SRC_URI ?= "git://github.com/victronenergy/u-boot.git;branch=rpi;tag=165921ec11deb8a343ef23d28c0809ccda7c9542"
UBOOT_SUFFIX ?= "bin"
UBOOT_BINARY ?= "u-boot.${UBOOT_SUFFIX}"

IMAGE_FSTYPES ?= "wic ext4.gz"

MACHINE_FEATURES += "apm usbhost keyboard vfat ext2 screen touchscreen alsa bluetooth wifi sdio ${@bb.utils.contains('DISABLE_VC4GRAPHICS', '1', '', 'vc4graphics', d)}"

# Raspberry Pi has no hardware clock
MACHINE_FEATURES_BACKFILL_CONSIDERED = "rtc"

IMAGE_BOOT_FILES ?= " \
    bcm2835-bootfiles/* \
    config.txt \
    cmdline.txt \
    ${RPI_KERNEL_DEVICETREE} \
    ${UBOOT_BINARY} \
"

do_image_wic[depends] += " \
    bcm2835-bootfiles:do_deploy \
    virtual/bootloader:do_deploy \
"

do_image_wic[recrdeps] = "do_deploy"
