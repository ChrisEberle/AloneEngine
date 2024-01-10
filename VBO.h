#ifndef VBO_CLASS_H
#define VBO_CLASS_H


#include<glad/glad.h>
#include <vector>
#include "Vertex.h"

template <typename DataType>
class VBO
{
public:
	// Reference ID of the Vertex Buffer Object
	GLuint ID;
	// Constructor that generates a Vertex Buffer Object and links it to vertices
	VBO(GLuint num_indices);

	VBO(const std::vector<DataType>& vertices, GLuint num_indices);

	//dynamically updates the vbo in program loop
	void dynamic_update(const std::vector<DataType>& data);
	void Bind();
	void Unbind();
	void Delete();
};

#endif