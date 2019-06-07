# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/03 09:24:41 by midrissi          #+#    #+#              #
#    Updated: 2019/06/07 06:52:52 by midrissi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

_END			=	\x1b[0m
_BOLD			=	\x1b[1m
_UNDER			=	\x1b[4m
_REV			=	\x1b[7m
_GREY			=	\x1b[30m
_RED			=	\x1b[31m
_GREEN			=	\x1b[32m
_YELLOW			=	\x1b[33m
_BLUE			=	\x1b[34m
_PURPLE			=	\x1b[35m
_CYAN			=	\x1b[36m
_WHITE			=	\x1b[37m
_IGREY			=	\x1b[40m
_IRED			=	\x1b[41m
_IGREEN			=	\x1b[42m
_IYELLOW		=	\x1b[43m
_IBLUE			=	\x1b[44m
_IPURPLE		=	\x1b[45m
_ICYAN			=	\x1b[46m
_IWHITE			=	\x1b[47m
_MAGENTA		=	\x1b[35m

MSG				=	Compiling 42sh
.PHONY: all, $(NAME), clean, fclean, re

NAME = 42sh
cc = gcc
C_FLAGS = -Wall -Wextra -Werror
SRC_PATH = ./srcs/
SRC_LEXER = $(shell find srcs/lexer -type f -name "*.c")
SRC_EXECUTOR = $(shell find srcs/executor -type f -name "*.c")
SRC_PROMPT = $(shell find srcs/prompt -type f -name "*.c")
SRC_PARSER = $(shell find srcs/parser -type f -name "*.c")
SRC_ROOT = handler.c
SRC_NAME = $(SRC_LEXER) $(SRC_EXECUTOR) $(SRC_PROMPT) $(SRC_PARSER) $(SRC_ROOT)
OBJ_PATH = ./obj/
LFT_PATH = ./libft/
LFT_NAME = libft.a
INC_PATH = ./includes

OBJ_NAME = $(shell echo $(SRC_NAME:.c=.o) | sed -e 's/srcs\///g')
INC_FPATH = ./includes/shell.h ./includes/lexer.h ./includes/prompt.h \
						./includes/parser.h
SRC = $(addprefix $(SRC_PATH),$(SRC_NAME))
LONGEST			=	$(shell echo $(notdir $(SRC)) | tr " " "\n" | awk ' { if (\
				length > x ) { x = length; y = $$0 } }END{ print y }' | wc -c)
OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))
INC = $(addprefix -I,$(INC_PATH))

all: $(LFT_PATH)$(LFT_NAME) $(NAME)

$(LFT_PATH)$(LFT_NAME):
	@$(MAKE) -C $(LFT_PATH);

$(NAME): $(OBJ)
		@$(CC) -o $(NAME) -L $(LFT_PATH) -lft -ltermcap $^ -o $@
		@printf "$(_BOLD)$(_RED)./$(NAME) is ready for use\n$(_END)"

$(OBJ_PATH)%.o: $(SRC_PATH)%.c $(INC_FPATH)
		@mkdir -p $(OBJ_PATH)
		@mkdir -p $(OBJ_PATH)/lexer
		@mkdir -p $(OBJ_PATH)/parser
		@mkdir -p $(OBJ_PATH)/executor
		@mkdir -p $(OBJ_PATH)/prompt
		@$(CC) $(C_FLAGS) $(INC) -o $@ -c $<
		@printf "$(_BOLD)$(_BLUE)$(MSG)$(_END) $(_BOLD)$(_CYAN)%-$(LONGEST)s\
		$(_END)" $(notdir $<)
		@if test -s obj/$*.o; then \
		printf "$(_GREEN) [SUCCES]\n$(_END)"; fi

clean:
		@make -C $(LFT_PATH) clean
		@rm -rf $(OBJ_PATH)
		@echo "$(_BOLD)$(_RED)Sucesfuly removed all objects from minishell$(_END)"

fclean: clean
		@make -C $(LFT_PATH) fclean
		@rm -f $(NAME) .21sh_alias
		@echo "$(_BOLD)$(_RED)Sucessfuly removed ${NAME} from minishell$(_END)"

re: fclean all
