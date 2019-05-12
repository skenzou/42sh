# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/13 13:11:49 by aben-azz          #+#    #+#              #
#    Updated: 2019/05/12 04:02:42 by aben-azz         ###   ########.fr        #
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
SRC_DIR			=	src/
INC_DIR			=	includes/
OBJ_DIR			=	objs/

SRC_BASE				=	ft_counti.c ft_round.c ft_intlen.c ft_ftoa.c ft_pow.c \
ft_count.c ft_indexof.c ft_isupper.c ft_islower.c ft_atoi.c ft_isalnum.c \
ft_bzero.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_lstadd.c  \
ft_lstdelone.c ft_lstiter.c ft_lstmap.c ft_lstnew.c ft_memalloc.c ft_memccpy.c \
ft_lstdel.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memdel.c ft_memmove.c \
ft_memset.c ft_putchar.c ft_putchar_fd.c ft_putendl.c ft_putendl_fd.c \
ft_putnbr_fd.c ft_putstr.c ft_putstr_fd.c ft_strcat.c ft_strchr.c ft_strclr.c \
ft_strcmp.c ft_strcpy.c ft_strdel.c ft_strdup.c ft_strequ.c ft_striter.c \
ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlen.c ft_strmap.c ft_strtrim.c \
ft_strsplit.c ft_strstr.c ft_strsub.c ft_toupper.c ft_strmapi.c ft_strncat.c \
ft_strncmp.c ft_strncpy.c ft_strnequ.c ft_strnew.c ft_strnstr.c ft_strrchr.c \
ft_putnbr.c ft_isalpha.c ft_tolower.c get_next_line.c ft_repeat_char.c \
ft_utoa_base.c ft_intlen_base.c min.c max.c ft_printf.c geters.c \
handle_numbers.c handlers.c ft_lstrev.c ft_lstdestroy.c ft_count_words.c \
ft_itoa_base.c rgb2dec.c ft_percent.c get_color_from_percent.c ft_rand.c \
ft_is_space.c ft_strendswith.c ft_strstartswith.c ft_lastindexof.c \
ft_strreplace.c ft_strsplitwhitespace.c ft_substr.c ft_split_count.c \
ft_levenshtein.c ft_strcjoin.c
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
