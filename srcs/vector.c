/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 21:05:03 by pipolint          #+#    #+#             */
/*   Updated: 2026/06/15 19:53:07 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

/**
 * @brief Returns the data size depending on the type of data passed
 * @param data_type The type of data
 * @return The size of the data
*/
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

t_vector	*alloc_vector(t_data_type data_type, size_t element_count)
{
	size_t		memb_size;
	t_vector	*vector;

	memb_size = get_data_size(data_type);
	vector = malloc(sizeof(t_vector));
	if (!vector)
		return (NULL);
	vector->data_type = data_type;
	vector->size = 0;
	vector->capacity = element_count * memb_size;
	vector->data = malloc(vector->capacity);
	vector->member_size = memb_size;
	if (!vector->data)
		return NULL;
	ft_memset(vector->data, 0, vector->capacity);
	return vector;
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
	vector.data = malloc(vector.capacity);
	if (!vector.data)
	{
		vector.capacity = -1;
		vector.size = -1;
		return vector;
	}
	ft_memset(vector.data, 0, vector.capacity);
	vector.size = 0;
	vector.member_size = member_size;
	return vector;
}

char	*get_element(t_vector *vector, size_t index)
{
	// cant traverse through vector->data
	// you have to return vector->data_type * index and cast data as char *
	char	*data;
	char	*ptr;

	data = vector->data;
	if (vector->data_type == STRING || vector->data_type == POINTER)
	{
		ft_memcpy(&ptr, data + (index * vector->member_size), vector->member_size);
		return (ptr);		
	}
	return (data + (index * vector->member_size));
}

size_t	get_size(t_vector *vector)
{
	return (vector->size);
}

size_t	get_capacity(t_vector *vector)
{
	return (vector->capacity);
}

void		resize(t_vector* vector, size_t new_capacity)
{
	void	*new_data;

	new_data = malloc(new_capacity);
	if (!new_data)
	{
		vector->capacity = -1;
		vector->size = -1;
		return ;
	}
	ft_memmove(new_data, vector->data, vector->capacity);
	free(vector->data);
	vector->data = new_data;
	vector->capacity = new_capacity;
}

// if data type is string, 
void	add_to_vector(t_vector * vector, void *element, t_data_type data_type)
{

	// if sizeof(data_type) * vector->size exceeds vector->capacity, realloc
	if (vector->member_size * vector->size >= vector->capacity)
	{
		resize(vector, vector->capacity * 2);
		// new_cap = vector->capacity * 2;
		// new_data = malloc(new_cap);
		// ft_memmove(new_data, vector->data, vector->capacity);
		// free(vector->data);
		// vector->data = new_data;
		// vector->capacity = new_cap;
	}
	if (data_type == STRING || data_type == POINTER)
		ft_memmove(vector->data + (vector->size * vector->member_size), &element, vector->member_size);
	else
		ft_memmove(vector->data + (vector->size * vector->member_size), element, vector->member_size);
	vector->size++;
}

void	free_vector(t_vector* vector)
{
	free(vector->data);
	free(vector);
}