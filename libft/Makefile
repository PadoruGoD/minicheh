# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gipaul <marvin@42lausanne.ch>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/13 16:23:14 by gipaul            #+#    #+#              #
#    Updated: 2023/12/06 17:06:41 by gipaul           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRCS = ft_isdigit.c ft_memset.c ft_strjoin.c ft_strtrim.c\
		ft_isprint.c ft_putchar_fd.c ft_strlcat.c ft_substr.c\
		ft_atoi.c ft_itoa.c ft_putendl_fd.c ft_strlcpy.c ft_tolower.c\
		ft_bzero.c ft_putnbr_fd.c ft_strlen.c ft_toupper.c ft_calloc.c\
		ft_memchr.c ft_putstr_fd.c ft_strmapi.c ft_isalnum.c ft_memcmp.c\
		ft_split.c ft_strncmp.c ft_isalpha.c ft_memcpy.c ft_strchr.c\
		ft_strnstr.c ft_isascii.c ft_memmove.c ft_strdup.c ft_strrchr.c\
		ft_striteri.c get_next_line.c ft_strcmp.c ft_isspace.c\
		ft_strrcmp.c ft_strstr.c


BONUS = ft_lstnew.c ft_lstadd_front.c ft_lstlast.c ft_lstsize.c\
		ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c\
		ft_lstmap.c ft_lstmap.c ft_next.c

OBJS = ${SRCS:.c=.o}

OBJSBONUS = ${BONUS:.c=.o}

CC		= gcc
RM		= rm -f

CFLAGS = -Wall -Wextra -Werror -g

all:	${NAME}

$(NAME): ${OBJS}
		ar rcs ${NAME} ${OBJS}

bonus:	${OBJS} ${OBJSBONUS}
		ar rcs ${NAME} ${OBJS} ${OBJSBONUS}

clean:
		${RM} ${OBJS} ${OBJSBONUS}

fclean:	clean
		${RM} ${NAME}

re:		fclean all

.PHONY:	all clean fclean re 
