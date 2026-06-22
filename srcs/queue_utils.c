/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 14:05:38 by pipolint          #+#    #+#             */
/*   Updated: 2026/06/22 14:06:02 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "queue.h"

void	print_queue_front(t_queue *queue)
{
	t_queue_node	*front;
	struct dirent	*node_data;

	front = queue->front;
	while (front)
	{
		node_data = front->data;
		ft_printf("%s\n", node_data->d_name);
		front = front->next;
	}
}

void	print_queue_back(t_queue *queue)
{
	t_queue_node	*trav;
	struct dirent	*node_data;
	t_queue_node	*front;

	trav = queue->rear;
	front = queue->front;
	while (trav != front)
	{
		node_data = trav->data;
		ft_printf("%s\n", node_data->d_name);
		trav = trav->prev;
	}
	node_data = trav->data;
	ft_printf("%s\n", node_data->d_name);
}
