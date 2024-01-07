#include"EBO.h"

// Batch rendering usage
EBO::EBO(GLsizeiptr num_indices)
{
	glCreateBuffers(1, &ID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * num_indices, nullptr, GL_STATIC_DRAW);
}

// dynamiccaly fills the ebo
void EBO::dynamic_update(const std::vector<GLuint>& data) {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, data.size() * sizeof(GLuint), data.data());
}


// Single rendering usage
EBO::EBO(const std::vector<Vertex>& vertices, GLsizeiptr num_vertices)
{
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * num_vertices, vertices.data(), GL_STATIC_DRAW);
}



// Binds the EBO
void EBO::Bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

// Unbinds the EBO
void EBO::Unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

// Deletes the EBO
void EBO::Delete()
{
	glDeleteBuffers(1, &ID);
}