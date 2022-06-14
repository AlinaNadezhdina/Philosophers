/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_set.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcollen <wcollen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 13:19:19 by wcollen           #+#    #+#             */
/*   Updated: 2022/06/14 13:01:34 by wcollen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	assign_last_taken_forks(t_sets *set)
{
	int	i;
	int min_f;
	int	max_f;

	i = 0;
	while (i < set->ph_count)
	{
		min_f = set->philos[i].min_fork_id;
		max_f = set->philos[i].max_fork_id;
		set->forks[min_f].last_taken_by = set->philos[i].num;
		if (i + 1 < set->ph_count)
		{	
			set->forks[max_f].last_taken_by = set->philos[i].num;
		}
		i += 2;
	}
}

void	fill_set(t_sets *set)
{
	int	i;
	
	set->flag_deth = 0;
	pthread_mutex_init(&(set->write), NULL);
	pthread_mutex_init(&(set->flag_deth_mutex), NULL);
	set->start_time = get_time_now();
	i = -1;	
	while(++i < set->ph_count)
	{	
		pthread_mutex_init(&(set->forks[i].usage), NULL);
		pthread_mutex_init(&(set->forks[i].access), NULL);
		pthread_mutex_init(&(set->philos[i].philo_access_mutex), NULL);
		set->philos[i].num = i + 1;
		set->philos[i].ph_cnt_eating = 0;
		set->philos[i].write = &(set->write);
		set->philos[i].sets = set;
		set->philos[i].ph_ate_flag = 0;
		set->philos[i].min_fork_id = i % (set->ph_count);
		set->philos[i].max_fork_id = (i + set->ph_count - 1) % set->ph_count;
		set->forks[i].last_taken_by = 0;	
	}
	assign_last_taken_forks(set);
}
