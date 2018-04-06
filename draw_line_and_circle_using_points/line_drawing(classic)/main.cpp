#include "CustomGLFW.h"

//void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
//{
//	if (key == GLFW_KEY_E && action == GLFW_RELEASE)
//		printf("E key is pressed");
//}
//
//static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
//{
//	printf("%f %f \n", xpos, ypos);
//}

int main(void)
{
	CustomGLFW my_glfw;

	my_glfw.initialize(640, 640);
	my_glfw.draw();

	return 0;
}
