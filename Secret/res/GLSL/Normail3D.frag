#version 330 

out vec3 fColor;
in vec3 vt_color;

void  main()  
{  
	fColor = vt_color; 
}  