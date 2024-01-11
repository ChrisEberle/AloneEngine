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
static std::unique_ptr<GLuint[]> generateCubeChunkIndices(size_t max_index_count, GLuint spacing_offset) {
	std::unique_ptr<GLuint[]> indices(new GLuint[max_index_count]);
	GLuint offset = 0;

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
	std::vector<PositionVertex> position_vertices;
	std::vector<TextureVertex> texture_coordinates;
	std::vector <NormalVertex> normals;
	std::vector<GLuint> indices;
	GLuint num_indices;


	//constructor
	PlaneMesh(GLfloat originX, GLfloat originY, GLfloat originZ,
		GLfloat sizeX, GLfloat sizeZ, GLuint rows, GLuint cols,
		GLfloat numOctaves, GLfloat persistence,
		GLfloat textureScaleX, GLfloat textureScaleY) : num_indices((rows - 1)* (cols - 1) * 6)
	{

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

				position_vertices.push_back({ x, y, z});
				texture_coordinates.push_back({ texCoordX, texCoordY});
			}
		}

		
		std::vector<GLuint> planeIndices(num_indices);
		size_t offset = 6;
		for (size_t i = 0; i < static_cast<size_t>(rows) - 1; ++i) {
			for (size_t j = 0; j < static_cast<size_t>(cols) - 1; ++j) {
				size_t currentVertex = i * cols + j;

				planeIndices[offset * (i * (static_cast<size_t>(cols) - 1) + j)] = static_cast<GLuint>(currentVertex);
				planeIndices[offset * (i * (static_cast<size_t>(cols) - 1) + j) + 1] = static_cast<GLuint>(currentVertex) + 1;
				planeIndices[offset * (i * (static_cast<size_t>(cols) - 1) + j) + 2] = static_cast<GLuint>(currentVertex) + static_cast<GLuint>(cols);

				planeIndices[offset * (i * (static_cast<size_t>(cols) - 1) + j) + 3] = static_cast<GLuint>(currentVertex) + 1;
				planeIndices[offset * (i * (static_cast<size_t>(cols) - 1) + j) + 4] = static_cast<GLuint>(currentVertex) + static_cast<GLuint>(cols) + 1;
				planeIndices[offset * (i * (static_cast<size_t>(cols) - 1) + j) + 5] = static_cast<GLuint>(currentVertex) + static_cast<GLuint>(cols);
			}
		}
		// add the object's indices to the parent indice vector
		indices.insert(indices.end(), planeIndices.begin(), planeIndices.end());

		calculateNormals();
	}


	void calculateNormals() {
		normals.resize(position_vertices.size(), NormalVertex{ 0.0f, 0.0f, 0.0f });

		for (size_t i = 0; i < indices.size(); i += 3) {
			GLuint index1 = indices[i];
			GLuint index2 = indices[i + 1];
			GLuint index3 = indices[i + 2];

			// Get the vertices of the current triangle
			glm::vec3 v1(position_vertices[index1].position[0], position_vertices[index1].position[1], position_vertices[index1].position[2]);
			glm::vec3 v2(position_vertices[index2].position[0], position_vertices[index2].position[1], position_vertices[index2].position[2]);
			glm::vec3 v3(position_vertices[index3].position[0], position_vertices[index3].position[1], position_vertices[index3].position[2]);

			// Calculate the tangent vectors
			glm::vec3 tangent1 = v2 - v1;
			glm::vec3 tangent2 = v3 - v1;

			// Calculate the normal using the cross product of the tangents
			glm::vec3 normal = glm::normalize(glm::cross(tangent1, tangent2));

			// Accumulate the normals for each vertex of the triangle
			normals[index1].normals[0] += normal.x;
			normals[index1].normals[1] += normal.y;
			normals[index1].normals[2] += normal.z;

			normals[index2].normals[0] += normal.x;
			normals[index2].normals[1] += normal.y;
			normals[index2].normals[2] += normal.z;

			normals[index3].normals[0] += normal.x;
			normals[index3].normals[1] += normal.y;
			normals[index3].normals[2] += normal.z;
		}

		// Normalize the accumulated normals
		for (size_t i = 0; i < normals.size(); ++i) {
			glm::vec3 norm = glm::normalize(glm::vec3(normals[i].normals[0], normals[i].normals[1], normals[i].normals[2]));

			normals[i].normals[0] = norm.x;
			normals[i].normals[1] = norm.y;
			normals[i].normals[2] = norm.z;
		}
	}
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

		// NORMAL COORDINATES

		//FRONT
		normal_vertices.push_back({ 0.0f, 0.0f, 1.0f});
		normal_vertices.push_back({ 0.0f, 0.0f, 1.0f});
		normal_vertices.push_back({ 0.0f, 0.0f, 1.0f});
		normal_vertices.push_back({ 0.0f, 0.0f, 1.0f});
		//BACK  							
		normal_vertices.push_back({ 0.0f, 0.0f, -1.0f});
		normal_vertices.push_back({ 0.0f, 0.0f, -1.0f});
		normal_vertices.push_back({ 0.0f, 0.0f, -1.0f});
		normal_vertices.push_back({ 0.0f, 0.0f, -1.0f});
		//LEFT  					
		normal_vertices.push_back({ -1.0f, 0.0f, 0.0f});
		normal_vertices.push_back({ -1.0f, 0.0f, 0.0f});
		normal_vertices.push_back({ -1.0f, 0.0f, 0.0f});
		normal_vertices.push_back({ -1.0f, 0.0f, 0.0f});
		//RIGHT 						
		normal_vertices.push_back({ 1.0f, 0.0f, 0.0f});
		normal_vertices.push_back({ 1.0f, 0.0f, 0.0f});
		normal_vertices.push_back({ 1.0f, 0.0f, 0.0f});
		normal_vertices.push_back({ 1.0f, 0.0f, 0.0f});
		//TOP   								
		normal_vertices.push_back({ 0.0f, 1.0f, 0.0f});
		normal_vertices.push_back({ 0.0f, 1.0f, 0.0f});
		normal_vertices.push_back({ 0.0f, 1.0f, 0.0f});
		normal_vertices.push_back({ 0.0f, 1.0f, 0.0f});
		//BOTTOM								   
		normal_vertices.push_back({ 0.0f, -1.0f, 0.0f});
		normal_vertices.push_back({ 0.0f, -1.0f, 0.0f});
		normal_vertices.push_back({ 0.0f, -1.0f, 0.0f});
		normal_vertices.push_back({ 0.0f, -1.0f, 0.0f});

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
		texCoord_vertices.push_back({1.0f, 1.0f });
	}

	std::vector<PositionVertex> position_vertices;
	std::vector<TextureVertex> texCoord_vertices;
	std::vector<NormalVertex> normal_vertices;

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
	std::vector<NormalVertex> normal_verts;
	std::vector<GLuint> indices;
	glm::mat4 worldTransform = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	glm::vec4 color = glm::vec4(1.0f,1.0f,1.0f,1.0f);

	GLuint texture;
	Mesh(const std::vector<PositionVertex>& vertices, const std::vector<TextureVertex>& tex_coords, const std::vector<NormalVertex>& normals, std::vector<GLuint>& indices, GLuint& texture) : position_verts(vertices), texture_coordinates(tex_coords), indices(indices), texture(texture), normal_verts(normals) {

	}
};

class BatchRenderer {
public:
	// SHADER PROGRAM
	Shaderer shaderProgram;
	// BUFFERS
	VAO vao;
	EBO ebo;
	VBO<PositionVertex> vbo_verts;
	VBO<TextureVertex> vbo_texCoords;
	VBO<NormalVertex> vbo_normals;
	// OBJECT DATA
	std::vector<Mesh> objects;
	std::vector<PositionVertex> verts_pos;
	std::vector<TextureVertex> tex_coords;
	std::vector<NormalVertex> normal_vertices;
	std::vector<GLuint> indices;
	GLuint max_indices;
	GLuint max_vertices;
	// OTHER
	Color color;
	GLuint texture;

	bool wire_state = false;
	bool is_light = false;
	
	// CONSTRUCTOR
	BatchRenderer(Shaderer shaderProgram, GLuint& tex, std::vector<Mesh> objs, GLuint max_indices, GLuint max_vertices) : texture(tex), shaderProgram(shaderProgram), max_indices(max_indices),max_vertices(max_vertices), vbo_verts(max_vertices), vbo_texCoords(max_vertices), ebo(max_indices), vbo_normals(max_vertices) {
		
		objects = objs;
		for (size_t i = 0; i < objects.size(); i++) {
			add_to_mesh(objects[i].position_verts, objects[i].texture_coordinates, objects[i].normal_verts, objects[i].indices);
		}
	}
	// DESTRUCTOR
	~BatchRenderer() {
		vao.Delete();
		vbo_verts.Delete();
		vbo_texCoords.Delete();
		vbo_normals;
		ebo.Delete();
	}



	void update_all_buffers() {
		vao.Bind();
		vbo_verts.dynamic_update(verts_pos);
		vbo_texCoords.dynamic_update(tex_coords);
		vbo_normals.dynamic_update(normal_vertices);
		ebo.dynamic_update(indices);
		// Unbind all buffers
		vbo_verts.Unbind();
		vbo_texCoords.Unbind();
		vbo_normals.Unbind();
		ebo.Unbind();
		vao.Unbind();
		// set class vars
		max_indices = static_cast<GLuint>(indices.size());
		max_vertices = static_cast<GLuint>(verts_pos.size());
	}

	void render(Camera& camera, glm::vec3 lightPos) {
		//activate current buffers
		vbo_verts.Bind();
		vao.Bind();
		ebo.Bind();
		// update object positions
		vbo_verts.dynamic_update(verts_pos);
		// Object doesn't render correctly without this
		glEnable(GL_DEPTH_TEST);
		// Tell OpenGL which Shader Program we want to use
		shaderProgram.Activate();
		// binds textures
		
		if (!is_light) {
			// If object being render is a object and not a light
				glUniform1i(getShaderUniform("tex0"), 0);
				glBindTexture(GL_TEXTURE_2D, texture);
			
				shaderProgram.setVec3("objectColor", 1.0f, 1.0f, 1.0f);
				shaderProgram.setVec3("lightColor", glm::vec3(1.0f,1.0f,1.0f));
				shaderProgram.setVec3("lightPos", lightPos);

				// world transformation
				glm::mat4 model = glm::mat4(1.0f);
				shaderProgram.setMat4("model", model);
		}
		else {
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, lightPos);
			shaderProgram.setMat4("model", model);
		}

			
		camera.Matrix(45.0f, 0.1f, 10000.0f, shaderProgram, "camMatrix");
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
		wire_state = get_state;
		// Whether to render wireframe or full textured
		if (get_state) {
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		else {
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
	}

	void add_to_mesh(std::vector<PositionVertex>& pos_verts, std::vector<TextureVertex>& tex_verts, std::vector<NormalVertex>& normals, std::vector<GLuint>& objInds) {
		// find the current size of the parent indice vector
		GLuint indice_offset = GLuint(verts_pos.size());
		// add the offset to each element of the objects indice
		for (GLuint i = 0; i < objInds.size(); ++i) {
			objInds[i] += indice_offset;
		}
		// adds vertices of new object to parent vertex vector
		verts_pos.insert(verts_pos.end(), pos_verts.begin(), pos_verts.end());
		tex_coords.insert(tex_coords.end(), tex_verts.begin(), tex_verts.end());
		// add the object's indices to the parent indice vector
		indices.insert(indices.end(), objInds.begin(), objInds.end());
		normal_vertices.insert(normal_vertices.end(), normals.begin(), normals.end());
		update_all_buffers();
	}

	void initializeMeshObject() {
		is_light = false;
		// Generates Vertex Array Object and binds it
		vao.Bind();
		// Links VBO attributes such as coordinates and colors to VAO
		vao.LinkAttrib(vbo_verts, 0, 3, GL_FLOAT, sizeof(PositionVertex), (void*)offsetof(PositionVertex, position));
		vao.LinkAttrib(vbo_texCoords, 1, 2, GL_FLOAT, sizeof(TextureVertex), (void*)offsetof(TextureVertex, texCoord));
		vao.LinkAttrib(vbo_normals, 2, 3, GL_FLOAT, sizeof(NormalVertex), (void*)offsetof(NormalVertex, normals));
	}

	void initializeMeshCubeLight() {
		is_light = true;
		// Generates Vertex Array Object and binds it
		vao.Bind();
		// Links VBO attributes such as coordinates and colors to VAO
		vao.LinkAttrib(vbo_verts, 0, 3, GL_FLOAT, sizeof(PositionVertex), (void*)offsetof(PositionVertex, position));
	}

private:

	GLuint getShaderUniform(std::string textureSampler) {
		return glGetUniformLocation(shaderProgram.ID, textureSampler.c_str());
	}
};