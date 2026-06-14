/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 18:05:27 by pipolint          #+#    #+#             */
/*   Updated: 2026/06/14 15:36:45 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUEUE_H
# define QUEUE_H

# include "libft.h"
# include <stdbool.h>
# include <stdlib.h>
# include <dirent.h>

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

/* Primary queue functions */
t_queue			*create_queue();
void    		enqueue_front(t_queue *queue, t_queue_node *node);
void			enqueue_back(t_queue *queue, t_queue_node *node);
t_queue_node	*create_queue_node(void *data);
void			free_queue(t_queue* queue);
bool			is_empty(t_queue *queue);
size_t			queue_size(t_queue *queue);
t_queue_node	*peek_front(t_queue *queue);
t_queue_node	*peek_rear(t_queue *queue);
void			pop_front(t_queue* queue);
void			pop_back(t_queue *queue);

/* Helper functions */
void			print_queue_front(t_queue *queue);
void			print_queue_back(t_queue *queue);
void			print_directories(t_queue* directories);

#endif