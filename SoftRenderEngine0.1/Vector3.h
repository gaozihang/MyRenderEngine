#pragma once
#include <math.h>
#include "Matrix4x4.h"

class  Vector3
{
public:
	Vector3(float, float, float);
	Vector3();
	~Vector3();
	float x, y, z;

	Vector3 copy();
	Vector3 inv();
	float length();
	float sqrlength();
	void normalize();
	Vector3 cross(Vector3);

	Vector3 operator= (Vector3&);
	Vector3 operator+ (Vector3&);
	Vector3 operator+ (float);
	Vector3 operator- (Vector3&);
	Vector3 operator- (float);
	float operator* (Vector3&);
	Vector3 operator* (float);
	Vector3 operator/ (float);

	static Vector3 ZERO;

private:

};



Vector3 Vector3::ZERO = Vector3(0, 0, 0);

Vector3::Vector3(float input_x, float input_y, float input_z)
	:x(input_x), y(input_y), z(input_z) { }

Vector3::Vector3()
	: x(0), y(0), z(0) { }

Vector3::~Vector3() { }

Vector3 Vector3::copy() {
	return Vector3(this->x, this->y, this->z);
}

Vector3 Vector3::inv() {
	return Vector3(-this->x, -this->y, -this->z);
}

float Vector3::length() {
	return sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
}

float Vector3::sqrlength() {
	return this->x * this->x + this->y * this->y + this->z * this->z;
}

void Vector3::normalize() {
	float inv = 1 / this->length();
	this->x *= inv;
	this->y *= inv;
	this->z *= inv;
}

Vector3 Vector3::cross(Vector3 v) {
	return Vector3(-z * v.y + y * v.z,
		z * v.x - x * v.z,
		-y * v.x + x * v.y);
}

Vector3 Vector3::operator= (Vector3 &v) {
	x = v.x;
	y = v.y;
	z = v.z;
	return *this;
}


Vector3 Vector3::operator+ (Vector3 &v) {
	return Vector3(x + v.x, y + v.y, z + v.z);
}

Vector3 Vector3::operator- (Vector3 &v) {
	return Vector3(x - v.x, y - v.y, z - v.z);
}

Vector3 Vector3::operator+ (float f) {
	return Vector3(x + f, y + f, z + f);
}

Vector3 Vector3::operator- (float f) {
	return Vector3(x - f, y - f, z - f);
}

float Vector3::operator* (Vector3 &v) {
	return x * v.x + y * v.y + z * v.z;
}

Vector3 Vector3::operator* (float f) {
	return Vector3(x * f, y * f, z * f);
}

Vector3 Vector3::operator/ (float f) {
	float invf = 1 / f;
	return Vector3(x * invf, y * invf, z * invf);
}