#pragma once
#include "Vector4.h"
#include "Material.h"
#include "Matrix4x4.h"

class Vertex
{
public:
	Vector4 position;
	Vector4 normal;
	Vector4 position_world;
	Vector4 normal_world;
	Vector3 position_screen;  // z' = a + b / z 
	Vertex(Vector4, Vector4);
	void Matrix_Transform(Matrix4x4);
	~Vertex();

private:

};

Vertex::Vertex(Vector4 input_position = Vector4::ZERO,
	Vector4 input_normal = Vector4::ZERO):
	position(input_normal), normal(input_normal)
{
}

void Vertex::Matrix_Transform(Matrix4x4 m)
{
	position = position * m;
	normal = normal * m;
}

Vertex::~Vertex()
{
	// if (material != NULL) delete material;
}