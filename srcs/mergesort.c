/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mergesort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 20:43:18 by pipolint          #+#    #+#             */
/*   Updated: 2026/06/18 17:59:45 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft.h"
#include <stdio.h>
#include <string.h>
#include <dirent.h>

// Merges two sorted subarrays into a temporary array, then copies back.
// Left subarray is array[start..middle]
// Right subarray is array[middle+1..end]
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

/*
	this is a recursive function that would keep calling itself on subarrays
	of the main array
	
	It takes three parameters: the array, the starting index, and the ending index
	
*/
void    mergesort_string(char **array, int start, int end)
{
	int     middle;
	
	if (end - start <= 1)   // base case: 0 or 1 element
	   return;
	middle = start + (end - start) / 2;
	mergesort_string(array, start, middle);
	mergesort_string(array, middle, end);
	merge(array, start, middle, end); 
	// mergeArrays(array, start, middle, end);    // mergeArrays(array, element_size, start1, end1, start2, end2)
}

// Merges two sorted subarrays into a temporary array, then copies back.
// Left subarray is array[start..middle]
// Right subarray is array[middle+1..end]
static void merger_dirent(struct dirent **array, int start, int middle, int end)
{
    int i;
	int	j;
	int	k;
	struct dirent **left_arr = calloc(middle - start, sizeof(struct dirent *));
	struct dirent **right_arr = calloc(end - middle, sizeof(struct dirent *));

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
        if (ft_strncmp(left_arr[i]->d_name, right_arr[j]->d_name, -1) <= 0)
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

/*
	this is a recursive function that would keep calling itself on subarrays
	of the main array
	
	It takes three parameters: the array, the starting index, and the ending index
	
*/
void    merge_dirent(struct dirent **entries, int start, int end)
{
	int     middle;
	
	if (end - start <= 1)   // base case: 0 or 1 element
	   return;
	middle = start + (end - start) / 2;
	merge_dirent(entries, start, middle);
	merge_dirent(entries, middle, end);
	merger_dirent(entries, start, middle, end); 
	// mergeArrays(array, start, middle, end);    // mergeArrays(array, element_size, start1, end1, start2, end2)
}

static void merger_dir_ptrs(t_dir_ptr **array, int start, int middle, int end)
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
	merger_dir_ptrs(dir_ptrs, start, middle, end); 
	// mergeArrays(array, start, middle, end);    // mergeArrays(array, element_size, start1, end1, start2, end2)
}