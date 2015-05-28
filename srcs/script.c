/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   script.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juloo <juloo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/26 16:28:38 by juloo             #+#    #+#             */
/*   Updated: 2015/05/28 18:06:26 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_script.h"
#include "msg.h"
#include <unistd.h>
#include <sys/wait.h>
#include <sys/select.h>
#include <sys/ioctl.h>

static void		exec_cmd(t_env *env)
{
	char 			*def_cmd[] = {NULL, "-i", NULL};
	extern char		**environ;

	if (env->cmd == NULL || env->cmd[0] == NULL)
	{
		def_cmd[0] = ft_getenv("SHELL");
		if (def_cmd[0] == NULL)
			def_cmd[0] = DEFAULT_SHELL;
		execve(def_cmd[0], def_cmd, environ);
		ft_fdprintf(2, ERR, def_cmd[0], "Cannot exec");
	}
	else
	{
		execve(env->cmd[0], env->cmd, environ);
		ft_fdprintf(2, ERR, env->cmd[0], "Cannot exec");
	}
}

static void		read_script(t_env *env, int master)
{
	fd_set			read_fds;
	int				len;
	char			buff[INPUT_BUFFER];

	while (true)
	{
		FD_ZERO(&read_fds);
		FD_SET(0, &read_fds);
		FD_SET(master, &read_fds);
		if (select(master + 1, &read_fds, NULL, NULL, NULL) < 0)
			return (ft_fdprintf(2, E_ERR, "Cannot select"), VOID);
		if (FD_ISSET(0, &read_fds))
		{
			if ((len = read(0, buff, INPUT_BUFFER)) <= 0)
				break ;
			write(master, buff, len);
			ft_write(&(env->out), buff, len);
		}
		if (FD_ISSET(master, &read_fds))
		{
			if ((len = read(master, buff, INPUT_BUFFER)) <= 0)
				break ;
			write(1, buff, len);
			ft_write(&(env->out), buff, len);
		}
	}
	ft_flush(&(env->out));
}

t_bool			start_script(t_env *env)
{
	int				master;
	int				slave;
	pid_t			pid;

	if (!ft_openpt(&master, &slave) || !init_term(env))
		return (false);
	if ((pid = fork()) < 0)
		return (ft_fdprintf(2, E_ERR, "Cannot fork"), false);
	if (pid == 0)
	{
		close(master);
		dup2(slave, 0);
		dup2(slave, 1);
		dup2(slave, 2);
		close(slave);
		setsid();
		ioctl(0, TIOCSCTTY, 1);
		exec_cmd(env);
		_exit(0);
	}
	close(slave);
	read_script(env, master);
	restore_term(env);
	return (true);
}
