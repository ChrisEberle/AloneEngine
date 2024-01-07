#ifndef VBO_CLASS_H
#define VBO_CLASS_H


#include<glad/glad.h>
#include <vector>
#include "Vertex.h"

class VBO
{
public:
	// Reference ID of the Vertex Buffer Object
	GLuint ID;
	// Constructor that generates a Vertex Buffer Object and links it to vertices
	VBO(GLsizeiptr num_indices);

	VBO(const std::vector<Vertex>& vertices, GLsizeiptr num_indices);
	//dynamically updates the vbo in program loop
	void dynamic_update(const std::vector<Vertex>& data);
	// Binds the VBO
	void Bind();
	// Unbinds the VBO
	void Unbind();
	// Deletes the VBO
	void Delete();
};

#endif