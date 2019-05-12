# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/02 18:27:31 by hcabel            #+#    #+#              #
#    Updated: 2019/05/11 20:54:07 by hcabel           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	fdf
FLAGS		=	-Wall -Wextra -Werror -g # DEBUG -g


OBJECT_REP	=	object
SOURCES_REP =	srcs

SOURCES		=	main.c			\
				parsing.c		\
				struct.c		\
				struct2.c		\
				display_map.c	\
				projection.c	\
				action.c		\
				image.c			\
				line.c			\
				color.c			\
				HUD.c

INCLUDES	=	-I includes/ -I libft/includes
LIB			=	-L /usr/local/lib/
FRAMEWORK	=	-framework OpenGL -framework Appkit

OBJECTS		=	$(addprefix $(OBJECT_REP)/, $(SOURCES:.c=.o))

.PHONY: all clean fclean re mkdir make
.SILENT: all clean fclean re $(OBJECT_FILE) $(NAME) $(OBJECTS) mkdir make remake

all: $(NAME)

$(NAME): mkdir make $(OBJECTS) 
	gcc $(FLAGS) -o $(NAME) $(OBJECTS) $(LIB) -lmlx $(FRAMEWORK) libft/libft.a

$(OBJECT_REP)/%.o: $(SOURCES_REP)/%.c includes/fdf.h Makefile
	gcc $(FLAGS) -o $@ $(INCLUDES) -c $<
	
mkdir:
	mkdir -p $(OBJECT_REP)

make:
	make -C libft/

clean:
	rm -rf $(OBJECT_REP)

fclean: clean
	rm -f $(NAME)

remake:
	make -C libft/ re

re: fclean remake all
