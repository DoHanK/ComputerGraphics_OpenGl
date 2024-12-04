#include "crushcheck.h"



float TwopointDistance(glm::vec3 a_pos, glm::vec3 b_pos) {

	return sqrt((a_pos.x - b_pos.x) * (a_pos.x - b_pos.x) +
		(a_pos.y - b_pos.y) * (a_pos.y - b_pos.y) +
		(a_pos.z - b_pos.z) * (a_pos.z - b_pos.z));
}