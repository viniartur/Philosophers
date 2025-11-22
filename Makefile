# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vvieira <vvieira@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/22 15:29:46 by vvieira           #+#    #+#              #
#    Updated: 2025/11/22 15:29:49 by vvieira          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
C_FLAGS = cc -Wall -Wextra -Werror -g -pthread

SRC = 	src/main.c		\
		src/init.c		\
		src/utils.c		\
		src/monitor.c	\
		src/routine.c

OBJ = $(SRC:.c=.o)

RESET = \033[0m
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
RED = \033[0;31m

all: $(NAME)

$(NAME): $(OBJ)
	@printf "$(BLUE)Linking $(NAME)...$(RESET)\n"
	@$(C_FLAGS) $(OBJ) -o $(NAME)
	@printf "$(GREEN)✔ $(NAME) created successfully!$(RESET)\n"

%.o: %.c
	@printf "$(YELLOW)Compiling $<...$(RESET)\n"
	@$(C_FLAGS) -c $< -o $@

clean:
	@printf "$(RED)Cleaning object files...$(RESET)\n"
	@rm -f $(OBJ)

fclean: clean
	@printf "$(RED)Cleaning executable $(NAME)...$(RESET)\n"
	@rm -f $(NAME)

re: fclean
	@$(MAKE) all

.PHONY: all clean fclean re