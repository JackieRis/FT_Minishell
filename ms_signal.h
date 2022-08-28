/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_signal.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberneli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 14:43:06 by aberneli          #+#    #+#             */
/*   Updated: 2022/03/29 13:30:25 by aberneli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_SIGNAL_H
# define MS_SIGNAL_H

# include <lexer.h>
# include <utils.h>
# include <env.h>
# include <exec.h>

# include <stdlib.h>
# include <signal.h>
# include <unistd.h>

# include <readline/readline.h>
# include <readline/history.h>

extern uint64_t	g_status;

void	ctrlc_handler(int a, siginfo_t *t, void *c);
void	ctrlc_handler_bis(int a, siginfo_t *t, void *c);
void	ctrlslash_handler(int a, siginfo_t *t, void *c);
void	ctrlslash_handler_bis(int a, siginfo_t *t, void *c);
void	init_sig_callbacks(int flag);

#endif