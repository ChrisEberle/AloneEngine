#pragma once

#include <cmath>

// Function to calculate distance between two 3D points
static float distanceBetween3DPoints(float x1, float y1, float z1, float x2, float y2, float z2) {
	return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2) + pow(z2 - z1, 2));
}


