#include"VBO.h"


// Constructor that generates a empty Vertex Buffer Object
VBO::VBO(GLsizeiptr size)
{
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glBufferData(GL_ARRAY_BUFFER,size, nullptr, GL_DYNAMIC_DRAW);
}

// dynamiccaly fills the vbo
void VBO::dynamic_update(const std::vector<Vertex>& data) {
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glBufferSubData(GL_ARRAY_BUFFER, 0, data.size() * sizeof(Vertex), data.data());
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