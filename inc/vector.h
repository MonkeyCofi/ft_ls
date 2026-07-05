/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 20:46:53 by pipolint          #+#    #+#             */
/*   Updated: 2026/07/05 15:35:06 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

# include "libft.h"
# include <stdbool.h>
# include <stdlib.h>
# include <sys/types.h>
# include <dirent.h>

typedef struct s_dir_ptr
{
	char	*directory_name;
	size_t	longest_filename;
	size_t	longest_filesize;
	size_t	longest_hlsize;
	size_t	longest_owner;
	size_t	longest_group;
	DIR		*directory;
}	t_dir_ptr;

typedef enum s_data_type
{
	INTEGER,
	STRING,
	POINTER,
	DIRECTORY
}	t_data_type;

typedef struct	s_vector
{
	bool		should_free;
	t_data_type	data_type;	// the type of data
	size_t		member_size;	// the size of each element
	size_t		size;		// the amount of elements in the vector
	size_t		capacity;	// the amount of space the vector takes
	void  		*data;		// an array of the data
}	t_vector;

t_vector	*alloc_vector(t_data_type data_type, size_t element_count, bool should_free);
t_vector	non_alloc_vector(t_data_type data_type, size_t size);
char		*get_element(t_vector *vector, size_t index);
bool		add_to_vector(t_vector * vector, void *element, t_data_type data_type);
bool		resize(t_vector* vector, size_t new_capacity);
void		print_vector(t_vector *vector);
void		free_vector(t_vector* vector);

#endif