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
	Circle(const double radius,double Red,double Green,double Blue)//�༺����� ���� ���� ������.
	{//������ ������ ������ ���������� �ϴ� �ﰢ���� ������ �׷��� ���� �����.

		red = Red; green = Green, blue = Blue;//���� ���� ���� ����.
		//std::vector<glm::vec3> vertices; //homemake
		vertices.resize(361);//vertices�� ������ ����. ������ �����ϰ� 0������ 360���� �� ���̹Ƿ� 361��
		vertices[0] = glm::vec3(0.0f, 0.0f, 0.0f);//���� ����.
		for (int i = 1; i <= 360; i++)//0������ 360������ ���� �ϳ��� �迭�� �����Ѵ�.
		{
			vertices[i] = glm::vec3(radius*cos(degree2radian(i)),radius*sin(degree2radian(i)), 0.0f);//1���� �Űܰ���.
		}
		
		
		//std::vector<unsigned int> indices;
		//indices.resize(3 * 3);
		for (int i = 1; i <= 360; i++)//�ﰢ���� ���� pushback�Ѵ�.
		{
			indices.push_back(0); indices.push_back(i); indices.push_back(i%360+1);
		}
	
	}

	void setVertex(const std::vector<glm::vec3>& vertices, const int& ix) {
		glVertex3f(vertices[ix].x, vertices[ix].y, vertices[ix].z);
	}
	void draw()
	{
		glBegin(GL_TRIANGLES);

		glColor3f(red, green, blue);
		//�Ϻ��� ���̵Ǹ� �����ϴ°��� ���� �Ⱥ��̱� ������ ������ ����� ���� ���������� �Ѵ�.
		for (int i = 0; i <540; i++) {
			setVertex(vertices, indices[i]);//setVertex�� �׸���.
		}
		glColor3f(0.0, 0.0, 0.0);
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

	float rotate_angle = 0.0f;

	void draw();

	float degree2radian(const float& degree)
	{
		const float pi = 3.14159265358979323846264338327950288;
		return degree / 180.0f * pi;
	}


	void drawObjects() {

		
		Circle sun(0.3f, 1.0f, 0.0f, 0.0f);
		Circle earth(0.3f, 0.0f, 0.0f, 1.0f);
		Circle moon(0.3f, 0.0f, 2.0f, 0.5f);
		//TODO:update geometry
		//for (int i = 0; i<myHouse.vertices.size(); ++i)
		//myHouse.vertices[i].x += 0.001f;

		rotate_angle += 1.0f;

		glPushMatrix();//��ü Matrix. ������ ȸ����Ų��.
		glRotatef(rotate_angle, 0.0f, 0.0f, 1.0f);
		glPushMatrix();//Sun�� �ٷ� Matrix
		
		glScalef(0.5f, 0.5f, 1.0f);//����� ����
		sun.draw();//Sun�� �׸���.
		glPopMatrix();

		glPushMatrix();//Earth�� �ٷ� Matrix
		glScalef(0.3f, 0.3f, 1.0f);//30���η� scale
		glTranslatef(2.0f*cos(degree2radian(rotate_angle)), 2.0f*sin(degree2radian(rotate_angle)), 0.0f);//�¾������� �����ؾ��ϹǷ� rotate angle������ ������ ������ �� ���·� ���ϰ� �Ѵ�.
		earth.draw();//earth�� �׸���.
		glPopMatrix();
		glPushMatrix();//moon�� �ٸ� Matrix
		glScalef(0.1f, 0.1, 1.0f);//10�ۼ�Ʈ�� scale
		//���� ������ ���� �׸��� ���� �������� ���� �׷��� �ϹǷ� ���� ������ �˵�+���� �����˵��� �ؾ��Ѵ�.
		//������ scale�� 0.3���� ���� �����̹Ƿ� 2.0*���� ���� 6.0���� ���ְ� +2.0*cos,sin�� �Ͽ� ���� ���������� �Ѵ�.
		glTranslatef(6.0f*cos(degree2radian(rotate_angle))+2.0f*cos(degree2radian(2*rotate_angle)),
					 6.0f*sin(degree2radian(rotate_angle))+2.0f*sin(degree2radian(2*rotate_angle)), 0.0f);
		moon.draw();//���� �׸���.
		glPopMatrix();
		glPopMatrix();
	}
};

