#include <iostream>
#include "src/Ray.h"
#include "src/Shader.h"
#include "src/Entity.h"
#include "src/Screen.h"
#include "src/Factor.h"
#include "src/Triangle.h"
#include "meshData.h"
#include <cmath>

int main() {
	int SCREEN_WIDTH = 600;
	int SCREEN_HEIGHT = 600;
	int NUM_OBJECTS = 4;
	int SAMPLES = 200;
	int ITERATIONS = 7;

	// Camera Options
	coordinates CAMERA_LOCATION = {0.1, 0, 0};
	bool ENABLE_DEPTH_OF_FIELD = true;
	double CAMERA_FOCAL_LENGTH = 5.0;
	double DEPTH_OF_FIELD_EFFECT = 0.1;

	//Colors
	color red {0.8, 0.2, 0.2};
	color yellow {0.8, 0.8, 0.2};
	color green {0.2, 0.8, 0.2};
	color blue {0.2, 0.2, 0.8};
	color black {0.2, 0.2, 0.2};
	color white {0.8, 0.8, 0.8};

	//Shaders
	fresnelFactor* glassFresnel = new fresnelFactor(1.5);
	glossyShader* redMirror = new glossyShader(red);
	glossyShader* blueMirror = new glossyShader(blue);
	diffuseShader* whiteDiffuse = new diffuseShader(white);
	diffuseShader* blackDiffuse = new diffuseShader(black);
	glassShader* glass = new glassShader(white, 1.5);
	checkerboardShader* chessBoard = new checkerboardShader(whiteDiffuse, blackDiffuse);

	//Objects
	Sphere* sphere1 = new Sphere(-0.9, 0.4, 5.0, glass, 2.0);
	Sphere* sphere2 = new Sphere(1.7, 1.4, 5.0, blueMirror, 1.0);
	Floor* floor = new Floor(2.4, chessBoard);
	Mesh* cube = new Mesh(getCubeMesh(1.0, {1.0, 1.895, 3.5}).baseMesh, cubeMeshLength, glass);

	//Object List
	Entity* objectList[NUM_OBJECTS];
	objectList[0] = sphere1;
	objectList[1] = sphere2;
	objectList[2] = floor;
	objectList[3] = cube;

	//Tracer Code
	double focus = 0.6*sqrt(SCREEN_WIDTH * SCREEN_HEIGHT);
	screen mainScreen = {SCREEN_WIDTH, SCREEN_HEIGHT, focus, CAMERA_FOCAL_LENGTH, DEPTH_OF_FIELD_EFFECT, ENABLE_DEPTH_OF_FIELD};
	mainScreen.createImage(objectList, NUM_OBJECTS, ITERATIONS, SAMPLES, CAMERA_LOCATION, "output.bmp");

	//Cleanup
	//Shaders
	delete redMirror;
	delete blueMirror;
	delete whiteDiffuse;
	delete blackDiffuse;
	delete glass;
	delete chessBoard;
	//Objects
	delete sphere1;
	delete sphere2;
	delete floor;
	delete cube;
	return 0;
}
