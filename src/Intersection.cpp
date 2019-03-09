#include "Intersection.h"
#include <iostream>

//Intersection
void intersection::printInfo() const {
	position.printInfo();
	printf("@%f, ", distance);
	printf(isEntering?"Entering":"Exiting");
}
