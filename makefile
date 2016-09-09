VPATH = obj
CC = @echo "Linking..."; g++
CXX = @echo "Compiling [$<]"; g++

CPPFLAGS = -MMD -MP -DR3V_EXPORT -DGLFW_INCLUDE_VULKAN -Idep/glfw/deps -Idep/glfw/include -Iinc
CXXFLAGS = -std=c++14 -Werror -Wall -Wconversion -msse2 -mstackrealign

LDFLAGS = -shared -Ldep/glfw/src
LDLIBS = -lglfw3 -lgdi32

ifeq ($(MAKECMDGOALS),)
SRC := $(shell cp -al src/. obj; find obj -name \*.cpp)
endif

r3dVoxel.dll: $(SRC:.cpp=.o)

-include $(SRC:.cpp=.d)

clean:
	@echo "Cleaning..."
	@$(RM) -rf obj

# debug target
#debug: OUTDIR = ../builds/Debug
#debug: CXXFLAGS += -O0 -g3
#debug: $(OUTPUT)

# release target
#release: OUTDIR = ../builds/Release
#release: CXXFLAGS += -O3
#release: $(OUTPUT)

#OUTPUT = $(OUTDIR)/

depbuild:
	@printf "\033[36mBuilding GLFW\033[m\n"
	@cd dep/glfw && cmake -G "Unix Makefiles" -DBUILD_SHARED_LIBS=OFF -DGLFW_BUILD_EXAMPLES=OFF -DGLFW_BUILD_TESTS=OFF -DGLFW_BUILD_DOCS=OFF .
	@make -C dep/glfw

depclean:
	@git submodule foreach "git clean -dffqx; git reset --hard"
