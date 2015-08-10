#ifndef DATALOAD_H_
#define DATALOAD_H_

#include <gl\freeglut.h>

#define X1 -0.25
#define Y1 +0.25

class DataLoad{
public:
	int Xc = 0;
	int Yc = 1;

	bool loaded = false;
	double balanceData[4000][2];
	double smoothedData[4000][2];
	double smoothedData2[4000][2];
	double balanceData1[8000];
	double smoothedData1[8000];
	void loadData();
	void DataSmoothed();
	GLfloat LoadData_point[8000];
	GLfloat LoadData_Balancepoint[4000][2];
	GLfloat LoadData_Smoothedpoint[4000][2];
	void renderScence(void);
	void Background();
	void DrawData();
	void DrawGraph();
	void DrawQuad();
	void DrawSphere();
	void init();
};
#endif