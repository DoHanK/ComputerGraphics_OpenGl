
#include "readObj.h"
#include "shader.h"
#include "plane.h"
#include "crushcheck.h"
#include "missil.h"
#include "balloon.h"
#include "effect.h"
#include "user_text.h"

#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#pragma comment(lib, "winmm.lib")
#include "Mmsystem.h"
#include "Digitalv.h"
MCI_OPEN_PARMS m_mciOpenParms;
MCI_PLAY_PARMS m_mciPlayParms;
DWORD m_dwDeviceID;
MCI_OPEN_PARMS mciOpen1;
MCI_PLAY_PARMS mciPlay;
MCI_OPEN_PARMS mciOpen2;
MCI_OPEN_PARMS mciOpen3;
MCI_OPEN_PARMS mciOpen4;
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define width 1080
#define height 1080

//함수 전방 선언



//I/o 입출력과 관련된 함수들
GLvoid ReShape(int w, int h);
GLvoid drawScene(int flag);
void InitBuffer();
void key_borad(unsigned char key, int x, int y);
GLvoid specialdown(int key, int x, int y);
void createrender();
float TwopointDistance(glm::vec3 a_pos, glm::vec3 b_pos);
GLvoid display();
GLvoid specialup(int key, int x, int y);
GLvoid UpdateCamera();
//draw 함수들
GLvoid DrawPlane();
GLvoid DrawSkyBox();
GLvoid DrawMissil();
GLvoid DrawBalloon();
GLvoid DrawEffect();
//충돌 처리 관련 함수들
GLvoid DrawSphereCrush(glm::vec3 pos, float length);


//미사일 함수
void makemissil();
void delmissil(MISSIL* o);
//풍선 삭제 만들기
void delballoon(Balloon* o);
void makeballoon();
//임펙트 함수
void makeeffect(glm::vec3 o);
void deleffect(BOMB* o);

//시간
GLvoid all_update(int value);
render* head = nullptr;
render* curmove = nullptr;
render* premove = nullptr;
render* move = nullptr;
////클래스
MISSIL* m_head;
MISSIL* m_premove;
MISSIL* m_curmove;
MISSIL* m_move;
MISSIL* m_delmove;

Balloon* b_head;
Balloon* b_premove;
Balloon* b_curmove;
Balloon* b_move;
Balloon* b_delmove;


BOMB* e_head;
BOMB* e_premove;
BOMB* e_curmove;
BOMB* e_move;
BOMB* e_delmove;




glm::vec3 camera_pos = glm::vec3(0.0f, 0.0f, 1.0f);
glm::vec3 camera_y_pos = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 camera_dir = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 camera_up = glm::vec3(0.0f, 1.0f, 0.0f);
glm::vec3 light_pos = glm::vec3(0.0f, 2000.0f, 00.0f);
glm::vec3 light_power = glm::vec3(1.0f, 1.0f, 1.0f);

glm::vec3 mini_camera_pos = glm::vec3(0.0f, 2.0f, 1.0f);
glm::vec3 mini_camera_dir = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 mini_camera_up = glm::vec3(0.0f, 1.0f, 0.0f);
glm::vec3 camera_control = glm::vec3(0.0, 1.0, 4.0);


Plane plane;
Line ballooneline;

render* sphere  = nullptr;
render* box = nullptr;
render* pyramid = nullptr;
render* missil = nullptr;
glm::vec3 temp_move = glm::vec3(0.0f, 5.0f, -5.0f);
float crush_size = 2.0f;


int show_crush_flag = 0;

int stage = 0;

int ballooncount;

int endingflag = 1;

std::vector<std::string> faces =
{
		  "top.jpg",
	   "bottom.jpg",
		 "left.jpg",
		"front.jpg", 
		"right.jpg",
		 "back.jpg",
};

unsigned int VBO, VAO;
unsigned int texture[6];
unsigned int start_img;
unsigned int clear_img;
unsigned int fail_img;

int dwID;//소리아이디
void initTex(const char* file, unsigned int& store, int flag) {
	glGenTextures(1, &store); //--- 텍스처 생성

	int imgWidth, imgHeight, imgChannels;
	unsigned char* data;


	glUseProgram(s_program[2]);


	glBindTexture(GL_TEXTURE_2D, store); //--- 텍스처 바인딩
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); //--- 현재 바인딩된 텍스처의 파라미터 설정하기
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	data = stbi_load(file, &imgWidth, &imgHeight, &imgChannels, 0);

	/*if (data) {
		std::cout << "이미지 로드 성공이염, 높이:" << imgHeight << "/ 길이: " << imgWidth << std::endl;
	}
	else {
		std::cout << "이미지 로드 에러염" << std::endl;
	}*/
	//front bottom
	if (flag==0) {
		glTexImage2D(GL_TEXTURE_2D, 0, 3, imgWidth, imgHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	}
	else {
		glTexImage2D(GL_TEXTURE_2D, 0, 3, imgWidth, imgHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	}
	char temp[100] = "outTexture";

	int tLocation1 = glGetUniformLocation(s_program[2], temp);
	glUniform1i(tLocation1, 0);


}
void initTexture() {

	glGenTextures(6, texture); //--- 텍스처 생성

	int imgWidth, imgHeight, imgChannels;
	unsigned char* data[6];
	int num;
	for (int i = 0; i < 6; ++i) {


		std::cout << faces[i].c_str() << std::endl;
	}

	std::cout << "   " << std::endl;
	glUseProgram(s_program[1]);
	for (int i = 0; i < 6; ++i) {
		glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &num);


		glBindTexture(GL_TEXTURE_2D, texture[i]); //--- 텍스처 바인딩
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); //--- 현재 바인딩된 텍스처의 파라미터 설정하기
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		data[i] = stbi_load(faces[i].c_str(), &imgWidth, &imgHeight, &imgChannels, 0);

		//if (data[i]) {
		//	std::cout << "이미지 로드 성공이염, 높이:" << imgHeight << "/ 길이: " << imgWidth << std::endl;
		//}
		//else {
		//	std::cout << "이미지 로드 에러염" << std::endl;
		//}
		//front bottom
		glTexImage2D(GL_TEXTURE_2D, 0, 3, imgWidth, imgHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data[i]);

		char temp[100] = "outTexture";
		temp[10] = i + 48;
		temp[11] = '\0';
		int tLocation1 = glGetUniformLocation(s_program[1], temp);
		glUniform1i(tLocation1, 0);

	}





}



int main(int argc, char** argv)
{

	mciOpen2.lpstrElementName = "airforce.mp3"; // 파일 경로 입력
	mciOpen2.lpstrDeviceType = "mpegvideo";
	mciOpen1.lpstrElementName = "Top_Gun.mp3"; // 파일 경로 입력
	mciOpen1.lpstrDeviceType = "mpegvideo";
	mciOpen3.lpstrElementName = "clear.mp3"; // 파일 경로 입력
	mciOpen3.lpstrDeviceType = "mpegvideo";
	mciOpen4.lpstrElementName = "fail.mp3"; // 파일 경로 입력
	mciOpen4.lpstrDeviceType = "mpegvideo";

	mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE,
		(DWORD)(LPVOID)&mciOpen1);

	dwID = mciOpen1.wDeviceID;

	mciSendCommand(dwID, MCI_PLAY, MCI_DGV_PLAY_REPEAT, // play & repeat
		(DWORD)(LPVOID)&m_mciPlayParms);




	//전투기 obj 호출
	createrender();
	curmove->readobj_file("f-60.obj");
	plane.model = curmove;
	plane.MakeColor();

	//원 obj 가져오기
	createrender();
	curmove->readobj_file("sphere.obj");
	sphere = curmove;


	createrender();
	curmove->readobj_file("box.obj");
	box = curmove;

	createrender();
	curmove->readobj_file("미사일.obj");
	missil = curmove;


	createrender();
	curmove->readobj_file("pyramid.obj");
	pyramid = curmove;

	//풍선 만들기
	for (int i = 0; i < 8; i++) {

		makeballoon();

	}

	//풍선 줄 만들기
	ballooneline.makeBalloonLine();

	InitGL();





	glutInit(&argc, argv);
	glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(width, height);
	glutCreateWindow("숙제");

	glewExperimental = GL_TRUE;
	glewInit();

	initTex("topgun.png", start_img,1);
	initTex("fail.jpg", fail_img,0);
	initTex("clear.jpg", clear_img,0);

	initTexture();
	InitShader(0,"vertex.glsl","fragment.glsl");
	InitShader(1, "sky_vertex.glsl", "sky_fragment.glsl");
	InitShader(2, "sky_vertex_cube.glsl", "sky_fragment_cube.glsl");
	InitBuffer();




	glutDisplayFunc(display);
	glutKeyboardFunc(key_borad);
	glutSpecialFunc(specialdown);
	glutSpecialUpFunc(specialup);
	glutTimerFunc(1,all_update,1);
	glutReshapeFunc(ReShape);


	glutMainLoop();
}


void InitBuffer()
{

	move = head;
	//vao 젠한다.
	while (move != nullptr)
	{
		if (move == box) {
			glUseProgram(s_program[1]);
			glGenVertexArrays(1, &move->vao);
			glGenBuffers(3, move->vbo);
		}
		else {
			glUseProgram(s_program[0]);
			glGenVertexArrays(1, &move->vao);
			glGenBuffers(2, move->vbo);
		}

		//glGenBuffers(1, &move->ebo);



	//정점 버퍼 저장
		glBindVertexArray(move->vao);
		glBindBuffer(GL_ARRAY_BUFFER, move->vbo[0]);
		glBufferData(GL_ARRAY_BUFFER, move->vertex.size() * sizeof(glm::vec3), move->vertex.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		glEnableVertexAttribArray(0);

		//법선 백터
		glBindBuffer(GL_ARRAY_BUFFER, move->vbo[1]);
		glBufferData(GL_ARRAY_BUFFER, move->normal.size() * sizeof(glm::vec3), move->normal.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		glEnableVertexAttribArray(1);

		if (box == move) {

			glBindBuffer(GL_ARRAY_BUFFER, move->vbo[2]);
			glBufferData(GL_ARRAY_BUFFER, move->uv.size() * sizeof(glm::vec2), move->uv.data(), GL_STATIC_DRAW);
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
			glEnableVertexAttribArray(2);
		}
		move = move->next;
	}



	//레이저 만들기
	glUseProgram(s_program[0]);
	glGenVertexArrays(1, &plane.lazer_vao);
	glGenBuffers(2, plane.lazer_vbo);

	glBindVertexArray(plane.lazer_vao);
	glBindBuffer(GL_ARRAY_BUFFER, plane.lazer_vbo[0]);
	glBufferData(GL_ARRAY_BUFFER,	sizeof(plane.lazer), plane.lazer, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(0);




	glUseProgram(s_program[0]);
	glGenVertexArrays(1, &ballooneline.vao);
	glGenBuffers(2, ballooneline.vbo);


	glBindVertexArray(ballooneline.vao);
	glBindBuffer(GL_ARRAY_BUFFER, ballooneline.vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, ballooneline.vertex.size() * sizeof(glm::vec3), ballooneline.vertex.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(0);



}


GLvoid display()
{


	glDisable(GL_SCISSOR_TEST);

	glClearColor(1.f, 1.f, 1.f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	if (stage == 0)
	{
		GLuint readFboId = 0;
		glGenFramebuffers(1, &readFboId);
		glBindFramebuffer(GL_READ_FRAMEBUFFER, readFboId);
		glFramebufferTexture2D(GL_READ_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
			GL_TEXTURE_2D ,start_img , 0);
		glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);

		// Every time you want to copy the texture to the default framebuffer.
		glBindFramebuffer(GL_READ_FRAMEBUFFER, readFboId);
		glBlitFramebuffer(0, 512, 512, 0,
			0, 0, width, height,
			GL_COLOR_BUFFER_BIT, GL_LINEAR);
		glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);


	
		


	}
	else if (stage==1) {
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_SCISSOR_TEST);


		//왼쪽 
		glViewport(0, 0, height, width);
		glLoadIdentity();

		glScissor(0, 0, height, width);
		glClearColor(0.f, 0.f, 0.f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//주변산란
		unsigned int lightflag = glGetUniformLocation(s_program[0], "flag");
		glUniform1i(lightflag ,0);
		drawScene(0);


		///
		const char* score_str = "Remaining=>";
		char score[100];
		
		sprintf(score, "%d",ballooncount);
		glColor3f(1.0, 1.0, 0.0);

		glRasterPos2f(-1.0, 0.9); //define position on the screen
		while (*score_str) {
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *score_str++);
		}


		glColor3f(1.0, 1.0, 0.0);

		glRasterPos2f(-0.75, 0.9); //define position on the screen
		int i = 0;
		while (score[i]!='\0') {
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, score[i]);
			++i;
		}
		/////////

		const char* hp_str = "HP=>";
		char hp[100];

		sprintf(hp, "%d", plane.hp);
		glColor3f(0.0, 0.0, 0.0);

		glRasterPos2f(-1.0, 0.8); //define position on the screen
		while (*hp_str) {
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *hp_str++);
		}


		glColor3f(0.0, 0.0, 0.0);

		glRasterPos2f(-0.875, 0.8); //define position on the screen
		 i = 0;
		while (hp[i] != '\0') {
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, hp[i]);
			++i;
		}






		//주변 조명만
		// 미니맵
		glViewport(width - width / 4, height - height / 4, width / 4  , height / 4  );
		glLoadIdentity();
		mini_camera_pos = glm::vec3(camera_pos.x,0, camera_pos.z)+glm::vec3(0.0,40+plane.pos.y,0.0);
		mini_camera_dir = plane.pos;

		glScissor(width - width / 4, height - height / 4 , width / 4  , height / 4  );
		glClearColor(0.f, 0.f, 0.f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUniform1i(lightflag, 0);
		drawScene(1);


	
	}
	else if (stage == 2) {//클리어 화면
	GLuint readFboId = 0;
	glGenFramebuffers(1, &readFboId);
	glBindFramebuffer(GL_READ_FRAMEBUFFER, readFboId);
	glFramebufferTexture2D(GL_READ_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
		GL_TEXTURE_2D, clear_img, 0);
	glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);

	// Every time you want to copy the texture to the default framebuffer.
	glBindFramebuffer(GL_READ_FRAMEBUFFER, readFboId);
	glBlitFramebuffer(0, 512, 512, 0,
		0, 0, width, height,
		GL_COLOR_BUFFER_BIT, GL_LINEAR);
	glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);



	}
	else if (stage == 3) {//실패화면
	GLuint readFboId = 0;
	glGenFramebuffers(1, &readFboId);
	glBindFramebuffer(GL_READ_FRAMEBUFFER, readFboId);
	glFramebufferTexture2D(GL_READ_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
		GL_TEXTURE_2D, fail_img, 0);
	glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);

	// Every time you want to copy the texture to the default framebuffer.
	glBindFramebuffer(GL_READ_FRAMEBUFFER, readFboId);
	glBlitFramebuffer(0, 512, 512, 0,
		0, 0, width, height,
		GL_COLOR_BUFFER_BIT, GL_LINEAR);
	glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);



	}

	glutSwapBuffers();
}

//월드 전체를 그려주는 함수
GLvoid drawScene(int flag )
{
	for (int i = 0; i < 2; ++i) {
		glUseProgram(s_program[i]);

		//원근 투영
		glm::mat4 projection = glm::mat4(1.0f);
		projection = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 5000.0f);
		projection = glm::translate(projection, glm::vec3(0.0, 0.0, -5.0f));
		unsigned int projectionLocation = glGetUniformLocation(s_program[i], "projectionTransform");
		glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &projection[0][0]);
		/////////////////////////////////////////////////////////////////////////////////////////

		if (flag==0)//큰 뷰
		{ //카메라 뷰잉
		glm::mat4 view_t = glm::mat4(1.0f);
		view_t = glm::lookAt(camera_pos, camera_dir, camera_up);
		unsigned int viewLocation = glGetUniformLocation(s_program[i], "viewtransform");
		glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view_t[0][0]);
		}
		else {//미니맵뷰
			//카메라 뷰잉
			glm::mat4 view_t = glm::mat4(1.0f);
			view_t = glm::lookAt(mini_camera_pos, mini_camera_dir, mini_camera_up);
			view_t = glm::translate(view_t, glm::vec3(mini_camera_pos.x, 0.f, mini_camera_pos.z));
			view_t = glm::rotate(view_t,glm::radians(180.f), glm::vec3(0.0f, 1.f, 0.0f));
			view_t = glm::translate(view_t, glm::vec3(-mini_camera_pos.x, 0.f, -mini_camera_pos.z));
			unsigned int viewLocation = glGetUniformLocation(s_program[i], "viewtransform");
			glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view_t[0][0]);

		}
		//모델 기본 변환
		glm::mat4 transformMatrix = glm::mat4(1.0f);
		unsigned int transformLoaciton = glGetUniformLocation(s_program[i], "modelTransform");
		glUniformMatrix4fv(transformLoaciton, 1, GL_FALSE, glm::value_ptr(transformMatrix));
	}


		glUseProgram(s_program[0]);
		//조명 위치
		unsigned int lightPosLocation = glGetUniformLocation(s_program[0], "lightPos");
		glUniform3f(lightPosLocation, light_pos.x, light_pos.y, light_pos.z);
		//조명 색깔
		unsigned int lightColorLocation = glGetUniformLocation(s_program[0], "lightColor");
		glUniform3f(lightColorLocation, light_power.x, light_power.y, light_power.z);
		//조명을 위한 카메라 보는 위치 
		unsigned int viewPosLocation = glGetUniformLocation(s_program[0], "viewPos");
		glUniform3f(viewPosLocation, camera_pos.x, camera_pos.y, camera_pos.z);


		///큐브
		DrawSkyBox();

		glUseProgram(s_program[0]);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
		//--- 블렌딩 해제

		//draw 함수들 호출
		DrawPlane();
		DrawMissil();
		DrawBalloon();
		DrawEffect();
		glDisable(GL_BLEND);

}
//객체들을 그려주는 함수들

GLvoid DrawPlane(){

	glUseProgram(s_program[0]);


	
	
	//모델 기본 변환
	glm::mat4 transformMatrix = glm::mat4(1.0f);
	transformMatrix = glm::translate(transformMatrix, glm::vec3(plane.pos.x, plane.pos.y, plane.pos.z));
	transformMatrix = glm::rotate(transformMatrix, glm::radians(180.f+plane.all_coordinare), glm::vec3(0.0f, 1.0f, 0.0f));
	transformMatrix = glm::rotate(transformMatrix, glm::radians(-plane.angle.y), glm::vec3(1.0f, 0.0f, 0.0f));
	transformMatrix = glm::rotate(transformMatrix, glm::radians(-plane.angle.x), glm::vec3(0.0f, 0.0f, 1.0f));
	transformMatrix = glm::scale(transformMatrix, glm::vec3(plane.scale.x, plane.scale.y, plane.scale.z));

	unsigned int transformLoaciton = glGetUniformLocation(s_program[0], "modelTransform");
	glUniformMatrix4fv(transformLoaciton, 1, GL_FALSE, glm::value_ptr(transformMatrix));

	if (plane.lazer_flag)
	{
		unsigned int lightflag = glGetUniformLocation(s_program[0], "flag");
		glUniform1i(lightflag, 1);
		glBindVertexArray(plane.lazer_vao);
		unsigned int objColorLocation = glGetUniformLocation(s_program[0], "objectColor");
		glUniform4f(objColorLocation, 1.0f, 0.0, 0.0,1.0f);
		glDrawArrays(GL_LINES, 0, 2);
		glUniform1i(lightflag, 0);
	}
	glBindVertexArray(plane.model->vao);
	for (int i = 0; i < plane.model->vertexIndex.size(); ++i) {
		

		
			//갈색
		unsigned int objColorLocation = glGetUniformLocation(s_program[0], "objectColor");
		glUniform4f(objColorLocation, plane.color[i].r, plane.color[i].g, plane.color[i].b, plane.stealth);


		glDrawArrays(GL_TRIANGLES, i, 3);

	}
	if (show_crush_flag) 
	{
		DrawSphereCrush(plane.crush_pos[0]+plane.pos, plane.crush_scale[0]);
		DrawSphereCrush(plane.crush_pos[1]+plane.pos, plane.crush_scale[1]);
		DrawSphereCrush(plane.crush_pos[2]+plane.pos, plane.crush_scale[2]);
	}
}

GLvoid DrawSphereCrush(glm::vec3 pos, float length) {


	glUseProgram(s_program[0]);
	glBindVertexArray(sphere->vao);

	unsigned int objColorLocation = glGetUniformLocation(s_program[0], "objectColor");

	//모델 기본 변환
	glm::mat4 transformMatrix = glm::mat4(1.0f);
	transformMatrix = glm::translate(transformMatrix, glm::vec3(pos.x, pos.y, pos.z));
	transformMatrix = glm::scale(transformMatrix, glm::vec3(length, length, length));
	unsigned int transformLoaciton = glGetUniformLocation(s_program[0], "modelTransform");
	glUniformMatrix4fv(transformLoaciton, 1, GL_FALSE, glm::value_ptr(transformMatrix));

	
	
	glUniform4f(objColorLocation, 1.0f, 0.0f, 0.0f,0.5f );


	glDrawArrays(GL_TRIANGLES, 0, sphere->vertexIndex.size());
	
}

GLvoid DrawBalloon() {

	glUseProgram(s_program[0]);
	

	unsigned int objColorLocation = glGetUniformLocation(s_program[0], "objectColor");
	

	b_move = b_head;
	glLineWidth(3.f);
	while (b_move != nullptr) {

	
		glUniform4f(objColorLocation, b_move->color.r, b_move->color.g, b_move->color.b, 1.0f);
		//모델 기본 변환
		glm::mat4 transformMatrix = glm::mat4(1.0f);
		transformMatrix = glm::translate(transformMatrix, glm::vec3(b_move->pos.x, b_move->pos.y, b_move-> pos.z));
		transformMatrix = glm::scale(transformMatrix, glm::vec3(b_move->size, b_move->size, b_move->size));
		unsigned int transformLoaciton = glGetUniformLocation(s_program[0], "modelTransform");
		glUniformMatrix4fv(transformLoaciton, 1, GL_FALSE, glm::value_ptr(transformMatrix));



		unsigned int lightflag = glGetUniformLocation(s_program[0], "flag");
		glUniform1i(lightflag, 0);
		glBindVertexArray(sphere->vao);
		glDrawArrays(GL_TRIANGLES, 0, sphere->vertexIndex.size());


		glUniform1i(lightflag, 0);
		glUniform4f(objColorLocation, b_move->color.r, b_move->color.g, b_move->color.b,0.9f);
		transformMatrix = glm::mat4(1.0f);
		transformMatrix = glm::translate(transformMatrix, glm::vec3(b_move->pos.x, b_move->pos.y-b_move->size*0.5- pyramid->max.y/2, b_move->pos.z));
		transformMatrix = glm::scale(transformMatrix, glm::vec3(0.3f, 0.5f, 0.3f));
		transformMatrix = glm::scale(transformMatrix, glm::vec3(b_move->size, b_move->size, b_move->size));
		glUniformMatrix4fv(transformLoaciton, 1, GL_FALSE, glm::value_ptr(transformMatrix));

		glBindVertexArray(pyramid->vao);
		glDrawArrays(GL_TRIANGLES, 0, pyramid->vertexIndex.size());
		//줄

		glUniform1i(lightflag, 1);
		glUniform4f(objColorLocation, 0.0,0.0,0.0,1.0f);
		glBindVertexArray(ballooneline.vao);
		glDrawArrays(GL_LINE_STRIP, 0, ballooneline.vertex.size());
		b_move = b_move->next;
	}
	glLineWidth(1.f);
}

GLvoid DrawEffect() {

	glUseProgram(s_program[0]);


	unsigned int objColorLocation = glGetUniformLocation(s_program[0], "objectColor");


	e_move = e_head;

	while (e_move != nullptr){


		//모델 기본 변환
		for (int i = 0; i < 3; i++) {
			glUniform4f(objColorLocation, 0.5f+0.1f*i, 0.1f * i, 0.0f, 0.5f - i * 0.1f);
			glm::mat4 transformMatrix = glm::mat4(1.0f);
			transformMatrix = glm::translate(transformMatrix, glm::vec3(e_move->pos.x, e_move->pos.y, e_move->pos.z));

			for (int j = 0; j < i + 1; j++) {
			transformMatrix = glm::scale(transformMatrix, glm::vec3(e_move->size, e_move->size, e_move->size));
			}
			unsigned int transformLoaciton = glGetUniformLocation(s_program[0], "modelTransform");
			glUniformMatrix4fv(transformLoaciton, 1, GL_FALSE, glm::value_ptr(transformMatrix));

			unsigned int lightflag = glGetUniformLocation(s_program[0], "flag");
			glUniform1i(lightflag, 1);
			glBindVertexArray(sphere->vao);
			glDrawArrays(GL_TRIANGLES, 0, sphere->vertexIndex.size());

		}





	
		e_move = e_move->next;
	}
	unsigned int lightflag = glGetUniformLocation(s_program[0], "flag");
	glUniform1i(lightflag, 0);
}

GLvoid DrawSkyBox() {
	//front  right  left  back  bottom
	glUseProgram(s_program[1]);
	glBindVertexArray(box->vao);

	glm::mat4 transformMatrix = glm::mat4(1.0f);
	//transformMatrix = glm::rotate(transformMatrix,glm::radians(180.f), glm::vec3(0.0f,1.0f, 0.0f));
	transformMatrix = glm::rotate(transformMatrix, glm::radians(180.f), glm::vec3(0.0f, 0.0f, 1.0f));
	transformMatrix = glm::scale(transformMatrix, glm::vec3(drawboxsize, drawboxsize, drawboxsize));


	//glm::mat4 sidewall = glm::mat4(1.0f);
	//sidewall = glm::rotate(sidewall, glm::radians(90.f), glm::vec3(0.0f, 1.0f, 0.0f));
	//sidewall *= transformMatrix;

	for (int i = 0; i < box->vertex.size(); ++i) {
		// 0 ->bottom,  1-> top
		if (i % 6 == 0)
		{
			if ( i / 6 == 1) { //90도
				glm::mat4 sidewall = glm::mat4(1.0f);
				sidewall = glm::rotate(sidewall, glm::radians(270.f), glm::vec3(0.0f, 1.0f, 0.0f));
				sidewall *= transformMatrix;

				unsigned int transformLoaciton = glGetUniformLocation(s_program[1], "modelTransform");
				glUniformMatrix4fv(transformLoaciton, 1, GL_FALSE, glm::value_ptr(sidewall));

				glBindTexture(GL_TEXTURE_2D, texture[i / 6]);
				glDrawArrays(GL_TRIANGLES, i, 6);
			}
			else if(i / 6 == 0) { //270도
				glm::mat4 sidewall = glm::mat4(1.0f);
				sidewall = glm::rotate(sidewall, glm::radians(90.f), glm::vec3(0.0f, 1.0f, 0.0f));
				sidewall *= transformMatrix;

				unsigned int transformLoaciton = glGetUniformLocation(s_program[1], "modelTransform");
				glUniformMatrix4fv(transformLoaciton, 1, GL_FALSE, glm::value_ptr(sidewall));

				glBindTexture(GL_TEXTURE_2D, texture[i / 6]);
				glDrawArrays(GL_TRIANGLES, i, 6);
			}
			else {


				unsigned int transformLoaciton = glGetUniformLocation(s_program[1], "modelTransform");
				glUniformMatrix4fv(transformLoaciton, 1, GL_FALSE, glm::value_ptr(transformMatrix));
				glBindTexture(GL_TEXTURE_2D, texture[i / 6]);
				glDrawArrays(GL_TRIANGLES, i, 6);
			}
		}
	

	}
}

GLvoid DrawMissil() {


	glUseProgram(s_program[0]);
	m_move = m_head;
	while (m_move != nullptr) {
		unsigned int objColorLocation = glGetUniformLocation(s_program[0], "objectColor");

		//모델 기본 변환
		glm::mat4 transformMatrix = glm::mat4(1.0f);
		transformMatrix = glm::translate(transformMatrix, glm::vec3(m_move->pos.x, m_move->pos.y, m_move->pos.z));
		transformMatrix = glm::rotate(transformMatrix, glm::radians(180.f+m_move->roate_xz), glm::vec3(0.0f, 1.0f, 0.0f));//비행기방향과 일치
	
		transformMatrix = glm::rotate(transformMatrix, glm::radians(m_move->roate_zy), glm::vec3(0.0f, 0.0f, 1.0f));//비행기방향과 일치
	
		transformMatrix = glm::translate(transformMatrix, glm::vec3(-0.55f, 0.0f,0.0f));
		//transformMatrix = glm::scale(transformMatrix, glm::vec3(1, 1, 1));
		unsigned int transformLoaciton = glGetUniformLocation(s_program[0], "modelTransform");
		glUniformMatrix4fv(transformLoaciton, 1, GL_FALSE, glm::value_ptr(transformMatrix));



			glUniform4f(objColorLocation, 0.0f, 0.0f, 0.0f,0.8f);
			glBindVertexArray(missil->vao);
			glDrawArrays(GL_TRIANGLES, 0, missil->vertexIndex.size());

		if (show_crush_flag)
		{
			glUniform3f(objColorLocation, 1.0f, 0.0f, 0.0f);
			DrawSphereCrush(m_move->pos+glm::vec3(0.0f, +0.4f, -0.1f), 0.7f);
		
		}

		m_move = m_move->next;
	}
}




GLvoid UpdateCamera() {

	float x = 0;
	float z = 0;
	
	camera_pos = plane.pos + camera_control+camera_y_pos;


	camera_dir = plane.pos + glm::vec3(0.0, 0.0f, 0.0f);

	//light_pos = plane.pos + camera_control + camera_y_pos;
}



GLvoid all_update(int value) {

	plane.update(camera_control ,camera_y_pos);
	UpdateCamera();
	b_move = b_head;
	while (b_move != nullptr) {
		b_move->update(plane.pos);
		if (plane.plane_crush_check(b_move->pos, b_move->size * ballsize))
		{
			PlaySound("balloon.wav", 0, SND_FILENAME | SND_ASYNC);
			glm::vec3 dir_m2b = b_move->pos - plane.pos;
			dir_m2b = dir_m2b / abs(dir_m2b);

			glm::vec3 point_m2b = plane.pos + dir_m2b * glm::vec3(0.7f, 0.7f, 0.7f);
			makeeffect(point_m2b);
			PlaySound("balloon.wav", 0, SND_FILENAME | SND_ASYNC);
			delballoon(b_move);

			plane.hp--;
			break;
		}
		b_move = b_move->next;
	}

	m_move = m_head;
	while (m_move != nullptr) {
		m_move->update();
		b_move = b_head;
		while (b_move != nullptr) {
			if ((0.7+b_move->size)*ballsize>TwopointDistance(m_move->pos+ glm::vec3(0.0f, +0.4f, -0.1f), b_move->pos))
			{
				//미사일에서 출발해서 풍선으로 가는 백터
				glm::vec3 dir_m2b = b_move->pos - m_move->pos;
				dir_m2b = dir_m2b / abs(dir_m2b);

				glm::vec3 point_m2b= m_move->pos+ dir_m2b*glm::vec3(0.7f, 0.7f, 0.7f);
				makeeffect(point_m2b);
				PlaySound("balloon.wav", 0, SND_FILENAME | SND_ASYNC);
				delballoon(b_move);
				break;
			}
			b_move = b_move->next;
		}
		if (500< TwopointDistance(plane.pos, m_move->pos))
		{
			MISSIL* temp = m_move;
			m_move = m_move->next;
			delmissil(temp);
		}
		else {
			m_move = m_move->next;
		}
	}


	//effect
	e_move = e_head;
	while (e_move != nullptr) {

		e_move->update();

		if (e_move->size > 2.0) {
			BOMB* temp = e_move;
			e_move = e_move->next;
			deleffect(temp);
		}
		else {
			e_move = e_move->next;
		}
	}

	if (endingflag) {
		if (ballooncount < 1)
		{
			stage = 2;

			mciSendCommandW(dwID, MCI_PAUSE, MCI_NOTIFY,
				(DWORD)(LPVOID)&m_mciPlayParms);


			mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE,
				(DWORD)(LPVOID)&mciOpen3);

			dwID = mciOpen3.wDeviceID;

			mciSendCommand(dwID, MCI_PLAY, MCI_DGV_PLAY_REPEAT, // play & repeat
				(DWORD)(LPVOID)&m_mciPlayParms);
			endingflag = 0;

		}
		if (plane.hp < 1)
		{
			stage = 3;
			mciSendCommandW(dwID, MCI_PAUSE, MCI_NOTIFY,
				(DWORD)(LPVOID)&m_mciPlayParms);


			mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE,
				(DWORD)(LPVOID)&mciOpen4);

			dwID = mciOpen4.wDeviceID;

			mciSendCommand(dwID, MCI_PLAY, MCI_DGV_PLAY_REPEAT, // play & repeat
				(DWORD)(LPVOID)&m_mciPlayParms);


			endingflag = 0;
		}


	
	}
	glutPostRedisplay();
	glutTimerFunc(1, all_update, 1);
	
}




GLvoid ReShape(int w, int h)
{
	glViewport(0, 0, w, h);
}
void createrender()
{
	if (head == nullptr)
	{
		head = new render;
		curmove = head;
		premove = curmove;

	}
	else
	{
		curmove = new render;
		premove->next = curmove;
		premove = curmove;
	}
}



GLvoid specialdown(int key, int x, int y)
{
	if (stage == 1)
	{
		if (key == GLUT_KEY_UP) {
			plane.dir.z -= 1.0f;
		}

		if (plane.dir.z != 0) {
			if (key == GLUT_KEY_RIGHT)
			{
				plane.dir.x += 1.0f;
			}

			if (key == GLUT_KEY_LEFT)
			{

				plane.dir.x -= 1.0f;

			}
			if (key == GLUT_KEY_DOWN) {

				plane.dir.z += 1.0f;
			}

			if (key == GLUT_KEY_CTRL_L)// Y축으로 올라가기
			{
				plane.dir.y += 1.0f;
			}
			if (key == GLUT_KEY_SHIFT_L)// Y축으로 내려가기
			{
				plane.dir.y -= 1.0f;
			}



		}
		UpdateCamera();
	}
	glutPostRedisplay();
}
GLvoid specialup(int key, int x, int y) {

	if (stage == 1) {
		if (key == GLUT_KEY_UP) {
			plane.dir.z += 1.0f;
		}


		if (key == GLUT_KEY_RIGHT)
		{
			plane.dir.x = 0.f;
		}
		if (key == GLUT_KEY_LEFT)
		{
			plane.dir.x = 0.f;
		}
		if (key == GLUT_KEY_DOWN) {

			plane.dir.z = 0.f;
		}
		if (key == GLUT_KEY_CTRL_L)// Y축으로 올라가기
		{
			plane.dir.y = 0.f;
		}
		if (key == GLUT_KEY_SHIFT_L)// Y축으로 내려가기
		{
			plane.dir.y = 0.f;
		}

	UpdateCamera();
	}


	glutPostRedisplay();

}
void key_borad(unsigned char key, int x, int y) {

	if (stage == 0) {
	if (key == 13)
	{
		stage = 1;
		mciSendCommandW(dwID, MCI_PAUSE, MCI_NOTIFY,
			(DWORD)(LPVOID)&m_mciPlayParms);


		mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE,
			(DWORD)(LPVOID)&mciOpen2);

		dwID = mciOpen2.wDeviceID;

		mciSendCommand(dwID, MCI_PLAY, MCI_DGV_PLAY_REPEAT, // play & repeat
			(DWORD)(LPVOID)&m_mciPlayParms);


	}

	}
	else {

	switch (key) {
	case 'r':
		if (plane.lazer_flag) {
			plane.lazer_flag = 0;
		}
		else 
		{

			plane.lazer_flag = 1;
		}
		break;
	case 'c':
		if (show_crush_flag) {
			show_crush_flag = 0;
		}
		else {
			show_crush_flag = 1;
		}
		break;
	case 'a':
			makemissil();
			PlaySound("laserver1.wav", 0, SND_FILENAME | SND_ASYNC);

	break;
	case '+':
		plane.stealth += 0.1f;
		if (plane.stealth>1.1f) {
			plane.stealth -= 0.1f;
		}
		break;
	case '-':
		plane.stealth -= 0.1f;
		if (plane.stealth < 0.0) {
			plane.stealth += 0.1f;
		}
		break;

	}
	}
	if (key == 'q')
	{
		exit(0);
	}
	glutPostRedisplay();
}

void makemissil() {

	if (m_head == nullptr) {

		m_head = new MISSIL(plane.pos, plane.planedir,plane.all_coordinare, plane.angle.y);
		m_curmove = m_head;
		m_premove = m_curmove;

	}
	else
	{
		m_curmove = new MISSIL(plane.pos, plane.planedir,plane.all_coordinare, plane.angle.y);
		m_premove->next = m_curmove;
		m_premove = m_curmove;
	}
}

void makeballoon()
{
	if (b_head == nullptr) {

		b_head = new Balloon;
		b_curmove = b_head;
		b_premove = b_curmove;

	}
	else
	{
		b_curmove = new Balloon;
		b_premove->next = b_curmove;
		b_premove = b_curmove;
	}
	ballooncount++;
	b_curmove->init(plane.pos);
}

void delballoon(Balloon *o) {
	Balloon* temp = nullptr;

	if (o == b_head)
	{
		temp = b_head->next;
		delete b_head;
		b_head = temp;
	}
	else if(o->next==nullptr)
	{
		b_delmove = b_head;
		while (b_delmove->next != o)
		{
			b_delmove = b_delmove->next;
		}
		b_delmove->next = nullptr;
		delete o;
	}
	else
	{
		b_delmove = b_head;
		while (b_delmove->next!=o)
		{
			b_delmove = b_delmove->next;
		}
		b_delmove->next = o->next;
		delete o;
	}
	ballooncount--;
}

void delmissil(MISSIL* o) {
	MISSIL* temp = nullptr;

	if (o == m_head)
	{
		temp = m_head->next;
		delete m_head;
		m_head = temp;
	}
	else if (o->next == nullptr)
	{
		m_delmove = m_head;
		while (m_delmove->next != o)
		{
			m_delmove = m_delmove->next;
		}
		m_curmove = m_delmove;
		m_premove = m_delmove;
		m_delmove->next = nullptr;
		delete o;
	}
	else
	{
		m_delmove = m_head;
		while (m_delmove->next != o)
		{
			m_delmove = m_delmove->next;
		}
		m_delmove->next = o->next;
		delete o;
	}
}

void makeeffect(glm::vec3 o) {

	if (e_head == nullptr) {

		e_head = new BOMB(o);
		e_curmove = e_head;
		e_premove = e_curmove;

	}
	else
	{
		e_curmove = new BOMB(o);
		e_premove->next = e_curmove;
		e_premove = e_curmove;
	}
}

void deleffect(BOMB* o) {
	BOMB* temp = nullptr;

	if (o == e_head)
	{
		temp = e_head->next;
		delete e_head;
		e_head = temp;
	}
	else if (o->next == nullptr)
	{
		e_delmove = e_head;
		while (e_delmove->next != o)
		{
			e_delmove = e_delmove->next;
		}
		e_curmove = e_delmove;
		e_premove = e_delmove;
		e_delmove->next = nullptr;
		delete o;
	}
	else
	{
		e_delmove = e_head;
		while (e_delmove->next != o)
		{
			e_delmove = e_delmove->next;
		}
		e_delmove->next = o->next;
		delete o;
	}
}


