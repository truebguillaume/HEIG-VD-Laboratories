cmake_minimum_required(VERSION 3.24)
project(prg2_labo3 C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_FLAGS "-Wall")
add_executable(prg2_labo3 main.c math.h math.c bateau.c bateau.h stats_bateau.c stats_bateau.h affichage.c affichage.h)
