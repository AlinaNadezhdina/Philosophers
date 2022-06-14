/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_destroy.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcollen <wcollen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 14:28:31 by wcollen           #+#    #+#             */
/*   Updated: 2022/06/13 19:51:19 by wcollen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	make_join(t_sets *set)
{
	int	i;

	i = 0;
	while (i < set->ph_count)
	{
		pthread_join(set->threads[i], NULL);
		i++;
	}
	pthread_join(set->th_live_cntrl, NULL);
}

void	make_free_and_destroy(t_sets *set)
{
	int	i;

	i = 0;
	while (i < set->ph_count)
	{
		pthread_mutex_destroy(&(set->forks[i].access));
		pthread_mutex_destroy(&(set->forks[i].usage));
		pthread_mutex_destroy(&(set->philos[i].philo_access_mutex));
		i++;
	}
	pthread_mutex_destroy(&(set->write));
	pthread_mutex_destroy(&(set->flag_deth_mutex));
	
	free(set->philos);
	free(set->forks);
	free(set->threads);
}