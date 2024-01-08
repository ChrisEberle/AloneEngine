#pragma once

static std::vector<Vertex> createQuad(GLfloat x, GLfloat y, GLfloat z) {
	std::vector<Vertex> vertices;

	//Quad
	vertices.push_back({ -0.5f + x,    -0.5f + y,     0.5f + z,      0.0f, 0.0f});
	vertices.push_back({ 0.5f + x,    -0.5f + y,     0.5f + z,      1.0f, 0.0f});
	vertices.push_back({ -0.5f + x,    -0.5f + y,     -0.5f + z,      0.0f, 1.0f});
	vertices.push_back({ 0.5f + x,    -0.5f + y,     -0.5f + z,      1.0f, 1.0f});

	return vertices;
}
static std::vector<Vertex> createVertice(GLfloat x, GLfloat y, GLfloat z, GLfloat texCoord0, GLfloat texCoord1) {
	std::vector<Vertex> vertices;
	vertices.push_back({ x,y,z,texCoord0, texCoord1});
	return vertices;
}
static std::unique_ptr<GLuint[]> generateCubeChunkIndices(size_t max_index_count, size_t spacing_offset) {
	std::unique_ptr<GLuint[]> indices(new GLuint[max_index_count]);
	size_t offset = 0;

	for (size_t i = 0; i < max_index_count; i += 36) {
		GLuint base = offset * 24;  // Calculate the base index for each cube
		GLuint indicesTemplate[36] = {
			0, 1, 2, 1, 2, 3, 4, 5, 6, 5, 6, 7, 8, 9, 10, 9, 10, 11, 12, 13, 14, 13, 14, 15,
			16, 17, 18, 17, 18, 19, 20, 21, 22, 21, 22, 23
		};

		// Offset the template by the base index for the current cube
		for (size_t j = 0; j < 36; ++j) {
			indices[i + j] = base + indicesTemplate[j];
		}

		offset += spacing_offset;  // Move to the next cube
	}

	return indices;
}
static void move_cube(GLFWwindow* window, std::vector<Vertex>& verts, int numVertices, GLfloat control_variable) {


	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) {
		// Modify the values in the verts vector
		for (int i = 0; i < numVertices; ++i) {
			// Access and modify the values of the vertices in the verts vector
			verts[i].position[2] = verts[i].position[2] + control_variable;  // Modify X-coordinate
			// Modify other attributes if needed...
		}
	}
	if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS) {
		// Modify the values in the verts vector
		for (int i = 0; i < numVertices; ++i) {
			// Access and modify the values of the vertices in the verts vector
			verts[i].position[2] = verts[i].position[2] - control_variable;  // Modify X-coordinate
			// Modify other attributes if needed...
		}
	}
}
static void back_face_culling(bool back_cull, bool select_side) {
	if (back_cull) {
		glEnable(GL_CULL_FACE);
		if (select_side) {
			glCullFace(GL_BACK);
		}
		else {
			glCullFace(GL_FRONT);
		}
	}
}


class PlaneMesh {
public:

	//constructor
	PlaneMesh(GLfloat originX, GLfloat originY, GLfloat originZ,
		GLfloat sizeX, GLfloat sizeZ, GLuint rows, GLuint cols,
		GLfloat numOctaves, GLfloat persistence,
		GLfloat textureScaleX, GLfloat textureScaleY)
	{
		// create the vertices for the plane
		std::vector<Vertex> planeVertices;
		for (GLuint i = 0; i < rows; ++i) {
			for (GLuint j = 0; j < cols; ++j) {
				GLfloat x = originX + j * (sizeX / (cols - 1));
				GLfloat z = originZ - i * (sizeZ / (rows - 1));

				// Use multiple octaves of Perlin noise
				GLfloat y = originY;
				GLfloat frequency = 0.1f; // Initial frequency
				GLfloat amplitude = 1.0f; // Initial amplitude

				for (int k = 0; k < numOctaves; ++k) {
					y += glm::perlin(glm::vec2(x * frequency, z * frequency)) * amplitude;
					frequency *= 2.0f; // Increase frequency with each octave
					amplitude *= persistence; // Decrease amplitude with each octave
				}

				if (y < -0.5f) {
					y = -0.5f;
				}
				// Calculate texCoordX to repeat within each column
				GLfloat texCoordX = static_cast<GLfloat>(j % cols) / (cols - 1) * textureScaleX;

				GLfloat texCoordY = static_cast<GLfloat>(i) / (rows - 1) * textureScaleY;

				planeVertices.push_back({ x, y, z, texCoordX, texCoordY });
			}
		}

		// create the indices for the plane
		GLuint num_indices = (rows - 1) * (cols - 1) * 6;
		std::vector<GLuint> planeIndices(num_indices);
		GLuint offset = 6;
		for (GLuint i = 0; i < rows - 1; ++i) {
			for (GLuint j = 0; j < cols - 1; ++j) {
				GLuint currentVertex = i * cols + j;

				planeIndices[offset * (i * (cols - 1) + j)] = currentVertex;
				planeIndices[offset * (i * (cols - 1) + j) + 1] = currentVertex + 1;
				planeIndices[offset * (i * (cols - 1) + j) + 2] = currentVertex + cols;

				planeIndices[offset * (i * (cols - 1) + j) + 3] = currentVertex + 1;
				planeIndices[offset * (i * (cols - 1) + j) + 4] = currentVertex + cols + 1;
				planeIndices[offset * (i * (cols - 1) + j) + 5] = currentVertex + cols;
			}
		}

		// adds vertices of new object to parent vertex vector
		vertices.insert(vertices.end(), planeVertices.begin(), planeVertices.end());
		// add the object's indices to the parent indice vector
		indices.insert(indices.end(), planeIndices.begin(), planeIndices.end());
	}




	// Getter Functions
	const std::vector<Vertex>& getVertices() const {
		return vertices;
	}

	const std::vector<GLuint>& getIndices() const {
		return indices;
	}

	size_t getNumVertices() const {
		return vertices.size();
	}

	size_t getNumIndices() const {
		return indices.size();
	}

	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
};
class CubeMesh {
public:
	//constructor
	CubeMesh(GLfloat x, GLfloat y, GLfloat z) {

		// POSITION VECTOR

		//FRONT
		position_vertices.push_back({ -0.5f + x,    -0.5f + y,     0.5f + z});
		position_vertices.push_back({ 0.5f + x,    -0.5f + y,     0.5f + z});
		position_vertices.push_back({ -0.5f + x,     0.5f + y,     0.5f + z});
		position_vertices.push_back({ 0.5f + x,     0.5f + y,     0.5f + z});
		//BACK  			
		position_vertices.push_back({ -0.5f + x,    -0.5f + y,    -0.5f + z});
		position_vertices.push_back({ 0.5f + x,    -0.5f + y,    -0.5f + z});
		position_vertices.push_back({ -0.5f + x,     0.5f + y,    -0.5f + z});
		position_vertices.push_back({ 0.5f + x,     0.5f + y,    -0.5f + z});
		//LEFT  			
		position_vertices.push_back({ -0.5f + x,    -0.5f + y,    -0.5f + z});
		position_vertices.push_back({ -0.5f + x,    -0.5f + y,     0.5f + z});
		position_vertices.push_back({ -0.5f + x,     0.5f + y,    -0.5f + z});
		position_vertices.push_back({ -0.5f + x,     0.5f + y,     0.5f + z});
		//RIGHT 		
		position_vertices.push_back({ 0.5f + x,    -0.5f + y,    -0.5f + z});
		position_vertices.push_back({ 0.5f + x,    -0.5f + y,     0.5f + z});
		position_vertices.push_back({ 0.5f + x,     0.5f + y,    -0.5f + z});
		position_vertices.push_back({ 0.5f + x,     0.5f + y,     0.5f + z});
		//TOP   		
		position_vertices.push_back({ -0.5f + x,     0.5f + y,     0.5f + z});
		position_vertices.push_back({ 0.5f + x,     0.5f + y,     0.5f + z});
		position_vertices.push_back({ -0.5f + x,     0.5f + y,    -0.5f + z});
		position_vertices.push_back({ 0.5f + x,     0.5f + y,    -0.5f + z});
		//BOTTOM	
		position_vertices.push_back({ -0.5f + x,    -0.5f + y,     0.5f + z});
		position_vertices.push_back({ 0.5f + x,    -0.5f + y,     0.5f + z});
		position_vertices.push_back({ -0.5f + x,    -0.5f + y,    -0.5f + z});
		position_vertices.push_back({ 0.5f + x,    -0.5f + y,    -0.5f + z});

		// TEXTURE COORDINATES
		
		//FRONT
		texCoord_vertices.push_back({ 0.0f, 0.0f });
		texCoord_vertices.push_back({1.0f, 0.0f });
		texCoord_vertices.push_back({ 0.0f, 1.0f });
		texCoord_vertices.push_back({1.0f, 1.0f });
		//BACK  			
		texCoord_vertices.push_back({ 0.0f, 0.0f });
		texCoord_vertices.push_back({1.0f, 0.0f });
		texCoord_vertices.push_back({ 0.0f, 1.0f });
		texCoord_vertices.push_back({ 1.0f, 1.0f });
		//LEFT  			
		texCoord_vertices.push_back({0.0f, 0.0f });
		texCoord_vertices.push_back({1.0f, 0.0f });
		texCoord_vertices.push_back({0.0f, 1.0f });
		texCoord_vertices.push_back({1.0f, 1.0f });
		//RIGHT 		
		texCoord_vertices.push_back({0.0f, 0.0f });
		texCoord_vertices.push_back({1.0f, 0.0f });
		texCoord_vertices.push_back({0.0f, 1.0f });
		texCoord_vertices.push_back({1.0f, 1.0f });
		//TOP   		
		texCoord_vertices.push_back({ 0.0f, 0.0f });
		texCoord_vertices.push_back({1.0f, 0.0f });
		texCoord_vertices.push_back({ 0.0f, 1.0f });
		texCoord_vertices.push_back({1.0f, 1.0f });
		//BOTTOM	
		texCoord_vertices.push_back({ 0.0f, 0.0f });
		texCoord_vertices.push_back({1.0f, 0.0f });
		texCoord_vertices.push_back({0.0f, 1.0f });
		texCoord_vertices.push_back({.0f, 1.0f });
	}


	size_t getNumVertices() const {
		return position_vertices.size();
	}

	size_t getNumIndices() const {
		return indices.size();
	}

	std::vector<PositionVertex> position_vertices;
	std::vector<TextureVertex> texCoord_vertices;

	std::vector<GLuint> indices = {
		// FRONT
		0, 1, 2, 1, 3, 2,
		// BACK
		4, 6, 5, 5, 6, 7,
		// LEFT
		8, 9, 10, 9, 11, 10,
		// RIGHT
		12, 14, 13, 13, 14, 15,
		// TOP
		16, 17, 18, 17, 19, 18,
		// BOTTOM
		20, 22, 21, 21, 22, 23
	};
};


class Mesh {
public:
	std::vector<PositionVertex> position_verts;
	std::vector<TextureVertex> texture_coordinates;
	std::vector<GLuint> indices;
	std::vector<Vertex> vertices;
	glm::mat4 worldTransform = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	glm::vec4 color = glm::vec4(1.0f,1.0f,1.0f,1.0f);

	GLuint texture;
	Mesh(const std::vector<PositionVertex>& vertices, const std::vector<TextureVertex>& tex_coords, std::vector<GLuint>& indices, GLuint& texture) : position_verts(vertices), texture_coordinates(tex_coords), indices(indices), texture(texture) {

	}


	size_t get_num_vertices() const {
		return position_verts.size();
	}

	size_t get_num_indices() const {
		return indices.size();
	}
};

class BatchRenderer {
public:
	Shaderer shaderProgram;
	VAO vao;
	EBO ebo;

	VBO<PositionVertex> vbo_verts;
	VBO<TextureVertex> vbo_texCoords;

	std::vector<PositionVertex> verts_pos;
	std::vector<TextureVertex> tex_coords;

	std::vector<GLuint> indices;
	GLsizeiptr max_indices;
	GLsizeiptr max_vertices;
	Color color;

	GLuint texture;
	std::vector<Mesh> objects;


	BatchRenderer(Shaderer shaderProgram, std::vector<Mesh> objs, GLsizeiptr max_indices, GLsizeiptr max_vertices) : shaderProgram(shaderProgram), max_indices(max_indices),max_vertices(max_vertices), vbo_verts(max_vertices), vbo_texCoords(max_vertices), ebo(max_indices) {
		initializeMesh();
		objects = objs;
		for (size_t i = 0; i < objects.size(); i++) {
			add_to_mesh(objects[i].position_verts, objects[i].texture_coordinates, objects[i].indices);
		}
		
	}
	
	~BatchRenderer() {
		vao.Delete();
		vbo_verts.Delete();
		vbo_texCoords.Delete();
		ebo.Delete();
	}

	void initializeMesh() {
		// Generates Vertex Array Object and binds it
		vao.Bind();
		// Links VBO attributes such as coordinates and colors to VAO
		vao.LinkAttrib(vbo_verts, 0, 3, GL_FLOAT, sizeof(PositionVertex), (void*)offsetof(PositionVertex, position));
		vao.LinkAttrib(vbo_texCoords, 1, 2, GL_FLOAT, sizeof(TextureVertex), (void*)offsetof(TextureVertex, texCoord));
	}

	GLuint getShaderUniform(std::string textureSampler) {
		return glGetUniformLocation(shaderProgram.ID, textureSampler.c_str());
	}

	void update() {
		vao.Bind();
		vbo_verts.dynamic_update(verts_pos);
		vbo_texCoords.dynamic_update(tex_coords);
		ebo.dynamic_update(indices);
		vbo_verts.Unbind();
		vbo_texCoords.Unbind();
		ebo.Unbind();
		vao.Unbind();
		max_indices = indices.size();
		max_vertices = verts_pos.size();
	}

	void render(GLuint tex) {
		texture = tex;
		//activate current buffers
		vbo_verts.Bind();
		vbo_texCoords.Bind();
		vao.Bind();
		ebo.Bind();

		vbo_verts.dynamic_update(verts_pos);


		glEnable(GL_DEPTH_TEST);
		// Tell OpenGL which Shader Program we want to use
		shaderProgram.Activate();
		// binds textures
		glUniform1i(getShaderUniform("tex0"), 0);
		glBindTexture(GL_TEXTURE_2D, texture);
		// set current object
		set_color(color.white);
		// draws the object
		glDrawElements(GL_TRIANGLES, max_indices, GL_UNSIGNED_INT, 0);
		//deactivate current buffers
		vbo_verts.Unbind();
		vbo_texCoords.Unbind();
		vao.Unbind();
		ebo.Unbind();
	}

	void set_color(glm::vec4 color) {
		GLint customColorLocation = glGetUniformLocation(shaderProgram.ID, "color");
		// Set the value of the customColor uniform
		glUniform4f(customColorLocation, color.x, color.y, color.z, color.a);
	}

	void wireframe_render(bool get_state) {
		// Whether to render wireframe or full textured
		if (get_state) {
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

			GLint customColorLocation = glGetUniformLocation(shaderProgram.ID, "color");
			// Set the value of the customColor uniform
			glUniform4f(customColorLocation, 1.0f, 0.0f, 0.0f, 1.0f);
		}
		else {
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			GLint customColorLocation = glGetUniformLocation(shaderProgram.ID, "color");
			// Set the value of the customColor uniform
			glUniform4f(customColorLocation, 1.0f, 1.0f, 1.0f, 1.0f); // Set to red color
		}
	}



	void add_to_mesh(std::vector<PositionVertex>& pos_verts, std::vector<TextureVertex>& tex_verts, std::vector<GLuint>& objInds) {
		// find the current size of the parent indice vector
		GLuint indice_offset = verts_pos.size();
		// add the offset to each element of the objects indice
		for (int i = 0; i < objInds.size(); ++i) {
			objInds[i] += indice_offset;
		}
		// adds vertices of new object to parent vertex vector
		verts_pos.insert(verts_pos.end(), pos_verts.begin(), pos_verts.end());
		tex_coords.insert(tex_coords.end(), tex_verts.begin(), tex_verts.end());
		// add the object's indices to the parent indice vector
		indices.insert(indices.end(), objInds.begin(), objInds.end());
	}

	// getters
	GLuint getShaderUniform(Shaderer& objectShader, std::string textureSampler) {
		return glGetUniformLocation(objectShader.ID, textureSampler.c_str());
	}
	size_t getNumVertices() const {
		return verts_pos.size();
	}
	size_t getNumIndices() const {
		return indices.size();
	}

	//setters
	void set_world_transform(glm::mat4 worldTransform) {
		// Pass the modified worldTransform matrix to the shader
		GLint worldTransformLocation = glGetUniformLocation(shaderProgram.ID, "worldTransform");
		glUniformMatrix4fv(worldTransformLocation, 1, GL_FALSE, glm::value_ptr(worldTransform));
	}
};

class SingleRender {
public:
	GLsizeiptr max_indices;
	GLsizeiptr max_vertices;
	VBO<Vertex> vbo;
	VAO vao;
	EBO ebo;
	Shaderer shaderProgram;
	
	std::vector<Mesh> objectContainer;
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	glm::mat4 worldTransform = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	glm::vec4 color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

	Mesh object;
	int obj_offset;
	GLuint texture;

	SingleRender(Shaderer& shadeProgram, std::vector<Mesh>& obj) : object(obj[0]), shaderProgram(shaderProgram), vbo(obj[0].get_num_vertices()), ebo(obj[0].get_num_indices()) {
		// initialize pointer to the shader program
		shaderProgram = shadeProgram;
		//initialize internal object
		objectContainer = obj;
		initializeMesh();
		use_object(0);
		worldTransform = object.worldTransform;
		color = object.color;
		//Unbind buffers
		vbo.Unbind();
		vao.Unbind();
		ebo.Unbind();
	}

	~SingleRender() {
		vao.Delete();
		vbo.Delete();
		ebo.Delete();
	}

	void initializeMesh() {
		// Binds the vertex array
		vao.Bind();
		// Links VBO attributes position, texCoords, normals
		vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, position));
		vao.LinkAttrib(vbo, 1, 2, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));
	}

	void activate() {
		
		//bind relevant
		vbo.Bind();
		vao.Bind();
		ebo.Bind();
		// Tell OpenGL which Shader Program we want to use
		shaderProgram.Activate();

	}
	void deactivate() {
		//un-bind relevant
		vbo.Unbind();
		vao.Unbind();
		ebo.Unbind();
	}

	void render(int obj_index, glm::mat4& objectTransform, glm::vec4 objectColor) {
		if (obj_index != obj_offset) {
			use_object(obj_index);
		}
		// makes sure object is rendered correctly, make sure to clear the depth
		glEnable(GL_DEPTH_TEST);
		// Binds the texture to the object
		glUniform1i(getShaderUniform(shaderProgram, "tex0"), 0);
		glBindTexture(GL_TEXTURE_2D, texture);
		//update the objects transform
		worldTransform = objectTransform;
		color = objectColor;
		//update the objects color
		set_world_transform(worldTransform);
		set_color(color);
		// draws the object
		glDrawElements(GL_TRIANGLES, max_indices, GL_UNSIGNED_INT, 0);
		// current object tracker
		obj_offset = obj_index;
	}

	void wireframe_render(bool get_state) {
		// Whether to render wireframe or full textured
		if (get_state) {
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		else {
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
	}

		
private:


	void use_object(int obj_index) {
		//initialize internal object
		object = objectContainer[obj_index];
		max_indices = object.get_num_indices();
		max_vertices = object.get_num_vertices();
		vertices = object.vertices;
		indices = object.indices;
		texture = object.texture;
		//update vbo and ebo with object data
		vbo.dynamic_update(vertices);
		ebo.dynamic_update(indices);
	}
	// getters
	GLuint getShaderUniform(Shaderer& objectShader, std::string textureSampler) {
		return glGetUniformLocation(objectShader.ID, textureSampler.c_str());
	}
	
	//setters
	void set_world_transform(glm::mat4& worldTransform) {
		// Pass the modified worldTransform matrix to the shader
		GLint worldTransformLocation = glGetUniformLocation(shaderProgram.ID, "worldTransform");
		glUniformMatrix4fv(worldTransformLocation, 1, GL_FALSE, glm::value_ptr(worldTransform));
	}
	void set_color(glm::vec4 color) {
		GLint customColorLocation = glGetUniformLocation(shaderProgram.ID, "color");
		// Set the value of the customColor uniform
		glUniform4f(customColorLocation, color.x, color.y, color.z, color.a);
	}
};