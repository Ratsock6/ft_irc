# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mgallais <mgallais@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/11 11:27:37 by mgallais          #+#    #+#              #
#    Updated: 2024/07/24 11:15:40 by mgallais         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME    = ircserv
CC      = c++
RM      = rm -f
CFLAGS += -g -Wall -Wextra -Werror -std=c++98
INCLUDE = -I include -I include/classes
DEBUG   = 0

SRC		= src/main.cpp \
		  src/signals.cpp \
		  src/classes/Server.cpp \
		  src/classes/Client.cpp \
		  src/commands/command.cpp \
		  src/commands/parsing.cpp \
		  src/classes/Channel.cpp #

OBJ		= $(SRC:.cpp=.o)

all:
	@printf "\033[1;36m\nStarting ircserv compilation\n\e[0m"
	@make -s redirect

redirect: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ)
	@printf "\033[1;92m >>> Ircserv compiled                                                     \n\n\033[0m"

%.o: %.cpp
	@printf "\033[0;33mCompilation de %-33.33s\r\e[0m" $@
	@if [ $(DEBUG) -eq 1 ]; then $(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@ -D DEBUG=1; else $(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@; fi

clean:
	@$(RM) $(OBJ)
	@printf "\033[1;31m- Object files deleted\n\033[0m"

fclean: clean	
	@$(RM) $(NAME)
	@printf "\033[1;31m- Executable file deleted\n\033[0m"

re: fclean all

test:
	@make -s re
	@make -s clean
	@clear
	@echo "\033[1;92mDONE !"

debug: fclean
	@make -s DEBUG=1 all
	@make clean
	@clear

.PHONY: all redirect clean fclean re test debug
