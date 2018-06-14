# Le makefile

# Check if pkg-config is installed.
ifeq '$(shell which pkg-config 2>/dev/null)' ''
$(error error: pkg-config is missing)
endif

# Explicit GLFW include for its vulkan headers.
export CPPFLAGS := -I$(CURDIR)/dep/glfw/deps -I$(CURDIR)/inc -MMD -MP -DGLFW_INCLUDE_VULKAN -DR3V_EXPORT
export CXXFLAGS := -pedantic -std=c++17 -Wall -Wconversion -Werror -Wextra -fPIC -fvisibility=hidden -msse2 -mstackrealign
export LDFLAGS := -shared
export LDLIBS :=

# Piecewise makefiles
include dep/*.mk

.PHONY: all build clean cleanall debug release

all:: debug

cleanall: clean
	@git submodule foreach 'git clean -dffqx; git reset --hard'
	@$(RM) -r bin

debug: CXXFLAGS += -O0 -g3
debug: build

release: CXXFLAGS += -O3
release: build

build: DEPS := $(basename $(notdir $(wildcard dep/*.mk)))
build: PKGS = $(shell echo $(PKG_CONFIG_PATH) | sed 's/ /:/g')

build: CPPFLAGS += $(shell PKG_CONFIG_PATH=$(PKGS) pkg-config --static --cflags $(DEPS))
build: LDFLAGS  += $(shell PKG_CONFIG_PATH=$(PKGS) pkg-config --static --libs-only-other --libs-only-L $(DEPS))
build: LDLIBS   += $(shell PKG_CONFIG_PATH=$(PKGS) pkg-config --static --libs-only-l $(DEPS))

build: SRC := $(shell find src -name \*.cpp -printf %P\ )
build:
	@mkdir -p bin obj
	@$(MAKE)\
		-Cobj\
		--eval='-include $(SRC:.cpp=.d)'\
		VPATH='$(CURDIR)/src'\
		CXX='@echo "Compiling [$$*.cpp]"; mkdir -p $$(*D); g++'\
		$(SRC:.cpp=.o)
	@$(MAKE)\
		-Cbin\
		--eval='r3dVoxel.dso: $(SRC:.cpp=.o)'\
		VPATH='$(CURDIR)/obj'\
		CC='@echo "Linking..."; g++'\
		r3dVoxel.dso

clean:
	@echo 'Cleaning...'
	@$(RM) -r obj
