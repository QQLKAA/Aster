#include "Shader.hpp"

#include <fstream>
#include <iostream>
#include <vector>

#include <glad/glad.h>

Shader::Shader(const std::vector<std::string> shaders)
{
	program = glCreateProgram();

	for (const auto& path : shaders)
	{
		std::ifstream file(path);
		if (file.fail())
			std::cout << "Cant open file " << path << "\n";

		std::string strShaderType;
		getline(file, strShaderType); // get first line in file
		strShaderType.erase(strShaderType.begin(), strShaderType.begin() + 8); // remove '#shader ' from string so we will only have shader type

		uint32_t shaderType = 0;
		// i didnt find any better way to do this
		if (strShaderType == "vertex")
			shaderType = GL_VERTEX_SHADER;
		else if (strShaderType == "fragment")
			shaderType = GL_FRAGMENT_SHADER;
			
		uint32_t id = glCreateShader(shaderType);
		std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>()); // get shader file content
		const char* source = content.c_str();
		glShaderSource(id, 1, &source, 0);
		glCompileShader(id);

		// error handling
		int result;
		glGetShaderiv(id, GL_COMPILE_STATUS, &result);
		if (!result)
		{
			int len;
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &len);
			char* message = (char*)_malloca(len * sizeof(char));
			glGetShaderInfoLog(id, len, &len, message);
			glDeleteShader(id);
			std::cout << message << "\n";
			return;
		}

		glAttachShader(program, id); // after we attached shader we can delete it
		glDeleteShader(id);
	}

	glLinkProgram(program);
	glValidateProgram(program);
}

Shader::~Shader()
{
	glDeleteProgram(program);
}

void Shader::SetUniformMat4(const std::string& name, const glm::mat4& matrix)
{
	//TODO: get uniform location function
	int location = glGetUniformLocation(program, name.c_str());
	if (location == -1)
	{
		std::cout << "Cant find " << name << " uniform\n";
		return;
	}
	glUniformMatrix4fv(location, 1, 0, &matrix[0][0]); // first 2 integers are values(i might be wrong)
}

void Shader::Bind() const
{ //TODO: bind only if not binded
	glUseProgram(program);
}

void Shader::Unbind() const
{ //TODO: unbind only if binded
	glUseProgram(0);
}