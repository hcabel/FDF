# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/02 18:27:31 by hcabel            #+#    #+#              #
#    Updated: 2019/04/19 18:24:50 by hcabel           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				=	libft.a
FLAGS				=	-Wall -Wextra -Werror -g

NAME_FOLDER_OBJECT 	= 	objects

PATH_SOURCES		=	srcs/
PATH_INCLUDE		=	includes/

PATH_OBJECT			=	$(NAME_FOLDER_OBJECT)/

PATH_STR			=	$(PATH_SOURCES)str/
PATH_LST			=	$(PATH_SOURCES)lst/
PATH_PUT			=	$(PATH_SOURCES)put/
PATH_IS				=	$(PATH_SOURCES)is/
PATH_MEM			=	$(PATH_SOURCES)mem/
PATH_OTHER			=	$(PATH_SOURCES)others/

LIST_STR			=	ft_strlen.c		\
						ft_strdup.c		\
						ft_strcpy.c		\
						ft_strncpy.c	\
						ft_strcat.c		\
						ft_strncat.c	\
						ft_strlcat.c	\
						ft_strchr.c		\
						ft_strrchr.c	\
						ft_strstr.c		\
						ft_strnstr.c	\
						ft_strcmp.c		\
						ft_strncmp.c	\
						ft_strnew.c		\
						ft_strdel.c		\
						ft_strclr.c		\
						ft_striter.c	\
						ft_striteri.c	\
						ft_strmap.c		\
						ft_strmapi.c	\
						ft_strequ.c		\
						ft_strnequ.c	\
						ft_strsub.c		\
						ft_strjoin.c	\
						ft_strtrim.c	\
						ft_strsplit.c	\
						ft_strrev.c		\
						ft_strndup.c	

LIST_LST			=	ft_lstnew.c		\
						ft_lstdelone.c	\
						ft_lstdel.c		\
						ft_lstadd.c		\
						ft_lstiter.c	\
						ft_lstmap.c		

LIST_PUT			=	ft_putchar.c	\
						ft_putstr.c		\
						ft_putendl.c 	\
						ft_putnbr.c		\
						ft_putchar_fd.c	\
						ft_putstr_fd.c	\
						ft_putendl_fd.c	\
						ft_putnbr_fd.c	

LIST_OTHER			=	ft_bzero.c		\
						ft_atoi.c		\
						ft_toupper.c 	\
						ft_tolower.c	\
						ft_itoa.c		\
						ft_lstnew.c		\
						ft_lstdelone.c	\
						ft_lstdel.c		\
						ft_lstadd.c		\
						ft_lstiter.c	\
						ft_lstmap.c		\
						ft_fibonacci.c	\
						ft_sqrt.c		\
						get_next_line.c			

LIST_IS				=	ft_isalpha.c	\
						ft_isdigit.c 	\
						ft_isalnum.c 	\
						ft_isascii.c 	\
						ft_isprint.c 	\
						ft_is_prime.c

LIST_MEM			=	ft_memset.c		\
						ft_memcpy.c		\
						ft_memccpy.c	\
						ft_memmove.c	\
						ft_memchr.c		\
						ft_memcmp.c		\
						ft_memalloc.c	\
						ft_memdel.c		

SOURCES				=	$(addprefix $(PATH_MEM), $(LIST_STR))		\
						$(addprefix $(PATH_LST), $(LIST_LST))		\
						$(addprefix $(PATH_PUT), $(LIST_PUT))		\
						$(addprefix $(PATH_OTHER), $(LIST_OTHER))	\
						$(addprefix $(PATH_IS), $(LIST_IS))			\
						$(addprefix $(PATH_MEM), $(LIST_MEM))

OBJECTS				=	$(addprefix $(PATH_OBJECT), $(LIST_STR:.c=.o))		\
						$(addprefix $(PATH_OBJECT), $(LIST_LST:.c=.o))		\
						$(addprefix $(PATH_OBJECT), $(LIST_PUT:.c=.o))		\
						$(addprefix $(PATH_OBJECT), $(LIST_OTHER:.c=.o))	\
						$(addprefix $(PATH_OBJECT), $(LIST_IS:.c=.o))		\
						$(addprefix $(PATH_OBJECT), $(LIST_MEM:.c=.o))

INCLUDES			=	$(addprefix -I, $(PATH_INCLUDE))

.PHONY: re clean fclean all
.SILENT: re fclean clean all $(NAME) $(OBJECTS) $(NAME_FOLDER_OBJECT)	\
			start_comp start_clean end_clean end_comp

all: start_comp $(NAME) end_comp

$(NAME): $(NAME_FOLDER_OBJECT) $(OBJECTS)
	echo "\r\033[0;35mCreate \033[0;32m[\033[0;33m$@\033[0;32m]                    "
	ar rc $(NAME) $(OBJECTS)
	ranlib $(NAME)

$(PATH_OBJECT)%.o: $(PATH_STR)%.c
	echo "\r\033[0;35mCreate \033[0;32m[\033[0;33m$@\033[0;32m]                    \c"
	gcc -o $@ $(FLAGS) $(INCLUDES) -c $<

$(PATH_OBJECT)%.o: $(PATH_LST)%.c
	echo "\r\033[0;35mCreate \033[0;32m[\033[0;33m$@\033[0;32m]                    \c"
	gcc -o $@ $(FLAGS) $(INCLUDES) -c $<

$(PATH_OBJECT)%.o: $(PATH_PUT)%.c
	echo "\r\033[0;35mCreate \033[0;32m[\033[0;33m$@\033[0;32m]                    \c"
	gcc -o $@ $(FLAGS) $(INCLUDES) -c $<

$(PATH_OBJECT)%.o: $(PATH_OTHER)%.c
	echo "\r\033[0;35mCreate \033[0;32m[\033[0;33m$@\033[0;32m]                    \c"
	gcc -o $@ $(FLAGS) $(INCLUDES) -c $<

$(PATH_OBJECT)%.o: $(PATH_IS)%.c
	echo "\r\033[0;35mCreate \033[0;32m[\033[0;33m$@\033[0;32m]                    \c"
	gcc -o $@ $(FLAGS) $(INCLUDES) -c $<

$(PATH_OBJECT)%.o: $(PATH_MEM)%.c
	echo "\r\033[0;35mCreate \033[0;32m[\033[0;33m$@\033[0;32m]                    \c"
	gcc -o $@ $(FLAGS) $(INCLUDES) -c $<

$(NAME_FOLDER_OBJECT):
	echo "\r\033[0;35mCreate \033[0;32m[\033[0;33m$@\033[0;32m]                    \c"
	mkdir -p $(NAME_FOLDER_OBJECT)

clean:
	echo "\r\033[0;31mRemove \033[0;32m[\033[0;33mall object\033[0;32m]                    "
	rm -f $(OBJECTS)

fclean: clean
	echo "\r\033[0;31mRemove \033[0;32m[\033[0;33m$(NAME)\033[0;32m]                      \c"
	rm -f $(NAME)
	echo "\r\033[0;31mRemove \033[0;32m[\033[0;33m$(NAME_FOLDER_OBJECT)\033[0;32m]                    "
	rm -rf $(NAME_FOLDER_OBJECT)

re: start_clean fclean end_clean all

start_clean:
	echo "\r \033[0;36m|------|  CLEAN START  |------| \n"

start_comp:
	echo "\r \033[0;36m|------| COMPILE START |------| \n"

end_clean:
	echo "\r\n \033[0;36m|------|   CLEAN END   |------| "

end_comp:
	echo "\r\n \033[0;36m|------|  COMPILE END  |------| \033[0;35m"

