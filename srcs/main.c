/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 18:05:41 by pipolint          #+#    #+#             */
/*   Updated: 2026/06/17 19:00:05 by pipolint         ###   ########.fr       */
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
	print_directories(ls.directory_queue);
	front = peek_front(ls.directory_queue);
	while (front)
	{
		add_to_vector(ls.directories, front->data, STRING);
		pop_front(ls.directory_queue);
		front = peek_front(ls.directory_queue);
	}
	mergesort_string(ls.directories->data, 0, ls.directories->size);
	ls.dir_entries = alloc_vector(POINTER, ls.directories->size);
	print_vector(ls.directories);
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
	t_vector *entries = alloc_vector(POINTER, 1);
	// call readdir() on each open directory
	for (size_t i = 0; i < pointers->size; i++)
	{
		DIR *dir = (DIR *)get_element(pointers, i);
		// save every directory into the entires vector
		struct dirent* entry = readdir(dir);
		while (entry)
		{
			add_to_vector(entries, entry, POINTER);
			entry = readdir(dir);
		}
		(void)entry;
	}
	(void)entries;
}