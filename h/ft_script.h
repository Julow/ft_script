/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_script.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/03 13:06:59 by jaguillo          #+#    #+#             */
/*   Updated: 2015/05/27 12:31:05 by juloo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SCRIPT_H
# define FT_SCRIPT_H

# include "libft.h"
# include <termios.h>

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
# define INPUT_BUFFER	256

# define DEFAULT_SHELL	"/bin/sh"
# define DEFAULT_FILE	"typescript"

# define TERM_FD		0

# define READ_O			(O_RDONLY)
# define WRITE_O		(O_WRONLY | O_CREAT | O_TRUNC)
# define APPEND_O		(O_WRONLY | O_CREAT | O_APPEND)
# define MODE_O			(S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH)

# define PIPE_W			1
# define PIPE_R			0

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

t_bool			start_script(t_env *env);

#endif
