# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acaryn <acaryn@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/01 19:28:45 by acaryn            #+#    #+#              #
#    Updated: 2021/04/10 17:19:08 by acaryn           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_three
CFLAGS = -Wall -Wextra -Werror
SRCDIR = src/
SRCS =	$(addprefix $(SRCDIR), \
		main.c \
		utils.c \
		threads.c \
		utils_to_three.c )

FILE_HEAD = includes/philosophers.h
HEAD =	includes
HEADERS = $(addprefix -I , $(HEAD))

all: $(NAME)

$(NAME): $(SRCS) $(FILE_HEAD)
	gcc $(CFLAGS) $(SRCS) $(HEADERS) -o $(NAME)

clean:
	rm -rf $(NAME)

fclean: clean

re: fclean all

.PHONY: all clean fclean re