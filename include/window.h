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

  OpenGL context and window declaration. Window is resizable etc.

  October 2019
*/

#pragma once

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "glm/vec2.hpp"
#include <string>

namespace CUDAVol {
  class Window {
  private:
    GLFWwindow *object;
    glm::ivec2 windowDims;
    glm::ivec2 framebufferDims;

  public:
    Window(glm::ivec2 windowDims, const std::string &windowTitle);
    ~Window();

    bool update();
    void close();

    GLFWwindow *getObject() const;
    glm::ivec2 getWindowDims() const;
    glm::ivec2 getFramebufferDims() const;
  };
} // namespace CUDAVol