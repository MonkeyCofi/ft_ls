/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 18:05:41 by pipolint          #+#    #+#             */
/*   Updated: 2026/06/14 15:51:20 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int main(int ac, char **av)
{
	t_vector	vector;
	t_ls		ls;

	ft_memset(&ls, 0, sizeof(t_ls));
	ls.directory_queue = malloc(sizeof(t_queue));
	parse_cli(av, ac, &ls);
	// t_queue_node*	test = ls.directory_queue->front;
	// while (test)
	// {
	// 	printf("%s\n", (char *)test->data);
	// 	test = test->next;
	// }
	print_directories(ls.directory_queue);
	(void)ac;
	(void)av;
	(void)vector;
}