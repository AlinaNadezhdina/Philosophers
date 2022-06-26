/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   detect_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcollen <wcollen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 12:25:58 by wcollen           #+#    #+#             */
/*   Updated: 2022/06/23 16:30:16 by wcollen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_negative_args(int count, char **arg)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (ft_atoi(arg[i]) <= 0)
			return (1);
		i++;
	}
	return (0);
}

int	error_msg(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(2, &str[i], 1);
		i++;
	}
	write(2, "\n", 1);
	return (1);
}

int	check_args(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (error_msg("Wrong arguments count!"));
	if (is_negative_args(argc - 1, &argv[1]))
		return (error_msg("Some argument isn't a positive int!"));
	return (0);
}
