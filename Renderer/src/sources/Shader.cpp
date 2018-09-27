#include "Shader.h"
#include "OpenGL.h"
#include <iostream>
#include <fstream>
#include <sstream>

Shader::Shader(const std::string &path) : id(0), filepath(path) {
	ShaderProgramSource shaderSource = ParseShader(filepath);
	CreateShader(shaderSource.VertexSource, shaderSource.FragmentSource);
}

Shader::~Shader() {
	GLCall(glDeleteProgram(id));
}

void Shader::Use() const {
	GLCall(glUseProgram(id));
}

void Shader::StopUse() const {
	GLCall(glUseProgram(0));
}

int Shader::GetUniformLocation(const std::string& name) const {
	GLCall(int location = glGetUniformLocation(id, name.c_str()));
	return location;
}

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3) const {
	Use();
	GLCall(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
}

void Shader::SetUniform1i(const std::string& name, int value) const {
	Use();
	GLCall(glUniform1i(GetUniformLocation(name), value));
}



void Shader::CreateShader(const std::string& vSource, const std::string &fSource) {

	GLCall(id = glCreateProgram());
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vSource);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fSource);

	GLCall(glAttachShader(id, vs));
	GLCall(glAttachShader(id, fs));
	GLCall(glLinkProgram(id));
	GLCall(glValidateProgram(id));

	GLCall(glDeleteShader(vs));
	GLCall(glDeleteShader(fs));

}

unsigned int Shader::CompileShader(unsigned int type, std::string source) {

	GLCall(int shader = glCreateShader(type));
	const char* src = source.c_str();
	GLCall(glShaderSource(shader, 1, &src, nullptr));
	GLCall(glCompileShader(shader));

	int result;
	GLCall(glGetShaderiv(shader, GL_COMPILE_STATUS, &result));
	if (!result) {

		int length;
		GLCall(glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length));
		char * msg = (char *)alloca(length * sizeof(char));
		GLCall(glGetShaderInfoLog(shader, length, &length, msg));
		
		std::cout << "Failed to compile shader." << std::endl;
		std::cout << msg << std::endl;
		GLCall(glDeleteShader(shader));
		return 0;
	}
	return shader;
}


ShaderProgramSource Shader::ParseShader(const std::string &filepath) {

	enum class ShaderType {
		NONE = -1,
		VERTEX = 0,
		FRAGMENT = 1
	};

	std::ifstream stream(filepath);

	std::string line;
	std::stringstream ss[2];
	ShaderType type = ShaderType::NONE;

	while (getline(stream, line)) {

		if (line.find("#shader") != std::string::npos) {
			if (line.find("vertex") != std::string::npos) {
				type = ShaderType::VERTEX;
			}
			else if (line.find("fragment") != std::string::npos) {
				type = ShaderType::FRAGMENT;
			}
		}
		else {
			ss[(int)type] << line << '\n';
		}
	}
	return { ss[0].str(), ss[1].str() };
}

