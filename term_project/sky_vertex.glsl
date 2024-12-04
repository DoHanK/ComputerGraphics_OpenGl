#version 330 core
layout(location=0)in vec3 vPos;
layout(location=1)in vec3 vNormal;
layout(location=2)in vec2 vTexCoord;


out vec3 Normal;
out vec2 TexCoord;

uniform mat4 modelTransform;
uniform mat4 projectionTransform;
uniform mat4 viewtransform;


void main()
{
	gl_Position=projectionTransform*viewtransform*modelTransform*vec4(vPos,1.0f);

	Normal= vNormal;

	TexCoord=vTexCoord;

}  