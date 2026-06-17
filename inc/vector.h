/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 20:46:53 by pipolint          #+#    #+#             */
/*   Updated: 2026/06/17 18:08:34 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

# include "libft.h"
# include <stdlib.h>

typedef enum s_data_type
{
	INTEGER,
	STRING,
	POINTER
}	t_data_type;

typedef struct	s_vector
{
	t_data_type	data_type;	// the type of data
	size_t		member_size;	// the size of each element
	size_t		size;		// the amount of elements in the vector
	size_t		capacity;	// the amount of space the vector takes
	void  		*data;		// an array of the data
}	t_vector;

t_vector	*alloc_vector(t_data_type data_type, size_t capacity);
t_vector	non_alloc_vector(t_data_type data_type, size_t size);
char		*get_element(t_vector *vector, size_t index);
void		add_to_vector(t_vector * vector, void *element, t_data_type data_type);
void		resize(t_vector* vector, size_t new_capacity);
void		print_vector(t_vector *vector);

#endif