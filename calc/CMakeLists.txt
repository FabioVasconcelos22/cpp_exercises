cmake_minimum_required(VERSION 3.10)

# set the project name
project(Calculator)

# add the executable

add_executable(Calc main.cpp)

target_compile_features (Calc PUBLIC cxx_std_11)