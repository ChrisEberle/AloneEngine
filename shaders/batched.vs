#version 330 core

// Positions/Coordinates
layout(location = 0) in vec3 aPos;
// Texture Coordinates
layout(location = 1) in vec2 aTex;
// Outputs the texture coordinates to the fragment shader
out vec2 texCoord;

flat out int objIndex;

uniform mat4 camMatrix;


void main()
{
    // Outputs the positions/coordinates of all vertices
    gl_Position = camMatrix * (vec4(aPos, 1.0));

    // Assigns the texture coordinates from the Vertex Data to "texCoord"
    texCoord = aTex;
}