cmake_minimum_required(VERSION 3.20)
project(Metodos_Numericos)

set(CMAKE_C_STANDARD 11)

add_executable(localizacion_raices  localizacion_raices/localizacionRaices.c)
add_executable(eliminacion_gaussiana sistemas_ecuaciones_lineales/eliminacionGaussiana.c)
add_executable(iterativos sistemas_ecuaciones_lineales/iterativos.c)
add_executable(interpolacion interpolacion/interpolacion.c)
add_executable(regresion regresion/regresion.c)




