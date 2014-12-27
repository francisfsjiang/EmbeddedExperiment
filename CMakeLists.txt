cmake_minimum_required(VERSION 2.8.4)
project(embedded_exp)

#subdirs(bin)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

subdirs(src)
