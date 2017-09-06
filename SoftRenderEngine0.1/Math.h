#pragma once
#include "Vector3.h"
struct Texture_uv
{
	float u, v;
};

struct Vertex_and_uv  //��Ļ���� + uv���꣬�˽ṹ�����ڹ�դ���׶�
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