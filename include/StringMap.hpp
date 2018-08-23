#ifndef STRINGMAP_HPP
#define STRINGMAP_HPP

#include <unordered_map>

template <class T>
using StringMap = std::unordered_map<std::string, T>;

#endif
