#include "Input.hpp"

#include <GLFW/glfw3.h>

#include "Window.hpp"

Input::Input(const std::shared_ptr<Window>& window) : window(window)
{

}

bool Input::IsKeyPressed(const Key& key) const
{
	return glfwGetKey(window->GetNative(), (int)key) == GLFW_PRESS;
}

bool Input::IsButtonPressed(const Button& button) const
{
	return glfwGetMouseButton(window->GetNative(), (int)button) == GLFW_PRESS;
}
