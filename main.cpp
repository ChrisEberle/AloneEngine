#include "engine.h"


static std::vector<Vertex> createCube(GLfloat x, GLfloat y, GLfloat z, GLfloat texID) {
	std::vector<Vertex> vertices;

		//FRONT
		vertices.push_back({ -0.5f + x,    -0.5f + y,     0.5f + z,      0.0f, 0.0f, texID });
		vertices.push_back({ 0.5f + x,    -0.5f + y,     0.5f + z,      1.0f, 0.0f, texID });
		vertices.push_back({ -0.5f + x,     0.5f + y,     0.5f + z,      0.0f, 1.0f, texID });
		vertices.push_back({ 0.5f  + x,     0.5f + y,     0.5f + z,      1.0f, 1.0f,  texID });
		//BACK  			
		vertices.push_back({ -0.5f + x,    -0.5f + y,    -0.5f + z,     0.0f, 0.0f, texID });
		vertices.push_back({ 0.5f  + x,    -0.5f + y,    -0.5f + z,     1.0f, 0.0f,  texID });
		vertices.push_back({ -0.5f + x,     0.5f + y,    -0.5f + z,     0.0f, 1.0f, texID });
		vertices.push_back({ 0.5f  + x,     0.5f + y,    -0.5f + z,     1.0f, 1.0f,  texID });
		//LEFT  			
		vertices.push_back({ -0.5f + x,    -0.5f + y,    -0.5f + z,     0.0f, 0.0f, texID });
		vertices.push_back({ -0.5f + x,    -0.5f + y,     0.5f + z,     1.0f, 0.0f, texID });
		vertices.push_back({ -0.5f + x,     0.5f + y,    -0.5f + z,     0.0f, 1.0f, texID });
		vertices.push_back({ -0.5f + x,     0.5f + y,     0.5f + z,     1.0f, 1.0f, texID });
		//RIGHT 		
		vertices.push_back({ 0.5f + x,    -0.5f + y,    -0.5f + z,     0.0f, 0.0f,  texID });
		vertices.push_back({ 0.5f + x,    -0.5f + y,     0.5f + z,     1.0f, 0.0f,  texID });
		vertices.push_back({ 0.5f + x,     0.5f + y,    -0.5f + z,     0.0f, 1.0f,  texID });
		vertices.push_back({ 0.5f + x,     0.5f + y,     0.5f + z,     1.0f, 1.0f,  texID });
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


void input_callback(GLFWwindow* window, Camera& camera) {
	if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS) {
		wireframe = true;
	}
	if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS) {
		wireframe = false;
	}
	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) {
		move_cube += 0.01f;
	}
	if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS) {
		move_cube -= 0.01f;
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


	const size_t max_cube_count = 1023;
	const size_t max_vertex_count = max_cube_count * 24;
	const size_t max_index_count = max_cube_count * 36;


	// Generates Shader object
	Shaderer objectShader("shaders/shape.vs", "shaders/shape.fs");
	// Generates Vertex Buffer Object and links it to vertices
	VBO VBO1(sizeof(Vertex)*max_vertex_count);
	// Generates Vertex Array Object and binds it
	VAO VAO1;
	// binds the VAO
	VAO1.Bind();
	// Links VBO attributes such as coordinates and colors to VAO
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, position));
	VAO1.LinkAttrib(VBO1, 1, 2, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex,texCoord));
	VAO1.LinkAttrib(VBO1, 2, 1, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, texId));



	GLuint indices[max_index_count];
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

		offset += 1;  // Move to the next cube
	}


	// Generates Element Buffer Object and links it to indices
	EBO EBO1(indices, sizeof(indices));



	// Load all the textures
	GLuint tex0 = LoadTexture("textures/dirt.png");
	GLuint tex1 = LoadTexture("textures/grasstop.png");
    GLuint tex2 = LoadTexture("textures/brick.png");
	// put textures in container array
	GLuint textureContainer[4] = { tex0,tex1,tex2 };


 	// Create camera object
	Camera camera(SCR_WIDTH, SCR_HEIGHT, glm::vec3(0.0f, 0.0f, 5.0f));

	
	// Timing variables for FPS calculation
	double lastTime = glfwGetTime();
	int frameCount = 0;
	float fps = 0.0f;

	std::vector<Vertex> verts(24 * max_cube_count);
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

		
		// Tell OpenGL which Shader Program we want to use
		objectShader.Activate();
		glEnable(GL_DEPTH_TEST);
		GLfloat row = 1.0f;
		GLfloat col = 1.0f;
		const size_t numRows = 32; // Assuming 32 blocks per row for a perfect square
		for (size_t i = 0; i < max_cube_count; ++i) {
			auto cube = createCube(col, 0.0f, row, 0);
			size_t offset = i * 24;
			std::copy(cube.begin(), cube.end(), verts.begin() + offset);

			col++; // Increment column for each cube

			// Check if the column reaches the end of a row
			if (col > numRows) {
				col = 1.0f; // Reset column to start from the beginning of the row
				row++;      // Move to the next row
			}
		}
		VBO1.dynamic_update(verts);
		


		VAO1.Bind();
		// bind the textures to the texture units in the vbo/shader
		texture_units(objectShader.ID, textureContainer, "textureContainer");
		glDrawElements(GL_TRIANGLES, max_index_count, GL_UNSIGNED_INT, 0);
		VBO1.Unbind();
		VAO1.Unbind();
			

		// update the camera
		camera.Matrix(45.0f, 0.1f, 180.0f, objectShader, "camMatrix");


		// Font Rendering
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glDisable(GL_DEPTH_TEST);
		font_shader.use();

		
		//draw text
		RenderText(font_shader, "Alone Engine - V 0.0.1", 25.0f, 25.0f, 1.0f, color.white, font_vao, font_vbo);
		RenderText(font_shader, std::to_string(get_fps(frameCount,lastTime)), 25.0f, SCR_HEIGHT - 50.0f, 1.0f, color.white, font_vao, font_vbo);
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