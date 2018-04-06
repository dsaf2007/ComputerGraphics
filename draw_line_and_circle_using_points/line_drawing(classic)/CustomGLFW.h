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
#include <vector>

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

	void setVertex(const std::vector<glm::vec3>& vertices, const int& ix)
	{
		glVertex3f(vertices[ix].x, vertices[ix].y, vertices[ix].z);
	}

	void drawObjects()
	{
		using namespace glm;
		using namespace std;

		// circle drawing example
		const float radius = 1.0f;

		std::vector<glm::vec3> vertices;
		vertices.resize(8);
		
		vertices[0] = vec3(-0.2f, 0.2f, -0.2f);
		vertices[1] = vec3(-0.2f, -0.2f, -0.2f);
		vertices[2] = vec3(0.2f, -0.2f, -0.2f);
		vertices[3] = vec3(0.2f, 0.2f, -0.2f);

		vertices[4] = vec3(-0.2f, 0.2f, 0.2f);
		vertices[5] = vec3(-0.2f, -0.2f, 0.2f);
		vertices[6] = vec3(0.2f, -0.2f, 0.2f);
		vertices[7] = vec3(0.2f, 0.2f, 0.2f);

		std::vector<unsigned int> indices;
		indices.push_back(0);
		indices.push_back(1);
		indices.push_back(2);
		indices.push_back(0);
		indices.push_back(2); 
		indices.push_back(3);
		indices.push_back(0);
		indices.push_back(3);
		indices.push_back(4);

		static float angle = 0.0f;
		angle += 1.0f;

		glPushMatrix();
		glRotatef(15.0f, 1.0f, 0.0f, 0.0f);
		glRotatef(angle, 0.0f, 1.0f, 0.0f);

		// axes
		glBegin(GL_LINES);

		// x-axis red
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(0, 0, 0);
		glVertex3f(1, 0, 0);

		// y-axis green
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 1, 0);

		// z-axis blue
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 0, 1);

		glEnd();

		glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);
		glDepthMask(GL_TRUE);

		// render vertices
		glPointSize(4.0f);
		glBegin(GL_POINTS);
		glColor3f(0.0f, 0.0f, 1.0f);
		for (int i = 0; i < 8; ++i)
			glVertex3fv(&vertices[i][0]);
		glEnd();

		// draw triangles
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glBegin(GL_TRIANGLES); // glBegin(GL_LINES)

		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3fv(&vertices[0][0]);
		glVertex3fv(&vertices[2][0]);
		glVertex3fv(&vertices[1][0]);

		glColor3f(0.0f, 1.0f, 1.0f);
		glVertex3fv(&vertices[4][0]);
		glVertex3fv(&vertices[0][0]);
		glVertex3fv(&vertices[1][0]);
		
		// define 10 more triangles

		glEnd();
		
		glPopMatrix();

		//const vec3  start_pt(radius, 0.0f, 0.0f);
		//glBegin(GL_POINTS);
		//for (float theta = 0.0f; theta < 360.0f; theta += 1.0f) // theta is degree
		//{
		//	const float rth = degree2radian(theta);

		//	vec3 point;
		//	glm::mat3 rot_mat;

		//	rot_mat[0][0] = start_pt.x * cos(rth);
		//	rot_mat[0][1] = -start_pt.y * sin(rth);
		//	rot_mat[1][0] = start_pt.x * sin(rth);
		//	rot_mat[1][1] = start_pt.y * cos(rth);
		//	rot_mat[2][2] = 1.0f; // for z coordinates. see rotation matrix part in the text book.
		//	// other compoments are all zeros

		//	rot_mat = glm::transpose(rot_mat); // glm mat uses column first indexing

		//	//point.x = start_pt.x * cos(rth) - start_pt.y * sin(rth); // we need radian
		//	//point.y = start_pt.x * sin(rth) + start_pt.y * cos(rth);
		//	//point.z = 0.0f;
		//	point = rot_mat * start_pt;

		//	glColor3f(0.0f, 0.0f, 1.0f);
		//	glVertex3f(point.x, point.y, point.z);
		//}
		//glEnd();
	}
};

