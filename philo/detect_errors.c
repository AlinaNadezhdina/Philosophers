/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   detect_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcollen <wcollen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 12:25:58 by wcollen           #+#    #+#             */
/*   Updated: 2022/06/14 12:47:04 by wcollen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	 is_negative_args(int count, char **arg)
{
	int	i;

	i = 0;
	while(i < count)
	{
		if (ft_atoi(arg[i]) <= 0)
			return (1);
		i++;
	}
	return (0);
}

int	error_msg(char *str)
{
	int	i = 0;
	while(str[i])
	{
		write(2, &str[i], 1);
		i++;
	}
	write(2, "\n", 1);
	return (1);
}
