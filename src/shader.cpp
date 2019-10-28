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

  shader.cpp

  OpenGL shader object definition.

  October 2019
*/

#include "shader.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <vector>

namespace CUDAVol {
  Shader::Shader(const std::string &filePath, GLenum shaderType) {
    // Attempt to read shader file
    std::ifstream ifs(filePath, std::ios::in | std::ios::binary);
    if (!ifs.is_open()) {
      // TODO: Log and exit
      std::cerr << "Error opening shader " << filePath << std::endl;
      throw std::runtime_error(nullptr);
    }

    // Buffer entire file into a string, no need for line access
    std::stringstream buffer;
    buffer << ifs.rdbuf();
    const std::string str = buffer.str();
    const GLchar *src = str.c_str();

    // Create shader object
    object = glCreateShader(shaderType);
    glShaderSource(object, 1, &src, nullptr);
    glCompileShader(object);

    // Check compilation
    GLint success = 0;
    glGetShaderiv(object, GL_COMPILE_STATUS, &success);
    if (success == GL_FALSE) {
      GLint logLength = 0;
      glGetShaderiv(object, GL_INFO_LOG_LENGTH, &logLength);
      std::string err(logLength, ' ');
      glGetShaderInfoLog(object, logLength, nullptr, &err[0]);

      // TODO: Log and exit
      std::cerr << "Error loading shader " << filePath
                << ", compilation error: " << err << std::endl;
      throw std::runtime_error(nullptr);
    }
  }

  Shader::~Shader() {
    glDeleteShader(object);
  }

  GLuint Shader::getObject() const {
    return object;
  }
} // namespace CUDAVol