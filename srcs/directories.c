/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directories.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 13:45:53 by pipolint          #+#    #+#             */
/*   Updated: 2026/06/22 13:57:48 by pipolint         ###   ########.fr       */
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
