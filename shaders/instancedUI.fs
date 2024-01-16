#version 330 core

in vec2 texCoord;

out vec4 FragColor;

uniform sampler2D textureSampler;  // Assuming you're using a 2D texture

void main()
{
    // Fetch the color from the texture using the texture coordinates
    vec4 texColor = texture(textureSampler, texCoord);

   // Set the color to black
    FragColor = vec4(0.0, 0.0, 0.0, 1.0);
}