#version 330 core

out vec4 FragColor;

in vec3 color;
in vec2 texCoords;

uniform sampler2D tex0;

void main() {
    // Gets the color from tex0 at coords texCoords;
    FragColor = texture(tex0, texCoords);
}