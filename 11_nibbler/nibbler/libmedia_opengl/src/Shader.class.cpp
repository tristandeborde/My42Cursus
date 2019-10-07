#include <Shader.class.hpp>
#include <Exception.class.hpp>

Shader::Shader(const char * vertex_path, const char * fragment_path) {
	uint32_t vertex, fragment;

	try {
		vertex	 = this->compile(vertex_path, GL_VERTEX_SHADER);
		fragment = this->compile(fragment_path, GL_FRAGMENT_SHADER);
	}
	catch (Exception &e) {
		glDeleteShader(vertex);
		glDeleteShader(fragment);
		throw Exception(std::string("Shadder::compile::compile_failed") + e.what());
	}

	// Program
	this->link(vertex, fragment);

	glDeleteShader(vertex);
	glDeleteShader(fragment);
}	// Shader::Shader

void Shader::link(uint32_t vertex, uint32_t fragment) {
	int success = 0;

	if ((this->_id = glCreateProgram()) == 0) {
		throw Exception("Shadder::glCreateProgram::Program");
	}
	glAttachShader(this->_id, vertex);
	glAttachShader(this->_id, fragment);
	glLinkProgram(this->_id);
	glGetProgramiv(this->_id, GL_LINK_STATUS, &success);
	if (success == 0) {
		char buffer[512];
		glGetProgramInfoLog(this->_id, sizeof(buffer), nullptr, buffer);
		glDeleteShader(vertex);
		glDeleteShader(fragment);
		throw Exception("Shadder::glGetProgramiv::link_failed " + std::string(buffer));
	}
}	// Shader::link

uint32_t Shader::compile(const char * path, uint32_t flag) const{
	uint32_t elem;
	int success = 0;
	std::string code;

	try
	{
		std::ifstream file;

		file.open(path);
		std::stringstream ss;
		ss << file.rdbuf();
		file.close();
		code = ss.str();
	}
	catch (std::ifstream::failure &)
	{
		throw Exception("Shader::File_Not_Succesfully_Read");
	}
	const char * shader_code = code.c_str();

	if ((elem = glCreateShader(flag)) == 0) {
		throw Exception("Shader::glCreateShader");
	}
	glShaderSource(elem, 1, &shader_code, nullptr);
	glCompileShader(elem);
	glGetShaderiv(elem, GL_COMPILE_STATUS, &success);
	if (success == 0) {
		char buffer[512];
		glGetShaderInfoLog(elem, sizeof(buffer), nullptr, buffer);
		glDeleteShader(elem);
		throw Exception("Shader::glGetShaderiv::Fragment::compilation_failed " + std::string(buffer));
	}
	return elem;
}	// Shader::compile

void Shader::use() {
	glUseProgram(this->_id);
}

void Shader::setBool(const std::string &name, bool value) const{
	glUniform1i(glGetUniformLocation(this->_id,
			name.c_str()), static_cast<int>(value));
}

void Shader::setInt(const std::string &name, int value) const{
	glUniform1i(glGetUniformLocation(this->_id, name.c_str()), value);
}

void Shader::setFloat(const std::string &name, float value) const{
	glUniform1f(glGetUniformLocation(this->_id, name.c_str()), value);
}

void Shader::setMat4(const std::string &name, glm::mat4 value) const{
	glUniformMatrix4fv(glGetUniformLocation(this->_id, name.c_str()), 1, GL_FALSE,
	  glm::value_ptr(value));
}

void Shader::setVec3(const std::string &name, glm::vec3 value) const{
	GLint loc = glGetUniformLocation(this->_id, name.c_str());

	glUniform3f(loc, value.x, value.y, value.z);
}

void Shader::stop(void) {
	glDeleteShader(this->_id);
}
