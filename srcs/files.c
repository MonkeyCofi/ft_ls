/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 14:33:44 by pipolint          #+#    #+#             */
/*   Updated: 2026/06/23 16:32:45 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_file(t_ls *ls, t_dir_ptr *dir, struct dirent *elem, struct stat *st)
{
	if (S_ISDIR(st->st_mode))
	{
		if (ls->multiple_columns)
			ls->columns_written += ft_printf("\e[1;34m%-*s\e[0m", \
                dir->longest_filename, elem->d_name);
		else
			ls->columns_written += ft_printf("%s", elem->d_name);
	}
	else if (st->st_mode & S_IXUSR)
	{
		if (ls->multiple_columns)
			ls->columns_written += ft_printf("\e[1;32m%-*s\e[0m", \
                dir->longest_filename, elem->d_name);
		else
			ls->columns_written += ft_printf("%s", elem->d_name);
	}
	else
	{
		if (ls->multiple_columns)
			ls->columns_written += ft_printf("\e[m%-*s\e[0m", \
                dir->longest_filename, elem->d_name);
		else
			ls->columns_written += ft_printf("%s", elem->d_name);
	}
}

void	traverse_entries(t_ls *ls, t_dir_ptr *dir, t_vector *entries, t_vector *directories)
{
	char			*path;
	size_t			i;
	struct stat		st;
	struct dirent	*elem;
	struct winsize	w;
	
	i = -1;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	path = NULL;
	ls->multiple_columns = multiple_col_print(ls, entries, &w);
	lstat(dir->directory_name, &st);
	ft_printf("%s total %d\n", dir->directory_name, st.st_size);
	while (++i < entries->size)
	{
		elem = (struct dirent *)get_element(entries, i);
		path = build_path(ls, dir->directory_name, elem);
		lstat(path, &st);
		if (ft_strchr(ls->options, 'R'))
		{
			if (S_ISDIR(st.st_mode))
			{
				if (ft_strncmp(elem->d_name, ".", -1) != 0 && ft_strncmp(elem->d_name, "..", -1) != 0)
					add_directory(path, directories);
			}
		}
		lstat(path, &st);
		if (ft_strchr(ls->options, 'l'))
			print_list(&st, dir);
		if (ls->columns_written > w.ws_col)
		{
			ls->columns_written = 0;
			ft_printf("\n");
		}
		print_file(ls, dir, elem, &st);
		ft_printf("  ");
		if (ft_strchr(ls->options, 'l'))
		{
			ft_printf("\n");
			ls->columns_written = 0;
		}
		// free(path);
		// path = NULL;
	}
	ls->multiple_columns = false;
	ls->columns_written = 0;
}

void	add_dirent_entries(t_ls *ls, t_vector *dirent_entries, t_dir_ptr* current_dir)
{
	struct dirent	*entry;

	entry = readdir(current_dir->directory);
	while (entry)
	{
		if (entry->d_name[0] == '.' && !ft_strchr(ls->options, 'a'))
		{
			entry = readdir(current_dir->directory);
			continue;
		}
		add_to_vector(dirent_entries, entry, POINTER);
		check_longest(ls, current_dir, entry);
		entry = readdir(current_dir->directory);
	}
}
