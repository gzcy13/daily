#make最低版本需求，不加入此行会受到警告信息
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(curl) #项目名称
AUX_SOURCE_DIRECTORY(. SRC_LIST)


set(CMAKE_C_COMPILER "/opt/hisi-linux/x86-arm/aarch64-himix100-linux/bin/aarch64-himix100-linux-gcc")
#set(CMAKE_CXX_COMPILER "/opt/hisi-linux/x86-arm/aarch64-himix100-linux/bin/aarch64-himix100-linux-g++")
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -std=c++0x -g")
set(CMAKE_EXE_LINKER_FLAGS " -lpthread -lrt -ldl")


#include_directories(/media/sf_utunbu/1/trafficBox/3rdparty/Hi3559/openssl-1.1.1g/include)
#include_directories(/usr/local/include)

#include_directories(/usr/include)
include_directories(./)

include_directories(${OPENCV_INCLUDE_DIRS})

AUX_SOURCE_DIRECTORY(./src SRC_LIST)

link_directories("../lib/")

link_libraries(libssl.so)
link_libraries(libcrypto.so)
link_libraries(libcryptopp.so)
link_libraries(libcurl.so)


#生成应用程序 AES
ADD_EXECUTABLE(curlEXECUTABLE ${SRC_LIST})
#ADD_LIBRARY(upgrade SHARED ${SRC_LIST})
