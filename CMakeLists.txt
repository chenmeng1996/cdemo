cmake_minimum_required(VERSION 3.7.2)
project(cdemo C)

set(CMAKE_C_STANDARD 11)

add_executable(cdemo cmd/main.c)

add_executable(tcp_server_server tcp_server/server.c)
add_executable(tcp_server_client tcp_server/client.c)

add_executable(io_select_client io/select/client.c)
add_executable(io_select_server io/select/server.c)

add_executable(io_epoll_server io/epoll/server.c)

add_executable(uds_server uds/server.c)
add_executable(uds_client uds/client.c)