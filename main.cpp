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

	float lightIntense = 1.0f;

	// Generates Shader object
	Shader objectShader("shaders/batched.vs", "shaders/batched.fs");
	Shader objectShader1("shaders/default.vs", "shaders/default.fs");
	Shader lightShader("shaders/light_cube.vs", "shaders/light_cube.fs");
	Shader guiShader("shaders/instancedUI.vs", "shaders/instancedUI.fs");

	GLuint tex0 = LoadTexture("textures/grey_sand.png");
	GLuint tex1 = LoadTexture("textures/dessert_sand.png");
	GLuint tex2 = LoadTexture("textures/dirt.png");
	GLuint tex3 = LoadTexture("textures/ak_low.png");
	GLuint tex4 = LoadTexture("textures/statue.png");
	// put textures in container array
	GLuint textureContainer[4] = { tex0,tex1,tex2 };
	// unifrom pointer for texture
	GLuint tex0Uni = glGetUniformLocation(objectShader1.ID, "tex0");



 	// Create camera object
	Camera camera(SCR_WIDTH, SCR_HEIGHT, glm::vec3(0.0f, 0.0f, 5.0f));



	// MATERIALS
	//Material(glm::vec3 color, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, GLfloat shine, GLuint & texture) : ambient(ambient), diffuse(diffuse), specular(specular), shine(shine), texture(texture) {
	Material mat0(glm::vec3(1.0f, 0.5f, 0.5f), glm::vec3(1.0f, 0.5f, 0.5f), glm::vec3(1.0f, 0.5f, 0.5f), glm::vec3(1.0f, 0.5f, 0.5f), 320.0f, tex0);
	Material mat1(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), 320.0f, tex2);



	// OBJECTS
	ModelOBJ  car("obj_models/statue2.obj");
	Mesh model0(glm::vec3(0.0f,0.0f,0.0f), mat1);
	model0.modelObj(car);
	Mesh plane0(glm::vec3(-50.0f, -5.0f, 50.0f), mat0);
	plane0.createPlane( 100.0f, 100.0f, 1000, 1000, 0.1f, 60.0f, 20.0f, 20.0f);
	Mesh cubeOBJ(glm::vec3(48.0f, 2.0f, -48.0f), mat0);
	cubeOBJ.createCube();



	// LIGHTS
	glm::vec3 diffuseColor = glm::vec3(1.0f, 1.0f, 1.0f) * glm::vec3(0.5f);
	glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f);
	glm::vec3 specularColor(1.0f, 1.0f, 1.0f);

	Material lightMat0(glm::vec3(1.0f, 0.0f, 0.0f), ambientColor, diffuseColor, specularColor, 32.0f, tex0);
	Material lightMat1(glm::vec3(1.0f, 1.0f, 1.0f), ambientColor, diffuseColor, specularColor, 32.0f, tex0);

	Mesh pointLight0(glm::vec3(1.0f, 8.0f, 7.0f), lightMat1, 2);
	pointLight0.createCube();
	Mesh spotLight0(glm::vec3(0.0f, 12.0f, 0.0f), lightMat1, 1);
	spotLight0.createCube();
	Mesh dirLight0(glm::vec3(120.0f, 120.0f, 120.0f), lightMat1, 0);
	dirLight0.createCube();
	dirLight0.direction = glm::vec3(1.0f, -1.0f, 1.0f);



	std::vector<Mesh> lightsVec;
	lightsVec.push_back(pointLight0);
	lightsVec.push_back(spotLight0);
	lightsVec.push_back(dirLight0);

	// Mesh vectors
	std::vector<Mesh> objectsTerrain = { plane0 };
	std::vector<Mesh> objectsBuildings = { model0};



	//house
	MatBatchRenderer batchBuildings(objectShader, objectsBuildings, mat1,31000000, 31000000);
	batchBuildings.initializeMeshObject();
	// terrain
	MatBatchRenderer batchTerrain(objectShader, objectsTerrain, mat0, 31000000, 31000000);
	batchTerrain.initializeMeshObject();
	// light
	MatBatchRenderer batchLight(lightShader, lightsVec,mat0, 1000, 1000);
	batchLight.initializeMeshCubeLight();


	guiMesh panel(glm::vec3(0.0f, 0.0f, 0.0f));

	InstancedRenderer ui(guiShader, panel, tex2);


	std::vector<glm::mat4> modelMatrices;

	// Assuming you want to render three GUI panels in a row
	for (int i = 0; i < 3; ++i) {
		glm::mat4 model = glm::mat4(1.0f);  // Initialize with an identity matrix
		model = glm::translate(model, glm::vec3(i + 1.0f, 0.0f, 0.0f));  // Translate each panel horizontally
		modelMatrices.push_back(model);
	}

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

		if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS) {
			if (lightsVec[0].lightIntensity > 0.0f) {
				lightsVec[0].lightIntensity -= 10.5f;
			}
		}
		if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) {
				lightsVec[0].lightIntensity += 10.5f;
			
		}



		if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS) {
			if (lightsVec[1].lightIntensity > 0.0f) {
				lightsVec[1].lightIntensity -= 0.5f;
			}
		}
		if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {
			if (lightsVec[1].lightIntensity < 40.0f) {
				lightsVec[1].lightIntensity += 0.5f;
			}
		}



		if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS) {
			if (lightsVec[2].lightIntensity > 0.0f) {
				lightsVec[2].lightIntensity -= 0.5f;
			}
		}
		if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) {
			if (lightsVec[2].lightIntensity < 40.0f) {
				lightsVec[2].lightIntensity += 0.5f;
			}
		}
		if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS) {
			
			lightsVec[0].material.objectColor = glm::vec3(1.0f, 0.0f, 0.0f);
			batchLight.objects[0].material.objectColor = glm::vec3(1.0f, 0.0f, 0.0f);
		}



		// Object Rendering
		//back_face_culling(true);
	//batchTerrain.wireframe_render(wireframe);
	//batchTerrain.render(camera, lightsVec);
	//batchBuildings.render(camera, lightsVec);
	//batchLight.renderLight(camera);


		ui.render(modelMatrices);

	//// Font Rendering
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	//glDisable(GL_DEPTH_TEST);
	//font_shader.Activate();
	////draw text
	//RenderText(font_shader, "Alone Engine - V 0.0.1", 25.0f, 25.0f, 1.0f, color.white, font_vao, font_vbo);
	//RenderText(font_shader, std::to_string(get_fps(frameCount,lastTime)), 25.0f, SCR_HEIGHT - 50.0f, 1.0f, color.white, font_vao, font_vbo);
	//RenderText(font_shader, std::to_string(batchBuildings.max_vertices + batchTerrain.max_vertices + batchLight.max_vertices), 500.0f, SCR_HEIGHT - 50.0f, 1.0f, color.white, font_vao, font_vbo);
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