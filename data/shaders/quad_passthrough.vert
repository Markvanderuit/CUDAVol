#version 430 core

layout(location = 0) in vec4 vertex_position;

out vec2 texture_coordinates;

void main() {
	texture_coordinates = 0.5 + 0.5 * vertex_position.xy;
	gl_Position = vertex_position;
}