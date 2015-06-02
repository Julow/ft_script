/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   script_slave.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/29 11:22:30 by jaguillo          #+#    #+#             */
/*   Updated: 2015/06/02 13:33:51 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_script.h"
#include "msg.h"
#include <unistd.h>
#include <sys/ioctl.h>

static void		exec_cmd(t_env *env)
{
	char			*def_cmd[3];

	def_cmd[0] = NULL;
	def_cmd[1] = "-i";
	def_cmd[2] = NULL;
	if (env->cmd == NULL || env->cmd[0] == NULL)
	{
		def_cmd[0] = ft_getenv("SHELL", NULL);
		if (def_cmd[0] == NULL)
			def_cmd[0] = DEFAULT_SHELL;
		ft_fdprintf(2, ERR, def_cmd[0], ft_strerror(ft_exec(def_cmd, NULL)));
	}
	else
		ft_fdprintf(2, ERR, env->cmd[0], ft_strerror(ft_exec(env->cmd, NULL)));
}

void			script_slave(t_env *env, int slave)
{
	dup2(slave, 0);
	dup2(slave, 1);
	dup2(slave, 2);
	close(slave);
	setsid();
	ioctl(0, TIOCSCTTY, 1);
	exec_cmd(env);
}
