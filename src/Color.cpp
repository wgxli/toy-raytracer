#include "Color.h"
#include <iostream>
#include <cmath>

//charColor
color charColor::toColor() const {
	double outR = (int)r/255.0;
	double outG = (int)g/255.0;
	double outB = (int)b/255.0;
//	return color {outR*outR, outG*outG, outB*outB};
	return color {outR, outG, outB};
}
//Color
color color::operator+(color other) const {
	return color {r+other.r, g+other.g, b+other.b};
}
color color::operator*(color other) const {
	return color {r*other.r, g*other.g, b*other.b};
}
color color::fade(double factor) const {
	return color {r*factor, g*factor, b*factor};
}
charColor color::toCharColor() const {
//	return charColor {(unsigned char)(sqrt(r)*255), (unsigned char)(sqrt(g)*255), (unsigned char)(sqrt(b)*255)};
	return charColor {(unsigned char)(r*255), (unsigned char)(g*255), (unsigned char)(b*255)};
}
void color::printInfo() const {
	printf("(%f, %f, %f)", r, g, b);
}
