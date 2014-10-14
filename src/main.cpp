#include "r3dVoxel.hpp"
#include "internal/internal.hpp"

GLEWContext *context = 0;

GLEWContext *glewGetContext()
{
	return context;
}

int main(int argv, char **argc)
{
	if(!glfwInit())
		return -1;

	GLFWwindow *wnd = glfwCreateWindow(800, 600, "Test", 0, 0);
	glfwMakeContextCurrent(wnd);

	context = new GLEWContext();

	if(glewInit() != GLEW_OK)
		return -1;

	while(!glfwWindowShouldClose(wnd))
	{
		glfwPollEvents();
	}

	glfwDestroyWindow(wnd);

	glfwTerminate();
	return 0;
}
