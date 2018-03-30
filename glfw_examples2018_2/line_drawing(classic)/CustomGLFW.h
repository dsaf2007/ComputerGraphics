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


class Circle
{
public:
	std::vector<glm::vec3> vertices; //homemake
	std::vector<int> indices;
	double red = 0, green = 0, blue = 0;
	float degree2radian(const float& degree)
	{
		const float pi = 3.14159265358979323846264338327950288;
		return degree / 180.0f * pi;
	}
	Circle(const double radius,double Red,double Green,double Blue)
	{

		red = Red; green = Green, blue = Blue;
		//std::vector<glm::vec3> vertices; //homemake
		vertices.resize(361);
		vertices[0] = glm::vec3(0.0f, 0.0f, 0.0f);
		for (int i = 1; i <= 360; i++)
		{
			vertices[i] = glm::vec3(radius*cos(degree2radian(i)),radius*sin(degree2radian(i)), 0.0f);
		}
		
		
		//std::vector<unsigned int> indices;
		//indices.resize(3 * 3);
		for (int i = 1; i <= 360; i++)
		{
			indices.push_back(0); indices.push_back(i); indices.push_back(i%360+1);
		}
		//indices.push_back(0); indices.push_back(12); indices.push_back(1);
		
	}

	void setVertex(const std::vector<glm::vec3>& vertices, const int& ix) { //&가 매우중요속도관련
		glVertex3f(vertices[ix].x, vertices[ix].y, vertices[ix].z);
	}
	void draw()
	{
		glBegin(GL_TRIANGLES);

		glColor3f(red, green, blue);

		for (int i = 0; i <540; i++) {
			setVertex(vertices, indices[i]);
		}
		glColor3f(red, 1.0, blue);
		for (int i = 540; i <1080; i++) {
			setVertex(vertices, indices[i]);
		}
	


		glEnd();
	}

};

class CustomGLFW
{
public:
	GLFWwindow * window = nullptr;

	int initialize(const int width, const int height);

	float my_house2_angle = 0.0f;

	void draw();

	float degree2radian(const float& degree)
	{
		const float pi = 3.14159265358979323846264338327950288;
		return degree / 180.0f * pi;
	}


	void drawObjects() {

		
		Circle sun(0.3f, 1.0f, 0.0f, 0.0f);
		//TODO:update geometry
		//for (int i = 0; i<myHouse.vertices.size(); ++i)
		//myHouse.vertices[i].x += 0.001f;

		my_house2_angle += 1.0f;

		glPushMatrix();
		glRotatef(my_house2_angle, 0.0f, 0.0f, 1.0f);
		glPushMatrix();
		glTranslatef(0.3f*cos(degree2radian(my_house2_angle)), 0.3f*sin(degree2radian(my_house2_angle)), 0.0f);
		glScalef(0.5f, 0.5f, 1.0f);
		sun.draw();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0.0f, 0.4, 0.0f);
		//glTranslatef(0.0f, 0.5f, 0.0f);//이 함수는 누적이 된다
		glScalef(0.3f, 0.3f, 1.0f);
		//glRotatef(my_house2_angle * 5.0f, 0.0f, 0.0f, 1.0f);
		//glRotatef(my_house2_angle, 0.0f, 1.0f);
		//myHouse2.draw();
		glPopMatrix();
		glPopMatrix();
	}
};

