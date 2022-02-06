# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: tblanker <tblanker@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2022/01/26 13:55:50 by tblanker      #+#    #+#                  #
#    Updated: 2022/02/06 15:48:08 by tblanker      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

CC_FLAGS = -Wall -Werror -Wextra

NAME = philo

CC = clang

FILES = c_files/main.c c_files/error.c c_files/init.c c_files/threads.c

OFILES = $(FILES:.c=.o)

all : $(NAME)

$(NAME) : $(OFILES) libft.a
	$(CC) $(CC_FLAGS) $(OFILES) -lft -o $(NAME)

%.o: %.c
	$(CC) $(CC_FLAGS) -pthread -o $@ -c $<

libft.a :
	$(MAKE) -C libft
	@mv libft/libft.a .

clean	:
	rm -rf $(OFILES)
	$(MAKE) clean -C libft

fclean	:	clean
	rm -rf libft.a $(NAME)

re		: fclean all