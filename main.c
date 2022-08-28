/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberneli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 22:13:09 by aberneli          #+#    #+#             */
/*   Updated: 2022/03/29 16:03:50 by aberneli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lexer.h>
#include <utils.h>
#include <env.h>
#include <exec.h>
#include <ms_signal.h>

#include <readline/readline.h>
#include <readline/history.h>

#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

uint64_t	g_status = 0;

static char	*ft_basename(char *s)
{
	char	*bname;
	size_t	i;

	bname = s;
	i = 0;
	while (s[i])
	{
		if (s[i] == '/')
			bname = &s[i + 1];
		i++;
	}
	return (bname);
}

static int	checkshell(t_env *e, t_cmd *cmd)
{
	char	*basename;
	char	*basecmd;

	if (cmd->next || !cmd->args[0] || cmd->builtin)
		return (0);
	basename = ft_basename(e->prgname);
	basecmd = ft_basename(cmd->args[0]);
	if (!basename || !basecmd)
		return (0);
	if (!basename[0] || !basecmd[0])
		return (0);
	if (ft_strcmp(basecmd, basename) == 0)
		return (1);
	return (0);
}

static void	minishell_exec(t_env *env, t_cmd *cmd)
{
	int	flag;

	if (cmd)
	{
		flag = checkshell(env, cmd);
		g_status = 1;
		tcsetattr(0, TCSANOW, &env->save);
		if (flag)
			init_sig_callbacks(1);
		exec(cmd, env);
		if (flag)
			init_sig_callbacks(0);
		tcsetattr(0, TCSANOW, &env->mod);
	}
	clean_cmd(cmd);
}

static void	minishell(t_env *env)
{
	t_pctrl	ctrl;
	int		quit;

	quit = 0;
	while (!quit)
	{
		g_status = 0;
		ctrl = prompt_user(env);
		if (ctrl.err == 0 && ctrl.curr_line)
			minishell_exec(env, ctrl.cmd);
		if (!ctrl.curr_line)
			quit = 1;
		else if (ctrl.full_line[0])
			add_history(ctrl.full_line);
		free(ctrl.full_line);
		free(ctrl.curr_line);
	}
}

int	main(int argc, char **argv, char **env_lst)
{
	t_env			env;

	(void)argc;
	(void)argv;
	init_sig_callbacks(0);
	env = env_init(env_lst);
	env.prgname = argv[0];
	tcgetattr(0, &env.save);
	env.mod = env.save;
	env.mod.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &env.mod);
	minishell(&env);
	ft_printf(1, 0, "exit\n");
	env_destroy(env.lst);
	free(env.pwd);
	free(env.codestr);
	clear_history();
	tcsetattr(0, TCSANOW, &env.save);
	return (env.lastcode);
}
