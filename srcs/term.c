/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/28 14:13:29 by jaguillo          #+#    #+#             */
/*   Updated: 2015/06/01 14:21:51 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_script.h"
#include <termios.h>

t_bool			init_term(t_env *env)
{
	struct termios	tmp;

	if (ft_tcgetattr(0, &tmp) < 0)
		return (false);
	env->save_term = tmp;
	tmp.c_iflag &= ~(
		IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL | IXON);
	tmp.c_oflag &= ~(OPOST);
	tmp.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
	tmp.c_cflag &= ~(CSIZE | PARENB);
	tmp.c_cflag |= CS8;
	tmp.c_cc[VMIN] = 1;
	tmp.c_cc[VTIME] = 0;
	if (ft_tcsetattr(0, &tmp))
		return (false);
	return (true);
}

void			restore_term(t_env *env)
{
	ft_tcsetattr(0, &(env->save_term));
}
