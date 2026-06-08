#ifndef QUEUE_H
# define QUEUE_H

# include <stdlib.h>
# include "./libft/libft.h"

typedef struct s_queue_node
{
	void                *data;
	struct s_queue_node	*next;   
}   t_queue_node;

typedef struct t_queue
{
	t_queue_node	*front;
	t_queue_node	*rear;
}	t_queue;

t_queue			*create_queue();
void    		add_to_front(t_queue *head, t_queue_node *node);
t_queue_node	*create_queue_node(void *data);
void			free_queue(t_queue* queue);

#endif