#pragma once
#include "Vector3.h"
struct Texture_uv
{
	float u, v;
};

struct Vertex_and_uv  //屏幕坐标 + uv坐标，此结构体用于光栅化阶段
{
	Vector3 position_screen;
	Texture_uv uv;
};

struct Vertex_t
{
	Vector3 position_screen;
	Vector3 position_world;
	Texture_uv uv;
};