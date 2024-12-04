#include "readObj.h"
#include "shader.h"
#define width 800
#define height 600


GLvoid ReShape(int w, int h);
GLvoid drawScene();
void InitBuffer();


render* head = nullptr;
render* curmove = nullptr;
render* premove = nullptr;
render* move = nullptr;
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



glm::vec3 camera_pos = glm::vec3(0.0f, 1.0f, 1.0f);
glm::vec3 camera_dir = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 camera_up = glm::vec3(0.0f, 1.0f, 0.0f);
glm::vec3 light_pos = glm::vec3(0.0f, 1.0f, 5.0f);
glm::vec3 light_power = glm::vec3(1.0f, 1.0f, 1.0f);



int main(int argc, char** argv)
{

	createrender();
	curmove->readobj_file("box.obj");

	
	


	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(width, height);
	glutCreateWindow("숙제");

	glewExperimental = GL_TRUE;
	glewInit();

	InitShader();
	InitBuffer();




	glutDisplayFunc(drawScene);

	glutReshapeFunc(ReShape);

	

	glutMainLoop();
}


void InitBuffer()
{
	move = head;
	//vao 젠한다.
	while (move != nullptr)
	{
		
			glGenVertexArrays(1, &move->vao);
			glGenBuffers(2, move->vbo);
			//glGenBuffers(1, &move->ebo);
			
		

		//정점 버퍼 저장
		glBindVertexArray(move->vao);
		glBindBuffer(GL_ARRAY_BUFFER, move->vbo[0]);
		glBufferData(GL_ARRAY_BUFFER, move->vertex.size() * sizeof(glm::vec3), move->vertex.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), 0);
		glEnableVertexAttribArray(0);

		//법선 백터
		glBindBuffer(GL_ARRAY_BUFFER, move->vbo[1]);
		glBufferData(GL_ARRAY_BUFFER, move->normal.size() * sizeof(glm::vec3), move->normal.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		glEnableVertexAttribArray(1);

		move = move->next;
	}


}

GLvoid drawScene()
{


	InitBuffer();

	glClearColor(0.f, 0.f, 0.f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glEnable(GL_DEPTH_TEST);


	

	glUseProgram(s_program);

	//원근 투영
	glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 100.0f);
	projection = glm::translate(projection, glm::vec3(0.0, 0.0, -5.0f));
	unsigned int projectionLocation = glGetUniformLocation(s_program, "projectionTransform");
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &projection[0][0]);
	/////////////////////////////////////////////////////////////////////////////////////////


	//카메라 뷰잉
	glm::mat4 view_t = glm::mat4(1.0f);
	view_t = glm::lookAt(camera_pos, camera_dir, camera_up);
	unsigned int viewLocation = glGetUniformLocation(s_program, "viewtransform");
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view_t[0][0]);






	//랜더링 파이프라인에 세이더 불러오기



	move = head;

	while (move != nullptr)
	{


		//사용할 VAO불러오기

		glUseProgram(s_program);

		
		glm::mat4 transformMatrix = glm::mat4(1.0f);
		unsigned int transformLoaciton = glGetUniformLocation(s_program, "modelTransform");
		glUniformMatrix4fv(transformLoaciton, 1, GL_FALSE, glm::value_ptr(transformMatrix));

		unsigned int lightPosLocation = glGetUniformLocation(s_program, "lightPos");
		glUniform3f(lightPosLocation, light_pos.x, light_pos.y, light_pos.z);

		unsigned int lightColorLocation = glGetUniformLocation(s_program, "lightColor");
		glUniform3f(lightColorLocation, light_power.x, light_power.y, light_power.z);

		unsigned int objColorLocation = glGetUniformLocation(s_program, "objectColor");
		glUniform3f(objColorLocation, 1.0, 0.5, 0.3);

		unsigned int viewPosLocation = glGetUniformLocation(s_program, "viewPos");
		glUniform3f(viewPosLocation, camera_pos.x, camera_pos.y, camera_pos.z);

	
	glBindVertexArray(move->vao);

	glDrawArrays(GL_TRIANGLES, 0, move->vertexIndex.size());
		

		move = move->next;
	}

	glutSwapBuffers();
}

GLvoid ReShape(int w, int h)
{
	glViewport(0, 0, w, h);
}