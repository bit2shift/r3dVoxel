# Only called from the top-level directory.

PKG_CONFIG_PATH := $(CURDIR)/dep/glfw/lib/pkgconfig

CPPFLAGS += $(call pkg-config,--cflags glfw3) -I$(call pkg-config,--variable=prefix glfw3)/deps -DGLFW_INCLUDE_VULKAN
LDFLAGS += $(call pkg-config,--static --libs-only-other --libs-only-L glfw3)
LDLIBS += $(call pkg-config,--static --libs-only-l glfw3)

ifeq ($(call pkg-config,--exists glfw3; echo $$?),1)
all::
	@printf "\033[36mBuilding GLFW\033[m\n"
	@cmake -G"Unix Makefiles" -Hdep/glfw -Bdep/glfw -DBUILD_SHARED_LIBS=OFF -DCMAKE_INSTALL_PREFIX=dep/glfw -DGLFW_BUILD_DOCS=OFF -DGLFW_BUILD_EXAMPLES=OFF -DGLFW_BUILD_TESTS=OFF
	@$(MAKE) -Cdep/glfw all install
endif
