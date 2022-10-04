cmake_minimum_required(VERSION 3.20)
project(Metodos_Numericos)

set(CMAKE_C_STANDARD 11)

add_executable(localizacion_raices  localizacion_raices/localizacionRaices.c)
add_executable(eliminacion_gaussiana sistemas_ecuaciones_lineales/eliminacionGaussiana.c)
add_executable(iterativos sistemas_ecuaciones_lineales/iterativos.c)
add_executable(interpolacion interpolacion/interpolacion.c)
add_executable(interpolacion_segmentaria interpolacion/interpolacionSegmentaria.c)
add_executable(regresion regresion/regresion.c)

target_link_libraries(interpolacion m)
target_link_libraries(regresion m)
target_link_libraries(interpolacion_segmentaria m)
target_link_libraries(iterativos m)
target_link_libraries(localizacion_raices  m)
target_link_libraries(eliminacion_gaussiana m)



