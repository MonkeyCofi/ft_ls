/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 20:55:17 by pipolint          #+#    #+#             */
/*   Updated: 2026/06/14 15:36:34 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "ft_ls.h"

void    parse_options(char *str, t_ls *ls)
{
	int		i;
	size_t	*opt_count;

	i = 1;
	opt_count = &(ls->option_count);
	while (str[i])
	{
		if (str[i] == '-')
		{
			ls->exit_code = 2;
			return ;
		}
			// return error
		if (ft_strchr(OPTIONS, str[i]) && !ft_strchr(ls->options, str[i]))
			ls->options[(*opt_count)++] = str[i];
		i++;
	}
	ft_printf("The options are %s\n", ls->options);
}

/**
 * @brief mallocs and adds directories to ls->directories array
 * @param ls The ls struct that stores all program information
 * @param args The command line arguments
 * @param directory_indices An array of indices for args where each index represents a directory name
 * @param directory_count The amount of entries in the directory_indices array
 * @return Nothing
*/
void	add_directories(t_ls *ls, char **args, int *directory_indices)
{
	int	i;
	int	directory_count;

	directory_count = ls->directory_count;
	ls->directories = malloc(sizeof(char *) * (directory_count + 1));
	if (ls->directories == NULL)
	{
		ls->exit_code = 2;
		return ;
	}
	ls->directories[directory_count] = 0;
	i = 0;
	while (i < directory_count)
	{
		ls->directories[i] = ft_strdup(args[directory_indices[i]]);
		i++;
	}
}


/**
 * @brief Parses program's arguments and sets t_ls struct. if ls->exit code is 2, stops parsing and just exits the function
 * @param args The command line arguments
 * @param arg_count The count of the arguments
 * @return Nothing
*/
// void    parse_cli(char **args, int arg_count, t_ls *ls)
// {
// 	/*
// 		detect if "-" is present in every string
// 		if detected, parse the option
// 			set the option in the ls struct
// 	*/
// 	int i;
// 	int	*directory_indices;
	
// 	i = 1;
// 	directory_indices = malloc(sizeof(int) * arg_count);
// 	while (args[i])
// 	{
// 		if (ls->exit_code == 2)
// 			return ;
// 		if (args[i][0] == '-')
// 			parse_options(args[i], ls);
// 		else
// 			directory_indices[ls->directory_count++] = i;
// 		i++;
// 	}
// 	add_directories(ls, args, directory_indices);
// 	free(directory_indices);
// 	(void)arg_count;
// }

/**
 * @brief Parses the command line input and acccounts for options
 * @param args The command line arguments
 * @param arg_count The number of arguments
 * @param ls The main struct that contains ls informatino
 * @return Nothing
*/
void    parse_cli(char **args, int arg_count, t_ls *ls)
{
	/*
		detect if "-" is present in every string
		if detected, parse the option
			set the option in the ls struct
	*/
	int 			i;
	t_queue_node	*new;
	char			*dup_str;
	
	i = 1;
	while (args[i])
	{
		if (ls->exit_code == 2)
			return ;
		if (args[i][0] == '-')
			parse_options(args[i], ls);
		else
		{
			dup_str = ft_strdup(args[i]);
			new = create_queue_node(dup_str);
			enqueue_back(ls->directory_queue, new);
		}
		i++;
	}
	(void)arg_count;
}

void	print_directories(t_queue* directories)
{
	t_queue_node	*front;
	char			*str;

	front = peek_front(directories);
	while (front)
	{
		str = (char *)front->data;
		ft_printf("%s\n", str);
		pop_front(directories);
	}
}