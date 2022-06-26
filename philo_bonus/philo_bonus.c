/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcollen <wcollen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 11:06:38 by wcollen           #+#    #+#             */
/*   Updated: 2022/06/25 23:37:11 by wcollen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	philo_eat(t_philo *philo)
{
	int		current_index;
	int		passed_index;
	long	time;

	if (single_philo_must_die(philo))
		return ;
	current_index = philo->num - 1;
	sem_wait(philo->set->queue_sems[current_index]);
	sem_wait(philo->set->forks_sem);
	print(philo, "has taken a fork");
	sem_wait(philo->set->forks_sem);
	print(philo, "has taken a fork");
	time = get_time_now();
	sem_wait(philo->ph_access_sem);
	philo->last_eating = time;
	sem_post(philo->ph_access_sem);
	print(philo, "is eating");
	usleep(philo->set->time_to_eat * 1000);
	sem_wait(philo->ph_access_sem);
	philo->ph_cnt_eating++;
	sem_post(philo->ph_access_sem);
	sem_post(philo->set->forks_sem);
	sem_post(philo->set->forks_sem);
	passed_index = (current_index + 1) % philo->set->ph_count;
	sem_post(philo->set->queue_sems[passed_index]);
}

void	philo_life(t_philo *philo)
{
	long	ph_cnt_eating;
	int		already_post_flag;

	already_post_flag = 0;
	while (1)
	{
		if (not_count_food_if_ph_died(philo, already_post_flag))
			return ;
		philo_eat(philo);
		sem_wait(philo->ph_access_sem);
		ph_cnt_eating = philo->ph_cnt_eating;
		sem_post(philo->ph_access_sem);
		if (philo->set->cnt_eatings != -1 && ph_cnt_eating
			>= philo->set->cnt_eatings && already_post_flag == 0)
		{			
			sem_post(philo->eat_cnt_sem);
			already_post_flag = 1;
		}
		if (not_count_food_if_ph_died(philo, already_post_flag))
			return ;
		print(philo, "is sleeping");
		usleep(philo->set->time_to_sleep * 1000);
		print(philo, "is thinking");
	}
	return ;
}

int	start_philo_life_process(t_philo *philo)
{
	philo->last_eating = get_time_now();
	if (pthread_create(&(philo->set->th_live_cntrl), NULL,
			death_monitor, philo) != 0)
		return (1);
	if (pthread_create(&(philo->set->shutdown_wait), NULL,
			wait_for_shutdown, philo) != 0)
		return (1);
	pthread_detach(philo->set->th_live_cntrl);
	pthread_detach(philo->set->shutdown_wait);
	philo_life(philo);
	return (0);
}

int	create_processes(t_sets *set)
{
	int		i;
	t_philo	*philos;

	philos = set->philos;
	i = -1;
	while (++i < set->ph_count)
	{
		philos[i].pid = fork();
		if (philos[i].pid == -1)
			return (error_msg("fork creation error"));
		if (philos[i].pid == 0)
		{
			sem_wait(set->launch_sem);
			start_philo_life_process(&philos[i]);
			exit(0);
		}
	}
	start_meal_count_thread(set);
	i = -1;
	while (++i < set->ph_count)
		sem_post(set->launch_sem);
	return (0);
}

int	main(int argc, char **argv)
{
	t_sets	set;
	int		status;
	int		i;

	i = 0;
	if (check_args(argc, argv))
		return (1);
	if (init(argv, &set) || create_processes(&set))
		return (error_msg("error: fatal!\n") && make_free_and_destroy(&set));
	sem_wait(set.death_or_ate_sem);
	while (i < set.ph_count)
	{
		sem_post(set.shutdown_signal_sem);
		i++;
	}
	while (waitpid(-1, &status, 0) > 0)
	{
		if (WEXITSTATUS(status))
			return (kill_processes(&set));
	}
	make_free_and_destroy(&set);
	return (0);
}
