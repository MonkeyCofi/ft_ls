/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/24 20:20:50 by pipolint          #+#    #+#             */
/*   Updated: 2026/06/24 20:57:34 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	initialize_ls(t_ls *ls)
{
	ft_memset(ls, 0, sizeof(t_ls));
    ls->files = alloc_vector(STRING, 20, true);
	ls->directories = alloc_vector(STRING, 20, true);
	ls->directory_queue = create_queue();
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
