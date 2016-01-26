#version 330  

uniform mat4 uni_projection;
uniform mat4 uni_rotate;
uniform mat4 uni_translate;

layout(location = 0) in  vec4 in_position;
layout(location = 1) in  vec4 in_color;

out vec4 out_color;

void  main()  
{  
	out_color = in_color;
	gl_Position = in_position * uni_translate * uni_rotate  * uni_projection;  
}  