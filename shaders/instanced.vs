#version 330 core

// Positions/Coordinates
layout (location = 0) in vec3 aPos;
// Texture Coordinates
layout (location = 1) in vec2 aTex;
// Normals (not necessarily normalized)
layout (location = 2) in vec3 aNormal;
// Instancing Transformations
layout (location = 3) in mat4 instanceMatrix;


// Outputs the current position for the Fragment Shader

// Outputs the normal for the Fragment Shader
out vec3 Normal;
// Outputs the color for the Fragment Shader
out vec3 color;
// Outputs the texture coordinates to the Fragment Shader
out vec2 texCoord;
// Exports the current position from the Vertex Shader
out vec3 crntPos;


// Imports the camera matrix
uniform mat4 camMatrix;


void main()
{
    // calculates current position
	crntPos = vec3(instanceMatrix * vec4(aPos, 1.0f));
	// Assigns the normal from the Vertex Data to "Normal"
	Normal = normalize(aNormal);
	// Assigns the colors from the Vertex Data to "color"
	color = vec3(1.0f,1.0f,1.0f);
	// Apply instance transformation (including scaling) to texture coordinates
	texCoord = mat2(0.0, -1.0, 1.0, 0.0) * aTex;
	// Outputs the positions/coordinates of all vertices
	gl_Position = camMatrix * vec4(crntPos, 1.0);
}