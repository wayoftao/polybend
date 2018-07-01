#ifndef PRIMITIVEDATA_H_INCLUDED
#define PRIMITIVEDATA_H_INCLUDED

#include <vector>
#include "PolygonData.h"
#include "ConstraintData.h"

struct PrimitiveData
{
    std::vector<PolygonData>  polygons;
    std::vector<ConstraintData> constraints;
};

#endif
