/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directories.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 13:45:53 by pipolint          #+#    #+#             */
/*   Updated: 2026/07/05 15:35:08 by pipolint         ###   ########.fr       */
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
		closedir(dir_ptr);
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
				print_error("cannot open directory", path, "");
				ls->error_code = 1;
				return ;
			}
			dir_ptr = create_tdirptr(path, open_dir);
			if (!dir_ptr)
			{
				ls->error_code = 2;
				return ;
			}
			if (!add_to_vector(directory_vector, dir_ptr, POINTER))
			{
				free(dir_ptr->directory_name);
				free(dir_ptr);
				ls->error_code = 2;
			}
		}
	}
	else
	{
		print_error("cannot access", path, "");
		ls->error_code = 1;
	}
}

void	add_arg_directories(t_ls *ls)
{
	char		*current_path;
	DIR			*ptr;
	t_dir_ptr	*dir_ptr;
	struct stat	st;
	size_t		i;

	current_path = NULL;
	i = -1;
	while (++i < ls->cli_args->size)
	{
		current_path = (char *)get_element(ls->cli_args, i);
		if (stat(current_path, &st) == -1)
		{
			print_error("cannot access", current_path, "");
			ls->error_code = 1;
			continue ;
		}
		if (S_ISDIR(st.st_mode))
		{
			ptr = opendir(current_path);
			if (!ptr)
			{
				print_error("cannot open directory", current_path, "");
				ls->error_code = 1;
				continue ;
			}
			dir_ptr = create_tdirptr(current_path, ptr);
			if (!dir_ptr)
			{
				ls->error_code = 2;
				return ;
			}
			if (!add_to_vector(ls->directories, dir_ptr, DIRECTORY))
			{
				free(dir_ptr->directory_name);
				free(dir_ptr);
				ls->error_code = 2;
				return ;
			}
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
		if (!entries)
		{
			ft_putstr_fd("failed to alloc vector\n", 2);
			ls->error_code = 2;
			return ;
		}
		ptr = (t_dir_ptr *)get_element(*directories, ls->trav_i);
		if (!ptr->directory)
		{
			ft_putstr_fd("cannot open directory ", STDERR_FILENO);
			ft_putstr_fd(ptr->directory_name, STDERR_FILENO);
			perror(" ");
			ls->error_code = 1;
			free_vector(entries);
			if (rec_directories)
				free_vector(rec_directories);
			return ;
		}
		add_dirent_entries(ls, entries, ptr);
		if (ls->error_code == 2)
		{
			free_vector(entries);
			free_vector(rec_directories);
			closedir(ptr->directory);
			return ;
		}
		ls->merge_array = (char **)entries->data;
		ls->merge_dir = ptr;
		merge_dirent(ls, 0, entries->size);
		if (ls->error_code == 2)
		{
			free_vector(entries);
			free_vector(rec_directories);
			closedir(ptr->directory);
			return ;
		}
		if (ls->no_args == false)
			ft_printf("%s:\n", ptr->directory_name);
		rec_directories = alloc_vector(DIRECTORY, 1, true);
		if (!rec_directories)
		{
			free_vector(entries);
			closedir(ptr->directory);
			ls->error_code = 2;
			return ;
		}
		traverse_entries(ls, ptr, entries, rec_directories);
		if (ls->error_code == 2)
		{
			free_vector(entries);
			free_vector(rec_directories);
			closedir(ptr->directory);
			return ;
		}
		if (ls->no_args == false)
			ft_printf("\n");
		if (ls->recursive)
			open_directories(ls, &rec_directories);
		free_vector(entries);
		free_vector(rec_directories);
		closedir(ptr->directory);
		if (ls->error_code == 2)
			return ;
	}
	ls->trav_i = temp;
}

void	add_directory_in_dir(t_ls *ls, t_vector *entries, \
t_vector *directories, t_dir_ptr *dir)
{
	char		*elem;
	char		*path;
	struct stat	st;
	size_t		i;

	i = 0;
	while (i < entries->size)
	{
		elem = (char *)get_element(entries, i);
		path = build_path(ls, dir->directory_name, elem);
		if (!path)
		{
			ls->error_code = 2;
			return ;
		}
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
		i++;
	}
}
