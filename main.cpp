#include "engine.h"


static std::array<Vertex, 24> createCube(GLfloat x, GLfloat y, GLfloat z, GLfloat texID) {
	// Define the eight vertices of a cube
	std::array<Vertex, 24> vertices = { {
		//FRONT
		{ -0.5f + x,    -0.5f + y,     0.5f + z,      0.0f, 0.0f, texID }, // v0
		{  0.5f + x,    -0.5f + y,     0.5f + z,      1.0f, 0.0f, texID }, // v1
		{ -0.5f + x,     0.5f + y,     0.5f + z,      0.0f, 1.0f, texID }, // v2
		{ 0.5f  + x,     0.5f + y,     0.5f + z,      1.0f, 1.0f,  texID }, // v3
		//BACK  			  + y		    + z
		{ -0.5f + x,    -0.5f + y,    -0.5f + z,     0.0f, 0.0f, texID }, // v4
		{ 0.5f  + x,    -0.5f + y,    -0.5f + z,     1.0f, 0.0f,  texID }, // v5
		{ -0.5f + x,     0.5f + y,    -0.5f + z,     0.0f, 1.0f, texID }, // v6
		{ 0.5f  + x,     0.5f + y,    -0.5f + z,     1.0f, 1.0f,  texID },  // v7
		//LEFT  			  + y		    + z
		{ -0.5f + x,    -0.5f + y,    -0.5f + z,     0.0f, 0.0f, texID }, // v8
		{ -0.5f + x,    -0.5f + y,     0.5f + z,     1.0f, 0.0f, texID }, // v9
		{ -0.5f + x,     0.5f + y,    -0.5f + z,     0.0f, 1.0f, texID }, // v10
		{ -0.5f + x,     0.5f + y,     0.5f + z,     1.0f, 1.0f, texID }, // v11
		//RIGHT 			  + y		    + z
		{ 0.5f  + x,    -0.5f + y,    -0.5f + z,     0.0f, 0.0f,  texID }, // v12s
		{ 0.5f  + x,    -0.5f + y,     0.5f + z,     1.0f, 0.0f,  texID }, // v13
		{ 0.5f  + x,     0.5f + y,    -0.5f + z,     0.0f, 1.0f,  texID }, // v14
		{ 0.5f  + x,     0.5f + y,     0.5f + z,     1.0f, 1.0f,  texID },  // v15
		//TOP   			  + y		    + z
		{ -0.5f + x,     0.5f + y,     0.5f + z,     0.0f, 0.0f, texID }, // v16
		{ 0.5f  + x,     0.5f + y,     0.5f + z,     1.0f, 0.0f,  texID }, // v17
		{ -0.5f + x,     0.5f + y,    -0.5f + z,     0.0f, 1.0f, texID }, // v18
		{ 0.5f  + x,     0.5f + y,    -0.5f + z,     1.0f, 1.0f,  texID }, // v19
		//BOTTOM			  + y		    + z
		{ -0.5f + x,    -0.5f + y,     0.5f + z,    0.0f, 0.0f, texID }, // v20
		{ 0.5f  + x,    -0.5f + y,     0.5f + z,    1.0f, 0.0f,  texID }, // v21
		{ -0.5f + x,    -0.5f + y,    -0.5f + z,    0.0f, 1.0f, texID }, // v22
		{ 0.5f  + x,    -0.5f + y,    -0.5f + z,    1.0f, 1.0f,  texID }  // v23
	} };

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


	const size_t max_cube_count = 1000;
	const size_t max_vertex_count = max_cube_count * 24;
	const size_t max_index_count = max_cube_count * 36;

	



	// Generates Shader object
	Shaderer objectShader("shaders/shape.vs", "shaders/shape.fs");
	// Generates Vertex Array Object and binds it
	VAO VAO1;
	// Generates Vertex Buffer Object and links it to vertices
	VBO VBO1(sizeof(Vertex)*max_vertex_count);
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
	// Unbind all to prevent accidentally modifying them
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();


	// Load all the textures
	GLuint tex0 = LoadTexture("textures/dirt.png");
	GLuint tex1 = LoadTexture("textures/grasstop.png");
    GLuint tex2 = LoadTexture("textures/brick.png");


 	// Create camera object
	Camera camera(SCR_WIDTH, SCR_HEIGHT, glm::vec3(0.0f, 0.0f, 5.0f));



	// Timing variables for FPS calculation
	double lastTime = glfwGetTime();
	int frameCount = 0;

	float fps = 0.0f;

	Vertex verts[24 * max_cube_count];
	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		
		//set the window background color and clear the window buffer
		wnd.clear_buffer(color.skyBlue);

		// input handling
		input_callback(window, camera);
		//===============


		// Whether to render wireframe or full textured
		if (wireframe) { glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); }
		else { glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); }

		
		// Tell OpenGL which Shader Program we want to use
		objectShader.Activate();
		glEnable(GL_DEPTH_TEST);
		
		for (size_t i = 0; i < max_cube_count; ++i) {

			auto cube = createCube(GLfloat(i),0.0f,0.0f, 0.0f);
			// Calculate the offset for the current cube
			size_t offset = i * 24;
			// Copy cube vertices to the correct position in verts array
			memcpy(verts + offset, cube.data(), cube.size() * sizeof(Vertex));
		}
		VBO1.dynamic_update(verts, sizeof(verts));
		


		VAO1.Bind();
		// bind the textures to the texture units in the vbo/shader
		auto loc = glGetUniformLocation(objectShader.ID, "textureContainer");
		int samplers[4] = { 0,1,2,3};
		glUniform1iv(loc, 4, samplers);
		glBindTextureUnit(0, tex0);
		glBindTextureUnit(1, tex1);
		glBindTextureUnit(2, tex2);
		glBindTextureUnit(3, tex0);
		//render the cube
		glDrawElements(GL_TRIANGLES, max_index_count, GL_UNSIGNED_INT, 0);
		VBO1.Unbind();
		VAO1.Unbind();
			

		// update the camera
		camera.Matrix(45.0f, 0.1f, 180.0f, objectShader, "camMatrix");





		



		// Font Rendering
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glDisable(GL_DEPTH_TEST);
		font_shader.use();

		// Calculate FPS
		double currentTime = glfwGetTime();
		frameCount++;
		if (currentTime - lastTime >= 1.0)
		{
			// Calculate and return FPS
			fps = static_cast<float>(frameCount) / static_cast<float>(currentTime - lastTime);
			frameCount = 0;
			lastTime += 1.0;
		}



		
		//draw text
		RenderText(font_shader, "Alone Engine - V 0.0.1", 25.0f, 25.0f, 1.0f, color.white, font_vao, font_vbo);
		RenderText(font_shader, std::to_string(fps), 500.0f, 500.0f, 1.0f, color.white, font_vao, font_vbo);
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