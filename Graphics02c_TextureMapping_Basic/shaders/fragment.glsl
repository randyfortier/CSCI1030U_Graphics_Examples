#version 130

uniform sampler2D textureSampler;

varying vec2 v_textureCoords;

void main() {
  gl_FragColor = vec4(texture(textureSampler, v_textureCoords).rgb, 1.0);

  //gl_FragColor.r = 1.0;
  //gl_FragColor.x = v_textureCoords.x;
  //gl_FragColor.y = v_textureCoords.y;
}
