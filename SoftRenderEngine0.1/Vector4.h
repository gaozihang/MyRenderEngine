#pragma once
#include "Vector3.h"
#include "Matrix4x4.h"
class Vector4
{
public:
	Vector4(float, float, float, float);
	Vector4(Vector3, float);
	Vector4();
	~Vector4();
	float x, y, z, w;

	Vector4 operator* (Matrix4x4&);
	Vector4 copy();
	Vector3 getVector3();
	static Vector4 ZERO;
private:

};

Vector4 Vector4::ZERO = Vector4(0, 0, 0, 0);

Vector4::Vector4(float input_x, float input_y, float input_z, float input_w)
	:x(input_x), y(input_y), z(input_z), w(input_w) { }

Vector4::Vector4() : x(0), y(0), z(0), w(0) { }
Vector4::Vector4(Vector3 v, float input_w = 1) : x(v.x), y(v.y), z(v.z), w(input_w) { }

Vector4::~Vector4()
{
}

Vector4 Vector4::operator* (Matrix4x4& v)
{
	Vector4 r;
	r.x = x * v.m[0][0] + y * v.m[1][0] + z * v.m[2][0] + w * v.m[3][0];
	r.y = x * v.m[0][1] + y * v.m[1][1] + z * v.m[2][1] + w * v.m[3][1];
	r.z = x * v.m[0][2] + y * v.m[1][2] + z * v.m[2][2] + w * v.m[3][2];
	r.w = x * v.m[0][3] + y * v.m[1][3] + z * v.m[2][3] + w * v.m[3][3];
	return r;
}

Vector4 Vector4::copy() {
	return Vector4(this->x, this->y, this->z, this->z);
}

Vector3 Vector4::getVector3()
{
	Vector3 v;
	v.x = x;
	v.y = y;
	v.z = z;
	return v;
}
