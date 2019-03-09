#include "Factor.h"
#include <cmath>

Factor::Factor() {}
double Factor::getFactor(intersection entityInfo, Entity* *objectList, int size, ray incomingRay, int iterations) const {
	return 0.5;
}

//constantFactor
constantFactor::constantFactor(double factor) {
	this->factor = factor;
}
double constantFactor::getFactor(intersection entityInfo, Entity* *objectList, int size, ray incomingRay, int iterations) const {
	return factor;
}

//fresnelFactor
fresnelFactor::fresnelFactor(double IOR) {
	this->IOR = IOR;
}
double fresnelFactor::getFactor(intersection entityInfo, Entity* *objectList, int size, ray incomingRay, int iterations) const {
	coordinates normal = entityInfo.normal;
	coordinates direction = incomingRay.direction;
	double sPolarized;
	double pPolarized;
	if (entityInfo.isEntering) {
		double cosTheta1 = 0-direction * normal;
		double cosTheta2 = sqrt((cosTheta1*cosTheta1-1)/(IOR*IOR)+1);
		sPolarized = (cosTheta1-IOR*cosTheta2)/(cosTheta1+IOR*cosTheta2);
		pPolarized = (cosTheta2-IOR*cosTheta1)/(cosTheta2+IOR*cosTheta1);
	} else {
		double cosTheta1 = direction * normal;
		double discriminant = (cosTheta1*cosTheta1-1)*IOR*IOR+1;
		if (discriminant > 0) {
			double cosTheta2 = sqrt(discriminant);
			sPolarized = (IOR*cosTheta1-cosTheta2)/(IOR*cosTheta1+cosTheta2);
			pPolarized = (IOR*cosTheta2-cosTheta1)/(IOR*cosTheta2+cosTheta1);
		} else {
			return 0;
		}
	}
	sPolarized *= sPolarized;
	pPolarized *= pPolarized;
	return (2-sPolarized-pPolarized)/2;
}
