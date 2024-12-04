#pragma once
#include "std_sum.h"

GLint result;
GLchar errorLog[512];

GLuint vertexShader[4], fragmentshader[4];
GLuint s_program[4];


GLuint make_fragmentShaders(const char* file, const int num);
GLuint make_vertexShaders(const char* file, const int num);
GLuint make_shaderProgram(const int num);
char* filetobuf(const char* file);


GLuint make_vertexShaders(const char * file, const int num)
{
	GLchar* vertexsource;
	vertexsource = filetobuf(file);

	vertexShader[num] = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(vertexShader[num], 1, (const GLchar**)&vertexsource, NULL);

	glCompileShader(vertexShader[num]);
	glGetShaderiv(vertexShader[num], GL_COMPILE_STATUS, &result);


	if (!result)
	{
		glGetShaderInfoLog(vertexShader[num], 512, NULL, errorLog);
		std::cerr << "ERROR: vertex shader error \n" << errorLog << std::endl;
		return false;

	}


}
GLuint make_fragmentShaders(const char *file , const int num)
{

	GLchar* fragmentsource;
	fragmentsource = filetobuf(file);

	fragmentshader[num] = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(fragmentshader[num], 1, (const GLchar**)&fragmentsource, NULL);
	glCompileShader(fragmentshader[num]);
	glGetShaderiv(fragmentshader[num], GL_COMPILE_STATUS, &result);

	if (!result)
	{
		glGetShaderInfoLog(fragmentshader[num], 512, NULL, errorLog);
		std::cerr << "ERROR:vertex Shader error \n" << errorLog << std::endl;
		return false;
	}
}
GLuint make_shaderProgram(const int num)
{
	s_program[num] = glCreateProgram();

	glAttachShader(s_program[num], vertexShader[num]);
	glAttachShader(s_program[num], fragmentshader[num]);

	glLinkProgram(s_program[num]);


	glDeleteShader(vertexShader[num]);
	glDeleteShader(fragmentshader[num]);

	if (!result)
	{
		glGetShaderInfoLog(s_program[num], 512, NULL, errorLog);
		std::cerr << "ERROR:shader program 연결실패 \n" << errorLog << std::endl;
		return false;
	}
}

void InitShader(const int num,const char * vertex,const char * fragment)
{
	make_vertexShaders(vertex,num);
	make_fragmentShaders(fragment,num);

	s_program[num] = glCreateProgram();

	glAttachShader(s_program[num], vertexShader[num]);
	glAttachShader(s_program[num], fragmentshader[num]);
	glLinkProgram(s_program[num]);


	glDeleteShader(vertexShader[num]);
	glDeleteShader(fragmentshader[num]);

	glUseProgram(s_program[num]);

}

char* filetobuf(const char* file)
{
	FILE* fptr;
	long length;
	char* buf;

	fptr = fopen(file, "rb"); /* Open file for reading */
	if (!fptr) /* Return NULL on failure */
		return NULL;
	fseek(fptr, 0, SEEK_END); /* Seek to the end of the file */
	length = ftell(fptr); /* Find out how many bytes into the file we are */
	buf = (char*)malloc(length + 1);
	fseek(fptr, 0, SEEK_SET); /* Go back to the beginning of the file */
	fread(buf, length, 1, fptr); /* Read the contents of the file in to the buffer */
	fclose(fptr); /* Close the file */
	buf[length] = 0; /* Null terminator */

	return buf; /* Return the buffer */
}

