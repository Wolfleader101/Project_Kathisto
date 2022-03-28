# CMakeList.txt : CMake project for Project_Kathisto, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)


set(PROJECT_NAME Project_Kathisto)
project(${PROJECT_NAME} LANGUAGES C CXX)

# find openGL
find_package(OpenGL REQUIRED)

# include sources
add_subdirectory(src)

# Add source to this project's executable.
add_executable(${PROJECT_NAME} ${SOURCES})

# include lib
add_subdirectory(lib)


add_definitions(-DIMGUI_IMPL_OPENGL_LOADER_GLUT)

target_compile_definitions(${PROJECT_NAME} PRIVATE IMGUI_IMPL_API=extern\ \"C\")

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

target_link_libraries(${PROJECT_NAME} freeglut_static imgui_impl)

target_compile_definitions(${PROJECT_NAME} PRIVATE IMGUI_IMPL_API=)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:${PROJECT_NAME}>/assets)
