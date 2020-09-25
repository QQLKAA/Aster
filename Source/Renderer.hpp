#pragma once

#include <memory>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/mat4x2.hpp>

#include "Shader.hpp"

// credits to Hazel Engine by The Cherno
class Renderer
{
public:
	Renderer();
	~Renderer();

	void Begin(const glm::mat4& projection);
	void End();

	void AddQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec3& color);
private:
	void Reset(); // aka End() -> Begin()
private:
	struct Vertex
	{
		glm::vec2 position;
		glm::vec3 color;
	};
private:
	const uint32_t MaxQuads = 1000, MaxVertices = MaxQuads * 4, MaxIndices = MaxQuads * 6;
	uint32_t vao, vbo, ibo;
	uint32_t indices; // indices count

	Vertex* buffer,* vertices;

	std::unique_ptr<Shader> shader;
};