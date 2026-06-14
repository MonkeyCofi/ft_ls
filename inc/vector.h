/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 20:46:53 by pipolint          #+#    #+#             */
/*   Updated: 2026/06/14 15:32:41 by pipolint         ###   ########.fr       */
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
	t_data_type	data_type;
	size_t		size;		// the amount of elements in the vector
	size_t		capacity;	// the amount of space the vector takes
	void  		*data;		// an array of the data
}	t_vector;

t_vector	*alloc_vector(t_data_type data_type, size_t capacity);
t_vector	non_alloc_vector(t_data_type data_type, size_t size);
char		*get_element(t_vector *vector, size_t index);

#endif