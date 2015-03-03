/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/03 13:20:11 by jaguillo          #+#    #+#             */
/*   Updated: 2015/03/03 15:29:40 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_script.h"
#include <unistd.h>

void			exec_shell(char *shell)
{
	char			*argv[2];

	argv[0] = shell;
	argv[1] = NULL;
	execve(shell, argv, NULL);
	_exit(0);
}
