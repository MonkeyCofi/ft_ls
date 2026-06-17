/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 18:05:24 by pipolint          #+#    #+#             */
/*   Updated: 2026/06/17 20:11:39 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# define OPTIONS "lRart"
# define OPTION_COUNT 5

# include <dirent.h>
# include <errno.h>
# include <stdio.h>
# include "parser.h"
# include "queue.h"
# include "vector.h"

typedef enum s_options
{
    NONE = 0,
	LONG,
	RECURSIVE,
	ALL,
	REVERSE,
	TIME,
}	t_options;

typedef struct s_ls
{
	t_queue		*directory_queue;	// queue of all directory strings
	t_vector	*directories;		// array of directory strings
	t_vector	*dir_entries;		// array of directory entries
	size_t		option_count;
	char		options[OPTION_COUNT + 1];
	int			directory_count;
	int			exit_code;
	int			error_code;
}   t_ls;

void    mergesort_string(char **array, int start, int end);
void    merge_dirent(struct dirent **entries, int start, int end);

#endif
