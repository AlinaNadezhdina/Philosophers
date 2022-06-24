/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   from_libft_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcollen <wcollen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 18:10:18 by wcollen           #+#    #+#             */
/*   Updated: 2022/06/24 18:14:28 by wcollen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

size_t	ft_strlen(const char *symb)
{
	unsigned long	length;

	length = 0;
	while (*symb)
	{
		length++;
		symb++;
	}
	return (length);
}

size_t	get_char_count(int num)
{
	size_t	char_count;

	char_count = 0;
	while (num != 0)
	{
		num = num / 10;
		char_count++;
	}
	return (char_count);
}

char	*ft_itoa(int n)
{
	size_t	char_count;
	char	*str;
	int		sign;

	sign = 2 * (n > 0) - 1;
	char_count = get_char_count(n) + (n <= 0);
	str = malloc(sizeof(char) * (char_count + 1));
	if (!str)
		return ((void *)0);
	if (n == 0)
	{	
		str[0] = '0';
		str[1] = '\0';
		return (str);
	}
	str[char_count] = '\0';
	while (n != 0)
	{
		str[--char_count] = (n % 10) * sign + '0';
		n = n / 10;
	}
	if (sign == -1)
		str[--char_count] = '-';
	return (str);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*result;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return ((void *)0);
	i = 0;
	result = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (result == (void *)0)
		return ((void *)0);
	while (s1[i] != '\0')
	{
		result[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
	{
		result[i + j] = s2[j];
		j++;
	}
	result[i + j] = '\0';
	return (result);
}