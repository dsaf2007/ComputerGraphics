#pragma once
#include "CustomGLFW.h"

int main(void)
{
	CustomGLFW my_glfw;
	my_glfw.initialize(800, 800);

	my_glfw.draw();
	
	return 0;
}
