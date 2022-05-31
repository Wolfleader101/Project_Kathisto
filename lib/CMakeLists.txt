

add_compile_options(
    # GCC
    $<$<C_COMPILER_ID:GNU>:-w>
    # Visual Studio
    $<$<C_COMPILER_ID:MSVC>:/W0>
)

 add_subdirectory(freeglut)
 #add_subdirectory(cimgui)

# set cimgui variables
# set(cimgui cimgui)
# set(imgui_impl ${cimgui}/imgui/backends)

# add_library(imgui_impl STATIC ${imgui_impl}/imgui_impl_opengl2.cpp ${imgui_impl}/imgui_impl_glut.cpp)

# target_include_directories(imgui_impl SYSTEM PUBLIC freeglut/include)

#link_libraries(${CMAKE_CURRENT_SOURCE_DIR}/lib/imgui/lib/imgui_impl.lib
 #PUBLIC freeglut_static {CMAKE_CURRENT_SOURCE_DIR}/lib/imgui/lib/cimgui.lib) 

#{CMAKE_CURRENT_SOURCE_DIR}/lib/imgui/lib/cimgui.lib
# include those folders
target_include_directories(${PROJECT_NAME} SYSTEM PUBLIC
    freeglut/include
    imgui/include
    #${cimgui}
    #${cimgui}/imgui
    #${imgui_impl}
    )