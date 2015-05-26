/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juloo <juloo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/26 13:31:24 by juloo             #+#    #+#             */
/*   Updated: 2015/05/26 16:30:44 by juloo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_H
# define MSH_H

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

#endif
