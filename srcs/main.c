/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 18:05:41 by pipolint          #+#    #+#             */
/*   Updated: 2026/06/22 16:15:21 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"


void	initialize_ls(t_ls *ls)
{
	ft_memset(ls, 0, sizeof(t_ls));
	ls->directories = alloc_vector(STRING, 20, true);
	ls->directory_queue = create_queue();
	ls->dir_entries = NULL;
}

void	add_dirent_entries(t_ls *ls, t_vector *dirent_entries, t_dir_ptr* current_dir)
{
	struct dirent	*entry;

	entry = readdir(current_dir->directory);
	while (entry)
	{
		if (entry->d_name[0] == '.' && !ft_strchr(ls->options, 'a'))
		{
			entry = readdir(current_dir->directory);
			continue;
		}
		add_to_vector(dirent_entries, entry, POINTER);
		check_longest(ls, current_dir, entry);
		entry = readdir(current_dir->directory);
	}
}

void	traverse_entries(t_ls *ls, t_dir_ptr *current_dir, t_vector *entries, t_vector *directories)
{
	size_t			i;
	char			*path;
	struct stat		st;
	struct dirent	*elem;
	size_t			col_written;

	i = 0;
	col_written = 0;
	// for (size_t j = 0; j < entries->size; j++)
	while (i < entries->size);
	{
		elem = (struct dirent *)get_element(entries, j);
		path = build_path(ls, current_dir->directory_name, elem);
		lstat(path, &st);
		if (ft_strchr(ls->options, 'R'))
		{
			if (S_ISDIR(st.st_mode))
			{
				if (ft_strncmp(elem->d_name, ".", -1) != 0 && ft_strncmp(elem->d_name, "..", -1) != 0)
					add_directory(path, directories);
			}
		}
		lstat(path, &st);
		if (ft_strchr(ls->options, 'l'))
			print_list(&st, current_dir);
		if (col_written > w.ws_col)
		{
			col_written = 0;
			ft_printf("\n");
		}
		if (S_ISDIR(st.st_mode))
			col_written += ft_printf("\e[1;34m%-*s\e[0m", current_dir->longest_filename, elem->d_name);
		else if (st.st_mode & S_IXUSR)
			col_written += ft_printf("\e[1;32m%-*s\e[0m", current_dir->longest_filename, elem->d_name);
		else
			col_written += ft_printf("\e[m%-*s\e[0m", current_dir->longest_filename, elem->d_name);
		ft_printf("  ");
		if (ft_strchr(ls->options, 'l'))
		{
			ft_printf("\n");
			col_written = 0;
		}
		// free(path);
	}
}

/**
 * @param ls The ls struct
 * @param pointers Vector cointaing DIR *
 */
void open_directories(t_ls *ls, t_vector *directories_ptrs)
{
	/*
		every directory has its own entries
		within each directory, its own entries has their own largest size and largest filename
		
	*/
	char			*path;
	size_t			col_written;
	t_vector		*rec_directories;
	struct stat		st;
	struct winsize	w;

	if (directories_ptrs->size == 0)
		return ;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	rec_directories = NULL;	// a vector of directories in the current directory
	col_written = 0;
	for (size_t i = 0; i < directories_ptrs->size; i++)
	{
		t_vector *entries = alloc_vector(POINTER, 1, false);
		t_dir_ptr *ptr = (t_dir_ptr *)get_element(directories_ptrs, i);	// returns the t_dir_ptr object which contains directory name and DIR *
		DIR *dir = ptr->directory;
		if (!dir)
		{
			perror("opendir");
			exit(1);
		}
		add_dirent_entries(ls, entries, ptr);	// loops through every entry in the current directory and adds them to entries vector
		merge_dirent(entries->data, 0, entries->size);
		ft_printf("%s:\n", ptr->directory_name);
		rec_directories = alloc_vector(POINTER, 1, true);
		for (size_t j = 0; j < entries->size; j++)
		{
			struct dirent *elem = (struct dirent *)get_element(entries, j);
			path = build_path(ls, ptr->directory_name, elem);
			lstat(path, &st);
			if (ft_strchr(ls->options, 'R'))
			{
				if (S_ISDIR(st.st_mode))
				{
					if (ft_strncmp(elem->d_name, ".", -1) != 0 && ft_strncmp(elem->d_name, "..", -1) != 0)
						add_directory(path, rec_directories);
				}
			}
			lstat(path, &st);
			if (ft_strchr(ls->options, 'l'))
				print_list(&st, ptr);
			if (col_written > w.ws_col)
			{
				col_written = 0;
				ft_printf("\n");
			}
			if (S_ISDIR(st.st_mode))
				col_written += ft_printf("\e[1;34m%-*s\e[0m", ptr->longest_filename, elem->d_name);
			else if (st.st_mode & S_IXUSR)
				col_written += ft_printf("\e[1;32m%-*s\e[0m", ptr->longest_filename, elem->d_name);
			else
				col_written += ft_printf("\e[m%-*s\e[0m", ptr->longest_filename, elem->d_name);
			ft_printf("  ");
			if (ft_strchr(ls->options, 'l'))
			{
				ft_printf("\n");
				col_written = 0;
			}
			// free(path);
		}
		ft_printf("\n\n");
		open_directories(ls, rec_directories);
		free_vector(entries);
		free_vector(rec_directories);
		closedir(dir);
		col_written = 0;
	}
}


void open_directories_reverse(t_ls *ls, t_vector *pointers)
{
	t_vector	*rec_directories;

	rec_directories = NULL;
	if (!pointers || pointers->size == 0)
		return ;
	for (size_t i = pointers->size; i-- > 0;)
	{
		t_vector *entries = alloc_vector(POINTER, 1, false);
		t_dir_ptr *ptr = (t_dir_ptr *)get_element(pointers, i);
		// DIR *dir = (DIR *)get_element(pointers, i);
		DIR *dir = ptr->directory;
		if (!dir)
		{
			printf("no dir\n");
			exit(1);
		}
		struct dirent* entry = readdir(dir);
		while (entry)
		{
			if (entry->d_name[0] == '.' && !ft_strchr(ls->options, 'a'))
			{
				entry = readdir(dir);
				continue;
			}
			add_to_vector(entries, entry, POINTER);
			entry = readdir(dir);
		}
		printf("%s:\n", ptr->directory_name);
		merge_dirent(entries->data, 0, entries->size);
		rec_directories = alloc_vector(POINTER, 1, false);
		for (size_t j = entries->size; j-- > 0;)
		{
			struct dirent *elem = (struct dirent *)get_element(entries, j);
			char *parent_dir = ptr->directory_name;
			char *parent_dir_slash = NULL;
			if (ft_strncmp(parent_dir, "./", -1) != 0)
				parent_dir_slash = ft_strjoin(parent_dir, "/");
			else
				parent_dir_slash = parent_dir;
			char *joined_dir = ft_strjoin(parent_dir_slash, elem->d_name);
			struct stat st;
			lstat(joined_dir, &st);
			if (ft_strchr(ls->options, 'R'))
			{
				if (S_ISDIR(st.st_mode))
				{
					// Avoid recursion on "." and ".."
					if (ft_strncmp(elem->d_name, ".", -1) != 0 && ft_strncmp(elem->d_name, "..", -1) != 0)
					{
						DIR *open_dir = opendir(joined_dir);
						if (open_dir)
						{
							t_dir_ptr *rec_ptr = malloc(sizeof(t_dir_ptr));
							rec_ptr->directory = open_dir;
							rec_ptr->directory_name = ft_strdup(joined_dir); // Use a copy
							add_to_vector(rec_directories, rec_ptr, POINTER);
						}
					}
				}
			}
			if (ft_strchr(ls->options, 'l'))
			{
				mode_t	perms = st.st_mode;
				struct passwd *pw = getpwuid(st.st_uid);
				struct group *grp = getgrgid(st.st_gid);
				// print the permissions
				ft_printf("%c", S_ISDIR(st.st_mode) ? 'd' : '-');
				ft_printf("%c%c%c", perms & S_IRUSR ? 'r' : '-', perms & S_IWUSR ? 'w' : '-', perms & S_IXUSR ? 'x' : '-');
				ft_printf("%c%c%c", perms & S_IRGRP ? 'r' : '-', perms & S_IWGRP ? 'w' : '-', perms & S_IXGRP ? 'x' : '-');
				ft_printf("%c%c%c ", perms & S_IROTH ? 'r' : '-', perms & S_IWOTH ? 'w' : '-', perms & S_IXOTH ? 'x' : '-');
				ft_printf("%ld ", st.st_nlink);
				ft_printf("%s ", grp->gr_name);
				ft_printf("%s ", pw->pw_name);
				ft_printf("%ld ", st.st_size);
				time_t time = st.st_mtime;
				struct tm now_t = *localtime(&time);
				(void)now_t;
				// ft_printf("%ld ", );
			}
			if (S_ISDIR(st.st_mode))
				ft_printf("\e[1;34m%s\e[0m  ", elem->d_name);
			else if (st.st_mode & S_IXUSR)
				ft_printf("\e[1;32m%s\e[0m  ", elem->d_name);
			else
				ft_printf("\e[m%s\e[0m  ", elem->d_name);
			if (ft_strchr(ls->options, 'l'))
				ft_printf("\n");
		}
		ft_printf("\n%c", (i != pointers->size) ? '\n' : 0);
		open_directories(ls, rec_directories);
		free_vector(entries);
		closedir(dir);
	}
}

int main(int ac, char **av)
{
	t_ls			ls;
	t_vector		*directories;
	struct stat		st;
	t_queue_node	*front;

	initialize_ls(&ls);
	parse_cli(av, ac, &ls);
	front = peek_front(ls.directory_queue);
	while (front)
	{
		lstat(front->data, &st);
		if (S_ISDIR(st.st_mode))
		{
			char *str = ft_strdup(front->data);
			if (!str)
				return (1);
			add_to_vector(ls.directories, str, STRING);
		}
		pop_front(ls.directory_queue);
		front = peek_front(ls.directory_queue);
	}
	mergesort_string(ls.directories->data, 0, ls.directories->size);
	directories = alloc_vector(POINTER, ls.directories->size, true);
	add_arg_directories(&ls, directories);
	if (ft_strchr(ls.options, 'r') == NULL)
		open_directories(&ls, directories);
	else
		open_directories_reverse(&ls, directories);
	free_queue(ls.directory_queue);
	free_vector(directories);
	free_vector(ls.directories);
}