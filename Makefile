# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: tblanker <tblanker@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2022/01/26 13:55:50 by tblanker      #+#    #+#                  #
#    Updated: 2022/03/10 21:02:47 by tblanker      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

CC_FLAGS = -Wall -Werror -Wextra -pthread -fsanitize=thread -g

NAME = philo

CC = clang

FILES = c_files/main.c c_files/error.c c_files/init.c c_files/threads.c \
		c_files/state_changes.c c_files/death_checks.c c_files/utils.c \
		c_files/ft_atoi.c

OFILES = $(FILES:.c=.o)

GREEN = \033[0;38;5;114m
RED = \033[38;5;124m
BLUE = \033[38;5;153m
NORMAL = \033[38;5;255m

all : $(NAME)

$(NAME) : $(OFILES)
	@echo "-----------------------------------"
	@echo "$(BLUE)Created executable:$(NORMAL)	$(NAME)"
	@echo "-----------------------------------"
	@$(CC) $(CC_FLAGS) $(OFILES) -o $(NAME)

%.o: %.c
	@echo "$(GREEN)Created object file:$(NORMAL)	$@"
	$(CC) $(CC_FLAGS) -g -o $@ -c $<

clean	:
	@echo "-----------------------------------"
	@echo "$(RED)Object files removed.$(NORMAL)"
	@echo "-----------------------------------"
	@rm -rf $(OFILES)

fclean	:	clean
	@echo "$(RED)./philo removed.$(NORMAL)"
	@echo "-----------------------------------"
	rm -rf $(NAME)

re		: fclean all

commit	:	
			git add .
			git commit -m "saving current state for backtracking"