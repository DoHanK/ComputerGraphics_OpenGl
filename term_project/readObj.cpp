#include "readObj.h"

int render:: readobj_file(const char* file)
{
	glm::vec3 temp;
	GLuint garbage = 0;
	char count[100];
	FILE* objFile;
	objFile = fopen(file, "rb");

	if (!objFile) /* Return NULL on failure */
	{
		std::cout << "can't find file\n";
		return 0;
	}
	else
		std::cout << "called obj file\n";


	char bind[100];



	//�ʿ�� ��� ���� Ŀ���� 0���� �Ű���
	//fseek(objFile, 0, SEEK_SET);

	while (!feof(objFile))
	{
		fscanf(objFile, "%s", bind);

	
		if (bind[0] == 'v' && bind[1] == '\0')
		{	
		

			fscanf(objFile, "%f %f %f", &temp.x, &temp.y, &temp.z);
			if (temp.x < min.x)min.x = temp.x;  //�Ը� -1~1���̷� ������ֱ� ���ؼ� �ִ� �ּҰ� ã��
			if (temp.x > max.x) max.x = temp.x;
			if (temp.y < min.y)	min.y =temp.y;
			if (temp.y > max.y)max.y =temp.y;
			if (temp.z < min.z)	min.z = temp.z;
			if (temp.z > max.y)max.z = temp.z;
			temp_vertex.emplace_back(temp);
		}
		else if (bind[0] == 'v' && bind[1] == 'n' && bind[2] == '\0')
		{
			fscanf(objFile, "%f %f %f", &temp.x, &temp.y, &temp.z);

			temp_normal.emplace_back(temp);
		
		}
		else if (bind[0] == 'v' && bind[1] == 't' && bind[2] == '\0')
		{
			glm::vec2 temp_vt;
			fscanf(objFile, "%f %f %f", &temp_vt.x, &temp_vt.y, &garbage);


			temp_uv.emplace_back(temp_vt);

		}
		else if (bind[0] == 'f' && bind[1] == '\0')
		{
			unsigned int v_i[3], uv_i[3], n_i[3];

			fscanf(objFile, "%d/%d/%d %d/%d/%d %d/%d/%d  ", 
				&v_i[0] , &uv_i[0] ,& n_i[0],
				&v_i[1], &uv_i[1], &n_i[1] ,
				&v_i[2], &uv_i[2], &n_i[2]);


			vertexIndex.emplace_back(v_i[0]);
			vertexIndex.emplace_back(v_i[1]);
			vertexIndex.emplace_back(v_i[2]);
			uvIndex.emplace_back(uv_i[0]);
			uvIndex.emplace_back(uv_i[1]);
			uvIndex.emplace_back(uv_i[2]);
			normalIndex.emplace_back(n_i[0]);
			normalIndex.emplace_back(n_i[1]);
			normalIndex.emplace_back(n_i[2]);


		}


	}


	//������ ����ȭ�� ���� ���
	obj_size = max - min;

	max_legth= (obj_size.x > obj_size.y) ? obj_size.x : obj_size.y;
	max_legth = (obj_size.x > obj_size.z) ? obj_size.x : obj_size.z;

	max = max / max_legth;
	min = min / max_legth;
	//vertex��
	for (unsigned int i = 0; i < vertexIndex.size(); i++) {
		int index = vertexIndex[i]-1;
		vertex.emplace_back(temp_vertex[index]/max_legth);

	}
	//uv��
	for (unsigned int i = 0; i < uvIndex.size(); i++) {
		int index = uvIndex[i] - 1;
		uv.emplace_back(temp_uv[index]);

	}

	//vn��
	for (unsigned int i = 0; i < normalIndex.size(); i++) {
		int index = normalIndex[i] - 1;
		normal.emplace_back(temp_normal[index]);

	}

}





