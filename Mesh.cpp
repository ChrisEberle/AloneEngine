#include "engine.h"

Mesh::Mesh
(
	std::vector <Vertex>& vertices,
	std::vector <GLuint>& indices,
	Material& mat,
	unsigned int instancing,
	std::vector <glm::mat4> instanceMatrix
)
{
	Mesh::vertices = vertices;
	Mesh::indices = indices;
	Mesh::material = mat;
	Mesh::instancing = instancing;

	VAO.Bind();
	// Generates Vertex Buffer Object and links it to vertices
	VBO instanceVBO(instanceMatrix);
	VBO VBO(vertices);
	// Generates Element Buffer Object and links it to indices
	EBO EBO(indices);
	// Links VBO attributes such as coordinates and normals to VAO
	VAO.LinkAttrib(VBO, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex ,position));
	VAO.LinkAttrib(VBO, 1, 2, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));
	VAO.LinkAttrib(VBO, 2, 3, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, normals));
	if (instancing != 1)
	{
		instanceVBO.Bind();
		// Can't link to a mat4 so you need to link four vec4s
		VAO.LinkAttrib(instanceVBO, 3, 4, GL_FLOAT, sizeof(glm::mat4), (void*)0);
		VAO.LinkAttrib(instanceVBO, 4, 4, GL_FLOAT, sizeof(glm::mat4), (void*)(1 * sizeof(glm::vec4)));
		VAO.LinkAttrib(instanceVBO, 5, 4, GL_FLOAT, sizeof(glm::mat4), (void*)(2 * sizeof(glm::vec4)));
		VAO.LinkAttrib(instanceVBO, 6, 4, GL_FLOAT, sizeof(glm::mat4), (void*)(3 * sizeof(glm::vec4)));
		// Makes it so the transform is only switched when drawing the next instance
		glVertexAttribDivisor(3, 1);
		glVertexAttribDivisor(4, 1);
		glVertexAttribDivisor(5, 1);
		glVertexAttribDivisor(6, 1);
	}
	// Unbind all to prevent accidentally modifying them
	VAO.Unbind();
	VBO.Unbind();
	instanceVBO.Unbind();
	EBO.Unbind();
}


void Mesh::Draw
(
	Shader& shader,
	Camera& camera,
	glm::mat4 matrix,
	glm::vec3 translation,
	glm::quat rotation,
	glm::vec3 scale
)
{
	// Bind shader to be able to access uniforms
	shader.Activate();
	VAO.Bind();
	//std::cout << "hit" << std::endl;
	// Keep track of how many of each type of textures we have
	unsigned int numDiffuse = 0;
	unsigned int numSpecular = 0;

	for (unsigned int i = 0; i < material.textures.size(); i++)
	{
		std::string num;
		std::string type = material.textures[i].type;
		if (type == "diffuse")
		{
			num = std::to_string(numDiffuse++);
		}
		else if (type == "specular")
		{
			num = std::to_string(numSpecular++);
		}

		material.textures[i].texUnit(shader, (type + num).c_str(), i);
		material.textures[i].Bind();
	}
	// Take care of the camera Matrix
	glUniform3f(glGetUniformLocation(shader.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
	camera.Matrix(45.0f, 0.001f, 10000.0f, shader, "camMatrix");

	// Check if instance drawing should be performed
	if (instancing == 1)
	{
		// Initialize matrices
		glm::mat4 trans = glm::mat4(1.0f);
		glm::mat4 rot = glm::mat4(1.0f);
		glm::mat4 sca = glm::mat4(1.0f);

		// Transform the matrices to their correct form
		trans = glm::translate(trans, translation);
		rot = glm::mat4_cast(rotation);
		sca = glm::scale(sca, scale);

		// Push the matrices to the vertex shader
		glUniformMatrix4fv(glGetUniformLocation(shader.ID, "translation"), 1, GL_FALSE, glm::value_ptr(trans));
		glUniformMatrix4fv(glGetUniformLocation(shader.ID, "rotation"), 1, GL_FALSE, glm::value_ptr(rot));
		glUniformMatrix4fv(glGetUniformLocation(shader.ID, "scale"), 1, GL_FALSE, glm::value_ptr(sca));
		glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(matrix));

		// Draw the actual mesh
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	}
	else
	{
		glDrawElementsInstanced(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0, instancing);
	}

	for (unsigned int i = 0; i < material.textures.size(); i++)
	{
		material.textures[i].Unbind();
	}
}