#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <GLFW/glfw3.h>
#include <cstring>
#include <stdlib.h>		  // srand, rand
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include "math.h"
#include <iostream>
#include <time.h>

class CustomGLFW
{
public:
	GLFWwindow *window = nullptr;

	int initialize(const int width, const int height);

	void draw();

	time_t curr;
	struct tm *Time;

	float degree2radian(const float& degree)
	{
		const float pi = 3.14159265358979323846264338327950288;
		return degree / 180.0f * pi;
	}

	void drawObjects()

	{

		using namespace glm;

		using namespace std;




		const float radius = 0.5;

		const vec3  start_pt(radius, 0.0f, 0.0f);

		curr = time(NULL);

		Time = localtime(&curr);

		glBegin(GL_POINTS);

		for (float theta = 0.0f; theta < 360.0f; theta += 0.5f) // theta is degree

		{

			const float rth = degree2radian(theta);




			vec3 point;

			glm::mat3 rot_mat; //TODO: make a rotation matrix cos, sin ...




			rot_mat[0][0] = start_pt.x*cos(rth);

			rot_mat[0][1] = -start_pt.y*sin(rth);

			rot_mat[1][0] = start_pt.x*sin(rth);

			rot_mat[1][1] = start_pt.y*cos(rth);

			rot_mat[2][2] = 1.0f;




			rot_mat = glm::transpose(rot_mat);

			point = rot_mat * start_pt;




			glColor3f(0.0f, 0.0f, 1.0f);

			glVertex3f(point.x, point.y, point.z);

		}

		glEnd();

		//시

		glBegin(GL_POINTS);

		glColor3f(1.0f, 0.0f, 0.0f);

		const glm::vec3 start_pt2(0.0f, 0.0f, 0.0f);

		const glm::vec3 end_pt2(cos(degree2radian(Time->tm_sec * 3)), sin(degree2radian(Time->tm_sec * 3)), 0.0);

		const glm::vec3 dir = end_pt2 - start_pt2;

		const glm::vec3 unit_dir = glm::normalize(dir); //단위벡터만듬




		for (float i = 0; i <= 0.1f; i += 1.0f / 512.0f)

		{ //숫자 나누기할때는 2의 제곱수로 나누어야 오차가 안쌓인다.

			float mid_x = start_pt2.x + i * (end_pt2.x - start_pt2.x);

			float mid_y = start_pt2.y + i * (end_pt2.y - start_pt2.y);

			const glm::vec3 mid = start_pt2 + i * unit_dir;

			glVertex3f(-mid.x, mid.y, 0.0f);

		}

		glEnd();

		//분

		glBegin(GL_POINTS);

		glColor3f(0.0f, 1.0f, 0.0f);

		//const glm::vec3 start_pt3(0.0f, 0.0f, 0.0f);

		const glm::vec3 end_pt3(cos(degree2radian(Time->tm_sec)), sin(degree2radian(Time->tm_sec)), 0.0);

		const glm::vec3 dir2 = end_pt3 - start_pt2;

		const glm::vec3 unit_dir2 = glm::normalize(dir2); //단위벡터만듬




		for (float i = 0; i <= 0.2f; i += 1.0f / 512.0f)

		{ //숫자 나누기할때는 2의 제곱수로 나누어야 오차가 안쌓인다.

			float mid_x = start_pt2.x + i * (end_pt3.x - start_pt2.x);

			float mid_y = start_pt2.y + i * (end_pt3.y - start_pt2.y);

			const glm::vec3 mid = start_pt2 + i * unit_dir2;

			glVertex3f(-mid.x, mid.y, 0.0f);

		}

		glEnd();




		glBegin(GL_POINTS);

		glColor3f(0.0f, 0.0f, 0.0f);

		//const glm::vec3 start_pt3(0.0f, 0.0f, 0.0f);

		const glm::vec3 end_pt4(cos(degree2radian(Time->tm_sec * 6)), sin(degree2radian(Time->tm_sec * 6)), 0.0);

		const glm::vec3 dir3 = end_pt4 - start_pt2;

		const glm::vec3 unit_dir3 = glm::normalize(dir3); //단위벡터만듬




		for (float i = 0; i <= 0.2f; i += 1.0f / 512.0f)

		{ //숫자 나누기할때는 2의 제곱수로 나누어야 오차가 안쌓인다.

			float mid_x = start_pt2.x + i * (end_pt4.x - start_pt2.x);

			float mid_y = start_pt2.y + i * (end_pt4.y - start_pt2.y);

			const glm::vec3 mid = start_pt2 + i * unit_dir3;

			glVertex3f(-mid.x, mid.y, 0.0f);

		}

		glEnd();





	}

};
