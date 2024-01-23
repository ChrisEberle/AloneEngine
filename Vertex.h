#pragma once

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normals;
	glm::vec2 texCoord;
	glm::vec3 color;
};

struct PositionVertex
{
	glm::vec3 position;
};

struct TextureVertex
{
	glm::vec2 texCoord;
};

struct NormalVertex
{
	glm::vec3 normals;
};

struct MatriceVertex
{
	glm::mat4 matrices;
};