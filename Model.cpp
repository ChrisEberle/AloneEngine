#include "engine.h"




Model::Model(std::string path, unsigned int instancing, std::vector<glm::mat4> instanceMatrix)
{
	Model::path = path;
	Model::instancing = instancing;
	Model::instanceMatrix = instanceMatrix;

	
	// Resize and initialize matricesMeshes vector
	matricesMeshes = instanceMatrix;
}

void Model::Draw(Shader& shader, Camera& camera, glm::vec3 translation, glm::quat rotation, glm::vec3 scale)
{
	// Go over all meshes and draw each one
	for (unsigned int i = 0; i < meshes.size(); i++)
	{
		meshes[i].Mesh::Draw(shader, camera, instanceMatrix[i], translation, rotation, scale);
	}
}


void Model::loadMesh()
{
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
				indices.push_back(static_cast<GLuint>(vertices.size() - 3));
				indices.push_back(static_cast<GLuint>(vertices.size() - 2));
				indices.push_back(static_cast<GLuint>(vertices.size() - 1));
			}
			// all other data case
		}

		meshes.push_back(Mesh(vertices, indices, material, instancing, instanceMatrix));

	}
	// File does not open case
	else {
		std::cout << "Failed to load file: " << path << std::endl;
	}
}

void Model::loadCube()
{
	//                     POSITION VECTOR
	
	Vertex verts;
	//FRONT
	verts.position = glm::vec3( -0.5f,  -0.5f,  0.5f);
	verts.texCoord = glm::vec2(0.0f, 0.0f);
	verts.normals = glm::vec3(0.0f, 0.0f, 1.0f);
	vertices.push_back(verts);
	verts.position = glm::vec3(  0.5f,  -0.5f,  0.5f);
	verts.texCoord = glm::vec2(1.0f, 0.0f);
	verts.normals = glm::vec3(0.0f, 0.0f, 1.0f);
	vertices.push_back(verts);
	verts.position = glm::vec3( -0.5f,   0.5f,  0.5f);
	verts.texCoord = glm::vec2(0.0f, 1.0f);
	verts.normals = glm::vec3(0.0f, 0.0f, 1.0f);
	vertices.push_back(verts);
	verts.position = glm::vec3(  0.5f,   0.5f,  0.5f);
	verts.texCoord = glm::vec2(1.0f, 1.0f);
	verts.normals = glm::vec3(0.0f, 0.0f, 1.0f);
	vertices.push_back(verts);

	//BACK  		
	verts.position = glm::vec3( -0.5f,  -0.5f,  -0.5f);
	verts.texCoord = glm::vec2(0.0f, 0.0f);
	verts.normals = glm::vec3(0.0f, 0.0f, -1.0f);
	vertices.push_back(verts);
	verts.position = glm::vec3(  0.5f,  -0.5f,  -0.5f);
	verts.texCoord = glm::vec2(1.0f, 0.0f);
	verts.normals = glm::vec3(0.0f, 0.0f, -1.0f);
	vertices.push_back(verts);
	verts.position = glm::vec3( -0.5f,   0.5f,  -0.5f);
	verts.texCoord = glm::vec2(0.0f, 1.0f);
	verts.normals = glm::vec3(0.0f, 0.0f, -1.0f);
	vertices.push_back(verts);
	verts.position = glm::vec3(  0.5f,   0.5f,  -0.5f);
	verts.texCoord = glm::vec2(1.0f, 1.0f);
	verts.normals = glm::vec3(0.0f, 0.0f, -1.0f);
	vertices.push_back(verts);
	//LEFT  			
	verts.position = glm::vec3(  -0.5f,  -0.5f,  -0.5f);
	verts.texCoord = glm::vec2(0.0f, 0.0f);
	verts.normals = glm::vec3(-1.0f, 0.0f, 0.0f);
	vertices.push_back(verts);
	verts.position = glm::vec3(  -0.5f,  -0.5f,   0.5f);
	verts.texCoord = glm::vec2(1.0f, 0.0f);
	verts.normals = glm::vec3(-1.0f, 0.0f, 0.0f);
	vertices.push_back(verts);
	verts.position = glm::vec3( -0.5f,   0.5f,  -0.5f);
	verts.texCoord = glm::vec2(0.0f, 1.0f);
	verts.normals = glm::vec3(-1.0f, 0.0f, 0.0f);
	vertices.push_back(verts);
	verts.position = glm::vec3( -0.5f,   0.5f,   0.5f);
	verts.texCoord = glm::vec2(1.0f, 1.0f);
	verts.normals = glm::vec3(-1.0f, 0.0f, 0.0f);
	vertices.push_back(verts);
	//RIGHT 		
	verts.position = glm::vec3( 0.5f,  -0.5f,  -0.5f);
	verts.texCoord = glm::vec2(0.0f, 0.0f);
	verts.normals = glm::vec3(1.0f, 0.0f, 0.0f);
	vertices.push_back(verts);
	verts.position = glm::vec3( 0.5f,  -0.5f,   0.5f);
	verts.texCoord = glm::vec2(1.0f, 0.0f);
	verts.normals = glm::vec3(1.0f, 0.0f, 0.0f);
	vertices.push_back(verts);
	verts.position = glm::vec3( 0.5f,   0.5f,  -0.5f);
	verts.texCoord = glm::vec2(0.0f, 1.0f);
	verts.normals = glm::vec3(1.0f, 0.0f, 0.0f);
	vertices.push_back(verts);
	verts.position = glm::vec3( 0.5f,   0.5f,   0.5f);
	verts.texCoord = glm::vec2(1.0f, 1.0f);
	verts.normals = glm::vec3(1.0f, 0.0f, 0.0f);
	vertices.push_back(verts);
	//TOP   		
	verts.position = glm::vec3( -0.5f,  0.5f,   0.5f);
	verts.texCoord = glm::vec2(0.0f, 0.0f);
	verts.normals = glm::vec3(0.0f, 1.0f, 0.0f);
	vertices.push_back(verts);
	verts.position = glm::vec3(  0.5f,  0.5f,   0.5f);
	verts.texCoord = glm::vec2(1.0f, 0.0f);
	verts.normals = glm::vec3(0.0f, 1.0f, 0.0f);
	vertices.push_back(verts);
	verts.position = glm::vec3( -0.5f,  0.5f,  -0.5f);
	verts.texCoord = glm::vec2(0.0f, 1.0f);
	verts.normals = glm::vec3(0.0f, 1.0f, 0.0f);
	vertices.push_back(verts);
	verts.position = glm::vec3(  0.5f,  0.5f,  -0.5f);
	verts.texCoord = glm::vec2(1.0f, 1.0f);
	verts.normals = glm::vec3(0.0f, 1.0f, 0.0f);
	vertices.push_back(verts);
	//BOTTOM	
	verts.position = glm::vec3( -0.5f,  -0.5f,   0.5f);
	verts.texCoord = glm::vec2(0.0f, 0.0f);
	verts.normals = glm::vec3(0.0f, -1.0f, 0.0f);
	vertices.push_back(verts);
	verts.position = glm::vec3(  0.5f,  -0.5f,   0.5f);
	verts.texCoord = glm::vec2(1.0f, 0.0f);
	verts.normals = glm::vec3(0.0f, -1.0f, 0.0f);
	vertices.push_back(verts);
	verts.position = glm::vec3( -0.5f,  -0.5f,  -0.5f);
	verts.texCoord = glm::vec2(0.0f, 1.0f);
	verts.normals = glm::vec3(0.0f, -1.0f, 0.0f);
	vertices.push_back(verts);
	verts.position = glm::vec3(  0.5f,  -0.5f,  -0.5f);
	verts.texCoord = glm::vec2(1.0f, 1.0f);
	verts.normals = glm::vec3(0.0f, -1.0f, 0.0f);
	vertices.push_back(verts);


	indices = {
		// FRONT
		0, 1, 2, 1, 3, 2,
		// BACK
		4, 6, 5, 5, 6, 7,
		// LEFT
		8, 9, 10, 9, 11, 10,
		// RIGHT
		12, 14, 13, 13, 14, 15,
		// TOP
		16, 17, 18, 17, 19, 18,
		// BOTTOM
		20, 22, 21, 21, 22, 23
	};

	meshes.push_back(Mesh(vertices, indices, material, instancing, instanceMatrix));
	
	
}

void Model::loadPlane(GLuint rows, GLuint cols, GLfloat numOctaves, GLfloat persistence, GLfloat textureScaleX, GLfloat textureScaleY) {
	GLfloat originX = 0.0f;
	GLfloat originY = 0.0f;
	GLfloat originZ = 0.0f;

	for (GLuint i = 0; i < rows; ++i) {
		for (GLuint j = 0; j < cols; ++j) {
			GLfloat x = originX + j * (1.0f / (cols - 1));
			GLfloat z = originZ - i * (1.0f / (rows - 1));

			// Use multiple octaves of Perlin noise
			GLfloat y = originY;
			GLfloat frequency = 0.1f; // Initial frequency
			GLfloat amplitude = 1.0f; // Initial amplitude

			for (int k = 0; k < numOctaves; ++k) {
				y += glm::perlin(glm::vec2(x * frequency, z * frequency)) * amplitude;
				frequency *= 2.0f; // Increase frequency with each octave
				amplitude *= persistence; // Decrease amplitude with each octave
			}

			// Calculate texCoordX to repeat within each column
			GLfloat texCoordX = static_cast<GLfloat>(j % cols) / (cols - 1) * textureScaleX;

			GLfloat texCoordY = static_cast<GLfloat>(i) / (rows - 1) * textureScaleY;

			Vertex vertex;
			vertex.position = glm::vec3(x, y, z);
			vertex.texCoord = glm::vec2(texCoordX, texCoordY);

			vertices.push_back(vertex);
		}
	}

	std::vector<GLuint> planeIndices((rows - 1) * (cols - 1) * 6);
	size_t offset = 6;

	for (size_t i = 0; i < static_cast<size_t>(rows) - 1; ++i) {
		for (size_t j = 0; j < static_cast<size_t>(cols) - 1; ++j) {
			size_t currentVertex = i * cols + j;

			planeIndices[offset * (i * (static_cast<size_t>(cols) - 1) + j)] = static_cast<GLuint>(currentVertex);
			planeIndices[offset * (i * (static_cast<size_t>(cols) - 1) + j) + 1] = static_cast<GLuint>(currentVertex) + 1;
			planeIndices[offset * (i * (static_cast<size_t>(cols) - 1) + j) + 2] = static_cast<GLuint>(currentVertex) + static_cast<GLuint>(cols);

			planeIndices[offset * (i * (static_cast<size_t>(cols) - 1) + j) + 3] = static_cast<GLuint>(currentVertex) + 1;
			planeIndices[offset * (i * (static_cast<size_t>(cols) - 1) + j) + 4] = static_cast<GLuint>(currentVertex) + static_cast<GLuint>(cols) + 1;
			planeIndices[offset * (i * (static_cast<size_t>(cols) - 1) + j) + 5] = static_cast<GLuint>(currentVertex) + static_cast<GLuint>(cols);
		}
	}

	// Add the object's indices to the parent indices vector
	indices.insert(indices.end(), planeIndices.begin(), planeIndices.end());

	// NORMAL CALCULATIONS
	for (size_t i = 0; i < indices.size(); i += 3) {
		GLuint index1 = indices[i];
		GLuint index2 = indices[i + 1];
		GLuint index3 = indices[i + 2];

		// Get the vertices of the current triangle
		glm::vec3 v1(vertices[index1].position[0], vertices[index1].position[1], vertices[index1].position[2]);
		glm::vec3 v2(vertices[index2].position[0], vertices[index2].position[1], vertices[index2].position[2]);
		glm::vec3 v3(vertices[index3].position[0], vertices[index3].position[1], vertices[index3].position[2]);

		// Calculate the tangent vectors
		glm::vec3 tangent1 = v2 - v1;
		glm::vec3 tangent2 = v3 - v1;

		// Calculate the normal using the cross product of the tangents
		glm::vec3 normal = glm::normalize(glm::cross(tangent1, tangent2));

		// Accumulate the normals for each vertex of the triangle
		vertices[index1].normals[0] += normal.x;
		vertices[index1].normals[1] += normal.y;
		vertices[index1].normals[2] += normal.z;

		vertices[index2].normals[0] += normal.x;
		vertices[index2].normals[1] += normal.y;
		vertices[index2].normals[2] += normal.z;

		vertices[index3].normals[0] += normal.x;
		vertices[index3].normals[1] += normal.y;
		vertices[index3].normals[2] += normal.z;
	}

	// Normalize the accumulated normals
	for (size_t i = 0; i < vertices.size(); ++i) {
		glm::vec3 norm = glm::normalize(glm::vec3(vertices[i].normals[0], vertices[i].normals[1], vertices[i].normals[2]));

		vertices[i].normals[0] = norm.x;
		vertices[i].normals[1] = norm.y;
		vertices[i].normals[2] = norm.z;
	}


	meshes.push_back(Mesh(vertices, indices, material, instancing, instanceMatrix));
}
void Model::addVertexData(int vIdx, int nIdx, int vtIdx, std::vector<PositionVertex>& pos, std::vector<TextureVertex>& tex, std::vector<NormalVertex>& norm)
{
	Vertex vert;
	PositionVertex p = pos[vIdx - 1];
	NormalVertex n = norm[nIdx - 1];
	TextureVertex t = tex[vtIdx - 1];

	vert.position = p.position;
	vert.normals = n.normals;
	vert.texCoord = t.texCoord;

	vertices.push_back(vert);
}
bool Model::startWith(std::string& line, const char* text)
{
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
