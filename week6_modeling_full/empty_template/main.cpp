/*
	Authored by Prof. Jeong-Mo Hong, CSE Dongguk University
	for Introduction to Computer Graphics, 2017 Spring
*/

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/GLU.h>
#include <cstring>
#include <stdlib.h>		  // srand, rand
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include <iostream>
#include "math.h"
#include <vector>
#include "Matrix4.h"
#include <fstream>
#include <string>
#include <sstream>
#include "Vector3.h"
#include "ObjReader.h"
#include "shader.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/detail/func_trigonometric.hpp"
const int width_window = 640;
const int height_window = 640;

float x, y= 0.0f,z=1.0f;//float for rotation
float angle = 0.0f;
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_UP && action == GLFW_PRESS)
	{
		x, y, z = 0.0f;
		x = 1.0f;
		angle += 10.0f;
	}
	if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
	{
		x, y, z = 0.0f;
		x = 1.0f;
		angle -= 10.0f;
	}
	if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
	{
		x, y, z = 0.0f;
		y = 1.0f;
		angle -= 10.0f;
	}
	if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
	{
		x, y, z = 0.0f;
		y = 1.0f;
		angle += 10.0f;
	}

		
}

int main(void)
{
	GLFWwindow *window = nullptr;

	/* Initialize the library */
	if (!glfwInit()) return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(width_window, height_window, "Hello World", NULL, NULL);

	if (!window){
		glfwTerminate();
		return -1;}

	// callbacks here

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return -1;}

	glClearColor(1, 1, 1, 1); // while background

	printf("%s\n", glGetString(GL_VERSION));

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	//glViewport(0, 0, width, height);
	//glOrtho(-1.2, 1.2, -1.2, 1.2, -100.0, 100.0);	
	////gluLookAt(1.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0, 1, 0);
	//gluLookAt(1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0, 1, 0);


	GLuint programID = LoadShaders("SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader");

	
	// read 3D model from obj file
	OBJReader obj_reader;
	obj_reader.readObj("./fixed.obj");
	//obj_reader.readObj("../../test-result-sphere_f80.obj");
	//obj_reader.dump();

	std::vector<Vector3<float> > colors;
	colors.resize(obj_reader.pos_stack_.size());
	for (int i = 0; i < colors.size(); i++)
	{
	/*	if (obj_reader.pos_stack_[i].x_ < 0.25f)

		{*/
			colors[i].x_ = 1.0f;
			colors[i].y_ = 177.0f/255.0f;
			colors[i].z_ = 33.0f/255.0f;
	/*	}
		else
		{
			colors[i].x_ = obj_reader.pos_stack_[i].x_;
			colors[i].y_ = obj_reader.pos_stack_[i].y_;
			colors[i].z_ = obj_reader.pos_stack_[i].z_;
		}*/
	}

	// copy geometry to buffer object
	GLuint vbo[3];
	glGenBuffers(3, vbo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, obj_reader.pos_stack_.size() * sizeof(float) *3, 
				&obj_reader.pos_stack_[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(float) * 3,
				&colors[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[2]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, obj_reader.ix_stack_.size()* sizeof(unsigned int)*3, 
				&obj_reader.ix_stack_[0], GL_STATIC_DRAW);

	// depth test
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		//glClear(GL_COLOR_BUFFER_BIT);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // <- depth test

		/*glEnableClientState(GL_COLOR_ARRAY);
		glEnableClientState(GL_VERTEX_ARRAY);

		glColorPointer(3, GL_FLOAT, 0, &obj_reader.pos_stack_[0]);
		glVertexPointer(3, GL_FLOAT, 0, &obj_reader.pos_stack_[0]);
		glDrawElements(GL_TRIANGLES, 3 * obj_reader.ix_stack_.size(), GL_UNSIGNED_INT, &obj_reader.ix_stack_[0]);

		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);*/

		// from last week (non-shader version)

		//angle += 10.0f;

		

		glUseProgram(programID);
		GLuint MatrixID = glGetUniformLocation(programID, "MVP");//
		glm::mat4 Projection = glm::ortho(-1.2f, 1.2f, -1.2f, 1.2f, -100.0f, 100.0f); // In world coordinates   //rendering pipeline

																					  // Camera matrix
		glm::mat4 View = glm::lookAt(
			glm::vec3(1.0, 0.0, 0), // Camera is at (4,3,3), in World Space
			glm::vec3(0, 0, 0), // and looks at the origin
			glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
		);

		glfwSetKeyCallback(window, key_callback);

		glm::mat4 Model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
		glm::mat4 Model2 = glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(x, y, z));
		glm::mat4 MVP = Projection * View * Model2;

		glEnableVertexAttribArray(0);

		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
		glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
		
		glVertexAttribPointer(
			0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);
		//glEnableClientState(GL_VERTEX_ARRAY);
		//glVertexPointer(3, GL_FLOAT, 0, 0);		// Vector 3

		//glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
		//glEnableClientState(GL_COLOR_ARRAY);
		//glColorPointer(3, GL_FLOAT, 0, 0);		// Vector 3

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[2]);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glDrawElements(GL_TRIANGLES, obj_reader.ix_stack_.size() * 3, GL_UNSIGNED_INT, 0);

		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);



		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();

		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	//glDeleteBuffersARB(3, vbo);

	glfwTerminate();

	return 0;
}

