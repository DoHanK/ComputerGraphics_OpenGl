#include "balloon.h"




void Balloon::init(glm::vec3 p_pos){

	pos.x = rand() % 50;
	pos.y = rand() % 10;
	pos.z = rand() % 50;
	if (rand() % 2 == 0)
	{
		pos.x = p_pos .x-pos.x;
	}
	else
	{
		pos.x = p_pos.x +pos.x;
	}


	pos.y = p_pos.y + pos.y-10.f;
	

	if (rand() % 2 == 0)
	{
		pos.z = p_pos .z-pos.z;
	}
	else 
	{
		pos.z = p_pos.z + pos.z;
	}
	size = (float)(1+rand()%2 )+(float)rand() / RAND_MAX;

	color.x= (float)rand() / RAND_MAX;
	color.y= (float)rand() / RAND_MAX;
	color.z= (float)rand() / RAND_MAX;

	if (rand() % 2 == 0)
	{
		dir.x = (float)rand() / RAND_MAX;
	}
	else
	{
		dir.x = -(float)rand() / RAND_MAX;
	}
	if (rand() % 2 == 0)
	{
		dir.y = (float)rand() / RAND_MAX;
	}
	else
	{
		dir.y = -(float)rand() / RAND_MAX;
	}
	if (rand() % 2 == 0)
	{
		dir.z = (float)rand() / RAND_MAX;
	}
	else
	{
		dir.z = -(float)rand() / RAND_MAX;
	}



}


void Balloon::update(glm::vec3 p_pos) {

	pos.x += 0.05 * dir.x;
	pos.y += 0.0005 * dir.y;
	pos.z += 0.05 * dir.z;

	if (80.0 < TwopointDistance(p_pos, pos))
	{
		pos.x -= 0.05 * dir.x;
		pos.y -= 0.0005 * dir.y;
		pos.z -= 0.05 * dir.z;
	}

}

GLvoid Line::makeBalloonLine() {

	GLfloat result[3][2];
	GLfloat result_1[3][2];

	memset(result, 0, sizeof(result));
	memset(result_1, 0, sizeof(result_1));


	GLfloat matrix[3][3] = { {2.0f, -4.0f, 2.0f}, {-3.0f, 4.0f, -1.0f}, {1.0f, 0.0f, 0.0f} };

	GLfloat point[3][3] = { { 0.0f, 0.0f, 0.0f},
						  {-0.1f,  -0.5f,  0.0f},
						  {0.0f,  -1.0f, 0.0f} };

	GLfloat point_1[3][3] = { { 0.0f, -1.0f,  0.0f},
							{ 0.1f,  -1.5f,  0.0f},
							{ 0.0f,  -2.0f,   0.0f} };



	// 행렬 (2) 와 (3) 의 곱
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			result[i][0] += matrix[i][j] * point[j][0];
			result[i][1] += matrix[i][j] * point[j][1];
			result_1[i][0] += matrix[i][j] * point_1[j][0];
			result_1[i][1] += matrix[i][j] * point_1[j][1];
		}
	}

	// 행렬 (1) 과 새로운 행렬 result 의 곱
	GLfloat t = 0.0f;
	GLfloat x, y;
	GLfloat x_1, y_1;
	while (t < 1) {
		x = result[2][0] + t * (result[1][0] + result[0][0] * t);
		y = result[2][1] + t * (result[1][1] + result[0][1] * t);
		vertex.emplace_back(glm::vec3(x, y, 0));
		t += 0.01f;
	}
	t = 0.0f;
	while (t < 1) {
		x_1 = result_1[2][0] + t * (result_1[1][0] + result_1[0][0] * t);
		y_1 = result_1[2][1] + t * (result_1[1][1] + result_1[0][1] * t);
		vertex.emplace_back(glm::vec3(x_1, y_1, 0));
		t += 0.01f;
	}


}