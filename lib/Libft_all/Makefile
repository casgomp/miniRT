# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aabdella <aabdella@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/02 18:27:10 by aabdella          #+#    #+#              #
#    Updated: 2026/03/05 18:19:19 by aabdella         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_FT = $(addprefix ft_, $(addsuffix .c, isquote atol_flow atoll atol read_pipe strcmp free_three_ary free_ary_count free_array isalpha free_double isdigit isalnum isascii isprint isspace trim_newline strlen memset bzero memcpy memmove append_str strlcpy strlcat toupper tolower strchr strcmp isnumber strrchr strncmp memchr memcmp strnstr lst_strsize atoi atof calloc strdup substr strjoin strtrim split itoa strmapi striteri putchar_fd putstr_fd putendl_fd putnbr_fd printf putstr_p putnum_p puthex_p swap))

SRC_OTHER = get_next_line.c

SRC = $(SRC_FT) $(SRC_OTHER) $(SRC_BONUS)

SRC_BONUS = $(addprefix ft_, $(addsuffix _bonus.c, lstnew lstadd_front lstsize lstlast lstadd_back lstdelone lstclear lstiter lstmap))

OBJS := $(SRC:%.c=%.o)

NAME = libft.a

ARNAME = ar rcs $(NAME)

CC = cc

CCFLAGS = -Wall -Werror -Wextra

CPPFLAGS = -I.

all: $(NAME)

$(NAME): $(OBJS)
	$(ARNAME) $(OBJS)

%.o: %.c libft.h
	$(CC) $(CPPFLAGS) $(CCFLAGS) -o $@ -c $<

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
