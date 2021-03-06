#ifndef TRIANGULATOR_HPP
#define TRIANGULATOR_HPP

#include <vector>
#include <glm/vec2.hpp>

#include "PolygonData.hpp"

class Triangulator
{
public:
    static std::vector<int> triangulate(const std::vector<glm::vec2>& points);
    static PolygonData::Ptr subdivide(const PolygonData::Ptr& data);
};

#endif
