#pragma once


/// Holds all state information relevant to a character as loaded using FreeType
struct Character {
    unsigned int TextureID; // ID handle of the glyph texture
    glm::ivec2   Size;      // Size of glyph
    glm::ivec2   Bearing;   // Offset from baseline to left/top of glyph
    unsigned int Advance;   // Horizontal offset to advance to next glyph
};

// custom functions for implementing freetype fonts on a glfw window using glad shaders
int ft_init(FT_Library& ft, FT_Face& face, Shader& shader, const char* filepath, float SCR_WIDTH, float SCR_HEIGHT);
void init_renderer(unsigned int& font_vao, unsigned int& font_vbo);
void RenderText(Shader& shader, std::string text, float x, float y, float scale, const glm::vec4 color, unsigned int VAO, unsigned int VBO);