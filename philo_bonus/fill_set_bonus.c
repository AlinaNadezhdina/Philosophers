/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_set_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcollen <wcollen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 15:42:05 by wcollen           #+#    #+#             */
/*   Updated: 2022/06/16 12:50:57 by wcollen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	fill_set(t_sets *set)
{
	sem_unlink("/forks");
	sem_unlink("/print");
	sem_unlink("/death");
	sem_unlink("/flag_death");

	set->forks_sem = sem_open("/forks", O_CREAT, 0644, set->ph_count);
	set->print_sem = sem_open("/print", O_CREAT, 0644, 1);
	set->death_sem = sem_open("/death", O_CREAT, 0644, 0);
	set->death_flag_sem = sem_open("/flag_death", O_CREAT, 0644, 1);
	set->flag_deth = 0;
	set->start_time = get_time_now();	 
}
