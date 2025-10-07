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
	mklink(${PROJECT_SOURCE_DIR}/cog2d "${COG2D_DIR}")
	add_subdirectory(cog2d)
	if(PROJECT_IS_TOP_LEVEL AND NOT EXISTS ${COG2D_SOURCE_DIR}/.clang-format)
		file(COPY ${COG2D_SOURCE_DIR}/.clang-format DESTINATION ${PROJECT_SOURCE_DIR})
	endif()
endif()

list(APPEND CMAKE_MODULE_PATH "${COG2D_SOURCE_DIR}/cmake")
include(Cog2dGame)

cog2d_add_game(defendguin_neo)
target_sources(defendguin_neo PRIVATE
	src/constants.hpp
	src/gameactorfactory.hpp
	src/bullet.cpp
	src/bullet.hpp
	src/bulletrocket.cpp
	src/bulletrocket.hpp
	src/bulletrocket2.cpp
	src/bulletrocket2.hpp
	src/camera.cpp
	src/camera.hpp
	src/cog2dintro.cpp
	src/cog2dintro.hpp
	src/gamescene.cpp
	src/gamescene.hpp
	src/main.cpp
	src/player.cpp
	src/player.hpp
	src/weapon.cpp
	src/weapon.hpp
	src/weaponbullet.cpp
	src/weaponbullet.hpp
	src/weaponpeashooter.cpp
	src/weaponpeashooter.hpp
	src/weaponrocket.cpp
	src/weaponrocket.hpp
	src/enemy.cpp
	src/enemy.hpp
	src/enemybullet.cpp
	src/enemybullet.hpp
	src/enemyfighter.cpp
	src/enemyfighter.hpp
	src/gameactorfactory.cpp
)
cog2d_unity_group_sources(defendguin_neo)

target_compile_features(defendguin_neo PUBLIC cxx_std_20)

include(GNUInstallDirs)
install(TARGETS defendguin_neo
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
	RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
