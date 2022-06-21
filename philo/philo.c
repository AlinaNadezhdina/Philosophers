/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcollen <wcollen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 17:45:13 by wcollen           #+#    #+#             */
/*   Updated: 2022/06/21 17:30:31 by wcollen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eat(t_philo *philo)
{
	wait_for_fork(philo, philo->min_fork_id);
	pthread_mutex_lock(&philo->sets->forks[philo->min_fork_id].usage);
	print(philo, "has taken a fork");
	if (philo->sets->ph_count == 1)
	{
		while (!are_you_already_dead(philo->sets))
			usleep(1);
		pthread_mutex_unlock(&philo->sets->forks[philo->min_fork_id].usage);
		return ;
	}
	wait_for_fork(philo, philo->max_fork_id);
	pthread_mutex_lock(&philo->sets->forks[philo->max_fork_id].usage);
	print(philo, "has taken a fork");
	set_fork_last_taken_by(philo, philo->min_fork_id);
	set_fork_last_taken_by(philo, philo->max_fork_id);
	pthread_mutex_lock(&(philo->philo_access_mutex));
	philo->last_eating = get_time_now();
	pthread_mutex_unlock(&(philo->philo_access_mutex));
	print(philo, "is eating");
	smart_sleep(philo->sets->time_to_eat);
	pthread_mutex_lock(&(philo->philo_access_mutex));
	philo->ph_cnt_eating++;
	pthread_mutex_unlock(&(philo->philo_access_mutex));
	pthread_mutex_unlock(&philo->sets->forks[philo->max_fork_id].usage);
	pthread_mutex_unlock(&philo->sets->forks[philo->min_fork_id].usage);
}

void *philo_life(void *ph)
{
	t_philo *philo;
	long	ph_cnt_eating;
	long	total_eating;

	philo = (t_philo *)ph;
	while (1)
	{
		if (are_you_already_dead(philo->sets))
			return (NULL);
		philo_eat(philo);
		total_eating = philo->sets->cnt_eatings;
		pthread_mutex_lock(&(philo->philo_access_mutex));
		ph_cnt_eating = philo->ph_cnt_eating;
		pthread_mutex_unlock(&(philo->philo_access_mutex));		
		if (total_eating != -1 && ph_cnt_eating >= total_eating)
		{
			pthread_mutex_lock(&(philo->philo_access_mutex));
			philo->ph_ate_flag = 1;
			pthread_mutex_unlock(&(philo->philo_access_mutex));
		}
		if (are_you_already_dead(philo->sets))
			return (NULL);
		print(philo, "is sleeping");
		smart_sleep(philo->sets->time_to_sleep);
		print(philo, "is thinking");
	}
	return (NULL);
}

void	create_philo_threads(t_sets set)
{
	int	i;

	i = -1;
	while(++i < set.ph_count)
	{
		set.philos[i].last_eating = get_time_now();
		pthread_create(&(set.threads[i]), NULL, philo_life, (void *)&(set.philos[i]));
	}
}

int main(int argc, char **argv)
{
	t_sets	set;
	
	if (check_args(argc, argv, &set))
		return (1);
	if (init_types(&set))
		return (error_msg("Allocation memory error!"));
	fill_set(&set);
	create_philo_threads(set);
	pthread_create(&(set.th_live_cntrl), NULL, check_live, &set);
	make_join(&set);
	make_free_and_destroy(&set);
	return (0);
}
