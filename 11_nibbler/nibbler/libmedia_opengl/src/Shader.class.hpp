#ifndef SHADER_CLASS_HPP
#define	SHADER_CLASS_HPP

#include "libmedia_opengl.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>


class Shader
{
	/* Instantiation **************************************************************/
	public:
		Shader(void) = default;
		Shader(const GLchar * vertex_path, const GLchar * fragment_path);
		Shader(const Shader&) = default;
		~Shader(void)		  = default;

		Shader& operator=(const Shader&) = default;

	/* Shader Methods *************************************************************/
	public:
		void use();
		void setBool(const std::string &name, bool value) const;
		void setInt(const std::string &name, int value) const;
		void setFloat(const std::string &name, float value) const;
		void setMat4(const std::string &name, glm::mat4 value) const;
		void setVec3(const std::string &name, glm::vec3 value) const;
		void stop(void);

	private:
		uint32_t compile(const char * path, uint32_t flag) const;
		void link(uint32_t vertex, uint32_t fragment);

	/* Attribute ******************************************************************/
	private:
		uint32_t _id {0};
};

#endif	// #ifndef SHADER_CLASS_HPP
