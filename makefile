# Le makefile
SHELL := /bin/bash

# Check if jq is installed.
ifeq '' '$(shell jq --version 2>/dev/null)'
$(error error: jq is missing)
endif

# Check if pkg-config is installed.
ifeq '' '$(shell pkg-config --version 2>/dev/null)'
$(error error: pkg-config is missing)
endif

# Detect if CXX is clang++ or g++.
ifneq '' '$(findstring clang++,$(CXX))'
CXXFLAGS = -stdlib=libc++
LDLIBS   = -lc++
else ifneq '' '$(findstring g++,$(CXX))'
LDLIBS   = -lstdc++
endif

# Build flags
CXXFLAGS += -std=c++17 -pedantic -Wall -Wconversion -Werror -Wextra -fPIC -fvisibility=hidden -msse2 -mstackrealign
CPPFLAGS += -MMD -MP -I$(CURDIR)/dep/glfw/deps -I$(CURDIR)/inc -DGLFW_INCLUDE_VULKAN -DR3V_EXPORT

.PHONY: all build clean cleanall compile debug depbuild release

all: depbuild debug
depbuild:
	@jq -r '"all:", (.depbuild | to_entries | map("\t@printf \("\u001B[36mBuilding \(.key)\u001B[m\\n" | @sh)\n\t@\(["cd \(.value.path)"] + .value.build | join(" && "))") | join("\n\n"))' über.json >dep/makefile
	@$(MAKE) -Cdep
	@$(RM) dep/makefile

pkg-config := PKG_CONFIG_PATH=$(shell jq -r '.depbuild | to_entries | map("$(CURDIR)/dep/\(.value.path)/\(.value.pkgconfig)") | join(":")' über.json) pkg-config $(shell jq -r '.dep + (.depbuild | to_entries | map(.key)) | join(" ")' über.json)

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

build: export CPPFLAGS += $(shell $(pkg-config) --static --cflags)
build: export LDFLAGS  += $(shell $(pkg-config) --static --libs-only-L --libs-only-other)
build: export LDLIBS   += $(shell $(pkg-config) --static --libs-only-l)

build: SRC != find src -name '*.cpp' -printf '%P '
build: $(shell find src -name '*.mk')

src/%.mk: compile | bin
	@$(MAKE)\
		-Cbin\
		-f'$(CURDIR)/$@'\
		VPATH='$(CURDIR)/obj'\
		CC='@echo "Linking [$$@]"; mkdir -p $$(@D); $(CC)'\
		OBJ='$(SRC:.cpp=.o)'

compile: | obj
	@$(MAKE)\
		-Cobj\
		--eval='-include $(SRC:.cpp=.d)'\
		VPATH='$(CURDIR)/src'\
		CXX='@echo "Compiling [$$@]"; mkdir -p $$(@D); $(CXX)'\
		$(SRC:.cpp=.o)

bin obj:
	@mkdir $@
