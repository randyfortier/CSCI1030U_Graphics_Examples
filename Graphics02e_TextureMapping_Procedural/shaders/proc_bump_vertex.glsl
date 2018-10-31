uniform mat4 u_MVPMatrix;
uniform mat4 u_MVMatrix;
uniform vec4 u_DiffuseColour;

attribute vec4 position;
attribute vec3 normal;

varying vec3 v_Position;
varying vec3 v_Normal;
varying vec3 v_OriginalPosition;

void main() {
    // interpolate the eye space position and normal
    v_Position = vec3(u_MVMatrix * position);
    v_Normal = vec3(u_MVMatrix * vec4(normal, 0.0));

    v_OriginalPosition = position;

    // perform the usual model-view-projection transformation for the vertex position
    gl_Position = u_MVPMatrix * position;
}
