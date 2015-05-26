/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_script.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/03 13:06:59 by jaguillo          #+#    #+#             */
/*   Updated: 2015/05/26 14:56:20 by juloo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SCRIPT_H
# define FT_SCRIPT_H

# include "libft.h"

/*
** ========================================================================== **
** ft_script
** ----
** ft_script [options] [file [command ...]]
** ----
** Options:
**  -a, --append   append the output
**  -q, --quiet    quiet mode
**  -h, --help     display help
** ----
*/

# define OUTPUT_BUFFER	1024

# define DEFAULT_SHELL	"/bin/sh"
# define DEFAULT_FILE	"typescript"

# define WRITE_O		(O_WRONLY | O_CREAT | O_TRUNC)
# define APPEND_O		(O_WRONLY | O_CREAT | O_APPEND)
# define MODE_O			(S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH)

typedef struct	s_env
{
	int				flags;
	char			*out_file;
	char			**cmd;
	t_out			out;
}				t_env;

# define FLAG_A		(1 << 1)
# define FLAG_Q		(1 << 2)

t_bool			parse_argv(t_env *env, int argc, char **argv);

#endif
