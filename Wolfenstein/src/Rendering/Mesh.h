#pragma once
#include "Vertex.h"

struct Mesh
{
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
};