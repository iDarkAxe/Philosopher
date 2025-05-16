/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 17:42:07 by ppontet           #+#    #+#             */
/*   Updated: 2025/05/16 12:36:43 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

void	*ft_calloc(size_t element_count, size_t element_size);
void	ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *destination, const void *source, size_t size);
size_t	ft_strlen(const char *str);

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
void	ft_bzero(void *s, size_t n)
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

/**
 * @brief Set a memory zone with a value, count times
 *
 * @param destination memory zone to paste
 * @param source memory zone to copy
 * @param size number of times to set the value
 * @return void* pointer to the memory zone
 */
void	*ft_memcpy(void *destination, const void *source, size_t size)
{
	char		*dest_pointer;
	const char	*src_pointer;
	size_t		index;

	dest_pointer = (char *)destination;
	src_pointer = (const char *)source;
	index = 0;
	if (destination == source)
		return (destination);
	while (size > 0)
	{
		dest_pointer[index] = (char)src_pointer[index];
		index++;
		size--;
	}
	return (destination);
}

/**
 * @brief Count the number of characters in a string
 * 
 * @param str string to count
 * @return size_t 
 */
size_t	ft_strlen(const char *str)
{
	size_t	count;

	if (str == NULL)
		return (0);
	count = 0;
	while (str[count] != '\0')
		count++;
	return (count);
}
