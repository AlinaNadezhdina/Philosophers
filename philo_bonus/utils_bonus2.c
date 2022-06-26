/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcollen <wcollen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 22:38:59 by wcollen           #+#    #+#             */
/*   Updated: 2022/06/25 23:36:43 by wcollen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

char	*make_semaphore_name(int num)
{
	char	*temp;
	char	*sem_name;

	temp = ft_itoa(num);
	sem_name = ft_strjoin("queue", temp);
	free(temp);
	return (sem_name);
}

int	single_philo_must_die(t_philo *philo)
{
	t_sets	*set;

	set = philo->set;
	if (set->ph_count == 1)
	{
		while (!are_you_already_dead(philo->set))
			usleep(1);
		return (1);
	}
	return (0);
}

int	not_count_food_if_ph_died(t_philo *philo, int already_post_flag)
{
	if (are_you_already_dead(philo->set))
	{
		if (already_post_flag == 0)
			sem_post(philo->eat_cnt_sem);
		return (1);
	}
	return (0);
}
