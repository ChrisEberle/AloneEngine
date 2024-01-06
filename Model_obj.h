#pragma once
class Model_obj
{
public:
	Model_obj(std::string path) : path(path) {}
	std::string path;
	 
	std::vector<Vertex> obj_vert_generator() {
		std::ifstream objFile(path);
		std::string lineText;
		std::vector<Vertex> vertices;
		std::vector<PositionVertex> posCoords;
		std::vector<TextureVertex> texCoords;
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



					Vertex vert;
					vert.position[0] = posCoords[pIndex - 1].position[0];
					vert.position[1] = posCoords[pIndex - 1].position[1];
					vert.position[2] = posCoords[pIndex - 1].position[2];

					vert.texCoord[0] = texCoords[tIndex - 1].texCoord[0];
					vert.texCoord[1] = texCoords[tIndex - 1].texCoord[1];
					vertices.push_back(vert);

					// Store the indices if needed for further processing
					positionIndices.push_back(pIndex);
					textureIndices.push_back(tIndex);
				}
			}
		}


		numVertices = vertices.size();
		return vertices;
	}



	std::vector<GLuint> obj_indices() {
		std::vector<GLuint> indices(numVertices);


		for (GLuint i = 0; i < numVertices; ++i) {
			indices[i] = i;
		}

		return indices;
	}

	//getters
	int get_num_verts() {
		return numVertices;
	}

private:
	 int numVertices;
	 int numIndices;
};
