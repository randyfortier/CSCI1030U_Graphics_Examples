#version 110

attribute vec3 position;
//attribute vec3 colour;
attribute vec2 textureCoords;
attribute vec3 normal;

//varying vec3 v_colour;
varying vec2 v_textureCoords;

uniform mat4 MVP;

void main() {
    gl_Position =  MVP * vec4(position, 1.0);
    //v_colour = colour;
    v_textureCoords = textureCoords;
}
