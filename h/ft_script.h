/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_script.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/03 13:06:59 by jaguillo          #+#    #+#             */
/*   Updated: 2015/03/05 17:23:22 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SCRIPT_H
# define FT_SCRIPT_H

# include "libft.h"

# define SCRIPT_BUFF	512

# define DEFAULT_SHELL	"/bin/sh"

# define PIPE_OUT		0
# define PIPE_IN		1

typedef struct	s_env
{
	int				pipe_0[2];
	int				pipe_1[2];
	int				pipe_2[2];
}				t_env;

/*
** script
*/
void			start_script(t_env *env);

/*
** exec
*/
void			exec_shell(t_env *env, char *shell);

/*
** utils
*/
char			*ft_getenv(const char *key);

#endif
