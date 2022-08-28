/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberneli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 17:45:31 by tnguyen-          #+#    #+#             */
/*   Updated: 2022/03/29 12:36:19 by aberneli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include <stdlib.h>
# include <stdio.h>

# include <termios.h>
# include <readline/history.h>

typedef struct s_key_val
{
	char	*name;
	char	*value;
}			t_key_val;

typedef struct s_envlst
{
	struct s_envlst	*next;
	char			*name;
	char			*value;
}					t_envlst;

typedef struct s_envquery
{
	char		*var;
	size_t		nlen;
	int			dollar;
}				t_envquery;

typedef struct s_env
{
	char			*pwd;
	char			*codestr;
	t_envlst		*lst;
	int				size;
	int				lastcode;
	char			*prgname;
	struct termios	save;
	struct termios	mod;
}				t_env;

t_env		env_init(char **envp);
void		env_export(t_env *e, char *name, char *value);
void		env_unset(t_env *e, char *name);
void		env_display(t_env *e);
char		*env_get(t_env *e, char *name);
char		**env_split(t_env *e);
t_envlst	*new_lst(char *name, char *value);
t_envlst	*env_delete(t_envlst *e);
void		env_destroy(t_envlst *e);
void		env_print_order(t_env *e);
t_envquery	env_query(t_env *e, char *name);

#endif