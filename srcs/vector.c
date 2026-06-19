/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 21:05:03 by pipolint          #+#    #+#             */
/*   Updated: 2026/06/18 14:38:21 by pipolint         ###   ########.fr       */
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

/**
 * @brief Allocates space for a vector and initializes its results
 * @param data_type The type of data the vector will store
 * @param element_count The amount of elements to account for when reserving space
 * @return The allocated vector
*/
t_vector	*alloc_vector(t_data_type data_type, size_t element_count, bool should_free)
{
	size_t		memb_size;
	t_vector	*vector;

	memb_size = get_data_size(data_type);
	vector = malloc(sizeof(t_vector));
	if (!vector)
		return (NULL);
	vector->data_type = data_type;
	vector->size = 0;
	vector->should_free = should_free;
	if (element_count)
		vector->capacity = element_count * memb_size;
	else
		vector->capacity = memb_size;
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

/**
 * @brief Resizes vector if needed and pushes a new element
 * @param vector The vector to push into
 * @param element The element to push into the vector
 * @param data_type The data type of the element
 * @return Nothinng
 * @e
*/
void	add_to_vector(t_vector * vector, void *element, t_data_type data_type)
{
	if (vector->member_size * vector->size >= vector->capacity)
		resize(vector, vector->capacity * 2);
	if (data_type == STRING || data_type == POINTER)
		ft_memmove(vector->data + (vector->size * vector->member_size), &element, vector->member_size);
	else
		ft_memmove(vector->data + (vector->size * vector->member_size), element, vector->member_size);
	vector->size++;
}

/**
 * @brief Frees the vector and the elements inside it if they are allocated addresses
 * @param vector The vector to free
 * @return Nothing
*/
void	free_vector(t_vector* vector)
{
	size_t	i;

	i = 0;
	if (vector->should_free)
	{
		while (i < vector->size)
		{
			free((char *)get_element(vector, i));
			i++;
		}
	}
	free(vector->data);
	free(vector);
}
