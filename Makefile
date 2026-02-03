# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aabdella <aabdella@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/02 18:51:43 by aabdella          #+#    #+#              #
#    Updated: 2026/02/03 17:44:57 by aabdella         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT
CC = cc

FLAG = -Wall -Wextra -Werror -I./lib/Libft_all -I./minilibx-linux -I./include
LFLAG = -L./lib/Libft_all -lft -L./minilibx-linux -lmlx -lX11 -lXext -lm -lz
SRC = $(addprefix src/, main.c)
OBJ = $(SRC:src/%.c=built/%.o)

all: libft minilibx $(NAME)

	@printf "\n\
	███╗   ███╗██╗███╗   ██╗██╗██████╗ ████████╗ \n\
	███╗   ███╗██╗███╗   ██╗██╗██████╗ ████████╗ \n\
	███╗   ███╗██╗███╗   ██╗██╗██████╗ ████████╗ \n\
	████╗ ████║██║████╗  ██║██║██╔══██╗╚══██╔══╝ \n\
	██╔████╔██║██║██╔██╗ ██║██║██████╔╝   ██║    \n\
	██║╚██╔╝██║██║██║╚██╗██║██║██╔══██╗   ██║    \n\
	██║ ╚═╝ ██║██║██║ ╚████║██║██║  ██║   ██║    \n\
	██║ ╚═╝ ██║██║██║ ╚████║██║██║  ██║   ██║    \n\
	██║ ╚═╝ ██║██║██║ ╚████║██║██║  ██║   ██║    \n\
	██║ ╚═╝ ██║██║██║ ╚████║██║██║  ██║   ██║    \n\
	╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚═╝  ╚═╝   ╚═╝    \n\
														\n\n"

$(NAME) : $(OBJ)
	$(CC) $(OBJ) $(LFLAG) -o $(NAME)

built/%.o: src/%.c include/miniRT.h
	@mkdir -p $(dir $@)
	$(CC) $(FLAG) -c $< -o $@

libft:
	$(MAKE) -C lib/Libft_all

minilibx:
	$(MAKE) -C minilibx-linux
clean:
	rm -f $(OBJ)
	$(MAKE) -C lib/Libft_all clean
	$(MAKE) -C minilibx-linux clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C lib/Libft_all fclean

re: fclean all

.PHONY: all clean fclean re
