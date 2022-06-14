/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcollen <wcollen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 16:09:35 by wcollen           #+#    #+#             */
/*   Updated: 2022/05/30 16:10:26 by wcollen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	parse_args(char **argv, t_sets	*set)
{
	set->ph_count = ft_atoi(argv[1]);
	set->time_to_die = ft_atoi(argv[2]);
	set->time_to_eat  = ft_atoi(argv[3]);
	set->time_to_sleep  = ft_atoi(argv[4]);
	if(argv[5])
		set->cnt_eatings  = ft_atoi(argv[5]);
	else
		set->cnt_eatings  = -1;
	if (set->time_to_die == 0 || set->time_to_eat == 0 || set->time_to_sleep == 0)
		return (1);
	return (0);
}

int	check_args(int argc, char **argv, t_sets *set)
{
	if (argc < 5 || argc > 6)
		return (error_msg("Wrong arguments count!"));
	if (is_negative_args(argc - 1, &argv[1]))
		return (error_msg("Some argument isn't a positive int!"));
	if (parse_args(argv, set))
		return (error_msg("Wrong arguments value"));
	return (0);
}