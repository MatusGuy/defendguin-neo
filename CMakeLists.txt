cmake_minimum_required(VERSION 3.16)

project(defendguin2 LANGUAGES CXX)

function(mklink link target)
	file(TO_NATIVE_PATH "${link}" nlink)
	file(TO_NATIVE_PATH "${target}" ntarget)
	if(CMAKE_HOST_WIN32)
		execute_process(COMMAND cmd /C "del /AS ${nlink} & mklink /D /J ${nlink} ${ntarget}"
						WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
						ERROR_VARIABLE result)
		message(DEBUG "mklink result: ${result}")
	else()
		file(CREATE_LINK "${ntarget}" "${nlink}" SYMBOLIC)
	endif()
endfunction()

set(COG2D_GRAPHICS_USE_INT YES)
set(COG2D_BUILD_TESTS OFF)

set(COG2D_DIR "" CACHE PATH "Path to the cog2d source code")
if(NOT COG2D_DIR)
	include(FetchContent)
	FetchContent_Declare(
		cog2d
		URL "https://github.com/MatusGuy/cog2d/archive/master.tar.gz"
	)
	FetchContent_MakeAvailable(cog2d)
else()
	mklink(${PROJECT_SOURCE_DIR}/cog2d "${COG2D_DIR}")
	add_subdirectory(cog2d)
	if(PROJECT_IS_TOP_LEVEL AND NOT EXISTS ${COG2D_SOURCE_DIR}/.clang-format)
		file(COPY ${COG2D_SOURCE_DIR}/.clang-format DESTINATION ${PROJECT_SOURCE_DIR})
	endif()
endif()

add_executable(defendguin2 main.cpp
	player.hpp player.cpp
	constants.hpp
	bullet.hpp bullet.cpp
	enemy.hpp enemy.cpp
	gamescene.hpp gamescene.cpp
	cog2dintro.hpp cog2dintro.cpp
	camera.hpp camera.cpp)

target_compile_features(defendguin2 PUBLIC cxx_std_20)

target_link_libraries(defendguin2 PUBLIC cog2d)

include(GNUInstallDirs)
install(TARGETS defendguin2
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
	RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
