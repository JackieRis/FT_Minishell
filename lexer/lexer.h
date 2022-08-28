/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberneli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 09:19:01 by aberneli          #+#    #+#             */
/*   Updated: 2022/03/25 18:37:18 by aberneli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <stdlib.h>
# include <utils.h>
# include <stdio.h>
# include <env.h>
# include <exec.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_token
{
	struct s_token	*next;
	t_str			str;
}					t_token;

// parse controller

typedef struct s_pctrl
{
	t_token		*pipes;
	t_cmd		*cmd;
	char		*full_line;
	char		*curr_line;
	int			err;
}				t_pctrl;

// heredoc.c
char		*parse_heredoc(char *delim, t_env *e, int quote_flag);

// token.c
t_token		*new_token(void);
void		append_token(t_token **beg, t_token *add);
void		clean_token(t_token *tok);

// io.c
t_io		*new_io(t_redir type, char *file, int fdnbr, t_env *e);
int			append_io(t_io **beg, t_io *add);
void		clean_io(t_io *io);

// cmd.c
t_cmd		*new_cmd(t_str *str, t_io *redir, t_env *e);
void		append_cmd(t_cmd **beg, t_cmd *add);
void		clean_cmd(t_cmd *cmd);

// redir.c
int			extract_redir(char *s, size_t *i, t_env *e, t_io **io);
int			parse_redir(char *s, t_env *e, t_io **tmp);

// pipes.c
t_token		*pipes_split(t_pctrl *ctrl, char *line);
int			pipes_err(int err);

// lexer.c
int			is_empty(char *str);
t_pctrl		prompt_user(t_env *e);

#endif
