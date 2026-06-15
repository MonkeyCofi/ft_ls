/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 18:05:41 by pipolint          #+#    #+#             */
/*   Updated: 2026/06/15 19:58:24 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int main(int ac, char **av)
{
	t_ls		ls;
	t_vector* 	vector;
	
	ft_memset(&ls, 0, sizeof(t_ls));
	ls.directory_queue = malloc(sizeof(t_queue));
	parse_cli(av, ac, &ls);
	print_directories(ls.directory_queue);
	t_queue_node *front;
	while ((front = peek_front(ls.directory_queue)))
	{
		ft_printf("%s\n", front->data);
		pop_front(ls.directory_queue);
	}
	/*
		store the directory strings in the vector and sort by alphabetical order
	*/
	(void)ac;
	(void)av;
	(void)vector;
}