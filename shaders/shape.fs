#version 330 core

// Outputs colors in RGBA
out vec4 FragColor;

// Inputs the texture coordinates from the Vertex Shader
in vec2 texCoord;

in float texIndex;

// Gets the Texture Unit from the main function
uniform sampler2D textures[2];


void main()
{
    int index = int(texIndex);
    FragColor = texture(textures[index], texCoord);
}