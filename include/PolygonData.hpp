#ifndef POLYGONDATA_HPP
#define POLYGONDATA_HPP

#include <vector>
#include <glm/vec2.hpp>
#include "Vertex.hpp"

struct PolygonData
{
    std::vector<Vertex> points;
    std::vector<int> mesh;
    // TODO: Mesh
};

#endif
