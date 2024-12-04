#include "std_sum.h"
#include "readObj.h"
class Plane {
public:
	glm::vec3 pos = { 0.0 ,125.0 ,-0.0 };  //비행기 위치
	glm::vec3 scale = { 2.0f ,4.0f ,2.0f }; //비행기 크기

	std::vector<glm::vec3> color;
	// 그래픽적 회전 부분
	glm::vec3 dir = { 0.0f,0.0f,0.0f }; //방향키 눌렷는지 확인
	glm::vec3 angle = { 0.0f,0.0f,0.0f }; // 눈에 보이는 비행기 이동
	glm::vec3 planedir = { 0.0f,0.0f,1.0f }; //좌우에대한 이동한 기체의 방향키
	float all_coordinare = 0;
	//background 회전 부분

	float stealth = 1.0f;
	//레이저 포인터
	glm::vec3 lazer[2] = { glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(0.0f,0.0f,0.0f)+glm::vec3(0.0f,0.0f,10000.0f)};
	GLuint lazer_vao;
	GLuint lazer_vbo[2];
	
	int lazer_flag = 0;

	int hp = 1;


	render* model = nullptr;
	int camera_check = 1;
	glm::vec3 crush_pos[3] = { { -0.7f, 0.1f, 0.2f},
							   { 0.7f, 0.1f, 0.2f},//양옆 작은 원
							   { 0.0f, 0.0f, 0.0f } };// 가운데 큰원
	float crush_scale[3] = { 0.7f ,0.7f ,1.0f };
	float crush_r[3] = { 0.35f, 0.35f, 0.5f };  //작은 반지름 큰 반지름


	void MakeColor();
	bool plane_crush_check(glm::vec3 obj_pos, float obj_r);
	void update(glm::vec3& camera_control, glm::vec3& camera_y_control);
};
