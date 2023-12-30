#include "engine.h"

bool wireframe = false;


struct Vertex {
	GLfloat position[3];
	GLfloat texCoord[2];
	GLfloat texId;
};

GLfloat vertices[] =
{ //          COORDINATES        // TexCoord  //
	// FRONT
	   -0.5f,   -0.5f,    0.5f,      0.0f, 0.0f, 0.0f,// fbl0
	    0.5f,   -0.5f,    0.5f,      1.0f, 0.0f, 0.0f,// fbr1
	   -0.5f,    0.5f,    0.5f,      0.0f, 1.0f, 0.0f,// ftl2
		0.5f,    0.5f,    0.5f,      1.0f, 1.0f, 0.0f,// ftr3
	// BACK										 0
	   -0.5f,   -0.5f,    -0.5f,     0.0f, 0.0f, 0.0f,// fbl4
		0.5f,   -0.5f,    -0.5f,     1.0f, 0.0f, 0.0f,// fbr5
	   -0.5f,    0.5f,    -0.5f,     0.0f, 1.0f, 0.0f,// ftl6
		0.5f,    0.5f,    -0.5f,     1.0f, 1.0f, 0.0f,// ftr7
	//LEFT						    			 0
	   -0.5f,   -0.5f,    -0.5f,     0.0f, 0.0f, 0.0f,// fbl8
	   -0.5f,   -0.5f,     0.5f,     1.0f, 0.0f, 0.0f,// fbr9
	   -0.5f,    0.5f,    -0.5f,     0.0f, 1.0f, 0.0f,// ftl10
	   -0.5f,    0.5f,     0.5f,     1.0f, 1.0f, 0.0f,// ftr11
	//RIGHT						    			 0
	    0.5f,   -0.5f,    -0.5f,     0.0f, 0.0f, 0.0f,// fbl12
	    0.5f,   -0.5f,     0.5f,     1.0f, 0.0f, 0.0f,// fbr13
	    0.5f,    0.5f,    -0.5f,     0.0f, 1.0f, 0.0f,// ftl14
	    0.5f,    0.5f,     0.5f,     1.0f, 1.0f, 0.0f,// ftr15
	//TOP						    			 0
	   -0.5f,    0.5f,     0.5f,     0.0f, 0.0f, 0.0f,// fbl16
		0.5f,    0.5f,     0.5f,     1.0f, 0.0f, 0.0f,// fbr17
	   -0.5f,    0.5f,    -0.5f,     0.0f, 1.0f, 0.0f,// ftl18
		0.5f,    0.5f,    -0.5f,     1.0f, 1.0f, 0.0f,// ftr19
	//BOTTOM									 0
	   -0.5f,    -0.5f,     0.5f,    0.0f, 0.0f, 0.0f,// fbl20
		0.5f,    -0.5f,     0.5f,    1.0f, 0.0f, 0.0f,// fbr21
	   -0.5f,    -0.5f,    -0.5f,    0.0f, 1.0f, 0.0f,// ftl22
		0.5f,    -0.5f,    -0.5f,    1.0f, 1.0f, 0.0f,// ftr23
};

// Indices for vertices order
GLuint indices[] =
{	
	// CUBE 1
	// ~~~~~~~~~~~~~~~~
	//front face
	0, 1, 2,
	1, 2, 3,
	//back face
	4, 5, 6,
	5, 6, 7,
	//left face
	8, 9, 10,
	9, 10, 11,
	//right face
	12, 13, 14,
	13, 14, 15,
	//top face
	16, 17, 18,
	17, 18, 19,
	//bottom face
	20, 21, 22,
	21, 22, 23,

	

};


// Render function without redundant bindings and uniform updates in the loop
void render_cube(Shaderer& shaderProgram, const GLuint* indices, GLsizei size, glm::vec3 translate) {
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, translate);
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "modelMatrix"), 1, GL_FALSE, glm::value_ptr(model));

	// Draw primitives
	glDrawElements(GL_TRIANGLES, size, GL_UNSIGNED_INT, 0);
}



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
	Shaderer cubeShader("shaders/shape.vs", "shaders/shape.fs");
	// Generates Vertex Array Object and binds it
	VAO VAO1;
	// Generates Vertex Buffer Object and links it to vertices
	VBO VBO1(vertices, sizeof(Vertex)*1000);
	// binds the VAO
	VAO1.Bind();
	// Generates Element Buffer Object and links it to indices
	EBO EBO1(indices, sizeof(indices));
	// Links VBO attributes such as coordinates and colors to VAO
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, position));
	VAO1.LinkAttrib(VBO1, 1, 2, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex,texCoord));
	VAO1.LinkAttrib(VBO1, 2, 1, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, texId));
	// Unbind all to prevent accidentally modifying them
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();
	// filepath name for the texture you are going to be using
	std::string texPath = "textures/grasstop.png";
	std::string texPathBrick = "textures/dirt.png";
	// Texture
	Texture tex0(texPath.c_str(), GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	Texture tex1(texPathBrick.c_str(), GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	tex0.texUnit(cubeShader, "tex0", 0);
	tex1.texUnit(cubeShader, "tex1", 1);


	// Get and print OpenGL version
	const GLubyte* version = glGetString(GL_VERSION);
	if (version == nullptr) {
		std::cerr << "Unable to retrieve OpenGL version" << std::endl;
		return -1;
	}

	std::cout << "OpenGL version: " << version << std::endl;

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


		glEnable(GL_DEPTH_TEST);
		// Whether to render wireframe or full textured
		if (wireframe) { glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); }
		else { glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); }
		// Tell OpenGL which Shader Program we want to use
		cubeShader.Activate();

		// Move uniform updates outside the loop
		camera.Matrix(45.0f, 0.1f, 180.0f, cubeShader, "camMatrix");
		tex1.Bind();
		tex0.Bind();
		VAO1.Bind();
		for (float j = 0.0f; j < 10; j++) {
			for (float i = 0.0f; i < 25; i++) {
				for (float z = 0.0f; z < 25; z++) {
					render_cube(cubeShader, indices, std::size(indices), glm::vec3(z, j, i));
				}
			}
		}
		tex0.Unbind();
		tex1.Unbind();
		VAO1.Unbind();
			

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
	cubeShader.Delete();
	font_shader.Delete();
	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}