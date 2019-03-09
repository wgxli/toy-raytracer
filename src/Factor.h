#ifndef FACTOR_H
#define FACTOR_H

class Entity;
#include "Ray.h"
#include "Intersection.h"

class Factor {
	public:
	Factor ();
	virtual double getFactor(intersection, Entity* [], int, ray, int) const;
} ;
class constantFactor : public Factor {
	public:
	double factor;
	constantFactor (double);
	double getFactor(intersection, Entity* [], int, ray, int) const;
} ;
class fresnelFactor : public Factor {
	public:
	double IOR;
	fresnelFactor (double);
	double getFactor(intersection, Entity* [], int, ray, int) const;
} ;
#endif
