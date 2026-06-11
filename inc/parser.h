/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 21:49:09 by pipolint          #+#    #+#             */
/*   Updated: 2026/06/08 21:49:42 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef struct s_ls t_ls;

void    parse_options(char *str, t_ls *ls);
void    parse_cli(char **args, int arg_count, t_ls *ls);
void	add_directories(t_ls *ls, char **args, int *directory_indices, int directory_count);

#endif