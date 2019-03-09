#ifndef MESHDATA
#define MESHDATA

#include "src/Triangle.h"
#include "src/Ray.h"


struct mesh {
	triangle* baseMesh;
	int length;
} ;
triangle* createMesh(triangle* baseMesh, int size, double scale, coordinates position) {
	triangle* outputMesh = new triangle[size];
	for (int i = 0; i < size; i++) {
		outputMesh[i] = baseMesh[i]*scale + position;
	}
	return outputMesh;
}

//mesh sizes
int cubeMeshLength = 12;

//mesh definitions
triangle* cubeMesh = new triangle[cubeMeshLength];

//cube
mesh getCubeMesh(double scale, coordinates position) {
	cubeMesh[0] = triangle {{0.5, -0.5, -0.5}, {0.5, -0.5, 0.5}, {0.5, 0.5, 0.5}};
	cubeMesh[1] = triangle {{0.5, -0.5, -0.5}, {0.5, 0.5, 0.5}, {0.5, 0.5, -0.5}};
	cubeMesh[2] = triangle {{-0.5, -0.5, -0.5}, {-0.5, 0.5, 0.5}, {-0.5, -0.5, 0.5}};
	cubeMesh[3] = triangle {{-0.5, -0.5, -0.5}, {-0.5, 0.5, -0.5}, {-0.5, 0.5, 0.5}};
	cubeMesh[4] = triangle {{-0.5, -0.5, -0.5}, {0.5, -0.5, -0.5}, {0.5, 0.5, -0.5}};
	cubeMesh[5] = triangle {{-0.5, -0.5, -0.5}, {0.5, 0.5, -0.5}, {-0.5, 0.5, -0.5}};
	cubeMesh[6] = triangle {{0.5, -0.5, 0.5}, {-0.5, -0.5, 0.5}, {0.5, 0.5, 0.5}};
	cubeMesh[7] = triangle {{0.5, 0.5, 0.5}, {-0.5, -0.5, 0.5}, {-0.5, 0.5, 0.5}};
	cubeMesh[8] = triangle {{-0.5, -0.5, 0.5}, {0.5, -0.5, 0.5}, {0.5, -0.5, -0.5}};
	cubeMesh[9] = triangle {{-0.5, -0.5, 0.5}, {0.5, -0.5, -0.5}, {-0.5, -0.5, -0.5}};
	cubeMesh[10] = triangle {{-0.5, 0.5, 0.5}, {0.5, 0.5, -0.5}, {0.5, 0.5, 0.5}};
	cubeMesh[11] = triangle {{-0.5, 0.5, 0.5}, {-0.5, 0.5, -0.5}, {0.5, 0.5, -0.5}};
	return mesh {createMesh(cubeMesh, cubeMeshLength, scale, position), cubeMeshLength};
}
#endif
