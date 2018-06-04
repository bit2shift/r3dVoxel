# Only called from the top-level directory.

GLFW := $(CURDIR)/dep/glfw
export PKG_CONFIG_PATH := $(GLFW)/lib/pkgconfig

$(GLFW).cf:
	@printf "\033[36mBuilding GLFW\033[m\n"
	@cmake -G"Unix Makefiles" -H$(GLFW) -B$(GLFW) -DBUILD_SHARED_LIBS=OFF -DCMAKE_INSTALL_PREFIX=$(GLFW) -DGLFW_BUILD_DOCS=OFF -DGLFW_BUILD_EXAMPLES=OFF -DGLFW_BUILD_TESTS=OFF
	@$(MAKE) -C$(GLFW) all install
	@printf "# Leave me alone, I'm auto-generated!\n# $$(date +%F\ %T)\n\n" > $@
	@echo "CPPFLAGS += $$(pkg-config --cflags glfw3) -I$$(pkg-config --variable=prefix glfw3)/deps" >> $@
	@echo "LDFLAGS += $$(pkg-config --static --libs-only-other --libs-only-L glfw3)" >> $@
	@echo "LDLIBS += $$(pkg-config --static --libs-only-l glfw3)" >> $@
