/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/28 14:13:29 by jaguillo          #+#    #+#             */
/*   Updated: 2015/05/28 18:03:30 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_script.h"
#include <termios.h>
#include <sys/ioctl.h>

// tcgetattr
// tcsetattr

t_bool			init_term(t_env *env)
{
	struct termios	tmp;

	if (tcgetattr(0, &tmp) < 0)
		return (false);
	env->save_term = tmp;
	tmp.c_lflag &= ~(ECHO | ICANON);
	tmp.c_cc[VMIN] = 1;
	tmp.c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSADRAIN, &tmp))
		return (false);
	return (true);
}

void			restore_term(t_env *env)
{
	tcsetattr(0, TCSADRAIN, &(env->save_term));
}
