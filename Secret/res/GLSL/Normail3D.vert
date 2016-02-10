#version 330  

uniform mat4 uni_projection;
uniform mat4 uni_rotate;
uniform mat4 uni_translate;

layout(location = 0) in  vec4 in_position;
layout(location = 1) in  vec3 in_color;
layout(location = 2) in  vec2 in_texpos;
layout(location = 3) in  vec3 in_normal;

out vec2 vt_texpos;
out vec3 vt_normal;
out vec3 vt_color;

void  main()
{	
	vt_texpos = in_texpos;
	vt_normal = in_normal;
	vt_color  = in_color;
	
	gl_Position = in_position * uni_translate * uni_rotate * uni_projection;
}  