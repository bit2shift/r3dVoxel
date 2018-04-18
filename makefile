# Top-level makefile

export CPPFLAGS = -I$(CURDIR)/inc -MMD -MP -DR3V_EXPORT
export CXXFLAGS = -pedantic -std=c++17 -Wall -Wconversion -Werror -Wextra -fPIC -fvisibility=hidden -msse2 -mstackrealign
export LDFLAGS = -shared
export LDLIBS =

pkg-config = $(shell PKG_CONFIG_PATH='$(PKG_CONFIG_PATH)' pkg-config --silence-errors $(1))

# These includes cannot be used directly.
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

build: SRC := $(shell find src -name \*.cpp -printf %P\ )
build:
	@mkdir -p bin obj
	@$(MAKE) -Cobj                                                   \
	         --eval='-include $(SRC:.cpp=.d)'                        \
	         VPATH='$(CURDIR)/src'                                   \
	         CXX='@echo "Compiling [$$*.cpp]"; mkdir -p $$(*D); g++' \
	         $(SRC:.cpp=.o)
	@$(MAKE) -Cbin                                 \
	         --eval='r3dVoxel.dso: $(SRC:.cpp=.o)' \
	         VPATH='$(CURDIR)/obj'                 \
	         CC='@echo "Linking..."; g++'          \
	         r3dVoxel.dso

clean:
	@echo 'Cleaning...'
	@$(RM) -r obj
