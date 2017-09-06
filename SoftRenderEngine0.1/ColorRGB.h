#pragma once

class ColorRGB
{
public:
	ColorRGB();
	ColorRGB(float, float, float);
	~ColorRGB();
	float r, g, b;
	ColorRGB operator= (ColorRGB&);
	ColorRGB operator+ (ColorRGB&);
	ColorRGB operator+ (float);
	ColorRGB operator- (ColorRGB&);
	ColorRGB operator- (float);
	ColorRGB operator* (ColorRGB&);
	ColorRGB operator* (float);
	static ColorRGB BLACK;
	static ColorRGB WHITE;
	static ColorRGB RED;
	static ColorRGB GREEN;
	static ColorRGB BLUE;
	static ColorRGB YELLOW;
private:

};

ColorRGB ColorRGB::BLACK = ColorRGB(0, 0, 0);
ColorRGB ColorRGB::WHITE = ColorRGB(1, 1, 1);
ColorRGB ColorRGB::RED = ColorRGB(1, 0, 0);
ColorRGB ColorRGB::GREEN = ColorRGB(0, 1, 0);
ColorRGB ColorRGB::BLUE = ColorRGB(0, 0, 1);
ColorRGB ColorRGB::YELLOW = ColorRGB(0, 1, 1);

ColorRGB::ColorRGB() :r(0), g(0), b(0)
{
}

ColorRGB::ColorRGB(float input_r, float input_g, float input_b)
	: r(input_r), g(input_g), b(input_b)
{
}

ColorRGB::~ColorRGB()
{
}

ColorRGB ColorRGB::operator= (ColorRGB &c) {
	r = c.r;
	g = c.g;
	b = c.b;
	return *this;
}


ColorRGB ColorRGB::operator+ (ColorRGB &c) {
	return ColorRGB(r + c.r, g + c.g, b + c.b);
}

ColorRGB ColorRGB::operator- (ColorRGB &c) {
	return ColorRGB(r - c.r, g - c.g, b - c.b);
}

ColorRGB ColorRGB::operator+ (float f) {
	return ColorRGB(r + f, g + f, b + f);
}

ColorRGB ColorRGB::operator- (float f) {
	return ColorRGB(r - f, g - f, b - f);
}

ColorRGB ColorRGB::operator* (ColorRGB &c) {
	return ColorRGB(r * c.r, g * c.g, b * c.b);
}

ColorRGB ColorRGB::operator* (float f) {
	return ColorRGB(r * f, g * f, b * f);
}