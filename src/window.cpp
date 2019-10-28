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

// Debug callback translation
// Src: https://learnopengl.com/In-Practice/Debugging
void APIENTRY glDebugOutput(GLenum source,
                            GLenum type,
                            GLuint id,
                            GLenum severity,
                            GLsizei length,
                            const GLchar *message,
                            const void *userParam) {
  // ignore non-significant error/warning codes
  if (id == 131169 || id == 131185 || id == 131218 || id == 131204)
    return;

  std::cout << "---------------" << std::endl;
  std::cout << "Debug message (" << id << "): " << message << std::endl;

  switch (source) {
  case GL_DEBUG_SOURCE_API:
    std::cout << "Source: API";
    break;
  case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
    std::cout << "Source: Window System";
    break;
  case GL_DEBUG_SOURCE_SHADER_COMPILER:
    std::cout << "Source: Shader Compiler";
    break;
  case GL_DEBUG_SOURCE_THIRD_PARTY:
    std::cout << "Source: Third Party";
    break;
  case GL_DEBUG_SOURCE_APPLICATION:
    std::cout << "Source: Application";
    break;
  case GL_DEBUG_SOURCE_OTHER:
    std::cout << "Source: Other";
    break;
  }
  std::cout << std::endl;

  switch (type) {
  case GL_DEBUG_TYPE_ERROR:
    std::cout << "Type: Error";
    break;
  case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
    std::cout << "Type: Deprecated Behaviour";
    break;
  case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
    std::cout << "Type: Undefined Behaviour";
    break;
  case GL_DEBUG_TYPE_PORTABILITY:
    std::cout << "Type: Portability";
    break;
  case GL_DEBUG_TYPE_PERFORMANCE:
    std::cout << "Type: Performance";
    break;
  case GL_DEBUG_TYPE_MARKER:
    std::cout << "Type: Marker";
    break;
  case GL_DEBUG_TYPE_PUSH_GROUP:
    std::cout << "Type: Push Group";
    break;
  case GL_DEBUG_TYPE_POP_GROUP:
    std::cout << "Type: Pop Group";
    break;
  case GL_DEBUG_TYPE_OTHER:
    std::cout << "Type: Other";
    break;
  }
  std::cout << std::endl;

  switch (severity) {
  case GL_DEBUG_SEVERITY_HIGH:
    std::cout << "Severity: high";
    break;
  case GL_DEBUG_SEVERITY_MEDIUM:
    std::cout << "Severity: medium";
    break;
  case GL_DEBUG_SEVERITY_LOW:
    std::cout << "Severity: low";
    break;
  case GL_DEBUG_SEVERITY_NOTIFICATION:
    std::cout << "Severity: notification";
    break;
  }
  std::cout << std::endl;
  std::cout << std::endl;
}

namespace CUDAVol {
  Window::Window(glm::ivec2 windowDims, const std::string &windowTitle)
    : windowDims(windowDims), framebufferDims(windowDims) {
    // Initialize GLFW
    if (auto c = glfwInit(); !c) {
      std::cerr << "GLFW initialization returned code " << c << std::endl;
      throw std::runtime_error(nullptr);
    }

    // Enable debug output for now
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

    // Create window, gives us context as well
    object = glfwCreateWindow(windowDims.x, windowDims.y, windowTitle.c_str(),
                              nullptr, nullptr);
    if (!object) {
      std::cerr << "Window initialization failed" << std::endl;
      throw std::runtime_error(nullptr);
    }

    // Configure window
    glfwSwapInterval(1);
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

    // Enable debug output
    GLint flags;
    if (glGetIntegerv(GL_CONTEXT_FLAGS, &flags); flags & GL_CONTEXT_FLAG_DEBUG_BIT) {
      glEnable(GL_DEBUG_OUTPUT);
      glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
      glDebugMessageCallback(glDebugOutput, nullptr);
      glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
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

  glm::ivec2 Window::getWindowDims() const {
    return windowDims;
  }
  glm::ivec2 Window::getFramebufferDims() const {
    return framebufferDims;
  }
} // namespace CUDAVol