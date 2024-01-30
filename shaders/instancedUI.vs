#version 330 core
layout (location = 0) in vec3 aPos;
// Instancing Transformations
layout (location = 1) in mat4 instanceMatrix;

out vec3 crntPos;


void main()
{
    crntPos = vec3(instanceMatrix * vec4(aPos, 1.0f));
    gl_Position = vec4(crntPos, 1.0);
}