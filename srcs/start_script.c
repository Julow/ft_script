/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_script.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/03 14:22:38 by jaguillo          #+#    #+#             */
/*   Updated: 2015/03/03 15:30:08 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_script.h"
#include <unistd.h>
#include <sys/select.h>

static void		process_fd(char *buff, int fd)
{
	int				len;

	len = read(fd, buff, SCRIPT_BUFF);
	if (len < 0)
		return ;
	write(fd, buff, SCRIPT_BUFF);
	write(3, buff, SCRIPT_BUFF);
}

void			start_script(void)
{
	char		buff[SCRIPT_BUFF];
	fd_set		fdset;

	while (true)
	{
		FD_ZERO(&fdset);
		FD_SET(1, &fdset);
		FD_SET(2, &fdset);
		if (select(3, &fdset, NULL, NULL, NULL) <= 0)
			break ;
		if (FD_ISSET(1, &fdset))
			process_fd(buff, 1);
		if (FD_ISSET(2, &fdset))
			process_fd(buff, 2);
	}
}
