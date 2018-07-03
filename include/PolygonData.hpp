#ifndef POLYGONDATA_HPP
#define POLYGONDATA_HPP

#include <vector>
#include <glm/vec3.hpp>

struct PolygonData
{
    std::vector<glm::dvec3> points;
    glm::vec3 color;
    // TODO: Mesh
};

#endif
