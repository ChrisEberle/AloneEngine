#include "engine.h"

bool wireframe = false;
// Vertices coordinates
GLfloat vertices[] =
{ //     COORDINATES      /   TexCoord  //
	-0.5f, 0.0f,  0.5f,  	0.0f, 0.0f,
	-0.5f, 0.0f, -0.5f,  	3.0f, 0.0f,
	 0.5f, 0.0f, -0.5f,  	0.0f, 0.0f,
	 0.5f, 0.0f,  0.5f,  	3.0f, 0.0f,
	 0.0f, 0.8f,  0.0f,  	1.5f, 3.0f
};

// Indices for vertices order
GLuint indices[] =
{
	0, 1, 2,
	0, 2, 3,
	0, 1, 4,
	1, 2, 4,
	2, 3, 4,
	3, 0, 4
};


void input_callback(GLFWwindow* window, Camera& camera) {
	if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS) {
		wireframe = true;
	}
	if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS) {
		wireframe = false;
	}
	// Handles camera inputs
	camera.Inputs(window);
}

int main()
{


	// GLFW window creation ang initialization of GLAD
	GLFWwindow* window = wnd.createWindow(SCR_WIDTH, SCR_HEIGHT, "Alone Engine V - 0.0.1");
	wnd.glad_init();
	wnd.framebuffer_size_callback(window, SCR_WIDTH, SCR_HEIGHT);

	


	// Font Rendering Initialization
	Shader font_shader("shaders/text.vs", "shaders/text.fs");
	GLuint font_vao, font_vbo;
	FT_Library ft;
	FT_Face face;
	ft_init(ft, face, font_shader, filepath, SCR_WIDTH, SCR_HEIGHT);
	init_renderer(font_vao, font_vbo);





	// Generates Shader object
	Shaderer shaderProgram("shaders/shape.vs", "shaders/shape.fs");
	// Generates Vertex Array Object and binds it
	VAO VAO1;
	// Generates Vertex Buffer Object and links it to vertices
	VBO VBO1(vertices, sizeof(vertices));
	// binds the VAO
	VAO1.Bind();
	// Generates Element Buffer Object and links it to indices
	EBO EBO1(indices, sizeof(indices));
	// Links VBO attributes such as coordinates and colors to VAO
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 5 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	// Unbind all to prevent accidentally modifying them
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();
	// filepath name for the texture you are going to be using
	std::string texPath = "textures/grasstop.png";
	// Texture
	Texture tex0(texPath.c_str(), GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	tex0.texUnit(shaderProgram, "tex0", 0);




	// Creates camera object
	Camera camera(SCR_WIDTH, SCR_HEIGHT, glm::vec3(0.0f, 0.0f, 2.0f));


	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		//set the window background color and clear the buffer
		wnd.clear_buffer(color.skyBlue);

		// input handling
		// ==========================================================
		input_callback(window, camera);


		// Shape Rendering
		// ==========================================================

		glEnable(GL_DEPTH_TEST);
		// Whether to render wireframe or full textured
		if (wireframe) {glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);}
		else { glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); }
		// Tell OpenGL which Shader Program we want to use
		shaderProgram.Activate();
		// Updates and exports the camera matrix to the Vertex Shader
		camera.Matrix(45.0f, 0.1f, 100.0f, shaderProgram, "camMatrix");
		// Binds texture so that is appears in rendering
		tex0.Bind();
		// Bind the VAO so OpenGL knows to use it
		VAO1.Bind();
		// Draw primitives, number of indices, datatype of indices, index of indices
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);


		// Font Rendering
		// ==========================================================
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glDisable(GL_DEPTH_TEST);
		font_shader.use();
		//draw text
		RenderText(font_shader, "Alone Engine - V 0.0.1", 25.0f, 25.0f, 1.0f, color.white, font_vao, font_vbo);


		// Swap the back buffer with the front buffer
		wnd.swap_buffers(window);


		


		// Take care of all GLFW events and swap buffers
		wnd.events();
	}
	// Delete all the objects we've created
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	tex0.Delete();
	shaderProgram.Delete();
	font_shader.Delete();
	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}