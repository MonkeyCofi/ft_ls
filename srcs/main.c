/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 18:05:41 by pipolint          #+#    #+#             */
/*   Updated: 2026/06/29 13:57:29 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int main(int ac, char **av)
{
	t_ls			ls;

	initialize_ls(&ls);
	parse_cli(av, ac, &ls);
	initialize_dir_strs(&ls);
	if (ls.files->size > 1)
		mergesort_string(ls.files->data, 0, ls.files->size);
	mergesort_string(ls.cli_args->data, 0, ls.cli_args->size);
	print_files(&ls, ls.files);
	if (ls.files->size > 0 && ls.cli_args->size > 0)
		ft_printf("\n");
	ls.directories = alloc_vector(DIRECTORY, ls.cli_args->size, true);
	add_arg_directories(&ls);
	if (ls.directories->size > 0)
		open_directories(&ls, &ls.directories);
	free_queue(ls.directory_queue);
	free_vector(ls.files);
	free_vector(ls.cli_args);
	free_vector(ls.directories);
	exit(ls.error_code);
}