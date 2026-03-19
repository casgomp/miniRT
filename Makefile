# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pecastro <pecastro@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/02 18:51:43 by aabdella          #+#    #+#              #
#    Updated: 2026/03/19 15:43:09 by pecastro         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



NAME = miniRT
CC = cc
DFLAG = -g

FLAG = -Wall -Wextra -Werror -I./lib/Libft_all -I./minilibx-linux -I./include
LFLAG = -L./lib/Libft_all -lft -L./minilibx-linux -lmlx -lX11 -lXext -lm -lz
SRC_RENDER = $(addprefix src/, main.c \
						render_loop.c \
						ray_for_pixel.c \
						intersections.c \
						intersect_cylinder_utils.c \
						intersect_objects.c \
						implement_camera.c \
						computations.c \
						lighting.c \
						lighting2.c \
						transform_matrix.c \
						transform_tuple.c \
						utils_matrix.c \
						utils_tuple.c \
						construct_matrix.c \
						construct_tuples.c \
						inversion_matrix.c \
						ray_tracing_utils.c\
						utils.c \
						utils2.c \
						cleanup.c \
						minilibx.c)
SRC_PARSING = $(addprefix parsing/, parsing.c \
									parsing_utils.c \
									parsing_utils_2.c \
									parse_ambient.c \
									parse_camera.c \
									parse_light.c \
									parse_sphere.c \
									parse_plane.c \
									free_scene.c \
									print_lists.c \
									parse_cylinder.c)
SRC = 									$(SRC_RENDER) \
										$(SRC_PARSING)
OBJ = $(SRC:%.c=built/%.o)

all: libft  $(NAME)

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

built/%.o: %.c include/miniRT.h
	@mkdir -p $(dir $@)
	$(CC) $(FLAG) -c $< -o $@

debug: FLAG += $(DFLAG)
debug:	re
		@echo "Debug_Build done"

libft:
	$(MAKE) -C lib/Libft_all

minilibx:
	$(MAKE) -C minilibx-linux
clean:
	rm -f $(OBJ)
	$(MAKE) -C lib/Libft_all clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C lib/Libft_all fclean

re: fclean all

.PHONY: all clean fclean re
