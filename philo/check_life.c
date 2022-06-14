/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcollen <wcollen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 12:44:40 by wcollen           #+#    #+#             */
/*   Updated: 2022/06/14 12:45:52 by wcollen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_all_ph_ate(t_sets *set)
{
	int	i;
	int	ate_flag;

	i = 0;
	if (set->cnt_eatings == -1)
		return (0);
	while (i < set->ph_count)
	{
		pthread_mutex_lock(&(set->philos[i].philo_access_mutex));
		ate_flag = set->philos[i].ph_ate_flag;
		pthread_mutex_unlock(&(set->philos[i].philo_access_mutex));
		if (ate_flag == 0)
			return (0);
		i++;
	}
	return (1);
}

int	check_die(t_philo *philo)
{
	long	time;
	int		ate_flag;
	long	last_eat_time;

	pthread_mutex_lock(&(philo->philo_access_mutex));
	ate_flag = philo->ph_ate_flag;
	pthread_mutex_unlock(&(philo->philo_access_mutex));
	if (ate_flag == 1)
		return (0);
	time = get_time_now();
	pthread_mutex_lock(&(philo->philo_access_mutex));
	last_eat_time = philo->last_eating;
	pthread_mutex_unlock(&(philo->philo_access_mutex));
	if ((time - last_eat_time) > philo->sets->time_to_die)
	{
		return (1);
	}
	return (0);
}

void	*check_live(void *param)
{
	t_sets *set = param;
	int	i;

	while (1)
	{
		i = 0;
		while	(i < set->ph_count)
		{
			if (check_die(&(set->philos[i])))
			{
				pthread_mutex_lock(&(set->flag_deth_mutex));
				set->flag_deth = 1;
				pthread_mutex_unlock(&(set->flag_deth_mutex));
				print_die(&(set->philos[i]));
				return (NULL);
			}
			i++;
		}
		if (check_all_ph_ate(set))
		{
			return (NULL);
		}
	}
	return (NULL);
}