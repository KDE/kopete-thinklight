cmake_minimum_required(VERSION 2.6)
project(kopete-thinklight) 

find_package(KDE4 REQUIRED)
find_package(Kopete REQUIRED)

add_definitions(${QT_DEFINITIONS} ${KDE4_DEFINITIONS})

add_subdirectory(src)
