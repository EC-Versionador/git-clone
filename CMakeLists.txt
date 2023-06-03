cmake_minimum_required(VERSION 3.25)
project(git_clone C)

set(CMAKE_C_STANDARD 11)

include_directories(src)

add_executable(git_clone
        src/git.c
        src/actions.h src/validations.h src/validations.c src/actions.c src/archives.h src/files.h src/files.c src/data_structures.h src/data_structures.c src/parse.h src/parse.c src/utils.h src/utils.c src/serialize.h src/serialize.c)