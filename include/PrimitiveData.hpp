#ifndef PRIMITIVEDATA_H_INCLUDED
#define PRIMITIVEDATA_H_INCLUDED

#include <memory>
#include <vector>
#include "PolygonData.hpp"
#include "ConstraintData.hpp"

struct PrimitiveData
{
	typedef std::shared_ptr<PrimitiveData> Ptr;
    std::vector<PolygonData>  polygons;
    std::vector<ConstraintData> constraints;
};

#endif
