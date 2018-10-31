uniform mat4 u_MVPMatrix;
uniform mat4 u_MVMatrix;
uniform vec4 u_DiffuseColour;

attribute vec4 position;
attribute vec3 normal;
attribute vec2 textureCoords;

varying vec3 v_Position;
varying vec3 v_Normal;
varying vec3 v_OriginalPosition;
varying vec2 v_TexCoord2D;
varying vec4 v_TexCoord3D;

void main() {
    // interpolate the eye space position and normal
    v_Position = vec3(u_MVMatrix * position);
    v_Normal = vec3(u_MVMatrix * vec4(normal, 0.0));

    v_OriginalPosition = position;
    v_TexCoord2D = textureCoords;
    v_TexCoord3D = position;

    // perform the usual model-view-projection transformation for the vertex position
    gl_Position = u_MVPMatrix * position;
}
