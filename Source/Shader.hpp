#pragma once

#include <vector>
#include <string>

#include <glm/mat4x2.hpp>

class Shader
{
public:
	Shader(const std::vector<std::string> shaders);
	~Shader();

	void SetUniformMat4(const std::string& name, const glm::mat4& matrix);

	void Bind() const;
	void Unbind() const;
private:
	uint32_t program;
};