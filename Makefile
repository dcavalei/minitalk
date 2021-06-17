# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dcavalei <dcavalei@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/14 12:48:35 by dcavalei          #+#    #+#              #
#    Updated: 2021/06/17 13:24:29 by dcavalei         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC			= $(shell find src -type f -name "*.c")
LIB			= $(shell find libs -type f -name "*.a")
INCLUDE		= $(addprefix -I, include)
OBJS		= $(SRC:.c=.o)
OBJS_CLIENT	= $(filter-out src/server.o, $(OBJS))
OBJS_SERVER	= $(filter-out src/client.o, $(OBJS))
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror
NAME_SERVER	= server
NAME_CLIENT	= client

all:		libft $(NAME_SERVER) $(NAME_CLIENT)

bonus:		all

libft:
			@$(MAKE) -C libs/libft/

$(NAME_SERVER):	libft $(OBJS_SERVER)
			@$(CC) -o $(NAME_SERVER) $(CFLAGS) $(INCLUDE) $(LIB) $(OBJS_SERVER)
			
$(NAME_CLIENT):	libft $(OBJS_CLIENT)
			@$(CC) -o $(NAME_CLIENT) $(CFLAGS) $(INCLUDE) $(LIB) $(OBJS_CLIENT)
.c.o:
			@echo "Creating object: $@"
			@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
			@rm -f $(OBJS)
			@$(MAKE) -C libs/libft/ clean

fclean:
			@$(MAKE) -C libs/libft/ fclean
			@rm -f $(OBJS)
			@rm -f $(NAME_SERVER)
			@rm -f $(NAME_CLIENT)

re:			fclean all

.PHONY:		all clean fclean re libft $(NAME_SERVER) $(NAME_CLIENT)
