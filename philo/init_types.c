/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_types.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcollen <wcollen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 12:47:26 by wcollen           #+#    #+#             */
/*   Updated: 2022/06/14 16:13:04 by wcollen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int init_types(t_sets *set)
{
	set->threads = malloc(sizeof(pthread_t) * set->ph_count);
	if (!set->threads)
	{
		printf("Pthreads create error!\n");
		return (1);
	}
	set->forks = malloc(sizeof(t_fork) * set->ph_count);
	if (!set->forks)
	{
		printf("Mutexes creating error!\n");
		free(set->threads);
		return (1);
	}
	set->philos = malloc(sizeof(t_philo) * set->ph_count);
	if (!set->philos)
	{
		printf("Philo array creating error!\n");
		free(set->threads);
		free(set->forks);
		return (1);
	}
	return (0);
}
