/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 14:33:44 by pipolint          #+#    #+#             */
/*   Updated: 2026/06/28 17:51:27 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_file(t_ls *ls, t_dir_ptr *dir, char *elem)
{
	if (ls->multiple_columns)
		ls->columns_written += ft_printf("\e[m%-*s", \
dir->longest_filename, elem);
	else
		ls->columns_written += ft_printf("%s", elem);
	ft_printf("  ");
	if (ft_strchr(ls->options, 'l'))
	{
		ft_printf("\n");
		ls->columns_written = 0;
	}
}

void	loop_entries(t_ls *ls, t_vector *entries, \
t_dir_ptr *dir, struct winsize *w)
{
	char		*elem;
	char		*path;
	struct stat	st;

	while (looper(ls, entries->size))
	{
		elem = (char *)get_element(entries, ls->trav_i);
		path = build_path(ls, dir->directory_name, elem);
		lstat(path, &st);
		if (ls->list)
			print_list(&st, dir);
		if (ls->columns_written >= w->ws_col)
		{
			ls->columns_written = 0;
			ft_printf("\n");
		}
		print_file(ls, dir, elem);
		free(path);
	}
}

void	traverse_entries(t_ls *ls, t_dir_ptr *dir, t_vector *entries, \
t_vector *directories)
{
	size_t			temp;
	struct stat		st;
	struct winsize	w;

	temp = ls->trav_i;
	set_index(ls, entries->size);
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	ls->multiple_columns = multiple_col_print(ls, entries, &w);
	lstat(dir->directory_name, &st);
	if (ls->list)
		print_block_size(ls, entries, dir);
	loop_entries(ls, entries, dir, &w);
	if (ls->columns_written > 0)
		ft_printf("\n");
	ls->multiple_columns = false;
	ls->columns_written = 0;
	add_directory_in_dir(ls, entries, directories, dir);
	ls->trav_i = temp;
}

void	add_dirent_entries(t_ls *ls, t_vector *dirent_entries, \
t_dir_ptr *current_dir)
{
	struct dirent	*entry;
	char			*entry_str;

	entry = readdir(current_dir->directory);
	while (entry)
	{
		if (entry->d_name[0] == '.' && ls->all == false)
		{
			entry = readdir(current_dir->directory);
			continue ;
		}
		entry_str = ft_strdup(entry->d_name);
		add_to_vector(dirent_entries, entry_str, STRING);
		check_longest(ls, current_dir, entry);
		entry = readdir(current_dir->directory);
	}
}
