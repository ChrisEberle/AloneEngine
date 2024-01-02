#pragma once
# include "engine.h"


static int get_fps(int& frameCount, double& lastTime) {
	double currentTime = glfwGetTime();
	frameCount++;
	if (currentTime - lastTime >= 1.0)
	{
		// Calculate and return FPS
		return static_cast<float>(frameCount) / static_cast<float>(currentTime - lastTime);
		frameCount = 0;
		lastTime += 1.0;
	}
	return 0;
}