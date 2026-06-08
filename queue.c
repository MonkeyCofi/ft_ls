#include "queue.h"

void    add_to_front(t_queue *queue, t_queue_node *node)
{
	node->next = queue->front;
	queue->front = node;
}

t_queue_node	*create_queue_node(void *data)
{
	t_queue_node	*new;

	new = malloc(sizeof(t_queue_node));
	if (!new)
		return NULL;
	new->data = data;
	new->next = NULL;
	return new;
}

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

t_queue	*create_queue()
{
	t_queue	*queue;
	
	queue = malloc(sizeof(t_queue));
	if (!queue)
		return NULL;
	ft_memset(queue, 0, sizeof(t_queue));
	return queue;
}