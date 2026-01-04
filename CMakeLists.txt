cmake_minimum_required(VERSION 3.20)

project(Boiler)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB_RECURSE SOURCES "${PROJECT_SOURCE_DIR}/src/*.cpp" "${PROJECT_SOURCE_DIR}/src/*.h" "${PROJECT_SOURCE_DIR}/src/*.c")


find_package(OpenGL REQUIRED)

if (APPLE)
find_package(glfw3 REQUIRED)
#message(STATUS "Compiling for mac")
endif()
add_executable(Boiler ${SOURCES})
target_include_directories(Boiler PUBLIC "${PROJECT_SOURCE_DIR}/include/")
target_link_directories(Boiler PRIVATE
    "${CMAKE_SOURCE_DIR}/lib/"
)

target_link_libraries(Boiler PRIVATE ${OPENGL_LIBRARIES})
if (APPLE)
message(STATUS "Linking Apple Silicone")
find_package(OpenAL REQUIRED)
target_link_libraries(Boiler PRIVATE glfw libassimp.6.dylib OpenAL::OpenAL)
elseif(LINUX)
	find_package(OpenAL REQUIRED)
	message(STATUS "Linking linux (with temporary local openal lib)")
target_link_libraries(Boiler PRIVATE glfw libassimp.so OpenAL::OpenAL)
else()
message(STATUS "Linking assimp-vc143-mtd.lib & openal32.lib for windows possibly")
target_link_libraries(Boiler PRIVATE glfw3 assimp-vc143-mtd OpenAL32)
endif()


add_custom_command(
    TARGET Boiler POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets ${CMAKE_CURRENT_BINARY_DIR}/assets
)

# github copilot code for assimp dll missing instead of forcing people to copy it >:(
if (WIN32)
    message("doing things for windows")
    set(ASSIMP_DLL "${CMAKE_SOURCE_DIR}/lib/assimp-vc143-mtd.dll")
    if (EXISTS "${ASSIMP_DLL}")
        add_custom_command(TARGET Boiler POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${ASSIMP_DLL}"
                $<TARGET_FILE_DIR:Boiler>
            COMMENT "Copying Assimp DLL to output directory"
        )
    else()
        message(WARNING "Assimp DLL not found at ${ASSIMP_DLL}. If you installed Assimp elsewhere, add its DLL to PATH or update CMakeLists to point to it.")
    endif()
endif()