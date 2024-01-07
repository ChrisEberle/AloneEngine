#include"VBO.h"


// Batch rendering usage of the vbo
VBO::VBO(GLsizeiptr num_vertices)
{
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * num_vertices, nullptr, GL_DYNAMIC_DRAW);
}

// dynamiccaly fills the vbo
void VBO::dynamic_update(const std::vector<Vertex>& data) {
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glBufferSubData(GL_ARRAY_BUFFER, 0, data.size() * sizeof(Vertex), data.data());
}


// Single rendering usage of the vbo
VBO::VBO(const std::vector<Vertex>& vertices, GLsizeiptr num_vertices)
{
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * num_vertices, vertices.data(), GL_DYNAMIC_DRAW);
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