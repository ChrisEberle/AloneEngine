#include"VBO.h"
#include "Vertex.h"

// Constructor that generates a empty Vertex Buffer Object
VBO::VBO(GLsizeiptr size)
{
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glBufferData(GL_ARRAY_BUFFER,size, nullptr, GL_DYNAMIC_DRAW);
}

// dynamiccaly fills the vbo
void VBO::dynamic_update(const void* data, GLsizei size)
{
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
}

// Binds the VBO
void VBO::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

// Unbinds the VBO
void VBO::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

// Deletes the VBO
void VBO::Delete()
{
	glDeleteBuffers(1, &ID);
}