/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mergesort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 20:43:18 by pipolint          #+#    #+#             */
/*   Updated: 2026/06/15 21:02:58 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
    this is a recursive function that would keep calling itself on subarrays
    of the main array
    
    It takes three parameters: the array, the starting index, and the ending index
    
*/
void    mergesort(void *array, int start, int end)
{
    int middle;

    if (start < end)
    {
        middle = (start + end) / 2;
        mergesort(start, middle);
        mergesort(middle + 1, end);
    }
}
