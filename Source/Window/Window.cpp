#include "Window.h"

Window::Window(WindowSize size, const std::string& title) 
	: mSize(size), mTitle(title), mWindow(nullptr)
{
}

Window::~Window()
{
	glfwTerminate();
}

void Window::Initialize()
{
	if (!glfwInit()){
		printf("Failed to initialize GLFW!\n");
		abort();
	}
	else
		printf("GLFW initialized successfully!\n");

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	mWindow = glfwCreateWindow(mSize.X, mSize.Y, mTitle.c_str(), nullptr, nullptr);

	if (mWindow == nullptr)
	{
		printf("Failed to create window!\n");
		abort();
	}
	else
		printf("Window created successfully!\n");

}

void Window::Run()
{
	glfwPollEvents();
}

