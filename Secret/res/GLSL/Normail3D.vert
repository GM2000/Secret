#version 330  

uniform mat4 uni_projection;
uniform mat4 uni_rotate;
uniform mat4 uni_translate;

layout(location = 0) in  vec4 in_position;
layout(location = 1) in  vec3 in_color;
layout(location = 2) in  vec2 in_texpos;

out vec3 vt_color;
out vec2 vt_texpos;

void  main()  
{  
	vt_color = in_color;
	vt_texpos = in_texpos;
	gl_Position = in_position * uni_translate * uni_rotate  * uni_projection;  
}  