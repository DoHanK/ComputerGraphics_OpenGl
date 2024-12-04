#include "plane.h"
#include "crushcheck.h"



void Plane::MakeColor() {
	for (int i = 0; i < model->vertexIndex.size(); ++i) {
		int random = rand() % 5;

		if (random == 0) {
			//갈색
			color.emplace_back(0.302f, 0.470f, 0.306f);

		}
		else if (random == 1) {
			//초록색
			color.emplace_back(0.431f, 0.631f, 0.443f);

		}
		else if (random == 2) {

			color.emplace_back(0.882f, 0.943f, 0.596f);

		}
		else if (random == 3) {

			color.emplace_back(0.404f, 0.337f, 0.270f);

		}
		else {

			color.emplace_back(0.259f, 0.278f, 0.337f);

		}
	}
}
bool Plane::plane_crush_check(glm::vec3 obj_pos, float obj_r) {
	float left, middle, right;
	left = TwopointDistance(crush_pos[0] + pos, obj_pos);
	right = TwopointDistance(crush_pos[1] + pos, obj_pos);
	middle = TwopointDistance(crush_pos[2] + pos, obj_pos);

	if (left < crush_r[0] + obj_r) {
		return true;
	}
	if (right < crush_r[1] + obj_r) {
		return true;
	}
	if (middle < crush_r[2] + obj_r) {
		return true;
	}
	return false;
}

void Plane::update(glm::vec3& camera_control, glm::vec3& camera_y_control) {
	glm::vec3 temp1 = planedir;
	glm::vec3 temp = camera_control;



	//all_coordinare 비행기체의 바라보는 방향
	pos.x += planedir.x * dir.z * planespeed;
	planedir.y = dir.y;
	pos.y += dir.y * (-dir.z) * planespeed;
	pos.z += planedir.z * dir.z * planespeed;


	//키보드 조작에 따른 회전   좌우
	if (dir.x < 0) { //좌측키눌렀을때

		angle.x += planeangle;//기체 좌로 돌리기
		//비행기 몸체 좌표  돌리기
		all_coordinare += planedirangle;
		camera_control.z = temp.x * sin(3.1415 * -planedirangle / 180) + temp.z * cos(3.1415 * -planedirangle / 180);
		camera_control.x = temp.x * cos(3.1415 * -planedirangle / 180) - temp.z * sin(3.1415 * -planedirangle / 180);


		planedir.z = temp1.x * sin(3.1415 * -planedirangle / 180) + temp1.z * cos(3.1415 * -planedirangle / 180);
		planedir.x = temp1.x * cos(3.1415 * -planedirangle / 180) - temp1.z * sin(3.1415 * -planedirangle / 180);


		//충돌 체크 점 돌리기
		for (int i = 0 ;i < 3; i++)
		{
			glm::vec3 temp2 = crush_pos[i];
			crush_pos[i].z = temp2.x * sin(3.1415 * -planedirangle / 180) + temp2.z * cos(3.1415 * -planedirangle / 180);
			crush_pos[i].x = temp2.x * cos(3.1415 * -planedirangle / 180) - temp2.z * sin(3.1415 * -planedirangle / 180);
		}

		if (angle.x > 60.f)
		{
			angle.x -= planeangle;
		}
	}
	else if (dir.x == 0) { //아무것도 안눌렀을때


		if (angle.x < 0) {
			angle.x += planeangle;

		}
		else if (angle.x == 0) {

		}
		else {
			angle.x -= planeangle;

		}
	}
	else {//좌키눌렀을때
		angle.x -= planeangle;

		//좌우 상하에 대한 처리
		all_coordinare -= planedirangle;


		camera_control.z = temp.x * sin(3.1415 * planedirangle / 180) + temp.z * cos(3.1415 * planedirangle / 180);
		camera_control.x = temp.x * cos(3.1415 * planedirangle / 180) - temp.z * sin(3.1415 * planedirangle / 180);

		planedir.z = temp1.x * sin(3.1415 * planedirangle / 180) + temp1.z * cos(3.1415 * planedirangle / 180);
		planedir.x = temp1.x * cos(3.1415 * planedirangle / 180) - temp1.z * sin(3.1415 * planedirangle / 180);

		for (int i = 0; i < 3; i++)
		{
			glm::vec3 temp2 = crush_pos[i];
			crush_pos[i].z = temp2.x * sin(3.1415 * planedirangle / 180) + temp2.z * cos(3.1415 * planedirangle / 180);
			crush_pos[i].x = temp2.x * cos(3.1415 * planedirangle / 180) - temp2.z * sin(3.1415 * planedirangle / 180);

		}
		if (angle.x < -60.f)
		{
			angle.x += planeangle;
		}
	}


	// 위로 올라갈때 y축
	if (dir.y > 0) {


		angle.y += plane_angle_y_move*planeangle;
		camera_y_control.y -= 0.2 * cameramoving;


		if (angle.y > 60.f) {
			angle.y -= plane_angle_y_move * planeangle;
			camera_y_control.y += 0.2 * cameramoving;

		}

	}
	else if (dir.y == 0) {



		if (angle.y < -0.1) {

			angle.y += plane_angle_y_move * planeangle;
			camera_y_control.y -= 0.2 * cameramoving;
		}
		else if (angle.y == 0) {

		}
		else if (angle.y > 0.1) {

			angle.y -= plane_angle_y_move * planeangle;
			camera_y_control.y += 0.2 * cameramoving;
		}
	}
	else if (dir.y < 0) {


		angle.y -= plane_angle_y_move * planeangle;
		camera_y_control.y += 0.2 * cameramoving;

		if (angle.y < -60.f) {
			angle.y += plane_angle_y_move * planeangle;
			camera_y_control.y -= 0.2 * cameramoving;

		}

	}

	


	for (int i = 0; i < 3; i++)
	{
		glm::vec3 temp2 = crush_pos[i];
		crush_pos[i].y = 100*temp2.y * sin(3.1415 * angle.x / 180);

	}

}

