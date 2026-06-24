/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 20:55:17 by pipolint          #+#    #+#             */
/*   Updated: 2026/06/24 20:45:24 by pipolint         ###   ########.fr       */
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
		if (str[i] == 'r')
			ls->reverse = true;
		else if (str[i] == 't')
			ls->time = true;
		else if (str[i] == 'l')
			ls->list = true;
		else if (str[i] == 'a')
			ls->all = true;
		else if (str[i] == 'R')
			ls->recursive = true;
		i++;
	}
}

/**
 * @brief Parses the command line input and acccounts for options
 * @param args The command line arguments
 * @param arg_count The number of arguments
 * @param ls The main struct that contains ls informatino
 * @return Nothing
*/
void    parse_cli(char **args, int arg_count, t_ls *ls)
{
	int 			i;
	t_queue_node	*new;
	char			*dup_str;
	
	i = 1;
	while (args[i])
	{
		if (ls->exit_code == 2)
			return ;
		if (args[i][0] == '-')
		{
			parse_options(args[i], ls);
		}
		else
		{
			dup_str = ft_strdup(args[i]);
			new = create_queue_node(dup_str, true);
			enqueue_back(ls->directory_queue, new);
		}
		i++;
	}
	// if the queue is empty, add the current directory to the queue
	if (is_empty(ls->directory_queue))
	{
		ls->no_args = true;
		dup_str = ft_strdup("./");
		new = create_queue_node(dup_str, true);
		enqueue_back(ls->directory_queue, new);
	}
	if (ls->no_args == true && ft_strchr(ls->options, 'R'))
		ls->no_args = false;
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
		front = front->next;
	}
}