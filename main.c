/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 18:05:41 by pipolint          #+#    #+#             */
/*   Updated: 2026/06/08 18:05:42 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "ft_ls.h"

int main(int ac, char **av)
{
	// parse_cli(av);
	DIR				*dirp;
	t_ls			ls;
	char			*base_path;
	struct dirent	*entry;
	t_queue			*entry_queue;

	base_path = ".";
	dirp = opendir(base_path);
	if (dirp == NULL)
	{
		printf("error number: %d\n", errno);
		perror("opendir");
		return 1;
	}
	entry = readdir(dirp);
	entry_queue = create_queue();
	if (!entry_queue)
		return 1;
	int i = 0;
	while (entry)
	{
		entry = readdir(dirp);
		if (!entry)
			break ;
		printf("%d - %s\n", ++i, entry->d_name);
		t_queue_node* node = create_queue_node(entry);
		if (node)
			enqueue_back(entry_queue, node);
	}
	closedir(dirp);
	free_queue(entry_queue);
	(void)ls;
	(void)entry_queue;
	(void)ac;
	(void)av;
}
