#include "engine.h"

static std::vector<Vertex> obj_vert_generator(std::string file_path) {
	std::ifstream objFile(file_path);
	std::string lineText;
	std::vector<Vertex> vertices;
	std::vector<ObjPositionCoordinates> posCoords;
	std::vector<ObjTextureCoordinates> texCoords;

	while (std::getline(objFile, lineText)) {
		std::stringstream objTextStream(lineText);
		GLfloat pos[3];
		GLfloat tc[2];

		// Extract the three float position values
		if (lineText[0] == 'v' && lineText[1] == ' ') {
			// Ignore the first token ("v")
			std::string token;
			objTextStream >> token;
			objTextStream >> pos[0] >> pos[1] >> pos[2];
			ObjPositionCoordinates vert;
			vert.position[0] = pos[0];
			vert.position[1] = pos[1];
			vert.position[2] = pos[2];
			posCoords.push_back(vert);
		}
		// Extract the two float texCoord values
		if (lineText[0] == 'v' && lineText[1] == 't') {
			// Ignore the first token ("vt")
			std::string token;
			objTextStream >> token;
			objTextStream >> tc[0] >> tc[1];
			ObjTextureCoordinates vert;
			vert.texCoord[0] = tc[0];  // Corrected line
			vert.texCoord[1] = tc[1];  // Corrected line
			texCoords.push_back(vert);
		}
	}


	// Move the file cursor back to the beginning of the file
	objFile.clear();
	objFile.seekg(0, std::ios::beg);


	while (std::getline(objFile, lineText)) {
		std::stringstream objTextStream(lineText);

		if (lineText.substr(0, 2) == "f ") {
			// Extract face indices
			std::string token;
			objTextStream >> token; // Ignore 'f'

			std::vector<int> positionIndices;
			std::vector<int> textureIndices;

			while (objTextStream >> token) {
				std::istringstream indexStream(token);
				std::string positionIndexStr, textureIndexStr;

				// Extract position index and texture coordinate index
				std::getline(indexStream, positionIndexStr, '/');
				std::getline(indexStream, textureIndexStr, '/');

				// Convert strings to integers
				int pIndex = std::stoi(positionIndexStr);
				int tIndex = std::stoi(textureIndexStr);

			

				Vertex vert;
				vert.position[0] = posCoords[pIndex - 1].position[0];
				vert.position[1] = posCoords[pIndex - 1].position[1];
				vert.position[2] = posCoords[pIndex - 1].position[2];

				vert.texCoord[0] = texCoords[tIndex - 1].texCoord[0];
				vert.texCoord[1] = texCoords[tIndex - 1].texCoord[1];
				vert.texId = 1;
				vertices.push_back(vert);


				// Store the indices if needed for further processing
				positionIndices.push_back(pIndex);
				textureIndices.push_back(tIndex);
			}
		}
	}

	return vertices;
}



static std::unique_ptr<GLuint[]> obj_indices(GLuint num_verts) {
	std::unique_ptr<GLuint[]> indicesPLANE(new GLuint[num_verts]);


	for (GLuint i = 0; i < num_verts; ++i) {
		indicesPLANE[i] = i;
	}

	return indicesPLANE;
}




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


	// 3 by 3 plane
	const GLfloat cols_rows = 20;
	const GLfloat max_verts = cols_rows*cols_rows;
	const GLfloat max_indices = ((cols_rows -1)*(cols_rows-1)) * 6;
	const GLfloat max_quads = ((cols_rows - 1) * (cols_rows - 1));

	// OBJ
	std::vector<Vertex> objModel = obj_vert_generator("obj_models/car.obj");
	int size_of_model = objModel.size();

	// PLANE
	std::vector<Vertex> plane = createPlane(0.0f, 0.0f, 0.0f, 100.0f, 100.0f, cols_rows, cols_rows, 0.05f, 4.0f);

	// Use smart pointer for verts
	std::unique_ptr<std::vector<Vertex>> verts = std::make_unique<std::vector<Vertex>>(size_of_model);

	// Generate indices for the plane and chunk
	std::unique_ptr<GLuint[]> indicesPLANE = generatePlaneIndices(cols_rows, cols_rows);
	std::unique_ptr<GLuint[]> indicesOBJ = obj_indices(size_of_model);
	
	//copy obj verts to verts
	std::copy(objModel.begin(), objModel.end(), verts->begin());


	// Generates Shader object
	Shaderer objectShader("shaders/shape.vs", "shaders/shape.fs");
	// Generates Vertex Buffer Object and links it to vertices
	VBO VBO1(size_of_model);
	// Generates Vertex Array Object and binds it
	VAO VAO1;
	// binds the VAO
	VAO1.Bind();
	// Links VBO attributes such as coordinates and colors to VAO
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, position));
	VAO1.LinkAttrib(VBO1, 1, 2, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex,texCoord));
	VAO1.LinkAttrib(VBO1, 2, 1, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, texId));





	// Generates Element Buffer Object and links it to indices
	EBO EBO1(indicesOBJ.get(), size_of_model);

	GLuint tex0 = LoadTexture("textures/grey_sand.png");
	GLuint tex1 = LoadTexture("textures/dirasdt.png");
	GLuint tex2 = LoadTexture("textures/dirt.png");
	// put textures in container array
	GLuint textureContainer[4] = { tex0,tex1,tex2 };


 	// Create camera object
	Camera camera(SCR_WIDTH, SCR_HEIGHT, glm::vec3(0.0f, 0.0f, 5.0f));

	// Timing variables for FPS calculation
	double lastTime = glfwGetTime();
	int frameCount = 0;
	float fps = 0.0f;

	std::cout << size_of_model;

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


		move_cube(window, *verts, size_of_model, xpos);
		// Tell OpenGL which Shader Program we want to use
		objectShader.Activate();
		glEnable(GL_DEPTH_TEST);
		VBO1.dynamic_update(*verts);
		VAO1.Bind();
		// bind the textures to the texture units in the vbo/shader
		texture_units(objectShader.ID, textureContainer, "textureContainer");
		glDrawElements(GL_TRIANGLES, size_of_model, GL_UNSIGNED_INT, 0);
		VBO1.Unbind();
		VAO1.Unbind();
			


		// update the camera
		camera.Matrix(45.0f, 0.1f, 10000.0f, objectShader, "camMatrix");


		// Font Rendering
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glDisable(GL_DEPTH_TEST);
		font_shader.use();


		//draw text
		RenderText(font_shader, "Alone Engine - V 0.0.1", 25.0f, 25.0f, 1.0f, color.white, font_vao, font_vbo);
		RenderText(font_shader, std::to_string(get_fps(frameCount,lastTime)), 25.0f, SCR_HEIGHT - 50.0f, 1.0f, color.white, font_vao, font_vbo);
		RenderText(font_shader, std::to_string(size_of_model), 500.0f, SCR_HEIGHT - 50.0f, 1.0f, color.white, font_vao, font_vbo);
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