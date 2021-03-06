#pragma once

#include <string>
#include "glm/glm.hpp"

struct ShaderProgramSource {
	std::string VertexSource;
	std::string FragmentSource;
};

class Shader {
private:
	unsigned int id;
	std::string filepath;

public:
	Shader(const std::string &path);
	~Shader();

	void Use() const;
	void StopUse() const;

	int GetUniformLocation(const std::string& name) const;

	void SetUniformMatrix4f(const std::string& name, const glm::mat4& matrix) const;
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3) const;
	void SetUniform1i(const std::string& name, int value) const;

private:
	void CreateShader(const std::string& vSource, const std::string& fSource);
	unsigned int CompileShader(unsigned int type, std::string source);
	ShaderProgramSource ParseShader(const std::string &filepath);

};