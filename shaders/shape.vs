#version 330 core

// Positions/Coordinates
layout (location = 0) in vec3 aPos;
// Texture Coordinates
layout (location = 1) in vec2 aTex;
// Texture ID
layout (location = 2) in float aTexIndex;

// Outputs the texture coordinates to the fragment shader
out vec2 texCoord;

flat out float texIndex;

uniform mat4 camMatrix;


uniform mat4 modelMatrix;


void main()
{
	// Outputs the positions/coordinates of all vertices
	gl_Position = camMatrix * (modelMatrix * vec4(aPos, 1.0));

	// Assigns the texture coordinates from the Vertex Data to "texCoord"
	texCoord = aTex;

	texIndex = aTexIndex;
}