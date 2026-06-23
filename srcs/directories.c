/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directories.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 13:45:53 by pipolint          #+#    #+#             */
/*   Updated: 2026/06/23 14:34:29 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_dir_ptr	*create_tdirptr(char *directory_name, DIR *dir_ptr)
{
	t_dir_ptr	*ptr;

	ptr = malloc(sizeof(t_dir_ptr));
	if (!ptr)
		return (NULL);
	ptr->directory_name = directory_name;
	ptr->directory = dir_ptr;
	ptr->longest_filename = 0;
	ptr->longest_filesize = 0;
	ptr->longest_hlsize = 0;
	ptr->longest_group = 0;
	ptr->longest_owner = 0;
	return (ptr);
}

void	add_directory(char *path, t_vector *directory_vector)
{
	struct stat	st;
	DIR			*open_dir;
	t_dir_ptr	*dir_ptr;

	if (lstat(path, &st) == 0)
	{
		if (S_ISDIR(st.st_mode))
		{
			open_dir = opendir(path);
			if (!open_dir)
			{
				perror("opendir");
				return ;
			}
			dir_ptr = create_tdirptr(path, open_dir);
			add_to_vector(directory_vector, dir_ptr, POINTER);
		}
	}
}

void	add_arg_directories(t_ls *ls, t_vector *directory_vector)
{
	char		*current_path;
	DIR			*ptr;
	t_dir_ptr	*dir_ptr;
	struct stat	st;
	size_t		i;

	current_path = NULL;
	i = -1;
	while (++i < ls->directories->size)
	{
		current_path = (char *)get_element(ls->directories, i);
		lstat(current_path, &st);
		if (S_ISDIR(st.st_mode))
		{
			ptr = opendir(current_path);
			dir_ptr = create_tdirptr(current_path, ptr);
			add_to_vector(directory_vector, dir_ptr, POINTER);
		}
		else
			printf("failed %s\n", get_element(ls->directories, i));
	}
}

/**
 * @param ls The ls struct
 * @param pointers Vector cointaing DIR *
 */
void open_directories(t_ls *ls, t_vector *directories_ptrs)
{
	t_vector		*rec_directories;
	t_dir_ptr		*ptr;
	t_vector		*entries;
	DIR				*dir;

	if (directories_ptrs->size == 0)
		return ;
	rec_directories = NULL;
	for (size_t i = 0; i < directories_ptrs->size; i++)
	{
		entries = alloc_vector(POINTER, 1, false);
		ptr = (t_dir_ptr *)get_element(directories_ptrs, i);	// returns the t_dir_ptr object which contains directory name and DIR *
		dir = ptr->directory;
		if (!dir)
		{
			perror("opendir");
			exit(1);
		}
		add_dirent_entries(ls, entries, ptr);	// loops through every entry in the current directory and adds them to entries vector
		merge_dirent(entries->data, 0, entries->size);
		if (ls->no_args == false)
			ft_printf("%s:\n", ptr->directory_name);
		rec_directories = alloc_vector(POINTER, 1, true);
		traverse_entries(ls, ptr, entries, rec_directories);
		ft_printf("\n");
		if (ls->no_args == false)
			ft_printf("\n");
		open_directories(ls, rec_directories);
		free_vector(entries);
		free_vector(rec_directories);
		closedir(dir);
	}
}
