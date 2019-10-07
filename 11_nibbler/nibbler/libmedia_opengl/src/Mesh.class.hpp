#ifndef MESH_CLASS_HPP
#define	MESH_CLASS_HPP

#include <glm/glm.hpp>
#include <string>
#include <vector>

#include "libmedia_opengl.h"
#include "Shader.class.hpp"

struct Vertex{
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};

struct Texture{
	uint32_t	id {0};
	std::string path;
};

class Mesh
{
	/* Instantiation **************************************************************/
	public:
		Mesh(std::vector<Vertex> & vertices, std::vector<uint32_t> & indices, std::vector<Texture> && textures);
		~Mesh(void)		  = default;
		Mesh(const Mesh&) = default;
		Mesh& operator=(const Mesh&) = default;

	private:
		Mesh(void) = default;

	/* Mesh Methods ***************************************************************/
	public:
		void draw(Shader &shader);
		Texture * getLastTexture(void);

	private:
		void setup_mesh(std::vector<Vertex> &, std::vector<uint32_t> &);

	/* Attributes *****************************************************************/
	private:
		uint32_t _vao {0};
		uint32_t _vbo {0};
		uint32_t _ebo {0};
		uint64_t _nb_indices {0};
		std::vector<Texture> _textures {};
};

#endif	// #ifndef MESH_CLASS_HPP
