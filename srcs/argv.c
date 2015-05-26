/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juloo <juloo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/26 13:23:52 by juloo             #+#    #+#             */
/*   Updated: 2015/05/26 15:02:25 by juloo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_script.h"
#include "ft_argv.h"
#include "msg.h"
#include <unistd.h>

static void		usage(void)
{
	ft_fdprintf(2, "\n"
		"Usage:\n"
		" ft_script [options] [file [command ...]]\n"
		"\n"
		"Options:\n"
		" -a, --append   append the output\n"
		" -q, --quiet    quiet mode\n"
		" -h, --help     display this message and exit\n"
		"\n");
}

static t_bool	parse_opt(t_env *env, t_args *args)
{
	char			*opt;

	while ((opt = ft_argvopt(args)) != NULL)
		if (ft_strequ(opt, "a") || ft_strequ(opt, "append"))
			env->flags |= FLAG_A;
		else if (ft_strequ(opt, "q") || ft_strequ(opt, "quiet"))
			env->flags |= FLAG_Q;
		else if (ft_strequ(opt, "h") || ft_strequ(opt, "help"))
		{
			usage();
			_exit(0);
		}
		else
			return (ft_fdprintf(2, E_OPT, opt), false);
	return (true);
}

t_bool			parse_argv(t_env *env, int argc, char **argv)
{
	t_args			args;
	char			*arg;

	args = ARGS(argc, argv);
	if (!parse_opt(env, &args))
		return (usage(), false);
	if ((arg = ft_argvarg(&args)) != NULL)
		env->out_file = arg;
	env->cmd = args.argv + args.c;
	return (true);
}
