/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   script.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juloo <juloo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/26 16:28:38 by juloo             #+#    #+#             */
/*   Updated: 2015/05/26 23:47:40 by juloo            ###   ########.fr       */
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

static void		script_read(t_env *env, int fd)
{
	int				len;
	char			buff[INPUT_BUFFER];

	while ((len = read(fd, buff, INPUT_BUFFER)) > 0)
	{
		write(1, buff, len);
		ft_write(&(env->out), buff, len);
		ft_flush(&(env->out));
	}
}

t_bool			start_script(t_env *env)
{
	pid_t			pid;
	int				fds[2];

	if (pipe(fds) < 0)
		return (ft_fdprintf(2, E_ERR, "Cannot pipe"), false);
	if ((pid = fork()) < 0)
		return (ft_fdprintf(2, E_ERR, "Cannot fork"), false);
	if (pid == 0)
	{
		close(fds[0]);
		dup2(fds[1], 1);
		dup2(fds[1], 2);
		exec_cmd(env);
		close(fds[1]);
		_exit(0);
	}
	close(fds[1]);
	script_read(env, fds[0]);
	waitpid(pid, NULL, 0);
	return (true);
}
