cmake_minimum_required(VERSION 3.24)
project(HCNNG)

set(CMAKE_CXX_STANDARD 20)

add_executable(HCNNG main.cpp header/MST.h MST.cpp header/spt.h dataProcess.cpp header/dataProcess.h header/HCNNG.h HCNNG.cpp header/header.h header/guideStructure.h guideStruct.cpp spt.cpp search.cpp header/search.h)
