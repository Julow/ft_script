/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/28 18:42:06 by jaguillo          #+#    #+#             */
/*   Updated: 2015/05/28 20:05:28 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_script.h"
#include <errno.h>
#include <unistd.h>

/*
** ft_exec
** ----
** Try to execute a binary
** ----
** The command name is argv[0]
** Search in the PATHs (except if the cmd contains '/')
** Never return if success
** If 'env' is NULL, the environ variable is used
** ----
** Return errno if fail else never return
** ----
** TODO: move get_env to ft_
*/
static char		*key_equ(char *env, const char *key)
{
	int				i;

	i = 0;
	while (env[i] != '\0' && env[i] == key[i])
		i++;
	if (key[i] == '\0' && env[i] == '=')
		return (env + i + 1);
	return (NULL);
}

static char		*get_env(const char *key, char **env)
{
	extern char		**environ;
	char			*tmp;
	int				i;

	if (env == NULL)
		env = environ;
	i = -1;
	while (env[++i] != NULL)
	{
		tmp = key_equ(env[i], key);
		if (tmp != NULL)
			return (tmp);
	}
	return (NULL);
}

static void		try_exec(t_sub path, t_sub cmd, char **argv, char **env)
{
	char			cmd_path[path.length + cmd.length + 2];

	ft_memcpy(cmd_path, path.str, path.length);
	ft_memcpy(cmd_path + path.length + 1, cmd.str, cmd.length);
	cmd_path[path.length] = '/';
	cmd_path[path.length + cmd.length + 1] = '\0';
	if (path.length == 0)
		execve(cmd_path + 1, argv, env);
	else
		execve(cmd_path, argv, env);
}

int				ft_exec(char **argv, char **env)
{
	t_sub			sub;
	t_sub			cmd;
	int				err;
	extern char		**environ;

	if (env == NULL)
		env = environ;
	if (argv[0] == NULL || (sub.str = get_env("PATH", env)) == NULL)
		return (ENOENT);
	sub.length = 0;
	cmd = ft_sub(argv[0], 0, -1);
	if (ft_strchr(cmd.str, '/') != NULL)
		return (try_exec(sub, cmd, argv, env), errno);
	err = ENOENT;
	while (ft_subnextc(&sub, ':'))
	{
		try_exec(sub, cmd, argv, env);
		if (err == ENOENT)
			err = errno;
	}
	return (err);
}
