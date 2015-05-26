/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juloo <juloo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/26 15:09:01 by juloo             #+#    #+#             */
/*   Updated: 2015/05/26 17:25:37 by juloo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_script.h"
#include "msg.h"
#include <unistd.h>
#include <fcntl.h>

t_bool			init_term(t_env *env)
{
	struct termios	term;

	if (!isatty(TERM_FD) || (env->in_fd = open(ttyname(TERM_FD), READ_O)) < 0)
		return (ft_fdprintf(2, MSG, "Is not a terminal"), false);
	if (tcgetattr(TERM_FD, &term) < 0)
		return (ft_fdprintf(2, E_ERR, "Cannot get termios"), false);
	ft_memcpy(&(env->term_save), &term, sizeof(struct termios));
	term.c_lflag &= ~(ECHO);
	if (tcsetattr(TERM_FD, TCSADRAIN, &term) < 0)
		return (ft_fdprintf(2, E_ERR, "Cannot set termios"), false);
	return (true);
}

void			restore_term(t_env *env)
{
	tcsetattr(TERM_FD, TCSADRAIN, &(env->term_save));
}
