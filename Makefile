# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/09 16:46:14 by eperperi          #+#    #+#              #
#    Updated: 2024/06/19 20:32:41 by eperperi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#.SILENT:

CC = cc -g #-fsanitize=thread


# valgrind --tool=helgrind

CFLAGS = -Wall -Wextra -Werror

INCLUDE	= -lpthread

SRCS = main.c tools.c threads.c

OFILES = $(SRCS:.c=.o)

NAME = philo

all: $(NAME)

$(NAME): $(OFILES)
	$(CC) $(OFILES) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) -f $(OFILES)

fclean: clean
	$(RM) -f $(NAME)

re: fclean all

.PHONY:  all clean fclean re
