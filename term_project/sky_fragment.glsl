#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec2 TexCoord;

uniform vec3 cameraPos;

uniform sampler2D outTexture; 
uniform sampler2D outTexture1; 
uniform sampler2D outTexture2; 
uniform sampler2D outTexture3;
uniform sampler2D outTexture4; 
uniform sampler2D outTexture5;
uniform sampler2D outTexture6;

void main()
{             

	FragColor=texture(outTexture,TexCoord);


//    vec3 I = normalize(FragPos - cameraPos);
//    vec3 R = reflect(I, normalize(Normal));

}