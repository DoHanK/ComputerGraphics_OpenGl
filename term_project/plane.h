#include "std_sum.h"
#include "readObj.h"
class Plane {
public:
	glm::vec3 pos = { 0.0 ,125.0 ,-0.0 };  //����� ��ġ
	glm::vec3 scale = { 2.0f ,4.0f ,2.0f }; //����� ũ��

	std::vector<glm::vec3> color;
	// �׷����� ȸ�� �κ�
	glm::vec3 dir = { 0.0f,0.0f,0.0f }; //����Ű ���Ǵ��� Ȯ��
	glm::vec3 angle = { 0.0f,0.0f,0.0f }; // ���� ���̴� ����� �̵�
	glm::vec3 planedir = { 0.0f,0.0f,1.0f }; //�¿쿡���� �̵��� ��ü�� ����Ű
	float all_coordinare = 0;
	//background ȸ�� �κ�

	float stealth = 1.0f;
	//������ ������
	glm::vec3 lazer[2] = { glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(0.0f,0.0f,0.0f)+glm::vec3(0.0f,0.0f,10000.0f)};
	GLuint lazer_vao;
	GLuint lazer_vbo[2];
	
	int lazer_flag = 0;

	int hp = 1;


	render* model = nullptr;
	int camera_check = 1;
	glm::vec3 crush_pos[3] = { { -0.7f, 0.1f, 0.2f},
							   { 0.7f, 0.1f, 0.2f},//�翷 ���� ��
							   { 0.0f, 0.0f, 0.0f } };// ��� ū��
	float crush_scale[3] = { 0.7f ,0.7f ,1.0f };
	float crush_r[3] = { 0.35f, 0.35f, 0.5f };  //���� ������ ū ������


	void MakeColor();
	bool plane_crush_check(glm::vec3 obj_pos, float obj_r);
	void update(glm::vec3& camera_control, glm::vec3& camera_y_control);
};
