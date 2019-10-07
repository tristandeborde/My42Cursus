#include "Camera.class.hpp"

void Camera::setPos(float x, float y, float z) {
	this->_pos = glm::vec3(x, y, z);
}

glm::vec3 Camera::getPos(void) {
	return glm::vec3(-this->_pos.x, this->_pos.z, this->_pos.y);
}

void Camera::setTarget(float x, float y, float z) {
	this->_target = glm::vec3(x, y, z);
}

void Camera::setUp(float x, float y, float z) {
	this->_up = glm::vec3(x, y, z);
}

void Camera::setProjectionPerspective(float width, float height, float fov) {
	this->_projection = glm::perspective(glm::radians(fov), width / height, 0.1f, 100.0f);
}

void Camera::setProjectionOrtho(float width, float height, float fov) {
	float aspect = width / height;
	float w		 = fov / 2 * aspect;
	float h		 = fov / 2;

	this->_projection = glm::ortho(-w, w, -h, h, 0.0f, 100.0f);
}

glm::mat4 Camera::getProjection(void) {
	return this->_projection;
}

glm::mat4 Camera::getView(void) {
	glm::mat4 view;

	view = glm::lookAt(
			glm::vec3(-this->_pos.x, this->_pos.z, this->_pos.y),
			glm::vec3(-this->_target.x, this->_target.z, this->_target.y),
			glm::vec3(0.0f, 1.0f, 0.0f));
	return view;
}
