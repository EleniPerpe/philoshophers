# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/09 16:46:14 by eperperi          #+#    #+#              #
#    Updated: 2024/06/25 13:41:33 by eperperi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#.SILENT:

CC = cc -g #-fsanitize=thread


# valgrind --tool=helgrind

CFLAGS = -Wall -Wextra -Werror

INCLUDE	= -lpthread

SRCS = main.c tools.c threads.c dead_check.c init.c

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
