cmake_minimum_required(VERSION 3.10)

project(StateMachinePattern VERSION 1.0 LANGUAGES CXX DESCRIPTION "A simple example  of a State Machine Design Pattern by Vladimir Petukhov in modern C++")

set(CMAKE_CONFIGURATION_TYPES "Release")

add_executable(StateMachinePattern StateMachinePattern.cpp StateMachinePattern.h main.cpp)
