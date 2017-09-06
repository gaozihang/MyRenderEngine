#pragma once

#include "Math.h"

class Triangle_Face
{
public:
	Triangle_Face();
	~Triangle_Face();
	int index[3];
	bool is_Hide;
	Vector4 normal;
	Texture_uv uv[3];
private:

};

Triangle_Face::Triangle_Face()
{
	is_Hide = false;
}

Triangle_Face::~Triangle_Face()
{
}