cmake_minimum_required(VERSION 3.10)
project(PSU_myftp_2017 C)

set(CMAKE_C_STANDARD 11)

include_directories(server/include)

add_executable(PSU_myftp_2017
        server/include/ftp.h
        server/src/cmd/abor.c
        server/src/cmd/cwd.c
        server/src/cmd/default.c
        server/src/cmd/delete.c
        server/src/cmd/list.c
        server/src/cmd/mkdir.c
        server/src/cmd/noop.c
        server/src/cmd/pass.c
        server/src/cmd/pasv.c
        server/src/cmd/pwd.c
        server/src/cmd/quit.c
        server/src/cmd/retr.c
        server/src/cmd/rmd.c
        server/src/cmd/size.c
        server/src/cmd/stor.c
        server/src/cmd/type.c
        server/src/cmd/user.c
        server/src/commands.c
        server/src/logger.c
        server/src/main.c
        server/src/response.c
        server/src/utils.c
        server/src/utils_port.c)
