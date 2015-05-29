/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   script_slave.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/29 11:22:30 by jaguillo          #+#    #+#             */
/*   Updated: 2015/05/29 11:26:01 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_script.h"
#include "msg.h"
#include <unistd.h>
#include <sys/ioctl.h>

#include <string.h> // OMG

// strerror

static void		exec_cmd(t_env *env)
{
	char 			*def_cmd[] = {NULL, "-i", NULL};

	if (env->cmd == NULL || env->cmd[0] == NULL)
	{
		def_cmd[0] = ft_getenv("SHELL");
		if (def_cmd[0] == NULL)
			def_cmd[0] = DEFAULT_SHELL;
		ft_fdprintf(2, ERR, def_cmd[0], strerror(ft_exec(def_cmd, NULL)));
	}
	else
		ft_fdprintf(2, ERR, env->cmd[0], strerror(ft_exec(env->cmd, NULL)));
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
