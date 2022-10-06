cmake_minimum_required(VERSION 3.0.0)
project(puissancec VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(puissancec main.c game.c user.c config.c colors.c printGrille.c)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
