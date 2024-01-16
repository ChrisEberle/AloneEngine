#pragma once

struct Vertex
{
	GLfloat position[3];
	GLfloat texCoord[2];
};

struct PositionVertex
{
	GLfloat position[3];
};

struct TextureVertex
{
	GLfloat texCoord[2];
};

struct NormalVertex
{
	GLfloat normals[3];
};

struct MatriceVertex
{
	glm::mat4 matrices;
};