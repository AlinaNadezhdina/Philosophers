/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_destroy_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcollen <wcollen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 18:23:06 by wcollen           #+#    #+#             */
/*   Updated: 2022/06/22 13:25:02 by wcollen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	make_free_and_destroy(t_sets *set)
{
	int		i;
	t_philo *philos;

	i = 0;
	philos = set->philos;
	printf("sem_wait(set->death_sem)  make_free_and_destroy\n");
	while (i < set->ph_count)
	{	
		// sem_close(philos[i].ph_access_sem);
		// sem_close(philos[i].eat_cnt_sem);
		i++;
	}
	sem_unlink("forks");
	sem_unlink("print");
	sem_unlink("death");
	sem_unlink("flag_death");
	sem_close(set->forks_sem);
	// sem_close(set->death_flag_sem);
	// sem_close(set->death_sem);
	// sem_close(set->print_sem);
	free(philos);
	return (0);
}

int	kill_processes(t_sets *set)
{
	int	i;

	i = -1;
	while (i < set->ph_count)
	{	
		kill(set->philos[++i].pid, SIGTERM);
	}
	return (0);
}