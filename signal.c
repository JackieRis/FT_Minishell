/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberneli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 14:41:52 by aberneli          #+#    #+#             */
/*   Updated: 2022/03/29 13:30:13 by aberneli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_signal.h"

void	ctrlc_handler_bis(int a, siginfo_t *t, void *c)
{
	(void)a;
	(void)t;
	(void)c;
}

void	ctrlc_handler(int a, siginfo_t *t, void *c)
{
	if (g_status == 3)
	{
		g_status = 128 + dup(0);
		close(0);
	}
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	if (g_status == 0)
		rl_redisplay();
	(void)a;
	(void)t;
	(void)c;
}

void	ctrlslash_handler_bis(int a, siginfo_t *t, void *c)
{
	(void)a;
	(void)t;
	(void)c;
}

void	ctrlslash_handler(int a, siginfo_t *t, void *c)
{
	if (g_status == 1)
	{
		write(2, "Quit: 3\n", 8);
	}
	else if (g_status == 0)
	{
		rl_on_new_line();
		rl_redisplay();
	}
	(void)a;
	(void)t;
	(void)c;
}

void	init_sig_callbacks(int flag)
{
	struct sigaction	act;

	ft_memset(&act, 0, sizeof(struct sigaction));
	act.__sigaction_u.__sa_sigaction = ctrlc_handler;
	if (flag)
		act.__sigaction_u.__sa_sigaction = ctrlc_handler_bis;
	act.sa_flags = SA_SIGINFO | SA_RESTART;
	sigaction(SIGINT, &act, NULL);
	act.__sigaction_u.__sa_sigaction = ctrlslash_handler;
	if (flag)
		act.__sigaction_u.__sa_sigaction = ctrlslash_handler_bis;
	act.sa_flags = SA_SIGINFO | SA_RESTART;
	sigaction(SIGQUIT, &act, NULL);
}
