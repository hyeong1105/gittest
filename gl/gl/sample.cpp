#include "sample.h"

#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <glm\glm.hpp>




void DataLoad::loadData(){

	std::ifstream in;
	int c = 0;
	int d = 0;
	int Xcount = 0;
	int Ycount = 0;
	bool readingX = true;
	double w = 0;
	double x = 0;
	double y = 0;
	double z = 0;
	int count = 0;
	in.open("User/00003.txt");

	char str; // 텍스트파일의 길이 만큼의 문자형 배열을 만듬

	while (in.good())
	{
		str = in.get();	// 텍스트 글자별로 읽어드림
		if (str == '+')
		{
			w = 1;
		}
		else if (str == '-')
		{
			w = -1;
		}
		else if (count == 4)
		{
			count = -1;
		}
		else if (str == 'C')
		{
			break;
		}
		else
		{
			if (count == 1){
				x = atoi(&str); // char형을 int형으로 형변환
			}
			else if (count == 2){
				y = atoi(&str); // char형을 int형으로 형변환
			}
			else if (count == 3)
			{
				z = atoi(&str); // char형을 int형으로 형변환
				if (d == 0)
				{
					balanceData[Xcount][d] = (x * 100 + y * 10 + z)*w;
					Xcount++;
					d++;
				}
				else if (d == 1)
				{
					balanceData[Ycount][d] = (x * 100 + y * 10 + z)*w;
					Ycount++;
					d--;
				}
			}
		}
		count++;
	}

	for (int i = 0; i < 4000; i++)
	{
		smoothedData[i][0] = balanceData[i][0];
		smoothedData[i][1] = balanceData[i][1];
		balanceData1[i * 2] = balanceData[i][0];
		balanceData1[i * 2 + 1] = balanceData[i][1];

		//vertex.push_back(glm::vec2(0, 0));

		Xc = +2;
		Yc = +2;
	}
	in.close();
	Xc = 0;
	Yc = 1;
}

void DataLoad::DataSmoothed()
{
	for (int i = 0; i < 4000; i++)
	{
		int p = i - 1;
		int n = i + 1;
		double midX, midY;
		if (p >= 0 && n < 4000)
		{
			midX = (smoothedData[p][0] + smoothedData[n][0]) / 2.0;
			midY = (smoothedData[p][1] + smoothedData[n][1]) / 2.0;
			smoothedData2[i][0] = (smoothedData[i][0] + midX) * 0.5;
			smoothedData2[i][1] = (smoothedData[i][1] + midY) * 0.5;
		}
	}

	for (int i = 0; i < 4000; i++) // 버텍스 버퍼를 사용하기 위해 1차원 배열로 정리
	{
		smoothedData1[Xc] = smoothedData[i][0];
		smoothedData1[Yc] = smoothedData[i][1];
		Xc = +2;
		Yc = +2;
	}

}

///////////////////////// OpenGL ////////////////////////////////////
void DataLoad::renderScence(void)
{
	glClear(GL_COLOR_BUFFER_BIT || GL_DEPTH_TEST);

	glViewport(0, 0, 800, 800);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(-1.f, 1.f, -1.f, 1.f, -1.f, 1.f);

	//gluPerspective(45, 1, 0.01, 1000);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// 버텍스 버퍼 사용

	//glEnableClientState(GL_VERTEX_ARRAY);
	//glVertexPointer()
	//glDrawArrays();
	//glDisableClientState(GL_VERTEX_ARRAY);

	Background();
	//	DrawQuad();
	DrawGraph();
	DrawData();

	glutSwapBuffers();

}

void DataLoad::init()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//glOrtho(-1.f, 1.f, -1.f, 1.f, -1.f, 1.f);
	//gluPerspective(45, 1, 0.01, 1000);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}

////////////////////////// DRAW ////////////////////////////////////

void DataLoad::DrawData()
{
	std::vector<glm::vec2> vertex;

	for (int i = 0; i < 4000; i++)
	{
		this->LoadData_point[i] = balanceData1[i] / 20;
		//this->LoadData_Balancepoint[i][0] = smoothedData[i][0] *0.05;
		//this->LoadData_Balancepoint[i][1] = smoothedData[i][1] *0.05;
		//this->LoadData_Smoothedpoint[i][0] = smoothedData2[i][0] *0.05;
		//this->LoadData_Smoothedpoint[i][1] = smoothedData2[i][1] *0.05;  // 여기 오타
	}
	// 버텍스 버퍼 사용


	//	vertex.size();

	glPointSize(2.0f);

	glEnableClientState(GL_VERTEX_ARRAY);
	glColor3f(0.f, 1.f, 0.f);
	glVertexPointer(2, GL_DOUBLE, 0, &LoadData_point);
	glDrawArrays(GL_POINTS, 0, 4000);
	glDisableClientState(GL_VERTEX_ARRAY);

	glPointSize(4.0f);

	//glBegin(GL_LINE_STRIP);
	//glColor3f(1.f, 0.f, 0.f);
	//for (int i = 0; i < 4000; i++)
	//{
	//	glVertex3f(LoadData_point[i*2], LoadData_point[i*2+1], 0);
	////	glVertex3f(LoadData_Balancepoint[i][0], LoadData_Balancepoint[i][1], 0);
	////	glVertex3f(LoadData_Smoothedpoint[i][0], LoadData_Smoothedpoint[i][1], 0);
	//}

	//glEnd();

	//glColor3f(1, 0.0, 0.0);
	//glutSolidSphere(1, 100, 100);
}

void DataLoad::DrawGraph(){


	gluLookAt(0, 0, 1,  // 카메라 위치
		0, 0, 0,	// 카메라 보는 위치
		0, 1, 0);  // 카메라 업벡터

	glBegin(GL_LINES);
	glColor3f(1.f, 1.f, 1.f);
	for (float i = -1; i < 1.1; i += 0.05)
	{
		glVertex3f(i, 1.0, 0.0);
		glVertex3f(i, -1.0, 0.0);
	}
	for (float i = -1.0; i < 1.01; i += 0.05)
	{
		glVertex3f(-1.0, i, 0.f);
		glVertex3f(1.0, i, 0.f);
	}
	glColor3f(0.f, 0.f, 1.f);
	glVertex3f(0.f, 1.f, 0.f);
	glVertex3f(0.f, -1.f, 0.f);
	glColor3f(0.f, 1.f, 0.f);
	glVertex3f(1.f, 0.f, 0.f);
	glVertex3f(-1.f, 0.f, 0.f);
	glEnd();

}

void DataLoad::Background()
{
	glBegin(GL_QUADS);
	glColor3f(0.8f, 0.8f, 0.8f);
	glVertex3f(-1.f, -1.f, 0.f);
	glVertex3f(1.f, -1.f, 0.f);
	glVertex3f(1.f, 1.f, 0.f);
	glVertex3f(-1.f, 1.f, 0.f);
	glEnd();
}

void DataLoad::DrawQuad()
{
	glBegin(GL_QUADS);
	glColor3f(1.f, 1.f, 1.f);
	glVertex3f(-1.0, 1.0, 0.0);
	glVertex3f(-1.0, -0.5, 0.0);
	glVertex3f(0.5, -0.5, 0.0);
	glVertex3f(0.5, 1.0, 0.0);
	glEnd();
}

/////////////////////////////////////////////////////////////////////
