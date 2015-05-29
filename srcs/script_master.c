/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   script_master.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/29 11:22:30 by jaguillo          #+#    #+#             */
/*   Updated: 2015/05/29 11:47:44 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_script.h"
#include "msg.h"
#include <unistd.h>
#include <sys/select.h>

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

void			script_master(t_env *env, int master)
{
	read_script(env, master);
}
