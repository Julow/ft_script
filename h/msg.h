/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juloo <juloo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/26 13:31:24 by juloo             #+#    #+#             */
/*   Updated: 2015/06/01 14:21:28 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSG_H
# define MSG_H

# define NAME			"ft_script"
# define ENDL			"\n"

# define E_OPT			NAME ": invalid option -- '%s'" ENDL

# define MSG			NAME ": %s" ENDL
# define ERR			NAME ": %s: %s" ENDL
# define E_ERR			NAME ": Error: %s" ENDL

# define M_RIGHT		"Permission denied"
# define M_ISDIR		"Is a directory"
# define M_LOOP			"Too many symbolic links"
# define M_PATH			"Bad path"

# define M_START		NAME " started, output file is %s" ENDL "\r"
# define M_START_F		NAME " started on %s"

# define M_DONE			ENDL NAME " done, output file is %s" ENDL
# define M_DONE_F		ENDL NAME " done on %s"

#endif
