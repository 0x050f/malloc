# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/09/16 10:53:35 by lmartin           #+#    #+#              #
#    Updated: 2020/09/17 03:06:12 by lmartin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

## PIMPED MAKEFILE ##

# COLORS #

# This is a minimal set of ANSI/VT100 color codes
_END		=	\e[0m
_BOLD		=	\e[1m
_UNDER		=	\e[4m
_REV		=	\e[7m

# Colors
_GREY		=	\e[30m
_RED		=	\e[31m
_GREEN		=	\e[32m
_YELLOW		=	\e[33m
_BLUE		=	\e[34m
_PURPLE		=	\e[35m
_CYAN		=	\e[36m
_WHITE		=	\e[37m

# Inverted, i.e. colored backgrounds
_IGREY		=	\e[40m
_IRED		=	\e[41m
_IGREEN		=	\e[42m
_IYELLOW	=	\e[43m
_IBLUE		=	\e[44m
_IPURPLE	=	\e[45m
_ICYAN		=	\e[46m
_IWHITE		=	\e[47m

# **************************************************************************** #

# NORMINETTE #

NORMINETTE	:=	$(shell which norminette)

ifeq ($$?, 1)
	NORMINETTE := ${HOME}/.norminette/norminette.rb
endif

# HOSTTYPE #

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

## VARIABLES ##

# COMPILATION #

CC			=	gcc

CC_FLAGS	=	-Wall -Wextra -Werror

SANITIZE	=	-g3 -fsanitize=address

# DELETE #

RM			=	rm -rf


# DIRECTORIES #

DIR_LIBFT		=	./libft/

DIR_LIBFT_HEADERS	=	$(DIR_LIBFT)includes/

DIR_HEADERS		=	./includes/

DIR_SRCS		=	./srcs/

DIR_OBJS		=	./compiled_srcs/

DIR_MAIN_OBJS	=	./compiled_srcs/

SUB_DIRS		=	.

SUB_DIR_OBJS	=	$(SUB_DIRS:%=$(DIR_OBJS)%)

# FILES #

MAIN_FILE		=	main.c

SRCS			=	malloc.c \
					free.c \
					realloc.c

# COMPILED_SOURCES #

LIBFT		=	$(DIR_LIBFT)libft.a

LIBFT_FLAGS	=	-L$(DIR_LIBFT) -lft

MAIN_OBJ	=	$(MAIN_FILE:%.c=$(DIR_OBJS)%.o)

OBJS		=	$(SRCS:%.c=$(DIR_OBJS)%.o)

NAME		=	libft_malloc.so

DYNAMIC_LIB =	libft_malloc_$(HOSTTYPE).so

STATIC_LIB	=	libft_malloc.a

MAIN		=	main

# **************************************************************************** #

## RULES ##

all:			$(NAME)

# VARIABLES RULES #

$(NAME):		$(DYNAMIC_LIB)
				@ln -sf $(DYNAMIC_LIB) $(NAME)
				@printf "$(_GREEN) Library '$(DYNAMIC_LIB)' linked as '$(NAME)'. $(_END)✅\n"

$(DYNAMIC_LIB):	$(LIBFT) $(OBJS)
				@printf "\033[2K\r$(_GREEN) All files has been compiled into '$(DIR_OBJS)'. $(_END)✅\n"
				@$(CC) $(CC_FLAGS) $(LIBFT_FLAGS) $(OBJS) -shared -o $(DYNAMIC_LIB)
				@printf "$(_GREEN) Library '$(DYNAMIC_LIB)' created. $(_END)✅\n"


$(LIBFT):
				@printf "$(_BLUE) make -C $(DIR_LIBFT) $(_END)\n"
				@$(MAKE) -C $(DIR_LIBFT) MAKEFLAGS=
				@printf "$(_BLUE) Back in malloc's makefile $(_END)\n"

$(MAIN):		$(NAME) $(STATIC_LIB) $(MAIN_OBJ)
				@$(CC) $(CC_FLAGS) -L. -lft_malloc -I $(DIR_HEADERS) -I $(DIR_LIBFT_HEADERS) $(MAIN_OBJ) -o $(MAIN)
				@printf "\033[2K\r$(_GREEN) Executable '$(MAIN)' compiled. $(_END)✅\n"

$(STATIC_LIB):
				@cp -f $(LIBFT) ./$(STATIC_LIB)
				@ar rc $(STATIC_LIB) $(OBJS)
				@ranlib $(STATIC_LIB)
				@printf "$(_GREEN) Library '$(STATIC_LIB)' created. $(_END)✅\n"

# COMPILED_SOURCES RULES #

$(OBJS):		| $(DIR_OBJS)

$(DIR_OBJS)%.o: $(DIR_SRCS)%.c
				@printf "\033[2K\r $(_YELLOW)Compiling $< $(_END)⌛"
				@$(CC) $(CC_FLAGS) -I $(DIR_HEADERS) -I $(DIR_LIBFT_HEADERS) -c $< -o $@

$(DIR_OBJS):	$(SUB_DIR_OBJS)

$(SUB_DIR_OBJS):
				@mkdir -p $(SUB_DIR_OBJS)

$(MAIN_OBJ):			| $(DIR_MAIN_OBJS)

$(DIR_MAIN_OBJS)%.o:	%.c
						@printf "\033[2K\r $(_YELLOW)Compiling $< $(_END)⌛"
						@$(CC) $(CC_FLAGS) -I $(DIR_HEADERS) -I $(DIR_LIBFT_HEADERS) -c $< -o $@

# OBLIGATORY PART #

clean:
				@printf "$(_BLUE) make fclean -C $(DIR_LIBFT)$(_END)\n"
				@$(MAKE) fclean -C $(DIR_LIBFT)
				@printf "$(_BLUE) Back in malloc's makefile $(_END)\n"
				@$(RM) $(LIBFT)
				@$(RM) $(DIR_OBJS)
				@printf "$(_RED) '"$(DIR_OBJS)"' has been deleted. $(_END)🗑️\n"

fclean:			clean
				@$(RM) $(MAIN)
				@printf "$(_RED) '"$(MAIN)"' has been deleted. $(_END)🗑️\n"
				@$(RM) $(STATIC_LIB)
				@printf "$(_RED) '"$(STATIC_LIB)"' has been deleted. $(_END)🗑️\n"
				@$(RM) $(NAME)
				@printf "$(_RED) '"$(NAME)"' has been deleted. $(_END)🗑️\n"
				@$(RM) $(DYNAMIC_LIB)
				@printf "$(_RED) '"$(DYNAMIC_LIB)"' has been deleted. $(_END)🗑️\n"

norm:
				@printf "$(_BLUE) make norm -C $(DIR_LIBFT)$(_END)\n"
				@$(MAKE) norm -C $(DIR_LIBFT)
				@printf "$(_BLUE) Back in malloc's makefile $(_END)\n"
				@$(NORMINETTE) $(DIR_SRCS)
				@$(NORMINETTE) $(DIR_HEADERS)

re:				fclean all

# PHONY #

.PHONY:			all clean fclean re norm
