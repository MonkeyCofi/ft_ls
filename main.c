#include <stdio.h>
#include <dirent.h>
#include <errno.h>
#include "queue.h"
#include "structs.h"
#include <unistd.h>

#define OPTIONS "lRart"

/*
	parse the command line arguments
	check for a prefix - in every string. if present, check if it is one of the options
*/
void parse_cli(const char **av)
{
	int	i;
	int	j;

	i = 0;
	while (av[i])
	{
		j = 0;
		if (av[i][0] == '-')
		{
			j += 1;
			// check if the current character is any of the options
			if (ft_strchr(OPTIONS, av[i][j]))
			{
				// add option
			}
		}
	}
}

/*
	if there are parameters given, list every file within the given parameters
	else if there is no parameter given, list every file in the current directory
*/
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
		// if (entry->d_name[0] == '.')
		// {
		// 	entry = readdir(dirp);
		// 	continue ;
		// }
		entry = readdir(dirp);
		if (!entry)
			break ;
		printf("%d - %s\n", ++i, entry->d_name);
		t_queue_node* node = create_queue_node(entry);
		if (node)
			// add_to_front(entry_queue, node);
			enqueue_back(entry_queue, node);
	}
	closedir(dirp);
	free_queue(entry_queue);
	(void)ls;
	(void)entry_queue;
	(void)ac;
	(void)av;
}
