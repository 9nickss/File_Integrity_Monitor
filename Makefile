##
## 9nickss, 2025
## File_Integrity_Monitor
## File description:
## Makefile
##

NAME	=	fim

SRCS	=	$(wildcard src/*.c) \
			$(wildcard src/**/*.c)

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
