# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/03 09:24:41 by midrissi          #+#    #+#              #
#    Updated: 2019/06/20 16:47:34 by midrissi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#
##	COLORS
#

_END		=	\x1b[0m
_BOLD		=	\x1b[1m
_UNDER		=	\x1b[4m
_REV		=	\x1b[7m
_GREY		=	\x1b[30m
_RED		=	\x1b[31m
_GREEN		=	\x1b[32m
_YELLOW		=	\x1b[33m
_BLUE		=	\x1b[34m
_PURPLE		=	\x1b[35m
_CYAN		=	\x1b[36m
_WHITE		=	\x1b[37m
_IGREY		=	\x1b[40m
_IRED		=	\x1b[41m
_IGREEN		=	\x1b[42m
_IYELLOW	=	\x1b[43m
_IBLUE		=	\x1b[44m
_IPURPLE	=	\x1b[45m
_ICYAN		=	\x1b[46m
_IWHITE		=	\x1b[47m
_MAGENTA	=	\x1b[35m

#
##	MISC
#

NAME		= 42sh

MSG			=	$(_BOLD)$(_BLUE)Compiling 42sh$(_END)

CC			= gcc
C_FLAGS		= -Wall -Wextra -Werror -g -v#-fsanitize=address
SRC_PATH	= srcs/
OBJ_PATH	= .obj/
LFT_PATH	= ./libft/
LFT_NAME	= libft.a
INC_PATH	= includes/
INC_FPATH	= includes/shell.h includes/lexer.h includes/prompt.h \
			includes/parser.h includes/executor.h
INC			= -Iincludes -I$(LFT_PATH)includes

LONGEST		:=	$(shell echo $(notdir $(SRC)) | tr " " "\n" | awk ' { if (\
			length > x ) { x = length; y = $$0 } }END{ print y }' | wc -c)

#
##	SRCS & OBJS
#

_LEXER 		= lexer.c print_lexer.c utils.c
LEXER 		= $(addprefix $(SRC_PATH)lexer/,$(_LEXER))
_LEXER_O 	:= $(_LEXER:.c=.o)
LEXER_O 	:= $(LEXER:.c=.o)

_EXEC 		= alias_builtin.c alias_init.c alias_utils.c bg_builtin.c tools.c\
			bin_hash.c cd_builtin.c echo_builtin.c env_builtin.c \
			err_handler.c executor.c exit_builtin.c expansions.c \
			export_builtin.c fg_builtin.c fg_utils.c ft_fork.c get_options.c \
			handle_redir.c job_utils.c jobs_builtin.c param_expansion.c \
			handle_pipe.c pre_exec.c quote_expansion.c redir_utils.c \
			set_builtin.c setenv_builtin.c shell_var.c tab_utils.c \
			test_builtin.c tilde_expansion.c type_builtin.c unset_builtin.c \
			unsetenv_builtin.c cd_builtin_utils.c hash_builtin.c \
			cd_builtin_chdir.c parse_pipes.c utils2.c handle_hdoc.c signals.c \
			signals_utils.c
EXEC 		= $(addprefix $(SRC_PATH)executor/,$(_EXEC))
_EXEC_O 	:= $(_EXEC:.c=.o)
EXEC_O 		:= $(EXEC:.c=.o)

_PROMPT 	= arrow_events.c \
			completion.c \
			copy_cut.c \
			ctrl_r.c \
			history.c \
			history_expansion.c \
			history_up_down.c \
			home_end_events.c \
			init_struct.c \
			key_events.c \
			main.c \
			move.c \
			others.c \
			prompt_prefix.c \
			push.c \
			read_alt.c \
			read_arrow.c \
			read_key.c \
			reader.c \
			shift_events.c \
			signal_handler.c
PROMPT 		= $(addprefix $(SRC_PATH)prompt/,$(_PROMPT))
_PROMPT_O 	:= $(_PROMPT:.c=.o)
PROMPT_O 	:= $(PROMPT:.c=.o)

_PARSER		= ast.c build_ast.c inhibitors.c parser.c redir_list.c \
			syntax_errors.c
PARSER		= $(addprefix $(SRC_PATH)parser/,$(_PARSER))
_PARSER_O 	:= $(_PARSER:.c=.o)
PARSER_O 	:= $(PARSER:.c=.o)

_ROOT 		= handler.c
ROOT 		= $(SRC_PATH)handler.c
_ROOT_O 	:= $(_ROOT:.c=.o)
ROOT_O 		:= $(ROOT:.c=.o)

SRC			:= $(LEXER) $(EXEC) $(PROMPT) $(PARSER) $(ROOT)
_OBJ		:= $(_LEXER_O) $(_EXEC_O) $(_PROMPT_O) $(_PARSER_O) $(_ROOT_O)
OBJ_		:= $(LEXER_O) $(EXEC_O) $(PROMPT_O) $(PARSER_O) $(ROOT_O)
OBJ			:= $(addprefix $(OBJ_PATH), $(_OBJ))

#
##	RULES
#

all: $(LFT_PATH)$(LFT_NAME) $(NAME)

$(LFT_PATH)$(LFT_NAME):
	@$(MAKE) -C $(LFT_PATH);

$(NAME): $(OBJ)
	@$(CC) $(C_FLAGS) -o $(NAME) -L $(LFT_PATH) -lft -ltermcap $^ -o $@
	@printf "\r\033[K$(_BOLD)$(_RED)./$(NAME) is ready for use\n$(_END)"

$(OBJ_PATH)%.o: $(SRC_PATH)lexer/%.c $(INC_FPATH)
	@printf "\r\033[K$(MSG) $(_BOLD)$(_CYAN)%-$(LONGEST)s\$(_END)" $(notdir $<)
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(C_FLAGS) $(INC) -o $@ -c $<

$(OBJ_PATH)%.o: $(SRC_PATH)executor/%.c $(INC_FPATH)
	@printf "\r\033[K$(MSG) $(_BOLD)$(_CYAN)%-$(LONGEST)s\$(_END)" $(notdir $<)
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(C_FLAGS) $(INC) -o $@ -c $<

$(OBJ_PATH)%.o: $(SRC_PATH)prompt/%.c $(INC_FPATH)
	@printf "\r\033[K$(MSG) $(_BOLD)$(_CYAN)%-$(LONGEST)s\$(_END)" $(notdir $<)
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(C_FLAGS) $(INC) -o $@ -c $<

$(OBJ_PATH)%.o: $(SRC_PATH)parser/%.c $(INC_FPATH)
	@printf "\r\033[K$(MSG) $(_BOLD)$(_CYAN)%-$(LONGEST)s\$(_END)" $(notdir $<)
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(C_FLAGS) $(INC) -o $@ -c $<

$(OBJ_PATH)%.o: $(SRC_PATH)%.c $(INC_FPATH)
	@printf "\r\033[K$(MSG) $(_BOLD)$(_CYAN)%-$(LONGEST)s\$(_END)" $(notdir $<)
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(C_FLAGS) $(INC) -o $@ -c $<

clean: clean_obj
		@make clean -C $(LFT_PATH)

clean_obj:
		@rm -rf $(OBJ_PATH)
		@echo "$(_BOLD)$(_RED)Successfully removed all objects from 42sh\
		$(_END)"

fclean: clean_obj
		@make fclean -C $(LFT_PATH)
		@rm -f $(NAME) .21sh_alias
		@echo "$(_BOLD)$(_RED)Successfully removed ${NAME} from 42sh\
		$(_END)"

re: fclean all

.PHONY: all, $(NAME), clean, fclean, re, clean_obj
