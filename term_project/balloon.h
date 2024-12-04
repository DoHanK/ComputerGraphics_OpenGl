#include "std_sum.h"
#include "crushcheck.h"

class Balloon {
public:
	glm::vec3 pos = glm::vec3{ 0.0f,0.0f,0.0f };
	glm::vec3 dir = glm::vec3{ 0.0f,0.0f,0.0f };



	float size;
	glm::vec3 color;

	Balloon* next;
	void update(glm::vec3 p_pos);
	void init(glm::vec3 p_pos);
};

class Line {
public:
	
	std::vector<glm::vec3> vertex;
	GLuint vao;
	GLuint vbo[2];


	GLvoid makeBalloonLine();

};


