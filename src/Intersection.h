#ifndef INTERSECTION_H
#define INTERSECTION_H

#include "Ray.h"
struct intersection {
	double distance;
	bool isEntering;
	coordinates position;
	coordinates normal;
	void printInfo() const;
} ;
#endif
