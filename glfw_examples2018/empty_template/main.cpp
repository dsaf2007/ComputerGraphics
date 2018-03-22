#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstring>
#include <stdlib.h>		  // srand, rand
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include <iostream>
#include "math.h"

const int width_window = 640;
const int height_window = 640;


double x = 0, y = 0;//key input으로 그림을 움직이기 위한 x y 값.
void drawFilledCircle(GLfloat x, GLfloat y, GLfloat radius) {
	//속에 색이 찬 원을 그린다.
	int i;
	int triangleAmount = 200; //원을 그리는데 사용할 삼각형 갯수.

							 
	GLfloat twicePi = 2.0f * 3.141592f;//파이의 두배

	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x, y); // 중심 좌표.
	for (i = 0; i <= triangleAmount; i++) {
		glVertex2f(
			x + (radius * cos(i *  twicePi / triangleAmount)),
			y + (radius * sin(i * twicePi / triangleAmount))
		);
	}
	glEnd();
}
void drawFilledEllipse(GLfloat x, GLfloat y, GLfloat radius) {
	//삼각형을 이용하여 타원을 그리는 함수
	//원을 그리는 함수에서 x좌표가 찍히는 범위를 절반으로 하고 y좌표가 찍히는 범위를 90프로로 하였다.
	int i;
	int triangleAmount = 200; 

							  
	GLfloat twicePi = 2.0f * 3.141592f;

	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x, y); 
	for (i = 0; i <= triangleAmount; i++) {
		glVertex2f(
			x + (radius / 2 * cos(i *  twicePi / triangleAmount)),
			y + (radius*0.9 * sin(i * twicePi / triangleAmount))
		);
	}
	glEnd();
}

void parabola(GLfloat midX,GLfloat midY) {
	//입모양을 그리는 함수.
	//포물선을 이용하였다.
	

	GLfloat y = 0;

	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_POINTS);//포물선 식을 이용하여, 포물선 식 위에 점을 찍는다.
	for (float a = 0; a < 0.025; a += 0.0005)
	{
		for (GLfloat x = -0.25; x <= 0.25; x += 0.0005) {
			y = x * x;
			glVertex2f(midX + x, midY + y + a);
		}
	}
	glEnd();
	glFlush();
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)//key입력을 받아 실행할 기능
{
	if (key == GLFW_KEY_UP && action == GLFW_PRESS)//위로 이동
	{
		y += 0.05;
	}
	if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)//아래로이동
	{
		y -= 0.05;
	}
	if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)//우로 이동
	{
		x += 0.05;
	}
	if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)//좌로 이동
	{
		x -= 0.05;
	}

}

int main(void)
{
	GLFWwindow *window = nullptr;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(width_window, height_window, "Hello World", NULL, NULL);

	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	// callbacks here
	

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	glClearColor(1, 1, 1, 1); // while background

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);
	//glOrtho(0, 1, 0, 1, -1.0, 1.0);
	glfwSetKeyCallback(window, key_callback);
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		//TODO: draw here
		//glBegin(GL_LINES);

		glColor3f(0.0f, 0.0f, 0.0f);
		drawFilledCircle(0+x, 0+y, 0.5);//검정색 테두리
		glColor3f(1.0f, 1.0f, 0.0f);
		drawFilledCircle(0+x, 0+y, 0.48);//노란색 속
		glColor3f(0.0f, 0.0f, 0.0f);
		drawFilledEllipse(0.15+x, 0.15+y, 0.1);//오른쪽 눈
		drawFilledEllipse(-0.15+x, 0.15+y, 0.1);//왼쪽 눈
		parabola(0.0+x,-0.25+y);//입

		//glEnd();

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();

		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	glfwTerminate();

	return 0;
}

