cmake_minimum_required(VERSION 3.20)

project(Boiler)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB_RECURSE SOURCES "${PROJECT_SOURCE_DIR}/src/*.cpp" "${PROJECT_SOURCE_DIR}/src/*.h" "${PROJECT_SOURCE_DIR}/src/*.c")


find_package(OpenGL REQUIRED)

if (APPLE)
find_package(glfw3 REQUIRED)
message(STATUS "Compiling for mac")
endif()
add_executable(Boiler ${SOURCES})
target_include_directories(Boiler PUBLIC "${PROJECT_SOURCE_DIR}/include/")
target_link_directories(Boiler PRIVATE
    "${CMAKE_SOURCE_DIR}/lib/"
)

target_link_libraries(Boiler PRIVATE ${OPENGL_LIBRARIES})
if (APPLE)
message(STATUS "Linking with libassimp.6.dylib")
find_package(OpenAL REQUIRED)
target_link_libraries(Boiler PRIVATE glfw libassimp.6.dylib OpenAL::OpenAL)
elseif(LINUX)
message(STATUS "Linking libassimp.so")
target_link_libraries(Boiler PRIVATE glfw libassimp.so)
else()
message(STATUS "Linking assimp-vc143-mtd & openal32.lib")
target_link_libraries(Boiler PRIVATE glfw3 assimp-vc143-mtd OpenAL32)
endif()


add_custom_command(
    TARGET Boiler POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets ${CMAKE_CURRENT_BINARY_DIR}/assets
)
