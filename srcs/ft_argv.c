/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_argv.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/02 14:20:50 by jaguillo          #+#    #+#             */
/*   Updated: 2015/06/02 16:36:42 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_script.h"

static void		argv_error(t_args *args, char *opt, char const *msg)
{
	if (opt[1] != '\0')
		ft_fdprintf(2, msg, args->argv[0], opt - 1);
	else
		ft_fdprintf(2, msg, args->argv[0], opt);
}

t_bool			ft_argv(t_args *args, t_opt const *opts, int len, void *data)
{
	char			*name;
	char			*value;
	int				i;

	while ((name = ft_argvopt(args)) != NULL)
	{
		i = -1;
		while (++i < len)
		{
			if ((opts[i].alias != NULL && ft_strequ(name, opts[i].alias))
				|| ft_strequ(name, opts[i].opt))
			{
				value = NULL;
				if (opts[i].arg && (value = ft_argvarg(args)) == NULL)
					return (argv_error(args, name, E_ARGV_ARG), false);
				if (!opts[i].f(data, args, opts[i].opt, value))
					return (false);
				break ;
			}
		}
		if (i >= len)
			return (argv_error(args, name, E_ARGV_NO), false);
	}
	return (true);
}
