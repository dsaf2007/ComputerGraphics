#version 330

uniform mat4 gl_ModelViewMatrix;
uniform mat4 gl_ProjectionMatrix;

in vec3 a_pos;
in vec3 a_color;

out vec4 v_color;

void main()
{
	gl_Position = gl_ModelViewMatrix * gl_ProjectionMatrix * vec4(a_pos, 1.0);
	v_color = vec4(a_color, 1.0);
};