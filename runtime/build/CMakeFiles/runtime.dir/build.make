# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.0

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
CMAKE_SOURCE_DIR = /home/rustam/CppProjects/bmstu-refal-runtime/runtime

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/rustam/CppProjects/bmstu-refal-runtime/runtime/build

# Include any dependencies generated for this target.
include CMakeFiles/runtime.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/runtime.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/runtime.dir/flags.make

CMakeFiles/runtime.dir/sources/gc/gc.c.o: CMakeFiles/runtime.dir/flags.make
CMakeFiles/runtime.dir/sources/gc/gc.c.o: ../sources/gc/gc.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/rustam/CppProjects/bmstu-refal-runtime/runtime/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/runtime.dir/sources/gc/gc.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/runtime.dir/sources/gc/gc.c.o   -c /home/rustam/CppProjects/bmstu-refal-runtime/runtime/sources/gc/gc.c

CMakeFiles/runtime.dir/sources/gc/gc.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/runtime.dir/sources/gc/gc.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/rustam/CppProjects/bmstu-refal-runtime/runtime/sources/gc/gc.c > CMakeFiles/runtime.dir/sources/gc/gc.c.i

CMakeFiles/runtime.dir/sources/gc/gc.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/runtime.dir/sources/gc/gc.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/rustam/CppProjects/bmstu-refal-runtime/runtime/sources/gc/gc.c -o CMakeFiles/runtime.dir/sources/gc/gc.c.s

CMakeFiles/runtime.dir/sources/gc/gc.c.o.requires:
.PHONY : CMakeFiles/runtime.dir/sources/gc/gc.c.o.requires

CMakeFiles/runtime.dir/sources/gc/gc.c.o.provides: CMakeFiles/runtime.dir/sources/gc/gc.c.o.requires
	$(MAKE) -f CMakeFiles/runtime.dir/build.make CMakeFiles/runtime.dir/sources/gc/gc.c.o.provides.build
.PHONY : CMakeFiles/runtime.dir/sources/gc/gc.c.o.provides

CMakeFiles/runtime.dir/sources/gc/gc.c.o.provides.build: CMakeFiles/runtime.dir/sources/gc/gc.c.o

CMakeFiles/runtime.dir/sources/gc/vterm_gc.c.o: CMakeFiles/runtime.dir/flags.make
CMakeFiles/runtime.dir/sources/gc/vterm_gc.c.o: ../sources/gc/vterm_gc.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/rustam/CppProjects/bmstu-refal-runtime/runtime/build/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/runtime.dir/sources/gc/vterm_gc.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/runtime.dir/sources/gc/vterm_gc.c.o   -c /home/rustam/CppProjects/bmstu-refal-runtime/runtime/sources/gc/vterm_gc.c

CMakeFiles/runtime.dir/sources/gc/vterm_gc.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/runtime.dir/sources/gc/vterm_gc.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/rustam/CppProjects/bmstu-refal-runtime/runtime/sources/gc/vterm_gc.c > CMakeFiles/runtime.dir/sources/gc/vterm_gc.c.i

CMakeFiles/runtime.dir/sources/gc/vterm_gc.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/runtime.dir/sources/gc/vterm_gc.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/rustam/CppProjects/bmstu-refal-runtime/runtime/sources/gc/vterm_gc.c -o CMakeFiles/runtime.dir/sources/gc/vterm_gc.c.s

CMakeFiles/runtime.dir/sources/gc/vterm_gc.c.o.requires:
.PHONY : CMakeFiles/runtime.dir/sources/gc/vterm_gc.c.o.requires

CMakeFiles/runtime.dir/sources/gc/vterm_gc.c.o.provides: CMakeFiles/runtime.dir/sources/gc/vterm_gc.c.o.requires
	$(MAKE) -f CMakeFiles/runtime.dir/build.make CMakeFiles/runtime.dir/sources/gc/vterm_gc.c.o.provides.build
.PHONY : CMakeFiles/runtime.dir/sources/gc/vterm_gc.c.o.provides

CMakeFiles/runtime.dir/sources/gc/vterm_gc.c.o.provides.build: CMakeFiles/runtime.dir/sources/gc/vterm_gc.c.o

CMakeFiles/runtime.dir/sources/gc/data_gc.c.o: CMakeFiles/runtime.dir/flags.make
CMakeFiles/runtime.dir/sources/gc/data_gc.c.o: ../sources/gc/data_gc.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/rustam/CppProjects/bmstu-refal-runtime/runtime/build/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/runtime.dir/sources/gc/data_gc.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/runtime.dir/sources/gc/data_gc.c.o   -c /home/rustam/CppProjects/bmstu-refal-runtime/runtime/sources/gc/data_gc.c

CMakeFiles/runtime.dir/sources/gc/data_gc.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/runtime.dir/sources/gc/data_gc.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/rustam/CppProjects/bmstu-refal-runtime/runtime/sources/gc/data_gc.c > CMakeFiles/runtime.dir/sources/gc/data_gc.c.i

CMakeFiles/runtime.dir/sources/gc/data_gc.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/runtime.dir/sources/gc/data_gc.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/rustam/CppProjects/bmstu-refal-runtime/runtime/sources/gc/data_gc.c -o CMakeFiles/runtime.dir/sources/gc/data_gc.c.s

CMakeFiles/runtime.dir/sources/gc/data_gc.c.o.requires:
.PHONY : CMakeFiles/runtime.dir/sources/gc/data_gc.c.o.requires

CMakeFiles/runtime.dir/sources/gc/data_gc.c.o.provides: CMakeFiles/runtime.dir/sources/gc/data_gc.c.o.requires
	$(MAKE) -f CMakeFiles/runtime.dir/build.make CMakeFiles/runtime.dir/sources/gc/data_gc.c.o.provides.build
.PHONY : CMakeFiles/runtime.dir/sources/gc/data_gc.c.o.provides

CMakeFiles/runtime.dir/sources/gc/data_gc.c.o.provides.build: CMakeFiles/runtime.dir/sources/gc/data_gc.c.o

CMakeFiles/runtime.dir/sources/builtins/unicode_io.c.o: CMakeFiles/runtime.dir/flags.make
CMakeFiles/runtime.dir/sources/builtins/unicode_io.c.o: ../sources/builtins/unicode_io.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/rustam/CppProjects/bmstu-refal-runtime/runtime/build/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/runtime.dir/sources/builtins/unicode_io.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/runtime.dir/sources/builtins/unicode_io.c.o   -c /home/rustam/CppProjects/bmstu-refal-runtime/runtime/sources/builtins/unicode_io.c

CMakeFiles/runtime.dir/sources/builtins/unicode_io.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/runtime.dir/sources/builtins/unicode_io.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/rustam/CppProjects/bmstu-refal-runtime/runtime/sources/builtins/unicode_io.c > CMakeFiles/runtime.dir/sources/builtins/unicode_io.c.i

CMakeFiles/runtime.dir/sources/builtins/unicode_io.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/runtime.dir/sources/builtins/unicode_io.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/rustam/CppProjects/bmstu-refal-runtime/runtime/sources/builtins/unicode_io.c -o CMakeFiles/runtime.dir/sources/builtins/unicode_io.c.s

CMakeFiles/runtime.dir/sources/builtins/unicode_io.c.o.requires:
.PHONY : CMakeFiles/runtime.dir/sources/builtins/unicode_io.c.o.requires

CMakeFiles/runtime.dir/sources/builtins/unicode_io.c.o.provides: CMakeFiles/runtime.dir/sources/builtins/unicode_io.c.o.requires
	$(MAKE) -f CMakeFiles/runtime.dir/build.make CMakeFiles/runtime.dir/sources/builtins/unicode_io.c.o.provides.build
.PHONY : CMakeFiles/runtime.dir/sources/builtins/unicode_io.c.o.provides

CMakeFiles/runtime.dir/sources/builtins/unicode_io.c.o.provides.build: CMakeFiles/runtime.dir/sources/builtins/unicode_io.c.o

CMakeFiles/runtime.dir/sources/builtins/arithmetics.c.o: CMakeFiles/runtime.dir/flags.make
CMakeFiles/runtime.dir/sources/builtins/arithmetics.c.o: ../sources/builtins/arithmetics.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/rustam/CppProjects/bmstu-refal-runtime/runtime/build/CMakeFiles $(CMAKE_PROGRESS_5)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/runtime.dir/sources/builtins/arithmetics.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/runtime.dir/sources/builtins/arithmetics.c.o   -c /home/rustam/CppProjects/bmstu-refal-runtime/runtime/sources/builtins/arithmetics.c

CMakeFiles/runtime.dir/sources/builtins/arithmetics.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/runtime.dir/sources/builtins/arithmetics.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/rustam/CppProjects/bmstu-refal-runtime/runtime/sources/builtins/arithmetics.c > CMakeFiles/runtime.dir/sources/builtins/arithmetics.c.i

CMakeFiles/runtime.dir/sources/builtins/arithmetics.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/runtime.dir/sources/builtins/arithmetics.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/rustam/CppProjects/bmstu-refal-runtime/runtime/sources/builtins/arithmetics.c -o CMakeFiles/runtime.dir/sources/builtins/arithmetics.c.s

CMakeFiles/runtime.dir/sources/builtins/arithmetics.c.o.requires:
.PHONY : CMakeFiles/runtime.dir/sources/builtins/arithmetics.c.o.requires

CMakeFiles/runtime.dir/sources/builtins/arithmetics.c.o.provides: CMakeFiles/runtime.dir/sources/builtins/arithmetics.c.o.requires
	$(MAKE) -f CMakeFiles/runtime.dir/build.make CMakeFiles/runtime.dir/sources/builtins/arithmetics.c.o.provides.build
.PHONY : CMakeFiles/runtime.dir/sources/builtins/arithmetics.c.o.provides

CMakeFiles/runtime.dir/sources/builtins/arithmetics.c.o.provides.build: CMakeFiles/runtime.dir/sources/builtins/arithmetics.c.o

CMakeFiles/runtime.dir/sources/builtins/case_map_table.c.o: CMakeFiles/runtime.dir/flags.make
CMakeFiles/runtime.dir/sources/builtins/case_map_table.c.o: ../sources/builtins/case_map_table.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/rustam/CppProjects/bmstu-refal-runtime/runtime/build/CMakeFiles $(CMAKE_PROGRESS_6)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/runtime.dir/sources/builtins/case_map_table.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/runtime.dir/sources/builtins/case_map_table.c.o   -c /home/rustam/CppProjects/bmstu-refal-runtime/runtime/sources/builtins/case_map_table.c

CMakeFiles/runtime.dir/sources/builtins/case_map_table.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/runtime.dir/sources/builtins/case_map_table.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/rustam/CppProjects/bmstu-refal-runtime/runtime/sources/builtins/case_map_table.c > CMakeFiles/runtime.dir/sources/builtins/case_map_table.c.i

CMakeFiles/runtime.dir/sources/builtins/case_map_table.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/runtime.dir/sources/builtins/case_map_table.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/rustam/CppProjects/bmstu-refal-runtime/runtime/sources/builtins/case_map_table.c -o CMakeFiles/runtime.dir/sources/builtins/case_map_table.c.s

CMakeFiles/runtime.dir/sources/builtins/case_map_table.c.o.requires:
.PHONY : CMakeFiles/runtime.dir/sources/builtins/case_map_table.c.o.requires

CMakeFiles/runtime.dir/sources/builtins/case_map_table.c.o.provides: CMakeFiles/runtime.dir/sources/builtins/case_map_table.c.o.requires
	$(MAKE) -f CMakeFiles/runtime.dir/build.make CMakeFiles/runtime.dir/sources/builtins/case_map_table.c.o.provides.build
.PHONY : CMakeFiles/runtime.dir/sources/builtins/case_map_table.c.o.provides

CMakeFiles/runtime.dir/sources/builtins/case_map_table.c.o.provides.build: CMakeFiles/runtime.dir/sources/builtins/case_map_table.c.o

CMakeFiles/runtime.dir/sources/builtins/io_builtins.c.o: CMakeFiles/runtime.dir/flags.make
CMakeFiles/runtime.dir/sources/builtins/io_builtins.c.o: ../sources/builtins/io_builtins.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/rustam/CppProjects/bmstu-refal-runtime/runtime/build/CMakeFiles $(CMAKE_PROGRESS_7)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/runtime.dir/sources/builtins/io_builtins.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/runtime.dir/sources/builtins/io_builtins.c.o   -c /home/rustam/CppProjects/bmstu-refal-runtime/runtime/sources/builtins/io_builtins.c

CMakeFiles/runtime.dir/sources/builtins/io_builtins.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/runtime.dir/sources/builtins/io_builtins.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/rustam/CppProjects/bmstu-refal-runtime/runtime/sources/builtins/io_builtins.c > CMakeFiles/runtime.dir/sources/builtins/io_builtins.c.i

CMakeFiles/runtime.dir/sources/builtins/io_builtins.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/runtime.dir/sources/builtins/io_builtins.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/rustam/CppProjects/bmstu-refal-runtime/runtime/sources/builtins/io_builtins.c -o CMakeFiles/runtime.dir/sources/builtins/io_builtins.c.s

CMakeFiles/runtime.dir/sources/builtins/io_builtins.c.o.requires:
.PHONY : CMakeFiles/runtime.dir/sources/builtins/io_builtins.c.o.requires

CMakeFiles/runtime.dir/sources/builtins/io_builtins.c.o.provides: CMakeFiles/runtime.dir/sources/builtins/io_builtins.c.o.requires
	$(MAKE) -f CMakeFiles/runtime.dir/build.make CMakeFiles/runtime.dir/sources/builtins/io_builtins.c.o.provides.build
.PHONY : CMakeFiles/runtime.dir/sources/builtins/io_builtins.c.o.provides

CMakeFiles/runtime.dir/sources/builtins/io_builtins.c.o.provides.build: CMakeFiles/runtime.dir/sources/builtins/io_builtins.c.o

CMakeFiles/runtime.dir/sources/builtins/slib.c.o: CMakeFiles/runtime.dir/flags.make
CMakeFiles/runtime.dir/sources/builtins/slib.c.o: ../sources/builtins/slib.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/rustam/CppProjects/bmstu-refal-runtime/runtime/build/CMakeFiles $(CMAKE_PROGRESS_8)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/runtime.dir/sources/builtins/slib.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/runtime.dir/sources/builtins/slib.c.o   -c /home/rustam/CppProjects/bmstu-refal-runtime/runtime/sources/builtins/slib.c

CMakeFiles/runtime.dir/sources/builtins/slib.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/runtime.dir/sources/builtins/slib.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/rustam/CppProjects/bmstu-refal-runtime/runtime/sources/builtins/slib.c > CMakeFiles/runtime.dir/sources/builtins/slib.c.i

CMakeFiles/runtime.dir/sources/builtins/slib.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/runtime.dir/sources/builtins/slib.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/rustam/CppProjects/bmstu-refal-runtime/runtime/sources/builtins/slib.c -o CMakeFiles/runtime.dir/sources/builtins/slib.c.s

CMakeFiles/runtime.dir/sources/builtins/slib.c.o.requires:
.PHONY : CMakeFiles/runtime.dir/sources/builtins/slib.c.o.requires

CMakeFiles/runtime.dir/sources/builtins/slib.c.o.provides: CMakeFiles/runtime.dir/sources/builtins/slib.c.o.requires
	$(MAKE) -f CMakeFiles/runtime.dir/build.make CMakeFiles/runtime.dir/sources/builtins/slib.c.o.provides.build
.PHONY : CMakeFiles/runtime.dir/sources/builtins/slib.c.o.provides

CMakeFiles/runtime.dir/sources/builtins/slib.c.o.provides.build: CMakeFiles/runtime.dir/sources/builtins/slib.c.o

CMakeFiles/runtime.dir/sources/vmachine.c.o: CMakeFiles/runtime.dir/flags.make
CMakeFiles/runtime.dir/sources/vmachine.c.o: ../sources/vmachine.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/rustam/CppProjects/bmstu-refal-runtime/runtime/build/CMakeFiles $(CMAKE_PROGRESS_9)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/runtime.dir/sources/vmachine.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/runtime.dir/sources/vmachine.c.o   -c /home/rustam/CppProjects/bmstu-refal-runtime/runtime/sources/vmachine.c

CMakeFiles/runtime.dir/sources/vmachine.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/runtime.dir/sources/vmachine.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/rustam/CppProjects/bmstu-refal-runtime/runtime/sources/vmachine.c > CMakeFiles/runtime.dir/sources/vmachine.c.i

CMakeFiles/runtime.dir/sources/vmachine.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/runtime.dir/sources/vmachine.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/rustam/CppProjects/bmstu-refal-runtime/runtime/sources/vmachine.c -o CMakeFiles/runtime.dir/sources/vmachine.c.s

CMakeFiles/runtime.dir/sources/vmachine.c.o.requires:
.PHONY : CMakeFiles/runtime.dir/sources/vmachine.c.o.requires

CMakeFiles/runtime.dir/sources/vmachine.c.o.provides: CMakeFiles/runtime.dir/sources/vmachine.c.o.requires
	$(MAKE) -f CMakeFiles/runtime.dir/build.make CMakeFiles/runtime.dir/sources/vmachine.c.o.provides.build
.PHONY : CMakeFiles/runtime.dir/sources/vmachine.c.o.provides

CMakeFiles/runtime.dir/sources/vmachine.c.o.provides.build: CMakeFiles/runtime.dir/sources/vmachine.c.o

CMakeFiles/runtime.dir/sources/memory_manager.c.o: CMakeFiles/runtime.dir/flags.make
CMakeFiles/runtime.dir/sources/memory_manager.c.o: ../sources/memory_manager.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/rustam/CppProjects/bmstu-refal-runtime/runtime/build/CMakeFiles $(CMAKE_PROGRESS_10)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/runtime.dir/sources/memory_manager.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/runtime.dir/sources/memory_manager.c.o   -c /home/rustam/CppProjects/bmstu-refal-runtime/runtime/sources/memory_manager.c

CMakeFiles/runtime.dir/sources/memory_manager.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/runtime.dir/sources/memory_manager.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/rustam/CppProjects/bmstu-refal-runtime/runtime/sources/memory_manager.c > CMakeFiles/runtime.dir/sources/memory_manager.c.i

CMakeFiles/runtime.dir/sources/memory_manager.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/runtime.dir/sources/memory_manager.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/rustam/CppProjects/bmstu-refal-runtime/runtime/sources/memory_manager.c -o CMakeFiles/runtime.dir/sources/memory_manager.c.s

CMakeFiles/runtime.dir/sources/memory_manager.c.o.requires:
.PHONY : CMakeFiles/runtime.dir/sources/memory_manager.c.o.requires

CMakeFiles/runtime.dir/sources/memory_manager.c.o.provides: CMakeFiles/runtime.dir/sources/memory_manager.c.o.requires
	$(MAKE) -f CMakeFiles/runtime.dir/build.make CMakeFiles/runtime.dir/sources/memory_manager.c.o.provides.build
.PHONY : CMakeFiles/runtime.dir/sources/memory_manager.c.o.provides

CMakeFiles/runtime.dir/sources/memory_manager.c.o.provides.build: CMakeFiles/runtime.dir/sources/memory_manager.c.o

CMakeFiles/runtime.dir/sources/allocators/data_alloc.c.o: CMakeFiles/runtime.dir/flags.make
CMakeFiles/runtime.dir/sources/allocators/data_alloc.c.o: ../sources/allocators/data_alloc.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/rustam/CppProjects/bmstu-refal-runtime/runtime/build/CMakeFiles $(CMAKE_PROGRESS_11)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/runtime.dir/sources/allocators/data_alloc.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/runtime.dir/sources/allocators/data_alloc.c.o   -c /home/rustam/CppProjects/bmstu-refal-runtime/runtime/sources/allocators/data_alloc.c

CMakeFiles/runtime.dir/sources/allocators/data_alloc.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/runtime.dir/sources/allocators/data_alloc.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/rustam/CppProjects/bmstu-refal-runtime/runtime/sources/allocators/data_alloc.c > CMakeFiles/runtime.dir/sources/allocators/data_alloc.c.i

CMakeFiles/runtime.dir/sources/allocators/data_alloc.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/runtime.dir/sources/allocators/data_alloc.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/rustam/CppProjects/bmstu-refal-runtime/runtime/sources/allocators/data_alloc.c -o CMakeFiles/runtime.dir/sources/allocators/data_alloc.c.s

CMakeFiles/runtime.dir/sources/allocators/data_alloc.c.o.requires:
.PHONY : CMakeFiles/runtime.dir/sources/allocators/data_alloc.c.o.requires

CMakeFiles/runtime.dir/sources/allocators/data_alloc.c.o.provides: CMakeFiles/runtime.dir/sources/allocators/data_alloc.c.o.requires
	$(MAKE) -f CMakeFiles/runtime.dir/build.make CMakeFiles/runtime.dir/sources/allocators/data_alloc.c.o.provides.build
.PHONY : CMakeFiles/runtime.dir/sources/allocators/data_alloc.c.o.provides

CMakeFiles/runtime.dir/sources/allocators/data_alloc.c.o.provides.build: CMakeFiles/runtime.dir/sources/allocators/data_alloc.c.o

CMakeFiles/runtime.dir/sources/allocators/vterm_alloc.c.o: CMakeFiles/runtime.dir/flags.make
CMakeFiles/runtime.dir/sources/allocators/vterm_alloc.c.o: ../sources/allocators/vterm_alloc.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/rustam/CppProjects/bmstu-refal-runtime/runtime/build/CMakeFiles $(CMAKE_PROGRESS_12)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/runtime.dir/sources/allocators/vterm_alloc.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/runtime.dir/sources/allocators/vterm_alloc.c.o   -c /home/rustam/CppProjects/bmstu-refal-runtime/runtime/sources/allocators/vterm_alloc.c

CMakeFiles/runtime.dir/sources/allocators/vterm_alloc.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/runtime.dir/sources/allocators/vterm_alloc.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/rustam/CppProjects/bmstu-refal-runtime/runtime/sources/allocators/vterm_alloc.c > CMakeFiles/runtime.dir/sources/allocators/vterm_alloc.c.i

CMakeFiles/runtime.dir/sources/allocators/vterm_alloc.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/runtime.dir/sources/allocators/vterm_alloc.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/rustam/CppProjects/bmstu-refal-runtime/runtime/sources/allocators/vterm_alloc.c -o CMakeFiles/runtime.dir/sources/allocators/vterm_alloc.c.s

CMakeFiles/runtime.dir/sources/allocators/vterm_alloc.c.o.requires:
.PHONY : CMakeFiles/runtime.dir/sources/allocators/vterm_alloc.c.o.requires

CMakeFiles/runtime.dir/sources/allocators/vterm_alloc.c.o.provides: CMakeFiles/runtime.dir/sources/allocators/vterm_alloc.c.o.requires
	$(MAKE) -f CMakeFiles/runtime.dir/build.make CMakeFiles/runtime.dir/sources/allocators/vterm_alloc.c.o.provides.build
.PHONY : CMakeFiles/runtime.dir/sources/allocators/vterm_alloc.c.o.provides

CMakeFiles/runtime.dir/sources/allocators/vterm_alloc.c.o.provides.build: CMakeFiles/runtime.dir/sources/allocators/vterm_alloc.c.o

CMakeFiles/runtime.dir/sources/to_string.c.o: CMakeFiles/runtime.dir/flags.make
CMakeFiles/runtime.dir/sources/to_string.c.o: ../sources/to_string.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/rustam/CppProjects/bmstu-refal-runtime/runtime/build/CMakeFiles $(CMAKE_PROGRESS_13)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/runtime.dir/sources/to_string.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/runtime.dir/sources/to_string.c.o   -c /home/rustam/CppProjects/bmstu-refal-runtime/runtime/sources/to_string.c

CMakeFiles/runtime.dir/sources/to_string.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/runtime.dir/sources/to_string.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/rustam/CppProjects/bmstu-refal-runtime/runtime/sources/to_string.c > CMakeFiles/runtime.dir/sources/to_string.c.i

CMakeFiles/runtime.dir/sources/to_string.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/runtime.dir/sources/to_string.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/rustam/CppProjects/bmstu-refal-runtime/runtime/sources/to_string.c -o CMakeFiles/runtime.dir/sources/to_string.c.s

CMakeFiles/runtime.dir/sources/to_string.c.o.requires:
.PHONY : CMakeFiles/runtime.dir/sources/to_string.c.o.requires

CMakeFiles/runtime.dir/sources/to_string.c.o.provides: CMakeFiles/runtime.dir/sources/to_string.c.o.requires
	$(MAKE) -f CMakeFiles/runtime.dir/build.make CMakeFiles/runtime.dir/sources/to_string.c.o.provides.build
.PHONY : CMakeFiles/runtime.dir/sources/to_string.c.o.provides

CMakeFiles/runtime.dir/sources/to_string.c.o.provides.build: CMakeFiles/runtime.dir/sources/to_string.c.o

# Object files for target runtime
runtime_OBJECTS = \
"CMakeFiles/runtime.dir/sources/gc/gc.c.o" \
"CMakeFiles/runtime.dir/sources/gc/vterm_gc.c.o" \
"CMakeFiles/runtime.dir/sources/gc/data_gc.c.o" \
"CMakeFiles/runtime.dir/sources/builtins/unicode_io.c.o" \
"CMakeFiles/runtime.dir/sources/builtins/arithmetics.c.o" \
"CMakeFiles/runtime.dir/sources/builtins/case_map_table.c.o" \
"CMakeFiles/runtime.dir/sources/builtins/io_builtins.c.o" \
"CMakeFiles/runtime.dir/sources/builtins/slib.c.o" \
"CMakeFiles/runtime.dir/sources/vmachine.c.o" \
"CMakeFiles/runtime.dir/sources/memory_manager.c.o" \
"CMakeFiles/runtime.dir/sources/allocators/data_alloc.c.o" \
"CMakeFiles/runtime.dir/sources/allocators/vterm_alloc.c.o" \
"CMakeFiles/runtime.dir/sources/to_string.c.o"

# External object files for target runtime
runtime_EXTERNAL_OBJECTS =

libruntime.a: CMakeFiles/runtime.dir/sources/gc/gc.c.o
libruntime.a: CMakeFiles/runtime.dir/sources/gc/vterm_gc.c.o
libruntime.a: CMakeFiles/runtime.dir/sources/gc/data_gc.c.o
libruntime.a: CMakeFiles/runtime.dir/sources/builtins/unicode_io.c.o
libruntime.a: CMakeFiles/runtime.dir/sources/builtins/arithmetics.c.o
libruntime.a: CMakeFiles/runtime.dir/sources/builtins/case_map_table.c.o
libruntime.a: CMakeFiles/runtime.dir/sources/builtins/io_builtins.c.o
libruntime.a: CMakeFiles/runtime.dir/sources/builtins/slib.c.o
libruntime.a: CMakeFiles/runtime.dir/sources/vmachine.c.o
libruntime.a: CMakeFiles/runtime.dir/sources/memory_manager.c.o
libruntime.a: CMakeFiles/runtime.dir/sources/allocators/data_alloc.c.o
libruntime.a: CMakeFiles/runtime.dir/sources/allocators/vterm_alloc.c.o
libruntime.a: CMakeFiles/runtime.dir/sources/to_string.c.o
libruntime.a: CMakeFiles/runtime.dir/build.make
libruntime.a: CMakeFiles/runtime.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C static library libruntime.a"
	$(CMAKE_COMMAND) -P CMakeFiles/runtime.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/runtime.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/runtime.dir/build: libruntime.a
.PHONY : CMakeFiles/runtime.dir/build

CMakeFiles/runtime.dir/requires: CMakeFiles/runtime.dir/sources/gc/gc.c.o.requires
CMakeFiles/runtime.dir/requires: CMakeFiles/runtime.dir/sources/gc/vterm_gc.c.o.requires
CMakeFiles/runtime.dir/requires: CMakeFiles/runtime.dir/sources/gc/data_gc.c.o.requires
CMakeFiles/runtime.dir/requires: CMakeFiles/runtime.dir/sources/builtins/unicode_io.c.o.requires
CMakeFiles/runtime.dir/requires: CMakeFiles/runtime.dir/sources/builtins/arithmetics.c.o.requires
CMakeFiles/runtime.dir/requires: CMakeFiles/runtime.dir/sources/builtins/case_map_table.c.o.requires
CMakeFiles/runtime.dir/requires: CMakeFiles/runtime.dir/sources/builtins/io_builtins.c.o.requires
CMakeFiles/runtime.dir/requires: CMakeFiles/runtime.dir/sources/builtins/slib.c.o.requires
CMakeFiles/runtime.dir/requires: CMakeFiles/runtime.dir/sources/vmachine.c.o.requires
CMakeFiles/runtime.dir/requires: CMakeFiles/runtime.dir/sources/memory_manager.c.o.requires
CMakeFiles/runtime.dir/requires: CMakeFiles/runtime.dir/sources/allocators/data_alloc.c.o.requires
CMakeFiles/runtime.dir/requires: CMakeFiles/runtime.dir/sources/allocators/vterm_alloc.c.o.requires
CMakeFiles/runtime.dir/requires: CMakeFiles/runtime.dir/sources/to_string.c.o.requires
.PHONY : CMakeFiles/runtime.dir/requires

CMakeFiles/runtime.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/runtime.dir/cmake_clean.cmake
.PHONY : CMakeFiles/runtime.dir/clean

CMakeFiles/runtime.dir/depend:
	cd /home/rustam/CppProjects/bmstu-refal-runtime/runtime/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/rustam/CppProjects/bmstu-refal-runtime/runtime /home/rustam/CppProjects/bmstu-refal-runtime/runtime /home/rustam/CppProjects/bmstu-refal-runtime/runtime/build /home/rustam/CppProjects/bmstu-refal-runtime/runtime/build /home/rustam/CppProjects/bmstu-refal-runtime/runtime/build/CMakeFiles/runtime.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/runtime.dir/depend

