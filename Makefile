_END			=	\x1b[0m
_BOLD			=	\x1b[1m
_UNDER		=	\x1b[4m
_REV			=	\x1b[7m
_GREY			=	\x1b[30m
_RED			=	\x1b[31m
_GREEN		=	\x1b[32m
_YELLOW		=	\x1b[33m
_BLUE			=	\x1b[34m
_PURPLE		=	\x1b[35m
_CYAN			=	\x1b[36m
_WHITE		=	\x1b[37m
_IGREY		=	\x1b[40m
_IRED			=	\x1b[41m
_IGREEN		=	\x1b[42m
_IYELLOW	=	\x1b[43m
_IBLUE		=	\x1b[44m
_IPURPLE	=	\x1b[45m
_ICYAN		=	\x1b[46m
_IWHITE		=	\x1b[47m
NAME			=	21sh
CC				=	gcc
FLAGS			=	-Wall -Wextra -Werror
D_FLAGS		=	-g
DELTA			=	$$(echo "$$(tput cols)-47"|bc)
LIBFT_DIR	=	libft/
LIBFT_LIB	=	$(LIBFT_DIR)libft.a -ltermcap
LIBFT_INC	=	$(LIBFT_DIR)includes/
SRC_DIR		=	srcs/
INC_DIR		=	includes/
OBJ_DIR		=	obj/
SRC_BASE 	= main.c arrow_events.c key_events.c reader.c signal_handler.c \
others.c
SRCS			=	$(addprefix $(SRC_DIR), $(SRC_BASE))
OBJS			=	$(addprefix $(OBJ_DIR), $(SRC_BASE:.c=.o))
NB				=	$(words $(SRC_BASE))
INDEX			=	0

all :
	@make -C $(LIBFT_DIR)
	@make -j $(NAME)

$(NAME):		$(LIBFT_LIB) $(OBJ_DIR) $(OBJS)
	@$(CC) $(OBJS) -o $(NAME) \
		-I $(INC_DIR) -I $(LIBFT_INC) $(LIBS) $(LIBFT_LIB) $(FLAGS) $(D_FLAGS)
	@printf "\r\x1b[32m✅  DONE $(NAME)\033[0m\033[K\n"

$(LIBFT_LIB):
	@make -C $(LIBFT_DIR)

$(OBJ_DIR) :
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(dir $(OBJS))

$(OBJ_DIR)%.o :	$(SRC_DIR)%.c | $(OBJ_DIR)
	@$(eval DONE=$(shell echo $$(($(INDEX)*20/$(NB)))))
	@$(eval PERCENT=$(shell echo $$(($(INDEX)*100/$(NB)))))
	@$(eval COLOR=$(shell echo $$(($(PERCENT)%35+196))))
	@$(eval TO_DO=$(shell echo $$((20-$(INDEX)*20/$(NB)))))
	@printf "\r\033[38;5;11mCompiling %1.100s : %2d%% \033[48;5;%dm%*s\033[0m%*s\033[48;5;255m \033[0m \033[38;5;11m %*.*s\033[0m\033[K" $(NAME) $(PERCENT) $(COLOR) $(DONE) "" $(TO_DO) "" $(DELTA) $(DELTA) "$@"
	@$(CC) $(FLAGS) $(D_FLAGS)  -c $< -o $@\
		-I $(INC_DIR)\
		-I $(LIBFT_INC)
	@$(eval INDEX=$(shell echo $$(($(INDEX)+1))))
clean:			cleanlib
	@rm -rf $(OBJ_DIR)
	@printf "\r\033[38;5;202m✖  clean $(NAME).\033[0m\033[K\n"

cleanlib:
	@make -C $(LIBFT_DIR) clean

fclean:			clean fcleanlib
	@rm -f $(NAME)
	@printf "\r\033[38;5;196m❌  fclean $(NAME).\033[0m\033[K\n"

fcleanlib:		cleanlib
	@make -C $(LIBFT_DIR) fclean

re:				fclean all
