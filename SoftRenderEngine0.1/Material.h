#pragma once
#include "ColorRGBA.h"
#include "Texture2D.h"
#include <string>

std::string WString2String(std::wstring wstr);
std::wstring String2WString(std::string str);

class Material
{
public:
	Material(ColorRGBA, float, float, float, float, string);
	~Material();
	ColorRGBA color;
	float ka, kd, ks, power;
	Texture2D* texture;
private:

};

Material::Material(ColorRGBA input_color,
	float input_ka, float input_kd, float input_ks, float input_power, 
	string filePath):
	color(input_color),
	ka(input_ka), kd(input_kd), ks(input_ks), power(input_power)
{
	wstring Tex_path = String2WString(filePath);
	texture = new Texture2D(Tex_path);
	texture->LoadBitmapToColorArray();
}

Material::~Material()
{
	if (texture != NULL) delete texture;
}


std::string WString2String(std::wstring wstr)
{
	std::string result;
	int len = WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), wstr.size(), NULL, 0, NULL, NULL);
	if (len <= 0)
		return result;

	char* buffer = new char[len + 1];
	if (buffer == NULL)
		return result;

	WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), wstr.size(), buffer, len, NULL, NULL);
	buffer[len] = '\0';               //�ַ�����β
	result.append(buffer);            //��ֵ
	delete[] buffer;                  //ɾ��������

	return result;
}

std::wstring String2WString(std::string str)
{
	std::wstring result;

	int len = MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), NULL, 0);
	if (len < 0)
		return result;

	wchar_t* buffer = new wchar_t[len + 1];
	if (buffer == NULL)
		return result;

	MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), buffer, len);

	buffer[len] = '\0';                    //�ַ�����β
	result.append(buffer);                 //��ֵ
	delete[] buffer;                       //ɾ��������

	return result;
}