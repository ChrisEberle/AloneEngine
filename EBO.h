#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include<glad/glad.h>
#include <iostream>
#include <vector>
#include "Vertex.h"

class EBO
{
public:
	// ID reference of Elements Buffer Object
	GLuint ID;
	// Constructor that generates a Elements Buffer Object and links it to indices
	EBO(GLsizeiptr num_indices);

	// Single rendering usage of the vbo
	EBO(const std::vector<Vertex>& vertices, GLsizeiptr num_vertices);

	// Binds the EBO
	void Bind();
	// Dynamically updates the EBO
	void dynamic_update(const std::vector<GLuint>& data);
	// Unbinds the EBO
	void Unbind();
	// Deletes the EBO
	void Delete();
};

#endif