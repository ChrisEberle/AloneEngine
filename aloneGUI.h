#pragma once


class guiMesh {
public:
	std::vector<PositionVertex> position_coordinates;
	std::vector<TextureVertex> texture_coordinates;
	std::vector<NormalVertex> normals;
	std::vector<GLuint> indices;

	glm::vec3 position;


	// Constructor for regular object
	guiMesh(glm::vec3 pos) : position(pos) {


	}

	// Mesh Types
	void createPanel() {
		GLfloat x = position.x;
		GLfloat y = position.y;
		GLfloat z = position.z;

		//             POSITION VECTOR
		position_coordinates.push_back({ -0.5f,    -0.5f,     0.0f});
		position_coordinates.push_back({ 0.5f,    -0.5f,     0.0f});
		position_coordinates.push_back({ -0.5f,     0.5f,     0.0f});
		position_coordinates.push_back({ 0.5f,     0.5f,     0.0f});

		//             TEXTURE COORDINATES
		texture_coordinates.push_back({ 0.0f, 0.0f });
		texture_coordinates.push_back({ 1.0f, 0.0f });
		texture_coordinates.push_back({ 0.0f, 1.0f });
		texture_coordinates.push_back({ 1.0f, 1.0f });

		//          INDICES
		indices = { 0, 1, 2, 1, 3, 2 };
	}

private:
};





class InstancedRenderer {
public:
	// SHADER PROGRAM
	Shader shaderProgram;
	// BUFFERS
	VAO vao;
	EBO ebo;
	VBO<PositionVertex> vbo_verts;
	VBO<TextureVertex> vbo_texCoords;
	// OBJECT DATA
	std::vector<PositionVertex> verts_pos;
	std::vector<TextureVertex> tex_coords;
	std::vector<GLuint> indices;

	GLuint max_indices;
	GLuint max_vertices;
	// OTHER
	Color color;

	GLuint texture;


	bool wire_state = false;

	// CONSTRUCTOR
	InstancedRenderer(Shader shaderProgram, guiMesh mesh, GLuint tex) : texture(tex), verts_pos(mesh.position_coordinates), tex_coords(mesh.texture_coordinates), shaderProgram(shaderProgram), vbo_verts(mesh.position_coordinates.size()), vbo_texCoords(mesh.texture_coordinates.size()), ebo(mesh.indices.size()) {
		max_vertices = static_cast<GLuint>(mesh.position_coordinates.size());
		max_indices = static_cast<GLuint>(mesh.indices.size());
		
		initializeMeshObject();
		update_all_buffers();
	}
	// DESTRUCTOR
	~InstancedRenderer() {
		vao.Delete();
		vbo_verts.Delete();
		vbo_texCoords.Delete();
		ebo.Delete();
	}



	void update_all_buffers() {
		vao.Bind();
		vbo_verts.dynamic_update(verts_pos);
		vbo_texCoords.dynamic_update(tex_coords);
		ebo.dynamic_update(indices);
		// Unbind all buffers
		vbo_verts.Unbind();
		vbo_texCoords.Unbind();
		ebo.Unbind();
		vao.Unbind();
	}

	void render(std::vector<glm::mat4>& modelMatrices) {
		// Activate current buffers
		vbo_verts.Bind();
		vao.Bind();
		ebo.Bind();

		// UI Rendering setup
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glDisable(GL_DEPTH_TEST);

		// Tell OpenGL which Shader Program we want to use
		shaderProgram.Activate();
		update_all_buffers();
		// Set the modelMatrices uniform array in the shader

		for (size_t i = 0; i < modelMatrices.size(); i++) {
			std::string prefix = "modelMatrices[" + std::to_string(i) + "].";
			// Set light properties
			shaderProgram.setMat4(prefix, modelMatrices[i]);
		}

		// Bind Texture
		glBindTexture(GL_TEXTURE_2D, texture);
		// Draw instances of the object
		glDrawElementsInstanced(GL_TRIANGLES, static_cast<GLsizei>(max_indices), GL_UNSIGNED_INT, 0, static_cast<GLsizei>(modelMatrices.size()));

		// Deactivate current buffers
		vbo_verts.Unbind();
		vbo_texCoords.Unbind();
		vao.Unbind();
		ebo.Unbind();
	}

	void initializeMeshObject() {
		// Generates Vertex Array Object and binds it
		vao.Bind();
		// Links VBO attributes such as coordinates and colors to VAO
		vao.LinkAttrib(vbo_verts, 0, 3, GL_FLOAT, sizeof(PositionVertex), (void*)offsetof(PositionVertex, position));
		vao.LinkAttrib(vbo_texCoords, 1, 2, GL_FLOAT, sizeof(TextureVertex), (void*)offsetof(TextureVertex, texCoord));
	}

private:

	GLuint getShaderUniform(std::string textureSampler) {
		return glGetUniformLocation(shaderProgram.ID, textureSampler.c_str());
	}
};