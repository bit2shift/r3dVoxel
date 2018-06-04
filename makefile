# Top-level makefile

export CPPFLAGS := -I$(CURDIR)/inc -MMD -MP -DGLFW_INCLUDE_VULKAN -DR3V_EXPORT
export CXXFLAGS := -pedantic -std=c++17 -Wall -Wconversion -Werror -Wextra -fPIC -fvisibility=hidden -msse2 -mstackrealign
export LDFLAGS := -shared
export LDLIBS :=

.PHONY: all build clean cleanall debug release

all: $(subst .mk,.cf,$(wildcard $(CURDIR)/dep/*.mk)) debug

cleanall: clean
	@git submodule foreach 'git clean -dffqx; git reset --hard'
	@$(RM) -r bin dep/*.cf

# Piecewise makefiles
include dep/*.mk

debug: CXXFLAGS += -O0 -g3
debug: build

release: CXXFLAGS += -O3
release: build

build: SRC := $(shell find src -name \*.cpp -printf %P\ )
build:
	@mkdir -p bin obj
	@$(MAKE)\
		-Cobj\
		--eval='include $(CURDIR)/dep/*.cf'\
		--eval='-include $(SRC:.cpp=.d)'\
		VPATH='$(CURDIR)/src'\
		CXX='@echo "Compiling [$$*.cpp]"; mkdir -p $$(*D); g++'\
		$(SRC:.cpp=.o)
	@$(MAKE)\
		-Cbin\
		--eval='include $(CURDIR)/dep/*.cf'\
		--eval='r3dVoxel.dso: $(SRC:.cpp=.o)'\
		VPATH='$(CURDIR)/obj'\
		CC='@echo "Linking..."; g++'\
		r3dVoxel.dso

clean:
	@echo 'Cleaning...'
	@$(RM) -r obj
