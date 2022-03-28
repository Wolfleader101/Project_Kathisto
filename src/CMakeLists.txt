add_subdirectory(math)
add_subdirectory(game)
add_subdirectory(window)
add_subdirectory(gui)


set(SOURCES
    src/main.c
    ${MATH}
    ${GAME}
    ${WINDOW}
    ${GUI}
    PARENT_SCOPE)