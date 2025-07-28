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

file(GLOB_RECURSE DGN_SOURCES CONFIGURE_DEPENDS src/*.cpp src/*.hpp)
add_executable(defendguin_neo ${DGN_SOURCES})

target_compile_features(defendguin_neo PUBLIC cxx_std_20)

target_link_libraries(defendguin_neo PUBLIC cog2d)

include(GNUInstallDirs)
install(TARGETS defendguin_neo
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
	RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
