/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcollen <wcollen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 11:02:07 by wcollen           #+#    #+#             */
/*   Updated: 2022/06/15 23:26:17 by wcollen          ###   ########.fr       */
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
#include  <signal.h>

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
	sem_t		*forks_sem;
	sem_t		*print_sem;
	sem_t		*death_sem;
	sem_t		*death_flag_sem;	
}t_sets;

typedef struct s_philo
{
	pthread_t	thread;
	t_sets		*set;
	pid_t		pid;
	int			num;
	long		last_eating;
	long		ph_cnt_eating;
	sem_t		*ph_access_sem;
	int			ph_ate_flag;
}t_philo;

//================ft_atoi_bonus.c================//
int		ft_atoi(const char *str);

//===============detect_errors_bonus.c============//
int		is_negative_args(int count, char **arg);
int		error_msg(char *str);

//==============parse_args_bonus.c============//
int		parse_args(char **argv, t_sets	*set);
int		check_args(int argc, char **argv, t_sets *set);

//==============init_types_bonus.c================//
int init_philos(t_philo **philos, t_sets *set);

//================fill_set_bonus.c=============//
void	fill_set(t_sets *set);

//===============check_life_bonus.c============//
void	*check_life(void *param);

//=================utils_bonus.c===============//
long	get_time_now();
void	smart_sleep(unsigned long time_to_sleep);
void	print(t_philo *philo, char *str);
void	print_die(t_philo *philo);
int		are_you_already_dead(t_sets *set);


//==================free_and_destroy.c=======//
void	make_free_and_destroy(t_philo *philos, t_sets *set);
#endif