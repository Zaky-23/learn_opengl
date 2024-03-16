#version 460 core

in vec3 color;

layout (location = 0) out vec4 fragcolor;

void main() {
	fragcolor = vec4(color.x, color.y, color.z, 1.0);
}