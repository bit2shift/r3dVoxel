VPATH = obj
CC = @echo "Linking..."; g++
CXX = @echo "Compiling [$<]"; g++

CPPFLAGS = -MMD -MP -DR3V_EXPORT -DGLEW_MX -DGLEW_STATIC -Idep/glew/include -Idep/glfw/include -Iinc
CXXFLAGS = -std=c++14 -Werror -Wall -Wconversion -msse2 -mstackrealign

LDFLAGS = -shared -Ldep/glew/lib -Ldep/glfw/src
LDLIBS = -lglew32 -lglfw3 -lgdi32 -lopengl32

ifneq ($(MAKECMDGOALS),clean)
SRC := $(shell cp -al src/. obj; /usr/bin/find obj -name \*.cpp)
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
	@printf "\e[36mBuilding GLEW\e[m\n"
	@make -C dep/glew extensions glew.lib

	@printf "\e[36mBuilding GLFW\e[m\n"
	@cd dep/glfw && cmake -G "Unix Makefiles" -DBUILD_SHARED_LIBS=OFF -DGLFW_BUILD_EXAMPLES=OFF -DGLFW_BUILD_TESTS=OFF -DGLFW_BUILD_DOCS=OFF .
	@make -C dep/glfw

depclean:
	@git submodule foreach "git clean -dffqx; git reset --hard"
