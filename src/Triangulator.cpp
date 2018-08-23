#include "Triangulator.hpp"

#define DEBUG
#include <tuple>
#include "rbtree.hpp"
#undef DEBUG

std::vector<int> Triangulator::triangulate(const std::vector<glm::vec2>& points)
{
    // One R-B Tree for nodes
    RBTree<float, glm::vec2> nodes;
    // One R-B Tree for edges
    RBTree<float, glm::vec2> edges;

    for (const auto& p : points)
    {
        nodes.insert(p.x, p);
    }

    return std::vector<int>();
}
