vpath %.cpp ../src

CC = @echo "Linking..."; g++
CXX = @echo "Compiling [$<]"; g++

CPPFLAGS = -MMD -MP -I../dep/glfw/deps -I../dep/glfw/include -I../inc -DGLFW_INCLUDE_VULKAN -DR3V_EXPORT
CXXFLAGS ?= -pedantic -std=c++17 -Wall -Wconversion -Werror -Wextra -fPIC -fvisibility=hidden -msse2 -mstackrealign

LDFLAGS = -shared -L../dep/glfw/src
LDLIBS = $(shell PKG_CONFIG_PATH=../dep/glfw/src pkg-config --static --libs-only-l glfw3)

.PHONY: all build clean cleanall debug depbuild depclean release

all: depbuild debug

cleanall: depclean clean
	@$(RM) r3dVoxel.dso

depbuild:
	@printf "\033[36mBuilding GLFW\033[m\n"
	@cmake -G"Unix Makefiles" -Hdep/glfw -Bdep/glfw -DBUILD_SHARED_LIBS=OFF -DGLFW_BUILD_DOCS=OFF -DGLFW_BUILD_EXAMPLES=OFF -DGLFW_BUILD_TESTS=OFF
	@$(MAKE) -Cdep/glfw

depclean:
	@git submodule foreach "git clean -dffqx; git reset --hard"

debug: export CXXFLAGS += -O0 -g3
debug: build

release: export CXXFLAGS += -O3
release: build

build:
	@mkdir -p $$(find src -type d -printf obj/%P\ )
	@$(MAKE) -Cobj $(MAKEFILE_LIST:%=-f../%) SRC="$$(find src -name \*.cpp -printf %P\ )" r3dVoxel.dso
	@cp -fl obj/r3dVoxel.dso .

clean:
	@echo "Cleaning..."
	@$(RM) -r obj

-include $(SRC:.cpp=.d)
r3dVoxel.dso: $(SRC:.cpp=.o)
