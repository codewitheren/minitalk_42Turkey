# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: muerdoga <muerdoga@student.42kocaeli.com.  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/28 15:48:15 by muerdoga          #+#    #+#              #
#    Updated: 2022/08/28 16:09:17 by muerdoga         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minitalk.a
CLIENT = client
SERVER = server

PRINTF = printf/libftprintf.a

SRC_C = client.c
SRC_S = server.c
OBJ_C = $(SRC_C:.c=.o)
OBJ_S = $(SRC_S:.c=.o)

CC = gcc
CFLAG = -Wall -Wextra -Werror
RM = rm -rf

all: $(NAME)

$(NAME): $(OBJ_C) $(OBJ_S)
	@make -C ./printf
	@gcc -o server $(SRC_S) $(CFLAG) $(PRINTF)
	@gcc -o client $(SRC_C) $(CFLAGS) $(PRINTF)

clean:
	@rm -f $(OBJ_S) $(OBJ_C)
	@make -C ./printf clean

fclean: clean
	@rm -f server client
	@make -C ./printf fclean

re: fclean all

.PHONY: all clean fclean re
 	  	
