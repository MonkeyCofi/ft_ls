/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 18:05:41 by pipolint          #+#    #+#             */
/*   Updated: 2026/06/24 20:44:47 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

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
	open_directories(&ls, directories);
	free_queue(ls.directory_queue);
	free_vector(directories);
	free_vector(ls.directories);
}