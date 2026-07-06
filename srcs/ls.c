/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/24 20:20:50 by pipolint          #+#    #+#             */
/*   Updated: 2026/07/06 15:54:17 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	initialize_ls(t_ls *ls)
{
	ft_memset(ls, 0, sizeof(t_ls));
    ls->files = alloc_vector(STRING, 20, true);
    if (ls->files == NULL)
    {
        exit(MAJOR_ERR);
    }
	ls->cli_args = alloc_vector(STRING, 20, true);
    if (!ls->cli_args)
    {
        free_vector(ls->files);
        exit(MAJOR_ERR);
    }
	ls->directory_queue = create_queue();
    if (!ls->directory_queue)
    {
        free_vector(ls->files);
        free_vector(ls->cli_args);
        exit(MAJOR_ERR);
    }
	ls->dir_entries = NULL;
}

void    set_index(t_ls *ls, size_t max)
{
    if (ls->reverse)
    {
        ls->trav_i = max;
        return ;
    }
    ls->trav_i = (size_t)-1;
}

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
			ft_putstr_fd((char *)front->data, STDERR_FILENO);
			ft_putstr_fd(": ", STDERR_FILENO);
			perror("");
			ls->error_code = 2;
		}
		else
		{
			str = ft_strdup(front->data);
			if (!str)
			{
				ls->error_code = 2;
				continue ;
			}
			if (S_ISDIR(st.st_mode))
			{
				if (!add_to_vector(ls->cli_args, str, STRING))
				{
					free(str);
					ls->error_code = 2;
					continue ;
				}
			}
			else
			{
				if (!add_to_vector(ls->files, str, STRING))
				{
					free(str);
					ls->error_code = 2;
					continue ;
				}
			}
		}
		front = front->next;
	}
}
