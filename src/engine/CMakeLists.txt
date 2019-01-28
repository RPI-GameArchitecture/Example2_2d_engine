cmake_minimum_required (VERSION 3.10)
project (gamearch)

# SDL: for windowing and input:
set(SDL_AUDIO_ENABLED_BY_DEFAULT OFF)
set(SDL_ATOMIC_ENABLED_BY_DEFAULT OFF)
set(SDL_DLOPEN_ENABLED_BY_DEFAULT OFF)
set(SDL_FILE_ENABLED_BY_DEFAULT OFF)
set(SDL_FILESYSTEM_ENABLED_BY_DEFAULT OFF)
set(SDL_RENDER_ENABLED_BY_DEFAULT OFF)
set(SDL_THREADS_ENABLED_BY_DEFAULT OFF)
set(SDL_TIMER_ENABLED_BY_DEFAULT OFF)
set(SDL_SHARED_ENABLED_BY_DEFAULT OFF)
set(SDL_STATIC_ENABLED_BY_DEFAULT OFF)

add_subdirectory (${CMAKE_CURRENT_SOURCE_DIR}/../3rdparty/SDL2-2.0.7 ${PROJECT_BINARY_DIR}/SDL2-2.0.7)
include_directories ("${PROJECT_BINARY_DIR}/SDL2-2.0.7/include")
include_directories ("${CMAKE_CURRENT_SOURCE_DIR}/../3rdparty/SDL2-2.0.7/include")

# GLEW: for OpenGL loading:
set(CMAKE_PREFIX_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../3rdparty/glew-2.1.0")
set(CMAKE_LIBRARY_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../3rdparty/glew-2.1.0/lib/Release/x64")
find_package(GLEW REQUIRED)
include_directories (${GLEW_INCLUDE_DIRS})
link_directories ("${CMAKE_CURRENT_SOURCE_DIR}/../3rdparty/glew-2.1.0/lib/Release/x64")

# GA engine:
include_directories ("${CMAKE_CURRENT_SOURCE_DIR}")
file(GLOB_RECURSE GA_SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
if (MSVC)
	set(CMAKE_CXX_FLAGS "$(CMAKE_CXX_FLAGS) /EHsc")
endif()
add_executable(ga ${GA_SOURCE_FILES})
target_link_libraries (ga SDL2-static glew32s opengl32)
if (MSVC)
	set_target_properties(ga PROPERTIES LINK_FLAGS "/ignore:4098 /ignore:4099")
endif()
