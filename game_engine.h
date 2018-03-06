#pragma once
#include <cmath>
#include <vector>


class vector3D {
public:
	double X, Y, Z;
	vector3D(double, double, double);
	vector3D();
	~vector3D();
	vector3D operator+(vector3D &other);
	vector3D operator-(vector3D &other);
	vector3D operator*(double &other);
	void Rotate(double, double, double, double);
private:

};

class object3D {
public:
	vector3D position;
	vector3D rotation;
	object3D();
	~object3D();
private:
	vector3D axisX, axisZ, axisY;
};
