cmake_minimum_required(VERSION 3.16)

project(DGN
		LANGUAGES CXX
		DESCRIPTION "Defendguin NEO: A horizontal shoot em' up game.")

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
set(COG2D_ASSET_PATH "${PROJECT_SOURCE_DIR}/assets" CACHE STRING "Where cog2d looks for assets.")

set(COG2D_DIR "" CACHE PATH "Path to the cog2d source code")
if(NOT COG2D_DIR)
	include(FetchContent)
	FetchContent_Declare(
		cog2d
		URL "https://github.com/MatusGuy/cog2d/archive/master.tar.gz"
	)
	FetchContent_MakeAvailable(cog2d)
else()
	mklink(${PROJECT_SOURCE_DIR}/external/cog2d "${COG2D_DIR}")
	add_subdirectory(external/cog2d)
endif()

cog2d_project_setup()
cog2d_add_game(defendguin_neo)
target_sources(defendguin_neo PRIVATE
	src/constants.hpp
	src/entity.hpp
	src/main.cpp
	src/player.cpp
	src/player.hpp
	src/game.hpp
	src/game.cpp
	src/enemy.hpp
	src/enemyegg.hpp
	src/enemyegg.cpp
	src/enemyfighter.hpp
	src/enemyfighter.cpp
	src/enemy.cpp
	src/bullet.hpp
	src/bulletblaster.hpp
	src/bulletblaster.cpp
	src/enemybullet.cpp
	src/enemybullet.hpp
)
cog2d_unity_group_sources(defendguin_neo)

target_compile_features(defendguin_neo PUBLIC cxx_std_20)

target_compile_definitions(defendguin_neo PUBLIC COG2D_NUM_COLGROUPS=4)
target_compile_definitions(defendguin_neo PUBLIC COG2D_NUM_ASSET_COLLECTIONS=1)

include(GNUInstallDirs)
install(TARGETS defendguin_neo
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
	RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
