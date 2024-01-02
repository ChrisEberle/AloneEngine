static GLuint LoadTexture(const std::string& path) {
	int w, h, bits;

	stbi_set_flip_vertically_on_load(1);
	auto* pixels = stbi_load(path.c_str(), &w, &h, &bits, STBI_rgb);

	GLuint textureID;

	glCreateTextures(GL_TEXTURE_2D, 1, &textureID);
	// Binds the texture to a Texture Unit directly
	glBindTexture(GL_TEXTURE_2D, textureID);
	// Configures the type of algorithm that is used to make the image smaller or bigger
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Set LOD bias to -0.5 (adjust this value as needed)
	glTextureParameterf(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, -0.5f);
	// Configures the way the texture repeats (if it does at all)
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Assigns the image to the OpenGL Texture object
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);
	// Generates MipMaps
	glGenerateTextureMipmap(textureID);
	// Unbind the texture (important to avoid issues with other texture operations)
	glBindTexture(textureID, 0);

	stbi_image_free(pixels);

	return textureID;
}

static void load_texture_package() {

}


static void texture_units(GLuint& id,GLuint* texture_array, std::string path ) {
	// bind the textures to the texture units in the vbo/shader
	auto loc = glGetUniformLocation(id, path.c_str());
	int samplers[4] = { 0,1,2,3 };
	glUniform1iv(loc, 4, samplers);
	glBindTextureUnit(0, texture_array[0]);
	glBindTextureUnit(1, texture_array[1]);
	glBindTextureUnit(2, texture_array[2]);
	glBindTextureUnit(3, texture_array[3]);
}