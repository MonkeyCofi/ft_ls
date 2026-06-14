/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 21:05:03 by pipolint          #+#    #+#             */
/*   Updated: 2026/06/14 15:32:49 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

size_t	get_data_size(t_data_type data_type)
{
	if (data_type == INTEGER)
		return sizeof(int);
	else if (data_type == STRING)
		return (sizeof(char *));
	else if (data_type == POINTER)
		return (sizeof(void *));
	return -1;
}

t_vector	*alloc_vector(t_data_type data_type, size_t size)
{
	size_t		member_size;
	t_vector	*vector;

	member_size = get_data_size(data_type);
	vector = malloc(sizeof(t_vector));
	if (!vector)
		return NULL;
	vector->capacity = member_size * size;
	vector->size = 0;
	vector->data = malloc(vector->capacity);
	if (!vector->data)
		return NULL;
	return (vector);
}

/**
 * @brief initializes data of a vector
 * @param data_type The type of data the vector will hold
 * @param size The amount of elements the vector is initially expected to hold
 * @return The initialized vector
*/
t_vector	non_alloc_vector(t_data_type data_type, size_t size)
{
	size_t		member_size;
	t_vector	vector;

	member_size = get_data_size(data_type);
	vector.capacity = member_size * size;
	vector.size = 0;
	vector.data = malloc(vector.capacity);
	if (!vector.data)
	{
		vector.capacity = -1;
		vector.size = -1;
	}
	return vector;
}

char	*get_element(t_vector *vector, size_t index)
{
	// cant traverse through vector->data
	// you have to return vector->data_type * index and cast data as char *
	char	*ptr;

	ptr = vector->data;
	return (ptr + (index * get_data_size(vector->data_type)));
}

size_t	get_size(t_vector *vector)
{
	return (vector->size);
}

size_t	get_capacity(t_vector *vector)
{
	return (vector->capacity);
}

void	add_to_vector(t_vector * vector, void *element, t_data_type data_type)
{
	/*
		add the element to vector->data[size]
		if the size of the vector is higher than the capacity, remalloc
			and double the memory the vector takes
		size is the number of members and capacity is the number of bytes
			the vector takes. if size * data_type is >= capacity, remalloc
	*/
	if ((vector->size * vector->data_type) + data_type >= vector->capacity)
	{
		void	*new_data = malloc(vector->capacity * 2);
		ft_memmove(new_data, vector->data, vector->capacity);
	}
	(void)element;
}