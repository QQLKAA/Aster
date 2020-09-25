#include <memory>

#include <Window.hpp>
#include <Renderer.hpp>

const std::string WindowTitle = "Aster Test";
const glm::vec2 WindowSize = { 1280, 720 };

int main()
{
	std::unique_ptr<Window> window = std::make_unique<Window>(WindowTitle, WindowSize);
	std::unique_ptr<Renderer> renderer = std::make_unique<Renderer>();

	while (window->IsOpen())
	{
		renderer->Begin(window->GetProjection());
		renderer->AddQuad({ 0.0f, 0.0f }, { 16.0f, 16.0f }, { 1.0f, 0.0f, 1.0f });
		renderer->End();
	}
}