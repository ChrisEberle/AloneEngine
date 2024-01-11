#include"VBO.h"

// Explicit instantiation for the required data type(s)
template class VBO<Vertex>;
template class VBO<PositionVertex>;
template class VBO<TextureVertex>;
template class VBO<NormalVertex>;

template <typename DataType>
// Batch rendering usage of the vbo
VBO<DataType>::VBO(GLuint num_vertices)
{
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(DataType) * num_vertices, nullptr, GL_DYNAMIC_DRAW);
}
template <typename DataType>

// dynamiccaly fills the vbo
void VBO<DataType>::dynamic_update(const std::vector<DataType>& data) {
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glBufferSubData(GL_ARRAY_BUFFER, 0, data.size() * sizeof(DataType), data.data());
}

template <typename DataType>

// Single rendering usage of the vbo
VBO<DataType>::VBO(const std::vector<DataType>& vertices, GLuint num_vertices)
{
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(DataType) * num_vertices, vertices.data(), GL_DYNAMIC_DRAW);
}

template <typename DataType>
void VBO<DataType>::Bind() {
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

template <typename DataType>
void VBO<DataType>::Unbind() {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
template <typename DataType>
void VBO<DataType>::Delete() {
	glDeleteBuffers(1, &ID);
}