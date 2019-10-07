#include "Entity3d.class.hpp"

Entity3d::Entity3d(Model &model) :
	_model(model) {}

Entity3d::Entity3d(Model &model, float x, float y, float z) :
	_model(model) {
	this->translate(x, y, z);
}

Entity3d::Entity3d(Model &model, float x, float y, float z, float size) :
	_size(glm::vec3(size)),
	_model(model) {
	this->translate(x, y, z);
}

glm::vec3 Entity3d::getPos(void) {
	return glm::vec3(
			this->_mat[0][3],
			this->_mat[1][3],
			this->_mat[2][3]
	);
}

void Entity3d::translate(float x, float y, float z) {
	this->_mat = glm::translate(this->_mat, glm::vec3(-x, z, -y));
}

void Entity3d::rotate(float angle, float x, float y, float z) {
	this->_mat = glm::rotate(this->_mat, angle, glm::vec3(-x, z, -y));
}

void Entity3d::resize(float f) {
	this->_size *= glm::vec3(f);
}

void Entity3d::resize(float x, float y, float z) {
	this->_size *= glm::vec3(x, y, z);
}

void Entity3d::resize(glm::vec3 vec) {
	this->_size *= vec;
}

void Entity3d::draw(Shader &shader) {
	glm::mat4 mat  = this->_mat;
	glm::vec3 size = this->_size;

	shader.setMat4("model", mat);
	shader.setVec3("size", size);
	this->_model.draw(shader);
}
