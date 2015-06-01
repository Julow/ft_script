/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_openpt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/28 13:40:10 by jaguillo          #+#    #+#             */
/*   Updated: 2015/06/01 17:45:26 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_script.h"
#include "msg.h"
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <stdlib.h>

/*
** Portable version
** ========================================================================== **
** t_bool			ft_openpt(int *master, int *slave)
** {
** 	int				master_fd;
** 	struct winsize	win;
** 	*master = -1;
** 	*slave = -1;
** 	if (ioctl(0, TIOCGWINSZ, &win) < 0)
** 		return (false);
** 	if ((master_fd = posix_openpt(O_RDWR)) < 0)
** 		return (ft_fdprintf(2, E_ERR, "Cannot open master tty"), false);
** 	if (grantpt(master_fd) < 0)
** 		return (ft_fdprintf(2, E_ERR, "Cannot grant tty"), false);
** 	if (unlockpt(master_fd) < 0)
** 		return (ft_fdprintf(2, E_ERR, "Cannot unlock tty"), false);
** 	if ((*slave = open(ptsname(master_fd), O_RDWR)) < 0)
** 		return (ft_fdprintf(2, E_ERR, "Cannot open slave tty"), false);
** 	if (ioctl(master_fd, TIOCSWINSZ, &win) < 0)
** 		return (false);
** 	*master = master_fd;
** 	return (true);
** }
** ========================================================================== **
*/

static int		test_pty(char const *prefix, char c, int n)
{
	const int		prefix_len = ft_strlen(prefix);
	char			name[5 + prefix_len + 3];

	ft_memcpy(name, "/dev/", 5);
	ft_memcpy(name + 5, prefix, prefix_len);
	name[5 + prefix_len] = c;
	name[5 + prefix_len + 1] = BASE_16_LOWER[n];
	name[5 + prefix_len + 2] = '\0';
	return (open(name, O_RDWR));
}

t_bool			ft_openpt(int *master, int *slave)
{
	char			c;
	char			n;
	struct winsize	win;

	if (ioctl(0, TIOCGWINSZ, &win) < 0)
		return (false);
	c = 'p';
	while (c <= 'w')
	{
		n = -1;
		while (++n < 16)
			if ((*master = test_pty("pty", c, n)) >= 0)
			{
				if ((*slave = test_pty("tty", c, n)) >= 0)
				{
					if (ioctl(*master, TIOCSWINSZ, &win) < 0)
						return (close(*master), close(*slave), false);
					return (true);
				}
				close(*master);
			}
		c++;
	}
	return (false);
}
