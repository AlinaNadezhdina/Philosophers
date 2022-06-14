/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcollen <wcollen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 11:02:07 by wcollen           #+#    #+#             */
/*   Updated: 2022/06/08 13:04:47 by wcollen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdlib.h>
#include  <semaphore.h>

typedef struct s_sets
{
	int			flag_deth;
	int			ph_count;
	long		start_time;
	long		time_to_die;
	long		time_to_eat;
	long 		time_to_sleep;
	long 		cnt_eatings;
	pthread_t	th_live_cntrl;
	t_philo		*philos;
	sem_t		*forks_sem;
	sem_t		*print_sem;
	
}t_sets;

typedef struct s_philo
{
	pthread_t	thread;
	t_sets		*set;
	pid_t		pid;
	int			num;
	int			fork_l;
	int			fork_r;
	long		last_eating;
	long		ph_cnt_eating;
}t_philo;

//================ft_atoi_bonus.c================//
int		ft_atoi(const char *str);

//==============parse_args_bonus.c============//
int		parse_args(char **argv, t_sets	*set);
int		check_args(int argc, char **argv, t_sets *set);
#endif