#include "CustomGLFW.h"

int CustomGLFW::initialize(const int width, const int height)
{
	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(width, height, "Hello World", NULL, NULL);

	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // white background
}
int shape = 0;
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)//key입력을 받아 실행할 기능
{
	if (key == GLFW_KEY_E && action == GLFW_PRESS)
	{
		shape = 1;
	}
	if (key == GLFW_KEY_F && action == GLFW_PRESS)
	{
		shape = 0;
	}



}

void CustomGLFW::draw() //TODO: find better name
{
	//float px = 0.0f, py = 0.0f;

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		// update data
		//px += 0.01f;
		
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glfwSetKeyCallback(window, key_callback);
		
		std::cout << shape << std::endl;
		drawObjects(shape);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();

		std::this_thread::sleep_for(std::chrono::milliseconds(50));
	}

	glfwTerminate();
}
