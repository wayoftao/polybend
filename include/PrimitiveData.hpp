#ifndef PRIMITIVEDATA_HPP
#define PRIMITIVEDATA_HPP

#include <memory>
#include <vector>
#include "PolygonData.hpp"
#include "ConstraintData.hpp"

struct PrimitiveData
{
	typedef std::shared_ptr<PrimitiveData> Ptr;
	typedef const Ptr& PtrRef;
    std::vector<PolygonData>  polygons;
    std::vector<ConstraintData> constraints;
};

#endif
