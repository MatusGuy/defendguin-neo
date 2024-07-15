cmake_minimum_required(VERSION 3.16)

project(defendguin2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(cog2d_DIR "" CACHE PATH "Path to the cog2d source code")
if(NOT cog2d_DIR)
	include(FetchContent)
	FetchContent_Declare(
		cog2d
		URL "https://codeberg.org/MatusGuy/cog2d/archive/master.tar.gz"
	)
	FetchContent_MakeAvailable(cog2d)
else()
	file(CREATE_LINK ${cog2d_DIR} ${PROJECT_BINARY_DIR}/cog2d SYMBOLIC)
	add_subdirectory(${PROJECT_BINARY_DIR}/cog2d)
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
