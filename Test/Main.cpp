#include <memory>

#include <Window.hpp>
#include <Renderer.hpp>
#include <Input.hpp>

#include <iostream>

constexpr auto WindowTitle = "Aster Test";
constexpr glm::vec2 WindowSize = { 1280, 720 };

int main()
{
	std::shared_ptr<Window> window = std::make_shared<Window>(WindowTitle, WindowSize);
	std::unique_ptr<Renderer> renderer = std::make_unique<Renderer>();
	std::unique_ptr<Input> input = std::make_unique<Input>(window);

	glm::vec2 position = { 0.0f, 0.0f };
	constexpr float pps = 512.0f; // pixels per second*
	float time, lastTime = window->GetTime(), deltaTime;

	while (window->IsOpen())
	{
		// calculate delta time
		time = window->GetTime();
		deltaTime = time - lastTime;
		lastTime = time;

		renderer->Begin(window->GetProjection());
		renderer->AddQuad(position, { 16.0f, 16.0f }, { 1.0f, 0.0f, 1.0f });
		renderer->End();

		const float move = pps * deltaTime;

		if (input->IsKeyPressed(Key::W))
			position.y -= move;
		if (input->IsKeyPressed(Key::S))
			position.y += move;
		if (input->IsKeyPressed(Key::D))
			position.x += move;
		if (input->IsKeyPressed(Key::A))
			position.x -= move;
	}
}