#pragma once
#include "Mesh.h"
#include "Vector4.h"
#include "Vertex.h"
#include "Material.h"

void InitCube(Mesh* mesh, Material* material)
{
	//顶点坐标
	mesh->vertices[0].position = Vector4(-1, 1, -1, 1);
	mesh->vertices[1].position = Vector4(1, 1, -1, 1);
	mesh->vertices[2].position = Vector4(-1, 1, 1, 1);
	mesh->vertices[3].position = Vector4(1, 1, 1, 1);
	mesh->vertices[4].position = Vector4(-1, -1, -1, 1);
	mesh->vertices[5].position = Vector4(1, -1, -1, 1);
	mesh->vertices[6].position = Vector4(-1, -1, 1, 1);
	mesh->vertices[7].position = Vector4(1, -1, 1, 1);

	//三角面的顶点索引
	mesh->faces[0].index[0] = 4;
	mesh->faces[0].index[1] = 5;
	mesh->faces[0].index[2] = 1;
	mesh->faces[1].index[0] = 1;
	mesh->faces[1].index[1] = 0;
	mesh->faces[1].index[2] = 4;

	mesh->faces[2].index[0] = 7;
	mesh->faces[2].index[1] = 6;
	mesh->faces[2].index[2] = 2;
	mesh->faces[3].index[0] = 2;
	mesh->faces[3].index[1] = 3;
	mesh->faces[3].index[2] = 7;

	mesh->faces[4].index[0] = 6;
	mesh->faces[4].index[1] = 4;
	mesh->faces[4].index[2] = 0;
	mesh->faces[5].index[0] = 0;
	mesh->faces[5].index[1] = 2;
	mesh->faces[5].index[2] = 6;

	mesh->faces[6].index[0] = 5;
	mesh->faces[6].index[1] = 7;
	mesh->faces[6].index[2] = 3;
	mesh->faces[7].index[0] = 3;
	mesh->faces[7].index[1] = 1;
	mesh->faces[7].index[2] = 5;

	mesh->faces[8].index[0] = 0;
	mesh->faces[8].index[1] = 1;
	mesh->faces[8].index[2] = 3;
	mesh->faces[9].index[0] = 3;
	mesh->faces[9].index[1] = 2;
	mesh->faces[9].index[2] = 0;

	mesh->faces[10].index[0] = 5;
	mesh->faces[10].index[1] = 4;
	mesh->faces[10].index[2] = 6;
	mesh->faces[11].index[0] = 6;
	mesh->faces[11].index[1] = 7;
	mesh->faces[11].index[2] = 5;

	//计算三角面的法线
	for (int i = 0; i < mesh->faces_number; i++)
	{
		int p0 = mesh->faces[i].index[0];
		int p1 = mesh->faces[i].index[1];
		int p2 = mesh->faces[i].index[2];

		Vector3 t0 = mesh->vertices[p1].position.getVector3() -
			mesh->vertices[p0].position.getVector3();
		Vector3 t1 = mesh->vertices[p2].position.getVector3() -
			mesh->vertices[p0].position.getVector3();
		Vector3 tn = t1.cross(t0);
		tn.normalize();
		mesh->faces[i].normal = Vector4(tn, 0);
	}

	//计算顶点法线
	Vector3* vertices_sum = new Vector3[mesh->vertices_number];
	int* vertices_count = new int[mesh->vertices_number];
	memset(vertices_count, 0, sizeof(vertices_count));
	for (int i = 0; i < mesh->faces_number; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			vertices_sum[mesh->faces[i].index[j]] = vertices_sum[mesh->faces[i].index[j]] + mesh->faces[i].normal.getVector3();
			vertices_count[mesh->faces[i].index[j]]++;
		}
	}

	for (int i = 0; i < mesh->vertices_number; i++)
	{
		mesh->vertices[i].normal = Vector4(vertices_sum[i] / vertices_count[i], 0);
	}

	//赋上材质
	mesh->material = material;

	//赋上uv
	for (int i = 0; i < mesh->faces_number; i++)
	{
		if(i % 2 == 0)
		{
			mesh->faces[i].uv[0] = { 0, 1 };
			mesh->faces[i].uv[1] = { 1, 1 };
			mesh->faces[i].uv[2] = { 1, 0 };
		}
		else
		{
			mesh->faces[i].uv[0] = { 1, 0 };
			mesh->faces[i].uv[1] = { 0, 0 };
			mesh->faces[i].uv[2] = { 0, 1 };
		}
	}
}