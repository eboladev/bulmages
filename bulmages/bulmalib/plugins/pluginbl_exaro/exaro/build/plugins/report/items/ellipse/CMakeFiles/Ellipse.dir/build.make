# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canoncical targets will work.
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
CMAKE_SOURCE_DIR = /home/tborras/exaro/exaro

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/tborras/exaro/exaro/build

# Include any dependencies generated for this target.
include plugins/report/items/ellipse/CMakeFiles/Ellipse.dir/depend.make

# Include the progress variables for this target.
include plugins/report/items/ellipse/CMakeFiles/Ellipse.dir/progress.make

# Include the compile flags for this target's objects.
include plugins/report/items/ellipse/CMakeFiles/Ellipse.dir/flags.make

plugins/report/items/ellipse/CMakeFiles/Ellipse.dir/ellipse.cpp.o: plugins/report/items/ellipse/CMakeFiles/Ellipse.dir/flags.make
plugins/report/items/ellipse/CMakeFiles/Ellipse.dir/ellipse.cpp.o: ../plugins/report/items/ellipse/ellipse.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/tborras/exaro/exaro/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object plugins/report/items/ellipse/CMakeFiles/Ellipse.dir/ellipse.cpp.o"
	cd /home/tborras/exaro/exaro/build/plugins/report/items/ellipse && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/Ellipse.dir/ellipse.cpp.o -c /home/tborras/exaro/exaro/plugins/report/items/ellipse/ellipse.cpp

plugins/report/items/ellipse/CMakeFiles/Ellipse.dir/ellipse.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Ellipse.dir/ellipse.cpp.i"
	cd /home/tborras/exaro/exaro/build/plugins/report/items/ellipse && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/tborras/exaro/exaro/plugins/report/items/ellipse/ellipse.cpp > CMakeFiles/Ellipse.dir/ellipse.cpp.i

plugins/report/items/ellipse/CMakeFiles/Ellipse.dir/ellipse.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Ellipse.dir/ellipse.cpp.s"
	cd /home/tborras/exaro/exaro/build/plugins/report/items/ellipse && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/tborras/exaro/exaro/plugins/report/items/ellipse/ellipse.cpp -o CMakeFiles/Ellipse.dir/ellipse.cpp.s

plugins/report/items/ellipse/CMakeFiles/Ellipse.dir/ellipse.cpp.o.requires:
.PHONY : plugins/report/items/ellipse/CMakeFiles/Ellipse.dir/ellipse.cpp.o.requires

plugins/report/items/ellipse/CMakeFiles/Ellipse.dir/ellipse.cpp.o.provides: plugins/report/items/ellipse/CMakeFiles/Ellipse.dir/ellipse.cpp.o.requires
	$(MAKE) -f plugins/report/items/ellipse/CMakeFiles/Ellipse.dir/build.make plugins/report/items/ellipse/CMakeFiles/Ellipse.dir/ellipse.cpp.o.provides.build
.PHONY : plugins/report/items/ellipse/CMakeFiles/Ellipse.dir/ellipse.cpp.o.provides

plugins/report/items/ellipse/CMakeFiles/Ellipse.dir/ellipse.cpp.o.provides.build: plugins/report/items/ellipse/CMakeFiles/Ellipse.dir/ellipse.cpp.o
.PHONY : plugins/report/items/ellipse/CMakeFiles/Ellipse.dir/ellipse.cpp.o.provides.build

plugins/report/items/ellipse/CMakeFiles/Ellipse.dir/moc_ellipse.cxx.o: plugins/report/items/ellipse/CMakeFiles/Ellipse.dir/flags.make
plugins/report/items/ellipse/CMakeFiles/Ellipse.dir/moc_ellipse.cxx.o: plugins/report/items/ellipse/moc_ellipse.cxx
	$(CMAKE_COMMAND) -E cmake_progress_report /home/tborras/exaro/exaro/build/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object plugins/report/items/ellipse/CMakeFiles/Ellipse.dir/moc_ellipse.cxx.o"
	cd /home/tborras/exaro/exaro/build/plugins/report/items/ellipse && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/Ellipse.dir/moc_ellipse.cxx.o -c /home/tborras/exaro/exaro/build/plugins/report/items/ellipse/moc_ellipse.cxx

plugins/report/items/ellipse/CMakeFiles/Ellipse.dir/moc_ellipse.cxx.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Ellipse.dir/moc_ellipse.cxx.i"
	cd /home/tborras/exaro/exaro/build/plugins/report/items/ellipse && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/tborras/exaro/exaro/build/plugins/report/items/ellipse/moc_ellipse.cxx > CMakeFiles/Ellipse.dir/moc_ellipse.cxx.i

plugins/report/items/ellipse/CMakeFiles/Ellipse.dir/moc_ellipse.cxx.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Ellipse.dir/moc_ellipse.cxx.s"
	cd /home/tborras/exaro/exaro/build/plugins/report/items/ellipse && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/tborras/exaro/exaro/build/plugins/report/items/ellipse/moc_ellipse.cxx -o CMakeFiles/Ellipse.dir/moc_ellipse.cxx.s

plugins/report/items/ellipse/CMakeFiles/Ellipse.dir/moc_ellipse.cxx.o.requires:
.PHONY : plugins/report/items/ellipse/CMakeFiles/Ellipse.dir/moc_ellipse.cxx.o.requires

plugins/report/items/ellipse/CMakeFiles/Ellipse.dir/moc_ellipse.cxx.o.provides: plugins/report/items/ellipse/CMakeFiles/Ellipse.dir/moc_ellipse.cxx.o.requires
	$(MAKE) -f plugins/report/items/ellipse/CMakeFiles/Ellipse.dir/build.make plugins/report/items/ellipse/CMakeFiles/Ellipse.dir/moc_ellipse.cxx.o.provides.build
.PHONY : plugins/report/items/ellipse/CMakeFiles/Ellipse.dir/moc_ellipse.cxx.o.provides

plugins/report/items/ellipse/CMakeFiles/Ellipse.dir/moc_ellipse.cxx.o.provides.build: plugins/report/items/ellipse/CMakeFiles/Ellipse.dir/moc_ellipse.cxx.o
.PHONY : plugins/report/items/ellipse/CMakeFiles/Ellipse.dir/moc_ellipse.cxx.o.provides.build

plugins/report/items/ellipse/CMakeFiles/Ellipse.dir/qrc_ellipse.cxx.o: plugins/report/items/ellipse/CMakeFiles/Ellipse.dir/flags.make
plugins/report/items/ellipse/CMakeFiles/Ellipse.dir/qrc_ellipse.cxx.o: plugins/report/items/ellipse/qrc_ellipse.cxx
	$(CMAKE_COMMAND) -E cmake_progress_report /home/tborras/exaro/exaro/build/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object plugins/report/items/ellipse/CMakeFiles/Ellipse.dir/qrc_ellipse.cxx.o"
	cd /home/tborras/exaro/exaro/build/plugins/report/items/ellipse && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/Ellipse.dir/qrc_ellipse.cxx.o -c /home/tborras/exaro/exaro/build/plugins/report/items/ellipse/qrc_ellipse.cxx

plugins/report/items/ellipse/CMakeFiles/Ellipse.dir/qrc_ellipse.cxx.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Ellipse.dir/qrc_ellipse.cxx.i"
	cd /home/tborras/exaro/exaro/build/plugins/report/items/ellipse && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/tborras/exaro/exaro/build/plugins/report/items/ellipse/qrc_ellipse.cxx > CMakeFiles/Ellipse.dir/qrc_ellipse.cxx.i

plugins/report/items/ellipse/CMakeFiles/Ellipse.dir/qrc_ellipse.cxx.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Ellipse.dir/qrc_ellipse.cxx.s"
	cd /home/tborras/exaro/exaro/build/plugins/report/items/ellipse && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/tborras/exaro/exaro/build/plugins/report/items/ellipse/qrc_ellipse.cxx -o CMakeFiles/Ellipse.dir/qrc_ellipse.cxx.s

plugins/report/items/ellipse/CMakeFiles/Ellipse.dir/qrc_ellipse.cxx.o.requires:
.PHONY : plugins/report/items/ellipse/CMakeFiles/Ellipse.dir/qrc_ellipse.cxx.o.requires

plugins/report/items/ellipse/CMakeFiles/Ellipse.dir/qrc_ellipse.cxx.o.provides: plugins/report/items/ellipse/CMakeFiles/Ellipse.dir/qrc_ellipse.cxx.o.requires
	$(MAKE) -f plugins/report/items/ellipse/CMakeFiles/Ellipse.dir/build.make plugins/report/items/ellipse/CMakeFiles/Ellipse.dir/qrc_ellipse.cxx.o.provides.build
.PHONY : plugins/report/items/ellipse/CMakeFiles/Ellipse.dir/qrc_ellipse.cxx.o.provides

plugins/report/items/ellipse/CMakeFiles/Ellipse.dir/qrc_ellipse.cxx.o.provides.build: plugins/report/items/ellipse/CMakeFiles/Ellipse.dir/qrc_ellipse.cxx.o
.PHONY : plugins/report/items/ellipse/CMakeFiles/Ellipse.dir/qrc_ellipse.cxx.o.provides.build

plugins/report/items/ellipse/moc_ellipse.cxx: ../plugins/report/items/ellipse/ellipse.h
	$(CMAKE_COMMAND) -E cmake_progress_report /home/tborras/exaro/exaro/build/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Generating moc_ellipse.cxx"
	cd /home/tborras/exaro/exaro/build/plugins/report/items/ellipse && /usr/bin/moc-qt4 -I/home/tborras/exaro/exaro/libs/report -I/usr/include/qt4 -I/usr/include/qt4/QtOpenGL -I/usr/include/qt4/QtScript -I/usr/include/qt4/QtUiTools -I/usr/include/qt4/QtWebKit -I/usr/include/qt4/QtGui -I/usr/include/qt4/QtXml -I/usr/include/qt4/QtSql -I/usr/include/qt4/QtCore -I/home/tborras/exaro/exaro -I/home/tborras/exaro/exaro/build -DEXARO_VERSION="2.0.0" -DQT_OPENGL_LIB -DQT_SCRIPT_LIB -DQT_UITOOLS_LIB -DQT_WEBKIT_LIB -DQT_GUI_LIB -DQT_XML_LIB -DQT_SQL_LIB -DQT_CORE_LIB -DLIB_INSTALL_DIR="/usr/local/lib" -o /home/tborras/exaro/exaro/build/plugins/report/items/ellipse/moc_ellipse.cxx /home/tborras/exaro/exaro/plugins/report/items/ellipse/ellipse.h

plugins/report/items/ellipse/qrc_ellipse.cxx: ../plugins/report/items/ellipse/ellipse.png
plugins/report/items/ellipse/qrc_ellipse.cxx: ../plugins/report/items/ellipse/ellipse.qrc
	$(CMAKE_COMMAND) -E cmake_progress_report /home/tborras/exaro/exaro/build/CMakeFiles $(CMAKE_PROGRESS_5)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Generating qrc_ellipse.cxx"
	cd /home/tborras/exaro/exaro/build/plugins/report/items/ellipse && /usr/bin/rcc -name ellipse -o /home/tborras/exaro/exaro/build/plugins/report/items/ellipse/qrc_ellipse.cxx /home/tborras/exaro/exaro/plugins/report/items/ellipse/ellipse.qrc

# Object files for target Ellipse
Ellipse_OBJECTS = \
"CMakeFiles/Ellipse.dir/ellipse.cpp.o" \
"CMakeFiles/Ellipse.dir/moc_ellipse.cxx.o" \
"CMakeFiles/Ellipse.dir/qrc_ellipse.cxx.o"

# External object files for target Ellipse
Ellipse_EXTERNAL_OBJECTS =

plugins/report/items/ellipse/libEllipse.so: plugins/report/items/ellipse/CMakeFiles/Ellipse.dir/ellipse.cpp.o
plugins/report/items/ellipse/libEllipse.so: plugins/report/items/ellipse/CMakeFiles/Ellipse.dir/moc_ellipse.cxx.o
plugins/report/items/ellipse/libEllipse.so: plugins/report/items/ellipse/CMakeFiles/Ellipse.dir/qrc_ellipse.cxx.o
plugins/report/items/ellipse/libEllipse.so: libs/report/libReport.so.2.0.0
plugins/report/items/ellipse/libEllipse.so: /usr/lib/libQtOpenGL.so
plugins/report/items/ellipse/libEllipse.so: /usr/lib/libQtScript.so
plugins/report/items/ellipse/libEllipse.so: /usr/lib/libQtUiTools.a
plugins/report/items/ellipse/libEllipse.so: /usr/lib/libQtWebKit.so
plugins/report/items/ellipse/libEllipse.so: /usr/lib/libQtGui.so
plugins/report/items/ellipse/libEllipse.so: /usr/lib/libQtXml.so
plugins/report/items/ellipse/libEllipse.so: /usr/lib/libQtSql.so
plugins/report/items/ellipse/libEllipse.so: /usr/lib/libQtXmlPatterns.so
plugins/report/items/ellipse/libEllipse.so: /usr/lib/libQtNetwork.so
plugins/report/items/ellipse/libEllipse.so: /usr/lib/libQtCore.so
plugins/report/items/ellipse/libEllipse.so: plugins/report/items/ellipse/CMakeFiles/Ellipse.dir/build.make
plugins/report/items/ellipse/libEllipse.so: plugins/report/items/ellipse/CMakeFiles/Ellipse.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX shared library libEllipse.so"
	cd /home/tborras/exaro/exaro/build/plugins/report/items/ellipse && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Ellipse.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
plugins/report/items/ellipse/CMakeFiles/Ellipse.dir/build: plugins/report/items/ellipse/libEllipse.so
.PHONY : plugins/report/items/ellipse/CMakeFiles/Ellipse.dir/build

plugins/report/items/ellipse/CMakeFiles/Ellipse.dir/requires: plugins/report/items/ellipse/CMakeFiles/Ellipse.dir/ellipse.cpp.o.requires
plugins/report/items/ellipse/CMakeFiles/Ellipse.dir/requires: plugins/report/items/ellipse/CMakeFiles/Ellipse.dir/moc_ellipse.cxx.o.requires
plugins/report/items/ellipse/CMakeFiles/Ellipse.dir/requires: plugins/report/items/ellipse/CMakeFiles/Ellipse.dir/qrc_ellipse.cxx.o.requires
.PHONY : plugins/report/items/ellipse/CMakeFiles/Ellipse.dir/requires

plugins/report/items/ellipse/CMakeFiles/Ellipse.dir/clean:
	cd /home/tborras/exaro/exaro/build/plugins/report/items/ellipse && $(CMAKE_COMMAND) -P CMakeFiles/Ellipse.dir/cmake_clean.cmake
.PHONY : plugins/report/items/ellipse/CMakeFiles/Ellipse.dir/clean

plugins/report/items/ellipse/CMakeFiles/Ellipse.dir/depend: plugins/report/items/ellipse/moc_ellipse.cxx
plugins/report/items/ellipse/CMakeFiles/Ellipse.dir/depend: plugins/report/items/ellipse/qrc_ellipse.cxx
	cd /home/tborras/exaro/exaro/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/tborras/exaro/exaro /home/tborras/exaro/exaro/plugins/report/items/ellipse /home/tborras/exaro/exaro/build /home/tborras/exaro/exaro/build/plugins/report/items/ellipse /home/tborras/exaro/exaro/build/plugins/report/items/ellipse/CMakeFiles/Ellipse.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : plugins/report/items/ellipse/CMakeFiles/Ellipse.dir/depend
