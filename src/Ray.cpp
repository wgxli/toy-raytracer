#include "Ray.h"
#include "Entity.h"
#include "Color.h"
#include "Shader.h"
#include <iostream>
#include <cmath>
#include <random>

std::default_random_engine generator;
std::uniform_real_distribution<double> jitter (-0.5, 0.5);
std::normal_distribution<double> randNormal (0.0, 1.0);

imageShader* BACKGROUND_SHADER = new imageShader();
Entity* DEFAULT_BACKGROUND = new Background(BACKGROUND_SHADER);

//coordinates
coordinates coordinates::operator+(coordinates other) const {
	return coordinates {x+other.x, y+other.y, z+other.z};
}
coordinates coordinates::operator-(coordinates other) const {
	return coordinates {x-other.x, y-other.y, z-other.z};
}
double coordinates::operator*(coordinates other) const {
	return x*other.x + y*other.y + z*other.z;
}
coordinates coordinates::cross(coordinates other) const {
	return coordinates {y*other.z-z*other.y, z*other.x-x*other.z, x*other.y-y*other.x};
}
coordinates coordinates::scale(double factor) const {
	return coordinates {x*factor, y*factor, z*factor};
}
coordinates coordinates::normalize() const {
	return scale(1.0/length());
}
void coordinates::printInfo() const {
	printf("(%f, %f, %f)", x, y, z);
}
double coordinates::lengthSquared() const {
	return x*x + y*y + z*z;
}
double coordinates::length() const {
	return sqrt(lengthSquared());
}
//ray
coordinates ray::tracePosition(double distance) const {
	return position + direction.scale(distance);
}
ray ray::randomizeDirection() const {
	coordinates newDirection = (coordinates {randNormal(generator), randNormal(generator), randNormal(generator)}).normalize();
	return ray {position, newDirection};
}
color ray::getColor(Entity* *objectList, int size, int iterations) const {
	double minDistance = 999999999.9;
	Entity* minEntity = DEFAULT_BACKGROUND;
	intersection minIntersection =  {-1.0, true, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}};
	for (int i = 0; i < size; i++) {
		intersection entityIntersection = objectList[i]->getIntersection(ray {position, direction});
		if (entityIntersection.distance > 0.001 && entityIntersection.distance < minDistance) {
			minDistance = entityIntersection.distance;
			minEntity = objectList[i];
			minIntersection = entityIntersection;
		}
	}
	return minEntity->getColor(minIntersection, ray {position, direction}, iterations, objectList, size);
}
void ray::printInfo() const {
	direction.printInfo();
	std::cout << "@";
	position.printInfo();
}

//pixel
ray pixel::project(double focus, coordinates cameraPosition, double cameraFocus, double DOF) const {
	double deltaX = DOF*jitter(generator);
	double deltaY = DOF*jitter(generator);
	coordinates direction = {x + jitter(generator) - focus*deltaX/cameraFocus, y + jitter(generator) - focus*deltaY/cameraFocus, focus};
	return ray {{deltaX + cameraPosition.x, deltaY + cameraPosition.y, cameraPosition.z}, direction.normalize()};
}
ray pixel::project(double focus, coordinates cameraPosition) const {
	coordinates direction = {x + jitter(generator), y + jitter(generator), focus};
	return ray {cameraPosition, direction.normalize()};
}

color pixel::getColor(double focus, int iterations, coordinates cameraPosition, Entity* *objectList, int size) const {
	return project(focus, cameraPosition).getColor(objectList, size, iterations);
}
color pixel::getColor(double focus, double cameraFocus, double DOF, int iterations, coordinates cameraPosition, Entity* *objectList, int size) const {
	return project(focus, cameraPosition, cameraFocus, DOF).getColor(objectList, size, iterations);
}
