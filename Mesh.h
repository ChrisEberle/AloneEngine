#pragma once

static void back_face_culling(bool back_cull) {
	if (back_cull) {
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
	}
}


class Mesh
{
public:
	std::vector <Vertex> vertices;
	std::vector <GLuint> indices;
	Material material;
	// Store VAO in public so it can be used in the Draw function
	VAO VAO;

	// Holds number of instances (if 1 the mesh will be rendered normally)
	unsigned int instancing;

	// Initializes the mesh
	Mesh
	(
		std::vector <Vertex>& vertices,
		std::vector <GLuint>& indices,
		Material& mat,
		unsigned int instancing = 1,
		std::vector <glm::mat4> instanceMatrix = {}
	);

	// Draws the mesh
	void Draw
	(
		Shader& shader,
		Camera& camera,
		glm::mat4 matrix = glm::mat4(1.0f),
		glm::vec3 translation = glm::vec3(0.0f, 0.0f, 0.0f),
		glm::quat rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f),
		glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f)
	);
};