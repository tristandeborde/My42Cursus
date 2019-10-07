#include "Model.class.hpp"
#include "Exception.class.hpp"
#include "Opengl.class.hpp"
#include "unistd.h"

void addText(SDL_Surface * img, const std::string &str, glm::vec3 color) {
	SDL_Rect rect;
	TTF_Font * font;
	SDL_Surface * text;

	if ((font = TTF_OpenFont("common/assets/font/OpenSans-Bold.ttf", 50)) == nullptr) {
		throw Exception("addText::TTF_OpenFont // " + std::string(SDL_GetError()));
	}
	if ((text = TTF_RenderText_Blended(font, str.c_str(),
			{static_cast<uint8_t>(255.0f * color.r), static_cast<uint8_t>(255.0f * color.g),
			 static_cast<uint8_t>(255.0f * color.b), 255})) == nullptr)
	{
		TTF_CloseFont(font);
		throw Exception("addText::TTF_RenderText_Blended // " + std::string(SDL_GetError()));
	}

	int x = img->w / 2 - text->w / 2;
	int y = img->h / 2 - text->h / 2;

	rect = {x, y, text->w, text->h};

	TTF_CloseFont(font);
	SDL_BlitSurface(text, nullptr, img, &rect);
	SDL_FreeSurface(text);
}

Model::Model(std::string const &path) {
	this->loadModel(path);
}

void Model::draw(Shader &shader) {
	for (auto & meshe : _meshes) {
		meshe.draw(shader);
	}
}

void Model::loadModel(const std::string &path) {
	Assimp::Importer import;

	const aiScene * scene = import.ReadFile(path,
			aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_PreTransformVertices | aiProcess_GenNormals);

	if (scene == nullptr || ((scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE) != 0u) || (scene->mRootNode == nullptr)) {
		throw Exception("Model::loadModel::assimp // " + std::string(import.GetErrorString()));
	}
	this->_directory = path.substr(0, path.find_last_of('/'));

	this->processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode * node, const aiScene * scene) {
	// process all the node's meshes (if any)
	for (uint32_t i = 0; i < node->mNumMeshes; i++) {
		aiMesh * mesh = scene->mMeshes[node->mMeshes[i]];
		_meshes.push_back(processMesh(mesh, scene));
	}
	// then do the same for each of its children
	for (uint32_t i = 0; i < node->mNumChildren; i++) {
		processNode(node->mChildren[i], scene);
	}
}

Mesh Model::processMesh(aiMesh * mesh, const aiScene * scene) {
	std::vector<Vertex> vertices;
	std::vector<uint32_t> indices;
	std::vector<Texture> textures;

	for (uint32_t i = 0; i < mesh->mNumVertices; i++) {
		Vertex vertex;
		// process vertex positions, normals and texture coordinates
		glm::vec3 vector;
		vector.x		= mesh->mVertices[i].x;
		vector.y		= mesh->mVertices[i].y;
		vector.z		= mesh->mVertices[i].z;
		vertex.Position = vector;
		if (mesh->mNormals != nullptr) {
			vector.x	  = mesh->mNormals[i].x;
			vector.y	  = mesh->mNormals[i].y;
			vector.z	  = mesh->mNormals[i].z;
			vertex.Normal = vector;
		}
		if (mesh->mTextureCoords[0] != nullptr) {	// does the mesh contain texture coordinates?
			glm::vec2 vec;
			vec.x = mesh->mTextureCoords[0][i].x;
			vec.y = mesh->mTextureCoords[0][i].y;
			vertex.TexCoords = vec;
		}
		else {
			vertex.TexCoords = glm::vec2(0.0f, 0.0f);
		}
		vertices.push_back(vertex);
	}
	// process indices
	for (uint32_t i = 0; i < mesh->mNumFaces; i++) {
		aiFace face = mesh->mFaces[i];
		for (uint32_t j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}
	// process material
	aiMaterial * material = scene->mMaterials[mesh->mMaterialIndex];
	std::vector<Texture> diffuseMaps = loadMaterialTextures(material,
			aiTextureType_DIFFUSE);
	textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
	std::vector<Texture> specularMaps = loadMaterialTextures(material,
			aiTextureType_SPECULAR);
	textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

	return Mesh(vertices, indices, std::move(textures));
}	// Model::processMesh

std::vector<Texture> Model::loadMaterialTextures(aiMaterial * mat, aiTextureType type) {
	std::vector<Texture> textures;

	for (uint32_t i = 0; i < mat->GetTextureCount(type); i++) {
		aiString str;
		mat->GetTexture(type, i, &str);
		bool skip = false;
		for (auto & texture : this->_textures_loaded) {
			if (std::strcmp(texture.path.data(), str.C_Str()) == 0) {
				textures.push_back(texture);
				skip = true;
				break;
			}
		}
		if (!skip) {// if texture hasn't been loaded already, load it
			Texture texture;
			texture.id	 = this->textureFromFile(str.C_Str(), "", glm::vec3(0.0f, 0.0f, 0.0f));
			texture.path = str.C_Str();
			textures.push_back(texture);
			this->_textures_loaded.push_back(texture);	// add to loaded textures
		}
	}
	return textures;
}

Model Model::withText(const std::string &str, glm::vec3 color) {
	Model model = *this;

	if (model._meshes.empty())
		return model;

	Texture * texture = model._meshes.back().getLastTexture();
	if (texture != nullptr)
		texture->id = model.textureFromFile(texture->path.c_str(), str, color);
	return model;
}

uint32_t Model::textureFromFile(const char * path, const std::string &str, glm::vec3 color) {
	std::string filename = std::string(path);

	filename = this->_directory + '/' + filename;

	uint32_t textureID;
	glGenTextures(1, &textureID);

	SDL_Surface * img = IMG_Load(filename.c_str());
	if (img == nullptr) {
		Opengl::get()->log("Error IMG_Load(" + filename + "): ", eMsgType::SDLError);
		return 0;
	}
	if (str.empty() == false) {
		addText(img, str, color);
	}
	int n_colors = img->format->BytesPerPixel;
	GLenum texture_format = GL_RGB;
	if (n_colors == 4) {
		if (img->format->Rmask == 0x000000ff)
			texture_format = GL_RGBA;
		else
			texture_format = GL_BGRA;
	}
	else if (n_colors == 3) {
		if (img->format->Rmask == 0x000000ff)
			texture_format = GL_RGB;
		else
			texture_format = GL_BGR;
	}
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, static_cast<int>(texture_format), static_cast<int>(img->w), static_cast<int>(img->h),
	  0,
	  texture_format, GL_UNSIGNED_BYTE, img->pixels);
	glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	SDL_FreeSurface(img);
	return textureID;
}	// Model::textureFromFile
