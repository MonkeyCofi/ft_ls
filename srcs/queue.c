/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 18:05:14 by pipolint          #+#    #+#             */
/*   Updated: 2026/06/08 18:05:15 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "queue.h"

/**
 * @brief Adds a node to the front of the list (the start)
 * @param queue The queue object
 * @param node The node to add to the front of the queue
 * @return Nothing
*/
void    enqueue_front(t_queue *queue, t_queue_node *node)
{
	if (is_empty(queue))
	{
		queue->rear = node;
		queue->front = node;
		return ;
	}
	queue->front->prev = node;
	node->next = queue->front;
	queue->front = node;
}

/**
 * @brief Checks whether the queue is empty
 * @param queue The queue object
 * @return Whether the queue is empty or not
*/
bool	is_empty(t_queue *queue)
{
	if (queue->front == NULL)
		return true;
	return false;
}

/**
 * @brief Adds a node to the back of the list (the end)
 * @param queue The queue object
 * @param node The node to add to the back of the queue
 * @return Nothing
*/
void	enqueue_back(t_queue *queue, t_queue_node *node)
{
	if (is_empty(queue))
	{
		queue->front = node;
		queue->rear = node;
		return ;
	}
	node->prev = queue->rear;
	queue->rear->next = node;
	queue->rear = node;
}

/**
 * @brief Creates a dynamically allocated node and points the data attribute to data passed
 * @param data The data to pass to the node
 * @return The malloc'd node
*/
t_queue_node	*create_queue_node(void *data)
{
	t_queue_node	*new;

	new = malloc(sizeof(t_queue_node));
	if (!new)
		return NULL;
	new->data = data;
	new->prev = NULL;
	new->next = NULL;
	return new;
}

/**
 * @brief Frees every link in the queue as well as the queue object itself
 * @param queue The queue object
 * @return Nothing
*/
void	free_queue(t_queue* queue)
{
	t_queue_node	*trav;
	t_queue_node	*temp;

	trav = queue->front;
	while (trav)
	{
		temp = trav->next;
		free(trav);
		trav = temp;
	}
	free(queue);
}

/**
 * @brief Dynamically allocates the queue object
 * @return The dynamically allocated queue
*/
t_queue	*create_queue()
{
	t_queue	*queue;
	
	queue = malloc(sizeof(t_queue));
	if (!queue)
		return NULL;
	ft_memset(queue, 0, sizeof(t_queue));
	return queue;
}

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

t_queue_node	*peek_front(t_queue *queue)
{
	return (queue->front);
}

t_queue_node	*peek_rear(t_queue *queue)
{
	return (queue->rear);
}

t_queue_node	*pop_front(t_queue* queue)
{
	t_queue_node	*front;

	front = queue->front;
	queue->front = front->next;
	queue->front->prev = NULL;
	return (front);
}

t_queue_node	*pop_back(t_queue *queue)
{
	t_queue_node	*rear;
	t_queue_node	*rear_prev;

	rear = queue->rear;
	rear_prev = rear->prev;
	queue->rear = rear_prev;
	rear_prev->next = NULL;
	return rear;
}