/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 18:05:41 by pipolint          #+#    #+#             */
/*   Updated: 2026/06/11 23:15:44 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

// int main(int ac, char **av)
// {
// 	DIR				*dirp;
// 	t_ls			ls;
// 	char			*base_path;
// 	struct dirent	*entry;
// 	t_queue			*entry_queue;

// 	ft_memset(&ls, 0, sizeof(t_ls));
// 	base_path = ".";
// 	dirp = opendir(base_path);
// 	if (dirp == NULL)
// 	{
// 		printf("error number: %d\n", errno);
// 		perror("opendir");
// 		return 1;
// 	}
// 	entry = readdir(dirp);
// 	entry_queue = create_queue();
// 	if (!entry_queue)
// 		return 1;
// 	int i = 0;
// 	while (entry)
// 	{
// 		entry = readdir(dirp);
// 		if (!entry)
// 			break ;
// 		printf("%d - %s\n", ++i, entry->d_name);
// 		t_queue_node* node = create_queue_node(entry);
// 		if (node)
// 			enqueue_front(entry_queue, node);
// 			// enqueue_back(entry_queue, node);
// 	}
// 	print_queue_front(entry_queue);
// 	printf("\n");
// 	print_queue_back(entry_queue);
// 	closedir(dirp);
// 	free_queue(entry_queue);
// 	(void)ls;
// 	(void)entry_queue;
// 	(void)ac;
// 	(void)av;
// }

void	sort_entries(t_ls *ls)
{
	char	*options;
	bool	sort_by_time;

	options = ls->options;
	sort_by_time = ft_strchr(options, 't') != NULL;
}

void	exec_ls(t_ls *ls)
{
	sort_entries(&ls);
}

int main(int ac, char **av)
{
	t_ls	ls;

	ft_memset(&ls, 0, sizeof(t_ls));
	parse_cli(av, ac, &ls);
	exec_ls(&ls);
}