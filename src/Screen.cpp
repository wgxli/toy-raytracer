#include "Screen.h"
#include "Entity.h"
#include "Ray.h"
#include <iostream>
#include "lib/bitmap_image.hpp"

double const ADAPTIVE_SAMPLE_TOLERANCE = 0.02;

bool compare(double val1, double val2, int samples) {
	double difference = val1-val2;
	double epsilon = ADAPTIVE_SAMPLE_TOLERANCE * samples;
	return (difference < epsilon && difference > -epsilon);
}
bool closeEnough(color color1, color color2, int samples) {
	return (compare(color1.r, color2.r, samples) && compare(color1.g, color2.g, samples) && compare(color1.b, color2.b, samples));
}


void screen::createImage(Entity* *objectList, int size, int iterations, int samples, coordinates cameraPosition, std::string filename) const {
	bitmap_image finishedImage (width, height);
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			color pixelColor = {0, 0, 0};
			color sampleColor = {0, 0, 0};
			int sample = 0;
			for (sample = 0; sample < samples; sample++) {
				if (enableDOF) {
					sampleColor = (pixel {(double)(x-width/2), (double)(y-height/2)}).getColor(focus, cameraFocus, DOF, iterations, cameraPosition, objectList, size);
				} else {
					sampleColor = (pixel {(double)(x-width/2), (double)(y-height/2)}).getColor(focus, iterations, cameraPosition, objectList, size);
				}
				//Adaptive Sampling
				if (sample > 7 && closeEnough(sampleColor.fade(sample), pixelColor, sample)) {
					break;
				}
				pixelColor = pixelColor + sampleColor;
			}
			charColor finalColor = pixelColor.fade(1.0/sample).toCharColor();
			finishedImage.set_pixel(x, y, finalColor.r, finalColor.g, finalColor.b);
		}
		printf("%d%% complete.\n", 100*(y+1)/height);
	}
	finishedImage.save_image(filename);
}
			
