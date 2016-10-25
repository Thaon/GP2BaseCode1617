#ifndef VERTEX_H
#define VERTEX_H

#include "Common.h"

//keeping this a struct to be able to use offsetof, it can malfunction on classes based on the compiler
struct Vertex {
	glm::vec3 position;
	glm::vec4 colour;
	glm::vec2 texCoords;
};

#endif
