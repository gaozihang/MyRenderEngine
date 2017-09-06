// SoftRenderEngine_ver0.1
// 2017/09/02 
#include <windows.h>
#include <iostream>
#include "CalFPS.h"
#include "Application.h"
#include "Material.h"
#include "ColorRGBA.h"
#include "Matrix4x4.h"
#include "Camera.h"
#include "Geometry.h"
#include "Rasterizer.h"

#pragma warning (disable : 4996) 

#define WINDOW_TITLE   L"GaoniiSoftRenderEngine0.1"
#define MAX(a, b) ((a) > (b) ? (a): (b))

#define window_w  640
#define window_h  480
#define Near 1
#define Far 20

enum  DisplayMode
{
	POINT_FRAME_MODE, WIRE_FRAME_MODE, RASTER_FRAME_MODE
};
DisplayMode MyDisplayMode = POINT_FRAME_MODE;

bool m_keys[256];
byte buffer[window_w * window_h * 4];
float zbuffer[window_w * window_h];

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
void UpdateScene(Mesh*);
void UpdateBuffer(HWND);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	memset(m_keys, 0, sizeof(m_keys));

	WNDCLASSEX wndclass = { 0 };
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = (HICON)::LoadImage(NULL, L"icon.ico", IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = WINDOW_TITLE;
	if (!RegisterClassEx(&wndclass))
		return -1;

	HWND hwnd;
	hwnd = CreateWindow(WINDOW_TITLE, WINDOW_TITLE, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, window_w, window_h, NULL, NULL, hInstance, NULL);
	MoveWindow(hwnd, 250, 80, window_w, window_h, true);

	ShowWindow(hwnd, nShowCmd);
	UpdateWindow(hwnd);

	// add console to print log
	AllocConsole();
	freopen("CONOUT$", "w", stdout);
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SMALL_RECT rc = { 0, 0, 60, 30 };
	SetConsoleWindowInfo(hOut, 1, &rc);

	// eye, lookat, up
	uvnCamera camera(Vector3(0, 0, 0), Vector3(0, 0, 1), Vector3(0, 1, 0));

	// name, position, rotation, vertices_number, faces_number
	Mesh mesh("cube", Vector3(0, 0, 10), Vector3::ZERO, 8, 12);
	Material material(ColorRGBA::WHITE, 1, 1, 1, 0, "tex.bmp");
	InitCube(&mesh, &material);

	CalFPS fps;
	fps.init();

	MSG msg = { 0 };
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			UpdateScene(&mesh);
			//fov = 3.1415926 / , Near = 1, Far = 20
			Geometry(&mesh, &camera, window_w, window_h,
				3.1415926 / 8, Near, Far);

			if (MyDisplayMode == POINT_FRAME_MODE)
				DrawPoint(buffer, &mesh, window_w, window_h, ColorRGBA(1, 1, 0, 1));
			if (MyDisplayMode == WIRE_FRAME_MODE)
				DrawWire(buffer, &mesh, window_w, window_h, ColorRGBA(1, 1, 0, 1));
			if (MyDisplayMode == RASTER_FRAME_MODE)
				Rasterizer(buffer, zbuffer, &mesh, Near, Far, window_w, window_h);

			UpdateBuffer(hwnd);
			fps.printFPS();
		}
	}
	UnregisterClass(L"GaoniiSoftRenderEngine", wndclass.hInstance);
	return 0;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_PAINT:

		ValidateRect(hwnd, NULL);
		break;

	case WM_KEYDOWN:
		m_keys[(unsigned int)wParam] = true;

		if (wParam == VK_ESCAPE)
			DestroyWindow(hwnd);
		break;

	case WM_KEYUP:
		m_keys[(unsigned int)wParam] = false;
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default: return DefWindowProc(hwnd, message, wParam, lParam);
	}
	return 0;
}

void UpdateScene(Mesh* mesh)
{
	mesh->rotation.x += 0.01;
	mesh->rotation.y += 0.01;
	//mesh->rotation.z += 0.01;

	//cout << "rotationz(x, y): " << mesh->rotation.x << " " << mesh->rotation.y << endl;


	if (m_keys['1'] == true)
		MyDisplayMode = POINT_FRAME_MODE;

	else if (m_keys['2'] == true)
		MyDisplayMode = WIRE_FRAME_MODE;

	else if (m_keys['3'] == true)
		MyDisplayMode = RASTER_FRAME_MODE;

	ClearBackBuffer(buffer, zbuffer, window_w, window_h, ColorRGBA(0, 0, 0, 1));
}

void UpdateBuffer(HWND hwnd)
{
	//´´½¨Î»Í¼
	static BITMAPINFO binfo;
	ZeroMemory(&binfo, sizeof(BITMAPINFO));
	binfo.bmiHeader.biBitCount = 32;
	binfo.bmiHeader.biCompression = BI_RGB;
	binfo.bmiHeader.biHeight = -window_h;
	binfo.bmiHeader.biPlanes = 1;
	binfo.bmiHeader.biSizeImage = 0;
	binfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	binfo.bmiHeader.biWidth = window_w;

	HDC hdc = GetDC(hwnd);

	StretchDIBits(hdc, 0, 0, window_w,
		window_h, 0, 0, window_w,
		window_h, buffer, (BITMAPINFO*)&binfo,
		DIB_RGB_COLORS, SRCCOPY);

	ReleaseDC(hwnd, hdc);
}