# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/09/16 10:53:35 by lmartin           #+#    #+#              #
#    Updated: 2020/09/16 11:43:04 by lmartin          ###   ########.fr        #
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


# DELETE #

RM			=	rm -rf


# DIRECTORIES #

DIR_LIBFT		=	./libft/

DIR_HEADERS		=	./includes/

DIR_SRCS		=	./srcs/

DIR_OBJS		=	./compiled_srcs/

SUB_DIRS		=	.

SUB_DIR_OBJS	=	$(SUB_DIRS:%=$(DIR_OBJS)%)

# FILES #

SRCS			=	malloc.c

# COMPILED_SOURCES #

LIBFT		=	libft.a

OBJS		=	$(SRCS:%.c=$(DIR_OBJS)%.o)

NAME		=	libft_malloc_$(HOSTTYPE).so

LINKED_NAME =	libft_malloc.so

# **************************************************************************** #

## RULES ##

all:			$(NAME)

# VARIABLES RULES #

$(NAME):		$(LIBFT) $(OBJS)
				@printf "\033[2K\r$(_GREEN) All files compiled into '$(DIR_OBJS)'. $(_END)✅\n"
				@ar rc $(NAME) $(OBJS)
				@ranlib $(NAME)
				@printf "$(_GREEN) Library '$(NAME)' created. $(_END)✅\n"
				@ln -s $(LINKED_NAME) libft_malloc_$(HOSTTYPE).so
				@printf "$(_GREEN) Library '$(NAME)' linked as $(LINKED_NAME). $(_END)✅\n"

$(LIBFT):
				@printf "$(_BLUE) make -C $(DIR_LIBFT) $(_END)\n"
				@$(MAKE) -C $(DIR_LIBFT) MAKEFLAGS=
				@printf "$(_BLUE) Copy '$(LIBFT)' compiled in $(DIR_LIBFT) to . $(_END)✅\n"
				@cp -rf $(DIR_LIBFT)$(LIBFT) ./$(LIBFT)

# COMPILED_SOURCES RULES #

$(OBJS):		| $(DIR_OBJS)

$(DIR_OBJS)%.o: $(DIR_SRCS)%.c
				@printf "\033[2K\r $(_YELLOW)Compiling $< $(_END)⌛"
				@$(CC) $(CC_FLAGS) -I $(DIR_HEADERS) -c $< -o $@

$(DIR_OBJS):	$(SUB_DIR_OBJS)

$(SUB_DIR_OBJS):
				@mkdir -p $(SUB_DIR_OBJS)

# OBLIGATORY PART #

clean:
				@$(RM) $(LIBFT)
				@$(RM) $(DIR_OBJS)
				@printf "$(_RED) '"$(DIR_OBJS)"' has been deleted. $(_END)🗑️\n"
				@printf "$(_BLUE) make fclean -C $(DIR_LIBFT)$(_END)\n"
				@$(MAKE) fclean -C $(DIR_LIBFT)

fclean:			clean
				@$(RM) $(NAME)
				@printf "$(_RED) '"$(NAME)"' has been deleted. $(_END)🗑️\n"

norm:
				@$(NORMINETTE) $(DIR_SRCS)
				@$(NORMINETTE) $(DIR_HEADERS)
				@printf "$(_BLUE) make norm -C $(DIR_LIBFT)$(_END)\n"
				@$(MAKE) norm -C $(DIR_LIBFT)

re:				fclean all

# PHONY #

.PHONY:			all clean fclean re norm
