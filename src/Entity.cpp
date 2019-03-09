#include "Entity.h"
#include "Shader.h"
#include "Color.h"
#include "Ray.h"
#include <iostream>
#include <cmath>

//Entity
Entity::Entity (double x, double y, double z, Shader* material) {
	position = {x, y, z};
	this->material = material;
}
color Entity::getColor(intersection entityInfo, ray incomingRay, int iterations, Entity* *objectList, int size) const {
	return material->getColor(entityInfo, objectList, size, incomingRay, iterations);
}
intersection Entity::getIntersection(ray incomingRay) const {
	return intersection {-1.0, true, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}};
}
void Entity::printInfo() const {
	position.printInfo();
	printf(" with shader ");
	material->printInfo();
}

//Background
Background::Background (Shader* material) : Entity(0, 0, 0, material) {}

//Sphere
Sphere::Sphere (double x, double y, double z, Shader* material, double radius) : Entity(x, y, z, material) {
	this->radius = radius;
}
intersection Sphere::getIntersection(ray incomingRay) const {
	coordinates positionDifference = position - incomingRay.position;
	double dotProduct = incomingRay.direction * positionDifference;
	double discriminant = dotProduct*dotProduct - positionDifference.lengthSquared() + radius*radius;
	double distance;
	coordinates intersectionPosition;
	if (discriminant < 0) {
		return intersection {-1.0, true, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}};
	}
	if (dotProduct*dotProduct-discriminant > 0.001) {
		distance = dotProduct-sqrt(discriminant);
		intersectionPosition = incomingRay.tracePosition(distance);
		return intersection {distance, true, intersectionPosition, (intersectionPosition-position).normalize()};
	} else {
		distance = dotProduct+sqrt(discriminant);
		intersectionPosition = incomingRay.tracePosition(distance);
		return intersection {distance, false, intersectionPosition, (intersectionPosition-position).normalize()};
	}
}

//Floor
Floor::Floor (double y, Shader* material) : Entity(0, y, 0, material) {}
intersection Floor::getIntersection(ray incomingRay) const {
	double distance = (position.y-incomingRay.position.y)/incomingRay.direction.y;
	return intersection {distance, true, incomingRay.tracePosition(distance), {0.0, -1.0, 0.0}};
}


//Triangle
Triangle::Triangle (triangle internalTriangle, Shader* material) : Entity(0, 0, 0, material) {
	this->internalTriangle = internalTriangle;
	this->normal = internalTriangle.getNormal();
}
intersection Triangle::getIntersection(ray incomingRay) const {
	return internalTriangle.getIntersection(incomingRay, normal);
}

//Mesh
Mesh::Mesh (triangle* triangleList, int length, Shader* material) : Entity(0, 0, 0, material) {
	this->triangleList = triangleList;
	this->length = length;
	normalList = new coordinates[length];
	coordinates centroid = {0, 0, 0};
	for (int i = 0; i < length; i++) {
		triangle currentTriangle = triangleList[i];
		normalList[i] = currentTriangle.getNormal();
		centroid = centroid + currentTriangle.vertex1 + currentTriangle.vertex2 + currentTriangle.vertex3;
	}
	position = centroid.scale(0.333333/length);
	calculateRadius();
}
Mesh::~Mesh() {
	delete normalList;
	delete triangleList;
}
void Mesh::calculateRadius() {
	double maxDistance = 0.0;
	for (int i = 0; i < length; i++) {
		triangle currentTriangle = triangleList[i];
		double distance1 = (currentTriangle.vertex1-position).lengthSquared();
		double distance2 = (currentTriangle.vertex2-position).lengthSquared();
		double distance3 = (currentTriangle.vertex3-position).lengthSquared();
		if (distance1 > maxDistance) {maxDistance = distance1;}
		if (distance2 > maxDistance) {maxDistance = distance2;}
		if (distance3 > maxDistance) {maxDistance = distance3;}
	}
	radius = sqrt(maxDistance);
}
bool Mesh::checkBoundingSphere(ray incomingRay) const {
	coordinates positionDifference = position - incomingRay.position;
	double dotProduct = incomingRay.direction * positionDifference;
	double discriminant = dotProduct*dotProduct - positionDifference.lengthSquared() + radius*radius;
	if (discriminant < 0) {return false;}
	return true;
}
intersection Mesh::getIntersection(ray incomingRay) const {
	if (!checkBoundingSphere(incomingRay)) {return intersection {-1.0, true, {0, 0, 0}, {0, 0, 0}};}
	double minDistance = 9999999.9;
	intersection output = {-1.0, true, {0, 0, 0}, {0, 0, 0}};
	for (int i = 0; i < length; i++) {
		intersection triangleIntersection = triangleList[i].getIntersection(incomingRay, normalList[i]);
		if (triangleIntersection.distance>0.001 && triangleIntersection.distance<minDistance) {
			minDistance = triangleIntersection.distance;	       
			output = triangleIntersection;
		}
	}
	return output;
}
