/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 17:42:07 by ppontet           #+#    #+#             */
/*   Updated: 2025/02/22 17:42:58 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

static void	ft_bzero(void *s, size_t n);

/**
 * @brief Allocates a new memory zone, and set all bits to zero
 *
 * @param element_count number of elements
 * @param element_size size of each element
 * @return void* pointer to the new memory zone
 */
void	*ft_calloc(size_t element_count, size_t element_size)
{
	void	*pointer;
	size_t	nbr_element;

	if (element_size == 0 || element_count == 0)
		return (malloc(0));
	if (SIZE_MAX / element_size < element_count || SIZE_MAX
		/ element_count < element_size)
		return (NULL);
	nbr_element = element_size * element_count;
	pointer = malloc(nbr_element);
	if (pointer == NULL)
		return (NULL);
	ft_bzero(pointer, nbr_element);
	return (pointer);
}

/**
 * @brief Set at 0, the n first bytes at the pointer adress
 *
 * @param s pointer to the memory to set
 * @param n number of bytes to set at 0
 */
static void	ft_bzero(void *s, size_t n)
{
	unsigned char	*new_pointer;
	size_t			index;

	new_pointer = (unsigned char *)s;
	index = 0;
	while (n > 0)
	{
		new_pointer[index] = 0;
		index++;
		n--;
	}
	return ;
}
