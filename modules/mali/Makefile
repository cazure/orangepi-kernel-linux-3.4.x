PWD=$(shell pwd)

include ../../.config

MALI_DRV_ROOT=DX910-SW-99002-r4p0-00rel0/driver/src/devicedrv/mali
MALI_UMP_ROOT=DX910-SW-99002-r4p0-00rel0/driver/src/devicedrv/ump
MALI_EGL_ROOT=DX910-SW-99002-r4p0-00rel0/driver/src/egl/x11/drm_module/mali_drm


install: build
	cp $(MALI_DRV_ROOT)/mali.ko $(MOD_DIR)/
	cp $(MALI_EGL_ROOT)/mali_drm.ko $(MOD_DIR)/
	cp $(MALI_UMP_ROOT)/ump.ko $(MOD_DIR)/; 

build:
	@echo KERNEL_DIR: $(KERNEL_DIR)
	@echo UMP_ENABLE: 1
	$(MAKE) -j16 -C $(MALI_UMP_ROOT) CONFIG=ca8-virtex820-m400-1 BUILD=release KDIR=${KERNEL_DIR}
	$(MAKE) -j16 -C $(MALI_DRV_ROOT) USING_MMU=1 USING_UMP=1 USING_PMM=1 BUILD=release KDIR=${KERNEL_DIR}
	$(MAKE) -j16 -C $(MALI_EGL_ROOT) CONFIG=ca8-virtex820-m400-1 BUILD=release KDIR=${KERNEL_DIR}
	
clean:
	$(MAKE) -C $(MALI_UMP_ROOT) CONFIG=ca8-virtex820-m400-1 BUILD=release KDIR=${KERNEL_DIR} clean
	$(MAKE) -C $(MALI_DRV_ROOT) USING_MMU=1 USING_UMP=1 USING_PMM=1 BUILD=release KDIR=${KERNEL_DIR} clean
	$(MAKE) -C $(MALI_EGL_ROOT) USING_MMU=1 BUILD=release KDIR=${KERNEL_DIR} clean

