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
		if (stat(front->data, &st) == -1)
		{
			ft_printf("%s: ", (char *)front->data);
			perror("stat");
			ls->error_code = 1;
		}
		else
		{
			str = ft_strdup(front->data);
			if (!str)
				return ;
			if (S_ISDIR(st.st_mode))
				add_to_vector(ls->directories, str, STRING);
			else
				add_to_vector(ls->files, str, STRING);
		}
		front = front->next;
	}
}

int main(int ac, char **av)
{
	t_ls			ls;
	t_vector		*directories;

	initialize_ls(&ls);
	parse_cli(av, ac, &ls);
	initialize_dir_strs(&ls);
	if (ls.files->size > 1)
		mergesort_string(ls.files->data, 0, ls.files->size);
	mergesort_string(ls.directories->data, 0, ls.directories->size);
	print_files(&ls, ls.files);
	if (ls.files->size > 0 && ls.directories->size > 0)
		ft_printf("\n");
	directories = alloc_vector(DIRECTORY, ls.directories->size, true);
	add_arg_directories(&ls, &directories);
	if (directories->size > 0)
		open_directories(&ls, &directories);
	free_queue(ls.directory_queue);
	free_vector(ls.files);
	free_vector(ls.directories);
	free_vector(directories);
	exit(ls.error_code);
}