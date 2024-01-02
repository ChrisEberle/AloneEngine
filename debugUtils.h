#pragma once
# include "engine.h"


static int get_fps(int& frameCount, double& lastTime) {
	double currentTime = glfwGetTime();
	frameCount++;
	if (currentTime - lastTime >= 1.0)
	{
		// Calculate and return FPS
		float fps = static_cast<float>(frameCount) / static_cast<float>(currentTime - lastTime);

		return static_cast<int>(fps);
		frameCount = 0;
		lastTime += 1.0;
	}
	return 0;
}