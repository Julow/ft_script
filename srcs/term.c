/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/28 14:13:29 by jaguillo          #+#    #+#             */
/*   Updated: 2015/05/28 14:22:38 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_script.h"
#include <termios.h>
#include <sys/ioctl.h>

// tcgetattr
// cfmakeraw
// tcsetattr

t_bool			init_term(t_env *env, int tty)
{
	struct termios	tmp;

	tcgetattr(tty, &tmp);
	env->save_term = tmp;
	cfmakeraw(&tmp);
	tcsetattr(tty, TCSANOW, &tmp);
	return (true);
}

void			restore_term(t_env *env, int tty)
{
	tcsetattr(tty, TCSANOW, &(env->save_term));
}
