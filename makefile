# Compiler flags and include folders
CXXFLAG=-c -std=c++14 -Werror -Wall -Wconversion -msse2 -mstackrealign -DR3V_EXPORT -DGLEW_MX -DGLEW_STATIC
INCDIRS=-Idep/glew/include -Idep/glfw/include -Iinc -Isrc

# Linker flags, library folders and libraries
LNKFLAG=-shared
LIBDIRS=-Ldep/glew/lib -Ldep/glfw/src
LIBS=-lglew32mx -lglfw3 -lgdi32 -lopengl32

# Sources and objects
SRC=$(wildcard src/impl/*.cpp src/impl/*/*.cpp)
OBJ=$(SRC:src/%.cpp=obj/%.o)

# Default target
all: debug

# Debug target details
debug: OUTPUT=../builds/Debug
debug: CXXFLAG += -O0 -g3
debug: clean build

# Release target details
release: OUTPUT=../builds/Release
release: CXXFLAG += -O3
release: clean build

# Clean the object files
clean:
	@echo "Cleaning..."
	@rm -rf obj

# Compile source
obj/%.o: src/%.cpp
	@mkdir -p $(dir $@)
	@echo "Compiling [$<]"
	@g++ $< $(CXXFLAG) $(INCDIRS) -o $@

# Main target, links binary after clean'n'compile
build: $(OBJ)
	@echo "Linking..."
	@g++ $^ $(LNKFLAG) $(LIBDIRS) $(LIBS) -o $(OUTPUT)/r3dVoxel.dll

depbuild:
	@sh dep/depmake build

depclean:
	@sh dep/depmake clean
