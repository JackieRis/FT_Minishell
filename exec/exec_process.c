/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberneli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 23:16:46 by tnguyen-          #+#    #+#             */
/*   Updated: 2022/03/26 09:07:49 by aberneli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

//fonction cerveau de gestion de lancement de process

static void	exec_sigdefault(void)
{
	struct sigaction	act;

	ft_memset(&act, 0, sizeof(struct sigaction));
	act.__sigaction_u.__sa_handler = SIG_DFL;
	sigaction(SIGINT, &act, NULL);
	act.__sigaction_u.__sa_handler = SIG_DFL;
	sigaction(SIGQUIT, &act, NULL);
}

static void	exec_here_doc(t_io *t)
{
	int	f;
	int	fd[2];

	pipe(fd);
	f = fork();
	if (f == 0)
	{
		close(fd[0]);
		ft_buf_write(fd[1], t->file, 4096);
		exit(0);
	}
	else if (f < 0)
		ft_printf(2, 1, "minishell: %s\n", strerror(errno));
	else
		dup2(fd[0], 0);
	close(fd[1]);
	close(fd[0]);
}

int	exec_redirection(t_io *t)
{
	int	fd;

	if (!t)
		return (0);
	if (t->type == REDIR_IN)
	{
		fd = open(t->file, 0);
		if (fd < 0)
			return (ft_printf(2, 1, \
				"minishell: %s: %s\n", t->file, strerror(errno)));
		dup2(fd, 0);
		close(fd);
	}
	else if (t->type == REDIR_HEREDOC)
		exec_here_doc(t);
	else
	{
		fd = open(t->file, O_CREAT | t->type | O_WRONLY, 0664);
		if (fd < 0)
			return (ft_printf(2, 1, \
				"minishell: %s: %s\n", t->file, strerror(errno)));
		dup2(fd, 1);
		close(fd);
	}
	return (exec_redirection(t->next));
}

int	solo_cmd(t_cmd *t, t_exec *exec)
{
	int		status;

	t->f = fork();
	if (t->f < 0)
		return (ft_printf(2, 1, "minishell: %s\n", strerror(errno)));
	else if (t->f != 0)
	{
		waitpid(t->f, &status, 0);
		return (status_to_error(status));
	}
	exec_sigdefault();
	if (exec_redirection(t->redirections) == 1)
		exit (1);
	execute_cmd(t, exec);
	return (1);
}

int	exec_process(t_cmd *t, t_exec *exec, t_env *e, int i)
{
	exec_sigdefault();
	if (i > 0)
	{
		if (dup2(exec->fdin[0], 0) < 0)
			ft_printf(2, 1, "minishell: %s\n", strerror(errno));
		close(exec->fdin[0]);
		close(exec->fdin[1]);
	}
	if (t->next)
	{
		if (dup2(exec->fdout[1], 1) < 0)
			ft_printf(2, 1, "minishell: %s\n", strerror(errno));
		close(exec->fdout[0]);
		close(exec->fdout[1]);
	}
	if (exec_redirection(t->redirections) == 1)
		exit (1);
	if (t->builtin)
		bi_execute(e, t->args, 1);
	execute_cmd(t, exec);
	return (0);
}
