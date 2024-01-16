#version 330 core

// Positions/Coordinates
layout(location = 0) in vec3 aPos;
// Texture Coordinates
layout(location = 1) in vec2 aTex;

out vec2 texCoord;

uniform mat4 modelMatrices[100];  // Assuming you have a maximum of 100 instances

void main()
{
    // Retrieve the model matrix for the current instance
    mat4 model = modelMatrices[gl_InstanceID];

    // Calculate the final position in camera space
    gl_Position = model * vec4(aPos.xy, 0.0f, 1.0);

    // Pass the texture coordinate to the fragment shader
    texCoord = aTex;
}