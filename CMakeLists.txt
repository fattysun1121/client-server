cmake_minimum_required(VERSION 3.28)

project(client_server LANGUAGES CXX)

add_executable(server server.cpp)
add_executable(client client.cpp)