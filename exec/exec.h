/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberneli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 23:06:33 by tnguyen-          #+#    #+#             */
/*   Updated: 2022/03/26 09:07:58 by aberneli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include <env.h>
# include <builtin.h>
# include <fcntl.h>

# include <sys/types.h>
# include <sys/stat.h>
# include <sys/errno.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <signal.h>

typedef enum e_redir
{
	REDIR_IN,
	REDIR_HEREDOC,
	REDIR_OUT = O_TRUNC,
	REDIR_APPEND = O_APPEND,
}				t_redir;

typedef struct s_io
{
	struct s_io		*next;
	t_redir			type;
	char			*file;
	int				fdnbr;
}					t_io;

typedef struct s_cmd
{
	struct s_cmd	*next;
	char			**args;
	t_io			*redirections;
	int				builtin;
	pid_t			f;
}					t_cmd;

typedef struct s_exec
{
	char	**env;
	char	**path;
	char	*pathvar;
	int		fdin[2];
	int		fdout[2];
}				t_exec;

typedef struct s_error
{
	int			err;
	int			errnum;
	char		*errpath;
}				t_error;

// fonction exec.c
void	exec(t_cmd *t, t_env *e);

// fonction exec_parse.c
char	*path_maker(t_exec *exe, t_env *e, char	*cmd);

//fonction access
//fonction exec_process.c
int		exec_redirection(t_io *t);
int		exec_process(t_cmd *t, t_exec *exec, t_env *e, int i);
int		solo_cmd(t_cmd *t, t_exec *exec);

// exec_execute.c
void	execute_cmd(t_cmd *t, t_exec *exe);

// exec_utils.c
int		status_to_error(int status);
void	wait_pid(t_cmd *t, t_env *e);

#endif