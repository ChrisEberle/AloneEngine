#pragma once
#include "engine.h"

static void wireframe_state(bool get_state, Shaderer& objectShader) {
	// Whether to render wireframe or full textured
	if (get_state) { 
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); 
	}
	else {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}

static void point_state(bool get_state) {
	// Whether to render wireframe or full textured
	if (get_state) { glPolygonMode(GL_FRONT_AND_BACK, GL_POINT); glPointSize(5.0f);  }
	else { glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); }
}