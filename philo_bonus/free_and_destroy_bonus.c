/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_destroy_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcollen <wcollen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 18:23:06 by wcollen           #+#    #+#             */
/*   Updated: 2022/06/25 23:15:59 by wcollen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	make_unlink_and_close(t_sets *set)
{
	sem_unlink("/forks");
	sem_unlink("/print");
	sem_unlink("/death_or_ate_sem");
	sem_unlink("/flag_death");
	sem_unlink("/shutdown_sem");
	sem_unlink("/launch");
	sem_close(set->forks_sem);
	sem_close(set->print_sem);
	sem_close(set->death_or_ate_sem);
	sem_close(set->death_flag_sem);
	sem_close(set->shutdown_signal_sem);
	sem_close(set->launch_sem);
}

int	make_free_and_destroy(t_sets *set)
{
	int		i;
	t_philo	*philos;
	char	*sem_name;

	i = 0;
	philos = set->philos;
	while (i < set->ph_count)
	{	
		sem_close(philos[i].ph_access_sem);
		sem_unlink("/ph_access_sem");
		sem_close(philos[i].eat_cnt_sem);
		sem_unlink("/eat_cnt_sem");
		sem_close(set->queue_sems[i]);
		sem_name = make_semaphore_name(i);
		sem_unlink(sem_name);
		free(sem_name);
		i++;
	}
	make_unlink_and_close(set);
	free(set->queue_sems);
	free(set->philos);
	return (0);
}

int	kill_processes(t_sets *set)
{
	int	i;

	i = 0;
	while (i < set->ph_count)
	{	
		kill(set->philos[i].pid, SIGTERM);
		i++;
	}
	return (0);
}
