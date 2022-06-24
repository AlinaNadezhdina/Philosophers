/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   food_life_monitor_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcollen <wcollen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 17:02:26 by wcollen           #+#    #+#             */
/*   Updated: 2022/06/24 16:48:08 by wcollen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*food_monitor(void *param)
{
	t_sets	*set;
	int		i;
	
	set = param;
	i = 0;
	while (i < set->ph_count)
	{
		sem_wait(set->philos[i].eat_cnt_sem);
		i++;
	}
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

	while (1)
	{
		//когда фил поел сколько нужно и не умер, чтобы выйти из своего осн. потока жизни 
		//флаг death_flag_sem должен быть равен = 1, его выставляет поток-ждун фила wait_for_shutdown
		if(are_you_already_dead(set)) { 
			return (NULL);
		}
		if (check_die(philo))
		{
			print_die(philo);
			set_flag_death_value(set);
					
			sem_post(set->death_or_ate_sem);
			return (NULL);
		}
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

void	*wait_for_shutdown(void *param)
{
	t_philo	*philo;
	
	philo = param;
	sem_wait(philo->set->shutdown_signal_sem);
	set_flag_death_value(philo->set);
	return 0;
}
