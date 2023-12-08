/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gipaul <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:31:39 by gipaul            #+#    #+#             */
/*   Updated: 2023/12/06 18:00:31 by gipaul           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
// # include "wraloc.h"

typedef struct s_listo
{
	void			*content;
	struct s_listo	*next;
}					t_listo;

char	*ft_strstr(char	*str, char	*to_find);
int		ft_strrcmp(const char *s1, const char *s2, size_t n);
t_listo	*ft_next(t_listo *lst);
void	ft_error(int e);
char	*get_next_line(int fd);
int		ft_strcmp(char *s1, char *s2);
int		ft_isspace(char c);

// partie 1

void	*ft_memset(void *b, int c, size_t len);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t len);
void	*ft_memchr(const void *s, int c, size_t n);

void	ft_bzero(void *s, size_t n);

int		ft_memcmp(const void *s1, const void *s2, size_t n);

size_t	ft_strlen(const	char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);

int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);

int		ft_toupper(int c);
int		ft_tolower(int c);

int		ft_atoi(const char *str);

char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);

int		ft_strncmp(const char *s1, const char *s2, size_t n);

char	*ft_strdup(const char *s1);
void	*ft_calloc(size_t count, size_t size);

// partie 2

char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);

char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));

void	ft_striteri(char *s, void (*f)(unsigned int, char*));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);

// partie bonus

t_listo	*ft_lstnew(void *content);
t_listo	*ft_lstlast(t_listo *lst);

int		ft_lstsize(t_listo *lst);

void	ft_lstadd_front(t_listo **alst, t_listo *new);
void	ft_lstadd_back(t_listo **alst, t_listo *new);

void	ft_lstdelone(t_listo *lst, void (*del)(void *));
void	ft_lstclear(t_listo **lst, void (*del)(void *));
void	ft_lstiter(t_listo *lst, void (*f)(void *));

t_listo	*ft_lstmap(t_listo *lst, void *(*f)(void *), void (*del)(void *));

#endif
