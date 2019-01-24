# Le makefile
SHELL := /bin/bash

# Check if pkg-config is installed.
ifeq '' '$(shell pkg-config --version 2>/dev/null)'
$(error error: pkg-config is missing)
endif

# Build target
TARGET := r3dVoxel/r3dVoxel.dso

# Build flags
CXXFLAGS := -std=c++17 -pedantic -Wall -Wconversion -Werror -Wextra -fPIC -fvisibility=hidden -msse2 -mstackrealign
CPPFLAGS := -MMD -MP -I$(CURDIR)/dep/glfw/deps -I$(CURDIR)/inc -DGLFW_INCLUDE_VULKAN -DR3V_EXPORT
LDFLAGS  := -shared
LDLIBS   := -lstdc++

.PHONY: all build clean cleanall debug depbuild release

all: depbuild debug

# Piecewise makefiles
include dep/*.mk

cleanall: clean
	@git submodule foreach 'git clean -dffqx; git reset --hard'
	@$(RM) -r bin

clean:
	@echo 'Cleaning...'
	@$(RM) -r obj

debug: export CXXFLAGS += -O0 -g3
debug: build

release: export CXXFLAGS += -O3
release: build

build: SRC != find src -name '*.cpp' -printf '%P '
build: pkg-config := PKG_CONFIG_PATH=$(shell sed 's/ /:/g' <<< '$(PKG_CONFIG_PATH)') pkg-config $(shell basename -s.mk dep/*.mk)

build: export CPPFLAGS += $(shell $(pkg-config) --static --cflags)
build: export LDFLAGS  += $(shell $(pkg-config) --static --libs-only-L --libs-only-other)
build: export LDLIBS   += $(shell $(pkg-config) --static --libs-only-l)

build: compile link

compile: | obj
	@$(MAKE)\
		-Cobj\
		--eval='-include $(SRC:.cpp=.d)'\
		VPATH='$(CURDIR)/src'\
		CXX='@echo "Compiling [$$@]"; mkdir -p $$(@D); $(CXX)'\
		$(SRC:.cpp=.o)

link: | bin
	@$(MAKE)\
		-Cbin\
		--eval='$(TARGET): $(SRC:.cpp=.o)'\
		VPATH='$(CURDIR)/obj'\
		CC='@echo "Linking [$$@]"; mkdir -p $$(@D); $(CC)'\
		$(TARGET)

bin obj:
	@mkdir $@
