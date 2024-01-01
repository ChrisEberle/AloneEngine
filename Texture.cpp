#include"engine.h"

Texture::Texture(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType)
{
    // Assigns the type of the texture to the texture object
    type = texType;

    // Stores the width, height, and the number of color channels of the image
    int widthImg, heightImg, numColCh;
    // Flips the image so it appears right side up
    stbi_set_flip_vertically_on_load(true);
    // Reads the image from a file and stores it in bytes
    unsigned char* bytes = stbi_load(image, &widthImg, &heightImg, &numColCh, 0);

    // Generates an OpenGL texture object
    glGenTextures(1, &ID);

    // Binds the texture to a Texture Unit directly
    glBindTextureUnit(slot - GL_TEXTURE0, ID);

    // Configures the type of algorithm that is used to make the image smaller or bigger
    glTextureParameteri(ID, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
    glTextureParameteri(ID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // Configures the way the texture repeats (if it does at all)
    glTextureParameteri(ID, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTextureParameteri(ID, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // Assigns the image to the OpenGL Texture object
    glTextureStorage2D(ID, 1, GL_RGBA8, widthImg, heightImg);
    glTextureSubImage2D(ID, 0, 0, 0, widthImg, heightImg, format, pixelType, bytes);
    // Generates MipMaps
    glGenerateTextureMipmap(ID);

    // Deletes the image data as it is already in the OpenGL Texture object
    stbi_image_free(bytes);
}

void Texture::texUnit(Shaderer& shader, const char* uniform, GLuint unit)
{
    // Gets the location of the uniform
    GLuint texUni = glGetUniformLocation(shader.ID, uniform);
    // Shader needs to be activated before changing the value of a uniform
    shader.Activate();
    // Sets the value of the uniform
    glUniform1i(texUni, unit);
}

void Texture::Bind()
{
    // This function is not required anymore as binding is handled during texture creation
}

void Texture::Unbind()
{
    // This function is not required anymore as binding is handled during texture creation
}

void Texture::Delete()
{
    glDeleteTextures(1, &ID);
}