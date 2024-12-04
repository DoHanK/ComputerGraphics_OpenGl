#version 330 core

layout(location=0)in vec3 vPos;
layout(location=1)in vec3 vNormal;

out vec3 FragPos;
out vec3 Normal;

uniform mat4 modelTransform;
uniform mat4 projectionTransform;
uniform mat4 viewtransform;



void main()
{

	gl_Position=projectionTransform*viewtransform*modelTransform*vec4(vPos,1.0f);

	FragPos =vec3(modelTransform * vec4(vPos,1.0f));

	Normal=vec3(modelTransform *vec4(vNormal,1.0f));

}