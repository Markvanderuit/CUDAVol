cmake_minimum_required(VERSION 3.11)

target_sources(
  CUDAVol PRIVATE
  src/main.cpp 
  src/shader.cpp 
  src/program.cpp 
  src/window.cpp
  src/renderer.cpp
)