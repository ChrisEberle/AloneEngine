#pragma once

struct Vertex
{
	GLfloat position[3];
	GLfloat texCoord[2];
	GLfloat texId;
};

struct PositionVertex
{
	GLfloat position[3];
};

struct TextureVertex
{
	GLfloat texCoord[2];
};
