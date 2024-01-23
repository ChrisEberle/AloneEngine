#pragma once

class Model {
public:
	Material material;
	std::vector<GLuint> indices;
	std::vector<Vertex> vertices;
	// CONSTRUCTOR
	Model(std::string path, unsigned int instancing = 1, std::vector<glm::mat4> instanceMatrix = {});

	void Draw
	(
		Shader& shader,
		Camera& camera,
		glm::vec3 translation = glm::vec3(0.0f, 0.0f, 0.0f),
		glm::quat rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f),
		glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f)
	);

	// Loads a single mesh by its index
	void loadMesh();
	void loadCube();
	void loadPlane(GLuint rows, GLuint cols, GLfloat numOctaves, GLfloat persistence, GLfloat textureScaleX, GLfloat textureScaleY);

private:
	// Holds number of instances (if 1 the mesh will be rendered normally)
	unsigned int instancing;
	// public variables
	std::string path;
	// All the meshes and transformations
	std::vector<Mesh> meshes;
	std::vector<glm::vec3> translationsMeshes;
	std::vector<glm::quat> rotationsMeshes;
	std::vector<glm::vec3> scalesMeshes;
	std::vector<glm::mat4> matricesMeshes;
	std::vector<glm::mat4> instanceMatrix;

	void addVertexData(int vIdx, int nIdx, int vtIdx, std::vector<PositionVertex>& pos, std::vector<TextureVertex>& tex, std::vector<NormalVertex>& norm);
	bool startWith(std::string& line, const char* text);
};