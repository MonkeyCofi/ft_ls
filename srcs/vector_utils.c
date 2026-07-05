/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 17:18:29 by pipolint          #+#    #+#             */
/*   Updated: 2026/06/27 13:47:51 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include <string.h>

/**
 * @brief Returns the element from vector at given index
 * @param vector The vector to fetch the element from
 * @param index The index of the element
 * @return The element as a char *
 */
char	*get_element(t_vector *vector, size_t index)
{
	// cant traverse through vector->data
	// you have to return vector->data_type * index and cast data as char *
	char	*data;
	char	*ptr;

	data = vector->data;
	if (vector->data_type == STRING || vector->data_type == POINTER || vector->data_type == DIRECTORY)
	{
		// ft_memmove(&ptr, data + (index * vector->member_size), vector->member_size);
		memmove(&ptr, data + (index * vector->member_size), vector->member_size);
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

/**
 * @brief Resizes the dynamic vector to the new_capacity size
 * @param vector The vector to resize
 * @param new_capacity The new capacity
 * @return Nothing
*/
bool		resize(t_vector* vector, size_t new_capacity)
{
	void	*new_data;

	new_data = malloc(new_capacity);
	if (!new_data)
	{
		return (false);
	}
	// ft_memmove(new_data, vector->data, vector->capacity);
	memmove(new_data, vector->data, vector->capacity);
	free(vector->data);
	vector->data = new_data;
	vector->capacity = new_capacity;
	return (true);
}

void	print_vector(t_vector *vector)
{
	size_t	i;

	i = 0;
	while (i < vector->size)
	{
		if (vector->data_type == STRING)
			ft_printf("%s ", get_element(vector, i));
		i++;
	}
}