/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 20:55:17 by pipolint          #+#    #+#             */
/*   Updated: 2026/06/08 21:51:52 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void    parse_options(char *str, t_ls *ls)
{
	int	i;

	i = 1;
	while (str[i])
	{
		if (ft_strchr(OPTIONS, str[i]))
		{
			
		}
		i++;
	}
}


/**
 * @brief Parses program's arguments and sets t_ls struct
 * @param args The command line arguments
 * @param arg_count The count of the arguments
 * @return Nothing
*/
void    parse_cli(char **args, int arg_count, t_ls *ls)
{
	/*
		detect if "-" is present in every string
		if detected, parse the option
			set the option in the ls struct
	*/
	int i;
	
	i = 0;
	while (args[i])
	{
		if (args[i][0] == '-')
		{
			parse_options(args[i], ls);
		}
	}
}