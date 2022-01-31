# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: tblanker <tblanker@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2022/01/26 13:55:50 by tblanker      #+#    #+#                  #
#    Updated: 2022/01/26 14:56:43 by tblanker      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

CC_FLAGS = -Wall -Werror -Wextra

NAME = philo

CC = clang

FILES = c_files/main.c

OFILES = $(FILES:.c=.o)

all : $(NAME)

$(NAME) : $(OFILES) libft.a
	$(CC) $(CC_FLAGS) $(OFILES) -lft -o $(NAME)

%.o: %.c_
	$(CC) -pthread $(CC_FLAGS) -o $@ -c $<

libft.a :
	$(MAKE) -C libft
	@mv libft/libft.a .

clean	:
	rm -rf $(OFILES)
	$(MAKE) clean -C libft

fclean	:	clean
	rm -rf libft.a $(NAME)

re		: fclean all