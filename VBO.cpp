#include"VBO.h"
#include "Vertex.h"
// Constructor that generates a Vertex Buffer Object and links it to vertices
VBO::VBO(GLsizeiptr size)
{
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
}

void VBO::dynamic_update(GLfloat* vertices)
{
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vertex)*1000, vertices);
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