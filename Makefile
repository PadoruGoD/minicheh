# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gipaul <marvin@42lausanne.ch>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/13 15:57:09 by gipaul            #+#    #+#              #
#    Updated: 2023/11/15 16:46:22 by gipaul           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#=======================================#
#[MINISHELL] Fonctions partie principale#
#=======================================#

SRCS = 	main/main.c \
		src/builtins/cd.c \
		src/builtins/echo.c \
		src/builtins/env.c \
		src/builtins/export.c \
		src/builtins/unset.c \
		src/builtins/utils.c \
		src/builtins/exit.c \
		src/signal/signal.c \
		src/signal/signal2.c \
		src/lst/cmd.c \
		src/lst/hd.c \
		src/lst/hd_2.c \
		src/lst/token.c \
		src/lst/token_2.c \
		src/utils/add_q.c \
		src/utils/cleanstr.c \
		src/utils/cut.c \
		src/utils/file_redirect.c \
		src/utils/file_redirect2.c \
		src/utils/file_redirect3.c \
		src/utils/file_redirect4.c \
		src/utils/ft_chdir.c \
		src/utils/ft_chdollar.c \
		src/utils/ft_chdollar2.c \
		src/utils/ft_chdollar3.c \
		src/utils/ft_chdollar_hd.c \
		src/utils/ft_chdollar_hd2.c \
		src/utils/ft_chwc.c \
		src/utils/ft_chwc2.c \
		src/utils/ft_chwc_utils.c \
		src/utils/ft_chwc_utils2.c \
		src/utils/ft_cut_chevron.c \
		src/utils/ft_ecrase.c \
		src/utils/ft_epur_str.c \
		src/utils/ft_error.c \
		src/utils/ft_exist.c \
		src/utils/ft_exit.c \
		src/utils/ft_free.c \
		src/utils/ft_hd_finder.c \
		src/utils/ft_pgross_str.c \
		src/utils/ft_redirect_chwc.c \
		src/utils/ft_redirect_chwc2.c \
		src/utils/ft_replace.c \
		src/utils/ft_skip_hd.c \
		src/utils/ft_split2.c \
		src/utils/ft_split3.c \
		src/utils/ft_split4.c \
		src/utils/split_utils.c \
		src/utils/ft_strjoin2.c \
		src/utils/ft_trijoin.c \
		src/utils/here_doc.c \
		src/utils/john_side.c \
		src/utils/parse_error.c \
		src/utils/parse_error2.c \
		src/utils/parsing.c \
		src/utils/prompt.c \
		src/utils/purge_q.c \
		src/utils/quajoin.c \
		src/utils/sort_word.c \
		src/utils/utils.c \
		src/utils/utils2.c \
		src/utils/utils3.c \
		src/utils/utils4.c \
		src/utils/utils5.c \
		src/utils/utils6.c \
		src/exec/exec.c \
		src/exec/exec_2.c \
		src/exec/ope.c \
		src/exec/ope_2.c \
		src/exec/pipe.c \
		src/exec/utils.c


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
