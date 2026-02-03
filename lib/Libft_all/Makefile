# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aabdella <aabdella@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/02 18:27:10 by aabdella          #+#    #+#              #
#    Updated: 2026/02/03 17:24:06 by aabdella         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_FT = $(addprefix ft_, $(addsuffix .c, isquote atol_flow atoll atol read_pipe strcmp free_three_ary free_ary_count free_array isalpha isdigit isalnum isascii isprint isspace strlen memset bzero memcpy memmove strlcpy strlcat toupper tolower strchr strcmp strrchr strncmp memchr memcmp strnstr atoi calloc strdup substr strjoin strtrim split itoa strmapi striteri putchar_fd putstr_fd putendl_fd putnbr_fd printf putstr_p putnum_p puthex_p))

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
