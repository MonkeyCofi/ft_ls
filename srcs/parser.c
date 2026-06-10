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
 * @brief mallocs and adds the directory string and adds it to the list of directories in the ls struct
 * @param directory The directory string to parse
 * @param ls The ls struct that stores all program information
 * @return Nothing
*/
void	add_directory(char *directory, t_ls *ls)
{
	
}


/**
 * @brief Parses program's arguments and sets t_ls struct. if ls->exit code is 2, stops parsing and just exits the function
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
		if (ls->exit_code == 2)
		{
			return ;
		}
		if (args[i][0] == '-')
			parse_options(args[i], ls);
		else
			add_directory(args[i], ls);
		i += 1;
	}
	(void)arg_count;
}