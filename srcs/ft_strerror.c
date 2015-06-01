/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strerror.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/01 14:05:25 by jaguillo          #+#    #+#             */
/*   Updated: 2015/06/01 14:10:15 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_script.h"
#include <stdio.h>

char const		*ft_strerror(int err)
{
	if (err < 0 || err > sys_nerr)
		return (NULL);
	return (sys_errlist[err]);
}
