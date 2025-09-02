#pragma once
#include "glm/ext/matrix_float4x4.hpp"
#include<iostream>
#include<memory>
//define debug macro
#define DEBUG 1
#ifdef DEBUG
#define LOG(x) std::cout << x << '\n'
#else
#define LOG(x)
#endif
#define VSYNC 0


// Should be the default error box to exist
class PurpleError {


};
