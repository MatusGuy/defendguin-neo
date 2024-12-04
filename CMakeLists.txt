cmake_minimum_required(VERSION 3.16)

project(defendguin2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

function(mklink link target)
	file(TO_NATIVE_PATH "${link}" nlink)
	file(TO_NATIVE_PATH "${target}" ntarget)
	if(WIN32)
		execute_process(COMMAND cmd /C "mklink /D /J ${nlink} ${ntarget}"
						WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
						ERROR_VARIABLE result)
		message(DEBUG "mklink result: ${result}")
	else()
		file(CREATE_LINK "${ntarget}" "${nlink}" SYMBOLIC)
	endif()
endfunction()

set(cog2d_DIR "" CACHE PATH "Path to the cog2d source code")
if(NOT cog2d_DIR)
	include(FetchContent)
	FetchContent_Declare(
		cog2d
		URL "https://codeberg.org/MatusGuy/cog2d/archive/master.tar.gz"
	)
	FetchContent_MakeAvailable(cog2d)
else()
	mklink("${PROJECT_BINARY_DIR}/cog2d" "${cog2d_DIR}")
	add_subdirectory("${PROJECT_BINARY_DIR}/cog2d")
endif()

add_executable(defendguin2 main.cpp
	player.hpp player.cpp
	constants.hpp
	bullet.hpp bullet.cpp)

target_link_libraries(defendguin2 PUBLIC cog2d)

include(GNUInstallDirs)
install(TARGETS defendguin2
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
	RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
