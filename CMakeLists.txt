cmake_minimum_required(VERSION 3.11)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(CUDAVol LANGUAGES CXX CUDA)

# Add executable with source files in /src
add_executable(CUDAVol)
add_subdirectory(src)

# Set absolute data directory for shaders and volume files
add_definitions(-DDATA_DIR="${CMAKE_CURRENT_SOURCE_DIR}/data")

# Set CUDA flags
set_target_properties(CUDAVol PROPERTIES CUDA_SEPARABLE_COMPILATION ON)
set_target_properties(CUDAVol PROPERTIES POSITION_INDEPENDENT_CODE ON)

# Add GLEW library from source
set(BUILD_UTILS OFF CACHE BOOL "" FORCE)
add_subdirectory(thirdparty/glew/build/cmake)

# Add GLFW library from source
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(thirdparty/glfw)

# Add libs to project
target_link_libraries(CUDAVol glew_s glfw)

# Add include directories for libs to project
target_include_directories(
  CUDAVol PUBLIC
  thirdparty/glew/include
  thirdparty/glfw/include
  thirdparty/glm
  include
)