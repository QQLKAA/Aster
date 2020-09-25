#include "Renderer.hpp"

#include <glad/glad.h>

#include <glm/mat4x2.hpp>
#include <glm/gtc/matrix_transform.hpp>

Renderer::Renderer()
{
	// vao
	glCreateVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// vbo
	glCreateBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * MaxVertices, nullptr, GL_DYNAMIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, 0, sizeof(Vertex), (const void*)offsetof(Vertex, position));

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, 0, sizeof(Vertex), (const void*)offsetof(Vertex, color));

	// ibo
	glCreateBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	{
		uint32_t* indices = new uint32_t[MaxIndices];
		uint32_t offset = 0;

		for (uint32_t i = 0; i < MaxIndices; i += 6)
		{
			indices[i + 0] = offset + 0;
			indices[i + 1] = offset + 1;
			indices[i + 2] = offset + 2;

			indices[i + 3] = offset + 2;
			indices[i + 4] = offset + 3;
			indices[i + 5] = offset + 0;

			offset += 4;
		}

		glBufferData(GL_ELEMENT_ARRAY_BUFFER, MaxIndices, indices, GL_STATIC_DRAW);
		delete[] indices;
	}

	// unbind buffers
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	vertices = new Vertex[MaxVertices];
	buffer = nullptr;
	indices = 0;

	const std::vector<std::string> shaders = {
		"Assets/Vertex.glsl",
		"Assets/Fragment.glsl"
	};
	shader = std::make_unique<Shader>(shaders);
}

Renderer::~Renderer()
{
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ibo);

	delete[] vertices;
}

void Renderer::Begin(const glm::mat4& projection)
{
	buffer = vertices;
	indices = 0;
	shader->SetUniformMat4("u_proj", projection);
}

void Renderer::End()
{
	{
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		uint32_t size = (uint32_t)((uint8_t*)buffer - (uint8_t*)vertices);
		glBufferSubData(GL_ARRAY_BUFFER, 0, size, vertices);
	}

	if (indices == 0)
		return;

	{
		glBindVertexArray(vao);
		uint32_t count = indices ? indices : MaxIndices;
		shader->Bind();
		glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
	}
}

void Renderer::AddQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec3& color)
{
	constexpr glm::vec2 positions[] = { { 0.0f, 0.0f }, { 0.0f, 1.0f }, { 1.0f, 1.0f }, { 1.0f, 0.0f } };
	const glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(position, 1.0f)) * glm::scale(glm::mat4(1.0f), { size, 1.0f });

	if (indices >= MaxIndices)
		Reset();

	for (uint8_t i = 0; i < 4; i++)
	{
		buffer->position = transform * glm::vec4(positions[i], 0.0f, 1.0f);
		buffer->color = color;
		buffer++;
	}

	indices += 6;
}

void Renderer::Reset()
{
	buffer = vertices;
	indices = 0;

	End();
}
