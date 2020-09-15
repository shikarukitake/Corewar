cmake_minimum_required(VERSION 3.16)
project(asm_corewar C)

set(CMAKE_C_STANDARD 11)

include_directories(general/includes)
include_directories(general/libftprintf/includes)

# Libft
file(GLOB_RECURSE LIBFT_FILES "${PROJECT_SOURCE_DIR}/general/libftprintf/srcs/*.c")
set(LIBFT_FILES ${LIBFT_FILES} ${LIBFT_ADD_FILES})
add_library(ftprintf STATIC ${LIBFT_FILES})


# lem-in
add_executable(asm general/srcs/main.c general/includes/asm.h general/srcs/t_asm.c general/srcs/service.c general/srcs/read_file.c general/srcs/write_file.c general/srcs/special_gnl.c general/srcs/process_file.c general/srcs/token.c general/srcs/parse_command.c general/srcs/debug_only.c general/srcs/parse_label.c general/srcs/parse_small.c general/srcs/process_file_extra.c)
target_link_libraries(asm ${PROJECT_BINARY_DIR}/libftprintf.a)
add_dependencies(asm ftprintf)
