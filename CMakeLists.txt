cmake_minimum_required(VERSION 3.16)

project(defendguin2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
	cog2d
	URL "https://codeberg.org/MatusGuy/cog2d/archive/master.tar.gz"
)

FetchContent_MakeAvailable(cog2d)

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
