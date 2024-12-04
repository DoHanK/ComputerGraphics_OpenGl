#pragma once
#include "std_sum.h"


class BOMB {
public:
	glm::vec3 pos;
	float size= 1.0f;

	BOMB* next = nullptr;

	BOMB(glm::vec3 b_pos) {
		pos = b_pos;

	}


	void update();

};