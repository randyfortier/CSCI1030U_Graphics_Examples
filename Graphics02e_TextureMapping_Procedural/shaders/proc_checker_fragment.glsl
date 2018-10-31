uniform vec3 u_LightPos;
uniform vec4 u_DiffuseColour;
uniform vec3 u_EyePosition;
uniform float u_Shininess;

varying vec3 v_Position;
varying vec3 v_Normal;
varying vec3 v_OriginalPosition;
varying vec2 v_texCoord;

void main() {
    // procedural checker texture
    int stride = 4;
    int size = 20;
    vec4 white = vec4(1.0, 1.0, 1.0, 1.0);
    vec4 gray = vec4(0.25, 0.25, 0.25, 1.0);

    vec4 baseColour;
    int row, col ;

    col = floor(v_texCoord.s * size);
    row = floor(v_texCoord.t * size);

    int sum = row/stride + col/stride;
    if (mod(sum,2) == 0) {
       baseColour = white;
    } else {
       baseColour = gray;
    }

    // lighting
    vec3 normal = normalize(v_Normal);

    vec4 ambientColour = vec4(0.1, 0.1, 0.1, 1.0);

    // Will be used for attenuation.
    float distance = length(u_LightPos - v_Position);

    // Get a lighting direction vector from the light to the vertex.
    vec3 lightVector = normalize(u_LightPos - v_Position);

    // Calculate the dot product of the light vector and vertex normal. If the normal and light vector are
    // pointing in the same direction then it will get max illumination.
    float diffuse = clamp(dot(normal, lightVector), 0, 1);

    // Add attenuation.
    diffuse = diffuse * (1.0 / (1.0 + (0.00025 * distance * distance)));

    vec3 incidenceVector = -lightVector;
    vec3 reflectionVector = reflect(incidenceVector, normal);
    vec3 eyeVector = normalize(u_EyePosition - v_Position);
    float cosAngle = max(0.0, dot(eyeVector, reflectionVector));
    float specularCoefficient = pow(cosAngle, u_Shininess);

    // should be (diffuse * specular) * attenuationFactor;

    // Multiply the color by the diffuse illumination level to get final output color.
    gl_FragColor = baseColour; //specularCoefficient * baseColour + baseColour * diffuse + ambientColour;
}
