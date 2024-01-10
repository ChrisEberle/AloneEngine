#pragma once
class Model_obj
{
public:
	Model_obj(std::string path) : path(path), numIndices(0), numVertices(0) {
		obj_vert_generator();
		obj_indices();
	}
	std::string path;

	std::vector<GLuint> indices;
	std::vector<Vertex> vertices;
	
	std::vector<PositionVertex> positions;
	std::vector<TextureVertex> texture_coordinates;

	GLuint numVertices;
	GLuint numIndices;

	 
	void obj_vert_generator() {
		std::vector<PositionVertex> posCoords;
		std::vector<TextureVertex> texCoords;
		std::ifstream objFile(path);
		std::string lineText;
		while (std::getline(objFile, lineText)) {
			std::stringstream objTextStream(lineText);
			GLfloat pos[3];
			GLfloat tc[2];

			// Extract the three float position values
			if (lineText[0] == 'v' && lineText[1] == ' ') {
				// Ignore the first token ("v")
				std::string token;
				objTextStream >> token;
				objTextStream >> pos[0] >> pos[1] >> pos[2];
				PositionVertex vert;
				vert.position[0] = pos[0];
				vert.position[1] = pos[1];
				vert.position[2] = pos[2];
				posCoords.push_back(vert);
			}
			// Extract the two float texCoord values
			if (lineText[0] == 'v' && lineText[1] == 't') {
				// Ignore the first token ("vt")
				std::string token;
				objTextStream >> token;
				objTextStream >> tc[0] >> tc[1];
				TextureVertex vert;
				vert.texCoord[0] = tc[0];  // Corrected line
				vert.texCoord[1] = tc[1];  // Corrected line
				texCoords.push_back(vert);
			}
		}


		// Move the file cursor back to the beginning of the file
		objFile.clear();
		objFile.seekg(0, std::ios::beg);


		while (std::getline(objFile, lineText)) {
			std::stringstream objTextStream(lineText);

			if (lineText.substr(0, 2) == "f ") {
				// Extract face indices
				std::string token;
				objTextStream >> token; // Ignore 'f'

				std::vector<int> positionIndices;
				std::vector<int> textureIndices;

				while (objTextStream >> token) {
					std::istringstream indexStream(token);
					std::string positionIndexStr, textureIndexStr;

					// Extract position index and texture coordinate index
					std::getline(indexStream, positionIndexStr, '/');
					std::getline(indexStream, textureIndexStr, '/');

					// Convert strings to integers
					int pIndex = std::stoi(positionIndexStr);
					int tIndex = std::stoi(textureIndexStr);



					PositionVertex vert;
					vert.position[0] = posCoords[pIndex - 1].position[0];
					vert.position[1] = posCoords[pIndex - 1].position[1];
					vert.position[2] = posCoords[pIndex - 1].position[2];
					positions.push_back(vert);

					TextureVertex vertT;
					vertT.texCoord[0] = texCoords[tIndex - 1].texCoord[0];
					vertT.texCoord[1] = texCoords[tIndex - 1].texCoord[1];
					texture_coordinates.push_back(vertT);

					// Store the indices if needed for further processing
					positionIndices.push_back(pIndex);
					textureIndices.push_back(tIndex);
				}
			}
		}
		numVertices = static_cast<GLuint>(posCoords.size());
	}



	void obj_indices() {
		std::vector<GLuint> indicess;

		// Assuming you have stored the face indices during vertex generation
		for (size_t i = 0; i < positions.size(); ++i) {
			indicess.push_back(static_cast<GLuint>(i));
		}

		indices = indicess;
	}

	//getters
	int get_num_verts() {
		return numVertices;
	}
};

