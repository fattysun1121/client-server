cmake_minimum_required(VERSION 3.28)

project(client_server LANGUAGES CXX)

find_package(PkgConfig REQUIRED)
pkg_check_modules(PQXX REQUIRED IMPORTED_TARGET libpqxx)

add_executable(Demo)
add_executable(Server) 
add_executable(Client)

target_sources(Demo 
    PRIVATE
        src/demo.cpp src/Client.cpp src/Server.cpp
    PRIVATE
        FILE_SET HEADERS
        BASE_DIRS 
            include
        FILES
            include/Client.h
            include/Server.h
)

target_sources(Server
    PRIVATE
        src/Server.cpp src/run_server.cpp
    PRIVATE 
        FILE_SET HEADERS
        BASE_DIRS 
            include
        FILES
            include/Server.h
)

target_sources(Client
    PRIVATE
        src/Client.cpp src/run_client.cpp
    PRIVATE
        FILE_SET HEADERS
        BASE_DIRS 
            include
        FILES
            include/Client.h
)

target_compile_features(Server PRIVATE cxx_std_20)
target_compile_features(Client PRIVATE cxx_std_20)
target_compile_features(Demo PRIVATE cxx_std_20)

target_link_libraries(Server PRIVATE PkgConfig::PQXX)
target_link_libraries(Client PRIVATE PkgConfig::PQXX)
target_link_libraries(Demo PRIVATE PkgConfig::PQXX)