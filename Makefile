# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/09 16:46:14 by eperperi          #+#    #+#              #
#    Updated: 2024/06/09 17:11:16 by eperperi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#.SILENT:

CC = cc #-g -fsanitize=address

CFLAGS = -Wall -Wextra -Werror

SRCS = main.c tools.c

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

.PHONY:  all clean fclean re bonus
