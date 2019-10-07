#ifndef CAMERA_CLASS_HPP
#define	CAMERA_CLASS_HPP

#include "libmedia_opengl.h"

class Camera
{
	/* Instantiation **************************************************************/
	public:
		Camera(void)		  = default;
		~Camera(void)		  = default;
		Camera(const Camera&) = default;
		Camera& operator=(const Camera&) = default;

	/* Camera Methods *************************************************************/
	public:
		void setPos(float x, float y, float z);
		glm::vec3 getPos(void);
		void setTarget(float x, float y, float z);
		void setUp(float x, float y, float z);
		void setProjectionPerspective(float width, float height, float fov);
		void setProjectionOrtho(float width, float height, float fov);

		glm::mat4 getProjection(void);
		glm::mat4 getView(void);

	/* Attributes *****************************************************************/
	private:
		glm::vec3 _pos {};
		glm::vec3 _target {};
		glm::vec3 _up {};
		glm::mat4 _projection {};
};

#endif	// #ifndef CAMERA_CLASS_HPP
