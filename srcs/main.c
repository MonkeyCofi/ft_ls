/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 18:05:41 by pipolint          #+#    #+#             */
/*   Updated: 2026/06/28 17:58:10 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	initialize_dir_strs(t_ls *ls)
{
	char			*str;
	struct stat		st;
	t_queue_node	*front;

	front = peek_front(ls->directory_queue);
	while (front)
	{
		stat(front->data, &st);
		if (S_ISDIR(st.st_mode))
		{
			str = ft_strdup(front->data);
			if (!str)
				return ;
			add_to_vector(ls->directories, str, STRING);
		}
		pop_front(ls->directory_queue);
		front = peek_front(ls->directory_queue);
	}
}

int main(int ac, char **av)
{
	t_ls			ls;
	t_vector		*directories;

	initialize_ls(&ls);
	parse_cli(av, ac, &ls);
	initialize_dir_strs(&ls);
	mergesort_string(ls.directories->data, 0, ls.directories->size);
	directories = alloc_vector(DIRECTORY, ls.directories->size, true);
	add_arg_directories(&ls, &directories);
	open_directories(&ls, &directories);
	free_queue(ls.directory_queue);
	free_vector(ls.directories);
	free_vector(directories);
	exit(ls.error_code);
}