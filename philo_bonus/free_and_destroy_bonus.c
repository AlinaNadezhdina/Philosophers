/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_destroy_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcollen <wcollen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 18:23:06 by wcollen           #+#    #+#             */
/*   Updated: 2022/06/16 12:38:38 by wcollen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	make_free_and_destroy(t_philo *philos, t_sets *set)
{
	int	i;

	i = 0;
	sem_wait(set->death_sem);
	while (i < set->ph_count)
	{	
		sem_close(philos[i].ph_access_sem);
		kill(philos[i].pid, SIGTERM);
		i++;
	}
	free(philos);
	sem_close(set->forks_sem);
	sem_close(set->death_flag_sem);
	sem_close(set->death_sem);
	sem_close(set->print_sem);
}