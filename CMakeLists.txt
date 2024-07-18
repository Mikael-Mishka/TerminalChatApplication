cmake_minimum_required(VERSION 3.2)
project(SimpleSockets)

set(CMAKE_CXX_STANDARD 26)

set(INCLUDE_HEADERS
        include/
        include/network/
        include/network/client/
        include/network/server/
)

set(SOURCE_FILES
        main/main.cpp
        network/client/Client.cpp
        network/server/Server.cpp
        include/network/server/server.hpp
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_HEADERS})
