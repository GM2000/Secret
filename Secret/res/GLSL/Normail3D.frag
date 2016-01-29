#version 330 

uniform sampler2D tex;

out vec4 fColor;

in vec2 vt_texpos;
in vec3 vt_color;

void  main()  
{  
	fColor = texture2D(tex,vt_texpos); 
}  