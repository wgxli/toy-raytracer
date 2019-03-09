#ifndef SHADER_H
#define SHADER_H

class Entity;
#include "Color.h"
#include "Ray.h"
#include "Intersection.h"
#include "Factor.h"

class Shader {
	public:
	color baseColor;
	Shader ();
	Shader (color);
	virtual color getColor(intersection, Entity* [], int, ray, int) const;
	virtual void printInfo() const;
} ;

//Base Shaders
class emissionShader : public Shader {
	public:
	emissionShader(color);
	color getColor(intersection, Entity* [], int, ray, int) const;
	void printInfo() const;
} ;
class diffuseShader : public Shader {
	public:
	diffuseShader(color);
	color getColor(intersection, Entity* [], int, ray, int) const;
	void printInfo() const;
} ;
class glossyShader : public Shader {
	public:
	glossyShader(color);
	color getColor(intersection, Entity* [], int, ray, int) const;
	void printInfo() const;
} ;
class refractiveShader : public Shader {
	public:
	double IOR;
	refractiveShader(color, double);
	color getColor(intersection, Entity* [], int, ray, int) const;
	void printInfo() const;
} ;
class imageShader : public Shader {
	public:
	int width;
	int height;
	imageShader ();
	color getColor(intersection, Entity* [], int, ray, int) const;
	void printInfo() const;
} ;

//Complex Shaders
class mixShader : public Shader {
	public:
	Shader* shader1;
	Shader* shader2;
	Factor* factor;
	mixShader(Shader*, Shader*, Factor*);
	color getColor(intersection, Entity* [], int, ray, int) const;
	void printInfo() const;
} ;
class checkerboardShader : public Shader {
	public:
	Shader* shader1;
	Shader* shader2;
	checkerboardShader(Shader*, Shader*);
	color getColor(intersection, Entity* [], int, ray, int) const;
	void printInfo() const;
} ;

//Hybrid Shaders
class glassShader : public Shader {
	public:
	double IOR;
	Shader* refraction;
	Shader* reflection;
	Factor* fresnel;
	mixShader* mainShader;
	glassShader (color, double);
	~glassShader ();
	color getColor(intersection, Entity* [], int, ray, int) const;
	void printInfo() const;
} ;
#endif
