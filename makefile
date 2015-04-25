# Compiler flags and include folders
CXXFLAG=-c -std=c++14 -Wall -Wconversion -msse2 -mstackrealign
INCDIRS=-I../../glew/include -I../../glfw/include

# Linker flags, library folders and libraries
LNKFLAG=-shared -static
LIBDIRS=-L../../glew/lib -L../../glfw/lib-mingw
LIBS=-lglew32mxs -lglfw3 -lgdi32 -lopengl32

# Sources and objects
SRC=$(wildcard src/implementation/*.cpp src/implementation/*/*.cpp)
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
	rm -fR obj

# Compile source
obj/%.o: src/%.cpp
	mkdir -p $(dir $@)
	g++ $< $(CXXFLAG) $(INCDIRS) -o $@

# Main target, links binary after clean'n'compile
build: $(OBJ)
	g++ $^ $(LNKFLAG) $(LIBDIRS) $(LIBS) -o $(OUTPUT)/r3dVoxel.dll
