/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 18:05:24 by pipolint          #+#    #+#             */
/*   Updated: 2026/06/22 13:47:12 by pipolint         ###   ########.fr       */
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
	char		options[OPTION_COUNT + 1];
	int			directory_count;
	int			exit_code;
	int			error_code;
}   t_ls;

typedef struct s_dir_ptr
{
	char	*directory_name;
	size_t	longest_filename;
	size_t	longest_filesize;
	size_t	longest_hlsize;
	size_t	longest_owner;
	size_t	longest_group;
	DIR		*directory;
}	t_dir_ptr;

void	check_group_owner(struct stat *st, t_dir_ptr *current_dir);
void    mergesort_string(char **array, int start, int end);
void    merge_dirent(struct dirent **entries, int start, int end);
void    merge_directories(t_dir_ptr **dir_ptrs, int start, int end);
char	*build_path(t_ls *ls, const char *directory, struct dirent *entry);

/*************************/
/*		Directories		 */ 
/*************************/
t_dir_ptr	*create_tdirptr(char *directory_name, DIR *dir_ptr);
void	add_directory(char *path, t_vector *directory_vector);
void	add_arg_directories(t_ls *ls, t_vector *directory_vector);

/*************************/
/*			List		 */ 
/*************************/
void	check_longest(t_ls *ls, t_dir_ptr *current_dir, struct dirent *entry);
void	print_list(struct stat *st, t_dir_ptr *ptr);


#endif
