#pragma once
// standard libs
#include <iostream>
#include <vector>
#include <map>
#include <cmath>

//openGL libs
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

//Texture libs
#include <stb/stb_image.h>

//Font libs
#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H
#include FT_OUTLINE_H
#include FT_TRIGONOMETRY_H

// internal engine files
#include "Colors.h"
#include "shaders/shader.h"
#include "FreeTypeFont.h"
#include "Window.h"
#include"Texture.h"
#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"
#include"Camera.h"

//program run
#include "main.h"