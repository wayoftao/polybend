#ifndef POLYGONDATA_HPP
#define POLYGONDATA_HPP

#include <memory>
#include <vector>
#include <glm/vec2.hpp>
#include "Vertex.hpp"

struct PolygonData
{
    typedef std::shared_ptr<PolygonData> Ptr;

    std::vector<Vertex> points;
    std::vector<int>    mesh;
};

#endif
