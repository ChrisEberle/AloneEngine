#pragma once



static std::vector<Vertex> createQuad(GLfloat x, GLfloat y, GLfloat z, GLfloat texID) {
	std::vector<Vertex> vertices;

	//Quad
	vertices.push_back({ -0.5f + x,    -0.5f + y,     0.5f + z,      0.0f, 0.0f, texID + 2.0f });
	vertices.push_back({ 0.5f + x,    -0.5f + y,     0.5f + z,      1.0f, 0.0f, texID + 2.0f });
	vertices.push_back({ -0.5f + x,    -0.5f + y,     -0.5f + z,      0.0f, 1.0f, texID + 2.0f });
	vertices.push_back({ 0.5f + x,    -0.5f + y,     -0.5f + z,      1.0f, 1.0f,  texID + 2.0f });

	return vertices;
}

static std::vector<Vertex> createVertice(GLfloat x, GLfloat y, GLfloat z, GLfloat texCoord0, GLfloat texCoord1, GLfloat texID) {
	std::vector<Vertex> vertices;
	vertices.push_back({ x,y,z,texCoord0, texCoord1, texID });
	return vertices;
}


static std::vector<Vertex> createCube(GLfloat x, GLfloat y, GLfloat z, GLfloat texID) {
	std::vector<Vertex> vertices;
	//FRONT
	vertices.push_back({ -0.5f + x,    -0.5f + y,     0.5f + z,      0.0f, 0.0f, texID + 2.0f });
	vertices.push_back({ 0.5f + x,    -0.5f + y,     0.5f + z,      1.0f, 0.0f, texID + 2.0f });
	vertices.push_back({ -0.5f + x,     0.5f + y,     0.5f + z,      0.0f, 1.0f, texID + 2.0f });
	vertices.push_back({ 0.5f + x,     0.5f + y,     0.5f + z,      1.0f, 1.0f,  texID + 2.0f });
	//BACK  			
	vertices.push_back({ -0.5f + x,    -0.5f + y,    -0.5f + z,     0.0f, 0.0f, texID + 2.0f });
	vertices.push_back({ 0.5f + x,    -0.5f + y,    -0.5f + z,     1.0f, 0.0f,  texID + 2.0f });
	vertices.push_back({ -0.5f + x,     0.5f + y,    -0.5f + z,     0.0f, 1.0f, texID + 2.0f });
	vertices.push_back({ 0.5f + x,     0.5f + y,    -0.5f + z,     1.0f, 1.0f,  texID + 2.0f });
	//LEFT  			
	vertices.push_back({ -0.5f + x,    -0.5f + y,    -0.5f + z,     0.0f, 0.0f, texID + 2.0f });
	vertices.push_back({ -0.5f + x,    -0.5f + y,     0.5f + z,     1.0f, 0.0f, texID + 2.0f });
	vertices.push_back({ -0.5f + x,     0.5f + y,    -0.5f + z,     0.0f, 1.0f, texID + 2.0f });
	vertices.push_back({ -0.5f + x,     0.5f + y,     0.5f + z,     1.0f, 1.0f, texID + 2.0f });
	//RIGHT 		
	vertices.push_back({ 0.5f + x,    -0.5f + y,    -0.5f + z,     0.0f, 0.0f,  texID + 2.0f });
	vertices.push_back({ 0.5f + x,    -0.5f + y,     0.5f + z,     1.0f, 0.0f,  texID + 2.0f });
	vertices.push_back({ 0.5f + x,     0.5f + y,    -0.5f + z,     0.0f, 1.0f,  texID + 2.0f });
	vertices.push_back({ 0.5f + x,     0.5f + y,     0.5f + z,     1.0f, 1.0f,  texID + 2.0f });
	//TOP   		
	vertices.push_back({ -0.5f + x,     0.5f + y,     0.5f + z,     0.0f, 0.0f, texID + 1.0f });
	vertices.push_back({ 0.5f + x,     0.5f + y,     0.5f + z,     1.0f, 0.0f,  texID + 1.0f });
	vertices.push_back({ -0.5f + x,     0.5f + y,    -0.5f + z,     0.0f, 1.0f, texID + 1.0f });
	vertices.push_back({ 0.5f + x,     0.5f + y,    -0.5f + z,     1.0f, 1.0f,  texID + 1.0f });
	//BOTTOM	
	vertices.push_back({ -0.5f + x,    -0.5f + y,     0.5f + z,    0.0f, 0.0f, texID });
	vertices.push_back({ 0.5f + x,    -0.5f + y,     0.5f + z,    1.0f, 0.0f,  texID });
	vertices.push_back({ -0.5f + x,    -0.5f + y,    -0.5f + z,    0.0f, 1.0f, texID });
	vertices.push_back({ 0.5f + x,    -0.5f + y,    -0.5f + z,    1.0f, 1.0f,  texID });

	return vertices;
}

static std::vector<Vertex> createPlane(GLfloat originX, GLfloat originY, GLfloat originZ, GLfloat width, GLfloat height, GLuint rows, GLuint cols, GLfloat frequency, GLfloat amplitude, GLfloat textureScaleX, GLfloat textureScaleY) {
	std::vector<Vertex> vertices;

	for (GLuint i = 0; i < rows; ++i) {
		for (GLuint j = 0; j < cols; ++j) {
			GLfloat x = originX + j * (width / (cols - 1));
			GLfloat y = originY + glm::perlin(glm::vec2(x * frequency, i * frequency)) * amplitude;  // Use Perlin noise for height
			GLfloat z = originZ - i * (height / (rows - 1));




			// Calculate texCoordX to repeat within each column
			GLfloat texCoordX = static_cast<GLfloat>(j % cols) / (cols - 1) * textureScaleX;

			GLfloat texCoordY = static_cast<GLfloat>(i) / (rows - 1) * textureScaleY;


			GLfloat texID = 0.0f;  // You can adjust this based on your requirements

			vertices.push_back({ x, y, z, texCoordX, texCoordY, texID });
		}
	}

	return vertices;
}

static std::unique_ptr<GLuint[]> generatePlaneIndices(GLuint rows, GLuint cols) {
	GLuint max_indices = (rows - 1) * (cols - 1) * 6;
	std::unique_ptr<GLuint[]> indicesPLANE(new GLuint[max_indices]);

	GLuint offset = 6;
	for (GLuint i = 0; i < rows - 1; ++i) {
		for (GLuint j = 0; j < cols - 1; ++j) {
			GLuint currentVertex = i * cols + j;

			indicesPLANE[offset * (i * (cols - 1) + j)] = currentVertex;
			indicesPLANE[offset * (i * (cols - 1) + j) + 1] = currentVertex + 1;
			indicesPLANE[offset * (i * (cols - 1) + j) + 2] = currentVertex + cols;

			indicesPLANE[offset * (i * (cols - 1) + j) + 3] = currentVertex + 1;
			indicesPLANE[offset * (i * (cols - 1) + j) + 4] = currentVertex + cols + 1;  
			indicesPLANE[offset * (i * (cols - 1) + j) + 5] = currentVertex + cols;
		}
	}

	return indicesPLANE;
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