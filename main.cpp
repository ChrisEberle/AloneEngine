#include "engine.h"

float res = 1.0f;

bool texChange = false;

void input_callback(GLFWwindow* window, Camera& camera) {
	if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS) {
		wireframe = true;
	}
	if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS) {
		wireframe = false;
	}
	if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS) {
		texChange = true;
	}
	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {
		texChange = false;
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
	Shaderer objectShader("shaders/batched.vs", "shaders/batched.fs");
	Shaderer objectShader1("shaders/default.vs", "shaders/default.fs");
	Shaderer lightShader("shaders/light_cube.vs", "shaders/light_cube.fs");


	GLuint tex0 = LoadTexture("textures/grey_sand.png");
	GLuint tex1 = LoadTexture("textures/dessert_sand.png");
	GLuint tex2 = LoadTexture("textures/dirt.png");
	// put textures in container array
	GLuint textureContainer[4] = { tex0,tex1,tex2 };
	// unifrom pointer for texture
	GLuint tex0Uni = glGetUniformLocation(objectShader1.ID, "tex0");



 	// Create camera object
	Camera camera(SCR_WIDTH, SCR_HEIGHT, glm::vec3(0.0f, 0.0f, 5.0f));

	glm::vec3 posLight(0.0f, 0.0f, 0.0f);

	// imported obj model initialization
	Model_obj car("obj_models/carUV.obj");

	CubeMesh cube0(1.0f, 0.0f, 0.0f);
	CubeMesh cube1(3.0f, 0.0f, 0.0f);
	CubeMesh cube2(-3.0f, 0.0f, 0.0f);
	CubeMesh cube3(posLight.x, posLight.y, posLight.z);
	PlaneMesh plane(0.0f, 0.0f, 0.0f, 100.0f, 100.0f, 100, 100, 0.1f, 4.0f, 20.0f, 20.0f);
	Mesh object0(cube0.position_vertices, cube0.texCoord_vertices, cube0.normal_vertices, cube0.indices, tex0);

	Mesh planeOBJ(plane.position_vertices, plane.texture_coordinates, plane.normals, plane.indices, tex0);

	Mesh cubeLight(cube3.position_vertices, cube3.texCoord_vertices, cube3.normal_vertices, cube3.indices, tex0);

	std::vector<Mesh> objects = { cubeLight };
	std::vector<Mesh> objs = { planeOBJ};

	BatchRenderer batch1(objectShader,tex1, objs, 3100000, 3100000);
	batch1.initializeMeshObject();

	BatchRenderer batch(lightShader, tex0 ,objects, 3100000, 3100000);
	batch.initializeMeshCubeLight();

	

	// Timing variables for FPS calculation
	double lastTime = glfwGetTime();
	int frameCount = 0;
	float fps = 0.0f;

	int counter = 0;

	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		//set the window background color and clear the window buffer
		wnd.clear_buffer(color.darkGrey);

		// input handling
		input_callback(window, camera);

		if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
			posLight.y -= 0.2f;
		}
		if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {
			posLight.y += 0.2f;
		}

		if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS) {
			posLight.x -= 0.2f;
		}
		if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS) {
			posLight.x += 0.2f;
		}

		if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS) {
			posLight.z -= 0.2f;
		}
		if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS) {
			posLight.z += 0.2f;
		}

		//===============
	
		
		back_face_culling(true, true);
		batch.wireframe_render(wireframe);
		batch1.render(camera, posLight);
		batch.render(camera, posLight);
	


		//glUseProgram(0);

		// Font Rendering
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glDisable(GL_DEPTH_TEST);
		font_shader.use();


		//draw text
		RenderText(font_shader, "Alone Engine - V 0.0.1", 25.0f, 25.0f, 1.0f, color.white, font_vao, font_vbo);
		RenderText(font_shader, std::to_string(get_fps(frameCount,lastTime)), 25.0f, SCR_HEIGHT - 50.0f, 1.0f, color.white, font_vao, font_vbo);
		RenderText(font_shader, std::to_string(batch.max_vertices), 500.0f, SCR_HEIGHT - 50.0f, 1.0f, color.white, font_vao, font_vbo);
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