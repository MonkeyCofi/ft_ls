/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mergesort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 20:43:18 by pipolint          #+#    #+#             */
/*   Updated: 2026/06/26 14:51:12 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include "ft_ls.h"
#include "libft.h"
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

static void merge(char **array, int start, int middle, int end)
{
	int i;
	int	j;
	int	k;
	char **left_arr = calloc(middle - start, sizeof(char *));
	char **right_arr = calloc(end - middle, sizeof(char *));

	if (!left_arr || !right_arr)
	{
		free(left_arr);
		free(right_arr);
		return;
	}
	for (i = 0; i < middle - start; i++)
		left_arr[i] = array[start + i];
	for (j = 0; j < end - middle; j++)
		right_arr[j] = array[middle + j];
	i = 0;
	j = 0;
	k = start;
	while (i < middle - start && j < end - middle)
	{
		if (ft_strncmp(left_arr[i], right_arr[j], -1) <= 0)
			array[k] = left_arr[i++];
		else
			array[k] = right_arr[j++];
		k++;
	}
	while (i < middle - start)
		array[k++] = left_arr[i++];
	while (j < end - middle)
		array[k++] = right_arr[j++];
	free(left_arr);
	free(right_arr);
}

void    mergesort_string(char **array, int start, int end)
{
	int     middle;
	
	if (end - start <= 1)   // base case: 0 or 1 element
	   return;
	middle = start + (end - start) / 2;
	mergesort_string(array, start, middle);
	mergesort_string(array, middle, end);
	merge(array, start, middle, end); 
}

static void merger_dirent(struct dirent **array, int start, int middle, int end, bool time)
{
	int i;
	int	j;
	int	k;
	char **left_arr = calloc(middle - start, sizeof(char *));
	char **right_arr = calloc(end - middle, sizeof(char *));
	struct stat	left;
	struct stat	right;

	if (!left_arr || !right_arr)
	{
		free(left_arr);
		free(right_arr);
		return;
	}
	for (i = 0; i < middle - start; i++)
		left_arr[i] = array[start + i];
	for (j = 0; j < end - middle; j++)
		right_arr[j] = array[middle + j];
	i = 0;
	j = 0;
	k = start;
	while (i < middle - start && j < end - middle)
	{
		lstat(left_arr[i], &left);
		lstat(right_arr[j], &right);
		if (time)
		{
			if (left.st_mtime > right.st_mtime)
				array[k] = left_arr[i++];
			else
				array[k] = right_arr[j++];
		}
		else
		{
			if (ft_strncmp(left_arr[i], right_arr[j], -1) <= 0)
				array[k] = left_arr[i++];
			else
				array[k] = right_arr[j++];
		}
		k++;
	}
	while (i < middle - start)
		array[k++] = left_arr[i++];
	while (j < end - middle)
		array[k++] = right_arr[j++];
	free(left_arr);
	free(right_arr);
}

/*
	this is a recursive function that would keep calling itself on subarrays
	of the main array
	
	It takes three parameters: the array, the starting index, and the ending index
	
*/
void    merge_dirent(struct dirent **entries, int start, int end, bool time_sort)
{
	int     middle;
	
	if (end - start <= 1)   // base case: 0 or 1 element
	   return;
	middle = start + (end - start) / 2;
	merge_dirent(entries, start, middle, time_sort);
	merge_dirent(entries, middle, end, time_sort);
	merger_dirent(entries, start, middle, end, time_sort); 
}

static void merge_dir_vectors(t_dir_ptr **array, int start, int middle, int end)
{
	int i;
	int	j;
	int	k;
	t_dir_ptr **left_arr = calloc(middle - start, sizeof(t_dir_ptr *));
	t_dir_ptr **right_arr = calloc(end - middle, sizeof(t_dir_ptr *));

	if (!left_arr || !right_arr)
	{
		free(left_arr);
		free(right_arr);
		return;
	}
	for (i = 0; i < middle - start; i++)
		left_arr[i] = array[start + i];
	for (j = 0; j < end - middle; j++)
		right_arr[j] = array[middle + j];
	i = 0;
	j = 0;
	k = start;
	while (i < middle - start && j < end - middle)
	{
		if (ft_strncmp(left_arr[i]->directory_name, right_arr[j]->directory_name, -1) <= 0)
			array[k] = left_arr[i++];
		else
			array[k] = right_arr[j++];
		k++;
	}
	while (i < middle - start)
		array[k++] = left_arr[i++];
	while (j < end - middle)
		array[k++] = right_arr[j++];
	free(left_arr);
	free(right_arr);
}

void    merge_directories(t_dir_ptr **dir_ptrs, int start, int end)
{
	int     middle;
	
	if (end - start <= 1)   // base case: 0 or 1 element
	   return;
	middle = start + (end - start) / 2;
	merge_directories(dir_ptrs, start, middle);
	merge_directories(dir_ptrs, middle, end);
	merge_dir_vectors(dir_ptrs, start, middle, end);
}