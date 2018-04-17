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

			vec3 mulColor = vec3(5.0f, 5.0f, 5.0f);//색을 나타내기 위해 곱해줄 벡터

			std::vector<glm::vec3> vertices;//정육면체의 좌표
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
				color[i] = mulColor * vertices[i];//좌표값에 5를 곱한 색을 나타내는 백터
			}


			std::vector<Triangle>triangles;//std라이브러리의 벡터를 이용해 좌표 number을 배열에 저장.
			triangles.resize(4);
			triangles[0] = Triangle(0, 2, 7);
			triangles[1] = Triangle(5, 2, 0);
			triangles[2] = Triangle(7, 2, 5);
			triangles[3] = Triangle(5, 0, 7);



			static float angle = 0.0f; //static안좋음 나중에 변수 따로만들어서 하기
			angle += 10.0f;
			glPushMatrix();
			glRotatef(15.0f, 1.0f, 0.0f, 0.0f);//x축으로 15도 회전
			glRotatef(angle, 0.0f, 1.0f, 0.0f);//y축으로 계속 회전
			

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
				glVertex3fv(&vertices[i][0]);//꼭짓점을 찍는다.
			}
		
			glEnd();

			// draw triangle
			glEnable(GL_CULL_FACE);
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			glBegin(GL_TRIANGLES); // 
								   //   glColor3f(0.0f, 0.0f, 1.0f);

			for (int i = 0; i < triangles.size(); i++) {
				glColor3fv(&color[triangles[i][0]][0]);//triangles의 좌표를 받아 색을 입힌다
				glVertex3fv(&vertices[triangles[i][0]][0]);//triangles 벡터의 첫번째 값,즉 x좌표를 그린다.

				glColor3fv(&color[triangles[i][1]][0]);
				glVertex3fv(&vertices[triangles[i][1]][0]);//triangles 벡터의 두번째 값,즉 y좌표를 그린다.

				glColor3fv(&color[triangles[i][2]][0]);
				glVertex3fv(&vertices[triangles[i][2]][0]); //triangles 벡터의 마지막 값, 즉 y좌표를 그린다.

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
	vec3 mulcolor2 = vec3(5.0f, -5.0f, 5.0f);//아랫면은 y좌표가 음수이기 때문에 색이 너무 어둡게 나와서 다른 값을 곱해준다.

		std::vector<glm::vec3> vertices;
		vertices.resize(13);
		vertices[0] = vec3(0.0f, 0.3f, 0.0f);//윗면의 원점
		for (int i = 1; i < 13; i++)//원을 12개의 삼각형으로 나누어 그리기 때문에 12개위 원위의 점을 찍는다.
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
			triangles[i] = Triangle(0,(i+1)%12+1, i+1);//마지막 삼각형은 첫번째 점을 다시 찍어야 하기 때문에 나머지 연산자를 이용한다.
		}



		std::vector<glm::vec3> vertices1;//아랫면을 그리기 위한 vertices
		vertices1.resize(13);
		vertices1[0] = vec3(0.0f, -0.3f, 0.0f);//아랫면의 원점
		for (int i = 1; i < 13; i++)//12등분하여 삼각형의 좌표를 찍는다.
		{
			vertices1[i] = vec3(0.2*cos(degree2radian(30 * i)), -0.3f, 0.2*sin(degree2radian(30 * i)));
		}

		std::vector<glm::vec3> colors1;//아랫면의 색.
		colors1.resize(13);

		for (int i = 0; i < 13; i++)
		{
			colors1[i] =mulcolor2*vertices1[i];
		}
		std::vector<Triangle>triangles1;
		triangles1.resize(12);
		for (int i = 0; i < 12; i++)
		{
			triangles1[i] = Triangle(0, i + 1, (i + 1) % 12 + 1);//윗면과 마찬가지로 1번째 점을 그리기 위해 나머지 연산자 이용
		}

		std::vector<glm::vec3> colors2;
		colors2.resize(24);//옆면의 색을 위한 vector
		
		for (int i = 0; i < 12; i++)//colors2에 colors와 colors1의 값을 차례대로 넣는다.
		{
			colors2[i] = colors[i];
		}
		for (int i = 12; i < 24; i++)
		{
			colors2[i] = colors1[i - 12];
		}
		
	
		std::vector<glm::vec3> vertices2;//옆면을 그리기 위한 vertices.옆면을 그리기 위해서는 윗면과 아랫면의 점 모두가 필요하기 때문에(원점 제외) 24로 사이즈를 정한다.
		vertices2.resize(24);
		for (int i = 0; i < 12; i++)//윗면의 값 입력
		{
			vertices2[i] = vertices[i+1];
		}
		for (int i = 12; i < 24; i++)//아랫면의 값 입력
		{
			vertices2[i] = vertices1[i -11];
		}
		std::vector<Triangle>triangles2;//옆면 벡터
		//옆면은 사각형이 여러개 붙은 형태이기 때문에 그 사각형을 삼각형 두개로 나누어서 그린다.
		triangles2.resize(24);
		for (int i = 0; i < 12; i++)
		{
			triangles2[i] = Triangle(i+12,i,(i+1)%12);//옆면 삼각형의 일부. 마찬가지로 첫번째 점을 찍어야해서 나머지 연산자 이용
		}
		for (int i = 0; i < 11; i++)
		{
			triangles2[i + 12] = Triangle(i+13, i+12,i+1);//첫번째 점을 찍어야하는데 index가 12이기때문에 나머지 연산자 사용이 어려워서 따로 정하였다.
		}
		triangles2[23] = Triangle(0, 12, 23);//마지막 삼각형



	

		static float angle = 0.0f; //static안좋음 나중에 변수 따로만들어서 하기
		angle += 5.0f;
		glPushMatrix();
		glRotatef(angle, 1.0f, 0.0f, 0.0f);
		glRotatef(angle, 0.0f, 1.0f, 0.0f);
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

		for (int i = 0; i < triangles.size(); i++) {//윗면 렌더링
			glColor3f(1.0f, 1.0f, 0.0f);
			glColor3fv(&colors[triangles[i][0]][0]);
			glVertex3fv(&vertices[triangles[i][0]][0]);

			glColor3fv(&colors[triangles[i][1]][0]);
			glVertex3fv(&vertices[triangles[i][1]][0]);

			glColor3fv(&colors[triangles[i][2]][0]);
			glVertex3fv(&vertices[triangles[i][2]][0]);

		}

		for (int i = 0; i < triangles.size(); i++) {//아랫면 랜더링
			glColor3f(1.0f, 1.0f, 0.0f);
			glColor3fv(&colors1[triangles[i][0]][0]);
			glVertex3fv(&vertices1[triangles1[i][0]][0]);

			glColor3fv(&colors1[triangles[i][1]][0]);
			glVertex3fv(&vertices1[triangles1[i][1]][0]);

			glColor3fv(&colors1[triangles[i][2]][0]);
			glVertex3fv(&vertices1[triangles1[i][2]][0]);

		}
		for (int i = 0; i <triangles2.size(); i++) {//옆면
			glColor3f(1.0f, 1.0f, 0.0f);
			glColor3fv(&colors2[triangles2[i][0]][0]);
			glVertex3fv(&vertices2[triangles2[i][0]][0]);

			glColor3fv(&colors2[triangles2[i][1]][0]);
			glVertex3fv(&vertices2[triangles2[i][1]][0]);

			glColor3fv(&colors2[triangles2[i][2]][0]);
			glVertex3fv(&vertices2[triangles2[i][2]][0]);

		}

		glEnd();
		glPopMatrix();

	}
	}
};
