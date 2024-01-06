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
	Shaderer objectShader("shaders/shape.vs", "shaders/shape.fs");

	Model_obj car("obj_models/car.obj");
	std::vector<Vertex> objModel = car.obj_vert_generator();
	std::vector<GLuint> ind = car.obj_indices();
	BatchRenderer bm(10000000);
	bm.initializeMesh();

	PlaneMesh plane(0.0f, 0.0f, 0.0f, 100.0f, 100.0f, 10.0f, 10.0f, 0.0f, 0.0f, 20.0f, 20.0f);
	CubeMesh cube1(0.0f, 0.0f, 0.0f);
	CubeMesh cube2(2.0f, 0.0f, 0.0f);
	//bm.add_to_mesh(plane.vertices, plane.indices);
	//bm.add_to_mesh(cube2.vertices, cube2.indices);
	bm.add_to_mesh(objModel, ind);

	GLuint tex0 = LoadTexture("textures/grey_sand.png");
	GLuint tex1 = LoadTexture("textures/dirt.png");
	GLuint tex2 = LoadTexture("textures/dirt.png");
	// put textures in container array
	GLuint textureContainer[4] = { tex0,tex1,tex2 };

	GLuint tex0Uni = glGetUniformLocation(objectShader.ID, "tex0");

 	// Create camera object
	Camera camera(SCR_WIDTH, SCR_HEIGHT, glm::vec3(0.0f, 0.0f, 5.0f));

	// Timing variables for FPS calculation
	double lastTime = glfwGetTime();
	int frameCount = 0;
	float fps = 0.0f;
	//terrain.add_to_mesh(objectShader, cube1.vertices, cube1.indices);
	bm.update();
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

		back_face_culling(true, true);
		bm.render(objectShader,tex0);

		//bm.render(objectShader, tex0);
		// update the camera
		camera.Matrix(45.0f, 0.1f, 10000.0f, objectShader, "camMatrix");

		// Font Rendering
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glDisable(GL_DEPTH_TEST);
		font_shader.use();


		//draw text
		RenderText(font_shader, "Alone Engine - V 0.0.1", 25.0f, 25.0f, 1.0f, color.white, font_vao, font_vbo);
		RenderText(font_shader, std::to_string(get_fps(frameCount,lastTime)), 25.0f, SCR_HEIGHT - 50.0f, 1.0f, color.white, font_vao, font_vbo);
		RenderText(font_shader, std::to_string(bm.getNumIndices()), 500.0f, SCR_HEIGHT - 50.0f, 1.0f, color.white, font_vao, font_vbo);
		// ==========================================================

		
		// Swap the back buffer with the front buffer
		wnd.swap_buffers(window);
		// Take care of all GLFW events and swap buffers
		wnd.events();
	}

	objectShader.Delete();
	font_shader.Delete();
	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}