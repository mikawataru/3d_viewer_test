#include "game_engine.h"

/******************************* vector3Dクラス *************************************/

vector3D::vector3D(double x, double y, double z) :X(x), Y(y), Z(z) {}
vector3D::vector3D() : X(0), Y(0), Z(0) {}
vector3D::~vector3D() {}

vector3D vector3D::operator+(vector3D &other) {
	return vector3D(X + other.X, Y + other.Y, Z + other.Z);
}
vector3D vector3D::operator-(vector3D &other) {
	return vector3D(X - other.X, Y - other.Y, Z - other.Z);
}
vector3D vector3D::operator*(double &other) {
	return vector3D(X * other, Y * other, Z * other);
}

void vector3D::Rotate(double axisX, double axisY, double axisZ, double angle) {
	vector3D buff(X, Y, Z);
	X	=	(cos(angle) + pow(axisX, 2)*(1.0 - cos(angle)))*buff.X
		+	(axisX*axisY*(1.0 - cos(angle)) - axisZ * sin(angle))*buff.Y
		+	(axisX*axisZ*(1.0 - cos(angle)) + axisY * sin(angle))*buff.Z;

	Y	=	(axisY*axisX*(1.0 - cos(angle)) + axisZ * sin(angle))*buff.X
		+	(cos(angle) + pow(axisY, 2)*(1.0 - cos(angle)))*buff.Y
		+	(axisY*axisZ*(1.0 - cos(angle)) + axisX * sin(angle))*buff.Z;

	Z	=	(axisZ*axisX*(1.0 - cos(angle)) - axisY * sin(angle))*buff.X
		+	(axisZ*axisY*(1.0 - cos(angle)) - axisX * sin(angle))*buff.Y
		+	(cos(angle) + pow(axisZ, 2)*(1.0 - cos(angle)))*buff.Z;

}


/******************************* object3Dクラス *************************************/

object3D::object3D() {

	axisX = vector3D(1.0, 0.0, 0.0);
	axisY = vector3D(0.0, 1.0, 0.0);
	axisZ = vector3D(0.0, 0.0, 1.0);
}

object3D::~object3D() {}
