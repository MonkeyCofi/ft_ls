/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 18:05:41 by pipolint          #+#    #+#             */
/*   Updated: 2026/06/19 12:31:22 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <string.h>
#include <sys/stat.h>

void	initialize_ls(t_ls *ls)
{
	ft_memset(ls, 0, sizeof(t_ls));
	ls->directories = alloc_vector(STRING, 20, true);
	ls->directory_queue = create_queue();
	ls->dir_entries = NULL;
}

/**
 * @param ls The ls struct
 * @param pointers Vector cointaing DIR *
 */
void open_directories(t_ls *ls, t_vector *pointers)
{
	t_vector	*rec_directories;

	rec_directories = NULL;
	if (!pointers || pointers->size == 0)
		return ;
	for (size_t i = 0; i < pointers->size; i++)
	{
		t_vector *entries = alloc_vector(POINTER, 1, false);
		t_dir_ptr *ptr = (t_dir_ptr *)get_element(pointers, i);
		// DIR *dir = (DIR *)get_element(pointers, i);
		DIR *dir = ptr->directory;
		if (!dir)
		{
			printf("no dir\n");
			exit(1);
		}
		struct dirent* entry = readdir(dir);
		while (entry)
		{
			if (entry->d_name[0] == '.' && !ft_strchr(ls->options, 'a'))
			{
				entry = readdir(dir);
				continue;
			}
			add_to_vector(entries, entry, POINTER);
			entry = readdir(dir);
		}
		printf("%s:\n", ptr->directory_name);
		merge_dirent(entries->data, 0, entries->size);
		rec_directories = alloc_vector(POINTER, 1, false);
		for (size_t j = 0; j < entries->size; j++)
		{
			struct dirent *elem = (struct dirent *)get_element(entries, j);
			char *parent_dir = ptr->directory_name;
			char *parent_dir_slash = NULL;
			if (ft_strncmp(parent_dir, "./", -1) != 0)
				parent_dir_slash = ft_strjoin(parent_dir, "/");
			else
				parent_dir_slash = parent_dir;
			char *joined_dir = ft_strjoin(parent_dir_slash, elem->d_name);
			// printf("directory %s\n", joined_dir);
			if (ft_strchr(ls->options, 'R'))
			{
				struct stat st;
				if (lstat(joined_dir, &st) == 0 && S_ISDIR(st.st_mode))
				{
					// Avoid recursion on "." and ".."
					if (ft_strncmp(elem->d_name, ".", -1) != 0 && ft_strncmp(elem->d_name, "..", -1) != 0)
					{
						DIR *open_dir = opendir(joined_dir);
						if (open_dir)
						{
							t_dir_ptr *rec_ptr = malloc(sizeof(t_dir_ptr));
							rec_ptr->directory = open_dir;
							rec_ptr->directory_name = ft_strdup(joined_dir); // Use a copy
							add_to_vector(rec_directories, rec_ptr, POINTER);
						}
					}
				}
			}
			printf("%s ", elem->d_name);
		}
		printf("\n%c", (i != pointers->size) ? '\n' : 0);
		free_vector(entries);
		closedir(dir);
	}
	if (ft_strchr(ls->options, 'R'))
	{
		// merge_directories((t_dir_ptr **)rec_directories->data, 0, rec_directories->size);
		// printf("directories: ");
		// for (size_t i = 0; i < rec_directories->size; i++)
		// {
		// 	t_dir_ptr *elem = (t_dir_ptr *)get_element(rec_directories, i);
		// 	printf("%s ", elem->directory_name);
		// }
		// printf("\n");
		// printf("recursively calling\n");
		open_directories(ls, rec_directories);
	}
}

int main(int ac, char **av)
{
	t_ls		ls;
	t_queue_node *front;
	t_vector	*initial_directories;

	initialize_ls(&ls);
	parse_cli(av, ac, &ls);
	initial_directories = alloc_vector(STRING, 20, true);
	front = peek_front(ls.directory_queue);
	while (front)
	{
		DIR *test = opendir(front->data);
		if (test)
		{
			char *str = ft_strdup(front->data);
			add_to_vector(ls.directories, str, STRING);
			closedir(test);
		}
		pop_front(ls.directory_queue);
		front = peek_front(ls.directory_queue);
	}
	(void)initial_directories;
	mergesort_string(ls.directories->data, 0, ls.directories->size);
	t_vector *pointers = alloc_vector(POINTER, ls.directories->size, false);
	for (size_t i = 0; i < ls.directories->size; i++)
	{
		t_dir_ptr *directory_ptr = malloc(sizeof(t_dir_ptr));
		directory_ptr->directory_name = (char *)get_element(ls.directories, i);
		DIR *ptr = opendir(get_element(ls.directories, i));
		if (ptr)
		{
			// add_to_vector(pointers, ptr, POINTER);
			directory_ptr->directory = ptr;
			add_to_vector(pointers, directory_ptr, POINTER);
		}
		else
			printf("failed %s\n", get_element(ls.directories, i));
	}
	if (ft_strchr(ls.options, 'r') == NULL)
		open_directories(&ls, pointers);
	else
	{
		for (size_t i = pointers->size; i-- > 0;)
		{
			t_vector *entries = alloc_vector(POINTER, 1, false);
			DIR *dir = (DIR *)get_element(pointers, i);
			// save every directory into the entires vector
			struct dirent* entry = readdir(dir);
			while (entry)
			{
				if (entry->d_name[0] == '.' && !ft_strchr(ls.options, 'a'))
				{
					entry = readdir(dir);
					continue;
				}
				add_to_vector(entries, entry, POINTER);
				entry = readdir(dir);
			}
			(void)entry;
			printf("%s:\n", get_element(ls.directories, i));
			merge_dirent(entries->data, 0, entries->size);
			for (size_t j = entries->size; j-- > 0;)
			{
				printf("%s  ", ((struct dirent *)get_element(entries, j))->d_name);
			}
			printf("\n\n");
			free_vector(entries);
			closedir((DIR *)get_element(pointers, i));
		}
	}
	free_queue(ls.directory_queue);
	free_vector(pointers);
	free_vector(ls.directories);
}