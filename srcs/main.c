/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 18:05:41 by pipolint          #+#    #+#             */
/*   Updated: 2026/06/17 21:23:47 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <string.h>

void	initialize_ls(t_ls *ls)
{
	ft_memset(ls, 0, sizeof(t_ls));
	ls->directories = alloc_vector(STRING, 20);
	ls->directory_queue = create_queue();
	ls->dir_entries = NULL;
}

int main(int ac, char **av)
{
	t_ls		ls;
	t_queue_node *front;
	
	initialize_ls(&ls);
	parse_cli(av, ac, &ls);
	front = peek_front(ls.directory_queue);
	while (front)
	{
		add_to_vector(ls.directories, front->data, STRING);
		pop_front(ls.directory_queue);
		front = peek_front(ls.directory_queue);
	}
	mergesort_string(ls.directories->data, 0, ls.directories->size);
	/*
		each entry in ls.directories is a directory name
		create a vector of DIR pointers which will be in 
		alphabetical order
	*/
	t_vector *pointers = alloc_vector(POINTER, ls.directories->size);
	for (size_t i = 0; i < ls.directories->size; i++)
	{
		DIR *ptr = opendir(get_element(ls.directories, i));
		if (ptr)
			add_to_vector(pointers, ptr, POINTER);
	}
	// call readdir() on each open directory
	if (ft_strchr(ls.options, 'r') == NULL)
	{
		for (size_t i = 0; i < pointers->size; i++)
		{
			t_vector *entries = alloc_vector(POINTER, 1);
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
			for (size_t j = 0; j < entries->size; j++)
			{
				printf("%s  ", ((struct dirent *)get_element(entries, j))->d_name);
			}
			printf("\n\n");
			free_vector(entries);
			closedir((DIR *)get_element(pointers, i));
		}
	}
	else
	{
		for (size_t i = pointers->size; i-- > 0;)
		{
			t_vector *entries = alloc_vector(POINTER, 1);
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
	printf("here\n");
}