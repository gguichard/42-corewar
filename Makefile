# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vifonne <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/23 03:29:11 by vifonne           #+#    #+#              #
#    Updated: 2019/02/23 04:30:25 by vifonne          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	corewar_project

ASM			=	asm
ASM_DIR	 	=	asm_dir

DASM		=	dasm
DASM_DIR	=	dasm_dir

VM			=	corewar
VM_DIR		=	vm_dir

UNDER		=		$'\x1b[4m$'
RED			=		$'\x1b[31m$'
GREEN		=		$'\x1b[32m$'
YELLOW		=		$'\x1b[33m$'
WHITE		=		$'\x1b[37m$'
END			=		$'\x1b[0m$'

LIBFT		=		libft/libft.a

CC			=		gcc
CFLAGS		=		-Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(LIBFT) $(VM) $(ASM) $(DASM)

$(VM):
	@echo "\n$(UNDER)Compiling vm:$(END)\t\t$(GREEN)$(CC) $(CFLAGS)$(END)\n"
	@/bin/echo -n "0% ["
	@$(MAKE) -C $(VM_DIR)
	@echo "] 100%\n"
	@cp $(VM_DIR)/$(VM) .

$(ASM):	
	@echo "\n$(UNDER)Compiling asm:$(END)\t\t$(GREEN)$(CC) $(CFLAGS)$(END)\n"
	@/bin/echo -n "0% ["
	@$(MAKE) -C $(ASM_DIR)
	@echo "] 100%\n"
	@cp $(ASM_DIR)/$(ASM) .
	
$(DASM):
	@echo "\n$(UNDER)Compiling dasm:$(END)\t\t$(GREEN)$(CC) $(CFLAGS)$(END)\n"
	@/bin/echo -n "0% ["
	@$(MAKE) -C $(DASM_DIR)
	@echo "] 100%\n"
	@cp $(DASM_DIR)/$(DASM) .

$(LIBFT):
	@echo "\n$(UNDER)Compiling libft:$(END)\t\t$(GREEN)$(CC) $(CFLAGS)$(END)\n"
	@/bin/echo -n "0% ["
	@$(MAKE) -C libft
	@echo "] 100%\n"

clean:
	@echo "$(UNDER)Cleaning project:$(END)\n"
	@echo "$(YELLOW)"
	@echo "Cleaning libft"
	@$(MAKE) -C libft clean
	@$(MAKE) -C $(ASM_DIR) clean
	@$(MAKE) -C $(DASM_DIR) clean
	@$(MAKE) -C $(VM_DIR) clean
	@echo "$(END)"

fclean: clean
	@echo "\n$(UNDER)Full clean project:$(END)\n"
	@echo "$(RED)"
	@echo "Full clean libft"
	@$(MAKE) -C libft fclean
	@$(MAKE) -C $(ASM_DIR) fclean
	@$(MAKE) -C $(DASM_DIR) fclean
	@$(MAKE) -C $(VM_DIR) fclean
	@echo "$(END)"
	@echo "\n$(UNDER)Cleaning exec in current directory:$(END)\n"
	@echo "$(RED)"
	/bin/rm -f $(ASM)
	/bin/rm -f $(DASM)
	/bin/rm -f $(VM)
	@echo "$(END)"

re: fclean all

.PHONY: all clean fclean re $(NAME) $(VM) $(ASM) $(DASM)
