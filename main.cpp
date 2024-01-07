#include "engine.h"

float res = 1.0f;

void input_callback(GLFWwindow* window, Camera& camera) {
	if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS) {
		wireframe = true;
	}
	if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS) {
		wireframe = false;
	}
	if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS) {
		res += 0.2f;
	}
	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {
		res -= 0.2f;
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
	//Shaderer objectShader("shaders/batched.vs", "shaders/batched.fs");
	Shaderer objectShader1("shaders/default.vs", "shaders/default.fs");
	




	GLuint tex0 = LoadTexture("textures/grey_sand.png");
	GLuint tex1 = LoadTexture("textures/dessert_sand.png");
	GLuint tex2 = LoadTexture("textures/dirt.png");
	// put textures in container array
	GLuint textureContainer[4] = { tex0,tex1,tex2 };
	// unifrom pointer for texture
	GLuint tex0Uni = glGetUniformLocation(objectShader1.ID, "tex0");


 	// Create camera object
	Camera camera(SCR_WIDTH, SCR_HEIGHT, glm::vec3(0.0f, 0.0f, 5.0f));

	// Create a transformation matrix with a 45-degree rotation on the x-axis and a translation of 10 units to the right
	glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(45.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(10.0f, 0.0f, 0.0f));
	glm::mat4 worldTransform = translationMatrix * rotationMatrix;


	//// imported obj model initialization
	Model_obj car("obj_models/car.obj");
	std::vector<Vertex> objVerts = car.obj_vert_generator();
	std::vector<GLuint> objInds = car.obj_indices();


	CubeMesh cubesmall(0.0f, 0.0f, 0.0f);

	glm::mat4 start_pos = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	

	//Mesh object0(plane.vertices, plane.indices,tex0);
	Mesh object2(cubesmall.vertices, cubesmall.indices, tex0);
	Mesh object1(objVerts, objInds, tex0);

	std::vector<Mesh> objects = { object1, object2 };

	SingleRender simpleRender(objectShader1,objects);
	simpleRender.use_object(1, start_pos);



	// Timing variables for FPS calculation
	double lastTime = glfwGetTime();
	int frameCount = 0;
	float fps = 0.0f;


	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		//set the window background color and clear the window buffer
		wnd.clear_buffer(color.darkGrey);

		// input handling
		input_callback(window, camera);
		//===============

	
		back_face_culling(true, true);

		simpleRender.wireframe_render(wireframe);
		simpleRender.activate();
		simpleRender.render(wireframe);
		simpleRender.deactivate();



		// update the camera
		camera.Matrix(45.0f, 0.1f, 10000.0f, objectShader1, "camMatrix");

		// Font Rendering
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glDisable(GL_DEPTH_TEST);
		font_shader.use();


		//draw text
		RenderText(font_shader, "Alone Engine - V 0.0.1", 25.0f, 25.0f, 1.0f, color.white, font_vao, font_vbo);
		RenderText(font_shader, std::to_string(get_fps(frameCount,lastTime)), 25.0f, SCR_HEIGHT - 50.0f, 1.0f, color.white, font_vao, font_vbo);
		RenderText(font_shader, std::to_string(simpleRender.max_vertices), 500.0f, SCR_HEIGHT - 50.0f, 1.0f, color.white, font_vao, font_vbo);
		// ==========================================================

		
		// Swap the back buffer with the front buffer
		wnd.swap_buffers(window);
		// Take care of all GLFW events and swap buffers
		wnd.events();
	}

	objectShader1.Delete();
	font_shader.Delete();
	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}