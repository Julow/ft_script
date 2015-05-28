/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_openpt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/28 13:40:10 by jaguillo          #+#    #+#             */
/*   Updated: 2015/05/28 17:52:18 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_script.h"
#include "msg.h"
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <stdlib.h> // OMG

// posix_openpt
// grantpt
// unlockpt

t_bool			ft_openpt(int *master, int *slave)
{
	int				master_fd;
	struct winsize	win;

	*master = -1;
	*slave = -1;
	if (ioctl(0, TIOCGWINSZ, &win) < 0)
		return (false);
	if ((master_fd = posix_openpt(O_RDWR)) < 0)
		return (ft_fdprintf(2, E_ERR, "Cannot open master tty"), false);
	if (grantpt(master_fd) < 0)
		return (ft_fdprintf(2, E_ERR, "Cannot grant tty"), false);
	if (unlockpt(master_fd) < 0)
		return (ft_fdprintf(2, E_ERR, "Cannot unlock tty"), false);
	if ((*slave = open(ptsname(master_fd), O_RDWR)) < 0)
		return (ft_fdprintf(2, E_ERR, "Cannot open slave tty"), false);
	if (ioctl(master_fd, TIOCSWINSZ, &win) < 0)
		return (false);
	*master = master_fd;
	return (true);
}
