VPATH = obj
CC = @echo "Linking..."; g++
CXX = @echo "Compiling [$<]"; g++

CPPFLAGS = -MMD -MP -Idep/glfw/deps -Idep/glfw/include -Iinc -DGLFW_INCLUDE_VULKAN -DR3V_EXPORT
CXXFLAGS = -pedantic -std=c++17 -Wall -Wconversion -Werror -Wextra -fPIC -fvisibility=hidden -msse2 -mstackrealign

LDFLAGS = -shared -Ldep/glfw/src
LDLIBS = $(shell PKG_CONFIG_PATH=dep/glfw/src pkg-config --static --libs-only-l glfw3)

SRC = $(shell find obj -name *.cpp 2> /dev/null)

.PHONY: all build clean cleanall debug depbuild depclean release

all: depbuild debug

build:
	@cp -al src/. obj
	@$(MAKE) -e r3dVoxel.dso
	@cp -fl r3dVoxel.dso $(OUTDIR)

clean:
	@echo "Cleaning..."
	@$(RM) -r obj

cleanall: depclean clean
	@$(RM) r3dVoxel.dso

debug: OUTDIR = ../builds/Debug/
debug: export CXXFLAGS += -O0 -g3
debug: build

depbuild:
	@printf "\033[36mBuilding GLFW\033[m\n"
	@cmake -G"Unix Makefiles" -Hdep/glfw -Bdep/glfw -DBUILD_SHARED_LIBS=OFF -DGLFW_BUILD_DOCS=OFF -DGLFW_BUILD_EXAMPLES=OFF -DGLFW_BUILD_TESTS=OFF
	@$(MAKE) -Cdep/glfw

depclean:
	@git submodule foreach "git clean -dffqx; git reset --hard"

release: OUTDIR = ../builds/Release/
release: export CXXFLAGS += -O3
release: build

r3dVoxel.dso: $(SRC:.cpp=.o)

-include $(SRC:.cpp=.d)
