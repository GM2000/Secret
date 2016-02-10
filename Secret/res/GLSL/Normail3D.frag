#version 330 

uniform sampler2D tex;

out vec4 fColor;

in vec2 vt_texpos;
in vec3 vt_color;

in vec3 vt_normal;

void  main()  
{
	float diffuse = max(0.8,dot(vt_normal,vec3(1.0,1.0,1.0)));
	
	vec3 scatteredLight = vec3(1.0,1.0,1.0) * diffuse;
	
	vec3 total = min(vt_color * scatteredLight,vec3(1.0));
	
	fColor = texture2D(tex,vt_texpos);
	
	fColor=fColor * vec4(total,1.0);
	
	if (fColor.a==0)
	{
		//discard;
	}
}  