#pragma once

#include <GLFW/glfw3.h>
#include <cstring>
#include <stdlib.h>		  // srand, rand
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include "math.h"
#include <glm/glm.hpp>
#include <glm/vec3.hpp>





void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
class CustomGLFW
{
public:
	GLFWwindow * window = nullptr;

	int initialize(int width, int height);

	void draw();
	
	void drawObj();

	float degreetoradian(const float & degree)
	{
		const float pi = 3.14159265358974;

		return degree / 180.0f*pi;
	}
};

