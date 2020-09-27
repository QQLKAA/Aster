#include "Window.hpp"

#include <iostream>

#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include <glm/gtc/matrix_transform.hpp>

Window::Window(const std::string& title, const glm::vec2& size)
{
	glfwInit();
	window = glfwCreateWindow(size.x, size.y, title.c_str(), 0, 0);
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1); // turn vsync on
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress); // init glad

	glViewport(0, 0, size.x, size.y);
	projection = glm::ortho(0.0f, (float)size.x, (float)size.y, 0.0f);

	glfwSetWindowUserPointer(window, this); // set glfw user pointer to this class so we can access non-static variables in static functions
	glfwSetWindowSizeCallback(window, WindowResize); // on window resize callback

	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(HandleGLError, 0);
}

Window::~Window()
{
	glfwTerminate();
}

bool Window::IsOpen() const
{
	glfwSwapBuffers(window); // "Swaps the front and back buffers of the specified window" aka renders things to screen
	glClear(GL_COLOR_BUFFER_BIT); // clear screen
	glfwPollEvents();

	return !glfwWindowShouldClose(window);
}

float Window::GetTime() const
{
	return (float)glfwGetTime();
}

void Window::HandleGLError(uint32_t source, uint32_t type, uint32_t id, uint32_t severity, int length, const char* message, const void* userParam)
{
	if (severity == GL_DEBUG_SEVERITY_MEDIUM || severity == GL_DEBUG_SEVERITY_HIGH) //TODO: bitwise operation if possible
		std::cout << message << "\n";
}

void Window::WindowResize(GLFWwindow* window, int width, int height)
{
	auto _this = (Window*)glfwGetWindowUserPointer(window);

	_this->projection = glm::ortho(0.0f, (float)width, (float)height, 0.0f);
	glViewport(0, 0, width, height);
}