#pragma once
#include <string>
#include "Vector3.h"
#include "ColorRGBA.h"
#include "Vertex.h"
#include "Triangle_Face.h"
#include "Material.h"

class Mesh
{
public:
	Mesh(std::string, Vector3, Vector3, int, int);
	~Mesh();
	std::string name;
	Vector3 position;
	Vector3 rotation;
	Vertex* vertices;
	Triangle_Face* faces;
	int vertices_number, faces_number;
	Material* material;

private:

};

Mesh::Mesh(std::string str = "", Vector3 p = Vector3::ZERO,
	Vector3 r = Vector3::ZERO, int vn = 0, int fn = 0)
	:name(str), position(p), rotation(r), vertices_number(vn), faces_number(fn)
{
	vertices = new Vertex[vertices_number];
	faces = new Triangle_Face[faces_number];
}

Mesh::~Mesh()
{
	delete[] vertices;
	delete[] faces;
}
