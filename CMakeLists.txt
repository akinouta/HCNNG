#cmake_minimum_required(VERSION 3.24)
#project(HCNNG)
#
#set(CMAKE_CXX_STANDARD 20)
#
#add_executable(HCNNG main.cpp header/MST.h MST.cpp header/spt.h dataProcess.cpp header/dataProcess.h header/HCNNG.h HCNNG.cpp header/header.h header/guideStructure.h guideStruct.cpp spt.cpp search.cpp header/search.h header/MHT.h MHT.cpp)
cmake_minimum_required(VERSION 3.24)
project(HCNNG)
set(CMAKE_CXX_STANDARD 20)

# 寻找 OpenSSL 库
find_package(OpenSSL REQUIRED)

# 添加头文件路径
include_directories(${OPENSSL_INCLUDE_DIR})

add_executable(HCNNG main.cpp header/MST.h MST.cpp header/spt.h dataProcess.cpp header/dataProcess.h header/HCNNG.h HCNNG.cpp header/header.h header/guideStructure.h guideStruct.cpp spt.cpp search.cpp header/search.h header/MHT.h MHT.cpp)

# 链接 OpenSSL 库
target_link_libraries(HCNNG PRIVATE ${OPENSSL_SSL_LIBRARY} ${OPENSSL_CRYPTO_LIBRARY})

