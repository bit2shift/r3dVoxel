VPATH = obj
CC = @echo "Linking..."; g++
CXX = @echo "Compiling [$<]"; g++

CPPFLAGS = -MMD -MP -Idep/glfw/deps -Idep/glfw/include -Iinc -DGLFW_INCLUDE_VULKAN -DR3V_EXPORT
CXXFLAGS = -pedantic -std=c++14 -Wall -Wconversion -Werror -fvisibility=hidden -msse2 -mstackrealign

LDFLAGS = -shared -static -Ldep/glfw/src
LDLIBS = $(shell PKG_CONFIG_PATH=dep/glfw/src pkg-config --static --libs-only-l glfw3)

SRC = $(shell find obj -name *.cpp 2> /dev/null)

# debug target
debug: OUTDIR = ../builds/Debug/
debug: export CXXFLAGS += -O0 -g3
debug: all

# release target
release: OUTDIR = ../builds/Release/
release: export CXXFLAGS += -O3
release: all

all:
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
	@cd dep/glfw && cmake -G "Unix Makefiles" -DBUILD_SHARED_LIBS=OFF -DGLFW_BUILD_EXAMPLES=OFF -DGLFW_BUILD_TESTS=OFF -DGLFW_BUILD_DOCS=OFF .
	@make -C dep/glfw

depclean:
	@git submodule foreach "git clean -dffqx; git reset --hard"
