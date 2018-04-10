#pragma once

#include <GLFW/glfw3.h>
#include <cstring>
#include <stdlib.h>        // srand, rand
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include "math.h"
#include <iostream>
#include <vector>
//코드정리도할것


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
	Circle(const double radius, double Red, double Green, double Blue)//행성모양인 원을 만들 생성자.
	{//원점과 원위의 두점을 꼭지점으로 하는 삼각형을 여러개 그려서 원을 만든다.

		red = Red; green = Green, blue = Blue;//원의 색을 정할 변수.
											  //std::vector<glm::vec3> vertices; //homemake
		vertices.resize(361);//vertices의 갯수를 지정. 원점을 생성하고 0도부터 360까지 할 것이므로 361개
		vertices[0] = glm::vec3(0.0f, 0.0f, 0.0f);//원의 원점.
		for (int i = 1; i <= 360; i++)//0도부터 360도까지 점을 하나씩 배열에 지정한다.
		{
			vertices[i] = glm::vec3(radius*cos(degree2radian(i)), radius*sin(degree2radian(i)), 0.0f);//1도씩 옮겨간다.
		}


		//std::vector<unsigned int> indices;
		//indices.resize(3 * 3);
		for (int i = 1; i <= 360; i++)//삼각형을 각각 pushback한다.
		{
			indices.push_back(0); indices.push_back(i); indices.push_back(i % 360 + 1);
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

	
	
	void initializeobject() {

	}
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



	//class Triangle
	//{
	//public:
	//   unsigned int v0, v1, v2;
	//};

	typedef glm::tvec3<unsigned int, glm::highp> Triangle;
	void assingrandomcolor(std::vector<glm::vec3> &colors) {

		for (int i = 0; i < colors.size(); i++) {
			colors[i].r = (float)(rand() % 255) / 255.0f;    // this is equal to colors[i].x, 메모리 공유함
			colors[i].g = (float)(rand() % 255) / 255.0f;
			colors[i].b = (float)(rand() % 255) / 255.0f;
		}
	}

	void drawObjects(int shape)
	{
		if (shape == 0)//사면체
		{
			using namespace glm;
			using namespace std;

			// circle drawing example
			const float radius = 1.0f;

			vec3 mulColor = vec3(5.0f, 5.0f, 5.0f);

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

			std::vector<glm::vec3> color;
			color.resize(8);
			for (int i = 0; i < 8; i++)
			{
				color[i] = mulColor * vertices[i];
			}


			std::vector<Triangle>triangles;
			triangles.resize(4);
			triangles[0] = Triangle(0, 2, 7);
			triangles[1] = Triangle(5, 2, 0);
			triangles[2] = Triangle(7, 2, 5);
			triangles[3] = Triangle(5, 0, 7);


			/*   std::vector<unsigned int> indices;
			indices.push_back(0);
			indices.push_back(1);
			indices.push_back(2);
			indices.push_back(0);
			indices.push_back(2);
			indices.push_back(3);
			indices.push_back(0);
			indices.push_back(3);
			indices.push_back(4);*/
			std::vector<glm::vec3> vertex_color;
			std::vector<glm::vec3> triangle_color;
			triangle_color.resize(4);
			vertex_color.resize(8);
			assingrandomcolor(triangle_color);
			assingrandomcolor(vertex_color);

			static float angle = 0.0f; //static안좋음 나중에 변수 따로만들어서 하기
			angle += 10.0f;
			glPushMatrix();
			glRotatef(15.0f, 1.0f, 0.0f, 0.0f);
			glRotatef(angle, 0.0f, 1.0f, 0.0f);
			

			//axes
			glBegin(GL_LINES);

			//x - axis red

			glColor3f(1.0f, 0.0f, 0.0f);
			glVertex3f(0.0f, 0.0f, 0.0f);
			glVertex3f(1.0f, 0.0f, 0.0f);

			//y - axis red
			glColor3f(1.0f, 0.0f, 0.0f);
			glVertex3f(0.0f, 0.0f, 0.0f);
			glVertex3f(0.0f, 1.0f, 0.0f);

			//z - axis red
			glColor3f(0.0f, 0.0f, 0.0f);
			glVertex3f(0.0f, 0.0f, 0.0f);
			glVertex3f(0.0f, 0.0f, 1.0f);

			glEnd();


			//render
			glPointSize(4.0f);
			glBegin(GL_POINTS);
			glColor3f(0.0f, 0.0f, 1.0f);
			for (int i = 0; i < 8; ++i) {
				glVertex3fv(&vertices[i][0]);
			}
			for (int i = 0; i < 8; ++i) {
				glVertex3fv(&color[i][0]);
			}
			glEnd();

			// draw triangle
			glEnable(GL_CULL_FACE);
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			glBegin(GL_TRIANGLES); // 
								   //   glColor3f(0.0f, 0.0f, 1.0f);

			for (int i = 0; i < triangles.size(); i++) {
				glColor3fv(&color[triangles[i][0]][0]);
				glVertex3fv(&vertices[triangles[i][0]][0]);

				glColor3fv(&color[triangles[i][1]][0]);
				glVertex3fv(&vertices[triangles[i][1]][0]);

				glColor3fv(&color[triangles[i][2]][0]);
				glVertex3fv(&vertices[triangles[i][2]][0]);

			}

			glEnd();
			glPopMatrix();

		}
	
	if (shape == 1)//원기둥
	{

		using namespace glm;
		using namespace std;

		// circle drawing example
		const float radius = 1.0f;

	vec3 midcolor=vec3(0.5f,0.5f,0.5f);
	vec3 mulcolor = vec3(5.0f, 5.0f, 5.0f);

		std::vector<glm::vec3> vertices;
		vertices.resize(13);
		vertices[0] = vec3(0.0f, 0.3f, 0.0f);
		for (int i = 1; i < 13; i++)
		{
			vertices[i] = vec3(0.2*cos(degree2radian(30*i)), 0.3f,0.2*sin(degree2radian(30*i)));
		}

		std::vector<glm::vec3> colors;
		colors.resize(13);

		for (int i = 0; i < 13; i++)
		{
			colors[i] = mulcolor * vertices[i];
		}

		std::vector<Triangle>triangles;
		triangles.resize(12);
		for (int i = 0; i < 12; i++)
		{
			triangles[i] = Triangle(0,(i+1)%12+1, i+1);
		}



		std::vector<glm::vec3> vertices1;
		vertices1.resize(13);
		vertices1[0] = vec3(0.0f, -0.3f, 0.0f);
		for (int i = 1; i < 13; i++)
		{
			vertices1[i] = vec3(0.2*cos(degree2radian(30 * i)), -0.3f, 0.2*sin(degree2radian(30 * i)));
		}

		std::vector<glm::vec3> colors1;
		colors1.resize(13);

		for (int i = 0; i < 13; i++)
		{
			colors1[i] =mulcolor*vertices1[i];
		}



		std::vector<Triangle>triangles1;
		triangles1.resize(12);
		for (int i = 0; i < 12; i++)
		{
			triangles1[i] = Triangle(0, i+1,(i + 1) % 12 + 1);
		}

		std::vector<glm::vec3> vertices2;
		vertices2.resize(24);
		for (int i = 1; i < 13; i++)
		{
			vertices2[i] = vertices[i];
		}
		for (int i = 13; i < 24; i)
		{
			vertices2[i] = vertices1[i + 1];
		}
		std::vector<Triangle>triangles2;
		triangles1.resize(24);
		for (int i = 0; i < 12; i++)
		{
			triangles2[i] = Triangle(i+12,i,i+1);
		}
		for (int i = 0; i < 12; i++)
		{
			triangles2[i + 12] = Triangle(i + 1, (i + 13) % 24, i);
		}



		//std::vector<glm::vec3> vertex_color;
		//std::vector<glm::vec3> triangle_color;
		//triangle_color.resize(4);
		//vertex_color.resize(8);
		//assingrandomcolor(triangle_color);
		//assingrandomcolor(vertex_color);

		static float angle = 0.0f; //static안좋음 나중에 변수 따로만들어서 하기
		angle += 10.0f;
		glPushMatrix();
		glRotatef(15.0f, 1.0f, 0.0f, 0.0f);
		//glRotatef(angle, 0.0f, 1.0f, 0.0f);
		//glRotatef(15.0f, 0.0f, 0.0f, 1.0f);
		

		//axes
		glBegin(GL_LINES);

		//x - axis red

		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(1.0f, 0.0f, 0.0f);

		//y - axis red
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 1.0f, 0.0f);

		//z - axis red
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, 1.0f);

		glEnd();


		//render
		glPointSize(4.0f);
		glBegin(GL_POINTS);
		glColor3f(0.0f, 0.0f, 1.0f);
		for (int i = 0; i < 13; ++i) {
			glVertex3fv(&vertices[i][0]);
		}
		for (int i = 0; i < 13; ++i) {
			glVertex3fv(&vertices1[i][0]);
		}
		glEnd();

		// draw triangle
		glEnable(GL_CULL_FACE);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glBegin(GL_TRIANGLES); // 
							   //   glColor3f(0.0f, 0.0f, 1.0f);

		for (int i = 0; i < triangles.size(); i++) {
			glColor3f(1.0f, 1.0f, 0.0f);
			glColor3fv(&colors[triangles[i][0]][0]);
			glVertex3fv(&vertices[triangles[i][0]][0]);

			glColor3fv(&colors[triangles[i][1]][0]);
			glVertex3fv(&vertices[triangles[i][1]][0]);

			glColor3fv(&colors[triangles[i][2]][0]);
			glVertex3fv(&vertices[triangles[i][2]][0]);

		}

		for (int i = 0; i < triangles.size(); i++) {
			glColor3f(1.0f, 1.0f, 0.0f);
			glColor3fv(&colors1[triangles[i][0]][0]);
			glVertex3fv(&vertices1[triangles1[i][0]][0]);

			glColor3fv(&colors1[triangles[i][1]][0]);
			glVertex3fv(&vertices1[triangles1[i][1]][0]);

			glColor3fv(&colors1[triangles[i][2]][0]);
			glVertex3fv(&vertices1[triangles1[i][2]][0]);

		}
		for (int i = 0; i < triangles2.size(); i++) {
			glColor3f(1.0f, 1.0f, 0.0f);
			glColor3fv(&colors[triangles2[i%12][0]][0]);
			glVertex3fv(&vertices2[triangles2[i][0]][0]);

			glColor3fv(&colors[triangles2[i%12][1]][0]);
			glVertex3fv(&vertices2[triangles2[i][1]][0]);

			glColor3fv(&colors[triangles2[i%12][2]][0]);
			glVertex3fv(&vertices2[triangles2[i][2]][0]);

		}

		glEnd();
		glPopMatrix();

	}
	}
};
