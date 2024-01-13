#pragma once

class ModelOBJ {
public:
	// public variables
	std::string path;
	std::vector<GLuint> indices;
	std::vector<PositionVertex> position_coordinates;
	std::vector<NormalVertex> normal_coordinates;
	std::vector<TextureVertex> texture_coordinates;

	// CONSTRUCTOR
	ModelOBJ(std::string path) : path(path) {loadFromFile();}

	// loads the model
	void loadFromFile();

private:
	void addVertexData(int vIdx, int nIdx, int vtIdx, std::vector<PositionVertex>& pos, std::vector<TextureVertex>& tex, std::vector<NormalVertex>& norm);
	bool startWith(std::string& line, const char* text);
};