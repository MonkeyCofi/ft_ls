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
	/*
		if the queue has a rear node:
			set node->prev to queue->rear
			set queue->rear to node
		else if the queue does not have a rear node
			set queue->rear to node
			set queue->front to node
	*/
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