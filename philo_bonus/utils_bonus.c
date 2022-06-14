/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcollen <wcollen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 12:23:30 by wcollen           #+#    #+#             */
/*   Updated: 2022/06/08 14:31:49 by wcollen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time_now()
{
	struct timeval time;

	gettimeofday(&time, NULL);
	return (long)(time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	smart_sleep(unsigned long time_to_sleep)
{
	unsigned long start;
	
	start = get_time_now();
	while(get_time_now() - start <= time_to_sleep)
		usleep(1);
}

// void	print(t_philo *philo, char *str)
// {
// 	unsigned long	time;

// 	if (are_you_already_dead(philo->sets))
// 		return ;
// 	time = get_time_now();
// 	pthread_mutex_lock(philo->write);
// 	printf("%ld %d %s\n", time - philo->sets->start_time, philo->num, str);
// 	pthread_mutex_unlock(philo->write);
// }

// void	print_die(t_philo *philo)
// {
// 	unsigned long	time;

// 	time = get_time_now();
// 	pthread_mutex_lock(philo->write);
// 	printf("\033[31m%ld %d died \033[37m",  time - philo->sets->start_time, philo->num);
// 	pthread_mutex_unlock(philo->write);
// }

// int	are_you_already_dead(t_sets *set)
// {
// 	int death;

// 	pthread_mutex_lock(&(set->flag_deth_mutex));
// 	death = set->flag_deth;
// 	pthread_mutex_unlock(&(set->flag_deth_mutex));
// 	return (death);
//}