#pragma once
#include "glm/ext/matrix_float4x4.hpp"
#include<iostream>
#include<memory>
#include<glm/vec3.hpp>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"


#define DEBUG 1
#define FORCE_EDITOR 1
#if DEBUG
#define LOG(x) std::cout << x << '\n'
#define LOGVEC(x, y, z, msg) std::cout << msg <<": x: " << x << ", y: " << y << ", z: " << z << '\n';
#else
#define LOGVEC(x, y, z)
#define LOG(x)
#endif
#define VSYNC 0
#define LOCKCURSOR 0


// Should be the default error box to exist
class PurpleError {
	

};
