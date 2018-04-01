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
	Circle(const double radius,double Red,double Green,double Blue)//행성모양인 원을 만들 생성자.
	{//원점과 원위의 두점을 꼭지점으로 하는 삼각형을 여러개 그려서 원을 만든다.

		red = Red; green = Green, blue = Blue;//원의 색을 정할 변수.
		//std::vector<glm::vec3> vertices; //homemake
		vertices.resize(361);//vertices의 갯수를 지정. 원점을 생성하고 0도부터 360까지 할 것이므로 361개
		vertices[0] = glm::vec3(0.0f, 0.0f, 0.0f);//원의 원점.
		for (int i = 1; i <= 360; i++)//0도부터 360도까지 점을 하나씩 배열에 지정한다.
		{
			vertices[i] = glm::vec3(radius*cos(degree2radian(i)),radius*sin(degree2radian(i)), 0.0f);//1도씩 옮겨간다.
		}
		
		
		//std::vector<unsigned int> indices;
		//indices.resize(3 * 3);
		for (int i = 1; i <= 360; i++)//삼각형을 각각 pushback한다.
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
		//완벽한 원이되면 자전하는것이 눈에 안보이기 때문에 절반을 나누어서 반은 검정색으로 한다.
		for (int i = 0; i <540; i++) {
			setVertex(vertices, indices[i]);//setVertex로 그린다.
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

		glPushMatrix();//전체 Matrix. 원들을 회전시킨다.
		glRotatef(rotate_angle, 0.0f, 0.0f, 1.0f);
		glPushMatrix();//Sun을 다룰 Matrix
		
		glScalef(0.5f, 0.5f, 1.0f);//사이즈를 절반
		sun.draw();//Sun을 그린다.
		glPopMatrix();

		glPushMatrix();//Earth를 다룰 Matrix
		glScalef(0.3f, 0.3f, 1.0f);//30프로로 scale
		glTranslatef(2.0f*cos(degree2radian(rotate_angle)), 2.0f*sin(degree2radian(rotate_angle)), 0.0f);//태양주위를 공전해야하므로 rotate angle에따라 지구의 변위가 원 형태로 변하게 한다.
		earth.draw();//earth를 그린다.
		glPopMatrix();
		glPushMatrix();//moon을 다를 Matrix
		glScalef(0.1f, 0.1, 1.0f);//10퍼센트로 scale
		//달의 변위는 원을 그리는 지구 주위에서 원을 그려야 하므로 원래 지구의 궤도+달의 공전궤도를 해야한다.
		//지구의 scale은 0.3으로 달의 세배이므로 2.0*였던 것을 6.0으로 해주고 +2.0*cos,sin을 하여 지구 주위를돌게 한다.
		glTranslatef(6.0f*cos(degree2radian(rotate_angle))+2.0f*cos(degree2radian(2*rotate_angle)),
					 6.0f*sin(degree2radian(rotate_angle))+2.0f*sin(degree2radian(2*rotate_angle)), 0.0f);
		moon.draw();//달을 그린다.
		glPopMatrix();
		glPopMatrix();
	}
};

