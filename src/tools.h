#pragma once
#include "glm/ext/matrix_float4x4.hpp"
#include<iostream>
#include<memory>
#include<glm/vec3.hpp>
#define DEBUG 1
#if DEBUG
#define LOG(x) std::cout << x << '\n'
#define LOGVEC(x, y, z) std::cout << "x: " << x << ", y: " << y << ", z: " << z << '\n';
#else
#define LOGVEC(x, y, z)
#define LOG(x)
#endif
#define VSYNC 0
#define LOCKCURSOR 1


// Should be the default error box to exist
class PurpleError {
	

};
