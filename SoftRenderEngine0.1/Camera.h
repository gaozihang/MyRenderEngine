#pragma once
#include "Vector3.h"

class EulerCamera
{
public:
	//相机默认朝向Z轴
	Vector3 position;
	Vector3 rotate;
	EulerCamera(Vector3, Vector3);
	~EulerCamera();

private:

};

EulerCamera::EulerCamera(Vector3 p = Vector3::ZERO, Vector3 r = Vector3::ZERO)
	: position(p), rotate(r) { }

EulerCamera::~EulerCamera() { }


class uvnCamera
{
public:
	//右 上 前
	Vector3 u, v, n;
	Vector3 eye, lookat, up;
	uvnCamera(Vector3, Vector3, Vector3);
	~uvnCamera();

private:

};

uvnCamera::uvnCamera(Vector3 eye_in = Vector3::ZERO, Vector3 lookat_in = Vector3::ZERO,
	Vector3 up_in = Vector3(0, 0, 1)) : eye(eye_in), lookat(lookat_in), up(up_in)
{
	n = lookat - eye;
	u = up.cross(n);
	v = n.cross(u);
	n.normalize();
	u.normalize();
	v.normalize();
}
uvnCamera::~uvnCamera() { }
