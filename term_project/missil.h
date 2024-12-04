#pragma once
#include "std_sum.h"

class MISSIL {
public:
	glm::vec3 pos = glm::vec3{ 0.0f,0.0f,0.0f };
	glm::vec3 dir = glm::vec3{ 0.0f,0.0f,0.0f };
	
	float roate_xz;
	float roate_zy;
	MISSIL(glm::vec3 p_pos , glm::vec3 p_dir, float p_roate_xz, float p_roatate_zy) {
		glm::vec3 temp = p_dir;
		pos = p_pos+glm::vec3(0.0f,-0.4f,0.0f);
		dir.z = temp.x * sin(3.1415 * 180/ 180) + temp.z * cos(3.1415 * 180 / 180);
		dir.y = sin(3.1415 * p_roatate_zy / 180);
		dir.x = temp.x * cos(3.1415 * 180/ 180) - temp.z * sin(3.1415 * 180 / 180);
	
		roate_zy = p_roatate_zy;
		roate_xz = p_roate_xz;
	}
	MISSIL* next = nullptr;
	void update();
	
};
