cmake_minimum_required(VERSION 3.6)
project(FTP)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp FTPClient.cpp FTPClient.h)
add_executable(FTP ${SOURCE_FILES})