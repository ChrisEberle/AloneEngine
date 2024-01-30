#include "engine.h"

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


	// Generates Shader object
	//Shader lightShader("shaders/light_cube.vs", "shaders/light_cube.fs");
	Shader instanceShader("shaders/instanced.vs", "shaders/instanced.fs");


	// Take care of all the light related things
	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);

 	// Create camera object
	Camera camera(SCR_WIDTH, SCR_HEIGHT, glm::vec3(0.0f, 0.0f, 5.0f));

	// Holds all transformations for the asteroids
	std::vector <glm::mat4> instanceMatrix;

	unsigned int number = 15;
	for (unsigned int i = 0; i < number; i++)
	{
		for (unsigned int j = 0; j < number; j++)
		{
			// Holds transformations before multiplying them
			glm::vec3 trans;
			glm::quat rot;
			glm::vec3 scale;

			// Generates a translation near a circle of radius "radius"
			trans = glm::vec3(0.0f + i*3.5f, 0.0f, 0.0f + j*3.5f);
			// Generates random rotations
			rot = glm::quat(0.0f, 0.0f, 0.0f, 0.0f);
			// Generates random scales
			scale = 0.1f * glm::vec3(5.0f, 5.0f, 5.0f);



			// Push matrix transformation
			instanceMatrix.push_back(glm::translate(trans) * glm::mat4_cast(rot) * glm::scale(scale));
		}
	}


	


	std::string path = "obj_models/statue0.obj";
	Model cube0(path, number*number, instanceMatrix);
	cube0.loadMesh();
	instanceShader.Activate();
	glUniform4f(glGetUniformLocation(instanceShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(instanceShader.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);

	// Holds all transformations for the asteroids
	
	// Timing variables for FPS calculation
	double lastTime = glfwGetTime();
	int frameCount = 0;
	float fps = 0.0f;
	float counter = 1;
	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		//set the window background color and clear the window buffer
		wnd.clear_buffer(color.black);
		counter++;

		
		// input handling
		input_callback(window, camera);

		if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS) {
			wireframe_state(true, instanceShader);
			
		}
		if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS) {
			wireframe_state(false, instanceShader);
		}

		//===============
		// Enables the Depth Buffer
		glEnable(GL_DEPTH_TEST);
	
		
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		cube0.Draw(instanceShader, camera);

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glDisable(GL_DEPTH_TEST);
		font_shader.Activate();
		RenderText(font_shader, "Alone Engine - V 0.0.1", 25.0f, 25.0f, 1.0f, color.white, font_vao, font_vbo);
		RenderText(font_shader, std::to_string(get_fps(frameCount,lastTime)), 25.0f, SCR_HEIGHT - 50.0f, 1.0f, color.white, font_vao, font_vbo);
		RenderText(font_shader, "P COUNT: ", 600.0f, SCR_HEIGHT - 50.0f, 1.0f, color.white, font_vao, font_vbo);
		RenderText(font_shader, std::to_string(cube0.vertices.size()*number), 950.0f, SCR_HEIGHT - 50.0f, 1.0f, color.white, font_vao, font_vbo);
		//// ==========================================================
		

		// Swap the back buffer with the front buffer
		wnd.swap_buffers(window);
		// Take care of all GLFW events and swap buffers
		wnd.events();
	}
	//lightShader.Delete();
	font_shader.Delete();
	instanceShader.Delete();
	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}