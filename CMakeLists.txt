cmake_minimum_required(VERSION 3.10)
project(PSU_myftp_2017 C)

set(CMAKE_C_STANDARD 11)

include_directories(srv/include)

add_executable(PSU_myftp_2017
        srv/include/ftp.h
        srv/src/cmd/abor.c
        srv/src/cmd/cwd.c
        srv/src/cmd/default.c
        srv/src/cmd/delete.c
        srv/src/cmd/list.c
        srv/src/cmd/mkdir.c
        srv/src/cmd/noop.c
        srv/src/cmd/pass.c
        srv/src/cmd/pasv.c
        srv/src/cmd/pwd.c
        srv/src/cmd/quit.c
        srv/src/cmd/retr.c
        srv/src/cmd/rmd.c
        srv/src/cmd/size.c
        srv/src/cmd/stor.c
        srv/src/cmd/type.c
        srv/src/cmd/user.c
        srv/src/commands.c
        srv/src/logger.c
        srv/src/main.c
        srv/src/response.c
        srv/src/utils.c
        srv/src/utils_port.c)
