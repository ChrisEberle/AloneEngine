#pragma once
#include "engine.h"

static void wireframe_state(bool get_state) {
	// Whether to render wireframe or full textured
	if (get_state) { glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); }
	else { glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); }
}