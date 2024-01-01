#include "engine.h"

bool wireframe = false;

GLfloat move_cube;


static std::array<Vertex, 24> createCube(GLfloat x, GLfloat texID) {
	// Define the eight vertices of a cube
	std::array<Vertex, 24> vertices = { {
		//FRONT
		{ -0.5f + x,   -0.5f,    0.5f,      0.0f, 0.0f, texID }, // v0
		{  0.5f + x,   -0.5f,    0.5f,      1.0f, 0.0f, texID }, // v1
		{ -0.5f + x,    0.5f,    0.5f,      0.0f, 1.0f, texID }, // v2
		{ 0.5f  + x,    0.5f,    0.5f,      1.0f, 1.0f,  texID }, // v3
		//BACK  
		{ -0.5f + x,   -0.5f,    -0.5f,     0.0f, 0.0f, texID }, // v4
		{ 0.5f  + x,   -0.5f,    -0.5f,     1.0f, 0.0f,  texID }, // v5
		{ -0.5f + x,    0.5f,    -0.5f,     0.0f, 1.0f, texID }, // v6
		{ 0.5f  + x,    0.5f,    -0.5f,     1.0f, 1.0f,  texID },  // v7
		//LEFT  
		{ -0.5f + x,   -0.5f,    -0.5f,     0.0f, 0.0f, texID }, // v8
		{ -0.5f + x,   -0.5f,     0.5f,     1.0f, 0.0f, texID }, // v9
		{ -0.5f + x,    0.5f,    -0.5f,     0.0f, 1.0f, texID }, // v10
		{ -0.5f + x,    0.5f,     0.5f,     1.0f, 1.0f, texID }, // v11
		//RIGHT 
		{ 0.5f  + x,   -0.5f,    -0.5f,     0.0f, 0.0f,  texID }, // v12
		{ 0.5f  + x,   -0.5f,     0.5f,     1.0f, 0.0f,  texID }, // v13
		{ 0.5f  + x,    0.5f,    -0.5f,     0.0f, 1.0f,  texID }, // v14
		{ 0.5f  + x,    0.5f,     0.5f,     1.0f, 1.0f,  texID },  // v15
		//TOP   
		{ -0.5f + x,    0.5f,     0.5f,     0.0f, 0.0f, texID }, // v16
		{ 0.5f  + x,    0.5f,     0.5f,     1.0f, 0.0f,  texID }, // v17
		{ -0.5f + x,    0.5f,    -0.5f,     0.0f, 1.0f, texID }, // v18
		{ 0.5f  + x,    0.5f,    -0.5f,     1.0f, 1.0f,  texID }, // v19
		//BOTTOM
		{ -0.5f + x,    -0.5f,     0.5f,    0.0f, 0.0f, texID }, // v20
		{ 0.5f  + x,    -0.5f,     0.5f,    1.0f, 0.0f,  texID }, // v21
		{ -0.5f + x,    -0.5f,    -0.5f,    0.0f, 1.0f, texID }, // v22
		{ 0.5f  + x,    -0.5f,    -0.5f,    1.0f, 1.0f,  texID }  // v23
	} };

	return vertices;
}


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
	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) {
		move_cube += 0.01;
	}
	if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS) {
		move_cube -= 0.01;
	}
	// Handles camera inputs
	camera.Inputs(window);
}




static GLuint LoadTexture(const std::string& path) {
	int w, h, bits;
	
	stbi_set_flip_vertically_on_load(1);
	auto* pixels = stbi_load(path.c_str(), &w, &h, &bits, STBI_rgb);
	GLuint textureID;

	glCreateTextures(GL_TEXTURE_2D, 1, &textureID);
	// Binds the texture to a Texture Unit directly
	glBindTexture(GL_TEXTURE_2D, textureID);

	// Configures the type of algorithm that is used to make the image smaller or bigger
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Configures the way the texture repeats (if it does at all)
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Assigns the image to the OpenGL Texture object
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);
	// Generates MipMaps
   	glGenerateTextureMipmap(textureID);
	// Unbind the texture (important to avoid issues with other texture operations)
	glBindTexture(textureID, 0);

	stbi_image_free(pixels);

	return textureID;

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


	// Generates Shader object
	Shaderer cubeShader("shaders/shape.vs", "shaders/shape.fs");
	// Generates Vertex Array Object and binds it
	VAO VAO1;
	// Generates Vertex Buffer Object and links it to vertices
	VBO VBO1(sizeof(Vertex) * 1000);
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

	GLfloat tex0 = LoadTexture("textures/dirt.png");
	GLfloat tex1 = LoadTexture("textures/grasstop.png");
    GLfloat tex2 = LoadTexture("textures/brick.png");

 	// Creates camera object
	Camera camera(SCR_WIDTH, SCR_HEIGHT, glm::vec3(0.0f, 0.0f, 2.0f));
	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		//set the window background color and clear the buffer
		wnd.clear_buffer(color.skyBlue);

		// input handling
		// ==========================================================A
		input_callback(window, camera);

		auto c0 = createCube(move_cube,3);

		Vertex verts[24];
		memcpy(verts, c0.data(), c0.size() * sizeof(Vertex));

		VBO1.Bind();
		//VBO1.dynamic_update(verts);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(verts), verts);

		glEnable(GL_DEPTH_TEST);
		// Whether to render wireframe or full textured
		if (wireframe) { glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); }
		else { glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); }
		// Tell OpenGL which Shader Program we want to use
		cubeShader.Activate();

		auto loc = glGetUniformLocation(cubeShader.ID, "textureContainer");
		int samplers[4] = { 0,1,2,3};
		glUniform1iv(loc, 4, samplers);
		
		glBindTextureUnit(0, tex0);
		glBindTextureUnit(1, tex1);
		glBindTextureUnit(2, tex2);
		glBindTextureUnit(3, tex0);

		// Move uniform updates outside the loop
		camera.Matrix(45.0f, 0.1f, 180.0f, cubeShader, "camMatrix");
		VAO1.Bind();
	    render_cube(cubeShader, indices, std::size(indices), glm::vec3(0.0f,0.0f,0.0f));

		VBO1.Unbind();
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
	cubeShader.Delete();
	font_shader.Delete();
	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}