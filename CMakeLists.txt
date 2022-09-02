cmake_minimum_required(VERSION 3.20)
project(Metodos_Numericos)

set(CMAKE_C_STANDARD 11)

add_executable(localizacion_raices  localizacion_raices/localizacionRaices.c)
add_executable(eliminacion_gaussiana sistemas_ecuaciones_lineales/eliminacionGaussiana.c)
add_executable(jacobi sistemas_ecuaciones_lineales/jacobi.c)


