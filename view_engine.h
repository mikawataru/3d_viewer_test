#pragma once
#include <cmath>
#include <vector>

enum MODEL3D {
	CUBE = 0, PANEL = 1
};

class vector2D {
public:
	double x, y;
	vector2D(double,double);
	~vector2D();
private:
};

class vector3D {
public:
	double x, y, z;
	vector3D(double, double, double);
	vector3D();
	~vector3D();
	vector3D operator+(vector3D &other);
	vector3D operator-(vector3D &other);
	vector3D operator*(double &other);
	void Rotate(double, double, double, double);
	void Rotate(double, double, double);
private:

};

class Model3D{
public:
	Model3D(MODEL3D);
	Model3D(std::vector<vector3D>);
	Model3D();
	~Model3D();
	std::vector<vector3D> getpixels();
private:
	std::vector<vector3D> pixels;
};

class Object3D{
public:
	std::vector<Model3D> models;
	vector3D position;
	vector3D rotation;
	vector3D axisX,axisY,axisZ;
	std::vector<vector2D> display();
	Object3D();
	~Object3D();
private:
};
