# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/02 09:43:55 by gguichar          #+#    #+#              #
#                                                                              #
# **************************************************************************** #

NAME		=	corewar

ASM			=	asm
ASM_DIR	 	=	src_asm

DASM		=	dasm
DASM_DIR	=	src_dasm

SRC_DIR		=	src
SRC			=			\
main.c					\
options.c				\
options_utils.c			\
read.c					\
champs.c				\
cycles.c				\
process.c				\
errors.c				\
print_arena.c			\
pc_utils.c				\
op/op_utils.c			\
op/op_utils2.c			\
op/live.c				\
op/ld.c					\
op/st.c					\
op/add.c				\
op/sub.c				\
op/ft_and.c				\
op/ft_or.c				\
op/ft_xor.c				\
op/zjmp.c				\
op/ldi.c				\
op/sti.c				\
op/ft_fork.c			\
op/lld.c				\
op/lldi.c				\
op/ft_lfork.c			\
op/aff.c				\
visual/func_print.c		\
visual/init_ncurses.c	\
visual/print_hud.c		\
visual/print_champ.c	\
visual/key_hook.c		\
visual/math_utils.c		\
visual/sig_handler.c

OBJ_DIR	=	.obj
OBJ		=	$(SRC:.c=.o)
DEP		=	$(OBJ:.o=.d)
INC_DIR	=	includes

CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror -I libft/includes -I $(INC_DIR)

LIBFT	=	libft/libft.a

UNDER		=		$'\x1b[4m$'
RED			=		$'\x1b[31m$'
GREEN		=		$'\x1b[32m$'
YELLOW		=		$'\x1b[33m$'
WHITE		=		$'\x1b[37m$'
END			=		$'\x1b[0m$'

all: $(NAME)

$(NAME): $(LIBFT) $(addprefix $(OBJ_DIR)/,$(OBJ))
	$(CC) -lncurses -o $@ $^
	$(MAKE) -C $(ASM_DIR)
	$(MAKE) -C $(DASM_DIR)
	mv src_asm/asm .
	mv src_dasm/dasm .

$(LIBFT):
	@echo "\n$(UNDER)Compiling libft:$(END)\t\t$(YELLOW)$(CC) $(CFLAGS)$(WHITE)\n"
	@/bin/echo -n "0% ["
	@$(MAKE) -C libft
	@echo "] 100%\n"

-include $(addprefix $(OBJ_DIR)/,$(DEP))

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -MMD -o $@ -c $<

$(OBJ_DIR):
	/bin/mkdir $@
	/bin/mkdir $@/op
	/bin/mkdir $@/visual

clean:
	$(MAKE) -C libft clean
	$(MAKE) -C $(ASM_DIR) clean
	$(MAKE) -C $(DASM_DIR) clean
	/bin/rm -rf $(OBJ_DIR)

fclean: clean
	$(MAKE) -C libft fclean
	/bin/rm -f $(ASM)
	/bin/rm -f $(DASM)
	/bin/rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
