#ifndef OBJECTMANAGER_HPP
#define OBJECTMANAGER_HPP

#include <memory>
#include "PrimitiveData.hpp"

class ObjectManager
{
public:

    ObjectManager();

    PrimitiveData::Ptr getData()
    {
        return _data;
    }
    void setData(PrimitiveData::Ptr data)
    {
        _data = data;
    }

private:
    PrimitiveData::Ptr _data;
};

#endif
