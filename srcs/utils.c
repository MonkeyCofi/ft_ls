/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 13:45:05 by pipolint          #+#    #+#             */
/*   Updated: 2026/06/24 21:01:21 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	*build_path(t_ls *ls, const char *directory, struct dirent *entry)
{
	char	*path;
	char	*temp;

	if (!ft_strncmp(directory, "./", -1) || !ft_strncmp(directory, "../", -1))
		path = ft_strdup(directory);
	else
		path = ft_strjoin(directory, "/");
	if (!path)
	{
		return (NULL);
	}
	temp = path;
	path = ft_strjoin(path, entry->d_name);
	if (!path)
	{
		return (NULL);
	}
	free(temp);
	(void)ls;
	(void)temp;
	return (path);
}

void	check_group_owner(struct stat *st, t_dir_ptr *current_dir)
{
	struct group	*gw;
	struct passwd	*pw;

	gw = getgrgid(st->st_gid);
	pw = getpwuid(st->st_uid);
	if (pw)
	{
		if (ft_strlen(pw->pw_name) > current_dir->longest_owner)
		current_dir->longest_owner = ft_strlen(pw->pw_name);
	}
	if (gw)
	{
		if (ft_strlen(gw->gr_name) > current_dir->longest_group)
			current_dir->longest_group = ft_strlen(gw->gr_name);
	}
}

bool	multiple_col_print(t_ls *ls, t_vector *entries, struct winsize *w)
{
	size_t			i;
	size_t			size;
	size_t			count;
	struct dirent	*element;

	i = -1;
	size = entries->size;
	count = 0;
	while (++i < size)
	{
		element = (struct dirent *)get_element(entries, i);
		count += ft_strlen(element->d_name);
		if (count >= w->ws_col)
			return true;
	}
	(void)ls;
	return false;
}

bool	looper(t_ls *ls, size_t max)
{
	if (ls->reverse)
		return ls->trav_i-- > 0;
	return ++ls->trav_i < max;
}