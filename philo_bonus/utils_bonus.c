/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcollen <wcollen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 12:23:30 by wcollen           #+#    #+#             */
/*   Updated: 2022/06/28 17:29:49 by wcollen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long	get_time_now(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((long)(time.tv_sec * 1000 + time.tv_usec / 1000));
}

void	print(t_philo *philo, char *str)
{
	long	time;

	if (are_you_already_dead(philo->set))
		return ;
	time = get_time_now();
	sem_wait(philo->set->print_sem);
	printf("|%ld|\t\t %d %s\n", time - philo->set->start_time, philo->num, str);
	sem_post(philo->set->print_sem);
}

void	print_die(t_philo *philo)
{
	long	time;

	time = get_time_now();
	sem_wait(philo->set->print_sem);
	printf("|\033[31m%ld|\t\t %d died \033[37m\n",
		time - philo->set->start_time, philo->num);
}

int	are_you_already_dead(t_sets *set)
{
	int	death;

	sem_wait(set->death_flag_sem);
	death = set->flag_death;
	sem_post(set->death_flag_sem);
	return (death);
}

void	set_flag_death_value(t_sets *set)
{
	sem_wait(set->death_flag_sem);
	set->flag_death = 1;
	sem_post(set->death_flag_sem);
}
