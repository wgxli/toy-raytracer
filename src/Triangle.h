#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Ray.h"
#include "Intersection.h"

struct triangle {
	coordinates vertex1;
	coordinates vertex2;
	coordinates vertex3;
	triangle operator+(coordinates) const;
	triangle operator*(double) const;
	coordinates getNormal() const;
	intersection getIntersection(ray, coordinates) const;
	coordinates positionFromBary(double u, double v) const;
} ;
#endif
