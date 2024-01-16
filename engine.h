#pragma once
// standard libs
#include <iostream>
#include <array>
#include <vector>
#include <map>
#include <cmath>
#include <iomanip>
#include <fstream>

//openGL libs
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <glm/gtc/noise.hpp>

//Texture libs
#include <stb/stb_image.h>

//Font libs
#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H
#include FT_OUTLINE_H
#include FT_TRIGONOMETRY_H

// internal engine files
#include "mathUtils.h"
#include "debugUtils.h"
#include "Vertex.h"
#include "Colors.h"
#include "Window.h"
#include"shaderClass.h"
#include "FreeTypeFont.h"
#include "Renderer.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"
#include"Texture.h"
#include"Camera.h"
#include "aloneGUI.h"


#include "Model_obj.h"
#include "Mesh.h"



//program run
#include "main.h"