#pragma once

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

class CustomGLFW
{
public:
	GLFWwindow *window = nullptr;

	int initialize(const int width, const int height);

	void draw();

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

		glBegin(GL_POINTS);
		for (float theta = 0.0f; theta < 360.0f; theta += 1.0f) // theta is degree
		{
			const float rth = degree2radian(theta);

			vec3 point;
			glm::mat3 rot_mat; //TODO: make a rotation matrix cos, sin ...

			//point.x = start_pt.x * cos(rth) - start_pt.y * sin(rth); // we need radian
			//point.y = start_pt.x * sin(rth) + start_pt.y * cos(rth);
			//point.z = 0.0f;
			point = rot_mat * start_pt;

			glColor3f(0.0f, 0.0f, 1.0f);
			glVertex3f(point.x, point.y, point.z);
		}
		glEnd();
	}
};

