# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.12

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
CMAKE_COMMAND = /home/ubuntu/Sitlos/cmake-3.12.1/bin/cmake

# The command to remove a file.
RM = /home/ubuntu/Sitlos/cmake-3.12.1/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/ubuntu/Sitlos/UserServer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ubuntu/Sitlos/UserServer/build

# Include any dependencies generated for this target.
include CMakeFiles/UserServer.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/UserServer.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/UserServer.dir/flags.make

CMakeFiles/UserServer.dir/epoll_handler.cpp.o: CMakeFiles/UserServer.dir/flags.make
CMakeFiles/UserServer.dir/epoll_handler.cpp.o: ../epoll_handler.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/Sitlos/UserServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/UserServer.dir/epoll_handler.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/UserServer.dir/epoll_handler.cpp.o -c /home/ubuntu/Sitlos/UserServer/epoll_handler.cpp

CMakeFiles/UserServer.dir/epoll_handler.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/UserServer.dir/epoll_handler.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/Sitlos/UserServer/epoll_handler.cpp > CMakeFiles/UserServer.dir/epoll_handler.cpp.i

CMakeFiles/UserServer.dir/epoll_handler.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/UserServer.dir/epoll_handler.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/Sitlos/UserServer/epoll_handler.cpp -o CMakeFiles/UserServer.dir/epoll_handler.cpp.s

CMakeFiles/UserServer.dir/messages.pb.cpp.o: CMakeFiles/UserServer.dir/flags.make
CMakeFiles/UserServer.dir/messages.pb.cpp.o: ../messages.pb.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/Sitlos/UserServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/UserServer.dir/messages.pb.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/UserServer.dir/messages.pb.cpp.o -c /home/ubuntu/Sitlos/UserServer/messages.pb.cpp

CMakeFiles/UserServer.dir/messages.pb.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/UserServer.dir/messages.pb.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/Sitlos/UserServer/messages.pb.cpp > CMakeFiles/UserServer.dir/messages.pb.cpp.i

CMakeFiles/UserServer.dir/messages.pb.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/UserServer.dir/messages.pb.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/Sitlos/UserServer/messages.pb.cpp -o CMakeFiles/UserServer.dir/messages.pb.cpp.s

CMakeFiles/UserServer.dir/redis_handler.cpp.o: CMakeFiles/UserServer.dir/flags.make
CMakeFiles/UserServer.dir/redis_handler.cpp.o: ../redis_handler.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/Sitlos/UserServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/UserServer.dir/redis_handler.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/UserServer.dir/redis_handler.cpp.o -c /home/ubuntu/Sitlos/UserServer/redis_handler.cpp

CMakeFiles/UserServer.dir/redis_handler.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/UserServer.dir/redis_handler.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/Sitlos/UserServer/redis_handler.cpp > CMakeFiles/UserServer.dir/redis_handler.cpp.i

CMakeFiles/UserServer.dir/redis_handler.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/UserServer.dir/redis_handler.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/Sitlos/UserServer/redis_handler.cpp -o CMakeFiles/UserServer.dir/redis_handler.cpp.s

CMakeFiles/UserServer.dir/server_method.cpp.o: CMakeFiles/UserServer.dir/flags.make
CMakeFiles/UserServer.dir/server_method.cpp.o: ../server_method.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/Sitlos/UserServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/UserServer.dir/server_method.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/UserServer.dir/server_method.cpp.o -c /home/ubuntu/Sitlos/UserServer/server_method.cpp

CMakeFiles/UserServer.dir/server_method.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/UserServer.dir/server_method.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/Sitlos/UserServer/server_method.cpp > CMakeFiles/UserServer.dir/server_method.cpp.i

CMakeFiles/UserServer.dir/server_method.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/UserServer.dir/server_method.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/Sitlos/UserServer/server_method.cpp -o CMakeFiles/UserServer.dir/server_method.cpp.s

CMakeFiles/UserServer.dir/thread_pool.cpp.o: CMakeFiles/UserServer.dir/flags.make
CMakeFiles/UserServer.dir/thread_pool.cpp.o: ../thread_pool.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/Sitlos/UserServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/UserServer.dir/thread_pool.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/UserServer.dir/thread_pool.cpp.o -c /home/ubuntu/Sitlos/UserServer/thread_pool.cpp

CMakeFiles/UserServer.dir/thread_pool.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/UserServer.dir/thread_pool.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/Sitlos/UserServer/thread_pool.cpp > CMakeFiles/UserServer.dir/thread_pool.cpp.i

CMakeFiles/UserServer.dir/thread_pool.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/UserServer.dir/thread_pool.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/Sitlos/UserServer/thread_pool.cpp -o CMakeFiles/UserServer.dir/thread_pool.cpp.s

CMakeFiles/UserServer.dir/util.cpp.o: CMakeFiles/UserServer.dir/flags.make
CMakeFiles/UserServer.dir/util.cpp.o: ../util.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/Sitlos/UserServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/UserServer.dir/util.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/UserServer.dir/util.cpp.o -c /home/ubuntu/Sitlos/UserServer/util.cpp

CMakeFiles/UserServer.dir/util.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/UserServer.dir/util.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/Sitlos/UserServer/util.cpp > CMakeFiles/UserServer.dir/util.cpp.i

CMakeFiles/UserServer.dir/util.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/UserServer.dir/util.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/Sitlos/UserServer/util.cpp -o CMakeFiles/UserServer.dir/util.cpp.s

# Object files for target UserServer
UserServer_OBJECTS = \
"CMakeFiles/UserServer.dir/epoll_handler.cpp.o" \
"CMakeFiles/UserServer.dir/messages.pb.cpp.o" \
"CMakeFiles/UserServer.dir/redis_handler.cpp.o" \
"CMakeFiles/UserServer.dir/server_method.cpp.o" \
"CMakeFiles/UserServer.dir/thread_pool.cpp.o" \
"CMakeFiles/UserServer.dir/util.cpp.o"

# External object files for target UserServer
UserServer_EXTERNAL_OBJECTS =

UserServer: CMakeFiles/UserServer.dir/epoll_handler.cpp.o
UserServer: CMakeFiles/UserServer.dir/messages.pb.cpp.o
UserServer: CMakeFiles/UserServer.dir/redis_handler.cpp.o
UserServer: CMakeFiles/UserServer.dir/server_method.cpp.o
UserServer: CMakeFiles/UserServer.dir/thread_pool.cpp.o
UserServer: CMakeFiles/UserServer.dir/util.cpp.o
UserServer: CMakeFiles/UserServer.dir/build.make
UserServer: CMakeFiles/UserServer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ubuntu/Sitlos/UserServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking CXX executable UserServer"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/UserServer.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/UserServer.dir/build: UserServer

.PHONY : CMakeFiles/UserServer.dir/build

CMakeFiles/UserServer.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/UserServer.dir/cmake_clean.cmake
.PHONY : CMakeFiles/UserServer.dir/clean

CMakeFiles/UserServer.dir/depend:
	cd /home/ubuntu/Sitlos/UserServer/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ubuntu/Sitlos/UserServer /home/ubuntu/Sitlos/UserServer /home/ubuntu/Sitlos/UserServer/build /home/ubuntu/Sitlos/UserServer/build /home/ubuntu/Sitlos/UserServer/build/CMakeFiles/UserServer.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/UserServer.dir/depend

