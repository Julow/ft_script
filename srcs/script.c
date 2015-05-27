/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   script.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juloo <juloo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/26 16:28:38 by juloo             #+#    #+#             */
/*   Updated: 2015/05/28 00:15:06 by juloo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_script.h"
#include "msg.h"
#include <unistd.h>
#include <sys/wait.h>
#include <sys/select.h>

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

static void		script_read(t_env *env, int fd_r, int fd_w)
{
	fd_set			read_fds;
	int				len;
	char			buff[INPUT_BUFFER];

	while (true)
	{
		FD_ZERO(&read_fds);
		FD_SET(fd_r, &read_fds);
		FD_SET(0, &read_fds);
		if (select(fd_r + 1, &read_fds, NULL, NULL, NULL) <= 0)
			continue ;
		if (FD_ISSET(0, &read_fds))
		{
			len = read(0, buff, INPUT_BUFFER);
			write(fd_w, buff, len);
			ft_write(&(env->out), buff, len);
			ft_flush(&(env->out));
		}
		if (FD_ISSET(fd_r, &read_fds))
		{
			len = read(fd_r, buff, INPUT_BUFFER);
			write(1, buff, len);
			ft_write(&(env->out), buff, len);
			ft_flush(&(env->out));
		}
	}
}

t_bool			start_script(t_env *env)
{
	pid_t			pid;
	int				pipe_in[2];
	int				pipe_out[2];

	if (pipe(pipe_out) < 0 || pipe(pipe_in) < 0)
		return (ft_fdprintf(2, E_ERR, "Cannot pipe"), false);
	if ((pid = fork()) < 0)
		return (ft_fdprintf(2, E_ERR, "Cannot fork"), false);
	if (pid == 0)
	{
		close(pipe_out[PIPE_R]);
		close(pipe_in[PIPE_W]);
		dup2(pipe_in[PIPE_R], 0);
		dup2(pipe_out[PIPE_W], 1);
		dup2(pipe_out[PIPE_W], 2);
		exec_cmd(env);
		_exit(0);
	}
	close(pipe_out[PIPE_W]);
	close(pipe_in[PIPE_R]);
	script_read(env, pipe_out[PIPE_R], pipe_in[PIPE_W]);
	waitpid(pid, NULL, 0);
	return (true);
}
