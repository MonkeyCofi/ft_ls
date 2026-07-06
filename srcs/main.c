/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 18:05:41 by pipolint          #+#    #+#             */
/*   Updated: 2026/07/06 16:13:56 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	free_ls(t_ls *ls)
{
	if (ls->directory_queue)
		free_queue(ls->directory_queue);
	if (ls->files)
		free_vector(ls->files);
	if (ls->cli_args)
		free_vector(ls->cli_args);
	if (ls->directories)
		free_vector(ls->directories);
}

int main(int ac, char **av)
{
	t_ls			ls;
	int				final_error_code;

	initialize_ls(&ls);
	parse_cli(av, ac, &ls);
	initialize_dir_strs(&ls);
	final_error_code = ls.error_code;
	if (final_error_code == 2)
		ls.error_code = 0;
	if (ls.files->size > 1)
		mergesort_string(ls.files->data, 0, ls.files->size);
	mergesort_string(ls.cli_args->data, 0, ls.cli_args->size);
	print_files(&ls, ls.files);
	if (ls.files->size > 0 && ls.cli_args->size > 0)
		ft_printf("\n");
	ls.directories = alloc_vector(DIRECTORY, ls.cli_args->size, true);
	if (!ls.directories)
	{
		free_ls(&ls);
		exit(MAJOR_ERR);
	}
	add_arg_directories(&ls);
	if (ls.directories->size > 0)
		open_directories(&ls, &ls.directories);
	free_ls(&ls);
	if (ls.error_code > final_error_code)
		final_error_code = ls.error_code;
	exit(final_error_code);
}