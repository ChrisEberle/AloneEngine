#include"EBO.h"

// Constructor that generates a Elements Buffer Object and links it to indices
EBO::EBO(GLsizeiptr num_indices)
{
	glCreateBuffers(1, &ID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * num_indices, nullptr, GL_STATIC_DRAW);
}

// Binds the EBO
void EBO::Bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

// dynamiccaly fills the ebo
void EBO::dynamic_update(const std::vector<GLuint>& data) {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, data.size() * sizeof(GLuint), data.data());
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