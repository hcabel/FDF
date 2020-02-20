# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/02 18:27:31 by hcabel            #+#    #+#              #
#    Updated: 2020/02/21 09:15:14 by hcabel           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

DEBUG				=	no

ifeq ($(DEBUG), yes)
	FLAGS			=	-g
	COLOR			=	\033[31m
else
	FLAGS			=	-Wall -Wextra -Werror
	COLOR			=	\033[32m
endif

NAME				=	fdf

NAME_FOLDER_OBJECT	=	objects

PATH_SOURCES		=	srcs/
PATH_INCLUDE		=	includes/
PATH_LIBG			=	minilibx/

PATH_OBJECT			=	$(NAME_FOLDER_OBJECT)/

_GRAS				=	\033[1m
_FADE				=	\033[2m
_ITALIQUE			=	\033[3m
_SOUSLIGNER			=	\033[4m
_BLACK				=	\033[30m
_RED				=	\033[31m
_GREEN				=	\033[32m
_YELLOW				=	\033[33m
_BLUE				=	\033[34m
_VIOLET				=	\033[35m
_CYAN				=	\033[36m
_WHITE				=	\033[37m
_END				=	\033[0m
OK_COLOR			=	\x1b[32;01m
WARN_COLOR			=	\x1b[33;01m
ERROR_COLOR			=	\x1b[31;01m

LIST				=	color.c		\
						hud.c		\
						input.c		\
						line.c		\
						main.c		\
						parsing.c	\
						view.c		\

SOURCES				=	$(addprefix $(PATH_SOURCES), $(LIST))
OBJECTS				=	$(addprefix $(PATH_OBJECT), $(LIST:.c=.o))

INCLUDES			=	-I $(PATH_INCLUDE) -I libft/$(PATH_INCLUDE) -I $(PATH_LIBG)/
FRAMEWORK			=	-framework OpenGL -framework Appkit
LIB					=	libft/libftprintf.a $(PATH_LIBG)/libmlx.a

START				=	1
PRC					=	0

.PHONY:		re refclean reall fclean fcleanref cleanref all allref clean cleanref reref norme renorme
.SILENT:	re refclean reall fclean fcleanref cleanref all allref clean cleanref reref norme renorme\
				$(NAME) $(OBJECTS) $(NAME_FOLDER_OBJECT)

all: allref $(NAME)
	if [[ $(DEBUG) == yes ]]; then echo "\n$(_BLUE)        <==========|$(ERROR_COLOR)$(_SOUSLIGNER)   End   $(_END)$(_BLUE)|==========>        "; \
	else echo "\n$(_BLUE)        <==========|$(OK_COLOR)$(_SOUSLIGNER)   End   $(_END)$(_BLUE)|==========>        "; fi

allref:
	if [[ $(START) -eq 1 ]]; then echo "$(_BLUE) <=================|$(_SOUSLIGNER)$(WARN_COLOR) $(NAME) $(_END)$(_BLUE)|=================>"; fi
	$(eval START = 0)
	Make -C libft

reall: $(NAME)
	if [[ $(DEBUG) == yes ]]; then echo "\n$(_BLUE)        <==========|$(ERROR_COLOR)$(_SOUSLIGNER)   End   $(_END)$(_BLUE)|==========>        "; \
	else echo "\n$(_BLUE)        <==========|$(OK_COLOR)$(_SOUSLIGNER)   End   $(_END)$(_BLUE)|==========>        "; fi

$(NAME): $(NAME_FOLDER_OBJECT) $(OBJECTS)
	if [[ $(START) -eq 1 ]]; then echo "$(_BLUE) <=================|$(_SOUSLIGNER)$(WARN_COLOR) $(NAME) $(_END)$(_BLUE)|=================>"; fi
	$(eval START = 0)
	clang -g $(FLAGS) -o $(NAME) $(INCLUDES) $(FRAMEWORK) $(LIB) $(OBJECTS)

$(PATH_OBJECT)%.o: $(PATH_SOURCES)%.c $(PATH_INCLUDE)/$(NAME).h Makefile libft/$(PATH_INCLUDE)/libft.h libft/Makefile
	$(eval PRC = $(shell echo "$(PRC) + 1" | bc -l))
	printf "\r$(_VIOLET)[$(_GRAS)%3.f%%$(_END)$(_VIOLET)] $(_CYAN)[> $(COLOR)$(_GRAS)%-17s%17s$(_END)$(_CYAN) <]\t" \
	$(shell echo "100 / $(words $(SOURCES)) * $(PRC)" | bc -l) $(shell echo $@ | cut -d '/' -f2)  $(shell echo $< | cut -d '/' -f2)
	clang -g $(FLAGS) -o $@ $(INCLUDES) -c $<

$(NAME_FOLDER_OBJECT):
	if [[ $(START) -eq 1 ]]; then echo "$(_BLUE) <=================|$(_SOUSLIGNER)$(WARN_COLOR) $(NAME) $(_END)$(_BLUE)|=================>"; fi
	$(eval START = 0)
	mkdir -p $(NAME_FOLDER_OBJECT)

clean: cleanref
	echo "$(COLOR)[$(_GRAS)Remove$(_END)$(COLOR)] $(_GRAS)$(COLOR)$(NAME_FOLDER_OBJECT)"
	rm -rf $(NAME_FOLDER_OBJECT)
	if [[ $(DEBUG) == yes ]]; then echo "$(_BLUE)        <==========|$(ERROR_COLOR)$(_SOUSLIGNER)   End   $(_END)$(_BLUE)|==========>        "; \
	else echo "$(_BLUE)        <==========|$(OK_COLOR)$(_SOUSLIGNER)   End   $(_END)$(_BLUE)|==========>        "; fi

cleanref:
	if [[ $(START) -eq 1 ]]; then echo "$(_BLUE) <=================|$(_SOUSLIGNER)$(WARN_COLOR) $(NAME) $(_END)$(_BLUE)|=================>"; fi
	$(eval START = 0)
	make -C libft clean

fclean: fcleanref
	echo "$(COLOR)[$(_GRAS)Remove$(_END)$(COLOR)] $(_GRAS)$(COLOR)$(NAME)$(_END)"
	rm -f $(NAME)
	echo "$(COLOR)[$(_GRAS)Remove$(_END)$(COLOR)] $(_GRAS)$(COLOR)$(NAME_FOLDER_OBJECT)$(_END)"
	rm -rf $(NAME_FOLDER_OBJECT)
	if [[ $(DEBUG) == yes ]]; then echo "$(_BLUE)        <==========|$(ERROR_COLOR)$(_SOUSLIGNER)   End   $(_END)$(_BLUE)|==========>        "; \
	else echo "$(_BLUE)        <==========|$(OK_COLOR)$(_SOUSLIGNER)   End   $(_END)$(_BLUE)|==========>        "; fi

fcleanref:
	if [[ $(START) -eq 1 ]]; then echo "$(_BLUE) <=================|$(_SOUSLIGNER)$(WARN_COLOR) $(NAME) $(_END)$(_BLUE)|=================>"; fi
	$(eval START = 0)
	make -C libft fclean

refclean:
	if [[ $(START) -eq 1 ]]; then echo "$(_BLUE) <=================|$(_SOUSLIGNER)$(WARN_COLOR) $(NAME) $(_END)$(_BLUE)|=================>"; fi
	$(eval START = 0)
	echo "$(COLOR)[$(_GRAS)Remove$(_END)$(COLOR)] $(_GRAS)$(COLOR)$(NAME)$(_END)"
	rm -f $(NAME)
	echo "$(COLOR)[$(_GRAS)Remove$(_END)$(COLOR)] $(_GRAS)$(COLOR)$(NAME_FOLDER_OBJECT)$(_END)"
	rm -rf $(NAME_FOLDER_OBJECT)

re: reref refclean reall

reref:
	if [[ $(START) -eq 1 ]]; then echo "$(_BLUE) <=================|$(_SOUSLIGNER)$(WARN_COLOR) $(NAME) $(_END)$(_BLUE)|=================>"; fi
	$(eval START = 0)
	Make -C libft re

norme: renorme
	echo "$(_VIOLET)\c"
	norminette $(SOURCES)
	norminette $(PATH_INCLUDE)
	if [[ $(DEBUG) == yes ]]; then echo "$(_BLUE)        <==========|$(ERROR_COLOR)$(_SOUSLIGNER)   End   $(_END)$(_BLUE)|==========>        "; \
	else echo "$(_BLUE)        <==========|$(OK_COLOR)$(_SOUSLIGNER)   End   $(_END)$(_BLUE)|==========>        "; fi

renorme:
	if [[ $(START) -eq 1 ]]; then echo "$(_BLUE) <=================|$(_SOUSLIGNER)$(WARN_COLOR) $(NAME) $(_END)$(_BLUE)|=================>"; fi
	$(eval START = 0)
	make -C libft norme
