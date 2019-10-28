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

  renderer.h

  Main renderer component definition.

  October 2019
*/

#include "renderer.h"
#include <array>
#include <string>

const std::string shaderDirectory = std::string(DATA_DIR) + "/shaders/";

namespace CUDAVol {
  Renderer::Renderer()
    : colorCorrectionPrg(shaderDirectory + "quad_passthrough.vert",
                         shaderDirectory + "color_correction.frag"),
      windowDrawPrg(shaderDirectory + "quad_passthrough.vert",
                    shaderDirectory + "quad_passthrough.frag") {
    // Define screen filling quad vertices
    std::array<GLfloat, 8> quad = {-1.f, 1.f, -1.f, -1.f, 1.f, 1.f, 1.f, -1.f};

    // Define vertex array object (VAO) for screen quad, keep as handle
    glGenVertexArrays(1, &quadVAO);
    glBindVertexArray(quadVAO);

    // Define vertex buffer object (VB0) for screen quad
    GLuint quadVBO;
    glGenBuffers(1, &quadVBO);
    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);

    // Copy vertex data to buffer
    glBufferData(GL_ARRAY_BUFFER, quad.size(), quad.data(), GL_STATIC_DRAW);

    // Enable attribute index 0
    glEnableVertexAttribArray(0);

    // Quad has 2 floats per vertex, data at index 0
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

    // Clean up
    glBindVertexArray(0);
    glDeleteBuffers(1, &quadVBO);
  }

  Renderer::~Renderer() {
    glDeleteVertexArrays(1, &quadVAO);
  }

  void Renderer::update() {}
} // namespace CUDAVol