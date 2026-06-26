/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 18:05:41 by pipolint          #+#    #+#             */
/*   Updated: 2026/06/26 13:31:00 by pipolint         ###   ########.fr       */
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
		stat(front->data, &st);
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
	for (size_t i = 0; i < ls.directories->size; i++)
	{
		ft_printf("vector %s\n", get_element(ls.directories, i));
	}
	directories = alloc_vector(POINTER, ls.directories->size, true);
	add_arg_directories(&ls, &directories);
	open_directories(&ls, &directories);
	free_vector(directories);
	free_queue(ls.directory_queue);
	free_vector(ls.directories);
}