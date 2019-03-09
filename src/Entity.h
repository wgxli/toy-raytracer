#ifndef ENTITY_H
#define ENTITY_H

class Shader;
#include "Ray.h"
#include "Color.h"
#include "Shader.h"
#include "Intersection.h"
#include "Triangle.h"

class Entity {
	public:
	coordinates position;
	Shader* material;
	Entity (double, double, double, Shader*);
	color getColor(intersection, ray, int, Entity* [], int) const;
	virtual intersection getIntersection(ray) const;
	void printInfo() const;
} ;

class Background : public Entity {
	public:
	Background (Shader*);
} ;

class Sphere : public Entity {
	public:
	double radius;
	Sphere (double, double, double, Shader*, double);
	intersection getIntersection(ray) const;
} ;

class Floor : public Entity {
	public:
	Floor (double, Shader*);
	intersection getIntersection(ray) const;
} ;

class Triangle : public Entity {
	public:
	coordinates normal;
	triangle internalTriangle;
	Triangle (triangle, Shader*);
	intersection getIntersection(ray) const;
} ;

class Mesh : public Entity {
	public:
	int length;
	double radius;
	triangle* triangleList;
	coordinates* normalList;
	Mesh (triangle[], int, Shader*);
	~Mesh ();
	void calculateRadius();
	bool checkBoundingSphere(ray) const;
	intersection getIntersection(ray) const;
} ;
#endif
