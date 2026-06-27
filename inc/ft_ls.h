/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 18:05:24 by pipolint          #+#    #+#             */
/*   Updated: 2026/06/27 14:25:19 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# define OPTIONS "lRart"
# define OPTION_COUNT 5

# include <dirent.h>
# include <errno.h>
# include <grp.h>
# include "libft.h"
# include "parser.h"
# include <pwd.h>
# include "queue.h"
# include <stdio.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/ioctl.h>
# include <time.h>
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
	size_t		columns_written;
	char		options[OPTION_COUNT + 1];
	bool		reverse;
	bool		time;
	bool		all;
	bool		recursive;
	bool		list;
	bool		no_args;
	bool		multiple_columns;
	int			directory_count;
	int			exit_code;
	int			error_code;
	size_t		trav_i;
}   t_ls;

void		check_group_owner(struct stat *st, t_dir_ptr *current_dir);
void    	mergesort_string(char **array, int start, int end);
void    	merge_dirent(char **entries, int start, int end, bool time_sort, t_dir_ptr *dir);
void    	merge_directories(t_dir_ptr **dir_ptrs, int start, int end);
char		*build_path(t_ls *ls, const char *directory, char *entry);
bool		multiple_col_print(t_ls *ls, t_vector *entries, struct winsize *w);

/*************************/
/*			Files		 */ 
/*************************/
void		add_dirent_entries(t_ls *ls, t_vector *dirent_entries, t_dir_ptr* current_dir);
void		traverse_entries(t_ls *ls, t_dir_ptr *dir, t_vector *entries, t_vector **directories);

/*************************/
/*		Directories		 */ 
/*************************/
t_dir_ptr	*create_tdirptr(char *directory_name, DIR *dir_ptr);
void		add_directory(char *path, t_vector *directory_vector);
void		add_arg_directories(t_ls *ls, t_vector **directory_vector);
void 		open_directories(t_ls *ls, t_vector **directories_ptrs);

/*************************/
/*			List		 */ 
/*************************/
void		check_longest(t_ls *ls, t_dir_ptr *current_dir, struct dirent *entry);
void		print_list(struct stat *st, t_dir_ptr *ptr);

bool		looper(t_ls *ls, size_t max);
void    	set_index(t_ls *ls, size_t max);
void		initialize_ls(t_ls *ls);

#endif
