/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_types_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcollen <wcollen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 12:17:36 by wcollen           #+#    #+#             */
/*   Updated: 2022/06/08 14:36:37 by wcollen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int init_types(t_sets *set)
{
	set->philos = malloc(sizeof(t_philo) * set->ph_count);
	if (!set->philos)
	{
		printf("Pthreads creating error!\n");
		return (1);
	}
	return (0);
}

int	fill_set(t_sets *set)
{
	int	i;
	sem_unlink("/forks");
	sem_unlink("/print");

	set->forks_sem = sem_open("/forks", O_CREAT, 0644, set->ph_count);
	set->print_sem = sem_open("/print", O_CREAT, 0644, 1);
	set->flag_deth = 0;
	set->start_time = get_time_now();
	i = -1;	
	while(++i < set->ph_count)
	{	
		set->philos[i].num = i + 1;
		set->philos[i].ph_cnt_eating = 0;
		set->philos[i].set = set;
	}
}