/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 14:33:44 by pipolint          #+#    #+#             */
/*   Updated: 2026/07/03 12:38:30 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	check_longest_file(t_dir_ptr *current_dir, char *name, struct stat *st)
{
	char	*itoa_str;

	if (ft_strlen(name) > current_dir->longest_filename)
		current_dir->longest_filename = ft_strlen(name);
	itoa_str = ft_itoa(st->st_size);
	if (itoa_str)
	{
		if (ft_strlen(itoa_str) > current_dir->longest_filesize)
			current_dir->longest_filesize = ft_strlen(itoa_str);
		free(itoa_str);
	}
	itoa_str = ft_itoa(st->st_nlink);
	if (itoa_str)
	{
		if (ft_strlen(itoa_str) > current_dir->longest_hlsize)
			current_dir->longest_hlsize = ft_strlen(itoa_str);
		free(itoa_str);
	}
	check_group_owner(st, current_dir);
}

void	print_file(t_ls *ls, t_dir_ptr *dir, char *elem)
{
	if (ls->multiple_columns)
		ls->columns_written += ft_printf("\e[m%-*s", \
dir->longest_filename, elem);
	else
		ls->columns_written += ft_printf("%s", elem);
	ft_printf("  ");
	if (ls->list)
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
		if (!path)
		{
			ls->error_code = 2;
			return ;
		}
		if (!path)
		{
			ls->error_code = 2;
			return ;
		}
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
	ft_memset(&w, 0, sizeof(struct winsize));
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	if (w.ws_col == 0)
		w.ws_col = 80;
	ls->multiple_columns = multiple_col_print(ls, entries, &w);
	lstat(dir->directory_name, &st);
	if (ls->list)
		print_block_size(ls, entries, dir);
	if (ls->error_code == 2)
		return ;
	loop_entries(ls, entries, dir, &w);
	if (ls->error_code == 2)
		return ;
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
		if (!entry_str)
		{
			ls->error_code = 2;
			return ;
		}
		if (!add_to_vector(dirent_entries, entry_str, STRING))
		{
			free(entry_str);
			ls->error_code = 2;
			return ;
		}
		check_longest(ls, current_dir, entry);
		entry = readdir(current_dir->directory);
	}
}

void	print_files(t_ls *ls, t_vector *files)
{
	t_dir_ptr		file_info;
	char			*elem;
	struct stat		st;
	struct winsize	w;
	size_t			i;

	if (!files || files->size == 0)
		return ;
	ft_memset(&file_info, 0, sizeof(t_dir_ptr));
	ft_memset(&w, 0, sizeof(struct winsize));
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	if (w.ws_col == 0)
		w.ws_col = 80;
	i = 0;
	while (i < files->size)
	{
		elem = (char *)get_element(files, i);
		if (ls->list)
		{
			if (lstat(elem, &st) == -1)
			{
				ft_printf("%s: ", elem);
				perror("lstat");
				continue ;
			}
			check_longest_file(&file_info, elem, &st);
		}
		else if (!ls->list)
		{
			if (ft_strlen(elem) > file_info.longest_filename)
				file_info.longest_filename = ft_strlen(elem);
		}
		i++;
	}
	ls->multiple_columns = !ls->list && multiple_col_print(ls, files, &w);
	if (ls->reverse)
	{
		i = files->size;
		while (i-- > 0)
		{
			elem = (char *)get_element(files, i);
			if (ls->list)
			{
				if (lstat(elem, &st) == -1)
					continue ;
				print_list(&st, &file_info);
				ft_printf("%s\n", elem);
			}
			else
				print_file(ls, &file_info, elem);
		}
	}
	else
	{
		i = 0;
		while (i < files->size)
		{
			elem = (char *)get_element(files, i);
			if (ls->list)
			{
				if (lstat(elem, &st) == -1)
				{
					i++;
					continue ;
				}
				print_list(&st, &file_info);
				ft_printf("%s\n", elem);
			}
			else
				print_file(ls, &file_info, elem);
			i++;
		}
	}
	if (!ls->list && ls->columns_written > 0)
		ft_printf("\n");
	ls->columns_written = 0;
	ls->multiple_columns = false;
}
