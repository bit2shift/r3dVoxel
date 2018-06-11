# Only called from the top-level directory.

all:: GLFW := $(CURDIR)/dep/glfw
all:: PKG_CONFIG_PATH += $(GLFW)/lib/pkgconfig
all::
	@printf "\033[36mBuilding GLFW\033[m\n"
	@cmake -G"Unix Makefiles" -H$(GLFW) -B$(GLFW) -DBUILD_SHARED_LIBS=OFF -DCMAKE_INSTALL_PREFIX=$(GLFW) -DGLFW_BUILD_DOCS=OFF -DGLFW_BUILD_EXAMPLES=OFF -DGLFW_BUILD_TESTS=OFF
	@$(MAKE) -C$(GLFW) all install
