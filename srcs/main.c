/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 18:05:41 by pipolint          #+#    #+#             */
/*   Updated: 2026/06/17 00:55:45 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <string.h>

int main(int ac, char **av)
{
	t_ls		ls;
	t_vector 	*vector;
	
	ft_memset(&ls, 0, sizeof(t_ls));
	ls.directory_queue = create_queue();
	parse_cli(av, ac, &ls);
	// print_directories(ls.directory_queue);
	t_queue_node *front;
	vector = alloc_vector(STRING, 0);
	while ((front = peek_front(ls.directory_queue)))
	{
		add_to_vector(vector, front->data, STRING);
		pop_front(ls.directory_queue);
	}
	/*
		store the directory strings in the vector and sort by alphabetical order
		unless the -t flag is specified, then sort by time
		once sorted, open directories in that order
		
	*/
	char *strs[] = {"cabbage", "zone", "apple", "weed", "botany", "zigzag"};
	int size = sizeof(strs) / sizeof(char *);
	ft_printf("size %d\n", size);
	for (int i = 0; i < size; i++)
	{
		ft_printf("%s ", strs[i]);
	}
	ft_printf("\n");
	mergesort_string(strs, 0, sizeof(strs) / sizeof(char *));
	for (int i = 0; i < size; i++)
	{
		ft_printf("%s ", strs[i]);
	}
	ft_printf("\n");
	(void)ac;
	(void)av;
	(void)vector;
}