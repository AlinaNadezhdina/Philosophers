/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcollen <wcollen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 12:17:36 by wcollen           #+#    #+#             */
/*   Updated: 2022/06/24 18:28:09 by wcollen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

sem_t	*open_semaphore(char *name, int val)
{
	sem_t	*i;

	sem_unlink(name);
	i = sem_open(name, O_CREAT, 0644, val);
	return (i);
}

int	init_semaphores(t_sets *set)
{
	char *sem_name;

	set->forks_sem = open_semaphore("/forks", set->ph_count);
	set->queue_sems = malloc(sizeof(sem_t*) * set->ph_count);
	for (int i = 0; i < set->ph_count; i++)
	{
		sem_name = make_semaphore_name(i);
		sem_unlink(sem_name); // also close when ending the program
		sem_t *queue_sem = sem_open(sem_name, O_CREAT, 0644, i % 2);
		free(sem_name);
		if (queue_sem < 0)
			return (1);
		set->queue_sems[i] = queue_sem;
	}
	set->print_sem = open_semaphore("/print", 1);
	set->death_or_ate_sem = open_semaphore("/death_or_ate_sem",  0);// семафор выставляется в 1 если кто-то умер
	set->shutdown_signal_sem = open_semaphore("/shutdown_sem", 0);
	set->death_flag_sem = open_semaphore("/flag_death", 1);//семафор для флага смерти между 3 потоками процесса филлософа
	if (set->forks_sem < 0 || set->print_sem < 0 || set->death_or_ate_sem < 0 
			|| set->death_flag_sem < 0 || set->shutdown_signal_sem < 0)
		return (1);
	return (0);
}

int	init_philos(t_sets *set)
{
	int	i;

	i = 0;
	while (i < set->ph_count)
	{
		set->philos[i].num = i + 1;

		set->philos[i].ph_access_sem = open_semaphore("/ph_access_sem", 1);
		if (set->philos[i].ph_access_sem < 0)
			return (1);
		set->philos[i].eat_cnt_sem = open_semaphore("/eat_cnt_sem", 0);
		if (set->philos[i].eat_cnt_sem < 0)
			return (1);
		set->philos[i].ph_cnt_eating = 0;
		set->philos[i].set = set;
		set->philos[i].last_eating = get_time_now();
		i++;
	}
	return (0);
}

int init(char **argv, t_sets *set)
{	
	set->flag_death = 0;
	set->start_time = get_time_now();
	set->ph_count = ft_atoi(argv[1]);
	set->time_to_die = ft_atoi(argv[2]);
	set->time_to_eat  = ft_atoi(argv[3]);
	set->time_to_sleep  = ft_atoi(argv[4]);
	if(argv[5])
		set->cnt_eatings  = ft_atoi(argv[5]);
	else
		set->cnt_eatings  = -1;
	if (set->time_to_die == 0 || set->time_to_eat == 0 || set->time_to_sleep == 0)
		return (error_msg("error: wrong arguments value"));
	set->philos = malloc(sizeof(t_philo) * set->ph_count);
	if (!set->philos)
		return (1);
	if (init_philos(set))
		return (1);
	return (init_semaphores(set));
}

int	check_args(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (error_msg("error: wrong arguments count!"));
	if (is_negative_args(argc - 1, &argv[1]))
		return (error_msg("error: some argument isn't a positive int!"));
	return (0);
}

