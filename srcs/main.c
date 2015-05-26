/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/03 13:07:18 by jaguillo          #+#    #+#             */
/*   Updated: 2015/05/26 15:02:02 by juloo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_script.h"
#include "ft_argv.h"
#include "msg.h"
#include <fcntl.h>
#include <errno.h>

static t_bool	init_file(t_env *env)
{
	if ((env->out.fd = open(env->out_file,
		(env->flags & FLAG_A) ? APPEND_O : WRITE_O, MODE_O)) >= 0)
		return (true);
	if (errno == EISDIR)
		ft_fdprintf(2, E_FILE, env->out_file, M_ISDIR);
	else if (errno == ELOOP)
		ft_fdprintf(2, E_FILE, env->out_file, M_LOOP);
	else if (errno == ENOTDIR)
		ft_fdprintf(2, E_FILE, env->out_file, M_PATH);
	else
		ft_fdprintf(2, E_FILE, env->out_file, M_RIGHT);
	return (false);
}

int				main(int argc, char **argv)
{
	t_env			env;
	char			out_buff[OUTPUT_BUFFER];

	env = (t_env){0, DEFAULT_FILE, NULL, OUT(0, out_buff, OUTPUT_BUFFER)};
	if (!parse_argv(&env, argc, argv))
		return (1);
	if (!init_file(&env))
		return (1);
	return (0);
}
