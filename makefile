ifeq ($(MAKELEVEL),0)

INCDIR := $(addprefix $(CURDIR)/,dep/glfw/deps dep/glfw/include inc)
LIBDIR := $(addprefix $(CURDIR)/,dep/glfw/src)

export CPPFLAGS := $(addprefix -I,$(INCDIR)) -MMD -MP -DGLFW_INCLUDE_VULKAN -DR3V_EXPORT
export CXXFLAGS := -pedantic -std=c++17 -Wall -Wconversion -Werror -Wextra -fPIC -fvisibility=hidden -msse2 -mstackrealign
export LDFLAGS := $(addprefix -L,$(LIBDIR)) -shared

export SRCDIR := $(CURDIR)/src
export OBJDIR := $(CURDIR)/obj

SRC := $(shell find $(SRCDIR) -name \*.cpp -printf %P\ )
export DEP := $(SRC:.cpp=.d)
export OBJ := $(SRC:.cpp=.o)

.PHONY: all build clean cleanall debug depbuild depclean release

all: depbuild debug

cleanall: depclean clean
	@$(RM) -r bin

depbuild:
	@printf "\033[36mBuilding GLFW\033[m\n"
	@cmake -G"Unix Makefiles" -Hdep/glfw -Bdep/glfw -DBUILD_SHARED_LIBS=OFF -DGLFW_BUILD_DOCS=OFF -DGLFW_BUILD_EXAMPLES=OFF -DGLFW_BUILD_TESTS=OFF
	@$(MAKE) -Cdep/glfw

depclean:
	@git submodule foreach "git clean -dffqx; git reset --hard"

debug: CXXFLAGS += -O0 -g3
debug: build

release: CXXFLAGS += -O3
release: build

build: export LDLIBS = $(shell PKG_CONFIG_PATH=$(subst $(eval) $(eval),:,$(LIBDIR)) pkg-config --static --libs-only-l glfw3)
build:
	@mkdir -p bin obj
	@$(MAKE) -Cobj $(addprefix -f$(CURDIR)/,$(MAKEFILE_LIST))
	@$(MAKE) -Cbin $(addprefix -f$(CURDIR)/,$(MAKEFILE_LIST))

clean:
	@echo "Cleaning..."
	@$(RM) -r obj

else ifeq ($(notdir $(CURDIR)),obj)

VPATH := $(SRCDIR)
CXX = @echo "Compiling [$*.cpp]"; mkdir -p $(*D); g++
build: $(OBJ)
-include $(DEP)

else ifeq ($(notdir $(CURDIR)),bin)

VPATH := $(OBJDIR)
CC = @echo "Linking..."; g++
r3dVoxel.dso: $(OBJ)

endif
