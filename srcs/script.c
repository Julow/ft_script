/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   script.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juloo <juloo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/26 16:28:38 by juloo             #+#    #+#             */
/*   Updated: 2015/05/26 17:28:15 by juloo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_script.h"
#include "msg.h"
#include <unistd.h>
#include <sys/wait.h>

static void		exec_cmd(t_env *env)
{
	char *const		def_cmd[] = {DEFAULT_SHELL, "-i", NULL};

	if (env->cmd == NULL || env->cmd[0] == NULL)
	{
		execv(DEFAULT_SHELL, def_cmd);
		return ;
	}
	// exec env->cmd
}

static void		script_read(t_env *env)
{
	int				len;
	char			buff[INPUT_BUFFER];

	while ((len = read(env->in_fd, buff, INPUT_BUFFER)) > 0)
	{
		write(1, buff, len);
		ft_write(&(env->out), buff, len);
	}
}

t_bool			start_script(t_env *env)
{
	pid_t			pid;

	if ((pid = fork()) < 0)
		return (ft_fdprintf(2, E_ERR, "Cannot fork"), false);
	if (pid == 0)
	{
		exec_cmd(env);
		_exit(0);
	}
	script_read(env);
	waitpid(pid, NULL, 0);
	return (true);
}
