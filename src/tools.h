#pragma once
#include "glm/ext/matrix_float4x4.hpp"
#include<iostream>
#include<memory>

#define DEBUG 1
#if DEBUG
#define LOG(x) std::cout << x << '\n'
#else
#define LOG(x)
#endif
#define VSYNC 0
#define LOCKCURSOR 1


// Should be the default error box to exist
class PurpleError {


};
