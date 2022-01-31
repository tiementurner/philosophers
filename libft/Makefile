# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: tblanker <tblanker@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2019/11/05 12:12:06 by tblanker      #+#    #+#                  #
#    Updated: 2020/10/22 14:39:02 by tblanker      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME	=	libft.a

SRC		=	ft_bzero ft_memccpy ft_memchr ft_memcmp ft_memcpy\
ft_memmove ft_memset ft_strchr ft_strlcat ft_strlcpy ft_strlen\
ft_strncmp ft_strnstr ft_strrchr ft_atoi ft_calloc ft_isalnum\
ft_isalpha ft_isascii ft_isdigit ft_isprint ft_strdup\
ft_tolower ft_toupper ft_substr ft_strjoin ft_strtrim ft_split\
ft_itoa ft_strmapi ft_putchar_fd ft_putstr_fd ft_putendl_fd\
ft_putnbr_fd

B_SRCS	=	ft_lstnew_bonus ft_lstadd_front_bonus ft_lstsize_bonus\
ft_lstlast_bonus ft_lstadd_back_bonus ft_lstdelone_bonus\
ft_lstiter_bonus ft_lstmap_bonus ft_lstclear_bonus

CFILES	=	$(SRC:%=%.c)
OFILES	=	$(SRC:%=%.o)
BFILES	=	$(B_SRCS:%=%.c)
BOFILES	=	$(BFILES:.c=.o)
FLAGS	=	-Wall -Werror -Wextra

GREEN	= \x1b[32;01m
YELLOW	= \x1b[33;01m
RED		= \x1b[31;01m

all: $(NAME)

$(NAME): $(OFILES)
	@echo "$(YELLOW)\n\nLINKING LIB...\n"
	@ar rc $(NAME) $(OFILES)
	@echo "$(GREEN)\n\nLIBFT IS READY!\n\n"

%.o: %.c
	@echo "$(GREEN)Compiling $<"
	@gcc -o $@ -c $< $(FLAGS)

clean:
	@echo "$(RED)\n.O FILES DESTROYED\n"
	@rm -f $(OFILES) $(BOFILES)

fclean: clean
	@rm -f $(NAME)
	@echo "$(RED)\nLIBFT.A DESTROYED\n"

re: fclean all

bonus: $(OFILES) $(BOFILES)
	ar rc $(NAME) $(OFILES) $(BOFILES)
