#ifndef ENTITY3D_CLASS_HPP
#define	ENTITY3D_CLASS_HPP

#include <vector>

#include "libmedia_opengl.h"
#include "Shader.class.hpp"
#include "Model.class.hpp"

class Entity3d
{
	/* Instantiation **************************************************************/
	public:
		Entity3d(void) = default;
		explicit Entity3d(Model &model);
		Entity3d(Model &model, float x, float y, float z);
		Entity3d(Model &model, float x, float y, float z, float size);
		~Entity3d(void) = default;
		Entity3d(const Entity3d&) = default;
		Entity3d& operator=(const Entity3d&) = default;

	/* Entity3d Methods ***********************************************************/
	public:
		void translate(float x, float y, float z);
		void rotate(float angle, float x, float y, float z);
		void resize(float f);
		void resize(float x, float y, float z);
		void resize(glm::vec3 vec);
		void draw(Shader &shader);
		glm::vec3 getPos(void);

	/* Attributes *****************************************************************/
	private:
		glm::mat4 _mat {glm::mat4(1.0f)};
		glm::vec3 _size {glm::vec3(1.0f)};
		Model _model {};
};

#endif	// #ifndef ENTITY3D_CLASS_HPP
