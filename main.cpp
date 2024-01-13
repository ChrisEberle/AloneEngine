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

	float lightIntense = 1.0f;

	// Generates Shader object
	Shader objectShader("shaders/batched.vs", "shaders/batched.fs");
	Shader objectShader1("shaders/default.vs", "shaders/default.fs");
	Shader lightShader("shaders/light_cube.vs", "shaders/light_cube.fs");


	GLuint tex0 = LoadTexture("textures/grey_sand.png");
	GLuint tex1 = LoadTexture("textures/dessert_sand.png");
	GLuint tex2 = LoadTexture("textures/dirt.png");
	// put textures in container array
	GLuint textureContainer[4] = { tex0,tex1,tex2 };
	// unifrom pointer for texture
	GLuint tex0Uni = glGetUniformLocation(objectShader1.ID, "tex0");


	//Material(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, GLfloat shine, GLuint & texture) : ambient(ambient), diffuse(diffuse), specular(specular), shine(shine), texture(texture) {
	Material mat0(glm::vec3(1.0f,0.5f,0.31f), glm::vec3(1.0f, 0.5f, 0.31f), glm::vec3(0.5f, 0.5f, 0.5f), 302.0f, tex0);
	Material mat1(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.5f, 0.5f, 0.5f), 302.0f, tex0);

 	// Create camera object
	Camera camera(SCR_WIDTH, SCR_HEIGHT, glm::vec3(0.0f, 0.0f, 5.0f));



	// OBJECTS
	ModelOBJ  car("obj_models/AK47.obj");
	Mesh model0(mat1);
	model0.modelObj(car);
	Mesh plane0(mat0);
	plane0.createPlane(-50.0f, -5.0f, 50.0f, 100.0f, 100.0f, 1500, 1500, 0.1f, 60.0f, 20.0f, 20.0f);
	Mesh cubeOBJ(mat0);
	cubeOBJ.createCube(48.0f, 2.0f, -48.0f);



	// LIGHTS
	Mesh cubeLight0(mat0);
	cubeLight0.createCube(-5.0f, 0.0f, 0.0f);
	Mesh cubeLight1(mat0);
	cubeLight1.createCube(5.0f, 0.0f, 0.0f);
	Mesh cubeLight2(mat0);
	cubeLight2.createCube(0.0f, 10.0f, 0.0f);
	std::vector<glm::vec3> lightPositions;
	lightPositions.push_back(cubeLight0.position);
	lightPositions.push_back(cubeLight1.position);
	lightPositions.push_back(cubeLight2.position);



	// Mesh vectors
	std::vector<Mesh> lightObjects = { cubeLight0,cubeLight1,cubeLight2 };
	std::vector<Mesh> objectsTerrain = { plane0 };
	std::vector<Mesh> objectsBuildings = { model0};



	//house
	MatBatchRenderer batchBuildings(objectShader, objectsBuildings, mat1,31000000, 31000000);
	batchBuildings.initializeMeshObject();
	// terrain
	MatBatchRenderer batchTerrain(objectShader, objectsTerrain, mat0, 31000000, 31000000);
	batchTerrain.initializeMeshObject();
	// light
	MatBatchRenderer batchLight(lightShader, lightObjects,mat0, 1000, 1000);
	batchLight.initializeMeshCubeLight();
	

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
	


		// Object Rendering
		back_face_culling(true);
		batchTerrain.wireframe_render(wireframe);
		batchTerrain.render(camera, lightPositions);
		batchBuildings.render(camera, lightPositions);
		batchLight.renderLight(camera, glm::vec3(0.0f,0.0f,0.0f));

		// Font Rendering
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glDisable(GL_DEPTH_TEST);
		font_shader.Activate();


		//draw text
		RenderText(font_shader, "Alone Engine - V 0.0.1", 25.0f, 25.0f, 1.0f, color.white, font_vao, font_vbo);
		RenderText(font_shader, std::to_string(get_fps(frameCount,lastTime)), 25.0f, SCR_HEIGHT - 50.0f, 1.0f, color.white, font_vao, font_vbo);
		RenderText(font_shader, std::to_string(batchBuildings.max_vertices), 500.0f, SCR_HEIGHT - 50.0f, 1.0f, color.white, font_vao, font_vbo);
		// ==========================================================

		
		// Swap the back buffer with the front buffer
		wnd.swap_buffers(window);
		// Take care of all GLFW events and swap buffers
		wnd.events();
	}
	lightShader.Delete();
	objectShader.Delete();
	objectShader1.Delete();
	font_shader.Delete();
	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}