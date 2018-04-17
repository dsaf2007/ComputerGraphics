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
//�ڵ��������Ұ�





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
			colors[i].r = (float)(rand() % 255) / 255.0f;    // this is equal to colors[i].x, �޸� ������
			colors[i].g = (float)(rand() % 255) / 255.0f;
			colors[i].b = (float)(rand() % 255) / 255.0f;
		}
	}

	void drawObjects(int shape)
	{
		if (shape == 0)//���ü
		{
			using namespace glm;
			using namespace std;

			// circle drawing example
			const float radius = 1.0f;

			vec3 mulColor = vec3(5.0f, 5.0f, 5.0f);//���� ��Ÿ���� ���� ������ ����

			std::vector<glm::vec3> vertices;//������ü�� ��ǥ
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
				color[i] = mulColor * vertices[i];//��ǥ���� 5�� ���� ���� ��Ÿ���� ����
			}


			std::vector<Triangle>triangles;//std���̺귯���� ���͸� �̿��� ��ǥ number�� �迭�� ����.
			triangles.resize(4);
			triangles[0] = Triangle(0, 2, 7);
			triangles[1] = Triangle(5, 2, 0);
			triangles[2] = Triangle(7, 2, 5);
			triangles[3] = Triangle(5, 0, 7);



			static float angle = 0.0f; //static������ ���߿� ���� ���θ��� �ϱ�
			angle += 10.0f;
			glPushMatrix();
			glRotatef(15.0f, 1.0f, 0.0f, 0.0f);//x������ 15�� ȸ��
			glRotatef(angle, 0.0f, 1.0f, 0.0f);//y������ ��� ȸ��
			

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
				glVertex3fv(&vertices[i][0]);//�������� ��´�.
			}
		
			glEnd();

			// draw triangle
			glEnable(GL_CULL_FACE);
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			glBegin(GL_TRIANGLES); // 
								   //   glColor3f(0.0f, 0.0f, 1.0f);

			for (int i = 0; i < triangles.size(); i++) {
				glColor3fv(&color[triangles[i][0]][0]);//triangles�� ��ǥ�� �޾� ���� ������
				glVertex3fv(&vertices[triangles[i][0]][0]);//triangles ������ ù��° ��,�� x��ǥ�� �׸���.

				glColor3fv(&color[triangles[i][1]][0]);
				glVertex3fv(&vertices[triangles[i][1]][0]);//triangles ������ �ι�° ��,�� y��ǥ�� �׸���.

				glColor3fv(&color[triangles[i][2]][0]);
				glVertex3fv(&vertices[triangles[i][2]][0]); //triangles ������ ������ ��, �� y��ǥ�� �׸���.

			}

			glEnd();
			glPopMatrix();

		}
	
	if (shape == 1)//�����
	{

		using namespace glm;
		using namespace std;

		// circle drawing example
		const float radius = 1.0f;

	vec3 midcolor=vec3(0.5f,0.5f,0.5f);
	vec3 mulcolor = vec3(5.0f, 5.0f, 5.0f);
	vec3 mulcolor2 = vec3(5.0f, -5.0f, 5.0f);//�Ʒ����� y��ǥ�� �����̱� ������ ���� �ʹ� ��Ӱ� ���ͼ� �ٸ� ���� �����ش�.

		std::vector<glm::vec3> vertices;
		vertices.resize(13);
		vertices[0] = vec3(0.0f, 0.3f, 0.0f);//������ ����
		for (int i = 1; i < 13; i++)//���� 12���� �ﰢ������ ������ �׸��� ������ 12���� ������ ���� ��´�.
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
			triangles[i] = Triangle(0,(i+1)%12+1, i+1);//������ �ﰢ���� ù��° ���� �ٽ� ���� �ϱ� ������ ������ �����ڸ� �̿��Ѵ�.
		}



		std::vector<glm::vec3> vertices1;//�Ʒ����� �׸��� ���� vertices
		vertices1.resize(13);
		vertices1[0] = vec3(0.0f, -0.3f, 0.0f);//�Ʒ����� ����
		for (int i = 1; i < 13; i++)//12����Ͽ� �ﰢ���� ��ǥ�� ��´�.
		{
			vertices1[i] = vec3(0.2*cos(degree2radian(30 * i)), -0.3f, 0.2*sin(degree2radian(30 * i)));
		}

		std::vector<glm::vec3> colors1;//�Ʒ����� ��.
		colors1.resize(13);

		for (int i = 0; i < 13; i++)
		{
			colors1[i] =mulcolor2*vertices1[i];
		}
		std::vector<Triangle>triangles1;
		triangles1.resize(12);
		for (int i = 0; i < 12; i++)
		{
			triangles1[i] = Triangle(0, i + 1, (i + 1) % 12 + 1);//����� ���������� 1��° ���� �׸��� ���� ������ ������ �̿�
		}

		std::vector<glm::vec3> colors2;
		colors2.resize(24);//������ ���� ���� vector
		
		for (int i = 0; i < 12; i++)//colors2�� colors�� colors1�� ���� ���ʴ�� �ִ´�.
		{
			colors2[i] = colors[i];
		}
		for (int i = 12; i < 24; i++)
		{
			colors2[i] = colors1[i - 12];
		}
		
	
		std::vector<glm::vec3> vertices2;//������ �׸��� ���� vertices.������ �׸��� ���ؼ��� ����� �Ʒ����� �� ��ΰ� �ʿ��ϱ� ������(���� ����) 24�� ����� ���Ѵ�.
		vertices2.resize(24);
		for (int i = 0; i < 12; i++)//������ �� �Է�
		{
			vertices2[i] = vertices[i+1];
		}
		for (int i = 12; i < 24; i++)//�Ʒ����� �� �Է�
		{
			vertices2[i] = vertices1[i -11];
		}
		std::vector<Triangle>triangles2;//���� ����
		//������ �簢���� ������ ���� �����̱� ������ �� �簢���� �ﰢ�� �ΰ��� ����� �׸���.
		triangles2.resize(24);
		for (int i = 0; i < 12; i++)
		{
			triangles2[i] = Triangle(i+12,i,(i+1)%12);//���� �ﰢ���� �Ϻ�. ���������� ù��° ���� �����ؼ� ������ ������ �̿�
		}
		for (int i = 0; i < 11; i++)
		{
			triangles2[i + 12] = Triangle(i+13, i+12,i+1);//ù��° ���� �����ϴµ� index�� 12�̱⶧���� ������ ������ ����� ������� ���� ���Ͽ���.
		}
		triangles2[23] = Triangle(0, 12, 23);//������ �ﰢ��



	

		static float angle = 0.0f; //static������ ���߿� ���� ���θ��� �ϱ�
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

		for (int i = 0; i < triangles.size(); i++) {//���� ������
			glColor3f(1.0f, 1.0f, 0.0f);
			glColor3fv(&colors[triangles[i][0]][0]);
			glVertex3fv(&vertices[triangles[i][0]][0]);

			glColor3fv(&colors[triangles[i][1]][0]);
			glVertex3fv(&vertices[triangles[i][1]][0]);

			glColor3fv(&colors[triangles[i][2]][0]);
			glVertex3fv(&vertices[triangles[i][2]][0]);

		}

		for (int i = 0; i < triangles.size(); i++) {//�Ʒ��� ������
			glColor3f(1.0f, 1.0f, 0.0f);
			glColor3fv(&colors1[triangles[i][0]][0]);
			glVertex3fv(&vertices1[triangles1[i][0]][0]);

			glColor3fv(&colors1[triangles[i][1]][0]);
			glVertex3fv(&vertices1[triangles1[i][1]][0]);

			glColor3fv(&colors1[triangles[i][2]][0]);
			glVertex3fv(&vertices1[triangles1[i][2]][0]);

		}
		for (int i = 0; i <triangles2.size(); i++) {//����
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
