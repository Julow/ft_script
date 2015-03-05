/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_script.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/03 14:22:38 by jaguillo          #+#    #+#             */
/*   Updated: 2015/03/05 17:23:19 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_script.h"
#include <unistd.h>

void			start_script(t_env *env)
{
	pid_t			pid;

	pid = fork();
	if (pid == 0)
	{
	}
}
