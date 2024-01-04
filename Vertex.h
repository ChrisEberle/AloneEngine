#pragma once

struct Vertex
{
	GLfloat position[3];
	GLfloat texCoord[2];
	GLfloat texId;
};

struct ObjPositionCoordinates
{
	GLfloat position[3];
};

struct ObjTextureCoordinates
{
	GLfloat texCoord[2];
};
