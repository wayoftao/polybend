#include "ObjectManager.hpp"
#include <memory>

ObjectManager::ObjectManager()
    : _data(std::make_shared<PrimitiveData>())
{
}
