#version 330

in vec4 v_color;
out vec4 frag_colour;

void main()
{
	frag_colour = v_color * 0.5;
};