/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directories.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 13:45:53 by pipolint          #+#    #+#             */
/*   Updated: 2026/06/26 16:42:01 by pipolint         ###   ########.fr       */
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
	char		*directory;
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
				return ;
			}
			directory = ft_strdup(path);
			if (!directory)
			{
				return ;
			}
			dir_ptr = create_tdirptr(directory, open_dir);
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
			add_to_vector(*directory_vector, dir_ptr, POINTER);
		}
		else
			printf("failed %s\n", get_element(ls->directories, i));
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
		entries = alloc_vector(POINTER, 1, false);
		ptr = (t_dir_ptr *)get_element(*directories, ls->trav_i);
		if (!ptr->directory)
		{
			perror("opendir");
			return ;
		}
		// ft_printf("checking %s\n", ptr->directory_name);
		add_dirent_entries(ls, entries, ptr);
		// for (size_t i = 0; i < entries->size; i++)
		// {
		// 	char *elem = get_element(entries, i);
		// 	ft_printf("entries[%d] %s\n", i, elem);
		// 	// ft_printf("test test %s\n", get_element(entries, i));
		// }
		merge_dirent(entries->data, 0, entries->size, ls->time);
		if (ls->no_args == false)
			ft_printf("%s:\n", ptr->directory_name);
		rec_directories = alloc_vector(POINTER, 1, true);
		traverse_entries(ls, ptr, entries, &rec_directories);
		ft_printf("\n");
		if (ls->no_args == false)
			ft_printf("\n");
		if (ls->recursive)
			open_directories(ls, &rec_directories);
		// else
		// 	ft_printf("no recursive\n");
		free_vector(entries);
		free_vector(rec_directories);
		closedir(ptr->directory);
	}
	ls->trav_i = temp;
}
