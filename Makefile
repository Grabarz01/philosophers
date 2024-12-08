# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fgrabows <fgrabows@student.42warsaw.pl>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/26 13:50:20 by fgrabows          #+#    #+#              #
#    Updated: 2024/12/08 19:36:40 by fgrabows         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o);

CC = cc
CFLAGS = -I includes/ #-Wall -Wextra -Werror
TR_FLAG = -pthread
all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(TR_FLAG) -o $(NAME) $(OBJ) 
	
%.o: %.c
	$(CC) $(CFLAGS) $(TR_FLAG) -c $< -o $@ 

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re  