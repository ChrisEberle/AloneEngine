#version 330 core
out vec4 FragColor;

uniform vec3 objectColor;

void main()
{
    FragColor = vec4(objectColor.x,objectColor.y,objectColor.z,1.0);
}