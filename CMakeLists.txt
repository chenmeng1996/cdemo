cmake_minimum_required(VERSION 3.7.2)
project(cdemo C)

set(CMAKE_C_STANDARD 11)


add_executable(fork cmd/fork.c)
add_executable(show cmd/show.c)
add_executable(test cmd/test.c)
add_executable(cp cmd/cp.c)
add_executable(mkstemp cmd/mkstemp.c)
add_executable(environment cmd/environment.c)

add_executable(tcp_server_server tcp_server/server.c)
add_executable(tcp_server_client tcp_server/client.c)

add_executable(io_select_client io/select/client.c)
add_executable(io_select_server io/select/server.c)

# add_executable(io_epoll_server io/epoll/server.c)



# Set the directories that should be included in the build command for this target
# when running g++ these will be included as -I/directory/path/

# target_include_directories(cp
#     PRIVATE 
#         ${PROJECT_SOURCE_DIR}/util
# )

include_directories(cdemo
    PRIVATE 
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/include-other
)
