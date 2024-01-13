#pragma once

class ModelOBJ {
public:
	std::string path;

	std::vector<GLuint> indices;

	std::vector<PositionVertex> position_coordinates;
	std::vector<NormalVertex> normal_coordinates;
	std::vector<TextureVertex> texture_coordinates;

	// CONSTRUCTOR
	ModelOBJ(std::string path) : path(path) {
		loadFromFile();
	}

	void loadFromFile() {
		std::ifstream file(path);

		std::vector<PositionVertex> pos_coordinates;
		std::vector<NormalVertex> norm_coordinates;
		std::vector<TextureVertex> tex_coordinates;

		// File successfully opens case
		if (file) {
			std::string lineText;
			while (std::getline(file, lineText)) {

				// position data case
				if (startWith(lineText, "v ")) {
					PositionVertex pos;
					sscanf_s(lineText.c_str(), "v %f %f %f", &pos.position[0], &pos.position[1], &pos.position[2]);
					pos_coordinates.push_back(pos);
				}
				// normal coord data case
				if (startWith(lineText, "vn ")) {
					NormalVertex n;
					sscanf_s(lineText.c_str(), "vn %f %f %f", &n.normals[0], &n.normals[1], &n.normals[2]);
					norm_coordinates.push_back(n);
				}
				// texture coord data case
				if (startWith(lineText, "vt ")) {
					TextureVertex tex;
					sscanf_s(lineText.c_str(), "vt %f %f %f", &tex.texCoord[0], &tex.texCoord[1], &tex.texCoord[2]);
					tex_coordinates.push_back(tex);
				}
				// face creation case
				if (startWith(lineText, "f ")) {
					int v1, v2, v3;
					int vt1, vt2, vt3;
					int vn1, vn2, vn3;
					sscanf_s(lineText.c_str(), "f %d/%d/%d %d/%d/%d %d/%d/%d",
						&v1, &vt1, &vn1,
						&v2, &vt2, &vn2,
						&v3, &vt3, &vn3);

					// Add face data
					addVertexData(v1, vn1, vt1, pos_coordinates, tex_coordinates, norm_coordinates);
					addVertexData(v2, vn2, vt2, pos_coordinates, tex_coordinates, norm_coordinates);
					addVertexData(v3, vn3, vt3, pos_coordinates, tex_coordinates, norm_coordinates);

					// Add indices for the vertices
					indices.push_back(static_cast<GLuint>(position_coordinates.size() - 3));
					indices.push_back(static_cast<GLuint>(position_coordinates.size() - 2));
					indices.push_back(static_cast<GLuint>(position_coordinates.size() - 1));
				}
				// all other data case
			}
		}
		// File does not open case
		else {  
			std::cout << "Failed to load file: " << path << std::endl;
		}
	}


private:

	void addVertexData(int vIdx, int nIdx, int vtIdx, std::vector<PositionVertex>& pos, std::vector<TextureVertex>& tex, std::vector<NormalVertex>& norm) {

		PositionVertex p = pos[vIdx - 1];
		NormalVertex n = norm[nIdx - 1];
		TextureVertex t = tex[vtIdx - 1];

		position_coordinates.push_back(p);
		normal_coordinates.push_back(n);
		texture_coordinates.push_back(t);
	}

	bool startWith(std::string& line, const char* text) {
		size_t textLen = strlen(text);
		if (line.size() < textLen) {
			return false;
		}
		for (size_t i = 0; i < textLen; i++) {
			if (line[i] == text[i]) continue;
			else return false;
		}
		return true;
	}
};