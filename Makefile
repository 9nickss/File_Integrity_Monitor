##
## EPITECH PROJECT, 2024
## makefile
## File description:
## make moi des files
##

NAME	=	FIM

SRCS	=	$(wildcard src/*.c)

OBJS	=	$(SRCS:.c=.o)

all		:	$(NAME)

$(NAME)	:	$(OBJS)
			gcc -o $(NAME) $(SRCS) -I /include/

CFLAGS	:	-Wall -Wextra -Wshadow

clean	:
			rm -f $(OBJS)

fclean	:	clean
			rm $(NAME)

re		:	fclean all
