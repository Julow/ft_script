/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   script.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juloo <juloo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/26 16:28:38 by juloo             #+#    #+#             */
/*   Updated: 2015/05/29 11:44:50 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_script.h"
#include "msg.h"
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>

// ctime

static void		print_start(t_env *env)
{
	struct timeval	tp;

	gettimeofday(&tp, NULL);
	ft_printf(M_START, env->out_file);
	ft_writef(&(env->out), M_START_F, ctime(&(tp.tv_sec)));
	ft_flush(&(env->out));
}

static void		print_done(t_env *env)
{
	struct timeval	tp;

	gettimeofday(&tp, NULL);
	ft_printf(M_DONE, env->out_file);
	ft_writef(&(env->out), M_DONE_F, ctime(&(tp.tv_sec)));
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
		script_slave(env, slave);
		_exit(0);
	}
	close(slave);
	print_start(env);
	script_master(env, master);
	restore_term(env);
	print_done(env);
	return (true);
}
