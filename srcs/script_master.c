/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   script_master.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/29 11:22:30 by jaguillo          #+#    #+#             */
/*   Updated: 2015/06/02 17:20:09 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_script.h"
#include "msg.h"
#include <unistd.h>
#include <sys/time.h>
#include <sys/select.h>

static void		flush_script(t_env *env)
{
	struct timeval	tp;

	gettimeofday(&tp, NULL);
	if (tp.tv_sec >= env->next_flush)
	{
		env->next_flush = env->flush_interval + tp.tv_sec;
		ft_flush(&(env->out));
		fsync(env->out.fd);
	}
}

static t_bool	read_script(t_env *env, int master)
{
	fd_set			read_fds;
	int				len;
	char			buff[INPUT_BUFFER];

	FD_ZERO(&read_fds);
	FD_SET(0, &read_fds);
	FD_SET(master, &read_fds);
	if (select(master + 1, &read_fds, NULL, NULL, &(struct timeval){0, 0}) < 0)
		return (ft_fdprintf(2, E_ERR, "Cannot select"), false);
	if (FD_ISSET(0, &read_fds))
	{
		if ((len = read(0, buff, INPUT_BUFFER)) <= 0)
			return (false);
		if (env->flags & FLAG_K)
			ft_write(&(env->out), buff, len);
		write(master, buff, len);
	}
	if (FD_ISSET(master, &read_fds))
	{
		if ((len = read(master, buff, INPUT_BUFFER)) <= 0)
			return (false);
		write(1, buff, len);
		ft_write(&(env->out), buff, len);
	}
	return (true);
}

void			script_master(t_env *env, int master)
{
	while (read_script(env, master))
		flush_script(env);
	ft_flush(&(env->out));
}
