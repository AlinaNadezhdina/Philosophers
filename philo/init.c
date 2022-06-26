/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcollen <wcollen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 12:47:26 by wcollen           #+#    #+#             */
/*   Updated: 2022/06/23 16:50:33 by wcollen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	assign_last_taken_forks(t_sets *set)
{
	int	i;
	int	min_f;
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
	while (++i < set->ph_count)
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

int	parse_args(char **argv, t_sets	*set)
{
	set->ph_count = ft_atoi(argv[1]);
	set->time_to_die = ft_atoi(argv[2]);
	set->time_to_eat = ft_atoi(argv[3]);
	set->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		set->cnt_eatings = ft_atoi(argv[5]);
	else
		set->cnt_eatings = -1;
	if (set->time_to_die == 0 || set->time_to_eat == 0
		|| set->time_to_sleep == 0)
		return (1);
	return (0);
}

int	init(char **argv, t_sets *set)
{
	if (parse_args(argv, set))
		return (error_msg("Wrong arguments value"));
	set->threads = malloc(sizeof(pthread_t) * set->ph_count);
	if (!set->threads)
	{
		return (error_msg("Pthreads malloc error!\n"));
	}
	set->forks = malloc(sizeof(t_fork) * set->ph_count);
	if (!set->forks)
	{
		free(set->threads);
		return (error_msg("Mutexes malloc error!\n"));
	}
	set->philos = malloc(sizeof(t_philo) * set->ph_count);
	if (!set->philos)
	{
		free(set->threads);
		free(set->forks);
		return (error_msg("Philo array malloc error!\n"));
	}
	fill_set(set);
	return (0);
}
