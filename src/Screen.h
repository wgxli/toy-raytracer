#ifndef SCREEN_H
#define SCREEN_H

#include "Entity.h"
#include "Ray.h"
#include <iostream>

struct screen {
	int width;
	int height;
	double focus;
	double cameraFocus;
	double DOF;
	bool enableDOF;
	void createImage(Entity* [], int, int, int, coordinates, std::string) const;
} ;
#endif
