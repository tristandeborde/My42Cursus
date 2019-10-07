#include "Mesh.class.hpp"
#include "Exception.class.hpp"

Mesh::Mesh(std::vector<Vertex> & vertices, std::vector<uint32_t> & indices, std::vector<Texture> && textures) :
	_textures(textures) {
	this->_nb_indices = indices.size();
	this->setup_mesh(vertices, indices);
}

void Mesh::setup_mesh(std::vector<Vertex> & vertices, std::vector<uint32_t> & indices) {
	glGenVertexArrays(1, &(this->_vao));
	glGenBuffers(1, &(this->_vbo));
	glGenBuffers(1, &(this->_ebo));

	glBindVertexArray(this->_vao);
	glBindBuffer(GL_ARRAY_BUFFER, this->_vbo);

	glBufferData(GL_ARRAY_BUFFER,
	  static_cast<int64_t>(vertices.size() * sizeof(Vertex)), vertices.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->_ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
	  static_cast<int64_t>(this->_nb_indices * sizeof(uint32_t)), indices.data(), GL_STATIC_DRAW);

	// this union allow us to cast a uint64_t into a void*
	// without cpplint complaining about a reinterpret_cast.
	union {
		uint64_t i = 0;
		void *	 v;
	} off;

	// vertex positions
	glEnableVertexAttribArray(0);
	off.i = offsetof(Vertex, Position);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), off.v);
	// vertex normals
	glEnableVertexAttribArray(1);
	off.i = offsetof(Vertex, Normal);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), off.v);
	// vertex texture coords
	glEnableVertexAttribArray(2);
	off.i = offsetof(Vertex, TexCoords);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), off.v);

	glBindVertexArray(0);
}	// Mesh::setup_mesh

void Mesh::draw(Shader &shader) {
	shader.use();
	if (!_textures.empty()) {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, _textures[0].id);
	}
	// draw mesh
	glBindVertexArray(this->_vao);
	glDrawElements(GL_TRIANGLES,
	  static_cast<int>(this->_nb_indices), GL_UNSIGNED_INT, nullptr);
	glBindVertexArray(0);
}

Texture * Mesh::getLastTexture(void) {
	if (this->_textures.empty()) {
		return nullptr;
	}
	return &(this->_textures.back());
}
