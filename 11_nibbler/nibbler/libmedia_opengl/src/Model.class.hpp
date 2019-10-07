#ifndef MODEL_CLASS_HPP
#define	MODEL_CLASS_HPP

#include "Mesh.class.hpp"

class Model
{
	/* Instantiation **************************************************************/
	public:
		Model(void)	= default;
		explicit Model(std::string const &path);
		explicit Model(const char * path);
		Model(const Model&) = default;
		~Model(void)		= default;

		Model& operator=(const Model&) = default;


	/* Model Methods **************************************************************/
	public:
		void draw(Shader &shader);
		Model withText(const std::string &str, glm::vec3 color);

	private:
		void loadModel(const std::string &path);
		void processNode(aiNode * node, const aiScene * scene);
		Mesh processMesh(aiMesh * mesh, const aiScene * scene);
		std::vector<Texture> loadMaterialTextures(aiMaterial * mat, aiTextureType type);

		uint32_t textureFromFile(const char * path, const std::string &str, glm::vec3 color);

	/* Attributes *****************************************************************/
	private:
		std::vector<Mesh> _meshes {};
		std::string	_directory {};
		std::vector<Texture> _textures_loaded {};
};

void addText(SDL_Surface * img, const std::string &str, glm::vec3 color);

#endif	// #ifndef MODEL_CLASS_HPP
