NAME_1 = asm

LIBFT_A = libftprintf.a

SR_LI_1 =	convert_tokens.c \
			find_name_and_comment.c \
			parse_command.c \
			parse_small.c \
			process_file.c \
			read_file.c \
			special_gnl.c \
			token.c \
			main.c \
			parse_label.c \
			parse_some.c \
			process_file_extra.c \
			service.c \
			t_asm.c \
			write_file.c \
			special_atoi.c \
			get_type.c \
			convert_tokens_part.c \
			new_get.c \
			parse_some_part.c \
			procces_args.c \
			skip_some.c \


SOURCES_DIR = ./general/srcs/

SRCS_LI_1 = $(addprefix $(SOURCES_DIR), $(SR_LI_1))
OBJECT_DIR_1 = objects1/
OBJ_LIST_LI_1 = $(patsubst %.c, %.o, $(SR_LI_1))
OBJ_LI_1 = $(addprefix $(OBJECT_DIR_1), $(OBJ_LIST_LI_1))

HEADER_DIR = ./general/includes/

LIB_MLX = minilibx/libmlx.a
LIBS_MLX = -L./ft_printf -lftprintf
MLX_DIR = ./minilibx

COMPILER := gcc
HDRPATH := ./general/includes -I./general/libftprintf/includes -I./minilibx
IFLAGS := -I$(HDRPATH)
CFLAGS := -Wall -Wextra -Werror -O2

LIB_DIR = ./general/libftprintf
LIB_RULE = $(addsuffix .lib, $(LIB_DIR))

LIBFT = ./general/libftprintf/libftprintf.a
LIBS = -L./general/ft_libftprintf -l_ftprintf


all: $(LIB_RULE) $(NAME_1)

%.lib:
	@$(MAKE) -sC $(LIB_DIR)

$(NAME_1): $(LIBFT) $(OBJECT_DIR_1) $(OBJ_LI_1)
	@$(COMPILER) $(CFLAGS) $(IFLAGS) $(LIBFT) $(OBJ_LI_1) -o $(NAME_1)
	@echo "\n\x1b[32masm compiled\x1b[0m"

$(OBJECT_DIR_1):
	@mkdir -p $(OBJECT_DIR_1)

$(OBJECT_DIR_1)%.o : $(SOURCES_DIR)%.c $(HEADERS)
	@$(COMPILER) $(CFLAGS) -c $(IFLAGS) $< -o $@
	@echo "\x1b[32m.\x1b[0m\c"

$(LIBFT):
	@make -C $(LIB_DIR)

clean:
	@rm -rf $(OBJECT_DIR_1)
	@make -C $(LIB_DIR) clean
	@rm -rf $(OBJECT_PF)

fclean: clean
	@make -C $(LIB_DIR) fclean
	@/bin/rm -f $(NAME_1)

re: fclean all
