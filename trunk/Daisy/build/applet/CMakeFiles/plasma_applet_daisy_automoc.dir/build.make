# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/shared/Daisy

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/shared/Daisy/build

# Utility rule file for plasma_applet_daisy_automoc.

# Include the progress variables for this target.
include applet/CMakeFiles/plasma_applet_daisy_automoc.dir/progress.make

applet/CMakeFiles/plasma_applet_daisy_automoc:
	cd /home/shared/Daisy/build/applet && /usr/bin/automoc4 /home/shared/Daisy/build/applet/plasma_applet_daisy_automoc.cpp /home/shared/Daisy/applet /home/shared/Daisy/build/applet /usr/bin/moc-qt4 /usr/bin/cmake

plasma_applet_daisy_automoc: applet/CMakeFiles/plasma_applet_daisy_automoc
plasma_applet_daisy_automoc: applet/CMakeFiles/plasma_applet_daisy_automoc.dir/build.make
.PHONY : plasma_applet_daisy_automoc

# Rule to build all files generated by this target.
applet/CMakeFiles/plasma_applet_daisy_automoc.dir/build: plasma_applet_daisy_automoc
.PHONY : applet/CMakeFiles/plasma_applet_daisy_automoc.dir/build

applet/CMakeFiles/plasma_applet_daisy_automoc.dir/clean:
	cd /home/shared/Daisy/build/applet && $(CMAKE_COMMAND) -P CMakeFiles/plasma_applet_daisy_automoc.dir/cmake_clean.cmake
.PHONY : applet/CMakeFiles/plasma_applet_daisy_automoc.dir/clean

applet/CMakeFiles/plasma_applet_daisy_automoc.dir/depend:
	cd /home/shared/Daisy/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/shared/Daisy /home/shared/Daisy/applet /home/shared/Daisy/build /home/shared/Daisy/build/applet /home/shared/Daisy/build/applet/CMakeFiles/plasma_applet_daisy_automoc.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : applet/CMakeFiles/plasma_applet_daisy_automoc.dir/depend
