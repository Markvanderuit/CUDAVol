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

  program.h

  OpenGL program object declaration.

  October 2019
*/

#pragma once

#include "GL/glew.h"
#include "shader.h"
#include <initializer_list>

namespace CUDAVol {
  class Program {
  private:
    GLuint object;

  public:
    Program(const std::string &vertexFilePath, const std::string &fragmentFilePath);
    Program(const std::initializer_list<Shader> &shaders);
    ~Program();

    void beginUse() const;
    void endUse() const;
    GLuint getObject() const;
  };
} // namespace CUDAVol