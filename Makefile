# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/21 11:09:36 by hcabel            #+#    #+#              #
#    Updated: 2019/09/21 17:24:14 by hcabel           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

DEBUG			=	no
DL				=	yes

ifeq ($(DEBUG), yes)
	MSG			=	echo "\033[0;31m/!\\ Warning /!\\ \
						\033[0;35mDebug mode ON\033[0;34m"
	FLAGS		=	-g
else
	MSG			=	echo "\033[0;36mDebug mode OFF\033[0;35m"
	FLAGS		=	-Wall -Wextra -Werror
endif

ifeq (, $(wildcard libft))
ifeq ($(DL), yes)
	UPDATE		=	git clone https://github.com/hcabel/libft.git libft \
						&& echo '\n'
else
	UPDATE		=	echo "\033[0;31m/!\\ Warning /!\\ \033[0;36m DL is \
						off \n But you can add your libft\033[0;35m"
endif
endif

NAME			=	fdf

OBJECT_REP		=	objects
INCLUDE_REP		=	includes
SOURCES_REP		=	srcs
MINILIBX_REP	=	/usr/local/

INCLUDES_FILE	=	fdf.h

SOURCES			=	main.c		\
					input.c		\
					parsing.c	\
					line.c		\
					view.c		\
					hud.c		\
					color.c		

INCLUDES		=	-I $(MINILIBX_REP)include -I $(INCLUDE_REP)/ -I libft/$(INCLUDE_REP)
LIB				=	-L $(MINILIBX_REP)lib
FRAMEWORK		=	-framework OpenGL -framework Appkit

OBJECTS			=	$(addprefix $(OBJECT_REP)/, $(SOURCES:.c=.o))

.PHONY: all clean fclean re mkdir make
.SILENT: all clean fclean re $(OBJECT_FILE) $(NAME) $(OBJECTS) mkdir make \
			remake update remove norm norm_sources norm_includes make_norm

all: update $(NAME)
	$(MSG)

$(NAME): mkdir make $(OBJECTS)
	gcc $(FLAGS) -o $(NAME) $(OBJECTS) $(LIB) -lmlx $(FRAMEWORK) libft/libft.a 

mkdir:
	mkdir -p $(OBJECT_REP)

$(OBJECT_REP)/%.o: $(SOURCES_REP)/%.c $(INCLUDE_REP)/$(INCLUDES_FILE) Makefile
	gcc $(FLAGS) -o $@ $(INCLUDES) -c $<

clean:
	rm -rf $(OBJECT_REP)

fclean: clean
	rm -f $(NAME)

re: remove fclean all

remove:
	make -C libft re

update:
	$(UPDATE)

make:
	make -C libft

make_norm:
	make -C libft norm

norm_includes:
	echo "\r\033[0;31mNorme \033[0;32m[\033[0;33mInclcudes\033[0;32m]\033[0;34m"
	norminette $(INCLUDE_REP)

norm_sources:
	echo "\r\033[0;31mNorme \033[0;32m[\033[0;33mSources\033[0;32m]\033[0;34m"
	norminette $(SOURCES_REP)

norm: make_norm norm_includes norm_sources

