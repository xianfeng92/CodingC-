# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/home/parallels/Stan/CodingCPlusPlus/NoteBook/Compile_Link_Lib/13 运行库实现/MiniCRTV4"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/parallels/Stan/CodingCPlusPlus/NoteBook/Compile_Link_Lib/13 运行库实现/MiniCRTV4/build"

# Include any dependencies generated for this target.
include src/CMakeFiles/minicrt.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/minicrt.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/minicrt.dir/flags.make

src/CMakeFiles/minicrt.dir/entry.c.o: src/CMakeFiles/minicrt.dir/flags.make
src/CMakeFiles/minicrt.dir/entry.c.o: ../src/entry.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/parallels/Stan/CodingCPlusPlus/NoteBook/Compile_Link_Lib/13 运行库实现/MiniCRTV4/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object src/CMakeFiles/minicrt.dir/entry.c.o"
	cd "/home/parallels/Stan/CodingCPlusPlus/NoteBook/Compile_Link_Lib/13 运行库实现/MiniCRTV4/build/src" && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/minicrt.dir/entry.c.o   -c "/home/parallels/Stan/CodingCPlusPlus/NoteBook/Compile_Link_Lib/13 运行库实现/MiniCRTV4/src/entry.c"

src/CMakeFiles/minicrt.dir/entry.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/minicrt.dir/entry.c.i"
	cd "/home/parallels/Stan/CodingCPlusPlus/NoteBook/Compile_Link_Lib/13 运行库实现/MiniCRTV4/build/src" && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/home/parallels/Stan/CodingCPlusPlus/NoteBook/Compile_Link_Lib/13 运行库实现/MiniCRTV4/src/entry.c" > CMakeFiles/minicrt.dir/entry.c.i

src/CMakeFiles/minicrt.dir/entry.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/minicrt.dir/entry.c.s"
	cd "/home/parallels/Stan/CodingCPlusPlus/NoteBook/Compile_Link_Lib/13 运行库实现/MiniCRTV4/build/src" && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/home/parallels/Stan/CodingCPlusPlus/NoteBook/Compile_Link_Lib/13 运行库实现/MiniCRTV4/src/entry.c" -o CMakeFiles/minicrt.dir/entry.c.s

src/CMakeFiles/minicrt.dir/format.c.o: src/CMakeFiles/minicrt.dir/flags.make
src/CMakeFiles/minicrt.dir/format.c.o: ../src/format.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/parallels/Stan/CodingCPlusPlus/NoteBook/Compile_Link_Lib/13 运行库实现/MiniCRTV4/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building C object src/CMakeFiles/minicrt.dir/format.c.o"
	cd "/home/parallels/Stan/CodingCPlusPlus/NoteBook/Compile_Link_Lib/13 运行库实现/MiniCRTV4/build/src" && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/minicrt.dir/format.c.o   -c "/home/parallels/Stan/CodingCPlusPlus/NoteBook/Compile_Link_Lib/13 运行库实现/MiniCRTV4/src/format.c"

src/CMakeFiles/minicrt.dir/format.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/minicrt.dir/format.c.i"
	cd "/home/parallels/Stan/CodingCPlusPlus/NoteBook/Compile_Link_Lib/13 运行库实现/MiniCRTV4/build/src" && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/home/parallels/Stan/CodingCPlusPlus/NoteBook/Compile_Link_Lib/13 运行库实现/MiniCRTV4/src/format.c" > CMakeFiles/minicrt.dir/format.c.i

src/CMakeFiles/minicrt.dir/format.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/minicrt.dir/format.c.s"
	cd "/home/parallels/Stan/CodingCPlusPlus/NoteBook/Compile_Link_Lib/13 运行库实现/MiniCRTV4/build/src" && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/home/parallels/Stan/CodingCPlusPlus/NoteBook/Compile_Link_Lib/13 运行库实现/MiniCRTV4/src/format.c" -o CMakeFiles/minicrt.dir/format.c.s

src/CMakeFiles/minicrt.dir/malloc.c.o: src/CMakeFiles/minicrt.dir/flags.make
src/CMakeFiles/minicrt.dir/malloc.c.o: ../src/malloc.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/parallels/Stan/CodingCPlusPlus/NoteBook/Compile_Link_Lib/13 运行库实现/MiniCRTV4/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Building C object src/CMakeFiles/minicrt.dir/malloc.c.o"
	cd "/home/parallels/Stan/CodingCPlusPlus/NoteBook/Compile_Link_Lib/13 运行库实现/MiniCRTV4/build/src" && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/minicrt.dir/malloc.c.o   -c "/home/parallels/Stan/CodingCPlusPlus/NoteBook/Compile_Link_Lib/13 运行库实现/MiniCRTV4/src/malloc.c"

src/CMakeFiles/minicrt.dir/malloc.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/minicrt.dir/malloc.c.i"
	cd "/home/parallels/Stan/CodingCPlusPlus/NoteBook/Compile_Link_Lib/13 运行库实现/MiniCRTV4/build/src" && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/home/parallels/Stan/CodingCPlusPlus/NoteBook/Compile_Link_Lib/13 运行库实现/MiniCRTV4/src/malloc.c" > CMakeFiles/minicrt.dir/malloc.c.i

src/CMakeFiles/minicrt.dir/malloc.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/minicrt.dir/malloc.c.s"
	cd "/home/parallels/Stan/CodingCPlusPlus/NoteBook/Compile_Link_Lib/13 运行库实现/MiniCRTV4/build/src" && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/home/parallels/Stan/CodingCPlusPlus/NoteBook/Compile_Link_Lib/13 运行库实现/MiniCRTV4/src/malloc.c" -o CMakeFiles/minicrt.dir/malloc.c.s

src/CMakeFiles/minicrt.dir/stdio.c.o: src/CMakeFiles/minicrt.dir/flags.make
src/CMakeFiles/minicrt.dir/stdio.c.o: ../src/stdio.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/parallels/Stan/CodingCPlusPlus/NoteBook/Compile_Link_Lib/13 运行库实现/MiniCRTV4/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_4) "Building C object src/CMakeFiles/minicrt.dir/stdio.c.o"
	cd "/home/parallels/Stan/CodingCPlusPlus/NoteBook/Compile_Link_Lib/13 运行库实现/MiniCRTV4/build/src" && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/minicrt.dir/stdio.c.o   -c "/home/parallels/Stan/CodingCPlusPlus/NoteBook/Compile_Link_Lib/13 运行库实现/MiniCRTV4/src/stdio.c"

src/CMakeFiles/minicrt.dir/stdio.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/minicrt.dir/stdio.c.i"
	cd "/home/parallels/Stan/CodingCPlusPlus/NoteBook/Compile_Link_Lib/13 运行库实现/MiniCRTV4/build/src" && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/home/parallels/Stan/CodingCPlusPlus/NoteBook/Compile_Link_Lib/13 运行库实现/MiniCRTV4/src/stdio.c" > CMakeFiles/minicrt.dir/stdio.c.i

src/CMakeFiles/minicrt.dir/stdio.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/minicrt.dir/stdio.c.s"
	cd "/home/parallels/Stan/CodingCPlusPlus/NoteBook/Compile_Link_Lib/13 运行库实现/MiniCRTV4/build/src" && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/home/parallels/Stan/CodingCPlusPlus/NoteBook/Compile_Link_Lib/13 运行库实现/MiniCRTV4/src/stdio.c" -o CMakeFiles/minicrt.dir/stdio.c.s

src/CMakeFiles/minicrt.dir/string.c.o: src/CMakeFiles/minicrt.dir/flags.make
src/CMakeFiles/minicrt.dir/string.c.o: ../src/string.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/parallels/Stan/CodingCPlusPlus/NoteBook/Compile_Link_Lib/13 运行库实现/MiniCRTV4/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_5) "Building C object src/CMakeFiles/minicrt.dir/string.c.o"
	cd "/home/parallels/Stan/CodingCPlusPlus/NoteBook/Compile_Link_Lib/13 运行库实现/MiniCRTV4/build/src" && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/minicrt.dir/string.c.o   -c "/home/parallels/Stan/CodingCPlusPlus/NoteBook/Compile_Link_Lib/13 运行库实现/MiniCRTV4/src/string.c"

src/CMakeFiles/minicrt.dir/string.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/minicrt.dir/string.c.i"
	cd "/home/parallels/Stan/CodingCPlusPlus/NoteBook/Compile_Link_Lib/13 运行库实现/MiniCRTV4/build/src" && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/home/parallels/Stan/CodingCPlusPlus/NoteBook/Compile_Link_Lib/13 运行库实现/MiniCRTV4/src/string.c" > CMakeFiles/minicrt.dir/string.c.i

src/CMakeFiles/minicrt.dir/string.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/minicrt.dir/string.c.s"
	cd "/home/parallels/Stan/CodingCPlusPlus/NoteBook/Compile_Link_Lib/13 运行库实现/MiniCRTV4/build/src" && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/home/parallels/Stan/CodingCPlusPlus/NoteBook/Compile_Link_Lib/13 运行库实现/MiniCRTV4/src/string.c" -o CMakeFiles/minicrt.dir/string.c.s

src/CMakeFiles/minicrt.dir/cxxabi.cpp.o: src/CMakeFiles/minicrt.dir/flags.make
src/CMakeFiles/minicrt.dir/cxxabi.cpp.o: ../src/cxxabi.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/parallels/Stan/CodingCPlusPlus/NoteBook/Compile_Link_Lib/13 运行库实现/MiniCRTV4/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object src/CMakeFiles/minicrt.dir/cxxabi.cpp.o"
	cd "/home/parallels/Stan/CodingCPlusPlus/NoteBook/Compile_Link_Lib/13 运行库实现/MiniCRTV4/build/src" && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/minicrt.dir/cxxabi.cpp.o -c "/home/parallels/Stan/CodingCPlusPlus/NoteBook/Compile_Link_Lib/13 运行库实现/MiniCRTV4/src/cxxabi.cpp"

src/CMakeFiles/minicrt.dir/cxxabi.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/minicrt.dir/cxxabi.cpp.i"
	cd "/home/parallels/Stan/CodingCPlusPlus/NoteBook/Compile_Link_Lib/13 运行库实现/MiniCRTV4/build/src" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/parallels/Stan/CodingCPlusPlus/NoteBook/Compile_Link_Lib/13 运行库实现/MiniCRTV4/src/cxxabi.cpp" > CMakeFiles/minicrt.dir/cxxabi.cpp.i

src/CMakeFiles/minicrt.dir/cxxabi.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/minicrt.dir/cxxabi.cpp.s"
	cd "/home/parallels/Stan/CodingCPlusPlus/NoteBook/Compile_Link_Lib/13 运行库实现/MiniCRTV4/build/src" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/parallels/Stan/CodingCPlusPlus/NoteBook/Compile_Link_Lib/13 运行库实现/MiniCRTV4/src/cxxabi.cpp" -o CMakeFiles/minicrt.dir/cxxabi.cpp.s

src/CMakeFiles/minicrt.dir/new_delete.cpp.o: src/CMakeFiles/minicrt.dir/flags.make
src/CMakeFiles/minicrt.dir/new_delete.cpp.o: ../src/new_delete.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/parallels/Stan/CodingCPlusPlus/NoteBook/Compile_Link_Lib/13 运行库实现/MiniCRTV4/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object src/CMakeFiles/minicrt.dir/new_delete.cpp.o"
	cd "/home/parallels/Stan/CodingCPlusPlus/NoteBook/Compile_Link_Lib/13 运行库实现/MiniCRTV4/build/src" && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/minicrt.dir/new_delete.cpp.o -c "/home/parallels/Stan/CodingCPlusPlus/NoteBook/Compile_Link_Lib/13 运行库实现/MiniCRTV4/src/new_delete.cpp"

src/CMakeFiles/minicrt.dir/new_delete.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/minicrt.dir/new_delete.cpp.i"
	cd "/home/parallels/Stan/CodingCPlusPlus/NoteBook/Compile_Link_Lib/13 运行库实现/MiniCRTV4/build/src" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/parallels/Stan/CodingCPlusPlus/NoteBook/Compile_Link_Lib/13 运行库实现/MiniCRTV4/src/new_delete.cpp" > CMakeFiles/minicrt.dir/new_delete.cpp.i

src/CMakeFiles/minicrt.dir/new_delete.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/minicrt.dir/new_delete.cpp.s"
	cd "/home/parallels/Stan/CodingCPlusPlus/NoteBook/Compile_Link_Lib/13 运行库实现/MiniCRTV4/build/src" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/parallels/Stan/CodingCPlusPlus/NoteBook/Compile_Link_Lib/13 运行库实现/MiniCRTV4/src/new_delete.cpp" -o CMakeFiles/minicrt.dir/new_delete.cpp.s

src/CMakeFiles/minicrt.dir/string.cpp.o: src/CMakeFiles/minicrt.dir/flags.make
src/CMakeFiles/minicrt.dir/string.cpp.o: ../src/string.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/parallels/Stan/CodingCPlusPlus/NoteBook/Compile_Link_Lib/13 运行库实现/MiniCRTV4/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object src/CMakeFiles/minicrt.dir/string.cpp.o"
	cd "/home/parallels/Stan/CodingCPlusPlus/NoteBook/Compile_Link_Lib/13 运行库实现/MiniCRTV4/build/src" && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/minicrt.dir/string.cpp.o -c "/home/parallels/Stan/CodingCPlusPlus/NoteBook/Compile_Link_Lib/13 运行库实现/MiniCRTV4/src/string.cpp"

src/CMakeFiles/minicrt.dir/string.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/minicrt.dir/string.cpp.i"
	cd "/home/parallels/Stan/CodingCPlusPlus/NoteBook/Compile_Link_Lib/13 运行库实现/MiniCRTV4/build/src" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/parallels/Stan/CodingCPlusPlus/NoteBook/Compile_Link_Lib/13 运行库实现/MiniCRTV4/src/string.cpp" > CMakeFiles/minicrt.dir/string.cpp.i

src/CMakeFiles/minicrt.dir/string.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/minicrt.dir/string.cpp.s"
	cd "/home/parallels/Stan/CodingCPlusPlus/NoteBook/Compile_Link_Lib/13 运行库实现/MiniCRTV4/build/src" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/parallels/Stan/CodingCPlusPlus/NoteBook/Compile_Link_Lib/13 运行库实现/MiniCRTV4/src/string.cpp" -o CMakeFiles/minicrt.dir/string.cpp.s

src/CMakeFiles/minicrt.dir/iostream.cpp.o: src/CMakeFiles/minicrt.dir/flags.make
src/CMakeFiles/minicrt.dir/iostream.cpp.o: ../src/iostream.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/parallels/Stan/CodingCPlusPlus/NoteBook/Compile_Link_Lib/13 运行库实现/MiniCRTV4/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object src/CMakeFiles/minicrt.dir/iostream.cpp.o"
	cd "/home/parallels/Stan/CodingCPlusPlus/NoteBook/Compile_Link_Lib/13 运行库实现/MiniCRTV4/build/src" && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/minicrt.dir/iostream.cpp.o -c "/home/parallels/Stan/CodingCPlusPlus/NoteBook/Compile_Link_Lib/13 运行库实现/MiniCRTV4/src/iostream.cpp"

src/CMakeFiles/minicrt.dir/iostream.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/minicrt.dir/iostream.cpp.i"
	cd "/home/parallels/Stan/CodingCPlusPlus/NoteBook/Compile_Link_Lib/13 运行库实现/MiniCRTV4/build/src" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/parallels/Stan/CodingCPlusPlus/NoteBook/Compile_Link_Lib/13 运行库实现/MiniCRTV4/src/iostream.cpp" > CMakeFiles/minicrt.dir/iostream.cpp.i

src/CMakeFiles/minicrt.dir/iostream.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/minicrt.dir/iostream.cpp.s"
	cd "/home/parallels/Stan/CodingCPlusPlus/NoteBook/Compile_Link_Lib/13 运行库实现/MiniCRTV4/build/src" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/parallels/Stan/CodingCPlusPlus/NoteBook/Compile_Link_Lib/13 运行库实现/MiniCRTV4/src/iostream.cpp" -o CMakeFiles/minicrt.dir/iostream.cpp.s

# Object files for target minicrt
minicrt_OBJECTS = \
"CMakeFiles/minicrt.dir/entry.c.o" \
"CMakeFiles/minicrt.dir/format.c.o" \
"CMakeFiles/minicrt.dir/malloc.c.o" \
"CMakeFiles/minicrt.dir/stdio.c.o" \
"CMakeFiles/minicrt.dir/string.c.o" \
"CMakeFiles/minicrt.dir/cxxabi.cpp.o" \
"CMakeFiles/minicrt.dir/new_delete.cpp.o" \
"CMakeFiles/minicrt.dir/string.cpp.o" \
"CMakeFiles/minicrt.dir/iostream.cpp.o"

# External object files for target minicrt
minicrt_EXTERNAL_OBJECTS =

lib/libminicrt.a: src/CMakeFiles/minicrt.dir/entry.c.o
lib/libminicrt.a: src/CMakeFiles/minicrt.dir/format.c.o
lib/libminicrt.a: src/CMakeFiles/minicrt.dir/malloc.c.o
lib/libminicrt.a: src/CMakeFiles/minicrt.dir/stdio.c.o
lib/libminicrt.a: src/CMakeFiles/minicrt.dir/string.c.o
lib/libminicrt.a: src/CMakeFiles/minicrt.dir/cxxabi.cpp.o
lib/libminicrt.a: src/CMakeFiles/minicrt.dir/new_delete.cpp.o
lib/libminicrt.a: src/CMakeFiles/minicrt.dir/string.cpp.o
lib/libminicrt.a: src/CMakeFiles/minicrt.dir/iostream.cpp.o
lib/libminicrt.a: src/CMakeFiles/minicrt.dir/build.make
lib/libminicrt.a: src/CMakeFiles/minicrt.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/parallels/Stan/CodingCPlusPlus/NoteBook/Compile_Link_Lib/13 运行库实现/MiniCRTV4/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_10) "Linking CXX static library ../lib/libminicrt.a"
	cd "/home/parallels/Stan/CodingCPlusPlus/NoteBook/Compile_Link_Lib/13 运行库实现/MiniCRTV4/build/src" && $(CMAKE_COMMAND) -P CMakeFiles/minicrt.dir/cmake_clean_target.cmake
	cd "/home/parallels/Stan/CodingCPlusPlus/NoteBook/Compile_Link_Lib/13 运行库实现/MiniCRTV4/build/src" && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/minicrt.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/minicrt.dir/build: lib/libminicrt.a

.PHONY : src/CMakeFiles/minicrt.dir/build

src/CMakeFiles/minicrt.dir/clean:
	cd "/home/parallels/Stan/CodingCPlusPlus/NoteBook/Compile_Link_Lib/13 运行库实现/MiniCRTV4/build/src" && $(CMAKE_COMMAND) -P CMakeFiles/minicrt.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/minicrt.dir/clean

src/CMakeFiles/minicrt.dir/depend:
	cd "/home/parallels/Stan/CodingCPlusPlus/NoteBook/Compile_Link_Lib/13 运行库实现/MiniCRTV4/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/parallels/Stan/CodingCPlusPlus/NoteBook/Compile_Link_Lib/13 运行库实现/MiniCRTV4" "/home/parallels/Stan/CodingCPlusPlus/NoteBook/Compile_Link_Lib/13 运行库实现/MiniCRTV4/src" "/home/parallels/Stan/CodingCPlusPlus/NoteBook/Compile_Link_Lib/13 运行库实现/MiniCRTV4/build" "/home/parallels/Stan/CodingCPlusPlus/NoteBook/Compile_Link_Lib/13 运行库实现/MiniCRTV4/build/src" "/home/parallels/Stan/CodingCPlusPlus/NoteBook/Compile_Link_Lib/13 运行库实现/MiniCRTV4/build/src/CMakeFiles/minicrt.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : src/CMakeFiles/minicrt.dir/depend

