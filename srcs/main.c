/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/03 13:07:18 by jaguillo          #+#    #+#             */
/*   Updated: 2015/03/03 17:14:01 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_script.h"
#include <unistd.h>

static char		*get_shell(void)
{
	char			*tmp;

	tmp = ft_getenv("SHELL");
	if (tmp == NULL)
		return (DEFAULT_SHELL);
	return (tmp);
}

int				main(int argc, char **argv)
{
	pid_t			pid;

	ft_putstr("Start script\n");
	pid = fork();
	if (pid == 0)
		exec_shell(get_shell());
	else
		start_script();
	ft_putstr("End script\n");
	(void)argc;
	(void)argv;
	return (0);
}
