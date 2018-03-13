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

void vector3D::Rotate(double angleX, double angleY, double angleZ) {

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
Object3D::Object3D(){}
Object3D::~Object3D(){}
std::vector<vector2D> Object3D::display() {

	std::vector<vector3D> pixels;
	std::vector<vector2D> screen;

	for (int i = 0; i < models.size(); i++){
		pixels = models[i].getpixels();
		for (int j = 0; j < pixels.size(); j++){
			screen.push_back(vector2D(100 * pixels[j].x / (150 + pixels[j].z), 100 * pixels[j].y / (150 + pixels[j].z)));
		}
	}
	return screen;
}