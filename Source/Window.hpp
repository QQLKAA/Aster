#pragma once

#include <string>

#include <glm/vec2.hpp>
#include <glm/mat4x2.hpp>

struct GLFWwindow;

class Window
{
public:
	Window(const std::string& title, const glm::vec2& size);
	~Window();

	bool IsOpen() const;
	const glm::mat4& GetProjection() const { return projection; }
	GLFWwindow* GetNative() const { return window; } //TODO: basically i need to do like hazel entry point
	float GetTime() const; // "This function returns the value of the GLFW timer. Unless the timer has been set using glfwSetTime, the timer measures time elapsed since GLFW was initialized."
private:
	static void HandleGLError(uint32_t source, uint32_t type, uint32_t id, uint32_t severity, int length, const char* message, const void* userParam);
	static void WindowResize(GLFWwindow* window, int width, int height);
private:
	GLFWwindow* window;
	glm::mat4 projection;
};