#ifndef RAY_H
#define RAY_H

class Entity;
#include "Color.h"

//3D Vector Coordinates
struct coordinates {
	double x;
	double y;
	double z;
	coordinates operator+(coordinates) const;
	coordinates operator-(coordinates) const;
	double operator*(coordinates) const;
	coordinates cross(coordinates) const;
	coordinates scale(double) const;
	coordinates normalize() const;
	double lengthSquared() const;
	double length() const;
	void printInfo() const;
} ;

//Single Ray
struct ray {
	coordinates position;
	coordinates direction;
	coordinates tracePosition(double) const;
	ray randomizeDirection() const;
	color getColor(Entity* [], int, int) const;
	void printInfo() const;
} ;

//Pixel
struct pixel {
	double x;
	double y;
	ray project(double, coordinates) const;
	ray project(double, coordinates, double, double) const;
	color getColor(double, int, coordinates, Entity* [], int) const;
	color getColor(double, double, double, int, coordinates, Entity* [], int) const;
	void printInfo() const;
} ;
#endif
