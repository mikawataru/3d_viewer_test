#include "view_engine.h"

/******************************* vector2Dクラス *************************************/

vector2D::vector2D(double X, double Y) :x(X),y(Y) {}
vector2D::~vector2D(){}

/******************************* vector3Dクラス *************************************/

vector3D::vector3D(double X, double Y, double Z) :x(X), y(Y), z(Z) {}
vector3D::vector3D() : x(0), y(0), z(0) {}
vector3D::~vector3D() {}

vector3D vector3D::operator+(vector3D &other) {
	return vector3D(x + other.x, y + other.y, z + other.z);
}
vector3D vector3D::operator-(vector3D &other) {
	return vector3D(x - other.x, y - other.y, z - other.z);
}
vector3D vector3D::operator*(double &other) {
	return vector3D(x * other, y * other, z * other);
}

void vector3D::Rotate(double axisX, double axisY, double axisZ, double angle) {
	vector3D buff(x, y, z);
	x	=	(cos(angle) + pow(axisX, 2)*(1.0 - cos(angle)))*buff.x
		+	(axisX*axisY*(1.0 - cos(angle)) - axisZ * sin(angle))*buff.y
		+	(axisX*axisZ*(1.0 - cos(angle)) + axisY * sin(angle))*buff.z;

	y	=	(axisY*axisX*(1.0 - cos(angle)) + axisZ * sin(angle))*buff.x
		+	(cos(angle) + pow(axisY, 2)*(1.0 - cos(angle)))*buff.y
		+	(axisY*axisZ*(1.0 - cos(angle)) + axisX * sin(angle))*buff.z;

	z	=	(axisZ*axisX*(1.0 - cos(angle)) - axisY * sin(angle))*buff.x
		+	(axisZ*axisY*(1.0 - cos(angle)) - axisX * sin(angle))*buff.y
		+	(cos(angle) + pow(axisZ, 2)*(1.0 - cos(angle)))*buff.z;
}

/******************************* Model3Dクラス *************************************/

Model3D::Model3D(MODEL3D m){
	switch (m){
	case PANEL:
		for (int i = -50; i < 50; i += 5) {
			for (int j = -50; j < 50; j += 5) {
				pixels.push_back(vector3D((double)i, (double)j, 0));
			}
		}
		break;
	case CUBE:
		for (int i = -50; i < 50; i += 5) {
			for (int j = -50; j < 50; j += 5) {
				pixels.push_back(vector3D((double)i, (double)j, 50));
				pixels.push_back(vector3D((double)i, (double)j, -50));

				pixels.push_back(vector3D(50,(double)i, (double)j));
				pixels.push_back(vector3D(-50,(double)i, (double)j));

				pixels.push_back(vector3D((double)j, 50, (double)i));
				pixels.push_back(vector3D((double)j, -50, (double)i));
			}
		}

		break;
	default:
		break;
	}
}

Model3D::Model3D(std::vector<vector3D> m) {
	pixels = m;
}

Model3D::Model3D() {}
Model3D::~Model3D(){}

std::vector<vector3D> Model3D::getpixels(){return pixels;}

/******************************* Object3Dクラス *************************************/
Object3D::Object3D():axisX(vector3D(1,0,0)),axisY(vector3D(0,1,0)),axisZ(vector3D(0,0,1)){}
Object3D::~Object3D(){}

void Object3D::Rotate(double X, double Y, double Z, double deg) {
	axisX.Rotate(X,Y,Z, deg*DEG2RAD);
	axisY.Rotate(X,Y,Z, deg*DEG2RAD);
	axisZ.Rotate(X,Y,Z, deg*DEG2RAD);
}

std::vector<POINT> Object3D::display() {

	std::vector<vector3D> law_pixel;
	std::vector<POINT> screen;
	law_pixel = models.getpixels();

	for (int j = 0; j < law_pixel.size(); j++){
		vector3D pixel_1 = axisX * law_pixel[j].x;
		vector3D pixel_2 = axisY * law_pixel[j].y;
		vector3D pixel_3 = axisZ * law_pixel[j].z;
		vector3D pixel = pixel_1 + pixel_2 + pixel_3;
		screen.push_back(POINT{(100 * pixel.x / (150 + pixel.z)), 100 * pixel.y / (150 + pixel.z) });
	}
	return screen;
}