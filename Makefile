# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gipaul <marvin@42lausanne.ch>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/13 15:57:09 by gipaul            #+#    #+#              #
#    Updated: 2023/12/07 16:26:30 by gipaul           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#=======================================#
#[MINISHELL] Fonctions partie principale#
#=======================================#

SRCS =	src/builtins/cd.c \
		src/builtins/echo.c \
		src/builtins/env.c \
		src/builtins/exit.c \
		src/builtins/export.c \
		src/builtins/pwd.c \
		src/builtins/unset.c \
		src/builtins/utils.c \
		src/exec/exec.c \
		src/exec/exec_utils.c \
		src/exec/heredoc_fd.c \
		src/exec/init_fd.c \
		src/exec/process.c \
		src/exec/status_hd.c \
		src/exec/systeme_call.c \
		src/lexer/init_exit_lexer.c \
		src/lexer/lexer.c \
		src/lexer/lexer_utils.c \
		src/lexer/lexer_utils_2.c \
		src/main/main.c \
		src/main/prompt.c \
		src/main/signal.c \
		src/parsing/correct_parse.c \
		src/parsing/parsing.c \
		src/parsing/parsing_utils.c \
		src/parsing/parsing_utils_2.c \
		src/parsing/syntax_checker.c \
		src/parsing/syntax_checker_2.c \
		src/parsing/token_hd.c \
		src/utils/string_utils.c \
		src/utils/expander.c


#====#
#Tags#
#====#

NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror
OUT_LIBS = -lreadline
OUT_LIBS += -L/Users/$(USER)/.brew/opt/readline/lib
DIALINK = -I/Users/$(USER)/.brew/opt/readline/include
OBJS = $(SRCS:.c=.o)
LIBFT = -L./libft -lft
HEADER	= includes/

#pour installer readline https://rawgit.com/kube/42homebrew/master/install.sh#

#=========#
#Commandes#
#=========#	

.c.o:
		$(CC) $(CFLAGS) $(DIALINK) -c $< -o $(<:.c=.o)

$(NAME): 	$(OBJS) $(HEADER)
			make -C libft
			make bonus -C libft
			$(CC) $(CFLAGS) $(OUT_LIBS) $(LIBFT) -o $(NAME) $(OBJS)

all: 	$(NAME)

clean:
		rm -f $(OBJS)
		make clean -C libft

fclean: clean
		rm -f $(NAME)
		make fclean -C libft

re: fclean all

.PHONY:		all clean fclean re
