#include "Triangle.h"
#include "Ray.h"

triangle triangle::operator+(coordinates translation) const {
	return triangle {vertex1+translation, vertex2+translation, vertex3+translation};
}
triangle triangle::operator*(double factor) const {
	return triangle {vertex1.scale(factor), vertex2.scale(factor), vertex3.scale(factor)};
}
coordinates triangle::getNormal() const {
	return (vertex3-vertex1).cross(vertex2-vertex1).normalize();
}
intersection triangle::getIntersection(ray incomingRay, coordinates normal) const {
	coordinates edge1 = vertex2-vertex1;
	coordinates edge2 = vertex3-vertex1;
	coordinates direction = incomingRay.direction;
	coordinates P = direction.cross(edge2);
	double determinant = edge1 * P;
	if (determinant>-0.001 && determinant<0.001) {
		return {-1.0, true, {0, 0, 0}, normal};
	}
	double invDet = 1/determinant;
	coordinates T = incomingRay.position - vertex1;
	double u = (T*P) * invDet;
	if (u<0 || u>1) {
		return {-1.0, true, {0, 0, 0}, normal};
	}
	coordinates Q = T.cross(edge1);
	double v = (direction*Q) * invDet;
	if (v<0 || u+v>1) {
		return {-1.0, true, {0, 0, 0}, normal};
	}
	double t = (edge2*Q)*invDet;
	return {t, (direction * normal < 0), incomingRay.tracePosition(t), normal};
}
coordinates triangle::positionFromBary(double u, double v) const {
	return vertex1.scale(1-u-v) + vertex2.scale(u) + vertex3.scale(v);
}
