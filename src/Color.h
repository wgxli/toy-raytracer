#ifndef COLOR_H
#define COLOR_H

struct color;

struct charColor {
	unsigned char r;
	unsigned char g;
	unsigned char b;
	color toColor() const;
} ;

struct color {
	double r;
	double g;
	double b;
	color operator+(color) const;
	color operator*(color) const;
	color fade(double) const;
	charColor toCharColor() const;
	void printInfo() const;
} ;
#endif
