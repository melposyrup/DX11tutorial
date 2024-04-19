#include "Window.h"

Window::Window(WindowSize size, const std::string& title) : mSize(size), mTitle(title)
{
}

Window::~Window()
{
	glfwTerminate();
}

void Window::Initialize()
{
	if (!glfwInit())
		printf("Failed to initialize GLFW!");
	else
		printf("GLFW initialized successfully!");

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	mWindow = glfwCreateWindow(mSize.X, mSize.Y, mTitle.c_str(), nullptr, nullptr);
}

void Window::Run()
{
	glfwPollEvents();
}

