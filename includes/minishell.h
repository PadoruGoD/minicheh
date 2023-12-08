/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gipaul <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 15:57:24 by gipaul            #+#    #+#             */
/*   Updated: 2023/12/08 15:38:40 by gipaul           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <strings.h>
# include <stddef.h>
# include <stdlib.h>
# include <string.h>
# include <crt_externs.h>
# include "../libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <errno.h>
# include <limits.h>
# include <dirent.h>
# include <errno.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <signal.h>
# include <termios.h>
# include <malloc/malloc.h>

# define CMD_OK 1
# define PIPE_OK 2
# define ENTRY_TOKEN 3
# define HEREDOC_TOKEN 4
# define EXIT_TOKEN 5
# define APPEND_TOKEN 6
# define BUILTIN_OK 7
# define PIPE_ERROR 8

typedef struct s_list
{
	int				id;
	int				fd_in;
	int				fd_out;
	char			*value;
	char			**arg;
	struct s_list	*next;
	struct s_list	*prev;
}	t_list;

typedef struct s_cur
{
	int				m;
	int				i;
	int				l;
	int				k;
	char			*tmp;
}	t_cur;

typedef struct s_data
{
	int				lexer_size;
	int				lexer_current;
	int				*is_quote;
	int				quote_count;
	int				dquote_count;
	int				heredoc_pipe[2];
	int				lastret;
	int				in_heredoc;
	int				exit_heredoc;
	int				heredoc;
	char			*input;
	char			**lexer;
	char			*word;
	char			**env;
	char			**path;
	char			*tmp_filename;
	char			tmp_fd;
	pid_t			*pid;
	int				n_pid;
	struct s_list	*first;
	struct s_list	*last;
}	t_data;

extern int	g_data_heredoc;

/*-----BUILTINS-----*/

void	path_in_env(t_data *shell, char *new_pwd);
int		ft_cd(t_data *shell, t_list *cmd);
void	ft_echo(t_list *list);
void	ft_env(t_data *shell, t_list *list);
void	ft_exit(t_data *shell, t_list *list);
void	sort_env(char **env);
char	**array_dup(t_data *shell);
void	ft_export(t_data *shell, t_list *list);
//void	ft_pwd(t_data *shell, t_list *list);
int		ft_pwd(void);
void	remove_env(t_data *shell, int id);
void	unset_cmd(t_data *shell, char *arg);
void	hd_unset(t_data *shell, char **args);
void	ft_unset(t_list *list);

/*-UTILS-*/

int		find_token(t_data *shell, char *token);
char	*get_token(char *arg);
void	add_env(t_data *shell, char *arg);
void	export_cmd(t_data *shell, char *arg);
void	hd_export(t_data *shell, char **args);

/*-----EXEC-----*/

void	hd_child_exec(t_list *list, t_data *shell, char *cmd, char **args);
void	hd_parent_exec(t_list *list, t_data *shell, pid_t pid);
void	exec_cmd(t_list *list, t_data *shell);
void	exec_builtins(t_list *list, t_data *shell);
void	exec(t_data *shell);
void	close_all_fd(t_data *shell);
char	*add_path(t_data *shell, t_list *list);
void	prepare_cmd(t_data *shell, t_list *list, char **cmd, char ***args);
char	*append_buffer(char *result, char *buffer, size_t byte_read,
			size_t *total_byte);
char	*copy_fd_to_str(int fd);
void	set_heredoc_fd(t_list *list, int *currend_fd_in, t_data *shell);
int		heredoc_fd_2(t_list *list, t_data *shell);
void	set_exit_fd(t_list *list, int *current_fd_out);
void	set_append_fd(t_list *list, int *current_fd_out);
void	set_entry_fd(t_list *list, int *current_fd_in);
void	set_pipe_fd(t_list *list, int *currend_fd_in, int *currend_fd_out);
void	set_fd(t_data *shell);
void	pipe_and_exec(t_list *list, t_data *shell, char *cmd, char **args);
void	child_process(t_list *list, t_data *shell, char *cmd, char **args);
void	hd_child_error(int pid);
void	close_fd(t_list *list);
void	reset_fd(void);
void	hd_status(t_list *list, t_data *shell, int pid);
void	ft_dup2(int to_change, int new);
void	ft_close(int to_close);
void	ft_write(int fd, char *value, size_t size);
void	ft_unlink(char *name);

/*-----LEXER-----*/

void	init_lexer_malloc(t_data *shell);
void	free_lexer(t_data *shell);
void	clean_exit(char *msg, t_data *shell);
void	ft_free_tab(t_data *shell);
void	init_struct(t_data *shell, char **env);
void	lexer_size(char *input, t_data *shell);
char	**lexer(char *input, t_data *shell);
int		calculate_redir_to_char(char *input, int i, t_data *shell);
void	stock_in_struct(t_data *shell, char *word, int j, int only_count);
int		get_substr_real_length(char *str, int start_idx);
int		redir_to_char(char *input, int i, t_data *shell, int only_count);
int		pipe_to_char(char *input, int i, t_data *shell, int only_count);
int		word_to_char(char *input, int i, t_data *shell, int only_count);
int		quote_to_char(char *input, int i, t_data *shell, int only_count);
void	replace_with_empty(t_data *shell, t_cur *cur);
int		comp_word_len(char *input, int *i);
char	*allocate_word(int lenght, t_data *shell);
int		fill_word(char *input, int i_save, int only_count, t_data *shell);
int		ft_is_separator(char c);

/*-----MAIN-----*/

void	ft_shlvl(t_data *shell);
int		main(int ac, char **av, char *env[]);
char	*prompt_data(t_data *shell);
void	disable_ctrl_c(void);
void	child_sigint_hd(int sig);
void	sigint_hd(int sig);
void	sigquit_hd(int sig);
void	setup_signal(void);

/*-----PARSING-----*/

void	correct_redir(t_data *shell);
void	parsing(t_data *shell);
char	**ft_parsing_execve(char **env, t_data *shell);
int		is_builtin(char *tmp);
int		ft_check_cmd(char *ok, t_data *shell);
void	count_quote(char *input, t_data *shell);
int		ft_is_quote(char c);
int		ft_is_blank(char c);
int		ft_skip_blank(char *line, int i);
void	set_last_of_list(t_data *shell);
int		check_syntax(t_data *shell);
int		unclosed_quote_error(t_data *shell);
int		wrong_cmd_error(t_data *shell);
int		pipe_syntax_error(t_data *shell);
int		pipe_syntax_error_2(t_data *shell);
t_list	*ft_init_token(t_data *shell);
void	ft_add_token(t_data *shell, t_list *to_add);
void	ft_connect_token(t_list *list, t_list *to_add);
void	destroy_token(t_data *shell);

/*-----UTILS-----*/

void	replace_substring(char **str, t_cur *cur, t_data *shell);
void	expand_lastret(t_data *shell, t_cur *cur);
void	expander(t_data *shell, char **env);
void	expander_2(t_data *shell, t_cur *cur);
int		get_substr_length(char *str, int start_idx);
char	*create_new_string(char **str, t_cur *cur, t_data *shell);
char	*create_new_string2(char *prefix, t_cur *cur, char *temp_str);

#endif
