# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/02 09:43:55 by gguichar          #+#    #+#              #
#    Updated: 2019/02/16 00:31:42 by vifonne          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	corewar

SRC_DIR	=	src
SRC		=		\
main.c			\
read.c			\
champs.c		\
cycles.c		\
errors.c		\
print_arena.c	\
op/op_utils.c	\
op/live.c		\
op/ld.c			\
op/sub.c		\
op/ft_and.c		\
op/add.c

OBJ_DIR	=	.obj
OBJ		=	$(SRC:.c=.o)
DEP		=	$(OBJ:.o=.d)
INC_DIR	=	includes

CC		=	gcc -g -fsanitize=address
CFLAGS	=	-Wall -Wextra -Werror -I libft/includes -I $(INC_DIR)

LIBFT	=	libft/libft.a

all: $(NAME)

$(NAME): $(LIBFT) $(addprefix $(OBJ_DIR)/,$(OBJ))
	$(CC) -o $@ $^

$(LIBFT):
	$(MAKE) -C libft

-include $(addprefix $(OBJ_DIR)/,$(DEP))

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -MMD -o $@ -c $<

$(OBJ_DIR):
	/bin/mkdir $@
	/bin/mkdir $@/op

clean:
	$(MAKE) -C libft clean
	/bin/rm -rf $(OBJ_DIR)

fclean: clean
	$(MAKE) -C libft fclean
	/bin/rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
