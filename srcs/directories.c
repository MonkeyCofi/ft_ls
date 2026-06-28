/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directories.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 13:45:53 by pipolint          #+#    #+#             */
/*   Updated: 2026/06/28 20:54:47 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_dir_ptr	*create_tdirptr(char *directory_name, DIR *dir_ptr)
{
	t_dir_ptr	*ptr;

	ptr = malloc(sizeof(t_dir_ptr));
	if (!ptr)
		return (NULL);
	ptr->directory_name = ft_strdup(directory_name);
	if (!ptr->directory_name)
	{
		free(ptr);
		return (NULL);
	}
	ptr->directory = dir_ptr;
	ptr->longest_filename = 0;
	ptr->longest_filesize = 0;
	ptr->longest_hlsize = 0;
	ptr->longest_group = 0;
	ptr->longest_owner = 0;
	return (ptr);
}

void	add_directory(t_ls *ls, char *path, t_vector *directory_vector)
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
				ft_printf("%s : ", path);
				perror("opendir");
				ls->error_code = 1;
				return ;
			}
			dir_ptr = create_tdirptr(path, open_dir);
			add_to_vector(directory_vector, dir_ptr, POINTER);
		}
	}
}

void	add_arg_directories(t_ls *ls, t_vector **directory_vector)
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
		stat(current_path, &st);
		if (S_ISDIR(st.st_mode))
		{
			ptr = opendir(current_path);
			dir_ptr = create_tdirptr(current_path, ptr);
			add_to_vector(*directory_vector, dir_ptr, DIRECTORY);
		}
	}
}

/**
 * @param ls The ls struct
 * @param pointers Vector cointaing DIR *
 */
void	open_directories(t_ls *ls, t_vector **directories)
{
	t_vector		*rec_directories;
	t_vector		*entries;
	t_dir_ptr		*ptr;
	size_t			temp;

	rec_directories = NULL;
	temp = ls->trav_i;
	set_index(ls, (*directories)->size);
	while (looper(ls, (*directories)->size))
	{
		entries = alloc_vector(STRING, 1, true);
		ptr = (t_dir_ptr *)get_element(*directories, ls->trav_i);
		if (!ptr->directory)
		{
			perror("opendir");
			ls->error_code = 1;
			return ;
		}
		add_dirent_entries(ls, entries, ptr);
		ls->merge_array = (char **)entries->data;
		ls->merge_dir = ptr;
		merge_dirent(ls, 0, entries->size);
		if (ls->no_args == false)
			ft_printf("%s:\n", ptr->directory_name);
		rec_directories = alloc_vector(DIRECTORY, 1, true);
		traverse_entries(ls, ptr, entries, rec_directories);
		// ft_printf("\n");
		if (ls->no_args == false)
			ft_printf("\n");
		if (ls->recursive)
			open_directories(ls, &rec_directories);
		free_vector(entries);
		free_vector(rec_directories);
		closedir(ptr->directory);
	}
	ls->trav_i = temp;
}

void	add_directory_in_dir(t_ls *ls, t_vector *entries, \
t_vector *directories, t_dir_ptr *dir)
{
	char		*elem;
	char		*path;
	struct stat	st;

	set_index(ls, entries->size);
	while (looper(ls, entries->size))
	{
		elem = (char *)get_element(entries, ls->trav_i);
		path = build_path(ls, dir->directory_name, elem);
		lstat(path, &st);
		if (ls->recursive)
		{
			if (S_ISDIR(st.st_mode))
			{
				if (ft_strncmp(elem, ".", -1) != 0 && \
ft_strncmp(elem, "..", -1) != 0)
					add_directory(ls, path, directories);
			}
		}
		free(path);
	}
}
