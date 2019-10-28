/*
  Copyright (c) 2019 Mark van de Ruit

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.

  #############################################################################

  window.h

  OpenGL context and window definition. Window is resizable etc.

  October 2019
*/

#include "window.h"
#include <iostream>
#include <stdexcept>

namespace CUDAVol {
  Window::Window(glm::ivec2 windowDims, const std::string &windowTitle)
    : windowDims(windowDims), framebufferDims(windowDims) {
    // Initialize GLFW
    if (auto c = glfwInit(); !c) {
      std::cerr << "GLFW initialization returned code " << c << std::endl;
      throw std::runtime_error(nullptr);
    }

    // Create window, gives us context as well
    object = glfwCreateWindow(windowDims.x, windowDims.y, windowTitle.c_str(),
                              nullptr, nullptr);
    if (!object) {
      std::cerr << "Window initialization failed" << std::endl;
      throw std::runtime_error(nullptr);
    }
    glfwSwapInterval(1); // This should enable vsync
    glfwGetFramebufferSize(object, &framebufferDims.x, &framebufferDims.y);
    glfwMakeContextCurrent(object);

    // Check GL ERR
    if (auto c = glGetError(); c != GL_NO_ERROR) {
      std::cerr << "glGetError() returned code " << c << std::endl;
      throw std::runtime_error(nullptr);
    }

    // Initialize GLEW
    if (auto c = glewInit(); c != GLEW_OK) {
      std::cerr << "GLEW initialization returned code " << c << std::endl;
      throw std::runtime_error(nullptr);
    }
  }

  Window::~Window() {
    glfwDestroyWindow(object);
  }

  bool Window::update() {
    glfwPollEvents();
    glfwGetFramebufferSize(object, &framebufferDims.x, &framebufferDims.y);
    glfwGetWindowSize(object, &windowDims.x, &windowDims.y);
    glfwSwapBuffers(object);
    return !glfwWindowShouldClose(object);
  }

  void Window::close() {
    glfwSetWindowShouldClose(object, GLFW_TRUE);
  }

  GLFWwindow *Window::getObject() const {
    return object;
  }
} // namespace CUDAVol