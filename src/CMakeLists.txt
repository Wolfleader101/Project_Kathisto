add_subdirectory(math)
add_subdirectory(game)
add_subdirectory(loader)
add_subdirectory(utilities)
add_subdirectory(window)
add_subdirectory(gui)


set(SOURCES
    src/main.c
    ${MATH}
    ${GAME}
    ${LOADER}
    ${WINDOW}
    ${UTILITIES}
    ${GUI}
    PARENT_SCOPE)