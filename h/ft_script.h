/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_script.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/03 13:06:59 by jaguillo          #+#    #+#             */
/*   Updated: 2015/06/02 17:19:12 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SCRIPT_H
# define FT_SCRIPT_H

# include "libft.h"
# include "ft_argv.h"

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

# define FLUSH_INTERVAL	30

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
	int				flush_interval;
	int				next_flush;
	struct termios	save_term;
}				t_env;

# define FLAG_A		(1 << 1)
# define FLAG_Q		(1 << 2)
# define FLAG_K		(1 << 3)

t_bool			parse_argv(t_env *env, int argc, char **argv);
t_bool			parse_opt_time(t_env *env, t_args *args, char *opt, char *arg);
t_bool			parse_opt(t_env *env, t_args *args, char *opt);

t_bool			init_term(t_env *env);
void			restore_term(t_env *env);

t_bool			start_script(t_env *env);
void			script_slave(t_env *env, int slave);
void			script_master(t_env *env, int master);

t_bool			ft_openpt(int *master, int *slave);

int				ft_tcsetattr(int fd, struct termios *t);
int				ft_tcgetattr(int fd, struct termios *t);
char const		*ft_strerror(int err);

int				ft_exec(char **argv, char **env);
t_bool			ft_subnextc(t_sub *sub, char c);

/*
** ========================================================================== **
** ft_argv
** ----
** Iter over options using ft_argvopt
** Take an array of t_opt:
**  t_opt.opt     Opt name (first arg of t_opt.f)
**  t_opt.alias   Opt name (compared with result of ft_argvopt)
**  t_opt.arg     If require a argument
**  t_opt.f       Callback(opt name, argument if t_opt.arg else NULL)
** ----
** t_bool			callback(void *data, t_args *args, char *opt, char *arg);
**  If the callback function return false, ft_argv stop
** ----
** Warning: An empty opt name cause an undefined behavior
** TODO: Add const to t_opt.opt and callback arguments
** ----
** Return false if an option fail or does not exists
** true otherwise
*/

typedef struct	s_opt
{
	char			*opt;
	char const		*alias;
	t_bool			arg;
	t_bool			(*f)();
}				t_opt;

t_bool			ft_argv(t_args *args, t_opt const *opts, int len, void *data);

/*
** Error messages
**  E_ARGV_NO      Option does not exists
**  E_ARGV_ARG     t_opt.arg is true and there is no argment
*/
# define E_ARGV_NO		"%s: -%s: unknown option\n"
# define E_ARGV_ARG		"%s: -%s: need an argument\n"

#endif
