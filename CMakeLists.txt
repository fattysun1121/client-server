cmake_minimum_required(VERSION 3.28)

project(client_server LANGUAGES CXX)


find_package(PkgConfig REQUIRED)
pkg_check_modules(PQXX REQUIRED IMPORTED_TARGET libpqxx)

add_executable(server server.cpp)
add_executable(client client.cpp)

target_compile_features(server PRIVATE cxx_std_20)
target_compile_features(client PRIVATE cxx_std_20)

target_link_libraries(server PRIVATE PkgConfig::PQXX)
target_link_libraries(client PRIVATE PkgConfig::PQXX)