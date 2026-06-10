/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 18:05:27 by pipolint          #+#    #+#             */
/*   Updated: 2026/06/08 20:49:44 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUEUE_H
# define QUEUE_H

# include "libft.h"
# include <stdbool.h>
# include <stdlib.h>

typedef struct s_queue_node
{
	void                *data;
	struct s_queue_node	*prev;
	struct s_queue_node	*next;
}   t_queue_node;

typedef struct t_queue
{
	t_queue_node	*front;
	t_queue_node	*rear;
}	t_queue;

t_queue			*create_queue();
void    		enqueue_front(t_queue *queue, t_queue_node *node);
void			enqueue_back(t_queue *queue, t_queue_node *node);
t_queue_node	*create_queue_node(void *data);
void			free_queue(t_queue* queue);
bool			is_empty(t_queue *queue);

#endif