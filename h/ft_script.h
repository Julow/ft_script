/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_script.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/03 13:06:59 by jaguillo          #+#    #+#             */
/*   Updated: 2015/03/03 16:22:56 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SCRIPT_H
# define FT_SCRIPT_H

# include "libft.h"

# define SCRIPT_BUFF	512

# define DEFAULT_SHELL	"/bin/sh"

/*
** script
*/
void			start_script(void);

/*
** exec
*/
void			exec_shell(char *shell);

/*
** utils
*/
char			*ft_getenv(const char *key);

#endif
