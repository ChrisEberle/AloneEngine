#pragma once
class Material
{
public:
	std::vector<Texture> textures;

	Material() {
		Texture tex0("textures/dirt.png", "diffuse", 0);
		Texture tex1("textures/dirt.png", "specular", 1);

		textures.push_back(tex0);
		textures.push_back(tex1);
	};


private:
};

