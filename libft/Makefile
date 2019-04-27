# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/12 06:27:40 by aben-azz          #+#    #+#              #
#    Updated: 2019/04/12 07:36:02 by midrissi         ###   ########.fr        #
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
NAME			=	libft.a
CC				=	gcc
AR				=	ar -rc
MKDIR			=	mkdir -p
RM				=	/bin/rm -rf
W_FLAGS			=	-Wall -Wextra -Werror -Ofast
FLAGS			=	$(W_FLAGS)
DELTA			=	$$(echo "$$(tput cols)-47"|bc)
SRCS			=	$(addprefix $(SRC_DIR), $(SRC_BASE))
OBJS			=	$(addprefix $(OBJ_DIR), $(SRC_BASE:.c=.o))
NB				=	$(words $(SRC_BASE))
INDEX			=	0
SRC_DIR			=	srcs/
INC_DIR			=	includes/
OBJ_DIR			=	objs/

SRC_BASE		= SRCS DE LA LIBFT A RAJOUTER

all:
	@make -j $(NAME)

$(NAME): $(OBJ_DIR) $(OBJS)
	@$(AR) $(NAME) $(OBJS)
	@ranlib $(NAME)
	@printf "\r\x1b[32m✅  DONE $(NAME)\033[0m\033[K\n"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJ_DIR)
	@$(eval DONE=$(shell echo $$(($(INDEX)*20/$(NB)))))
	@$(eval PERCENT=$(shell echo $$(($(INDEX)*100/$(NB)))))
	@$(eval COLOR=$(shell echo $$(($(PERCENT)%35+196))))
	@$(eval TO_DO=$(shell echo $$((20-$(INDEX)*20/$(NB)))))
	@printf "\r\033[38;5;11mCompiling %1.100s : %2d%% \033[48;5;%dm%*s\033[0m%*s\033[48;5;255m \033[0m \033[38;5;11m %*.*s\033[0m\033[K" $(NAME) $(PERCENT) $(COLOR) $(DONE) "" $(TO_DO) "" $(DELTA) $(DELTA) "$@"
	@$(CC) $(FLAGS) -c $< -o $@ -I $(INC_DIR)
	@$(eval INDEX=$(shell echo $$(($(INDEX)+1))))

$(OBJ_DIR):
	@$(MKDIR) $(OBJ_DIR)
	@$(MKDIR) $(dir $(OBJS))

clean:
	@$(RM) $(OBJ_DIR)
	@printf "\r\033[38;5;202m✖  clean $(NAME)\033[0m\033[K\n"

fclean: clean
	@$(RM) $(NAME)
	@printf "\r\033[38;5;196m❌  fclean $(NAME)\033[0m\033[K\n"

re: fclean all

.PHONY: all clean fclean re
