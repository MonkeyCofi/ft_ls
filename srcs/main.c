/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 18:05:41 by pipolint          #+#    #+#             */
/*   Updated: 2026/06/23 14:34:47 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"


void	initialize_ls(t_ls *ls)
{
	ft_memset(ls, 0, sizeof(t_ls));
	ls->directories = alloc_vector(STRING, 20, true);
	ls->directory_queue = create_queue();
	ls->dir_entries = NULL;
}

int main(int ac, char **av)
{
	t_ls			ls;
	t_vector		*directories;
	struct stat		st;
	t_queue_node	*front;

	initialize_ls(&ls);
	parse_cli(av, ac, &ls);
	front = peek_front(ls.directory_queue);
	while (front)
	{
		lstat(front->data, &st);
		if (S_ISDIR(st.st_mode))
		{
			char *str = ft_strdup(front->data);
			if (!str)
				return (1);
			add_to_vector(ls.directories, str, STRING);
		}
		pop_front(ls.directory_queue);
		front = peek_front(ls.directory_queue);
	}
	mergesort_string(ls.directories->data, 0, ls.directories->size);
	directories = alloc_vector(POINTER, ls.directories->size, true);
	add_arg_directories(&ls, directories);
	if (ft_strchr(ls.options, 'r') == NULL)
		open_directories(&ls, directories);
	// else
	// 	open_directories_reverse(&ls, directories);
	free_queue(ls.directory_queue);
	free_vector(directories);
	free_vector(ls.directories);
}