#pragma once
#include <stdexcept>

class SDLInitException : public std::runtime_error {
public:
    SDLInitException(const char* message) : runtime_error(message) {}
};