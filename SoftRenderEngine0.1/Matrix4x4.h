#pragma once
#include <math.h>

class Matrix4x4
{
public:
	Matrix4x4(float[][4]);
	Matrix4x4();
	~Matrix4x4();
	float m[4][4];

	Matrix4x4 operator= (Matrix4x4&);
	Matrix4x4 operator+ (Matrix4x4&);
	Matrix4x4 operator+ (float);
	Matrix4x4 operator- (Matrix4x4&);
	Matrix4x4 operator- (float);
	Matrix4x4 operator* (Matrix4x4&);
	Matrix4x4 operator* (float);
	Matrix4x4 operator/ (Matrix4x4&);
	Matrix4x4 operator/ (float);

	Matrix4x4 trans();
	Matrix4x4 inv();
	Matrix4x4 star();
	float det();

private:

};


Matrix4x4::Matrix4x4()
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			m[i][j] = 0;
}

Matrix4x4::Matrix4x4(float v[][4])
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			m[i][j] = v[i][j];
}

Matrix4x4::~Matrix4x4()
{
}

Matrix4x4 Matrix4x4::operator= (Matrix4x4& v) {
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			m[i][j] = v.m[i][j];
	return *this;
}

Matrix4x4 Matrix4x4::operator+ (Matrix4x4& v) {
	Matrix4x4 r;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			r.m[i][j] = m[i][j] + v.m[i][j];
	return r;
}

Matrix4x4 Matrix4x4::operator+ (float f) {
	Matrix4x4 r;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			r.m[i][j] = m[i][j] + f;
	return r;
}

Matrix4x4 Matrix4x4::operator- (Matrix4x4& v) {
	Matrix4x4 r;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			r.m[i][j] = m[i][j] - v.m[i][j];
	return r;
}

Matrix4x4 Matrix4x4::operator- (float f) {
	Matrix4x4 r;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			r.m[i][j] = m[i][j] - f;
	return r;
}

Matrix4x4 Matrix4x4::operator* (Matrix4x4& v) {
	Matrix4x4 r;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
		{
			r.m[i][j] = 0;
			for (int k = 0; k < 4; k++)
				r.m[i][j] += m[i][k] * v.m[k][j];
		}
	return r;
}

Matrix4x4 Matrix4x4::operator* (float f) {
	Matrix4x4 r;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			r.m[i][j] = m[i][j] * f;
	return r;
}

Matrix4x4 Matrix4x4::operator/ (Matrix4x4& v) {
	Matrix4x4 r;
	r = *this * v.inv();
	return r;
}

Matrix4x4 Matrix4x4::operator/ (float f) {
	Matrix4x4 r;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			r.m[i][j] = m[i][j] / f;
	return r;
}

Matrix4x4 Matrix4x4::trans() {
	Matrix4x4 r;
	r.m[0][0] = m[0][0]; r.m[0][1] = m[1][0]; r.m[0][2] = m[2][0]; r.m[0][3] = m[3][0];
	r.m[1][0] = m[0][1]; r.m[1][1] = m[1][1]; r.m[1][2] = m[2][1]; r.m[1][3] = m[3][1];
	r.m[2][0] = m[0][2]; r.m[2][1] = m[1][2]; r.m[2][2] = m[2][2]; r.m[2][3] = m[3][2];
	r.m[3][0] = m[0][3]; r.m[3][1] = m[1][3]; r.m[3][2] = m[2][3]; r.m[3][3] = m[3][3];
	return r;
}

Matrix4x4 Matrix4x4::inv() {
	Matrix4x4 r;
	//
	return r;
}

Matrix4x4 Matrix4x4::star() {
	Matrix4x4 r;
	//
	return r;
}

float Matrix4x4::det() {
	float r = 0;
	//
	return r;
}
