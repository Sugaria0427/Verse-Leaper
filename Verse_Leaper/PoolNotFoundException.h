#pragma once
#include <stdexcept>

class PoolNotFoundException : public std::runtime_error {
public:
    PoolNotFoundException(const char* message) : runtime_error(message) {}
};