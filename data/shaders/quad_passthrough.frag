#version 430 core

// uniform sampler2D source_texture_in;

in vec2 texture_coordinates;
out vec4 fragment_color;

void main() {
	fragment_color = vec4(1, 1, 0, 1);
  // texture(source_texture_in, texture_coordinates);
}
