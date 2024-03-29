#include "coordinate.h"

Coordinate::Coordinate() {
	coordinate = new Vector3 * [10];
	full = new bool* [10];
	for (int i = 0; i < 10; i++) {
		if (i % 2 == 0) {
			coordinate[i] = new Vector3[10];
			full[i] = new bool[10];
			for (int j = 0; j < 10; j++) {
				coordinate[i][j] = Vector3(-180 + 2 * j * COORX, 180 - i * COORY, 0);
				full[i][j] = false;
			}
		}
		else {
			coordinate[i] = new Vector3[9];
			full[i] = new bool[9];
			for (int j = 0; j < 9; j++) {
				coordinate[i][j] = Vector3(-160 + 2 * j * COORX, 180 - i * COORY, 0);
				full[i][j] = false;
			}
		}
	}

	
}

Coordinate::~Coordinate() {
	for (int i = 0; i < 10; i++) {
		delete[]coordinate[i];
		delete[]full[i];
	}
	delete[]coordinate;
	delete[]full;

}

Vector3 Coordinate::XYtoMatrix(const Vector3& v) {
	int row = (180.0 - v.getXYZ()[1]) / COORY;
	int column;
	if (row % 2 == 0)
		column = (180.0 + v.getXYZ()[0]) / (2 * COORX);
	else
		column = (160.0 + v.getXYZ()[0]) / (2 * COORX);
	return Vector3(row, column, 0);
}

bool Coordinate::isfull(const Vector3& v) {
	int x, y;
	x = XYtoMatrix(v)[0];
	y = XYtoMatrix(v)[1];
	return full[x][y];
}

Vector3 Coordinate::search(const Vector3& ball,const Vector3& collisionBall) {
	Vector3 position;
	Vector3 near[6]; //충돌한 공 주변의 6개 공
	near[0].setXYZ(collisionBall[0] - COORX, collisionBall[1] + COORY, 0);
	near[1].setXYZ(collisionBall[0] + COORX, collisionBall[1] + COORY, 0);
	near[2].setXYZ(collisionBall[0] + 2 * COORX, collisionBall[1], 0);
	near[3].setXYZ(collisionBall[0] + COORX, collisionBall[1] - COORY, 0);
	near[4].setXYZ(collisionBall[0] - COORX, collisionBall[1] - COORY, 0);
	near[5].setXYZ(collisionBall[0] - 2 * COORX, collisionBall[1], 0);
	float min = 4*COORX*COORX;  //공지름^2(=최대거리^2)
	for (int i = 0; i < 6; i++) {
		float distance = dotProduct(near[i]-ball,near[i]-ball);  //주변6개 공과 쏘아진 공의 중심 사이 거리 계산
		if (distance < min ) {  //최소거리 탐색
			position = near[i];  //좌표 대입
			min = distance; //거리 대입
		}
	}
	return position;  //가장 가까운 거리에 있는 공의 중심 좌표 return
}

void Coordinate::setfull(const Vector3& v) {
	int x, y;
	x = XYtoMatrix(v)[0];
	y = XYtoMatrix(v)[1];
	full[x][y] = true;
}

void Coordinate::setempty(const Vector3& v) {
	int x, y;
	x = XYtoMatrix(v)[0];
	y = XYtoMatrix(v)[1];
	full[x][y] = false;
}

Vector3 Coordinate::upper(Vector3& ball) {
	float min = 2 * COORX;
	int ballX=0;
	for (int x = -180; x <= 180; x += 40) {
		float distance = x - ball.getXYZ()[0];
		
		if (distance * distance < min * min) {
			min = distance;
			ballX = x;
		}
		//ball.setXYZ(ballX, 180, 0);
		
	}
	return Vector3(ballX, 180, 0);
}