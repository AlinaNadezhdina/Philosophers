/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   food_life_monitor_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcollen <wcollen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 17:02:26 by wcollen           #+#    #+#             */
/*   Updated: 2022/06/22 13:38:06 by wcollen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*food_monitor(void *set_arg)
{
	t_sets	*set;
	int		i;
	
	set = set_arg;
	i = 0;

	while (i < set->ph_count)
	{
		sem_wait(set->philos[i].eat_cnt_sem);
		i++;
	}
	printf("ALL ATE\n");

	sem_post(set->death_or_ate_sem);
	return (NULL);
}

int	check_die(t_philo *philo)
{
	long	last_eat_time;
	long	time;

	time = get_time_now();

	sem_wait(philo->ph_access_sem);
	last_eat_time = philo->last_eating;
	sem_post(philo->ph_access_sem);

	if (time - last_eat_time > philo->set->time_to_die)
		return (1);
	return (0);
}

void	*death_monitor(void *param)
{
	t_philo	*philo;
	long	time;
	t_sets	*set;

	philo = param;
	set = philo->set;
	time = get_time_now();

	// sem_t *flag_sem = sem_open("flag_death", 0);

	while (1)
	{
		if (check_die(philo))
		{
			printf("HERE!!!\n");
			print_die(philo);

			// sem_wait(flag_sem);
			set->flag_death = 1;
			// sem_post(flag_sem);
			
			sem_post(set->death_or_ate_sem);
			return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}

int	start_meal_count_thread(t_sets *set)
{
	pthread_t meal_thread;

	if (set->cnt_eatings != -1)
	{
		if (pthread_create(&meal_thread, NULL, food_monitor, set) != 0)
			return (1);
		pthread_detach(meal_thread);
	}
	return (0);
}