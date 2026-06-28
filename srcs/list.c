/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 13:18:36 by pipolint          #+#    #+#             */
/*   Updated: 2026/06/28 17:43:52 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	check_longest(t_ls *ls, t_dir_ptr *current_dir, struct dirent *entry)
{
	char		*path;
	char		*itoa_str;
	struct stat	st;

	path = build_path(ls, current_dir->directory_name, entry->d_name);
	if (lstat(path, &st) == -1)
	{
		perror("lstat");
		return ;
	}
	itoa_str = NULL;
	itoa_str = ft_itoa(st.st_size);
	if (!itoa_str)
		return ;
	if (ft_strlen(itoa_str) > current_dir->longest_filesize)
		current_dir->longest_filesize = ft_strlen(itoa_str);
	if (ft_strlen(entry->d_name) > current_dir->longest_filename)
		current_dir->longest_filename = ft_strlen(entry->d_name);
	free(itoa_str);
	itoa_str = ft_itoa(st.st_nlink);
	if (ft_strlen(itoa_str) > current_dir->longest_hlsize)
		current_dir->longest_hlsize = ft_strlen(itoa_str);
	check_group_owner(&st, current_dir);
	free(itoa_str);
	free(path);
}

static char	list_char(mode_t	*perms, int perm)
{
	if (((*perms) & S_IRUSR && perm == S_IRUSR) || \
((*perms) & S_IRGRP && perm == S_IRGRP) || \
((*perms) & S_IROTH && perm == S_IROTH))
		return ('r');
	if (((*perms) & S_IWUSR && perm == S_IWUSR) || \
((*perms) & S_IWGRP && perm == S_IWGRP) || \
((*perms) & S_IWOTH && perm == S_IWOTH))
		return ('w');
	if (((*perms) & S_IXUSR && perm == S_IXUSR) || \
((*perms) & S_IXGRP && perm == S_IXGRP) || \
((*perms) & S_IXOTH && perm == S_IXOTH))
		return ('x');
	return ('-');
}

char	is_directory(struct stat *st)
{
	if (S_ISDIR(st->st_mode))
		return ('d');
	return ('-');
}

void	print_list(struct stat *st, t_dir_ptr *ptr)
{
	static const char	*months[] = {"Jan", "Feb", "Mar", "Apr", "May",\
		"Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
	mode_t				perms;
	struct passwd		*pw;
	struct group		*grp;
	struct tm			now_t;

	perms = st->st_mode;
	pw = getpwuid(st->st_uid);
	grp = getgrgid(st->st_gid);
	now_t = *localtime(&st->st_mtime);
	ft_printf("%c", is_directory(st));
	ft_printf("%c%c%c", list_char(&perms, S_IRUSR), list_char(&perms, S_IWUSR), \
list_char(&perms, S_IXUSR));
	ft_printf("%c%c%c", list_char(&perms, S_IRGRP), list_char(&perms, S_IWGRP), \
list_char(&perms, S_IXGRP));
	ft_printf("%c%c%c ", list_char(&perms, S_IROTH), list_char(&perms, S_IWOTH), \
list_char(&perms, S_IXOTH));
	ft_printf("%*d ", ptr->longest_hlsize, st->st_nlink);
	ft_printf("%*s ", ptr->longest_group, grp->gr_name);
	ft_printf("%*s ", ptr->longest_owner, pw->pw_name);
	ft_printf("%*d ", ptr->longest_filesize, st->st_size);
	ft_printf("%s %02d ", months[now_t.tm_mon], now_t.tm_mday);
	ft_printf("%02d:%02d ", now_t.tm_hour, now_t.tm_min);
}

void	print_block_size(t_ls *ls, t_vector *entries, t_dir_ptr *curr_dir)
{
	char		*path;
	char		*elem;
	size_t		total;
	struct stat	st;

	total = 0;
	while (looper(ls, entries->size))
	{
		elem = (char *)get_element(entries, ls->trav_i);
		path = build_path(ls, curr_dir->directory_name, elem);
		lstat(path, &st);
		total += st.st_blocks / 2;
		free(path);
	}
	ft_printf("total %ld\n", total);
	set_index(ls, entries->size);
}