SRC		=	main.c  controls/controls.c  planets/planets.c  render/render.c  ship/ship.c  ship/littledot.c
OBJ 	=	$(SRC:%.c=%.o)
CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror
NAME	=	newton
LIB_FLAGS	= -Lmlx -lmlx -lXext -lX11 -lm -lz -Imlx -g

all		: $(NAME)

%.o		: %.c
	$(CC) $(CFLAGS) -c $< -o $@ 
	
$(NAME)	: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIB_FLAGS) -o $(NAME)

clean	:
	rm -f $(OBJ)

fclean	:	clean
	rm -rf $(NAME)

re		:	fclean all

.PHONY	:	all bonus clean fclean re