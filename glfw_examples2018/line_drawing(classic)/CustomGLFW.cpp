#pragma once
#include "CustomGLFW.h"


float red = 0.0f, green = 0.0f, blue = 0.0f;
int color = 0;
int CustomGLFW::initialize(int width, int height)
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
	glClearColor(1, 1, 1, 1); // while background
	glfwSetKeyCallback(window, key_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);

}

void CustomGLFW::draw()
{
	float px = 0.0f, py = 0.0f;


	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		//upadate data
		px += 0.001f;

		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);
		//glPushMatrix();
		////glRotatef(45.0f, 0.0f, 0.0f,1.0f);
		////TODO: draw here
		//glBegin(GL_TRIANGLE_FAN);



		drawObj();
		//glColor3f(red, green, blue);//Basiclly 3D
		//glVertex3f(0.0f, 0.0f, 0.0f);
		//glVertex3f(0.5f, 0.0f, 0.0f);
		//glVertex3f(0.5f, 0.5f, 0.0f);
		//glVertex3f(0.0f, 0.5f, 0.0f);

		//glPopMatrix();
		//glEnd();


		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();

		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	glfwTerminate();
}

void CustomGLFW::drawObj()
{

	//glm::vec3 start_pt(0.0f, 0.0f, 0.0f);
	//glm::vec3 end_pt(0.5f, 0.5f, 0.0f);
	//glm::vec3 dir = end_pt - start_pt;
	//const glm::vec3 unit_dir = glm::normalize(dir);

	//float start_x = 0.0f, start_y = 0.0f;
	//float end_x = 0.5f, end_y=0.5f;
	float mid_x, mid_y;

	const int n_pts = 10;
	//for (float t = 0.0f; t <= 1.0f; t +=1.0/128.0f)
	//{
	//
	//	glBegin(GL_POINTS);
	//	glColor3f(0.0f, 0.0f, 1.0f);
	//
	//	//parametric line
	//	//const float t = 0.5;
	//	glm::vec3 mid_pt = start_pt + t*unit_dir;
	//	
	//	glVertex3f(mid_pt.x, mid_pt.y, mid_pt.z);
	//	
	//	glEnd();
	//	/*glBegin(GL_POINT);
	//	glColor3f(0.0f, 0.0f, 1.0f);
	//	glVertex3f(start_x, start_y, 0.0f);
	//	glVertex3f(end_x, end_y, 0.0f);
	//	glEnd();*/
	//}
	const float radius = 1.0f;
	glm::vec3 start_pt(radius, 0.0f, 0.0f);
	glBegin(GL_POINTS);
	for (float theta = 0.0f; theta < 360.0f; theta += 1.0f)
	{
		const float rth = degreetoradian(theta);

		glm::vec3 point;
		glm::mat3 rot_mat;//cos,sin...
		point.x = start_pt.x*cos(rth) - start_pt.y*sin(rth);
		point.y = start_pt.x*sin(rth) + start_pt.y*cos(rth);
		//point =rot_mat*start_pt;
		
		glColor3f(0.0f, 0.0f, 1.0f);

		//parametric line
		//const float t = 0.5;
		//glm::vec3 mid_pt = start_pt + t * unit_dir;

		glVertex3f(point.x, point.y, 0.0f);

		
		/*glBegin(GL_POINT);
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(start_x, start_y, 0.0f);
		glVertex3f(end_x, end_y, 0.0f);
		glEnd();*/
	}
	glEnd();
}

void key_callback(GLFWwindow * window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_E && action == GLFW_PRESS)
	{
		int temp = color;
		while (color == temp)
		{
			color = rand() % 3;
		}

		switch (color)
		{
		case 0: red = 1.0f, green = 0.0f, blue = 0.0f; break;
		case 1: red = 0.0f, green = 1.0f, blue = 0.0f; break;
		case 2: red = 0.0f, green = 0.0f, blue = 1.0f; break;
		}
	}

}

void mouse_button_callback(GLFWwindow * window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
	{
		int temp = color;
		while (color == temp)
		{
			color = rand() % 3;
		}

		switch (color)
		{
		case 0: red = 1.0f, green = 0.0f, blue = 0.0f; break;
		case 1: red = 0.0f, green = 1.0f, blue = 0.0f; break;
		case 2: red = 0.0f, green = 0.0f, blue = 1.0f; break;
		}
	}
}
