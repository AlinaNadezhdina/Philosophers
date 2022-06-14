/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcollen <wcollen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 17:39:29 by wcollen           #+#    #+#             */
/*   Updated: 2022/06/14 13:20:53 by wcollen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdlib.h>

struct s_sets;

typedef struct s_philo
{
	int					num;
	long				last_eating;
	long				ph_cnt_eating;
	int					min_fork_id;
	int					max_fork_id;
	pthread_mutex_t		*write;
	struct s_sets		*sets;
	pthread_mutex_t		philo_access_mutex;
	int					ph_ate_flag;
}t_philo;

typedef struct s_fork
{
	int 				last_taken_by;//номер философа, который последним брал вилку
	pthread_mutex_t		access;// mutex for last_taken_by;
	pthread_mutex_t		usage;//fork mutex

}t_fork;

typedef struct s_sets
{
	int					flag_deth;
	int					ph_count;
	long				start_time;
	long				time_to_die;
	long				time_to_eat;
	long 				time_to_sleep;
	long 				cnt_eatings;
	t_philo				*philos;
	pthread_t			*threads;
	pthread_mutex_t		write;
	pthread_t			th_live_cntrl;
	pthread_mutex_t		flag_deth_mutex;
	t_fork				*forks;

}t_sets;

//================philo.c================//
void	philo_eat(t_philo *philo);
int		are_you_already_dead(t_sets *set);

//================ft_atoi.c================//
int		ft_atoi(const char *str);

//==============parse_args.c============//
int		parse_args(char **argv, t_sets	*set);
int		check_args(int argc, char **argv, t_sets *set);

//===============detect_errors.c============//
int		is_negative_args(int count, char **arg);
int		error_msg(char *str);

//==============init_types.c===============//
int		init_types(t_sets *set);

//==============fill_set.c=================//
void	fill_set(t_sets *set);

//=============fork_functions.c===========//
void	wait_for_fork(t_philo *philo, int fork_id);
void	set_fork_last_taken_by(t_philo *philo, int fork_id);

//================utils.c================//
void	print_die(t_philo *philo);
long	get_time_now();
void	smart_sleep(unsigned long time_to_sleep);
void	print(t_philo *philo, char *str);
int		are_you_already_dead(t_sets *set);

//================check_life.c================//
void	*check_live(void *param);

//===============free_and_destroy.c=========//
void	make_join(t_sets *set);
void	make_free_and_destroy(t_sets *set);

#endif