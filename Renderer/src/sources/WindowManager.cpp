#include "WindowManager.h"

WindowManager::WindowManager(bool *success)
	: window(nullptr), width(-1), height(-1), name("")
{
	(*success) = glfwInit();
}

WindowManager::~WindowManager()
{
	glfwTerminate();
}

bool WindowManager::CreateWindow(int width, int height, std::string & name)
{
	window = glfwCreateWindow(width, height, name.c_str(), NULL, NULL);
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
	return (bool)window;
}

void WindowManager::MakeContextCurrent() 
{
	glfwMakeContextCurrent(window);
}
