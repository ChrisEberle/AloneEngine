#version 330 core
out vec4 color;

uniform vec3 color;
uniform float transparency;

void main()
{    
    color = vec4(color,transparency);
}