/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 14:33:44 by pipolint          #+#    #+#             */
/*   Updated: 2026/06/26 14:54:29 by pipolint         ###   ########.fr       */
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

void	traverse_entries(t_ls *ls, t_dir_ptr *dir, t_vector *entries, t_vector **directories)
{
	char			*path;
	size_t			temp;
	struct stat		st;
	char			*elem;
	struct winsize	w;
	
	temp = ls->trav_i;
	set_index(ls, entries->size);
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	path = NULL;
	ls->multiple_columns = multiple_col_print(ls, entries, &w);
	lstat(dir->directory_name, &st);
	ft_printf("number of entries %d\n", entries->size);
	ft_printf("capacity %d\n", entries->capacity);
	while (looper(ls, entries->size))
	{
		// elem = (struct dirent *)get_element(entries, ls->trav_i);
		elem = (char *)get_element(entries, ls->trav_i);
		path = build_path(ls, dir->directory_name, elem);
		lstat(path, &st);
		if (ls->recursive)
		{
			if (S_ISDIR(st.st_mode))
			{
				if (ft_strncmp(elem, ".", -1) != 0 && ft_strncmp(elem, "..", -1) != 0)
					add_directory(path, *directories);
			}
		}
		lstat(path, &st);
		if (ls->list)
			print_list(&st, dir);
		if (ls->columns_written > w.ws_col)
		{
			ls->columns_written = 0;
			ft_printf("\n");
		}
		// print_file(ls, dir, elem, &st);
		ft_printf("  ");
		if (ft_strchr(ls->options, 'l'))
		{
			ft_printf("\n");
			ls->columns_written = 0;
		}
		free(path);
	}
	ls->multiple_columns = false;
	ls->columns_written = 0;
	ls->trav_i = temp;
}

void	add_dirent_entries(t_ls *ls, t_vector *dirent_entries, t_dir_ptr* current_dir)
{
	struct dirent	*entry;
	char			*entry_str;

	entry = readdir(current_dir->directory);
	while (entry)
	{
		if (entry->d_name[0] == '.' && ls->all == false)
		{
			entry = readdir(current_dir->directory);
			continue;
		}
		
		entry_str = ft_strdup(entry->d_name);
		// ft_printf("adding %s\n", entry->d_name);
		// add_to_vector(*dirent_entries, entry, POINTER);
		add_to_vector(dirent_entries, entry_str, STRING);
		check_longest(ls, current_dir, entry);
		entry = readdir(current_dir->directory);
	}
}
