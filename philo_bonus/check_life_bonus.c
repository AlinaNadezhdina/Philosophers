/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_life_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcollen <wcollen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 17:02:26 by wcollen           #+#    #+#             */
/*   Updated: 2022/06/16 13:20:17 by wcollen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	check_all_ph_ate(t_philo *philo)
{
	int		i;
	int		ate_flag;
	t_sets *set;

	i = 0;
	set = philo->set;
	if (set->cnt_eatings == -1)
		return (0);
	while (i < set->ph_count)
	{
		sem_wait(philo->ph_access_sem);
		ate_flag = philo->ph_ate_flag;
		sem_post(philo->ph_access_sem);
		if (ate_flag == 0)
			return (0);
		i++;
	}
	return (1);
}

int	check_die(t_philo *philo)
{
	int		ate_flag;
	long	last_eat_time;
	long	time;

	sem_wait(philo->ph_access_sem);
	ate_flag = philo->ph_ate_flag;
	sem_post(philo->ph_access_sem);
	if (ate_flag)
		return (0);
	time = get_time_now();
	sem_wait(philo->ph_access_sem);
	last_eat_time = philo->last_eating;
	sem_post(philo->ph_access_sem);
	if (time - last_eat_time > philo->set->time_to_die)
		return (1);
	return (0);
}

void	set_death_flag(t_sets *set)
{
	sem_wait(set->death_flag_sem);
	set->flag_deth = 1;
	sem_post(set->death_sem);
}

void	*check_life(void *param)
{
	t_philo	*philo;
	long	last_eat_time;
	long	time;
	t_sets	*set;

	philo = param;
	set = philo->set;
	time = get_time_now();
	last_eat_time = philo->last_eating;
	while (1)
	{
		if (check_die(philo))
		{
			set_death_flag(philo->set);
			print_die(philo);
			return (NULL);
		}
		if (check_all_ph_ate(philo))
		{
			set_death_flag(philo->set);
			return (NULL);
		}
	}
	return (NULL);
}