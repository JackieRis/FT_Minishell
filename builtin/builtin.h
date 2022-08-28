/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberneli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 00:45:58 by aberneli          #+#    #+#             */
/*   Updated: 2022/02/16 14:54:48 by aberneli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include <env.h>
# include <utils.h>
# include <exec.h>

# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <sys/errno.h>

typedef struct s_cmd	t_cmd;

// bi_utils.c
int		which_builtin(const char *name);
void	bi_parentexec(t_cmd *t, t_env *e);
int		bi_execute(t_env *env, char **argv, int child);

int		bi_echo(t_env *env, char **argv, int child);
int		bi_cd(t_env *env, char **argv, int child);
int		bi_pwd(t_env *env, char **argv, int child);
int		bi_export(t_env *env, char **argv, int child);
int		bi_unset(t_env *env, char **argv, int child);
int		bi_env(t_env *env, char **argv, int child);
int		bi_exit(t_env *env, char **argv, int child);

#endif
