/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juloo <juloo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/26 13:23:52 by juloo             #+#    #+#             */
/*   Updated: 2015/06/02 17:18:37 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_script.h"
#include "ft_argv.h"
#include "msg.h"
#include <unistd.h>

const t_opt		g_opts[] = {
	{"a", "append", false, &parse_opt},
	{"q", "quiet", false, &parse_opt},
	{"h", "help", false, &parse_opt},
	{"k", "key", false, &parse_opt},
	{"t", "time", true, &parse_opt_time}
};

static void		usage(void)
{
	ft_fdprintf(2, "\n"
		"Usage:\n"
		" ft_script [options] [file [command ...]]\n"
		"\n"
		"Options:\n"
		" -a, --append    append the output\n"
		" -q, --quiet     quiet mode\n"
		" -t <time>,\n"
		" --time=<time>   set flush interval (default 30)\n"
		" -k, --key       log keys\n"
		" -h, --help      display this message and exit\n"
		"\n");
}

t_bool			parse_opt_time(t_env *env, t_args *args, char *opt, char *arg)
{
	if (!ft_sisint(arg) || (env->flush_interval = ft_atoi(arg)) < 0)
		return (ft_fdprintf(2, E_ERR, "Invalid time argument"), false);
	return (true);
	(void)opt;
	(void)args;
}

t_bool			parse_opt(t_env *env, t_args *args, char *opt)
{
	if (*opt == 'a')
		env->flags |= FLAG_A;
	else if (*opt == 'q')
		env->flags |= FLAG_Q;
	else if (*opt == 'k')
		env->flags |= FLAG_K;
	else if (*opt == 'h')
	{
		usage();
		_exit(0);
	}
	return (true);
	(void)args;
}

t_bool			parse_argv(t_env *env, int argc, char **argv)
{
	t_args			args;
	char			*arg;

	args = ARGS(argc, argv);
	if (!ft_argv(&args, g_opts, sizeof(g_opts) / sizeof(t_opt), env))
		return (usage(), false);
	if ((arg = ft_argvarg(&args)) != NULL)
		env->out_file = arg;
	env->cmd = args.argv + args.c;
	return (true);
}
