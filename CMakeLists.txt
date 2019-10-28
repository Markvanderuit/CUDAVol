cmake_minimum_required(VERSION 3.11)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(CUDAVol LANGUAGES CXX CUDA)

add_executable(CUDAVol src/main.cpp src/shader.cpp src/program.cpp src/window.cpp)

add_definitions(-DDATA_DIR="${CMAKE_CURRENT_SOURCE_DIR}/data")

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
  CUDAVol PRIVATE
  thirdparty/glew/include
  thirdparty/glfw/include
  thirdparty/glm
  include
)