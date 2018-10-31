#version 330 core

in vec4 Position;
in vec3 Normal;
out vec3 vPosition;
out vec3 vNormal;

void main() {
    vPosition = Position.xyz;
    vNormal = Normal;
    gl_Position = Position;
}
