#pragma once

class ColorRGBA
{
public:
	ColorRGBA();
	ColorRGBA(float, float, float, float);
	~ColorRGBA();
	float r, g, b, a;
	ColorRGBA operator= (ColorRGBA&);
	ColorRGBA operator+ (ColorRGBA&);
	ColorRGBA operator+ (float);
	ColorRGBA operator- (ColorRGBA&);
	ColorRGBA operator- (float);
	ColorRGBA operator* (ColorRGBA&);
	ColorRGBA operator* (float);
	ColorRGBA operator/ (float);
	static ColorRGBA BLACK;
	static ColorRGBA WHITE;
	static ColorRGBA RED;
	static ColorRGBA GREEN;
	static ColorRGBA BLUE;
	static ColorRGBA YELLOW;
private:

};

ColorRGBA ColorRGBA::BLACK = ColorRGBA(0, 0, 0, 1);
ColorRGBA ColorRGBA::WHITE = ColorRGBA(1, 1, 1, 1);
ColorRGBA ColorRGBA::RED = ColorRGBA(1, 0, 0, 1);
ColorRGBA ColorRGBA::GREEN = ColorRGBA(0, 1, 0, 1);
ColorRGBA ColorRGBA::BLUE = ColorRGBA(0, 0, 1, 1);
ColorRGBA ColorRGBA::YELLOW = ColorRGBA(0, 1, 1, 1);

ColorRGBA::ColorRGBA() :r(0), g(0), b(0)
{
}

ColorRGBA::ColorRGBA(float input_r, float input_g, float input_b, float input_a)
	: r(input_r), g(input_g), b(input_b), a(input_a)
{
}

ColorRGBA::~ColorRGBA()
{
}

ColorRGBA ColorRGBA::operator= (ColorRGBA &c) {
	r = c.r;
	g = c.g;
	b = c.b;
	a = c.a;
	return *this;
}


ColorRGBA ColorRGBA::operator+ (ColorRGBA &c) {
	return ColorRGBA(r + c.r, g + c.g, b + c.b, a + c.a);
}

ColorRGBA ColorRGBA::operator- (ColorRGBA &c) {
	return ColorRGBA(r - c.r, g - c.g, b - c.b, a - c.a);
}

ColorRGBA ColorRGBA::operator+ (float f) {
	return ColorRGBA(r + f, g + f, b + f, a + f);
}

ColorRGBA ColorRGBA::operator- (float f) {
	return ColorRGBA(r - f, g - f, b - f, a - f);
}

ColorRGBA ColorRGBA::operator* (ColorRGBA &c) {
	return ColorRGBA(r * c.r, g * c.g, b * c.b, a * c.a);
}

ColorRGBA ColorRGBA::operator* (float f) {
	return ColorRGBA(r * f, g * f, b * f, a * f);
}

ColorRGBA ColorRGBA::operator/ (float f) {
	return ColorRGBA(r / f, g / f, b / f, a / f);
}