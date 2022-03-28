

add_compile_options(
    # GCC
    $<$<C_COMPILER_ID:GNU>:-w>
    # Visual Studio
    $<$<C_COMPILER_ID:MSVC>:/W0>
)

add_subdirectory(freeglut)
add_subdirectory(cimgui)

# set cimgui variables
set(cimgui cimgui)
set(imgui_impl ${cimgui}/imgui/backends)

add_library(imgui_impl STATIC ${imgui_impl}/imgui_impl_opengl2.cpp ${imgui_impl}/imgui_impl_glut.cpp)

target_include_directories(imgui_impl SYSTEM PUBLIC freeglut/include)

target_link_libraries(imgui_impl PUBLIC freeglut_static cimgui)

# include those folders
target_include_directories(${PROJECT_NAME} SYSTEM PUBLIC
    freeglut/include
    ${cimgui}
    ${cimgui}/imgui
    ${imgui_impl}
    )