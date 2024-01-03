#include "engine.h"

static std::vector<Vertex> createQuad(GLfloat x, GLfloat y, GLfloat z, GLfloat texID) {
	std::vector<Vertex> vertices;

	//Quad
	vertices.push_back({ -0.5f + x,    -0.5f + y,     0.5f + z,      0.0f, 0.0f, texID + 2.0f });
	vertices.push_back({ 0.5f + x,    -0.5f + y,     0.5f + z,      1.0f, 0.0f, texID + 2.0f });
	vertices.push_back({ -0.5f + x,    -0.5f + y,     -0.5f + z,      0.0f, 1.0f, texID + 2.0f });
	vertices.push_back({ 0.5f + x,    -0.5f + y,     -0.5f + z,      1.0f, 1.0f,  texID + 2.0f });

	return vertices;
}


static std::vector<Vertex> createCube(GLfloat x, GLfloat y, GLfloat z, GLfloat texID) {
	std::vector<Vertex> vertices;

		//FRONT
		vertices.push_back({ -0.5f + x,    -0.5f + y,     0.5f + z,      0.0f, 0.0f, texID  + 2.0f});
		vertices.push_back({ 0.5f + x,    -0.5f + y,     0.5f + z,      1.0f, 0.0f, texID   + 2.0f});
		vertices.push_back({ -0.5f + x,     0.5f + y,     0.5f + z,      0.0f, 1.0f, texID  + 2.0f});
		vertices.push_back({ 0.5f  + x,     0.5f + y,     0.5f + z,      1.0f, 1.0f,  texID + 2.0f});
		//BACK  			
		vertices.push_back({ -0.5f + x,    -0.5f + y,    -0.5f + z,     0.0f, 0.0f, texID  + 2.0f});
		vertices.push_back({ 0.5f  + x,    -0.5f + y,    -0.5f + z,     1.0f, 0.0f,  texID + 2.0f});
		vertices.push_back({ -0.5f + x,     0.5f + y,    -0.5f + z,     0.0f, 1.0f, texID  + 2.0f});
		vertices.push_back({ 0.5f  + x,     0.5f + y,    -0.5f + z,     1.0f, 1.0f,  texID + 2.0f});
		//LEFT  			
		vertices.push_back({ -0.5f + x,    -0.5f + y,    -0.5f + z,     0.0f, 0.0f, texID + 2.0f});
		vertices.push_back({ -0.5f + x,    -0.5f + y,     0.5f + z,     1.0f, 0.0f, texID + 2.0f});
		vertices.push_back({ -0.5f + x,     0.5f + y,    -0.5f + z,     0.0f, 1.0f, texID + 2.0f});
		vertices.push_back({ -0.5f + x,     0.5f + y,     0.5f + z,     1.0f, 1.0f, texID + 2.0f});
		//RIGHT 		
		vertices.push_back({ 0.5f + x,    -0.5f + y,    -0.5f + z,     0.0f, 0.0f,  texID + 2.0f});
		vertices.push_back({ 0.5f + x,    -0.5f + y,     0.5f + z,     1.0f, 0.0f,  texID + 2.0f});
		vertices.push_back({ 0.5f + x,     0.5f + y,    -0.5f + z,     0.0f, 1.0f,  texID + 2.0f});
		vertices.push_back({ 0.5f + x,     0.5f + y,     0.5f + z,     1.0f, 1.0f,  texID + 2.0f});
		//TOP   		
		vertices.push_back({ -0.5f + x,     0.5f + y,     0.5f + z,     0.0f, 0.0f, texID  + 1.0f});
		vertices.push_back({ 0.5f  + x,     0.5f + y,     0.5f + z,     1.0f, 0.0f,  texID + 1.0f});
		vertices.push_back({ -0.5f + x,     0.5f + y,    -0.5f + z,     0.0f, 1.0f, texID  + 1.0f});
		vertices.push_back({ 0.5f  + x,     0.5f + y,    -0.5f + z,     1.0f, 1.0f,  texID + 1.0f});
		//BOTTOM	
		vertices.push_back({ -0.5f + x,    -0.5f + y,     0.5f + z,    0.0f, 0.0f, texID });
		vertices.push_back({ 0.5f  + x,    -0.5f + y,     0.5f + z,    1.0f, 0.0f,  texID });
		vertices.push_back({ -0.5f + x,    -0.5f + y,    -0.5f + z,    0.0f, 1.0f, texID });
		vertices.push_back({ 0.5f  + x,    -0.5f + y,    -0.5f + z,    1.0f, 1.0f,  texID });

	return vertices;
}
 

void move_cube(GLFWwindow* window, std::vector<Vertex>& verts, int numVertices) {
	

	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) {
		// Modify the values in the verts vector
		for (int i = 0; i < numVertices; ++i) {
			// Access and modify the values of the vertices in the verts vector
			verts[i].position[0] = verts[i].position[0] + xpos;  // Modify X-coordinate
			// Modify other attributes if needed...
		}
	}
	if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS) {
		// Modify the values in the verts vector
		for (int i = 0; i < numVertices; ++i) {
			// Access and modify the values of the vertices in the verts vector
			verts[i].position[0] = verts[i].position[0] -xpos;  // Modify X-coordinate
			// Modify other attributes if needed...
		}
	}
}
static std::vector<Vertex> createPlane(GLfloat originX, GLfloat originY, GLfloat originZ, GLfloat width, GLfloat height, GLuint rows, GLuint cols, GLfloat frequency, GLfloat amplitude) {
	std::vector<Vertex> vertices;

	for (GLuint i = 0; i < rows; ++i) {
		for (GLuint j = 0; j < cols; ++j) {
			GLfloat x = originX + j * (width / (cols - 1));
			GLfloat y = originY + glm::perlin(glm::vec2(x * frequency, i * frequency)) * amplitude;  // Use Perlin noise for height
			GLfloat z = originZ - i * (height / (rows - 1));

			// Calculate texCoordX to repeat within each column
			GLfloat texCoordX = static_cast<GLfloat>(j % cols) / (cols - 1);

			GLfloat texCoordY = static_cast<GLfloat>(i) / (rows - 1);

			GLfloat texID = 0.0f;  // You can adjust this based on your requirements

			vertices.push_back({ x, y, z, texCoordX, texCoordY, texID });
		}
	}

	return vertices;
}

std::unique_ptr<GLuint[]> generatePlaneIndices(GLuint rows, GLuint cols) {
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
			indicesPLANE[offset * (i * (cols - 1) + j) + 4] = currentVertex + cols;
			indicesPLANE[offset * (i * (cols - 1) + j) + 5] = currentVertex + cols + 1;
		}
	}

	return indicesPLANE;
}


std::unique_ptr<GLuint[]> generateCubeIndices(size_t max_index_count, size_t spacing_offset) {
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


// Assuming GLuint is defined somewhere in your code
typedef unsigned int GLuint;

std::unique_ptr<GLuint[]> concatenateArrays(const std::unique_ptr<GLuint[]>& arr1, size_t size1, const std::unique_ptr<GLuint[]>& arr2, size_t size2) {
	std::unique_ptr<GLuint[]> result(new GLuint[size1 + size2]);

	// Copy elements from the first array
	std::copy(arr1.get(), arr1.get() + size1, result.get());

	// Copy elements from the second array
	std::copy(arr2.get(), arr2.get() + size2, result.get() + size1);

	return result;
}




void input_callback(GLFWwindow* window, Camera& camera) {
	if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS) {
		wireframe = true;
	}
	if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS) {
		wireframe = false;
	}
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		exit(EXIT_SUCCESS);
	}
	// Handles camera inputs
	camera.Inputs(window);
}


int main()
{
	// GLFW window creation ang initialization of GLAD
	GLFWwindow* window = wnd.createWindow(SCR_WIDTH, SCR_HEIGHT, "Alone Engine V - 0.0.1");
	wnd.glad_init();
	wnd.print_gl_renderer();
	wnd.framebuffer_size_callback(window, SCR_WIDTH, SCR_HEIGHT);


	// Font Rendering Initialization
	Shader font_shader("shaders/text.vs", "shaders/text.fs");
	GLuint font_vao, font_vbo;
	FT_Library ft;
	FT_Face face;
	ft_init(ft, face, font_shader, filepath, SCR_WIDTH, SCR_HEIGHT);
	init_renderer(font_vao, font_vbo);


	// 3 by 3 plane
	const GLfloat cols_rows = 1000;
	const GLfloat max_verts = cols_rows*cols_rows;
	const GLfloat max_indices = ((cols_rows -1)*(cols_rows-1)) * 6;
	const GLfloat max_quads = ((cols_rows - 1) * (cols_rows - 1));


	// Generates Shader object
	Shaderer objectShader("shaders/shape.vs", "shaders/shape.fs");
	// Generates Vertex Buffer Object and links it to vertices
	VBO VBO1(sizeof(Vertex)*(max_verts));
	// Generates Vertex Array Object and binds it
	VAO VAO1;
	// binds the VAO
	VAO1.Bind();
	// Links VBO attributes such as coordinates and colors to VAO
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, position));
	VAO1.LinkAttrib(VBO1, 1, 2, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex,texCoord));
	VAO1.LinkAttrib(VBO1, 2, 1, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, texId));




	// Use smart pointer for verts
	std::unique_ptr<std::vector<Vertex>> verts = std::make_unique<std::vector<Vertex>>(max_verts);
	// Generate indices for the plane and chunk
	std::unique_ptr<GLuint[]> indicesPLANE = generatePlaneIndices(cols_rows, cols_rows);
	std::vector<Vertex> plane = createPlane(0.0f, 0.0f, 0.0f, 100.0f, 100.0f, cols_rows, cols_rows, 0.01f, 5.0f);
	std::copy(plane.begin(), plane.end(), verts->begin());


	// Generates Element Buffer Object and links it to indices
	EBO EBO1(indicesPLANE.get(), sizeof(GLuint) * (max_indices));

	GLuint tex0 = LoadTexture("textures/grey_sand.png");
	GLuint tex1 = LoadTexture("textures/dirt.png");
	GLuint tex2 = LoadTexture("textures/dirt.png");
	// put textures in container array
	GLuint textureContainer[4] = { tex0,tex1,tex2 };


 	// Create camera object
	Camera camera(SCR_WIDTH, SCR_HEIGHT, glm::vec3(0.0f, 0.0f, 5.0f));

	// Timing variables for FPS calculation
	double lastTime = glfwGetTime();
	int frameCount = 0;
	float fps = 0.0f;

	GLfloat sizw = 100.0f;
	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		//set the window background color and clear the window buffer
		wnd.clear_buffer(color.skyBlue);

		// input handling
		input_callback(window, camera);
		//===============


		//switch between textured or wireframe
		wireframe_state(wireframe);


		move_cube(window, *verts, max_verts);
		// Tell OpenGL which Shader Program we want to use
		objectShader.Activate();
		glEnable(GL_DEPTH_TEST);
		VBO1.dynamic_update(*verts);
		VAO1.Bind();
		// bind the textures to the texture units in the vbo/shader
		texture_units(objectShader.ID, textureContainer, "textureContainer");
		glDrawElements(GL_TRIANGLES, max_indices, GL_UNSIGNED_INT, 0);
		VBO1.Unbind();
		VAO1.Unbind();
			


		// update the camera
		camera.Matrix(45.0f, 0.1f, 10000.0f, objectShader, "camMatrix");


		// Font Rendering
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glDisable(GL_DEPTH_TEST);
		font_shader.use();


		//draw text
		RenderText(font_shader, "Alone Engine - V 0.0.1", 25.0f, 25.0f, 1.0f, color.white, font_vao, font_vbo);
		RenderText(font_shader, std::to_string(get_fps(frameCount,lastTime)), 25.0f, SCR_HEIGHT - 50.0f, 1.0f, color.white, font_vao, font_vbo);
		RenderText(font_shader, std::to_string((int(max_verts))), 500.0f, SCR_HEIGHT - 50.0f, 1.0f, color.white, font_vao, font_vbo);
		// ==========================================================

		
		// Swap the back buffer with the front buffer
		wnd.swap_buffers(window);
		// Take care of all GLFW events and swap buffers
		wnd.events();
	}
	// Delete all the objects we've created
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	objectShader.Delete();
	font_shader.Delete();
	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}