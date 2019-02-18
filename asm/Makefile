# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/02 09:43:55 by gguichar          #+#    #+#              #
#    Updated: 2019/02/18 04:44:40 by wta              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	asm

SRC_DIR	=	src
SRC		=			\
asm_managers.c		\
asm_utils.c			\
check_line.c		\
check_valid_tab.c	\
create_cor_utils.c	\
error_handler.c		\
get_file_cor.c		\
lexer.c				\
lst_utils.c			\
main.c				\
read_file.c			\
utils.c				\
utils2.c			\
write_bytes.c

OBJ_DIR	=	.obj
OBJ		=	$(SRC:.c=.o)
DEP		=	$(OBJ:.o=.d)

INC_DIR	=	includes

CC		=	gcc -g
CFLAGS	=	-Wall -Wextra -Werror -I ../libft/includes -I $(INC_DIR)

LIBFT	=	../libft/libft.a

all: $(NAME)

$(NAME): $(LIBFT) $(addprefix $(OBJ_DIR)/,$(OBJ))
	$(CC) -o $@ $^

$(LIBFT):
	$(MAKE) -C ../libft

-include $(addprefix $(OBJ_DIR)/,$(DEP))

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -MMD -o $@ -c $<

$(OBJ_DIR):
	/bin/mkdir $@

clean:
	$(MAKE) -C ../libft clean
	/bin/rm -rf $(OBJ_DIR)

fclean: clean
	$(MAKE) -C ../libft fclean
	/bin/rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
