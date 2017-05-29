VPATH = obj
CC = @echo "Linking..."; g++
CXX = @echo "Compiling [$<]"; g++

CPPFLAGS = -MMD -MP -Idep/glfw/deps -Idep/glfw/include -Iinc -DGLFW_INCLUDE_VULKAN -DR3V_EXPORT
CXXFLAGS = -pedantic -std=c++17 -Wall -Wconversion -Werror -Wextra -fvisibility=hidden -msse2 -mstackrealign

LDFLAGS = -shared -Ldep/glfw/src
LDLIBS = $(shell PKG_CONFIG_PATH=dep/glfw/src pkg-config --static --libs-only-l glfw3)

SRC = $(shell find obj -name *.cpp 2> /dev/null)

.PHONY: all build clean cleanall debug depbuild depclean release

all: depbuild debug

cleanall: depclean clean
	@$(RM) r3dVoxel.dll

# debug target
debug: OUTDIR = ../builds/Debug/
debug: export CXXFLAGS += -O0 -g3
debug: build

# release target
release: OUTDIR = ../builds/Release/
release: export CXXFLAGS += -O3
release: build

build:
	@cp -al src/. obj
	@$(MAKE) -e r3dVoxel.dll
	@cp -fl r3dVoxel.dll $(OUTDIR)

r3dVoxel.dll: $(SRC:.cpp=.o)

-include $(SRC:.cpp=.d)

clean:
	@echo "Cleaning..."
	@$(RM) -r obj

depbuild:
	@printf "\033[36mBuilding GLFW\033[m\n"
	@cmake -Bdep/glfw -Hdep/glfw -G "Unix Makefiles" -DBUILD_SHARED_LIBS=OFF -DGLFW_BUILD_DOCS=OFF -DGLFW_BUILD_EXAMPLES=OFF -DGLFW_BUILD_TESTS=OFF
	@make -C dep/glfw

depclean:
	@git submodule foreach "git clean -dffqx; git reset --hard"
