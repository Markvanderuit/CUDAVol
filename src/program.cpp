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

  OpenGL program object definition.

  October 2019
*/

#include "program.h"
#include <iostream>
#include <string>

namespace CUDAVol {
  Program::Program(const std::string &vertexFilePath, const std::string &fragmentFilePath)
    : Program({Shader(vertexFilePath, GL_VERTEX_SHADER),
               Shader(fragmentFilePath, GL_FRAGMENT_SHADER)}) {}

  Program::Program(const std::initializer_list<Shader> &shaders) {
    // Create program object
    object = glCreateProgram();
    for (const auto &shader : shaders) {
      glAttachShader(object, shader.getObject());
    }
    glLinkProgram(object);
    for (const auto &shader : shaders) {
      glDetachShader(object, shader.getObject());
    }

    // Check linking
    GLint success = 0;
    glGetProgramiv(object, GL_LINK_STATUS, &success);
    if (success == GL_FALSE) {
      GLint logLength = 0;
      glGetProgramiv(object, GL_INFO_LOG_LENGTH, &logLength);
      std::string err(logLength, ' ');
      glGetProgramInfoLog(object, logLength, &logLength, &err[0]);

      // TODO: Log and exit
      std::cerr << "Error loading program, linking error: " << err << std::endl;
      throw std::runtime_error(nullptr);
    }
  }

  Program::~Program() {
    glDeleteProgram(object);
  }

  void Program::beginUse() const {
    glUseProgram(object);
  }

  void Program::endUse() const {
    glUseProgram(0);
  }

  GLuint Program::getObject() const {
    return object;
  }
} // namespace CUDAVol