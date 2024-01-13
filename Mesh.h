#pragma once

static void back_face_culling(bool back_cull) {
	if (back_cull) {
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
	}
}


class LightMesh {
public:
	std::vector<PositionVertex> position_coordinates;
	std::vector<GLuint> indices;

	glm::vec3 color;

	glm::mat4 worldTransform = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	GLuint texture;

	LightMesh(glm::vec3 COLOR) : color(COLOR) {}

	// Mesh Types
	void createCube(GLfloat x, GLfloat y, GLfloat z) {
		//                     POSITION VECTOR
		//FRONT
		position_coordinates.push_back({ -0.5f + x,    -0.5f + y,     0.5f + z });
		position_coordinates.push_back({ 0.5f + x,    -0.5f + y,     0.5f + z });
		position_coordinates.push_back({ -0.5f + x,     0.5f + y,     0.5f + z });
		position_coordinates.push_back({ 0.5f + x,     0.5f + y,     0.5f + z });
		//BACK  			
		position_coordinates.push_back({ -0.5f + x,    -0.5f + y,    -0.5f + z });
		position_coordinates.push_back({ 0.5f + x,    -0.5f + y,    -0.5f + z });
		position_coordinates.push_back({ -0.5f + x,     0.5f + y,    -0.5f + z });
		position_coordinates.push_back({ 0.5f + x,     0.5f + y,    -0.5f + z });
		//LEFT  			
		position_coordinates.push_back({ -0.5f + x,    -0.5f + y,    -0.5f + z });
		position_coordinates.push_back({ -0.5f + x,    -0.5f + y,     0.5f + z });
		position_coordinates.push_back({ -0.5f + x,     0.5f + y,    -0.5f + z });
		position_coordinates.push_back({ -0.5f + x,     0.5f + y,     0.5f + z });
		//RIGHT 		
		position_coordinates.push_back({ 0.5f + x,    -0.5f + y,    -0.5f + z });
		position_coordinates.push_back({ 0.5f + x,    -0.5f + y,     0.5f + z });
		position_coordinates.push_back({ 0.5f + x,     0.5f + y,    -0.5f + z });
		position_coordinates.push_back({ 0.5f + x,     0.5f + y,     0.5f + z });
		//TOP   		
		position_coordinates.push_back({ -0.5f + x,     0.5f + y,     0.5f + z });
		position_coordinates.push_back({ 0.5f + x,     0.5f + y,     0.5f + z });
		position_coordinates.push_back({ -0.5f + x,     0.5f + y,    -0.5f + z });
		position_coordinates.push_back({ 0.5f + x,     0.5f + y,    -0.5f + z });
		//BOTTOM	
		position_coordinates.push_back({ -0.5f + x,    -0.5f + y,     0.5f + z });
		position_coordinates.push_back({ 0.5f + x,    -0.5f + y,     0.5f + z });
		position_coordinates.push_back({ -0.5f + x,    -0.5f + y,    -0.5f + z });
		position_coordinates.push_back({ 0.5f + x,    -0.5f + y,    -0.5f + z });

		indices = {
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
	}

};
class Mesh {
public:
	std::vector<PositionVertex> position_coordinates;
	std::vector<TextureVertex> texture_coordinates;
	std::vector<NormalVertex> normals;
	std::vector<GLuint> indices;

	glm::vec3 color;

	glm::mat4 worldTransform = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	GLuint texture;

	// Constructor
	Mesh(glm::vec3 objColor, GLuint& texture) : texture(texture), color(objColor) {
	}

	// Mesh Types
	void createCube(GLfloat x, GLfloat y, GLfloat z) {
			//                     POSITION VECTOR
			//FRONT
			position_coordinates.push_back({ -0.5f + x,    -0.5f + y,     0.5f + z });
			position_coordinates.push_back({ 0.5f + x,    -0.5f + y,     0.5f + z });
			position_coordinates.push_back({ -0.5f + x,     0.5f + y,     0.5f + z });
			position_coordinates.push_back({ 0.5f + x,     0.5f + y,     0.5f + z });
			//BACK  			
			position_coordinates.push_back({ -0.5f + x,    -0.5f + y,    -0.5f + z });
			position_coordinates.push_back({ 0.5f + x,    -0.5f + y,    -0.5f + z });
			position_coordinates.push_back({ -0.5f + x,     0.5f + y,    -0.5f + z });
			position_coordinates.push_back({ 0.5f + x,     0.5f + y,    -0.5f + z });
			//LEFT  			
			position_coordinates.push_back({ -0.5f + x,    -0.5f + y,    -0.5f + z });
			position_coordinates.push_back({ -0.5f + x,    -0.5f + y,     0.5f + z });
			position_coordinates.push_back({ -0.5f + x,     0.5f + y,    -0.5f + z });
			position_coordinates.push_back({ -0.5f + x,     0.5f + y,     0.5f + z });
			//RIGHT 		
			position_coordinates.push_back({ 0.5f + x,    -0.5f + y,    -0.5f + z });
			position_coordinates.push_back({ 0.5f + x,    -0.5f + y,     0.5f + z });
			position_coordinates.push_back({ 0.5f + x,     0.5f + y,    -0.5f + z });
			position_coordinates.push_back({ 0.5f + x,     0.5f + y,     0.5f + z });
			//TOP   		
			position_coordinates.push_back({ -0.5f + x,     0.5f + y,     0.5f + z });
			position_coordinates.push_back({ 0.5f + x,     0.5f + y,     0.5f + z });
			position_coordinates.push_back({ -0.5f + x,     0.5f + y,    -0.5f + z });
			position_coordinates.push_back({ 0.5f + x,     0.5f + y,    -0.5f + z });
			//BOTTOM	
			position_coordinates.push_back({ -0.5f + x,    -0.5f + y,     0.5f + z });
			position_coordinates.push_back({ 0.5f + x,    -0.5f + y,     0.5f + z });
			position_coordinates.push_back({ -0.5f + x,    -0.5f + y,    -0.5f + z });
			position_coordinates.push_back({ 0.5f + x,    -0.5f + y,    -0.5f + z });
			//             TEXTURE COORDINATES
			//FRONT
			texture_coordinates.push_back({ 0.0f, 0.0f });
			texture_coordinates.push_back({ 1.0f, 0.0f });
			texture_coordinates.push_back({ 0.0f, 1.0f });
			texture_coordinates.push_back({ 1.0f, 1.0f });
			//BACK  			
			texture_coordinates.push_back({ 0.0f, 0.0f });
			texture_coordinates.push_back({ 1.0f, 0.0f });
			texture_coordinates.push_back({ 0.0f, 1.0f });
			texture_coordinates.push_back({ 1.0f, 1.0f });
			//LEFT  			
			texture_coordinates.push_back({ 0.0f, 0.0f });
			texture_coordinates.push_back({ 1.0f, 0.0f });
			texture_coordinates.push_back({ 0.0f, 1.0f });
			texture_coordinates.push_back({ 1.0f, 1.0f });
			//RIGHT 		
			texture_coordinates.push_back({ 0.0f, 0.0f });
			texture_coordinates.push_back({ 1.0f, 0.0f });
			texture_coordinates.push_back({ 0.0f, 1.0f });
			texture_coordinates.push_back({ 1.0f, 1.0f });
			//TOP   		
			texture_coordinates.push_back({ 0.0f, 0.0f });
			texture_coordinates.push_back({ 1.0f, 0.0f });
			texture_coordinates.push_back({ 0.0f, 1.0f });
			texture_coordinates.push_back({ 1.0f, 1.0f });
			//BOTTOM	
			texture_coordinates.push_back({ 0.0f, 0.0f });
			texture_coordinates.push_back({ 1.0f, 0.0f });
			texture_coordinates.push_back({ 0.0f, 1.0f });
			texture_coordinates.push_back({ 1.0f, 1.0f });
			//           NORMAL COORDINATES
			//FRONT
			normals.push_back({ 0.0f, 0.0f, 1.0f });
			normals.push_back({ 0.0f, 0.0f, 1.0f });
			normals.push_back({ 0.0f, 0.0f, 1.0f });
			normals.push_back({ 0.0f, 0.0f, 1.0f });
			//BACK  							
			normals.push_back({ 0.0f, 0.0f, -1.0f });
			normals.push_back({ 0.0f, 0.0f, -1.0f });
			normals.push_back({ 0.0f, 0.0f, -1.0f });
			normals.push_back({ 0.0f, 0.0f, -1.0f });
			//LEFT  					
			normals.push_back({ -1.0f, 0.0f, 0.0f });
			normals.push_back({ -1.0f, 0.0f, 0.0f });
			normals.push_back({ -1.0f, 0.0f, 0.0f });
			normals.push_back({ -1.0f, 0.0f, 0.0f });
			//RIGHT 						
			normals.push_back({ 1.0f, 0.0f, 0.0f });
			normals.push_back({ 1.0f, 0.0f, 0.0f });
			normals.push_back({ 1.0f, 0.0f, 0.0f });
			normals.push_back({ 1.0f, 0.0f, 0.0f });
			//TOP   								
			normals.push_back({ 0.0f, 1.0f, 0.0f });
			normals.push_back({ 0.0f, 1.0f, 0.0f });
			normals.push_back({ 0.0f, 1.0f, 0.0f });
			normals.push_back({ 0.0f, 1.0f, 0.0f });
			//BOTTOM								   
			normals.push_back({ 0.0f, -1.0f, 0.0f });
			normals.push_back({ 0.0f, -1.0f, 0.0f });
			normals.push_back({ 0.0f, -1.0f, 0.0f });
			normals.push_back({ 0.0f, -1.0f, 0.0f });

		    indices = {
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
	}
	void createPlane(GLfloat originX, GLfloat originY, GLfloat originZ,GLfloat sizeX, GLfloat sizeZ, GLuint rows, GLuint cols,GLfloat numOctaves, GLfloat persistence,GLfloat textureScaleX, GLfloat textureScaleY) {

		GLuint num_indices = (rows - 1) * (cols - 1) * 6;

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


					// Calculate texCoordX to repeat within each column
					GLfloat texCoordX = static_cast<GLfloat>(j % cols) / (cols - 1) * textureScaleX;

					GLfloat texCoordY = static_cast<GLfloat>(i) / (rows - 1) * textureScaleY;

					position_coordinates.push_back({ x, y, z });
					texture_coordinates.push_back({ texCoordX, texCoordY });
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

			// NORMAL CALCULATIONS
			normals.resize(position_coordinates.size(), NormalVertex{ 0.0f, 0.0f, 0.0f });
			for (size_t i = 0; i < indices.size(); i += 3) {
				GLuint index1 = indices[i];
				GLuint index2 = indices[i + 1];
				GLuint index3 = indices[i + 2];

				// Get the vertices of the current triangle
				glm::vec3 v1(position_coordinates[index1].position[0], position_coordinates[index1].position[1], position_coordinates[index1].position[2]);
				glm::vec3 v2(position_coordinates[index2].position[0], position_coordinates[index2].position[1], position_coordinates[index2].position[2]);
				glm::vec3 v3(position_coordinates[index3].position[0], position_coordinates[index3].position[1], position_coordinates[index3].position[2]);

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
	void modelObj(ModelOBJ& model) {
		position_coordinates = model.position_coordinates;
		texture_coordinates = model.texture_coordinates;
		normals = model.normal_coordinates;
		indices = model.indices;
	}
private:
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
			add_to_mesh(objects[i].position_coordinates, objects[i].texture_coordinates, objects[i].normals, objects[i].indices);
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

	void render(Camera& camera, glm::vec3 lightPos, float lt) {
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
				shaderProgram.setVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
				shaderProgram.setVec3("viewPos", camera.Position);
				shaderProgram.setVec3("lightPos", lightPos);
				shaderProgram.setFloat("lightIntensity", lt);

				// world transformation
				glm::mat4 model = glm::mat4(1.0f);
				shaderProgram.setMat4("model", model);
		}
		else {
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, lightPos);
			shaderProgram.setVec3("objectColor", objects[0].color);
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