#pragma once
#include "Matrix4x4.h"
#include "Vector3.h"
#include "Camera.h"

// 矩阵变换
Matrix4x4 Matrix_Rotation(Vector3 rotation)
{
	float t[4][4];
	float a = rotation.x;
	t[0][0] = 1; t[0][1] = 0;       t[0][2] = 0;      t[0][3] = 0;
	t[1][0] = 0; t[1][1] = cos(a);  t[1][2] = sin(a); t[1][3] = 0;
	t[2][0] = 0; t[2][1] = -sin(a); t[2][2] = cos(a); t[2][3] = 0;
	t[3][0] = 0; t[3][1] = 0;       t[3][2] = 0;      t[3][3] = 1;
	Matrix4x4 Rx(t);

	a = rotation.y;
	t[0][0] = cos(a); t[0][1] = 0; t[0][2] = -sin(a); t[0][3] = 0;
	t[1][0] = 0;      t[1][1] = 1; t[1][2] = 0;       t[1][3] = 0;
	t[2][0] = sin(a); t[2][1] = 0; t[2][2] = cos(a);  t[2][3] = 0;
	t[3][0] = 0;      t[3][1] = 0; t[3][2] = 0;       t[3][3] = 1;
	Matrix4x4 Ry(t);

	a = rotation.z;
	t[0][0] = cos(a);  t[0][1] = sin(a); t[0][2] = 0; t[0][3] = 0;
	t[1][0] = -sin(a); t[1][1] = cos(a); t[1][2] = 0; t[1][3] = 0;
	t[2][0] = 0;       t[2][1] = 0;      t[2][2] = 1; t[2][3] = 0;
	t[3][0] = 0;       t[3][1] = 0;      t[3][2] = 0; t[3][3] = 1;
	Matrix4x4 Rz(t);

	return Rx * Ry * Rz;
}

Matrix4x4 Matrix_Translation(Vector3 position)
{
	float t[4][4];

	t[0][0] = 1; t[0][1] = 0; t[0][2] = 0; t[0][3] = 0;
	t[1][0] = 0; t[1][1] = 1; t[1][2] = 0; t[1][3] = 0;
	t[2][0] = 0; t[2][1] = 0; t[2][2] = 1; t[2][3] = 0;
	t[3][0] = position.x;
	t[3][1] = position.y;
	t[3][2] = position.z;
	t[3][3] = 1;

	return Matrix4x4(t);
}

Matrix4x4 Matrix_View(EulerCamera camera)
{
	// 欧拉照相机
	float t[4][4];

	t[0][0] = 1; t[0][1] = 0; t[0][2] = 0; t[0][3] = 0;
	t[1][0] = 0; t[1][1] = 1; t[1][2] = 0; t[1][3] = 0;
	t[2][0] = 0; t[2][1] = 0; t[2][2] = 1; t[2][3] = 0;
	t[3][0] = -camera.position.x;
	t[3][1] = -camera.position.y;
	t[3][2] = -camera.position.z;
	t[3][3] = 1;
	Matrix4x4 T(t);

	float a = -camera.rotate.x;
	t[0][0] = 1; t[0][1] = 0;       t[0][2] = 0;      t[0][3] = 0;
	t[1][0] = 0; t[1][1] = cos(a);  t[1][2] = sin(a); t[1][3] = 0;
	t[2][0] = 0; t[2][1] = -sin(a); t[2][2] = cos(a); t[2][3] = 0;
	t[3][0] = 0; t[3][1] = 0;       t[3][2] = 0;      t[3][3] = 1;
	Matrix4x4 Rx(t);

	a = -camera.rotate.y;
	t[0][0] = cos(a); t[0][1] = 0; t[0][2] = -sin(a); t[0][3] = 0;
	t[1][0] = 0;      t[1][1] = 1; t[1][2] = 0;       t[1][3] = 0;
	t[2][0] = sin(a); t[2][1] = 0; t[2][2] = cos(a);  t[2][3] = 0;
	t[3][0] = 0;      t[3][1] = 0; t[3][2] = 0;       t[3][3] = 1;
	Matrix4x4 Ry(t);

	a = -camera.rotate.z;
	t[0][0] = cos(a);  t[0][1] = sin(a); t[0][2] = 0; t[0][3] = 0;
	t[1][0] = -sin(a); t[1][1] = cos(a); t[1][2] = 0; t[1][3] = 0;
	t[2][0] = 0;       t[2][1] = 0;      t[2][2] = 1; t[2][3] = 0;
	t[3][0] = 0;       t[3][1] = 0;      t[3][2] = 0; t[3][3] = 1;
	Matrix4x4 Rz(t);

	return T * Rx * Ry * Rz;
}

Matrix4x4 Matrix_View(uvnCamera* camera)
{
	// uvn相机
	float t[4][4];

	t[0][0] = 1; t[0][1] = 0; t[0][2] = 0; t[0][3] = 0;
	t[1][0] = 0; t[1][1] = 1; t[1][2] = 0; t[1][3] = 0;
	t[2][0] = 0; t[2][1] = 0; t[2][2] = 1; t[2][3] = 0;
	t[3][0] = -camera->eye.x;
	t[3][1] = -camera->eye.y;
	t[3][2] = -camera->eye.z;
	t[3][3] = 1;
	Matrix4x4 T(t);

	t[0][0] = camera->u.x; t[0][1] = camera->v.x; t[0][2] = camera->n.x; t[0][3] = 0;
	t[1][0] = camera->u.y; t[1][1] = camera->v.y; t[1][2] = camera->n.y; t[1][3] = 0;
	t[2][0] = camera->u.z; t[2][1] = camera->v.z; t[2][2] = camera->n.z; t[2][3] = 0;
	t[3][0] = -camera->eye.x;
	t[3][1] = -camera->eye.y;
	t[3][2] = -camera->eye.z;
	t[3][3] = 1;
	Matrix4x4 R(t);

	return T * R;
}


Matrix4x4 Matrix_Projection(float fov, float aspect, float n, float f)
{
	float ta, tb, l, r, t, b;
	ta = (f + n) / (f - n);
	tb = 2 * f * n / (n - f);
	l = -atan(fov / 2) * n;
	r = -l;
	t = r / aspect;
	b = -t;

	float m[4][4];
	m[0][0] = 2 * n / (r - l); m[0][1] = 0; m[0][2] = 0; m[0][3] = 0;
	m[1][0] = 0; m[1][1] = 2 * n / (t - b); m[1][2] = 0; m[1][3] = 0;
	m[2][0] = -(r + l) / (r - l); m[2][1] = -(t + b) / (t - b); m[2][2] = ta; m[2][3] = 1;
	m[3][0] = 0; m[3][1] = 0; m[3][2] = tb; m[3][3] = 0;

	return Matrix4x4(m);
}

// 背面剔除，在世界坐标进行
void BackCull(Mesh* mesh, uvnCamera* camera, Vector3* normal_world_faces)
{
	for (int i = 0; i < mesh->faces_number; i++)
	{
		float alpha = normal_world_faces[i] * camera->lookat.inv();
		if (alpha > 0)
			mesh->faces[i].is_Hide = false;
		else
			mesh->faces[i].is_Hide = true;
	}
}

// CVV裁剪
void ClipTriangle(Vector4 v0, Vector4 v1, Vector4 v2)
{
	//
}

void Geometry(Mesh* mesh, uvnCamera* camera, int window_w, int window_h, float fov, float Near, float Far)
{
	Matrix4x4 R = Matrix_Rotation(mesh->rotation);
	Matrix4x4 T = Matrix_Translation(mesh->position);
	Matrix4x4 Model2World = R * T;

	Matrix4x4 World2View = Matrix_View(camera);

	//3.1415926 / 2 / 2 视口为45度， 4 / 3 宽高比， Near = 1， Far = 20， 投影面默认为near 
	Matrix4x4 View2Project = Matrix_Projection(fov, window_w / window_h, Near, Far);

	//顶点坐标和法向量转换到世界坐标系下
	for (int i = 0; i < mesh->vertices_number; i++)
	{
		mesh->vertices[i].position_world = mesh->vertices[i].position * Model2World;
		mesh->vertices[i].normal_world = mesh->vertices[i].normal * Model2World;
	}

	// 背面剔除，在世界坐标系下进行
	Vector3* normal_world_faces = new Vector3[mesh->faces_number];
	for (int i = 0; i < mesh->faces_number; i++)
	{
		normal_world_faces[i] = (mesh->faces[i].normal * Model2World).getVector3();
		normal_world_faces[i].normalize();
	}
	BackCull(mesh, camera, normal_world_faces);

	//顶点坐标投影到裁剪空间
	Vector4* position_project = new Vector4[mesh->vertices_number];
	for (int i = 0; i < mesh->vertices_number; i++)
	{
		position_project[i] = mesh->vertices[i].position_world * World2View * View2Project;
	}

	// CVV裁剪，未完成
	//for (int i; i < mesh->faces_number; i++)
	//{
	//	int p0 = mesh->faces[i].index[0];
	//	int p1 = mesh->faces[i].index[1];
	//	int p2 = mesh->faces[i].index[2];
	//	ClipTriangle(position_project[p0], position_project[p1], position_project[p2]);
	//}

	for (int i = 0; i < mesh->vertices_number; i++)
	{
		// 透视除法
		float w = position_project[i].w;
		float x = position_project[i].x / w;
		float y = position_project[i].y / w;
		float z = position_project[i].z / w;

		//转换到屏幕坐标  x(-1, 1) y(-1, 1) z(-1, 1)
		mesh->vertices[i].position_screen.x = window_w * (x / 2 + 0.5);
		mesh->vertices[i].position_screen.y = -window_h * (y / 2 + 0.5) + window_h;
		mesh->vertices[i].position_screen.z = z;
	}
}