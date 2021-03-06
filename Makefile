NAME_1 = asm
NAME_2 = corewar
NAME_3 = disasm

LIBFT_A = libftprintf.a

#asm

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

SOURCES_DIR_1 = ./assembler/general/srcs/
SRCS_LI_1 = $(addprefix $(SOURCES_DIR_1), $(SR_LI_1))
OBJECT_DIR_1 = objects1/
OBJ_LIST_LI_1 = $(patsubst %.c, %.o, $(SR_LI_1))
OBJ_LI_1 = $(addprefix $(OBJECT_DIR_1), $(OBJ_LIST_LI_1))

#corewar

SR_LI_2 =	all_inits.c \
			calculate.c \
			corewar.c \
			err_func.c \
			free_all.c \
			help_func.c \
			help_func2.c \
			in_cycles_check.c \
			log.c \
			parce_champ.c \
			parce_flags.c \
			print_func.c \
			start.c \
			cursor.c \
			start_parsing.c \
			validate_args.c \
			op_add.c \
			op_aff.c \
			op_and.c \
			op_fork.c \
			op_ld.c \
			op_ldi.c \
			op_lfork.c \
			op_live.c \
			op_lld.c \
			op_lldi.c \
			op_or.c \
			op_st.c \
			op_sti.c \
			op_sub.c \
			op_xor.c \
			op_zjmp.c \
			utils.c \

SOURCES_DIR_2 = ./vm/src/
SRCS_LI_2 = $(addprefix $(SOURCES_DIR_2), $(SR_LI_2))
OBJECT_DIR_2 = objects2/
OBJ_LIST_LI_2 = $(patsubst %.c, %.o, $(SR_LI_2))
OBJ_LI_2 = $(addprefix $(OBJECT_DIR_2), $(OBJ_LIST_LI_2))

SR_LI_3 =	main.c \
			reader.c \
			reader_code.c \
			writer.c \
			utils.c \
			utils_struct.c

SOURCES_DIR_3 = ./disassembler/src/
SRCS_LI_3 = $(addprefix $(SOURCES_DIR_3), $(SR_LI_3))
OBJECT_DIR_3 = objects3/
OBJ_LIST_LI_3 = $(patsubst %.c, %.o, $(SR_LI_3))
OBJ_LI_3 = $(addprefix $(OBJECT_DIR_3), $(OBJ_LIST_LI_3))

HEADER_DIR = ./general/includes/

LIB_MLX = minilibx/libmlx.a
LIBS_MLX = -L./ft_printf -lftprintf
MLX_DIR = ./minilibx

COMPILER := gcc
HDRPATH := ./assembler/general/includes -I./vm/includes -I./libftprintf/includes
IFLAGS := -I$(HDRPATH)
IFLAGS_COREWAR = -I./vm/includes -I./libftprintf/includes
IFLAGS_DISASM = -I./disassembler/includes -I./libftprintf/includes
CFLAGS := -Wall -Wextra -Werror -O2

LIB_DIR = ./libftprintf
LIB_RULE = $(addsuffix .lib, $(LIB_DIR))

LIBFT = ./libftprintf/libftprintf.a

all: $(LIB_RULE) $(NAME_1) $(NAME_2) $(NAME_3)

%.lib:
	@$(MAKE) -sC $(LIB_DIR)

# ASM

$(NAME_1): $(LIBFT) $(OBJECT_DIR_1) $(OBJ_LI_1)
	@$(COMPILER) $(CFLAGS) $(IFLAGS) $(LIBFT) $(OBJ_LI_1) -o $(NAME_1)
	@echo "\n\x1b[32masm compiled\x1b[0m"

$(OBJECT_DIR_1):
	@mkdir -p $(OBJECT_DIR_1)

$(OBJECT_DIR_1)%.o : $(SOURCES_DIR_1)%.c
	@$(COMPILER) $(CFLAGS) -c $(IFLAGS) $< -o $@
	@echo "\x1b[32m.\x1b[0m\c"

# COREWAR

$(NAME_2): $(LIBFT) $(OBJECT_DIR_2) $(OBJ_LI_2)
	@$(COMPILER) $(CFLAGS) $(IFLAGS_COREWAR) $(LIBFT) $(OBJ_LI_2) -o $(NAME_2)
	@echo "\n\x1b[32mcorewar compiled\x1b[0m"

$(OBJECT_DIR_2):
	@mkdir -p $(OBJECT_DIR_2)

$(OBJECT_DIR_2)%.o : $(SOURCES_DIR_2)%.c
	@$(COMPILER) $(CFLAGS) -c $(IFLAGS_COREWAR) $< -o $@
	@echo "\x1b[32m.\x1b[0m\c"

# DISASM

$(NAME_3): $(LIBFT) $(OBJECT_DIR_3) $(OBJ_LI_3)
	@$(COMPILER) $(CFLAGS) $(IFLAGS_DISASM) $(LIBFT) $(OBJ_LI_3) -o $(NAME_3)
	@echo "\n\x1b[32mdisasm compiled\x1b[0m"

$(OBJECT_DIR_3):
	@mkdir -p $(OBJECT_DIR_3)

$(OBJECT_DIR_3)%.o : $(SOURCES_DIR_3)%.c
	@$(COMPILER) $(CFLAGS) -c $(IFLAGS_DISASM) $< -o $@
	@echo "\x1b[32m.\x1b[0m\c"

# LIBFT

$(LIBFT):
	@make -C $(LIB_DIR)

clean:
	@rm -rf $(OBJECT_DIR_1)
	@rm -rf $(OBJECT_DIR_2)
	@rm -rf $(OBJECT_DIR_3)
	@make -C $(LIB_DIR) clean
	@rm -rf $(OBJECT_PF)

fclean: clean
	@make -C $(LIB_DIR) fclean
	@/bin/rm -f $(NAME_1)
	@/bin/rm -f $(NAME_2)
	@/bin/rm -f $(NAME_3)

re: fclean all