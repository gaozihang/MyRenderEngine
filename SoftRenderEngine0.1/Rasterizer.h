#pragma once
#include "windows.h"
#include "Vector3.h"
#include "Math.h"
#include "ColorRGBA.h"
#include "Triangle_Face.h"
#include "Vertex.h"
#include <iostream>

using namespace std;

void DrawLine(byte* buffer, Vector3 b, Vector3 e, int window_w, ColorRGBA color)
{
	float tx = e.x - b.x;
	float ty = e.y - b.y;
	float dist = sqrt(tx * tx + ty * ty);
	if (dist < 2)
		return;
	Vector3 m;
	m.x = (b.x + e.x) / 2;
	m.y = (b.y + e.y) / 2;
	buffer[int(m.y + 0.5) * window_w * 4 + int(m.x + 0.5) * 4 + 0] = color.b * 255;
	buffer[int(m.y + 0.5) * window_w * 4 + int(m.x + 0.5) * 4 + 1] = color.g * 255;
	buffer[int(m.y + 0.5) * window_w * 4 + int(m.x + 0.5) * 4 + 2] = color.r * 255;
	buffer[int(m.y + 0.5) * window_w * 4 + int(m.x + 0.5) * 4 + 3] = color.a * 255;

	DrawLine(buffer, b, m, window_w, color);
	DrawLine(buffer, m, e, window_w, color);
}

void DrawBLine(byte* buffer, Vector3 b, Vector3 e, int window_w, ColorRGBA color)
{
	int x0 = (int)(b.x + 0.5);
	int y0 = (int)(b.y + 0.5);
	int x1 = (int)(e.x + 0.5);
	int y1 = (int)(e.y + 0.5);

	int dx = abs(x1 - x0);
	int dy = abs(y1 - y0);
	int sx = (x0 < x1) ? 1 : -1;
	int sy = (y0 < y1) ? 1 : -1;
	int err = dx - dy;

	while (1) {
		buffer[int(y0) * window_w * 4 + int(x0) * 4 + 0] = color.b * 255;
		buffer[int(y0) * window_w * 4 + int(x0) * 4 + 1] = color.g * 255;
		buffer[int(y0) * window_w * 4 + int(x0) * 4 + 2] = color.r * 255;
		buffer[int(y0) * window_w * 4 + int(x0) * 4 + 3] = color.a * 255;
		if ((x0 == x1) && (y0 == y1)) break;
		int e2 = 2 * err;
		if (e2 > -dy) { err -= dy; x0 += sx; }
		if (e2 < dx) { err += dx; y0 += sy; }
	}
}

float interp(float x1, float x2, float t)
{
	return x1 + (x2 - x1) * t;
}

Vector3 Vector3_interp(Vector3 x1, Vector3 x2, float t)
{
	Vector3 v;
	v.x = interp(x1.x, x2.x, t);
	v.y = interp(x1.y, x2.y, t);
	v.z = interp(x1.z, x2.z, t);

	return v;
}

ColorRGBA ColorRGBA_interp(ColorRGBA x1, ColorRGBA x2, float t)
{
	ColorRGBA c;
	c.r = interp(x1.r, x2.r, t);
	c.g = interp(x1.g, x2.g, t);
	c.b = interp(x1.b, x2.b, t);
	c.a = interp(x1.a, x2.a, t);
	return c;
}

Texture_uv uv_interp(Texture_uv x1, Texture_uv x2, float t)
{
	Texture_uv tex;
	tex.u = interp(x1.u, x2.u, t);
	tex.v = interp(x1.v, x2.v, t);
	return tex;
}

void Vertex_Swap(Vertex& p0, Vertex& p1, Vertex& p2)
{
	if (int(p0.position_screen.y + 0.5) > int(p1.position_screen.y + 0.5))
	{
		Vertex tmp = p0;
		p0 = p1;
		p1 = tmp;
	}

	if (int(p1.position_screen.y + 0.5) > int(p2.position_screen.y + 0.5))
	{
		Vertex tmp = p1;
		p1 = p2;
		p2 = tmp;
	}

	if (int(p0.position_screen.y + 0.5) > int(p1.position_screen.y + 0.5))
	{
		Vertex tmp = p0;
		p0 = p1;
		p1 = tmp;
	}
}

void Vertex_and_uv_Swap(Vertex_and_uv& v0, Vertex_and_uv& v1, Vertex_and_uv& v2)
{
	if (int(v0.position_screen.y + 0.5) > int(v1.position_screen.y + 0.5))
	{
		Vertex_and_uv tmp = v0;
		v0 = v1;
		v1 = tmp;
	}

	if (int(v1.position_screen.y +0.5) > int(v2.position_screen.y +0.5))
	{
		Vertex_and_uv tmp = v1;
		v1 = v2;
		v2 = tmp;
	}

	if (int(v0.position_screen.y +0.5) > int(v1.position_screen.y + 0.5))
	{
		Vertex_and_uv tmp = v0;
		v0 = v1;
		v1 = tmp;
	}
}


void DrawPixel(byte* buffer, float* zbuffer, Vector3 pixel, int window_w, int window_h, ColorRGBA color)
{
	int x = int(pixel.x + 0.5);
	int y = int(pixel.y + 0.5);

	if (pixel.z < zbuffer[y * window_w + x] && x >= 0 && x <= window_w && y >= 0 && y <= window_h)
	{
		zbuffer[y * window_w + x] = pixel.z;
		buffer[int(y) * window_w * 4 + int(x) * 4 + 0] = color.b * 255;
		buffer[int(y) * window_w * 4 + int(x) * 4 + 1] = color.g * 255;
		buffer[int(y) * window_w * 4 + int(x) * 4 + 2] = color.r * 255;
		buffer[int(y) * window_w * 4 + int(x) * 4 + 3] = color.a * 255;
	}
}

void ClearBackBuffer(byte* buffer, float* zbuffer, int window_w, int window_h, ColorRGBA color)
{
	for (int y = 0; y < window_h; y++)
		for (int x = 0; x < window_w; x++)
		{
			zbuffer[int(y) * window_w + int(x)] = 1;
			buffer[int(y) * window_w * 4 + int(x) * 4 + 0] = color.b * 255;
			buffer[int(y) * window_w * 4 + int(x) * 4 + 1] = color.g * 255;
			buffer[int(y) * window_w * 4 + int(x) * 4 + 2] = color.r * 255;
			buffer[int(y) * window_w * 4 + int(x) * 4 + 3] = color.a * 255;
		}
}

void DrawPoint(byte* buffer, Mesh* mesh, int window_w, int window_h, ColorRGBA color)
{
	for (int i = 0; i < mesh->vertices_number; i++)
	{
		int x = int(mesh->vertices[i].position_screen.x + 0.5);
		int y = int(mesh->vertices[i].position_screen.y + 0.5);

//		cout << "DrawPoint--(i, x, y): " << i << ", " << x << ", " << y << endl;

		if (x >= 0 && x <= window_w && y >= 0 && y <= window_h)
		{
			buffer[int(y) * window_w * 4 + int(x) * 4 + 0] = color.b * 255;
			buffer[int(y) * window_w * 4 + int(x) * 4 + 1] = color.g * 255;
			buffer[int(y) * window_w * 4 + int(x) * 4 + 2] = color.r * 255;
			buffer[int(y) * window_w * 4 + int(x) * 4 + 3] = color.a * 255;
		}
	}
}

void DrawWire(byte* buffer, Mesh* mesh, int window_w, int window_h, ColorRGBA color)
{
	for (int i = 0; i < mesh->faces_number; i++)
	{
		if (mesh->faces[i].is_Hide) continue;

		int p0 = mesh->faces[i].index[0];
		int p1 = mesh->faces[i].index[1];
		int p2 = mesh->faces[i].index[2];

//		cout << "DrawWire--(p0, p1, p2): " << p0 << ", " << p1 << ", " << p2 << endl;

		Vector3 v0 = mesh->vertices[p0].position_screen;
		Vector3 v1 = mesh->vertices[p1].position_screen;
		Vector3 v2 = mesh->vertices[p2].position_screen;

		DrawBLine(buffer, v0, v1, window_w, color);
		DrawBLine(buffer, v1, v2, window_w, color);
		DrawBLine(buffer, v2, v0, window_w, color);
	}
}

void DrawTriangle(byte* buffer, float* zbuffer, Mesh* mesh, Vertex_t p0, Vertex_t p1, Vertex_t p2, float a, float b, int window_w, int window_h)
{
	if (int(p0.position_screen.y + 0.5) == int(p1.position_screen.y + 0.5))
	{
		if (int(p0.position_screen.x + 0.5) > int(p1.position_screen.x + 0.5))
		{
			Vertex_t tmp = p0;
			p0 = p1;
			p1 = tmp;
		}

		int y_begin = int(p0.position_screen.y + 0.5);
		int y_end = int(p2.position_screen.y + 0.5);
		int y_span = y_end - y_begin;

		Texture_uv p0_over_z = { p0.uv.u / p0.position_world.z, p0.uv.v / p0.position_world.z };
		Texture_uv p1_over_z = { p1.uv.u / p1.position_world.z, p1.uv.v / p1.position_world.z };
		Texture_uv p2_over_z = { p2.uv.u / p2.position_world.z, p2.uv.v / p2.position_world.z };

		for (int y = y_begin, dy = 0; y <= y_end; y++, dy++)
		{
			float y_scale = (y_span == 0) ? 1 : ((float)dy / y_span);
			Vector3 l = Vector3_interp(p0.position_screen, p2.position_screen, y_scale);
			Vector3 r = Vector3_interp(p1.position_screen, p2.position_screen, y_scale);

			Texture_uv uv_l = uv_interp(p0_over_z, p2_over_z, y_scale);
			Texture_uv uv_r = uv_interp(p1_over_z, p2_over_z, y_scale);

			int x_begin = int(l.x + 0.5);
			int x_end = int(r.x + 0.5);
			int x_span = x_end - x_begin;

			for (int x = x_begin, dx = 0; x <= x_end; x++, dx++)
			{
				float x_scale = (x_span == 0) ? 1 : ((float)dx / x_span);
				Vector3 pixel_screen = Vector3_interp(l, r, x_scale);
				Texture_uv pixel_uv = uv_interp(uv_l, uv_r, x_scale);
				float world_z = b / (pixel_screen.z - a);

				pixel_uv.u *= world_z;
				pixel_uv.v *= world_z;

				//	cout << "(type, y, x, u, v): " << 1 << " " << y << " " << x << " " << pixel_uv.u << " " << pixel_uv.v << endl;

				ColorRGBA color;
				if (mesh->material->texture != NULL)
					color = mesh->material->texture->GetPixelColor(pixel_uv);

				DrawPixel(buffer, zbuffer, pixel_screen, window_w, window_h, color);
			}
		}
		return;
	}

	if (int(p1.position_screen.y + 0.5) == int(p2.position_screen.y + 0.5))
	{
		if (int(p1.position_screen.x + 0.5) > int(p2.position_screen.x + 0.5))
		{
			Vertex_t tmp = p1;
			p1 = p2;
			p2 = tmp;
		}

		int y_begin = int(p0.position_screen.y + 0.5);
		int y_end = int(p1.position_screen.y + 0.5);
		int y_span = y_end - y_begin;

		Texture_uv p0_over_z = { p0.uv.u / p0.position_world.z, p0.uv.v / p0.position_world.z };
		Texture_uv p1_over_z = { p1.uv.u / p1.position_world.z, p1.uv.v / p1.position_world.z };
		Texture_uv p2_over_z = { p2.uv.u / p2.position_world.z, p2.uv.v / p2.position_world.z };

		for (int y = y_begin, dy = 0; y <= y_end; y++, dy++)
		{
			float y_scale = (y_span == 0) ? 1 : ((float)dy / y_span);
			Vector3 l = Vector3_interp(p0.position_screen, p1.position_screen, y_scale);
			Vector3 r = Vector3_interp(p0.position_screen, p2.position_screen, y_scale);

			Texture_uv uv_l = uv_interp(p0_over_z, p1_over_z, y_scale);
			Texture_uv uv_r = uv_interp(p0_over_z, p2_over_z, y_scale);

			int x_begin = int(l.x + 0.5);
			int x_end = int(r.x + 0.5);
			int x_span = x_end - x_begin;

			for (int x = x_begin, dx = 0; x <= x_end; x++, dx++)
			{
				float x_scale = (x_span == 0) ? 1 : ((float)dx / x_span);
				Vector3 pixel_screen = Vector3_interp(l, r, x_scale);
				Texture_uv pixel_uv = uv_interp(uv_l, uv_r, x_scale);
				float world_z = b / (pixel_screen.z - a);

				pixel_uv.u *= world_z;
				pixel_uv.v *= world_z;

				//	cout << "(type, y, x, u, v): " << 2 << " " << y << " " << x << " " << pixel_uv.u << " " << pixel_uv.v << endl;

				ColorRGBA color;
				if (mesh->material->texture != NULL)
					color = mesh->material->texture->GetPixelColor(pixel_uv);

				DrawPixel(buffer, zbuffer, pixel_screen, window_w, window_h, color);

			}
		}
		return;
	}
}

void Rasterizer(byte* buffer, float* zbuffer, Mesh* mesh, float n, float f, int window_w, int window_h)
{
	float a = (f + n) / (f - n);
	float b = 2 * f * n / (n - f);

	for (int i = 0; i < mesh->faces_number; i++)
	{
		if (mesh->faces[i].is_Hide) continue;

		Vertex p0 = mesh->vertices[mesh->faces[i].index[0]];
		Vertex p1 = mesh->vertices[mesh->faces[i].index[1]];
		Vertex p2 = mesh->vertices[mesh->faces[i].index[2]];

		Vertex_t t0, t1, t2;
		t0.position_screen = p0.position_screen;
		t0.position_world = p0.position_world.getVector3();
		t0.uv = mesh->faces[i].uv[0];
		
		t1.position_screen = p1.position_screen;
		t1.position_world = p1.position_world.getVector3();
		t1.uv = mesh->faces[i].uv[1];

		t2.position_screen = p2.position_screen;
		t2.position_world = p2.position_world.getVector3();
		t2.uv = mesh->faces[i].uv[2];

		if (int(t0.position_screen.y + 0.5) > int(t1.position_screen.y + 0.5))
		{
			Vertex_t tmp = t0;
			t0 = t1;
			t1 = tmp;
		}

		if (int(t1.position_screen.y + 0.5) > int(t2.position_screen.y + 0.5))
		{
			Vertex_t tmp = t1;
			t1 = t2;
			t2 = tmp;
		}

		if (int(t0.position_screen.y + 0.5) > int(t1.position_screen.y + 0.5))
		{
			Vertex_t tmp = t0;
			t0 = t1;
			t1 = tmp;
		}

		if (int(p0.position_screen.y + 0.5) == int(p1.position_screen.y + 0.5) ||
			int(p1.position_screen.y + 0.5) == int(p2.position_screen.y + 0.5))
		{
			DrawTriangle(buffer, zbuffer, mesh, t0, t1, t2, a, b, window_w, window_h);
		}
		else
		{
			float dt0t1 = (float)(t1.position_screen.x - t0.position_screen.x) / (t1.position_screen.y - t0.position_screen.y);
			float dt0t2 = (float)(t2.position_screen.x - t0.position_screen.x) / (t2.position_screen.y - t0.position_screen.y);
			
			Vertex_t mid;

			mid.position_screen = Vector3_interp(t0.position_screen, t2.position_screen, (t1.position_screen.y - t0.position_screen.y) / (t2.position_screen.y - t0.position_screen.y));

			Vector3 mid_t = Vector3_interp(t0.position_world / t0.position_world.z, t2.position_world / t2.position_world.z, (t1.position_screen.y - t0.position_screen.y) / (t2.position_screen.y - t0.position_screen.y));
			float mid_z = b / (mid.position_screen.z - a);
			mid.position_world = mid_t * mid_z;

			mid.uv = uv_interp(t0.uv, t2.uv, (mid.position_world.y - t0.position_world.y) / (t2.position_world.y - t0.position_world.y));

			if (dt0t2 > dt0t1)
			{
				DrawTriangle(buffer, zbuffer, mesh, t0, t1, mid, a, b, window_w, window_h);
				DrawTriangle(buffer, zbuffer, mesh, t1, mid, t2, a, b, window_w, window_h);
			}

			if (dt0t1 > dt0t2)
			{
				DrawTriangle(buffer, zbuffer, mesh, t0, mid, t1, a, b, window_w, window_h);
				DrawTriangle(buffer, zbuffer, mesh, mid, t1, t2, a, b, window_w, window_h);
			}
		}
	}
}