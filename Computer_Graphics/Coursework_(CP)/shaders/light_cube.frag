#version 450 core

out vec4 FragColor;

uniform vec3 minorColor;

void main() {
    FragColor = vec4(minorColor, 1.0);
}