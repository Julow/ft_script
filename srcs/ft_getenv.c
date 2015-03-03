/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/03 13:13:11 by jaguillo          #+#    #+#             */
/*   Updated: 2015/03/03 18:55:48 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_script.h"

static char		*key_equ(char *env, const char *key)
{
	int				i;

	i = 0;
	while (env[i] != '\0' && env[i] == key[i])
		i++;
	if (key[i] == '\0' && env[i] == '=')
		return (env + i + 1);
	return (NULL);
}

char			*ft_getenv(const char *key)
{
	extern char		**environ;
	char			*tmp;
	int				i;

	i = -1;
	while (environ[++i] != NULL)
	{
		tmp = key_equ(environ[i], key);
		if (tmp != NULL)
			return (tmp);
	}
	return (NULL);
}
