/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mergesort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 20:43:18 by pipolint          #+#    #+#             */
/*   Updated: 2026/06/17 01:18:36 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static void    mergeArrays(char **array, int start, int middle, int end)
{
	int     i;
	int     j;
	int     k;
	char    *temp;

	i = start;
	j = middle + 1;
	k = start + 1;
	printf("start %d middle %d end %d\n", start, middle, end);
	printf("left subarray: ");
	for (int t = start; t <= middle; t++)
		printf("%s ", array[t]);
	printf("\n");
	printf("right subarray: ");
	for (int t = j; t < end; t++)
		printf("%s ", array[t]);
	printf("\n");
	while (i <= middle && j < end)
	{
		printf("left %s right %s k %s\n", array[i], array[j], array[k]);
		if (ft_strncmp(array[i], array[k], -1) > 0)
		{
			temp = array[i];
			array[i] = array[k];
			array[k] = temp;
			k++;
		}
		if (ft_strncmp(array[i], array[j], -1) > 0)
		{
			temp = array[i];
			array[i] = array[j];
			array[j] = temp;
			j++;
		}
		i++;
	}
}

/*
	this is a recursive function that would keep calling itself on subarrays
	of the main array
	
	It takes three parameters: the array, the starting index, and the ending index
	
*/
void    mergesort_string(char **array, int start, int end)
{
	int     middle;

	middle = start + (end - start) / 2;
	if (start < end)
	{
		mergesort_string(array, start, middle);
		mergesort_string(array, middle + 1, end);
	}
	mergeArrays(array, start, middle, end);    // mergeArrays(array, element_size, start1, end1, start2, end2)
	for (int i = start; i <= end; i++)
	{
		printf("%s ", array[i]);
	}
	printf("\n");
}
