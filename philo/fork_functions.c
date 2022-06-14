/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcollen <wcollen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 13:19:04 by wcollen           #+#    #+#             */
/*   Updated: 2022/06/14 13:21:04 by wcollen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_for_fork(t_philo *philo, int fork_id)
{
	int	fork_last_taken_by;

	while (1)
	{
		pthread_mutex_lock(&philo->sets->forks[fork_id].access);
		fork_last_taken_by = philo->sets->forks[fork_id].last_taken_by;
		pthread_mutex_unlock(&philo->sets->forks[fork_id].access);
		if (fork_last_taken_by != philo->num)
			return ;
		usleep(100);
	}
}

void	set_fork_last_taken_by(t_philo *philo, int fork_id)
{
	pthread_mutex_lock(&philo->sets->forks[fork_id].access);
	philo->sets->forks[fork_id].last_taken_by = philo->num;
	pthread_mutex_unlock(&philo->sets->forks[fork_id].access);
}
