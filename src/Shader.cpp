#include "Shader.h"
#include "Factor.h"
#include <iostream>
#include <cmath>
#include "lib/bitmap_image.hpp"

bitmap_image BACKGROUND_IMAGE ("HDR.bmp");

//Shader
Shader::Shader () {}
Shader::Shader (color baseColor) {
	this->baseColor = baseColor;
}
color Shader::getColor(intersection entityInfo, Entity* *objectList, int size, ray incomingRay, int iterations) const {
	return baseColor;
}
void Shader::printInfo() const {
	baseColor.printInfo();
}

//emissionShader
emissionShader::emissionShader (color baseColor) : Shader(baseColor) {}
color emissionShader::getColor(intersection entityInfo, Entity* *objectList, int size, ray incomingRay, int iterations) const {
	return baseColor;
}
void emissionShader::printInfo() const {
	printf("Emission, color ");
	baseColor.printInfo();
}

//diffuseShader
diffuseShader::diffuseShader (color baseColor) : Shader(baseColor) {}
color diffuseShader::getColor(intersection entityInfo, Entity* *objectList, int size, ray incomingRay, int iterations) const {
	if (iterations < 0) {return baseColor;}
	coordinates normal = entityInfo.normal;
	color outputColor = {0, 0, 0};
	for (int i = 0; i < 5; i++) {
		ray outgoingRay = (ray {entityInfo.position, {0, 0, 0}}).randomizeDirection();
		outputColor = outputColor + outgoingRay.getColor(objectList, size, iterations-3);
	}
	return baseColor * outputColor.fade(0.2);
}
void diffuseShader::printInfo() const {
	printf("Diffuse, color ");
	baseColor.printInfo();
}

//glossyShader
glossyShader::glossyShader (color baseColor) : Shader(baseColor) {}
color glossyShader::getColor(intersection entityInfo, Entity* *objectList, int size, ray incomingRay, int iterations) const {
	if (iterations < 0) {return baseColor;}
	coordinates normal = entityInfo.normal;
	coordinates direction = incomingRay.direction;
	coordinates newDirection = direction - normal.scale(2.0*(direction*normal));
	ray outgoingRay = {entityInfo.position, newDirection.normalize()};
	return baseColor * outgoingRay.getColor(objectList, size, iterations-1);
}
void glossyShader::printInfo() const {
	printf("Glossy, color ");
	baseColor.printInfo();
}

//refractiveShader
refractiveShader::refractiveShader (color baseColor, double IOR) : Shader(baseColor) {this->IOR = IOR;}
color refractiveShader::getColor(intersection entityInfo, Entity* *objectList, int size, ray incomingRay, int iterations) const {
	if (iterations < 0) {return baseColor;}
	coordinates normal = entityInfo.normal;
	coordinates direction = incomingRay.direction;
	coordinates newDirection;
	ray outgoingRay;
	if (entityInfo.isEntering) {
		double cosTheta1 = 0-direction*normal;
		double cosTheta2 = sqrt((cosTheta1*cosTheta1-1)/(IOR*IOR)+1);
		newDirection = direction + normal.scale(cosTheta1 - IOR*cosTheta2);
	} else {
		double cosTheta1 = direction*normal;
		double discriminant = (cosTheta1*cosTheta1-1)*IOR*IOR+1;
		if (discriminant>0) {
			double cosTheta2 = sqrt(discriminant);
			newDirection = direction + normal.scale(cosTheta2/IOR - cosTheta1);
		} else {
			newDirection = direction - normal.scale(2.0*(direction*normal));
		}
	}
	outgoingRay = {entityInfo.position, newDirection.normalize()};
	return baseColor * outgoingRay.getColor(objectList, size, iterations-1);
}
void refractiveShader::printInfo() const {
	printf("Refractive, color ");
	baseColor.printInfo();
	printf(", IOR %f", IOR);
}

//imageShader
imageShader::imageShader () : Shader(color {0, 0, 0}) {
	width = BACKGROUND_IMAGE.width();
	height = BACKGROUND_IMAGE.height();
}
color imageShader::getColor(intersection entityInfo, Entity* *objectList, int size, ray incomingRay, int iterations) const {
	coordinates direction = incomingRay.direction;
	double x = (atan2(direction.x, direction.z) + 3.14159265358979323)/6.283185071795;
	double y = (atan2(direction.y, sqrt(direction.x*direction.x+direction.z*direction.z)) + 1.5707963)/3.14159265358979323;
	unsigned char r;
	unsigned char g;
	unsigned char b;
	BACKGROUND_IMAGE.get_pixel((int)(x*width), (int)(y*height), r, g, b);
	return (charColor {r, g, b}).toColor();
}
void imageShader::printInfo() const {
	printf("Image");
}


//checkerboardShader
checkerboardShader::checkerboardShader (Shader* shader1, Shader* shader2) : Shader(color {0.5, 0.5, 0.5}) {
	this->shader1 = shader1;
	this->shader2 = shader2;
}
color checkerboardShader::getColor(intersection entityInfo, Entity* *objectList, int size, ray incomingRay, int iterations) const {
	if (iterations < 0) {return baseColor;}
	if ((int)(floor(entityInfo.position.x) + floor(entityInfo.position.z))%2 == 0) {
		return shader1->getColor(entityInfo, objectList, size, incomingRay, iterations);
	} else {
		return shader2->getColor(entityInfo, objectList, size, incomingRay, iterations);
	}
}
void checkerboardShader::printInfo() const {
	printf("Checkerboard, shaders ");
	shader1->printInfo();
	printf(" and ");
	shader2->printInfo();
}

//mixShader
mixShader::mixShader (Shader* shader1, Shader* shader2, Factor* factor) : Shader(color {0.5, 0.5, 0.5}) {
	this->shader1 = shader1;
	this->shader2 = shader2;
	this->factor = factor;
}
color mixShader::getColor(intersection entityInfo, Entity* *objectList, int size, ray incomingRay, int iterations) const {
	if (iterations < 0) {return baseColor;}
	double fadeFactor = factor->getFactor(entityInfo, objectList, size, incomingRay, iterations);
	color outputColor = shader1->getColor(entityInfo, objectList, size, incomingRay, iterations).fade(fadeFactor);
	outputColor = outputColor + shader2->getColor(entityInfo, objectList, size, incomingRay, iterations).fade(1-fadeFactor);
	return outputColor;
}
void mixShader::printInfo() const {
	printf("Mix Shader, shaders ");
	shader1->printInfo();
	printf(" and ");
	shader2->printInfo();
}

//glassShader
glassShader::glassShader (color baseColor, double IOR) : Shader(baseColor) {
	this->IOR = IOR;
	refraction = new refractiveShader(baseColor, IOR);
	reflection = new glossyShader(baseColor);
	fresnel = new fresnelFactor(IOR);
	mainShader = new mixShader(refraction, reflection, fresnel);
}
glassShader::~glassShader () {
	delete mainShader;
	delete fresnel;
	delete reflection;
	delete refraction;
}
color glassShader::getColor(intersection entityInfo, Entity* *objectList, int size, ray incomingRay, int iterations) const {
	return mainShader->getColor(entityInfo, objectList, size, incomingRay, iterations);
}
void glassShader::printInfo() const {
	printf("Glass Shader, color ");
	baseColor.printInfo();
	printf(", IOR %f", IOR);
}
