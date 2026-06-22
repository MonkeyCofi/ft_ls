/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 13:45:05 by pipolint          #+#    #+#             */
/*   Updated: 2026/06/22 13:55:01 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	*build_path(t_ls *ls, const char *directory, struct dirent *entry)
{
	char	*path;
	char	*temp;

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
