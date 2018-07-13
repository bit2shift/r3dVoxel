# Le makefile

# Check if pkg-config is installed.
ifeq '' '$(shell pkg-config --version 2>/dev/null)'
$(error error: pkg-config is missing)
endif

r3dVoxel != git rev-parse --show-toplevel

.PHONY: all build clean cleanall debug release

# Piecewise makefiles
include dep/*.mk

# Piecewise-related
DEPS != basename -s.mk dep/*.mk
PKGS != sed 's/ /:/g' <<< '$(PKG_CONFIG_PATH)'

all:: debug

cleanall: clean
	@git submodule foreach 'git clean -dffqx; git reset --hard'
	@$(RM) -r bin

debug: CXXFLAGS = -O0 -g3
debug: build

release: CXXFLAGS = -O3
release: build

build: export CXXFLAGS += -std=c++17 -pedantic -Wall -Wconversion -Werror -Wextra -fPIC -fvisibility=hidden -msse2 -mstackrealign
build: export CPPFLAGS  = $(shell PKG_CONFIG_PATH=$(PKGS) pkg-config --static --cflags $(DEPS)) -I$(r3dVoxel)/dep/glfw/deps -I$(r3dVoxel)/inc -MMD -MP -DGLFW_INCLUDE_VULKAN -DR3V_EXPORT
build: export LDFLAGS   = $(shell PKG_CONFIG_PATH=$(PKGS) pkg-config --static --libs-only-L --libs-only-other $(DEPS)) -shared -fPIC
build: export LDLIBS    = $(shell PKG_CONFIG_PATH=$(PKGS) pkg-config --static --libs-only-l $(DEPS)) -lstdc++

build: SRC != find src -name \*.cpp -printf %P\n
build:
	@mkdir -p bin obj
	@$(MAKE)\
		-Cobj\
		--eval='-include $(SRC:.cpp=.d)'\
		VPATH='$(r3dVoxel)/src'\
		CXX='@echo "Compiling [$$*.cpp]"; mkdir -p $$(*D); $(CXX)'\
		$(SRC:.cpp=.o)
	@$(MAKE)\
		-Cbin\
		--eval='r3dVoxel.dso: $(SRC:.cpp=.o)'\
		VPATH='$(r3dVoxel)/obj'\
		CC='@echo "Linking..."; $(CC)'\
		r3dVoxel.dso

clean:
	@echo 'Cleaning...'
	@$(RM) -r obj
