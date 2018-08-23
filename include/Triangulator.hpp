#ifndef TRIANGULATOR_HPP
#define TRIANGULATOR_HPP

#include <PolygonData.hpp>
#include <vector>
#include <glm/vec2.hpp>

class Triangulator
{
public:
    static std::vector<int> triangulate(const std::vector<glm::vec2>& points);
    static PolygonData::ptr subdivide(const PolygonData::ptr& data);
};

#endif
