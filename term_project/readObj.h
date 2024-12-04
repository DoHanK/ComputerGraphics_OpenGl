#pragma once
#include "std_sum.h"

class render {
public:
	std::vector< unsigned int > vertexIndex, uvIndex, normalIndex;
	std::vector<glm::vec3> temp_vertex;
	std::vector<glm::vec3> temp_normal;
	std::vector<glm::vec2> temp_uv;


	std::vector<glm::vec3> vertex, normal;
	std::vector<glm::vec2> uv;

	glm::vec3 min;
	glm::vec3 max;
	glm::vec3 obj_size;
	
	float max_legth = 0;




	GLuint vao, vbo[3];
	render* next=nullptr;
	int readobj_file(const char* filename);
};