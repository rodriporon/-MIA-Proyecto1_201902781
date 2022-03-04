cmake_minimum_required(VERSION 3.21)
project(Proyecto1)

set(CMAKE_CXX_STANDARD 20)

add_executable(Proyecto1 main.cpp Analizador.cpp Analizador.h Comandos.cpp Comandos.h Utils.cpp Utils.h)
